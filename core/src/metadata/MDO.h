//---------------------------------------------------------------------------

#ifndef MDOH
#define MDOH
//---------------------------------------------------------------------------
class TMDO : public TObject
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

