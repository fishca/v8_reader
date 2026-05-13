//---------------------------------------------------------------------------

#ifndef CommonModulesH
#define CommonModulesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------
class TCommonModules : public BaseMetadataObject
{
private:
	ModuleTextDocument textDocument;
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> comands;
    std::vector<std::unique_ptr<TMoxel>> moxels;
    std::vector<std::unique_ptr<TTabular>> tabulars;
    std::vector<std::unique_ptr<TForm1C>> forms;
	void LoadTextIfNeeded();
	void RefreshEditableTextIfNeeded();

public:
	TCommonModules();
	TCommonModules(v8catalog* _parent, const String& _guid);
	TCommonModules(v8catalog* _parent, const String& _guid, const String& _name);
	virtual ~TCommonModules();
	String GetText();
	void SetText(String _text);
	ModuleTextDocument& GetTextDocument();
	bool SaveTextToSource(const String& newText, String& errorText);
	bool HasEditableModuleText() override;
	String GetEditableModuleText() override;
	void SetEditableModuleText(const String& value) override;
	bool SaveEditableModuleText(const String& value, String& errorText) override;
	ModuleTextLocation GetEditableModuleLocation() override;
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	void initializeFromTree() override;

};
#endif

