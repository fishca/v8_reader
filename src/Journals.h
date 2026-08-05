//---------------------------------------------------------------------------

#ifndef JournalsH
#define JournalsH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetJournalsPaths();

//---------------------------------------------------------------------------

class TJournals : public MetadataObjectWithSectionsT<TJournals, GetJournalsPaths>
{
public:
	__fastcall TJournals();
	__fastcall TJournals(v8catalog *_parent, const String& _guid);
	__fastcall TJournals(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TJournals();
};

#endif
