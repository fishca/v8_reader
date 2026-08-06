//---------------------------------------------------------------------------

#pragma hdrstop

#include "FunctionalOptionsParameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TFunctionalOptionsParameters::TFunctionalOptionsParameters() : EmptyMetadataObject<TFunctionalOptionsParameters>()
{
    name = "";
    root_data.reset();
}

__fastcall TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TFunctionalOptionsParameters>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TFunctionalOptionsParameters>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TFunctionalOptionsParameters::GetParameterName()
{
    return name;
}

void __fastcall TFunctionalOptionsParameters::SetParameterName(String _name)
{
    name = _name;
}
