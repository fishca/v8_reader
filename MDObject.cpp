//---------------------------------------------------------------------------

#pragma hdrstop

#include "MDObject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TMDObject* TMDObjectManager::newMetaData()
{
	TMDObject* md = CreateMetaData();
	md_list->Add(md);

	return md;
}

__fastcall TMDObjectManager::TMDObjectManager()
{
	md_list = new TObjectList(true);
}

