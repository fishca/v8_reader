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
private:
    String exchangePlanName;  // РРјСЏ РїР»Р°РЅР° РѕР±РјРµРЅР°

public:
    TExchangePlans();
    TExchangePlans(v8catalog* _parent, const String& _guid);
    TExchangePlans(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TExchangePlans();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РїР»Р°РЅР° РѕР±РјРµРЅР°
    String GetExchangePlanName();
    void SetExchangePlanName(String _name);

    void initializeFromTree() override;
};

#endif

