//---------------------------------------------------------------------------

#ifndef UZlibH
#define UZlibH

#include <cstdio>

#include "../include/v8reader_core/io/IByteStream.h"
#include "zlib.h"

void ZInflateStream(v8reader::core::io::IByteStream& src, v8reader::core::io::IByteStream& dst);
void ZDeflateStream(v8reader::core::io::IByteStream& src, v8reader::core::io::IByteStream& dst);

int inf(FILE* source, FILE* dest);
int def(FILE* source, FILE* dest, int level);

#endif

