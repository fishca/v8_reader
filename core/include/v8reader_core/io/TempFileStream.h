#pragma once

#include "IByteStream.h"

#include <string>
#include <windows.h>

namespace v8reader::core::io {

class TempFileStream final : public IByteStream {
public:
    TempFileStream();
    ~TempFileStream() override;

    TempFileStream(const TempFileStream&) = delete;
    TempFileStream& operator=(const TempFileStream&) = delete;

    std::size_t Read(void* buffer, std::size_t count) override;
    std::size_t Write(const void* buffer, std::size_t count) override;
    std::uint64_t Seek(std::int64_t offset, SeekOrigin origin) override;
    std::uint64_t Position() const override;
    std::uint64_t Size() const override;
    void SetSize(std::uint64_t size) override;

private:
    HANDLE handle_;
    std::wstring path_;
};

} // namespace v8reader::core::io
