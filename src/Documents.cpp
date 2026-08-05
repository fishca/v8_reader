//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Documents.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Убрать static для CRTP-шаблона
MetadataTreePaths GetDocumentsPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 5;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.tabIdx = 3;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 7;
	paths.cmdIdx = 6;
	paths.cmdItemPath = {0, 1, 3, 2, 9, 2};
	paths.moxIdx = 4;
	paths.getFormNameFunc = GetNameFormCatalogs;
	paths.hasTabulars = true;
	return paths;
}

__fastcall TDocuments::TDocuments()
	: MetadataObjectWithSectionsT<TDocuments, GetDocumentsPaths>()
{
}

__fastcall TDocuments::TDocuments(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSectionsT<TDocuments, GetDocumentsPaths>(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TDocuments::TDocuments(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSectionsT<TDocuments, GetDocumentsPaths>(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TDocuments::~TDocuments()
{
}
