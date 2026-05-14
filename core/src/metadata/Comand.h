//---------------------------------------------------------------------------

#ifndef ComandH
#define ComandH

#include "MDO.h"

//---------------------------------------------------------------------------
class TComand : public TMDO
{
public:
	TComand();
	TComand(const Utf16String& _name, const Utf16String& _guid);
	~TComand();

	template <typename TName, typename TGuid>
	TComand(const TName& _name, const TGuid& _guid)
		: TComand(mdo_detail::ToUtf16(_name), mdo_detail::ToUtf16(_guid))
	{
	}
};
#endif

