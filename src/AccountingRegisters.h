//---------------------------------------------------------------------------

#ifndef AccountingRegistersH
#define AccountingRegistersH

#include "MetadataObjectInformationRegister.h"
#include "Requisite.h"

// Глобальная функция для CRTP-шаблона (не static)
InfoRegisterTreePaths GetAccountingRegistersPaths();

//---------------------------------------------------------------------------

// Класс для регистров бухгалтерии
// Добавляет AccountingFlags и DimensionAccountingFlags к стандартным атрибутам
class TAccountingRegisters : public MetadataObjectInformationRegisterT<TAccountingRegisters, GetAccountingRegistersPaths>
{
protected:
    std::vector<std::unique_ptr<TAccountingFlag>> accountingFlags;           // Признаки учета
    std::vector<std::unique_ptr<TDimensionAccountingFlag>> dimensionAccountingFlags;  // Признаки учета субконто

public:
    __fastcall TAccountingRegisters();
    __fastcall TAccountingRegisters(v8catalog *_parent, const String& _guid);
    __fastcall TAccountingRegisters(v8catalog *_parent, const String& _guid, const String& _name);
    __fastcall ~TAccountingRegisters();

    // Геттеры для AccountingFlags
    std::vector<std::unique_ptr<TAccountingFlag>>& getAccountingFlags() { return accountingFlags; }
    std::vector<std::unique_ptr<TDimensionAccountingFlag>>& getDimensionAccountingFlags() { return dimensionAccountingFlags; }
};

//---------------------------------------------------------------------------
#endif
