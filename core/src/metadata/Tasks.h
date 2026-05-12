//---------------------------------------------------------------------------

#ifndef TasksH
#define TasksH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

class TTasks : public MetadataObjectWithSections
{
public:
	__fastcall TTasks();
	__fastcall TTasks(v8catalog *_parent, const String& _guid);
	__fastcall TTasks(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TTasks();

	void __fastcall initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif
