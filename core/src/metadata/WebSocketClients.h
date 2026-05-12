//---------------------------------------------------------------------------

#ifndef WebSocketClientsH
#define WebSocketClientsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TWebSocketClients : public BaseMetadataObject
{
private:
    String clientName;

public:
    __fastcall TWebSocketClients();
    __fastcall TWebSocketClients(v8catalog* _parent, const String& _guid);
    __fastcall TWebSocketClients(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TWebSocketClients();

    String __fastcall GetClientName();
    void __fastcall SetClientName(String _name);

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void __fastcall initializeFromTree() override;

private:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif
