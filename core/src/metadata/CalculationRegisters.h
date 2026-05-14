//---------------------------------------------------------------------------

#ifndef CalculationRegistersH
#define CalculationRegistersH

#include "MetadataObjectInformationRegister.h"

//---------------------------------------------------------------------------

class TCalculationRegisters : public MetadataObjectInformationRegister
{
public:
	TCalculationRegisters();
	TCalculationRegisters(v8catalog *_parent, const Utf16String& _guid);
	TCalculationRegisters(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TCalculationRegisters(v8catalog *_parent, const TStringLike& _guid)
		: TCalculationRegisters(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TCalculationRegisters(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TCalculationRegisters(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TCalculationRegisters();

	void initializeFromTree() override;
};

//---------------------------------------------------------------------------
#endif

