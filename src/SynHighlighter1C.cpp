//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SynHighlighter1C.h"

//---------------------------------------------------------------------------

__fastcall TSyn1CSyn::TSyn1CSyn(TComponent* AOwner) : TSynCustomHighlighter(AOwner)
{
	FCaseSensitive = false;
	FKeywords = new TStringList();
	FKeywords->Sorted = true;
	FKeywords->Duplicates = System::Classes::dupIgnore;
	FEnglishKeywords = new TStringList();
	FEnglishKeywords->Sorted = true;
	FEnglishKeywords->Duplicates = System::Classes::dupIgnore;
	FAnnotations = new TStringList();
	FAnnotations->Sorted = true;
	FAnnotations->Duplicates = System::Classes::dupIgnore;

	FCommentAttri = new TSynHighlighterAttributes(L"Comment", L"Comment");
	FDirectiveAttri = new TSynHighlighterAttributes(L"Directive", L"Directive");
	FIdentifierAttri = new TSynHighlighterAttributes(L"Identifier", L"Identifier");
	FKeyAttri = new TSynHighlighterAttributes(L"Key", L"Key");
	FNumberAttri = new TSynHighlighterAttributes(L"Number", L"Number");
	FSpaceAttri = new TSynHighlighterAttributes(L"Space", L"Space");
	FStringAttri = new TSynHighlighterAttributes(L"String", L"String");
	FSymbolAttri = new TSynHighlighterAttributes(L"Symbol", L"Symbol");
	FAnnotationAttri = new TSynHighlighterAttributes(L"Annotation", L"Annotation");

	FCommentAttri->Foreground = clGreen;
	FCommentAttri->Style = TFontStyles() << fsItalic;
	FDirectiveAttri->Foreground = clTeal;
	FIdentifierAttri->Foreground = clWindowText;
	FKeyAttri->Foreground = clNavy;
	FKeyAttri->Style = TFontStyles() << fsBold;
	FNumberAttri->Foreground = clPurple;
	FSpaceAttri->Foreground = clWindowText;
	FStringAttri->Foreground = clMaroon;
	FSymbolAttri->Foreground = clGrayText;
	FAnnotationAttri->Foreground = clOlive;

	AddAttribute(FCommentAttri);
	AddAttribute(FDirectiveAttri);
	AddAttribute(FIdentifierAttri);
	AddAttribute(FKeyAttri);
	AddAttribute(FNumberAttri);
	AddAttribute(FSpaceAttri);
	AddAttribute(FStringAttri);
	AddAttribute(FSymbolAttri);
	AddAttribute(FAnnotationAttri);

	LoadRussianKeywords();
	LoadEnglishKeywordPlaceholders();
	LoadAnnotations();
	SetAttributesOnChange(DefHighlightChange);
}

__fastcall TSyn1CSyn::~TSyn1CSyn()
{
	delete FKeywords;
	delete FEnglishKeywords;
	delete FAnnotations;
}

String __fastcall TSyn1CSyn::GetLanguageName()
{
	return L"1C";
}

String __fastcall TSyn1CSyn::GetFriendlyLanguageName()
{
	return L"1C:Enterprise";
}

void __fastcall TSyn1CSyn::LoadRussianKeywords()
{
	const wchar_t* keywords[] = {
		L"\u0430", L"\u0432", L"\u0432\u043E\u0437\u0432\u0440\u0430\u0442",
		L"\u0432\u044B\u0437\u0432\u0430\u0442\u044C\u0438\u0441\u043A\u043B\u044E\u0447\u0435\u043D\u0438\u0435",
		L"\u0432\u044B\u043F\u043E\u043B\u043D\u0438\u0442\u044C",
		L"\u0434\u043B\u044F", L"\u0434\u043E", L"\u0435\u0441\u043B\u0438", L"\u0438", L"\u0438\u043B\u0438",
		L"\u0438\u043D\u0430\u0447\u0435", L"\u0438\u043D\u0430\u0447\u0435\u0435\u0441\u043B\u0438",
		L"\u0438\u0441\u043A\u043B\u044E\u0447\u0435\u043D\u0438\u0435", L"\u0438\u0441\u0442\u0438\u043D\u0430",
		L"\u043A\u0430\u0436\u0434\u043E\u0433\u043E", L"\u043A\u043E\u043D\u0435\u0446\u0435\u0441\u043B\u0438",
		L"\u043A\u043E\u043D\u0435\u0446\u043F\u043E\u043F\u044B\u0442\u043A\u0438",
		L"\u043A\u043E\u043D\u0435\u0446\u043F\u0440\u043E\u0446\u0435\u0434\u0443\u0440\u044B",
		L"\u043A\u043E\u043D\u0435\u0446\u0444\u0443\u043D\u043A\u0446\u0438\u0438",
		L"\u043A\u043E\u043D\u0435\u0446\u0446\u0438\u043A\u043B\u0430", L"\u043B\u043E\u0436\u044C",
		L"\u043D\u0435", L"\u043D\u0435\u043E\u043F\u0440\u0435\u0434\u0435\u043B\u0435\u043D\u043E",
		L"\u043D\u043E\u0432\u044B\u0439", L"\u043F\u0435\u0440\u0435\u0439\u0442\u0438", L"\u043F\u0435\u0440\u0435\u043C",
		L"\u043F\u043E", L"\u043F\u043E\u043A\u0430", L"\u043F\u043E\u043F\u044B\u0442\u043A\u0430",
		L"\u043F\u0440\u0435\u0440\u0432\u0430\u0442\u044C", L"\u043F\u0440\u043E\u0434\u043E\u043B\u0436\u0438\u0442\u044C",
		L"\u043F\u0440\u043E\u0446\u0435\u0434\u0443\u0440\u0430", L"\u0442\u043E\u0433\u0434\u0430",
		L"\u0444\u0443\u043D\u043A\u0446\u0438\u044F", L"\u0446\u0438\u043A\u043B", L"\u044D\u043A\u0441\u043F\u043E\u0440\u0442"
	};

	for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i)
		FKeywords->Add(keywords[i]);
}

void __fastcall TSyn1CSyn::LoadEnglishKeywordPlaceholders()
{
	// English 1C keywords can be enabled later by filling this list.
}

void __fastcall TSyn1CSyn::LoadAnnotations()
{
	const wchar_t* annotations[] = {
		L"&\u043D\u0430\u043A\u043B\u0438\u0435\u043D\u0442\u0435",
		L"&\u043D\u0430\u0441\u0435\u0440\u0432\u0435\u0440\u0435",
		L"&\u043D\u0430\u0441\u0435\u0440\u0432\u0435\u0440\u0435\u0431\u0435\u0437\u043A\u043E\u043D\u0442\u0435\u043A\u0441\u0442\u0430",
		L"&\u043D\u0430\u043A\u043B\u0438\u0435\u043D\u0442\u0435\u043D\u0430\u0441\u0435\u0440\u0432\u0435\u0440\u0435",
		L"&\u043F\u0435\u0440\u0435\u0434", L"&\u043F\u043E\u0441\u043B\u0435"
	};

	for (int i = 0; i < sizeof(annotations) / sizeof(annotations[0]); ++i)
		FAnnotations->Add(annotations[i]);
}

bool __fastcall TSyn1CSyn::IsIdentifierChar(WideChar ch) const
{
	return (ch == L'_')
		|| (ch >= L'0' && ch <= L'9')
		|| (ch >= L'a' && ch <= L'z')
		|| (ch >= L'A' && ch <= L'Z')
		|| (ch >= L'\u0430' && ch <= L'\u044F')
		|| (ch >= L'\u0410' && ch <= L'\u042F')
		|| (ch == L'\u0451')
		|| (ch == L'\u0401');
}

bool __fastcall TSyn1CSyn::IsKeywordToken(const String& token) const
{
	return FKeywords->IndexOf(token) >= 0 || FEnglishKeywords->IndexOf(token) >= 0;
}

bool __fastcall TSyn1CSyn::IsAnnotationToken(const String& token) const
{
	return FAnnotations->IndexOf(token) >= 0;
}

bool __fastcall TSyn1CSyn::IsIdentChar(WideChar AChar)
{
	return IsIdentifierChar(AChar);
}

bool __fastcall TSyn1CSyn::IsKeyword(const String AKeyword)
{
	return IsKeywordToken(AKeyword.LowerCase());
}

String __fastcall TSyn1CSyn::GetKeyWords(int TokenKind)
{
	if (TokenKind == tk1CKeyword)
		return FKeywords->CommaText;
	if (TokenKind == tk1CAnnotation)
		return FAnnotations->CommaText;

	return L"";
}

String __fastcall TSyn1CSyn::GetSampleSource()
{
	return L"&\u041D\u0430\u0421\u0435\u0440\u0432\u0435\u0440\u0435\n"
		L"\u041F\u0440\u043E\u0446\u0435\u0434\u0443\u0440\u0430 \u041E\u0431\u043D\u043E\u0432\u0438\u0442\u044C\u0414\u0430\u043D\u043D\u044B\u0435() \u042D\u043A\u0441\u043F\u043E\u0440\u0442\n"
		L"    // \u041A\u043E\u043C\u043C\u0435\u043D\u0442\u0430\u0440\u0438\u0439\n"
		L"    \u0415\u0441\u043B\u0438 \u0417\u043D\u0430\u0447\u0435\u043D\u0438\u0435 = 10 \u0422\u043E\u0433\u0434\u0430\n"
		L"        \u0421\u043E\u043E\u0431\u0449\u0438\u0442\u044C(\"\u0413\u043E\u0442\u043E\u0432\u043E \"\"\u041E\u041A\"\");\n"
		L"    \u041A\u043E\u043D\u0435\u0446\u0415\u0441\u043B\u0438;\n"
		L"\u041A\u043E\u043D\u0435\u0446\u041F\u0440\u043E\u0446\u0435\u0434\u0443\u0440\u044B";
}

TSynHighlighterAttributes* __fastcall TSyn1CSyn::GetDefaultAttribute(int Index)
{
	switch (Index)
	{
		case SYN_ATTR_COMMENT: return FCommentAttri;
		case SYN_ATTR_IDENTIFIER: return FIdentifierAttri;
		case SYN_ATTR_KEYWORD: return FKeyAttri;
		case SYN_ATTR_STRING: return FStringAttri;
		case SYN_ATTR_WHITESPACE: return FSpaceAttri;
		case SYN_ATTR_SYMBOL: return FSymbolAttri;
		default: return FIdentifierAttri;
	}
}

bool __fastcall TSyn1CSyn::GetEol()
{
	return Run == FLineLen + 1;
}

String __fastcall TSyn1CSyn::GetToken()
{
	int len = Run - FTokenPos;
	if (len <= 0 || FTokenPos >= FLineLen)
		return L"";

	if (FTokenPos + len > FLineLen)
		len = FLineLen - FTokenPos;

	return FLineStr.SubString(FTokenPos + 1, len);
}

TSynHighlighterAttributes* __fastcall TSyn1CSyn::GetTokenAttribute()
{
	switch (FTokenID)
	{
		case tk1CComment: return FCommentAttri;
		case tk1CDirective: return FDirectiveAttri;
		case tk1CIdentifier: return FIdentifierAttri;
		case tk1CKeyword: return FKeyAttri;
		case tk1CNumber: return FNumberAttri;
		case tk1CSpace: return FSpaceAttri;
		case tk1CString: return FStringAttri;
		case tk1CSymbol: return FSymbolAttri;
		case tk1CAnnotation: return FAnnotationAttri;
		default: return FIdentifierAttri;
	}
}

int __fastcall TSyn1CSyn::GetTokenKind()
{
	return FTokenID;
}

int __fastcall TSyn1CSyn::GetTokenPos()
{
	return FTokenPos;
}

void __fastcall TSyn1CSyn::SetLine(const String Value, int LineNumber)
{
	FLineStr = Value;
	FCasedLineStr = Value.LowerCase();
	FLine = FLineStr.c_str();
	FCasedLine = FCasedLineStr.c_str();
	FLineLen = FLineStr.Length();
	FLineNumber = LineNumber;
	Run = 0;
	FOldRun = Run;
	FTokenPos = 0;
	FTokenID = tk1CNull;
}

void __fastcall TSyn1CSyn::NullProc()
{
	FTokenID = tk1CNull;
	++Run;
}

void __fastcall TSyn1CSyn::SpaceProc()
{
	FTokenID = tk1CSpace;
	while (Run < FLineLen && FLine[Run] <= L' ')
		++Run;
}

void __fastcall TSyn1CSyn::CommentProc()
{
	FTokenID = tk1CComment;
	Run = FLineLen;
}

void __fastcall TSyn1CSyn::StringProc()
{
	FTokenID = tk1CString;
	++Run;
	while (Run < FLineLen)
	{
		if (FLine[Run] == L'"')
		{
			++Run;
			if (Run < FLineLen && FLine[Run] == L'"')
			{
				++Run;
				continue;
			}
			break;
		}
		++Run;
	}
}

void __fastcall TSyn1CSyn::NumberProc()
{
	FTokenID = tk1CNumber;
	while (Run < FLineLen && FLine[Run] >= L'0' && FLine[Run] <= L'9')
		++Run;
	if (Run < FLineLen && (FLine[Run] == L'.' || FLine[Run] == L','))
	{
		++Run;
		while (Run < FLineLen && FLine[Run] >= L'0' && FLine[Run] <= L'9')
			++Run;
	}
}

void __fastcall TSyn1CSyn::DirectiveProc()
{
	FTokenID = tk1CDirective;
	++Run;
	while (Run < FLineLen && IsIdentifierChar(FCasedLine[Run]))
		++Run;
}

void __fastcall TSyn1CSyn::AnnotationProc()
{
	++Run;
	while (Run < FLineLen && IsIdentifierChar(FCasedLine[Run]))
		++Run;

	String token = GetToken().LowerCase();
	FTokenID = IsAnnotationToken(token) ? tk1CAnnotation : tk1CSymbol;
}

void __fastcall TSyn1CSyn::IdentifierProc()
{
	while (Run < FLineLen && IsIdentifierChar(FCasedLine[Run]))
		++Run;

	String token = GetToken().LowerCase();
	FTokenID = IsKeywordToken(token) ? tk1CKeyword : tk1CIdentifier;
}

void __fastcall TSyn1CSyn::SymbolProc()
{
	FTokenID = tk1CSymbol;
	++Run;
}

void __fastcall TSyn1CSyn::Next()
{
	FTokenPos = Run;
	if (Run >= FLineLen)
	{
		NullProc();
		TSynCustomHighlighter::Next();
		return;
	}

	WideChar ch = FLine[Run];
	if (ch <= L' ')
		SpaceProc();
	else if (ch == L'/' && Run + 1 < FLineLen && FLine[Run + 1] == L'/')
		CommentProc();
	else if (ch == L'"')
		StringProc();
	else if (ch >= L'0' && ch <= L'9')
		NumberProc();
	else if (ch == L'#')
		DirectiveProc();
	else if (ch == L'&')
		AnnotationProc();
	else if (IsIdentifierChar(FCasedLine[Run]) && !(FCasedLine[Run] >= L'0' && FCasedLine[Run] <= L'9'))
		IdentifierProc();
	else
		SymbolProc();

	TSynCustomHighlighter::Next();
}
