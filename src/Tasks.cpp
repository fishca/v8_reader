//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Tasks.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static MetadataTreePaths GetTasksPaths()
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

__fastcall TTasks::TTasks()
	: MetadataObjectWithSections()
{
}

__fastcall TTasks::TTasks(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TTasks::TTasks(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TTasks::~TTasks()
{
}

void __fastcall TTasks::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetTasksPaths());
}
