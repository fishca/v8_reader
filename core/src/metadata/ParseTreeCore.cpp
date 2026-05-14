//---------------------------------------------------------------------------

#include "../../include/v8reader_core/ParseTreeCore.h"

#include "Parse_tree.h"

#include <vector>

namespace
{
	LegacyText Utf16ToVclString(std::u16string_view value)
	{
#ifndef _DELPHI_STRING_UNICODE
		std::vector<wchar_t> buffer(value.size() + 1);
		for (std::size_t i = 0; i < value.size(); ++i)
			buffer[i] = static_cast<wchar_t>(value[i]);
		buffer[value.size()] = 0;
		return LegacyText(buffer.data());
#else
		return LegacyText(reinterpret_cast<const wchar_t*>(value.data()), static_cast<int>(value.size()));
#endif
	}

	std::u16string VclStringToUtf16(const LegacyText& value)
	{
#ifndef _DELPHI_STRING_UNICODE
		const int ws = value.WideCharBufSize();
		std::vector<wchar_t> buffer(ws);
		value.WideChar(buffer.data(), ws);
		return std::u16string(reinterpret_cast<const char16_t*>(buffer.data()));
#else
		return std::u16string(reinterpret_cast<const char16_t*>(value.c_str()), value.Length());
#endif
	}
}

tree* parse_1Ctext_u16(std::u16string_view text, std::u16string_view path)
{
	return parse_1Ctext(Utf16ToVclString(text), Utf16ToVclString(path));
}

std::u16string outtext_u16(tree* t)
{
	return VclStringToUtf16(outtext(t));
}

tree* find_node_by_guid_u16(tree* root, std::u16string_view target_guid)
{
	return find_node_by_guid(root, Utf16ToVclString(target_guid));
}

tree* find_metadata_node_by_guid_u16(tree* root, std::u16string_view target_guid)
{
	return find_metadata_node_by_guid(root, Utf16ToVclString(target_guid));
}

