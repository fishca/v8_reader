//---------------------------------------------------------------------------

#ifndef DataProcessorsH
#define DataProcessorsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TDataProcessors : public MetadataObjectWithSections
{
public:
	TDataProcessors();
	TDataProcessors(v8catalog *_parent, const Utf16String& _guid);
	TDataProcessors(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TDataProcessors(v8catalog *_parent, const TStringLike& _guid)
		: TDataProcessors(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TDataProcessors(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TDataProcessors(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TDataProcessors();

	void initializeFromTree() override;
};

#endif

