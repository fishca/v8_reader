//---------------------------------------------------------------------------

#ifndef NumeratorsH
#define NumeratorsH

#include <vector>
#include <memory>
#include "../APIcfBase.h"
#include "Parse_tree.h"

//---------------------------------------------------------------------------
class TNumerators : public TObject
{
public:

	std::unique_ptr<tree> root_data;
	v8catalog* parent;

	String name;
	String guid;

	std::vector<String> attributes;  // список реквизитов
	std::vector<String> comands;     // список команд
	std::vector<String> moxels;      // список макетов
	std::vector<String> tabulars;    // список табличных частей
	std::vector<String> forms;       // список форм
	/* TODO : Реализовать класс */
	TNumerators();
	TNumerators(v8catalog *_parent, const String& _guid);
	TNumerators(v8catalog *_parent, const String& _guid, const String& _name);
	~TNumerators();
};

#endif

