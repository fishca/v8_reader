//---------------------------------------------------------------------------

#ifndef NumeratorsH
#define NumeratorsH

#include <vector>
#include <memory>
#include "../APIcfBase.h"
#include "Parse_tree.h"
#include "MetadataEntity.h"

//---------------------------------------------------------------------------
class TNumerators : public MetadataEntity
{
public:

	std::unique_ptr<tree> root_data;
	v8catalog* parent;

	Utf16String name;
	Utf16String guid;

	std::vector<Utf16String> attributes;  // список реквизитов
	std::vector<Utf16String> comands;     // список команд
	std::vector<Utf16String> moxels;      // список макетов
	std::vector<Utf16String> tabulars;    // список табличных частей
	std::vector<Utf16String> forms;       // список форм
	/* TODO : Реализовать класс */
	TNumerators();
	TNumerators(v8catalog *_parent, const Utf16String& _guid);
	TNumerators(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	~TNumerators();

	template <typename TGuid>
	TNumerators(v8catalog* _parent, const TGuid& _guid)
		: TNumerators(_parent, V8Utf16FromString(_guid))
	{
	}

	template <typename TGuid, typename TName>
	TNumerators(v8catalog* _parent, const TGuid& _guid, const TName& _name)
		: TNumerators(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
	{
	}
};

#endif

