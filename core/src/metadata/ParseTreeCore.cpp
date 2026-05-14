//---------------------------------------------------------------------------

#include "../../include/v8reader_core/ParseTreeCore.h"

#include "Parse_tree.h"

#include <vector>

namespace
{
	Utf16String Utf16ViewToString(std::u16string_view value)
	{
		return Utf16String(value.data(), value.size());
	}

	std::u16string Utf16StringToView(const Utf16String& value)
	{
		return std::u16string(value.data(), value.size());
	}
}

tree* parse_1Ctext_u16(std::u16string_view text, std::u16string_view path)
{
	return parse_1Ctext(Utf16ViewToString(text), Utf16ViewToString(path));
}

std::u16string outtext_u16(tree* t)
{
	return Utf16StringToView(outtext(t));
}

tree* find_node_by_guid_u16(tree* root, std::u16string_view target_guid)
{
	return find_node_by_guid(root, Utf16ViewToString(target_guid));
}

tree* find_metadata_node_by_guid_u16(tree* root, std::u16string_view target_guid)
{
	return find_metadata_node_by_guid(root, Utf16ViewToString(target_guid));
}
