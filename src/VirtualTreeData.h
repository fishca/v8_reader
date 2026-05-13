//---------------------------------------------------------------------------

#ifndef VirtualTreeDataH
#define VirtualTreeDataH

#include <System.hpp>

#include "ModuleTextStorage.h"
#include "MetadataEntity.h"

struct VirtualTreeData
{
	String Name;
	String text_module;
	String moduleItemGuid;
	MetadataEntity* MetadataObject = nullptr;
	ModuleTextLocation moduleLocation;
	bool moduleEditable = false;
	bool moduleDirty = false;
	int Age = 0;
	int ImgIndex = 0;
};

#endif
