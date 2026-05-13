//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma hdrstop

#include "MDObject.h"
//---------------------------------------------------------------------------


TMDObject* TMDObjectManager::newMetaData()
{
	TMDObject* md = CreateMetaData();
	md_list->Add(md);

	return md;
}

TMDObjectManager::TMDObjectManager()
{
	md_list = new TObjectList(true);
}


