//---------------------------------------------------------------------------

#ifndef TempStreamH
#define TempStreamH

#include <System.Classes.hpp>
#include <memory>

namespace v8reader::core::io {
class TempFileStream;
}


//---------------------------------------------------------------------------
class TTempStream : public TStream
{
public:
	TTempStream();
	virtual ~TTempStream();

	virtual int __fastcall Read(void* Buffer, int Count) override;
	virtual int __fastcall Write(const void* Buffer, int Count) override;
	virtual int __fastcall Seek(int Offset, System::Word Origin) override;
	virtual __int64 __fastcall Seek(const __int64 Offset, TSeekOrigin Origin) override;

private:
	std::unique_ptr<v8reader::core::io::TempFileStream> stream_;
};

//---------------------------------------------------------------------------
#endif
