//---------------------------------------------------------------------------

#pragma hdrstop

#include "EventSubscriptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TEventSubscriptions::TEventSubscriptions() : EmptyMetadataObject<TEventSubscriptions>()
{
    name = "";
    root_data.reset();
}

__fastcall TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TEventSubscriptions>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TEventSubscriptions>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TEventSubscriptions::GetEventSubscriptionName()
{
    return name;
}

void __fastcall TEventSubscriptions::SetEventSubscriptionName(String _name)
{
    name = _name;
}
