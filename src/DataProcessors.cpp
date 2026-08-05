//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "DataProcessors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Убрать static для CRTP-шаблона
MetadataTreePaths GetDataProcessorsPaths()
{
	MetadataTreePaths paths;
	paths.attIdx = 7;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.tabIdx = 3;
	paths.tabItemPath = {0, 1, 5, 1, 2};
	paths.formsIdx = 6;
	paths.cmdIdx = 5;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	paths.moxIdx = 4;
	paths.getFormNameFunc = GetNameFormReports;
	paths.hasTabulars = true;
	return paths;
}

__fastcall TDataProcessors::TDataProcessors()
	: MetadataObjectWithSectionsT<TDataProcessors, GetDataProcessorsPaths>()
{
}

__fastcall TDataProcessors::TDataProcessors(v8catalog *_parent, const String& _guid)
	: MetadataObjectWithSectionsT<TDataProcessors, GetDataProcessorsPaths>(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TDataProcessors::TDataProcessors(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectWithSectionsT<TDataProcessors, GetDataProcessorsPaths>(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TDataProcessors::~TDataProcessors()
{
}
