//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Journals.h"
#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Убрать static для CRTP-шаблона
MetadataTreePaths GetJournalsPaths()
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
	paths.getFormNameFunc = GetNameFormCatalogs;
	paths.hasTabulars = false;  // у журналов документов нет табличных частей
	return paths;
}

__fastcall TJournals::TJournals()
	: MetadataObjectWithSectionsT<TJournals, GetJournalsPaths>()
{
}

__fastcall TJournals::TJournals(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSectionsT<TJournals, GetJournalsPaths>(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TJournals::TJournals(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSectionsT<TJournals, GetJournalsPaths>(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TJournals::~TJournals()
{
}
