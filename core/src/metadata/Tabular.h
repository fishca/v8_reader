//---------------------------------------------------------------------------

#ifndef TabularH
#define TabularH

#include <memory>
#include <vector>

#include "MDO.h"
#include "Parse_tree.h"
#include "Requisite.h"

//---------------------------------------------------------------------------
class TTabular : public TMDO
{
public:
	std::vector<std::unique_ptr<TRequisite>> attributes;

	TTabular();
	TTabular(const Utf16String& _name, const Utf16String& _guid);
	~TTabular();

	template <typename TName, typename TGuid>
	TTabular(const TName& _name, const TGuid& _guid)
		: TTabular(mdo_detail::ToUtf16(_name), mdo_detail::ToUtf16(_guid))
	{
	}

	void initializeFromTree(tree* root);
};
#endif

