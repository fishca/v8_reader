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
public:
    TSettingsStorages();
    TSettingsStorages(v8catalog* _parent, const Utf16String& _guid);
    TSettingsStorages(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TSettingsStorages(v8catalog* _parent, const TStringLike& _guid)
        : TSettingsStorages(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TSettingsStorages(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TSettingsStorages(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TSettingsStorages();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё С…СЂР°РЅРёР»РёС‰Р° РЅР°СЃС‚СЂРѕРµРє
    Utf16String GetStorageName() const;
    void SetStorageName(const Utf16String& _name);

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

