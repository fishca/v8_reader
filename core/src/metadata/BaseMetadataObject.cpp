//---------------------------------------------------------------------------

#pragma hdrstop

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall BaseMetadataObject::BaseMetadataObject()
{
    name = "";
    guid = "";
    root_data = nullptr;
    parent = nullptr;
}

__fastcall BaseMetadataObject::BaseMetadataObject(v8catalog* _parent, const String& _guid)
{
    guid = _guid;
    parent = _parent;
    root_data.reset(get_treeFromV8file(parent->GetFile(_guid)));
    name = ""; // Имя будет инициализировано в производных классах
}

__fastcall BaseMetadataObject::BaseMetadataObject(v8catalog* _parent, const String& _guid, const String& _name)
{
    name = _name;
    guid = _guid;
    parent = _parent;
    root_data.reset(get_treeFromV8file(parent->GetFile(_guid)));
}

__fastcall BaseMetadataObject::~BaseMetadataObject()
{
	// unique_ptr автоматически освобождает память
}

String __fastcall BaseMetadataObject::GetName()
{
    return name;
}

String __fastcall BaseMetadataObject::GetGUID()
{
    return guid;
}

bool __fastcall BaseMetadataObject::HasEditableModuleText()
{
	return false;
}

String __fastcall BaseMetadataObject::GetEditableModuleText()
{
	return L"";
}

void __fastcall BaseMetadataObject::SetEditableModuleText(const String& value)
{
}

bool __fastcall BaseMetadataObject::SaveEditableModuleText(const String& value, String& errorText)
{
	errorText = L"Для этого объекта редактирование модуля не реализовано.";
	return false;
}

ModuleTextLocation __fastcall BaseMetadataObject::GetEditableModuleLocation()
{
	return ModuleTextLocation();
}

bool __fastcall BaseMetadataObject::HasEditableModuleText(ModuleTextKind kind)
{
	return HasEditableModuleText();
}

String __fastcall BaseMetadataObject::GetEditableModuleText(ModuleTextKind kind)
{
	return GetEditableModuleText();
}

void __fastcall BaseMetadataObject::SetEditableModuleText(ModuleTextKind kind, const String& value)
{
	SetEditableModuleText(value);
}

bool __fastcall BaseMetadataObject::SaveEditableModuleText(ModuleTextKind kind, const String& value, String& errorText)
{
	return SaveEditableModuleText(value, errorText);
}

ModuleTextLocation __fastcall BaseMetadataObject::GetEditableModuleLocation(ModuleTextKind kind)
{
	return GetEditableModuleLocation();
}
