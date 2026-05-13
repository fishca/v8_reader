//---------------------------------------------------------------------------

#ifndef MetadataObjectInformationRegisterH
#define MetadataObjectInformationRegisterH
//---------------------------------------------------------------------------

#include "BaseMetadataObject.h"
#include "Common.h"
#include <functional>

//---------------------------------------------------------------------------
// РљРѕРЅС„РёРіСѓСЂР°С†РёСЏ РїСѓС‚РµР№ РІ РґРµСЂРµРІРµ РїР°СЂСЃРёРЅРіР° РґР»СЏ СЂРµРіРёСЃС‚СЂРѕРІ СЃРІРµРґРµРЅРёР№
struct InfoRegisterTreePaths
{
    int attIdx;
    std::vector<int> attItemPath;
    int dimIdx;           // РёРЅРґРµРєСЃ РґР»СЏ РёР·РјРµСЂРµРЅРёР№
    std::vector<int> dimItemPath;
    int resIdx;           // РёРЅРґРµРєСЃ РґР»СЏ СЂРµСЃСѓСЂСЃРѕРІ
    std::vector<int> resItemPath;
    int formsIdx;
    int cmdIdx;
    std::vector<int> cmdItemPath;
    int moxIdx;
    std::function<String(v8catalog*, String&)> getFormNameFunc;
};

//---------------------------------------------------------------------------
// Р‘Р°Р·РѕРІС‹Р№ РєР»Р°СЃСЃ РґР»СЏ СЂРµРіРёСЃС‚СЂРѕРІ СЃРІРµРґРµРЅРёР№: СЂРµРєРІРёР·РёС‚С‹, РёР·РјРµСЂРµРЅРёСЏ, СЂРµСЃСѓСЂСЃС‹, С„РѕСЂРјС‹, РєРѕРјР°РЅРґС‹, РјР°РєРµС‚С‹
// РўР°Р±Р»РёС‡РЅС‹С… С‡Р°СЃС‚РµР№ РЅРµС‚
class MetadataObjectInformationRegister : public BaseMetadataObject
{
protected:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TRequisite>> dimensions;   // РёР·РјРµСЂРµРЅРёСЏ
    std::vector<std::unique_ptr<TRequisite>> resources;    // СЂРµСЃСѓСЂСЃС‹
    std::vector<std::unique_ptr<TComand>> comands;
    std::vector<std::unique_ptr<TMoxel>> moxels;
    std::vector<std::unique_ptr<TForm1C>> forms;
    std::vector<std::unique_ptr<TTabular>> tabulars;       // РїСѓСЃС‚РѕР№, РґР»СЏ СЃРѕРІРјРµСЃС‚РёРјРѕСЃС‚Рё СЃ BaseMetadataObject

    void initializeFromTreeWithPaths(const InfoRegisterTreePaths& paths);

public:
    MetadataObjectInformationRegister();
    MetadataObjectInformationRegister(v8catalog* _parent, const String& _guid);
    MetadataObjectInformationRegister(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~MetadataObjectInformationRegister();

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

    std::vector<std::unique_ptr<TRequisite>>& getDimensions() { return dimensions; }
    std::vector<std::unique_ptr<TRequisite>>& getResources() { return resources; }
};

//---------------------------------------------------------------------------
#endif

