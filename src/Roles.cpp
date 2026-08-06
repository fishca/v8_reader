//---------------------------------------------------------------------------

#pragma hdrstop

#include "Roles.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TRoles::TRoles() : EmptyMetadataObject<TRoles>()
{
    roleName = "";
    root_data.reset();
}

__fastcall TRoles::TRoles(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TRoles>(_parent, _guid)
{
    roleName = "";
    root_data.reset();
}

__fastcall TRoles::TRoles(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TRoles>(_parent, _guid, _name)
{
    roleName = _name;
    root_data.reset();
}

String __fastcall TRoles::GetRoleName()
{
    return roleName;
}

void __fastcall TRoles::SetRoleName(String _name)
{
    roleName = _name;
    name = _name;
}
