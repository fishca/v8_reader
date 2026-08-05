//---------------------------------------------------------------------------

#ifndef ExchangePlansH
#define ExchangePlansH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetExchangePlansPaths();

//---------------------------------------------------------------------------

/**
 * @class TExchangePlans
 * @brief Класс для хранения планов обмена (md_ExchangePlans)
 *
 * Планы обмена - это объекты метаданных, которые определяют
 * правила обмена данными между информационными базами 1С.
 */
class TExchangePlans : public MetadataObjectWithSectionsT<TExchangePlans, GetExchangePlansPaths>
{
private:
    String exchangePlanName;  // Имя плана обмена

public:
    __fastcall TExchangePlans();
    __fastcall TExchangePlans(v8catalog* _parent, const String& _guid);
    __fastcall TExchangePlans(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TExchangePlans();

    // Методы для получения имени плана обмена
    String __fastcall GetExchangePlanName();
    void __fastcall SetExchangePlanName(String _name);

    void __fastcall initializeFromTree() override;
};

#endif
