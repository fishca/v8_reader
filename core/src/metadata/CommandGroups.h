//---------------------------------------------------------------------------

#ifndef CommandGroupsH
#define CommandGroupsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommandGroups
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РіСЂСѓРїРї РєРѕРјР°РЅРґ (md_CommandGroups)
 *
 * Р“СЂСѓРїРїС‹ РєРѕРјР°РЅРґ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РіСЂСѓРїРїС‹ РєРѕРјР°РЅРґ РґР»СЏ РѕСЂРіР°РЅРёР·Р°С†РёРё РёРЅС‚РµСЂС„РµР№СЃР°.
 */
class TCommandGroups : public BaseMetadataObject
{
private:
    // groupName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TCommandGroups();
    TCommandGroups(v8catalog* _parent, const String& _guid);
    TCommandGroups(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TCommandGroups();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РіСЂСѓРїРїС‹ РєРѕРјР°РЅРґ
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

