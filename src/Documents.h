//---------------------------------------------------------------------------

#ifndef DocumentsH
#define DocumentsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TDocuments : public MetadataObjectWithSections
{
public:
	__fastcall TDocuments();
	__fastcall TDocuments(v8catalog *_parent, const String& _guid);
	__fastcall TDocuments(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TDocuments();

	void __fastcall initializeFromTree() override;
};

#endif
