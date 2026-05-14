//---------------------------------------------------------------------------

#ifndef DocumentsH
#define DocumentsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TDocuments : public MetadataObjectWithSections
{
public:
	TDocuments();
	TDocuments(v8catalog *_parent, const Utf16String& _guid);
	TDocuments(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TDocuments(v8catalog *_parent, const TStringLike& _guid)
		: TDocuments(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TDocuments(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TDocuments(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TDocuments();

	void initializeFromTree() override;
};

#endif

