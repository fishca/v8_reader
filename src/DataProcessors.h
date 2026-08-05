//---------------------------------------------------------------------------

#ifndef DataProcessorsH
#define DataProcessorsH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetDataProcessorsPaths();

//---------------------------------------------------------------------------

class TDataProcessors : public MetadataObjectWithSectionsT<TDataProcessors, GetDataProcessorsPaths>
{
public:
	__fastcall TDataProcessors();
	__fastcall TDataProcessors(v8catalog *_parent, const String& _guid);
	__fastcall TDataProcessors(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TDataProcessors();
};

#endif
