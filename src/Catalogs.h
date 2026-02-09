//---------------------------------------------------------------------------

#ifndef CatalogsH
#define CatalogsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TCatalogs : public MetadataObjectWithSections
{
public:
	__fastcall TCatalogs();
	__fastcall TCatalogs(v8catalog *_parent, const String& _guid);
	__fastcall TCatalogs(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TCatalogs();

	void __fastcall initializeFromTree() override;
};

#endif
