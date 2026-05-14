//---------------------------------------------------------------------------

#ifndef InformationRegistersH
#define InformationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TInformationRegisters : public MetadataObjectInformationRegister
{
public:
	TInformationRegisters();
	TInformationRegisters(v8catalog *_parent, const Utf16String& _guid);
	TInformationRegisters(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TInformationRegisters(v8catalog *_parent, const TStringLike& _guid)
		: TInformationRegisters(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TInformationRegisters(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TInformationRegisters(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TInformationRegisters();

	void initializeFromTree() override;
};

#endif

