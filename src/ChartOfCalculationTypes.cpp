//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "ChartOfCalculationTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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

__fastcall TChartOfCalculationTypes::TChartOfCalculationTypes()
	: MetadataObjectWithSections()
{
}

__fastcall TChartOfCalculationTypes::TChartOfCalculationTypes(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSections(_parent, _guid)
{
	initializeFromTree();
}

__fastcall TChartOfCalculationTypes::TChartOfCalculationTypes(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSections(_parent, _guid, _name)
{
	initializeFromTree();
}

__fastcall TChartOfCalculationTypes::~TChartOfCalculationTypes()
{
}

void __fastcall TChartOfCalculationTypes::initializeFromTree()
{
	MetadataObjectWithSections::initializeFromTreeWithPaths(GetChartOfCalculationTypesPaths());
}
