//---------------------------------------------------------------------------


#include "Common.h"
#include "DataProcessors.h"
//---------------------------------------------------------------------------

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
	paths.getFormNameFunc = GetNameFormReports16;
	paths.hasTabulars = true;
	return paths;
}

TDataProcessors::TDataProcessors()
	: MetadataObjectWithSections()
{
}

TDataProcessors::TDataProcessors(v8catalog *_parent, const Utf16String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TDataProcessors::TDataProcessors(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TDataProcessors::~TDataProcessors()
{
}

void TDataProcessors::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetDataProcessorsPaths());
}

