//---------------------------------------------------------------------------

#ifndef MDOH
#define MDOH
//---------------------------------------------------------------------------
class TMDO : public TObject
{
public:
	String name;
	String guid;

	__fastcall TMDO();
	__fastcall ~TMDO();
	void __fastcall SetName(String _name);
	void __fastcall SetGUID(String _guid);
	String GetName();
	String GetGUID();
};

#endif
