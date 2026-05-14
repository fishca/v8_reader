//---------------------------------------------------------------------------


#include "ScheduledJobs.h"
//---------------------------------------------------------------------------


TScheduledJobs::TScheduledJobs() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TScheduledJobs::TScheduledJobs(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TScheduledJobs::TScheduledJobs(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TScheduledJobs::~TScheduledJobs()
{
}

Utf16String TScheduledJobs::GetScheduledJobsName() const
{
    return name;
}

void TScheduledJobs::SetScheduledJobsName(const Utf16String& _name)
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

