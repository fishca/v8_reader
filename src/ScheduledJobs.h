//---------------------------------------------------------------------------

#ifndef ScheduledJobsH
#define ScheduledJobsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TScheduledJobs
 * @brief Класс для хранения регламентных заданий (md_ScheduledJobs)
 *
 * Регламентные задания - это объекты метаданных, которые содержат
 * настройки автоматического выполнения задач по расписанию.
 */
class TScheduledJobs : public EmptyMetadataObject<TScheduledJobs>
{
private:
    // scheduledJobsName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TScheduledJobs();
    __fastcall TScheduledJobs(v8catalog* _parent, const String& _guid);
    __fastcall TScheduledJobs(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени регламентного задания
    String __fastcall GetScheduledJobsName();
    void __fastcall SetScheduledJobsName(String _name);
};

#endif
