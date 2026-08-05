//---------------------------------------------------------------------------
#ifndef XDTOPackagesH
#define XDTOPackagesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TXDTOPackages
 * @brief Класс для хранения XDTO-пакетов (md_XDTOPackages)
 *
 * XDTO-пакеты используются для работы с XDTO (XML Data Transfer Objects)
 */
class TXDTOPackages : public EmptyMetadataObject<TXDTOPackages>
{
public:
    __fastcall TXDTOPackages();
    __fastcall TXDTOPackages(v8catalog* _parent, const String& _guid);
    __fastcall TXDTOPackages(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени XDTO-пакета
    String __fastcall GetXDTOPackageName();
};

//---------------------------------------------------------------------------
#endif
