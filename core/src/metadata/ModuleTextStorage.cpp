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
	inline LegacyText ToVclString(const Utf16String& value)
	{
		return LegacyText(reinterpret_cast<const wchar_t*>(value.c_str()));
	}
}

namespace ModuleTextStorage
{
	bool LooksLike1CModuleText(const LegacyText& value);
	bool IsGuidLike(const LegacyText& value);
	LegacyText NormalizeGuidFileName(const LegacyText& guid);
	ModuleTextDocument LoadCommonModule(v8catalog* parent, const LegacyText& metadataGuid, const LegacyText& moduleName);
	ModuleTextDocument LoadCommonForm(v8catalog* parent, const LegacyText& metadataGuid, const LegacyText& formName);
	ModuleTextDocument LoadByMetadataObject(v8catalog* parent, const LegacyText& metadataGuid, const LegacyText& objectName, ModuleTextKind kind);
	ModuleTextDocument LoadBySourceCfModuleDataGuid(const LegacyText& metadataGuid, const LegacyText& moduleDataGuid, ModuleTextKind kind);
}

namespace
{
	namespace fs = std::filesystem;

	fs::path ToFsPath(const LegacyText& path)
	{
		return fs::path(path.c_str());
	}

	LegacyText FromFsPath(const fs::path& path)
	{
		return LegacyText(path.wstring().c_str());
	}

	LegacyText CombinePath(const LegacyText& left, const LegacyText& right)
	{
		return FromFsPath(ToFsPath(left) / ToFsPath(right));
	}

	bool DirectoryExistsFs(const LegacyText& path)
	{
		std::error_code ec;
		return fs::is_directory(ToFsPath(path), ec);
	}

	bool FileExistsFs(const LegacyText& path)
	{
		std::error_code ec;
		return fs::is_regular_file(ToFsPath(path), ec);
	}

	std::vector<LegacyText> GetFilesInDirectory(const LegacyText& directoryPath)
	{
		std::vector<LegacyText> files;
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

	bool DeleteFileFs(const LegacyText& path)
	{
		std::error_code ec;
		return fs::remove(ToFsPath(path), ec);
	}

	bool MoveFileFs(const LegacyText& fromPath, const LegacyText& toPath)
	{
		std::error_code ec;
		fs::rename(ToFsPath(fromPath), ToFsPath(toPath), ec);
		return !ec;
	}

	bool LooksLikeStrictModuleBody(const LegacyText& value);

	void AddUniquePath(std::vector<LegacyText>& values, const LegacyText& value)
	{
		if (value.IsEmpty())
			return;

		const LegacyText normalized = FromFsPath(ToFsPath(value).lexically_normal()).UpperCase();
		for (const auto& existing : values)
		{
			const LegacyText existingNormalized = FromFsPath(ToFsPath(existing).lexically_normal()).UpperCase();
			if (existingNormalized == normalized)
				return;
		}

		values.push_back(value);
	}

	std::vector<LegacyText> GetSourceCfRoots()
	{
		std::vector<LegacyText> roots;
		AddUniquePath(roots, CombinePath(GetCurrentDir(), L"SourceCF"));
		AddUniquePath(roots, CombinePath(ExtractFilePath(ParamStr(0)), L"SourceCF"));
		return roots;
	}

	void AddUniqueString(std::vector<LegacyText>& values, const LegacyText& value)
	{
		if (value.IsEmpty())
			return;

		LegacyText upperValue = value.UpperCase();
		for (const auto& existing : values)
			if (existing.UpperCase() == upperValue)
				return;

		values.push_back(value);
	}

	std::vector<LegacyText> GetModuleContainerCandidates(const LegacyText& baseGuid,
		ModuleTextKind kind = ModuleTextKind::Unknown)
	{
		std::vector<LegacyText> candidates;

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

	LegacyText ReadDiskFileRawText(const LegacyText& filePath, ModuleTextEncodingKind& encoding)
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

	bool TryReadDiskModuleFile(const LegacyText& filePath,
										  ModuleTextKind kind,
										  const LegacyText& metadataGuid,
										  const LegacyText& moduleDataGuid,
										  ModuleTextDocument& document)
	{
		ModuleTextEncodingKind encoding;
		LegacyText text = ReadDiskFileRawText(filePath, encoding);
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

		document.text = V8Utf16FromString(text);
		document.loaded = true;
		document.dirty = false;
		document.location.metadataGuid = V8Utf16FromString(metadataGuid);
		document.location.moduleDataGuid = V8Utf16FromString(moduleDataGuid);
		document.location.filePath = V8Utf16FromString(filePath);
		document.location.fileName = V8Utf16FromString(ExtractFileName(filePath));
		document.location.containerPath = V8Utf16FromString(ExtractFileDir(filePath));
		document.location.sourceRoot = V8Utf16FromString(ExtractFileDir(filePath));
		document.location.kind = kind;
		document.location.encoding = encoding;
		document.location.editable = true;
		document.location.foundInSourceCF = true;
		return true;
	}

	bool TryLoadFromSourceCfByGuid(const LegacyText& metadataGuid,
											  ModuleTextKind kind,
											  ModuleTextDocument& document)
	{
		const LegacyText normalizedGuid = ModuleTextStorage::NormalizeGuidFileName(metadataGuid);
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
				const LegacyText containerPath = CombinePath(sourceRoot, containerName);
				const LegacyText textPath = CombinePath(containerPath, L"text");
				if (TryReadDiskModuleFile(textPath, kind, metadataGuid, containerName, candidate))
				{
					if (kind != ModuleTextKind::ManagerModule || !candidate.text.empty())
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

				const LegacyText modulePath = CombinePath(containerPath, L"module");
				if (TryReadDiskModuleFile(modulePath, kind, metadataGuid, containerName, candidate))
				{
					if (kind != ModuleTextKind::ManagerModule || !candidate.text.empty())
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

				const LegacyText directPath = CombinePath(sourceRoot, containerName);
				if (TryReadDiskModuleFile(directPath, kind, metadataGuid, containerName, candidate))
				{
					if (kind != ModuleTextKind::ManagerModule || !candidate.text.empty())
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

	bool TryLoadFromSourceCfByModuleName(const LegacyText& moduleName,
													ModuleTextKind kind,
													ModuleTextDocument& document)
	{
		if (moduleName.IsEmpty())
			return false;

		for (const auto& sourceRoot : GetSourceCfRoots())
		{
			if (!DirectoryExistsFs(sourceRoot))
				continue;

			const std::vector<LegacyText> files = GetFilesInDirectory(sourceRoot);
			for (const auto& metadataFile : files)
			{
				const LegacyText objectGuid = ExtractFileName(metadataFile);
				if (!ModuleTextStorage::IsGuidLike(objectGuid))
					continue;

				ModuleTextEncodingKind encoding;
				LegacyText metadataText = ReadDiskFileRawText(metadataFile, encoding);
				if (metadataText.Pos(moduleName) <= 0)
					continue;

				if (TryLoadFromSourceCfByGuid(objectGuid, kind, document))
					return true;
			}
		}

		return false;
	}

	void CollectGuidReferences(tree* node, std::vector<LegacyText>& guids)
	{
		if (!node)
			return;

		if (ModuleTextStorage::IsGuidLike(node->get_value()))
			AddUniqueString(guids, node->get_value());

		for (int i = 0; i < node->get_num_subnode(); i++)
			CollectGuidReferences(node->get_subnode(i), guids);
	}

	LegacyText FindEmbeddedModuleText(tree* node)
	{
		if (!node)
			return L"";

		if (node->get_type() == nd_string && ModuleTextStorage::LooksLike1CModuleText(node->get_value()))
			return node->get_value();

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			LegacyText found = FindEmbeddedModuleText(node->get_subnode(i));
			if (!found.IsEmpty())
				return found;
		}

		return L"";
	}

	LegacyText ReadRootMetadataGuid(v8catalog* parent)
	{
		if (!parent)
			return L"";

		try
		{
			v8file* rootFile = parent->GetFile16(u"root");
			std::unique_ptr<tree> rootTree(get_treeFromV8file(rootFile));
			std::vector<LegacyText> rootGuids;
			CollectGuidReferences(rootTree.get(), rootGuids);
			for (const auto& guid : rootGuids)
				return guid;
		}
		catch (...)
		{
		}

		return L"";
	}

	LegacyText ReadV8FileAsText(v8file* file)
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
			LegacyText text = ModuleTextEncodingUtils::DecodeModuleText(bytes, bytesCount, encoding);
			return text;
		}
		catch (...)
		{
			return L"";
		}
	}

	bool LooksLikeStrictModuleBody(const LegacyText& value)
	{
		LegacyText text = Trim(value);
		if (text.IsEmpty())
			return false;

		if (text[1] == L'{')
			return false;

		const LegacyText upper = UpperCase(text);
		if (upper.Pos(L"РџР РћР¦Р•Р”РЈР Рђ") > 0 || upper.Pos(L"Р¤РЈРќРљР¦РРЇ") > 0
			|| upper.Pos(L"PROCEDURE") > 0 || upper.Pos(L"FUNCTION") > 0)
			return true;

		if (text.Pos(L";") > 0 && (text.Pos(L"=") > 0 || text.Pos(L"(") > 0 || text.Pos(L")") > 0))
			return true;

		// Allow short comment-only modules.
		if ((text.Pos(L"//") == 1 || text.Pos(L"//") == 2) && text.Length() < 4096)
			return true;

		return false;
	}

	LegacyText ExtractConfigurationObjectGuid(const LegacyText& metadataText)
	{
		const LegacyText marker = L"{1,0,";
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
				LegacyText guid = metadataText.SubString(guidStart, 36);
				if (ModuleTextStorage::IsGuidLike(guid))
					return guid;
			}

			searchFrom = markerPos + marker.Length();
		}

		return L"";
	}


	LegacyText ReadConfigurationObjectGuid(v8catalog* parent)
	{
		const LegacyText metadataGuid = ReadRootMetadataGuid(parent);
		if (metadataGuid.IsEmpty() || !parent)
			return metadataGuid;

		v8file* metadataFile = parent->GetFile16(V8Utf16FromString(metadataGuid));
		LegacyText metadataText = ReadV8FileAsText(metadataFile);
		LegacyText objectGuid = ExtractConfigurationObjectGuid(metadataText);
		return objectGuid.IsEmpty() ? metadataGuid : objectGuid;
	}

	LegacyText TryReadNamedTextFile(v8catalog* catalog, const LegacyText& fileName)
	{
		if (!catalog)
			return L"";

		v8file* file = catalog->GetFile16(V8Utf16FromString(fileName));
		if (!file)
			return L"";

		LegacyText text = ReadV8FileAsText(file);
		return ModuleTextStorage::LooksLike1CModuleText(text) ? text : L"";
	}

	LegacyText TryReadModuleContainer(v8file* file, bool strictContainerOnly = false)
	{
		if (!file)
			return L"";

		try
		{
			v8catalog* catalog = new v8catalog(file);
			if (catalog)
			{
				catalog->ClearIs8316();

				LegacyText text = TryReadNamedTextFile(catalog, L"text");
				if (text.IsEmpty())
					text = TryReadNamedTextFile(catalog, L"module");

				if (text.IsEmpty())
				{
					for (v8file* child = catalog->GetFirst(); child; child = child->GetNext())
					{
						const Utf16String childName16 = child->GetFileName16();
						LegacyText childName(reinterpret_cast<const wchar_t*>(childName16.c_str()));
						childName = childName.LowerCase();
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

		LegacyText directText = ReadV8FileAsText(file);
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
	bool LooksLike1CModuleText(const LegacyText& value)
	{
		LegacyText trimmed = Trim(value);
		if (trimmed.IsEmpty() || trimmed[1] == L'{')
			return false;

		return value.Length() > 0
			&& (value.Pos(L"\n") > 0
				|| value.Pos(L"\r") > 0
				|| value.Pos(L"РџСЂРѕС†РµРґСѓСЂР°") > 0
				|| value.Pos(L"Р¤СѓРЅРєС†РёСЏ") > 0
				|| value.Pos(L"РљРѕРЅРµС†РџСЂРѕС†РµРґСѓСЂС‹") > 0
				|| value.Pos(L"РљРѕРЅРµС†Р¤СѓРЅРєС†РёРё") > 0);
	}

	bool IsGuidLike(const LegacyText& value)
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

	LegacyText NormalizeGuidFileName(const LegacyText& guid)
	{
		LegacyText result = Trim(guid).LowerCase();
		if (result.Length() >= 2 && result[1] == L'{' && result[result.Length()] == L'}')
			result = result.SubString(2, result.Length() - 2);
		return result;
	}

	ModuleTextDocument LoadCommonModule(v8catalog* parent, const LegacyText& metadataGuid, const LegacyText& moduleName)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = ModuleTextKind::CommonModule;
		document.location.metadataGuid = V8Utf16FromString(metadataGuid);

		if (TryLoadFromSourceCfByGuid(metadataGuid, ModuleTextKind::CommonModule, document))
			return document;

		if (TryLoadFromSourceCfByModuleName(moduleName, ModuleTextKind::CommonModule, document))
			return document;

		if (parent && !metadataGuid.IsEmpty())
		{
			std::vector<LegacyText> candidates = GetModuleContainerCandidates(NormalizeGuidFileName(metadataGuid), ModuleTextKind::CommonModule);

			try
			{
				v8file* objectFile = parent->GetFile16(V8Utf16FromString(metadataGuid));
				if (objectFile)
				{
					std::unique_ptr<tree> objectTree(get_treeFromV8file(objectFile));
					document.text = V8Utf16FromString(FindEmbeddedModuleText(objectTree.get()));

					std::vector<LegacyText> referencedGuids;
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
				LegacyText text = TryReadModuleContainer(dataModule, true);
				if (!text.IsEmpty())
				{
					document.text = V8Utf16FromString(text);
					document.location.moduleDataGuid = V8Utf16FromString(candidates[i]);
					document.location.editable = false;
					document.location.foundInSourceCF = false;
					return document;
				}
			}
		}

		return document;
	}

	ModuleTextDocument LoadCommonForm(v8catalog* parent, const LegacyText& metadataGuid, const LegacyText& formName)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = ModuleTextKind::CommonForm;
		document.location.metadataGuid = V8Utf16FromString(metadataGuid);

		if (TryLoadFromSourceCfByGuid(metadataGuid, ModuleTextKind::CommonForm, document))
			return document;

		if (parent && !metadataGuid.IsEmpty())
		{
			v8file* dataForm = parent->GetFile16(V8Utf16FromString(metadataGuid + L".0"));
			LegacyText text = TryReadModuleContainer(dataForm, true);
			if (!text.IsEmpty())
			{
				document.text = V8Utf16FromString(text);
				document.location.moduleDataGuid = V8Utf16FromString(metadataGuid + L".0");
				document.location.editable = false;
				document.location.foundInSourceCF = false;
			}
		}

		return document;
	}

	ModuleTextDocument LoadByMetadataObject(v8catalog* parent, const LegacyText& metadataGuid, const LegacyText& objectName, ModuleTextKind kind)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = kind;
		document.location.metadataGuid = V8Utf16FromString(metadataGuid);

		if (TryLoadFromSourceCfByGuid(metadataGuid, kind, document))
			return document;

		if (parent && !metadataGuid.IsEmpty())
		{
			std::vector<LegacyText> candidates = GetModuleContainerCandidates(NormalizeGuidFileName(metadataGuid), kind);

			try
			{
				v8file* objectFile = parent->GetFile16(V8Utf16FromString(metadataGuid));
				if (objectFile)
				{
					std::unique_ptr<tree> objectTree(get_treeFromV8file(objectFile));

					std::vector<LegacyText> referencedGuids;
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
				LegacyText text = TryReadModuleContainer(file, true);
				if (!text.IsEmpty())
				{
					document.text = V8Utf16FromString(text);
					document.location.moduleDataGuid = V8Utf16FromString(candidates[i]);
					document.location.editable = false;
					document.location.foundInSourceCF = false;
					return document;
				}
			}
		}

		return document;
	}

	ModuleTextDocument LoadBySourceCfModuleDataGuid(const LegacyText& metadataGuid, const LegacyText& moduleDataGuid, ModuleTextKind kind)
	{
		ModuleTextDocument document;
		document.loaded = true;
		document.location.kind = kind;
		document.location.metadataGuid = V8Utf16FromString(metadataGuid);

		if (moduleDataGuid.IsEmpty())
			return document;

		for (const auto& sourceRoot : GetSourceCfRoots())
		{
			if (!DirectoryExistsFs(sourceRoot))
				continue;

			const LegacyText containerPath = CombinePath(sourceRoot, moduleDataGuid);
			const LegacyText textPath = CombinePath(containerPath, L"text");
			const LegacyText modulePath = CombinePath(containerPath, L"module");

			auto loadExactTextFile = [&](const LegacyText& filePath) -> bool
			{
				if (!FileExistsFs(filePath))
					return false;

				ModuleTextEncodingKind encoding = ModuleTextEncodingKind::Unknown;
				document.text = V8Utf16FromString(ReadDiskFileRawText(filePath, encoding));
				document.location.moduleDataGuid = V8Utf16FromString(moduleDataGuid);
				document.location.filePath = V8Utf16FromString(filePath);
				document.location.fileName = V8Utf16FromString(ExtractFileName(filePath));
				document.location.containerPath = V8Utf16FromString(ExtractFileDir(filePath));
				document.location.sourceRoot = V8Utf16FromString(ExtractFileDir(filePath));
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

		const LegacyText rootMetadataGuid = ReadConfigurationObjectGuid(parent);
		document.location.metadataGuid = V8Utf16FromString(rootMetadataGuid);

		if (!rootMetadataGuid.IsEmpty())
		{
			if (TryLoadFromSourceCfByGuid(rootMetadataGuid, kind, document))
				return document;

			if (parent)
			{
				const LegacyText normalizedGuid = NormalizeGuidFileName(rootMetadataGuid);
				const std::vector<LegacyText> candidates = GetModuleContainerCandidates(normalizedGuid, kind);
				for (const auto& candidate : candidates)
				{
					LegacyText text = TryReadModuleContainer(parent->GetFile16(V8Utf16FromString(candidate)), true);
					if (!text.IsEmpty())
					{
						document.text = V8Utf16FromString(text);
						document.location.moduleDataGuid = V8Utf16FromString(candidate);
						document.location.editable = false;
						document.location.foundInSourceCF = false;
						return document;
					}
				}
			}
		}

		return document;
	}

	Utf16String NormalizeGuidFileName(const Utf16String& guid)
	{
		return V8Utf16FromString(NormalizeGuidFileName(ToVclString(guid)));
	}

	bool IsGuidLike(const Utf16String& value)
	{
		return IsGuidLike(ToVclString(value));
	}

	bool LooksLike1CModuleText(const Utf16String& value)
	{
		return LooksLike1CModuleText(ToVclString(value));
	}

	ModuleTextDocument LoadCommonModule(v8catalog* parent, const Utf16String& metadataGuid, const Utf16String& moduleName)
	{
		return LoadCommonModule(parent, ToVclString(metadataGuid), ToVclString(moduleName));
	}

	ModuleTextDocument LoadCommonForm(v8catalog* parent, const Utf16String& metadataGuid, const Utf16String& formName)
	{
		return LoadCommonForm(parent, ToVclString(metadataGuid), ToVclString(formName));
	}

	ModuleTextDocument LoadByMetadataObject(v8catalog* parent, const Utf16String& metadataGuid, const Utf16String& objectName, ModuleTextKind kind)
	{
		return LoadByMetadataObject(parent, ToVclString(metadataGuid), ToVclString(objectName), kind);
	}

	ModuleTextDocument LoadBySourceCfModuleDataGuid(const Utf16String& metadataGuid, const Utf16String& moduleDataGuid, ModuleTextKind kind)
	{
		return LoadBySourceCfModuleDataGuid(ToVclString(metadataGuid), ToVclString(moduleDataGuid), kind);
	}

	bool SaveDocument(ModuleTextDocument& document, const Utf16String& newText, Utf16String& errorText)
	{
		errorText.clear();

		if (!document.location.editable || document.location.filePath.empty())
		{
			errorText = u"Не найден редактируемый файл модуля в SourceCF.";
			return false;
		}

		const LegacyText target = LegacyText(reinterpret_cast<const wchar_t*>(document.location.filePath.c_str()));
		const LegacyText dir = ExtractFileDir(target);
		if (!DirectoryExistsFs(dir))
		{
			errorText = u"Каталог модуля не существует: ";
			errorText += Utf16String(reinterpret_cast<const char16_t*>(dir.c_str()));
			return false;
		}

		const LegacyText tmp = CombinePath(dir, ExtractFileName(target) + L".codex.tmp");
		try
		{
			{
				v8reader::core::io::StdFileStream out(ToFsPath(tmp), v8reader::core::io::FileOpenMode::CreateTruncate);
				ModuleTextEncodingUtils::WriteTextWithEncoding(out, LegacyText(reinterpret_cast<const wchar_t*>(newText.c_str())), document.location.encoding);
			}

			if (FileExistsFs(target) && !DeleteFileFs(target))
			{
				errorText = u"Не удалось удалить исходный файл модуля: ";
				errorText += document.location.filePath;
				return false;
			}
			if (!MoveFileFs(tmp, target))
			{
				errorText = u"Не удалось переместить временный файл модуля: ";
				errorText += Utf16String(reinterpret_cast<const char16_t*>(tmp.c_str()));
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
			errorText = Utf16String(reinterpret_cast<const char16_t*>(e.Message.c_str()));
			return false;
		}
	}

	Utf16String DescribeLocation(const ModuleTextLocation& location)
	{
		if (!location.filePath.empty())
			return location.filePath;
		if (!location.containerPath.empty())
			return location.containerPath;
		if (!location.moduleDataGuid.empty())
			return location.moduleDataGuid;
		return u"";
	}
}
