//---------------------------------------------------------------------------

#ifndef DocumentsH
#define DocumentsH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetDocumentsPaths();

//---------------------------------------------------------------------------

class TDocuments : public MetadataObjectWithSectionsT<TDocuments, GetDocumentsPaths>
{
public:
	__fastcall TDocuments();
	__fastcall TDocuments(v8catalog *_parent, const String& _guid);
	__fastcall TDocuments(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TDocuments();
};

#endif
