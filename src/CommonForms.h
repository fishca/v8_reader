//---------------------------------------------------------------------------

#ifndef CommonFormsH
#define CommonFormsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonForms
 * @brief Класс для хранения общих форм (md_CommonForms)
 *
 * Общие формы - это объекты метаданных, которые содержат
 * формы, доступные в различных частях конфигурации.
 */
class TCommonForms : public BaseMetadataObject
{
private:
    // formName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TCommonForms();
    __fastcall TCommonForms(v8catalog* _parent, const String& _guid);
    __fastcall TCommonForms(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TCommonForms();

    // Методы для получения имени общей формы
    String __fastcall GetFormName();
    void __fastcall SetFormName(String _name);

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
