#pragma once

#include "../include/v8reader_core/io/IByteStream.h"

#include <cstddef>
#include <string_view>

namespace v8reader::core::encoding {

void base64_encode(io::IByteStream& infile, io::IByteStream& outfile, int linesize);
void base64_decode(io::IByteStream& infile, io::IByteStream& outfile);
void base64_decode(std::u16string_view instr, io::IByteStream& outfile, std::size_t start = 0);

} // namespace v8reader::core::encoding

