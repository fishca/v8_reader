//---------------------------------------------------------------------------

#ifndef ExchangePlansH
#define ExchangePlansH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

/**
 * @class TExchangePlans
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РїР»Р°РЅРѕРІ РѕР±РјРµРЅР° (md_ExchangePlans)
 *
 * РџР»Р°РЅС‹ РѕР±РјРµРЅР° - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ РѕРїСЂРµРґРµР»СЏСЋС‚
 * РїСЂР°РІРёР»Р° РѕР±РјРµРЅР° РґР°РЅРЅС‹РјРё РјРµР¶РґСѓ РёРЅС„РѕСЂРјР°С†РёРѕРЅРЅС‹РјРё Р±Р°Р·Р°РјРё 1РЎ.
 */
class TExchangePlans : public MetadataObjectWithSections
{
public:
    TExchangePlans();
    TExchangePlans(v8catalog* _parent, const Utf16String& _guid);
    TExchangePlans(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TExchangePlans(v8catalog* _parent, const TStringLike& _guid)
        : TExchangePlans(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TExchangePlans(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TExchangePlans(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TExchangePlans();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РїР»Р°РЅР° РѕР±РјРµРЅР°
    Utf16String GetExchangePlanName() const;
    void SetExchangePlanName(const Utf16String& _name);

    void initializeFromTree() override;
};

#endif

