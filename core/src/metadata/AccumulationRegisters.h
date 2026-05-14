//---------------------------------------------------------------------------

#ifndef AccumulationRegistersH
#define AccumulationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TAccumulationRegisters : public MetadataObjectInformationRegister
{
public:
	TAccumulationRegisters();
	TAccumulationRegisters(v8catalog *_parent, const Utf16String& _guid);
	TAccumulationRegisters(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TAccumulationRegisters(v8catalog *_parent, const TStringLike& _guid)
		: TAccumulationRegisters(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TAccumulationRegisters(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TAccumulationRegisters(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TAccumulationRegisters();

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

