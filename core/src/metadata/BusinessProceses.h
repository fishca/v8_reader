//---------------------------------------------------------------------------

#ifndef BusinessProcesesH
#define BusinessProcesesH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

class TBusinessProceses : public MetadataObjectWithSections
{
public:
	TBusinessProceses();
	TBusinessProceses(v8catalog *_parent, const String& _guid);
	TBusinessProceses(v8catalog *_parent, const String& _guid, const String& _name);
	~TBusinessProceses();

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

