//---------------------------------------------------------------------------

#ifndef DataProcessorsH
#define DataProcessorsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TDataProcessors : public MetadataObjectWithSections
{
public:
	__fastcall TDataProcessors();
	__fastcall TDataProcessors(v8catalog *_parent, const String& _guid);
	__fastcall TDataProcessors(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TDataProcessors();

	void __fastcall initializeFromTree() override;
};

#endif
