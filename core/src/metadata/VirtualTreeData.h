//---------------------------------------------------------------------------

#ifndef VirtualTreeDataH
#define VirtualTreeDataH

#include <System.hpp>

#include "ModuleTextStorage.h"

struct VirtualTreeData
{
	String Name;
	String text_module;
	String moduleItemGuid;
	TObject* MetadataObject = nullptr;
	ModuleTextLocation moduleLocation;
	bool moduleEditable = false;
	bool moduleDirty = false;
	int Age = 0;
	int ImgIndex = 0;
};

#endif

