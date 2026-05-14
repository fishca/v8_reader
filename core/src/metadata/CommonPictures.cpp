//---------------------------------------------------------------------------


#include "CommonPictures.h"
//---------------------------------------------------------------------------


TCommonPictures::TCommonPictures() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TCommonPictures::TCommonPictures(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TCommonPictures::TCommonPictures(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonPictures::~TCommonPictures()
{
}

Utf16String TCommonPictures::GetPictureName() const
{
    return name;
}

void TCommonPictures::SetPictureName(const Utf16String& _name)
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
    // Инициализация общей картинки из дерева метаданных
    // Имя общей картинки уже установлено в конструкторе
}

