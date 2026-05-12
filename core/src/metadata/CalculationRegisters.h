//---------------------------------------------------------------------------

#ifndef CalculationRegistersH
#define CalculationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TCalculationRegisters : public MetadataObjectInformationRegister
{
public:
	__fastcall TCalculationRegisters();
	__fastcall TCalculationRegisters(v8catalog *_parent, const String& _guid);
	__fastcall TCalculationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TCalculationRegisters();

	void __fastcall initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif
