//---------------------------------------------------------------------------

#ifndef RolesH
#define RolesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TRoles
 * @brief Класс для хранения ролей (md_Roles)
 *
 * Роли - это объекты метаданных, которые содержат
 * права доступа и настройки безопасности для пользователей.
 */
class TRoles : public BaseMetadataObject
{
private:
    String roleName;  // Имя роли

public:
    __fastcall TRoles();
    __fastcall TRoles(v8catalog* _parent, const String& _guid);
    __fastcall TRoles(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TRoles();

    // Методы для получения имени роли
    String __fastcall GetRoleName();
    void __fastcall SetRoleName(String _name);

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
