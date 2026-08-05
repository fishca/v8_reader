//---------------------------------------------------------------------------

#ifndef WSReferencesH
#define WSReferencesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

class TWSReferences : public EmptyMetadataObject<TWSReferences>
{
private:
	String referenceName;

public:
	__fastcall TWSReferences();
	__fastcall TWSReferences(v8catalog* _parent, const String& _guid);
	__fastcall TWSReferences(v8catalog* _parent, const String& _guid, const String& _name);

	String __fastcall GetReferenceName();
	void __fastcall SetReferenceName(String _name);
};

#endif
