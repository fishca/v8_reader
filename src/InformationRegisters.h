//---------------------------------------------------------------------------

#ifndef InformationRegistersH
#define InformationRegistersH

#include "MetadataObjectInformationRegister.h"

// Глобальная функция для CRTP-шаблона (не static)
InfoRegisterTreePaths GetInformationRegistersPaths();

//---------------------------------------------------------------------------

class TInformationRegisters : public MetadataObjectInformationRegisterT<TInformationRegisters, GetInformationRegistersPaths>
{
public:
	__fastcall TInformationRegisters();
	__fastcall TInformationRegisters(v8catalog *_parent, const String& _guid);
	__fastcall TInformationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TInformationRegisters();
};

#endif
