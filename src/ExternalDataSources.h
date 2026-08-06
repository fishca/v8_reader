//---------------------------------------------------------------------------

#ifndef ExternalDataSourcesH
#define ExternalDataSourcesH
//---------------------------------------------------------------------------
#include "EmptyMetadataObject.h"

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

class TExternalDataSources : public EmptyMetadataObject<TExternalDataSources>
{
public:
	__fastcall TExternalDataSources();
	__fastcall TExternalDataSources(v8catalog* _parent, const String& _guid);
	__fastcall TExternalDataSources(v8catalog* _parent, const String& _guid, const String& _name);
	virtual __fastcall ~TExternalDataSources();

	std::vector<TExternalDataSourceTable> tables;
	std::vector<TExternalDataSourceCube> cubes;
	std::vector<String> functions;

	void __fastcall initializeFromTree() override;
};

#endif
