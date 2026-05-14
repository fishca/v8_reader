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
	TCommonForms(v8catalog* _parent, const Utf16String& _guid);
	TCommonForms(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TCommonForms(v8catalog* _parent, const TStringLike& _guid)
		: TCommonForms(_parent, V8Utf16FromString(_guid))
	{}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TCommonForms(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TCommonForms(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
	{}
	virtual ~TCommonForms();

	Utf16String GetFormName();
	void SetFormName(const Utf16String& _name);
	Utf16String GetText();
	void SetText(const Utf16String& _text);
	ModuleTextDocument& GetTextDocument();
	bool SaveTextToSource(const Utf16String& newText, Utf16String& errorText);
	bool HasEditableModuleText() override;
	Utf16String GetEditableModuleText() override;
	void SetEditableModuleText(const Utf16String& value) override;
	bool SaveEditableModuleText(const Utf16String& value, Utf16String& errorText) override;
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

