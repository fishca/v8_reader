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
    TWebSocketClients();
    TWebSocketClients(v8catalog* _parent, const String& _guid);
    TWebSocketClients(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TWebSocketClients();

    String GetClientName();
    void SetClientName(String _name);

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void initializeFromTree() override;

private:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif

