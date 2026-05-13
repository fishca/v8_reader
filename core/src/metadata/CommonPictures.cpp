//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonPictures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TCommonPictures::TCommonPictures() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TCommonPictures::TCommonPictures(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TCommonPictures::TCommonPictures(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonPictures::~TCommonPictures()
{
}

String TCommonPictures::GetPictureName()
{
    return name;
}

void TCommonPictures::SetPictureName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonPictures::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonPictures::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonPictures::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonPictures::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonPictures::getForms()
{
    return forms;
}

void TCommonPictures::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РѕР±С‰РµР№ РєР°СЂС‚РёРЅРєРё РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РѕР±С‰РµР№ РєР°СЂС‚РёРЅРєРё СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}

