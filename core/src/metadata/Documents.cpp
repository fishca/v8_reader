//---------------------------------------------------------------------------


#include "Common.h"
#include "Documents.h"
//---------------------------------------------------------------------------

static MetadataTreePaths GetDocumentsPaths()
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

TDocuments::TDocuments()
	: MetadataObjectWithSections()
{
}

TDocuments::TDocuments(v8catalog *_parent, const Utf16String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TDocuments::TDocuments(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TDocuments::~TDocuments()
{
}

void TDocuments::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetDocumentsPaths());
}

