//---------------------------------------------------------------------------

#ifndef ChartOfCalculationTypesH
#define ChartOfCalculationTypesH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TChartOfCalculationTypes : public MetadataObjectWithSections
{
public:
	TChartOfCalculationTypes();
	TChartOfCalculationTypes(v8catalog *_parent, const Utf16String& _guid);
	TChartOfCalculationTypes(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TChartOfCalculationTypes(v8catalog *_parent, const TStringLike& _guid)
		: TChartOfCalculationTypes(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TChartOfCalculationTypes(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TChartOfCalculationTypes(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TChartOfCalculationTypes();

	void initializeFromTree() override;
};

#endif

