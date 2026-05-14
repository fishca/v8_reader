//---------------------------------------------------------------------------

#ifndef MDOH
#define MDOH
//---------------------------------------------------------------------------
#include <cstddef>

#include "../APIcfBase.h"
#include "MetadataEntity.h"

namespace mdo_detail
{
	inline Utf16String ToUtf16(const Utf16String& value)
	{
		return value;
	}

	inline Utf16String ToUtf16(const wchar_t* value)
	{
		return V8Utf16FromString(value);
	}

	inline Utf16String ToUtf16(const char* value)
	{
		Utf16String result;
		if (!value)
			return result;

		while (*value)
			result.push_back(static_cast<unsigned char>(*value++));

		return result;
	}

	template <std::size_t N>
	inline Utf16String ToUtf16(const char (&value)[N])
	{
		return ToUtf16(static_cast<const char*>(value));
	}

	template <typename TText>
	inline Utf16String ToUtf16(const TText& value)
	{
		return V8Utf16FromString(value);
	}
}

class TMDO : public MetadataEntity
{
public:
	Utf16String name;
	Utf16String guid;

	TMDO();
	~TMDO();
	void SetName(const Utf16String& _name);
	void SetGUID(const Utf16String& _guid);
	Utf16String GetName();
	Utf16String GetGUID();

	template <typename TText>
	void SetName(const TText& _name) { SetName(mdo_detail::ToUtf16(_name)); }

	template <typename TText>
	void SetGUID(const TText& _guid) { SetGUID(mdo_detail::ToUtf16(_guid)); }
};

#endif

