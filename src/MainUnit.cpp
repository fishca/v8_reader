//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.IniFiles.hpp>
#include <System.IOUtils.hpp>
#include <System.UITypes.hpp>
#include <System.Zip.hpp>

#include <windows.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <System.SysUtils.hpp>

#include "APIcfBase_vcl_adapter.h"
#include "../core/src/Base64.h"
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Graphics.hpp>
#include "VclByteStreamAdapter.h"
#include "MetadataTreeBuilder.h"
#include "Class_1CD.h"
#include "CommonModules.h"
#include "MainUnit.h"
#include "guids.h"
#include "Catalogs.h"
#include "Documents.h"
#include "Numerators.h"
#include "Sequences.h"
#include "Journals.h"
#include "Enums.h"
#include "Reports.h"
#include "DataProcessors.h"
#include "ChartOfCharacteristicTypes.h"
#include "ChartOfAccounts.h"
#include "ChartOfCalculationTypes.h"
#include "InformationRegisters.h"
#include "AccumulationRegisters.h"
#include "AccountingRegisters.h"
#include "CalculationRegisters.h"
#include "BusinessProceses.h"
#include "Tasks.h"
#include "SessionParameters.h"
#include "EventSubscriptions.h"
#include "Roles.h"
#include "CommonCommands.h"
#include "TConstants.h"
#include "CommonPictures.h"
#include "CommandGroups.h"
#include "CommonForms.h"
#include "Interfaces.h"
#include "ExternalDataSources.h"
#include "CommonAttributes.h"
#include "ExchangePlans.h"
#include "FilterCriteria.h"
#include "ScheduledJobs.h"
#include "Bots.h"
#include "FunctionalOptions.h"
#include "FunctionalOptionsParameters.h"
#include "DefinedTypes.h"
#include "SettingsStorages.h"
#include "XDTOPackages.h"
#include "WebServices.h"
#include "WSReferences.h"
#include "HTTPServices.h"
#include "WebSocketClients.h"
#include "IntegrationServices.h"
#include "StyleItems.h"
#include "Styles.h"
#include "Langs.h"
#include "Subsystem.h"
#include "../core/include/v8reader_core/V8ReaderCore.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "SynEdit"
#pragma link "SynMemo"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterCpp"
#pragma link "SynHighlighterGeneral"
#pragma link "SynEdit"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterCpp"
#pragma link "SynHighlighterGeneral"
#pragma link "SynMemo"
#pragma resource "*.dfm"
TMainForm *MainForm;
MessageRegistrator* msreg;

static void get_cf_name(v8catalog* cf, Messager* mess);
static void get_cf_name(tree* tr, Messager* mess);

static const TColor DefaultHighlightKeywordColor = clNavy;
static const TColor DefaultHighlightCommentColor = clGreen;
static const TColor DefaultHighlightStringColor = clMaroon;
static const TColor DefaultHighlightNumberColor = clPurple;
static const TColor DefaultHighlightPreprocessorColor = clTeal;
static const TColor DefaultHighlightSymbolColor = clGrayText;
static const TColor DefaultHighlightAnnotationColor = clOlive;

static bool IsVerboseUiLoggingEnabled()
{
	String envValue = GetEnvironmentVariable(L"V8READER_VERBOSE_LOG");
	envValue = Trim(envValue).LowerCase();
	if (envValue == L"1" || envValue == L"true" || envValue == L"yes" || envValue == L"on")
		return true;

	for (int i = 1; i <= ParamCount(); i++)
	{
		String arg = Trim(ParamStr(i)).LowerCase();
		if (arg == L"--verbose-log" || arg == L"/verbose-log" || arg == L"--diagnostic-log")
			return true;
	}

	return false;
}

static bool IsMessOutputEnabled()
{
	String envValue = Trim(GetEnvironmentVariable(L"V8READER_MESS_OUTPUT")).LowerCase();
	if (envValue == L"0" || envValue == L"false" || envValue == L"no" || envValue == L"off")
		return false;
	if (envValue == L"1" || envValue == L"true" || envValue == L"yes" || envValue == L"on")
		return true;

	for (int i = 1; i <= ParamCount(); i++)
	{
		String arg = Trim(ParamStr(i)).LowerCase();
		if (arg == L"--no-mess-output" || arg == L"/no-mess-output" || arg == L"--quiet")
			return false;
		if (arg == L"--mess-output" || arg == L"/mess-output")
			return true;
	}

	return false;
}

static bool IsFileLoggingEnabled()
{
	String envValue = GetEnvironmentVariable(L"V8READER_FILE_LOG");
	envValue = Trim(envValue).LowerCase();
	if (envValue == L"1" || envValue == L"true" || envValue == L"yes" || envValue == L"on")
		return true;

	for (int i = 1; i <= ParamCount(); i++)
	{
		String arg = Trim(ParamStr(i)).LowerCase();
		if (arg == L"--logfile" || arg == L"/logfile" || arg == L"--enable-file-log")
			return true;
	}

	return false;
}

static String GetHighlightSettingsFileName()
{
	String appData = GetEnvironmentVariable(L"APPDATA");
	if (appData.IsEmpty())
		appData = TPath::GetHomePath();

	String settingsDir = TPath::Combine(appData, L"v8reader");
	ForceDirectories(settingsDir);
	return TPath::Combine(settingsDir, L"highlight.ini");
}

static void Configure1CHighlighter(TSyn1CSyn* highlighter)
{
	if (!highlighter)
		return;

	highlighter->CommentAttri->Foreground = DefaultHighlightCommentColor;
	highlighter->IdentifierAttri->Foreground = clWindowText;
	highlighter->SpaceAttri->Foreground = clWindowText;
	highlighter->KeyAttri->Foreground = DefaultHighlightKeywordColor;
	highlighter->NumberAttri->Foreground = DefaultHighlightNumberColor;
	highlighter->DirectiveAttri->Foreground = DefaultHighlightPreprocessorColor;
	highlighter->StringAttri->Foreground = DefaultHighlightStringColor;
	highlighter->SymbolAttri->Foreground = DefaultHighlightSymbolColor;
	highlighter->AnnotationAttri->Foreground = DefaultHighlightAnnotationColor;
	highlighter->KeyAttri->Style = TFontStyles() << fsBold;
	highlighter->CommentAttri->Style = TFontStyles() << fsItalic;
}

static void ConfigureModuleGeneralHighlighter(TSynGeneralSyn* highlighter)
{
	if (!highlighter)
		return;

	highlighter->Comments = TCommentStyles() << csCPPStyle;
	highlighter->StringDelim = sdDoubleQuote;
	highlighter->DetectPreprocessor = true;
	highlighter->IdentifierChars =
		L"_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
		L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
		L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

	highlighter->KeyWords->Clear();
	const wchar_t* keywords[] = {
		L"Если", L"Тогда", L"Иначе", L"ИначеЕсли", L"КонецЕсли",
		L"Для", L"Каждого", L"Из", L"По", L"Цикл", L"Пока", L"КонецЦикла",
		L"Процедура", L"КонецПроцедуры", L"Функция", L"КонецФункции",
		L"Возврат", L"Экспорт", L"Попытка", L"Исключение", L"КонецПопытки",
		L"ВызватьИсключение", L"Продолжить", L"Прервать", L"Перейти",
		L"Новый", L"Неопределено", L"Истина", L"Ложь", L"И", L"Или", L"Не",
		L"Выполнить", L"Перем"
	};

	for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i)
	{
		highlighter->KeyWords->Add(keywords[i]);
		highlighter->KeyWords->Add(String(keywords[i]).LowerCase());
	}

	highlighter->CommentAttri->Foreground = DefaultHighlightCommentColor;
	highlighter->CommentAttri->Style = TFontStyles() << fsItalic;
	highlighter->IdentifierAttri->Foreground = clBlack;
	highlighter->KeyAttri->Foreground = DefaultHighlightKeywordColor;
	highlighter->KeyAttri->Style = TFontStyles() << fsBold;
	highlighter->NumberAttri->Foreground = DefaultHighlightNumberColor;
	highlighter->PreprocessorAttri->Foreground = DefaultHighlightPreprocessorColor;
	highlighter->StringAttri->Foreground = DefaultHighlightStringColor;
	highlighter->SymbolAttri->Foreground = DefaultHighlightSymbolColor;
	highlighter->SpaceAttri->Foreground = clBlack;
}

static TColorBox* CreateHighlightColorBox(TWinControl* parent, int top, TColor selected)
{
	TColorBox* colorBox = new TColorBox(parent);
	colorBox->Parent = parent;
	colorBox->Left = 210;
	colorBox->Top = top - 3;
	colorBox->Width = 240;
	colorBox->Height = 22;
	colorBox->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbSystemColors << cbPrettyNames;
	colorBox->Selected = selected;
	return colorBox;
}

static String Strip1CStringAndComment(const String& line)
{
	String result;
	bool inString = false;

	for (int i = 1; i <= line.Length(); ++i)
	{
		wchar_t ch = line[i];
		if (inString)
		{
			if (ch == L'"')
			{
				if (i < line.Length() && line[i + 1] == L'"')
					++i;
				else
					inString = false;
			}
			result += L' ';
			continue;
		}

		if (ch == L'"')
		{
			inString = true;
			result += L' ';
			continue;
		}

		if (ch == L'/' && i < line.Length() && line[i + 1] == L'/')
			break;

		result += ch;
	}

	return Trim(result).LowerCase();
}

static bool IsLineComment(const UnicodeString& s)
{
	UnicodeString t = s.TrimLeft();
	return t.SubString(1, 2) == L"//";
}


static bool Is1CProcedureOrFunctionStart(const String& line)
{
	return line.Pos(L"\u043F\u0440\u043E\u0446\u0435\u0434\u0443\u0440\u0430") == 1
		|| line.Pos(L"\u0444\u0443\u043D\u043A\u0446\u0438\u044F") == 1;
}

static bool Is1CProcedureOrFunctionEnd(const String& line)
{
	return line.Pos(L"\u043A\u043E\u043D\u0435\u0446\u043F\u0440\u043E\u0446\u0435\u0434\u0443\u0440\u044B") == 1
		|| line.Pos(L"\u043A\u043E\u043D\u0435\u0446\u0444\u0443\u043D\u043A\u0446\u0438\u0438") == 1;
}

static PVirtualNode GetActiveTreeNode(TVirtualStringTree* tree, PVirtualNode fallbackNode = nullptr)
{
	if (fallbackNode)
		return fallbackNode;

	if (!tree)
		return nullptr;

	if (tree->FocusedNode)
		return tree->FocusedNode;

	return tree->GetFirstSelected();
}

static bool IsConfigurationRootNode(TVirtualStringTree* tree, PVirtualNode node)
{
	return tree && node && node->Parent == tree->RootNode;
}

static bool LooksLikeGuidFileName(const String& value)
{
	if (value.Length() != 36)
		return false;

	for (int i = 1; i <= value.Length(); ++i)
	{
		wchar_t ch = value[i];
		if (i == 9 || i == 14 || i == 19 || i == 24)
		{
			if (ch != L'-')
				return false;
		}
		else if (!((ch >= L'0' && ch <= L'9')
			|| (ch >= L'a' && ch <= L'f')
			|| (ch >= L'A' && ch <= L'F')))
			return false;
	}

	return true;
}

static String DecodeTextFileForModuleFallback(const String& fileName)
{
	if (!FileExists(fileName))
		return L"";

	try
	{
		TBytes bytes = TFile::ReadAllBytes(fileName);
		if (bytes.empty())
			return L"";

		TEncoding* encoding = nullptr;
		int offset = TEncoding::GetBufferEncoding(bytes, encoding);
		if (offset > 0)
			return encoding->GetString(bytes, offset, bytes.Length - offset);

		int limit = bytes.Length < 200 ? bytes.Length : 200;
		int checked = 0;
		int zeroOdd = 0;
		for (int i = 1; i < limit; i += 2)
		{
			++checked;
			if (bytes[i] == 0)
				++zeroOdd;
		}

		if (checked > 0 && zeroOdd * 2 >= checked)
			return String((wchar_t*)&bytes[0], bytes.Length / 2);

		return TEncoding::UTF8->GetString(bytes);
	}
	catch (...)
	{
		return L"";
	}
}

static bool LooksLike1CModuleFallbackText(const String& text)
{
	return text.Length() > 20
		&& (text.Pos(L"\n") > 0
			|| text.Pos(L"\r") > 0
			|| text.Pos(L"Процедура") > 0
			|| text.Pos(L"Функция") > 0
			|| text.Pos(L"КонецПроцедуры") > 0
			|| text.Pos(L"КонецФункции") > 0);
}

static String ReadUnpackedModuleTextByObjectGuid(const String& sourceDir, const String& guid)
{
	for (int i = 0; i <= 5; ++i)
	{
		String suffix = L"." + IntToStr(i);
		String objectDir = TPath::Combine(sourceDir, guid + suffix);

		String text = DecodeTextFileForModuleFallback(TPath::Combine(objectDir, L"text"));
		if (LooksLike1CModuleFallbackText(text))
			return text;

		text = DecodeTextFileForModuleFallback(TPath::Combine(objectDir, L"module"));
		if (LooksLike1CModuleFallbackText(text))
			return text;

		text = DecodeTextFileForModuleFallback(TPath::Combine(sourceDir, guid + suffix));
		if (LooksLike1CModuleFallbackText(text))
			return text;
	}

	return L"";
}

static String FindUnpackedModuleTextByNodeName(const String& nodeName)
{
	if (nodeName.IsEmpty())
		return L"";

	std::vector<String> sourceDirs;
	sourceDirs.push_back(TPath::Combine(GetCurrentDir(), L"SourceCF"));
	sourceDirs.push_back(TPath::Combine(ExtractFilePath(ParamStr(0)), L"SourceCF"));

	for (const auto& sourceDir : sourceDirs)
	{
		if (!TDirectory::Exists(sourceDir))
			continue;

		TStringDynArray files = TDirectory::GetFiles(sourceDir);
		for (int i = 0; i < files.Length; ++i)
		{
			String guid = ExtractFileName(files[i]);
			if (!LooksLikeGuidFileName(guid))
				continue;

			String metadataText = DecodeTextFileForModuleFallback(files[i]);
			if (metadataText.Pos(nodeName) <= 0)
				continue;

			String moduleText = ReadUnpackedModuleTextByObjectGuid(sourceDir, guid);
			if (!moduleText.IsEmpty())
				return moduleText;
		}
	}

	return L"";
}

static void AddUniqueCandidate(std::vector<String>& values, const String& value)
{
	if (value.IsEmpty())
		return;

	String upper = value.UpperCase();
	for (const auto& existing : values)
	{
		if (existing.UpperCase() == upper)
			return;
	}

	values.push_back(value);
}

static bool ExtractBytesFromStream(TBytesStream* stream, TBytes& outBytes)
{
	if (!stream || stream->Size <= 0)
		return false;

	TBytes bytes = stream->Bytes;
	bytes.Length = static_cast<int>(stream->Size);
	outBytes = bytes;
	return !outBytes.empty();
}

static bool TryLoadPictureFromBytes(const TBytes& bytes, TPicture* targetPicture = nullptr)
{
	if (bytes.empty())
		return false;

	try
	{
		std::unique_ptr<TBytesStream> stream(new TBytesStream(bytes));
		stream->Position = 0;
		if (targetPicture)
		{
			targetPicture->LoadFromStream(stream.get());
			return targetPicture->Graphic && !targetPicture->Graphic->Empty;
		}

		std::unique_ptr<TPicture> probePicture(new TPicture());
		probePicture->LoadFromStream(stream.get());
		return probePicture->Graphic && !probePicture->Graphic->Empty;
	}
	catch (...)
	{
		return false;
	}
}

static bool EndsWithIgnoreCase(const String& value, const String& suffix)
{
	if (value.Length() < suffix.Length())
		return false;

	const String rightPart = value.SubString(value.Length() - suffix.Length() + 1, suffix.Length());
	return rightPart.LowerCase() == suffix.LowerCase();
}

static bool TryDecodeSvgTextFromBytes(const TBytes& bytes, String& svgText)
{
	svgText = L"";
	if (bytes.empty())
		return false;

	String text;
	try
	{
		TEncoding* enc = nullptr;
		int offset = TEncoding::GetBufferEncoding(bytes, enc);
		if (offset > 0 && enc)
			text = enc->GetString(bytes, offset, bytes.Length - offset);
		else
			text = TEncoding::UTF8->GetString(bytes, 0, bytes.Length);
	}
	catch (...)
	{
		try
		{
			text = String((char*)&bytes[0], bytes.Length);
		}
		catch (...)
		{
			return false;
		}
	}

	String lowered = text.LowerCase();
	if (lowered.Pos(L"<svg") > 0 || (lowered.Pos(L"<?xml") > 0 && lowered.Pos(L"<svg") > 0))
	{
		svgText = text;
		return true;
	}

	return false;
}

static bool LooksLikeBase64Payload(const String& value)
{
	const String trimmed = Trim(value);
	if (trimmed.Length() < 64)
		return false;

	for (int i = 1; i <= trimmed.Length(); ++i)
	{
		const wchar_t ch = trimmed[i];
		const bool base64Char =
			(ch >= L'A' && ch <= L'Z')
			|| (ch >= L'a' && ch <= L'z')
			|| (ch >= L'0' && ch <= L'9')
			|| ch == L'+'
			|| ch == L'/'
			|| ch == L'='
			|| ch == L'\r'
			|| ch == L'\n'
			|| ch == L'\t'
			|| ch == L' ';
		if (!base64Char)
			return false;
	}

	return true;
}

static bool TryExtractEmbeddedPictureBytes(const TBytes& sourceBytes, TBytes& outBytes)
{
	if (sourceBytes.Length < 8)
		return false;

	auto isPngAt = [&sourceBytes](int i) -> bool
	{
		return i + 8 <= sourceBytes.Length
			&& sourceBytes[i] == 0x89 && sourceBytes[i + 1] == 0x50 && sourceBytes[i + 2] == 0x4E && sourceBytes[i + 3] == 0x47
			&& sourceBytes[i + 4] == 0x0D && sourceBytes[i + 5] == 0x0A && sourceBytes[i + 6] == 0x1A && sourceBytes[i + 7] == 0x0A;
	};

	auto isJpegAt = [&sourceBytes](int i) -> bool
	{
		return i + 3 <= sourceBytes.Length
			&& sourceBytes[i] == 0xFF && sourceBytes[i + 1] == 0xD8 && sourceBytes[i + 2] == 0xFF;
	};

	auto isGifAt = [&sourceBytes](int i) -> bool
	{
		return i + 6 <= sourceBytes.Length
			&& sourceBytes[i] == 0x47 && sourceBytes[i + 1] == 0x49 && sourceBytes[i + 2] == 0x46
			&& sourceBytes[i + 3] == 0x38 && (sourceBytes[i + 4] == 0x39 || sourceBytes[i + 4] == 0x37) && sourceBytes[i + 5] == 0x61;
	};

	auto isBmpAt = [&sourceBytes](int i) -> bool
	{
		return i + 2 <= sourceBytes.Length && sourceBytes[i] == 0x42 && sourceBytes[i + 1] == 0x4D;
	};

	auto isIcoAt = [&sourceBytes](int i) -> bool
	{
		return i + 4 <= sourceBytes.Length
			&& sourceBytes[i] == 0x00 && sourceBytes[i + 1] == 0x00 && sourceBytes[i + 2] == 0x01 && sourceBytes[i + 3] == 0x00;
	};

	for (int i = 0; i < sourceBytes.Length - 2; ++i)
	{
		const bool isCandidate =
			isPngAt(i) || isJpegAt(i) || isGifAt(i) || isBmpAt(i) || isIcoAt(i);
		if (!isCandidate)
			continue;

		const int tailLen = sourceBytes.Length - i;
		if (tailLen <= 0)
			continue;

		TBytes candidateBytes;
		candidateBytes.Length = tailLen;
		Move(&sourceBytes[i], &candidateBytes[0], tailLen);
		if (TryLoadPictureFromBytes(candidateBytes))
		{
			outBytes = candidateBytes;
			return true;
		}
	}

	return false;
}

static bool TryExtractPictureFromZipBytes(const TBytes& sourceBytes, TBytes& outBytes)
{
	if (sourceBytes.Length < 4)
		return false;

	// PK\003\004
	if (!(sourceBytes[0] == 0x50 && sourceBytes[1] == 0x4B && sourceBytes[2] == 0x03 && sourceBytes[3] == 0x04))
		return false;

	try
	{
		std::unique_ptr<TBytesStream> zipStream(new TBytesStream(sourceBytes));
		std::unique_ptr<TZipFile> zipFile(new TZipFile());
		zipFile->Open(zipStream.get(), zmRead);

		System::DynamicArray<String> fileNames = zipFile->FileNames;
		const int fileCount = zipFile->FileCount;

		auto isPreferredImageExt = [](const String& name) -> bool
		{
			String lowerName = Trim(name).LowerCase();
			return EndsWithIgnoreCase(lowerName, L".png")
				|| EndsWithIgnoreCase(lowerName, L".jpg")
				|| EndsWithIgnoreCase(lowerName, L".jpeg")
				|| EndsWithIgnoreCase(lowerName, L".gif")
				|| EndsWithIgnoreCase(lowerName, L".bmp")
				|| EndsWithIgnoreCase(lowerName, L".ico")
				|| EndsWithIgnoreCase(lowerName, L".tif")
				|| EndsWithIgnoreCase(lowerName, L".tiff")
				|| EndsWithIgnoreCase(lowerName, L".webp");
		};

		for (int pass = 0; pass < 2; ++pass)
		{
			for (int i = 0; i < fileCount; ++i)
			{
				if (i >= fileNames.Length)
					continue;

				const String entryName = fileNames[i];
				if (pass == 0 && !isPreferredImageExt(entryName))
					continue;

				TBytes entryBytes;
				zipFile->Read(i, entryBytes);

				if (TryLoadPictureFromBytes(entryBytes))
				{
					outBytes = entryBytes;
					zipFile->Close();
					return true;
				}

				if (TryExtractEmbeddedPictureBytes(entryBytes, outBytes))
				{
					zipFile->Close();
					return true;
				}
			}
		}

		zipFile->Close();
	}
	catch (...)
	{
		return false;
	}

	return false;
}

static bool DecodeBase64ValueToBytes(const String& rawValue, TBytes& outBytes)
{
	String value = Trim(rawValue);
	if (value.IsEmpty())
		return false;

	std::size_t startIndex = 0;
	if (value.Length() >= 8 && value.SubString(1, 8).LowerCase() == L"#base64:")
		startIndex = 8;
	else if (value.Length() >= 6 && value.SubString(1, 6).LowerCase() == L"#data:")
		startIndex = 6;

	try
	{
		TBytes decodeBuffer;
		std::unique_ptr<TBytesStream> decoded(new TBytesStream(decodeBuffer));
		v8reader::vcl_bridge::TStreamByteStreamAdapter adapter(decoded.get());
		std::u16string encoded = v8reader::vcl_bridge::StringToUtf16(value);
		v8reader::core::encoding::base64_decode(encoded, adapter, startIndex);
		return ExtractBytesFromStream(decoded.get(), outBytes);
	}
	catch (...)
	{
		return false;
	}
}

static bool TryExtractImageBytesFromTree(tree* node, TBytes& outBytes)
{
	if (!node)
		return false;

	const node_type nodeType = node->get_type();
	const String value = node->get_value();
	const bool isBinaryNode = nodeType == nd_binary || nodeType == nd_binary2 || nodeType == nd_binary_d;
	const bool looksLikePrefixedBase64 = value.Length() >= 8 && value.SubString(1, 8).LowerCase() == L"#base64:";
	const bool looksLikeDataPrefix = value.Length() >= 6 && value.SubString(1, 6).LowerCase() == L"#data:";
	const bool looksLikeStringBase64 = nodeType == nd_string && LooksLikeBase64Payload(value);

	if ((isBinaryNode || looksLikePrefixedBase64 || looksLikeDataPrefix || looksLikeStringBase64)
		&& DecodeBase64ValueToBytes(value, outBytes))
	{
		if (TryLoadPictureFromBytes(outBytes))
			return true;
		String svgText;
		if (TryDecodeSvgTextFromBytes(outBytes, svgText))
			return true;
		if (TryExtractPictureFromZipBytes(outBytes, outBytes))
			return true;
		if (TryExtractEmbeddedPictureBytes(outBytes, outBytes))
			return true;
	}

	for (int i = 0; i < node->get_num_subnode(); ++i)
	{
		if (TryExtractImageBytesFromTree(node->get_subnode(i), outBytes))
			return true;
	}

	return false;
}

static void CollectGuidReferences(tree* node, std::vector<String>& guids)
{
	if (!node)
		return;

	const String value = node->get_value();
	if (ModuleTextStorage::IsGuidLike(value))
		AddUniqueCandidate(guids, value);

	for (int i = 0; i < node->get_num_subnode(); ++i)
		CollectGuidReferences(node->get_subnode(i), guids);
}

static bool TryReadV8FileBytes(v8file* file, TBytes& outBytes)
{
	if (!file)
		return false;

	try
	{
		TBytes rawBuffer;
		std::unique_ptr<TBytesStream> stream(new TBytesStream(rawBuffer));
		v8reader::vcl_bridge::SaveV8FileToVclStream(file, stream.get());
		return ExtractBytesFromStream(stream.get(), outBytes);
	}
	catch (...)
	{
		return false;
	}
}

static bool TryExtractImageBytesFromV8File(v8file* file, TBytes& outBytes)
{
	if (!file)
		return false;

	TBytes fileBytes;
	if (TryReadV8FileBytes(file, fileBytes))
	{
		if (TryLoadPictureFromBytes(fileBytes))
		{
			outBytes = fileBytes;
			return true;
		}
		String svgText;
		if (TryDecodeSvgTextFromBytes(fileBytes, svgText))
		{
			outBytes = fileBytes;
			return true;
		}
		if (TryExtractPictureFromZipBytes(fileBytes, outBytes))
			return true;
		if (TryExtractEmbeddedPictureBytes(fileBytes, outBytes))
			return true;
	}

	try
	{
		std::unique_ptr<tree> objectTree(get_treeFromV8file(file));
		if (objectTree && TryExtractImageBytesFromTree(objectTree.get(), outBytes))
			return true;
	}
	catch (...)
	{
	}

	if (file->IsCatalog())
	{
		try
		{
			std::unique_ptr<v8catalog> catalog(new v8catalog(file));
			if (catalog)
			{
				catalog->ClearIs8316();
				for (v8file* child = catalog->GetFirst(); child; child = child->GetNext())
				{
					if (TryExtractImageBytesFromV8File(child, outBytes))
						return true;
				}
			}
		}
		catch (...)
		{
		}
	}

	return false;
}

static bool TryExtractImageBytesFromSourceCf(const String& guid, TBytes& outBytes)
{
	if (guid.IsEmpty())
		return false;

	std::vector<String> roots;
	AddUniqueCandidate(roots, TPath::Combine(GetCurrentDir(), L"SourceCF"));
	AddUniqueCandidate(roots, TPath::Combine(ExtractFilePath(ParamStr(0)), L"SourceCF"));

	const String normalizedGuid = ModuleTextStorage::NormalizeGuidFileName(guid);
	std::vector<String> candidates;
	AddUniqueCandidate(candidates, normalizedGuid);
	for (int i = 0; i <= 7; ++i)
		AddUniqueCandidate(candidates, normalizedGuid + L"." + IntToStr(i));

	for (const auto& root : roots)
	{
		if (!TDirectory::Exists(root))
			continue;

		for (const auto& candidate : candidates)
		{
			const String directFile = TPath::Combine(root, candidate);
			if (FileExists(directFile))
			{
				try
				{
					TBytes bytes = TFile::ReadAllBytes(directFile);
					if (TryLoadPictureFromBytes(bytes))
					{
						outBytes = bytes;
						return true;
					}
					String svgText;
					if (TryDecodeSvgTextFromBytes(bytes, svgText))
					{
						outBytes = bytes;
						return true;
					}
					if (TryExtractPictureFromZipBytes(bytes, outBytes))
						return true;
					if (TryExtractEmbeddedPictureBytes(bytes, outBytes))
						return true;
				}
				catch (...)
				{
				}
			}

			const String candidateDir = TPath::Combine(root, candidate);
			if (!TDirectory::Exists(candidateDir))
				continue;

			TStringDynArray files = TDirectory::GetFiles(candidateDir);
			for (int i = 0; i < files.Length; ++i)
			{
				try
				{
					TBytes bytes = TFile::ReadAllBytes(files[i]);
					if (TryLoadPictureFromBytes(bytes))
					{
						outBytes = bytes;
						return true;
					}
					String svgText;
					if (TryDecodeSvgTextFromBytes(bytes, svgText))
					{
						outBytes = bytes;
						return true;
					}
					if (TryExtractPictureFromZipBytes(bytes, outBytes))
						return true;
					if (TryExtractEmbeddedPictureBytes(bytes, outBytes))
						return true;
				}
				catch (...)
				{
				}
			}
		}
	}

	return false;
}

void __fastcall TMainForm::ModuleMemoScanForFoldRanges(TObject *Sender,
	TSynFoldRanges *FoldRanges, TStrings *LinesToScan, int FromLine, int ToLine)
{
	if (FoldRanges == NULL || LinesToScan == NULL)
		return;

	const int ProcedureFoldType = 2;
	const int CommentFoldType   = 1;

	bool inCommentBlock = false;
	int commentStartLine = -1;

	bool inMultiLineComment = false;
	int multiCommentStartLine = -1;

	bool inProcBlock = false;

	for (int lineIndex = FromLine; lineIndex <= ToLine; ++lineIndex)
	{
		if (lineIndex < 0 || lineIndex >= LinesToScan->Count)
			continue;

		int foldLine = lineIndex + 1;
		String originalLine = LinesToScan->Strings[lineIndex];
		String line = Strip1CStringAndComment(originalLine);

		bool foldInfoSet = false;
		bool isLineComment = IsLineComment(originalLine);
		bool startsMultiLineComment = !isLineComment && line.Pos(L"/*") > 0;
		bool endsMultiLineComment = line.Pos(L"*/") > 0;

		// --- folding для многострочных комментариев /* */ ---
		if (!inMultiLineComment && startsMultiLineComment)
		{
			if (endsMultiLineComment)
			{
				FoldRanges->NoFoldInfo(foldLine);
			}
			else
			{
				inMultiLineComment = true;
				multiCommentStartLine = foldLine;
				FoldRanges->StartFoldRange(multiCommentStartLine, CommentFoldType);
			}
			foldInfoSet = true;
		}
		else if (inMultiLineComment && endsMultiLineComment)
		{
			FoldRanges->StopFoldRange(foldLine, CommentFoldType);
			inMultiLineComment = false;
			multiCommentStartLine = -1;
			foldInfoSet = true;
		}
		else if (inMultiLineComment)
		{
			FoldRanges->NoFoldInfo(foldLine);
			foldInfoSet = true;
		}

		// --- folding для последовательных // комментариев ---
		if (!foldInfoSet)
		{
			if (isLineComment)
			{
				if (!inCommentBlock)
				{
					inCommentBlock = true;
					commentStartLine = foldLine;
					FoldRanges->StartFoldRange(commentStartLine, CommentFoldType);
				}
				else
				{
					FoldRanges->NoFoldInfo(foldLine);
				}
				foldInfoSet = true;
			}
			else if (inCommentBlock)
			{
				FoldRanges->StopFoldRange(foldLine - 1, CommentFoldType);
				inCommentBlock = false;
				commentStartLine = -1;
			}
		}

		// --- folding для procedure/function ---
		if (!foldInfoSet)
		{
			if (line.IsEmpty())
			{
				FoldRanges->NoFoldInfo(foldLine);
			}
			else if (Is1CProcedureOrFunctionStart(line))
			{
				inProcBlock = true;
				FoldRanges->StartFoldRange(foldLine, ProcedureFoldType);
			}
			else if (inProcBlock && Is1CProcedureOrFunctionEnd(line))
			{
				FoldRanges->StopFoldRange(foldLine, ProcedureFoldType);
				inProcBlock = false;
			}
			else
			{
				FoldRanges->NoFoldInfo(foldLine);
			}
		}
	}

	if (inCommentBlock)
		FoldRanges->StopFoldRange(ToLine + 1, CommentFoldType);
	if (inMultiLineComment)
		FoldRanges->StopFoldRange(ToLine + 1, CommentFoldType);
}

static void AddConditionalInfoMessage(Messager* mess, const String& message)
{
	if (mess && mess->getUiMessagesEnabled() && IsVerboseUiLoggingEnabled())
		mess->AddMessage(message, msInfo);
}

static void AddConditionalInfoMessageParams(Messager* mess, const String& description, const String& parname1, const String& par1, const String& parname2, const String& par2)
{
	if (mess && mess->getUiMessagesEnabled() && IsVerboseUiLoggingEnabled())
		mess->AddMessage_(description, msInfo, parname1, par1, parname2, par2);
}

static void AddConditionalInfoMessageParams(Messager* mess, const String& description, const String& parname1, const String& par1, const String& parname2, const String& par2, const String& parname3, const String& par3)
{
	if (mess && mess->getUiMessagesEnabled() && IsVerboseUiLoggingEnabled())
		mess->AddMessage_(description, msInfo, parname1, par1, parname2, par2, parname3, par3);
}

static void StartConfigUnpackThread(const String& cfFileName, const String& sourceCfDir)
{
	const String targetDir = sourceCfDir;
	const std::string cfFileNameStd = AnsiString(cfFileName).c_str();
	const std::string targetDirStd = AnsiString(sourceCfDir).c_str();

	TThread* unpackThread = TThread::CreateAnonymousThread([targetDir, cfFileNameStd, targetDirStd]()
	{
		try
		{
			if (TDirectory::Exists(targetDir))
				TDirectory::Delete(targetDir, true);

			std::vector<std::string> filter;
			v8reader::core::parse_to_folder(cfFileNameStd, targetDirStd, filter);
		}
		catch (...)
		{
		}
	});
	unpackThread->FreeOnTerminate = true;
	unpackThread->Start();
}

static String FormatHeapStatus()
{
	THeapStatus hs = GetHeapStatus();
	return L"Allocated=" + IntToStr((__int64)hs.TotalAllocated)
		+ L", Free=" + IntToStr((__int64)hs.TotalFree)
		+ L", Committed=" + IntToStr((__int64)hs.TotalCommitted)
		+ L", Uncommitted=" + IntToStr((__int64)hs.TotalUncommitted);
}

static void LogHeapStatus(const String& stage, const String& guid = L"", const String& fileName = L"", int currentIndex = -1, int totalCount = -1)
{
	Messager* activeMessager = dynamic_cast<Messager*>(msreg);
	if(!msreg || (activeMessager && !activeMessager->getUiMessagesEnabled())) return;

	MessageRegistrator::MessageParams params;
	params.reserve(5);
	params.emplace_back(u"Heap", v8reader::vcl_bridge::StringToUtf16(FormatHeapStatus()));
	if(guid.Length())
		params.emplace_back(u"GUID", v8reader::vcl_bridge::StringToUtf16(guid));
	if(fileName.Length())
		params.emplace_back(u"File", v8reader::vcl_bridge::StringToUtf16(fileName));
	if(currentIndex >= 0)
		params.emplace_back(u"Item", v8reader::vcl_bridge::StringToUtf16(IntToStr(currentIndex)));
	if(totalCount >= 0)
		params.emplace_back(u"Total", v8reader::vcl_bridge::StringToUtf16(IntToStr(totalCount)));
	msreg->AddMessage(v8reader::vcl_bridge::StringToUtf16(stage), msInfo, &params);
}

void TMainForm::SetDefaultHighlightSettingsControls()
{
	if (HighlightKeywordColorBox) HighlightKeywordColorBox->Selected = DefaultHighlightKeywordColor;
	if (HighlightCommentColorBox) HighlightCommentColorBox->Selected = DefaultHighlightCommentColor;
	if (HighlightStringColorBox) HighlightStringColorBox->Selected = DefaultHighlightStringColor;
	if (HighlightNumberColorBox) HighlightNumberColorBox->Selected = DefaultHighlightNumberColor;
	if (HighlightPreprocessorColorBox) HighlightPreprocessorColorBox->Selected = DefaultHighlightPreprocessorColor;
	if (HighlightSymbolColorBox) HighlightSymbolColorBox->Selected = DefaultHighlightSymbolColor;
	if (HighlightAnnotationColorBox) HighlightAnnotationColorBox->Selected = DefaultHighlightAnnotationColor;
	if (HighlightKeywordBoldCheckBox) HighlightKeywordBoldCheckBox->Checked = true;
	if (HighlightCommentItalicCheckBox) HighlightCommentItalicCheckBox->Checked = true;
	if (UnpackCheckBox) UnpackCheckBox->Checked = false;
}

void TMainForm::ApplyHighlightSettings()
{
	if (!Syn1CSyn && !ModuleGeneralSyn)
		return;

	if (Syn1CSyn)
	{
		if (HighlightKeywordColorBox) Syn1CSyn->KeyAttri->Foreground = HighlightKeywordColorBox->Selected;
		if (HighlightCommentColorBox) Syn1CSyn->CommentAttri->Foreground = HighlightCommentColorBox->Selected;
		if (HighlightStringColorBox) Syn1CSyn->StringAttri->Foreground = HighlightStringColorBox->Selected;
		if (HighlightNumberColorBox) Syn1CSyn->NumberAttri->Foreground = HighlightNumberColorBox->Selected;
		if (HighlightPreprocessorColorBox) Syn1CSyn->DirectiveAttri->Foreground = HighlightPreprocessorColorBox->Selected;
		if (HighlightSymbolColorBox) Syn1CSyn->SymbolAttri->Foreground = HighlightSymbolColorBox->Selected;
		if (HighlightAnnotationColorBox) Syn1CSyn->AnnotationAttri->Foreground = HighlightAnnotationColorBox->Selected;

		Syn1CSyn->KeyAttri->Style =
			(HighlightKeywordBoldCheckBox && HighlightKeywordBoldCheckBox->Checked) ? (TFontStyles() << fsBold) : TFontStyles();
		Syn1CSyn->CommentAttri->Style =
			(HighlightCommentItalicCheckBox && HighlightCommentItalicCheckBox->Checked) ? (TFontStyles() << fsItalic) : TFontStyles();
	}

	if (ModuleGeneralSyn)
	{
		if (HighlightKeywordColorBox) ModuleGeneralSyn->KeyAttri->Foreground = HighlightKeywordColorBox->Selected;
		if (HighlightCommentColorBox) ModuleGeneralSyn->CommentAttri->Foreground = HighlightCommentColorBox->Selected;
		if (HighlightStringColorBox) ModuleGeneralSyn->StringAttri->Foreground = HighlightStringColorBox->Selected;
		if (HighlightNumberColorBox) ModuleGeneralSyn->NumberAttri->Foreground = HighlightNumberColorBox->Selected;
		if (HighlightPreprocessorColorBox) ModuleGeneralSyn->PreprocessorAttri->Foreground = HighlightPreprocessorColorBox->Selected;
		if (HighlightSymbolColorBox) ModuleGeneralSyn->SymbolAttri->Foreground = HighlightSymbolColorBox->Selected;
		ModuleGeneralSyn->IdentifierAttri->Foreground = clBlack;
		ModuleGeneralSyn->SpaceAttri->Foreground = clBlack;
		ModuleGeneralSyn->KeyAttri->Style =
			(HighlightKeywordBoldCheckBox && HighlightKeywordBoldCheckBox->Checked) ? (TFontStyles() << fsBold) : TFontStyles();
		ModuleGeneralSyn->CommentAttri->Style =
			(HighlightCommentItalicCheckBox && HighlightCommentItalicCheckBox->Checked) ? (TFontStyles() << fsItalic) : TFontStyles();
	}

	if (MemoObject) MemoObject->Invalidate();
	if (MemoManager) MemoManager->Invalidate();
	if (HighlightPreviewMemo) HighlightPreviewMemo->Invalidate();
}

void TMainForm::LoadHighlightSettings()
{
	HighlightSettingsLoading = true;
	std::unique_ptr<TIniFile> ini(new TIniFile(GetHighlightSettingsFileName()));
	HighlightKeywordColorBox->Selected = (TColor)ini->ReadInteger(L"Colors", L"Keyword", DefaultHighlightKeywordColor);
	HighlightCommentColorBox->Selected = (TColor)ini->ReadInteger(L"Colors", L"Comment", DefaultHighlightCommentColor);
	HighlightStringColorBox->Selected = (TColor)ini->ReadInteger(L"Colors", L"String", DefaultHighlightStringColor);
	HighlightNumberColorBox->Selected = (TColor)ini->ReadInteger(L"Colors", L"Number", DefaultHighlightNumberColor);
	HighlightPreprocessorColorBox->Selected = (TColor)ini->ReadInteger(L"Colors", L"Preprocessor", DefaultHighlightPreprocessorColor);
	HighlightSymbolColorBox->Selected = (TColor)ini->ReadInteger(L"Colors", L"Symbol", DefaultHighlightSymbolColor);
	HighlightAnnotationColorBox->Selected = (TColor)ini->ReadInteger(L"Colors", L"Annotation", DefaultHighlightAnnotationColor);
	HighlightKeywordBoldCheckBox->Checked = ini->ReadBool(L"Style", L"KeywordBold", true);
	HighlightCommentItalicCheckBox->Checked = ini->ReadBool(L"Style", L"CommentItalic", true);
	UnpackCheckBox->Checked = ini->ReadBool(L"Style", L"Unpack", false);
	HighlightSettingsLoading = false;

	ApplyHighlightSettings();
}

void TMainForm::SaveHighlightSettings()
{
	std::unique_ptr<TIniFile> ini(new TIniFile(GetHighlightSettingsFileName()));
	ini->WriteInteger(L"Colors", L"Keyword", HighlightKeywordColorBox->Selected);
	ini->WriteInteger(L"Colors", L"Comment", HighlightCommentColorBox->Selected);
	ini->WriteInteger(L"Colors", L"String", HighlightStringColorBox->Selected);
	ini->WriteInteger(L"Colors", L"Number", HighlightNumberColorBox->Selected);
	ini->WriteInteger(L"Colors", L"Preprocessor", HighlightPreprocessorColorBox->Selected);
	ini->WriteInteger(L"Colors", L"Symbol", HighlightSymbolColorBox->Selected);
	ini->WriteInteger(L"Colors", L"Annotation", HighlightAnnotationColorBox->Selected);
	ini->WriteBool(L"Style", L"KeywordBold", HighlightKeywordBoldCheckBox->Checked);
	ini->WriteBool(L"Style", L"CommentItalic", HighlightCommentItalicCheckBox->Checked);
	ini->WriteBool(L"Style", L"Unpack", UnpackCheckBox->Checked);
}

void __fastcall TMainForm::HighlightSettingsChanged(TObject *Sender)
{
	if (HighlightSettingsLoading)
		return;

	ApplyHighlightSettings();
	SaveHighlightSettings();
}

void __fastcall TMainForm::ResetHighlightSettingsClick(TObject *Sender)
{
	HighlightSettingsLoading = true;
	SetDefaultHighlightSettingsControls();
	HighlightSettingsLoading = false;
	ApplyHighlightSettings();
	SaveHighlightSettings();
}

void TMainForm::CreateHighlightSettingsTab()
{
	TTabSheet* previousActivePage = pagesEdit ? pagesEdit->ActivePage : nullptr;
	HighlightSettingsTab = new TTabSheet(this);
	HighlightSettingsTab->PageControl = pagesEdit;
	HighlightSettingsTab->Caption = L"Настройка";

	TPanel* panel = new TPanel(HighlightSettingsTab);
	panel->Parent = HighlightSettingsTab;
	panel->Align = alClient;
	panel->BevelOuter = bvNone;
	panel->ParentColor = true;

	const wchar_t* captions[] = {
		L"Ключевые слова", L"Комментарии", L"Строки",
		L"Числа", L"Директивы #", L"Символы", L"Аннотации &"
	};
	TColorBox** boxes[] = {
		&HighlightKeywordColorBox, &HighlightCommentColorBox, &HighlightStringColorBox,
		&HighlightNumberColorBox, &HighlightPreprocessorColorBox, &HighlightSymbolColorBox,
		&HighlightAnnotationColorBox
	};
	TColor defaults[] = {
		DefaultHighlightKeywordColor, DefaultHighlightCommentColor, DefaultHighlightStringColor,
		DefaultHighlightNumberColor, DefaultHighlightPreprocessorColor, DefaultHighlightSymbolColor,
		DefaultHighlightAnnotationColor
	};

	for (int i = 0; i < 7; ++i)
	{
		int top = 18 + i * 34;
		TLabel* label = new TLabel(panel);
		label->Parent = panel;
		label->Left = 18;
		label->Top = top;
		label->Caption = captions[i];

		*boxes[i] = CreateHighlightColorBox(panel, top, defaults[i]);
		(*boxes[i])->OnChange = HighlightSettingsChanged;
	}

	HighlightKeywordBoldCheckBox = new TCheckBox(panel);
	HighlightKeywordBoldCheckBox->Parent = panel;
	HighlightKeywordBoldCheckBox->Left = 18;
	HighlightKeywordBoldCheckBox->Top = 264;
	HighlightKeywordBoldCheckBox->Width = 250;
	HighlightKeywordBoldCheckBox->Caption = L"Ключевые слова жирным";
	HighlightKeywordBoldCheckBox->Checked = true;
	HighlightKeywordBoldCheckBox->OnClick = HighlightSettingsChanged;

	HighlightCommentItalicCheckBox = new TCheckBox(panel);
	HighlightCommentItalicCheckBox->Parent = panel;
	HighlightCommentItalicCheckBox->Left = 18;
	HighlightCommentItalicCheckBox->Top = 294;
	HighlightCommentItalicCheckBox->Width = 250;
	HighlightCommentItalicCheckBox->Caption = L"Комментарии курсивом";
	HighlightCommentItalicCheckBox->Checked = true;
	HighlightCommentItalicCheckBox->OnClick = HighlightSettingsChanged;

	UnpackCheckBox = new TCheckBox(panel);
	UnpackCheckBox->Parent = panel;
	UnpackCheckBox->Left = 18;
	UnpackCheckBox->Top = 316;
	UnpackCheckBox->Width = 250;
	UnpackCheckBox->Caption = L"Распаковывать в исходники";
	UnpackCheckBox->Checked = false;
	UnpackCheckBox->OnClick = HighlightSettingsChanged;

	TButton* resetButton = new TButton(panel);
	resetButton->Parent = panel;
	resetButton->Left = 18;
	resetButton->Top = 336;
	resetButton->Width = 150;
	resetButton->Caption = L"Сбросить";
	resetButton->OnClick = ResetHighlightSettingsClick;

	HighlightPreviewMemo = new TSynMemo(panel);
	HighlightPreviewMemo->Parent = panel;
	HighlightPreviewMemo->Left = 480;
	HighlightPreviewMemo->Top = 18;
	HighlightPreviewMemo->Width = 430;
	HighlightPreviewMemo->Height = 230;
	HighlightPreviewMemo->Anchors = TAnchors() << akLeft << akTop << akRight;
	HighlightPreviewMemo->ReadOnly = true;
	HighlightPreviewMemo->Font->Name = L"Courier New";
	HighlightPreviewMemo->Font->Size = 10;
	HighlightPreviewMemo->Highlighter = Syn1CSyn;
	HighlightPreviewMemo->OnScanForFoldRanges = ModuleMemoScanForFoldRanges;
	HighlightPreviewMemo->UseCodeFolding = true;
	HighlightPreviewMemo->Lines->Text =
		L"#Область ПримерКода\n"
		L"&НаСервере\n"
		L"Процедура ОбновитьДанные() Экспорт\n"
		L"    // Комментарий\n"
		L"    Если Значение = 10 Тогда\n"
		L"        Сообщить(\"Готово\");\n"
		L"    КонецЕсли;\n"
		L"КонецПроцедуры\n"
		L"#КонецОбласти";
	HighlightPreviewMemo->Invalidate();

	LoadHighlightSettings();
	if (previousActivePage)
		pagesEdit->ActivePage = previousActivePage;
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner), HighlightSettingsLoading(false),
	ModuleGeneralSyn(nullptr), ModuleSelectionTimer(nullptr), LastModuleNodeShown(nullptr), PendingModuleNode(nullptr),
	CurrentModuleNode(nullptr), CurrentModuleObject(nullptr), LoadingModuleText(false),
	CurrentModuleDirty(false), CurrentModuleOriginalText(L""), CurrentModuleKind(ModuleTextKind::Unknown),
	CurrentModuleStandalone(false), SwitchingModuleTab(false), CommonPicturePreviewImage(nullptr),
	CommonPicturePreviewSvg(nullptr),
	CommonPicturePreviewScrollBox(nullptr),
	CommonPicturePreviewInfoLabel(nullptr), MDManager(std::make_unique<MetaDataManager>())
{
	VirtualStringTreeValue1C->NodeDataSize = sizeof(VirtualTreeData);
	Syn1CSyn = new TSyn1CSyn(this);
	Configure1CHighlighter(Syn1CSyn);
	ModuleGeneralSyn = new TSynGeneralSyn(this);
	ConfigureModuleGeneralHighlighter(ModuleGeneralSyn);
	MemoObject->Highlighter = Syn1CSyn;
	MemoManager->Highlighter = Syn1CSyn;
	MemoObject->Color = clWindow;
	MemoManager->Color = clWindow;
	MemoObject->Font->Color = clBlack;
	MemoManager->Font->Color = clBlack;
	MemoObject->OnScanForFoldRanges = ModuleMemoScanForFoldRanges;
	MemoManager->OnScanForFoldRanges = ModuleMemoScanForFoldRanges;
	MemoObject->UseCodeFolding = true;
	MemoManager->UseCodeFolding = true;
	MemoObject->ReadOnly = false;
	VirtualStringTreeValue1C->OnClick = VirtualStringTreeValue1CClick;
	VirtualStringTreeValue1C->OnChange = VirtualStringTreeValue1CChange;
	VirtualStringTreeValue1C->OnNodeClick = VirtualStringTreeValue1CNodeClick;
	VirtualStringTreeValue1C->OnFocusChanged = VirtualStringTreeValue1CFocusChanged;
	VirtualStringTreeValue1C->OnMouseDown = VirtualStringTreeValue1CMouseDown;
	pagesEdit->OnChange = PagesEditChange;
	ConfigurationPopupMenu = new TPopupMenu(this);
	ConfigurationPopupMenu->OnPopup = ConfigurationPopupMenuPopup;
	OpenApplicationModuleMenuItem = new TMenuItem(ConfigurationPopupMenu);
	OpenApplicationModuleMenuItem->Caption = L"Открыть модуль приложения";
	OpenApplicationModuleMenuItem->Tag = static_cast<int>(ModuleTextKind::ApplicationModule);
	OpenApplicationModuleMenuItem->OnClick = OpenConfigurationModuleMenuItemClick;
	ConfigurationPopupMenu->Items->Add(OpenApplicationModuleMenuItem);
	OpenSessionModuleMenuItem = new TMenuItem(ConfigurationPopupMenu);
	OpenSessionModuleMenuItem->Caption = L"Открыть модуль сеанса";
	OpenSessionModuleMenuItem->Tag = static_cast<int>(ModuleTextKind::SessionModule);
	OpenSessionModuleMenuItem->OnClick = OpenConfigurationModuleMenuItemClick;
	ConfigurationPopupMenu->Items->Add(OpenSessionModuleMenuItem);
	OpenExternalConnectionModuleMenuItem = new TMenuItem(ConfigurationPopupMenu);
	OpenExternalConnectionModuleMenuItem->Caption = L"Открыть модуль внешнего соединения";
	OpenExternalConnectionModuleMenuItem->Tag = static_cast<int>(ModuleTextKind::ExternalConnectionModule);
	OpenExternalConnectionModuleMenuItem->OnClick = OpenConfigurationModuleMenuItemClick;
	ConfigurationPopupMenu->Items->Add(OpenExternalConnectionModuleMenuItem);
	ConstantsModulesMenuItem = new TMenuItem(ConfigurationPopupMenu);
	ConstantsModulesMenuItem->Caption = L"Модули констант";
	ConfigurationPopupMenu->Items->Add(ConstantsModulesMenuItem);
	OpenConstantsManagerModuleMenuItem = new TMenuItem(ConstantsModulesMenuItem);
	OpenConstantsManagerModuleMenuItem->Caption = L"Открыть модуль менеджера";
	OpenConstantsManagerModuleMenuItem->Tag = static_cast<int>(ModuleTextKind::ManagerModule);
	OpenConstantsManagerModuleMenuItem->OnClick = OpenConstantsModuleMenuItemClick;
	ConstantsModulesMenuItem->Add(OpenConstantsManagerModuleMenuItem);
	OpenConstantsValueManagerModuleMenuItem = new TMenuItem(ConstantsModulesMenuItem);
	OpenConstantsValueManagerModuleMenuItem->Caption = L"Открыть модуль менеджера значения";
	OpenConstantsValueManagerModuleMenuItem->Tag = static_cast<int>(ModuleTextKind::ObjectModule);
	OpenConstantsValueManagerModuleMenuItem->OnClick = OpenConstantsModuleMenuItemClick;
	ConstantsModulesMenuItem->Add(OpenConstantsValueManagerModuleMenuItem);
	VirtualStringTreeValue1C->PopupMenu = ConfigurationPopupMenu;
	ModuleSelectionTimer = new TTimer(this);
	ModuleSelectionTimer->Interval = 250;
	ModuleSelectionTimer->OnTimer = ModuleSelectionTimerTimer;
	ModuleSelectionTimer->Enabled = false;
	CreateHighlightSettingsTab();
	mess = new Messager(ListViewMessager, StatusBar1);
	LoadProgressBar->Position = 0;
	LoadProgressBar->Visible = false;
	mess->setUiMessagesEnabled(IsMessOutputEnabled());
	mess->setFileLoggingEnabled(IsFileLoggingEnabled());
	msreg = mess;
	if (mess->getFileLoggingEnabled())
	{
		String appDir = ExtractFilePath(ParamStr(0));
		String logfile = TPath::Combine(appDir, "v8reader.log");
		mess->setlogfile(logfile);
		AddConditionalInfoMessage(mess, L"Файловое логирование включено");
	}

}

//---------------------------------------------------------------------------
void TMainForm::ResetLoadProgress(int maxValue, const String& statusText)
{
	if (maxValue < 1)
		maxValue = 1;

	LoadProgressBar->Min = 0;
	LoadProgressBar->Max = maxValue;
	LoadProgressBar->Position = 0;
	LoadProgressBar->Visible = true;
	LoadProgressBar->BringToFront();

	if (!statusText.IsEmpty())
		mess->Status(statusText);

	LoadProgressBar->Update();
	Application->ProcessMessages();
}

void TMainForm::AdvanceLoadProgress(const String& statusText)
{
	if (!LoadProgressBar->Visible)
		LoadProgressBar->Visible = true;

	if (LoadProgressBar->Position < LoadProgressBar->Max)
		LoadProgressBar->Position = LoadProgressBar->Position + 1;

	if (!statusText.IsEmpty())
		mess->Status(statusText);

	LoadProgressBar->Update();
	Application->ProcessMessages();
}

void TMainForm::CompleteLoadProgress(const String& statusText)
{
	LoadProgressBar->Position = LoadProgressBar->Max;
	if (!statusText.IsEmpty())
		mess->Status(statusText);
	LoadProgressBar->Update();
	Application->ProcessMessages();
	LoadProgressBar->Visible = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::btnOpenEditNameClick(TObject *Sender)
{
	if (dlgOpenCF->Execute())
	{
		if (FileExists(dlgOpenCF->FileName))
		  EditNameCF->Text = dlgOpenCF->FileName;
		else
		  throw(Exception("File does not exist."));
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::btnGOClick(TObject *Sender)
{
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::VirtualStringTreeValue1CInitNode(TBaseVirtualTree *Sender, PVirtualNode ParentNode, PVirtualNode Node, TVirtualNodeInitStates &InitialStates)
{
	if(!ParentNode)
	{
		VirtualTreeData* d = (VirtualTreeData*)(Sender->GetNodeData(Node));
		initNode(d, L"Типы 1С", TreeImage::Root, 0);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::VirtualStringTreeValue1CGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	VirtualTreeData *NodeData = (VirtualTreeData*)Sender->GetNodeData(Node);
	CellText = NodeData->Name;
	//    switch (Column)
	//    {
	//	case 0:
	//		CellText = NodeData->Name;
	//		break;
	//	case 1:
	//		CellText = IntToStr(NodeData->Age);
	//		break;
	//    }
}
//---------------------------------------------------------------------------

void TMainForm::FillTreeMDConcrete(TVirtualStringTree *tree1C, PVirtualNode parentNode, const MetadataVector<MetadataEntity>& mdData, const String& md_name, int imgIndex)
{
	for(size_t i = 0; i < mdData.size(); i++)
	{
		MetadataEntity *CurCat = nullptr;
		if (md_name == md_Catalogs)
			CurCat = dynamic_cast<TCatalogs*>(mdData[i].get());
		else if(md_name == md_Documents)
			CurCat = dynamic_cast<TDocuments*>(mdData[i].get());
		else if(md_name == md_DocumentJournals)
			CurCat = dynamic_cast<TJournals*>(mdData[i].get());
		else if(md_name == md_Enums)
			CurCat = dynamic_cast<TEnums*>(mdData[i].get());
		else if(md_name == md_Reports)
			CurCat = dynamic_cast<TReports*>(mdData[i].get());
		else if(md_name == md_DataProcessors)
			CurCat = dynamic_cast<TDataProcessors*>(mdData[i].get());
		else if(md_name == md_ChartsOfCharacteristicTypes)
			CurCat = dynamic_cast<TChartOfCharacteristicTypes*>(mdData[i].get());
		if (!CurCat) continue;

		PVirtualNode childNode = tree1C->AddChild(parentNode);
		VirtualTreeData *childData = (VirtualTreeData*)tree1C->GetNodeData(childNode);
	}
}


void TMainForm::FillTreeMD(PVirtualNode parentNode, const MetadataVector<MetadataEntity>& mdData, const String& md_name, int imgIndex)
{
static const std::unordered_set<String> catalogTypes = {md_Catalogs, md_Documents, md_Reports, md_DataProcessors, md_ChartsOfCharacteristicTypes, md_ChartOfCalculationTypes, md_BusinessProcesses, md_Tasks};
    static const std::unordered_set<String> journalTypes = {md_DocumentJournals};
    static const std::unordered_set<String> chartAccTypes = {md_ChartOfAccounts};
    static const std::unordered_set<String> informationRegisterTypes = {md_InformationRegisters, md_AccumulationRegisters, md_AccountingRegisters, md_CalculationRegisters};
    static const std::unordered_set<String> exchangePlanTypes = {md_ExchangePlans};
	for(size_t i = 0; i < mdData.size(); i++)
	{
		PVirtualNode childNode = VirtualStringTreeValue1C->AddChild(parentNode);
		VirtualTreeData *childData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNode);

        if (catalogTypes.count(md_name))
        {
			BaseMetadataObject* metadataObject = dynamic_cast<BaseMetadataObject*>(mdData[i].get());
			if (metadataObject)
				::fillCatalogsTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, metadataObject);
		}
        else if (journalTypes.count(md_name))
        {
            if (md_name == md_DocumentJournals)
            {
                TJournals* CurCat = dynamic_cast<TJournals*>(mdData[i].get());
                if (CurCat) ::fillJournalTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
            }
		}
		else if (chartAccTypes.count(md_name))
        {
            if (md_name == md_ChartOfAccounts)
            {
                TChartOfAccounts* CurCat = dynamic_cast<TChartOfAccounts*>(mdData[i].get());
                if (CurCat) ::fillChartAccTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
            }
        }
        else if (informationRegisterTypes.count(md_name))
        {
            if (md_name == md_InformationRegisters)
            {
                TInformationRegisters* CurCat = dynamic_cast<TInformationRegisters*>(mdData[i].get());
                if (CurCat) ::fillInformationRegisterTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
            }
            else if (md_name == md_AccumulationRegisters)
            {
                TAccumulationRegisters* CurCat = dynamic_cast<TAccumulationRegisters*>(mdData[i].get());
                if (CurCat) ::fillAccumulationRegisterTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
            }
            else if (md_name == md_AccountingRegisters)
            {
                TAccountingRegisters* CurCat = dynamic_cast<TAccountingRegisters*>(mdData[i].get());
                if (CurCat) ::fillAccountingRegisterTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
            }
            else if (md_name == md_CalculationRegisters)
            {
                TCalculationRegisters* CurCat = dynamic_cast<TCalculationRegisters*>(mdData[i].get());
                if (CurCat) ::fillCalculationRegisterTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
            }
        }
        else if (exchangePlanTypes.count(md_name))
        {
            TExchangePlans* CurCat = dynamic_cast<TExchangePlans*>(mdData[i].get());
            if (CurCat) ::fillCatalogsTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
        }
        else if (md_name == md_FilterCriteria)
        {
            BaseMetadataObject* metadataObject = dynamic_cast<BaseMetadataObject*>(mdData[i].get());
            if (metadataObject) ::fillFormsCommandsTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, metadataObject);
        }
        else if (md_name == md_Enums)
        {
            TEnums* CurCat = dynamic_cast<TEnums*>(mdData[i].get());
            if (CurCat) ::fillEnumTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
		}
		else if (md_name == md_ExternalDataSources)
		{
			TExternalDataSources* CurCat = dynamic_cast<TExternalDataSources*>(mdData[i].get());
			if (CurCat) ::fillExternalDataSourceTree(VirtualStringTreeValue1C, childNode, childData, imgIndex, CurCat);
		}
        else
        {
            if (md_name == md_DocumentNumerators)
            {
                TNumerators* CurCat = dynamic_cast<TNumerators*>(mdData[i].get());
                if (CurCat) initNode(childData, CurCat->name, imgIndex);
			}
			else if (md_name == md_Sequences)
			{
				TSequences* CurCat = dynamic_cast<TSequences*>(mdData[i].get());
                if (CurCat) initNode(childData, CurCat->name, imgIndex);
			}
		}
	}
}

void TMainForm::FillVirtualTree() {
    // Добавление команд и форм плана обмена
    PVirtualNode exchangePlansNode = VirtualStringTreeValue1C->AddChild(nullptr);
    VirtualTreeData *exchangePlansData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(exchangePlansNode);
    initNode(exchangePlansData, L"Планы обмена", 41, 25);
    VirtualStringTreeValue1C->Expanded[exchangePlansNode] = true;

	struct CategoryData
	{
		const MetadataVector<MetadataEntity>* data;
		const String name;
		int imgIndex;
		int age;
	};

	std::vector<CategoryData> md_categories = {
		{&MainForm->mdCommonss,                    md_Common,                      84,  25},
		{&MainForm->mdConstants,                   md_Constants,                   0,   25},
		{&MainForm->mdCatalogs,                    md_Catalogs,                    1,   25},
		{&MainForm->mdDocuments,                   md_Documents,                   4,   25},
		{&MainForm->mdDocumentJournals,            md_DocumentJournals,            5,   25},
		{&MainForm->mdEnums,                       md_Enums,                       2,   25},
		{&MainForm->mdReports,                     md_Reports,                     9,   25},
		{&MainForm->mdDataProcessors,              md_DataProcessors,              7,   25},
		{&MainForm->mdChartsOfCharacteristicTypes, md_ChartsOfCharacteristicTypes, 16,  25},
		{&MainForm->mdChartOfAccounts,             md_ChartOfAccounts,             116, 25},
		{&MainForm->mdChartOfCalculationTypes,     md_ChartOfCalculationTypes,     17,  25},
		{&MainForm->mdInformationRegisters,        md_InformationRegisters,        14,  25},
		{&MainForm->mdAccumulationRegisters,       md_AccumulationRegisters,       13,  25},
		{&MainForm->mdAccountingRegisters,         md_AccountingRegisters,         117, 25},
		{&MainForm->mdCalculationRegisters,        md_CalculationRegisters,        18,  25},
		{&MainForm->mdBusinessProcesses,           md_BusinessProcesses,           58,  25},
		{&MainForm->mdTasks,                       md_Tasks,                       59,  25},
		{&MainForm->mdExternalDataSources,         md_ExternalDataSources,         27,  25}
	};

	std::vector<CategoryData> md_categoriesCommon = {
		{&MainForm->mdSubsystems,                  md_Subsystems,                      74,  25},
		{&MainForm->mdCommonModules,               md_CommonModules,                   87,  25},
		{&MainForm->mdSessionParameters,           md_SessionParameters,               90,  25},
		{&MainForm->mdRoles,                       md_Roles,                           81,  25},
		{&MainForm->mdCommonAttributes,            md_CommonAttributes,                24,  25},
		{&MainForm->mdExchangePlans,               md_ExchangePlans,                   41,  25},
		{&MainForm->mdFilterCriteria,              md_FilterCriteria,                  85,  25},
		{&MainForm->mdEventSubscriptions,          md_EventSubscriptions,              100, 25},
		{&MainForm->mdScheduledJobs,               md_ScheduledJobs,                   104, 25},
		{&MainForm->mdBots,                        md_Bots,                            132, 25},
		{&MainForm->mdFunctionalOptions,           md_FunctionalOptions,               108, 25},
		{&MainForm->mdFunctionalOptionsParameters, md_FunctionalOptionsParameters,     109, 25},
		{&MainForm->mdDefinedTypes,                md_DefinedTypes,                    111, 25},
		{&MainForm->mdSettingsStorages,            md_SettingsStorages,                52,  25},
		{&MainForm->mdCommonCommands,              md_CommonCommands,                  98,  25},
		{&MainForm->mdCommonTemplates,             md_CommonTemplates,                 79,  25},
		{&MainForm->mdCommandGroups,               md_CommandGroups,                   99,  25},
		{&MainForm->mdCommonForms,                 md_CommonForms,                     86,  25},
		{&MainForm->mdInterfaces,                  md_Interfaces,                      80,  25},
		{&MainForm->mdCommonPictures,              md_CommonPictures,                  77,  25},
		{&MainForm->mdXDTOPackages,                md_XDTOPackages,                    91,  25},
		{&MainForm->mdWebServices,                 md_WebServices,                     92,  25},
		{&MainForm->mdHTTPServices,                md_HTTPServices,                    113, 25},
		{&MainForm->mdWSReferences,                md_WSReferences,                   96,  25},
		{&MainForm->mdWebSocketClients,            md_WebSocketClients,                96,  25},
		{&MainForm->mdIntegrationServices,         md_IntegrationServices,             131, 25},
		{&MainForm->mdStyleItems,                  md_StyleItems,                      76,  25},
		{&MainForm->mdStyles,                      md_Styles,                          75,  25},
		{&MainForm->mdLanguages,                   md_Languages,                       73,  25}
	};



	// Создаем корневой узел
	VirtualStringTreeValue1C->Clear();
	LastModuleNodeShown = nullptr;
	PVirtualNode RootNode = VirtualStringTreeValue1C->AddChild(nullptr);


	VirtualTreeData *RootData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(RootNode);

	// Обработка каждой категории
	for (const auto& category : md_categories)
	{
		PVirtualNode parentNode = VirtualStringTreeValue1C->AddChild(RootNode);
		VirtualTreeData *parentNodeData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(parentNode);

		parentNodeData->Name = category.name;
		parentNodeData->Age = category.age;
		parentNodeData->ImgIndex = category.imgIndex;

		if (category.name == "Общие")
		{
			std::unordered_set<String> nestedSubsystemGuids = collectChildSubsystemGuids(MainForm->GlobalCF.get(), MainForm->mdSubsystems);

			for (const auto& categoryCom : md_categoriesCommon)
			{
				PVirtualNode parentNodeCom = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *parentNodeDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(parentNodeCom);

				parentNodeDataCom->Name = categoryCom.name;
				parentNodeDataCom->Age = categoryCom.age;
				parentNodeDataCom->ImgIndex = categoryCom.imgIndex;
				if (categoryCom.name == md_Subsystems || categoryCom.name == md_ExchangePlans || categoryCom.name == md_FilterCriteria)
					VirtualStringTreeValue1C->Expanded[parentNodeCom] = true;

				for (const auto& item : *categoryCom.data)
				{
					BaseMetadataObject* mdObj = dynamic_cast<BaseMetadataObject*>(item.get());
					if (!mdObj) continue;

					if (categoryCom.name == md_Subsystems)
					{
						TSubsystem* CurSubsystem = static_cast<TSubsystem*>(mdObj);
						String subsystemFileGuid = normalizeGuid(CurSubsystem->guid);
						String originalGuid = CurSubsystem->guid;
						String subsystemInnerGuid = normalizeGuid(GetSubsystemInnerGuid(MainForm->GlobalCF.get(), originalGuid));
						if (nestedSubsystemGuids.count(subsystemFileGuid) || nestedSubsystemGuids.count(subsystemInnerGuid))
							continue;
					}

					PVirtualNode childNodeCom = VirtualStringTreeValue1C->AddChild(parentNodeCom);
					VirtualTreeData *childDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeCom);

					childDataCom->Name = mdObj->GetName();
					childDataCom->Age = 99;
					childDataCom->ImgIndex = categoryCom.imgIndex;
					childDataCom->text_module = L"";
					childDataCom->MetadataObject = mdObj;

					if (categoryCom.name == md_ExchangePlans || categoryCom.name == md_FilterCriteria)
					{
						BaseMetadataObject* metadataObject = dynamic_cast<BaseMetadataObject*>(mdObj);
						if (metadataObject)
						{
							if (categoryCom.name == md_FilterCriteria)
								::fillFormsCommandsTree(VirtualStringTreeValue1C, childNodeCom, childDataCom, categoryCom.imgIndex, metadataObject);
							else
								::fillCatalogsTree(VirtualStringTreeValue1C, childNodeCom, childDataCom, categoryCom.imgIndex, metadataObject);
							VirtualStringTreeValue1C->Expanded[childNodeCom] = true;
						}
					}

					if (categoryCom.name == md_Subsystems)
					{
						TSubsystem* CurSubsystem = static_cast<TSubsystem*>(mdObj);
						VirtualStringTreeValue1C->Expanded[childNodeCom] = true;
						addSubsystemChildrenToTree(VirtualStringTreeValue1C, childNodeCom, MainForm->GlobalCF.get(), MainForm->mdSubsystems, CurSubsystem, categoryCom.imgIndex);
					}
				}
			}
		}

		if(category.name == md_Catalogs)
		{
			FillTreeMD(parentNode, MainForm->mdCatalogs, md_Catalogs, category.imgIndex);
		}
		else if(category.name == md_Documents)
		{
			if (parentNode->ChildCount == 0)
			{
				PVirtualNode childNodeNum = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *childDataNum = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeNum);
				childDataNum->Name = md_DocumentNumerators;
				childDataNum->Age = 30;
				childDataNum->ImgIndex = 8;

				FillTreeMD(childNodeNum, MainForm->mdDocumentNumerators, md_DocumentNumerators, 8);

				PVirtualNode childNodeSeq = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *childDataSeq = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeSeq);
				childDataSeq->Name = md_Sequences;
				childDataSeq->Age = 30;
				childDataSeq->ImgIndex = 12;

				FillTreeMD(childNodeSeq, MainForm->mdSequences,          md_Sequences,          12);
			}
			FillTreeMD(parentNode, MainForm->mdDocuments, md_Documents, category.imgIndex);
		}
		else if(category.name == md_Reports)
		{
			FillTreeMD(parentNode, MainForm->mdReports, md_Reports, category.imgIndex);
		}
		else if(category.name == md_DataProcessors)
		{
			FillTreeMD(parentNode, MainForm->mdDataProcessors, md_DataProcessors, category.imgIndex);
		}
		else if(category.name == md_ChartsOfCharacteristicTypes)
		{
			FillTreeMD(parentNode, MainForm->mdChartsOfCharacteristicTypes, md_ChartsOfCharacteristicTypes, category.imgIndex);
		}
		else if(category.name == md_BusinessProcesses)
		{
			FillTreeMD(parentNode, MainForm->mdBusinessProcesses, md_BusinessProcesses, category.imgIndex);
		}
		else if(category.name == md_Tasks)
		{
			FillTreeMD(parentNode, MainForm->mdTasks, md_Tasks, category.imgIndex);
		}
		else if (category.name == md_DocumentJournals)
		{
			FillTreeMD(parentNode, MainForm->mdDocumentJournals, md_DocumentJournals, category.imgIndex);
		}
		else if (category.name == md_Enums)
		{
			FillTreeMD(parentNode, MainForm->mdEnums, md_Enums, category.imgIndex);
		}
        else if (category.name == md_ChartOfAccounts)
		{
			FillTreeMD(parentNode, MainForm->mdChartOfAccounts, md_ChartOfAccounts, category.imgIndex);
		}
		else if (category.name == md_ChartOfCalculationTypes)
		{
			FillTreeMD(parentNode, MainForm->mdChartOfCalculationTypes, md_ChartOfCalculationTypes, category.imgIndex);
		}
		else if (category.name == md_AccumulationRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdAccumulationRegisters, md_AccumulationRegisters, category.imgIndex);
		}
		else if (category.name == md_AccountingRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdAccountingRegisters, md_AccountingRegisters, category.imgIndex);
		}
		else if (category.name == md_CalculationRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdCalculationRegisters, md_CalculationRegisters, category.imgIndex);
		}
		else if (category.name == md_Constants)
		{
			for (size_t i = 0; i < MainForm->mdConstants.size(); i++)
			{
				PVirtualNode childNodeConst = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *childDataConst = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeConst);
				TConstants* CurConstant = static_cast<TConstants*>(MainForm->mdConstants[i].get());
				childDataConst->Name = CurConstant->name;
				childDataConst->Age = 30;
				childDataConst->ImgIndex = category.imgIndex;
				childDataConst->MetadataObject = CurConstant;
				childDataConst->text_module = L"";
			}
		}
		else if (category.name == md_InformationRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdInformationRegisters, md_InformationRegisters, category.imgIndex);
		}
		else if (category.name == md_ExchangePlans)
		{
			FillTreeMD(parentNode, MainForm->mdExchangePlans, md_ExchangePlans, category.imgIndex);
		}
		else if (category.name == md_FilterCriteria)
		{
			FillTreeMD(parentNode, MainForm->mdFilterCriteria, md_FilterCriteria, category.imgIndex);
		}
		else if (category.name == md_ExternalDataSources)
		{
			FillTreeMD(parentNode, MainForm->mdExternalDataSources, md_ExternalDataSources, category.imgIndex);
		}

	}

	VirtualStringTreeValue1C->Expanded[RootNode] = true;
	RootData->Name = MainForm->ConfigName;
	RootData->Age = 100;
	RootData->ImgIndex = 72;

}


void TMainForm::TreeInit()
{
	// Заготовка
}



void __fastcall TMainForm::VirtualStringTreeValue1CFreeNode(TBaseVirtualTree *Sender, PVirtualNode Node)
{
	VirtualTreeData *NodeData =(VirtualTreeData*)Sender->GetNodeData(Node);
	NodeData->Name = L"";
	NodeData->text_module = L"";
	NodeData->MetadataObject = nullptr;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CGetImageIndex(TBaseVirtualTree *Sender, PVirtualNode Node, TVTImageKind Kind,
		  TColumnIndex Column, bool &Ghosted, TImageIndex &ImageIndex)
{
	VirtualTreeData *NodeRec = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(Node);
	if (Kind != ikState)
	{
		ImageIndex = NodeRec->ImgIndex;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	if (dlgOpenCatalog->Execute())
	{
		//editFolderName->Text = dlgOpenCatalog->FileName;
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionFileOpenExecute(TObject *Sender)
{
	ULONGLONG loadStartTick = 0;
	ULONGLONG loadEndTick = 0;
	ULONGLONG loadDurationMs = 0;

	if (!dlgOpenCF->Execute())
		return;

	if (!FileExists(dlgOpenCF->FileName))
		throw(Exception("File does not exist."));

	String filename = dlgOpenCF->FileName;
	EditNameCF->Text = filename;
	loadStartTick = GetTickCount64();
	ResetLoadProgress(38, L"Подготовка к загрузке конфигурации...");
	AddConditionalInfoMessage(mess, L"ActionFileOpenExecute: начало открытия конфигурации");
	AddConditionalInfoMessageParams(mess, L"ActionFileOpenExecute: параметры открытия",
		L"file", filename,
		L"logfile", mess->getFileLoggingEnabled() ? mess->getlogfile() : L"disabled");

	try
	{
		AdvanceLoadProgress(L"Очистка предыдущих данных...");
		GlobalCF.reset();

		mdCatalogs.clear();
		mdLanguages.clear();
		mdAccumulationRegisters.clear();
		mdAccountingRegisters.clear();
		mdCalculationRegisters.clear();
		mdBusinessProcesses.clear();
		mdChartsOfCharacteristicTypes.clear();
		mdCommandGroups.clear();
		mdCommonAttributes.clear();
		mdCommonCommands.clear();
		mdCommonTemplates.clear();
		mdCommonForms.clear();
		mdCommonModules.clear();
		mdCommonPictures.clear();
		mdConstants.clear();
		mdDataProcessors.clear();
		mdDefinedTypes.clear();
		mdDocumentJournals.clear();
		mdDocumentNumerators.clear();
		mdDocuments.clear();
		mdEnums.clear();
		mdEventSubscriptions.clear();
		mdExchangePlans.clear();
		mdChartOfAccounts.clear();
		mdChartOfCalculationTypes.clear();
		mdExternalDataSources.clear();
		mdFilterCriteria.clear();
		mdFunctionalOptions.clear();
		mdFunctionalOptionsParameters.clear();
		mdHTTPServices.clear();
		mdInformationRegisters.clear();
		mdInterfaces.clear();
		mdReports.clear();
		mdRoles.clear();
		mdBots.clear();
		mdScheduledJobs.clear();
		mdSessionParameters.clear();
		mdSettingsStorages.clear();
		mdStyleItems.clear();
		mdStyles.clear();
		mdSubsystems.clear();
		mdTasks.clear();
		mdWebServices.clear();
		mdWSReferences.clear();
		mdWebSocketClients.clear();
		mdXDTOPackages.clear();
		mdIntegrationServices.clear();
		mdSequences.clear();

		AddConditionalInfoMessage(mess, L"ActionFileOpenExecute: создание v8catalog");
		AdvanceLoadProgress(L"Открытие файла конфигурации...");
		GlobalCF = std::make_unique<v8catalog>(filename, true);

		AddConditionalInfoMessage(mess, L"ActionFileOpenExecute: чтение метаданных конфигурации");
		AdvanceLoadProgress(L"Чтение метаданных конфигурации...");
		get_cf_name(GlobalCF.get(), mess);

		AddConditionalInfoMessage(mess, L"ActionFileOpenExecute: построение дерева интерфейса");
		AdvanceLoadProgress(L"Построение дерева метаданных...");

		const String sourceCfDir = TPath::Combine(ExtractFilePath(ParamStr(0)), L"SourceCF");

		if (UnpackCheckBox->Checked)
			StartConfigUnpackThread(EditNameCF->Text, sourceCfDir);

		VirtualStringTreeValue1C->BeginUpdate();
		try
		{
			FillVirtualTree();
		}
		__finally
		{
			VirtualStringTreeValue1C->EndUpdate();
		}

		loadEndTick = GetTickCount64();
		loadDurationMs = loadEndTick - loadStartTick;
		String loadDurationMsStr = IntToStr((__int64)loadDurationMs);
		String loadDurationSecStr = FormatFloat(L"0.000", (double)loadDurationMs / 1000.0);
		CompleteLoadProgress(L"Загрузка завершена");
		mess->Status(L"Время загрузки конфигурации: " + loadDurationMsStr + L" мс (" + loadDurationSecStr + L" сек)");
		AddConditionalInfoMessageParams(mess, L"Детали загрузки конфигурации",
			L"file", filename,
			L"duration_ms", loadDurationMsStr,
			L"duration_sec", loadDurationSecStr);
		if (mess->getUiMessagesEnabled() && IsVerboseUiLoggingEnabled())
			mess->AddMessage(L"ActionFileOpenExecute: конфигурация успешно открыта", msSuccesfull);
	}
	catch (const Exception &e)
	{
		LoadProgressBar->Visible = false;
		if (mess->getUiMessagesEnabled())
			mess->AddMessage_(L"ActionFileOpenExecute: VCL exception", msError,
				L"file", filename,
				L"message", e.Message);
		throw;
	}
	catch (...)
	{
		LoadProgressBar->Visible = false;
		if (mess->getUiMessagesEnabled())
			mess->AddMessage_(L"ActionFileOpenExecute: неизвестное исключение", msError,
				L"file", filename,
				L"stage", L"open configuration");
		throw;
	}
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ActionOpenCFExecute(TObject *Sender)
{
	TMainForm::ActionFileOpenExecute(Sender);
}

//---------------------------------------------------------------------------
//                           Messager
//---------------------------------------------------------------------------
Messager::Messager(TListView* lv, TStatusBar* sb)
{
	ListView = lv;
	StatusBar = sb;
	uiMessagesEnabled = true;
	fileLoggingEnabled = false;
	FormatSettings.DateSeparator = L'.';
	FormatSettings.TimeSeparator = L':';
	FormatSettings.ShortDateFormat = L"dd.mm.yyyy";
	FormatSettings.LongTimeFormat = L"hh:mm:ss:zzz";
}

void Messager::setUiMessagesEnabled(bool enabled)
{
	uiMessagesEnabled = enabled;
}

bool Messager::getUiMessagesEnabled() const
{
	return uiMessagesEnabled;
}

void Messager::setFileLoggingEnabled(bool enabled)
{
	fileLoggingEnabled = enabled;
	if (!fileLoggingEnabled)
		logfile = L"";
}

bool Messager::getFileLoggingEnabled() const
{
	return fileLoggingEnabled;
}

//---------------------------------------------------------------------------
void Messager::setlogfile(String _logfile)
{
	if(!fileLoggingEnabled)
	{
		logfile = L"";
		return;
	}
	logfile = System::Ioutils::TPath::GetFullPath(_logfile);
	if(FileExists(logfile))
    	DeleteFile(logfile);
}

String Messager::getlogfile() const
{
	return logfile;
}


//---------------------------------------------------------------------------
void Messager::StatusCore(const Utf16String& message)
{
	StatusBar->SimpleText = v8reader::vcl_bridge::Utf16ToString(message);
	StatusBar->Update();
}

//---------------------------------------------------------------------------
void Messager::AddMessageCore(const Utf16String& message, const MessageState mstate, const MessageParams* param)
{
	TFileStream* log = NULL;
	TStreamWriter* sw;
	String s;
	String messageText = v8reader::vcl_bridge::Utf16ToString(message);
	const bool verboseInfo = (mstate == msInfo && !IsVerboseUiLoggingEnabled());

	if (uiMessagesEnabled && !verboseInfo)
	{
		TStringList* listParams = nullptr;
		if (param && !param->empty())
		{
			listParams = new TStringList;
			for (const auto& entry : *param)
			{
				listParams->Add(
					v8reader::vcl_bridge::Utf16ToString(entry.first) +
					L" = " +
					v8reader::vcl_bridge::Utf16ToString(entry.second));
			}
		}
		ListView->AddItem(messageText, listParams);
		TListItem* item = ListView->Items->Item[ListView->Items->Count - 1];
		item->StateIndex = mstate;
		ListView->Selected = item;
		ListView->Scroll(0, 0xfffffff);
		ListView->Update();
	}

	if(fileLoggingEnabled && logfile.Length())
	{
		if(FileExists(logfile))
		{
			log = new TFileStream(logfile, fmOpenReadWrite | fmShareDenyNone);
			log->Seek(0, soFromEnd);
		}
		else
		{
			log = new TFileStream(logfile, fmCreate | fmShareDenyNone);
			DynamicArray<System::Byte> preamble = TEncoding::UTF8->GetPreamble();
			if (preamble.Length > 0)
				log->WriteBuffer(&preamble[0], preamble.Length);
		}
		sw = new TStreamWriter(log, TEncoding::UTF8, 4096);
		sw->Write(DateTimeToStr(Now(), FormatSettings));
		s = L" ";
        sw->Write(s);
		switch(mstate)
		{
			case msEmpty:      s = L"<>";        break;
			case msSuccesfull: s = L"<ok>";      break;
			case msWarning:    s = L"<warning>"; break;
			case msInfo:       s = L"<info>";    break;
			case msError:      s = L"<error>";   break;
			case msWait:       s = L"<wait>";    break;
			case msHint:       s = L"<hint>";    break;
			default:           s = L"<>";
		}
		sw->Write(s);
		s = L" ";
        sw->Write(s);
		sw->Write(messageText);
		if(param)
        {
			for (const auto& entry : *param)
            {
                s = L"\r\n\t";
                sw->Write(s);
				sw->Write(v8reader::vcl_bridge::Utf16ToString(entry.first));
				s = L" = ";
				sw->Write(s);
				sw->Write(v8reader::vcl_bridge::Utf16ToString(entry.second));
            }
        }
		s = L"\r\n\r\n";
        sw->Write(s);

		delete sw;
		delete log;
	}

}

static void get_cf_name(v8catalog* cf, Messager* mess)
{
	std::unique_ptr<tree> tr;
	tree* node;
	v8catalog* cat;
	v8file* filedata;
	String meta;
	String s;
	int ver;

	if(!cf)
	{
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка открытия файла");
		return;
	}

	filedata = cf->GetFile(L"version");
	if(!filedata)
	{
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка получения файла root конфигурации");
		return;
	}

	tr.reset(get_treeFromV8file(filedata));
	if(!tr)
	{
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка разбора файла root конфигурации");
		return;
	}

	node = tr.get();

	node = &(*node)[0][0][0];
	if(node->get_type() != nd_number)
	{
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка получения версии формата конфигурации");
		return;
	}

	ver = node->get_value().ToInt();
	tr.reset();

	if(ver < 100)
	{
		// 8.0
		filedata = cf->GetFile(L"metadata");
		if(!filedata)
		{
			if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка получения файла metadata конфигурации");
			return;
		}

		cat = filedata->GetCatalog();
		if(!cat)
		{
			if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка открытия файла metadata конфигурации");
			return;
		}

	}
	else
	{
		//8.1 или 8.2
		cat = cf;
	}

	filedata = cat->GetFile(L"root");
	if(!filedata)
	{
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка получения файла root конфигурации");
		return;
	}

	tr.reset(get_treeFromV8file(filedata));
	if(!tr)
	{
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка разбора файла root конфигурации");
		return;
	}

	node = tr.get();
	node = &(*node)[0][1];

	if(node->get_type() != nd_guid)
	{
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(L"Ошибка получения имени файла метаданных");
		return;
	}

	meta = node->get_value();
	tr.reset();

	filedata = cat->GetFile(meta);
	if(!filedata)
	{
		s = L"Ошибка получения файла ";
		s += meta;
		s += L" конфигурации";
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(s);
		return;
	}

	tr.reset(get_treeFromV8file(filedata));
	if(!tr)
	{
		s = L"Ошибка разбора файла ";
		s += meta;
		s += L" конфигурации";
		if (mess && mess->getUiMessagesEnabled()) mess->AddError(s);
		return;
	}

	get_cf_name(tr.release(), mess);
}

void fill_subsystem(tree* tr, std::vector<SubSys> &md_subsys)
{
	v8file *filedata;
	tree* tree_md;
	tree* node;
	tree* node_children;
	String s = "";

	String guid_md = GUID_Subsystems;

	v8catalog *cf = MainForm->GlobalCF.get();

	tree* node_md = find_metadata_node_by_guid(tr, guid_md);

	int CountMD = (node_md->get_next())->get_value().ToInt();

	md_subsys.clear();

	tree* curNode = node_md->get_next();

	while (curNode)
	{
		curNode = curNode->get_next();
		if (curNode)
		{
			s = curNode->get_value();
			String val = GetNameSubsystem(cf, s); // имя подсистемы

			std::vector<String> children;

			GetListChildrenSubsystem(cf, s, children);

			md_subsys.push_back( {val, children} );
		}
	}
}

namespace
{
	tree* GetNodeByPathSafe(tree* startNode, const std::vector<int>& path)
	{
		tree* currentNode = startNode;
		if (!currentNode)
			return nullptr;

		for (size_t i = 0; i < path.size(); i++)
		{
			int idx = path[i];
			if (idx < 0 || idx >= currentNode->get_num_subnode())
				return nullptr;

			currentNode = currentNode->get_subnode(idx);
			if (!currentNode)
				return nullptr;
		}

		return currentNode;
	}

	void AddUniqueGuid(std::vector<String>& guids, const String& guid)
	{
		if (guid.IsEmpty())
			return;

		for (const auto& existingGuid : guids)
		{
			if (existingGuid.CompareIC(guid) == 0)
				return;
		}

		guids.push_back(guid);
	}

	void CollectMetadataSectionGuids(tree* node, const String& sectionGuid, std::vector<String>& guids)
	{
		if (!node)
			return;

		if (node->get_type() == nd_list && node->get_num_subnode() >= 2)
		{
			tree* guidNode = node->get_subnode(0);
			tree* countNode = node->get_subnode(1);
			if (guidNode && countNode && guidNode->get_value().CompareIC(sectionGuid) == 0 && countNode->get_type() == nd_number)
			{
				int count = countNode->get_value().ToIntDef(0);
				for (int i = 0; i < count && i + 2 < node->get_num_subnode(); i++)
				{
					tree* itemNode = node->get_subnode(i + 2);
					if (itemNode)
						AddUniqueGuid(guids, itemNode->get_value());
				}
			}
		}

		for (int i = 0; i < node->get_num_subnode(); i++)
			CollectMetadataSectionGuids(node->get_subnode(i), sectionGuid, guids);
	}

	String GetObjectNameByPath(v8catalog* cf, const String& objectGuid, const std::vector<int>& path)
	{
		if (!cf || objectGuid.IsEmpty())
			return L"";

		v8file* filedata = cf->GetFile(objectGuid);
		if (!filedata)
			return L"";

		std::unique_ptr<tree> objectTree(get_treeFromV8file(filedata));
		tree* nameNode = GetNodeByPathSafe(objectTree.get(), path);
		if (nameNode && !nameNode->get_value().IsEmpty())
			return nameNode->get_value();

		std::function<String(tree*)> findWsReferenceName = [&](tree* node) -> String
		{
			if (!node)
				return L"";

			if (node->get_type() == nd_list && node->get_num_subnode() >= 3)
			{
				tree* markerNode = node->get_subnode(0);
				tree* possibleNameNode = node->get_subnode(2);
				if (markerNode && possibleNameNode &&
					(markerNode->get_value() == L"2" || markerNode->get_value() == L"3") &&
					possibleNameNode->get_type() == nd_string &&
					!possibleNameNode->get_value().IsEmpty())
				{
					return possibleNameNode->get_value();
				}
			}

			for (int i = 0; i < node->get_num_subnode(); i++)
			{
				String result = findWsReferenceName(node->get_subnode(i));
				if (!result.IsEmpty())
					return result;
			}

			return L"";
		};

		return findWsReferenceName(objectTree.get());
	}
}


// Процедура заполняет метаданные по корневому гуиду
void fill_md(tree* tr, String guid_md)
{
	v8file *filedata;
	tree* tree_md;
	tree* node;
	String s;

	v8catalog *cf = MainForm->GlobalCF.get();
	msreg->AddMessage(L"fill_md: Начало обработки GUID: " + guid_md, MessageState::msInfo);

	// Карта путей для извлечения имен
	std::unordered_map<String, std::vector<int>> namePaths = {
		{GUID_Catalogs,          {0,1,9,1,2}},
		{GUID_Languages,         {0,1,1,2}},
		{GUID_CommonModules,     {0,1,1,2}},
		{GUID_Roles,             {0,1,1,2}},
		{GUID_CommonTemplates,   {0,1,1,2}},
		{GUID_HTTPServices,      {0,1,2,2}},
		{GUID_ScheduledJobs,     {0,1,1,2}},
		{GUID_CommonAttributes,  {0,1,1,1,1,2}},
		{GUID_SessionParameters, {0,1,1,1,2}},
		{GUID_FunctionalOptionsParameters, {0,1,1,2}},
		{GUID_Subsystems,           {0,1,1,2}},
		{GUID_Interfaces,           {0,1,2,2}},
		{GUID_Styles,               {0,1,1,2}},
		{GUID_FilterCriteria,       {0,1,5,1,2}},
		{GUID_SettingsStorages,     {0,1,1,1,2}},
		{GUID_EventSubscriptions,   {0,1,1,2}},
		{GUID_StyleItems,           {0,1,3,2}},
		{GUID_CommonPictures,       {0,1,1,2}},
		{GUID_ExchangePlans,        {0,1,12,2}},
		{GUID_WebServices,          {0,1,2,2}},
		{GUID_WSReferences,         {1,2,2}},
		{GUID_WebSocketClients,     {0,1,1,2}},
		{GUID_IntegrationServices,  {0,1,1,2}},
		{GUID_FunctionalOptions,    {0,1,1,2}},
		{GUID_DefinedTypes,         {0,1,3,2}},
		{GUID_XDTOPackages,         {0,1,1,2}},
		{GUID_Constants,            {0,1,1,1,1,2}},
		{GUID_Documents,            {0,1,9,1,2}},
		{GUID_InformationRegisters, {0,1,15,1,2}},
		{GUID_CalculationRegisters, {0,1,15,1,2}},
		{GUID_BusinessProcesses,    {0,1,1,2}},
		{GUID_Tasks,                {0,1,1,2}},
		{GUID_AccountingRegisters,  {0,1,16,1,2}},
		{GUID_CommandGroups,        {0,1,6,2}},
		{GUID_CommonCommands,       {0,1,1,2,9,2}},
		{GUID_CommonForms,         {0,1,1,1,2}},
		{GUID_Numerators,           {0,1,1,2}},
		{GUID_JournDocuments,       {0,1,3,1,2}},
		{GUID_Reports,              {0,1,3,1,2}},
		{GUID_ChartOfCharacteristicTypes, {0,1,13,1,2}},
		{GUID_ChartsOfAccounts,           {0,1,15,1,2}},
		{GUID_ChartsOfCalculationTypes,   {0,1,1,1,2}},
		{GUID_AccumulationRegisters,      {0,1,13,1,2}},
		{GUID_Sequences,                  {0,1,7,1,2}},
		{GUID_ExternalDataSources,        {1,1,1,2}},
		{GUID_DataProcessors,             {0,1,3,1,2}},
		{GUID_Enums,                      {0,1,5,1,2}},
		{GUID_DefinedTypes,               {0,1,3,2}},
		{GUID_Bots,                       {0,1,1,2}}
	};

	auto pathIt = namePaths.find(guid_md);

	auto tryGetNodeByPath = [](tree* startNode, const std::vector<int>& candidatePath) -> tree*
	{
		tree* currentNode = startNode;
		if (!currentNode)
			return nullptr;

		for (size_t i = 0; i < candidatePath.size(); i++)
		{
			int idx = candidatePath[i];
			if (idx < 0 || idx >= currentNode->get_num_subnode())
				return nullptr;

			currentNode = currentNode->get_subnode(idx);
			if (!currentNode)
				return nullptr;
		}

		return currentNode;
	};

	if (pathIt == namePaths.end()) {
		// GUID не найден в карте путей, пропустить
		msreg->AddMessage(L"fill_md: GUID не найден в карте путей: " + guid_md, MessageState::msWarning);
		return;
	}

	msreg->AddMessage(L"fill_md: Поиск узла по GUID", MessageState::msInfo);
	tree* node_md = find_metadata_node_by_guid(tr, guid_md);
	if (!node_md) {
		msreg->AddMessage(L"fill_md: Узел не найден по GUID: " + guid_md, MessageState::msWarning);
		return; // Защита от nullptr
	}
	msreg->AddMessage(L"fill_md: Узел найден", MessageState::msInfo);

	const std::vector<int>& path = pathIt->second;

	if (guid_md == GUID_WSReferences)
	{
		std::vector<String> referenceGuids;
		CollectMetadataSectionGuids(tr, GUID_WSReferences, referenceGuids);
		msreg->AddMessage(L"fill_md: WS-ссылок найдено структурным поиском: " + String((int)referenceGuids.size()), MessageState::msInfo);

		for (const auto& referenceGuid : referenceGuids)
		{
			String val = GetObjectNameByPath(cf, referenceGuid, path);
			if (val.IsEmpty())
				val = referenceGuid;

			msreg->AddMessage(L"fill_md: Создание WS-ссылки: " + val, MessageState::msInfo);
			MainForm->mdWSReferences.push_back(std::make_unique<TWSReferences>(cf, referenceGuid, val));
		}

		return;
	}

	msreg->AddMessage(L"fill_md: Получение количества элементов", MessageState::msInfo);
	tree* nextNode = node_md->get_next();
	if (!nextNode) {
		msreg->AddMessage(L"fill_md: Ошибка - следующий узел равен null", MessageState::msError);
		return;
	}
	int CountMD = nextNode->get_value().ToInt();
	msreg->AddMessage(L"fill_md: Количество элементов: " + String(CountMD), MessageState::msInfo);

	if (guid_md == GUID_ExternalDataSources)
	{
		tree* sourceNode = node_md->get_next();
		int processedExternalCount = 0;
		while (sourceNode)
		{
			sourceNode = sourceNode->get_next();
			if (!sourceNode)
				continue;

			processedExternalCount++;
			String sourceGuid = sourceNode->get_value();
			msreg->AddMessage(L"fill_md: Создание внешнего источника данных из списка GUID: " + sourceGuid, MessageState::msInfo);
			MainForm->mdExternalDataSources.push_back(std::make_unique<TExternalDataSources>(cf, sourceGuid));
		}
		msreg->AddMessage(L"fill_md: Внешних источников данных создано: " + String((int)MainForm->mdExternalDataSources.size()), MessageState::msInfo);
		return;
	}

	//md_list.clear();

	tree* curNode = node_md->get_next();
	int processedCount = 0;
	while (curNode)
	{
		curNode = curNode->get_next();
		if (curNode)
		{
			processedCount++;
			String curNodeValue = curNode->get_value();
			msreg->AddMessage(L"fill_md: Обработка элемента " + String(processedCount) + L" из " + String(CountMD) + L", файл: " + curNodeValue, MessageState::msInfo);
			if ((processedCount == 1) || (processedCount % 25 == 0))
				LogHeapStatus(L"fill_md: состояние памяти перед чтением элемента", guid_md, curNodeValue, processedCount, CountMD);

			filedata = cf->GetFile(curNodeValue);
			if(!filedata)
			{
				s = L"Ошибка получения файла ";
				s += curNodeValue;
				s += L" конфигурации";
				msreg->AddMessage(s, MessageState::msError);
				//msreg->AddError(s);
				//return;
				continue; // Продолжить с следующим
			}
			msreg->AddMessage(L"fill_md: Файл получен успешно", MessageState::msInfo);

			msreg->AddMessage(L"fill_md: Разбор дерева файла", MessageState::msInfo);
			try
			{
				tree_md = get_treeFromV8file(filedata);
			}
			catch (const Exception &e)
			{
				msreg->AddMessage_(L"fill_md: VCL exception при разборе дерева файла", msError,
					L"GUID", guid_md,
					L"File", curNodeValue,
					L"Message", e.Message);
				LogHeapStatus(L"fill_md: память при VCL exception разбора файла", guid_md, curNodeValue, processedCount, CountMD);
				continue;
			}
			catch (...)
			{
				msreg->AddMessage_(L"fill_md: неизвестное исключение при разборе дерева файла", msError,
					L"GUID", guid_md,
					L"File", curNodeValue);
				LogHeapStatus(L"fill_md: память при неизвестном exception разбора файла", guid_md, curNodeValue, processedCount, CountMD);
				continue;
			}
			if(!tree_md)
			{
				LogHeapStatus(L"fill_md: память во время ошибки разбора файла", guid_md, curNodeValue, processedCount, CountMD);
				s = L"Ошибка разбора файла ";
				s += curNodeValue;
				s += L" конфигурации";
				msreg->AddMessage(s, MessageState::msError);
				//msreg->AddError(s);
				//return;
				continue;
			}
			msreg->AddMessage(L"fill_md: Дерево разобрано успешно", MessageState::msInfo);

			node = nullptr;
			msreg->AddMessage(L"fill_md: Навигация по пути", MessageState::msInfo);
			try {
				std::vector<std::vector<int>> candidatePaths = {path};

				if (guid_md == GUID_BusinessProcesses || guid_md == GUID_Tasks)
				{
					candidatePaths.push_back({0,1,1});
					candidatePaths.push_back({0,1,2});
				}
				else if (guid_md == GUID_ExternalDataSources)
				{
					candidatePaths.push_back({1,0,1,2});
					candidatePaths.push_back({0,1,1,2});
				}

				for (size_t candidateIndex = 0; candidateIndex < candidatePaths.size() && !node; candidateIndex++)
				{
					const std::vector<int>& candidatePath = candidatePaths[candidateIndex];
					msreg->AddMessage(L"fill_md: Попытка пути #" + String((int)candidateIndex + 1), MessageState::msInfo);
					node = tryGetNodeByPath(tree_md, candidatePath);
				}
			}
			catch (...) {
				msreg->AddMessage(L"fill_md: Исключение при навигации по пути для файла: " + curNodeValue, MessageState::msError);
				LogHeapStatus(L"fill_md: память при исключении навигации", guid_md, curNodeValue, processedCount, CountMD);
				delete tree_md;
				continue;
			}

			if (!node) {
				msreg->AddMessage(L"fill_md: Пропуск элемента из-за null узла: " + curNodeValue, MessageState::msError);
				delete tree_md;
				continue;
			}

			// Проверка типа узла перед получением значения
			msreg->AddMessage(L"fill_md: Тип узла перед получением значения: " + String(node->get_type()), MessageState::msInfo);
			if (node->get_type() == nd_empty || node->get_type() == nd_unknown) {
				msreg->AddMessage(L"fill_md: Пропуск элемента - пустой или неизвестный тип узла: " + curNodeValue + L", тип: " + String(node->get_type()), MessageState::msError);
				delete tree_md;
				continue;
			}

			String val = node->get_value();
			msreg->AddMessage(L"fill_md: Получено значение длиной: " + String(val.Length()), MessageState::msInfo);
			if (val.Length() == 0) {
				if (guid_md == GUID_ExternalDataSources)
				{
					val = curNodeValue;
					msreg->AddMessage(L"fill_md: Имя внешнего источника данных пустое, используется GUID файла: " + val, MessageState::msWarning);
				}
				else
				{
					msreg->AddMessage(L"fill_md: Пропуск элемента - пустое значение: " + curNodeValue, MessageState::msError);
					delete tree_md;
					continue;
				}
			}
			msreg->AddMessage(L"fill_md: Получено имя: " + val, MessageState::msInfo);

			if ((processedCount == 1) || (processedCount % 25 == 0))
				LogHeapStatus(L"fill_md: состояние памяти перед созданием объекта", guid_md, curNodeValue, processedCount, CountMD);

			// Создание объектов для специфических типов
			try {
				if (guid_md == GUID_Catalogs)
				{
					msreg->AddMessage(L"fill_md: Создание справочника: " + val, MessageState::msInfo);
					MainForm->mdCatalogs.push_back(std::make_unique<TCatalogs>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Languages)
				{
					msreg->AddMessage(L"fill_md: Создание языка: " + val, MessageState::msInfo);
					MainForm->mdLanguages.push_back(std::make_unique<TLangs>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_CommonModules)
				{
					msreg->AddMessage(L"fill_md: Создание общего модуля: " + val, MessageState::msInfo);
					MainForm->mdCommonModules.push_back(std::make_unique<TCommonModules>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Roles)
				{
					msreg->AddMessage(L"fill_md: Создание роли: " + val, MessageState::msInfo);
					MainForm->mdRoles.push_back(std::make_unique<TRoles>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_CommonTemplates)
				{
					msreg->AddMessage(L"fill_md: Создание общего макета: " + val, MessageState::msInfo);
					MainForm->mdCommonTemplates.push_back(std::make_unique<TCommonTemplates>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_HTTPServices)
				{
					msreg->AddMessage(L"fill_md: Создание HTTP-сервиса: " + val, MessageState::msInfo);
					MainForm->mdHTTPServices.push_back(std::make_unique<THTTPServices>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_ScheduledJobs)
				{
					msreg->AddMessage(L"fill_md: Создание регламентного задания: " + val, MessageState::msInfo);
					MainForm->mdScheduledJobs.push_back(std::make_unique<TScheduledJobs>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_CommonAttributes)
				{
					msreg->AddMessage(L"fill_md: Создание общего реквизита: " + val, MessageState::msInfo);
					MainForm->mdCommonAttributes.push_back(std::make_unique<TCommonAttributes>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_SessionParameters)
				{
					msreg->AddMessage(L"fill_md: Создание параметра сеанса: " + val, MessageState::msInfo);
					MainForm->mdSessionParameters.push_back(std::make_unique<TSessionParameters>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_FunctionalOptionsParameters)
				{
					msreg->AddMessage(L"fill_md: Создание параметра функциональной опции: " + val, MessageState::msInfo);
					MainForm->mdFunctionalOptionsParameters.push_back(std::make_unique<TFunctionalOptionsParameters>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Subsystems)
				{
					//msreg->AddMessage(L"fill_md: Пропуск подсистемы: " + val, MessageState::msInfo);
					msreg->AddMessage(L"fill_md: Создание подсистемы: " + val, MessageState::msInfo);
					MainForm->mdSubsystems.push_back(std::make_unique<TSubsystem>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Interfaces)
				{
					msreg->AddMessage(L"fill_md: Создание интерфейса: " + val, MessageState::msInfo);
					MainForm->mdInterfaces.push_back(std::make_unique<TInterfaces>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Styles)
				{
					msreg->AddMessage(L"fill_md: Создание стиля: " + val, MessageState::msInfo);
					MainForm->mdStyles.push_back(std::make_unique<TStyles>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_FilterCriteria)
				{
					msreg->AddMessage(L"fill_md: Создание критерия отбора: " + val, MessageState::msInfo);
					MainForm->mdFilterCriteria.push_back(std::make_unique<TFilterCriteria>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_SettingsStorages)
				{
					msreg->AddMessage(L"fill_md: Создание хранилища настроек: " + val, MessageState::msInfo);
					MainForm->mdSettingsStorages.push_back(std::make_unique<TSettingsStorages>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_StyleItems)
				{
					msreg->AddMessage(L"fill_md: Создание элемента стиля: " + val, MessageState::msInfo);
					MainForm->mdStyleItems.push_back(std::make_unique<TStyleItems>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_CommonPictures)
				{
					msreg->AddMessage(L"fill_md: Создание общей картинки: " + val, MessageState::msInfo);
					MainForm->mdCommonPictures.push_back(std::make_unique<TCommonPictures>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_ExchangePlans)
				{
					msreg->AddMessage(L"fill_md: Создание плана обмена: " + val, MessageState::msInfo);
					MainForm->mdExchangePlans.push_back(std::make_unique<TExchangePlans>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_EventSubscriptions)
				{
					msreg->AddMessage(L"fill_md: Создание подписки на событие: " + val, MessageState::msInfo);
					MainForm->mdEventSubscriptions.push_back(std::make_unique<TEventSubscriptions>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_WebServices)
				{
					msreg->AddMessage(L"fill_md: Создание веб-сервиса: " + val, MessageState::msInfo);
					MainForm->mdWebServices.push_back(std::make_unique<TWebServices>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_FunctionalOptions)
				{
					msreg->AddMessage(L"fill_md: Создание функциональной опции: " + val, MessageState::msInfo);
					MainForm->mdFunctionalOptions.push_back(std::make_unique<TFunctionalOptions>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_DefinedTypes)
				{
					msreg->AddMessage(L"fill_md: Создание определяемого типа: " + val, MessageState::msInfo);
					MainForm->mdDefinedTypes.push_back(std::make_unique<TDefinedTypes>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_XDTOPackages)
				{
					msreg->AddMessage(L"fill_md: Создание XDTO-пакета: " + val, MessageState::msInfo);
					MainForm->mdXDTOPackages.push_back(std::make_unique<TXDTOPackages>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_WSReferences)
				{
					msreg->AddMessage(L"fill_md: Создание WS-ссылки: " + val, MessageState::msInfo);
					MainForm->mdWSReferences.push_back(std::make_unique<TWSReferences>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_WebSocketClients)
				{
					msreg->AddMessage(L"fill_md: Создание WebSocket-клиента: " + val, MessageState::msInfo);
					MainForm->mdWebSocketClients.push_back(std::make_unique<TWebSocketClients>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_IntegrationServices)
				{
					msreg->AddMessage(L"fill_md: Создание сервиса интеграции: " + val, MessageState::msInfo);
					MainForm->mdIntegrationServices.push_back(std::make_unique<TIntegrationServices>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Constants)
				{
					msreg->AddMessage(L"fill_md: Создание константы: " + val, MessageState::msInfo);
					MainForm->mdConstants.push_back(std::make_unique<TConstants>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Documents)
				{
					msreg->AddMessage(L"fill_md: Создание документа: " + val, MessageState::msInfo);
					MainForm->mdDocuments.push_back(std::make_unique<TDocuments>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_CommonForms)
				{
					msreg->AddMessage(L"fill_md: Создание общей формы: " + val, MessageState::msInfo);
					MainForm->mdCommonForms.push_back(std::make_unique<TCommonForms>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_InformationRegisters)
				{
					msreg->AddMessage(L"fill_md: Создание регистра сведений: " + val, MessageState::msInfo);
					MainForm->mdInformationRegisters.push_back(std::make_unique<TInformationRegisters>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_CalculationRegisters)
				{
					msreg->AddMessage(L"fill_md: Создание регистра расчета: " + val, MessageState::msInfo);
					MainForm->mdCalculationRegisters.push_back(std::make_unique<TCalculationRegisters>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_BusinessProcesses)
				{
					msreg->AddMessage(L"fill_md: Создание бизнес-процесса: " + val, MessageState::msInfo);
					MainForm->mdBusinessProcesses.push_back(std::make_unique<TBusinessProceses>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Tasks)
				{
					msreg->AddMessage(L"fill_md: Создание задачи: " + val, MessageState::msInfo);
					MainForm->mdTasks.push_back(std::make_unique<TTasks>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_AccountingRegisters)
				{
					msreg->AddMessage(L"fill_md: Создание регистра бухгалтерии: " + val, MessageState::msInfo);
					MainForm->mdAccountingRegisters.push_back(std::make_unique<TAccountingRegisters>(cf, curNode->get_value(), val));
					msreg->AddMessage(L"fill_md: Регистр бухгалтерии создан успешно: " + val, MessageState::msInfo);
				}
				else if (guid_md == GUID_CommandGroups)
				{
					msreg->AddMessage(L"fill_md: Создание группы команд: " + val, MessageState::msInfo);
					MainForm->mdCommandGroups.push_back(std::make_unique<TCommandGroups>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_CommonCommands)
				{
					msreg->AddMessage(L"fill_md: Создание общей команды: " + val, MessageState::msInfo);
					MainForm->mdCommonCommands.push_back(std::make_unique<TCommonCommands>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Numerators)
				{
					msreg->AddMessage(L"fill_md: Создание нумератора: " + val, MessageState::msInfo);
					MainForm->mdDocumentNumerators.push_back(std::make_unique<TNumerators>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_JournDocuments)
				{
					msreg->AddMessage(L"fill_md: Создание журнала документов: " + val, MessageState::msInfo);
					MainForm->mdDocumentJournals.push_back(std::make_unique<TJournals>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Reports)
				{
					msreg->AddMessage(L"fill_md: Создание отчета: " + val, MessageState::msInfo);
					MainForm->mdReports.push_back(std::make_unique<TReports>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_ChartOfCharacteristicTypes)
				{
					msreg->AddMessage(L"fill_md: Создание ПВХ: " + val, MessageState::msInfo);
					MainForm->mdChartsOfCharacteristicTypes.push_back(std::make_unique<TChartOfCharacteristicTypes>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_ChartsOfAccounts)
				{
					msreg->AddMessage(L"fill_md: Создание плана счетов: " + val, MessageState::msInfo);
					MainForm->mdChartOfAccounts.push_back(std::make_unique<TChartOfAccounts>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_ChartsOfCalculationTypes)
				{
					msreg->AddMessage(L"fill_md: Создание ПВР: " + val, MessageState::msInfo);
					MainForm->mdChartOfCalculationTypes.push_back(std::make_unique<TChartOfCalculationTypes>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_AccumulationRegisters)
				{
					msreg->AddMessage(L"fill_md: Создание регистра накопления: " + val, MessageState::msInfo);
					MainForm->mdAccumulationRegisters.push_back(std::make_unique<TAccumulationRegisters>(cf, curNode->get_value(), val));
					msreg->AddMessage(L"fill_md: Регистр накопления создан успешно: " + val, MessageState::msInfo);
				}
				else if (guid_md == GUID_Sequences)
				{
					msreg->AddMessage(L"fill_md: Создание последовательности: " + val, MessageState::msInfo);
					MainForm->mdSequences.push_back(std::make_unique<TSequences>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_DataProcessors)
				{
					msreg->AddMessage(L"fill_md: Создание обработки: " + val, MessageState::msInfo);
					MainForm->mdDataProcessors.push_back(std::make_unique<TDataProcessors>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Enums)
				{
					msreg->AddMessage(L"fill_md: Создание перечисления: " + val, MessageState::msInfo);
					MainForm->mdEnums.push_back(std::make_unique<TEnums>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_Bots)
				{
					msreg->AddMessage(L"fill_md: Создание бота: " + val, MessageState::msInfo);
					MainForm->mdBots.push_back(std::make_unique<TBots>(cf, curNode->get_value(), val));
				}
				else if (guid_md == GUID_ExternalDataSources)
				{
					msreg->AddMessage(L"fill_md: Создание внешнего источника данных: " + val, MessageState::msInfo);
					MainForm->mdExternalDataSources.push_back(std::make_unique<TExternalDataSources>(cf, curNode->get_value(), val));
				}
				else
				{
					msreg->AddMessage(L"fill_md: Неизвестный GUID для объекта: " + val, MessageState::msWarning);
				}
			}
			catch (const Exception &e) {
				msreg->AddMessage_(L"fill_md: VCL exception при создании объекта", msError,
						L"Name", val,
						L"GUID", guid_md,
						L"File", curNodeValue,
						L"Message", e.Message);
				LogHeapStatus(L"fill_md: память при VCL exception создания объекта", guid_md, curNodeValue, processedCount, CountMD);
			}
			catch (...) {
				msreg->AddMessage_(L"fill_md: неизвестное исключение при создании объекта", msError,
						L"Name", val,
						L"GUID", guid_md,
						L"File", curNodeValue);
				LogHeapStatus(L"fill_md: память при неизвестном exception создания объекта", guid_md, curNodeValue, processedCount, CountMD);
			}
			delete tree_md;
			//md_list.push_back(val);
		 }

	 }

}

static void get_cf_name(tree* tr, Messager* mess)
{
	int j, k;
	tree* node;
	tree* node2;
	tree* node3;
	tree* node_Catalogs;
	tree* node_md;
	tree* curNode;
	String cf_synonym;
	String cf_version;
	String s;
	bool ok;
	int structver;
	int offset_name;
	int offset_ver;
	int CountCatalogs;

	node = tr;
	node = &(*node)[0][3][1][1];

	node3 = tr;

	if (MainForm)
		MainForm->AdvanceLoadProgress(L"Обработка справочников...");

        // Заполняем справочники
		if (mess && mess->getUiMessagesEnabled()) mess->AddMessage(L"Начало обработки справочников", MessageState::msInfo);
        fill_md(tr, GUID_Catalogs);
		if (mess && mess->getUiMessagesEnabled()) mess->AddMessage(L"Справочники обработаны", MessageState::msInfo);

        // Заполняем языки
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка языков...");
        mess->AddMessage(L"Начало обработки языков", MessageState::msInfo);
        fill_md(tr, GUID_Languages);
        mess->AddMessage(L"Языки обработаны", MessageState::msInfo);

        // Заполняем регистры накопления
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка регистров накопления...");
        mess->AddMessage(L"Начало обработки регистров накопления", MessageState::msInfo);
        try {
                fill_md(tr, GUID_AccumulationRegisters);
        }
        catch (...) {
				mess->AddMessage(L"Исключение при обработке регистров накопления", MessageState::msError);
        }
        mess->AddMessage(L"Регистры накопления обработаны", MessageState::msInfo);

        // Заполняем регистры бухгалтерии
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка регистров бухгалтерии...");
        mess->AddMessage(L"Начало обработки регистров бухгалтерии", MessageState::msInfo);
        try {
                fill_md(tr, GUID_AccountingRegisters);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке регистров бухгалтерии", MessageState::msError);
        }
        mess->AddMessage(L"Регистры бухгалтерии обработаны", MessageState::msInfo);

        // Заполняем регистры расчета
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка регистров расчета...");
        mess->AddMessage(L"Начало обработки регистров расчета", MessageState::msInfo);
        try {
                fill_md(tr, GUID_CalculationRegisters);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке регистров расчета", MessageState::msError);
        }
        mess->AddMessage(L"Регистры расчета обработаны", MessageState::msInfo);

        // Заполняем бизнес-процессы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка бизнес-процессов...");
        mess->AddMessage(L"Начало обработки бизнес-процессов", MessageState::msInfo);
		try {
                fill_md(tr, GUID_BusinessProcesses);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке бизнес-процессов", MessageState::msError);
        }
        mess->AddMessage(L"Бизнес-процессы обработаны", MessageState::msInfo);

        // ПВХ
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка планов видов характеристик...");
        mess->AddMessage(L"Начало обработки планов видов характеристик", MessageState::msInfo);
        try {
                fill_md(tr, GUID_ChartOfCharacteristicTypes);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке ПВХ", MessageState::msError);
        }
        mess->AddMessage(L"Планы видов характеристик обработаны", MessageState::msInfo);


        // группы команд
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка групп команд...");
        mess->AddMessage(L"Начало обработки групп команд", MessageState::msInfo);
        try {
                fill_md(tr, GUID_CommandGroups);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке групп команд", MessageState::msError);
        }
		mess->AddMessage(L"Группы команд обработаны", MessageState::msInfo);


        // общие реквизиты
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка общих реквизитов...");
        mess->AddMessage(L"Начало обработки общих реквизитов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_CommonAttributes);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке общих реквизитов", MessageState::msError);
        }
        mess->AddMessage(L"Общие реквизиты обработаны", MessageState::msInfo);

        // общие команды
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка общих команд...");
        mess->AddMessage(L"Начало обработки общих команд", MessageState::msInfo);
        try {
                fill_md(tr, GUID_CommonCommands);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке общих команд", MessageState::msError);
        }
        mess->AddMessage(L"Общие команды обработаны", MessageState::msInfo);

        // общие формы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка общих форм...");
        mess->AddMessage(L"Начало обработки общих форм", MessageState::msInfo);
        try {
				fill_md(tr, GUID_CommonForms);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке общих форм", MessageState::msError);
        }
        mess->AddMessage(L"Общие формы обработаны", MessageState::msInfo);

        // общие модули
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка общих модулей...");
        mess->AddMessage(L"Начало обработки общих модулей", MessageState::msInfo);
        try {
                fill_md(tr, GUID_CommonModules);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке общих модулей", MessageState::msError);
        }
        mess->AddMessage(L"Общие модули обработаны", MessageState::msInfo);


        // общие картинки
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка общих картинок...");
        mess->AddMessage(L"Начало обработки общих картинок", MessageState::msInfo);
        try {
                fill_md(tr, GUID_CommonPictures);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке общих картинок", MessageState::msError);
        }
        mess->AddMessage(L"Общие картинки обработаны", MessageState::msInfo);

        // общие макеты
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка общих макетов...");
        mess->AddMessage(L"Начало обработки общих макетов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_CommonTemplates);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке общих макетов", MessageState::msError);
        }
        mess->AddMessage(L"Общие макеты обработаны", MessageState::msInfo);

        // константы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка констант...");
        mess->AddMessage(L"Начало обработки констант", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Constants);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке констант", MessageState::msError);
        }
        mess->AddMessage(L"Константы обработаны: ", MessageState::msInfo);

        // обработки
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка обработок...");
        mess->AddMessage(L"Начало обработки обработок", MessageState::msInfo);
        try {
                fill_md(tr, GUID_DataProcessors);
        }
		catch (...) {
                mess->AddMessage(L"Исключение при обработке обработок", MessageState::msError);
        }
        mess->AddMessage(L"Обработки обработаны", MessageState::msInfo);

        // определяемые типы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка определяемых типов...");
        mess->AddMessage(L"Начало обработки определяемых типов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_DefinedTypes);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке определяемых типов", MessageState::msError);
        }
        mess->AddMessage(L"Определяемые типы обработаны", MessageState::msInfo);

        // журналы документов
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка журналов документов...");
        mess->AddMessage(L"Начало обработки журналов документов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_JournDocuments);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке журналов документов", MessageState::msError);
        }
        mess->AddMessage(L"Журналы документов обработаны", MessageState::msInfo);

        // нумераторы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка нумераторов...");
		mess->AddMessage(L"Начало обработки нумераторов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Numerators);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке нумераторов", MessageState::msError);
        }
        mess->AddMessage(L"Нумераторы обработаны", MessageState::msInfo);

        // документы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка документов...");
        mess->AddMessage(L"Начало обработки документов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Documents);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке документов", MessageState::msError);
        }
        mess->AddMessage(L"Документы обработаны", MessageState::msInfo);

        // перечисления
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка перечислений...");
        mess->AddMessage(L"Начало обработки перечислений", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Enums);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке перечислений", MessageState::msError);
        }
		mess->AddMessage(L"Перечисления обработаны", MessageState::msInfo);

        // подписки на события
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка подписок на события...");
        mess->AddMessage(L"Начало обработки подписок на события", MessageState::msInfo);
        try {
                fill_md(tr, GUID_EventSubscriptions);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке подписок на события", MessageState::msError);
        }
        mess->AddMessage(L"Подписки на события обработаны", MessageState::msInfo);

        // планы обмена
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка планов обмена...");
        mess->AddMessage(L"Начало обработки планов обмена", MessageState::msInfo);
        try {
                fill_md(tr, GUID_ExchangePlans);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке планов обмена", MessageState::msError);
        }
        mess->AddMessage(L"Планы обмена обработаны", MessageState::msInfo);

        // планы счетов
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка планов счетов...");
        mess->AddMessage(L"Начало обработки планов счетов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_ChartsOfAccounts);
		}
        catch (...) {
                mess->AddMessage(L"Исключение при обработке планов счетов", MessageState::msError);
        }
        mess->AddMessage(L"Планы счетов обработаны", MessageState::msInfo);

        // планы видов расчета
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка планов видов расчета...");
        mess->AddMessage(L"Начало обработки планов видов расчета", MessageState::msInfo);
        try {
                fill_md(tr, GUID_ChartsOfCalculationTypes);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке планов видов расчета", MessageState::msError);
        }
        mess->AddMessage(L"Планы видов расчета обработаны", MessageState::msInfo);

        // внешние источники данных
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка внешних источников данных...");
        mess->AddMessage(L"Начало обработки внешних источников данных", MessageState::msInfo);
        try {
                fill_md(tr, GUID_ExternalDataSources);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке внешних источников данных", MessageState::msError);
        }
        mess->AddMessage(L"Внешние источники данных обработаны", MessageState::msInfo);

        // критерии отбора
		if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка критериев отбора...");
        mess->AddMessage(L"Начало обработки критериев отбора", MessageState::msInfo);
        try {
                fill_md(tr, GUID_FilterCriteria);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке критериев отбора", MessageState::msError);
        }
        mess->AddMessage(L"Критерии отбора обработаны", MessageState::msInfo);

        // функциональные опции
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка функциональных опций...");
        mess->AddMessage(L"Начало обработки функциональных опций", MessageState::msInfo);
        try {
                fill_md(tr, GUID_FunctionalOptions);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке функциональных опций", MessageState::msError);
        }
        mess->AddMessage(L"Функциональные опции обработаны", MessageState::msInfo);

        // параметры функциональных опций
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка параметров функциональных опций...");
        mess->AddMessage(L"Начало обработки параметров функциональных опций", MessageState::msInfo);
        try {
                fill_md(tr, GUID_FunctionalOptionsParameters);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке параметров функциональных опций", MessageState::msError);
		}
        mess->AddMessage(L"Параметры функциональных опций обработаны", MessageState::msInfo);

        // http - сервисы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка HTTP-сервисов...");
        mess->AddMessage(L"Начало обработки HTTP-сервисов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_HTTPServices);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке HTTP-сервисов", MessageState::msError);
        }
        mess->AddMessage(L"http - сервисы обработаны", MessageState::msInfo);

        // регистры сведений
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка регистров сведений...");
        mess->AddMessage(L"Начало обработки регистров сведений", MessageState::msInfo);
        try {
                fill_md(tr, GUID_InformationRegisters);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке регистров сведений", MessageState::msError);
        }
        mess->AddMessage(L"Регистры сведений обработаны", MessageState::msInfo);

        // интерфейсы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка интерфейсов...");
        mess->AddMessage(L"Начало обработки интерфейсов", MessageState::msInfo);
        try {
				fill_md(tr, GUID_Interfaces);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке интерфейсов", MessageState::msError);
        }
        mess->AddMessage(L"Интерфейсы обработаны", MessageState::msInfo);

        // отчеты
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка отчетов...");
        mess->AddMessage(L"Начало обработки отчетов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Reports);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке отчетов", MessageState::msError);
        }
        mess->AddMessage(L"Отчеты обработаны", MessageState::msInfo);

        // роли
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка ролей...");
        mess->AddMessage(L"Начало обработки ролей", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Roles);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке ролей", MessageState::msError);
        }
        mess->AddMessage(L"Роли обработаны", MessageState::msInfo);

		// параметры сеанса
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка параметров сеанса...");
        mess->AddMessage(L"Начало обработки параметров сеанса", MessageState::msInfo);
        try {
                fill_md(tr, GUID_SessionParameters);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке параметров сеанса", MessageState::msError);
        }
        mess->AddMessage(L"Параметры сеанса обработаны", MessageState::msInfo);

        // хранилища настроек
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка хранилищ настроек...");
        mess->AddMessage(L"Начало обработки хранилищ настроек", MessageState::msInfo);
        try {
                fill_md(tr, GUID_SettingsStorages);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке хранилищ настроек", MessageState::msError);
        }
        mess->AddMessage(L"Хранилища настроек обработаны", MessageState::msInfo);

        // элементы стиля
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка элементов стиля...");
        mess->AddMessage(L"Начало обработки элементов стиля", MessageState::msInfo);
        try {
                fill_md(tr, GUID_StyleItems);
        }
        catch (...) {
				mess->AddMessage(L"Исключение при обработке элементов стиля", MessageState::msError);
        }
        mess->AddMessage(L"Элементы стиля обработаны", MessageState::msInfo);

        // стили
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка стилей...");
        mess->AddMessage(L"Начало обработки стилей", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Styles);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке стилей", MessageState::msError);
        }
        mess->AddMessage(L"Стили обработаны", MessageState::msInfo);

        // подсистемы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка подсистем...");
        mess->AddMessage(L"Начало обработки подсистем", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Subsystems);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке подсистем", MessageState::msError);
        }
        mess->AddMessage(L"Подсистемы обработаны", MessageState::msInfo);

        // задачи
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка задач...");
        mess->AddMessage(L"Начало обработки задач", MessageState::msInfo);
		try {
                fill_md(tr, GUID_Tasks);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке задач", MessageState::msError);
        }
        mess->AddMessage(L"Задачи обработаны", MessageState::msInfo);

        // веб-сервисы
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка веб-сервисов...");
        mess->AddMessage(L"Начало обработки веб-сервисов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_WebServices);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке веб-сервисов", MessageState::msError);
        }
        mess->AddMessage(L"веб-сервисы обработаны", MessageState::msInfo);

        // ws-ссылки
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка WS-ссылок...");
        mess->AddMessage(L"Начало обработки WS-ссылок", MessageState::msInfo);
        try {
                fill_md(tr, GUID_WSReferences);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке WS-ссылок", MessageState::msError);
        }
        mess->AddMessage(L"ws-ссылки обработаны", MessageState::msInfo);

        // websocket-клиенты
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка WebSocket-клиентов...");
        mess->AddMessage(L"Начало обработки WebSocket-клиентов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_WebSocketClients);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке WebSocket-клиентов", MessageState::msError);
        }
        mess->AddMessage(L"WebSocket-клиенты обработаны", MessageState::msInfo);

        // сервисы интеграции
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка сервисов интеграции...");
        mess->AddMessage(L"Начало обработки сервисов интеграции", MessageState::msInfo);
        try {
                fill_md(tr, GUID_IntegrationServices);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке сервисов интеграции", MessageState::msError);
        }
        mess->AddMessage(L"Сервисы интеграции обработаны", MessageState::msInfo);

        // xdto-пакеты
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка XDTO-пакетов...");
        mess->AddMessage(L"Начало обработки XDTO-пакетов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_XDTOPackages);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке XDTO-пакетов", MessageState::msError);
        }
        mess->AddMessage(L"xdto-пакеты обработаны", MessageState::msInfo);

        // регл задания
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка регламентных заданий...");
        mess->AddMessage(L"Начало обработки регламентных заданий", MessageState::msInfo);
        try {
                fill_md(tr, GUID_ScheduledJobs);
        }
        catch (...) {
                mess->AddMessage(L"Исключение при обработке регламентных заданий", MessageState::msError);
        }
        mess->AddMessage(L"Регламентные задания обработаны", MessageState::msInfo);

        // боты
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка ботов...");
        mess->AddMessage(L"Начало обработки ботов", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Bots);
        }
		catch (...) {
                mess->AddMessage(L"Исключение при обработке ботов", MessageState::msError);
        }
        mess->AddMessage(L"Боты обработаны", MessageState::msInfo);

        // последовательности
        if (MainForm) MainForm->AdvanceLoadProgress(L"Обработка последовательностей...");
        mess->AddMessage(L"Начало обработки последовательностей", MessageState::msInfo);
        try {
                fill_md(tr, GUID_Sequences);
		}
		catch (...) {
				mess->AddMessage(L"Исключение при обработке последовательностей", MessageState::msError);
		}
		mess->AddMessage(L"Последовательности обработаны", MessageState::msInfo);

	structver = (*node)[0].get_value().ToInt();

	if(structver <= 15)
	{
		offset_name = 1;
		offset_ver = 12;
	}
	else
	{
		offset_name = 1;
		offset_ver = 15;
	}

	node2 = &(*node)[offset_name][1][3];

	if(node2->get_type() != nd_list)
	{
		mess->AddError(L"Ошибка получения синонима имени конфигурации");
		delete tr;
		return;
	}
	if((*node2)[0].get_type() != nd_number)
	{
		mess->AddError(L"Ошибка получения синонима имени конфигурации");
		delete tr;
		return;
	}

	j = (*node2)[0].get_value().ToIntDef(0);

	if(j == 0)
		cf_synonym = (*node)[offset_name][1][2].get_value();
	else
	{
		ok = false;
		for(k = 0; k < j; k++)
		{
			if((*node2)[k * 2 + 1].get_value().CompareIC(L"ru") == 0)
			{
				cf_synonym = (*node2)[k * 2 + 2].get_value();
				ok = true;
				break;
			}
		}

		if(!ok)
			cf_synonym = (*node2)[2].get_value();
	}

	cf_version = (*node)[offset_ver].get_value();
	delete tr;

	//mess->AddMessage(cf_synonym + " (" + cf_version + ")", msEmpty);
	MainForm->ConfigName = cf_synonym + " (" + cf_version + ")";
	//ConfigName = cf_synonym + " (" + cf_version + ")";
		if (mess && mess->getUiMessagesEnabled()) mess->AddMessage("Прочитана конфигурация: " + cf_synonym + " (" + cf_version + ")", msInfo);

}

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	// GlobalCF автоматически удаляется через std::unique_ptr
}
//---------------------------------------------------------------------------

String TMainForm::BuildModuleTabKey(PVirtualNode node, BaseMetadataObject* metadataObject,
	const String& moduleItemGuid, ModuleTextKind kind) const
{
	if (!moduleItemGuid.IsEmpty())
		return L"guid:" + moduleItemGuid + L"|kind:" + IntToStr(static_cast<int>(kind));
	if (metadataObject)
		return L"obj:" + IntToHex((NativeInt)metadataObject, 16) + L"|kind:" + IntToStr(static_cast<int>(kind));
	if (node)
		return L"node:" + IntToHex((NativeInt)node, 16) + L"|kind:" + IntToStr(static_cast<int>(kind));
	return L"kind:" + IntToStr(static_cast<int>(kind));
}
//---------------------------------------------------------------------------

TTabSheet* TMainForm::FindModuleTabByKey(const String& key) const
{
	for (const auto& it : ModuleTabs)
	{
		if (it.second.key == key)
			return it.first;
	}
	return nullptr;
}
//---------------------------------------------------------------------------

TTabSheet* TMainForm::CreateModuleTab(const String& key, const String& title)
{
	TTabSheet* tab = new TTabSheet(pagesEdit);
	tab->PageControl = pagesEdit;
	tab->Caption = title;

	TSynMemo* memo = new TSynMemo(tab);
	memo->Parent = tab;
	memo->Align = alClient;
	memo->Highlighter = Syn1CSyn;
	memo->Color = clWindow;
	memo->Font->Color = clBlack;
	memo->OnScanForFoldRanges = ModuleMemoScanForFoldRanges;
	memo->UseCodeFolding = true;
	memo->ReadOnly = false;
	memo->OnChange = MemoObjectChange;

	ModuleEditorTabState state;
	state.tab = tab;
	state.memo = memo;
	state.key = key;
	state.title = title;
	ModuleTabs.emplace(tab, state);
	return tab;
}
//---------------------------------------------------------------------------

String TMainForm::BuildModuleTabTitle(const String& objectName, ModuleTextKind kind, const String& fallbackTitle) const
{
	String modulePart = fallbackTitle;
	if (modulePart.IsEmpty())
	{
		switch (kind)
		{
			case ModuleTextKind::ObjectModule: modulePart = L"Модуль объекта"; break;
			case ModuleTextKind::ManagerModule: modulePart = L"Модуль менеджера"; break;
			case ModuleTextKind::FormModule: modulePart = L"Модуль формы"; break;
			case ModuleTextKind::CommandModule: modulePart = L"Модуль команды"; break;
			case ModuleTextKind::ApplicationModule: modulePart = L"Модуль приложения"; break;
			case ModuleTextKind::SessionModule: modulePart = L"Модуль сеанса"; break;
			case ModuleTextKind::ExternalConnectionModule: modulePart = L"Модуль внешнего соединения"; break;
			default: modulePart = L"Модуль"; break;
		}
	}

	if (!objectName.IsEmpty())
		return objectName + L" · " + modulePart;
	return modulePart;
}
//---------------------------------------------------------------------------

ModuleEditorTabState* TMainForm::GetModuleTabStateByMemo(TObject* sender)
{
	TSynMemo* memo = dynamic_cast<TSynMemo*>(sender);
	if (!memo)
		return nullptr;

	for (auto& it : ModuleTabs)
	{
		if (it.second.memo == memo)
			return &it.second;
	}
	return nullptr;
}
//---------------------------------------------------------------------------

ModuleEditorTabState* TMainForm::GetActiveModuleTabState()
{
	if (!pagesEdit)
		return nullptr;
	auto it = ModuleTabs.find(pagesEdit->ActivePage);
	return it != ModuleTabs.end() ? &it->second : nullptr;
}
//---------------------------------------------------------------------------

void TMainForm::ActivateModuleTab(TTabSheet* tab)
{
	if (!tab || !pagesEdit)
		return;
	SwitchingModuleTab = true;
	pagesEdit->ActivePage = tab;
	SwitchingModuleTab = false;
	PagesEditChange(pagesEdit);
}
//---------------------------------------------------------------------------

void TMainForm::PopulateModuleTab(ModuleEditorTabState& state, const String& text)
{
	if (!state.memo)
		return;

	LoadingModuleText = true;
	state.memo->BeginUpdate();
	try
	{
		state.memo->Lines->Text = text;
	}
	__finally
	{
		state.memo->EndUpdate();
		LoadingModuleText = false;
	}

	state.memo->CaretX = 1;
	state.memo->CaretY = 1;
	state.memo->TopLine = 1;
	state.memo->LeftChar = 1;
	state.memo->Invalidate();
	state.memo->Refresh();
}
//---------------------------------------------------------------------------

void TMainForm::SyncCurrentModuleFromTab(const ModuleEditorTabState* state)
{
	if (!state)
	{
		CurrentModuleNode = nullptr;
		CurrentModuleObject = nullptr;
		CurrentModuleDirty = false;
		CurrentModuleOriginalText = L"";
		CurrentModuleKind = ModuleTextKind::Unknown;
		CurrentModuleStandalone = false;
		CurrentStandaloneModuleDocument = ModuleTextDocument();
		CurrentModuleLocation = ModuleTextLocation();
		return;
	}

	CurrentModuleNode = state->node;
	CurrentModuleObject = state->metadataObject;
	CurrentModuleDirty = state->dirty;
	CurrentModuleOriginalText = state->originalText;
	CurrentModuleKind = state->kind;
	CurrentModuleStandalone = state->standalone;
	CurrentStandaloneModuleDocument = state->standaloneDocument;
	CurrentModuleLocation = state->location;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PagesEditChange(TObject *Sender)
{
	if (SwitchingModuleTab)
		return;
	ModuleEditorTabState* state = GetActiveModuleTabState();
	SyncCurrentModuleFromTab(state);
}
//---------------------------------------------------------------------------

bool TMainForm::SaveModuleTabIfNeeded(ModuleEditorTabState& state, bool forcePrompt)
{
	if ((!state.metadataObject && !state.standalone) || !state.dirty || !state.memo)
		return true;

	const String newText = state.memo->Lines->Text;

	if (forcePrompt)
	{
		const String tabName = state.title.IsEmpty() ? L"модуль" : state.title;
		int answer = Application->MessageBox(
			(L"Текст \"" + tabName + L"\" изменен. Сохранить изменения в SourceCF?").c_str(),
			L"Сохранение модуля",
			MB_YESNOCANCEL | MB_ICONQUESTION);
		if (answer == IDCANCEL)
			return false;
		if (answer == IDNO)
		{
			state.dirty = false;
			if (state.node)
			{
				VirtualTreeData* data = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(state.node);
				if (data)
					data->moduleDirty = false;
			}
			return true;
		}
	}

	String errorText;
	const bool saved = state.standalone
		? ModuleTextStorage::SaveDocument(state.standaloneDocument, newText, errorText)
		: (state.kind == ModuleTextKind::Unknown
			? state.metadataObject->SaveEditableModuleText(newText, errorText)
			: state.metadataObject->SaveEditableModuleText(state.kind, newText, errorText));
	if (!saved)
	{
		Application->MessageBox((L"Не удалось сохранить модуль:\r\n" + errorText).c_str(),
			L"Ошибка сохранения", MB_OK | MB_ICONERROR);
		return false;
	}

	state.originalText = newText;
	state.dirty = false;
	if (state.node)
	{
		VirtualTreeData* data = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(state.node);
		if (data)
		{
			data->text_module = newText;
			data->moduleDirty = false;
		}
	}
	if (mess)
		mess->Status(L"Модуль сохранен: " + ModuleTextStorage::DescribeLocation(state.location));
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MemoObjectChange(TObject *Sender)
{
	ModuleEditorTabState* state = GetModuleTabStateByMemo(Sender);
	if (LoadingModuleText || !state || (!state->metadataObject && !state->standalone) || !state->memo)
		return;

	state->dirty = state->memo->Lines->Text != state->originalText;

	if (state->node)
	{
		VirtualTreeData* data = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(state->node);
		if (data)
			data->moduleDirty = state->dirty;
	}

	if (state->dirty && mess)
		mess->Status(L"Модуль изменен: " + ModuleTextStorage::DescribeLocation(state->location));
	SyncCurrentModuleFromTab(GetActiveModuleTabState());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionSaveModuleExecute(TObject *Sender)
{
	SaveCurrentModuleTextIfNeeded(false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = true;
	for (auto& it : ModuleTabs)
	{
		if (!SaveModuleTabIfNeeded(it.second, true))
		{
			CanClose = false;
			break;
		}
	}
}
//---------------------------------------------------------------------------

void TMainForm::SetModuleEditorState(BaseMetadataObject* metadataObject, PVirtualNode node, const String& text,
	ModuleTextKind kind)
{
	CurrentModuleNode = node;
	CurrentModuleObject = metadataObject;
	CurrentModuleDirty = false;
	CurrentModuleOriginalText = text;
	CurrentModuleKind = kind;
	CurrentModuleStandalone = false;
	CurrentStandaloneModuleDocument = ModuleTextDocument();
	CurrentModuleLocation = metadataObject
		? (kind == ModuleTextKind::Unknown
			? metadataObject->GetEditableModuleLocation()
			: metadataObject->GetEditableModuleLocation(kind))
		: ModuleTextLocation();

	if (MemoObject)
	{
		bool editable = metadataObject && CurrentModuleLocation.editable && FileExists(CurrentModuleLocation.filePath);
		MemoObject->ReadOnly = !editable;
	}
}
//---------------------------------------------------------------------------

bool TMainForm::SaveCurrentModuleTextIfNeeded(bool forcePrompt)
{
	ModuleEditorTabState* state = GetActiveModuleTabState();
	if (!state)
		return true;
	const bool ok = SaveModuleTabIfNeeded(*state, forcePrompt);
	SyncCurrentModuleFromTab(state);
	return ok;
}
//---------------------------------------------------------------------------

bool TMainForm::FlushCurrentModuleBeforeBuild()
{
	for (auto& it : ModuleTabs)
	{
		if (!SaveModuleTabIfNeeded(it.second, false))
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------

bool TMainForm::IsConstantsContextNode(PVirtualNode node) const
{
	if (!VirtualStringTreeValue1C || !node)
		return false;

	VirtualTreeData* data = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(node);
	if (data && data->Name == md_Constants)
		return true;

	PVirtualNode parent = VirtualStringTreeValue1C->NodeParent[node];
	VirtualTreeData* parentData = parent
		? (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(parent)
		: nullptr;
	return parentData && parentData->Name == md_Constants;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ConfigurationPopupMenuPopup(TObject *Sender)
{
	PVirtualNode node = GetActiveTreeNode(VirtualStringTreeValue1C);
	const bool rootSelected = IsConfigurationRootNode(VirtualStringTreeValue1C, node);
	const bool constantsSelected = IsConstantsContextNode(node);

	OpenApplicationModuleMenuItem->Visible = rootSelected;
	OpenSessionModuleMenuItem->Visible = rootSelected;
	OpenExternalConnectionModuleMenuItem->Visible = rootSelected;
	ConstantsModulesMenuItem->Visible = constantsSelected;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenConfigurationModuleMenuItemClick(TObject *Sender)
{
	TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (!item)
		return;

	ShowConfigurationModule(static_cast<ModuleTextKind>(item->Tag), item->Caption);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenConstantsModuleMenuItemClick(TObject *Sender)
{
	TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (!item)
		return;

	ShowConstantsModule(static_cast<ModuleTextKind>(item->Tag), item->Caption);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (Button != mbRight || !VirtualStringTreeValue1C)
		return;

	PVirtualNode node = VirtualStringTreeValue1C->GetNodeAt(X, Y);
	if (!node)
		return;

	VirtualStringTreeValue1C->FocusedNode = node;
	VirtualStringTreeValue1C->ClearSelection();
	VirtualStringTreeValue1C->Selected[node] = true;
}
//---------------------------------------------------------------------------

void TMainForm::ShowConstantsModule(ModuleTextKind kind, const String& caption)
{
	PVirtualNode node = GetActiveTreeNode(VirtualStringTreeValue1C);
	if (!IsConstantsContextNode(node))
		return;

	String constantsMetadataGuid;
	String constantsObjectName = md_Constants;

	VirtualTreeData* nodeData = node
		? (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(node)
		: nullptr;
	BaseMetadataObject* mdObject = nodeData
		? dynamic_cast<BaseMetadataObject*>(nodeData->MetadataObject)
		: nullptr;
	if (mdObject)
	{
		constantsMetadataGuid = mdObject->guid;
		constantsObjectName = mdObject->name;
	}
	else
	{
		PVirtualNode child = node ? VirtualStringTreeValue1C->GetFirstChild(node) : nullptr;
		while (child)
		{
			VirtualTreeData* childData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(child);
			BaseMetadataObject* childObject = childData
				? dynamic_cast<BaseMetadataObject*>(childData->MetadataObject)
				: nullptr;
			if (childObject)
			{
				constantsMetadataGuid = childObject->guid;
				constantsObjectName = childObject->name;
				break;
			}
			child = VirtualStringTreeValue1C->GetNextSibling(child);
		}
	}

	if (constantsMetadataGuid.IsEmpty())
	{
		if (mess)
			mess->Status(caption + L": не найден GUID объекта констант");
		return;
	}

	const String normalizedGuid = ModuleTextStorage::NormalizeGuidFileName(constantsMetadataGuid);
	const String explicitModuleDataGuid = normalizedGuid
		+ (kind == ModuleTextKind::ManagerModule ? L".1" : L".0");

	const String moduleKey = L"constants:" + IntToStr(static_cast<int>(kind));
	const String tabKey = BuildModuleTabKey(node, nullptr, moduleKey, kind);
	TTabSheet* tab = FindModuleTabByKey(tabKey);
	if (tab)
	{
		ActivateModuleTab(tab);
		return;
	}

	ModuleTextDocument document = ModuleTextStorage::LoadBySourceCfModuleDataGuid(
		constantsMetadataGuid, explicitModuleDataGuid, kind);
	if (document.text.IsEmpty() && !document.location.editable)
	{
		document = ModuleTextStorage::LoadByMetadataObject(
			GlobalCF.get(), constantsMetadataGuid, constantsObjectName, kind);
	}
	const String moduleText = document.text;
	tab = CreateModuleTab(tabKey, BuildModuleTabTitle(constantsObjectName, kind, caption));
	ModuleEditorTabState* state = &ModuleTabs[tab];
	state->node = node;
	state->metadataObject = nullptr;
	state->kind = kind;
	state->standalone = true;
	state->standaloneDocument = document;
	state->location = document.location;
	state->originalText = moduleText;
	state->dirty = false;
	PopulateModuleTab(*state, moduleText);
	state->memo->ReadOnly = !(state->location.editable && FileExists(state->location.filePath));
	ActivateModuleTab(tab);

	if (mess)
	{
		const String location = ModuleTextStorage::DescribeLocation(state->location);
		if (!location.IsEmpty())
			mess->Status(caption + L": " + location);
		else
			mess->Status(caption + L": модуль не найден");
	}
}
//---------------------------------------------------------------------------

void TMainForm::ShowConfigurationModule(ModuleTextKind kind, const String& caption)
{
	PVirtualNode node = GetActiveTreeNode(VirtualStringTreeValue1C);
	if (!IsConfigurationRootNode(VirtualStringTreeValue1C, node))
		return;

	const String tabKey = BuildModuleTabKey(node, nullptr, L"", kind);
	TTabSheet* tab = FindModuleTabByKey(tabKey);
	if (tab)
	{
		ActivateModuleTab(tab);
		return;
	}

	ModuleTextDocument document = ModuleTextStorage::LoadConfigurationModule(GlobalCF.get(), kind);
	const String moduleText = document.text;
	tab = CreateModuleTab(tabKey, BuildModuleTabTitle(L"Конфигурация", kind, caption));
	ModuleEditorTabState* state = &ModuleTabs[tab];
	state->node = node;
	state->metadataObject = nullptr;
	state->kind = kind;
	state->standalone = true;
	state->standaloneDocument = document;
	state->location = document.location;
	state->originalText = moduleText;
	state->dirty = false;
	PopulateModuleTab(*state, moduleText);
	state->memo->ReadOnly = !(state->location.editable && FileExists(state->location.filePath));
	ActivateModuleTab(tab);

	if (mess)
	{
		const String location = ModuleTextStorage::DescribeLocation(state->location);
		if (!location.IsEmpty())
			mess->Status(caption + L": " + location);
		else
			mess->Status(caption + L": модуль не найден");
	}
}
//---------------------------------------------------------------------------

void TMainForm::EnsureCommonPicturePreviewControls()
{
	if (!Panel1)
		return;

	if (!CommonPicturePreviewInfoLabel)
	{
		CommonPicturePreviewInfoLabel = new TLabel(this);
		CommonPicturePreviewInfoLabel->Parent = Panel1;
		CommonPicturePreviewInfoLabel->Align = alTop;
		CommonPicturePreviewInfoLabel->Alignment = taLeftJustify;
		CommonPicturePreviewInfoLabel->Layout = tlCenter;
		CommonPicturePreviewInfoLabel->WordWrap = true;
		CommonPicturePreviewInfoLabel->Margins->Left = 8;
		CommonPicturePreviewInfoLabel->Margins->Top = 8;
		CommonPicturePreviewInfoLabel->Margins->Right = 8;
		CommonPicturePreviewInfoLabel->Margins->Bottom = 8;
		CommonPicturePreviewInfoLabel->Caption = L"Выберите изображение в списке \"Общие картинки\".";
		CommonPicturePreviewInfoLabel->Height = 42;
	}

	if (!CommonPicturePreviewImage)
	{
		if (!CommonPicturePreviewScrollBox)
		{
			CommonPicturePreviewScrollBox = new TScrollBox(this);
			CommonPicturePreviewScrollBox->Parent = Panel1;
			CommonPicturePreviewScrollBox->Align = alClient;
			CommonPicturePreviewScrollBox->AutoScroll = true;
			CommonPicturePreviewScrollBox->HorzScrollBar->Tracking = true;
			CommonPicturePreviewScrollBox->VertScrollBar->Tracking = true;
			CommonPicturePreviewScrollBox->OnResize = CommonPicturePreviewScrollBoxResize;
		}

		CommonPicturePreviewImage = new TImage(this);
		CommonPicturePreviewImage->Parent = CommonPicturePreviewScrollBox;
		CommonPicturePreviewImage->Align = alNone;
		CommonPicturePreviewImage->AutoSize = true;
		CommonPicturePreviewImage->Center = false;
		CommonPicturePreviewImage->Proportional = false;
		CommonPicturePreviewImage->Stretch = false;
		CommonPicturePreviewImage->Transparent = true;
		CommonPicturePreviewImage->Left = 0;
		CommonPicturePreviewImage->Top = 0;
	}

	if (!CommonPicturePreviewSvg)
	{
		CommonPicturePreviewSvg = new TSkSvg(this);
		CommonPicturePreviewSvg->Parent = CommonPicturePreviewScrollBox;
		CommonPicturePreviewSvg->Align = alNone;
		CommonPicturePreviewSvg->Left = 0;
		CommonPicturePreviewSvg->Top = 0;
		CommonPicturePreviewSvg->Width = 1;
		CommonPicturePreviewSvg->Height = 1;
		CommonPicturePreviewSvg->Svg->WrapMode = TSkSvgWrapMode::Original;
		CommonPicturePreviewSvg->Visible = false;
	}
}

void TMainForm::CenterCommonPicturePreviewContent()
{
	if (!CommonPicturePreviewScrollBox)
		return;

	TControl* activePreview = nullptr;
	if (CommonPicturePreviewSvg && CommonPicturePreviewSvg->Visible)
		activePreview = CommonPicturePreviewSvg;
	else if (CommonPicturePreviewImage && CommonPicturePreviewImage->Visible)
		activePreview = CommonPicturePreviewImage;

	if (!activePreview)
		return;

	const int viewportWidth = CommonPicturePreviewScrollBox->ClientWidth;
	const int viewportHeight = CommonPicturePreviewScrollBox->ClientHeight;
	int left = 0;
	int top = 0;

	if (activePreview->Width < viewportWidth)
		left = (viewportWidth - activePreview->Width) / 2;
	if (activePreview->Height < viewportHeight)
		top = (viewportHeight - activePreview->Height) / 2;

	activePreview->Left = left;
	activePreview->Top = top;
}

void __fastcall TMainForm::CommonPicturePreviewScrollBoxResize(TObject *Sender)
{
	CenterCommonPicturePreviewContent();
}

void TMainForm::ClearCommonPicturePreview(const String& statusText)
{
	EnsureCommonPicturePreviewControls();
	if (!CommonPicturePreviewInfoLabel || !CommonPicturePreviewImage)
		return;

	CommonPicturePreviewImage->Picture->Assign(nullptr);
	CommonPicturePreviewImage->Width = 1;
	CommonPicturePreviewImage->Height = 1;
	CommonPicturePreviewImage->Visible = true;
	if (CommonPicturePreviewSvg)
	{
		CommonPicturePreviewSvg->Svg->Source = L"";
		CommonPicturePreviewSvg->Width = 1;
		CommonPicturePreviewSvg->Height = 1;
		CommonPicturePreviewSvg->Visible = false;
	}
	if (CommonPicturePreviewScrollBox)
	{
		CommonPicturePreviewScrollBox->HorzScrollBar->Position = 0;
		CommonPicturePreviewScrollBox->VertScrollBar->Position = 0;
	}
	CenterCommonPicturePreviewContent();
	CommonPicturePreviewInfoLabel->Caption = statusText;
}

bool TMainForm::ShowCommonPicturePreviewForNode(VirtualTreeData* data)
{
	if (!data)
		return false;

	TCommonPictures* pictureMetadata = dynamic_cast<TCommonPictures*>(data->MetadataObject);
	if (!pictureMetadata)
		return false;

	EnsureCommonPicturePreviewControls();
	if (!CommonPicturePreviewInfoLabel || !CommonPicturePreviewImage)
		return false;

	TBytes imageBytes;
	bool loaded = false;
	String loadedFrom = L"";

	if (pictureMetadata->root_data && TryExtractImageBytesFromTree(pictureMetadata->root_data.get(), imageBytes))
	{
		loaded = true;
		loadedFrom = L"данные метаданных";
	}

	if (!loaded && pictureMetadata->parent)
	{
		std::vector<String> guidCandidates;
		AddUniqueCandidate(guidCandidates, pictureMetadata->guid);
		if (pictureMetadata->root_data)
			CollectGuidReferences(pictureMetadata->root_data.get(), guidCandidates);

		for (const auto& guidCandidate : guidCandidates)
		{
			if (guidCandidate.IsEmpty())
				continue;

			std::vector<String> fileCandidates;
			const String normalizedGuid = ModuleTextStorage::NormalizeGuidFileName(guidCandidate);
			AddUniqueCandidate(fileCandidates, guidCandidate);
			AddUniqueCandidate(fileCandidates, normalizedGuid);
			for (int i = 0; i <= 7; ++i)
			{
				AddUniqueCandidate(fileCandidates, guidCandidate + L"." + IntToStr(i));
				AddUniqueCandidate(fileCandidates, normalizedGuid + L"." + IntToStr(i));
			}

			for (const auto& fileName : fileCandidates)
			{
				v8file* file = pictureMetadata->parent->GetFile(fileName);
				if (TryExtractImageBytesFromV8File(file, imageBytes))
				{
					loaded = true;
					loadedFrom = fileName;
					break;
				}
			}

			if (loaded)
				break;
		}
	}

	if (!loaded)
	{
		std::vector<String> sourceGuids;
		AddUniqueCandidate(sourceGuids, pictureMetadata->guid);
		if (pictureMetadata->root_data)
			CollectGuidReferences(pictureMetadata->root_data.get(), sourceGuids);
		for (const auto& sourceGuid : sourceGuids)
		{
			if (TryExtractImageBytesFromSourceCf(sourceGuid, imageBytes))
			{
				loaded = true;
				loadedFrom = L"SourceCF";
				break;
			}
		}
	}

	if (!loaded || imageBytes.empty())
	{
		ClearCommonPicturePreview(L"Изображение не найдено для: " + data->Name);
		return true;
	}

	try
	{
		String svgText;
		if (!TryLoadPictureFromBytes(imageBytes, CommonPicturePreviewImage->Picture))
		{
			TBytes embeddedBytes;
			if (TryExtractPictureFromZipBytes(imageBytes, embeddedBytes)
				&& TryLoadPictureFromBytes(embeddedBytes, CommonPicturePreviewImage->Picture))
			{
				imageBytes = embeddedBytes;
			}
			else if (TryExtractEmbeddedPictureBytes(imageBytes, embeddedBytes)
				&& TryLoadPictureFromBytes(embeddedBytes, CommonPicturePreviewImage->Picture))
			{
				imageBytes = embeddedBytes;
			}
			else if (TryDecodeSvgTextFromBytes(imageBytes, svgText))
			{
			}
			else
			{
				ClearCommonPicturePreview(L"Не удалось декодировать картинку: " + data->Name);
				return true;
			}
		}
		else
		{
			svgText = L"";
		}

		if (!svgText.IsEmpty())
		{
			if (!CommonPicturePreviewSvg)
			{
				ClearCommonPicturePreview(L"SVG не поддержан в текущей сборке: " + data->Name);
				return true;
			}

			CommonPicturePreviewImage->Visible = false;
			CommonPicturePreviewSvg->Visible = true;
			CommonPicturePreviewSvg->Svg->Source = svgText;

			int svgWidth = static_cast<int>(CommonPicturePreviewSvg->Svg->OriginalSize.Width + 0.5f);
			int svgHeight = static_cast<int>(CommonPicturePreviewSvg->Svg->OriginalSize.Height + 0.5f);
			if (svgWidth < 1) svgWidth = 1;
			if (svgHeight < 1) svgHeight = 1;
			CommonPicturePreviewSvg->Width = svgWidth;
			CommonPicturePreviewSvg->Height = svgHeight;
		}
		else
		{
			CommonPicturePreviewSvg->Visible = false;
			CommonPicturePreviewImage->Visible = true;
			if (CommonPicturePreviewImage->Picture->Graphic && !CommonPicturePreviewImage->Picture->Graphic->Empty)
			{
				CommonPicturePreviewImage->Width = CommonPicturePreviewImage->Picture->Graphic->Width;
				CommonPicturePreviewImage->Height = CommonPicturePreviewImage->Picture->Graphic->Height;
			}
		}
		if (CommonPicturePreviewScrollBox)
		{
			CommonPicturePreviewScrollBox->HorzScrollBar->Position = 0;
			CommonPicturePreviewScrollBox->VertScrollBar->Position = 0;
		}
		CenterCommonPicturePreviewContent();
		CommonPicturePreviewInfoLabel->Caption =
			L"Картинка: " + data->Name + L", размер: " + IntToStr(imageBytes.Length)
			+ L" байт, источник: " + loadedFrom;
		return true;
	}
	catch (...)
	{
		ClearCommonPicturePreview(L"Не удалось декодировать картинку: " + data->Name);
		return true;
	}
}

//---------------------------------------------------------------------------

void TMainForm::ShowMetadataNodeText(PVirtualNode Node)
{
	Node = GetActiveTreeNode(VirtualStringTreeValue1C, Node);
	if (!Node)
		return;

	VirtualTreeData* Data = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(Node);
	bool moduleTextSelected = false;
	String moduleText = L"";
	LastModuleNodeShown = Node;

	if (Data)
	{
		ModuleTextKind requestedKind = Data->moduleLocation.kind;
		BaseMetadataObject* metadataObject = dynamic_cast<BaseMetadataObject*>(Data->MetadataObject);
		TEnums* enumObject = dynamic_cast<TEnums*>(Data->MetadataObject);
		bool nestedModuleRequested = metadataObject && !Data->moduleItemGuid.IsEmpty()
			&& (requestedKind == ModuleTextKind::FormModule || requestedKind == ModuleTextKind::CommandModule);
		if (!nestedModuleRequested && enumObject && requestedKind == ModuleTextKind::ManagerModule)
			nestedModuleRequested = true;

		if (nestedModuleRequested)
		{
			String targetGuid = Data->moduleItemGuid;
			String targetName = Data->Name;
			v8catalog* targetParent = metadataObject ? metadataObject->parent : nullptr;
			if (enumObject && requestedKind == ModuleTextKind::ManagerModule)
			{
				targetGuid = enumObject->guid;
				targetName = enumObject->name;
				targetParent = enumObject->parent;
			}

			CurrentStandaloneModuleDocument = ModuleTextStorage::LoadByMetadataObject(
				targetParent, targetGuid, targetName, requestedKind);
			moduleText = CurrentStandaloneModuleDocument.text;
			moduleTextSelected = !moduleText.IsEmpty() || CurrentStandaloneModuleDocument.location.editable;
			Data->moduleLocation = CurrentStandaloneModuleDocument.location;
			Data->moduleEditable = Data->moduleLocation.editable;
		}
		else if (!Data->text_module.IsEmpty())
		{
			moduleText = Data->text_module;
			moduleTextSelected = true;
		}
		else if (requestedKind == ModuleTextKind::ManagerModule)
		{
			TEnums* enumObject = dynamic_cast<TEnums*>(Data->MetadataObject);
			if (enumObject && enumObject->parent && !enumObject->guid.IsEmpty())
			{
				CurrentStandaloneModuleDocument = ModuleTextStorage::LoadByMetadataObject(
					enumObject->parent, enumObject->guid, enumObject->name, requestedKind);
				moduleText = CurrentStandaloneModuleDocument.text;
				moduleTextSelected = !moduleText.IsEmpty() || CurrentStandaloneModuleDocument.location.editable;
				Data->moduleLocation = CurrentStandaloneModuleDocument.location;
				Data->moduleEditable = Data->moduleLocation.editable;
			}
		}
		else if (metadataObject && requestedKind != ModuleTextKind::Unknown &&
			metadataObject->HasEditableModuleText(requestedKind))
		{
			moduleText = metadataObject->GetEditableModuleText(requestedKind);
			moduleTextSelected = true;
		}
		else
		{
			TCommonModules* module = dynamic_cast<TCommonModules*>(Data->MetadataObject);
			if (module)
			{
				moduleText = module->GetText();
				moduleTextSelected = true;
			}
			else
			{
				TCommonForms* commonForm = dynamic_cast<TCommonForms*>(Data->MetadataObject);
				if (commonForm)
				{
					moduleText = commonForm->GetText();
					moduleTextSelected = true;
				}
			}
		}

	}

	if (Data && ShowCommonPicturePreviewForNode(Data))
	{
		if (pagesEdit && TabSheet1)
			pagesEdit->ActivePage = TabSheet1;
		return;
	}

	if (moduleTextSelected && mess)
	{
		String nodeName = Data ? Data->Name : L"";
		mess->Status(L"Модуль: " + nodeName + L", длина текста: " + IntToStr(moduleText.Length()));
	}

	BaseMetadataObject* editableObject = Data ? dynamic_cast<BaseMetadataObject*>(Data->MetadataObject) : nullptr;
	ModuleTextKind editableKind = Data ? Data->moduleLocation.kind : ModuleTextKind::Unknown;
	TEnums* enumEditableObject = Data ? dynamic_cast<TEnums*>(Data->MetadataObject) : nullptr;
	bool editableExists = false;
	bool standaloneExists = Data && !Data->moduleItemGuid.IsEmpty()
		&& (editableKind == ModuleTextKind::FormModule || editableKind == ModuleTextKind::CommandModule)
		&& moduleTextSelected;
	if (!standaloneExists && enumEditableObject && editableKind == ModuleTextKind::ManagerModule && moduleTextSelected)
		standaloneExists = true;
	if (editableObject && !standaloneExists)
	{
		editableExists = editableKind == ModuleTextKind::Unknown
			? editableObject->HasEditableModuleText()
			: editableObject->HasEditableModuleText(editableKind);
	}

	if (!moduleTextSelected)
		return;

	const String moduleItemGuid = Data ? Data->moduleItemGuid : L"";
	const String tabKey = BuildModuleTabKey(Node, editableObject, moduleItemGuid, editableKind);
	TTabSheet* tab = FindModuleTabByKey(tabKey);
	if (tab)
	{
		ActivateModuleTab(tab);
		return;
	}

	String objectName = editableObject ? editableObject->GetName() : L"";
	String moduleName = Data ? Data->Name : L"Модуль";
	tab = CreateModuleTab(tabKey, BuildModuleTabTitle(objectName, editableKind, moduleName));
	ModuleEditorTabState* state = &ModuleTabs[tab];
	state->node = Node;
	state->metadataObject = editableObject;
	state->kind = editableKind;
	state->originalText = moduleText;
	state->dirty = false;

	if (editableObject && standaloneExists)
	{
		state->standalone = true;
		state->standaloneDocument = CurrentStandaloneModuleDocument;
		state->location = CurrentStandaloneModuleDocument.location;
		Data->moduleLocation = state->location;
		Data->moduleEditable = state->location.editable;
		state->memo->ReadOnly = !(state->location.editable && FileExists(state->location.filePath));
		if (mess && Data->moduleEditable)
			mess->Status(L"Модуль открыт для редактирования: " + ModuleTextStorage::DescribeLocation(Data->moduleLocation));
	}
	else if (editableObject && editableExists)
	{
		state->standalone = false;
		state->location = editableKind == ModuleTextKind::Unknown
			? editableObject->GetEditableModuleLocation()
			: editableObject->GetEditableModuleLocation(editableKind);
		Data->moduleLocation = editableKind == ModuleTextKind::Unknown
			? editableObject->GetEditableModuleLocation()
			: editableObject->GetEditableModuleLocation(editableKind);
		Data->moduleEditable = Data->moduleLocation.editable;
		state->memo->ReadOnly = !(state->location.editable && FileExists(state->location.filePath));
		if (mess && Data->moduleEditable)
			mess->Status(L"Модуль открыт для редактирования: " + ModuleTextStorage::DescribeLocation(Data->moduleLocation));
	}
	else
	{
		state->standalone = false;
		state->metadataObject = nullptr;
		state->location = ModuleTextLocation();
		state->memo->ReadOnly = true;
	}

	PopulateModuleTab(*state, moduleText);
	ActivateModuleTab(tab);
}

void TMainForm::ScheduleMetadataNodeText(PVirtualNode Node)
{
	PendingModuleNode = GetActiveTreeNode(VirtualStringTreeValue1C, Node);
	if (!PendingModuleNode)
		return;

	if (ModuleSelectionTimer)
		ModuleSelectionTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CClick(TObject *Sender)
{
	ScheduleMetadataNodeText(GetActiveTreeNode(VirtualStringTreeValue1C));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CChange(TBaseVirtualTree *Sender, PVirtualNode Node)
{
	ScheduleMetadataNodeText(Node);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CNodeClick(TBaseVirtualTree *Sender, const THitInfo &HitInfo)
{
	ScheduleMetadataNodeText(HitInfo.HitNode);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModuleSelectionTimerTimer(TObject *Sender)
{
	if (ModuleSelectionTimer)
		ModuleSelectionTimer->Enabled = false;

	PVirtualNode node = PendingModuleNode ? PendingModuleNode : GetActiveTreeNode(VirtualStringTreeValue1C);
	PendingModuleNode = nullptr;

	if (!node || node == LastModuleNodeShown)
		return;

	ShowMetadataNodeText(node);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CFocusChanged(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column)
{
	ScheduleMetadataNodeText(Node);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N4Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionSaveCFExecute(TObject *Sender)
{
	if (!FlushCurrentModuleBeforeBuild())
		return;

	const String sourceCfDir = TPath::Combine(ExtractFilePath(ParamStr(0)), L"SourceCF");
	if (!TDirectory::Exists(sourceCfDir))
	{
		Application->MessageBox(
			L"Каталог SourceCF не найден. Откройте и распакуйте конфигурацию перед сборкой.",
			L"Сборка cf",
			MB_OK | MB_ICONWARNING);
		return;
	}

	const String outFileName = TPath::Combine(ExtractFilePath(ParamStr(0)), L"1Cv8_out.cf");
	const std::string sourceCfDirStd = AnsiString(sourceCfDir).c_str();
	const std::string outFileNameStd = AnsiString(outFileName).c_str();

	const auto result = v8reader::core::build_cf_file(sourceCfDirStd, outFileNameStd, false);
	if (result.ok())
	{
		if (mess)
			mess->AddMessage(L"Файл конфигурации собран: " + outFileName, msSuccesfull);
	}
	else
	{
		Application->MessageBox(
			(L"Ошибка сборки cf. Код: " + IntToStr(result.code)).c_str(),
			L"Сборка cf",
			MB_OK | MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------




