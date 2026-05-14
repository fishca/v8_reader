//---------------------------------------------------------------------------

#ifndef BusinessProcesesH
#define BusinessProcesesH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

class TBusinessProceses : public MetadataObjectWithSections
{
public:
	TBusinessProceses();
	TBusinessProceses(v8catalog *_parent, const Utf16String& _guid);
	TBusinessProceses(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TBusinessProceses(v8catalog *_parent, const TStringLike& _guid)
		: TBusinessProceses(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TBusinessProceses(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TBusinessProceses(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TBusinessProceses();

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

