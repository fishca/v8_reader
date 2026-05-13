//---------------------------------------------------------------------------

#ifndef MDObjectH
#define MDObjectH

#include <memory>
#include <vector>
#include "../APIcfBase.h"
#include "Parse_tree.h"
#include "MetadataEntity.h"

//---------------------------------------------------------------------------
class TMDObject : public MetadataEntity
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

class TMDObjectManager
{
private:
	std::vector<std::unique_ptr<TMDObject>> md_list;
	virtual TMDObject* CreateMetaData() = 0;
public:
	TMDObject* newMetaData();
	TMDObjectManager();
};

#endif

