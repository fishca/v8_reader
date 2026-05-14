//---------------------------------------------------------------------------


#include "CommonAttributes.h"
//---------------------------------------------------------------------------


TCommonAttributes::TCommonAttributes() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TCommonAttributes::TCommonAttributes(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TCommonAttributes::TCommonAttributes(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonAttributes::~TCommonAttributes()
{
}

Utf16String TCommonAttributes::GetAttributeName() const
{
    return name;
}

void TCommonAttributes::SetAttributeName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonAttributes::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonAttributes::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonAttributes::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonAttributes::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonAttributes::getForms()
{
    return forms;
}

void TCommonAttributes::initializeFromTree()
{
    // Инициализация общего реквизита из дерева метаданных
    // Имя общего реквизита уже установлено в конструкторе
}

