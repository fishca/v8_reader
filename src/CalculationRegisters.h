//---------------------------------------------------------------------------

#ifndef CalculationRegistersH
#define CalculationRegistersH

#include "MetadataObjectInformationRegister.h"

// Глобальная функция для CRTP-шаблона (не static)
InfoRegisterTreePaths GetCalculationRegistersPaths();

//---------------------------------------------------------------------------

class TCalculationRegisters : public MetadataObjectInformationRegisterT<TCalculationRegisters, GetCalculationRegistersPaths>
{
public:
	__fastcall TCalculationRegisters();
	__fastcall TCalculationRegisters(v8catalog *_parent, const String& _guid);
	__fastcall TCalculationRegisters(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TCalculationRegisters();
};

//---------------------------------------------------------------------------
#endif
