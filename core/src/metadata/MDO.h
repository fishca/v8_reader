//---------------------------------------------------------------------------

#ifndef MDOH
#define MDOH
//---------------------------------------------------------------------------
#include "MetadataEntity.h"

class TMDO : public MetadataEntity
{
public:
	String name;
	String guid;

	TMDO();
	~TMDO();
	void SetName(String _name);
	void SetGUID(String _guid);
	String GetName();
	String GetGUID();
};

#endif

