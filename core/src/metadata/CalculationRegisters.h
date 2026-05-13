//---------------------------------------------------------------------------

#ifndef CalculationRegistersH
#define CalculationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TCalculationRegisters : public MetadataObjectInformationRegister
{
public:
	TCalculationRegisters();
	TCalculationRegisters(v8catalog *_parent, const String& _guid);
	TCalculationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	~TCalculationRegisters();

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

