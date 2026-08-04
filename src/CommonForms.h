//---------------------------------------------------------------------------

#ifndef CommonFormsH
#define CommonFormsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

class TCommonForms : public EmptyMetadataObject<TCommonForms>
{
private:
	ModuleTextDocument textDocument;

public:
	__fastcall TCommonForms();
	__fastcall TCommonForms(v8catalog* _parent, const String& _guid);
	__fastcall TCommonForms(v8catalog* _parent, const String& _guid, const String& _name);

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

	void __fastcall LoadTextIfNeeded();
	void __fastcall RefreshEditableTextIfNeeded();
};

#endif
