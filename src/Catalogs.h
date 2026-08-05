//---------------------------------------------------------------------------

#ifndef CatalogsH
#define CatalogsH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetCatalogsPaths();

//---------------------------------------------------------------------------

class TCatalogs : public MetadataObjectWithSectionsT<TCatalogs, GetCatalogsPaths>
{
public:
	__fastcall TCatalogs();
	__fastcall TCatalogs(v8catalog *_parent, const String& _guid);
	__fastcall TCatalogs(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TCatalogs();
};

#endif
