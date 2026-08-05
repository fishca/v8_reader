//---------------------------------------------------------------------------

#ifndef WebSocketClientsH
#define WebSocketClientsH

#include "EmptyMetadataObject.h"

//---------------------------------------------------------------------------

class TWebSocketClients : public EmptyMetadataObject<TWebSocketClients>
{
public:
    __fastcall TWebSocketClients();
    __fastcall TWebSocketClients(v8catalog* _parent, const String& _guid);
    __fastcall TWebSocketClients(v8catalog* _parent, const String& _guid, const String& _name);

    String __fastcall GetClientName();
    void __fastcall SetClientName(String _name);

private:
    String clientName;  // имя клиента WebSocket
};

//---------------------------------------------------------------------------
#endif
