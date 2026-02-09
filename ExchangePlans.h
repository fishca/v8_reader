//---------------------------------------------------------------------------

#ifndef ExchangePlansH
#define ExchangePlansH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TExchangePlans
 * @brief Класс для хранения планов обмена (md_ExchangePlans)
 *
 * Планы обмена - это объекты метаданных, которые определяют
 * правила обмена данными между информационными базами 1С.
 */
class TExchangePlans : public BaseMetadataObject
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

    // Реализация виртуальных методов BaseMetadataObject
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void __fastcall initializeFromTree() override;

private:
    // Внутренние хранилища для совместимости с интерфейсом
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif
