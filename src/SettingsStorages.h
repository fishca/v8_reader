//---------------------------------------------------------------------------

#ifndef SettingsStoragesH
#define SettingsStoragesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TSettingsStorages
 * @brief Класс для хранения хранилищ настроек (md_SettingsStorages)
 *
 * Хранилища настроек - это объекты метаданных, которые содержат
 * настройки для хранения пользовательских параметров и настроек.
 */
class TSettingsStorages : public EmptyMetadataObject<TSettingsStorages>
{
private:
    String storageName;  // Имя хранилища настроек

public:
    __fastcall TSettingsStorages();
    __fastcall TSettingsStorages(v8catalog* _parent, const String& _guid);
    __fastcall TSettingsStorages(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени хранилища настроек
    String __fastcall GetStorageName();
    void __fastcall SetStorageName(String _name);
};

#endif
