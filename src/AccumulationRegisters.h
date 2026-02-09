//---------------------------------------------------------------------------

#ifndef AccumulationRegistersH
#define AccumulationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TAccumulationRegisters : public MetadataObjectInformationRegister
{
public:
	__fastcall TAccumulationRegisters();
	__fastcall TAccumulationRegisters(v8catalog *_parent, const String& _guid);
	__fastcall TAccumulationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TAccumulationRegisters();

	void __fastcall initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif
