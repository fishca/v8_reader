// v8_constants.h
// Общие константы формата файлов 1С v8
// Используется в APIcfBase.h и V8File.h (namespace v8unpack)

#ifndef V8_CONSTANTS_H
#define V8_CONSTANTS_H

// Размер страницы по умолчанию
const unsigned int V8_DEFAULT_PAGE_SIZE = 512;

// Сигнатура конца списка (32-бит формат, до 8.3.16)
const unsigned int V8_FF_SIGNATURE = 0x7fffffff;

// Сигнатура конца списка (64-бит формат, 8.3.16+)
const unsigned __int64 V8_FF64_SIGNATURE = 0xffffffffffffffffULL;

// Смещение начала данных в файлах формата 8.3.16+
// (волшебное смещение 0x1359 — происхождение неизвестно)
const int V8_OFFSET_8316 = 0x1359;

#endif // V8_CONSTANTS_H
