//---------------------------------------------------------------------------

#ifndef SubsystemH
#define SubsystemH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

class TSubsystem : public EmptyMetadataObject<TSubsystem>
{
private:
	// subsystemName хранится в унаследованном поле name из BaseMetadataObject

public:
	__fastcall TSubsystem();
	__fastcall TSubsystem(v8catalog* _parent, const String& _guid);
	__fastcall TSubsystem(v8catalog* _parent, const String& _guid, const String& _name);

	String __fastcall GetSubsystemName();
	void __fastcall SetSubsystemName(String _name);
};

#endif
