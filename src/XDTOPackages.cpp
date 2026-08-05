//---------------------------------------------------------------------------
#pragma hdrstop

#include "XDTOPackages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TXDTOPackages::TXDTOPackages() : EmptyMetadataObject<TXDTOPackages>()
{
    name = "";
    root_data = nullptr;
    parent = nullptr;
}

__fastcall TXDTOPackages::TXDTOPackages(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TXDTOPackages>()
{
    name = "";
    parent = _parent;
    root_data.reset();
}

__fastcall TXDTOPackages::TXDTOPackages(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TXDTOPackages>()
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

String __fastcall TXDTOPackages::GetXDTOPackageName()
{
    return name;
}
//---------------------------------------------------------------------------
