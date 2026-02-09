//---------------------------------------------------------------------------

#ifndef JournalsH
#define JournalsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TJournals : public MetadataObjectWithSections
{
public:
	__fastcall TJournals();
	__fastcall TJournals(v8catalog *_parent, const String& _guid);
	__fastcall TJournals(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TJournals();

	void __fastcall initializeFromTree() override;
};

#endif
