//---------------------------------------------------------------------------

#ifndef SettingsStoragesH
#define SettingsStoragesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TSettingsStorages
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ С…СЂР°РЅРёР»РёС‰ РЅР°СЃС‚СЂРѕРµРє (md_SettingsStorages)
 *
 * РҐСЂР°РЅРёР»РёС‰Р° РЅР°СЃС‚СЂРѕРµРє - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РЅР°СЃС‚СЂРѕР№РєРё РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РїРѕР»СЊР·РѕРІР°С‚РµР»СЊСЃРєРёС… РїР°СЂР°РјРµС‚СЂРѕРІ Рё РЅР°СЃС‚СЂРѕРµРє.
 */
class TSettingsStorages : public BaseMetadataObject
{
private:
    String storageName;  // РРјСЏ С…СЂР°РЅРёР»РёС‰Р° РЅР°СЃС‚СЂРѕРµРє

public:
    TSettingsStorages();
    TSettingsStorages(v8catalog* _parent, const String& _guid);
    TSettingsStorages(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TSettingsStorages();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё С…СЂР°РЅРёР»РёС‰Р° РЅР°СЃС‚СЂРѕРµРє
    String GetStorageName();
    void SetStorageName(String _name);

    // Р РµР°Р»РёР·Р°С†РёСЏ РІРёСЂС‚СѓР°Р»СЊРЅС‹С… РјРµС‚РѕРґРѕРІ BaseMetadataObject
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void initializeFromTree() override;

private:
    // Р’РЅСѓС‚СЂРµРЅРЅРёРµ С…СЂР°РЅРёР»РёС‰Р° РґР»СЏ СЃРѕРІРјРµСЃС‚РёРјРѕСЃС‚Рё СЃ РёРЅС‚РµСЂС„РµР№СЃРѕРј
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif

