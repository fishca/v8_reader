#ifndef StylesH
#define StylesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

class TStyles : public EmptyMetadataObject<TStyles>
{
private:
    String styleName;

public:
    __fastcall TStyles();
    __fastcall TStyles(v8catalog* _parent, const String& _guid);
    __fastcall TStyles(v8catalog* _parent, const String& _guid, const String& _name);

    String __fastcall GetStyleName();
    void __fastcall SetStyleName(String _name);
};

#endif
