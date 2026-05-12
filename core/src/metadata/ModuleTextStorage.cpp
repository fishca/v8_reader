//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.IOUtils.hpp>

#include <memory>
#include <vector>

#include "ModuleTextStorage.h"
#include "Class_1CD.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace
{
	bool __fastcall LooksLikeStrictModuleBody(const String& value);

	bool __fastcall LooksLikeUtf16Le(const TBytes& bytes, int sourceSize)
	{
		int limit = sourceSize < 200 ? sourceSize : 200;
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

	String __fastcall DecodeModuleText(const TBytes& sourceBytes, int sourceSize, ModuleTextEncodingKind& encoding)
	{
		encoding = ModuleTextEncodingKind::Unknown;

		if (sourceSize <= 0 || sourceBytes.empty())
			return L"";

		TBytes bytes = sourceBytes;
		sourceSize = sourceSize < bytes.Length ? sourceSize : bytes.Length;

		TEncoding* enc = nullptr;
		int off = TEncoding::GetBufferEncoding(bytes, enc);
		if (off > 0)
		{
			if (enc == TEncoding::UTF8)
				encoding = ModuleTextEncodingKind::Utf8Bom;
			else if (enc == TEncoding::Unicode)
				encoding = ModuleTextEncodingKind::Utf16LeBom;

			TBytes unicodeBytes = TEncoding::Convert(enc, TEncoding::Unicode, bytes, off, sourceSize - off);
			if (!unicodeBytes.empty())
				return String((wchar_t*)&unicodeBytes[0], unicodeBytes.Length / 2);
		}

		if (LooksLikeUtf16Le(bytes, sourceSize))
		{
			encoding = ModuleTextEncodingKind::Utf16Le;
			return String((wchar_t*)&bytes[0], sourceSize / 2);
		}

		try
		{
			encoding = ModuleTextEncodingKind::Utf8;
			return TEncoding::UTF8->GetString(bytes, 0, sourceSize);
		}
		catch (...)
		{
			encoding = ModuleTextEncodingKind::Ansi;
			return String((char*)&bytes[0], sourceSize);
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

	std::vector<String> __fastcall GetSourceCfRoots()
	{
		std::vector<String> roots;
		AddUniquePath(roots, TPath::Combine(GetCurrentDir(), L"SourceCF"));
		AddUniquePath(roots, TPath::Combine(ExtractFilePath(ParamStr(0)), L"SourceCF"));
		return roots;
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

	std::vector<String> __fastcall GetModuleContainerCandidates(const String& baseGuid,
		ModuleTextKind kind = ModuleTextKind::Unknown)
	{
		std::vector<String> candidates;

		if (kind == ModuleTextKind::ApplicationModule)
		{
			AddUniqueString(candidates, baseGuid + L".6");
			return candidates;
		}

		if (kind == ModuleTextKind::SessionModule
			|| kind == ModuleTextKind::ExternalConnectionModule)
		{
			AddUniqueString(candidates, baseGuid + (kind == ModuleTextKind::SessionModule ? L".7" : L".5"));
			return candidates;
		}

		if (kind == ModuleTextKind::ManagerModule)
		{
			AddUniqueString(candidates, baseGuid + L".1");
			AddUniqueString(candidates, baseGuid + L".3");
			AddUniqueString(candidates, baseGuid + L".2");
			AddUniqueString(candidates, baseGuid + L".4");
			AddUniqueString(candidates, baseGuid + L".5");
			AddUniqueString(candidates, baseGuid + L".0");
		}
		else if (kind == ModuleTextKind::ObjectModule)
		{
			AddUniqueString(candidates, baseGuid + L".0");
			AddUniqueString(candidates, baseGuid + L".2");
			AddUniqueString(candidates, baseGuid + L".1");
			AddUniqueString(candidates, baseGuid + L".3");
			AddUniqueString(candidates, baseGuid + L".4");
			AddUniqueString(candidates, baseGuid + L".5");
		}
		else
		{
			AddUniqueString(candidates, baseGuid + L".0");
			AddUniqueString(candidates, baseGuid + L".1");
			AddUniqueString(candidates, baseGuid + L".2");
			AddUniqueString(candidates, baseGuid + L".3");
			AddUniqueString(candidates, baseGuid + L".4");
			AddUniqueString(candidates, baseGuid + L".5");
		}

		// Bare metadata file (<guid>) often contains object structure, not module text.
		// Keep it only for unknown mode; for object/manager modules it causes false positives.
		if (kind == ModuleTextKind::Unknown)
			AddUniqueString(candidates, baseGuid);
		return candidates;
	}

	String __fastcall ReadDiskFileRawText(const String& filePath, ModuleTextEncodingKind& encoding)
	{
		if (!FileExists(filePath))
		{
			encoding = ModuleTextEncodingKind::Unknown;
			return L"";
		}

		std::unique_ptr<TFileStream> fs(new TFileStream(filePath, fmOpenRead | fmShareDenyNone));
		TBytes bytes;
		std::unique_ptr<TBytesStream> sb(new TBytesStream(bytes));
		sb->CopyFrom(fs.get(), 0);
		return DecodeModuleText(sb->Bytes, sb->Size, encoding);
	}

	bool __fastcall TryReadDiskModuleFile(const String& filePath,
										  ModuleTextKind kind,
										  const String& metadataGuid,
										  const String& moduleDataGuid,
										  ModuleTextDocument& document)
	{
		ModuleTextEncodingKind encoding;
		String text = ReadDiskFileRawText(filePath, encoding);
		if (!FileExists(filePath))
			return false;

		if (!text.IsEmpty())
		{
			const bool objectLikeModuleKind = kind == ModuleTextKind::ObjectModule
				|| kind == ModuleTextKind::ManagerModule;
			const bool looksValid = objectLikeModuleKind
				? LooksLikeStrictModuleBody(text)
				: ModuleTextStorage::LooksLike1CModuleText(text);
			if (!looksValid)
				return false;
		}

		document.text = text;
		document.loaded = true;
		document.dirty = false;
		document.location.metadataGuid = metadataGuid;
		document.location.moduleDataGuid = moduleDataGuid;
		document.location.filePath = filePath;
		document.location.fileName = ExtractFileName(filePath);
		document.location.containerPath = ExtractFileDir(filePath);
		document.location.sourceRoot = ExtractFileDir(document.location.containerPath);
		document.location.kind = kind;
		document.location.encoding = encoding;
		document.location.editable = true;
		document.location.foundInSourceCF = true;
		return true;
	}

	bool __fastcall TryLoadFromSourceCfByGuid(const String& metadataGuid,
											  ModuleTextKind kind,
											  ModuleTextDocument& document)
	{
		const String normalizedGuid = ModuleTextStorage::NormalizeGuidFileName(metadataGuid);
		if (normalizedGuid.IsEmpty())
			return false;

		ModuleTextDocument emptyFallback;
		bool hasEmptyFallback = false;

		for (const auto& sourceRoot : GetSourceCfRoots())
		{
			if (!TDirectory::Exists(sourceRoot))
				continue;

			for (const auto& containerName : GetModuleContainerCandidates(normalizedGuid, kind))
			{
				ModuleTextDocument candidate;
				const String containerPath = TPath::Combine(sourceRoot, containerName);
				const String textPath = TPath::Combine(containerPath, L"text");
				if (TryReadDiskModuleFile(textPath, kind, metadataGuid, containerName, candidate))
				{
					if (kind != ModuleTextKind::ManagerModule || !candidate.text.IsEmpty())
					{
						document = candidate;
						return true;
					}

					if (!hasEmptyFallback)
					{
						emptyFallback = candidate;
						hasEmptyFallback = true;
					}
				}

				const String modulePath = TPath::Combine(containerPath, L"module");
				if (TryReadDiskModuleFile(modulePath, kind, metadataGuid, containerName, candidate))
				{
					if (kind != ModuleTextKind::ManagerModule || !candidate.text.IsEmpty())
					{
						document = candidate;
						return true;
					}

					if (!hasEmptyFallback)
					{
						emptyFallback = candidate;
						hasEmptyFallback = true;
					}
				}

				const String directPath = TPath::Combine(sourceRoot, containerName);
				if (TryReadDiskModuleFile(directPath, kind, metadataGuid, containerName, candidate))
				{
					if (kind != ModuleTextKind::ManagerModule || !candidate.text.IsEmpty())
					{
						document = candidate;
						return true;
					}

					if (!hasEmptyFallback)
					{
						emptyFallback = candidate;
						hasEmptyFallback = true;
					}
				}
			}
		}

		if (hasEmptyFallback)
		{
			document = emptyFallback;
			return true;
		}

		return false;
	}

	bool __fastcall TryLoadFromSourceCfByModuleName(const String& moduleName,
													ModuleTextKind kind,
													ModuleTextDocument& document)
	{
		if (moduleName.IsEmpty())
			return false;

		for (const auto& sourceRoot : GetSourceCfRoots())
		{
			if (!TDirectory::Exists(sourceRoot))
				continue;

			TStringDynArray files = TDirectory::GetFiles(sourceRoot);
			for (int i = 0; i < files.Length; ++i)
			{
				const String metadataFile = files[i];
				const String objectGuid = ExtractFileName(metadataFile);
				if (!ModuleTextStorage::IsGuidLike(objectGuid))
					continue;

				ModuleTextEncodingKind encoding;
				String metadataText = ReadDiskFileRawText(metadataFile, encoding);
				if (metadataText.Pos(moduleName) <= 0)
					continue;

				if (TryLoadFromSourceCfByGuid(objectGuid, kind, document))
					return true;
			}
		}

		return false;
	}

	void __fastcall CollectGuidReferences(tree* node, std::vector<String>& guids)
	{
		if (!node)
			return;

		if (ModuleTextStorage::IsGuidLike(node->get_value()))
			AddUniqueString(guids, node->get_value());

		for (int i = 0; i < node->get_num_subnode(); i++)
			CollectGuidReferences(node->get_subnode(i), guids);
	}

	String __fastcall FindEmbeddedModuleText(tree* node)
	{
		if (!node)
			return L"";

		if (node->get_type() == nd_string && ModuleTextStorage::LooksLike1CModuleText(node->get_value()))
			return node->get_value();

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			String found = FindEmbeddedModuleText(node->get_subnode(i));
			if (!found.IsEmpty())
				return found;
		}

		return L"";
	}

	String __fastcall ReadRootMetadataGuid(v8catalog* parent)
	{
		if (!parent)
			return L"";

		try
		{
			v8file* rootFile = parent->GetFile(L"root");
			std::unique_ptr<tree> rootTree(get_treeFromV8file(rootFile));
			std::vector<String> rootGuids;
			CollectGuidReferences(rootTree.get(), rootGuids);
			for (const auto& guid : rootGuids)
				return guid;
		}
		catch (...)
		{
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
			ModuleTextEncodingKind encoding;
			String text = DecodeModuleText(sb->Bytes, sb->Size, encoding);
			delete sb;
			return text;
		}
		catch (...)
		{
			delete sb;
			return L"";
		}
	}

	bool __fastcall LooksLikeStrictModuleBody(const String& value)
	{
		String text = Trim(value);
		if (text.IsEmpty())
			return false;

		if (text[1] == L'{')
			return false;

		const String upper = UpperCase(text);
		if (upper.Pos(L"ПРОЦЕДУРА") > 0 || upper.Pos(L"ФУНКЦИЯ") > 0
			|| upper.Pos(L"PROCEDURE") > 0 || upper.Pos(L"FUNCTION") > 0)
			return true;

		if (text.Pos(L";") > 0 && (text.Pos(L"=") > 0 || text.Pos(L"(") > 0 || text.Pos(L")") > 0))
			return true;

		// Allow short comment-only modules.
		if ((text.Pos(L"//") == 1 || text.Pos(L"//") == 2) && text.Length() < 4096)
			return true;

		return false;
	}

	String __fastcall ExtractConfigurationObjectGuid(const String& metadataText)
	{
		const String marker = L"{1,0,";
		int searchFrom = 1;
		while (searchFrom <= metadataText.Length())
		{
			const int relativePos = metadataText.SubString(searchFrom, metadataText.Length() - searchFrom + 1).Pos(marker);
			if (relativePos <= 0)
				break;

			const int markerPos = searchFrom + relativePos - 1;
			const int guidStart = markerPos + marker.Length();
			if (guidStart + 35 <= metadataText.Length())
			{
				String guid = metadataText.SubString(guidStart, 36);
				if (ModuleTextStorage::IsGuidLike(guid))
					return guid;
			}

			searchFrom = markerPos + marker.Length();
		}

		return L"";
	}


	String __fastcall ReadConfigurationObjectGuid(v8catalog* parent)
	{
		const String metadataGuid = ReadRootMetadataGuid(parent);
		if (metadataGuid.IsEmpty() || !parent)
			return metadataGuid;

		v8file* metadataFile = parent->GetFile(metadataGuid);
		String metadataText = ReadV8FileAsText(metadataFile);
		String objectGuid = ExtractConfigurationObjectGuid(metadataText);
		return objectGuid.IsEmpty() ? metadataGuid : objectGuid;
	}

	String __fastcall TryReadNamedTextFile(v8catalog* catalog, const String& fileName)
	{
		if (!catalog)
			return L"";

		v8file* file = catalog->GetFile(fileName);
		if (!file)
			return L"";

		String text = ReadV8FileAsText(file);
		return ModuleTextStorage::LooksLike1CModuleText(text) ? text : L"";
	}

	String __fastcall TryReadModuleContainer(v8file* file, bool strictContainerOnly = false)
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

		String directText = ReadV8FileAsText(file);
		if (strictContainerOnly)
		{
			if (LooksLikeStrictModuleBody(directText))
				return directText;
			return L"";
		}

		if (ModuleTextStorage::LooksLike1CModuleText(directText))
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

	void __fastcall WriteTextWithEncoding(TStream* stream, const String& text, ModuleTextEncodingKind encoding)
	{
		TBytes bytes;

		switch (encoding)
		{
			case ModuleTextEncodingKind::Utf16LeBom:
			{
				const unsigned char bom[] = {0xFF, 0xFE};
				stream->WriteBuffer((void*)bom, 2);
				bytes = TEncoding::Unicode->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Utf16Le:
			{
				bytes = TEncoding::Unicode->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Utf8Bom:
			{
				const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
				stream->WriteBuffer((void*)bom, 3);
				bytes = TEncoding::UTF8->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Ansi:
			{
				bytes = TEncoding::Default->GetBytes(text);
				break;
			}
			case ModuleTextEncodingKind::Utf8:
			case ModuleTextEncodingKind::Unknown:
			default:
			{
				bytes = TEncoding::UTF8->GetBytes(text);
				break;
			}
		}

		if (!bytes.empty())
			stream->WriteBuffer(&bytes[0], bytes.Length);
	}
}

namespace ModuleTextStorage
{
	bool __fastcall LooksLike1CModuleText(const String& value)
	{
		String trimmed = Trim(value);
		if (trimmed.IsEmpty() || trimmed[1] == L'{')
			return false;

		return value.Length() > 0
			&& (value.Pos(L"\n") > 0
				|| value.Pos(L"\r") > 0
				|| value.Pos(L"Процедура") > 0
				|| value.Pos(L"Функция") > 0
				|| value.Pos(L"КонецПроцедуры") > 0
				|| value.Pos(L"КонецФункции") > 0);
	}

	bool __fastcall IsGuidLike(const String& value)
	{
		if (value.Length() != 36)
			return false;

		for (int i = 1; i <= value.Length(); i++)
		{
			wchar_t ch = value[i];
			bool dash = i == 9 || i == 14 || i == 19 || i == 24;
			if (dash)
			{
				if (ch != L'-')
					return false;
			}
			else
			{
				bool hex = (ch >= L'0' && ch <= L'9')
					|| (ch >= L'a' && ch <= L'f')
					|| (ch >= L'A' && ch <= L'F');
				if (!hex)
					return false;
			}
		}

		return true;
	}

	String __fastcall NormalizeGuidFileName(const String& guid)
	{
		String result = Trim(guid).LowerCase();
		if (result.Length() >= 2 && result[1] == L'{' && result[result.Length()] == L'}')
			result = result.SubString(2, result.Length() - 2);
		return result;
	}

	ModuleTextDocument __fastcall LoadCommonModule(v8catalog* parent, const String& metadataGuid, const String& moduleName)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = ModuleTextKind::CommonModule;
		document.location.metadataGuid = metadataGuid;

		if (TryLoadFromSourceCfByGuid(metadataGuid, ModuleTextKind::CommonModule, document))
			return document;

		if (TryLoadFromSourceCfByModuleName(moduleName, ModuleTextKind::CommonModule, document))
			return document;

		if (parent && !metadataGuid.IsEmpty())
		{
			std::vector<String> candidates = GetModuleContainerCandidates(NormalizeGuidFileName(metadataGuid), ModuleTextKind::CommonModule);

			try
			{
				v8file* objectFile = parent->GetFile(metadataGuid);
				if (objectFile)
				{
					std::unique_ptr<tree> objectTree(get_treeFromV8file(objectFile));
					document.text = FindEmbeddedModuleText(objectTree.get());

					std::vector<String> referencedGuids;
					CollectGuidReferences(objectTree.get(), referencedGuids);
					for (const auto& referencedGuid : referencedGuids)
					{
						if (TryLoadFromSourceCfByGuid(referencedGuid, ModuleTextKind::CommonModule, document))
							return document;
						for (const auto& candidate : GetModuleContainerCandidates(NormalizeGuidFileName(referencedGuid), ModuleTextKind::CommonModule))
							AddUniqueString(candidates, candidate);
					}
				}
			}
			catch (...)
			{
			}

			for (size_t i = 0; i < candidates.size(); i++)
			{
				v8file* dataModule = parent->GetFile(candidates[i]);
				String text = TryReadModuleContainer(dataModule, true);
				if (!text.IsEmpty())
				{
					document.text = text;
					document.location.moduleDataGuid = candidates[i];
					document.location.editable = false;
					document.location.foundInSourceCF = false;
					return document;
				}
			}
		}

		return document;
	}

	ModuleTextDocument __fastcall LoadCommonForm(v8catalog* parent, const String& metadataGuid, const String& formName)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = ModuleTextKind::CommonForm;
		document.location.metadataGuid = metadataGuid;

		if (TryLoadFromSourceCfByGuid(metadataGuid, ModuleTextKind::CommonForm, document))
			return document;

		if (parent && !metadataGuid.IsEmpty())
		{
			v8file* dataForm = parent->GetFile(metadataGuid + L".0");
			String text = TryReadModuleContainer(dataForm, true);
			if (!text.IsEmpty())
			{
				document.text = text;
				document.location.moduleDataGuid = metadataGuid + L".0";
				document.location.editable = false;
				document.location.foundInSourceCF = false;
			}
		}

		return document;
	}

	ModuleTextDocument __fastcall LoadByMetadataObject(v8catalog* parent, const String& metadataGuid, const String& objectName, ModuleTextKind kind)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = kind;
		document.location.metadataGuid = metadataGuid;

		if (TryLoadFromSourceCfByGuid(metadataGuid, kind, document))
			return document;

		if (parent && !metadataGuid.IsEmpty())
		{
			std::vector<String> candidates = GetModuleContainerCandidates(NormalizeGuidFileName(metadataGuid), kind);

			try
			{
				v8file* objectFile = parent->GetFile(metadataGuid);
				if (objectFile)
				{
					std::unique_ptr<tree> objectTree(get_treeFromV8file(objectFile));

					std::vector<String> referencedGuids;
					CollectGuidReferences(objectTree.get(), referencedGuids);
					for (const auto& referencedGuid : referencedGuids)
					{
						if (TryLoadFromSourceCfByGuid(referencedGuid, kind, document))
							return document;
						for (const auto& candidate : GetModuleContainerCandidates(NormalizeGuidFileName(referencedGuid), kind))
							AddUniqueString(candidates, candidate);
					}
				}
			}
			catch (...)
			{
			}

			for (size_t i = 0; i < candidates.size(); i++)
			{
				v8file* file = parent->GetFile(candidates[i]);
				String text = TryReadModuleContainer(file, true);
				if (!text.IsEmpty())
				{
					document.text = text;
					document.location.moduleDataGuid = candidates[i];
					document.location.editable = false;
					document.location.foundInSourceCF = false;
					return document;
				}
			}
		}

		return document;
	}

	ModuleTextDocument __fastcall LoadBySourceCfModuleDataGuid(const String& metadataGuid, const String& moduleDataGuid, ModuleTextKind kind)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = kind;
		document.location.metadataGuid = metadataGuid;

		if (moduleDataGuid.IsEmpty())
			return document;

		for (const auto& sourceRoot : GetSourceCfRoots())
		{
			if (!TDirectory::Exists(sourceRoot))
				continue;

			const String containerPath = TPath::Combine(sourceRoot, moduleDataGuid);
			const String textPath = TPath::Combine(containerPath, L"text");
			const String modulePath = TPath::Combine(containerPath, L"module");

			auto loadExactTextFile = [&](const String& filePath) -> bool
			{
				if (!FileExists(filePath))
					return false;

				ModuleTextEncodingKind encoding = ModuleTextEncodingKind::Unknown;
				document.text = ReadDiskFileRawText(filePath, encoding);
				document.location.moduleDataGuid = moduleDataGuid;
				document.location.filePath = filePath;
				document.location.fileName = ExtractFileName(filePath);
				document.location.containerPath = ExtractFileDir(filePath);
				document.location.sourceRoot = ExtractFileDir(document.location.containerPath);
				document.location.encoding = encoding;
				document.location.editable = true;
				document.location.foundInSourceCF = true;
				document.dirty = false;
				document.loaded = true;
				return true;
			};

			if (loadExactTextFile(textPath))
				return document;
			if (loadExactTextFile(modulePath))
				return document;
		}

		return document;
	}

	ModuleTextDocument __fastcall LoadConfigurationModule(v8catalog* parent, ModuleTextKind kind)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = kind;

		const String rootMetadataGuid = ReadConfigurationObjectGuid(parent);
		document.location.metadataGuid = rootMetadataGuid;

		if (!rootMetadataGuid.IsEmpty())
		{
			if (TryLoadFromSourceCfByGuid(rootMetadataGuid, kind, document))
				return document;

			if (parent)
			{
				const String normalizedGuid = NormalizeGuidFileName(rootMetadataGuid);
				const std::vector<String> candidates = GetModuleContainerCandidates(normalizedGuid, kind);
				for (const auto& candidate : candidates)
				{
					String text = TryReadModuleContainer(parent->GetFile(candidate), true);
					if (!text.IsEmpty())
					{
						document.text = text;
						document.location.moduleDataGuid = candidate;
						document.location.editable = false;
						document.location.foundInSourceCF = false;
						return document;
					}
				}
			}
		}

		return document;
	}

	bool __fastcall SaveDocument(ModuleTextDocument& document, const String& newText, String& errorText)
	{
		errorText = L"";

		if (!document.location.editable || document.location.filePath.IsEmpty())
		{
			errorText = L"Не найден редактируемый файл модуля в SourceCF.";
			return false;
		}

		const String target = document.location.filePath;
		const String dir = ExtractFileDir(target);
		if (!TDirectory::Exists(dir))
		{
			errorText = L"Каталог модуля не существует: " + dir;
			return false;
		}

		const String tmp = TPath::Combine(dir, ExtractFileName(target) + L".codex.tmp");
		try
		{
			{
				std::unique_ptr<TFileStream> out(new TFileStream(tmp, fmCreate));
				WriteTextWithEncoding(out.get(), newText, document.location.encoding);
			}

			if (FileExists(target))
				TFile::Delete(target);
			TFile::Move(tmp, target);

			document.text = newText;
			document.dirty = false;
			document.loaded = true;
			return true;
		}
		catch (const Exception& e)
		{
			if (FileExists(tmp))
				TFile::Delete(tmp);
			errorText = e.Message;
			return false;
		}
	}

	String __fastcall DescribeLocation(const ModuleTextLocation& location)
	{
		if (!location.filePath.IsEmpty())
			return location.filePath;
		if (!location.containerPath.IsEmpty())
			return location.containerPath;
		if (!location.moduleDataGuid.IsEmpty())
			return location.moduleDataGuid;
		return L"";
	}
}
