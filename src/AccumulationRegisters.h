//---------------------------------------------------------------------------

#ifndef AccumulationRegistersH
#define AccumulationRegistersH

#include "MetadataObjectInformationRegister.h"

// Глобальная функция для CRTP-шаблона (не static)
InfoRegisterTreePaths GetAccumulationRegistersPaths();

//---------------------------------------------------------------------------

class TAccumulationRegisters : public MetadataObjectInformationRegisterT<TAccumulationRegisters, GetAccumulationRegistersPaths>
{
public:
	__fastcall TAccumulationRegisters();
	__fastcall TAccumulationRegisters(v8catalog *_parent, const String& _guid);
	__fastcall TAccumulationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TAccumulationRegisters();
};

//---------------------------------------------------------------------------
#endif
