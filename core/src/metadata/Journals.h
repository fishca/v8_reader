//---------------------------------------------------------------------------

#ifndef JournalsH
#define JournalsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TJournals : public MetadataObjectWithSections
{
public:
	TJournals();
	TJournals(v8catalog *_parent, const Utf16String& _guid);
	TJournals(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TJournals(v8catalog *_parent, const TStringLike& _guid)
		: TJournals(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TJournals(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TJournals(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TJournals();

	void initializeFromTree() override;
};

#endif

