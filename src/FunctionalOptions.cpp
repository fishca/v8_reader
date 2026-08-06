//---------------------------------------------------------------------------

#pragma hdrstop

#include "FunctionalOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TFunctionalOptions::TFunctionalOptions() : EmptyMetadataObject<TFunctionalOptions>()
{
    name = "";
    root_data.reset();
}

__fastcall TFunctionalOptions::TFunctionalOptions(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TFunctionalOptions>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TFunctionalOptions::TFunctionalOptions(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TFunctionalOptions>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TFunctionalOptions::GetOptionName()
{
    return name;
}

void __fastcall TFunctionalOptions::SetOptionName(String _name)
{
    name = _name;
}
