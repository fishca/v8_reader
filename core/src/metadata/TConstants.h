//---------------------------------------------------------------------------

#ifndef TConstantsH
#define TConstantsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TConstants
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РєРѕРЅСЃС‚Р°РЅС‚ (md_Constants)
 *
 * РљРѕРЅСЃС‚Р°РЅС‚С‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РїРѕСЃС‚РѕСЏРЅРЅС‹Рµ Р·РЅР°С‡РµРЅРёСЏ, РёСЃРїРѕР»СЊР·СѓРµРјС‹Рµ РІ СЂР°Р·Р»РёС‡РЅС‹С… С‡Р°СЃС‚СЏС… РєРѕРЅС„РёРіСѓСЂР°С†РёРё.
 */
class TConstants : public BaseMetadataObject
{
private:
    // constantsName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TConstants();
    TConstants(v8catalog* _parent, const String& _guid);
    TConstants(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TConstants();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РєРѕРЅСЃС‚Р°РЅС‚С‹
    String GetConstantsName();
    void SetConstantsName(String _name);

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
