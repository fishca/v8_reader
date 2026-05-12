//---------------------------------------------------------------------------

#ifndef CommonCommandsH
#define CommonCommandsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonCommands
 * @brief Класс для хранения общих команд (md_CommonCommands)
 *
 * Общие команды - это объекты метаданных, которые содержат
 * команды, доступные в различных частях конфигурации.
 */
class TCommonCommands : public BaseMetadataObject
{
private:
    // commandName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TCommonCommands();
    __fastcall TCommonCommands(v8catalog* _parent, const String& _guid);
    __fastcall TCommonCommands(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TCommonCommands();

    // Методы для получения имени общей команды
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
