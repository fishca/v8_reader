//---------------------------------------------------------------------------


#include "Common.h"
#include "ChartOfCalculationTypes.h"
//---------------------------------------------------------------------------

static MetadataTreePaths GetChartOfCalculationTypesPaths()
{
	MetadataTreePaths paths;
	// TODO: пути скопированы из Catalogs - необходимо проверить и исправить для ПВР
	paths.attIdx = 4;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.tabIdx = 3;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 7;
	paths.cmdIdx = 5;
	paths.cmdItemPath = {0, 1, 3, 2, 9, 2};
	paths.moxIdx = 6;
	paths.getFormNameFunc = GetNameFormCatalogs;
	paths.hasTabulars = true;
	return paths;
}

TChartOfCalculationTypes::TChartOfCalculationTypes()
	: MetadataObjectWithSections()
{
}

TChartOfCalculationTypes::TChartOfCalculationTypes(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TChartOfCalculationTypes::TChartOfCalculationTypes(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TChartOfCalculationTypes::~TChartOfCalculationTypes()
{
}

void TChartOfCalculationTypes::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetChartOfCalculationTypesPaths());
}

