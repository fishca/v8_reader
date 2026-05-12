//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "BusinessProceses.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static MetadataTreePaths GetBusinessProcessesPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 6;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.tabIdx = 7;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 4;
	paths.cmdIdx = 5;
	paths.cmdItemPath = {0, 1, 3, 2, 9, 2};
	paths.moxIdx = 3;
	paths.getFormNameFunc = GetNameFormDescriptor;
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
