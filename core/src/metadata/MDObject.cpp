//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma hdrstop

#include "MDObject.h"
//---------------------------------------------------------------------------


TMDObject* __fastcall TMDObjectManager::newMetaData()
{
	TMDObject* md = CreateMetaData();
	md_list->Add(md);

	return md;
}

__fastcall TMDObjectManager::TMDObjectManager()
{
	md_list = new TObjectList(true);
}

