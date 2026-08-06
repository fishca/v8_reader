//---------------------------------------------------------------------------

#pragma hdrstop

#include "ScheduledJobs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TScheduledJobs::TScheduledJobs() : EmptyMetadataObject<TScheduledJobs>()
{
    name = "";
    root_data.reset();
}

__fastcall TScheduledJobs::TScheduledJobs(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TScheduledJobs>(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TScheduledJobs::TScheduledJobs(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TScheduledJobs>(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

String __fastcall TScheduledJobs::GetScheduledJobsName()
{
    return name;
}

void __fastcall TScheduledJobs::SetScheduledJobsName(String _name)
{
    name = _name;
}
