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
	__fastcall TCommonForms();
	__fastcall TCommonForms(v8catalog* _parent, const String& _guid);
	__fastcall TCommonForms(v8catalog* _parent, const String& _guid, const String& _name);
	virtual __fastcall ~TCommonForms();

	String __fastcall GetFormName();
	void __fastcall SetFormName(String _name);
	String __fastcall GetText();
	void __fastcall SetText(String _text);
	ModuleTextDocument& __fastcall GetTextDocument();
	bool __fastcall SaveTextToSource(const String& newText, String& errorText);
	bool __fastcall HasEditableModuleText() override;
	String __fastcall GetEditableModuleText() override;
	void __fastcall SetEditableModuleText(const String& value) override;
	bool __fastcall SaveEditableModuleText(const String& value, String& errorText) override;
	ModuleTextLocation __fastcall GetEditableModuleLocation() override;

	std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
	std::vector<std::unique_ptr<TComand>>& getCommands() override;
	std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
	std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
	std::vector<std::unique_ptr<TForm1C>>& getForms() override;

	void __fastcall initializeFromTree() override;

private:
	std::vector<std::unique_ptr<TRequisite>> attributes;
	std::vector<std::unique_ptr<TComand>> commands;
	std::vector<std::unique_ptr<TMoxel>> layouts;
	std::vector<std::unique_ptr<TTabular>> tabularSections;
	std::vector<std::unique_ptr<TForm1C>> forms;
	void __fastcall LoadTextIfNeeded();
	void __fastcall RefreshEditableTextIfNeeded();
};

#endif
