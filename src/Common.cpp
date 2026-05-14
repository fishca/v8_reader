//---------------------------------------------------------------------------

#pragma hdrstop

#include "Class_1CD.h"
#include "Common.h"
#include "VclByteStreamAdapter.h"
#include "../core/src/CommonCore.h"

#include <cstring>

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void time1CD_to_FileTime(FILETIME* ft, unsigned char* time1CD)
{
    SYSTEMTIME st;
    FILETIME lft;
    st.wYear = (time1CD[0] >> 4) * 1000 + (time1CD[0] & 0x0f) * 100 + (time1CD[1] >> 4) * 10 + (time1CD[1] & 0x0f);
    st.wMonth = (time1CD[2] >> 4) * 10 + (time1CD[2] & 0x0f);
    st.wDay = (time1CD[3] >> 4) * 10 + (time1CD[3] & 0x0f);
    st.wHour = (time1CD[4] >> 4) * 10 + (time1CD[4] & 0x0f);
    st.wMinute = (time1CD[5] >> 4) * 10 + (time1CD[5] & 0x0f);
    st.wSecond = (time1CD[6] >> 4) * 10 + (time1CD[6] & 0x0f);
    SystemTimeToFileTime(&st, &lft);
    LocalFileTimeToFileTime(&lft, ft);
}

//---------------------------------------------------------------------------
unsigned int reverse_byte_order(unsigned int value)
{
    return v8reader::core::common::reverse_byte_order(value);
}

//---------------------------------------------------------------------------
String GUIDas1C(const unsigned char* fr)
{
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::GUIDas1C(fr));
}

//---------------------------------------------------------------------------
String GUIDasMS(const unsigned char* fr)
{
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::GUIDasMS(fr));
}

//---------------------------------------------------------------------------
String GUID_to_string(const TGUID& guid)
{
    return GUIDas1C(reinterpret_cast<const unsigned char*>(&guid));
}

//---------------------------------------------------------------------------
bool string_to_GUID(const String& str, TGUID* guid)
{
    std::memset(guid, 0, sizeof(TGUID));
    std::u16string value = v8reader::vcl_bridge::StringToUtf16(str);
    return v8reader::core::common::string_to_GUID(value, reinterpret_cast<std::uint8_t*>(guid));
}

//---------------------------------------------------------------------------
String GUID_to_string_flat(TGUID* guid)
{
    const std::u16string value = v8reader::core::common::GUID_to_string_flat(reinterpret_cast<const std::uint8_t*>(guid));
    return v8reader::vcl_bridge::Utf16ToString(value);
}

//---------------------------------------------------------------------------
bool string_to_GUID_flat(const String& str, TGUID* guid)
{
    std::u16string value = v8reader::vcl_bridge::StringToUtf16(str);
    return v8reader::core::common::string_to_GUID_flat(value, reinterpret_cast<std::uint8_t*>(guid));
}

//---------------------------------------------------------------------------
bool two_hex_digits_to_byte(const wchar_t hi, const wchar_t lo, unsigned char& res)
{
    std::uint8_t value = 0;
    const bool ok = v8reader::core::common::two_hex_digits_to_byte(static_cast<char16_t>(hi), static_cast<char16_t>(lo), value);
    res = value;
    return ok;
}

//---------------------------------------------------------------------------
// yyyymmddhhmmss -> char[7]
bool string1C_to_date(const String& str, unsigned char* bytedate)
{
    std::u16string value = v8reader::vcl_bridge::StringToUtf16(str);
    return v8reader::core::common::string1C_to_date(value, bytedate);
}

//---------------------------------------------------------------------------
// dd.mm.yyyy hh:mm:ss -> char[7]
bool string_to_date(const String& str, unsigned char* bytedate)
{
    std::u16string value = v8reader::vcl_bridge::StringToUtf16(str);
    return v8reader::core::common::string_to_date(value, bytedate);
}

//---------------------------------------------------------------------------
// char[7] -> yyyymmddhhmmss
String date_to_string1C(const unsigned char* bytedate)
{
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::date_to_string1C(bytedate));
}

//---------------------------------------------------------------------------
// char[7] -> dd.mm.yyyy hh:mm:ss
String date_to_string(const unsigned char* bytedate)
{
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::date_to_string(bytedate));
}

//---------------------------------------------------------------------------
String hexstring(char* buf, int n)
{
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::hexstring(buf, n));
}

//---------------------------------------------------------------------------
String tohex(int n)
{
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::tohex(n));
}

//---------------------------------------------------------------------------
String tohex64(__int64 n)
{
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::tohex64(n));
}

//---------------------------------------------------------------------------
String hexstring(TStream* str)
{
    v8reader::vcl_bridge::TStreamByteStreamAdapter adapter(str);
    return v8reader::vcl_bridge::Utf16ToString(v8reader::core::common::hexstring(adapter));
}

String GetNameFromTreePath(v8catalog* cf, String& guid_md, const std::vector<int>& path)
{
    String Result = "";
    v8file* filedata = cf->GetFile(guid_md);
    if(!filedata)
    {
        return Result;
    }
    tree* tree_md = get_treeFromV8file(filedata);
    if(!tree_md)
    {
        return Result;
    }
    tree* node = tree_md;

    for(size_t i = 0; i < path.size(); ++i)
    {
        node = &(*node)[path[i]];
    }

    Result = node->get_value();

    return Result;
}

String GetNameFormCatalogs(v8catalog* cf, String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 1, 2};
    return GetNameFromTreePath(cf, guid_md, path);
}

String GetNameFormReports(v8catalog* cf, String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 1, 1, 2};
    return GetNameFromTreePath(cf, guid_md, path);
}

String GetNameFormPVH(v8catalog* cf, String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 2};
    return GetNameFromTreePath(cf, guid_md, path);
}

String GetNameFormDescriptor(v8catalog* cf, String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 2};
    return GetNameFromTreePath(cf, guid_md, path);
}

String GetNameMoxCatalogs(v8catalog* cf, String& guid_md)
{
    std::vector<int> path = {0, 1, 2, 2};
    return GetNameFromTreePath(cf, guid_md, path);
}

Utf16String GetNameFromTreePath16(v8catalog* cf, const Utf16String& guid_md, const std::vector<int>& path)
{
    String legacyGuid = v8reader::vcl_bridge::Utf16ToString(guid_md);
    return V8Utf16FromString(GetNameFromTreePath(cf, legacyGuid, path));
}

Utf16String GetNameFormCatalogs16(v8catalog* cf, const Utf16String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 1, 2};
    return GetNameFromTreePath16(cf, guid_md, path);
}

Utf16String GetNameFormReports16(v8catalog* cf, const Utf16String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 1, 1, 2};
    return GetNameFromTreePath16(cf, guid_md, path);
}

Utf16String GetNameFormPVH16(v8catalog* cf, const Utf16String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 2};
    return GetNameFromTreePath16(cf, guid_md, path);
}

Utf16String GetNameFormDescriptor16(v8catalog* cf, const Utf16String& guid_md)
{
    std::vector<int> path = {0, 1, 1, 2};
    return GetNameFromTreePath16(cf, guid_md, path);
}

Utf16String GetNameMoxCatalogs16(v8catalog* cf, const Utf16String& guid_md)
{
    std::vector<int> path = {0, 1, 2, 2};
    return GetNameFromTreePath16(cf, guid_md, path);
}

