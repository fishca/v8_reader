//---------------------------------------------------------------------------

#pragma hdrstop

#include "DefinedTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TDefinedTypes::TDefinedTypes() : EmptyMetadataObject<TDefinedTypes>()
{
    typeName = "";
    root_data.reset();
}

__fastcall TDefinedTypes::TDefinedTypes(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TDefinedTypes>(_parent, _guid)
{
    typeName = "";
    root_data.reset();
}

__fastcall TDefinedTypes::TDefinedTypes(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TDefinedTypes>(_parent, _guid, _name)
{
    typeName = _name;
    root_data.reset();
}

String __fastcall TDefinedTypes::GetTypeName()
{
    return typeName;
}

void __fastcall TDefinedTypes::SetTypeName(String _name)
{
    typeName = _name;
    name = _name;
}
