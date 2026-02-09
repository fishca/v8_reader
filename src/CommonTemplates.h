//---------------------------------------------------------------------------

#ifndef CommonTemplatesH
#define CommonTemplatesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonTemplates
 * @brief Класс для хранения общих макетов (md_CommonTemplates)
 *
 * Общие макеты - это объекты метаданных, которые содержат
 * макеты, доступные в различных частях конфигурации.
 */
class TCommonTemplates : public BaseMetadataObject
{
private:
    // templateName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TCommonTemplates();
    __fastcall TCommonTemplates(v8catalog* _parent, const String& _guid);
    __fastcall TCommonTemplates(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TCommonTemplates();

    // Методы для получения имени общего макета
    String __fastcall GetTemplateName();
    void __fastcall SetTemplateName(String _name);

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