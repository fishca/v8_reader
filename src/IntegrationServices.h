//---------------------------------------------------------------------------

#ifndef IntegrationServicesH
#define IntegrationServicesH

#include "EmptyMetadataObject.h"

//---------------------------------------------------------------------------

class TIntegrationServices : public EmptyMetadataObject<TIntegrationServices>
{
public:
    __fastcall TIntegrationServices();
    __fastcall TIntegrationServices(v8catalog* _parent, const String& _guid);
    __fastcall TIntegrationServices(v8catalog* _parent, const String& _guid, const String& _name);

    String __fastcall GetServiceName();
    void __fastcall SetServiceName(String _name);
};

//---------------------------------------------------------------------------
#endif
