//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.IOUtils.hpp>

#include "CommonModules.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace
{
	bool __fastcall LooksLikeUtf16Le(const TBytes& bytes)
	{
		int limit = bytes.Length < 200 ? bytes.Length : 200;
		int checked = 0;
		int zeroOdd = 0;

		for (int i = 1; i < limit; i += 2)
		{
			++checked;
			if (bytes[i] == 0)
				++zeroOdd;
		}

		return checked > 0 && zeroOdd * 2 >= checked;
	}

	String __fastcall DecodeModuleText(const TBytes& sourceBytes, int sourceSize)
	{
		if (sourceSize <= 0 || sourceBytes.empty())
			return L"";

		TBytes bytes = sourceBytes;
		sourceSize = sourceSize < bytes.Length ? sourceSize : bytes.Length;

		TEncoding *enc = nullptr;
		int off = TEncoding::GetBufferEncoding(bytes, enc);
		if (off > 0)
		{
			TBytes unicodeBytes = TEncoding::Convert(enc, TEncoding::Unicode, bytes, off, sourceSize - off);
			if (!unicodeBytes.empty())
				return String((wchar_t*)&unicodeBytes[0], unicodeBytes.Length / 2);
		}

		if (LooksLikeUtf16Le(bytes))
			return String((wchar_t*)&bytes[0], sourceSize / 2);

		try
		{
			return TEncoding::UTF8->GetString(bytes, 0, sourceSize);
		}
		catch (...)
		{
			return String((char*)&bytes[0], sourceSize);
		}
	}

	bool __fastcall LooksLike1CModuleText(const String& value)
	{
		return value.Length() > 20
			&& (value.Pos(L"\n") > 0
				|| value.Pos(L"\r") > 0
				|| value.Pos(L"Процедура") > 0
				|| value.Pos(L"Функция") > 0
				|| value.Pos(L"КонецПроцедуры") > 0
				|| value.Pos(L"КонецФункции") > 0);
	}

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

	String __fastcall FindEmbeddedModuleText(tree* node)
	{
		if (!node)
			return L"";

		if (node->get_type() == nd_string && LooksLike1CModuleText(node->get_value()))
			return node->get_value();

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			String found = FindEmbeddedModuleText(node->get_subnode(i));
			if (!found.IsEmpty())
				return found;
		}

		return L"";
	}

	String __fastcall ReadV8FileAsText(v8file* file)
	{
		if (!file)
			return L"";

		TBytes bytes;
		TBytesStream* sb = new TBytesStream(bytes);
		try
		{
			file->SaveToStream(sb);
			String text = DecodeModuleText(sb->Bytes, sb->Size);
			delete sb;
			return text;
		}
		catch (...)
		{
			delete sb;
			return L"";
		}
	}

	String __fastcall ReadDiskFileAsText(const String& fileName)
	{
		if (!FileExists(fileName))
			return L"";

		TFileStream* fs = nullptr;
		TBytesStream* sb = nullptr;
		try
		{
			fs = new TFileStream(fileName, fmOpenRead | fmShareDenyNone);
			TBytes bytes;
			sb = new TBytesStream(bytes);
			sb->CopyFrom(fs, 0);
			String text = DecodeModuleText(sb->Bytes, sb->Size);
			delete sb;
			delete fs;
			return text;
		}
		catch (...)
		{
			delete sb;
			delete fs;
			return L"";
		}
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
				String text = ReadDiskFileAsText(textFileName);
				if (!text.IsEmpty() && LooksLike1CModuleText(text))
					return text;

				const String moduleFileName = TPath::Combine(objectDir, L"module");
				text = ReadDiskFileAsText(moduleFileName);
				if (!text.IsEmpty() && LooksLike1CModuleText(text))
					return text;

				const String directFileName = TPath::Combine(sourceDir, normalizedGuid + L"." + IntToStr(i));
				text = ReadDiskFileAsText(directFileName);
				if (!text.IsEmpty() && LooksLike1CModuleText(text))
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

				String metadataText = ReadDiskFileAsText(fileName);
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

		String text = ReadV8FileAsText(file);
		return LooksLike1CModuleText(text) ? text : L"";
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
							text = ReadV8FileAsText(child);
							if (LooksLike1CModuleText(text))
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

		String directText = ReadV8FileAsText(file);
		if (LooksLike1CModuleText(directText))
			return directText;

		try
		{
			std::unique_ptr<tree> objectTree(get_treeFromV8file(file));
			return FindEmbeddedModuleText(objectTree.get());
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
	text = L"";
	textLoaded = false;
}

__fastcall TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	root_data.reset();
	text = L"";
	textLoaded = false;
}

__fastcall TCommonModules::TCommonModules(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	root_data.reset();
	text = L"";
	textLoaded = false;
	name = _name;
}

void __fastcall TCommonModules::LoadTextIfNeeded()
{
	if (textLoaded)
		return;

	text = L"";

	if (!guid.IsEmpty())
		text = TryReadUnpackedModuleText(guid);
	if (text.IsEmpty())
		text = TryReadUnpackedModuleTextByName(name);

	if ((parent) && (!guid.IsEmpty()))
	{
		std::vector<String> candidates;
		AddModuleFileCandidates(candidates, guid);

		try
		{
			v8file* objectFile = parent->GetFile(guid);
			if (objectFile)
			{
				std::unique_ptr<tree> objectTree(get_treeFromV8file(objectFile));
				if (text.IsEmpty())
					text = FindEmbeddedModuleText(objectTree.get());

				std::vector<String> referencedGuids;
				CollectGuidReferences(objectTree.get(), referencedGuids);
				for (const auto& referencedGuid : referencedGuids)
				{
					if (text.IsEmpty())
						text = TryReadUnpackedModuleText(referencedGuid);
					AddModuleFileCandidates(candidates, referencedGuid);
				}
			}
		}
		catch (...)
		{
		}

		for (size_t i = 0; i < candidates.size() && text.IsEmpty(); i++)
		{
			v8file* data_module = parent->GetFile(candidates[i]);
			text = TryReadModuleContainer(data_module);
		}
	}

	textLoaded = true;
}

__fastcall TCommonModules::~TCommonModules()
{

}

String __fastcall TCommonModules::GetText()
{
	LoadTextIfNeeded();
	return text;
}

void __fastcall TCommonModules::SetText(String _text)
{
	text = _text;
	textLoaded = true;
}

void __fastcall TCommonModules::initializeFromTree()
{

}
