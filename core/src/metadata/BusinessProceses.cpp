//---------------------------------------------------------------------------


#include "Common.h"
#include "BusinessProceses.h"
//---------------------------------------------------------------------------

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
	paths.getFormNameFunc = GetNameFormDescriptor16;
	paths.hasTabulars = true;
	return paths;
}

TBusinessProceses::TBusinessProceses()
	: MetadataObjectWithSections()
{
}

TBusinessProceses::TBusinessProceses(v8catalog *_parent, const Utf16String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TBusinessProceses::TBusinessProceses(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TBusinessProceses::~TBusinessProceses()
{
}

void TBusinessProceses::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetBusinessProcessesPaths());
}

