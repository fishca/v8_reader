//---------------------------------------------------------------------------

#pragma hdrstop

#include "StyleItems.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TStyleItems::TStyleItems() : EmptyMetadataObject<TStyleItems>()
{
    styleItemName = "";
    root_data.reset();
}

__fastcall TStyleItems::TStyleItems(v8catalog* _parent, const String& _guid)
    : EmptyMetadataObject<TStyleItems>(_parent, _guid)
{
    styleItemName = "";
    root_data.reset();
}

__fastcall TStyleItems::TStyleItems(v8catalog* _parent, const String& _guid, const String& _name)
    : EmptyMetadataObject<TStyleItems>(_parent, _guid, _name)
{
    styleItemName = _name;
    root_data.reset();
}

String __fastcall TStyleItems::GetStyleItemName()
{
    return styleItemName;
}

void __fastcall TStyleItems::SetStyleItemName(String _name)
{
    styleItemName = _name;
    name = _name;
}
