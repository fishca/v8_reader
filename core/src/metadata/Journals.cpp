//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Journals.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static MetadataTreePaths GetJournalsPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 4;
	paths.attItemPath = {0, 1, 2};  // Сѓ Р¶СѓСЂРЅР°Р»РѕРІ РґСЂСѓРіРѕР№ РїСѓС‚СЊ Рє РёРјРµРЅРё СЂРµРєРІРёР·РёС‚Р°
	paths.tabIdx = 3;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 6;
	paths.cmdIdx = 5;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	paths.moxIdx = 3;
	paths.getFormNameFunc = GetNameFormCatalogs;
	paths.hasTabulars = false;  // Сѓ Р¶СѓСЂРЅР°Р»РѕРІ РґРѕРєСѓРјРµРЅС‚РѕРІ РЅРµС‚ С‚Р°Р±Р»РёС‡РЅС‹С… С‡Р°СЃС‚РµР№
	return paths;
}

TJournals::TJournals()
	: MetadataObjectWithSections()
{
}

TJournals::TJournals(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TJournals::TJournals(v8catalog *_parent, const String& _guid, const String& _name)
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

