//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommandGroups.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommandGroups::TCommandGroups() : EmptyMetadataObject<TCommandGroups>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommandGroups::TCommandGroups(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TCommandGroups>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TCommandGroups::TCommandGroups(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TCommandGroups>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TCommandGroups::GetCommandName()
{
    return name;
}

void __fastcall TCommandGroups::SetCommandName(String _name)
{
    name = _name;
}
