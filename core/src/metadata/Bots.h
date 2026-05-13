//---------------------------------------------------------------------------

#ifndef BotsH
#define BotsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TBots
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ Р±РѕС‚РѕРІ (md_Bots)
 *
 * Р‘РѕС‚С‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * Р°РІС‚РѕРјР°С‚РёР·РёСЂРѕРІР°РЅРЅС‹Рµ РїСЂРѕС†РµРґСѓСЂС‹ РґР»СЏ РІР·Р°РёРјРѕРґРµР№СЃС‚РІРёСЏ СЃ РІРЅРµС€РЅРёРјРё СЃРёСЃС‚РµРјР°РјРё.
 */
class TBots : public BaseMetadataObject
{
private:
    String botName;  // РРјСЏ Р±РѕС‚Р°

public:
    TBots();
    TBots(v8catalog* _parent, const String& _guid);
    TBots(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TBots();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё Р±РѕС‚Р°
    String GetBotName();
    void SetBotName(String _name);

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

