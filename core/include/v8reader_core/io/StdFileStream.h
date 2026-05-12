#pragma once

#include "IByteStream.h"

#include <filesystem>
#include <fstream>

namespace v8reader::core::io {

enum class FileOpenMode {
    ReadOnly,
    ReadWrite,
    CreateTruncate,
};

class StdFileStream final : public IByteStream {
public:
    StdFileStream(const std::filesystem::path& filePath, FileOpenMode mode);
    ~StdFileStream() override;

    StdFileStream(const StdFileStream&) = delete;
    StdFileStream& operator=(const StdFileStream&) = delete;

    std::size_t Read(void* buffer, std::size_t count) override;
    std::size_t Write(const void* buffer, std::size_t count) override;
    std::uint64_t Seek(std::int64_t offset, SeekOrigin origin) override;
    std::uint64_t Position() const override;
    std::uint64_t Size() const override;
    void SetSize(std::uint64_t size) override;

    bool IsOpen() const;

private:
    mutable std::fstream stream_;
    std::filesystem::path path_;
};

} // namespace v8reader::core::io
