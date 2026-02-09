//---------------------------------------------------------------------------

#ifndef ReportsH
#define ReportsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TReports : public MetadataObjectWithSections
{
public:
	__fastcall TReports();
	__fastcall TReports(v8catalog *_parent, const String& _guid);
	__fastcall TReports(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TReports();

	void __fastcall initializeFromTree() override;
};

#endif
