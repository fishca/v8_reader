#ifndef HTTPServicesH
#define HTTPServicesH

#include "BaseMetadataObject.h"

//---------------------------------------------------------------------------

/**
 * @class THTTPServices
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ HTTP-СЃРµСЂРІРёСЃРѕРІ (md_HTTPServices)
 *
 * HTTP-СЃРµСЂРІРёСЃС‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ РїСЂРµРґРѕСЃС‚Р°РІР»СЏСЋС‚
 * REST РёРЅС‚РµСЂС„РµР№СЃС‹ РґР»СЏ РёРЅС‚РµРіСЂР°С†РёРё СЃ РІРЅРµС€РЅРёРјРё СЃРёСЃС‚РµРјР°РјРё.
 */
class THTTPServices : public BaseMetadataObject
{
private:
    // data С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ root_data РёР· BaseMetadataObject

public:
    THTTPServices();
    THTTPServices(v8catalog* _parent, const Utf16String& _guid);
    THTTPServices(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    THTTPServices(v8catalog* _parent, const TStringLike& _guid)
        : THTTPServices(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    THTTPServices(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : THTTPServices(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~THTTPServices();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё HTTP-СЃРµСЂРІРёСЃР°
    Utf16String GetHTTPServicesName() const;
    void SetHTTPServicesName(const Utf16String& _name);

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

//---------------------------------------------------------------------------

#endif

