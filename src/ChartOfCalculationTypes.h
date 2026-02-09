//---------------------------------------------------------------------------

#ifndef ChartOfCalculationTypesH
#define ChartOfCalculationTypesH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TChartOfCalculationTypes : public MetadataObjectWithSections
{
public:
	__fastcall TChartOfCalculationTypes();
	__fastcall TChartOfCalculationTypes(v8catalog *_parent, const String& _guid);
	__fastcall TChartOfCalculationTypes(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TChartOfCalculationTypes();

	void __fastcall initializeFromTree() override;
};

#endif
