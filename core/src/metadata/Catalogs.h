//---------------------------------------------------------------------------

#ifndef CatalogsH
#define CatalogsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TCatalogs : public MetadataObjectWithSections
{
public:
	TCatalogs();
	TCatalogs(v8catalog *_parent, const Utf16String& _guid);
	TCatalogs(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TCatalogs(v8catalog *_parent, const TStringLike& _guid)
		: TCatalogs(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TCatalogs(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TCatalogs(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TCatalogs();

	void initializeFromTree() override;
};

#endif

