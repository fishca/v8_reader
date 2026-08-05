//---------------------------------------------------------------------------

#pragma hdrstop

#include "TConstants.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TConstants::TConstants() : EmptyMetadataObject<TConstants>()
{
    name = "";
    root_data.reset();
}

__fastcall TConstants::TConstants(v8catalog* _parent, const String& _guid)
    : EmptyMetadataObject<TConstants>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TConstants::TConstants(v8catalog* _parent, const String& _guid, const String& _name)
    : EmptyMetadataObject<TConstants>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TConstants::GetConstantsName()
{
    return name;
}

void __fastcall TConstants::SetConstantsName(String _name)
{
    name = _name;
}
