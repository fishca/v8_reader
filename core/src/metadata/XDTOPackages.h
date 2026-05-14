//---------------------------------------------------------------------------
#ifndef XDTOPackagesH
#define XDTOPackagesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TXDTOPackages
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ XDTO-РїР°РєРµС‚РѕРІ (md_XDTOPackages)
 *
 * XDTO-РїР°РєРµС‚С‹ РёСЃРїРѕР»СЊР·СѓСЋС‚СЃСЏ РґР»СЏ СЂР°Р±РѕС‚С‹ СЃ XDTO (XML Data Transfer Objects)
 */
class TXDTOPackages : public BaseMetadataObject
{
private:
    // data С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ root_data РёР· BaseMetadataObject

public:
    TXDTOPackages();
    TXDTOPackages(v8catalog* _parent, const Utf16String& _guid);
    TXDTOPackages(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TXDTOPackages(v8catalog* _parent, const TStringLike& _guid)
        : TXDTOPackages(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TXDTOPackages(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TXDTOPackages(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TXDTOPackages();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё XDTO-РїР°РєРµС‚Р°
    Utf16String GetXDTOPackageName() const;

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

