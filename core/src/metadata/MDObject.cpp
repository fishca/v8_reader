//---------------------------------------------------------------------------


#include "MDObject.h"
//---------------------------------------------------------------------------
TMDObject* TMDObjectManager::newMetaData()
{
	std::unique_ptr<TMDObject> md(CreateMetaData());
	TMDObject* raw = md.get();
	md_list.push_back(std::move(md));
	return raw;
}

TMDObjectManager::TMDObjectManager()
{}


