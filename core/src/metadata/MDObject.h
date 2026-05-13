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

	TMDObject()
	{
		name = "";
		guid = "";
	};
	virtual void CreateMD() = 0;
	virtual ~TMDObject();

//	std::vector<String> attributes;  // список реквизитов
//	std::vector<String> comands;     // список команд
//	std::vector<String> moxels;      // список макетов
//	std::vector<String> tabulars;    // список табличных частей
//	std::vector<String> forms;       // список форм
//
//	TMDObject();
//	TMDObject(v8catalog *_parent, const String& _guid);
//	TMDObject(v8catalog *_parent, const String& _guid, const String& _name);
//	~TMDObject();
//	String GetName();
//	String GetGUID();
//	void SetName();
//	void SetGUID();

};

class TMDObjectManager : public TObject
{
private:
	TObjectList *md_list;
	virtual TMDObject* CreateMetaData() = 0;
public:
	TMDObject* newMetaData();
	TMDObjectManager();
};

#endif

