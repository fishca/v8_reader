//---------------------------------------------------------------------------

#ifndef FunctionalOptionsParametersH
#define FunctionalOptionsParametersH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFunctionalOptionsParameters
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РїР°СЂР°РјРµС‚СЂРѕРІ С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅС‹С… РѕРїС†РёР№ (md_FunctionalOptionsParameters)
 *
 * РџР°СЂР°РјРµС‚СЂС‹ С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅС‹С… РѕРїС†РёР№ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РїР°СЂР°РјРµС‚СЂС‹, РґРѕСЃС‚СѓРїРЅС‹Рµ РґР»СЏ С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅС‹С… РѕРїС†РёР№ СЃРёСЃС‚РµРјС‹.
 */
class TFunctionalOptionsParameters : public BaseMetadataObject
{
private:
    // name С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TFunctionalOptionsParameters();
    TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid);
    TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TFunctionalOptionsParameters();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РїР°СЂР°РјРµС‚СЂР° С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅРѕР№ РѕРїС†РёРё
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

