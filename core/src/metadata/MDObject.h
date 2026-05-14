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

	Utf16String name;
	Utf16String guid;

	TMDObject()
	{
		name = u"";
		guid = u"";
	};
	virtual void CreateMD() = 0;
	virtual ~TMDObject();
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

