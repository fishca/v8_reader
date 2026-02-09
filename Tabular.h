//---------------------------------------------------------------------------

#ifndef TabularH
#define TabularH

#include "MDO.h"

//---------------------------------------------------------------------------
class TTabular : public TMDO
{
public:
	__fastcall TTabular();
	__fastcall TTabular(String _name, String _guid);
	__fastcall ~TTabular();
};
#endif
