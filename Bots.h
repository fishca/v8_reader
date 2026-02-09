//---------------------------------------------------------------------------

#ifndef BotsH
#define BotsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TBots
 * @brief Класс для хранения ботов (md_Bots)
 *
 * Боты - это объекты метаданных, которые содержат
 * автоматизированные процедуры для взаимодействия с внешними системами.
 */
class TBots : public BaseMetadataObject
{
private:
    String botName;  // Имя бота

public:
    __fastcall TBots();
    __fastcall TBots(v8catalog* _parent, const String& _guid);
    __fastcall TBots(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TBots();

    // Методы для получения имени бота
    String __fastcall GetBotName();
    void __fastcall SetBotName(String _name);

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
