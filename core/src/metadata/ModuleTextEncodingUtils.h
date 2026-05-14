//---------------------------------------------------------------------------

#ifndef ModuleTextEncodingUtilsH
#define ModuleTextEncodingUtilsH

#include <Windows.h>
#include <cstring>
#include <vector>

#include "../APIcfBase.h"
#include "../../include/v8reader_core/io/IByteStream.h"
#include "ModuleTextStorage.h"

namespace ModuleTextEncodingUtils
{
	inline bool LooksLikeUtf16Le(const ByteVector& bytes, int sourceSize)
	{
		int limit = sourceSize < 200 ? sourceSize : 200;
		int checked = 0;
		int zeroOdd = 0;

		for (int i = 1; i < limit; i += 2)
		{
			++checked;
			if (bytes[static_cast<std::size_t>(i)] == 0)
				++zeroOdd;
		}

		return checked > 0 && zeroOdd * 2 >= checked;
	}

	inline Utf16String WideToUtf16(const std::wstring& value)
	{
		return Utf16String(reinterpret_cast<const char16_t*>(value.c_str()), value.size());
	}

	inline Utf16String DecodeUtf8(const ByteVector& bytes, int startOffset, int byteCount)
	{
		if (byteCount <= 0)
			return Utf16String();

		const char* src = reinterpret_cast<const char*>(bytes.data() + static_cast<std::size_t>(startOffset));
		const int required = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, src, byteCount, nullptr, 0);
		if (required <= 0)
			return Utf16String();

		std::wstring wide(static_cast<std::size_t>(required), L'\0');
		MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, src, byteCount, wide.data(), required);
		return WideToUtf16(wide);
	}

	inline Utf16String DecodeAnsi(const ByteVector& bytes, int startOffset, int byteCount)
	{
		if (byteCount <= 0)
			return Utf16String();

		const char* src = reinterpret_cast<const char*>(bytes.data() + static_cast<std::size_t>(startOffset));
		const int required = MultiByteToWideChar(CP_ACP, 0, src, byteCount, nullptr, 0);
		if (required <= 0)
			return Utf16String();

		std::wstring wide(static_cast<std::size_t>(required), L'\0');
		MultiByteToWideChar(CP_ACP, 0, src, byteCount, wide.data(), required);
		return WideToUtf16(wide);
	}

	inline Utf16String DecodeUtf16Le(const ByteVector& bytes, int startOffset, int byteCount)
	{
		if (byteCount <= 1)
			return Utf16String();

		const int aligned = byteCount - (byteCount % 2);
		const char16_t* data = reinterpret_cast<const char16_t*>(bytes.data() + static_cast<std::size_t>(startOffset));
		return Utf16String(data, static_cast<std::size_t>(aligned / 2));
	}

	inline Utf16String DecodeModuleText(const ByteVector& sourceBytes, int sourceSize, ModuleTextEncodingKind& encoding)
	{
		encoding = ModuleTextEncodingKind::Unknown;

		if (sourceSize <= 0 || sourceBytes.empty())
			return Utf16String();

		const int safeSize = sourceSize < static_cast<int>(sourceBytes.size()) ? sourceSize : static_cast<int>(sourceBytes.size());

		if (safeSize >= 3
			&& sourceBytes[0] == 0xEF
			&& sourceBytes[1] == 0xBB
			&& sourceBytes[2] == 0xBF)
		{
			encoding = ModuleTextEncodingKind::Utf8Bom;
			return DecodeUtf8(sourceBytes, 3, safeSize - 3);
		}

		if (safeSize >= 2
			&& sourceBytes[0] == 0xFF
			&& sourceBytes[1] == 0xFE)
		{
			encoding = ModuleTextEncodingKind::Utf16LeBom;
			return DecodeUtf16Le(sourceBytes, 2, safeSize - 2);
		}

		if (LooksLikeUtf16Le(sourceBytes, safeSize))
		{
			encoding = ModuleTextEncodingKind::Utf16Le;
			return DecodeUtf16Le(sourceBytes, 0, safeSize);
		}

		{
			Utf16String utf8 = DecodeUtf8(sourceBytes, 0, safeSize);
			if (!utf8.empty())
			{
				encoding = ModuleTextEncodingKind::Utf8;
				return utf8;
			}
		}

		encoding = ModuleTextEncodingKind::Ansi;
		return DecodeAnsi(sourceBytes, 0, safeSize);
	}

	inline ByteVector EncodeUtf16Le(const Utf16String& text)
	{
		const std::size_t bytesSize = text.size() * sizeof(char16_t);
		ByteVector bytes(bytesSize);
		if (!bytes.empty())
			std::memcpy(bytes.data(), text.data(), bytesSize);
		return bytes;
	}

	inline ByteVector EncodeWideWithCodePage(const Utf16String& text, UINT codePage)
	{
		if (text.empty())
			return ByteVector();

		const wchar_t* src = reinterpret_cast<const wchar_t*>(text.c_str());
		const int srcLen = static_cast<int>(text.size());
		const int required = WideCharToMultiByte(codePage, 0, src, srcLen, nullptr, 0, nullptr, nullptr);
		if (required <= 0)
			return ByteVector();

		ByteVector bytes(static_cast<std::size_t>(required));
		WideCharToMultiByte(codePage, 0, src, srcLen, reinterpret_cast<char*>(bytes.data()), required, nullptr, nullptr);
		return bytes;
	}

	inline void WriteTextWithEncoding(v8reader::core::io::IByteStream& stream, const Utf16String& text, ModuleTextEncodingKind encoding)
	{
		ByteVector bytes;

		switch (encoding)
		{
			case ModuleTextEncodingKind::Utf16LeBom:
			{
				const unsigned char bom[] = {0xFF, 0xFE};
				stream.Write(bom, 2);
				bytes = EncodeUtf16Le(text);
				break;
			}
			case ModuleTextEncodingKind::Utf16Le:
			{
				bytes = EncodeUtf16Le(text);
				break;
			}
			case ModuleTextEncodingKind::Utf8Bom:
			{
				const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
				stream.Write(bom, 3);
				bytes = EncodeWideWithCodePage(text, CP_UTF8);
				break;
			}
			case ModuleTextEncodingKind::Ansi:
			{
				bytes = EncodeWideWithCodePage(text, CP_ACP);
				break;
			}
			case ModuleTextEncodingKind::Utf8:
			case ModuleTextEncodingKind::Unknown:
			default:
			{
				bytes = EncodeWideWithCodePage(text, CP_UTF8);
				break;
			}
		}

		if (!bytes.empty())
			stream.Write(bytes.data(), bytes.size());
	}
}

#endif
