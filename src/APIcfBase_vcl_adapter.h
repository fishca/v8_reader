#ifndef APIcfBaseVclAdapterH
#define APIcfBaseVclAdapterH

// VCL compatibility facade for legacy code in src.
// Core implementation remains in core/src/APIcfBase.h during transition.
#include <System.Classes.hpp>
#include "../core/src/APIcfBase.h"
#include "VclByteStreamAdapter.h"
typedef System::DynamicArray<System::Byte> ByteArr;

namespace v8reader::vcl_bridge {

inline Utf16String V8Utf16FromVclString(const String& value)
{
	return Utf16String(
		reinterpret_cast<const char16_t*>(value.c_str()),
		static_cast<std::size_t>(value.Length()));
}

inline String V8VclStringFromUtf16(const Utf16String& value)
{
	return String(reinterpret_cast<const wchar_t*>(value.c_str()));
}

inline v8catalog* CreateCatalogFromVclStream(TStream* stream, bool zipped, bool leave_stream = false)
{
    if (!stream)
        return nullptr;

    // The catalog owns only adapter object; underlying VCL stream lifetime is still controlled by caller.
    auto* adapter = new TStreamByteStreamAdapter(stream);
    return new v8catalog(adapter, zipped, false);
}

inline void SaveV8FileToVclStream(v8file* file, TStream* stream)
{
    if (!file || !stream)
        return;

    TStreamByteStreamAdapter adapter(stream);
    file->SaveToByteStream(adapter);
}

inline int WriteAndCloseV8FileFromVclStream(v8file* file, TStream* stream, int length = -1)
{
    if (!file || !stream)
        return 0;

    TStreamByteStreamAdapter adapter(stream);
    return file->WriteAndClose(adapter, length);
}

inline int WriteV8FileFromVclStream(v8file* file, TStream* stream)
{
    if (!file || !stream)
        return 0;

    TStreamByteStreamAdapter adapter(stream);
    return file->Write(adapter);
}

} // namespace v8reader::vcl_bridge

#endif
