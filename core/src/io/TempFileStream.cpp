#include "v8reader_core/io/TempFileStream.h"

#include <atomic>
#include <chrono>
#include <filesystem>
#include <stdexcept>

namespace v8reader::core::io {

namespace {
std::wstring BuildTempFilePath()
{
    static std::atomic<std::uint64_t> counter{0};
    const std::filesystem::path tempDir = std::filesystem::temp_directory_path();
    const std::uint64_t tick = static_cast<std::uint64_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());

    for (std::uint64_t attempt = 0; attempt < 1024; ++attempt) {
        const std::uint64_t seq = counter.fetch_add(1, std::memory_order_relaxed);
        const std::wstring fileName = L"v8reader_tmp_" + std::to_wstring(tick) + L"_" + std::to_wstring(seq) + L".bin";
        const std::filesystem::path path = tempDir / fileName;
        if (!std::filesystem::exists(path)) {
            return path.wstring();
        }
    }

    throw std::runtime_error("Unable to create unique temp file path");
}

DWORD ToMoveMethod(SeekOrigin origin)
{
    switch (origin) {
    case SeekOrigin::Begin:
        return FILE_BEGIN;
    case SeekOrigin::Current:
        return FILE_CURRENT;
    case SeekOrigin::End:
        return FILE_END;
    }

    return FILE_BEGIN;
}
} // namespace

TempFileStream::TempFileStream() : handle_(INVALID_HANDLE_VALUE), path_(BuildTempFilePath())
{
    handle_ = ::CreateFileW(path_.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        CREATE_NEW,
        FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE,
        nullptr);

    if (handle_ == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Unable to create temp file");
    }
}

TempFileStream::~TempFileStream()
{
    if (handle_ != INVALID_HANDLE_VALUE) {
        ::CloseHandle(handle_);
        handle_ = INVALID_HANDLE_VALUE;
    }
}

std::size_t TempFileStream::Read(void* buffer, std::size_t count)
{
    if (count == 0) {
        return 0;
    }

    DWORD readBytes = 0;
    if (!::ReadFile(handle_, buffer, static_cast<DWORD>(count), &readBytes, nullptr)) {
        return 0;
    }

    return static_cast<std::size_t>(readBytes);
}

std::size_t TempFileStream::Write(const void* buffer, std::size_t count)
{
    if (count == 0) {
        return 0;
    }

    DWORD writtenBytes = 0;
    if (!::WriteFile(handle_, buffer, static_cast<DWORD>(count), &writtenBytes, nullptr)) {
        return 0;
    }

    return static_cast<std::size_t>(writtenBytes);
}

std::uint64_t TempFileStream::Seek(std::int64_t offset, SeekOrigin origin)
{
    LARGE_INTEGER distance;
    distance.QuadPart = offset;
    LARGE_INTEGER newPos{};
    if (!::SetFilePointerEx(handle_, distance, &newPos, ToMoveMethod(origin))) {
        return Position();
    }

    return static_cast<std::uint64_t>(newPos.QuadPart);
}

std::uint64_t TempFileStream::Position() const
{
    LARGE_INTEGER zero{};
    zero.QuadPart = 0;
    LARGE_INTEGER current{};
    if (!::SetFilePointerEx(handle_, zero, &current, FILE_CURRENT)) {
        return 0;
    }

    return static_cast<std::uint64_t>(current.QuadPart);
}

std::uint64_t TempFileStream::Size() const
{
    LARGE_INTEGER size{};
    if (!::GetFileSizeEx(handle_, &size)) {
        return 0;
    }

    return static_cast<std::uint64_t>(size.QuadPart);
}

void TempFileStream::SetSize(std::uint64_t size)
{
    const std::uint64_t currentPos = Position();
    LARGE_INTEGER targetSize;
    targetSize.QuadPart = static_cast<LONGLONG>(size);
    if (!::SetFilePointerEx(handle_, targetSize, nullptr, FILE_BEGIN)) {
        return;
    }
    if (!::SetEndOfFile(handle_)) {
        return;
    }

    LARGE_INTEGER restorePos;
    restorePos.QuadPart = static_cast<LONGLONG>(currentPos <= size ? currentPos : size);
    ::SetFilePointerEx(handle_, restorePos, nullptr, FILE_BEGIN);
}

} // namespace v8reader::core::io
