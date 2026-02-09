//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Catalogs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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

__fastcall TCatalogs::TCatalogs()
	: MetadataObjectWithSections()
{
}

__fastcall TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
}

__fastcall TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
}

__fastcall TCatalogs::~TCatalogs()
{
}

void __fastcall TCatalogs::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetCatalogsPaths());
}
