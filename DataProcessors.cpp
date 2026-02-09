//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "DataProcessors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static MetadataTreePaths GetDataProcessorsPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 7;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.tabIdx = 3;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 6;
	paths.cmdIdx = 5;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	paths.moxIdx = 4;
	paths.getFormNameFunc = GetNameFormReports;
	paths.hasTabulars = true;
	return paths;
}

__fastcall TDataProcessors::TDataProcessors()
	: MetadataObjectWithSections()
{
}

__fastcall TDataProcessors::TDataProcessors(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
}

__fastcall TDataProcessors::TDataProcessors(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
}

__fastcall TDataProcessors::~TDataProcessors()
{
}

void __fastcall TDataProcessors::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetDataProcessorsPaths());
}
