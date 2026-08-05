//---------------------------------------------------------------------------

#ifndef ReportsH
#define ReportsH

#include "MetadataObjectWithSections.h"

// Глобальная функция для CRTP-шаблона (не static)
MetadataTreePaths GetReportsPaths();

//---------------------------------------------------------------------------

class TReports : public MetadataObjectWithSectionsT<TReports, GetReportsPaths>
{
public:
	__fastcall TReports();
	__fastcall TReports(v8catalog *_parent, const String& _guid);
	__fastcall TReports(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TReports();
};

#endif
