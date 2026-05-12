#include "v8reader_core/io/StdFileStream.h"

#include <stdexcept>

namespace v8reader::core::io {

namespace {
std::ios::openmode ToStdOpenMode(FileOpenMode mode)
{
    switch (mode) {
    case FileOpenMode::ReadOnly:
        return std::ios::in | std::ios::binary;
    case FileOpenMode::ReadWrite:
        return std::ios::in | std::ios::out | std::ios::binary;
    case FileOpenMode::CreateTruncate:
        return std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc;
    }

    return std::ios::in | std::ios::binary;
}

std::ios::seekdir ToSeekDir(SeekOrigin origin)
{
    switch (origin) {
    case SeekOrigin::Begin:
        return std::ios::beg;
    case SeekOrigin::Current:
        return std::ios::cur;
    case SeekOrigin::End:
        return std::ios::end;
    }

    return std::ios::beg;
}
} // namespace

StdFileStream::StdFileStream(const std::filesystem::path& filePath, FileOpenMode mode)
    : path_(filePath)
{
    stream_.open(path_, ToStdOpenMode(mode));
    if (!stream_.is_open() && mode == FileOpenMode::ReadWrite && !std::filesystem::exists(path_)) {
        std::ofstream createFile(path_, std::ios::binary);
        createFile.close();
        stream_.open(path_, ToStdOpenMode(mode));
    }
}

StdFileStream::~StdFileStream()
{
    if (stream_.is_open()) {
        stream_.close();
    }
}

std::size_t StdFileStream::Read(void* buffer, std::size_t count)
{
    stream_.read(static_cast<char*>(buffer), static_cast<std::streamsize>(count));
    return static_cast<std::size_t>(stream_.gcount());
}

std::size_t StdFileStream::Write(const void* buffer, std::size_t count)
{
    stream_.write(static_cast<const char*>(buffer), static_cast<std::streamsize>(count));
    return count;
}

std::uint64_t StdFileStream::Seek(std::int64_t offset, SeekOrigin origin)
{
    const auto dir = ToSeekDir(origin);
    stream_.seekg(offset, dir);
    stream_.seekp(offset, dir);
    return Position();
}

std::uint64_t StdFileStream::Position() const
{
    std::streampos p = stream_.tellg();
    if (p == static_cast<std::streampos>(-1)) {
        p = stream_.tellp();
    }
    if (p == static_cast<std::streampos>(-1)) {
        return 0;
    }

    return static_cast<std::uint64_t>(p);
}

std::uint64_t StdFileStream::Size() const
{
    if (!std::filesystem::exists(path_)) {
        return 0;
    }

    return static_cast<std::uint64_t>(std::filesystem::file_size(path_));
}

void StdFileStream::SetSize(std::uint64_t size)
{
    stream_.flush();
    std::filesystem::resize_file(path_, static_cast<std::uintmax_t>(size));
    if (Position() > size) {
        const_cast<StdFileStream*>(this)->Seek(static_cast<std::int64_t>(size), SeekOrigin::Begin);
    }
}

bool StdFileStream::IsOpen() const
{
    return stream_.is_open();
}

} // namespace v8reader::core::io
