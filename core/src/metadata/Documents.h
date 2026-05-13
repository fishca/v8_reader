//---------------------------------------------------------------------------

#ifndef DocumentsH
#define DocumentsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TDocuments : public MetadataObjectWithSections
{
public:
	TDocuments();
	TDocuments(v8catalog *_parent, const String& _guid);
	TDocuments(v8catalog *_parent, const String& _guid, const String& _name);
	~TDocuments();

	void initializeFromTree() override;
};

#endif

