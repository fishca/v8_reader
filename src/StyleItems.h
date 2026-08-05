#ifndef StyleItemsH
#define StyleItemsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

class TStyleItems : public EmptyMetadataObject<TStyleItems>
{
private:
    String styleItemName;

public:
    __fastcall TStyleItems();
    __fastcall TStyleItems(v8catalog* _parent, const String& _guid);
    __fastcall TStyleItems(v8catalog* _parent, const String& _guid, const String& _name);

    String __fastcall GetStyleItemName();
    void __fastcall SetStyleItemName(String _name);
};

#endif
