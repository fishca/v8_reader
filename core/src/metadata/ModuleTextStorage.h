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
	String metadataGuid;
	String moduleDataGuid;
	String sourceRoot;
	String containerPath;
	String filePath;
	String fileName;
	ModuleTextKind kind = ModuleTextKind::Unknown;
	ModuleTextEncodingKind encoding = ModuleTextEncodingKind::Unknown;
	bool editable = false;
	bool foundInSourceCF = false;
};

struct ModuleTextDocument
{
	String text;
	ModuleTextLocation location;
	bool loaded = false;
	bool dirty = false;
};

namespace ModuleTextStorage
{
	String NormalizeGuidFileName(const String& guid);
	bool IsGuidLike(const String& value);
	bool LooksLike1CModuleText(const String& value);

	ModuleTextDocument LoadCommonModule(v8catalog* parent, const String& metadataGuid, const String& moduleName);
	ModuleTextDocument LoadCommonForm(v8catalog* parent, const String& metadataGuid, const String& formName);
	ModuleTextDocument LoadByMetadataObject(v8catalog* parent, const String& metadataGuid, const String& objectName, ModuleTextKind kind);
	ModuleTextDocument LoadBySourceCfModuleDataGuid(const String& metadataGuid, const String& moduleDataGuid, ModuleTextKind kind);
	ModuleTextDocument LoadConfigurationModule(v8catalog* parent, ModuleTextKind kind);

	bool SaveDocument(ModuleTextDocument& document, const String& newText, String& errorText);
	String DescribeLocation(const ModuleTextLocation& location);
}

#endif

