//---------------------------------------------------------------------------

#ifndef ChartOfCalculationTypesH
#define ChartOfCalculationTypesH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetChartOfCalculationTypesPaths();

//---------------------------------------------------------------------------

class TChartOfCalculationTypes : public MetadataObjectWithSectionsT<TChartOfCalculationTypes, GetChartOfCalculationTypesPaths>
{
public:
	__fastcall TChartOfCalculationTypes();
	__fastcall TChartOfCalculationTypes(v8catalog *_parent, const String& _guid);
	__fastcall TChartOfCalculationTypes(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TChartOfCalculationTypes();
};

#endif
