//---------------------------------------------------------------------------

#ifndef SequencesH
#define SequencesH

#include <vector>
#include <memory>
#include "Class_1CD.h"
#include "../APIcfBase.h"
#include "Parse_tree.h"

//---------------------------------------------------------------------------
class TSequences : public TObject
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
	TSequences();
	TSequences(v8catalog *_parent, const String& _guid);
	TSequences(v8catalog *_parent, const String& _guid, const String& _name);
	~TSequences();
};

#endif

