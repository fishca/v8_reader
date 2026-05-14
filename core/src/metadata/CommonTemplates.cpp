//---------------------------------------------------------------------------


#include "CommonTemplates.h"
//---------------------------------------------------------------------------


TCommonTemplates::TCommonTemplates() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TCommonTemplates::TCommonTemplates(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TCommonTemplates::TCommonTemplates(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonTemplates::~TCommonTemplates()
{
}

Utf16String TCommonTemplates::GetTemplateName() const
{
    return name;
}

void TCommonTemplates::SetTemplateName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonTemplates::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonTemplates::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonTemplates::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonTemplates::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonTemplates::getForms()
{
    return forms;
}

void TCommonTemplates::initializeFromTree()
{
    // Инициализация общего макета из дерева метаданных
    // Имя общего макета уже установлено в конструкторе
}
