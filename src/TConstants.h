//---------------------------------------------------------------------------

#ifndef TConstantsH
#define TConstantsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TConstants
 * @brief Класс для хранения констант (md_Constants)
 *
 * Константы - это объекты метаданных, которые содержат
 * постоянные значения, используемые в различных частях конфигурации.
 */
class TConstants : public BaseMetadataObject
{
private:
    // constantsName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TConstants();
    __fastcall TConstants(v8catalog* _parent, const String& _guid);
    __fastcall TConstants(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TConstants();

    // Методы для получения имени константы
    String __fastcall GetConstantsName();
    void __fastcall SetConstantsName(String _name);

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