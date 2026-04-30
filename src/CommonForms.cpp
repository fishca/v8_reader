//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonForms.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace
{
	bool __fastcall LooksLike1CModuleText(const String& value)
	{
		return value.Pos(L"Процедура ") > 0
			|| value.Pos(L"Функция ") > 0
			|| value.Pos(L"КонецПроцедуры") > 0
			|| value.Pos(L"КонецФункции") > 0
			|| value.Pos(L"\n") > 0;
	}

	String __fastcall FindEmbeddedModuleText(tree* node)
	{
		if (!node)
			return L"";

		if (node->get_type() == nd_string && LooksLike1CModuleText(node->get_value()))
			return node->get_value();

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			String found = FindEmbeddedModuleText(node->get_subnode(i));
			if (!found.IsEmpty())
				return found;
		}

		return L"";
	}

	String __fastcall GetManagedFormModuleText(tree* root)
	{
		if (!root || root->get_num_subnode() <= 0)
			return L"";

		tree* formRoot = root->get_subnode(0);
		if (!formRoot || formRoot->get_num_subnode() <= 2)
			return L"";

		tree* moduleNode = formRoot->get_subnode(2);
		if (!moduleNode || moduleNode->get_type() != nd_string)
			return L"";

		return moduleNode->get_value();
	}
}

__fastcall TCommonForms::TCommonForms() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
	text = L"";
	textLoaded = false;
}

__fastcall TCommonForms::TCommonForms(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
	text = L"";
	textLoaded = false;
}

__fastcall TCommonForms::TCommonForms(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
	text = L"";
	textLoaded = false;
}

__fastcall TCommonForms::~TCommonForms()
{
}

String __fastcall TCommonForms::GetFormName()
{
    return name;
}

void __fastcall TCommonForms::SetFormName(String _name)
{
    name = _name;
}

void __fastcall TCommonForms::LoadTextIfNeeded()
{
	if (textLoaded)
		return;

	text = L"";

	if ((parent) && (!guid.IsEmpty()))
	{
		v8file* data_form = parent->GetFile(guid + ".0");
		if (data_form)
		{
			v8catalog* data_form_cat = new v8catalog(data_form);
			if (data_form_cat)
			{
				auto module_file = data_form_cat->GetFile("module");
				if (module_file)
				{
					data_form_cat->ClearIs8316();
					TBytes bytes;
					TBytesStream* sb = new TBytesStream(bytes);
					module_file->SaveToStream(sb);

					TEncoding* enc = nullptr;
					TBytes sb_bytes = sb->Bytes;
					if (!sb_bytes.empty())
					{
						int off = TEncoding::GetBufferEncoding(sb_bytes, enc);
						if (off > 0)
						{
							bytes = TEncoding::Convert(enc, TEncoding::Unicode, sb_bytes, off, sb->Size - off);
							if (!bytes.empty())
								text = String((wchar_t*)&bytes[0], bytes.Length / 2);
						}
						else
						{
							text = String((char*)sb->Memory, sb->Size);
						}
					}

					delete sb;
				}

				delete data_form_cat;
			}
		}

		if (text.IsEmpty())
		{
			std::unique_ptr<tree> form_tree(get_treeFromV8file(data_form));
			text = GetManagedFormModuleText(form_tree.get());
			if (text.IsEmpty())
				text = FindEmbeddedModuleText(form_tree.get());
		}
	}

	textLoaded = true;
}

String __fastcall TCommonForms::GetText()
{
	LoadTextIfNeeded();
	return text;
}

void __fastcall TCommonForms::SetText(String _text)
{
	text = _text;
	textLoaded = true;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonForms::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonForms::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonForms::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonForms::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonForms::getForms()
{
    return forms;
}

void __fastcall TCommonForms::initializeFromTree()
{
    // Инициализация общей формы из дерева метаданных
    // Имя общей формы уже установлено в конструкторе
}
