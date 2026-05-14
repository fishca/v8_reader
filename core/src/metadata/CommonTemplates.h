//---------------------------------------------------------------------------

#ifndef CommonTemplatesH
#define CommonTemplatesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonTemplates
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РѕР±С‰РёС… РјР°РєРµС‚РѕРІ (md_CommonTemplates)
 *
 * РћР±С‰РёРµ РјР°РєРµС‚С‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РјР°РєРµС‚С‹, РґРѕСЃС‚СѓРїРЅС‹Рµ РІ СЂР°Р·Р»РёС‡РЅС‹С… С‡Р°СЃС‚СЏС… РєРѕРЅС„РёРіСѓСЂР°С†РёРё.
 */
class TCommonTemplates : public BaseMetadataObject
{
private:
    // templateName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TCommonTemplates();
    TCommonTemplates(v8catalog* _parent, const Utf16String& _guid);
    TCommonTemplates(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TCommonTemplates(v8catalog* _parent, const TStringLike& _guid)
        : TCommonTemplates(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TCommonTemplates(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TCommonTemplates(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TCommonTemplates();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РѕР±С‰РµРіРѕ РјР°РєРµС‚Р°
    Utf16String GetTemplateName() const;
    void SetTemplateName(const Utf16String& _name);

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
