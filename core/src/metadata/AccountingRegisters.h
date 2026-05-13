//---------------------------------------------------------------------------

#ifndef AccountingRegistersH
#define AccountingRegistersH

#include "MetadataObjectInformationRegister.h"
#include "Requisite.h"

//---------------------------------------------------------------------------

// Класс для регистров бухгалтерии
// Добавляет AccountingFlags и DimensionAccountingFlags к стандартным атрибутам
class TAccountingRegisters : public MetadataObjectInformationRegister
{
protected:
    std::vector<std::unique_ptr<TAccountingFlag>> accountingFlags;           // Признаки учета
    std::vector<std::unique_ptr<TDimensionAccountingFlag>> dimensionAccountingFlags;  // Признаки учета субконто

public:
    TAccountingRegisters();
    TAccountingRegisters(v8catalog *_parent, const String& _guid);
    TAccountingRegisters(v8catalog *_parent, const String& _guid, const String& _name);
    ~TAccountingRegisters();

    void initializeFromTree() override;

    // Геттеры для AccountingFlags
    std::vector<std::unique_ptr<TAccountingFlag>>& getAccountingFlags() { return accountingFlags; }
    std::vector<std::unique_ptr<TDimensionAccountingFlag>>& getDimensionAccountingFlags() { return dimensionAccountingFlags; }
};

//---------------------------------------------------------------------------
#endif

