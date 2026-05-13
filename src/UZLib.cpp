//---------------------------------------------------------------------------

#pragma hdrstop

#include "UZLib.h"

#include "VclByteStreamAdapter.h"
#include "../core/src/UZlib.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using v8reader::vcl_bridge::TStreamByteStreamAdapter;

void ZInflateStream(TStream* src, TStream* dst)
{
	if(!src || !dst)
		return;

	TStreamByteStreamAdapter srcAdapter(src);
	TStreamByteStreamAdapter dstAdapter(dst);
	::ZInflateStream(srcAdapter, dstAdapter);
}

void ZDeflateStream(TStream* src, TStream* dst)
{
	if(!src || !dst)
		return;

	TStreamByteStreamAdapter srcAdapter(src);
	TStreamByteStreamAdapter dstAdapter(dst);
	::ZDeflateStream(srcAdapter, dstAdapter);
}
