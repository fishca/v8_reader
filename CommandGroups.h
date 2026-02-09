//---------------------------------------------------------------------------

#ifndef CommandGroupsH
#define CommandGroupsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommandGroups
 * @brief Класс для хранения групп команд (md_CommandGroups)
 *
 * Группы команд - это объекты метаданных, которые содержат
 * группы команд для организации интерфейса.
 */
class TCommandGroups : public BaseMetadataObject
{
private:
    // groupName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TCommandGroups();
    __fastcall TCommandGroups(v8catalog* _parent, const String& _guid);
    __fastcall TCommandGroups(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TCommandGroups();

    // Методы для получения имени группы команд
    String __fastcall GetCommandName();
    void __fastcall SetCommandName(String _name);

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
