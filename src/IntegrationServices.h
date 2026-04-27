//---------------------------------------------------------------------------

#ifndef IntegrationServicesH
#define IntegrationServicesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TIntegrationServices : public BaseMetadataObject
{
private:
    String serviceName;

public:
    __fastcall TIntegrationServices();
    __fastcall TIntegrationServices(v8catalog* _parent, const String& _guid);
    __fastcall TIntegrationServices(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TIntegrationServices();

    String __fastcall GetServiceName();
    void __fastcall SetServiceName(String _name);

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
