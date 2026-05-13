//---------------------------------------------------------------------------

#ifndef AccumulationRegistersH
#define AccumulationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TAccumulationRegisters : public MetadataObjectInformationRegister
{
public:
	TAccumulationRegisters();
	TAccumulationRegisters(v8catalog *_parent, const String& _guid);
	TAccumulationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	~TAccumulationRegisters();

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

