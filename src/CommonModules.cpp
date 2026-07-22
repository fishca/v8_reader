//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.IOUtils.hpp>

#include "CommonModules.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace
{
	bool __fastcall IsGuidLikeChar(wchar_t ch)
	{
		return (ch >= L'0' && ch <= L'9')
			|| (ch >= L'a' && ch <= L'f')
			|| (ch >= L'A' && ch <= L'F');
	}

	bool __fastcall IsGuidLike(const String& value)
	{
		if (value.Length() != 36)
			return false;

		for (int i = 1; i <= value.Length(); i++)
		{
			wchar_t ch = value[i];
			if (i == 9 || i == 14 || i == 19 || i == 24)
			{
				if (ch != L'-')
					return false;
			}
			else if (!IsGuidLikeChar(ch))
				return false;
		}

		return true;
	}

	void __fastcall AddUniqueString(std::vector<String>& values, const String& value)
	{
		if (value.IsEmpty())
			return;

		String upperValue = value.UpperCase();
		for (const auto& existing : values)
			if (existing.UpperCase() == upperValue)
				return;

		values.push_back(value);
	}

	void __fastcall AddModuleFileCandidates(std::vector<String>& candidates, const String& baseGuid)
	{
		AddUniqueString(candidates, baseGuid + L".0");
		AddUniqueString(candidates, baseGuid + L".1");
		AddUniqueString(candidates, baseGuid + L".2");
		AddUniqueString(candidates, baseGuid + L".3");
		AddUniqueString(candidates, baseGuid);
	}

	String __fastcall NormalizeGuidFileName(const String& guid)
	{
		String result = Trim(guid).LowerCase();
		if (result.Length() >= 2 && result[1] == L'{' && result[result.Length()] == L'}')
			result = result.SubString(2, result.Length() - 2);
		return result;
	}

	void __fastcall CollectGuidReferences(tree* node, std::vector<String>& guids)
	{
		if (!node)
			return;

		if (IsGuidLike(node->get_value()))
			AddUniqueString(guids, node->get_value());

		for (int i = 0; i < node->get_num_subnode(); i++)
			CollectGuidReferences(node->get_subnode(i), guids);
	}

	

	void __fastcall AddUniquePath(std::vector<String>& values, const String& value)
	{
		if (value.IsEmpty())
			return;

		String normalized = ExcludeTrailingPathDelimiter(value).UpperCase();
		for (const auto& existing : values)
			if (ExcludeTrailingPathDelimiter(existing).UpperCase() == normalized)
				return;

		values.push_back(value);
	}

	String __fastcall TryReadUnpackedModuleText(const String& guid)
	{
		std::vector<String> sourceDirs;
		AddUniquePath(sourceDirs, TPath::Combine(GetCurrentDir(), L"SourceCF"));
		AddUniquePath(sourceDirs, TPath::Combine(ExtractFilePath(ParamStr(0)), L"SourceCF"));
		String normalizedGuid = NormalizeGuidFileName(guid);

		for (const auto& sourceDir : sourceDirs)
		{
			if (!TDirectory::Exists(sourceDir))
				continue;

			for (int i = 0; i <= 5; ++i)
			{
				const String objectDir = TPath::Combine(sourceDir, normalizedGuid + L"." + IntToStr(i));
				const String textFileName = TPath::Combine(objectDir, L"text");
				String text = ModuleTextStorage::ReadDiskFileAsText(textFileName);
				if (!text.IsEmpty() && ModuleTextStorage::LooksLike1CModuleText(text))
					return text;

				const String moduleFileName = TPath::Combine(objectDir, L"module");
				text = ModuleTextStorage::ReadDiskFileAsText(moduleFileName);
				if (!text.IsEmpty() && ModuleTextStorage::LooksLike1CModuleText(text))
					return text;

				const String directFileName = TPath::Combine(sourceDir, normalizedGuid + L"." + IntToStr(i));
				text = ModuleTextStorage::ReadDiskFileAsText(directFileName);
				if (!text.IsEmpty() && ModuleTextStorage::LooksLike1CModuleText(text))
					return text;
			}
		}

		return L"";
	}

	String __fastcall TryReadUnpackedModuleTextByName(const String& moduleName)
	{
		if (moduleName.IsEmpty())
			return L"";

		std::vector<String> sourceDirs;
		AddUniquePath(sourceDirs, TPath::Combine(GetCurrentDir(), L"SourceCF"));
		AddUniquePath(sourceDirs, TPath::Combine(ExtractFilePath(ParamStr(0)), L"SourceCF"));

		for (const auto& sourceDir : sourceDirs)
		{
			if (!TDirectory::Exists(sourceDir))
				continue;

			TStringDynArray files = TDirectory::GetFiles(sourceDir);
			for (int i = 0; i < files.Length; ++i)
			{
				const String fileName = files[i];
				String objectGuid = ExtractFileName(fileName);
				if (!IsGuidLike(objectGuid))
					continue;

				String metadataText = ModuleTextStorage::ReadDiskFileAsText(fileName);
				if (metadataText.Pos(moduleName) <= 0)
					continue;

				String moduleText = TryReadUnpackedModuleText(objectGuid);
				if (!moduleText.IsEmpty())
					return moduleText;
			}
		}

		return L"";
	}

	String __fastcall TryReadNamedTextFile(v8catalog* catalog, const String& fileName)
	{
		if (!catalog)
			return L"";

		v8file* file = catalog->GetFile(fileName);
		if (!file)
			return L"";

		String text = ModuleTextStorage::ReadV8FileAsText(file);
		return ModuleTextStorage::LooksLike1CModuleText(text) ? text : L"";
	}

	String __fastcall TryReadModuleContainer(v8file* file)
	{
		if (!file)
			return L"";

		try
		{
			v8catalog* catalog = new v8catalog(file);
			if (catalog)
			{
				catalog->ClearIs8316();

				String text = TryReadNamedTextFile(catalog, L"text");
				if (text.IsEmpty())
					text = TryReadNamedTextFile(catalog, L"module");

				if (text.IsEmpty())
				{
					for (v8file* child = catalog->GetFirst(); child; child = child->GetNext())
					{
						String childName = child->GetFileName().LowerCase();
						if (childName.Pos(L"text") > 0 || childName.Pos(L"module") > 0)
						{
							text = ModuleTextStorage::ReadV8FileAsText(child);
							if (ModuleTextStorage::LooksLike1CModuleText(text))
								break;
							text = L"";
						}
					}
				}

				delete catalog;
				if (!text.IsEmpty())
					return text;
			}
		}
		catch (...)
		{
		}

		String directText = ModuleTextStorage::ReadV8FileAsText(file);
		if (ModuleTextStorage::LooksLike1CModuleText(directText))
			return directText;

		try
		{
			std::unique_ptr<tree> objectTree(get_treeFromV8file(file));
			return ModuleTextStorage::FindEmbeddedModuleText(objectTree.get());
		}
		catch (...)
		{
			return L"";
		}
	}
}


__fastcall TCommonModules::TCommonModules() : BaseMetadataObject()
{
	root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

__fastcall TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
}

__fastcall TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	root_data.reset();
	textDocument.text = L"";
	textDocument.loaded = false;
	textDocument.dirty = false;
	name = _name;
}

void __fastcall TCommonModules::LoadTextIfNeeded()
{
	if (textDocument.loaded)
		return;

	textDocument = ModuleTextStorage::LoadCommonModule(parent, guid, name);
	textDocument.loaded = true;
}

void __fastcall TCommonModules::RefreshEditableTextIfNeeded()
{
	LoadTextIfNeeded();
	if (textDocument.location.editable)
		return;

	ModuleTextDocument refreshed = ModuleTextStorage::LoadCommonModule(parent, guid, name);
	if (refreshed.location.editable)
		textDocument = refreshed;
}

__fastcall TCommonModules::~TCommonModules()
{

}

String __fastcall TCommonModules::GetText()
{
	LoadTextIfNeeded();
	return textDocument.text;
}

void __fastcall TCommonModules::SetText(String _text)
{
	LoadTextIfNeeded();
	textDocument.text = _text;
	textDocument.loaded = true;
	textDocument.dirty = true;
}

ModuleTextDocument& __fastcall TCommonModules::GetTextDocument()
{
	RefreshEditableTextIfNeeded();
	return textDocument;
}

bool __fastcall TCommonModules::SaveTextToSource(const String& newText, String& errorText)
{
	RefreshEditableTextIfNeeded();
	return ModuleTextStorage::SaveDocument(textDocument, newText, errorText);
}

bool __fastcall TCommonModules::HasEditableModuleText()
{
	RefreshEditableTextIfNeeded();
	return !textDocument.text.IsEmpty() || textDocument.location.editable;
}

String __fastcall TCommonModules::GetEditableModuleText()
{
	return GetText();
}

void __fastcall TCommonModules::SetEditableModuleText(const String& value)
{
	SetText(value);
}

bool __fastcall TCommonModules::SaveEditableModuleText(const String& value, String& errorText)
{
	return SaveTextToSource(value, errorText);
}

ModuleTextLocation __fastcall TCommonModules::GetEditableModuleLocation()
{
	RefreshEditableTextIfNeeded();
	return textDocument.location;
}

void __fastcall TCommonModules::initializeFromTree()
{

}

