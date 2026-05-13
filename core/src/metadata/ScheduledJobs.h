//---------------------------------------------------------------------------

#ifndef ScheduledJobsH
#define ScheduledJobsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TScheduledJobs
 * @brief РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ СЂРµРіР»Р°РјРµРЅС‚РЅС‹С… Р·Р°РґР°РЅРёР№ (md_ScheduledJobs)
 *
 * Р РµРіР»Р°РјРµРЅС‚РЅС‹Рµ Р·Р°РґР°РЅРёСЏ - СЌС‚Рѕ РѕР±СЉРµРєС‚С‹ РјРµС‚Р°РґР°РЅРЅС‹С…, РєРѕС‚РѕСЂС‹Рµ СЃРѕРґРµСЂР¶Р°С‚
 * РЅР°СЃС‚СЂРѕР№РєРё Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРѕРіРѕ РІС‹РїРѕР»РЅРµРЅРёСЏ Р·Р°РґР°С‡ РїРѕ СЂР°СЃРїРёСЃР°РЅРёСЋ.
 */
class TScheduledJobs : public BaseMetadataObject
{
private:
    // scheduledJobsName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
    TScheduledJobs();
    TScheduledJobs(v8catalog* _parent, const String& _guid);
    TScheduledJobs(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TScheduledJobs();

    // РњРµС‚РѕРґС‹ РґР»СЏ РїРѕР»СѓС‡РµРЅРёСЏ РёРјРµРЅРё СЂРµРіР»Р°РјРµРЅС‚РЅРѕРіРѕ Р·Р°РґР°РЅРёСЏ
    String GetScheduledJobsName();
    void SetScheduledJobsName(String _name);

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

