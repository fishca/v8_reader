//---------------------------------------------------------------------------

#ifndef InformationRegistersH
#define InformationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TInformationRegisters : public MetadataObjectInformationRegister
{
public:
	__fastcall TInformationRegisters();
	__fastcall TInformationRegisters(v8catalog *_parent, const String& _guid);
	__fastcall TInformationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TInformationRegisters();

	void __fastcall initializeFromTree() override;
};

#endif
