//---------------------------------------------------------------------------


#include "Common.h"
#include "Journals.h"
//---------------------------------------------------------------------------

static MetadataTreePaths GetJournalsPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 4;
	paths.attItemPath = {0, 1, 2};  // у журналов другой путь к имени реквизита
	paths.tabIdx = 3;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 6;
	paths.cmdIdx = 5;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	paths.moxIdx = 3;
	paths.getFormNameFunc = GetNameFormCatalogs16;
	paths.hasTabulars = false;  // у журналов документов нет табличных частей
	return paths;
}

TJournals::TJournals()
	: MetadataObjectWithSections()
{
}

TJournals::TJournals(v8catalog *_parent, const Utf16String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TJournals::TJournals(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TJournals::~TJournals()
{
}

void TJournals::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetJournalsPaths());
}

