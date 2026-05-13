//---------------------------------------------------------------------------

#ifndef DataProcessorsH
#define DataProcessorsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TDataProcessors : public MetadataObjectWithSections
{
public:
	TDataProcessors();
	TDataProcessors(v8catalog *_parent, const String& _guid);
	TDataProcessors(v8catalog *_parent, const String& _guid, const String& _name);
	~TDataProcessors();

	void initializeFromTree() override;
};

#endif

