//---------------------------------------------------------------------------

#ifndef CommonFormsH
#define CommonFormsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TCommonForms : public BaseMetadataObject
{
private:
	ModuleTextDocument textDocument;

public:
	TCommonForms();
	TCommonForms(v8catalog* _parent, const String& _guid);
	TCommonForms(v8catalog* _parent, const String& _guid, const String& _name);
	virtual ~TCommonForms();

	String GetFormName();
	void SetFormName(String _name);
	String GetText();
	void SetText(String _text);
	ModuleTextDocument& GetTextDocument();
	bool SaveTextToSource(const String& newText, String& errorText);
	bool HasEditableModuleText() override;
	String GetEditableModuleText() override;
	void SetEditableModuleText(const String& value) override;
	bool SaveEditableModuleText(const String& value, String& errorText) override;
	ModuleTextLocation GetEditableModuleLocation() override;

	std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
	std::vector<std::unique_ptr<TComand>>& getCommands() override;
	std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
	std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
	std::vector<std::unique_ptr<TForm1C>>& getForms() override;

	void initializeFromTree() override;

private:
	std::vector<std::unique_ptr<TRequisite>> attributes;
	std::vector<std::unique_ptr<TComand>> commands;
	std::vector<std::unique_ptr<TMoxel>> layouts;
	std::vector<std::unique_ptr<TTabular>> tabularSections;
	std::vector<std::unique_ptr<TForm1C>> forms;
	void LoadTextIfNeeded();
	void RefreshEditableTextIfNeeded();
};

#endif

