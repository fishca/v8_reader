//---------------------------------------------------------------------------

#ifndef JournalsH
#define JournalsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TJournals : public MetadataObjectWithSections
{
public:
	TJournals();
	TJournals(v8catalog *_parent, const String& _guid);
	TJournals(v8catalog *_parent, const String& _guid, const String& _name);
	~TJournals();

	void initializeFromTree() override;
};

#endif

