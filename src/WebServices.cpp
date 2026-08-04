//---------------------------------------------------------------------------
#pragma hdrstop

#include "WebServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TWebServices::TWebServices() : EmptyMetadataObject<TWebServices>()
{
	name = "";
	root_data = nullptr;
	parent = nullptr;
}

__fastcall TWebServices::TWebServices(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TWebServices>()
{
	name = "";
	parent = _parent;
	root_data.reset();
}

__fastcall TWebServices::TWebServices(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TWebServices>()
{
	name = _name;
	parent = _parent;
	root_data.reset();
}

String __fastcall TWebServices::GetWebServiceName()
{
	return name;
}

void __fastcall TWebServices::SetWebServiceName(String _name)
{
	name = _name;
}
//---------------------------------------------------------------------------
