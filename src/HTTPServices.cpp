#include <vcl.h>
#pragma hdrstop

#include "HTTPServices.h"

//---------------------------------------------------------------------------
__fastcall THTTPServices::THTTPServices() : EmptyMetadataObject<THTTPServices>()
{
	name = "";
	root_data = nullptr;
	parent = nullptr;
}

//---------------------------------------------------------------------------
__fastcall THTTPServices::THTTPServices(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<THTTPServices>()
{
	name = "";
	parent = _parent;
	root_data.reset();
}

//---------------------------------------------------------------------------
__fastcall THTTPServices::THTTPServices(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<THTTPServices>()
{
	name = _name;
	parent = _parent;
	root_data.reset();
}

//---------------------------------------------------------------------------
String __fastcall THTTPServices::GetHTTPServicesName()
{
	return name;
}
//---------------------------------------------------------------------------
void __fastcall THTTPServices::SetHTTPServicesName(String _name)
{
	name = _name;
}
//---------------------------------------------------------------------------
