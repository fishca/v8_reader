//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonPictures.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonPictures::TCommonPictures() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonPictures::TCommonPictures(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TCommonPictures::TCommonPictures(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

__fastcall TCommonPictures::~TCommonPictures()
{
}

String __fastcall TCommonPictures::GetPictureName()
{
    return name;
}

void __fastcall TCommonPictures::SetPictureName(String _name)
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

void __fastcall TCommonPictures::initializeFromTree()
{
    // Инициализация общей картинки из дерева метаданных
    // Имя общей картинки уже установлено в конструкторе
}
