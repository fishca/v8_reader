//---------------------------------------------------------------------------

#ifndef CommonCommandsH
#define CommonCommandsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonCommands
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РѕР±С‰РёС… РєРѕРјР°РЅРґ (md_CommonCommands)
 *
 * РћР±С‰РёРµ РєРѕРјР°РЅРґС‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РєРѕРјР°РЅРґС‹, РґРѕСЃС‚СѓРїРЅС‹Рµ РІ СЂР°Р·Р»РёС‡РЅС‹С… С‡Р°СЃС‚СЏС… РєРѕРЅС„РёРіСѓСЂР°С†РёРё.
 */
class TCommonCommands : public BaseMetadataObject
{
private:
    // commandName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TCommonCommands();
    TCommonCommands(v8catalog* _parent, const String& _guid);
    TCommonCommands(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TCommonCommands();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РѕР±С‰РµР№ РєРѕРјР°РЅРґС‹
    String GetCommandName();
    void SetCommandName(String _name);

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

