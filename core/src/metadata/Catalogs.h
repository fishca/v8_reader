//---------------------------------------------------------------------------

#ifndef CatalogsH
#define CatalogsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TCatalogs : public MetadataObjectWithSections
{
public:
	TCatalogs();
	TCatalogs(v8catalog *_parent, const String& _guid);
	TCatalogs(v8catalog *_parent, const String& _guid, const String& _name);
	~TCatalogs();

	void initializeFromTree() override;
};

#endif

