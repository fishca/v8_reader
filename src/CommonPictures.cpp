//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonPictures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonPictures::TCommonPictures() : EmptyMetadataObject<TCommonPictures>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonPictures::TCommonPictures(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TCommonPictures>()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonPictures::TCommonPictures(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TCommonPictures>()
{
    name = _name;
    root_data.reset();
}

String __fastcall TCommonPictures::GetPictureName()
{
    return name;
}

void __fastcall TCommonPictures::SetPictureName(String _name)
{
    name = _name;
}
