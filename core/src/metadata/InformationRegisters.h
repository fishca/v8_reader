//---------------------------------------------------------------------------

#ifndef InformationRegistersH
#define InformationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TInformationRegisters : public MetadataObjectInformationRegister
{
public:
	TInformationRegisters();
	TInformationRegisters(v8catalog *_parent, const String& _guid);
	TInformationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	~TInformationRegisters();

	void initializeFromTree() override;
};

#endif

