//---------------------------------------------------------------------------
#ifndef XDTOPackagesH
#define XDTOPackagesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TXDTOPackages
 * @brief Класс для хранения XDTO-пакетов (md_XDTOPackages)
 *
 * XDTO-пакеты используются для работы с XDTO (XML Data Transfer Objects)
 */
class TXDTOPackages : public BaseMetadataObject
{
private:
    // data хранится в унаследованном поле root_data из BaseMetadataObject

public:
    __fastcall TXDTOPackages();
    __fastcall TXDTOPackages(v8catalog* _parent, const String& _guid);
    __fastcall TXDTOPackages(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TXDTOPackages();

    // Методы для получения имени XDTO-пакета
    String __fastcall GetXDTOPackageName();

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

//---------------------------------------------------------------------------
#endif
