//---------------------------------------------------------------------------

#ifndef WebSocketClientsH
#define WebSocketClientsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TWebSocketClients : public BaseMetadataObject
{
public:
    TWebSocketClients();
    TWebSocketClients(v8catalog* _parent, const Utf16String& _guid);
    TWebSocketClients(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TWebSocketClients(v8catalog* _parent, const TStringLike& _guid)
        : TWebSocketClients(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TWebSocketClients(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TWebSocketClients(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TWebSocketClients();

    Utf16String GetClientName() const;
    void SetClientName(const Utf16String& _name);

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

