//---------------------------------------------------------------------------

#ifndef ReportsH
#define ReportsH

#include "MetadataObjectWithSections.h"

//---------------------------------------------------------------------------

class TReports : public MetadataObjectWithSections
{
public:
	TReports();
	TReports(v8catalog *_parent, const Utf16String& _guid);
	TReports(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	~TReports();

	template <typename TGuid>
	TReports(v8catalog* _parent, const TGuid& _guid)
		: TReports(_parent, V8Utf16FromString(_guid))
	{
	}

	template <typename TGuid, typename TName>
	TReports(v8catalog* _parent, const TGuid& _guid, const TName& _name)
		: TReports(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
	{
	}

	void initializeFromTree() override;
};

#endif

