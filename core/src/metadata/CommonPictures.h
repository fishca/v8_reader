//---------------------------------------------------------------------------

#ifndef CommonPicturesH
#define CommonPicturesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonPictures
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РѕР±С‰РёС… РєР°СЂС‚РёРЅРѕРє (md_CommonPictures)
 *
 * РћР±С‰РёРµ РєР°СЂС‚РёРЅРєРё - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РєР°СЂС‚РёРЅРєРё, РґРѕСЃС‚СѓРїРЅС‹Рµ РІ СЂР°Р·Р»РёС‡РЅС‹С… С‡Р°СЃС‚СЏС… РєРѕРЅС„РёРіСѓСЂР°С†РёРё.
 */
class TCommonPictures : public BaseMetadataObject
{
private:
    // pictureName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TCommonPictures();
    TCommonPictures(v8catalog* _parent, const Utf16String& _guid);
    TCommonPictures(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TCommonPictures(v8catalog* _parent, const TStringLike& _guid)
        : TCommonPictures(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TCommonPictures(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TCommonPictures(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TCommonPictures();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё РѕР±С‰РµР№ РєР°СЂС‚РёРЅРєРё
    Utf16String GetPictureName() const;
    void SetPictureName(const Utf16String& _name);

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

