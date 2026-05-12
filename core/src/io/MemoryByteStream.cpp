#include "v8reader_core/io/MemoryByteStream.h"

#include <algorithm>
#include <cstring>
#include <utility>

namespace v8reader::core::io {

MemoryByteStream::MemoryByteStream() : position_(0) {}

MemoryByteStream::MemoryByteStream(std::vector<std::uint8_t> initialData)
    : data_(std::move(initialData)), position_(0) {}

std::size_t MemoryByteStream::Read(void* buffer, std::size_t count)
{
    if (position_ >= data_.size() || count == 0) {
        return 0;
    }

    const std::size_t available = data_.size() - static_cast<std::size_t>(position_);
    const std::size_t toRead = std::min(count, available);
    std::memcpy(buffer, data_.data() + position_, toRead);
    position_ += toRead;
    return toRead;
}

std::size_t MemoryByteStream::Write(const void* buffer, std::size_t count)
{
    if (count == 0) {
        return 0;
    }

    const std::uint64_t endPos = position_ + count;
    if (endPos > data_.size()) {
        data_.resize(static_cast<std::size_t>(endPos));
    }

    std::memcpy(data_.data() + position_, buffer, count);
    position_ = endPos;
    return count;
}

std::uint64_t MemoryByteStream::Seek(std::int64_t offset, SeekOrigin origin)
{
    std::int64_t base = 0;
    switch (origin) {
    case SeekOrigin::Begin:
        base = 0;
        break;
    case SeekOrigin::Current:
        base = static_cast<std::int64_t>(position_);
        break;
    case SeekOrigin::End:
        base = static_cast<std::int64_t>(data_.size());
        break;
    }

    std::int64_t target = base + offset;
    if (target < 0) {
        target = 0;
    }

    position_ = static_cast<std::uint64_t>(target);
    return position_;
}

std::uint64_t MemoryByteStream::Position() const
{
    return position_;
}

std::uint64_t MemoryByteStream::Size() const
{
    return data_.size();
}

void MemoryByteStream::SetSize(std::uint64_t size)
{
    data_.resize(static_cast<std::size_t>(size));
    if (position_ > size) {
        position_ = size;
    }
}

const std::vector<std::uint8_t>& MemoryByteStream::Data() const
{
    return data_;
}

std::vector<std::uint8_t>& MemoryByteStream::Data()
{
    return data_;
}

} // namespace v8reader::core::io
