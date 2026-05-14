//---------------------------------------------------------------------------

#ifndef MoxelH
#define MoxelH

#include "MDO.h"
//---------------------------------------------------------------------------
class TMoxel : public TMDO
{
public:
	TMoxel();
	TMoxel(const Utf16String& _name, const Utf16String& _guid);
	~TMoxel();

	template <typename TName, typename TGuid>
	TMoxel(const TName& _name, const TGuid& _guid)
		: TMoxel(mdo_detail::ToUtf16(_name), mdo_detail::ToUtf16(_guid))
	{
	}
};
#endif

