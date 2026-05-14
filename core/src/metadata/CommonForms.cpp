//---------------------------------------------------------------------------


#include "CommonForms.h"
//---------------------------------------------------------------------------

namespace
{
	bool LooksLike1CModuleText(const String& value)
	{
		return value.Pos(L"Процедура ") > 0
			|| value.Pos(L"Функция ") > 0
			|| value.Pos(L"КонецПроцедуры") > 0
			|| value.Pos(L"КонецФункции") > 0
			|| value.Pos(L"\n") > 0;
	}

	String FindEmbeddedModuleText(tree* node)
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

	String GetManagedFormModuleText(tree* root)
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

TCommonForms::TCommonForms() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
	textDocument.text = u"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

TCommonForms::TCommonForms(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
	textDocument.text = u"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

TCommonForms::TCommonForms(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
	textDocument.text = u"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

TCommonForms::~TCommonForms()
{
}

Utf16String TCommonForms::GetFormName()
{
    return name;
}

void TCommonForms::SetFormName(const Utf16String& _name)
{
    name = _name;
}

void TCommonForms::LoadTextIfNeeded()
{
	if (textDocument.loaded)
		return;

	textDocument = ModuleTextStorage::LoadCommonForm(parent, guid, name);
	textDocument.loaded = true;
}

void TCommonForms::RefreshEditableTextIfNeeded()
{
	LoadTextIfNeeded();
	if (textDocument.location.editable)
		return;

	ModuleTextDocument refreshed = ModuleTextStorage::LoadCommonForm(parent, guid, name);
	if (refreshed.location.editable)
		textDocument = refreshed;
}

Utf16String TCommonForms::GetText()
{
	LoadTextIfNeeded();
	return textDocument.text;
}

void TCommonForms::SetText(const Utf16String& _text)
{
	LoadTextIfNeeded();
	textDocument.text = _text;
	textDocument.loaded = true;
	textDocument.dirty = true;
}

ModuleTextDocument& TCommonForms::GetTextDocument()
{
	RefreshEditableTextIfNeeded();
	return textDocument;
}

bool TCommonForms::SaveTextToSource(const Utf16String& newText, Utf16String& errorText)
{
	RefreshEditableTextIfNeeded();
	return ModuleTextStorage::SaveDocument(textDocument, newText, errorText);
}

bool TCommonForms::HasEditableModuleText()
{
	RefreshEditableTextIfNeeded();
	return !textDocument.text.empty() || textDocument.location.editable;
}

Utf16String TCommonForms::GetEditableModuleText()
{
	return GetText();
}

void TCommonForms::SetEditableModuleText(const Utf16String& value)
{
	SetText(value);
}

bool TCommonForms::SaveEditableModuleText(const Utf16String& value, Utf16String& errorText)
{
	return SaveTextToSource(value, errorText);
}

ModuleTextLocation TCommonForms::GetEditableModuleLocation()
{
	RefreshEditableTextIfNeeded();
	return textDocument.location;
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

void TCommonForms::initializeFromTree()
{
    // Инициализация общей формы из дерева метаданных
    // Имя общей формы уже установлено в конструкторе
}

