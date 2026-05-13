//---------------------------------------------------------------------------

#ifndef UZLibH
#define UZLibH

#include <cstdio>

#include <System.Classes.hpp>

void ZInflateStream(TStream* src, TStream* dst);
void ZDeflateStream(TStream* src, TStream* dst);

int inf(FILE* source, FILE* dest);
int def(FILE* source, FILE* dest, int level);

#endif
