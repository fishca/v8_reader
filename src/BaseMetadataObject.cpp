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

