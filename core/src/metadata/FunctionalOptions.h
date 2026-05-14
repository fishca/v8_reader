//---------------------------------------------------------------------------

#ifndef FunctionalOptionsH
#define FunctionalOptionsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFunctionalOptions
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅС‹С… РѕРїС†РёР№ (md_FunctionalOptions)
 *
 * Р¤СѓРЅРєС†РёРѕРЅР°Р»СЊРЅС‹Рµ РѕРїС†РёРё - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РЅР°СЃС‚СЂРѕР№РєРё С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅРѕСЃС‚Рё СЃРёСЃС‚РµРјС‹.
 */
class TFunctionalOptions : public BaseMetadataObject
{
private:
    // name С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TFunctionalOptions();
    TFunctionalOptions(v8catalog* _parent, const Utf16String& _guid);
    TFunctionalOptions(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TFunctionalOptions(v8catalog* _parent, const TStringLike& _guid)
        : TFunctionalOptions(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TFunctionalOptions(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TFunctionalOptions(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TFunctionalOptions();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅРѕР№ РѕРїС†РёРё
    Utf16String GetOptionName() const;
    void SetOptionName(const Utf16String& _name);

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

