//---------------------------------------------------------------------------

#ifndef ModuleTextStorageH
#define ModuleTextStorageH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

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
	String __fastcall NormalizeGuidFileName(const String& guid);
	bool __fastcall IsGuidLike(const String& value);
	bool __fastcall LooksLike1CModuleText(const String& value);

	ModuleTextDocument __fastcall LoadCommonModule(v8catalog* parent, const String& metadataGuid, const String& moduleName);
	ModuleTextDocument __fastcall LoadCommonForm(v8catalog* parent, const String& metadataGuid, const String& formName);
	ModuleTextDocument __fastcall LoadByMetadataObject(v8catalog* parent, const String& metadataGuid, const String& objectName, ModuleTextKind kind);
	ModuleTextDocument __fastcall LoadBySourceCfModuleDataGuid(const String& metadataGuid, const String& moduleDataGuid, ModuleTextKind kind);
	ModuleTextDocument __fastcall LoadConfigurationModule(v8catalog* parent, ModuleTextKind kind);

	bool __fastcall SaveDocument(ModuleTextDocument& document, const String& newText, String& errorText);
	String __fastcall DescribeLocation(const ModuleTextLocation& location);
}

#endif
