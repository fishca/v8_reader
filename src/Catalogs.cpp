//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Catalogs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Убрать static для CRTP-шаблона
MetadataTreePaths GetCatalogsPaths()
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
	: MetadataObjectWithSectionsT<TCatalogs, GetCatalogsPaths>()
{
}

__fastcall TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSectionsT<TCatalogs, GetCatalogsPaths>(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSectionsT<TCatalogs, GetCatalogsPaths>(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TCatalogs::~TCatalogs()
{
}
