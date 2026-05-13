//---------------------------------------------------------------------------

#ifndef ComandH
#define ComandH

#include "MDO.h"

//---------------------------------------------------------------------------
class TComand : public TMDO
{
public:
	TComand();
	TComand(String _name, String _guid);
	~TComand();
};
#endif

