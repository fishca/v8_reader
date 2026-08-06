//---------------------------------------------------------------------------

#pragma hdrstop

#include "Interfaces.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TInterfaces::TInterfaces() : EmptyMetadataObject<TInterfaces>()
{
    name = "";
    root_data.reset();
}

__fastcall TInterfaces::TInterfaces(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TInterfaces>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TInterfaces::TInterfaces(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TInterfaces>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TInterfaces::GetInterfaceName()
{
    return name;
}

void __fastcall TInterfaces::SetInterfaceName(String _name)
{
    name = _name;
}
