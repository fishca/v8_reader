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
	paths.tabIdx = 7;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 4;
	paths.cmdIdx = 8;
	paths.cmdItemPath = {0, 1, 3, 2, 9, 2};
	paths.moxIdx = 3;
	paths.getFormNameFunc = GetNameFormDescriptor;
	paths.hasTabulars = true;
	return paths;
}

TTasks::TTasks()
	: MetadataObjectWithSections()
{
}

TTasks::TTasks(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TTasks::TTasks(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TTasks::~TTasks()
{
}

void TTasks::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetTasksPaths());
}

