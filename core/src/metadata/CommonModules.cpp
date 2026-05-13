//---------------------------------------------------------------------------


#include "CommonModules.h"
//---------------------------------------------------------------------------

TCommonModules::TCommonModules() : BaseMetadataObject()
{
	root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
	name = _name;
}

void TCommonModules::LoadTextIfNeeded()
{
	if (textDocument.loaded)
		return;

	textDocument = ModuleTextStorage::LoadCommonModule(parent, guid, name);
	textDocument.loaded = true;
}

void TCommonModules::RefreshEditableTextIfNeeded()
{
	LoadTextIfNeeded();
	if (textDocument.location.editable)
		return;

	ModuleTextDocument refreshed = ModuleTextStorage::LoadCommonModule(parent, guid, name);
	if (refreshed.location.editable)
		textDocument = refreshed;
}

TCommonModules::~TCommonModules()
{
}

String TCommonModules::GetText()
{
	LoadTextIfNeeded();
	return textDocument.text;
}

void TCommonModules::SetText(String _text)
{
	LoadTextIfNeeded();
	textDocument.text = _text;
	textDocument.loaded = true;
	textDocument.dirty = true;
}

ModuleTextDocument& TCommonModules::GetTextDocument()
{
	RefreshEditableTextIfNeeded();
	return textDocument;
}

bool TCommonModules::SaveTextToSource(const String& newText, String& errorText)
{
	RefreshEditableTextIfNeeded();
	return ModuleTextStorage::SaveDocument(textDocument, newText, errorText);
}

bool TCommonModules::HasEditableModuleText()
{
	RefreshEditableTextIfNeeded();
	return !textDocument.text.IsEmpty() || textDocument.location.editable;
}

String TCommonModules::GetEditableModuleText()
{
	return GetText();
}

void TCommonModules::SetEditableModuleText(const String& value)
{
	SetText(value);
}

bool TCommonModules::SaveEditableModuleText(const String& value, String& errorText)
{
	return SaveTextToSource(value, errorText);
}

ModuleTextLocation TCommonModules::GetEditableModuleLocation()
{
	RefreshEditableTextIfNeeded();
	return textDocument.location;
}

void TCommonModules::initializeFromTree()
{
}

