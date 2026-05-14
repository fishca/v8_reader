//---------------------------------------------------------------------------


#include "TConstants.h"
//---------------------------------------------------------------------------


TConstants::TConstants() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TConstants::TConstants(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TConstants::TConstants(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TConstants::~TConstants()
{
}

Utf16String TConstants::GetConstantsName() const
{
    return name;
}

void TConstants::SetConstantsName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TConstants::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TConstants::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TConstants::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TConstants::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TConstants::getForms()
{
    return forms;
}

void TConstants::initializeFromTree()
{
    // Инициализация константы из дерева метаданных
    // Имя константы уже установлено в конструкторе
}
