//---------------------------------------------------------------------------


#include <filesystem>
#include <memory>
#include <vector>
#include <cstring>
#include "../../include/v8reader_core/io/MemoryByteStream.h"
#include "../../include/v8reader_core/io/StdFileStream.h"

#include "ModuleTextStorage.h"
#include "ModuleTextEncodingUtils.h"

//---------------------------------------------------------------------------

namespace
{
	namespace fs = std::filesystem;

	fs::path ToFsPath(const String& path)
	{
		return fs::path(path.c_str());
	}

	String FromFsPath(const fs::path& path)
	{
		return String(path.wstring().c_str());
	}

	String CombinePath(const String& left, const String& right)
	{
		return FromFsPath(ToFsPath(left) / ToFsPath(right));
	}

	bool DirectoryExistsFs(const String& path)
	{
		std::error_code ec;
		return fs::is_directory(ToFsPath(path), ec);
	}

	bool FileExistsFs(const String& path)
	{
		std::error_code ec;
		return fs::is_regular_file(ToFsPath(path), ec);
	}

	std::vector<String> GetFilesInDirectory(const String& directoryPath)
	{
		std::vector<String> files;
		std::error_code ec;
		for (const auto& entry : fs::directory_iterator(ToFsPath(directoryPath), ec))
		{
			if (ec)
				break;

			std::error_code fileEc;
			if (fs::is_regular_file(entry.path(), fileEc) && !fileEc)
				files.push_back(FromFsPath(entry.path()));
		}
		return files;
	}

	bool DeleteFileFs(const String& path)
	{
		std::error_code ec;
		return fs::remove(ToFsPath(path), ec);
	}

	bool MoveFileFs(const String& fromPath, const String& toPath)
	{
		std::error_code ec;
		fs::rename(ToFsPath(fromPath), ToFsPath(toPath), ec);
		return !ec;
	}

	bool LooksLikeStrictModuleBody(const String& value);

	void AddUniquePath(std::vector<String>& values, const String& value)
	{
		if (value.IsEmpty())
			return;

		const String normalized = FromFsPath(ToFsPath(value).lexically_normal()).UpperCase();
		for (const auto& existing : values)
		{
			const String existingNormalized = FromFsPath(ToFsPath(existing).lexically_normal()).UpperCase();
			if (existingNormalized == normalized)
				return;
		}

		values.push_back(value);
	}

	std::vector<String> GetSourceCfRoots()
	{
		std::vector<String> roots;
		AddUniquePath(roots, CombinePath(GetCurrentDir(), L"SourceCF"));
		AddUniquePath(roots, CombinePath(ExtractFilePath(ParamStr(0)), L"SourceCF"));
		return roots;
	}

	void AddUniqueString(std::vector<String>& values, const String& value)
	{
		if (value.IsEmpty())
			return;

		String upperValue = value.UpperCase();
		for (const auto& existing : values)
			if (existing.UpperCase() == upperValue)
				return;

		values.push_back(value);
	}

	std::vector<String> GetModuleContainerCandidates(const String& baseGuid,
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

	String ReadDiskFileRawText(const String& filePath, ModuleTextEncodingKind& encoding)
	{
		if (!FileExistsFs(filePath))
		{
			encoding = ModuleTextEncodingKind::Unknown;
			return L"";
		}

		v8reader::core::io::StdFileStream fs(ToFsPath(filePath), v8reader::core::io::FileOpenMode::ReadOnly);
		v8reader::core::io::MemoryByteStream sb;
		ByteVector chunk(64 * 1024);
		while (true)
		{
			const std::size_t bytesRead = fs.Read(chunk.data(), chunk.size());
			if (bytesRead == 0)
				break;
			sb.Write(chunk.data(), bytesRead);
		}

		const std::vector<std::uint8_t>& payload = sb.Data();
		TBytes bytes;
		const int bytesCount = static_cast<int>(payload.size());
		bytes.Length = bytesCount;
		if (bytesCount > 0)
			std::memcpy(&bytes[0], payload.data(), static_cast<std::size_t>(bytesCount));

		return ModuleTextEncodingUtils::DecodeModuleText(bytes, bytesCount, encoding);
	}

	bool TryReadDiskModuleFile(const String& filePath,
										  ModuleTextKind kind,
										  const String& metadataGuid,
										  const String& moduleDataGuid,
										  ModuleTextDocument& document)
	{
		ModuleTextEncodingKind encoding;
		String text = ReadDiskFileRawText(filePath, encoding);
		if (!FileExistsFs(filePath))
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

	bool TryLoadFromSourceCfByGuid(const String& metadataGuid,
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
			if (!DirectoryExistsFs(sourceRoot))
				continue;

			for (const auto& containerName : GetModuleContainerCandidates(normalizedGuid, kind))
			{
				ModuleTextDocument candidate;
				const String containerPath = CombinePath(sourceRoot, containerName);
				const String textPath = CombinePath(containerPath, L"text");
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

				const String modulePath = CombinePath(containerPath, L"module");
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

				const String directPath = CombinePath(sourceRoot, containerName);
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

	bool TryLoadFromSourceCfByModuleName(const String& moduleName,
													ModuleTextKind kind,
													ModuleTextDocument& document)
	{
		if (moduleName.IsEmpty())
			return false;

		for (const auto& sourceRoot : GetSourceCfRoots())
		{
			if (!DirectoryExistsFs(sourceRoot))
				continue;

			const std::vector<String> files = GetFilesInDirectory(sourceRoot);
			for (const auto& metadataFile : files)
			{
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

	void CollectGuidReferences(tree* node, std::vector<String>& guids)
	{
		if (!node)
			return;

		if (ModuleTextStorage::IsGuidLike(node->get_value()))
			AddUniqueString(guids, node->get_value());

		for (int i = 0; i < node->get_num_subnode(); i++)
			CollectGuidReferences(node->get_subnode(i), guids);
	}

	String FindEmbeddedModuleText(tree* node)
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

	String ReadRootMetadataGuid(v8catalog* parent)
	{
		if (!parent)
			return L"";

		try
		{
			v8file* rootFile = parent->GetFile16(u"root");
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

	String ReadV8FileAsText(v8file* file)
	{
		if (!file)
			return L"";

		v8reader::core::io::MemoryByteStream sb;
		try
		{
			file->SaveToByteStream(sb);
			const std::vector<std::uint8_t>& payload = sb.Data();
			TBytes bytes;
			const int bytesCount = static_cast<int>(payload.size());
			bytes.Length = bytesCount;
			if (bytesCount > 0)
				std::memcpy(&bytes[0], payload.data(), static_cast<std::size_t>(bytesCount));
			ModuleTextEncodingKind encoding;
			String text = ModuleTextEncodingUtils::DecodeModuleText(bytes, bytesCount, encoding);
			return text;
		}
		catch (...)
		{
			return L"";
		}
	}

	bool LooksLikeStrictModuleBody(const String& value)
	{
		String text = Trim(value);
		if (text.IsEmpty())
			return false;

		if (text[1] == L'{')
			return false;

		const String upper = UpperCase(text);
		if (upper.Pos(L"–ü–†–û–¶–ï–î–£–†–ê") > 0 || upper.Pos(L"–§–£–ù–ö–¶–ò–Ø") > 0
			|| upper.Pos(L"PROCEDURE") > 0 || upper.Pos(L"FUNCTION") > 0)
			return true;

		if (text.Pos(L";") > 0 && (text.Pos(L"=") > 0 || text.Pos(L"(") > 0 || text.Pos(L")") > 0))
			return true;

		// Allow short comment-only modules.
		if ((text.Pos(L"//") == 1 || text.Pos(L"//") == 2) && text.Length() < 4096)
			return true;

		return false;
	}

	String ExtractConfigurationObjectGuid(const String& metadataText)
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


	String ReadConfigurationObjectGuid(v8catalog* parent)
	{
		const String metadataGuid = ReadRootMetadataGuid(parent);
		if (metadataGuid.IsEmpty() || !parent)
			return metadataGuid;

		v8file* metadataFile = parent->GetFile16(V8Utf16FromString(metadataGuid));
		String metadataText = ReadV8FileAsText(metadataFile);
		String objectGuid = ExtractConfigurationObjectGuid(metadataText);
		return objectGuid.IsEmpty() ? metadataGuid : objectGuid;
	}

	String TryReadNamedTextFile(v8catalog* catalog, const String& fileName)
	{
		if (!catalog)
			return L"";

		v8file* file = catalog->GetFile16(V8Utf16FromString(fileName));
		if (!file)
			return L"";

		String text = ReadV8FileAsText(file);
		return ModuleTextStorage::LooksLike1CModuleText(text) ? text : L"";
	}

	String TryReadModuleContainer(v8file* file, bool strictContainerOnly = false)
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
						String childName = V8StringFromUtf16(child->GetFileName16()).LowerCase();
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

}

namespace ModuleTextStorage
{
	bool LooksLike1CModuleText(const String& value)
	{
		String trimmed = Trim(value);
		if (trimmed.IsEmpty() || trimmed[1] == L'{')
			return false;

		return value.Length() > 0
			&& (value.Pos(L"\n") > 0
				|| value.Pos(L"\r") > 0
				|| value.Pos(L"–ü—Ä–æ—Ü–µ–¥—É—Ä–∞") > 0
				|| value.Pos(L"–§—É–Ω–∫—Ü–∏—è") > 0
				|| value.Pos(L"–ö–æ–Ω–µ—Ü–ü—Ä–æ—Ü–µ–¥—É—Ä—ã") > 0
				|| value.Pos(L"–ö–æ–Ω–µ—Ü–§—É–Ω–∫—Ü–∏–∏") > 0);
	}

	bool IsGuidLike(const String& value)
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

	String NormalizeGuidFileName(const String& guid)
	{
		String result = Trim(guid).LowerCase();
		if (result.Length() >= 2 && result[1] == L'{' && result[result.Length()] == L'}')
			result = result.SubString(2, result.Length() - 2);
		return result;
	}

	ModuleTextDocument LoadCommonModule(v8catalog* parent, const String& metadataGuid, const String& moduleName)
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
				v8file* objectFile = parent->GetFile16(V8Utf16FromString(metadataGuid));
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
				v8file* dataModule = parent->GetFile16(V8Utf16FromString(candidates[i]));
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

	ModuleTextDocument LoadCommonForm(v8catalog* parent, const String& metadataGuid, const String& formName)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = ModuleTextKind::CommonForm;
		document.location.metadataGuid = metadataGuid;

		if (TryLoadFromSourceCfByGuid(metadataGuid, ModuleTextKind::CommonForm, document))
			return document;

		if (parent && !metadataGuid.IsEmpty())
		{
			v8file* dataForm = parent->GetFile16(V8Utf16FromString(metadataGuid + L".0"));
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

	ModuleTextDocument LoadByMetadataObject(v8catalog* parent, const String& metadataGuid, const String& objectName, ModuleTextKind kind)
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
				v8file* objectFile = parent->GetFile16(V8Utf16FromString(metadataGuid));
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
				v8file* file = parent->GetFile16(V8Utf16FromString(candidates[i]));
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

	ModuleTextDocument LoadBySourceCfModuleDataGuid(const String& metadataGuid, const String& moduleDataGuid, ModuleTextKind kind)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = kind;
		document.location.metadataGuid = metadataGuid;

		if (moduleDataGuid.IsEmpty())
			return document;

		for (const auto& sourceRoot : GetSourceCfRoots())
		{
			if (!DirectoryExistsFs(sourceRoot))
				continue;

			const String containerPath = CombinePath(sourceRoot, moduleDataGuid);
			const String textPath = CombinePath(containerPath, L"text");
			const String modulePath = CombinePath(containerPath, L"module");

			auto loadExactTextFile = [&](const String& filePath) -> bool
			{
				if (!FileExistsFs(filePath))
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

	ModuleTextDocument LoadConfigurationModule(v8catalog* parent, ModuleTextKind kind)
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
					String text = TryReadModuleContainer(parent->GetFile16(V8Utf16FromString(candidate)), true);
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

	bool SaveDocument(ModuleTextDocument& document, const String& newText, String& errorText)
	{
		errorText = L"";

		if (!document.location.editable || document.location.filePath.IsEmpty())
		{
			errorText = L"–ù–µ –Ω–∞–π–¥–µ–Ω —Ä–µ–¥–∞–∫—Ç–∏—Ä—É–µ–º—ã–π —Ñ–∞–π–ª –º–æ–¥—É–ª—è –≤ SourceCF.";
			return false;
		}

		const String target = document.location.filePath;
		const String dir = ExtractFileDir(target);
		if (!DirectoryExistsFs(dir))
		{
			errorText = L"–ö–∞—Ç–∞–ª–æ–≥ –º–æ–¥—É–ª—è –Ω–µ —Å—É—â–µ—Å—Ç–≤—É–µ—Ç: " + dir;
			return false;
		}

		const String tmp = CombinePath(dir, ExtractFileName(target) + L".codex.tmp");
		try
		{
			{
				v8reader::core::io::StdFileStream out(ToFsPath(tmp), v8reader::core::io::FileOpenMode::CreateTruncate);
				ModuleTextEncodingUtils::WriteTextWithEncoding(out, newText, document.location.encoding);
			}

			if (FileExistsFs(target) && !DeleteFileFs(target))
			{
				errorText = L"ÕÂ Û‰‡ÎÓÒ¸ Û‰‡ÎËÚ¸ ËÒıÓ‰Ì˚È Ù‡ÈÎ ÏÓ‰ÛÎˇ: " + target;
				return false;
			}
			if (!MoveFileFs(tmp, target))
			{
				errorText = L"ÕÂ Û‰‡ÎÓÒ¸ ÔÂÂÏÂÒÚËÚ¸ ‚ÂÏÂÌÌ˚È Ù‡ÈÎ ÏÓ‰ÛÎˇ: " + tmp;
				return false;
			}

			document.text = newText;
			document.dirty = false;
			document.loaded = true;
			return true;
		}
		catch (const Exception& e)
		{
			if (FileExistsFs(tmp))
				DeleteFileFs(tmp);
			errorText = e.Message;
			return false;
		}
	}

	String DescribeLocation(const ModuleTextLocation& location)
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

