//---------------------------------------------------------------------------

#ifndef SynHighlighter1CH
#define SynHighlighter1CH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditHighlighter.hpp"

enum Ttk1CTokenKind
{
	tk1CComment,
	tk1CDirective,
	tk1CIdentifier,
	tk1CKeyword,
	tk1CNull,
	tk1CNumber,
	tk1CSpace,
	tk1CString,
	tk1CSymbol,
	tk1CAnnotation,
	tk1CUnknown
};

class TSyn1CSyn : public TSynCustomHighlighter
{
private:
	Ttk1CTokenKind FTokenID;
	TSynHighlighterAttributes* FCommentAttri;
	TSynHighlighterAttributes* FDirectiveAttri;
	TSynHighlighterAttributes* FIdentifierAttri;
	TSynHighlighterAttributes* FKeyAttri;
	TSynHighlighterAttributes* FNumberAttri;
	TSynHighlighterAttributes* FSpaceAttri;
	TSynHighlighterAttributes* FStringAttri;
	TSynHighlighterAttributes* FSymbolAttri;
	TSynHighlighterAttributes* FAnnotationAttri;
	TStringList* FKeywords;
	TStringList* FEnglishKeywords;
	TStringList* FAnnotations;

	bool __fastcall IsIdentifierChar(WideChar ch) const;
	bool __fastcall IsKeywordToken(const String& token) const;
	bool __fastcall IsAnnotationToken(const String& token) const;
	void __fastcall LoadRussianKeywords();
	void __fastcall LoadEnglishKeywordPlaceholders();
	void __fastcall LoadAnnotations();
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall CommentProc();
	void __fastcall StringProc();
	void __fastcall NumberProc();
	void __fastcall DirectiveProc();
	void __fastcall AnnotationProc();
	void __fastcall IdentifierProc();
	void __fastcall SymbolProc();

protected:
	virtual TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual String __fastcall GetSampleSource();

public:
	__fastcall virtual TSyn1CSyn(TComponent* AOwner);
	__fastcall virtual ~TSyn1CSyn();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	virtual bool __fastcall GetEol();
	virtual String __fastcall GetToken();
	virtual TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual int __fastcall GetTokenPos();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual bool __fastcall IsKeyword(const String AKeyword);
	virtual void __fastcall Next();
	virtual void __fastcall SetLine(const String Value, int LineNumber);
	virtual String __fastcall GetKeyWords(int TokenKind);

	__property TSynHighlighterAttributes* CommentAttri = {read=FCommentAttri};
	__property TSynHighlighterAttributes* DirectiveAttri = {read=FDirectiveAttri};
	__property TSynHighlighterAttributes* IdentifierAttri = {read=FIdentifierAttri};
	__property TSynHighlighterAttributes* KeyAttri = {read=FKeyAttri};
	__property TSynHighlighterAttributes* NumberAttri = {read=FNumberAttri};
	__property TSynHighlighterAttributes* SpaceAttri = {read=FSpaceAttri};
	__property TSynHighlighterAttributes* StringAttri = {read=FStringAttri};
	__property TSynHighlighterAttributes* SymbolAttri = {read=FSymbolAttri};
	__property TSynHighlighterAttributes* AnnotationAttri = {read=FAnnotationAttri};
};

//---------------------------------------------------------------------------
#endif
