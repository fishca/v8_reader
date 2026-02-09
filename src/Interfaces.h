//---------------------------------------------------------------------------

#ifndef InterfacesH
#define InterfacesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TInterfaces
 * @brief Класс для хранения интерфейсов (md_Interfaces)
 *
 * Интерфейсы - это объекты метаданных, которые содержат
 * интерфейсы конфигурации 1С:Предприятие.
 */
class TInterfaces : public BaseMetadataObject
{
private:
    // interfaceName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TInterfaces();
    __fastcall TInterfaces(v8catalog* _parent, const String& _guid);
    __fastcall TInterfaces(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TInterfaces();

    // Методы для получения имени интерфейса
    String __fastcall GetInterfaceName();
    void __fastcall SetInterfaceName(String _name);

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
