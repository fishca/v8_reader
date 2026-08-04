//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonForms.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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


__fastcall TCommonForms::TCommonForms() : EmptyMetadataObject<TCommonForms>()
{
    name = "";
    root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

__fastcall TCommonForms::TCommonForms(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TCommonForms>()
{
    name = "";
    root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

__fastcall TCommonForms::TCommonForms(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TCommonForms>()
{
    name = _name;
    root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
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
	if (textDocument.loaded)
		return;

	textDocument = ModuleTextStorage::LoadCommonForm(parent, guid, name);
	textDocument.loaded = true;
}

void __fastcall TCommonForms::RefreshEditableTextIfNeeded()
{
	LoadTextIfNeeded();
	if (textDocument.location.editable)
		return;

	ModuleTextDocument refreshed = ModuleTextStorage::LoadCommonForm(parent, guid, name);
	if (refreshed.location.editable)
		textDocument = refreshed;
}

String __fastcall TCommonForms::GetText()
{
	LoadTextIfNeeded();
	return textDocument.text;
}

void __fastcall TCommonForms::SetText(String _text)
{
	LoadTextIfNeeded();
	textDocument.text = _text;
	textDocument.loaded = true;
	textDocument.dirty = true;
}

ModuleTextDocument& __fastcall TCommonForms::GetTextDocument()
{
	RefreshEditableTextIfNeeded();
	return textDocument;
}

bool __fastcall TCommonForms::SaveTextToSource(const String& newText, String& errorText)
{
	RefreshEditableTextIfNeeded();
	return ModuleTextStorage::SaveDocument(textDocument, newText, errorText);
}

bool __fastcall TCommonForms::HasEditableModuleText()
{
	RefreshEditableTextIfNeeded();
	return !textDocument.text.IsEmpty() || textDocument.location.editable;
}

String __fastcall TCommonForms::GetEditableModuleText()
{
	return GetText();
}

void __fastcall TCommonForms::SetEditableModuleText(const String& value)
{
	SetText(value);
}

bool __fastcall TCommonForms::SaveEditableModuleText(const String& value, String& errorText)
{
	return SaveTextToSource(value, errorText);
}

ModuleTextLocation __fastcall TCommonForms::GetEditableModuleLocation()
{
	RefreshEditableTextIfNeeded();
	return textDocument.location;
}
