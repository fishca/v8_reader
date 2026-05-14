//---------------------------------------------------------------------------

#ifndef CommonAttributesH
#define CommonAttributesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonAttributes
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РѕР±С‰РёС… СЂРµРєРІРёР·РёС‚РѕРІ (md_CommonAttributes)
 *
 * РћР±С‰РёРµ СЂРµРєРІРёР·РёС‚С‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * СЂРµРєРІРёР·РёС‚С‹, РґРѕСЃС‚СѓРїРЅС‹Рµ РґР»СЏ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёСЏ РІ СЂР°Р·Р»РёС‡РЅС‹С… СЌР»РµРјРµРЅС‚Р°С… РєРѕРЅС„РёРіСѓСЂР°С†РёРё.
 */
class TCommonAttributes : public BaseMetadataObject
{
private:
    // attributeName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TCommonAttributes();
    TCommonAttributes(v8catalog* _parent, const Utf16String& _guid);
    TCommonAttributes(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TCommonAttributes(v8catalog* _parent, const TStringLike& _guid)
        : TCommonAttributes(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TCommonAttributes(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TCommonAttributes(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TCommonAttributes();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РѕР±С‰РµРіРѕ СЂРµРєРІРёР·РёС‚Р°
    Utf16String GetAttributeName() const;
    void SetAttributeName(const Utf16String& _name);

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

