//---------------------------------------------------------------------------

#ifndef ExternalDataSourcesH
#define ExternalDataSourcesH
//---------------------------------------------------------------------------
#include "BaseMetadataObject.h"

struct TExternalDataSourceTable
{
	Utf16String name;
	std::vector<Utf16String> fields;
	std::vector<Utf16String> forms;
	std::vector<Utf16String> commands;
	std::vector<Utf16String> layouts;
};

struct TExternalDataSourceCube
{
	Utf16String name;
	std::vector<TExternalDataSourceTable> dimensionTables;
	std::vector<Utf16String> dimensions;
	std::vector<Utf16String> resources;
	std::vector<Utf16String> forms;
	std::vector<Utf16String> commands;
	std::vector<Utf16String> layouts;
};

class TExternalDataSources : public BaseMetadataObject
{
public:
	TExternalDataSources();
	TExternalDataSources(v8catalog* _parent, const Utf16String& _guid);
	TExternalDataSources(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
	virtual ~TExternalDataSources();

	template <typename TGuid>
	TExternalDataSources(v8catalog* _parent, const TGuid& _guid)
		: TExternalDataSources(_parent, V8Utf16FromString(_guid))
	{
	}

	template <typename TGuid, typename TName>
	TExternalDataSources(v8catalog* _parent, const TGuid& _guid, const TName& _name)
		: TExternalDataSources(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
	{
	}

	std::vector<TExternalDataSourceTable> tables;
	std::vector<TExternalDataSourceCube> cubes;
	std::vector<Utf16String> functions;

	std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
	std::vector<std::unique_ptr<TComand>>& getCommands() override;
	std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
	std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
	std::vector<std::unique_ptr<TForm1C>>& getForms() override;

	void initializeFromTree() override;

private:
	std::vector<std::unique_ptr<TRequisite>> attributes;
	std::vector<std::unique_ptr<TComand>> commands;
	std::vector<std::unique_ptr<TMoxel>> layouts;
	std::vector<std::unique_ptr<TTabular>> tabularSections;
	std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif

