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
	TCommonModules(v8catalog* _parent, const Utf16String& _guid);
	TCommonModules(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TCommonModules(v8catalog* _parent, const TStringLike& _guid)
		: TCommonModules(_parent, V8Utf16FromString(_guid))
	{
	}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TCommonModules(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TCommonModules(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
	{
	}
	virtual ~TCommonModules();
	Utf16String GetText();
	void SetText(const Utf16String& _text);
	ModuleTextDocument& GetTextDocument();
	bool SaveTextToSource(const Utf16String& newText, Utf16String& errorText);
	bool HasEditableModuleText() override;
	Utf16String GetEditableModuleText() override;
	void SetEditableModuleText(const Utf16String& value) override;
	bool SaveEditableModuleText(const Utf16String& value, Utf16String& errorText) override;
	ModuleTextLocation GetEditableModuleLocation() override;
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	void initializeFromTree() override;

};
#endif

