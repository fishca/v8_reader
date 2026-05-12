//---------------------------------------------------------------------------

#ifndef ComandH
#define ComandH

#include "MDO.h"

//---------------------------------------------------------------------------
class TComand : public TMDO
{
public:
	__fastcall TComand();
	__fastcall TComand(String _name, String _guid);
	__fastcall ~TComand();
};
#endif
