//---------------------------------------------------------------------------

#ifndef ReportsH
#define ReportsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TReports : public MetadataObjectWithSections
{
public:
	TReports();
	TReports(v8catalog *_parent, const String& _guid);
	TReports(v8catalog *_parent, const String& _guid, const String& _name);
	~TReports();

	void initializeFromTree() override;
};

#endif

