//---------------------------------------------------------------------------


#include "ScheduledJobs.h"
//---------------------------------------------------------------------------


TScheduledJobs::TScheduledJobs() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TScheduledJobs::TScheduledJobs(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TScheduledJobs::TScheduledJobs(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TScheduledJobs::~TScheduledJobs()
{
}

String TScheduledJobs::GetScheduledJobsName()
{
    return name;
}

void TScheduledJobs::SetScheduledJobsName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TScheduledJobs::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TScheduledJobs::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TScheduledJobs::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TScheduledJobs::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TScheduledJobs::getForms()
{
    return forms;
}

void TScheduledJobs::initializeFromTree()
{
    // Инициализация регламентного задания из дерева метаданных
    // Имя регламентного задания уже установлено в конструкторе
}

