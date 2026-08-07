//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonAttributes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonAttributes::TCommonAttributes() : EmptyMetadataObject<TCommonAttributes>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonAttributes::TCommonAttributes(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TCommonAttributes>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TCommonAttributes::TCommonAttributes(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TCommonAttributes>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TCommonAttributes::GetAttributeName()
{
    return name;
}

void __fastcall TCommonAttributes::SetAttributeName(String _name)
{
    name = _name;
}
