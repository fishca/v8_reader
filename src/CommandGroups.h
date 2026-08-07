//---------------------------------------------------------------------------

#ifndef CommandGroupsH
#define CommandGroupsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommandGroups
 * @brief Класс для хранения групп команд (md_CommandGroups)
 *
 * Группы команд - это объекты метаданных, которые содержат
 * группы команд для организации интерфейса.
 */
class TCommandGroups : public EmptyMetadataObject<TCommandGroups>
{
private:
    // groupName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TCommandGroups();
    __fastcall TCommandGroups(v8catalog* _parent, const String& _guid);
    __fastcall TCommandGroups(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени группы команд
    String __fastcall GetCommandName();
    void __fastcall SetCommandName(String _name);
};

#endif
