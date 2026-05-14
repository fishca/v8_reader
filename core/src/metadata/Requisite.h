//---------------------------------------------------------------------------

#ifndef RequisiteH
#define RequisiteH

#include "MDO.h"

//---------------------------------------------------------------------------
class TRequisite : public TMDO
{
public:
	TRequisite();
	TRequisite(const Utf16String& _name, const Utf16String& _guid);
	~TRequisite();

	template <typename TName, typename TGuid>
	TRequisite(const TName& _name, const TGuid& _guid)
		: TRequisite(mdo_detail::ToUtf16(_name), mdo_detail::ToUtf16(_guid))
	{
	}
};

class TAccountingFlag : public TMDO
{
public:
	TAccountingFlag();
	TAccountingFlag(const Utf16String& _name, const Utf16String& _guid);
	~TAccountingFlag();

	template <typename TName, typename TGuid>
	TAccountingFlag(const TName& _name, const TGuid& _guid)
		: TAccountingFlag(mdo_detail::ToUtf16(_name), mdo_detail::ToUtf16(_guid))
	{
	}
};

class TDimensionAccountingFlag : public TMDO
{
public:
	TDimensionAccountingFlag();
	TDimensionAccountingFlag(const Utf16String& _name, const Utf16String& _guid);
	~TDimensionAccountingFlag();

	template <typename TName, typename TGuid>
	TDimensionAccountingFlag(const TName& _name, const TGuid& _guid)
		: TDimensionAccountingFlag(mdo_detail::ToUtf16(_name), mdo_detail::ToUtf16(_guid))
	{
	}
};


#endif

