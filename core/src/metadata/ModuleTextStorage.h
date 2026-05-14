//---------------------------------------------------------------------------

#ifndef ModuleTextStorageH
#define ModuleTextStorageH

#include "../APIcfBase.h"
#include "Parse_tree.h"

enum class ModuleTextKind
{
	Unknown,
	CommonModule,
	CommonForm,
	ObjectModule,
	ManagerModule,
	FormModule,
	CommandModule,
	ApplicationModule,
	SessionModule,
	ExternalConnectionModule
};

enum class ModuleTextEncodingKind
{
	Unknown,
	Utf8,
	Utf8Bom,
	Utf16Le,
	Utf16LeBom,
	Ansi
};

struct ModuleTextLocation
{
	Utf16String metadataGuid;
	Utf16String moduleDataGuid;
	Utf16String sourceRoot;
	Utf16String containerPath;
	Utf16String filePath;
	Utf16String fileName;
	ModuleTextKind kind = ModuleTextKind::Unknown;
	ModuleTextEncodingKind encoding = ModuleTextEncodingKind::Unknown;
	bool editable = false;
	bool foundInSourceCF = false;
};

struct ModuleTextDocument
{
	Utf16String text;
	ModuleTextLocation location;
	bool loaded = false;
	bool dirty = false;
};

namespace ModuleTextStorage
{
	Utf16String NormalizeGuidFileName(const Utf16String& guid);
	bool IsGuidLike(const Utf16String& value);
	bool LooksLike1CModuleText(const Utf16String& value);

	ModuleTextDocument LoadCommonModule(v8catalog* parent, const Utf16String& metadataGuid, const Utf16String& moduleName);
	ModuleTextDocument LoadCommonForm(v8catalog* parent, const Utf16String& metadataGuid, const Utf16String& formName);
	ModuleTextDocument LoadByMetadataObject(v8catalog* parent, const Utf16String& metadataGuid, const Utf16String& objectName, ModuleTextKind kind);
	ModuleTextDocument LoadBySourceCfModuleDataGuid(const Utf16String& metadataGuid, const Utf16String& moduleDataGuid, ModuleTextKind kind);
	ModuleTextDocument LoadConfigurationModule(v8catalog* parent, ModuleTextKind kind);

	bool SaveDocument(ModuleTextDocument& document, const Utf16String& newText, Utf16String& errorText);
	Utf16String DescribeLocation(const ModuleTextLocation& location);

	template <typename TStringLikeGuid>
	inline Utf16String NormalizeGuidFileName(const TStringLikeGuid& guid)
	{
		return NormalizeGuidFileName(V8Utf16FromString(guid));
	}

	template <typename TStringLikeValue>
	inline bool IsGuidLike(const TStringLikeValue& value)
	{
		return IsGuidLike(V8Utf16FromString(value));
	}

	template <typename TStringLikeValue>
	inline bool LooksLike1CModuleText(const TStringLikeValue& value)
	{
		return LooksLike1CModuleText(V8Utf16FromString(value));
	}

	template <typename TStringLikeGuid, typename TStringLikeName>
	inline ModuleTextDocument LoadCommonModule(v8catalog* parent, const TStringLikeGuid& metadataGuid, const TStringLikeName& moduleName)
	{
		return LoadCommonModule(parent, V8Utf16FromString(metadataGuid), V8Utf16FromString(moduleName));
	}

	template <typename TStringLikeGuid, typename TStringLikeName>
	inline ModuleTextDocument LoadCommonForm(v8catalog* parent, const TStringLikeGuid& metadataGuid, const TStringLikeName& formName)
	{
		return LoadCommonForm(parent, V8Utf16FromString(metadataGuid), V8Utf16FromString(formName));
	}

	template <typename TStringLikeGuid, typename TStringLikeName>
	inline ModuleTextDocument LoadByMetadataObject(v8catalog* parent, const TStringLikeGuid& metadataGuid, const TStringLikeName& objectName, ModuleTextKind kind)
	{
		return LoadByMetadataObject(parent, V8Utf16FromString(metadataGuid), V8Utf16FromString(objectName), kind);
	}

	template <typename TStringLikeGuid, typename TStringLikeModuleDataGuid>
	inline ModuleTextDocument LoadBySourceCfModuleDataGuid(const TStringLikeGuid& metadataGuid, const TStringLikeModuleDataGuid& moduleDataGuid, ModuleTextKind kind)
	{
		return LoadBySourceCfModuleDataGuid(V8Utf16FromString(metadataGuid), V8Utf16FromString(moduleDataGuid), kind);
	}

	template <typename TStringLikeText>
	inline bool SaveDocument(ModuleTextDocument& document, const TStringLikeText& newText, Utf16String& errorText)
	{
		return SaveDocument(document, V8Utf16FromString(newText), errorText);
	}
}

#endif

