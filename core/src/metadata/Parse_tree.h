//---------------------------------------------------------------------------

#ifndef Parse_treeH
#define Parse_treeH

#include "../APIcfBase.h"
#include <memory>
#include <string>
#include <type_traits>
#include <string_view>

#include "NodeTypes.h"
#include "../MessageRegistration.h"

//---------------------------------------------------------------------------
class tree
{
private:
	Utf16String value;
	node_type type;
	int num_subnode; // количество подчиненных
	tree* parent; // +1
	tree* next; // 0
	tree* prev; // 0
	tree* first; // -1
	tree* last; // -1
	unsigned int index;

public:
    tree(const wchar_t* _value, const node_type _type, tree* _parent) : tree(V8Utf16FromString(_value), _type, _parent) {}
    tree(const char16_t* _value, const node_type _type, tree* _parent) : tree(V8Utf16FromString(_value), _type, _parent) {}
    template <typename TStringLike>
    tree(const TStringLike& _value, const node_type _type, tree* _parent) : tree(V8Utf16FromString(_value), _type, _parent) {}
	tree(const Utf16String& _value, const node_type _type, tree* _parent);
	~tree();
	tree* add_child(const Utf16String& _value, const node_type _type);
    tree* add_child(const wchar_t* _value, const node_type _type) { return add_child(V8Utf16FromString(_value), _type); }
    tree* add_child(const char16_t* _value, const node_type _type) { return add_child(V8Utf16FromString(_value), _type); }
    template <typename TStringLike>
    tree* add_child(const TStringLike& _value, const node_type _type) { return add_child(V8Utf16FromString(_value), _type); }
	tree* add_child();
	tree* add_node();
	Utf16String& get_value();
	node_type get_type();
	int get_num_subnode();
	tree* get_subnode(int _index);
	tree* get_subnode(const Utf16String& node_name);
	tree* get_next();
	tree* get_parent();
	tree* get_first();
	tree* get_last();
	tree& operator [](int _index);
	void set_value(const Utf16String& v, const node_type t);
    void set_value(const wchar_t* v, const node_type t) { set_value(V8Utf16FromString(v), t); }
    void set_value(const char16_t* v, const node_type t) { set_value(V8Utf16FromString(v), t); }
    template <typename TNumber, typename = std::enable_if_t<std::is_arithmetic_v<TNumber>>>
    void set_value(TNumber v, const node_type t) { set_value(V8Utf16FromString(std::to_wstring(v).c_str()), t); }
	void outtext(Utf16String& text);
	Utf16String path();
};

typedef tree* treeptr;
class v8file;

typedef std::unique_ptr<tree> tree_unique_ptr;
typedef std::shared_ptr<tree> tree_shared_ptr;



//tree* parse_1Ctext_old(Utf16String& text, Utf16String path);
tree* parse_1Ctext(const Utf16String& text, const Utf16String& path);
tree* parse_1Cstream(v8reader::core::io::IByteStream& str, const Utf16String& path);
bool test_parse_1Ctext(v8reader::core::io::IByteStream& str, const Utf16String& path);
Utf16String outtext(tree* t);
tree* find_node_by_guid(tree* root, const Utf16String& target_guid);
tree* find_metadata_node_by_guid(tree* root, const Utf16String& target_guid);
tree* get_treeFromV8file(v8file* f);

// Transitional core-friendly wrappers (UTF-16 std strings on public boundary).
tree* parse_1Ctext_u16(std::u16string_view text, std::u16string_view path);
std::u16string outtext_u16(tree* t);
tree* find_node_by_guid_u16(tree* root, std::u16string_view target_guid);
tree* find_metadata_node_by_guid_u16(tree* root, std::u16string_view target_guid);


inline tree* parse_1Ctext(const Utf16String& text) { return parse_1Ctext(text, u""); }
inline tree* parse_1Ctext(const wchar_t* text, const wchar_t* path = L"") { return parse_1Ctext(V8Utf16FromString(text), V8Utf16FromString(path)); }
inline tree* parse_1Ctext(const char16_t* text, const char16_t* path = u"") { return parse_1Ctext(V8Utf16FromString(text), V8Utf16FromString(path)); }
template <typename TStringLike>
inline tree* parse_1Ctext(const TStringLike& text, const TStringLike& path) { return parse_1Ctext(V8Utf16FromString(text), V8Utf16FromString(path)); }
template <typename TStringLike>
inline tree* parse_1Ctext(const TStringLike& text) { return parse_1Ctext(V8Utf16FromString(text), Utf16String()); }

inline tree* find_node_by_guid(tree* root, const wchar_t* target_guid) { return find_node_by_guid(root, V8Utf16FromString(target_guid)); }
inline tree* find_metadata_node_by_guid(tree* root, const wchar_t* target_guid) { return find_metadata_node_by_guid(root, V8Utf16FromString(target_guid)); }
template <typename TStringLike>
inline tree* find_node_by_guid(tree* root, const TStringLike& target_guid) { return find_node_by_guid(root, V8Utf16FromString(target_guid)); }
template <typename TStringLike>
inline tree* find_metadata_node_by_guid(tree* root, const TStringLike& target_guid) { return find_metadata_node_by_guid(root, V8Utf16FromString(target_guid)); }
template <typename TText, typename TPath>
inline tree* parse_1Ctext(const TText& text, const TPath& path) { return parse_1Ctext(V8Utf16FromString(text), V8Utf16FromString(path)); }
#endif

