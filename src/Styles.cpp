//---------------------------------------------------------------------------

#pragma hdrstop

#include "Styles.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TStyles::TStyles() : EmptyMetadataObject<TStyles>()
{
    styleName = "";
    root_data.reset();
}

__fastcall TStyles::TStyles(v8catalog* _parent, const String& _guid)
    : EmptyMetadataObject<TStyles>(_parent, _guid)
{
    styleName = "";
    root_data.reset();
}

__fastcall TStyles::TStyles(v8catalog* _parent, const String& _guid, const String& _name)
    : EmptyMetadataObject<TStyles>(_parent, _guid, _name)
{
    styleName = _name;
    root_data.reset();
}

String __fastcall TStyles::GetStyleName()
{
    return styleName;
}

void __fastcall TStyles::SetStyleName(String _name)
{
    styleName = _name;
    name = _name;
}
