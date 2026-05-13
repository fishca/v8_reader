//---------------------------------------------------------------------------

#ifndef TasksH
#define TasksH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

class TTasks : public MetadataObjectWithSections
{
public:
	TTasks();
	TTasks(v8catalog *_parent, const String& _guid);
	TTasks(v8catalog *_parent, const String& _guid, const String& _name);
	~TTasks();

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

