//---------------------------------------------------------------------------


#include "Interfaces.h"
//---------------------------------------------------------------------------


TInterfaces::TInterfaces() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TInterfaces::TInterfaces(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TInterfaces::TInterfaces(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TInterfaces::~TInterfaces()
{
}

String TInterfaces::GetInterfaceName()
{
    return name;
}

void TInterfaces::SetInterfaceName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TInterfaces::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TInterfaces::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TInterfaces::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TInterfaces::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TInterfaces::getForms()
{
    return forms;
}

void TInterfaces::initializeFromTree()
{
    // Инициализация интерфейса из дерева метаданных
    // Имя интерфейса уже установлено в конструкторе
}

