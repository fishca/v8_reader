//---------------------------------------------------------------------------

#ifndef ChartOfCalculationTypesH
#define ChartOfCalculationTypesH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TChartOfCalculationTypes : public MetadataObjectWithSections
{
public:
	TChartOfCalculationTypes();
	TChartOfCalculationTypes(v8catalog *_parent, const String& _guid);
	TChartOfCalculationTypes(v8catalog *_parent, const String& _guid, const String& _name);
	~TChartOfCalculationTypes();

	void initializeFromTree() override;
};

#endif

