//---------------------------------------------------------------------------


#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

BaseMetadataObject::BaseMetadataObject()
{
    name = u"";
    guid = u"";
	guid16.clear();
    root_data = nullptr;
    parent = nullptr;
}

BaseMetadataObject::BaseMetadataObject(v8catalog* _parent, const Utf16String& _guid)
{
    guid = _guid;
	guid16 = _guid;
    parent = _parent;
    root_data.reset(get_treeFromV8file(parent->GetFile16(guid16)));
    name = u""; // Имя будет инициализировано в производных классах
}

BaseMetadataObject::BaseMetadataObject(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name)
{
    name = _name;
    guid = _guid;
	guid16 = _guid;
    parent = _parent;
    root_data.reset(get_treeFromV8file(parent->GetFile16(guid16)));
}

BaseMetadataObject::~BaseMetadataObject()
{
	// unique_ptr автоматически освобождает память
}

Utf16String BaseMetadataObject::GetName()
{
    return name;
}

Utf16String BaseMetadataObject::GetGUID()
{
    return guid;
}

Utf16String BaseMetadataObject::GetGUID16()
{
	return guid16;
}

bool BaseMetadataObject::HasEditableModuleText()
{
	return false;
}

Utf16String BaseMetadataObject::GetEditableModuleText()
{
	return u"";
}

void BaseMetadataObject::SetEditableModuleText(const Utf16String& value)
{
}

bool BaseMetadataObject::SaveEditableModuleText(const Utf16String& value, Utf16String& errorText)
{
	errorText = u"Для этого объекта редактирование модуля не реализовано.";
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

Utf16String BaseMetadataObject::GetEditableModuleText(ModuleTextKind kind)
{
	return GetEditableModuleText();
}

void BaseMetadataObject::SetEditableModuleText(ModuleTextKind kind, const Utf16String& value)
{
	SetEditableModuleText(value);
}

bool BaseMetadataObject::SaveEditableModuleText(ModuleTextKind kind, const Utf16String& value, Utf16String& errorText)
{
	return SaveEditableModuleText(value, errorText);
}

ModuleTextLocation BaseMetadataObject::GetEditableModuleLocation(ModuleTextKind kind)
{
	return GetEditableModuleLocation();
}



