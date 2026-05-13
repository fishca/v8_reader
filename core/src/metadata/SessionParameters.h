//---------------------------------------------------------------------------

#ifndef SessionParametersH
#define SessionParametersH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TSessionParameters
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РїР°СЂР°РјРµС‚СЂРѕРІ СЃРµР°РЅСЃР° (md_SessionParameters)
 *
 * РџР°СЂР°РјРµС‚СЂС‹ СЃРµР°РЅСЃР° - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РїР°СЂР°РјРµС‚СЂС‹, РґРѕСЃС‚СѓРїРЅС‹Рµ РІ С‚РµРєСѓС‰РµРј СЃРµР°РЅСЃРµ СЂР°Р±РѕС‚С‹ СЃРёСЃС‚РµРјС‹.
 */
class TSessionParameters : public BaseMetadataObject
{
private:
    // parameterName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TSessionParameters();
    TSessionParameters(v8catalog* _parent, const String& _guid);
    TSessionParameters(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TSessionParameters();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РїР°СЂР°РјРµС‚СЂР° СЃРµР°РЅСЃР°
    String GetParameterName();
    void SetParameterName(String _name);

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

