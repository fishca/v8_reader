//---------------------------------------------------------------------------

#ifndef MoxelH
#define MoxelH

#include "MDO.h"
//---------------------------------------------------------------------------
class TMoxel : public TMDO
{
public:
	__fastcall TMoxel();
	__fastcall TMoxel(String _name, String _guid);
	__fastcall ~TMoxel();
};
#endif
