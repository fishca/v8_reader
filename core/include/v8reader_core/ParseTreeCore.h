#ifndef V8READER_CORE_PARSETREECORE_H
#define V8READER_CORE_PARSETREECORE_H

#include <string>
#include <string_view>

class tree;

tree* parse_1Ctext_u16(std::u16string_view text, std::u16string_view path);
std::u16string outtext_u16(tree* t);
tree* find_node_by_guid_u16(tree* root, std::u16string_view target_guid);
tree* find_metadata_node_by_guid_u16(tree* root, std::u16string_view target_guid);

#endif

