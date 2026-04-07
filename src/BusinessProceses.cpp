//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "BusinessProceses.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static MetadataTreePaths GetBusinessProcessesPaths()
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

__fastcall TBusinessProceses::TBusinessProceses()
	: MetadataObjectWithSections()
{
}

__fastcall TBusinessProceses::TBusinessProceses(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TBusinessProceses::TBusinessProceses(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TBusinessProceses::~TBusinessProceses()
{
}

void __fastcall TBusinessProceses::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetBusinessProcessesPaths());
}
