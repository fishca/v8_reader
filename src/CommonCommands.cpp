//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonCommands.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonCommands::TCommonCommands() : EmptyMetadataObject<TCommonCommands>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonCommands::TCommonCommands(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TCommonCommands>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonCommands::TCommonCommands(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TCommonCommands>()
{
    name = _name;
    root_data.reset();
}

String __fastcall TCommonCommands::GetCommandName()
{
    return name;
}

void __fastcall TCommonCommands::SetCommandName(String _name)
{
    name = _name;
}
