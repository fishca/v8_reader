//=====================================================//
//      Модуль по работе с файлами 1С                  //
//      (c) awa                                        //
//                                                     //
//                                                     //
//=====================================================//

#ifndef APIcfBaseH
#define APIcfBaseH

#include <System.Classes.hpp>
#include <map>
#include <set>

//#include "Zip.h"

#pragma package(smart_init)

#ifndef _DELPHI_STRING_UNICODE
	#define UnicodeString AnsiString
	#define CompareIC AnsiCompareIC
	#define str_cfu ".cfu"
	#define str_cfe ".cfe"
	#define str_cf ".cf"
	#define str_epf ".epf"
	#define str_erf ".erf"
	#define str_backslash "\\"
#else
	#define str_cfu L".cfu"
	#define str_cfe L".cfe"
	#define str_cf L".cf"
	#define str_epf L".epf"
	#define str_erf L".erf"
	#define str_backslash L"\\"
#endif

typedef System::DynamicArray<System::Byte> ByteArr;

//===========================================================================
const size_t V8_DEFAULT_PAGE_SIZE = 512;
const uint32_t V8_FF_SIGNATURE = 0x7fffffff;

// Для конфигурации старше 8.3.16, без режима совместимости
//const uint64_t V8_FF64_SIGNATURE = 0xffffffffffffffff;
const __int64 V8_FF64_SIGNATURE = 0xffffffffffffffff;
//const size_t V8_OFFSET_8316 = 0x1359;  // волшебное смещение, откуда такая цифра неизвестно...
const int V8_OFFSET_8316 = 0x1359;  // волшебное смещение, откуда такая цифра неизвестно...


//===========================================================================
struct v8header_struct
{
	__int64 time_create;
	__int64 time_modify;
	int zero;
	//wchar_t* name;
};

//===========================================================================
struct fat_item
{
	int header_start;
	int data_start;
	int ff; // всегда 7fffffff
};

//===========================================================================
struct fat_item8316
{
	__int64 header_start;
	__int64 data_start;
	__int64 ff; // всегда 7fffffff
};

//===========================================================================
struct catalog_header
{
	int start_empty; // начало первого пустого блока
	int page_size;   // размер страницы по умолчанию
	int version;     // версия
	int zero;        // всегда ноль?
};

//===========================================================================
struct catalog_header8316
{
	__int64 start_empty; // начало первого пустого блока
	int page_size;       // размер страницы по умолчанию
	int version;         // версия
	int zero;            // всегда ноль?
};


//===========================================================================
class v8catalog;
class TV8FileStream;

//===========================================================================
enum FileIsCatalog
{
	iscatalog_unknown,
	iscatalog_true,
	iscatalog_false
};

//===========================================================================
class v8file
{
  private:
	friend v8catalog;
	friend TV8FileStream;

	String name;

	__int64 time_create;
	__int64 time_modify;

	TCriticalSection *Lock;

	TStream* data;

	v8catalog* parent;

	FileIsCatalog iscatalog;

	v8catalog* self; // указатель на каталог, если файл является каталогом

	v8file* next;      // следующий файл в каталоге
	v8file* previous;  // предыдущий файл в каталоге

	bool is_opened;    // признак открытого файла (инициализирован поток data)

	int start_data;   // начало блока данных файла в каталоге (0 означает, что файл в каталоге не записан)
	int start_header; // начало блока заголовка файла в каталоге

	bool is_datamodified;   // признак модифицированности данных файла (требуется запись в каталог при закрытии)
	bool is_headermodified; // признак модифицированности заголовка файла (требуется запись в каталог при закрытии)

	bool is_destructed; // признак, что работает деструктор
	bool flushed;       // признак, что происходит сброс
//	bool readonly;
	bool selfzipped; // Признак, что файл является запакованным независимо от признака zipped каталога

	std::set<TV8FileStream*> streams;

  public:
	__fastcall v8file(v8catalog* _parent, const String& _name, v8file* _previous, int _start_data, int _start_header, __int64* _time_create, __int64* _time_modify);

	__fastcall ~v8file();

	bool __fastcall IsCatalog();

	v8catalog* __fastcall GetCatalog();

	int __fastcall GetFileLength();
	__int64 __fastcall GetFileLength64();

	int __fastcall Read(void* Buffer, int Start, int Length);
	int __fastcall Read(ByteArr Buffer, int Start, int Length);

    // дозапись/перезапись частично
	int __fastcall Write(const void* Buffer, int Start, int Length);
    // дозапись/перезапись частично
	int __fastcall Write(ByteArr Buffer, int Start, int Length);

    // перезапись целиком
	int __fastcall Write(const void* Buffer, int Length);
    // дозапись/перезапись частично
	int __fastcall Write(TStream* Stream, int Start, int Length);
    // перезапись целиком
	int __fastcall Write(TStream* Stream);

	String __fastcall GetFileName();
	String __fastcall GetFullName();

	void __fastcall SetFileName(const String& _name);

	v8catalog* __fastcall GetParentCatalog();

	void __fastcall DeleteFile();

	v8file* __fastcall GetNext();

	bool __fastcall Open();
	void __fastcall Close();

    // перезапись целиком и закрытие файла (для экономии памяти не используется data файла)
	int __fastcall WriteAndClose(TStream* Stream, int Length = -1);

	void __fastcall GetTimeCreate(FILETIME* ft);
	void __fastcall GetTimeModify(FILETIME* ft);
	void __fastcall SetTimeCreate(FILETIME* ft);
	void __fastcall SetTimeModify(FILETIME* ft);

	void __fastcall SaveToFile(const String& FileName);
	void __fastcall SaveToStream(TStream* stream);
	//TStream* __fastcall get_data();

	TV8FileStream* __fastcall get_stream(bool own = false);

	void __fastcall Flush();
};

//===========================================================================
class v8catalog
{
  private:
	friend v8file;

	TCriticalSection *Lock;

	v8file* file; // файл, которым является каталог. Для корневого каталога NULL

	TStream* data; // поток каталога. Если file не NULL (каталог не корневой), совпадает с file->data
	TStream* cfu;  // поток файла cfu. Существует только при is_cfu == true

	void __fastcall initialize(int Offset = 0);


	v8file* first; // первый файл в каталоге
	v8file* last;  // последний файл в каталоге

	std::map<String, v8file*> files; // Соответствие имен и файлов

	int     start_empty; // начало первого пустого блока
    __int64 start_empty8316;

	int page_size;   // размер страницы по умолчанию

	int version; // версия

	bool zipped; // признак зазипованности файлов каталога
	bool is_cfu; // признак файла cfu (файл запакован deflate'ом)
	bool iscatalog;
	bool iscatalogdefined;

	bool is_fatmodified;
	bool is_emptymodified;
	bool is_modified;

    bool is_8316;

	void __fastcall free_block(int start);

    // возвращает адрес начала блока
	int __fastcall write_block(TStream* block, int start, bool use_page_size, int len = -1);

    // возвращает адрес начала блока
	int __fastcall write_datablock(TStream* block, int start, bool _zipped = false, int len = -1);

	TStream* __fastcall read_datablock(int start, int offset = 0);

	int __fastcall get_nextblock(int start);

	bool is_destructed; // признак, что работает деструктор
	bool flushed;       // признак, что происходит сброс
	bool leave_data;    // признак, что не нужно удалять основной поток (data) при уничтожении объекта

  public:
//	bool readonly;
	__fastcall v8catalog(v8file* f);   // создать каталог из файла
	__fastcall v8catalog(String name); // создать каталог из физического файла (cf, epf, erf, hbk, cfu)
	__fastcall v8catalog(String name, bool _zipped); // создать каталог из физического файла (cf, epf, erf, hbk, cfu)
	__fastcall v8catalog(TStream* stream, bool _zipped, bool leave_stream = false); // создать каталог из потока

	__fastcall ~v8catalog();

	bool __fastcall IsCatalog();
    bool __fastcall Is8316();
	v8file* __fastcall GetFile(const String& FileName);
	v8file* __fastcall GetFirst();

    // CreateFile в win64 определяется как CreateFileW, пришлось заменить на маленькую букву
	v8file* __fastcall createFile(const String& FileName, bool _selfzipped = false);
	v8catalog* __fastcall CreateCatalog(const String& FileName, bool _selfzipped = false);
	void __fastcall DeleteFile(const String& FileName);
	v8catalog* __fastcall GetParentCatalog();
	//void __fastcall Defrag(bool Recursively);
	v8file* __fastcall GetSelfFile();
	void __fastcall SaveToDir(String DirName);
	bool __fastcall isOpen();
	void __fastcall Flush();
	void __fastcall HalfClose();
	void __fastcall HalfOpen(const String& name);
	//void __fastcall set_leave_data(bool ld);
};

//===========================================================================
class TV8FileStream : public TStream
{
protected:
	v8file* file;
	bool own;
	__int64 pos;
public:
	__fastcall TV8FileStream(v8file* f, bool ownfile = false);
	virtual __fastcall ~TV8FileStream();

	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Read(ByteArr Buffer, int Offset, int Count);

	virtual int __fastcall Write(const void *Buffer, int Count);
	virtual int __fastcall Write(const ByteArr Buffer, int Offset, int Count);

	virtual int     __fastcall Seek(int Offset, System::Word Origin);
	virtual __int64 __fastcall Seek(const __int64 Offset, TSeekOrigin Origin);
};

#endif

