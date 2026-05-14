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
    TAccountingRegisters(v8catalog *_parent, const Utf16String& _guid);
    TAccountingRegisters(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TAccountingRegisters(v8catalog *_parent, const TStringLike& _guid)
        : TAccountingRegisters(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TAccountingRegisters(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TAccountingRegisters(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    ~TAccountingRegisters();

    void initializeFromTree() override;

    // Геттеры для AccountingFlags
    std::vector<std::unique_ptr<TAccountingFlag>>& getAccountingFlags() { return accountingFlags; }
    std::vector<std::unique_ptr<TDimensionAccountingFlag>>& getDimensionAccountingFlags() { return dimensionAccountingFlags; }
};

//---------------------------------------------------------------------------
#endif

