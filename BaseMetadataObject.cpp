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
    root_data = get_treeFromV8file(parent->GetFile(_guid));
    name = ""; // Имя будет инициализировано в производных классах
}

__fastcall BaseMetadataObject::BaseMetadataObject(v8catalog* _parent, const String& _guid, const String& _name)
{
    name = _name;
    guid = _guid;
    parent = _parent;
    root_data = get_treeFromV8file(parent->GetFile(_guid));
}

__fastcall BaseMetadataObject::~BaseMetadataObject()
{
	// Освобождение ресурсов, если необходимо
	if (root_data)
	{
		delete root_data;
		//root_data = nullptr;
	}
}

String __fastcall BaseMetadataObject::GetName()
{
    return name;
}

String __fastcall BaseMetadataObject::GetGUID()
{
    return guid;
}

