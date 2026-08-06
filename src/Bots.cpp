//---------------------------------------------------------------------------

#pragma hdrstop

#include "Bots.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TBots::TBots() : EmptyMetadataObject<TBots>()
{
    botName = "";
    root_data.reset();
}

__fastcall TBots::TBots(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TBots>(_parent, _guid)
{
    botName = "";
    root_data.reset();
}

__fastcall TBots::TBots(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TBots>(_parent, _guid, _name)
{
    botName = _name;
    root_data.reset();
}

String __fastcall TBots::GetBotName()
{
    return botName;
}

void __fastcall TBots::SetBotName(String _name)
{
    botName = _name;
    name = _name;
}
