//-------------------------------------------------------
// This file is part of the DataProcessor Engine
// Do not modify this file manually
// -----------------------------------

#pragma hdrstop

#include "IntegrationServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TIntegrationServices::TIntegrationServices()
	: EmptyMetadataObject<TIntegrationServices>()
{
	name = "";
	root_data.reset();
}

__fastcall TIntegrationServices::TIntegrationServices(v8catalog *_parent, const String& _guid)
	: EmptyMetadataObject<TIntegrationServices>(_parent, _guid)
{
	name = "";
	root_data.reset();
}

__fastcall TIntegrationServices::TIntegrationServices(v8catalog *_parent, const String& _guid, const String& _name)
	: EmptyMetadataObject<TIntegrationServices>(_parent, _guid, _name)
{
	name = _name;
	root_data.reset();
}

String __fastcall TIntegrationServices::GetServiceName()
{
	return name;
}

void __fastcall TIntegrationServices::SetServiceName(String _name)
{
	name = _name;
}
