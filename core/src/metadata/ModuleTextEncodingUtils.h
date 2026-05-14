//---------------------------------------------------------------------------

#ifndef ModuleTextEncodingUtilsH
#define ModuleTextEncodingUtilsH

#include "../APIcfBase.h"
#include "../../include/v8reader_core/io/IByteStream.h"
#include "ModuleTextStorage.h"

namespace ModuleTextEncodingUtils
{
	inline bool LooksLikeUtf16Le(const TBytes& bytes, int sourceSize)
	{
		int limit = sourceSize < 200 ? sourceSize : 200;
		int checked = 0;
		int zeroOdd = 0;

		for (int i = 1; i < limit; i += 2)
		{
			++checked;
			if (bytes[i] == 0)
				++zeroOdd;
		}

		return checked > 0 && zeroOdd * 2 >= checked;
	}

	inline LegacyText DecodeModuleText(const TBytes& sourceBytes, int sourceSize, ModuleTextEncodingKind& encoding)
	{
		encoding = ModuleTextEncodingKind::Unknown;

		if (sourceSize <= 0 || sourceBytes.empty())
			return L"";

		TBytes bytes = sourceBytes;
		sourceSize = sourceSize < bytes.Length ? sourceSize : bytes.Length;

		TEncoding* enc = nullptr;
		int off = TEncoding::GetBufferEncoding(bytes, enc);
		if (off > 0)
		{
			if (enc == TEncoding::UTF8)
				encoding = ModuleTextEncodingKind::Utf8Bom;
			else if (enc == TEncoding::Unicode)
				encoding = ModuleTextEncodingKind::Utf16LeBom;

			TBytes unicodeBytes = TEncoding::Convert(enc, TEncoding::Unicode, bytes, off, sourceSize - off);
			if (!unicodeBytes.empty())
				return LegacyText((wchar_t*)&unicodeBytes[0], unicodeBytes.Length / 2);
		}

		if (LooksLikeUtf16Le(bytes, sourceSize))
		{
			encoding = ModuleTextEncodingKind::Utf16Le;
			return LegacyText((wchar_t*)&bytes[0], sourceSize / 2);
		}

		try
		{
			encoding = ModuleTextEncodingKind::Utf8;
			return TEncoding::UTF8->GetString(bytes, 0, sourceSize);
		}
		catch (...)
		{
			encoding = ModuleTextEncodingKind::Ansi;
			return LegacyText((char*)&bytes[0], sourceSize);
		}
	}

	inline void WriteTextWithEncoding(v8reader::core::io::IByteStream& stream, const LegacyText& text, ModuleTextEncodingKind encoding)
	{
		TBytes bytes;

		switch (encoding)
		{
			case ModuleTextEncodingKind::Utf16LeBom:
			{
				const unsigned char bom[] = {0xFF, 0xFE};
				stream.Write(bom, 2);
				bytes = TEncoding::Unicode->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Utf16Le:
			{
				bytes = TEncoding::Unicode->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Utf8Bom:
			{
				const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
				stream.Write(bom, 3);
				bytes = TEncoding::UTF8->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Ansi:
			{
				bytes = TEncoding::Default->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Utf8:
			case ModuleTextEncodingKind::Unknown:
			default:
			{
				bytes = TEncoding::UTF8->GetBytes(text);
				break;
			}
		}

		if (!bytes.empty())
			stream.Write(&bytes[0], static_cast<std::size_t>(bytes.Length));
	}
}

#endif
