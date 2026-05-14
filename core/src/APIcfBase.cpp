#include "APIcfBase.h"
#include "../include/v8reader_core/io/IByteStream.h"
#include "../include/v8reader_core/io/MemoryByteStream.h"
#include "../include/v8reader_core/io/StdFileStream.h"


#include "UZlib.h"
#pragma comment (lib, "zlibstatic.lib")

#include <memory>
#include <algorithm>
#include <cwctype>
#include <stdexcept>

#define CHUNK 65536

// массив для преобразования числа в шестнадцатиричную строку
const char _bufhex[] = "0123456789abcdef";

// шаблон заголовка блока
const char _block_header_template[]    = "\r\n00000000 00000000 00000000 \r\n";
const char _empty_catalog_template[16] = {0xff,0xff,0xff,0x7f,0,2,0,0,0,0,0,0,0,0,0,0};
const char _empty_catalog_template8316[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

using v8reader::core::io::IByteStream;
using v8reader::core::io::MemoryByteStream;
using v8reader::core::io::SeekOrigin;
using v8reader::core::io::FileOpenMode;
using v8reader::core::io::StdFileStream;

namespace
{
static void ReadBufferExact(IByteStream& stream, void* buffer, std::size_t count)
{
	const std::size_t read = stream.Read(buffer, count);
	if(read != count)
		throw std::runtime_error("Unexpected EOF while reading stream");
}

static void WriteBufferExact(IByteStream& stream, const void* buffer, std::size_t count)
{
	const std::size_t written = stream.Write(buffer, count);
	if(written != count)
		throw std::runtime_error("Failed to write all bytes to stream");
}

static void CopyFromStream(IByteStream& destination, IByteStream& source, std::size_t count)
{
	ByteVector chunk(CHUNK);
	std::size_t remaining = count;
	while(remaining > 0)
	{
		const std::size_t toRead = std::min(remaining, chunk.size());
		const std::size_t bytesRead = source.Read(chunk.data(), toRead);
		if(bytesRead == 0)
			break;

		WriteBufferExact(destination, chunk.data(), bytesRead);
		remaining -= bytesRead;
	}
}

static std::wstring Utf16ToWide(const Utf16String& value)
{
	return std::wstring(value.begin(), value.end());
}

static Utf16String WideToUtf16(const std::wstring& value)
{
	return Utf16String(value.begin(), value.end());
}

static void SetFileTimesByPath(const std::filesystem::path& path, const FILETIME* createTime, const FILETIME* accessTime, const FILETIME* writeTime)
{
	HANDLE file = CreateFileW(path.c_str(),
		FILE_WRITE_ATTRIBUTES,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(file == INVALID_HANDLE_VALUE)
		return;

	SetFileTime(file, createTime, accessTime, writeTime);
	CloseHandle(file);
}

static Utf16String Utf16ToUpper(const Utf16String& value)
{
	Utf16String result(value);
	if(result.empty())
		return result;

	CharUpperBuffW(reinterpret_cast<wchar_t*>(result.data()), static_cast<DWORD>(result.size()));
	return result;
}

static bool Utf16EqualsIgnoreCase(const Utf16String& left, const Utf16String& right)
{
	if(left.size() != right.size())
		return false;

	return CompareStringOrdinal(
		reinterpret_cast<const wchar_t*>(left.c_str()),
		static_cast<int>(left.size()),
		reinterpret_cast<const wchar_t*>(right.c_str()),
		static_cast<int>(right.size()),
		TRUE) == CSTR_EQUAL;
}

} // namespace

#ifdef __cplusplus
int max(int value1, int value2)
{
	return ( (value1 > value2) ? value1 : value2);
}

int min(int value1, int value2)
{
	return ( (value1 < value2) ? value1 : value2);
}
#endif

//===========================================================================
// преобразует шестнадцатиричную восьмисимвольную строку в число
int hex_to_int(char* hexstr)
{
	int res = 0;
	int sym;
	for(int i = 0; i < 8; i++)
	{
		sym = hexstr[i];
		if(sym >= 'a')
        	sym -= 'a' - '9' - 1;
		else if(sym > '9')
        	sym -= 'A' - '9' - 1;
		sym -= '0';
		res = (res << 4) | (sym & 0xf);
	}
	return res;
}

int hex_to_int16(char* hexstr)
{
	int res = 0;
	int sym;
	for(int i = 0; i < 16; i++)
	{
		sym = hexstr[i];
		if(sym >= 'a')
        	sym -= 'a' - '9' - 1;
		else if(sym > '9')
        	sym -= 'A' - '9' - 1;
		sym -= '0';
		res = (res << 4) | (sym & 0xf);
	}
	return res;
}


//===========================================================================
// преобразует число в шестнадцатиричную восьмисимвольную строку
char* int_to_hex(char* hexstr, int dec)
{
	int _t1 = dec;
	int _t2;
	for(int i = 7; i >= 0; i--)
	{
		_t2 = _t1 & 0xf;
		hexstr[i] = _bufhex[_t2];
		_t1 >>= 4;
	}
	return hexstr;
}

static std::unique_ptr<MemoryByteStream> read_block_core(IByteStream& stream_from, int start)
{
	char temp_buf[32];
	int len, curlen, pos, readlen;
	auto out = std::make_unique<MemoryByteStream>();

	out->Seek(0, SeekOrigin::Begin);
	out->SetSize(0);

	if(start < 0 || start == V8_FF_SIGNATURE || static_cast<std::uint64_t>(start) > stream_from.Size())
		return out;

	stream_from.Seek(start, SeekOrigin::Begin);
	stream_from.Read(temp_buf, 31);

	len = hex_to_int(&temp_buf[2]);
	if(!len)
		return out;
	curlen = hex_to_int(&temp_buf[11]);
	start  = hex_to_int(&temp_buf[20]);

	readlen = min(len, curlen);
	if(readlen > 0)
	{
		ByteVector chunk(readlen);
		const std::size_t bytes = stream_from.Read(chunk.data(), static_cast<std::size_t>(readlen));
		out->Write(chunk.data(), bytes);
	}

	pos = readlen;

	while(start != V8_FF_SIGNATURE)
	{
		stream_from.Seek(start, SeekOrigin::Begin);
		stream_from.Read(temp_buf, 31);

		curlen = hex_to_int(&temp_buf[11]);
		start = hex_to_int(&temp_buf[20]);

		readlen = min(len - pos, curlen);
		if(readlen > 0)
		{
			ByteVector chunk(readlen);
			const std::size_t bytes = stream_from.Read(chunk.data(), static_cast<std::size_t>(readlen));
			out->Write(chunk.data(), bytes);
		}
		pos += readlen;
	}

	out->Seek(0, SeekOrigin::Begin);
	return out;
}

static std::unique_ptr<MemoryByteStream> read_block_16_core(IByteStream& stream_from, __int64 start)
{
	char temp_buf[55];
	int len, curlen, pos, readlen;
	auto out = std::make_unique<MemoryByteStream>();

	out->Seek(0, SeekOrigin::Begin);
	out->SetSize(0);

	if(start < 0 || start == V8_FF64_SIGNATURE || static_cast<std::uint64_t>(start) > stream_from.Size())
		return out;

	stream_from.Seek(start, SeekOrigin::Begin);
	stream_from.Read(temp_buf, 55);

	len = hex_to_int16(&temp_buf[2]);
	if(!len)
		return out;
	curlen = hex_to_int16(&temp_buf[19]);
	start = hex_to_int16(&temp_buf[36]);

	readlen = min(len, curlen);
	if(readlen > 0)
	{
		ByteVector chunk(readlen);
		const std::size_t bytes = stream_from.Read(chunk.data(), static_cast<std::size_t>(readlen));
		out->Write(chunk.data(), bytes);
	}

	pos = readlen;

	while(start != V8_FF64_SIGNATURE)
	{
		stream_from.Seek(start + V8_OFFSET_8316, SeekOrigin::Begin);
		stream_from.Read(temp_buf, 55);

		curlen = hex_to_int16(&temp_buf[19]);
		start  = hex_to_int16(&temp_buf[36]);

		readlen = min(len - pos, curlen);
		if(readlen > 0)
		{
			ByteVector chunk(readlen);
			const std::size_t bytes = stream_from.Read(chunk.data(), static_cast<std::size_t>(readlen));
			out->Write(chunk.data(), bytes);
		}
		pos += readlen;
	}

	out->Seek(0, SeekOrigin::Begin);
	return out;
}

//===========================================================================
// читает блок из потока каталога stream_from, собирая его по страницам
IByteStream* read_block(IByteStream& stream_from, int start, IByteStream* stream_to = NULL)
{
	if(!stream_to)
		stream_to = new MemoryByteStream;

	stream_to->Seek(0, SeekOrigin::Begin);
	stream_to->SetSize(0);

	std::unique_ptr<MemoryByteStream> block = read_block_core(stream_from, start);
	if(block->Size() > 0)
	{
		const std::vector<std::uint8_t>& data = block->Data();
		WriteBufferExact(*stream_to, data.data(), data.size());
	}
	stream_to->Seek(0, SeekOrigin::Begin);
	return stream_to;
}

//===========================================================================
// читает блок из потока каталога stream_from, собирая его по страницам
IByteStream* read_block_16(IByteStream& stream_from, __int64 start, IByteStream* stream_to = NULL)
{
	if(!stream_to)
		stream_to = new MemoryByteStream;

	stream_to->Seek(0, SeekOrigin::Begin);
	stream_to->SetSize(0);

	std::unique_ptr<MemoryByteStream> block = read_block_16_core(stream_from, start);
	if(block->Size() > 0)
	{
		const std::vector<std::uint8_t>& data = block->Data();
		WriteBufferExact(*stream_to, data.data(), data.size());
	}
	stream_to->Seek(0, SeekOrigin::Begin);
	return stream_to;
}


//===========================================================================
//преобразование времени
void V8timeToFileTime(const __int64* v8t, FILETIME* ft)
{
	FILETIME lft;
	__int64 t = *v8t;
	t -= 504911232000000i64; //504911232000000 = ((365 * 4 + 1) * 100 - 3) * 4 * 24 * 60 * 60 * 10000
	t *= 1000;
	*(__int64*)&lft = t;
	LocalFileTimeToFileTime(&lft, ft);
}

//===========================================================================
void FileTimeToV8time(const FILETIME* ft, __int64* v8t)
{
	FILETIME lft;
	FileTimeToLocalFileTime(ft, &lft);
	__int64 t = *(__int64*)&lft;
	t /= 1000;
	t += 504911232000000i64;
	*v8t = t;
}

//===========================================================================
void setCurrentTime(__int64* v8t)
{
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	FileTimeToV8time(&ft, v8t);
}

//===========================================================================

//********************************************************
// Класс v8file

//===========================================================================
v8file::v8file(v8catalog* _parent, const Utf16String& _name, v8file* _previous,
                          int _start_data, int _start_header,
                          __int64* _time_create, __int64* _time_modify)
{
	Lock = new V8RecursiveMutex();
	is_destructed = false;
	flushed = false;
	parent = _parent;
	name = _name;
	previous = _previous;
	next = NULL;
	data = NULL;
	start_data = _start_data;
	start_header = _start_header;
	is_datamodified = !start_data;
	is_headermodified = !start_header;
	if(previous)
		previous->next = this;
	else
		parent->first = this;
	iscatalog = iscatalog_unknown;
	self = NULL;
	is_opened = false;
	time_create = *_time_create;
	time_modify = *_time_modify;
	selfzipped = false;
	if(parent)
		parent->files[Utf16ToUpper(name)] = this;
}

//===========================================================================
void v8file::GetTimeCreate(FILETIME* ft)
{
	V8timeToFileTime(&time_create, ft);
}

//===========================================================================
void v8file::GetTimeModify(FILETIME* ft)
{
	V8timeToFileTime(&time_modify, ft);
}

//===========================================================================
void v8file::SetTimeCreate(FILETIME* ft)
{
	FileTimeToV8time(ft, &time_create);
}

//===========================================================================
void v8file::SetTimeModify(FILETIME* ft)
{
	FileTimeToV8time(ft, &time_modify);
}

//===========================================================================
void v8file::SaveToFile(const std::filesystem::path& filePath)
{
	FILETIME create, modify;

	StdFileStream fs(filePath, FileOpenMode::CreateTruncate);
	SaveToByteStream(fs);
	GetTimeCreate(&create);
	GetTimeModify(&modify);
	SetFileTimesByPath(filePath, &create, &modify, &modify);
}

//===========================================================================
void v8file::SaveToByteStream(IByteStream& stream)
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return;

	const std::uint64_t sourcePosition = data->Position();
	data->Seek(0, SeekOrigin::Begin);

	ByteVector buffer(CHUNK);
	while(true)
	{
		const std::size_t bytesRead = data->Read(buffer.data(), buffer.size());
		if(bytesRead == 0)
			break;

		WriteBufferExact(stream, buffer.data(), bytesRead);
	}

	data->Seek(static_cast<std::int64_t>(sourcePosition), SeekOrigin::Begin);
}

//===========================================================================
int v8file::GetFileLength()
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	return static_cast<int>(data->Size());
}

//===========================================================================
__int64 v8file::GetFileLength64()
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0l;

	return static_cast<__int64>(data->Size());
}

//===========================================================================
int v8file::Read(void* Buffer, int Start, int Length)
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	data->Seek(Start, SeekOrigin::Begin);
	return static_cast<int>(data->Read(Buffer, static_cast<std::size_t>(Length)));
}

//===========================================================================
int v8file::Read(ByteVector& Buffer, int Start, int Length)
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	if(Length <= 0)
		return 0;

	Buffer.resize(Length);
	data->Seek(Start, SeekOrigin::Begin);
	const int read = static_cast<int>(data->Read(Buffer.data(), static_cast<std::size_t>(Length)));
	if(read >= 0 && read < Length)
		Buffer.resize(read);

	return read;
}

////---------------------------------------------------------------------------
//// Потоконебезопасная функция!
//IByteStream* v8file::get_data()
//{
//	return data;
//}

// дозапись/перезапись частично
int v8file::Write(const void* Buffer, int Start, int Length)
{
//	if(readonly) return 0;
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	setCurrentTime(&time_modify);

	is_headermodified = true;
	is_datamodified = true;

	data->Seek(Start, SeekOrigin::Begin);
	return data->Write(Buffer, Length);
}

//===========================================================================
// дозапись/перезапись частично
int v8file::Write(const ByteVector& Buffer, int Start, int Length)
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	if(Length < 0 || Length > static_cast<int>(Buffer.size()))
		Length = static_cast<int>(Buffer.size());

	setCurrentTime(&time_modify);
	is_headermodified = true;
	is_datamodified = true;
	data->Seek(Start, SeekOrigin::Begin);
	if(Length == 0)
		return 0;

	return data->Write(Buffer.data(), Length);
}

//===========================================================================
// перезапись целиком
int v8file::Write(const void* Buffer, int Length)
{
//	if(readonly) return 0;
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	setCurrentTime(&time_modify);
	is_headermodified = true;
	is_datamodified = true;
	if(data->Size() > static_cast<std::uint64_t>(Length))
		data->SetSize(static_cast<std::uint64_t>(Length));
	data->Seek(0, SeekOrigin::Begin);
	return static_cast<int>(data->Write(Buffer, static_cast<std::size_t>(Length)));
}

// дозапись/перезапись частично
int v8file::Write(IByteStream& Stream, int Start, int Length)
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	setCurrentTime(&time_modify);
	is_headermodified = true;
	is_datamodified = true;
	data->Seek(Start, SeekOrigin::Begin);

	if(Length == 0)
		return 0;

	if(Length < 0)
	{
		const std::uint64_t sourcePos = Stream.Position();
		const std::uint64_t sourceSize = Stream.Size();
		Length = static_cast<int>(sourceSize > sourcePos ? sourceSize - sourcePos : 0);
	}

	int totalWritten = 0;
	ByteVector buffer(CHUNK);
	while(totalWritten < Length)
	{
		const int toRead = min(Length - totalWritten, static_cast<int>(buffer.size()));
		const std::size_t bytesRead = Stream.Read(buffer.data(), static_cast<std::size_t>(toRead));
		if(bytesRead == 0)
			break;

		WriteBufferExact(*data, buffer.data(), bytesRead);
		totalWritten += static_cast<int>(bytesRead);
	}

	return totalWritten;
}

//===========================================================================
// перезапись целиком
int v8file::Write(IByteStream& Stream)
{
	V8ScopedLock guard(Lock);
	if(!is_opened)
		if(!Open())
			return 0;

	setCurrentTime(&time_modify);
	is_headermodified = true;
	is_datamodified = true;

	const std::uint64_t sourceSize = Stream.Size();
	const std::uint64_t sourcePosition = Stream.Position();
	const std::uint64_t remaining = sourceSize > sourcePosition ? sourceSize - sourcePosition : 0;

	if(data->Size() > sourceSize)
		data->SetSize(sourceSize);
	data->Seek(0, SeekOrigin::Begin);

	int totalWritten = 0;
	ByteVector buffer(CHUNK);
	while(static_cast<std::uint64_t>(totalWritten) < remaining)
	{
		const int toRead = min(static_cast<int>(remaining - static_cast<std::uint64_t>(totalWritten)),
							   static_cast<int>(buffer.size()));
		const std::size_t bytesRead = Stream.Read(buffer.data(), static_cast<std::size_t>(toRead));
		if(bytesRead == 0)
			break;

		WriteBufferExact(*data, buffer.data(), bytesRead);
		totalWritten += static_cast<int>(bytesRead);
	}

	return totalWritten;
}

//===========================================================================
Utf16String v8file::GetFileName()
{
	return name;
}

//===========================================================================
Utf16String v8file::GetFileName16()
{
	return name;
}

//===========================================================================
Utf16String v8file::GetFullName()
{
	if(parent) if(parent->file)
	{
		Utf16String fulln = parent->file->GetFullName();
		if(!fulln.empty())
		{
			fulln += u"\\";
			fulln += name;

			return fulln;
		}
	}
	return name;
}

//===========================================================================
Utf16String v8file::GetFullName16()
{
	return GetFullName();
}

//===========================================================================
void v8file::SetFileName(const Utf16String& _name)
{
	name = _name;
	is_headermodified = true;
}

//===========================================================================
void v8file::SetFileName16(const Utf16String& _name)
{
	name = _name;
	is_headermodified = true;
}

//===========================================================================
bool v8file::IsCatalog()
{
	int _filelen;
	int _startempty = -1;
	char _t[32];

	Lock->Acquire();
	if(iscatalog == iscatalog_unknown)
    {
		// эмпирический метод?
		if(!is_opened)
			if(!Open())
				{
					Lock->Release();

					return false;
				}
		_filelen = data->Size();
		if(_filelen == 16)
		{
			data->Seek(0, SeekOrigin::Begin);
			data->Read(_t, 16);
			if(memcmp(_t, _empty_catalog_template, 16) != 0)
			{
				iscatalog = iscatalog_false;
				Lock->Release();

				return false;
			}
			else
			{
				iscatalog = iscatalog_true;
				Lock->Release();

				return true;
			}
		}

		data->Seek(0, SeekOrigin::Begin);
		data->Read(&_startempty, 4);
		if(_startempty != V8_FF_SIGNATURE)
        {
			if(_startempty + 31 >= _filelen)
            {
				iscatalog = iscatalog_false;
				Lock->Release();

				return false;
			}

			data->Seek(_startempty, SeekOrigin::Begin);
			data->Read(_t, 31);

			if(_t[0] != 0xd || _t[1] != 0xa || _t[10] != 0x20 || _t[19] != 0x20 || _t[28] != 0x20 || _t[29] != 0xd || _t[30] != 0xa)
            {
				iscatalog = iscatalog_false;
				Lock->Release();

				return false;
			}
		}
		if(_filelen < 31 + 16)
        {
			iscatalog = iscatalog_false;
			Lock->Release();

			return false;
		}
		data->Seek(16, SeekOrigin::Begin);
		data->Read(_t, 31);
		if(_t[0] != 0xd || _t[1] != 0xa || _t[10] != 0x20 || _t[19] != 0x20 || _t[28] != 0x20 || _t[29] != 0xd || _t[30] != 0xa)
        {
			iscatalog = iscatalog_false;
			Lock->Release();

			return false;
		}
		iscatalog = iscatalog_true;
		Lock->Release();

		return true;
	}
	Lock->Release();

	return iscatalog == iscatalog_true;
}

//---------------------------------------------------------------------------
v8catalog* v8file::GetCatalog()
{
	v8catalog* ret;

	V8ScopedLock guard(Lock);
	if(IsCatalog())
	{
		if(!self)
		{
			self = new v8catalog(this);
		}
		ret = self;
	}
	else
    	ret = NULL;

	return ret;
}

//===========================================================================
v8catalog* v8file::GetParentCatalog()
{
	return parent;
}

//===========================================================================
void v8file::DeleteFile()
{
//	if(readonly) return;
	Lock->Acquire();
	if(parent)
	{
		parent->Lock->Acquire();
		if(next)
		{
			next->Lock->Acquire();
			next->previous = previous;
			next->Lock->Release();
		}
		else
        	parent->last = previous;
		if(previous)
		{
			previous->Lock->Acquire();
			previous->next = next;
			previous->Lock->Release();
		}
		else
        	parent->first = next;

		parent->is_fatmodified = true;
		parent->free_block(start_data);
		parent->free_block(start_header);
		parent->files.erase(Utf16ToUpper(name));
		parent->Lock->Release();
		parent = NULL;
	}

	delete data;

	data = NULL;

	if(self)
	{
		self->data = NULL;
		delete self;
		self = NULL;
	}

	iscatalog = iscatalog_false;
	next = NULL;
	previous = NULL;
	is_opened = false;
	start_data = 0;
	start_header = 0;
	is_datamodified = false;
	is_headermodified = false;
	//Lock->Release();
	//delete this; // суицид
}

//===========================================================================
v8file* v8file::GetNext()
{
	return next;
}

//===========================================================================
bool v8file::Open()
{
	if(!parent)
    	return false;

	V8ScopedLock guard(Lock);

	if(is_opened)
		return true;

    if (parent->is_8316)
    {
        data = parent->read_datablock(start_data, V8_OFFSET_8316);
    }
    else
    {
	    data = parent->read_datablock(start_data);
    }


	is_opened = true;

	return true;
}

//===========================================================================
void v8file::Close()
{
	int _t = 0;

	if(!parent)
    	return;

	V8ScopedLock guard(Lock);

	if(!is_opened)
    	return;

	if(self)
    	if(!self->is_destructed)
		{
			// self->readonly = readonly;
			delete self;
		}

	self = NULL;

//	if(parent->data && !readonly)
	if(parent->data)
	{
		if(is_datamodified || is_headermodified)
		{
			V8ScopedLock parent_guard(parent->Lock);
			if(is_datamodified)
			{
				start_data = parent->write_datablock(*data, start_data, selfzipped);
			}
			if(is_headermodified)
			{
				MemoryByteStream hs;
				WriteBufferExact(hs, &time_create, 8);
				WriteBufferExact(hs, &time_modify, 8);
				WriteBufferExact(hs, &_t, 4);
				WriteBufferExact(hs, name.c_str(), static_cast<std::size_t>(name.size() * sizeof(char16_t)));
				WriteBufferExact(hs, &_t, 4);

				start_header = parent->write_block(hs, start_header, false);
			}
		}
	}
	delete data;
	data = NULL;
	iscatalog = iscatalog_unknown;
	is_opened = false;
	is_datamodified = false;
	is_headermodified = false;
}

//===========================================================================
int v8file::WriteAndClose(IByteStream& Stream, int Length)
{
	int _t = 0;

	V8ScopedLock guard(Lock);
	if(!is_opened)
    	if(!Open())
            return 0;

	if(!parent)
		return 0;

	if(self)
    	delete self;

	self = NULL;

	delete data;
	data = NULL;

	if(parent->data)
	{
		V8ScopedLock parent_guard(parent->Lock);
		start_data = parent->write_datablock(Stream, start_data, selfzipped, Length);
		MemoryByteStream hs;
		WriteBufferExact(hs, &time_create, 8);
		WriteBufferExact(hs, &time_modify, 8);
		WriteBufferExact(hs, &_t, 4);
		WriteBufferExact(hs, name.c_str(), static_cast<std::size_t>(name.size() * sizeof(char16_t)));
		WriteBufferExact(hs, &_t, 4);
		start_header = parent->write_block(hs, start_header, false);

	}
	iscatalog = iscatalog_unknown;
	is_opened = false;
	is_datamodified = false;
	is_headermodified = false;

	if(Length == -1)
    	return static_cast<int>(Stream.Size());

	return Length;
}

//===========================================================================
v8file::~v8file()
{
	Lock->Acquire();
	is_destructed = true;

	Close();

	if(parent)
	{
		if(next)
		{
			next->Lock->Acquire();
			next->previous = previous;
			next->Lock->Release();
		}
		else
		{
			parent->Lock->Acquire();
			parent->last = previous;
			parent->Lock->Release();
		}
		if(previous)
		{
			previous->Lock->Acquire();
			previous->next = next;
			previous->Lock->Release();
		}
		else
		{
			parent->Lock->Acquire();
			parent->first = next;
			parent->Lock->Release();
		}
	}
	delete Lock;
}

//===========================================================================
void v8file::Flush()
{
	int _t = 0;

	V8ScopedLock guard(Lock);
	if(flushed)
		return;
	if(!parent)
		return;
	if(!is_opened)
		return;

	flushed = true;
	if(self)
    	self->Flush();

//	if(parent->data && !readonly)
	if(parent->data)
	{
		if(is_datamodified || is_headermodified)
		{
			V8ScopedLock parent_guard(parent->Lock);
			if(is_datamodified)
			{
				start_data = parent->write_datablock(*data, start_data, selfzipped);
				is_datamodified = false;
			}
			if(is_headermodified)
			{
				MemoryByteStream hs;
				WriteBufferExact(hs, &time_create, 8);
				WriteBufferExact(hs, &time_modify, 8);
				WriteBufferExact(hs, &_t, 4);
				WriteBufferExact(hs, name.c_str(), static_cast<std::size_t>(name.size() * sizeof(char16_t)));
				WriteBufferExact(hs, &_t, 4);

				start_header = parent->write_block(hs, start_header, false);
				is_headermodified = false;
			}
		}
	}
	flushed = false;
}

//===========================================================================

//********************************************************
// Класс v8catalog

bool v8catalog::Is8316()
{
    char _temp_data[8] = "";

	V8ScopedLock guard(Lock);
	data->Seek(V8_OFFSET_8316, SeekOrigin::Begin);
	data->Read(_temp_data, 8);
    return memcmp(_temp_data, _empty_catalog_template8316, 8) == 0;


}

//===========================================================================
bool v8catalog::IsCatalog()
{
	int _filelen;
	int _startempty = -1;
	char _t[32];

	Lock->Acquire();
	if(iscatalogdefined)
	{
		Lock->Release();
		return iscatalog;
	}
	iscatalogdefined = true;
	iscatalog = false;

	// эмпирический метод?
	_filelen = data->Size();
	if(_filelen == 16)
	{
		data->Seek(0, SeekOrigin::Begin);
		data->Read(_t, 16);
		if(memcmp(_t, _empty_catalog_template, 16) != 0)
		{
			Lock->Release();
			return false;
		}
		else
		{
			iscatalog = true;
			Lock->Release();
			return true;
		}
	}

	data->Seek(0, SeekOrigin::Begin);
	data->Read(&_startempty, 4);
	if(_startempty != V8_FF_SIGNATURE)
    {
		if(_startempty + 31 >= _filelen)
		{
			Lock->Release();
			return false;
		}
		data->Seek(_startempty, SeekOrigin::Begin);
		data->Read(_t, 31);
		if(_t[0] != 0xd || _t[1] != 0xa || _t[10] != 0x20 || _t[19] != 0x20 || _t[28] != 0x20 || _t[29] != 0xd || _t[30] != 0xa)
		{
			Lock->Release();
			return false;
		}
	}
	if(_filelen < 31 + 16)
	{
		Lock->Release();
		return false;
	}
	data->Seek(16, SeekOrigin::Begin);
	data->Read(_t, 31);
	if(_t[0] != 0xd || _t[1] != 0xa || _t[10] != 0x20 || _t[19] != 0x20 || _t[28] != 0x20 || _t[29] != 0xd || _t[30] != 0xa)
	{
		Lock->Release();
		return false;
	}
	iscatalog = true;
	Lock->Release();

	return true;
}

//===========================================================================
// создать каталог из физического файла .cf
v8catalog::v8catalog(const std::filesystem::path& path)
{
	Lock = new V8RecursiveMutex();
	iscatalogdefined = false;

	std::wstring ext = path.extension().wstring();
	std::transform(ext.begin(), ext.end(), ext.begin(), towlower);
	const bool isCfuExt = ext == L".cfu";

	if(isCfuExt)
	{
		is_cfu = true;
		zipped = false;
		data = new MemoryByteStream();

		if(!std::filesystem::exists(path))
		{
			WriteBufferExact(*data, _empty_catalog_template, 16);
			cfu = new StdFileStream(path, FileOpenMode::CreateTruncate);
		}
		else
		{
			cfu = new StdFileStream(path, FileOpenMode::ReadWrite);
			ZInflateStream(*cfu, *data);
		}
	}
	else
	{
		zipped = ext == L".cf" || ext == L".epf" || ext == L".erf" || ext == L".cfe";
		is_cfu = false;

		if(!std::filesystem::exists(path))
		{
			data = new StdFileStream(path, FileOpenMode::CreateTruncate);
			WriteBufferExact(*data, _empty_catalog_template, 16);
			delete data;
		}
		data = new StdFileStream(path, FileOpenMode::ReadWrite);
	}

	file = NULL;
	if(IsCatalog())
    	initialize();
	else
	{
		first = NULL;
		last = NULL;
		start_empty = 0;
		page_size = 0;
		version = 0;
		zipped = false;

		is_fatmodified = false;
		is_emptymodified = false;
		is_modified = false;
		is_destructed = false;
		flushed = false;
		leave_data = false;
	}
}

//===========================================================================
// создать каталог из физического файла
v8catalog::v8catalog(const std::filesystem::path& path, bool _zipped)
{
	Lock = new V8RecursiveMutex();
	iscatalogdefined = false;
	is_cfu = false;
	zipped = _zipped;

	if(!std::filesystem::exists(path))
	{
		data = new StdFileStream(path, FileOpenMode::CreateTruncate);
		WriteBufferExact(*data, _empty_catalog_template, 16);
		delete data;
	}

	data = new StdFileStream(path, FileOpenMode::ReadWrite);

	file = NULL;

    is_8316 = Is8316();

    int curOffset = is_8316 ? V8_OFFSET_8316 : 0;

	if(IsCatalog())
    {
    	initialize(curOffset);
    }
	else
	{
		first = NULL;
		last = NULL;
		start_empty = 0;
		page_size   = 0;
		version     = 0;
		zipped = false;

		is_fatmodified   = false;
		is_emptymodified = false;
		is_modified      = false;
		is_destructed    = false;
		flushed          = false;
		leave_data       = false;
	}
}

//===========================================================================
// создать каталог из потока
v8catalog::v8catalog(IByteStream* stream, bool _zipped, bool leave_stream)
{
	Lock = new V8RecursiveMutex();
	is_cfu = false;
	iscatalogdefined = false;
	zipped = _zipped;
	//data = new MemoryByteStream;
	//CopyFromStream(*data, *stream, static_cast<std::size_t>( 0));
	data = stream;
	file = NULL;
	if(!data->Size())
    	WriteBufferExact(*data, _empty_catalog_template, 16);
	if(IsCatalog())
    	initialize();
	else
	{
		first = NULL;
		last = NULL;
		start_empty = 0;
		page_size = 0;
		version = 0;
		zipped = false;

		is_fatmodified = false;
		is_emptymodified = false;
		is_modified = false;
		is_destructed = false;
		flushed = false;
	}
	leave_data = leave_stream;
}

//===========================================================================
// создать каталог из файла
v8catalog::v8catalog(v8file* f)
{
	is_cfu = false;
	iscatalogdefined = false;
	file = f;
	Lock = file->Lock;
	Lock->Acquire();
	file->Open();
	data = file->data;
	zipped = false;

	if(IsCatalog())
    	initialize();
	else
	{
		first = NULL;
		last = NULL;
		start_empty = 0;
		page_size = 0;
		version = 0;
		zipped = false;

		is_fatmodified = false;
		is_emptymodified = false;
		is_modified = false;
		is_destructed = false;
		flushed = false;
		leave_data = false;
	}
	Lock->Release();
}

//===========================================================================
void v8catalog::initialize(int Offset)
{
	is_destructed = false;
	catalog_header     _ch;
    catalog_header8316 _ch8316;

	Utf16String _name;

	fat_item     _fi;
    fat_item8316 _fi8316;

	char* _temp_buf;

	MemoryByteStream* _file_header;
	IByteStream* _fat;

	v8file* _prev;
	v8file* _file;
	v8file* f;

    int _temp = 0;
	int _countfiles = 0;
    int HeaderSize  = 0;
    int dataStart   = 0;
    int headerStart = 0;

    data->Seek(Offset, SeekOrigin::Begin);
    if (Offset)
    {
	    HeaderSize = 20;
        ReadBufferExact(*data, &_ch8316, HeaderSize);
        start_empty8316 = _ch8316.start_empty;
        page_size = _ch8316.page_size;
        version = _ch8316.version;
    }
    else
    {
	    HeaderSize = 16;
    	ReadBufferExact(*data, &_ch, HeaderSize);
        start_empty = _ch.start_empty;
        page_size = _ch.page_size;
        version = _ch.version;
    }

	first = NULL;
	_prev = NULL;

	_file_header = new MemoryByteStream;

	try
	{
		if(data->Size() > HeaderSize)
		{
	        if (Offset)
            {
				_fat = read_block_16(*data, HeaderSize + Offset);
                _fat->Seek(0, SeekOrigin::Begin);
                _countfiles = _fat->Size() / 24;
            }
            else
            {
                _fat = read_block(*data, HeaderSize);
                _fat->Seek(0, SeekOrigin::Begin);
                _countfiles = _fat->Size() / 12;
            }

			for(int i = 0; i < _countfiles; i++)
            {
                if (Offset)
                {
	                _fat->Read(&_fi8316, 24);
                    read_block_16(*data, _fi8316.header_start + Offset, _file_header);
                }
                else
                {
	                _fat->Read(&_fi, 12);
                    read_block(*data, _fi.header_start, _file_header);
                }

				_file_header->Seek(0, SeekOrigin::Begin);

				_temp_buf = new char[_file_header->Size()];
				_file_header->Read(_temp_buf, _file_header->Size());
				_name = WideToUtf16(reinterpret_cast<const wchar_t*>(_temp_buf + 20));

				dataStart   = Offset ? _fi8316.data_start   + Offset : _fi.data_start;
				headerStart = Offset ? _fi8316.header_start + Offset : _fi.header_start;

                _file = new v8file(this, _name, _prev, dataStart, headerStart, (__int64*)_temp_buf, (__int64*)(_temp_buf + 8));

				delete[] _temp_buf;

				if(!_prev)
                	first = _file;
				_prev = _file;
			}
			delete _file_header;
			delete _fat;
		}
	}
	catch(...)
	{
		f = first;
		while(f)
		{
	//		f->readonly = readonly;
			f->Close();
			f = f->next;
		}

		while(first)
        	delete first;

		iscatalog = false;
		iscatalogdefined = true;

		first = NULL;
		last = NULL;
		start_empty = 0;
		page_size = 0;
		version = 0;
		zipped = false;
	}

	last = _prev;

	is_fatmodified   = false;
	is_emptymodified = false;
	is_modified      = false;
	is_destructed    = false;
	flushed          = false;
	leave_data       = false;
}

//void v8catalog::initialize(int Offset = 0)
//{
//	is_destructed = false;
//	catalog_header _ch;
//	int _temp;
//	LegacyText _name;
//	fat_item _fi;
//	char* _temp_buf;
//	MemoryByteStream* _file_header;
//	IByteStream* _fat;
//	v8file* _prev;
//	v8file* _file;
//	v8file* f;
//	int _countfiles;
//
//	data->Seek(0, SeekOrigin::Begin);
//    //data->Seek(4953, SeekOrigin::Begin);
//	ReadBufferExact(*data, &_ch, 16);
//    //ReadBufferExact(*data, &_ch, 20);
//	start_empty = _ch.start_empty;
//	page_size = _ch.page_size;
//	version = _ch.version;
//
//	first = NULL;
//
//	_file_header = new MemoryByteStream;
//	_prev = NULL;
//	try
//	{
//		if(data->Size() > 16)
//		{
//			_fat = read_block(data, 16);
//            //_fat = read_block(data, 20);
//			_fat->Seek(0, SeekOrigin::Begin);
//            //_fat->Seek(4953, SeekOrigin::Begin);
//			_countfiles = _fat->Size() / 12;
//            //_countfiles = _fat->Size() / 24;
//			for(int i = 0; i < _countfiles; i++){
//				_fat->Read(&_fi, 12);
//				read_block(*data, _fi.header_start, _file_header);
//				_file_header->Seek(0, SeekOrigin::Begin);
//                //_file_header->Seek(4953, SeekOrigin::Begin);
//				_temp_buf = new char[_file_header->Size()];
//				_file_header->Read(_temp_buf, _file_header->Size());
//				_name = (wchar_t*)(_temp_buf + 20);
//				_file = new v8file(this, _name, _prev, _fi.data_start, _fi.header_start, (__int64*)_temp_buf, (__int64*)(_temp_buf + 8));
//				delete[] _temp_buf;
//				if(!_prev) first = _file;
//				_prev = _file;
//			}
//			delete _file_header;
//			delete _fat;
//		}
//	}
//	catch(...)
//	{
//		f = first;
//		while(f)
//		{
//	//		f->readonly = readonly;
//			f->Close();
//			f = f->next;
//		}
//		while(first) delete first;
//
//		iscatalog = false;
//		iscatalogdefined = true;
//
//		first = NULL;
//		last = NULL;
//		start_empty = 0;
//		page_size = 0;
//		version = 0;
//		zipped = false;
//
//	}
//
//	last = _prev;
//
//	is_fatmodified = false;
//	is_emptymodified = false;
//	is_modified = false;
//	is_destructed = false;
//	flushed = false;
//	leave_data = false;
//}


//===========================================================================
void v8catalog::DeleteFile16(const Utf16String& fileName)
{
	V8ScopedLock guard(Lock);
	v8file* f = first;
	while(f)
	{
		if(Utf16EqualsIgnoreCase(f->name, fileName))
		{
			f->DeleteFile();
			delete f;
		}
		f = f->next;
	}
}

//===========================================================================
v8file* v8catalog::GetFile16(const Utf16String& fileName)
{
	V8ScopedLock guard(Lock);
	std::map<Utf16String, v8file*>::const_iterator it = files.find(Utf16ToUpper(fileName));
	if(it == files.end())
		return NULL;

	return it->second;
}

//===========================================================================
v8file* v8catalog::GetFirst()
{
	return first;
}

//===========================================================================
v8file* v8catalog::createFile16(const Utf16String& fileName, bool _selfzipped)
{
	__int64 v8t;
	v8file* f;

	V8ScopedLock guard(Lock);
	std::map<Utf16String, v8file*>::const_iterator it = files.find(Utf16ToUpper(fileName));
	f = it == files.end() ? NULL : it->second;
	if(!f)
	{
		setCurrentTime(&v8t);
		f = new v8file(this, fileName, last, 0, 0, &v8t, &v8t);
		f->selfzipped = _selfzipped;
		last = f;
		is_fatmodified = true;
	}
	return f;
}

//===========================================================================
v8catalog* v8catalog::GetParentCatalog()
{
	if(!file)
    	return NULL;

	return file->parent;
}

//===========================================================================
IByteStream* v8catalog::read_datablock(int start, int offset)
{
	IByteStream* stream;
	IByteStream* stream2;

	if(!start)
		return new MemoryByteStream;

	Lock->Acquire();

    if (offset)
    {
        stream = read_block_16(*data, start);
    }
    else
    {
	    stream = read_block(*data, start);
    }


	Lock->Release();

	if(zipped)
	{
		stream2 = new MemoryByteStream;
		stream->Seek(0, SeekOrigin::Begin);
		ZInflateStream(*stream, *stream2);
		delete stream;
	}
	else
		stream2 = stream;

	return stream2;
}

//===========================================================================
void v8catalog::free_block(int start)
{
	char temp_buf[32];
	int nextstart;
	int prevempty;

	if(!start)
    	return;
	if(start == V8_FF_SIGNATURE)
    	return;

	Lock->Acquire();
	prevempty = start_empty;
	start_empty = start;

	do
	{
		data->Seek(start, SeekOrigin::Begin);
		ReadBufferExact(*data, temp_buf, 31);
		nextstart = hex_to_int(&temp_buf[20]);
		int_to_hex(&temp_buf[2], V8_FF_SIGNATURE);
		if(nextstart == V8_FF_SIGNATURE)
        	int_to_hex(&temp_buf[20], prevempty);
		data->Seek(start, SeekOrigin::Begin);
		WriteBufferExact(*data, temp_buf, 31);
		start = nextstart;
	}
	while(start != V8_FF_SIGNATURE);

	is_emptymodified = true;
	is_modified = true;
	Lock->Release();
}

//===========================================================================
int v8catalog::write_datablock(IByteStream& block, int start, bool _zipped, int len)
{
	MemoryByteStream* stream2;
	MemoryByteStream* stream;
	int ret;

	//if(!file)
	if(zipped || _zipped)
	{
		if(len == -1)
		{
			stream2 = new MemoryByteStream;
			block.Seek(0, SeekOrigin::Begin);
			ZDeflateStream(block, *stream2);
			Lock->Acquire();
			start = write_block(*stream2, start, false);
			ret = start;
			Lock->Release();
			delete stream2;
		}
		else
		{
			stream = new MemoryByteStream;
			CopyFromStream(*stream, block, static_cast<std::size_t>(len));
			stream2 = new MemoryByteStream;
			stream->Seek(0, SeekOrigin::Begin);
			ZDeflateStream(*stream, *stream2);
			delete stream;
			Lock->Acquire();
			start = write_block(*stream2, start, false);
			ret = start;
			Lock->Release();
			delete stream2;
		}
	}
	else
	{
		Lock->Acquire();
		start = write_block(block, start, false, len);
		ret = start;
		Lock->Release();
	}
	return ret;
}

//===========================================================================
int v8catalog::get_nextblock(int start)
{
	int ret;

	Lock->Acquire();
	if(start == 0 || start == V8_FF_SIGNATURE)
	{
		start = start_empty;

		if(start == V8_FF_SIGNATURE)
        	start = data->Size();
	}
	ret = start;
	Lock->Release();
	return ret;
}

//===========================================================================
int v8catalog::write_block(IByteStream& block, int start, bool use_page_size, int len)
{
	char temp_buf[32];
	char* _t;
	int firststart, nextstart, blocklen, curlen;
	bool isfirstblock = true;
	bool addwrite = false; // признак, что надо дозаписать файл при использовании размера страницы по умолчанию

	Lock->Acquire();
	if(data->Size() == 16 && start != 16) // если каталог пустой, надо выделить первую страницу!!!
	{
		MemoryByteStream* _ts = new MemoryByteStream;
		write_block(*_ts, 16, true);
		delete _ts;
	}

	if(len == -1)
	{
		len = static_cast<int>(block.Size());
		block.Seek(0, SeekOrigin::Begin);
	}
	start = get_nextblock(start);

	do
	{
		if(start == start_empty)
		{
        	// пишем в свободный блок
			data->Seek(start, SeekOrigin::Begin);
			ReadBufferExact(*data, temp_buf, 31);
			blocklen = hex_to_int(&temp_buf[11]);
			nextstart = hex_to_int(&temp_buf[20]);
			//start_empty = len <= blocklen ? V8_FF_SIGNATURE : nextstart;
			start_empty = nextstart;
			is_emptymodified = true;
		}
		else if(start == data->Size())
		{
        	// пишем в новый блок
			memcpy(temp_buf, _block_header_template, 31);
			blocklen = use_page_size ? len > page_size ? len : page_size : len;
			int_to_hex(&temp_buf[11], blocklen);
			nextstart = 0;
			if(blocklen > len)
            	addwrite = true;
		}
		else
		{
        	// пишем в существующий блок
			data->Seek(start, SeekOrigin::Begin);
			ReadBufferExact(*data, temp_buf, 31);
			blocklen = hex_to_int(&temp_buf[11]);
			nextstart = hex_to_int(&temp_buf[20]);
		}

		int_to_hex(&temp_buf[2], isfirstblock ? len : 0);
		curlen = min(blocklen, len);

		if(!nextstart)
        	nextstart = data->Size() + 31 + blocklen;
		else
        	nextstart = get_nextblock(nextstart);

		int_to_hex(&temp_buf[20], len <= blocklen ? V8_FF_SIGNATURE : nextstart);

		data->Seek(start, SeekOrigin::Begin);
		WriteBufferExact(*data, temp_buf, 31);
		CopyFromStream(*data, block, static_cast<std::size_t>(curlen));
		if(addwrite)
		{
			_t = new char [blocklen - len];
			memset(_t, 0, blocklen - len);
			WriteBufferExact(*data, _t, blocklen - len);
			addwrite = false;
		}

		len -= curlen;

		if(isfirstblock)
		{
			firststart = start;
			isfirstblock = false;
		}
		start = nextstart;

	}while(len > 0);

	if(start < data->Size() && start != start_empty)
    	free_block(start);

	is_modified = true;
	Lock->Release();

	return firststart;
}

//===========================================================================
v8catalog::~v8catalog()
{
	fat_item fi;
	v8file* f;
	MemoryByteStream* fat = NULL;

	Lock->Acquire();
	is_destructed = true;

	f = first;
	while(f)
	{
//		f->readonly = readonly;
		f->Close();
		f = f->next;
	}

	if(data)
	{
		if(is_fatmodified)
		{
			try
			{
				fat = new MemoryByteStream;
				fi.ff = V8_FF_SIGNATURE;
				f = first;
				while(f)
				{
					fi.header_start = f->start_header;
					fi.data_start = f->start_data;
					WriteBufferExact(*fat, &fi, 12);
					f = f->next;
				}
				write_block(*fat, 16, true);
			}
			catch(...)
			{
			}
			delete fat;
		}
	}

	while(first) delete first;

	if(data)
	{
		if(is_emptymodified)
		{
			data->Seek(0, SeekOrigin::Begin);
			WriteBufferExact(*data, &start_empty, 4);
		}
		if(is_modified)
		{
			version++;
			data->Seek(8, SeekOrigin::Begin);
			WriteBufferExact(*data, &version, 4);
		}
	}

	if(file)
    {
		if(is_modified)
		{
			file->is_datamodified = true;
		}
		if(!file->is_destructed) file->Close();
	}
	else
	{
		if(is_cfu)
		{
			if(data && cfu && is_modified)
			{
				data->Seek(0, SeekOrigin::Begin);
				cfu->Seek(0, SeekOrigin::Begin);
				ZDeflateStream(*data, *cfu);
			}
			delete data;
			data = NULL;
			if(cfu && !leave_data)
            {
				delete cfu;
				cfu = NULL;
			}
		}
		if(data && !leave_data)
		{
			delete data;
			data = NULL;
		}

	}
	if(!file) delete Lock;
}

//===========================================================================
v8file* v8catalog::GetSelfFile()
{
	return file;
}

//===========================================================================
v8catalog* v8catalog::CreateCatalog16(const Utf16String& fileName, bool _selfzipped)
{
	v8catalog* ret;
	V8ScopedLock guard(Lock);
	v8file* f = createFile16(fileName, _selfzipped);
	if(f->GetFileLength())
	{
		if(f->IsCatalog()) ret = f->GetCatalog();
		else ret = NULL;
	}
	else
	{
		f->Write(_empty_catalog_template, 16);
		ret = f->GetCatalog();
	}
	return ret;
}

//===========================================================================
void v8catalog::SaveToDir(const std::filesystem::path& dirPath)
{
	std::error_code ec;
	std::filesystem::create_directories(dirPath, ec);

	V8ScopedLock guard(Lock);
	v8file* f = first;
	while(f)
	{
		const std::filesystem::path targetPath = dirPath / std::filesystem::path(Utf16ToWide(f->name));
		if(f->IsCatalog())
        	f->GetCatalog()->SaveToDir(targetPath);
		else
        	f->SaveToFile(targetPath);

		f->Close();
		f = f->next;
	}
}

//===========================================================================
bool v8catalog::isOpen()
{
	return IsCatalog();
}

//===========================================================================
void v8catalog::Flush()
{
	fat_item fi;
	v8file* f;

	Lock->Acquire();
	if(flushed)
	{
		Lock->Release();
		return;
	}
	flushed = true;

	f = first;
	while(f)
	{
		f->Flush();
		f = f->next;
	}

	if(data)
	{
		if(is_fatmodified)
		{
			MemoryByteStream* fat = new MemoryByteStream;
			fi.ff = V8_FF_SIGNATURE;
			f = first;
			while(f)
			{
				fi.header_start = f->start_header;
				fi.data_start = f->start_data;
				WriteBufferExact(*fat, &fi, 12);
				f = f->next;
			}
			write_block(*fat, 16, true);
			is_fatmodified = false;
		}

		if(is_emptymodified)
		{
			data->Seek(0, SeekOrigin::Begin);
			WriteBufferExact(*data, &start_empty, 4);
			is_emptymodified = false;
		}
		if(is_modified)
		{
			version++;
			data->Seek(8, SeekOrigin::Begin);
			WriteBufferExact(*data, &version, 4);
		}
	}

	if(file)
    {
		if(is_modified)
		{
			file->is_datamodified = true;
		}
		//if(!file->is_destructed) file->Close();
		file->Flush();
	}
	else
	{
		if(is_cfu)
		{
			if(data && cfu && is_modified)
			{
				data->Seek(0, SeekOrigin::Begin);
				cfu->Seek(0, SeekOrigin::Begin);
				ZDeflateStream(*data, *cfu);
			}
		}
	}

	is_modified = false;
	flushed = false;
	Lock->Release();
}

//===========================================================================
void v8catalog::HalfClose()
{
	Lock->Acquire();
	Flush();
	if(is_cfu)
	{
		delete cfu;
		cfu = NULL;
	}
	else
	{
		delete data;
		data = NULL;
	}
	Lock->Release();
}

//===========================================================================
void v8catalog::HalfOpen(const std::filesystem::path& path)
{
	V8ScopedLock guard(Lock);

	if(is_cfu)
    	cfu = new StdFileStream(path, FileOpenMode::ReadWrite);
	else
    	data = new StdFileStream(path, FileOpenMode::ReadWrite);
}

void v8catalog::ClearIs8316()
{
    is_8316 = false;
}

//void v8catalog::set_leave_data(bool ld)
//{
//    leave_data = ld;
//}

//===========================================================================




