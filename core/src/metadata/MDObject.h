//---------------------------------------------------------------------------

#ifndef MDObjectH
#define MDObjectH

#include <vector>
#include "Class_1CD.h"
#include "../APIcfBase.h"
#include "Parse_tree.h"

//---------------------------------------------------------------------------
class TMDObject	: public TObject
{
public:

	String name;
	String guid;

	__fastcall TMDObject()
	{
		name = "";
		guid = "";
	};
	virtual void __fastcall CreateMD() = 0;
	virtual __fastcall ~TMDObject();

//	std::vector<String> attributes;  // список реквизитов
//	std::vector<String> comands;     // список команд
//	std::vector<String> moxels;      // список макетов
//	std::vector<String> tabulars;    // список табличных частей
//	std::vector<String> forms;       // список форм
//
//	__fastcall TMDObject();
//	__fastcall TMDObject(v8catalog *_parent, const String& _guid);
//	__fastcall TMDObject(v8catalog *_parent, const String& _guid, const String& _name);
//	__fastcall ~TMDObject();
//	String __fastcall GetName();
//	String __fastcall GetGUID();
//	void SetName();
//	void SetGUID();

};

class TMDObjectManager : public TObject
{
private:
	TObjectList *md_list;
	virtual TMDObject* __fastcall CreateMetaData() = 0;
public:
	TMDObject* __fastcall newMetaData();
	__fastcall TMDObjectManager();
};

#endif
