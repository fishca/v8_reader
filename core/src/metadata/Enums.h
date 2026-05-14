//---------------------------------------------------------------------------

#ifndef EnumsH
#define EnumsH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include "../APIcfBase.h"
#include "Parse_tree.h"
#include "MetadataEntity.h"

class TEnums : public MetadataEntity
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
	TEnums();
	TEnums(v8catalog *_parent, const Utf16String& _guid);
	TEnums(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	~TEnums();

	template <typename TGuid>
	TEnums(v8catalog* _parent, const TGuid& _guid)
		: TEnums(_parent, V8Utf16FromString(_guid))
	{
	}

	template <typename TGuid, typename TName>
	TEnums(v8catalog* _parent, const TGuid& _guid, const TName& _name)
		: TEnums(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
	{
	}
};

#endif

