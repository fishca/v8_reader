//---------------------------------------------------------------------------

#ifndef RolesH
#define RolesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TRoles
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ СЂРѕР»РµР№ (md_Roles)
 *
 * Р РѕР»Рё - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РїСЂР°РІР° РґРѕСЃС‚СѓРїР° Рё РЅР°СЃС‚СЂРѕР№РєРё Р±РµР·РѕРїР°СЃРЅРѕСЃС‚Рё РґР»СЏ РїРѕР»СЊР·РѕРІР°С‚РµР»РµР№.
 */
class TRoles : public BaseMetadataObject
{
private:
    String roleName;  // РРјСЏ СЂРѕР»Рё

public:
    TRoles();
    TRoles(v8catalog* _parent, const String& _guid);
    TRoles(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TRoles();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё СЂРѕР»Рё
    String GetRoleName();
    void SetRoleName(String _name);

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

