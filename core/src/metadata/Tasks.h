//---------------------------------------------------------------------------

#ifndef TasksH
#define TasksH

#include "MetadataObjectWithSections.h"
//---------------------------------------------------------------------------

class TTasks : public MetadataObjectWithSections
{
public:
	TTasks();
	TTasks(v8catalog *_parent, const Utf16String& _guid);
	TTasks(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	~TTasks();

	template <typename TGuid>
	TTasks(v8catalog* _parent, const TGuid& _guid)
		: TTasks(_parent, V8Utf16FromString(_guid))
	{
	}

	template <typename TGuid, typename TName>
	TTasks(v8catalog* _parent, const TGuid& _guid, const TName& _name)
		: TTasks(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
	{
	}

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

