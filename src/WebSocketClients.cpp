//---------------------------------------------------------------------------

#pragma hdrstop

#include "WebSocketClients.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TWebSocketClients::TWebSocketClients() : EmptyMetadataObject<TWebSocketClients>()
{
    clientName = "";
    root_data.reset();
}

__fastcall TWebSocketClients::TWebSocketClients(v8catalog* _parent, const String& _guid)
    : EmptyMetadataObject<TWebSocketClients>(_parent, _guid)
{
    clientName = "";
    root_data.reset();
}

__fastcall TWebSocketClients::TWebSocketClients(v8catalog* _parent, const String& _guid, const String& _name)
    : EmptyMetadataObject<TWebSocketClients>(_parent, _guid, _name)
{
    clientName = _name;
    root_data.reset();
}

String __fastcall TWebSocketClients::GetClientName()
{
    return clientName;
}

void __fastcall TWebSocketClients::SetClientName(String _name)
{
    clientName = _name;
    name = _name;
}
