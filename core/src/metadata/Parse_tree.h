//---------------------------------------------------------------------------

#ifndef Parse_treeH
#define Parse_treeH

#include "../APIcfBase.h"
#include <memory>
#include <string>
#include <string_view>

#include "NodeTypes.h"
#include "../MessageRegistration.h"

//---------------------------------------------------------------------------
class tree
{
private:
	LegacyText value;
	node_type type;
	int num_subnode; // количество подчиненных
	tree* parent; // +1
	tree* next; // 0
	tree* prev; // 0
	tree* first; // -1
	tree* last; // -1
	unsigned int index;

public:
	tree(const LegacyText& _value, const node_type _type, tree* _parent);
	~tree();
	tree* add_child(const LegacyText& _value, const node_type _type);
	tree* add_child();
	tree* add_node();
	LegacyText& get_value();
	node_type get_type();
	int get_num_subnode();
	tree* get_subnode(int _index);
	tree* get_subnode(const LegacyText& node_name);
	tree* get_next();
	tree* get_parent();
	tree* get_first();
	tree* get_last();
	tree& operator [](int _index);
	void set_value(const LegacyText& v, const node_type t);
	void outtext(LegacyText& text);
	LegacyText path();
};

typedef tree* treeptr;
class v8file;

typedef std::unique_ptr<tree> tree_unique_ptr;
typedef std::shared_ptr<tree> tree_shared_ptr;



//tree* parse_1Ctext_old(LegacyText& text, LegacyText path);
tree* parse_1Ctext(const LegacyText& text, const LegacyText& path);
tree* parse_1Cstream(v8reader::core::io::IByteStream& str, const LegacyText& path);
bool test_parse_1Ctext(v8reader::core::io::IByteStream& str, const LegacyText& path);
LegacyText outtext(tree* t);
tree* find_node_by_guid(tree* root, const LegacyText& target_guid);
tree* find_metadata_node_by_guid(tree* root, const LegacyText& target_guid);
tree* get_treeFromV8file(v8file* f);

// Transitional core-friendly wrappers (UTF-16 std strings on public boundary).
tree* parse_1Ctext_u16(std::u16string_view text, std::u16string_view path);
std::u16string outtext_u16(tree* t);
tree* find_node_by_guid_u16(tree* root, std::u16string_view target_guid);
tree* find_metadata_node_by_guid_u16(tree* root, std::u16string_view target_guid);

#endif

