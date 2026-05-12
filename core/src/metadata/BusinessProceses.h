//---------------------------------------------------------------------------

#ifndef BusinessProcesesH
#define BusinessProcesesH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

class TBusinessProceses : public MetadataObjectWithSections
{
public:
	__fastcall TBusinessProceses();
	__fastcall TBusinessProceses(v8catalog *_parent, const String& _guid);
	__fastcall TBusinessProceses(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TBusinessProceses();

	void __fastcall initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif
