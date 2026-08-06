//---------------------------------------------------------------------------

#ifndef RolesH
#define RolesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TRoles
 * @brief Класс для хранения ролей (md_Roles)
 *
 * Роли - это объекты метаданных, которые содержат
 * права доступа и настройки безопасности для пользователей.
 */
class TRoles : public EmptyMetadataObject<TRoles>
{
private:
    String roleName;  // Имя роли

public:
    __fastcall TRoles();
    __fastcall TRoles(v8catalog* _parent, const String& _guid);
    __fastcall TRoles(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени роли
    String __fastcall GetRoleName();
    void __fastcall SetRoleName(String _name);
};

#endif
