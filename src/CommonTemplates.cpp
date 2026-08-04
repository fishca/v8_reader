//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonTemplates.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonTemplates::TCommonTemplates() : EmptyMetadataObject<TCommonTemplates>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonTemplates::TCommonTemplates(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TCommonTemplates>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonTemplates::TCommonTemplates(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TCommonTemplates>()
{
    name = _name;
    root_data.reset();
}

String __fastcall TCommonTemplates::GetTemplateName()
{
    return name;
}

void __fastcall TCommonTemplates::SetTemplateName(String _name)
{
    name = _name;
}
