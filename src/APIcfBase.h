//=====================================================//
//      Модуль по работе с файлами 1С                  //
//      (c) awa                                        //
//                                                     //
//                                                     //
//=====================================================//

#ifndef APIcfBaseH
#define APIcfBaseH

#include <System.Classes.hpp>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>
#include <map>

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
using ByteVector = std::vector<std::uint8_t>;
using Utf16String = std::u16string;

class V8RecursiveMutex
{
  private:
	std::recursive_mutex mutex_;

  public:
	void Acquire() { mutex_.lock(); }
	void Release() { mutex_.unlock(); }
};

class V8ScopedLock
{
  private:
	V8RecursiveMutex* lock_;

  public:
	explicit V8ScopedLock(V8RecursiveMutex* lock) : lock_(lock)
	{
		if(lock_)
			lock_->Acquire();
	}

	~V8ScopedLock()
	{
		if(lock_)
			lock_->Release();
	}
};

//===========================================================================
#include "v8_constants.h"


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

	String name;

	__int64 time_create;
	__int64 time_modify;

	V8RecursiveMutex *Lock;

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

  public:
	v8file(v8catalog* _parent, const String& _name, v8file* _previous, int _start_data, int _start_header, __int64* _time_create, __int64* _time_modify);

	~v8file();

	bool IsCatalog();

	v8catalog* GetCatalog();

	int GetFileLength();
	__int64 GetFileLength64();

	int Read(void* Buffer, int Start, int Length);
	int Read(ByteVector& Buffer, int Start, int Length);

    // дозапись/перезапись частично
	int Write(const void* Buffer, int Start, int Length);
    // дозапись/перезапись частично
	int Write(const ByteVector& Buffer, int Start, int Length);

    // перезапись целиком
	int Write(const void* Buffer, int Length);
    // дозапись/перезапись частично
	int Write(TStream* Stream, int Start, int Length);
    // перезапись целиком
	int Write(TStream* Stream);

	String GetFileName();
	Utf16String GetFileName16();
	String GetFullName();

	void SetFileName(const String& _name);
	void SetFileName16(const Utf16String& _name);

	v8catalog* GetParentCatalog();

	void DeleteFile();

	v8file* GetNext();

	bool Open();
	void Close();

    // перезапись целиком и закрытие файла (для экономии памяти не используется data файла)
	int WriteAndClose(TStream* Stream, int Length = -1);

	void GetTimeCreate(FILETIME* ft);
	void GetTimeModify(FILETIME* ft);
	void SetTimeCreate(FILETIME* ft);
	void SetTimeModify(FILETIME* ft);

	void SaveToFile(const String& FileName);
	void SaveToStream(TStream* stream);
	//TStream* get_data();

	void Flush();
};

//===========================================================================
class v8catalog
{
  private:
	friend v8file;

	V8RecursiveMutex *Lock;

	v8file* file; // файл, которым является каталог. Для корневого каталога NULL

	TStream* data; // поток каталога. Если file не NULL (каталог не корневой), совпадает с file->data
	TStream* cfu;  // поток файла cfu. Существует только при is_cfu == true

	void initialize(int Offset = 0);


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

	void free_block(int start);

    // возвращает адрес начала блока
	int write_block(TStream* block, int start, bool use_page_size, int len = -1);

    // возвращает адрес начала блока
	int write_datablock(TStream* block, int start, bool _zipped = false, int len = -1);

	TStream* read_datablock(int start, int offset = 0);

	int get_nextblock(int start);

	bool is_destructed; // признак, что работает деструктор
	bool flushed;       // признак, что происходит сброс
	bool leave_data;    // признак, что не нужно удалять основной поток (data) при уничтожении объекта

  public:
//	bool readonly;
	v8catalog(v8file* f);   // создать каталог из файла
	v8catalog(String name); // создать каталог из физического файла (cf, epf, erf, hbk, cfu)
	v8catalog(String name, bool _zipped); // создать каталог из физического файла (cf, epf, erf, hbk, cfu)
	v8catalog(TStream* stream, bool _zipped, bool leave_stream = false); // создать каталог из потока

	~v8catalog();

	bool IsCatalog();
    bool Is8316();
	v8file* GetFile(const String& FileName);
	v8file* GetFirst();

    // CreateFile в win64 определяется как CreateFileW, пришлось заменить на маленькую букву
	v8file* createFile(const String& FileName, bool _selfzipped = false);
	v8catalog* CreateCatalog(const String& FileName, bool _selfzipped = false);
	void DeleteFile(const String& FileName);
	v8catalog* GetParentCatalog();
	//void Defrag(bool Recursively);
	v8file* GetSelfFile();
	void SaveToDir(String DirName);
	bool isOpen();
	void Flush();
	void HalfClose();
	void HalfOpen(const String& name);
	//void set_leave_data(bool ld);
    void ClearIs8316();
};

#endif


