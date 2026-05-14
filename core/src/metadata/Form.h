//---------------------------------------------------------------------------

#ifndef FormH
#define FormH

#include "MDO.h"

//---------------------------------------------------------------------------
class TForm1C : public TMDO
{
public:
	TForm1C();
	TForm1C(const Utf16String& _name, const Utf16String& _guid);
	~TForm1C();

	template <typename TName, typename TGuid>
	TForm1C(const TName& _name, const TGuid& _guid)
		: TForm1C(mdo_detail::ToUtf16(_name), mdo_detail::ToUtf16(_guid))
	{
	}
};
#endif

