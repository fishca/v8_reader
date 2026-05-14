//---------------------------------------------------------------------------

#ifndef FilterCriteriaH
#define FilterCriteriaH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFilterCriteria
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РєСЂРёС‚РµСЂРёРµРІ РѕС‚Р±РѕСЂР° (md_FilterCriteria)
 *
 * РљСЂРёС‚РµСЂРёРё РѕС‚Р±РѕСЂР° - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * СѓСЃР»РѕРІРёСЏ РґР»СЏ С„РёР»СЊС‚СЂР°С†РёРё РґР°РЅРЅС‹С… РІ Р·Р°РїСЂРѕСЃР°С… Рё РѕС‚С‡РµС‚Р°С….
 */
class TFilterCriteria : public BaseMetadataObject
{
private:
    // filterCriteriaName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TFilterCriteria();
    TFilterCriteria(v8catalog* _parent, const Utf16String& _guid);
    TFilterCriteria(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TFilterCriteria(v8catalog* _parent, const TStringLike& _guid)
        : TFilterCriteria(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TFilterCriteria(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TFilterCriteria(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TFilterCriteria();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РєСЂРёС‚РµСЂРёСЏ РѕС‚Р±РѕСЂР°
    Utf16String GetFilterCriteriaName() const;
    void SetFilterCriteriaName(const Utf16String& _name);

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

