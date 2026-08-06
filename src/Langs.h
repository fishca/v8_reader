//---------------------------------------------------------------------------

#ifndef LangsH
#define LangsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

class TLangs : public EmptyMetadataObject<TLangs>
{
private:
	// langName хранится в унаследованном поле name из BaseMetadataObject

public:
	__fastcall TLangs();
	__fastcall TLangs(v8catalog* _parent, const String& _guid);
	__fastcall TLangs(v8catalog* _parent, const String& _guid, const String& _name);

	// Методы для получения имени языка
	String __fastcall GetLangName();
	void __fastcall SetLangName(String _name);
};

#endif
