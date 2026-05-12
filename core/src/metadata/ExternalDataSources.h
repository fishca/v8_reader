//---------------------------------------------------------------------------

#ifndef ExternalDataSourcesH
#define ExternalDataSourcesH
//---------------------------------------------------------------------------
#include "BaseMetadataObject.h"

struct TExternalDataSourceTable
{
	String name;
	std::vector<String> fields;
	std::vector<String> forms;
	std::vector<String> commands;
	std::vector<String> layouts;
};

struct TExternalDataSourceCube
{
	String name;
	std::vector<TExternalDataSourceTable> dimensionTables;
	std::vector<String> dimensions;
	std::vector<String> resources;
	std::vector<String> forms;
	std::vector<String> commands;
	std::vector<String> layouts;
};

class TExternalDataSources : public BaseMetadataObject
{
public:
	__fastcall TExternalDataSources();
	__fastcall TExternalDataSources(v8catalog* _parent, const String& _guid);
	__fastcall TExternalDataSources(v8catalog* _parent, const String& _guid, const String& _name);
	virtual __fastcall ~TExternalDataSources();

	std::vector<TExternalDataSourceTable> tables;
	std::vector<TExternalDataSourceCube> cubes;
	std::vector<String> functions;

	std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
	std::vector<std::unique_ptr<TComand>>& getCommands() override;
	std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
	std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
	std::vector<std::unique_ptr<TForm1C>>& getForms() override;

	void __fastcall initializeFromTree() override;

private:
	std::vector<std::unique_ptr<TRequisite>> attributes;
	std::vector<std::unique_ptr<TComand>> commands;
	std::vector<std::unique_ptr<TMoxel>> layouts;
	std::vector<std::unique_ptr<TTabular>> tabularSections;
	std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif
