//---------------------------------------------------------------------------

#ifndef MetadataObjectWithSectionsH
#define MetadataObjectWithSectionsH
//---------------------------------------------------------------------------

#include "BaseMetadataObject.h"
#include "Common.h"
#include <functional>

//---------------------------------------------------------------------------
// РљРѕРЅС„РёРіСѓСЂР°С†РёСЏ РїСѓС‚РµР№ РІ РґРµСЂРµРІРµ РїР°СЂСЃРёРЅРіР° РґР»СЏ СЂР°Р·РЅС‹С… С‚РёРїРѕРІ РјРµС‚Р°РґР°РЅРЅС‹С… 1РЎ
struct MetadataTreePaths
{
    int attIdx;           // РёРЅРґРµРєСЃ: root[0][attIdx][1] = РєРѕР»РёС‡РµСЃС‚РІРѕ СЂРµРєРІРёР·РёС‚РѕРІ
    std::vector<int> attItemPath;   // РїСѓС‚СЊ Рє РёРјРµРЅРё СЂРµРєРІРёР·РёС‚Р° РѕС‚ СѓР·Р»Р° СЌР»РµРјРµРЅС‚Р°
    int tabIdx;           // РёРЅРґРµРєСЃ РґР»СЏ С‚Р°Р±Р»РёС‡РЅС‹С… С‡Р°СЃС‚РµР№
    std::vector<int> tabItemPath;   // РїСѓС‚СЊ Рє РёРјРµРЅРё С‚Р°Р±Р»РёС‡РЅРѕР№ С‡Р°СЃС‚Рё
    int formsIdx;         // РёРЅРґРµРєСЃ: root[0][formsIdx][0] = СѓР·РµР» СЃРїРёСЃРєР° С„РѕСЂРј
    int cmdIdx;           // РёРЅРґРµРєСЃ: root[0][cmdIdx][1] = РєРѕР»РёС‡РµСЃС‚РІРѕ РєРѕРјР°РЅРґ
    std::vector<int> cmdItemPath;   // РїСѓС‚СЊ Рє РёРјРµРЅРё РєРѕРјР°РЅРґС‹ РѕС‚ СѓР·Р»Р° СЌР»РµРјРµРЅС‚Р°
    int moxIdx;           // РёРЅРґРµРєСЃ: root[0][moxIdx][0] = СѓР·РµР» СЃРїРёСЃРєР° РјР°РєРµС‚РѕРІ
    std::function<String(v8catalog*, String&)> getFormNameFunc;
    bool hasTabulars = true;  // Сѓ Р¶СѓСЂРЅР°Р»РѕРІ РЅРµС‚ С‚Р°Р±Р»РёС‡РЅС‹С… С‡Р°СЃС‚РµР№
};

//---------------------------------------------------------------------------
// Р‘Р°Р·РѕРІС‹Р№ РєР»Р°СЃСЃ РґР»СЏ РѕР±СЉРµРєС‚РѕРІ РјРµС‚Р°РґР°РЅРЅС‹С… СЃ СЂРµРєРІРёР·РёС‚Р°РјРё, РўР§, С„РѕСЂРјР°РјРё, РєРѕРјР°РЅРґР°РјРё Рё РјР°РєРµС‚Р°РјРё
class MetadataObjectWithSections : public BaseMetadataObject
{
protected:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> comands;
    std::vector<std::unique_ptr<TMoxel>> moxels;
    std::vector<std::unique_ptr<TTabular>> tabulars;
    std::vector<std::unique_ptr<TForm1C>> forms;
	ModuleTextDocument objectModuleDocument;
	ModuleTextDocument managerModuleDocument;

    void initializeFromTreeWithPaths(const MetadataTreePaths& paths);
	void RefreshModuleDocument(ModuleTextKind kind);
	ModuleTextDocument& GetModuleDocument(ModuleTextKind kind);

public:
    MetadataObjectWithSections();
    MetadataObjectWithSections(v8catalog* _parent, const String& _guid);
    MetadataObjectWithSections(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~MetadataObjectWithSections();

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	bool HasEditableModuleText() override;
	String GetEditableModuleText() override;
	void SetEditableModuleText(const String& value) override;
	bool SaveEditableModuleText(const String& value, String& errorText) override;
	ModuleTextLocation GetEditableModuleLocation() override;
	bool HasEditableModuleText(ModuleTextKind kind) override;
	String GetEditableModuleText(ModuleTextKind kind) override;
	void SetEditableModuleText(ModuleTextKind kind, const String& value) override;
	bool SaveEditableModuleText(ModuleTextKind kind, const String& value, String& errorText) override;
	ModuleTextLocation GetEditableModuleLocation(ModuleTextKind kind) override;
};

//---------------------------------------------------------------------------
#endif

