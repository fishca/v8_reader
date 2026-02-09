//---------------------------------------------------------------------------

#pragma hdrstop

#include "ScheduledJobs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TScheduledJobs::TScheduledJobs() : BaseMetadataObject()
{
    name = "";
}

__fastcall TScheduledJobs::TScheduledJobs(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
}

__fastcall TScheduledJobs::TScheduledJobs(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
}

__fastcall TScheduledJobs::~TScheduledJobs()
{
}

String __fastcall TScheduledJobs::GetScheduledJobsName()
{
    return name;
}

void __fastcall TScheduledJobs::SetScheduledJobsName(String _name)
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

void __fastcall TScheduledJobs::initializeFromTree()
{
    // Инициализация регламентного задания из дерева метаданных
    // Имя регламентного задания уже установлено в конструкторе
}
