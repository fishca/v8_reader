//---------------------------------------------------------------------------


#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

BaseMetadataObject::BaseMetadataObject()
{
    name = "";
    guid = "";
    root_data = nullptr;
    parent = nullptr;
}

BaseMetadataObject::BaseMetadataObject(v8catalog* _parent, const String& _guid)
{
    guid = _guid;
    parent = _parent;
    root_data.reset(get_treeFromV8file(parent->GetFile16(V8Utf16FromString(_guid))));
    name = ""; // Имя будет инициализировано в производных классах
}

BaseMetadataObject::BaseMetadataObject(v8catalog* _parent, const String& _guid, const String& _name)
{
    name = _name;
    guid = _guid;
    parent = _parent;
    root_data.reset(get_treeFromV8file(parent->GetFile16(V8Utf16FromString(_guid))));
}

BaseMetadataObject::~BaseMetadataObject()
{
	// unique_ptr автоматически освобождает память
}

String BaseMetadataObject::GetName()
{
    return name;
}

String BaseMetadataObject::GetGUID()
{
    return guid;
}

bool BaseMetadataObject::HasEditableModuleText()
{
	return false;
}

String BaseMetadataObject::GetEditableModuleText()
{
	return L"";
}

void BaseMetadataObject::SetEditableModuleText(const String& value)
{
}

bool BaseMetadataObject::SaveEditableModuleText(const String& value, String& errorText)
{
	errorText = L"Для этого объекта редактирование модуля не реализовано.";
	return false;
}

ModuleTextLocation BaseMetadataObject::GetEditableModuleLocation()
{
	return ModuleTextLocation();
}

bool BaseMetadataObject::HasEditableModuleText(ModuleTextKind kind)
{
	return HasEditableModuleText();
}

String BaseMetadataObject::GetEditableModuleText(ModuleTextKind kind)
{
	return GetEditableModuleText();
}

void BaseMetadataObject::SetEditableModuleText(ModuleTextKind kind, const String& value)
{
	SetEditableModuleText(value);
}

bool BaseMetadataObject::SaveEditableModuleText(ModuleTextKind kind, const String& value, String& errorText)
{
	return SaveEditableModuleText(value, errorText);
}

ModuleTextLocation BaseMetadataObject::GetEditableModuleLocation(ModuleTextKind kind)
{
	return GetEditableModuleLocation();
}

