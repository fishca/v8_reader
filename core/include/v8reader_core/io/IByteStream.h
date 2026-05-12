#pragma once

#include <cstddef>
#include <cstdint>

namespace v8reader::core::io {

enum class SeekOrigin {
    Begin,
    Current,
    End,
};

class IByteStream {
public:
    virtual ~IByteStream() = default;

    virtual std::size_t Read(void* buffer, std::size_t count) = 0;
    virtual std::size_t Write(const void* buffer, std::size_t count) = 0;
    virtual std::uint64_t Seek(std::int64_t offset, SeekOrigin origin) = 0;
    virtual std::uint64_t Position() const = 0;
    virtual std::uint64_t Size() const = 0;
    virtual void SetSize(std::uint64_t size) = 0;
};

} // namespace v8reader::core::io
