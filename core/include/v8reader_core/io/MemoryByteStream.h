#pragma once

#include "IByteStream.h"

#include <vector>

namespace v8reader::core::io {

class MemoryByteStream final : public IByteStream {
public:
    MemoryByteStream();
    explicit MemoryByteStream(std::vector<std::uint8_t> initialData);

    std::size_t Read(void* buffer, std::size_t count) override;
    std::size_t Write(const void* buffer, std::size_t count) override;
    std::uint64_t Seek(std::int64_t offset, SeekOrigin origin) override;
    std::uint64_t Position() const override;
    std::uint64_t Size() const override;
    void SetSize(std::uint64_t size) override;

    const std::vector<std::uint8_t>& Data() const;
    std::vector<std::uint8_t>& Data();

private:
    std::vector<std::uint8_t> data_;
    std::uint64_t position_;
};

} // namespace v8reader::core::io
