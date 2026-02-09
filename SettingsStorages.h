//---------------------------------------------------------------------------

#ifndef SettingsStoragesH
#define SettingsStoragesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TSettingsStorages
 * @brief Класс для хранения хранилищ настроек (md_SettingsStorages)
 *
 * Хранилища настроек - это объекты метаданных, которые содержат
 * настройки для хранения пользовательских параметров и настроек.
 */
class TSettingsStorages : public BaseMetadataObject
{
private:
    String storageName;  // Имя хранилища настроек

public:
    __fastcall TSettingsStorages();
    __fastcall TSettingsStorages(v8catalog* _parent, const String& _guid);
    __fastcall TSettingsStorages(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TSettingsStorages();

    // Методы для получения имени хранилища настроек
    String __fastcall GetStorageName();
    void __fastcall SetStorageName(String _name);

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
