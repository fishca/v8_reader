//---------------------------------------------------------------------------

#ifndef BusinessProcesesH
#define BusinessProcesesH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetBusinessProcessesPaths();

//---------------------------------------------------------------------------

class TBusinessProceses : public MetadataObjectWithSectionsT<TBusinessProceses, GetBusinessProcessesPaths>
{
public:
	__fastcall TBusinessProceses();
	__fastcall TBusinessProceses(v8catalog *_parent, const String& _guid);
	__fastcall TBusinessProceses(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TBusinessProceses();
};

//---------------------------------------------------------------------------
#endif
