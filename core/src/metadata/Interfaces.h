//---------------------------------------------------------------------------

#ifndef InterfacesH
#define InterfacesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TInterfaces
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РёРЅС‚РµСЂС„РµР№СЃРѕРІ (md_Interfaces)
 *
 * РРЅС‚РµСЂС„РµР№СЃС‹ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РёРЅС‚РµСЂС„РµР№СЃС‹ РєРѕРЅС„РёРіСѓСЂР°С†РёРё 1РЎ:РџСЂРµРґРїСЂРёСЏС‚РёРµ.
 */
class TInterfaces : public BaseMetadataObject
{
private:
    // interfaceName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TInterfaces();
    TInterfaces(v8catalog* _parent, const Utf16String& _guid);
    TInterfaces(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TInterfaces(v8catalog* _parent, const TStringLike& _guid)
        : TInterfaces(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TInterfaces(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TInterfaces(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TInterfaces();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РёРЅС‚РµСЂС„РµР№СЃР°
    Utf16String GetInterfaceName() const;
    void SetInterfaceName(const Utf16String& _name);

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

