//---------------------------------------------------------------------------


#include "Common.h"
#include "Catalogs.h"
//---------------------------------------------------------------------------

static MetadataTreePaths GetCatalogsPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 6;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.tabIdx = 5;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 7;
	paths.cmdIdx = 4;
	paths.cmdItemPath = {0, 1, 3, 2, 9, 2};
	paths.moxIdx = 3;
	paths.getFormNameFunc = GetNameFormCatalogs;
	paths.hasTabulars = true;
	return paths;
}

TCatalogs::TCatalogs()
	: MetadataObjectWithSections()
{
}

TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TCatalogs::~TCatalogs()
{
}

void TCatalogs::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetCatalogsPaths());
}

