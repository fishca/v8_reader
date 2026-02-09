//---------------------------------------------------------------------------

#ifndef ScheduledJobsH
#define ScheduledJobsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TScheduledJobs
 * @brief Класс для хранения регламентных заданий (md_ScheduledJobs)
 *
 * Регламентные задания - это объекты метаданных, которые содержат
 * настройки автоматического выполнения задач по расписанию.
 */
class TScheduledJobs : public BaseMetadataObject
{
private:
    // scheduledJobsName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TScheduledJobs();
    __fastcall TScheduledJobs(v8catalog* _parent, const String& _guid);
    __fastcall TScheduledJobs(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TScheduledJobs();

    // Методы для получения имени регламентного задания
    String __fastcall GetScheduledJobsName();
    void __fastcall SetScheduledJobsName(String _name);

    // Реализация виртуальных методов BaseMetadataObject
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void __fastcall initializeFromTree() override;

private:
    // Внутренние хранилища для совместимости с интерфейсом
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif
