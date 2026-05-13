//---------------------------------------------------------------------------

#pragma hdrstop

#include "TempStream.h"

#include "../core/include/v8reader_core/io/TempFileStream.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using v8reader::core::io::SeekOrigin;
using v8reader::core::io::TempFileStream;

namespace
{
SeekOrigin ToSeekOrigin(TSeekOrigin origin)
{
	switch(origin)
	{
		case soBeginning:
			return SeekOrigin::Begin;
		case soCurrent:
			return SeekOrigin::Current;
		case soEnd:
			return SeekOrigin::End;
	}

	return SeekOrigin::Begin;
}

SeekOrigin ToSeekOrigin(System::Word origin)
{
	switch(origin)
	{
		case soFromBeginning:
			return SeekOrigin::Begin;
		case soFromCurrent:
			return SeekOrigin::Current;
		case soFromEnd:
			return SeekOrigin::End;
	}

	return SeekOrigin::Begin;
}
} // namespace

//---------------------------------------------------------------------------
TTempStream::TTempStream()
	: stream_(std::make_unique<TempFileStream>())
{
}

//---------------------------------------------------------------------------
TTempStream::~TTempStream() = default;

//---------------------------------------------------------------------------
int __fastcall TTempStream::Read(void* Buffer, int Count)
{
	if(Count <= 0)
		return 0;

	return static_cast<int>(stream_->Read(Buffer, static_cast<std::size_t>(Count)));
}

//---------------------------------------------------------------------------
int __fastcall TTempStream::Write(const void* Buffer, int Count)
{
	if(Count <= 0)
		return 0;

	return static_cast<int>(stream_->Write(Buffer, static_cast<std::size_t>(Count)));
}

//---------------------------------------------------------------------------
int __fastcall TTempStream::Seek(int Offset, System::Word Origin)
{
	return static_cast<int>(stream_->Seek(static_cast<std::int64_t>(Offset), ToSeekOrigin(Origin)));
}

//---------------------------------------------------------------------------
__int64 __fastcall TTempStream::Seek(const __int64 Offset, TSeekOrigin Origin)
{
	return static_cast<__int64>(stream_->Seek(Offset, ToSeekOrigin(Origin)));
}

//---------------------------------------------------------------------------
