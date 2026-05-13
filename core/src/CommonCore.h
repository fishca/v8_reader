#pragma once

#include "../include/v8reader_core/io/IByteStream.h"

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace v8reader::core::common {

inline std::uint32_t reverse_byte_order(std::uint32_t value)
{
    return (value >> 24U) | ((value >> 8U) & 0x0000FF00U) | ((value << 8U) & 0x00FF0000U) | (value << 24U);
}

inline char16_t NibbleToHex(std::uint8_t value)
{
    return static_cast<char16_t>(value < 10U ? (u'0' + value) : (u'a' + (value - 10U)));
}

inline bool two_hex_digits_to_byte(char16_t hi, char16_t lo, std::uint8_t& out)
{
    auto decode_nibble = [](const char16_t ch, std::uint8_t& nibble) -> bool {
        if (ch >= u'0' && ch <= u'9') {
            nibble = static_cast<std::uint8_t>(ch - u'0');
            return true;
        }
        if (ch >= u'a' && ch <= u'f') {
            nibble = static_cast<std::uint8_t>(ch - u'a' + 10);
            return true;
        }
        if (ch >= u'A' && ch <= u'F') {
            nibble = static_cast<std::uint8_t>(ch - u'A' + 10);
            return true;
        }
        nibble = 0;
        return false;
    };

    std::uint8_t hiValue = 0;
    std::uint8_t loValue = 0;
    if (!decode_nibble(hi, hiValue) || !decode_nibble(lo, loValue)) {
        out = 0;
        return false;
    }

    out = static_cast<std::uint8_t>((hiValue << 4U) | loValue);
    return true;
}

inline std::u16string GUIDas1C(const std::uint8_t* fr)
{
    std::u16string out;
    out.reserve(36);

    auto append_byte = [&](const std::uint8_t v) {
        out.push_back(NibbleToHex(static_cast<std::uint8_t>((v >> 4U) & 0x0FU)));
        out.push_back(NibbleToHex(static_cast<std::uint8_t>(v & 0x0FU)));
    };

    for (int i = 12; i < 16; ++i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 10; i < 12; ++i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 8; i < 10; ++i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 0; i < 2; ++i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 2; i < 8; ++i) append_byte(fr[i]);

    return out;
}

inline std::u16string GUIDasMS(const std::uint8_t* fr)
{
    std::u16string out;
    out.reserve(36);

    auto append_byte = [&](const std::uint8_t v) {
        out.push_back(NibbleToHex(static_cast<std::uint8_t>((v >> 4U) & 0x0FU)));
        out.push_back(NibbleToHex(static_cast<std::uint8_t>(v & 0x0FU)));
    };

    for (int i = 3; i >= 0; --i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 5; i >= 4; --i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 7; i >= 6; --i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 8; i < 10; ++i) append_byte(fr[i]);
    out.push_back(u'-');
    for (int i = 10; i < 16; ++i) append_byte(fr[i]);

    return out;
}

inline bool string_to_GUID(std::u16string_view str, std::uint8_t* guid)
{
    for (int i = 0; i < 16; ++i) {
        guid[i] = 0;
    }

    if (str.size() != 36) {
        return false;
    }

    bool ok = true;
    std::size_t j = 0;

    for (int i = 12; i < 16; ++i) ok = ok && two_hex_digits_to_byte(str[j++], str[j++], guid[i]);
    ok = ok && (str[j++] == u'-');
    for (int i = 10; i < 12; ++i) ok = ok && two_hex_digits_to_byte(str[j++], str[j++], guid[i]);
    ok = ok && (str[j++] == u'-');
    for (int i = 8; i < 10; ++i) ok = ok && two_hex_digits_to_byte(str[j++], str[j++], guid[i]);
    ok = ok && (str[j++] == u'-');
    for (int i = 0; i < 2; ++i) ok = ok && two_hex_digits_to_byte(str[j++], str[j++], guid[i]);
    ok = ok && (str[j++] == u'-');
    for (int i = 2; i < 8; ++i) ok = ok && two_hex_digits_to_byte(str[j++], str[j++], guid[i]);

    return ok;
}

inline std::u16string GUID_to_string_flat(const std::uint8_t* guid)
{
    std::u16string out;
    out.reserve(32);
    for (int i = 0; i < 16; ++i) {
        out.push_back(NibbleToHex(static_cast<std::uint8_t>((guid[i] >> 4U) & 0x0FU)));
        out.push_back(NibbleToHex(static_cast<std::uint8_t>(guid[i] & 0x0FU)));
    }
    return out;
}

inline bool string_to_GUID_flat(std::u16string_view str, std::uint8_t* guid)
{
    if (str.size() != 32) {
        return false;
    }

    bool ok = true;
    std::size_t j = 0;
    for (int i = 0; i < 16; ++i) {
        std::uint8_t byteValue = 0;
        ok = ok && two_hex_digits_to_byte(str[j++], str[j++], byteValue);
        guid[i] = byteValue;
    }

    return ok;
}

inline bool string1C_to_date(std::u16string_view str, std::uint8_t* bytedate)
{
    if (str.size() < 14) {
        return false;
    }

    bytedate[0] = static_cast<std::uint8_t>(((str[0] - u'0') << 4) + (str[1] - u'0'));
    bytedate[1] = static_cast<std::uint8_t>(((str[2] - u'0') << 4) + (str[3] - u'0'));
    bytedate[2] = static_cast<std::uint8_t>(((str[4] - u'0') << 4) + (str[5] - u'0'));
    bytedate[3] = static_cast<std::uint8_t>(((str[6] - u'0') << 4) + (str[7] - u'0'));
    bytedate[4] = static_cast<std::uint8_t>(((str[8] - u'0') << 4) + (str[9] - u'0'));
    bytedate[5] = static_cast<std::uint8_t>(((str[10] - u'0') << 4) + (str[11] - u'0'));
    bytedate[6] = static_cast<std::uint8_t>(((str[12] - u'0') << 4) + (str[13] - u'0'));
    return true;
}

inline bool string_to_date(std::u16string_view str, std::uint8_t* bytedate)
{
    if (str.size() < 19) {
        return false;
    }

    bytedate[3] = static_cast<std::uint8_t>(((str[0] - u'0') << 4) + (str[1] - u'0'));
    bytedate[2] = static_cast<std::uint8_t>(((str[3] - u'0') << 4) + (str[4] - u'0'));
    bytedate[0] = static_cast<std::uint8_t>(((str[6] - u'0') << 4) + (str[7] - u'0'));
    bytedate[1] = static_cast<std::uint8_t>(((str[8] - u'0') << 4) + (str[9] - u'0'));
    bytedate[4] = static_cast<std::uint8_t>(((str[11] - u'0') << 4) + (str[12] - u'0'));
    bytedate[5] = static_cast<std::uint8_t>(((str[14] - u'0') << 4) + (str[15] - u'0'));
    bytedate[6] = static_cast<std::uint8_t>(((str[17] - u'0') << 4) + (str[18] - u'0'));
    return true;
}

inline std::u16string date_to_string1C(const std::uint8_t* bytedate)
{
    std::u16string out(14, u'0');
    out[0] = static_cast<char16_t>(u'0' + ((bytedate[0] >> 4) & 0x0FU));
    out[1] = static_cast<char16_t>(u'0' + (bytedate[0] & 0x0FU));
    out[2] = static_cast<char16_t>(u'0' + ((bytedate[1] >> 4) & 0x0FU));
    out[3] = static_cast<char16_t>(u'0' + (bytedate[1] & 0x0FU));
    out[4] = static_cast<char16_t>(u'0' + ((bytedate[2] >> 4) & 0x0FU));
    out[5] = static_cast<char16_t>(u'0' + (bytedate[2] & 0x0FU));
    out[6] = static_cast<char16_t>(u'0' + ((bytedate[3] >> 4) & 0x0FU));
    out[7] = static_cast<char16_t>(u'0' + (bytedate[3] & 0x0FU));
    out[8] = static_cast<char16_t>(u'0' + ((bytedate[4] >> 4) & 0x0FU));
    out[9] = static_cast<char16_t>(u'0' + (bytedate[4] & 0x0FU));
    out[10] = static_cast<char16_t>(u'0' + ((bytedate[5] >> 4) & 0x0FU));
    out[11] = static_cast<char16_t>(u'0' + (bytedate[5] & 0x0FU));
    out[12] = static_cast<char16_t>(u'0' + ((bytedate[6] >> 4) & 0x0FU));
    out[13] = static_cast<char16_t>(u'0' + (bytedate[6] & 0x0FU));
    return out;
}

inline std::u16string date_to_string(const std::uint8_t* bytedate)
{
    std::u16string out(19, u'0');
    out[0] = static_cast<char16_t>(u'0' + ((bytedate[3] >> 4) & 0x0FU));
    out[1] = static_cast<char16_t>(u'0' + (bytedate[3] & 0x0FU));
    out[2] = u'.';
    out[3] = static_cast<char16_t>(u'0' + ((bytedate[2] >> 4) & 0x0FU));
    out[4] = static_cast<char16_t>(u'0' + (bytedate[2] & 0x0FU));
    out[5] = u'.';
    out[6] = static_cast<char16_t>(u'0' + ((bytedate[0] >> 4) & 0x0FU));
    out[7] = static_cast<char16_t>(u'0' + (bytedate[0] & 0x0FU));
    out[8] = static_cast<char16_t>(u'0' + ((bytedate[1] >> 4) & 0x0FU));
    out[9] = static_cast<char16_t>(u'0' + (bytedate[1] & 0x0FU));
    out[10] = u' ';
    out[11] = static_cast<char16_t>(u'0' + ((bytedate[4] >> 4) & 0x0FU));
    out[12] = static_cast<char16_t>(u'0' + (bytedate[4] & 0x0FU));
    out[13] = u':';
    out[14] = static_cast<char16_t>(u'0' + ((bytedate[5] >> 4) & 0x0FU));
    out[15] = static_cast<char16_t>(u'0' + (bytedate[5] & 0x0FU));
    out[16] = u':';
    out[17] = static_cast<char16_t>(u'0' + ((bytedate[6] >> 4) & 0x0FU));
    out[18] = static_cast<char16_t>(u'0' + (bytedate[6] & 0x0FU));
    return out;
}

inline std::u16string U32ToHex(std::uint32_t value, int minWidth = 0)
{
    std::u16string digits;
    do {
        const std::uint8_t nibble = static_cast<std::uint8_t>(value & 0x0FU);
        digits.push_back(static_cast<char16_t>(nibble < 10U ? (u'0' + nibble) : (u'A' + nibble - 10U)));
        value >>= 4U;
    } while (value != 0);

    while (static_cast<int>(digits.size()) < minWidth) {
        digits.push_back(u'0');
    }

    std::u16string out;
    out.reserve(digits.size());
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        out.push_back(*it);
    }
    return out;
}

inline std::u16string tohex(int n)
{
    std::u16string out = u"0x";
    out += U32ToHex(static_cast<std::uint32_t>(n));
    return out;
}

inline std::u16string tohex64(std::int64_t n)
{
    const std::uint64_t un = static_cast<std::uint64_t>(n);
    const std::int32_t nh = static_cast<std::int32_t>(un >> 32U);
    const std::int32_t nl = static_cast<std::int32_t>(un & 0xFFFFFFFFULL);

    std::u16string out = u"0x";
    if (nh != 0) {
        out += U32ToHex(static_cast<std::uint32_t>(nh));
        out += U32ToHex(static_cast<std::uint32_t>(nl), 8);
    } else {
        out += U32ToHex(static_cast<std::uint32_t>(nl));
    }
    return out;
}

inline std::u16string hexstring(const char* buf, int n)
{
    if (buf == nullptr || n <= 0) {
        return u"";
    }

    std::u16string out;
    out.reserve(static_cast<std::size_t>(n) * 3U);
    for (int i = 0; i < n; ++i) {
        const std::uint8_t value = static_cast<std::uint8_t>(buf[i]);
        out.push_back(NibbleToHex(static_cast<std::uint8_t>((value >> 4U) & 0x0FU)));
        out.push_back(NibbleToHex(static_cast<std::uint8_t>(value & 0x0FU)));
        if (i < (n - 1)) {
            out.push_back(u' ');
        }
    }
    return out;
}

inline std::u16string hexstring(io::IByteStream& stream)
{
    std::u16string out;
    std::uint8_t byteValue = 0;

    while (stream.Read(&byteValue, 1U) == 1U) {
        out.push_back(NibbleToHex(static_cast<std::uint8_t>((byteValue >> 4U) & 0x0FU)));
        out.push_back(NibbleToHex(static_cast<std::uint8_t>(byteValue & 0x0FU)));
    }

    return out;
}

} // namespace v8reader::core::common

