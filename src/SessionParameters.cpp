//---------------------------------------------------------------------------

#pragma hdrstop

#include "SessionParameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TSessionParameters::TSessionParameters() : EmptyMetadataObject<TSessionParameters>()
{
    name = "";
    root_data.reset();
}

__fastcall TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TSessionParameters>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TSessionParameters>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TSessionParameters::GetParameterName()
{
    return name;
}

void __fastcall TSessionParameters::SetParameterName(String _name)
{
    name = _name;
}
