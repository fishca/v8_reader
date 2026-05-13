//---------------------------------------------------------------------------

#ifndef DefinedTypesH
#define DefinedTypesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TDefinedTypes
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РѕРїСЂРµРґРµР»СЏРµРјС‹С… С‚РёРїРѕРІ (md_DefinedTypes)
 *
 * РћРїСЂРµРґРµР»СЏРµРјС‹Рµ С‚РёРїС‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РїРѕР»СЊР·РѕРІР°С‚РµР»СЊСЃРєРёРµ С‚РёРїС‹ РґР°РЅРЅС‹С…, РёСЃРїРѕР»СЊР·СѓРµРјС‹Рµ РІ РєРѕРЅС„РёРіСѓСЂР°С†РёРё.
 */
class TDefinedTypes : public BaseMetadataObject
{
private:
    String typeName;  // РРјСЏ РѕРїСЂРµРґРµР»СЏРµРјРѕРіРѕ С‚РёРїР°

public:
    TDefinedTypes();
    TDefinedTypes(v8catalog* _parent, const String& _guid);
    TDefinedTypes(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TDefinedTypes();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РѕРїСЂРµРґРµР»СЏРµРјРѕРіРѕ С‚РёРїР°
    String GetTypeName();
    void SetTypeName(String _name);

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

