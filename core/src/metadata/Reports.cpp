//---------------------------------------------------------------------------


#include "Common.h"
#include "Reports.h"
//---------------------------------------------------------------------------

static MetadataTreePaths GetReportsPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 4;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.tabIdx = 6;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 5;
	paths.cmdIdx = 7;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	paths.moxIdx = 3;
	paths.getFormNameFunc = GetNameFormReports;
	paths.hasTabulars = true;
	return paths;
}

TReports::TReports()
	: MetadataObjectWithSections()
{
	root_data.reset();
}

TReports::TReports(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TReports::TReports(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TReports::~TReports()
{
}

void TReports::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetReportsPaths());
}

