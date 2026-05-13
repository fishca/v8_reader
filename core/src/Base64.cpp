#include "Base64.h"

#include <array>
#include <cstdint>

namespace v8reader::core::encoding {

namespace {

// Translation table as described in RFC1113.
constexpr char kEncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Translation table to decode (historical mapping preserved).
constexpr char kDecodeTable[] = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

bool ReadUtf16CodeUnit(io::IByteStream& stream, char16_t& value)
{
    std::uint8_t bytes[2] = {0, 0};
    const std::size_t read = stream.Read(bytes, sizeof(bytes));
    if (read != sizeof(bytes)) {
        return false;
    }

    value = static_cast<char16_t>(bytes[0] | (static_cast<std::uint16_t>(bytes[1]) << 8));
    return true;
}

unsigned char DecodeSymbol(char16_t ch)
{
    if (ch < 43 || ch > 122) {
        return 0;
    }

    unsigned char value = static_cast<unsigned char>(kDecodeTable[ch - 43]);
    if (value == 0) {
        return 0;
    }

    value = static_cast<unsigned char>((value == '$') ? 0 : (value - 61));
    return value;
}

} // namespace

void base64_encode(io::IByteStream& infile, io::IByteStream& outfile, int linesize)
{
    std::array<std::uint8_t, 3> in = {0, 0, 0};
    std::array<char16_t, 4> out = {0, 0, 0, 0};
    constexpr char16_t kCrLf[2] = {u'\r', u'\n'};

    int blocksout = 0;
    const std::uint64_t inlenblock = infile.Size() / 3;

    infile.Seek(0, io::SeekOrigin::Begin);
    for (std::uint64_t i = 0; i < inlenblock; ++i) {
        if (linesize != 0 && blocksout >= linesize / 4) {
            outfile.Write(kCrLf, sizeof(kCrLf));
            blocksout = 0;
        }

        ++blocksout;
        infile.Read(in.data(), in.size());
        out[0] = static_cast<char16_t>(kEncodeTable[in[0] >> 2]);
        out[1] = static_cast<char16_t>(kEncodeTable[((in[0] & 0x03U) << 4U) | ((in[1] & 0xF0U) >> 4U)]);
        out[2] = static_cast<char16_t>(kEncodeTable[((in[1] & 0x0FU) << 2U) | ((in[2] & 0xC0U) >> 6U)]);
        out[3] = static_cast<char16_t>(kEncodeTable[in[2] & 0x3FU]);
        outfile.Write(out.data(), sizeof(out));
    }

    const int len = static_cast<int>(infile.Size() - infile.Position());
    if (len > 0) {
        if (linesize != 0 && blocksout >= linesize / 4) {
            outfile.Write(kCrLf, sizeof(kCrLf));
        }

        in[1] = 0;
        in[2] = 0;
        infile.Read(in.data(), static_cast<std::size_t>(len));
        out[0] = static_cast<char16_t>(kEncodeTable[in[0] >> 2]);
        out[1] = static_cast<char16_t>(kEncodeTable[((in[0] & 0x03U) << 4U) | ((in[1] & 0xF0U) >> 4U)]);
        out[2] = (len > 1) ? static_cast<char16_t>(kEncodeTable[((in[1] & 0x0FU) << 2U) | ((in[2] & 0xC0U) >> 6U)]) : u'=';
        out[3] = (len > 2) ? static_cast<char16_t>(kEncodeTable[in[2] & 0x3FU]) : u'=';
        outfile.Write(out.data(), sizeof(out));
    }
}

void base64_decode(io::IByteStream& infile, io::IByteStream& outfile)
{
    std::array<unsigned char, 4> in = {0, 0, 0, 0};
    std::array<unsigned char, 3> out = {0, 0, 0};

    while (infile.Position() < infile.Size()) {
        int len = 0;
        for (int i = 0; i < 4 && infile.Position() < infile.Size(); ++i) {
            unsigned char v = 0;
            while (infile.Position() < infile.Size() && v == 0) {
                char16_t s = 0;
                if (!ReadUtf16CodeUnit(infile, s)) {
                    break;
                }
                v = DecodeSymbol(s);
            }

            if (v != 0) {
                in[i] = static_cast<unsigned char>(v - 1);
                ++len;
            } else {
                in[i] = 0;
            }
        }

        if (len > 0) {
            out[0] = static_cast<unsigned char>((in[0] << 2U) | (in[1] >> 4U));
            out[1] = static_cast<unsigned char>((in[1] << 4U) | (in[2] >> 2U));
            out[2] = static_cast<unsigned char>(((in[2] << 6U) & 0xC0U) | in[3]);
            outfile.Write(out.data(), static_cast<std::size_t>(len - 1));
        }
    }
}

void base64_decode(std::u16string_view instr, io::IByteStream& outfile, std::size_t start)
{
    std::array<unsigned char, 4> in = {0, 0, 0, 0};
    std::array<unsigned char, 3> out = {0, 0, 0};

    std::size_t index = start;
    while (index < instr.size()) {
        int len = 0;
        for (int i = 0; i < 4 && index < instr.size(); ++i) {
            unsigned char v = 0;
            while (index < instr.size() && v == 0) {
                v = DecodeSymbol(instr[index++]);
            }

            if (v != 0) {
                in[i] = static_cast<unsigned char>(v - 1);
                ++len;
            } else {
                in[i] = 0;
            }
        }

        if (len > 0) {
            out[0] = static_cast<unsigned char>((in[0] << 2U) | (in[1] >> 4U));
            out[1] = static_cast<unsigned char>((in[1] << 4U) | (in[2] >> 2U));
            out[2] = static_cast<unsigned char>(((in[2] << 6U) & 0xC0U) | in[3]);
            outfile.Write(out.data(), static_cast<std::size_t>(len - 1));
        }
    }
}

} // namespace v8reader::core::encoding

