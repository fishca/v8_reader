#pragma once

#include <System.Classes.hpp>
#include <System.hpp>

#include "../core/include/v8reader_core/io/IByteStream.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace v8reader::vcl_bridge {

class TStreamByteStreamAdapter final : public core::io::IByteStream
{
public:
    explicit TStreamByteStreamAdapter(TStream* stream)
        : stream_(stream) {}

    std::size_t Read(void* buffer, std::size_t count) override
    {
        return static_cast<std::size_t>(stream_->Read(buffer, static_cast<int>(count)));
    }

    std::size_t Write(const void* buffer, std::size_t count) override
    {
        return static_cast<std::size_t>(stream_->Write(buffer, static_cast<int>(count)));
    }

    std::uint64_t Seek(std::int64_t offset, core::io::SeekOrigin origin) override
    {
        TSeekOrigin vclOrigin = soBeginning;
        switch (origin) {
        case core::io::SeekOrigin::Begin:
            vclOrigin = soBeginning;
            break;
        case core::io::SeekOrigin::Current:
            vclOrigin = soCurrent;
            break;
        case core::io::SeekOrigin::End:
            vclOrigin = soEnd;
            break;
        }

        return static_cast<std::uint64_t>(stream_->Seek(offset, vclOrigin));
    }

    std::uint64_t Position() const override
    {
        return static_cast<std::uint64_t>(stream_->Position);
    }

    std::uint64_t Size() const override
    {
        return static_cast<std::uint64_t>(stream_->Size);
    }

    void SetSize(std::uint64_t size) override
    {
        stream_->Size = static_cast<__int64>(size);
    }

private:
    TStream* stream_;
};

inline std::u16string StringToUtf16(const String& value)
{
#ifndef _DELPHI_STRING_UNICODE
    const int ws = value.WideCharBufSize();
    std::vector<wchar_t> buffer(ws);
    value.WideChar(buffer.data(), ws);
    return std::u16string(reinterpret_cast<const char16_t*>(buffer.data()));
#else
    const wchar_t* w = reinterpret_cast<const wchar_t*>(value.c_str());
    return std::u16string(reinterpret_cast<const char16_t*>(w), value.Length());
#endif
}

inline String Utf16ToString(const std::u16string_view value)
{
#ifndef _DELPHI_STRING_UNICODE
    std::vector<wchar_t> buffer(value.size() + 1);
    for (std::size_t i = 0; i < value.size(); ++i) {
        buffer[i] = static_cast<wchar_t>(value[i]);
    }
    buffer[value.size()] = 0;
    return String(buffer.data());
#else
    return String(reinterpret_cast<const wchar_t*>(value.data()), static_cast<int>(value.size()));
#endif
}

} // namespace v8reader::vcl_bridge
