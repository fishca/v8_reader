//---------------------------------------------------------------------------

#include "Parse_tree.h"
#include "Common.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace
{
    inline bool is_ascii_digit(wchar_t ch)
    {
        return ch >= L'0' && ch <= L'9';
    }

    inline bool is_hex_digit(wchar_t ch)
    {
        return (ch >= L'0' && ch <= L'9')
            || (ch >= L'a' && ch <= L'f')
            || (ch >= L'A' && ch <= L'F');
    }

    inline bool is_base64_digit(wchar_t ch)
    {
        return (ch >= L'a' && ch <= L'z')
            || (ch >= L'A' && ch <= L'Z')
            || (ch >= L'0' && ch <= L'9')
            || ch == L'+'
            || ch == L'='
            || ch == L'/'
            || ch == L'\r'
            || ch == L'\n';
    }

    bool is_number_fast(const String& value)
    {
        const int len = value.Length();
        if(len == 0) return false;

        int i = 1;
        if(value[i] == L'-')
        {
            ++i;
            if(i > len) return false;
        }

        for(; i <= len; ++i)
        {
            if(!is_ascii_digit(value[i])) return false;
        }
        return true;
    }

    bool is_number_exp_fast(const String& value)
    {
        const int len = value.Length();
        if(len == 0) return false;

        int i = 1;
        if(value[i] == L'-')
        {
            ++i;
            if(i > len) return false;
        }

        bool has_digits = false;
        while(i <= len && is_ascii_digit(value[i]))
        {
            has_digits = true;
            ++i;
        }
        if(!has_digits) return false;

        if(i <= len && value[i] == L'.')
        {
            ++i;
            while(i <= len && is_ascii_digit(value[i])) ++i;
        }

        if(i <= len && (value[i] == L'e' || value[i] == L'E'))
        {
            ++i;
            if(i <= len && value[i] == L'-') ++i;
            if(i > len || !is_ascii_digit(value[i])) return false;
            while(i <= len && is_ascii_digit(value[i])) ++i;
        }

        return i > len;
    }

    bool is_guid_fast(const String& value)
    {
        static const int expected_len = 36;
        if(value.Length() != expected_len) return false;

        for(int i = 1; i <= expected_len; ++i)
        {
            if(i == 9 || i == 14 || i == 19 || i == 24)
            {
                if(value[i] != L'-') return false;
            }
            else if(!is_hex_digit(value[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool is_link_fast(const String& value)
    {
        const int len = value.Length();
        if(len < 34) return false;

        int i = 1;
        if(!is_ascii_digit(value[i])) return false;
        while(i <= len && is_ascii_digit(value[i])) ++i;
        if(i > len || value[i] != L':') return false;
        ++i;

        if(len - i + 1 != 32) return false;
        for(; i <= len; ++i)
        {
            if(!is_hex_digit(value[i])) return false;
        }
        return true;
    }

    bool is_base64_fast(const String& value, int start_index)
    {
        for(int i = start_index; i <= value.Length(); ++i)
        {
            if(!is_base64_digit(value[i])) return false;
        }
        return true;
    }
}

extern MessageRegistrator* msreg;
#define error if(msreg) msreg->AddError

//---------------------------------------------------------------------------
tree::tree(const String& _value, const node_type _type, tree* _parent)
{
	value = _value;
	type = _type;
	parent = _parent;

	num_subnode = 0;
	index = 0;
	if(parent)
	{
		parent->num_subnode++;
		prev = parent->last;
		if(prev)
		{
			prev->next = this;
			index = prev->index + 1;
		}
		else parent->first = this;
		parent->last = this;
	}
	else prev = NULL;
	next = NULL;
	first = NULL;
	last = NULL;
}

//---------------------------------------------------------------------------
tree::~tree()
{
	while(last) delete last;
	if(prev) prev->next = next;
	if(next) next->prev = prev;
	if(parent)
	{
		if(parent->first == this) parent->first = next;
		if(parent->last == this) parent->last = prev;
		parent->num_subnode--;
	}
}

//---------------------------------------------------------------------------
tree* tree::add_child(const String& _value, const node_type _type)
{
	return new tree(_value, _type, this);
}

//---------------------------------------------------------------------------
tree* tree::add_child()
{
	return new tree(L"", nd_empty, this);
}

//---------------------------------------------------------------------------
tree* tree::add_node()
{
	return new tree(L"", nd_empty, this->parent);
}

//---------------------------------------------------------------------------
String& tree::get_value()
{
	return value;
}

//---------------------------------------------------------------------------
node_type tree::get_type()
{
	return type;
}

//---------------------------------------------------------------------------
void tree::set_value(const String& v, const node_type t)
{
	value = v;
	type = t;
}

//---------------------------------------------------------------------------
int tree::get_num_subnode()
{
	return num_subnode;
}

//---------------------------------------------------------------------------
tree* tree::get_subnode(int _index)
{
	if(_index >= num_subnode) return NULL;
	tree* t = first;
	while(_index)
	{
		t = t->next;
		--_index;
	}
	return t;
}

//---------------------------------------------------------------------------
tree* tree::get_subnode(const String& node_name)
{
	tree* t = first;
	while(t)
	{
		if(t->value == node_name) return t;
		t = t->next;
	}
	return NULL;
}

//---------------------------------------------------------------------------
tree* tree::get_next()
{
	return next;
}

//---------------------------------------------------------------------------
tree* tree::get_parent()
{
	return parent;
}

//---------------------------------------------------------------------------
tree* tree::get_first()
{
	return first;
}

//---------------------------------------------------------------------------
tree* tree::get_last()
{
	return last;
}

//---------------------------------------------------------------------------
tree& tree::operator [](int _index)
{
	if(!this) return *this; //-V704

	tree* ret = first;
	while(_index)
	{
		if(ret) ret = ret->next;
		--_index;
	}
	return *ret;
}

//---------------------------------------------------------------------------
void tree::outtext(String& text)
{
	node_type lt;
	TReplaceFlags _ReplaceAll;

	if(num_subnode)
	{
		if(text.Length()) text += L"\r\n";
		text += L'{';
		tree* t = first;
		while(t)
		{
			t->outtext(text);
			lt = t->type;
			t = t->next;
			if(t) text += L',';
		}
		if(lt == nd_list) text += L"\r\n";
		text += L'}';
	}
	else
	{
		switch(type)
		{
			case nd_string:
				text += L'\"';
				_ReplaceAll << rfReplaceAll;
				text += StringReplace(value, L"\"", L"\"\"", _ReplaceAll);
				text += L'\"';
				break;
			case nd_number:
			case nd_number_exp:
			case nd_guid:
			case nd_list:
			case nd_binary:
			case nd_binary2:
			case nd_link:
			case nd_binary_d:
				text += value;
				break;
			default:
				//if(msreg) msreg->AddError(L"Ошибка вывода потока. Пустой или неизвестный узел.");
				break;
		}
	}
}

//---------------------------------------------------------------------------
String tree::path()
{
	String p = L"";
	tree* t;

	if(!this) return L":??"; //-V704
	for(t = this; t->parent; t = t->parent)
	{
		p = String(L":") + t->index + p;
	}
	return p;
}

//---------------------------------------------------------------------------
node_type classification_value(const String& value)
{
	if(value.Length() == 0) return nd_empty;
	if(is_number_fast(value)) return nd_number;
	if(is_number_exp_fast(value)) return nd_number_exp;
	if(is_guid_fast(value)) return nd_guid;
	if(value.Length() >= 8 && value.SubString(1, 8) == L"#base64:" && is_base64_fast(value, 9)) return nd_binary;
	if(is_link_fast(value)) return nd_link;
	if(is_base64_fast(value, 1)) return nd_binary2;
	if(value.Length() >= 6 && value.SubString(1, 6) == L"#data:" && is_base64_fast(value, 7)) return nd_binary_d;
	return nd_unknown;
}

tree* parse_1Cstream(TStream* str, const String& path)
{
	TStringBuilder* __curvalue__;

	enum _state{
		s_value, // ожидание начала значения
		s_delimitier, // ожидание разделителя
		s_string, // режим ввода строки
		s_quote_or_endstring, // режим ожидания конца строки или двойной кавычки
		s_nonstring // режим ввода значения не строки
	}state = s_value;

	String curvalue;
	tree* ret;
	tree* t;
	int i;
	wchar_t sym;
	int _sym;
	node_type nt;
	TStreamReader* reader;

	__curvalue__ = new TStringBuilder;

	ret = new tree(L"", nd_list, NULL);
	t = ret;

	//str->Seek(0l, soBeginning);
	reader = new TStreamReader(str, true);

	for(i = 1, _sym = reader->Read(); _sym >= 0; i++, _sym = reader->Read())
	{
		sym = _sym;
		//if(i % 0x100000 == 0) if(msreg) msreg->Status(String(i/0x100000) + L" MB");

		switch(state)
		{
			case s_value:
				switch(sym)
				{
					case L' ': // space
					case L'\t':
					case L'\r':
					case L'\n':
						break;
					case L'"':
						//curvalue = L"";
						__curvalue__->Clear();
						state = s_string;
						break;
					case L'{':
						t = new tree(L"", nd_list, t);
						break;
					case L'}':
						if(t->get_first()) t->add_child(L"", nd_empty);
						t = t->get_parent();
						if(!t)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							delete reader;
							delete __curvalue__;
							delete ret;
							return NULL;
						}
						state = s_delimitier;
						break;
					case L',':
						t->add_child(L"", nd_empty);
						break;
					default:
						//curvalue = String(sym);
						__curvalue__->Clear();
						__curvalue__->Append(sym);
						state = s_nonstring;
						break;
				}
				break;
			case s_delimitier:
				switch(sym)
				{
					case L' ': // space
					case L'\t':
					case L'\r':
					case L'\n':
						break;
					case L',':
						state = s_value;
						break;
					case L'}':
						t = t->get_parent();
						if(!t)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							delete ret;
							return NULL;
						}
						//state = s_delimitier;
						break;
					default:
						if(msreg) msreg->AddError(L"Ошибка формата потока. Ошибочный символ в режиме ожидания разделителя.",
							L"Символ", sym,
							L"Код символа", tohex(sym),
							L"Путь", path);
						delete reader;
						delete __curvalue__;
						delete ret;
						return NULL;
				}
				break;
			case s_string:
				if(sym == L'"'){
					state = s_quote_or_endstring;
				}
				//else curvalue += String(sym);
				else __curvalue__->Append(sym);
				break;
			case s_quote_or_endstring:
				if(sym == L'"')
				{
					//curvalue += String(sym);
					__curvalue__->Append(sym);
					state = s_string;
				}
				else
				{
					//t->add_child(curvalue, nd_string);
					t->add_child(__curvalue__->ToString(), nd_string);
					switch(sym)
					{
						case L' ': // space
						case L'\t':
						case L'\r':
						case L'\n':
							state = s_delimitier;
							break;
						case L',':
							state = s_value;
							break;
						case L'}':
							t = t->get_parent();
							if(!t)
							{
								if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
									L"Позиция", i,
									L"Путь", path);
								delete reader;
								delete __curvalue__;
								delete ret;
								return NULL;
							}
							state = s_delimitier;
							break;
						default:
							if(msreg) msreg->AddError(L"Ошибка формата потока. Ошибочный символ в режиме ожидания разделителя.",
								L"Символ", sym,
								L"Код символа", tohex(sym),
								L"Путь", path);
							delete reader;
							delete __curvalue__;
							delete ret;
							return NULL;
					}
				}
				break;
			case s_nonstring:
				switch(sym)
				{
					case L',':
						curvalue = __curvalue__->ToString();
						nt = classification_value(curvalue);
						if(nt == nd_unknown) if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
							L"Значение", curvalue,
							L"Путь", path);
						t->add_child(curvalue, nt);
						state = s_value;
						break;
					case L'}':
						curvalue = __curvalue__->ToString();
						nt = classification_value(curvalue);
						if(nt == nd_unknown) if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
							L"Значение", curvalue,
							L"Путь", path);
						t->add_child(curvalue, nt);
						t = t->get_parent();
						if(!t)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							delete reader;
							delete __curvalue__;
							delete ret;
							return NULL;
						}
						state = s_delimitier;
						break;
					default:
						//curvalue += String(sym);
						__curvalue__->Append(sym);
						break;
				}
				break;
			default:
				if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный режим разбора.",
					L"Режим разбора", tohex(state),
					L"Путь", path);
				delete reader;
				delete __curvalue__;
				delete ret;
				return NULL;

		}
	}

	if(state == s_nonstring)
	{
		curvalue = __curvalue__->ToString();
		nt = classification_value(curvalue);
		if(nt == nd_unknown) if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
			L"Значение", curvalue,
			L"Путь", path);
		t->add_child(curvalue, nt);
	}
	//else if(state == s_quote_or_endstring) t->add_child(curvalue, nd_string);
	else if(state == s_quote_or_endstring) t->add_child(__curvalue__->ToString(), nd_string);
	else if(state != s_delimitier)
	{
		if(msreg) msreg->AddError(L"Ошибка формата потока. Незавершенное значение",
			L"Режим разбора", tohex(state),
			L"Путь", path);
		delete reader;
		delete __curvalue__;
		delete ret;
		return NULL;
	}

	if(t != ret)
	{
		if(msreg) msreg->AddError(L"Ошибка формата потока. Не хватает закрывающих скобок } в конце текста разбора.",
			L"Путь", path);
		delete reader;
		delete __curvalue__;
		delete ret;
		return NULL;
	}

	delete reader;
	delete __curvalue__;

	return ret;

}


tree* parse_1Ctext(const String& text, const String& path)
{
	TStringBuilder* __curvalue__;

	enum _state{
		s_value, // ожидание начала значения
		s_delimitier, // ожидание разделителя
		s_string, // режим ввода строки
		s_quote_or_endstring, // режим ожидания конца строки или двойной кавычки
		s_nonstring // режим ввода значения не строки
	}state = s_value;

	String curvalue;
	tree* ret;
	tree* t;
	int len = text.Length();
	int i;
	wchar_t sym;
	node_type nt;

	__curvalue__ = new TStringBuilder;

	ret = new tree(L"", nd_list, NULL);
	t = ret;

	for(i = 1; i <= len; i++)
	{
		sym = text[i];
		if(!sym) break;

		switch(state)
		{
			case s_value:
				switch(sym)
				{
					case L' ': // space
					case L'\t':
					case L'\r':
					case L'\n':
						break;
					case L'"':
						//curvalue = L"";
						__curvalue__->Clear();
						state = s_string;
						break;
					case L'{':
						t = new tree(L"", nd_list, t);
						break;
					case L'}':
						if(t->get_first()) t->add_child(L"", nd_empty);
						t = t->get_parent();
						if(!t)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							delete __curvalue__;
							delete ret;
							return NULL;
						}
						state = s_delimitier;
						break;
					case L',':
						t->add_child(L"", nd_empty);
						break;
					default:
						//curvalue = String(sym);
						__curvalue__->Clear();
						__curvalue__->Append(sym);
						state = s_nonstring;
						break;
				}
				break;
			case s_delimitier:
				switch(sym)
				{
					case L' ': // space
					case L'\t':
					case L'\r':
					case L'\n':
						break;
					case L',':
						state = s_value;
						break;
					case L'}':
						t = t->get_parent();
						if(!t)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							delete ret;
							return NULL;
						}
						//state = s_delimitier;
						break;
					default:
						if(msreg) msreg->AddError(L"Ошибка формата потока. Ошибочный символ в режиме ожидания разделителя.",
							L"Символ", sym,
							L"Код символа", tohex(sym),
							L"Путь", path);
						delete __curvalue__;
						delete ret;
						return NULL;
				}
				break;
			case s_string:
				if(sym == L'"'){
					state = s_quote_or_endstring;
				}
				//else curvalue += String(sym);
				else __curvalue__->Append(sym);
				break;
			case s_quote_or_endstring:
				if(sym == L'"')
				{
					//curvalue += String(sym);
					__curvalue__->Append(sym);
					state = s_string;
				}
				else
				{
					//t->add_child(curvalue, nd_string);
					t->add_child(__curvalue__->ToString(), nd_string);
					switch(sym)
					{
						case L' ': // space
						case L'\t':
						case L'\r':
						case L'\n':
							state = s_delimitier;
							break;
						case L',':
							state = s_value;
							break;
						case L'}':
							t = t->get_parent();
							if(!t)
							{
								if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
									L"Позиция", i,
									L"Путь", path);
								delete __curvalue__;
								delete ret;
								return NULL;
							}
							state = s_delimitier;
							break;
						default:
							if(msreg) msreg->AddError(L"Ошибка формата потока. Ошибочный символ в режиме ожидания разделителя.",
								L"Символ", sym,
								L"Код символа", tohex(sym),
								L"Путь", path);
							delete __curvalue__;
							delete ret;
							return NULL;
					}
				}
				break;
			case s_nonstring:
				switch(sym)
				{
					case L',':
						curvalue = __curvalue__->ToString();
						nt = classification_value(curvalue);
						if(nt == nd_unknown) if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
							L"Значение", curvalue,
							L"Путь", path);
						t->add_child(curvalue, nt);
						state = s_value;
						break;
					case L'}':
						curvalue = __curvalue__->ToString();
						nt = classification_value(curvalue);
						if(nt == nd_unknown) if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
							L"Значение", curvalue,
							L"Путь", path);
						t->add_child(curvalue, nt);
						t = t->get_parent();
						if(!t)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							delete __curvalue__;
							delete ret;
							return NULL;
						}
						state = s_delimitier;
						break;
					default:
						//curvalue += String(sym);
						__curvalue__->Append(sym);
						break;
				}
				break;
			default:
				if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный режим разбора.",
					L"Режим разбора", tohex(state),
					L"Путь", path);
				delete __curvalue__;
				delete ret;
				return NULL;

		}
	}

	if(state == s_nonstring)
	{
		curvalue = __curvalue__->ToString();
		nt = classification_value(curvalue);
		if(nt == nd_unknown) if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
			L"Значение", curvalue,
			L"Путь", path);
		t->add_child(curvalue, nt);
	}
	//else if(state == s_quote_or_endstring) t->add_child(curvalue, nd_string);
	else if(state == s_quote_or_endstring) t->add_child(__curvalue__->ToString(), nd_string);
	else if(state != s_delimitier)
	{
		if(msreg) msreg->AddError(L"Ошибка формата потока. Незавершенное значение",
			L"Режим разбора", tohex(state),
			L"Путь", path);
		delete __curvalue__;
		delete ret;
		return NULL;
	}

	if(t != ret)
	{
		if(msreg) msreg->AddError(L"Ошибка формата потока. Не хватает закрывающих скобок } в конце текста разбора.",
			L"Путь", path);
		delete __curvalue__;
		delete ret;
		return NULL;
	}

	delete __curvalue__;

	return ret;

}

// проверка формата потока
bool test_parse_1Ctext(TStream* str, const String& path)
{
	TStringBuilder* __curvalue__;

	enum _state{
		s_value, // ожидание начала значения
		s_delimitier, // ожидание разделителя
		s_string, // режим ввода строки
		s_quote_or_endstring, // режим ожидания конца строки или двойной кавычки
		s_nonstring // режим ввода значения не строки
	}state = s_value;

	String curvalue;
	int i;
	wchar_t sym;
	int _sym;
	node_type nt;
	int level;
	bool ret = true;

	__curvalue__ = new TStringBuilder;

	TStreamReader* reader;

	reader = new TStreamReader(str, true);
	level = 0;

	//for(i = 1, _sym = reader->Read(); _sym >= 0; i++, _sym = reader->Read())
	for(i = 1, _sym = reader->Read(); _sym > 0; i++, _sym = reader->Read())
	{
		sym = _sym;
		//if(i % 0x100000 == 0) if(msreg) msreg->Status(String(i/0x100000) + L" MB");

		switch(state)
		{
			case s_value:
				switch(sym)
				{
					case L' ': // space
					case L'\t':
					case L'\r':
					case L'\n':
						break;
					case L'"':
						//curvalue = L"";
						__curvalue__->Clear();
						state = s_string;
						break;
					case L'{':
						level++;
						break;
					case L'}':
						if(level <= 0)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							ret = false;
						}
						state = s_delimitier;
						level--;
						break;
					default:
						//curvalue = String(sym);
						__curvalue__->Clear();
						__curvalue__->Append(sym);
						state = s_nonstring;
						break;
				}
				break;
			case s_delimitier:
				switch(sym)
				{
					case L' ': // space
					case L'\t':
					case L'\r':
					case L'\n':
						break;
					case L',':
						state = s_value;
						break;
					case L'}':
						if(level <= 0)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							ret = false;
						}
						level--;
						break;
					default:
						if(msreg) msreg->AddError(L"Ошибка формата потока. Ошибочный символ в режиме ожидания разделителя.",
							L"Символ", sym,
							L"Код символа", tohex(sym),
							L"Путь", path);
						//msreg->Status(L"");
						delete reader;
						return ret;
				}
				break;
			case s_string:
				if(sym == L'"'){
					state = s_quote_or_endstring;
				}
				//else curvalue += String(sym);
				else __curvalue__->Append(sym);
				break;
			case s_quote_or_endstring:
				if(sym == L'"')
				{
					//curvalue += String(sym);
					__curvalue__->Append(sym);
					state = s_string;
				}
				else
				{
					switch(sym)
					{
						case L' ': // space
						case L'\t':
						case L'\r':
						case L'\n':
							state = s_delimitier;
							break;
						case L',':
							state = s_value;
							break;
						case L'}':
							if(level <= 0)
							{
								if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
									L"Позиция", i,
									L"Путь", path);
								ret = false;
							}
							level--;
							state = s_delimitier;
							break;
						default:
							if(msreg) msreg->AddError(L"Ошибка формата потока. Ошибочный символ в режиме ожидания разделителя.",
								L"Символ", sym,
								L"Код символа", tohex(sym),
								L"Путь", path);
							//msreg->Status(L"");
							delete reader;
							return ret;
					}
				}
				break;
			case s_nonstring:
				switch(sym)
				{
					case L',':
						curvalue = __curvalue__->ToString();
						nt = classification_value(curvalue);
						if(nt == nd_unknown)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
								L"Значение", curvalue,
								L"Путь", path);
							ret = false;
						}
						state = s_value;
						break;
					case L'}':
						curvalue = __curvalue__->ToString();
						nt = classification_value(curvalue);
						if(nt == nd_unknown)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
								L"Значение", curvalue,
								L"Путь", path);
							ret = false;
						}
						if(level <= 0)
						{
							if(msreg) msreg->AddError(L"Ошибка формата потока. Лишняя закрывающая скобка }.",
								L"Позиция", i,
								L"Путь", path);
							ret = false;
						}
						level--;
						state = s_delimitier;
						break;
					default:
						//curvalue += String(sym);
						__curvalue__->Append(sym);
						break;
				}
				break;
			default:
				if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный режим разбора.",
					L"Режим разбора", tohex(state),
					L"Путь", path);
				ret = false;
				break;
		}
	}

	if(state == s_nonstring)
	{
		curvalue = __curvalue__->ToString();
		nt = classification_value(curvalue);
		if(nt == nd_unknown)
		{
			if(msreg) msreg->AddError(L"Ошибка формата потока. Неизвестный тип значения.",
				L"Значение", curvalue,
				L"Путь", path);
			ret = false;
		}
	}
	else if(state == s_quote_or_endstring)
	{

	}
	else if(state != s_delimitier)
	{
		if(msreg) msreg->AddError(L"Ошибка формата потока. Незавершенное значение",
			L"Режим разбора", tohex(state),
			L"Путь", path);
		ret = false;
	}

	if(level > 0)
	{
		if(msreg) msreg->AddError(L"Ошибка формата потока. Не хватает закрывающих скобок } в конце текста разбора.",
			L"Путь", path);
		ret = false;
	}

	//msreg->Status(L"");
	delete reader;
	return ret;

}

String outtext(tree* t)
{
	String text;
	if(t) if(t->get_first()) t->get_first()->outtext(text);
	return text;
}

tree* find_node_by_guid(tree* root, const String& target_guid)
{
    if (!root)
    	return NULL;

    // Проверяем текущий узел
    if (root->get_value() == target_guid)
    {
        return root;
    }

    // Рекурсивно ищем в подчиненных узлах
    tree* result = NULL;
    for (int i = 0; i < root->get_num_subnode(); i++)
    {
        result = find_node_by_guid(root->get_subnode(i), target_guid);
        if (result)
        	return result;
    }

    return NULL;
}

namespace
{
	tree* find_metadata_node_by_guid_impl(tree* root, const String& target_guid, tree*& fallback, int& bestCount)
	{
		if (!root)
			return NULL;

		if (root->get_value() == target_guid)
		{
			if (!fallback)
				fallback = root;

			tree* next = root->get_next();
			if (next && next->get_type() == nd_number)
			{
				int currentCount = next->get_value().ToIntDef(0);
				if (currentCount > bestCount)
				{
					bestCount = currentCount;
					fallback = root;
				}
			}
		}

		for (int i = 0; i < root->get_num_subnode(); i++)
		{
			tree* result = find_metadata_node_by_guid_impl(root->get_subnode(i), target_guid, fallback, bestCount);
			if (result)
				return result;
		}

		return NULL;
	}
}

tree* find_metadata_node_by_guid(tree* root, const String& target_guid)
{
	tree* fallback = NULL;
	int bestCount = -1;
	tree* result = find_metadata_node_by_guid_impl(root, target_guid, fallback, bestCount);
	if (result)
		return result;
	return fallback;
}

