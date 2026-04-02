//---------------------------------------------------------------------------

#ifndef CommonModulesH
#define CommonModulesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------
class TCommonModules : public BaseMetadataObject
{
private:
	String text;
	bool textLoaded;
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> comands;
    std::vector<std::unique_ptr<TMoxel>> moxels;
    std::vector<std::unique_ptr<TTabular>> tabulars;
    std::vector<std::unique_ptr<TForm1C>> forms;
	void __fastcall LoadTextIfNeeded();

public:
	__fastcall TCommonModules();
	__fastcall TCommonModules(v8catalog* _parent, const String& _guid);
	__fastcall TCommonModules(v8catalog* _parent, const String& _guid, const String& _name);
	virtual __fastcall ~TCommonModules();
	String __fastcall GetText();
	void __fastcall SetText(String _text);
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	void __fastcall initializeFromTree() override;

};
#endif
