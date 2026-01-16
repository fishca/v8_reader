#ifndef GuidsH
#define GuidsH

/* GUID-s всех метаданных 1С
09736b02-9cac-4e3f-b4f7-d3e9576ab948 // Роли
0c89c792-16c3-11d5-b96b-0050bae0a95d // Общие макеты
0fe48980-252d-11d6-a3c7-0050bae0a776 // Общие модули
0fffc09c-8f4c-47cc-b41c-8d5c5a221d79 // http-сервисы
11bdaf85-d5ad-4d91-bb24-aa0eee139052 // Регламентные задания
15794563-ccec-41f6-a83c-ec5f7b9a5bc1 // Общие реквизиты
24c43748-c938-45d0-8d14-01424a72b11e // Параметры сеанса
30d554db-541e-4f62-8970-a1c6dcfeb2bc // Параметры функциональных опций
37f2fa9a-b276-11d4-9435-004095e12fc7 // Подсистемы
39bddf6a-0c3c-452b-921c-d99cfa1c2f1b // Интерфейсы
3e5404af-6ef8-4c73-ad11-91bd2dfac4c8 // Стили
3e7bfcc0-067d-11d6-a3c7-0050bae0a776 // Критерии отбора
46b4cd97-fd13-4eaa-aba2-3bddd7699218 // Хранилища настроек
4e828da6-0f44-4b5b-b1c0-a2b3cfe7bdcc // Подписки на события
58848766-36ea-4076-8800-e91eb49590d7 // Элементы стиля
6e6dc072-b7ac-41e7-8f88-278d25b6da2a // Неизвестный
7dcd43d9-aca5-4926-b549-1842e6a4e8cf // Общие картинки
857c4a91-e5f4-4fac-86ec-787626f1c108 // Планы обмена
8657032e-7740-4e1d-a3ba-5dd6e8afb78f // Web-сервисы
9cd510ce-abfc-11d4-9434-004095e12fc7 // Языки
af547940-3268-434f-a3e7-e47d6d2638c3 // Функциональные опции
c045099e-13b9-4fb6-9d50-fca00202971e // Определяемые типы
cc9df798-7c94-4616-97d2-7aa0b7bc515e // XDTO - пакеты
d26096fb-7a5d-4df9-af63-47d04771fa9b // WS - ссылки
0195e80c-b157-11d4-9435-004095e12fc7 // Константы
061d872a-5787-460e-95ac-ed74ea3a3e84 // Документы
07ee8426-87f1-11d5-b99c-0050bae0a95d // Общие формы
13134201-f60b-11d5-a3c7-0050bae0a776 // Регистры сведений
1c57eabe-7349-44b3-b1de-ebfeab67b47d // Группы комманд
2f1a5187-fb0e-4b05-9489-dc5dd6412348 // Общие команды
36a8e346-9aaa-4af9-bdbd-83be3c177977 // Нумераторы документов
4612bd75-71b7-4a5c-8cc5-2b0b65f9fa0d // Журналы документов
631b75a0-29e2-11d6-a3c7-0050bae0a776 // Отчеты
82a1b659-b220-4d94-a9bd-14d757b95a48 // План видов характеристик
b64d9a40-1642-11d6-a3c7-0050bae0a776 // Регистры накопления
bc587f20-35d9-11d6-a3c7-0050bae0a776 // Последовательность
bf845118-327b-4682-b5c6-285d2a0eb296 // Обработки
cf4abea6-37b2-11d4-940f-008048da11f9 // Справочники
f6a80749-5ad7-400b-8519-39dc5dff2542 // Перечисления
238e7e88-3c5f-48b2-8a3b-81ebbecb20ed // План счетов
30b100d6-b29f-47ac-aec7-cb8ca8a54767 // План видов расчета
2deed9b8-0056-4ffe-a473-c20a6c32a0bc // Регистр бухгалтерии
f2de87a8-64e5-45eb-a22d-b3aedab050e7 // Регистр расчета
fcd3404e-1523-48ce-9bc0-ecdb822684a1 // Бизнес процессы
3e63355c-1378-4953-be9b-1deb5fb6bec5 // Задачи
5274d9fc-9c3a-4a71-8f5e-a0db8ab23de5 // Внешние источники данных

*/

// Метаданные 1С
constexpr auto md_Config                      = "Конфигурация";
constexpr auto md_Common                      = "Общие";
constexpr auto md_AccumulationRegisters       = "Регистры накопления";
constexpr auto md_AccountingRegisters         = "Регистры бухгалтерии";
constexpr auto md_CalculationRegisters        = "Регистры расчета";
constexpr auto md_BusinessProcesses           = "Бизнес-процессы";
constexpr auto md_Catalogs                    = "Справочники";
constexpr auto md_ChartsOfCharacteristicTypes = "Планы видов характеристик";
constexpr auto md_CommandGroups               = "Группы команд";
constexpr auto md_CommonAttributes            = "Общие реквизиты";
constexpr auto md_CommonCommands              = "Общие команды";
constexpr auto md_CommonForms                 = "Общие формы";
constexpr auto md_CommonModules               = "Общие модули";
constexpr auto md_CommonPictures              = "Общие картинки";
constexpr auto md_CommonTemplates             = "Общие макеты";
constexpr auto md_Constants                   = "Константы";
constexpr auto md_DataProcessors              = "Обработки";
constexpr auto md_DefinedTypes                = "Определяемые типы";
constexpr auto md_DocumentJournals            = "Журналы документов";
constexpr auto md_DocumentNumerators          = "Нумераторы";
constexpr auto md_Documents                   = "Документы";
constexpr auto md_Enums                       = "Перечисления";
constexpr auto md_EventSubscriptions          = "Подписки на события";
constexpr auto md_ExchangePlans               = "Планы обмена";
constexpr auto md_ChartOfAccounts             = "Планы счетов";
constexpr auto md_ChartOfCalculationTypes     = "Планы видов расчета";
constexpr auto md_ExternalDataSources         = "Внешние источники данных";
constexpr auto md_FilterCriteria              = "Критерии отбора";
constexpr auto md_FunctionalOptions           = "Функциональные опции";
constexpr auto md_FunctionalOptionsParameters = "Параметры функциональных опций";
constexpr auto md_HTTPServices                = "HTTP-сервисы";
constexpr auto md_InformationRegisters        = "Регистры сведений";
constexpr auto md_Interfaces                  = "Интерфейсы";
constexpr auto md_Languages                   = "Языки";
constexpr auto md_Reports                     = "Отчеты";
constexpr auto md_Roles                       = "Роли";
constexpr auto md_Bots                        = "Боты";
constexpr auto md_ScheduledJobs               = "Регламентные задания";
constexpr auto md_SessionParameters           = "Параметры сеанса";
constexpr auto md_SettingsStorages            = "Хранилища настроек";
constexpr auto md_StyleItems                  = "Элементы стиля";
constexpr auto md_Styles                      = "Стили";
constexpr auto md_Subsystems                  = "Подсистемы";
constexpr auto md_Tasks                       = "Задачи";
constexpr auto md_WebServices                 = "Web-сервисы";
constexpr auto md_WSReferences                = "WS-ссылки";
constexpr auto md_XDTOPackages                = "XDTO-пакеты";
constexpr auto md_IntegrationServices         = "Сервисы интеграции";
constexpr auto md_Sequences                   = "Последовательности";



// GUID-s

constexpr const char* GUID_Subsystems                  = "37f2fa9a-b276-11d4-9435-004095e12fc7";
constexpr const char* GUID_CommonModules               = "0fe48980-252d-11d6-a3c7-0050bae0a776";
constexpr const char* GUID_SessionParameters           = "24c43748-c938-45d0-8d14-01424a72b11e";
constexpr const char* GUID_Roles                       = "09736b02-9cac-4e3f-b4f7-d3e9576ab948";
constexpr const char* GUID_CommonAttributes            = "15794563-ccec-41f6-a83c-ec5f7b9a5bc1";
constexpr const char* GUID_ExchangePlans               = "857c4a91-e5f4-4fac-86ec-787626f1c108";
constexpr const char* GUID_FilterCriteria              = "3e7bfcc0-067d-11d6-a3c7-0050bae0a776";
constexpr const char* GUID_EventSubscriptions          = "4e828da6-0f44-4b5b-b1c0-a2b3cfe7bdcc";
constexpr const char* GUID_ScheduledJobs               = "11bdaf85-d5ad-4d91-bb24-aa0eee139052";
constexpr const char* GUID_FunctionalOptions           = "af547940-3268-434f-a3e7-e47d6d2638c3";
constexpr const char* GUID_FunctionalOptionsParameters = "30d554db-541e-4f62-8970-a1c6dcfeb2bc";
constexpr const char* GUID_DefinedTypes                = "c045099e-13b9-4fb6-9d50-fca00202971e";
constexpr const char* GUID_SettingsStorages            = "46b4cd97-fd13-4eaa-aba2-3bddd7699218";
constexpr const char* GUID_CommonForms                 = "07ee8426-87f1-11d5-b99c-0050bae0a95d";
constexpr const char* GUID_CommonCommands              = "2f1a5187-fb0e-4b05-9489-dc5dd6412348";
constexpr const char* GUID_CommandGroups               = "1c57eabe-7349-44b3-b1de-ebfeab67b47d";
constexpr const char* GUID_Interfaces                  = "39bddf6a-0c3c-452b-921c-d99cfa1c2f1b";
constexpr const char* GUID_CommonTemplates             = "0c89c792-16c3-11d5-b96b-0050bae0a95d";
constexpr const char* GUID_CommonPictures              = "7dcd43d9-aca5-4926-b549-1842e6a4e8cf";
constexpr const char* GUID_XDTOPackages                = "cc9df798-7c94-4616-97d2-7aa0b7bc515e";
constexpr const char* GUID_WebServices                 = "8657032e-7740-4e1d-a3ba-5dd6e8afb78f";
constexpr const char* GUID_HTTPServices                = "0fffc09c-8f4c-47cc-b41c-8d5c5a221d79";
constexpr const char* GUID_WSReferences                = "d26096fb-7a5d-4df9-af63-47d04771fa9b";
constexpr const char* GUID_StyleItems                  = "58848766-36ea-4076-8800-e91eb49590d7";
constexpr const char* GUID_Styles                      = "3e5404af-6ef8-4c73-ad11-91bd2dfac4c8";
constexpr const char* GUID_Languages                   = "9cd510ce-abfc-11d4-9434-004095e12fc7";
constexpr const char* GUID_Catalogs                    = "cf4abea6-37b2-11d4-940f-008048da11f9";
constexpr const char* GUID_Constants                   = "0195e80c-b157-11d4-9435-004095e12fc7";
constexpr const char* GUID_Documents                   = "061d872a-5787-460e-95ac-ed74ea3a3e84";
constexpr const char* GUID_Numerators                  = "36a8e346-9aaa-4af9-bdbd-83be3c177977";
constexpr const char* GUID_Sequences                   = "bc587f20-35d9-11d6-a3c7-0050bae0a776";
constexpr const char* GUID_JournDocuments              = "4612bd75-71b7-4a5c-8cc5-2b0b65f9fa0d";
constexpr const char* GUID_Enums                       = "f6a80749-5ad7-400b-8519-39dc5dff2542";
constexpr const char* GUID_Reports                     = "631b75a0-29e2-11d6-a3c7-0050bae0a776";
constexpr const char* GUID_DataProcessors              = "bf845118-327b-4682-b5c6-285d2a0eb296";
constexpr const char* GUID_ChartOfCharacteristicTypes  = "82a1b659-b220-4d94-a9bd-14d757b95a48";
constexpr const char* GUID_ChartsOfAccounts            = "238e7e88-3c5f-48b2-8a3b-81ebbecb20ed";
constexpr const char* GUID_ChartsOfCalculationTypes    = "30b100d6-b29f-47ac-aec7-cb8ca8a54767";
constexpr const char* GUID_InformationRegisters        = "13134201-f60b-11d5-a3c7-0050bae0a776";
constexpr const char* GUID_AccumulationRegisters       = "b64d9a40-1642-11d6-a3c7-0050bae0a776";
constexpr const char* GUID_AccountingRegisters         = "2deed9b8-0056-4ffe-a473-c20a6c32a0bc";
constexpr const char* GUID_CalculationRegisters        = "f2de87a8-64e5-45eb-a22d-b3aedab050e7";
constexpr const char* GUID_BusinessProcesses           = "fcd3404e-1523-48ce-9bc0-ecdb822684a1";
constexpr const char* GUID_Tasks                       = "3e63355c-1378-4953-be9b-1deb5fb6bec5";
constexpr const char* GUID_ExternalDataSources         = "5274d9fc-9c3a-4a71-8f5e-a0db8ab23de5";

// Макеты Справочника
constexpr const char* GUID_MoxelsCatalogs   = "3daea016-69b7-4ed4-9453-127911372fe6";
//Команды справочника
constexpr const char* GUID_CommandsCatalogs = "4fe87c89-9ad4-43f6-9fdb-9dc83b3879c6";
//Табличные части справочника
constexpr const char* GUID_TabsCatalogs     = "932159f9-95b2-4e76-a8dd-8849fe5c5ded";
//Реквизиты справочника
constexpr const char* GUID_AttCatalogs      = "cf4abea7-37b2-11d4-940f-008048da11f9";
// Формы Справочника
constexpr const char* GUID_FormsCatalogs    = "fdf816d2-1ead-11d5-b975-0050bae0a95d";






//Команды критерия отбора
constexpr const char* GUID_SelCritCommands             = "23fa3b84-220a-40e9-8331-e588bed87f7d";

//Команды ЗадачБП
constexpr const char* GUID_TasksCommands               = "f27c2152-a2c9-4c30-adb1-130f5eb2590f";

//Команды БизнесПРоцессов
constexpr const char* GUID_BPCommands                  = "7a3e533c-f232-40d5-a932-6a311d2480bf";
//Команда Обработки
constexpr const char* GUID_ProcessingCommand           = "45556acb-826a-4f73-898a-6025fc9536e1";
//Команда Регистра сведений
constexpr const char* GUID_InfoRegCommand              = "b44ba719-945c-445c-8aab-1088fa4df16e";

//Команда Регистра бухгалтерии
constexpr const char* GUID_AccRegCommand               = "7162da60-f7fe-4d78-ad5d-e31700f9af18";

//Команда Документа
constexpr const char* GUID_DocCommand                  = "b544fc6a-2ba3-4885-8fb2-cb289fb6d65e";
//Команда ПланаОбмена
constexpr const char* GUID_ExchPlanCommand             = "d5207c64-11d5-4d46-bba2-55b7b07ff4eb";
//Команда Журнала
constexpr const char* GUID_DocJrnlCommand              = "a49a35ce-120a-4c80-8eea-b0618479cd70";
//Команда Плана счетов
constexpr const char* GUID_AccPlnCommand               = "0df30176-6865-4787-9fc8-609eb144174f";
//Команда Регистра накопления
constexpr const char* GUID_RegAcmCommand               = "99f328af-a77f-4572-a2d8-80ed20c81890";
//Команда Бизнес процесса
constexpr const char* GUID_BsnPrcCommand               = "7a3e533c-f232-40d5-a932-6a311d2480bf";


constexpr auto GUID_1  = "5d4125ad-f6e7-4313-be32-f71d0ab60915"; // Булево;Булево
constexpr auto GUID_2  = "aae38c48-a877-411c-a6d3-fbaa1f83c4bd"; // Дата;Дата
constexpr auto GUID_3  = "9b6abf8b-0173-48e5-b0a0-83b21fcf63c5"; // Строка;Строка
constexpr auto GUID_4  = "b0be78f2-0ee6-4d31-a3bb-77dd32ba5bec"; // Число;Число
constexpr auto GUID_5  = "ee8d3e7c-f930-4a76-8aad-4ff9083a6ea6"; // Неопределено;Неопределено
constexpr auto GUID_6  = "af40a278-63bc-478e-91a8-19e0d16b10b5"; // Null;Null
constexpr auto GUID_7  = "5516da10-4560-4225-a10a-f81c0c3226a3"; // ИнформацияОбОшибке;Информация об ошибке
constexpr auto GUID_8  = "d47d59f8-73f0-481c-8b5e-f6384c0a4804"; // Тип;Тип
constexpr auto GUID_9  = "176f8193-b21b-4145-9219-e6f024ad1221"; // WSСсылкиМенеджер;Менеджер WS-ссылок
constexpr auto GUID_10 = "9e67a57e-430d-4bde-ab60-b29899dcaee9"; // БиблиотекаКартинок;БиблиотекаКартинок
constexpr auto GUID_11 = "a8141813-ca33-46d8-8c31-b324200ae13f"; // БиблиотекаМакетовОформленияКомпоновкиДанных;Библиотека макетов оформления компоновки данных
constexpr auto GUID_12 = "67fb917f-e3d1-4851-9818-4e03f1bdbea5"; // ;Макеты оформления компоновки данных
constexpr auto GUID_13 = "d96e5afe-10d1-4362-a680-0a4db1a4f0e5"; // БиблиотекаСтилей;БиблиотекаСтилей
constexpr auto GUID_14 = "a9e49e39-4fbf-4af1-a427-dac0f7a6e4c5"; // БизнесПроцессыМенеджер;Бизнес-процессы менеджер
constexpr auto GUID_15 = "5e58f017-1ea9-421e-b3b8-39b78bcac512"; // ВнешниеОбработкиМенеджер;Внешние обработки менеджер
constexpr auto GUID_16 = "d449c26e-3936-4d81-9873-868da97350ce"; // ВнешниеОтчетыМенеджер;Внешние отчеты менеджер
constexpr auto GUID_17 = "ce6c6a40-b8e9-11d5-a3c1-0050bae0a776"; // КоллекцияЭлементовУправленияИнтерфейсами;Коллекция элементов управления интерфейсами
constexpr auto GUID_18 = "c0f1f863-6f60-4c36-b25b-60f312e52be6"; // Стиль;Стиль
constexpr auto GUID_19 = "c1a952b4-da58-11d5-b9ac-0050bae0a95d"; // ДокументыМенеджер;Документы менеджер
constexpr auto GUID_20 = "b9c04742-eaee-11d5-b9b4-0050bae0a95d"; // ЖурналыДокументовМенеджер;Журналы документов менеджер
constexpr auto GUID_21 = "8eb22556-48a4-4897-8a9f-bded9db57b14"; // ЗадачиМенеджер;Задачи менеджер
constexpr auto GUID_22 = "be5b7fdc-f1c5-4a8b-ab6a-98bc15f3361e"; // РежимРабочейДаты;РежимРабочейДаты
constexpr auto GUID_23 = "9a8c20f5-e455-43e8-97e2-8ee916bc4b9f"; // КонстантыМенеджер;Константы менеджер
constexpr auto GUID_24 = "e41fd1e0-0a8f-11d6-a3c7-0050bae0a776"; // КритерииОтбораМенеджер;Критерии отбора менеджер
constexpr auto GUID_25 = "18a31cc0-159d-11d6-a3c7-0050bae0a776"; // ОбъектМетаданныхКонфигурация;Объект метаданных конфигурация
constexpr auto GUID_26 = "2a641781-de6a-11d5-a3c1-0050bae0a776"; // ОбработкиМенеджер;Обработки менеджер
constexpr auto GUID_27 = "b9754f03-29e9-11d6-a3c7-0050bae0a776"; // ОтчетыМенеджер;Отчеты менеджер
constexpr auto GUID_28 = "3601c7ba-a8f9-4d04-b9e9-0e2f0b06e368"; // ПараметрыСеанса;Параметры сеанса
constexpr auto GUID_29 = "0642d510-657e-4c0c-8a46-5bef8bcd3939"; // ПеречисленияМенеджер;Перечисления менеджер
constexpr auto GUID_30 = "929d3fed-652e-4bff-8ba2-55cfb3b94f71"; // ПланыВидовРасчетаМенеджер;Планы видов расчета менеджер
constexpr auto GUID_31 = "9faf7fdb-2ecb-42b2-827e-9905ead95e62"; // ПланыВидовХарактеристикМенеджер;Планы видов характеристик менеджер
constexpr auto GUID_32 = "9e9b297e-3c4b-40f9-82a7-9e158dbb0704"; // ПланыОбменаМенеджер;Планы обмена менеджер
constexpr auto GUID_33 = "d1c15906-758c-4ffa-8311-fcae59aa63d9"; // ПланыСчетовМенеджер;Планы счетов менеджер
constexpr auto GUID_34 = "a2fc2ce5-7735-4673-924b-bdb98dee818f"; // МенеджерПолнотекстовогоПоиска;Менеджер полнотекстового поиска
constexpr auto GUID_35 = "b0ad5309-becd-4eba-9599-72190e5499f7"; // МенеджерПользователейИнформационнойБазы;Менеджер пользователей
constexpr auto GUID_36 = "075d23e0-3cb5-11d6-a3c7-0050bae0a776"; // ПоследовательностиМенеджер;Последовательности менеджер
constexpr auto GUID_37 = "badb0b27-beca-43c8-91ef-60b86e006221"; // РегистрыБухгалтерииМенеджер;Регистры бухгалтерии менеджер
constexpr auto GUID_38 = "b509ea16-3fe8-46ec-8436-07704912cd04"; // РегистрыНакопленияМенеджер;Регистры накопления менеджер
constexpr auto GUID_39 = "7320f154-a38c-470a-bcb0-19f9c49213d9"; // РегистрыРасчетаМенеджер;Регистры расчета менеджер
constexpr auto GUID_40 = "305cb7b5-e193-4030-aeab-da6f9eae7ccd"; // РегистрыСведенийМенеджер;Регистры сведений менеджер
constexpr auto GUID_41 = "0dd04f14-3afe-4da4-83d7-c45107abddcb"; // МенеджерРегламентныхЗаданий;Менеджер регламентных заданий
constexpr auto GUID_42 = "6c181d1d-45bc-42a8-936f-3a8b422be0c3"; // СериализаторXDTO;Сериализатор XDTO
constexpr auto GUID_43 = "81bcd122-3599-48df-b0d4-19fd42d41d55"; // СправочникиМенеджер;Справочники менеджер
constexpr auto GUID_44 = "20c14bd6-d166-43f9-b1e3-253af05c4fdd"; // ФабрикаXDTO;Фабрика XDTO
constexpr auto GUID_45 = "325e78b8-3f54-4aed-986d-4d73e162519f"; // МенеджерФоновыхЗаданий;Менеджер фоновых заданий
constexpr auto GUID_46 = "ae18ec1e-8dde-420d-83c7-ae73fbe90b6f"; // ПараметрыДоступа;Параметры доступа
constexpr auto GUID_47 = "e199ca70-93cf-46ce-a54b-6edc88c3a296"; // ХранилищеЗначения;Хранилище значения
constexpr auto GUID_48 = "e6f51714-91cb-4dce-94fe-90ae3e3e1ad1"; // Картинка;Картинка
constexpr auto GUID_49 = "fc01b5df-97fe-449b-83d4-218a090e681e"; // УникальныйИдентификатор;Уникальный идентификатор
constexpr auto GUID_50 = "ad6b5cbb-5fc4-4b27-adc6-e63bc8bae012"; // ИзвлечениеТекста;Извлечение текста
constexpr auto GUID_51 = "504207fe-40b8-4a86-ba58-776ed3f372ac"; // СводнаяДиаграмма;Сводная диаграмма
constexpr auto GUID_52 = "4d10ca00-111a-4d43-9c96-92cd773716de"; // Рамка;Рамка
constexpr auto GUID_53 = "4d5a8344-6831-466c-9b90-0982241b03e1"; // ТипСводнойДиаграммы;ТипСводнойДиаграммы
constexpr auto GUID_54 = "f450b723-9221-40c9-8a9c-39627f60d02e"; // ПеречислениеТипСводнойДиаграммы;ПеречислениеТипСводнойДиаграммы
constexpr auto GUID_55 = "7531485a-c04c-4243-8ed3-58ce4f832eaf"; // ОбластьЗаголовкаСводнойДиаграммы;Область заголовка сводной диаграммы
constexpr auto GUID_56 = "9cd510c8-abfc-11d4-9434-004095e12fc7"; // Шрифт;Шрифт
constexpr auto GUID_57 = "296a02c7-b9dc-4855-aefa-3c0b3cc3b83c"; // ОбластьЛегендыСводнойДиаграммы;Область легенды сводной диаграммы
constexpr auto GUID_58 = "b5f1fb9e-9678-430c-88f3-e20b3b897305"; // ОбластьПостроенияСводнойДиаграммы;Область построения сводной диаграммы
constexpr auto GUID_59 = "581b1496-5d4f-41dc-8aad-dbe4edea4440"; // ПолеСводнойДиаграммы;Поле сводной диаграммы
constexpr auto GUID_60 = "65da34f7-d5ab-47cb-879f-76999de01260"; // КоллекцияПолейСводнойДиаграммы;Коллекция полей сводной диаграммы
constexpr auto GUID_61 = "fbce8b98-8a58-4aa1-be5d-2cc283fee0ff"; // ФиксированнаяКоллекция;Фиксированная коллекция
constexpr auto GUID_62 = "ebf766b1-f32c-11d3-9851-008048da1252"; // ТекстовыйДокумент;Текстовый документ
constexpr auto GUID_63 = "47aa67da-7b8f-4981-be70-4792bf72cc5a"; // ПараметрыМакетаТекстовогоДокумента;Параметры макета текстового документа
constexpr auto GUID_64 = "e603103e-a318-4edc-a014-b1c6cf94d49f"; // ТабличныйДокумент;Табличный документ
constexpr auto GUID_65 = "718a30b3-7279-4740-a75c-bb951a087880"; // ОриентацияСтраницы;ОриентацияСтраницы
constexpr auto GUID_66 = "01d0455f-a1fe-4129-9fb6-ad6f32a209c8"; // ПеречислениеОриентацияСтраницы;ПеречислениеОриентацияСтраницы
constexpr auto GUID_67 = "bec13d9a-95c7-4b3d-9228-51b4265565cd"; // КоллекцияОбластейТабличногоДокумента;Коллекция областей табличного документа
constexpr auto GUID_68 = "c8ec9b19-8c9a-4de5-8078-a3e5f0df8ef3"; // ОбластьЯчеекТабличногоДокумента;Область ячеек табличного документа
constexpr auto GUID_69 = "52616226-8ccf-4d1d-a3da-827eeb4f9cf9"; // ВертикальноеПоложение;ВертикальноеПоложение
constexpr auto GUID_70 = "968ece7f-2b50-4240-a040-033642e642a5"; // ПеречислениеВертикальноеПоложение;ПеречислениеВертикальноеПоложение
constexpr auto GUID_71 = "43f9c095-40e8-441a-8fad-20a45798c71b"; // ГоризонтальноеПоложение;ГоризонтальноеПоложение
constexpr auto GUID_72 = "bdc13cbc-c4e9-44de-9b4b-b3d80f07a96d"; // ПеречислениеГоризонтальноеПоложение;ПеречислениеГоризонтальноеПоложение
constexpr auto GUID_73 = "d334cf31-73c5-4f66-8ace-a77555d231c3"; // КоллекцияРисунковТабличногоДокумента;Коллекция рисунков табличного документа
constexpr auto GUID_74 = "46dc7489-c87e-4ddc-b150-61716da2eee0"; // РисунокТабличногоДокумента;Рисунок табличного документа
constexpr auto GUID_75 = "20da8ba7-aab3-445e-ae6b-6b206014abc9"; // Линия;Линия
constexpr auto GUID_76 = "11e6aa40-663f-11d5-a3be-0050bae0a776"; // РазмерКартинки;РазмерКартинки
constexpr auto GUID_77 = "11e6aa42-663f-11d5-a3be-0050bae0a776"; // ПеречислениеРазмерКартинки;ПеречислениеРазмерКартинки
constexpr auto GUID_78 = "0f3a6ed4-1fb4-4daf-9cfc-859b36546e57"; // ПараметрыМакетаТабличногоДокумента;Параметры макета табличного документа
constexpr auto GUID_79 = "b83c1adb-0f13-4ba1-935d-ae66735ded2c"; // КолонтитулТабличногоДокумента;Колонтитул табличного документа
constexpr auto GUID_80 = "6c8a5575-619d-4e50-abff-a217c17c283a"; // СводнаяТаблица;Сводная таблица
constexpr auto GUID_81 = "bb26af04-8886-430c-89e6-319b0af4bb9b"; // КоллекцияПолейСводнойТаблицы;Коллекция полей сводной таблицы
constexpr auto GUID_82 = "5f794beb-d5ae-4229-9561-93e0cdeaad09"; // ПолеСводнойТаблицы;Поле сводной таблицы
constexpr auto GUID_83 = "457f17bb-693b-4fad-8b15-d4af1ea91afa"; // КоллекцияВстроенныхТаблиц;Коллекция встроенных таблиц
constexpr auto GUID_84 = "53d222dc-bf24-4ebd-888a-c83be182d660"; // ВыделенныеОбластиТабличногоДокумента;Выделенные области табличного документа
constexpr auto GUID_85 = "3543ef08-3316-4f7e-9447-0cd0a1cbf1d5"; // Диаграмма;Диаграмма
constexpr auto GUID_86 = "def9480a-6191-4d87-87db-05525158c3ad"; // АвтоРаздвижениеСерий;АвтоРаздвижениеСерий
constexpr auto GUID_87 = "a3186891-060e-415c-8167-9d2732f4bd87"; // ПеречислениеАвтоРаздвижениеСерий;ПеречислениеАвтоРаздвижениеСерий
constexpr auto GUID_88 = "8bf2e9c3-9450-4a62-94ee-cf46834cc4f6"; // МаксимумСерий;МаксимумСерий
constexpr auto GUID_89 = "7b19d6ac-0eee-4b6a-8e59-787453d5a3bd"; // ПеречислениеМаксимумСерий;ПеречислениеМаксимумСерий
constexpr auto GUID_90 = "57f7dec3-6caa-11d5-a3be-0050bae0a776"; // Ориентация;Ориентация
constexpr auto GUID_91 = "57f7dec5-6caa-11d5-a3be-0050bae0a776"; // ПеречислениеОриентация;ПеречислениеОриентация
constexpr auto GUID_92 = "00fd5a7e-6a3b-410f-be93-7244b54d64af"; // ОтображениеЗначенияИзмерительнойДиаграммы;ОтображениеЗначенияИзмерительнойДиаграммы
constexpr auto GUID_93 = "b9f83fed-dfc9-459c-8bae-484855145ef8"; // ПеречислениеОтображениеЗначенияИзмерительнойДиаграммы;ПеречислениеОтображениеЗначенияИзмерительнойДиаграммы
constexpr auto GUID_94 = "dc5600f5-cf7e-4ff7-a274-508250c61af0"; // ПоложениеПодписейШкалыЗначенийИзмерительнойДиаграммы;ПоложениеПодписейШкалыЗначенийИзмерительнойДиаграммы
constexpr auto GUID_95 = "313ea1d1-8f3a-481c-b531-8ca97f33af04"; // ПеречислениеПоложениеПодписейШкалыЗначенийИзмерительнойДиаграммы;ПеречислениеПоложениеПодписейШкалыЗначенийИзмерительнойДиаграммы
constexpr auto GUID_96 = "13c2d22c-8fbe-40a2-88b1-94e32ba39d2d"; // ПолосыИзмерительнойДиаграммы;Полосы измерительной диаграммы
constexpr auto GUID_97 = "5878e725-50de-4998-b589-3c56ea63e735"; // ТипДиаграммы;ТипДиаграммы
constexpr auto GUID_98 = "8300ea5a-21df-4e20-901c-b221227bccaa"; // ПеречислениеТипДиаграммы;ПеречислениеТипДиаграммы
constexpr auto GUID_99 = "c6128b1c-2756-4937-b96f-3b28abdac38a"; // ЗначениеДиаграммы;Значение диаграммы
constexpr auto GUID_100 = "09942b0c-e225-4a7b-9ec7-dd6ba615d326"; // СерииДиаграммы;Серии диаграммы
constexpr auto GUID_101 = "598b75c7-9798-4b06-9b3d-3302831cbabe"; // СерияДиаграммы;Серия диаграммы
constexpr auto GUID_102 = "c0e8dac6-dd33-4fb4-aaa3-d743cd9448eb"; // Индикатор;Индикатор
constexpr auto GUID_103 = "9cd510c7-abfc-11d4-9434-004095e12fc7"; // Цвет;Цвет
constexpr auto GUID_104 = "cec04421-b954-47fa-823f-66c5c726eb8e"; // ТочкиДиаграммы;Точки диаграммы
constexpr auto GUID_105 = "55ee0cfb-f72d-4c95-aa98-6af595c12296"; // ТочкаДиаграммы;Точка диаграммы
constexpr auto GUID_106 = "8812221c-5985-4991-8803-e879f80abd49"; // ОбластьЗаголовкаДиаграммы;Область заголовка
constexpr auto GUID_107 = "f0c46547-752d-4a17-b48b-82f906098b25"; // ОбластьЛегендыДиаграммы;Область легенды
constexpr auto GUID_108 = "2f329321-654b-4fb8-af0f-50812a892224"; // ОбластьПостроенияДиаграммы;Область построения
constexpr auto GUID_109 = "5cdaa773-d36b-4d8b-82f1-7022c509a6e0"; // ТипШкалыРадарнойДиаграммы;ТипШкалыРадарнойДиаграммы
constexpr auto GUID_110 = "fa5f69c1-5795-42ae-bdc6-b2ddccd12175"; // ПеречислениеТипШкалыРадарнойДиаграммы;ПеречислениеТипШкалыРадарнойДиаграммы
constexpr auto GUID_111 = "f22a1ea4-6bdf-4ef2-a532-f19825c99315"; // ПолосаИзмерительнойДиаграммы;Полоса измерительной диаграммы
constexpr auto GUID_112 = "3a6e63bf-16aa-42eb-b48c-2fff9670ad2f"; // ДиаграммаГанта;Диаграмма Ганта
constexpr auto GUID_113 = "72e6a286-bfb5-4d77-9555-226839b9aa4e"; // ИнтервалДиаграммыГанта;Интервал диаграммы Ганта
constexpr auto GUID_114 = "eb1e3264-6843-4f9a-b4a3-76574bb0d36f"; // ЗначениеДиаграммыГанта;Значение диаграммы Ганта
constexpr auto GUID_115 = "8150d8ee-8586-4051-8036-e64108281ff6"; // ЭлементыШкалыВремени;Коллекция элементов шкалы времени
constexpr auto GUID_116 = "d04d37a0-a61b-4dbd-8f9f-00296239bdc2"; // ЭлементШкалыВремени;Элемент шкалы времени
constexpr auto GUID_117 = "3dec908e-f464-4b1a-b823-aed4a00759eb"; // ШкалаВремени;Шкала времени
constexpr auto GUID_118 = "b78d2afa-23bc-4ec1-8672-4f04249dfcce"; // ТочкиДиаграммыГанта;Точки диаграммы Ганта
constexpr auto GUID_119 = "7544ce6a-e8a5-4a54-8c95-3e0116a72f9e"; // ТочкаДиаграммыГанта;Точка диаграммы Ганта
constexpr auto GUID_120 = "d654a134-f72b-4a53-ba5b-d171ad0685af"; // СерииДиаграммыГанта;Серии диаграммы Ганта
constexpr auto GUID_121 = "db1cebc2-dfe7-4891-a9f3-1f7f926dcdf1"; // СерияДиаграммыГанта;Серия диаграммы Ганта
constexpr auto GUID_122 = "b92b22d7-68b3-4459-ad1a-a92fbf7b72d9"; // ОбластьЗаголовкаДиаграммыГанта;Область заголовка диаграммы Ганта
constexpr auto GUID_123 = "58283eb2-f39c-4f57-ab1a-cc0c406cbd67"; // ОбластьЛегендыДиаграммыГанта;Область легенды диаграммы Ганта
constexpr auto GUID_124 = "2f452997-e1f2-4239-a54f-2392c1ceb9bd"; // ОбластьПостроенияДиаграммыГанта;Область построения диаграммы Ганта
constexpr auto GUID_125 = "0b765d17-6056-42eb-8977-c2122409e04a"; // ИнтервалФонаДиаграммыГанта;Интервал фона диаграммы Ганта
constexpr auto GUID_126 = "4982040b-f34c-44fb-94ea-7029467a20a4"; // ИнтервалыФонаДиаграммыГанта;Интервалы фона диаграммы Ганта
constexpr auto GUID_127 = "4dd00a7b-6826-4648-9716-0800140af6a4"; // МеткаЭлементаШкалыВремени;Метка элемента шкалы времени
constexpr auto GUID_128 = "e84db715-28ce-4517-addb-548b05b389b2"; // МеткиЭлементаШкалыВремени;Метки элемента шкалы времени
constexpr auto GUID_129 = "46e0eb98-0c5f-459b-becd-2175dc18461b"; // СвязьДиаграммыГанта;Связь диаграммы Ганта
constexpr auto GUID_130 = "2957f638-fc52-4bbb-9bd5-614550730ca6"; // Дендрограмма;Дендрограмма
constexpr auto GUID_131 = "a9303e49-1431-4388-a51d-28dc006f67be"; // СвязиДендрограммы;Связи дендрограммы
constexpr auto GUID_132 = "51b38d06-6e45-47c5-94bb-190a73639fd0"; // СвязьДендрограммы;Связь дендрограммы
constexpr auto GUID_133 = "caf28362-f918-4c57-a7cd-fae8dc7d96c7"; // ЭлементыДендрограммы;Элементы дендрограммы
constexpr auto GUID_134 = "49ca6cc1-c43c-43bf-9e91-d5252056fa96"; // ЭлементДендрограммы;Элемент дендрограммы
constexpr auto GUID_135 = "a21ed133-9794-4907-bd20-175db5c66478"; // ОбластьЗаголовкаДендрограммы;Область заголовка дендрограммы
constexpr auto GUID_136 = "42783de2-d079-4867-9119-9eb91050cc3a"; // ОбластьПостроенияДендрограммы;Область построения дендрограммы
constexpr auto GUID_137 = "4af83795-fc2a-48cd-9bea-ce665789a62c"; // ГрафическаяСхема;Графическая схема
constexpr auto GUID_138 = "87ed61fe-9809-4888-9630-e098411a2c48"; // РежимРазмещенияНаСтранице;РежимРазмещенияНаСтранице
constexpr auto GUID_139 = "87ed61fe-9809-4888-9630-e098411a2c4a"; // ПеречислениеРежимРазмещенияНаСтранице;ПеречислениеРежимРазмещенияНаСтранице
constexpr auto GUID_140 = "d1e10048-eb2a-4d76-b466-acbdd6d1ab1a"; // ЭлементыГрафическойСхемы;Элементы графической схемы
constexpr auto GUID_141 = "f430c3fd-8653-4136-82d9-2900bd8cd210"; // ЭлементГрафическойСхемыСоединительнаяЛиния;Элемент графической схемы Соединительная линия
constexpr auto GUID_142 = "ac2dbe75-a25f-46fc-9a5e-527aba4df1b3"; // ЭлементГрафическойСхемыДекоративнаяЛиния;Элемент графической схемы Декоративная линия
constexpr auto GUID_143 = "6afa4f54-c289-4428-9ac0-7bbf72db601a"; // ЭлементГрафическойСхемыДекорация;Элемент графической схемы Декорация
constexpr auto GUID_144 = "1367f918-69db-4def-9da0-1c04e08d8832"; // ЭлементГрафическойСхемыДействие;Элемент графической схемы Действие
constexpr auto GUID_145 = "2912d46a-7949-4c11-a649-bb5082d1de84"; // ЭлементГрафическойСхемыРазделение;Элемент графической схемы Разделение
constexpr auto GUID_146 = "ce008b74-7167-4956-bb69-91023e93e358"; // ЭлементГрафическойСхемыУсловие;Элемент графической схемы Условие
constexpr auto GUID_147 = "a1592f92-9ea1-4b6f-b7d4-9a5a5f9117f2"; // ЭлементГрафическойСхемыЗавершение;Элемент графической схемы Завершение
constexpr auto GUID_148 = "f9a80f9d-32ad-4f4e-8a3e-58c24a50a493"; // ЭлементГрафическойСхемыСтарт;Элемент графической схемы Старт
constexpr auto GUID_149 = "8e9c2040-d786-457c-96eb-b4a8777d30dd"; // ЭлементГрафическойСхемыСлияние;Элемент графической схемы Слияние
constexpr auto GUID_150 = "62b4b2be-5904-4d7e-9c0f-332455f5834a"; // ЭлементГрафическойСхемыВложенныйБизнесПроцесс;Элемент графической схемы Вложенный бизнес-процесс
constexpr auto GUID_151 = "190961c5-9e0b-4d17-af3d-5db360483015"; // ЭлементГрафическойСхемыОбработка;Элемент графической схемы Обработка
constexpr auto GUID_152 = "eada2137-f888-4478-94f6-d60acde50811"; // ЭлементГрафическойСхемыВыборВарианта;Элемент графической схемы Выбор варианта
constexpr auto GUID_153 = "778e4f38-f499-45e8-a80d-11412370a9ab"; // ВариантыЭлементаГрафическойСхемыВыборВарианта;Элементы выбора
constexpr auto GUID_154 = "4e4d78a8-766e-42b1-b4c4-5ef2a5e26b26"; // ВариантЭлементаГрафическойСхемыВыборВарианта;Элемент выбора
constexpr auto GUID_155 = "95de81b0-81c3-4936-9dbb-6400e5c90378"; // ГеографическаяСхема;Поле географической схемы
constexpr auto GUID_156 = "aaa57e7c-8b14-4a27-8c1f-289cb8f55200"; // ПрямоугольникГеографическойСхемы;Ограничивающий прямоугольник объекта
constexpr auto GUID_157 = "1e4fa0e8-bce5-48ed-be33-fba9244d25b4"; // СлоиГеографическойСхемы;Коллекция слоев географической схемы
constexpr auto GUID_158 = "125d3ac5-7ed4-4deb-adfe-f8814796197b"; // СлойГеографическойСхемы;Слой географической схемы
constexpr auto GUID_159 = "315cbf98-a652-41bb-ab70-80f7eddaff7e"; // СерииСлояГеографическойСхемы;Коллекция серий слоя географической схемы
constexpr auto GUID_160 = "7aaa0404-3ac1-42d1-ad74-5cdb8163cda0"; // СерияДанныхСлояГеографическойСхемы;Серия слоя географической схемы
constexpr auto GUID_161 = "3717c72c-1ad4-4f4b-9b0b-779d7031cbee"; // ЗначениеСерииСлояГеографическойСхемы;Значение серии слоя географической схемы
constexpr auto GUID_162 = "d9af0419-3981-4755-87af-da24e40d1ad0"; // ОбъектыСлояГеографическойСхемы;Коллекция географической схемы
constexpr auto GUID_163 = "70ee4d05-294a-4fbd-b049-3bdbc4c05025"; // ТочечныйОбъектГеографическойСхемы;Точечный объект географической схемы
constexpr auto GUID_164 = "15360843-892a-4ad6-8087-34656202f375"; // МноготочечныйОбъектГеографическойСхемы;Многоточечный объект географической схемы
constexpr auto GUID_165 = "59985b9d-896a-4e94-82ca-0256ff82a688"; // ТочкиМноготочечногоОбъектаГеографическойСхемы;Коллекция географических координат
constexpr auto GUID_166 = "aae653bc-3cb3-4062-9af1-669314197fdd"; // ПолилинейныйОбъектГеографическойСхемы;Линейный объект географической схемы
constexpr auto GUID_167 = "6d2ced3f-ed20-4675-a9fc-922201b0a234"; // СегментПолилинейногоОбъектаГеографическойСхемы;Сегмент полилинейного объекта географической схемы
constexpr auto GUID_168 = "d6974e30-b24e-4cb5-9d67-07ece2f5fd25"; // ПолигональныйОбъектГеографическойСхемы;Полигональный объект географической схемы
constexpr auto GUID_169 = "9ebdd88c-a664-4b87-8f72-4a1b04204743"; // КонтурыПолигональногоОбъектаГеографическойСхемы;Коллекция контуров полигона географической схемы
constexpr auto GUID_170 = "ff03aedc-2b8f-4bcc-a29d-a498921d9569"; // КонтурПолигональногоОбъектаГеографическойСхемы;Контур полигонального объекта географической схемы
constexpr auto GUID_171 = "cb28ae7c-538b-48fb-ae6e-e5a8f6c2fe1e"; // КоординатыГеографическойСхемы;Географические координаты
constexpr auto GUID_172 = "eef57b26-1f7d-49b6-a8fb-e2dc296f9bb2"; // ОбластьЗаголовкаГеографическойСхемы;Область заголовка географической схемы
constexpr auto GUID_173 = "b8b1dd85-73df-4627-9c39-1143e7ab95ac"; // ОбластьЛегендыГеографическойСхемы;Область легенды географической схемы
constexpr auto GUID_174 = "0fb6deed-bba8-417a-b816-0b99251fc0d2"; // ЭлементыЛегендыГеографическойСхемы;Коллекция географических координат
constexpr auto GUID_175 = "1b2c3956-b386-4a17-94ec-8ba029ab9ccd"; // ЭлементЛегендыГеографическойСхемы;Элемент легенды географической схемы
constexpr auto GUID_176 = "5f697f26-f1f6-42ce-be40-0e3652612f1d"; // ОбластьПостроенияГеографическойСхемы;Область построения географической схемы
constexpr auto GUID_177 = "66cc719b-f493-4a0e-ac89-bbe5b3f5523e"; // РежимУправленияБлокировкойДанных;РежимУправленияБлокировкойДанных
constexpr auto GUID_178 = "0d1a1857-cf1b-417a-ae68-b863d1779ccd"; // ПеречислениеРежимУправленияБлокировкойДанных;ПеречислениеРежимУправленияБлокировкойДанных
constexpr auto GUID_179 = "1bb474f0-dde3-4be4-8e34-284adcc5f648"; // КоллекцияОбъектовМетаданных;Коллекция объектов метаданных
constexpr auto GUID_180 = "9fb58eea-17f2-4200-b105-b288d62f4303"; // ОбъектМетаданных;Объект метаданных
constexpr auto GUID_181 = "8c88b480-1573-11d6-a3c7-0050bae0a776"; // ПеречислимыеСвойстваОбъектовМетаданных;Перечислимые свойства объектов метаданных
constexpr auto GUID_182 = "1d7c3654-d0be-4130-92d2-c6102636310b"; // КоллекцияЗначенийСвойстваОбъектаМетаданных;Коллекция значений свойства объекта метаданных
constexpr auto GUID_183 = "9cf0ffae-0c41-4439-bc4f-adb6e245d554"; // СоставПланаОбмена;Состав плана обмена
constexpr auto GUID_184 = "f0e9bbe3-26c5-4409-af0b-5c3a6ab6634c"; // ЭлементСоставаПланаОбмена;Элемент состава плана обмена
constexpr auto GUID_185 = "5c83cba4-7a20-4102-a5be-add0ee74f6a1"; // Форма;Форма
constexpr auto GUID_186 = "3d5a3634-47c2-49f2-8ab0-e108a0600fba"; // ТипЗначенияXDTO;Тип значения XDTO
constexpr auto GUID_187 = "791b9fb3-ace5-42f5-b3da-2402ef6e3ad5"; // Файл;Файл
constexpr auto GUID_188 = "f2ad1437-e339-4f74-8c0c-e96d64058650"; // ДиалогВыбораФайла;Диалог выбора файла
constexpr auto GUID_189 = "21cbc846-ff7e-4f2e-9ed8-bbb95fb9cc60"; // СравнениеФайлов;Сравнение файлов
constexpr auto GUID_190 = "6794717c-1d51-4a70-998b-190db9bdc84d"; // XBase;XBase
constexpr auto GUID_191 = "cd132275-98d3-4a45-8d79-631b68fbbabd"; // КоллекцияПолейXBase;Коллекция полей XBase
constexpr auto GUID_192 = "6a112128-071e-4f43-b0b3-bcead70fc5b2"; // ПолеXBase;Поле XBase
constexpr auto GUID_193 = "8e5ac852-b2f6-48bd-b31e-465c8687a030"; // КоллекцияИндексовXBase;Коллекция индексов XBase
constexpr auto GUID_194 = "952c6b50-97e8-4a0d-874e-99f30545885c"; // ИндексXBase;Индекс XBase
constexpr auto GUID_195 = "570d1795-d3e2-4aa2-9195-dbfbf456e161"; // КлючXBase;Ключ XBase
constexpr auto GUID_196 = "f5c65050-3bbb-11d5-b988-0050bae0a95d"; // ОписаниеТипов;Описание типов
constexpr auto GUID_197 = "e73e1337-53df-4b30-a78c-ee1e8cf30fc0"; // КвалификаторыДаты;Квалификаторы даты
constexpr auto GUID_198 = "a5e1773c-a947-455a-a2f7-c51736d3f2de"; // КвалификаторыСтроки;Квалификаторы строки
constexpr auto GUID_199 = "f6f6ce00-392c-49ed-8c6e-4e0295fd4051"; // КвалификаторыЧисла;Квалификаторы числа
constexpr auto GUID_200 = "9c4a8801-ff83-40d7-96d7-cc2b85430fbe"; // ДопустимыйЗнак;ДопустимыйЗнак
constexpr auto GUID_201 = "eb851bfe-cc2a-4d16-84a4-e480da76672d"; // ПеречислениеДопустимыйЗнак;ПеречислениеДопустимыйЗнак
constexpr auto GUID_202 = "3e4a7ff2-82a0-40ee-9000-3e83a3191b71"; // ДопустимаяДлина;ДопустимаяДлина
constexpr auto GUID_203 = "2f7878c0-bc8a-4820-a3b9-6bf1111ae5b0"; // ПеречислениеДопустимаяДлина;ПеречислениеДопустимаяДлина
constexpr auto GUID_204 = "8089abb5-ff39-4414-8252-c0dcef1c3d6b"; // ЧастиДаты;ЧастиДаты
constexpr auto GUID_205 = "83f71799-efb3-4984-a19b-6ed4f3cbc691"; // ПеречислениеЧастиДаты;ПеречислениеЧастиДаты
constexpr auto GUID_206 = "87126200-3e98-44e0-b931-ccb1d7edc497"; // ДвоичныеДанные;Двоичные данные
constexpr auto GUID_207 = "6e289486-e766-49bc-a126-e179035b099d"; // ОболочкаActiveDocument;Оболочка Active Document
constexpr auto GUID_208 = "0387f3a2-7df5-4804-948b-4580a51e4a15"; // СтандартнаяДатаНачала;Стандартная дата начала
constexpr auto GUID_209 = "2319dcf1-f4ee-438d-b16f-6a145d6b9422"; // COMОбъект;COM Объект
constexpr auto GUID_210 = "2fdc88ec-7c9b-43cd-8ba5-873f043bdd88"; // СтандартныйПериод;Стандартный период
constexpr auto GUID_211 = "ca6ad9a7-8a55-4158-8815-a386260dfcb2"; // СжатиеДанных;Сжатие данных
constexpr auto GUID_212 = "0471c2d2-3b10-4d98-af60-35148d1d5ac2"; // ЧтениеXML;Чтение XML
constexpr auto GUID_213 = "8c1313e9-45b9-46ec-8970-46b5bcb47aea"; // ЗаписьXML;Запись XML
constexpr auto GUID_214 = "79bd225b-7b34-43aa-9562-c26e6dc4f69b"; // КаноническаяЗаписьXML;Каноническая Запись XML
constexpr auto GUID_215 = "1d717b0e-8ed7-4c4f-94eb-cdd59aa7e3eb"; // ПреобразованиеXSL;Преобразование XSL
constexpr auto GUID_216 = "7fe288e6-6e4e-46f2-bf88-a6ceb077d9f3"; // ТипДанныхXML;Тип данных XML
constexpr auto GUID_217 = "c80652eb-3882-4868-aaa6-ecd33fdcb8a9"; // КаноническийDOM;Каноническая Запись Узла DOM
constexpr auto GUID_218 = "3330818a-d0f6-466d-a8a1-75e98516f972"; // РасширенноеИмяXML;Расширенное имя XML
constexpr auto GUID_219 = "53683415-21f5-4131-a22a-9af781eff60a"; // СписокРасширенныхИменXML;Список расширенных имен XML
constexpr auto GUID_220 = "e582b7e6-2954-4b80-af27-690745c61ef1"; // КонтекстПространствИменXML;Контекст пространств имен XML
constexpr auto GUID_221 = "316cdeaa-82eb-4278-8105-17a0ff8a4056"; // ПараметрыЧтенияXML;Параметры чтения XML
constexpr auto GUID_222 = "5f38cd14-ad1a-4840-a7df-82a359c5f724"; // ПараметрыЗаписиXML;Параметры записи XML
constexpr auto GUID_223 = "9290e28f-4b59-46d8-980c-aa6e532ecd5a"; // СписокУзловDOM;Список узлов DOM
constexpr auto GUID_224 = "82c39f29-ed1e-4c6e-9a18-1d600d55ebdd"; // СписокЭлементовDOM;Список элементов DOM
constexpr auto GUID_225 = "3b695a89-2595-4918-a1a2-e3a799895041"; // КоллекцияАтрибутовDOM;Коллекция атрибутов DOM
constexpr auto GUID_226 = "de7ff04f-9b1c-4cb9-917c-0b65d20ccd80"; // КоллекцияНотацийDOM;Коллекция нотаций DOM
constexpr auto GUID_227 = "a04c6484-bacf-4ce6-92c0-62431eeaf5af"; // КоллекцияСущностейDOM;Коллекция сущностей DOM
constexpr auto GUID_228 = "2a7a2813-4216-40d1-b7c2-db11dda39f4a"; // АтрибутDOM;Атрибут DOM
constexpr auto GUID_229 = "4c40a072-cefe-4cf5-be87-632c5f8045c7"; // ДокументDOM;Документ  DOM
constexpr auto GUID_230 = "4e7570f2-b1d9-437e-b3bb-15133ad88b23"; // ЭлементDOM;Элемент DOM
constexpr auto GUID_231 = "fffb6450-74d4-4ae0-bfec-c856daab4be6"; // ОпределениеТипаДокументаDOM;Определение типа документа DOM
constexpr auto GUID_232 = "c01c413c-147c-4ba3-b118-0125ec99b088"; // НотацияDOM;Нотация DOM
constexpr auto GUID_233 = "45ce4316-434b-4562-846c-be20085234a3"; // СущностьDOM;Сущность
constexpr auto GUID_234 = "ccce8676-f8f3-43b0-ba40-d0f031a0cb9e"; // КонфигурацияДокументаDOM;Конфигурация документа DOM
constexpr auto GUID_235 = "4382221e-1000-4c86-b8e7-74175b3c4487"; // СписокСтрокDOM;Список строк DOM
constexpr auto GUID_236 = "911e4df0-b379-40f9-9352-d498e867227d"; // ФрагментДокументаDOM;Фрагмент документа DOM
constexpr auto GUID_237 = "71ddf5ed-93fc-47e9-87cb-84c132955b60"; // ТекстDOM;Текст DOM
constexpr auto GUID_238 = "94271e20-7e77-4506-b383-d0049af21cd4"; // КомментарийDOM;Комментарий  DOM
constexpr auto GUID_239 = "71832e09-6dc5-4b49-8682-dd2250267e65"; // СекцияCDATADOM;Секция CDATA DOM
constexpr auto GUID_240 = "c55e804a-9b52-47a9-93cc-dfc91a065f53"; // ИнструкцияОбработкиDOM;Инструкция обработки DOM
constexpr auto GUID_241 = "6d308130-9b91-4f25-8819-9e522d68088d"; // СсылкаНаСущностьDOM;Ссылка на сущность DOM
constexpr auto GUID_242 = "17bd75a2-1b6c-4dd5-818b-14ddb8898de3"; // ИтераторУзловDOM;Итератор узлов DOM
constexpr auto GUID_243 = "6e7d8d2d-6eb9-4082-8499-d094ac4a4e8b"; // ФильтрУзловDOM;Параметры итератора DOM
constexpr auto GUID_244 = "c6b7f807-c983-4b4e-a4ee-f331b5356f16"; // ОбходДереваDOM;Обход дерева DOM
constexpr auto GUID_245 = "ee59833c-e0b9-47ec-b09d-69550b6e792b"; // ВыражениеXPath;Выражение DOM XPath
constexpr auto GUID_246 = "f9d861fd-3b49-45db-9c82-e4698412d6e9"; // РазыменовательПространствИменDOM;Разыменователь пространств имен DOM XPath
constexpr auto GUID_247 = "a71c19fb-3b0f-49a7-a346-d3a00b2541c5"; // РезультатXPath;Результат DOM XPath
constexpr auto GUID_248 = "88c9f564-bdac-4d7d-9973-3b51f54c64c0"; // ПространствоИменXPath;Пространство имен XPath DOM
constexpr auto GUID_249 = "b7d8d036-cbd4-4241-8bc0-6e95b0a36f30"; // КонфигурацияПостроителяDOM;Конфигурация построителя DOM
constexpr auto GUID_250 = "d975ca53-35b3-42ef-bcbc-cba466169e25"; // ПостроительDOM;Построитель DOM
constexpr auto GUID_251 = "2ef5c308-22a0-4732-8b0c-5f826769ef03"; // КонфигурацияЗаписиDOM;Конфигурация записи DOM
constexpr auto GUID_252 = "9feb59a6-bf46-4216-a2f7-c51a6cc834ed"; // ЗаписьDOM;Запись DOM
constexpr auto GUID_253 = "62ac035f-52e3-424a-b14b-47786ed71469"; // ЧтениеУзловDOM;Чтение узлов DOM
constexpr auto GUID_254 = "4d466f72-d510-475d-aa4a-f9877d36ac6e"; // ЗаписьУзловDOM;Запись узлов DOM
constexpr auto GUID_255 = "48497e83-d59f-4ae7-93c1-752a5fec0a8f"; // ОбъединениеНедопустимыхПодстановкиXS;Объединение видов запрета подстановки XML Schema
constexpr auto GUID_256 = "b2a73fd7-c12d-45b1-a68a-6986fff737b3"; // ОбъединениеИсключенийГруппПодстановкиXS;Объединение исключений групп подстановки XML Schema
constexpr auto GUID_257 = "d5f76461-d865-4437-8745-96b618a84b05"; // ОбъединениеЗавершенностиПростогоТипаXS;Объединение завершения простого типа XML Schema
constexpr auto GUID_258 = "6f2f6d39-ad04-407d-81fd-adf4b65712a1"; // ОбъединениеЗавершенностиСоставногоТипаXS;Объединение завершения составного типа XML Schema
constexpr auto GUID_259 = "f481e1ac-7289-4e7a-b64c-9117f394e849"; // ОбъединениеЗавершенностиСхемыXS;Объединение завершения схемы XML Schema
constexpr auto GUID_260 = "f80b00f5-9f2d-48d6-bfae-f59ef84e505a"; // ОбъединениеЗапрещенныхПодстановокXS;Объединение запрещенных подстановок XML Schema
constexpr auto GUID_261 = "413d3bb0-864c-46db-9851-d0a866d2a839"; // ФиксированныйСписокКомпонентXS;Фиксированный список компонент XML Schema
constexpr auto GUID_262 = "103dfe35-900f-4e25-8f81-002b8ee4e040"; // СписокКомпонентXS;Список компонент XML Schema
constexpr auto GUID_263 = "32847fe4-8cb8-45b9-948d-5ba75f7274b9"; // АннотацияXS;Аннотация XML Schema
constexpr auto GUID_264 = "69150ff1-0da1-44ad-8137-9e7394d15591"; // ИнформацияДляПриложенияXS;Информация для приложения XML Schema
constexpr auto GUID_265 = "36bf42b2-3107-44cb-8acc-987c97b05cbd"; // ДокументацияXS;Документация XML Schema
constexpr auto GUID_266 = "74865931-2f20-47be-a794-5d675ec915de"; // КоллекцияИменованныхКомпонентXS;Коллекция именованных компонент XML Schema
constexpr auto GUID_267 = "64eaaac1-1002-43ab-a54a-97333e8f192a"; // ФасетОбщегоКоличестваРазрядовXS;Фасет общего количества разрядов значения XML Schema
constexpr auto GUID_268 = "c1aa2aaf-dfc8-49ba-8509-c5ea11d2c4de"; // ФасетКоличестваРазрядовДробнойЧастиXS;Фасет количества разрядов дробной части значения XML Schema
constexpr auto GUID_269 = "0b3a636c-8bdb-46ab-8a0c-9c92e294fa9c"; // ФасетПеречисленияXS;Фасет перечисления значения XML Schema
constexpr auto GUID_270 = "7fd29799-15df-4265-93cf-ddb6d02fc33c"; // ФасетДлиныXS;Фасет длины значения XML Schema
constexpr auto GUID_271 = "03b4874f-3feb-4306-adda-e098c660715d"; // ФасетМинимальнойДлиныXS;Фасет минимальной длины значения XML Schema
constexpr auto GUID_272 = "2612b4c0-9463-41ad-8732-3c33766b9a14"; // ФасетМаксимальнойДлиныXS;Фасет максимальной длины значения XML Schema
constexpr auto GUID_273 = "22e832d5-499d-4df1-8bc8-e97860c99e88"; // ФасетМинимальногоИсключающегоЗначенияXS;Фасет минимального исключающего значения XML Schema
constexpr auto GUID_274 = "7961f22f-ffab-422c-851e-b5c304803186"; // ФасетМинимальногоВключающегоЗначенияXS;Фасет минимального включающего значения XML Schema
constexpr auto GUID_275 = "4c71ba44-d3f2-418b-a103-e8342a6510a3"; // ФасетМаксимальногоИсключающегоЗначенияXS;Фасет максимального исключающего значения XML Schema
constexpr auto GUID_276 = "254d84e9-7981-424d-90af-ac11496a71e8"; // ФасетМаксимальногоВключающегоЗначенияXS;Фасет максимального включающего значения XML Schema
constexpr auto GUID_277 = "0cca2bd0-c25c-42f7-b8cb-54fe0e9cf010"; // ФасетОбразцаXS;Фасет образца значения XML Schema
constexpr auto GUID_278 = "66877974-5ad8-4cb1-8f5f-b51e5ab5acb5"; // ФасетПробельныхСимволовXS;Фасет пробельных символов XML Schema
constexpr auto GUID_279 = "1c9ac5fd-9501-4662-81bf-e200a234c237"; // ОпределениеПростогоТипаXS;Определение простого типа XML Schema
constexpr auto GUID_280 = "dc056fe7-49f8-4dde-81dd-19c9bb7da56a"; // ОпределениеСоставногоТипаXS;Определение составного типа XML Schema
constexpr auto GUID_281 = "44b7f86d-76a7-4f6b-bff0-9ec0b8fb31b9"; // МаскаXS;Маска XML Schema
constexpr auto GUID_282 = "a47c689a-25db-47e1-b0c2-8c06881e120f"; // ИмпортXS;Импорт XML Schema
constexpr auto GUID_283 = "12e7885c-35ce-4a14-8c9a-6f11f3088d9b"; // ВключениеXS;Включение XML Schema
constexpr auto GUID_284 = "7a71fd47-e78b-4b7e-9fe9-dda1d17a43d2"; // ПереопределениеXS;Переопределение XML Schema
constexpr auto GUID_285 = "17fd6869-4110-490e-9ae9-2af474d31c3f"; // ОпределениеГруппыАтрибутовXS;Определение группы атрибутов модели XML Schema
constexpr auto GUID_286 = "cc50c7b2-30ba-430c-86a4-813a747125aa"; // ИспользованиеАтрибутаXS;Использование атрибута XML Schema
constexpr auto GUID_287 = "c1863832-55cb-4cdb-8929-32ad6938e763"; // ОбъявлениеАтрибутаXS;Объявление атрибута XML Schema
constexpr auto GUID_288 = "368e2575-dea3-4d9e-ad38-3114e6064884"; // ОбъявлениеЭлементаXS;Объявление элемента XML Schema
constexpr auto GUID_289 = "e80e75ab-ee0e-42ab-93cf-714c6fc713d4"; // ОпределениеОграниченияИдентичностиXS;Определение ограничения идентичности XML Schema
constexpr auto GUID_290 = "686369bd-0b24-49f4-8ea0-b43bd1e15a2d"; // ОпределенияXPathXS;Определение компоненты XPath XML Schema
constexpr auto GUID_291 = "99a67d39-5acc-4154-9816-6b9ef8f07ec1"; // ОпределениеГруппыМоделиXS;Определение группы модели XML Schema
constexpr auto GUID_292 = "34b24784-c6d5-4a64-b2ea-a006c2d1c87c"; // ГруппаМоделиXS;Группа модели XML Schema
constexpr auto GUID_293 = "9b06b240-4665-4894-83ad-8d1d1df41a53"; // ОбъявлениеНотацииXS;Объявление нотации XML Schema
constexpr auto GUID_294 = "1d8cb728-cfde-4947-94ac-122c5ff1d012"; // ФрагментXS;Фрагмент XML Schema
constexpr auto GUID_295 = "be95b5b2-410e-4e4f-b045-384bce069d4c"; // СхемаXML;Схема XML
constexpr auto GUID_296 = "dad50d72-3dd4-4c63-a180-5eca6b65d634"; // ПостроительСхемXML;Построитель схем XML
constexpr auto GUID_297 = "30289051-2363-42ba-b0e7-edc0c13c84a2"; // НаборСхемXML;Набор схем XML
constexpr auto GUID_298 = "17fd7eda-ad4f-4ddc-ae50-f8693c13f4eb"; // КоллекцияТиповЗначенийXDTO;Коллекция типов значений XDTO
constexpr auto GUID_299 = "75187fab-35ea-4489-8229-3f435ed29db4"; // КоллекцияФасетовXDTO;Коллекция фасетов XDTO
constexpr auto GUID_300 = "4472d133-b769-4891-9d5f-4cb546ee07ce"; // ФасетXDTO;Фасет XDTO
constexpr auto GUID_301 = "c36db856-ba59-4519-86de-3f3cab08bf30"; // ЗначениеXDTO;Значение XDTO
constexpr auto GUID_302 = "32d5c9da-78ee-4473-9fe3-ad5039dbbe5c"; // КоллекцияЗначенийXDTO;Коллекция значений XDTO
constexpr auto GUID_303 = "fe56067a-4d8a-410d-b9f5-117f0a8b4c96"; // СвойствоXDTO;Свойство XDTO
constexpr auto GUID_304 = "82e77a59-999d-4b6a-818e-c25cea763f4e"; // КоллекцияСвойствXDTO;Коллекция свойств XDTO
constexpr auto GUID_305 = "66f0a0b7-50a4-4756-a3fa-9f9dbdde661e"; // ТипОбъектаXDTO;Тип объекта XDTO
constexpr auto GUID_306 = "6ba5c161-bef5-4a06-909d-183a02027242"; // ОбъектXDTO;Объект XDTO
constexpr auto GUID_307 = "2a647770-3db6-4107-afb6-136e464c301b"; // СписокXDTO;Список XDTO
constexpr auto GUID_308 = "9c53a943-13fe-4cba-a7c6-7abc776970d4"; // ПоследовательностьXDTO;Последовательность XDTO
constexpr auto GUID_309 = "9441787d-c13c-440e-a7e4-72bad7ce3bbb"; // ПакетXDTO;Пакет XDTO
constexpr auto GUID_310 = "4719bd07-f130-402e-9b16-1722945806e0"; // КоллекцияПакетовXDTO;Коллекция пакетов XDTO
constexpr auto GUID_311 = "1bdb5fb0-6894-4b6e-846d-fb68955d2f59"; // ВариантXDTO;ВариантXDTO
constexpr auto GUID_312 = "91a9e7f6-e14e-483a-8352-affcf1cf29dc"; // ЗаписьZipФайла;Запись ZIP файла
constexpr auto GUID_313 = "d9e00d71-f9b9-4e98-9a5b-85e2b24c6459"; // ЧтениеZipФайла;Чтение ZIP файла
constexpr auto GUID_314 = "7efb8db0-7f17-4776-b2c8-2d7799e979fa"; // ЭлементыZipФайла;Элементы ZIP файла
constexpr auto GUID_315 = "9574ad88-998f-4665-98c3-1bf7b3d69885"; // ЭлементZipФайла;Элемент ZIP файла
constexpr auto GUID_316 = "af7ccec8-62da-4ead-a391-8ae1dcc1e301"; // СистемнаяИнформация;СистемнаяИнформация
constexpr auto GUID_317 = "263f733e-36e8-4b34-a4f4-0d1f95ce0b5e"; // ИнтернетСоединение;ИнтернетСоединение
constexpr auto GUID_318 = "5a99793c-98d6-4dbf-bd4a-e1987d31fa66"; // ИнтернетПочта;ИнтернетПочта
constexpr auto GUID_319 = "23d189a6-58cf-40d2-8c2e-ec21981e6e03"; // ИнтернетПочтовыйПрофиль;ИнтернетПочтовыйПрофиль
constexpr auto GUID_320 = "e64d454e-c93b-4f30-b8c1-cd2c7c1dfe31"; // ИнтернетПочтовоеСообщение;ИнтернетПочтовоеСообщение
constexpr auto GUID_321 = "5e8dca04-b336-4baf-8d66-a1b3347ed8e1"; // Почта;Почта
constexpr auto GUID_322 = "23deb399-c0b6-4d53-a292-824e75d35ed4"; // ПочтовоеСообщение;ПочтовоеСообщение
constexpr auto GUID_323 = "10a765cf-5189-425c-ae6b-ac0383375b8c"; // ИнтернетПрокси;ИнтернетПрокси
constexpr auto GUID_324 = "18e3a3d9-0bf3-4cf8-8acd-830a8bcde887"; // HTTPСоединение;HTTPСоединение
constexpr auto GUID_325 = "4863c9ff-0456-4184-a867-560f6da710c9"; // FTPСоединение;FTPСоединение
constexpr auto GUID_326 = "eb8eb7e7-fc15-4bfc-90d7-64bff7b66257"; // ОболочкаHTMLДокумента;ОболочкаHTMLДокумента
constexpr auto GUID_327 = "668e0640-034b-4762-b155-81638ae38609"; // ЧтениеТекста;ЧтениеТекста
constexpr auto GUID_328 = "237eab83-3048-4939-ac70-4f008d69875c"; // ЗаписьТекста;ЗаписьТекста
constexpr auto GUID_329 = "0dda99d9-ae9f-43d2-b7ac-44f3fb0d4059"; // ПостроительОтчета;Построитель отчета
constexpr auto GUID_330 = "4652c4ec-1d1d-4af4-b835-e33fcb43af8c"; // Отбор;Отбор
constexpr auto GUID_331 = "0bbd3a56-3629-40a6-bf30-f3ea76d721a5"; // Порядок;Порядок
constexpr auto GUID_332 = "7dd764b6-b22f-4712-8edc-c0d634340e60"; // УсловноеОформление;Условное оформление
constexpr auto GUID_333 = "a6f6de04-a381-4047-98bd-1d0fe69ef2e5"; // ИзмерениеПостроителяОтчета;Измерение построителя отчета
constexpr auto GUID_334 = "c7a7b7cd-91cd-41cc-9790-e0e9fa39e766"; // ИзмеренияПостроителяОтчета;Коллекция измерений построителя отчета
constexpr auto GUID_335 = "b8633572-cb69-47a1-b64e-1eac612fb286"; // ПолеПостроителяОтчета;Поле построителя отчета
constexpr auto GUID_336 = "12cf13c1-b5a6-4d5b-b089-f8faad42f56d"; // ПоляПостроителяОтчета;Коллекция полей построителя отчета
constexpr auto GUID_337 = "de7ad39b-388d-46ef-97ea-dea11bd65471"; // НастройкиПостроителяОтчета;Настройки построителя отчета
constexpr auto GUID_338 = "ee7fc6a6-19df-4216-b7f3-7931a84b66e4"; // ПостроительЗапроса;Построитель запроса
constexpr auto GUID_339 = "ad1b7fdb-4172-4c59-818c-46794a0c318d"; // ИзмерениеПостроителяЗапроса;Измерение построителя запроса
constexpr auto GUID_340 = "f3e8049f-e5d4-437d-b9ce-89c593cd12e8"; // ИзмеренияПостроителяЗапроса;Коллекция измерений построителя запроса
constexpr auto GUID_341 = "9d87c412-8449-46f1-a0cf-0b43bf94cf40"; // ПолеПостроителяЗапроса;Поле построителя запроса
constexpr auto GUID_342 = "98fc0332-44ac-43eb-96c7-c22b27deffcb"; // ПоляПостроителяЗапроса;Коллекция полей построителя запроса
constexpr auto GUID_343 = "eadb6975-df3d-49f6-85e0-f10cb8f1b133"; // КонструкторФорматнойСтроки;Конструктор форматной строки
constexpr auto GUID_344 = "9f01aff1-2d19-4fe8-b805-f21b17a6c927"; // ПользовательИнформационнойБазы;Пользователь информационной базы
constexpr auto GUID_345 = "d6d05c81-8b72-4eef-96d3-f795c1424c29"; // РолиПользователя;Роли пользователя
constexpr auto GUID_346 = "56fbf80f-3dcc-4a5f-8ea9-2ee082b23c0b"; // СоединениеИнформационнойБазы;Активное соединение
constexpr auto GUID_347 = "511764f6-d39f-48c4-be7a-9327abe9fbd2"; // АнализДанных;Анализ данных
constexpr auto GUID_348 = "478fecbc-8a8d-4afe-a18e-7244141a3b42"; // КолонкиАнализаДанных;Коллекция колонок анализа данных
constexpr auto GUID_349 = "9b5ee266-054a-466b-9865-67b2ed2e1080"; // КолонкаАнализаДанных;Колонка анализа данных
constexpr auto GUID_350 = "9891013b-4b40-4a5f-8ca3-2f588729fd42"; // НастройкаКолонокАнализаДанных;Настройки колонок анализа данных
constexpr auto GUID_351 = "ee4363a9-55b4-429f-8d78-a5146d6afcb0"; // ЭлементУправленияКолонкамиАнализаДанных;Элемент управления колонкой анализа данных
constexpr auto GUID_352 = "56f0f2d7-84cc-4024-a5c2-bca753e0cb9c"; // ПараметрыАнализаДанных;Коллекция параметров анализа данных
constexpr auto GUID_353 = "735587c7-ae71-43e7-930d-acf34ae29d0a"; // ПараметрАнализаДанных;Параметр анализа данных
constexpr auto GUID_354 = "14e4711c-4cd8-40c7-b2e0-0f6b310efffa"; // НастройкаПараметровАнализаДанных;Настройки параметров анализа данных
constexpr auto GUID_355 = "1270c7ed-1eb8-4d54-89e5-6a2d425881bd"; // ЭлементУправленияПараметрамиАнализаДанных;Элемент управления параметром анализа данных
constexpr auto GUID_356 = "9dac100c-4977-4c59-be10-d66422ad2220"; // КолонкиМоделиПрогноза;Коллекция колонок модели прогноза
constexpr auto GUID_357 = "de8bf977-ad58-42a7-aa02-d732e077a6ac"; // КолонкаМоделиПрогноза;Колонка прогноза
constexpr auto GUID_358 = "9d53b372-9d3a-438b-b22f-5a30ad4d09b8"; // НастройкаВходныхКолонокМоделиПрогноза;Коллекция настроек входных колонок модели прогноза
constexpr auto GUID_359 = "8372e4c8-03e1-4d95-864a-38447951efdc"; // НастройкаВходнойКолонкиМоделиПрогноза;Настройка входной колонки модели прогноза
constexpr auto GUID_360 = "1baf0084-cf7e-4afc-a8ac-c3320e24497c"; // КолонкиРезультатаМоделиПрогноза;Коллекция результирующих колонок модели прогноза
constexpr auto GUID_361 = "366d1f2b-e4a5-418d-9b77-b61f6c600610"; // КолонкаРезультатаМоделиПрогноза;Результирующая колонка модели прогноза
constexpr auto GUID_362 = "8630ffc9-61e3-4ef0-8314-bdedcba9c1c6"; // ОбъектАнализаДанных;Объект анализа данных
constexpr auto GUID_363 = "ecf924cc-bd19-42ca-a3fa-e566552ccaf3"; // СвойствоОбъектаАнализаДанных;Свойство объекта анализа данных
constexpr auto GUID_364 = "b1b064f3-ae38-49bf-8c6d-390c65fd94af"; // ВидСравнения;ВидСравнения
constexpr auto GUID_365 = "f5b33f41-5396-4640-91e3-7eb1931d567a"; // ПеречислениеВидСравнения;ПеречислениеВидСравнения
constexpr auto GUID_366 = "fd585512-fcf5-4ec5-9559-bedb66050cc6"; // ПолеАнализаДанных;Поле анализа данных
constexpr auto GUID_367 = "67fc9c9c-d733-4e94-8dc1-eb884ddfefc5"; // ЗначениеПоляАнализаДанных;Значение поля анализа данных
constexpr auto GUID_368 = "483d17dd-826a-4234-b140-503227508491"; // РешениеАнализаДанных;Решение анализа данных
constexpr auto GUID_369 = "e72fe022-682f-445d-bba5-3bbd9ff02242"; // ПостроительОтчетаАнализаДанных;Построитель отчета анализа данных
constexpr auto GUID_370 = "41fda00e-eb76-4ab2-a3af-0aa6cffea116"; // АнализДанныхКластеризация;Анализ данных - кластеризация
constexpr auto GUID_371 = "48d91b6c-4542-4c87-ad04-785847f94f6f"; // ПараметрыКолонкиКластерногоАнализа;Параметры колонки кластерного анализа
constexpr auto GUID_372 = "34a626d3-3689-4ee8-a632-64dbd4866faf"; // КластерАнализаДанных;Кластер
constexpr auto GUID_373 = "7e1d13a1-813c-46e2-b793-d20c04dbee9c"; // МодельПрогнозаКластеризация;Модель прогноза кластеризация
constexpr auto GUID_374 = "65380768-de9c-46eb-ac0e-99edc24c7be9"; // РезультатАнализаДанныхКластеризация;Результат анализа данных - кластеризация
constexpr auto GUID_375 = "770e00f9-c3a8-4adf-9d2e-cdb6f525dfc0"; // АнализДанныхДеревоРешений;Анализ данных - дерево решений
constexpr auto GUID_376 = "e4bc6a07-3ef4-404a-8767-18213dc46920"; // КлассификацияОбъектаАнализаДанных;Классификация объекта
constexpr auto GUID_377 = "0c7585ee-e2ae-4ce7-9295-852409fdce33"; // УзелДереваРешений;Узел дерева решений
constexpr auto GUID_378 = "2b2318bb-2b40-495e-9765-9df25ff702c3"; // МодельПрогнозаДеревоРешений;Модель прогноза дерево решений
constexpr auto GUID_379 = "d028d5b5-210f-457b-8e01-93d91998a30f"; // РезультатАнализаДанныхДеревоРешений;Результат анализа данных - дерево решений
constexpr auto GUID_380 = "30aa5492-1275-4aae-8cea-11efc09b593d"; // АнализДанныхПоискАссоциаций;Анализ данных - поиск ассоциаций
constexpr auto GUID_381 = "39c2c0c0-58d2-4442-92ae-f6784901100a"; // АссоциированнаяГруппа;Ассоциированная группа
constexpr auto GUID_382 = "921dbba9-eb2b-4f8a-9f95-9553c0d3dd71"; // ПравилоАссоциации;Правило ассоциации
constexpr auto GUID_383 = "0ea99d02-f391-4e8e-8a5b-a14df14181e6"; // МодельПрогнозаПоискАссоциаций;Модель прогноза поиск ассоциаций
constexpr auto GUID_384 = "5b42e693-6226-48f7-8a80-f844b5067aa5"; // РезультатАнализаДанныхПоискАссоциаций;Результат анализа данных - поиск ассоциаций
constexpr auto GUID_385 = "16fcb0c7-caae-46d7-b563-70e4942bb26a"; // АнализДанныхПоискПоследовательностей;Анализ данных - поиск последовательностей
constexpr auto GUID_386 = "67d2a668-7b97-4455-9ea1-7b5f97c53d77"; // ШаблонПоследовательностиАнализаДанных;Шаблон последовательности
constexpr auto GUID_387 = "40194b1b-e2d8-40a0-a497-f86949163319"; // МодельПрогнозаПоискПоследовательностей;Модель прогноза поиск последовательностей
constexpr auto GUID_388 = "781eeda4-b90b-4f9b-975e-0936750c21ff"; // РезультатАнализаДанныхПоискПоследовательностей;Результат анализа данных - поиск последовательностей
constexpr auto GUID_389 = "fcfa33db-3260-4475-8171-9bd35e19f206"; // АнализДанныхОбщаяСтатистика;Анализ данных - общая статистика
constexpr auto GUID_390 = "78261c5a-1329-42eb-bae6-94abbc2e4d29"; // ИнформацияНепрерывногоПоляАнализаДанных;Информация о числовом поле анализа данных
constexpr auto GUID_391 = "cee23635-1a0b-4e52-add7-1bf07cd6c2c5"; // ИнформацияДискретногоПоляАнализаДанных;Информация о дискретном поле анализа данных
constexpr auto GUID_392 = "986e7582-25d3-47a3-abcf-da3313428720"; // РезультатАнализаДанныхОбщаяСтатистика;Результат анализа данных - общая статистика
constexpr auto GUID_393 = "70512ca5-2a47-4a66-8ccb-1ff59cb6c199"; // WSПараметр;Параметр
constexpr auto GUID_394 = "0b9e72e2-fbf0-4e15-a8c8-98992cebc7b1"; // WSКоллекцияПараметров;Коллекция параметров
constexpr auto GUID_395 = "622d0bdd-3f78-437b-a9be-3040d53629b9"; // WSВозвращаемоеЗначение;Возвращаемое значение
constexpr auto GUID_396 = "6d659293-1dc2-4ee8-9354-c8d961990bca"; // WSОперация;Операция
constexpr auto GUID_397 = "5b9af638-5565-4492-95f7-d6d0ae78e786"; // WSКоллекцияОпераций;Коллекция операций
constexpr auto GUID_398 = "846ba514-0118-4bbe-aae5-ba1cd0b40e74"; // WSИнтерфейс;Интерфейс
constexpr auto GUID_399 = "a0765937-cbd0-4e9d-a7ae-4becf7ba81a0"; // WSТочкаПодключения;Точка подключения
constexpr auto GUID_400 = "07994a20-612b-4234-9953-f0ee2b3210ed"; // WSКоллекцияТочекПодключения;Коллекция точек подключения
constexpr auto GUID_401 = "9f3e22e8-5373-4378-aef1-5b26f5ed0358"; // WSСервис;Web-cервис
constexpr auto GUID_402 = "18784cde-1274-4805-9567-11eda247914e"; // WSКоллекцияСервисов;Коллекция Web-сервисов
constexpr auto GUID_403 = "05a6095e-795e-469b-9d8d-8900e5c1640c"; // WSОпределения;Определения Web-сервисов
constexpr auto GUID_404 = "918542c4-13cd-47a8-882e-523e79763ac2"; // WSПрокси;Прокси Web-сервиса
constexpr auto GUID_405 = "ec5c4675-a178-4a33-89df-95ecce6f3bc3"; // КонструкторСхемыКомпоновкиДанных;Конструктор схемы компоновки данных
constexpr auto GUID_406 = "5c476589-3099-4aac-9a70-0891247aa866"; // КомпоновщикМакетаКомпоновкиДанных;Компоновщик макета компоновки данных
constexpr auto GUID_407 = "c294aeb6-922e-4cc9-8a29-a061d33504f7"; // ПроцессорКомпоновкиДанных;Процессор компоновки данных
constexpr auto GUID_408 = "303e87f5-4543-482e-b922-edc4a9907ad0"; // ЭлементРезультатаКомпоновкиДанных;Элемент результата компоновки данных
constexpr auto GUID_409 = "377d8ed3-8ad6-4206-b5b3-4669744f9950"; // ПроцессорВыводаРезультатаКомпоновкиДанныхВТабличныйДокумент;Процессор вывода результата компоновки данных в табличный документ
constexpr auto GUID_410 = "276c10d8-113c-4f7d-847b-19cd576545ad"; // ИсточникДанныхСводнойТаблицыКомпоновкиДанных;Источник данных сводной таблицы компоновки данных
constexpr auto GUID_411 = "4797dec6-187b-43a8-8737-c6df1a51ab4d"; // КонструкторНастроекКомпоновкиДанных;Конструктор настроек компоновки данных
constexpr auto GUID_412 = "1b94aa84-55f4-4677-b852-cc0bbfc8746d"; // КонструкторМакетаОформленияКомпоновкиДанных;Конструктор макета оформления компоновки данных
constexpr auto GUID_413 = "dc29f857-fc4f-4cd1-a7ca-e8e71f3955b3"; // СхемаКомпоновкиДанных;Схема компоновки данных
constexpr auto GUID_414 = "713ec741-64d3-4db6-9555-f6981af18c5c"; // ВложенныеСхемыКомпоновкиДанных;Вложенные схемы компоновки данных
constexpr auto GUID_415 = "920867d5-88ef-4c9f-ba3e-d4ebf0746a8d"; // ИсточникДанныхСхемыКомпоновкиДанных;Источник данных схемы компоновки данных
constexpr auto GUID_416 = "5c687638-4d54-4a77-aef8-122f7c44ec7f"; // ИсточникиДанныхСхемыКомпоновкиДанных;Источник данных схемы компоновки данных
constexpr auto GUID_417 = "73f4bb62-72cf-4a32-a515-3f4eb8a544ba"; // НаборДанныхЗапросСхемыКомпоновкиДанных;Набор данных схемы компоновки данных - запрос
constexpr auto GUID_418 = "0f33b4ac-4d9d-4fb0-b349-c6166c43056a"; // Запрос;Запрос
constexpr auto GUID_419 = "947c2026-2d58-4a0f-bd90-a3e4ece00358"; // НаборДанныхОбъектСхемыКомпоновкиДанных;Набор данных схемы компоновки данных - объект
constexpr auto GUID_420 = "214a9824-0065-4ca7-bed8-5bfa806218d9"; // НаборДанныхОбъединениеСхемыКомпоновкиДанных;Набор данных схемы компоновки данных - объединение
constexpr auto GUID_421 = "3f6ced48-231a-4935-98e9-d78752fc0dea"; // ОграничениеИспользованияПоляСхемыКомпоновкиДанных;Ограничение использования поля схемы компоновки данных
constexpr auto GUID_422 = "4760bb3c-3ef5-457f-a3a0-d0841b0caa0e"; // ПолеНабораДанныхСхемыКомпоновкиДанных;Поле набора данных схемы компоновки данных
constexpr auto GUID_423 = "1cfe6f7d-5a15-4924-94b0-523cda8d91de"; // ПапкаПолейНабораДанныхСхемыКомпоновкиДанных;Папка полей набора данных схемы компоновки данных
constexpr auto GUID_424 = "814d9d81-c002-4ac1-ac56-02995ee6f14c"; // ПоляНабораДанныхСхемыКомпоновкиДанных;Поля набора данных схемы компоновки данных
constexpr auto GUID_425 = "fbc5f6fe-9641-4551-b87c-36a46853a1e2"; // НаборыДанныхСхемыКомпоновкиДанных;Наборы данных схемы компоновки данных
constexpr auto GUID_426 = "bf09e5de-88d8-48a4-8bcc-553d2b870868"; // ВычисляемоеПолеСхемыКомпоновкиДанных;Вычисляемое поле схемы компоновки данных
constexpr auto GUID_427 = "4480b02e-ecaa-4e27-a2d7-edc2ed85af60"; // ВычисляемыеПоляСхемыКомпоновкиДанных;Вычисляемые поля схемы компоновки данных
constexpr auto GUID_428 = "f9a05347-8200-40e2-b640-ec738d2c53ca"; // ПолеИтогаСхемыКомпоновкиДанных;Поле итога схемы компоновки данных
constexpr auto GUID_429 = "b1397e30-d355-49cb-9923-5c2456a30200"; // ПоляИтогаСхемыКомпоновкиДанных;Поля итога схемы компоновки данных
constexpr auto GUID_430 = "16cd8047-383b-4593-86bd-b93e62219d79"; // СвязьНаборовДанныхСхемыКомпоновкиДанных;Связь наборов данных схемы компоновки данных
constexpr auto GUID_431 = "59cacbb6-45b9-47a5-b579-b47659516461"; // СвязиНаборовДанныхСхемыКомпоновкиДанных;Связи наборов данных схемы компоновки данных
constexpr auto GUID_432 = "0fe5e8b8-c003-4a38-bcaf-727915228219"; // ПараметрСхемыКомпоновкиДанных;Параметр схемы компоновки данных
constexpr auto GUID_433 = "f1fd083e-79d1-4c8b-b01a-6079c083ccc5"; // ПараметрыСхемыКомпоновкиДанных;Параметры схемы компоновки данных
constexpr auto GUID_434 = "f048b2de-9847-4914-896c-33081ac2fe2d"; // ВложеннаяСхемаКомпоновкиДанных;Вложенная схема компоновки данных
constexpr auto GUID_435 = "2f49c37e-abe1-4b8b-9dc5-cea60b7ef9d5"; // МакетПоляСхемыКомпоновкиДанных;Макет поля схемы компоновки данных
constexpr auto GUID_436 = "27d4b079-cc99-42ec-9e08-8af35c80b1b5"; // МакетыПолейСхемыКомпоновкиДанных;Макеты полей схемы компоновки данных
constexpr auto GUID_437 = "32dcf250-dbd1-44bc-952a-e39bd2fc51dc"; // МакетГруппировкиСхемыКомпоновкиДанных;Макет группировки схемы компоновки данных
constexpr auto GUID_438 = "cb9e1c75-fcff-49e8-b64b-d99935600a1a"; // МакетПолейИтогаСхемыКомпоновкиДанных;Макет полей итога схемы компоновки данных
constexpr auto GUID_439 = "4cf8c3df-27a3-49c0-980f-45a103b2df8a"; // МакетыГруппировокСхемыКомпоновкиДанных;Макеты группировок схемы компоновки данных
constexpr auto GUID_440 = "5e37f18a-6339-4d83-a244-acb661ddbbb8"; // МакетыПолейИтогаСхемыКомпоновкиДанных;Макеты полей итога схемы компоновки данных
constexpr auto GUID_441 = "87c2bdb8-d50c-4fd5-b601-7de9e1e53ee6"; // ОписаниеМакетаСхемыКомпоновкиДанных;Описание макета схемы компоновки данных
constexpr auto GUID_442 = "e01ec806-7d02-44e5-92a8-f9625127aef2"; // ОписанияМакетовСхемыКомпоновкиДанных;Описания макетов схемы компоновки данных
constexpr auto GUID_443 = "3c72ff56-7e04-4385-bc03-92d4bd6c351c"; // НастройкиКомпоновкиДанных;Настройки компоновки данных
constexpr auto GUID_444 = "4238019d-7e49-4fc9-91db-b6b951d5cf8e"; // Структура;Структура
constexpr auto GUID_445 = "bb79ced1-938e-4c74-8bd4-e3ca37b38d9d"; // КоллекцияЭлементовСтруктурыНастроекКомпоновкиДанных;Коллекция элементов структуры настроек компоновки данных
constexpr auto GUID_446 = "ab87afa4-b896-433c-aff0-31e550bc916f"; // КоллекцияЭлементовСтруктурыТаблицыКомпоновкиДанных;Коллекция элементов структуры таблицы компоновки данных
constexpr auto GUID_447 = "9ec3ac7c-ba9a-48cb-9e84-ba468bf83921"; // ГруппировкаКомпоновкиДанных;Группировка компоновки данных
constexpr auto GUID_448 = "4ae1d392-477c-4d50-a0f9-3425176dd3bf"; // ТаблицаКомпоновкиДанных;Таблица компоновки данных
constexpr auto GUID_449 = "cf21ffa3-bba8-4e75-93c9-93c842fcea86"; // ГруппировкаТаблицыКомпоновкиДанных;Группировка таблицы компоновки данных
constexpr auto GUID_450 = "7f82c89e-4412-4b88-8f0e-d15717c32e62"; // КоллекцияЭлементовСтруктурыДиаграммыКомпоновкиДанных;Коллекция элементов структуры диаграммы компоновки данных
constexpr auto GUID_451 = "7fc616cd-8769-477f-8f95-483defcfe792"; // ДиаграммаКомпоновкиДанных;Диаграмма компоновки данных
constexpr auto GUID_452 = "b19f1f63-0819-4593-895c-db11393e1442"; // ГруппировкаДиаграммыКомпоновкиДанных;Группировка диаграммы компоновки данных
constexpr auto GUID_453 = "9b49c053-aaf3-4745-8170-67fb77635b72"; // НастройкиВложенногоОбъектаКомпоновкиДанных;Настройки вложенного объекта
constexpr auto GUID_454 = "eb654f6e-0127-4acf-811a-beff315427c7"; // КоллекцияПолейГруппировкиКомпоновкиДанных;Коллекция полей группировки компоновки данных
constexpr auto GUID_455 = "6bdb31c2-941c-447a-aafc-24048fc0660e"; // ПолеГруппировкиКомпоновкиДанных;Поле группировки компоновки данных
constexpr auto GUID_456 = "e2e2f2e9-e309-4212-9c70-3ab32dd93b4d"; // ПоляГруппировкиКомпоновкиДанных;Поля группировки компоновки данных
constexpr auto GUID_457 = "33f87b19-3c6e-4663-932a-73082d62586f"; // КоллекцияДоступныхПолейКомпоновкиДанных;Коллекция доступных полей компоновки данных
constexpr auto GUID_458 = "057b5d8d-57b0-434d-b6c4-023f29ad7634"; // ДоступноеПолеКомпоновкиДанных;Доступное поле компоновки данных
constexpr auto GUID_459 = "0eeffa34-6a10-410f-abf0-3db0fca30954"; // ДоступноеПолеОтбораКомпоновкиДанных;Доступный параметр отбора компоновки данных
constexpr auto GUID_460 = "9d9f5b23-a154-4b09-8a43-d8f7cbcff42e"; // ДоступныеПоляКомпоновкиДанных;Доступные поля компоновки данных
constexpr auto GUID_461 = "4b8d22c3-e56d-4360-9e5b-141e64efda13"; // КоллекцияДоступныхОбъектовНастройкиКомпоновкиДанных;Коллекция доступных объектов настройки компоновки данных
constexpr auto GUID_462 = "fff609e6-f4aa-4522-b725-5fc7038cc5c2"; // ДоступныйОбъектНастройкиКомпоновкиДанных;Доступный объект настройки компоновки данных
constexpr auto GUID_463 = "8a39c1d6-e55b-44f7-9cd9-7a13545b9725"; // ДоступныеОбъектыНастройкиКомпоновкиДанных;Доступные объекты настройки компоновки данных
constexpr auto GUID_464 = "8031a993-5d80-4cf1-9e91-b75987a96595"; // КоллекцияВыбранныхПолейКомпоновкиДанных;Коллекция выбранных полей компоновки данных
constexpr auto GUID_465 = "1f6b2215-7ae1-45b4-96fc-8ede64c64320"; // ВыбранноеПолеКомпоновкиДанных;Выбранное поле компоновки данных
constexpr auto GUID_466 = "b822289e-f217-46d9-8923-50fab1d9cb5f"; // ГруппаВыбранныхПолейКомпоновкиДанных;Группа выбранных полей компоновки данных
constexpr auto GUID_467 = "a549d202-3b0a-420b-ab2b-6b396fd38da2"; // ВыбранныеПоляКомпоновкиДанных;Выбранные поля компоновки данных
constexpr auto GUID_468 = "946354c9-fd11-4957-99fa-19cd342a22e0"; // КоллекцияЭлементовПорядкаКомпоновкиДанных;Коллекция элементов порядка компоновки данных
constexpr auto GUID_469 = "df2fa84a-c2fd-488d-ba62-6425d5273530"; // ЭлементПорядкаКомпоновкиДанных;Элемент порядка компоновки данных
constexpr auto GUID_470 = "11743ff3-2db3-4cfc-9404-90ed8209437f"; // ПорядокКомпоновкиДанных;Порядок компоновки данных
constexpr auto GUID_471 = "cab0d12b-3c88-4993-8edc-8c3827cadc7d"; // КомпоновщикНастроекКомпоновкиДанных;Компоновщик настроек компоновки данных
constexpr auto GUID_472 = "b75f45b7-155d-436c-a105-6b5adb2f3711"; // КоллекцияЭлементовОтбораКомпоновкиДанных;Коллекция элементов отбора компоновки данных
constexpr auto GUID_473 = "e980362a-8a78-4dd1-ab4b-a7ce32b26f13"; // ЭлементОтбораКомпоновкиДанных;Элемент отбора сравнение компоновки данных
constexpr auto GUID_474 = "386d2646-4b6a-4b53-84bd-29167fada106"; // ГруппаЭлементовОтбораКомпоновкиДанных;Элемент отбора группа компоновки данных
constexpr auto GUID_475 = "f6841c6b-6c71-4c82-ae9e-d08b49db326c"; // ОтборКомпоновкиДанных;Отбор компоновки данных
constexpr auto GUID_476 = "fc3d5f99-0ced-4437-8a68-0afff111ca98"; // КоллекцияВариантовПользовательскогоПоляВыборКомпоновкиДанных;Коллекция вариантов пользовательских полей компоновки данных
constexpr auto GUID_477 = "3e9bb9bc-3f17-40bd-ac8b-779879c440b6"; // ВариантПользовательскогоПоляВыборКомпоновкиДанных;Вариант пользовательского поля выбор компоновки данных
constexpr auto GUID_478 = "a510731f-67a9-496e-aa24-c2b21a2dfd19"; // ВариантыПользовательскогоПоляВыборКомпоновкиДанных;Варианты пользовательского поля выбор компоновки данных
constexpr auto GUID_479 = "1f4a2c63-9335-4a14-a03a-97509c02bbda"; // КоллекцияПользовательскихПолейКомпоновкиДанных;Коллекция пользовательских полей компоновки данных
constexpr auto GUID_480 = "12fe8841-74b1-4a82-9202-4e7f451e839f"; // ПользовательскоеПолеВыражениеКомпоновкиДанных;Пользовательское поле выражение компоновки данных
constexpr auto GUID_481 = "3ff6f37e-df4e-4eee-b43f-e977ba5ad983"; // ПользовательскоеПолеВыборКомпоновкиДанных;Пользовательское поле выбор компоновки данных
constexpr auto GUID_482 = "58f85874-8948-4976-b0a6-b1b5fee095ba"; // ПользовательскиеПоляКомпоновкиДанных;Пользовательские поля компоновки данных
constexpr auto GUID_483 = "f228857f-8080-47c8-9091-4ab26480a581"; // КоллекцияОформляемыхПолейКомпоновкиДанных;Коллекция оформляемых полей компоновки данных
constexpr auto GUID_484 = "95a67d64-f655-4481-be98-d71154609507"; // ОформляемыеПоляКомпоновкиДанных;Оформляемые поля компоновки данных
constexpr auto GUID_485 = "ffd50ba1-926f-4b71-97bd-e244fa401709"; // ОформляемоеПолеКомпоновкиДанных;Оформляемое поле компоновки данных
constexpr auto GUID_486 = "674dd0a5-d850-4f37-89c6-343bf73156eb"; // КоллекцияЭлементовУсловногоОформленияКомпоновкиДанных;Коллекция элементов условного оформления компоновки данных
constexpr auto GUID_487 = "27abef2f-b82f-4076-8402-0f977fffd0ab"; // ЭлементУсловногоОформленияКомпоновкиДанных;Элемент условного оформления компоновки данных
constexpr auto GUID_488 = "93de27ad-a2d8-4b10-a82b-483c9b0648fe"; // УсловноеОформлениеКомпоновкиДанных;Условное оформление
constexpr auto GUID_489 = "6217eee1-6289-49d2-9315-d87888cd2d62"; // ЗначенияПараметровДанныхКомпоновкиДанных;Значения параметров данных компоновки данных
constexpr auto GUID_490 = "3300f132-2b00-4f2d-a0bc-a1495d02d706"; // ЗначенияПараметровВыводаКомпоновкиДанных;Значения параметров вывода компоновки данных
constexpr auto GUID_491 = "cf5b2a88-6d0a-4fc1-94b7-0f493f634515"; // ЗначенияПараметровВыводаГруппировкиКомпоновкиДанных;Значения параметров вывода группировки компоновки данных
constexpr auto GUID_492 = "d5f47dde-c65d-47c0-89f8-15f430d42fad"; // ЗначенияПараметровВыводаГруппировкиТаблицыКомпоновкиДанных;Значения параметров вывода группировки таблицы компоновки данных
constexpr auto GUID_493 = "a7951210-9783-4101-9d37-30a2248fac7f"; // ЗначенияПараметровВыводаГруппировкиДиаграммыКомпоновкиДанных;Значения параметров вывода группировки диаграммы компоновки данных
constexpr auto GUID_494 = "defbac7f-a5d7-457d-8439-2a1375ea079a"; // ЗначенияПараметровВыводаТаблицыКомпоновкиДанных;Значения параметров вывода таблицы компоновки данных
constexpr auto GUID_495 = "fccf7441-bb25-4fd1-93d6-88bee680ee36"; // ЗначенияПараметровВыводаДиаграммыКомпоновкиДанных;Значения параметров вывода диаграммы компоновки данных
constexpr auto GUID_496 = "9a1450ab-90d4-4f46-843a-bf3af6aaf8b2"; // АвтоВыбранноеПолеКомпоновкиДанных;Авто выбранное поле компоновки данных
constexpr auto GUID_497 = "6bafeba8-ef8b-43fd-8041-1570846ae2f9"; // АвтоЭлементПорядкаКомпоновкиДанных;Авто элемент порядка компоновки данных
constexpr auto GUID_498 = "62f33dd6-96a6-4a8d-9fff-47256f60b67b"; // АвтоПолеГруппировкиКомпоновкиДанных;Авто поле группировки компоновки данных
constexpr auto GUID_499 = "45c59573-b8ba-40c8-86e9-48f0e255f80b"; // ИсточникДоступныхНастроекКомпоновкиДанных;Источник доступных настроек компоновки данных для схемы компоновки данных
constexpr auto GUID_500 = "25eff738-1515-4534-8a3c-9ff33f544930"; // ТекущиеДанныеСтруктурыНастроекКомпоновкиДанных;Текущие данные структуры настроек компоновки данных
constexpr auto GUID_501 = "54ea12c9-d306-418f-93c0-586cb80d41a5"; // ОграниченияИспользованияДоступныхПолейКомпоновкиДанных;Ограничения использования доступных полей компоновки данных
constexpr auto GUID_502 = "0b8877bf-b632-4c2e-8a61-451d061b8570"; // ОграничениеИспользованияДоступногоПоляКомпоновкиДанных;Ограничение использования доступного поля компоновки данных
constexpr auto GUID_503 = "3cff7608-2159-4095-b12e-04d48bbe53a3"; // МакетКомпоновкиДанных;Макет компоновки данных
constexpr auto GUID_504 = "8ce2ea30-9a92-41ac-831a-c4c857fa9da8"; // ИсточникДанныхМакетаКомпоновкиДанных;Источник данных макета компоновки данных
constexpr auto GUID_505 = "60e2867b-8d8e-4a2c-b80a-c1ce481e1aec"; // ИсточникиДанныхМакетаКомпоновкиДанных;Источники данных макета компоновки данных
constexpr auto GUID_506 = "5f7cdd8e-aa42-4fb4-8788-e183e51a7e7f"; // НаборДанныхЗапросМакетаКомпоновкиДанных;Набор данных макета компоновки данных - запрос
constexpr auto GUID_507 = "a1b32870-df0f-4bf5-96ea-93bbed7be145"; // НаборДанныхОбъектМакетаКомпоновкиДанных;Набор данных макета компоновки данных - объект
constexpr auto GUID_508 = "4ce07835-8699-46f4-a35a-08283a1b34e7"; // НаборДанныхОбъединениеМакетаКомпоновкиДанных;Набор данных макета компоновки данных - объединение
constexpr auto GUID_509 = "9b462719-e895-43b7-9ece-e8656011c980"; // ПолеНабораДанныхМакетаКомпоновкиДанных;Поле набора данных макета компоновки данных
constexpr auto GUID_510 = "adcc9974-71b3-4ac4-a2e0-c6d59b31c679"; // ПоляНабораДанныхМакетаКомпоновкиДанных;Поля набора данных макета компоновки данных
constexpr auto GUID_511 = "8a438e9d-e648-439a-84b1-25d55ed6ef80"; // НаборыДанныхМакетаКомпоновкиДанных;Наборы данных макета компоновки данных
constexpr auto GUID_512 = "b654ac1e-25a5-4002-9ed3-f7dee8bb39d7"; // СвязьНаборовДанныхМакетаКомпоновкиДанных;Связь наборов данных макета компоновки данных
constexpr auto GUID_513 = "c2f2c14f-aa1e-4c43-b8af-fccd2e0503d1"; // СвязиНаборовДанныхМакетаКомпоновкиДанных;Связи наборов данных макета компоновки данных
constexpr auto GUID_514 = "3d6d167d-7439-4f13-a628-29054c4cd42f"; // МакетыТелаТаблицыМакетаКомпоновкиДанных;Макеты тела таблицы
constexpr auto GUID_515 = "7f07ff5a-1585-44d5-85f4-6d7ace2ce1a7"; // МакетыТелаДиаграммыМакетаКомпоновкиДанных;Макеты тела диаграммы
constexpr auto GUID_516 = "d31cf6da-b85d-41d7-99c0-fadccd30e963"; // ЗначениеПараметраМакетаКомпоновкиДанных;Значение параметра макета компоновки данных
constexpr auto GUID_517 = "60dfcac9-6739-42f0-90ea-dff9325b5fea"; // ЗначенияПараметровМакетаКомпоновкиДанных;Значения параметров макета компоновки данных
constexpr auto GUID_518 = "7ed84402-4d1f-4332-961f-c82c6d29d0de"; // ОписаниеМакетаОбластиМакетаКомпоновкиДанных;Определение макета макета компоновки данных
constexpr auto GUID_519 = "4c86f850-4b93-4c46-8966-133fcb90f13b"; // ОписанияМакетовОбластейМакетаКомпоновкиДанных;Определения макетов макета компоновки данных
constexpr auto GUID_520 = "4c4918fb-48a8-41e8-896d-1c51a9da4e30"; // ДополнениеПериодаМакетаКомпоновкиДанных;Дополнение периода макета компоновки данных
constexpr auto GUID_521 = "7b893d95-67bf-439b-aca7-479a0441fc91"; // ЭлементГруппировкиМакетаКомпоновкиДанных;Элемент группировки макета компоновки данных
constexpr auto GUID_522 = "cf09c7d0-1fce-4da5-82ca-4dfb67749e70"; // ГруппировкиМакетаКомпоновкиДанных;Группировки макета компоновки данных
constexpr auto GUID_523 = "476d65e3-be26-4cc7-bf6f-953d046cc3e2"; // ГруппировкиДиаграммыМакетаКомпоновкиДанных;Группировки диаграммы макета компоновки данных
constexpr auto GUID_524 = "1885ec0a-f66a-43f0-aae6-6aac383adda3"; // ТелоМакетаКомпоновкиДанных;Тело макета компоновки данных
constexpr auto GUID_525 = "23e38661-84cd-499a-b85a-171f8887a484"; // МакетОбластиМакетаКомпоновкиДанных;Макет макета компоновки данных
constexpr auto GUID_526 = "d4afc85f-4858-4ee4-bcb2-487dea2417a1"; // ГруппировкаМакетаКомпоновкиДанных;Группировка макета компоновки данных
constexpr auto GUID_527 = "7c54a644-32c0-42d5-b039-f38d3003e0bc"; // ИерархическаяГруппировкаМакетаКомпоновкиДанных;Иерархическая группировка макета компоновки данных
constexpr auto GUID_528 = "8e54946f-9139-4179-999e-3ee854b7194e"; // ЗаписиМакетаКомпоновкиДанных;Записи макета компоновки данных
constexpr auto GUID_529 = "a5c0fb1e-200d-4439-bd45-f7d8e62c2a3e"; // МакетГруппировкиТаблицыМакетаКомпоновкиДанных;Макет группировки таблицы макета компоновки данных
constexpr auto GUID_530 = "fd7d74da-9cd1-4a67-bd1e-b1aa95e7ea59"; // ГруппировкаТаблицыМакетаКомпоновкиДанных;Группировка таблицы макета компоновки данных
constexpr auto GUID_531 = "24c8b216-a3af-44f7-a04e-b9f4daedd625"; // ИерархическаяГруппировкаТаблицыМакетаКомпоновкиДанных;Иерархическая группировка макета компоновки данных
constexpr auto GUID_532 = "2c429dcd-9c3d-43c0-bcb3-7c29a1f6c049"; // ЗаписиТаблицыМакетаКомпоновкиДанных;Записи таблицы макета компоновки данных
constexpr auto GUID_533 = "6eb90130-73e3-4a0c-9287-0d071d61cf60"; // ТелоГруппировкиТаблицыМакетаКомпоновкиДанных;Тело таблицы макета компоновки данных
constexpr auto GUID_534 = "6f9cb7d8-7907-45fc-a24c-5db2eeec66a8"; // ТаблицаМакетаКомпоновкиДанных;Таблица макета компоновки данных
constexpr auto GUID_535 = "16bd2d67-c5ad-4fa0-b5df-d9810d1f1e2d"; // МакетГруппировкиДиаграммыМакетаКомпоновкиДанных;Макет группировки диаграммы макета компоновки данных
constexpr auto GUID_536 = "92051b77-e9da-4c04-a15b-ae687965e211"; // ГруппировкаДиаграммыМакетаКомпоновкиДанных;Группировка диаграммы макета компоновки данных
constexpr auto GUID_537 = "923d1dfe-0fde-408d-9234-1f2c4d287ae5"; // ИерархическаяГруппировкаДиаграммыМакетаКомпоновкиДанных;Иерархическая группировка диаграммы макета компоновки данных
constexpr auto GUID_538 = "3f71e54c-6f1e-498b-9103-557d3807db6c"; // ТелоГруппировкиДиаграммыМакетаКомпоновкиДанных;Тело диаграммы макета компоновки данных
constexpr auto GUID_539 = "ef0aa926-13c5-44de-bfce-108a7ff85e9a"; // ДиаграммаМакетаКомпоновкиДанных;Диаграмма макета компоновки данных
constexpr auto GUID_540 = "a4769021-d0f6-436c-8dc4-e50df43d04ec"; // ВложенныйОбъектМакетаКомпоновкиДанных;Вложенный объект части компоновки данных макета компоновки данных
constexpr auto GUID_541 = "8afd5f91-10ba-4ce9-9cdb-008d79f9ba07"; // МакетТелаТаблицыМакетаКомпоновкиДанных;Макет тела таблицы
constexpr auto GUID_542 = "3f316dfe-a0b4-4e28-86d7-becd5c637379"; // МакетТелаДиаграммыМакетаКомпоновкиДанных;Макет тела диаграммы
constexpr auto GUID_543 = "406f1b78-cc58-4ffa-8226-9d443fb28bf5"; // МакетОбластиКомпоновкиДанных;Макет области компоновки данных
constexpr auto GUID_544 = "49a445be-ca76-4de0-9858-2bd0cdb816d0"; // МакетДиаграммыОбластиКомпоновкиДанных;Макет диаграммы области компоновки данных
constexpr auto GUID_545 = "e3c4a911-993b-4ce4-b370-1f8c57cdda92"; // МакетРесурсаДиаграммыОбластиКомпоновкиДанных;Макет ресурса диаграммы области компоновки данных
constexpr auto GUID_546 = "0af2168b-0919-4f46-90db-9fe7454856dc"; // МакетГруппировкиДиаграммыОбластиКомпоновкиДанных;Макет группировки диаграммы области компоновки данных
constexpr auto GUID_547 = "277def41-af90-4a7a-8228-d03a9bcb8628"; // ОформлениеПоляОбластиКомпоновкиДанных;Оформление поля таблицы области компоновки данных
constexpr auto GUID_548 = "291053b7-0b71-4f25-ac04-066f04738d66"; // ПолеОбластиКомпоновкиДанных;Поле области компоновки данных
constexpr auto GUID_549 = "fb42ac69-74e4-491e-b21b-d5b6e91524bf"; // ЭлементыМакетаОбластиКомпоновкиДанных;Элементы макета области компоновки данных
constexpr auto GUID_550 = "9a55a66e-9da5-4b88-8f34-155a3f983f5e"; // ОформлениеЯчейкиТаблицыОбластиКомпоновкиДанных;Оформление ячейки таблицы области компоновки данных
constexpr auto GUID_551 = "500e497b-201c-4dc2-899f-628b6b9c9f16"; // ЯчейкаТаблицыОбластиКомпоновкиДанных;Ячейка таблицы области компоновки данных
constexpr auto GUID_552 = "a517f038-5666-41cd-ab31-a35717c98239"; // ЯчейкиТаблицыОбластиКомпоновкиДанных;Ячейки таблицы области компоновки данных
constexpr auto GUID_553 = "1ac47e29-e978-40e7-9af8-b718b3537c18"; // СтрокаТаблицыОбластиКомпоновкиДанных;Строка таблицы области компоновки данных
constexpr auto GUID_554 = "bf2a3e2e-5c7e-40ad-82f7-7b4282f990c3"; // ПараметрОбластиВыражениеКомпоновкиДанных;Параметр области макета - выражние компоновки данных
constexpr auto GUID_555 = "a3920ae3-f7b2-49fc-ad0f-4fb3923aafd8"; // ПараметрыОбластиКомпоновкиДанных;Параметры области макета компоновки данных
constexpr auto GUID_556 = "cede2cfe-af5b-4dd4-99a5-46991c9a0459"; // ПараметрОбластиРасшифровкаКомпоновкиДанных;Параметр области макета - расшифровка компоновки данных
constexpr auto GUID_557 = "85f5a78f-f87e-4cd4-b30d-c80667a02f20"; // ВыражениеПоляПараметраОбластиРасшифровкаКомпоновкиДанных;Выражение поля параметра области макета - расшифровка компоновки данных
constexpr auto GUID_558 = "736c9009-4c5d-46dd-a18c-4a81a0f36d26"; // ВыраженияПолейПараметраОбластиРасшифровкаКомпоновкиДанных;Выражения полей параметра области макета - расшифровка компоновки данных
constexpr auto GUID_559 = "87824786-f040-4d35-ae9f-581437aa80c4"; // ОформлениеГруппировкиДиаграммыОбластиКомпоновкиДанных;Оформление группировки диаграммы компоновки данных
constexpr auto GUID_560 = "a9120dbe-71cf-4f29-9262-cfec53ba7311"; // ОформлениеРесурсаДиаграммыОбластиКомпоновкиДанных;Оформление ресурса диаграммы компоновки данных
constexpr auto GUID_561 = "cbbe2630-d40f-4eff-954d-81804eaaf302"; // ОформлениеДиаграммыОбластиКомпоновкиДанных;Оформление диаграммы компоновки данных
constexpr auto GUID_562 = "ac07acb4-cf99-4ca4-95be-4500352e059b"; // МакетОформленияКомпоновкиДанных;Макет оформления
constexpr auto GUID_563 = "6ece2d0a-bb07-46ee-83f2-ae4b0943dfac"; // ЭлементОбластиМакетаОформленияКомпоновкиДанных;Элемент области макета оформления
constexpr auto GUID_564 = "a862465a-5e00-4432-b3e8-ce66a1c42232"; // ОбластьМакетаОформленияКомпоновкиДанных;Область макета оформления
constexpr auto GUID_565 = "131453ad-cb87-4303-80e9-7a12abfa9f35"; // ЭлементБиблиотекиМакетовОформленияКомпоновкиДанных;Элемент библиотеки макетов оформления компоновки данных
constexpr auto GUID_566 = "c231d4e8-e000-4b39-b8c8-b7f043b58c98"; // ОбработкаРасшифровкиКомпоновкиДанных;Обработка расшифровки компноновки данных
constexpr auto GUID_567 = "ab65b970-c690-4365-ab98-441c5ca59a03"; // ДанныеРасшифровкиКомпоновкиДанных;Информация расшифровки компноновки данных
constexpr auto GUID_568 = "98808cff-97b7-4e94-af74-2c385073a6f3"; // ИдентификаторРасшифровкиКомпоновкиДанных;Идентификатор расшифровки компноновки данных
constexpr auto GUID_569 = "e72ccf3d-fe08-46a0-a4d6-7a9b2f2364a9"; // ЗначениеПоляРасшифровкиКомпоновкиДанных;Значение поля расшифровки компноновки данных
constexpr auto GUID_570 = "b3ac1337-58d4-4500-9a7a-6716b555efac"; // ЗначенияПолейРасшифровкиКомпоновкиДанных;Значения полей расшифровки компноновки данных
constexpr auto GUID_571 = "1f20f3be-5538-4e47-8342-06d2d1e58802"; // ЭлементРасшифровкиКомпоновкиДанныхПоля;Элемент расшифровки компноновки данных - поля
constexpr auto GUID_572 = "16d7833e-ae75-4987-97c0-8077da08e220"; // ЭлементРасшифровкиКомпоновкиДанныхГруппировка;Элемент расшифровки компноновки данных - группировка
constexpr auto GUID_573 = "04b8e78d-3865-42db-a66e-0fd42e473ac5"; // ЭлементыРасшифровкиКомпоновкиДанных;Элементы расшифровки компноновки данных
constexpr auto GUID_574 = "2623cb24-984d-4ad4-a76a-a36463315e64"; // РольПоляНабораДанныхКомпоновкиДанных;Роль поля компоновки данных
constexpr auto GUID_575 = "4810b03e-5987-4960-96ec-be5df06a9b7e"; // ВыражениеУпорядочиванияКомпоновкиДанных;Выражение упорядочивания компоновки данных
constexpr auto GUID_576 = "d2143020-c9a8-4fde-89e1-5110137d9e30"; // ВыраженияУпорядочиванияКомпоновкиДанных;Выражения упорядочивания компоновки данных
constexpr auto GUID_577 = "913e8016-6e90-47a0-b2a0-4513f4edad61"; // ПолеКомпоновкиДанных;Поле компоновки данных
constexpr auto GUID_578 = "f2a66d01-96cb-4c2b-8cf2-f78f28dd285c"; // ПараметрКомпоновкиДанных;Параметр компоновки данных
constexpr auto GUID_579 = "e25a705b-ee1b-45e3-992e-ba5bcaef88c5"; // КоллекцияДоступныхПараметровКомпоновкиДанных;Коллекция доступных параметров компоновки данных
constexpr auto GUID_580 = "0ee1b62c-1f5a-42bf-bc79-a32f403ba00b"; // ДоступныйПараметрКомпоновкиДанных;Доступный параметр компоновки данных
constexpr auto GUID_581 = "3c6c7d50-2a16-41d7-9780-e00242084291"; // ДоступныеПараметрыКомпоновкиДанных;Доступные параметры компоновки данных
constexpr auto GUID_582 = "d8ef3801-2bad-441c-950a-2c085cc70a54"; // КоллекцияЗначенийПараметровКомпоновкиДанных;Коллекция значений параметров компоновки данных
constexpr auto GUID_583 = "710a7ca0-76de-4ad0-a0cc-dc8953bf4257"; // ЗначениеПараметраКомпоновкиДанных;Значение параметра компоновки данных
constexpr auto GUID_584 = "cace6510-b459-41cb-bdfd-b7c729442a9a"; // ОформлениеКомпоновкиДанных;Оформление
constexpr auto GUID_585 = "ae4e5f60-1ae2-4a69-b2b4-0d9aa8afb02f"; // СравнениеЗначений;СравнениеЗначений
constexpr auto GUID_586 = "37c9f8fc-89c2-4dd2-9cae-0eb2b98344c9"; // ГенераторСлучайныхЧисел;ГенераторСлучайныхЧисел
constexpr auto GUID_587 = "b51784f1-e87e-4bcf-ac6f-aaa1227437ea"; // Диапазон;Диапазон
constexpr auto GUID_588 = "9a2caeac-2e86-46a3-b046-4ffd114fc9e3"; // БлокировкаДанных;Блокировка данных
constexpr auto GUID_589 = "f20c5f19-2fb9-441c-9d4e-bd3dd208333d"; // ЭлементБлокировкиДанных;Элемент блокировки данных
constexpr auto GUID_590 = "1914bfc9-3824-43ad-9d12-30ec655299e6"; // ПолеЭлементаБлокировкиДанных;Поле элемента блокировки данных
constexpr auto GUID_591 = "5c22ec1c-a7b2-4bd9-8d73-d7ef2930983e"; // ПоляЭлементаБлокировкиДанных;Поля элемента блокировки данных
constexpr auto GUID_592 = "dde97c1d-b568-4649-a443-506b6207ac2e"; // СписокПолнотекстовогоПоиска;Список полнотекстового поиска
constexpr auto GUID_593 = "2c3dc6a9-b69c-4b90-9964-a0a5432c86aa"; // ЭлементСпискаПолнотекстовогоПоиска;Результат поиска
constexpr auto GUID_594 = "9f98209e-d416-45cd-a667-9edcc975150d"; // БлокировкаУстановкиСоединений;Блокировка установки соединений
constexpr auto GUID_595 = "55725d1f-c329-44c6-a424-7d51e8ece598"; // ОбщийМодуль;Общий Модуль
constexpr auto GUID_596 = "7807407a-5a9e-4807-b889-ea17edbb6c1a"; // ФоновоеЗадание;Фоновое задание
constexpr auto GUID_597 = "e45c2d0f-384f-4602-bb40-89f7e4824f5f"; // РегламентноеЗадание;Регламентное задание
constexpr auto GUID_598 = "28193e3e-c6a3-4d30-b4e7-9f8ff23b3931"; // РасписаниеРегламентногоЗадания;Расписание задания
constexpr auto GUID_599 = "5b43ae5b-cefc-46c8-8742-8c4291997f6c"; // ДиалогРасписанияРегламентногоЗадания;Диалог редактирования расписания
constexpr auto GUID_600 = "51e7a0d2-530b-11d4-b98a-008048da3034"; // Массив;Массив
constexpr auto GUID_601 = "3d48feae-a9c6-4c5a-a099-9eb6477630c6"; // Соответствие;Соответствие
constexpr auto GUID_602 = "4772b3b4-f4a3-49c0-a1a5-8cb5961511a3"; // СписокЗначений;Список значений
constexpr auto GUID_603 = "c27d99e0-2f53-11d5-a3be-0050bae0a776"; // ЭлементСпискаЗначений;Элемент списка значений
constexpr auto GUID_604 = "acf6192e-81ca-46ef-93a6-5a6968b78663"; // ТаблицаЗначений;Таблица значений
constexpr auto GUID_605 = "ac6bbae9-9a0f-4ec9-be2a-d9b1caa4eb36"; // СтрокаТаблицыЗначений;Строка таблицы значений
constexpr auto GUID_606 = "0e2c7b45-ad6d-4ebe-8c9b-358d42ab5002"; // КоллекцияКолонокТаблицыЗначений;Коллекция колонок таблицы значений
constexpr auto GUID_607 = "e162969e-36e8-44f4-a5fd-fa2bf170a4f5"; // КолонкаТаблицыЗначений;Колонка таблицы значений
constexpr auto GUID_608 = "3a461c5c-0a17-430a-ae05-90890129a7da"; // ИндексыКоллекции;Коллекция индексов таблицы значений
constexpr auto GUID_609 = "4523f487-9cd3-4779-89f5-92023e88037b"; // ИндексКоллекции;Индекс таблицы значений
constexpr auto GUID_610 = "e603c0f2-92fb-4d47-8f38-a44a381cf235"; // ДеревоЗначений;Дерево значений
constexpr auto GUID_611 = "f3778173-89f2-41c0-82e9-3066d5cede35"; // КоллекцияСтрокДереваЗначений;Коллекция строк дерева значений
constexpr auto GUID_612 = "3caee34f-7427-4838-af4b-e42add83dccd"; // СтрокаДереваЗначений;Строка дерева значений
constexpr auto GUID_613 = "1d2194c8-d6ab-40af-b67d-01b0d7c07082"; // КоллекцияКолонокДереваЗначений;Коллекция колонок дерева значений
constexpr auto GUID_614 = "7f5d723a-cf83-4f14-8b27-68053e097304"; // КолонкаДереваЗначений;Колонка дерева значений
constexpr auto GUID_615 = "5e450ae7-6cba-40da-a0bf-6cd3c321bd04"; // COMSafeArray;COMSafeArray
constexpr auto GUID_616 = "850afa6f-5244-482f-9729-d78ec65ff607"; // КлючИЗначение;Ключ и значение
constexpr auto GUID_617 = "4500381b-db30-4a10-9db4-990038032acf"; // ФиксированныйМассив;Фиксированный массив
constexpr auto GUID_618 = "babe83c5-d020-47ee-8c68-755beb6273e2"; // ИзменениеРазмераОкна;ИзменениеРазмераОкна
constexpr auto GUID_619 = "327e7bc0-5825-4312-b47f-e1f0f414708d"; // ИзменениеСпособаОтображенияОкна;ИзменениеСпособаОтображенияОкна
constexpr auto GUID_620 = "74c51f56-5a37-4917-a0c3-3fa9be38d100"; // Панель;Панель
constexpr auto GUID_621 = "7b483b17-cf2f-48ef-ab68-b43c80ddc91f"; // ТипПоведенияКлавишиEnter;ТипПоведенияКлавишиEnter
constexpr auto GUID_622 = "91ab652c-c472-48a7-a164-9ad596b1d26c"; // ВариантПоложенияОкна;ВариантПоложенияОкна
constexpr auto GUID_623 = "7fb61030-459c-4872-babb-868954e2dc00"; // ВариантПрикрепленияОкна;ВариантПрикрепленияОкна
constexpr auto GUID_624 = "4275ad46-b1f0-45f6-839e-0a215239af8a"; // ВариантСостоянияОкна;ВариантСостоянияОкна
constexpr auto GUID_625 = "db1aed9a-b7f9-406d-abc9-b244805cea51"; // ВариантСпособаОтображенияОкна;ВариантСпособаОтображенияОкна
constexpr auto GUID_626 = "a908adf1-b1ea-4ccd-91f5-4c63c234dad6"; // ПолеВвода;Поле ввода
constexpr auto GUID_627 = "74007e6f-1320-4e1c-9bc9-b6fc1c2a2449"; // ЭлементыФормы;Элементы формы
constexpr auto GUID_628 = "4559214f-e349-4fc1-98aa-f3bedd3c7484"; // ПолеКалендаря;Календарь
constexpr auto GUID_629 = "61be9d82-54bc-484b-92b3-0dab27dc9f51"; // КоллекцияВыделенныхДат;Коллекция выделенных дат
constexpr auto GUID_630 = "27eb6a9a-f297-45a5-a810-44bdbed8fafc"; // ОформлениеПериода;Оформление периода
constexpr auto GUID_631 = "864bdb59-6541-4bc4-8740-0a50a354a672"; // КоллекцияОформленийДат;Коллекция оформлений дат
constexpr auto GUID_632 = "746befce-d46e-4106-a1aa-c8e6b2edc405"; // ОформлениеДаты;Оформление даты
constexpr auto GUID_633 = "f2ef4ea6-de5e-48eb-9dc5-4e4a77579fa6"; // Кнопка;Кнопка
constexpr auto GUID_634 = "69cf4251-8759-11d5-bf7e-0050bae2bc79"; // СочетаниеКлавиш;Сочетание клавиш
constexpr auto GUID_635 = "7783f716-79fb-446d-9aae-94ba2f2e3957"; // КоманднаяПанель;Командная панель
constexpr auto GUID_636 = "9f422bf8-0edb-4f05-8d00-4dea9ed13c82"; // КнопкиКоманднойПанели;Кнопки командной панели
constexpr auto GUID_637 = "365b8b83-672d-4c9f-b2d7-5d8331db6c7c"; // КнопкаКоманднойПанели;Кнопка командной панели
constexpr auto GUID_638 = "6eb4b32a-c85d-4073-a1b5-7d82cb459b38"; // Действие;Действие
constexpr auto GUID_639 = "7b93bf11-27eb-4de2-b379-2b1d3db99496"; // Надпись;Надпись
constexpr auto GUID_640 = "c40c10e3-3a76-4f9a-86cd-9334dbe02cce"; // ПоложениеКартинкиНадписи;ПоложениеКартинкиНадписи
constexpr auto GUID_641 = "6988fc93-faf1-4aa8-bba9-74b6eb7816b4"; // ПеречислениеПоложениеКартинкиНадписи;ПеречислениеПоложениеКартинкиНадписи
constexpr auto GUID_642 = "8ddcb88c-7461-11d5-a3be-0050bae0a776"; // ОтображениеЗакладок;ОтображениеЗакладок
constexpr auto GUID_643 = "8ddcb88e-7461-11d5-a3be-0050bae0a776"; // ПеречислениеОтображениеЗакладок;ПеречислениеОтображениеЗакладок
constexpr auto GUID_644 = "7557dc83-bf96-434b-8540-2244e2f7a70c"; // ПоложениеКартинкиПанели;ПоложениеКартинкиПанели
constexpr auto GUID_645 = "7557dc83-bf96-434b-8540-2244e2f7a70e"; // ПеречислениеПоложениеКартинкиПанели;ПеречислениеПоложениеКартинкиПанели
constexpr auto GUID_646 = "5c561aeb-19a6-45d6-a75a-88d1471c714f"; // СтраницыПанели;Страницы панели
constexpr auto GUID_647 = "aa6b058c-596f-4475-ac7d-e202dd4791cf"; // СтраницаПанели;Страница панели
constexpr auto GUID_648 = "9a40851c-b55d-4d3f-8093-f6fdd9a36d7b"; // Переключатель;Переключатель
constexpr auto GUID_649 = "8503ae00-6a4b-11d5-a3be-0050bae0a776"; // ПоложениеЗаголовка;ПоложениеЗаголовка
constexpr auto GUID_650 = "8503ae02-6a4b-11d5-a3be-0050bae0a776"; // ПеречислениеПоложениеЗаголовка;ПеречислениеПоложениеЗаголовка
constexpr auto GUID_651 = "bb5c71e1-e0ec-469b-9f8e-c4840302563f"; // ПолеТабличногоДокумента;Поле табличного документа
constexpr auto GUID_652 = "26871708-5c7e-4dae-aac2-d5aad3421694"; // ПолеHTMLДокумента;ПолеHTMLДокумента
constexpr auto GUID_653 = "96e5adf8-2bd4-429a-a240-50639de0e7e7"; // ПолеТекстовогоДокумента;Поле текстового документа
constexpr auto GUID_654 = "cabdf819-0787-42b2-994c-878708ec9043"; // РежимВыбораНезаполненного;РежимВыбораНезаполненного
constexpr auto GUID_655 = "91313034-b0ed-43f3-8de6-2b511ea34cbc"; // ПеречислениеРежимВыбораНезаполненного;ПеречислениеРежимВыбораНезаполненного
constexpr auto GUID_656 = "e0a7c73e-0700-4a30-88c9-d780b524de40"; // ПолеВыбора;Поле выбора
constexpr auto GUID_657 = "4d890532-809a-4fd6-92c8-097a56f02970"; // ПолеСписка;Поле списка
constexpr auto GUID_658 = "fda42872-4acd-4382-bcfb-b330f5240be2"; // ПолеКартинки;Поле картинки
constexpr auto GUID_659 = "e45646e9-f770-4072-b355-4a4160172810"; // ПолосаРегулирования;Полоса регулирования
constexpr auto GUID_660 = "8fdb3c9a-bbbe-48a7-8546-399d030da8d5"; // Разделитель;Разделитель
constexpr auto GUID_661 = "5bda1be6-7c2a-47ba-a045-af077adb604e"; // РамкаГруппы;Рамка группы
constexpr auto GUID_662 = "75746124-44d6-4292-8887-ed80e2aada87"; // ТабличноеПоле;Табличное поле
constexpr auto GUID_663 = "3eb1265c-2c25-4920-aeb1-417a266a149c"; // НачальноеОтображениеДерева;НачальноеОтображениеДерева
constexpr auto GUID_664 = "b28e34c4-8eda-441f-972a-089186dba838"; // ПеречислениеНачальноеОтображениеДерева;ПеречислениеНачальноеОтображениеДерева
constexpr auto GUID_665 = "bf268307-cc35-410b-9d53-209362f2a5bf"; // НачальноеОтображениеСписка;НачальноеОтображениеСписка
constexpr auto GUID_666 = "29c3a8b1-2ab2-461d-97be-03fd57ebb46e"; // ПеречислениеНачальноеОтображениеСписка;ПеречислениеНачальноеОтображениеСписка
constexpr auto GUID_667 = "9c677fc7-d57e-4911-a91f-89afe97b1205"; // ОформлениеСтроки;Оформление строки
constexpr auto GUID_668 = "01fbaa72-c9fd-44f8-908e-743d0316cd66"; // КолонкиТабличногоПоля;Колонки табличного поля
constexpr auto GUID_669 = "8ad0e432-0e08-4cc8-bf79-6393d45ecc9d"; // КолонкаТабличногоПоля;Колонка табличного поля
constexpr auto GUID_670 = "687066dd-c810-405d-830e-952d7bc113f8"; // ВыделенныеСтрокиТабличногоПоля;Выбранные строки табличного поля
constexpr auto GUID_671 = "00d71766-cb6b-4db0-8f36-c19bf11b6461"; // ОформленияСтрок;Оформления строк табличного поля
constexpr auto GUID_672 = "cae69570-4484-486a-94a1-7df712940af3"; // ОформлениеЯчейки;Оформление ячейки
constexpr auto GUID_673 = "306e7a9f-1509-46fa-bf13-569eb1385cc2"; // Флажок;Флажок
constexpr auto GUID_674 = "c3be2da9-8938-4990-b8f1-a59a651b53f2"; // ПолеГрафическойСхемы;Поле графической схемы
constexpr auto GUID_675 = "e5ec2236-071f-447e-bd7e-53b37c4b1df1"; // ПоказываемаяОбластьГеографическойСхемы;Показываемая область географической схемы
constexpr auto GUID_676 = "1f881926-937a-422c-9c1e-0a89762dd203"; // ПолеГеографическойСхемы;Поле географической схемы
constexpr auto GUID_677 = "4c26177d-ef7c-4ed4-b5bd-e2cc7b517440"; // ДиалогВыбораЦвета;ДиалогВыбораЦвета
constexpr auto GUID_678 = "2f2a0434-0ea1-4756-83d9-09d84d3be327"; // ДиалогВыбораШрифта;ДиалогВыбораШрифта
constexpr auto GUID_679 = "69cf4252-8759-11d5-bf7e-0050bae2bc79"; // Клавиша;Клавиша
constexpr auto GUID_680 = "69cf4254-8759-11d5-bf7e-0050bae2bc79"; // ПеречислениеКлавиша;ПеречислениеКлавиша
constexpr auto GUID_681 = "21f9b4b6-d815-4003-ac52-c3a987573784"; // ПараметрыПеретаскивания;Параметры перетаскивания
constexpr auto GUID_682 = "53257c20-d2a5-11d5-a3c1-0050bae0a776"; // ЭлементУправленияИнтерфейсом;Элемент управления интерфейсом
constexpr auto GUID_683 = "adcf0baa-6ae4-4865-827e-01f4309f60b8"; // МенеджерВременныхТаблиц;Менеджер временных таблиц
constexpr auto GUID_684 = "0f725605-ea6e-420c-8968-a82dbfcd51cd"; // РезультатЗапроса;Результат запроса
constexpr auto GUID_685 = "ed7a9bb8-f9e7-4c56-a8c6-d4523bdec998"; // ВыборкаИзРезультатаЗапроса;Выборка из результата запроса
constexpr auto GUID_686 = "431f9e28-40cb-4e59-bfa8-3e6a38a52934"; // КоллекцияКолонокРезультатаЗапроса;Коллекция колонок результата запроса
constexpr auto GUID_687 = "9a0cfb52-e77c-49fa-acdf-226348db7fef"; // КолонкаРезультатаЗапроса;Колонка результата запроса
constexpr auto GUID_688 = "3e417814-c44e-4aff-bff4-3729b7b87952"; // КонструкторЗапроса;Конструктор запроса
constexpr auto GUID_689 = "8008c203-3735-4462-8d88-5e4bf06737f9"; // ОписаниеПараметраЗапроса;Параметр запроса
constexpr auto GUID_690 = "0fdfecbd-a26b-434f-a639-7820c9919b5d"; // ОписаниеПараметровЗапроса;Параметры запроса
constexpr auto GUID_691 = "5b2b819e-ebc7-4d0b-9af6-1d5e2c8cdb0c"; // МоментВремени;Момент времени
constexpr auto GUID_692 = "dcfc3784-a14f-4786-ac7b-c82db5ba275f"; // КонстантыНабор;Константы набор
constexpr auto GUID_693 = "b6cd02c9-a2f5-4f5b-8678-d62ef585dddc"; // НастройкаОтбора;Настройки отбора
constexpr auto GUID_694 = "a246df8a-68b3-43c2-9271-5081aac52701"; // НастройкаПорядка;НастройкаПорядка
constexpr auto GUID_695 = "adeb08a2-415c-11d6-b9d1-0050bae0a95d"; // ПеречислениеРежимАвтоВремя;ПеречислениеРежимАвтоВремя
constexpr auto GUID_696 = "86ee87bd-6635-418b-ad17-d42896a3d18c"; // КоллекцияДвижений;Коллекция движений
constexpr auto GUID_697 = "86afde75-445b-436b-8dc9-001c7608a172"; // ВариантыТочкиМаршрутаБизнесПроцесса;Варианты точки маршрута бизнес-процесса
constexpr auto GUID_698 = "64d9631a-3884-4483-b76a-24a0a1d4f48c"; // ВариантТочкиМаршрутаБизнесПроцесса;Вариант точки маршрута бизнес-процесса
constexpr auto GUID_699 = "7b045945-a3a2-4c1b-8981-804dd777381d"; // ЭлементФактическогоПериодаДействия;Элемент фактического периода действия
constexpr auto GUID_700 = "855b7988-cf4f-4c3d-ae6e-76a95aea9c59"; // ЭлементНастройкиОформления;Элемент настройки оформления
constexpr auto GUID_701 = "2f82c87b-0ca7-456d-b853-51bed6f08f90"; // НастройкаОформления;Настройка оформления
constexpr auto GUID_702 = "71a1ad90-d9cb-44d6-b5dd-81e24b3bf231"; // ЭлементУправленияНастройкойНастройкиОформления;Элемент управления настройкой настройки оформления
constexpr auto GUID_703 = "83ae9772-7cd8-415d-b2d5-7446f9bb5d47"; // НастройкаНастройкиОформления;Настройка настройки оформления
constexpr auto GUID_704 = "1b4d6a31-19db-452d-9c32-96d0495e24b5"; // ЭлементОбластиОформления;Элемент области оформления
constexpr auto GUID_705 = "287c6d39-f32c-4cc3-b973-8a57caadc645"; // ОбластьОформления;Область оформления
constexpr auto GUID_706 = "bcdd7920-74c2-4144-8f94-59a049f767bb"; // ЭлементУправленияНастройкойОбластиОформления;Элемент управления областью оформления
constexpr auto GUID_707 = "992d4a79-1124-4cc0-8601-6f5327a8dae4"; // НастройкаОбластиОформления;Настройка области оформления
constexpr auto GUID_708 = "4e1d8b2f-7936-4cf8-8f28-3856f37e76ed"; // ЭлементУсловногоОформления;Элемент условного оформления
constexpr auto GUID_709 = "e06b0394-0caa-459e-87b5-f121aa6ad7cd"; // ЭлементУправленияНастройкойУсловногоОформления;Элемент управления настройкой условного оформления
constexpr auto GUID_710 = "5dacdbdc-373d-4675-999f-3c601cd2f253"; // НастройкаУсловногоОформления;Настройка условного оформления
constexpr auto GUID_711 = "3bffcd36-90c6-4cac-958f-ee9b65288c98"; // ЭлементОтбора;Элемент отбора
constexpr auto GUID_712 = "4c4beaa0-efc3-45bf-8698-d7bd951f0fc7"; // ЭлементУправленияОтбором;Элемент управления отбором
constexpr auto GUID_713 = "7b17cf9a-7924-43f3-a2b0-25c566383147"; // ЭлементПорядка;Элемент порядка
constexpr auto GUID_714 = "ebb120b8-c62e-4555-9036-6a4087a94856"; // ЭлементУправленияПорядком;Элемент управления порядком
constexpr auto GUID_715 = "50741645-9ede-4b33-976f-ec179e324c83"; // НастройкаПериода;Настройка периода
constexpr auto GUID_716 = "759c8a9e-c4ab-4c96-99ae-0fe65695eb8c"; // ВариантПериода;ВариантПериода
constexpr auto GUID_717 = "e2c2f102-cb29-4cbe-a9c7-4c3bef7d6a7d"; // ПеречислениеВариантПериода;ПеречислениеВариантПериода
constexpr auto GUID_718 = "6733e851-ebd2-484a-acfc-6009b6d1ec2d"; // Граница;Граница
constexpr auto GUID_719 = "54482f42-e2b1-4ca7-8223-9959ab20c1f4"; // ВидГраницы;ВидГраницы
constexpr auto GUID_720 = "be0e91be-9984-4e23-8588-977d20c9cff0"; // ПеречислениеВидГраницы;ПеречислениеВидГраницы
constexpr auto GUID_721 = "99d350de-2de4-490d-9b01-53fdbfbebbe6"; // КолонкиСписка;Колонки списка
constexpr auto GUID_722 = "66d3e735-17b6-44e2-b499-2db791ff42a5"; // КолонкаСписка;Колонка списка
constexpr auto GUID_723 = "4d599114-9432-447f-ab67-2d9aafbce68e"; // ПоляНастройки;Коллекция полей
constexpr auto GUID_724 = "aad92bb0-9ded-4842-994d-df04e4a3daa9"; // ПолеНастройки;Поле
constexpr auto GUID_725 = "327ff937-2fb8-405b-9476-b732ac037b57"; // ПараметрыОбменаДанными;Параметры обмена данными
constexpr auto GUID_726 = "3f3b4576-c0ac-4541-b1e4-31206a7f2a8b"; // НаборУзлов;Коллекция узлов
constexpr auto GUID_727 = "6150bc2f-9f66-44ec-945e-d815a6378b26"; // УдалениеОбъекта;Удаление объекта
constexpr auto GUID_728 = "024e62d6-e6ac-4d91-a510-37b6cbfb3811"; // ТекущиеДанныеСписка;Текущие данные списка
constexpr auto GUID_729 = "d12693fe-e5f0-4c13-b47d-b38fdefdc415"; // КолонкаОписанияИсточникаДанных;Колонка описания источника данных
constexpr auto GUID_730 = "6d5c030f-aaba-4d9a-8cfa-797c8f7c6c89"; // КолонкиОписанияИсточникаДанных;Колонки описания источника данных
constexpr auto GUID_731 = "dfea241c-2a43-41a9-998c-1bd3a586b9dd"; // ОписаниеИсточникаДанных;Описание источника данных
constexpr auto GUID_732 = "2f4b2cea-29df-4520-9dd3-339cf46c7b19"; // ЗаписьСообщенияОбмена;Запись сообщения обмена данными
constexpr auto GUID_733 = "ccb02cbe-da12-4696-8e7f-5ee1cb551aff"; // ЧтениеСообщенияОбмена;Чтение сообщения обмена данными
constexpr auto GUID_734 = "5de78ba8-f39a-41ed-8906-3cc4e3b4a327"; // ВыборкаДанных;Выборка данных
constexpr auto GUID_735 = "0c658aad-04b2-4566-8693-b150b1d739d3"; // WebЦвета;Web цвета
constexpr auto GUID_736 = "9b0f03c1-a174-4ca9-b262-1c82d3ac94d1"; // WindowsЦвета;Windows цвета
constexpr auto GUID_737 = "0b2e254a-8ecf-415e-b79c-710dd87bfa3c"; // WindowsШрифты;Windows шрифты
constexpr auto GUID_738 = "7cc4f0d2-d935-42ff-a316-570f21cf2b1b"; // РамкиСтиля;Рамка
constexpr auto GUID_739 = "2d3f0556-fec0-46a6-9d74-83f8f85a7a72"; // Символы;Символы
constexpr auto GUID_740 = "2af71525-beff-4d37-afea-e841a60d8d33"; // ЦветаСтиля;Цвет
constexpr auto GUID_741 = "ef68c338-9b86-42a2-a3e0-c418acbe4ee4"; // ШрифтыСтиля;Шрифт
constexpr auto GUID_742 = "214b651c-315e-4f32-a567-d40e0ac7e85b"; // ВидПодписейКДиаграмме;ВидПодписейКДиаграмме
constexpr auto GUID_743 = "5f882339-25fa-4591-85b2-c32cbe761f81"; // ПеречислениеВидПодписейКДиаграмме;ПеречислениеВидПодписейКДиаграмме
constexpr auto GUID_744 = "1f4e5511-15d8-46c8-babb-644a2a684a3a"; // ОриентацияДиаграммы;ОриентацияДиаграммы
constexpr auto GUID_745 = "bb2d78e4-2e3c-4c5a-aa63-bbd10d188da8"; // ПеречислениеОриентацияДиаграммы;ПеречислениеОриентацияДиаграммы
constexpr auto GUID_746 = "fc55290c-df20-4c88-be54-7212a5c8f685"; // РежимПробеловДиаграммы;РежимПробеловДиаграммы
constexpr auto GUID_747 = "6188e6e2-9b9e-404b-a594-2f2548ac919f"; // ПеречислениеРежимПробеловДиаграммы;ПеречислениеРежимПробеловДиаграммы
constexpr auto GUID_748 = "d5819a92-a9cd-4075-90bc-6179cbb1caa6"; // ТипМаркераДиаграммы;ТипМаркераДиаграммы
constexpr auto GUID_749 = "1572fb1e-0651-40be-8d98-2daed6500591"; // ПеречислениеТипМаркераДиаграммы;ПеречислениеТипМаркераДиаграммы
constexpr auto GUID_750 = "fc86d767-22c2-4fa4-ad7d-7317295383f8"; // ТипЛинииДиаграммы;ТипЛинииДиаграммы
constexpr auto GUID_751 = "e48cee88-ba8c-4c95-b674-f984bca02029"; // ПеречислениеТипЛинииДиаграммы;ПеречислениеТипЛинииДиаграммы
constexpr auto GUID_752 = "7eef3d46-550e-49f7-9ffe-d7f9362fa8c6"; // ПоложениеПодписейКДиаграмме;ПоложениеПодписейКДиаграмме
constexpr auto GUID_753 = "3ef3038b-7fc3-416a-9116-2bfd40ea818e"; // ПеречислениеПоложениеПодписейКДиаграмме;ПеречислениеПоложениеПодписейКДиаграмме
constexpr auto GUID_754 = "f603a8fd-eb29-4b3a-8926-00dba3a72baa"; // ТипЕдиницыШкалыВремени;ТипЕдиницыШкалыВремени
constexpr auto GUID_755 = "ca8af4e2-3d15-4a08-ba38-de2ceed3c997"; // ПеречислениеТипЕдиницыШкалыВремени;ПеречислениеТипЕдиницыШкалыВремени
constexpr auto GUID_756 = "19a130b5-fb3b-440b-9af7-619b76a674b3"; // ПоложениеШкалыВремени;ПоложениеШкалыВремени
constexpr auto GUID_757 = "6449fde7-70a0-46c5-a62c-657c231d75da"; // ПеречислениеПоложениеШкалыВремени;ПеречислениеПоложениеШкалыВремени
constexpr auto GUID_758 = "f8ba7bcd-9b0d-42cf-a129-7586ee2c9a1f"; // ПоддержкаМасштабаДиаграммыГанта;ПоддержкаМасштабаДиаграммыГанта
constexpr auto GUID_759 = "95fe1e9d-9fe4-4744-8bc8-c8125b8a53d7"; // ПеречислениеПоддержкаМасштабаДиаграммыГанта;ПеречислениеПоддержкаМасштабаДиаграммыГанта
constexpr auto GUID_760 = "230ea4bd-c4f5-46fb-a665-7abbab9c9d3f"; // ФорматДняШкалыВремени;ФорматДняШкалыВремени
constexpr auto GUID_761 = "bba17f04-80b9-4230-bb04-e3295976b716"; // ПеречислениеФорматДняШкалыВремени;ПеречислениеФорматДняШкалыВремени
constexpr auto GUID_762 = "44ce89aa-91cf-4fd9-9639-c599e3ddd130"; // ОтображениеИнтервалаДиаграммыГанта;ОтображениеИнтервалаДиаграммыГанта
constexpr auto GUID_763 = "a92bf98b-e909-42a2-a563-ffc1ef0061c0"; // ПеречислениеОтображениеИнтервалаДиаграммыГанта;ПеречислениеОтображениеИнтервалаДиаграммыГанта
constexpr auto GUID_764 = "0f75cfc3-a764-4fe5-8217-ccb8a8843396"; // РастягиваниеПоВертикалиДиаграммыГанта;РастягиваниеПоВертикалиДиаграммыГанта
constexpr auto GUID_765 = "f41c9719-e825-460a-94be-d2e3ecaf9578"; // ПеречислениеРастягиваниеПоВертикалиДиаграммыГанта;ПеречислениеРастягиваниеПоВертикалиДиаграммыГанта
constexpr auto GUID_766 = "eceac06c-2427-4c48-905c-0ed63efb6c98"; // ОтображениеТекстаЗначенияДиаграммыГанта;ОтображениеТекстаЗначенияДиаграммыГанта
constexpr auto GUID_767 = "530f52ff-c835-473e-9338-f98ed4ddb15a"; // ПеречислениеОтображениеТекстаЗначенияДиаграммыГанта;ПеречислениеОтображениеТекстаЗначенияДиаграммыГанта
constexpr auto GUID_768 = "8a8342d7-8fea-4ab8-8ca6-e02e857a6dfd"; // ТипСвязиДиаграммыГанта;ТипСвязиДиаграммыГанта
constexpr auto GUID_769 = "30c52c9f-704e-4d27-bb18-1ee3dc8ab5ce"; // ПеречислениеТипСвязиДиаграммыГанта;ПеречислениеТипСвязиДиаграммыГанта
constexpr auto GUID_770 = "b0b4f3a1-27f3-474f-bf59-ada9fcdc787e"; // ОриентацияДендрограммы;ОриентацияДендрограммы
constexpr auto GUID_771 = "8458adc2-9e60-437d-93d7-b7b33dd517d1"; // ПеречислениеОриентацияДендрограммы;ПеречислениеОриентацияДендрограммы
constexpr auto GUID_772 = "1fea578c-2897-4a9a-9155-b9b01b608715"; // ПоддержкаМасштабаДендрограммы;ПоддержкаМасштабаДендрограммы
constexpr auto GUID_773 = "93c5abab-d1a7-44aa-87b0-c00c74ff2457"; // ПеречислениеПоддержкаМасштабаДендрограммы;ПеречислениеПоддержкаМасштабаДендрограммы
constexpr auto GUID_774 = "e1eb7024-e782-4212-a176-1cb415727a2a"; // ОтображениеЗначенийСводнойДиаграммы;ОтображениеЗначенийСводнойДиаграммы
constexpr auto GUID_775 = "51424f39-035e-4938-b86a-51233d79019a"; // ПеречислениеОтображениеЗначенийСводнойДиаграммы;ПеречислениеОтображениеЗначенийСводнойДиаграммы
constexpr auto GUID_776 = "a7e33104-ad1c-4648-b142-56107d8d2f38"; // ПоддержкаМасштабаСводнойДиаграммы;ПоддержкаМасштабаСводнойДиаграммы
constexpr auto GUID_777 = "5ebbc9e8-94e9-4ce0-8414-1ab4a1f6d134"; // ПеречислениеПоддержкаМасштабаСводнойДиаграммы;ПеречислениеПоддержкаМасштабаСводнойДиаграммы
constexpr auto GUID_778 = "2718a8b3-4893-428b-a21a-60135961f7ae"; // ОриентацияМетокСводнойДиаграммы;ОриентацияМетокСводнойДиаграммы
constexpr auto GUID_779 = "0781f3d6-2a61-4a35-85cc-e1001bbc3be1"; // ПеречислениеОриентацияМетокСводнойДиаграммы;ПеречислениеОриентацияМетокСводнойДиаграммы
constexpr auto GUID_780 = "8450265a-184e-4a6e-9ae7-b030eb50e4d9"; // ТипЛинииГеографическойСхемы;ТипЛинииГеографическойСхемы
constexpr auto GUID_781 = "e505675f-1d8c-482b-a475-866e1c0c27da"; // ПеречислениеТипЛинииГеографическойСхемы;ПеречислениеТипЛинииГеографическойСхемы
constexpr auto GUID_782 = "63cba583-b1af-4abf-a595-a3a287409d16"; // ТипОтображенияТочечногоОбъектаГеографическойСхемы;ТипОтображенияТочечногоОбъектаГеографическойСхемы
constexpr auto GUID_783 = "0222dab6-08a7-4f62-be6a-bbee300c2452"; // ПеречислениеТипОтображенияТочечногоОбъектаГеографическойСхемы;ПеречислениеТипОтображенияТочечногоОбъектаГеографическойСхемы
constexpr auto GUID_784 = "ac713a60-3162-47e8-a185-37a49d6dfc3e"; // ТипОтображенияСерииСлояГеографическойСхемы;ТипОтображенияСерииСлояГеографическойСхемы
constexpr auto GUID_785 = "11a8a987-d5e6-49c4-813f-6eff8337eb02"; // ПеречислениеТипОтображенияСерииСлояГеографическойСхемы;ПеречислениеТипОтображенияСерииСлояГеографическойСхемы
constexpr auto GUID_786 = "1a6f0f65-e117-406c-9089-587847a9835a"; // ТипОрганизацииИсточникаДанныхГеографическойСхемы;ТипОрганизацииИсточникаДанныхГеографическойСхемы
constexpr auto GUID_787 = "0bdcfc5d-81c8-4d11-8bc1-921338926248"; // ПеречислениеТипОрганизацииИсточникаДанныхГеографическойСхемы;ПеречислениеТипОрганизацииИсточникаДанныхГеографическойСхемы
constexpr auto GUID_788 = "1ee69261-5e67-4bbb-9fb4-5f852f96ac12"; // ПоложениеОпорнойТочкиОтрисовки;ПоложениеОпорнойТочкиОтрисовки
constexpr auto GUID_789 = "420dd864-ca86-4f6e-9e48-d5d3155f790c"; // ПеречислениеПоложениеОпорнойТочкиОтрисовки;ПеречислениеПоложениеОпорнойТочкиОтрисовки
constexpr auto GUID_790 = "f67e79e3-08fa-4d48-b880-598c11a7d65d"; // ТипМаркераГеографическойСхемы;ТипМаркераГеографическойСхемы
constexpr auto GUID_791 = "9c615ceb-3aa6-481b-a646-23b6042e691f"; // ПеречислениеТипМаркераГеографическойСхемы;ПеречислениеТипМаркераГеографическойСхемы
constexpr auto GUID_792 = "12682e50-f965-4d8e-80bc-bb1fd13045e8"; // РежимОтображенияГеографическойСхемы;РежимОтображенияГеографическойСхемы
constexpr auto GUID_793 = "33ff5cff-1bd9-43e4-a7a5-a65d567b28df"; // ПеречислениеРежимОтображенияГеографическойСхемы;ПеречислениеРежимОтображенияГеографическойСхемы
constexpr auto GUID_794 = "74124d00-4a48-4a78-9f9a-cccd6a1bf1df"; // ТипИмпортаСерийСлояГеографическойСхемы;ТипИмпортаСерийСлояГеографическойСхемы
constexpr auto GUID_795 = "6125386f-d6d6-4728-98db-d431c971ed2e"; // ПеречислениеТипИмпортаСерийСлояГеографическойСхемы;ПеречислениеТипИмпортаСерийСлояГеографическойСхемы
constexpr auto GUID_796 = "5548088f-c4a5-4c61-ae51-10db015200db"; // ТипПоискаОбъектовГеографическойСхемы;ТипПоискаОбъектовГеографическойСхемы
constexpr auto GUID_797 = "27ba9ec7-6a5e-4200-a8ae-51b8699bdeaf"; // ПеречислениеТипПоискаОбъектовГеографическойСхемы;ПеречислениеТипПоискаОбъектовГеографическойСхемы
constexpr auto GUID_798 = "dc1d7db0-e582-4a4c-94dc-5f4d9f1269cc"; // ТипОтображенияШкалыЭлементаЛегендыГеографическойСхемы;ТипОтображенияШкалыЭлементаЛегендыГеографическойСхемы
constexpr auto GUID_799 = "e0df413b-406d-4812-b55d-f77d179015cb"; // ПеречислениеТипОтображенияШкалыЭлементаЛегендыГеографическойСхемы;ПеречислениеТипОтображенияШкалыЭлементаЛегендыГеографическойСхемы
constexpr auto GUID_800 = "92e665c7-2adb-440e-9573-6a75da6ab70c"; // РежимОтображенияЗначенийСерии;РежимОтображенияЗначенийСерии
constexpr auto GUID_801 = "8050f5bd-1eff-4115-b582-e82e04aeb94c"; // ПеречислениеРежимОтображенияЗначенийСерии;ПеречислениеРежимОтображенияЗначенийСерии
constexpr auto GUID_802 = "b0711fb3-32c9-4c3e-946e-45eaaae778ec"; // ТипПроекцииГеографическойСхемы;ТипПроекцииГеографическойСхемы
constexpr auto GUID_803 = "17c46221-2e24-4a99-a8bf-04d639147108"; // ПеречислениеТипПроекцииГеографическойСхемы;ПеречислениеТипПроекцииГеографическойСхемы
constexpr auto GUID_804 = "c296a176-15e2-4298-ba34-ae95592d9ff0"; // ПеречислениеВариантСостоянияОкна;ПеречислениеВариантСостоянияОкна
constexpr auto GUID_805 = "f5f75aec-b814-477e-b158-b168c3631c12"; // ПеречислениеВариантСпособаОтображенияОкна;ПеречислениеВариантСпособаОтображенияОкна
constexpr auto GUID_806 = "7a856d4f-92ef-4702-86c1-ced4014a709a"; // ПеречислениеВариантПоложенияОкна;ПеречислениеВариантПоложенияОкна
constexpr auto GUID_807 = "8beee433-5f20-40a2-b2ea-e96f3a9de57e"; // ПеречислениеВариантПрикрепленияОкна;ПеречислениеВариантПрикрепленияОкна
constexpr auto GUID_808 = "6433cfa5-b687-4218-90db-d9f08ebf738b"; // ВариантПроверкиОтображенияНовойСтроки;ВариантПроверкиОтображенияНовойСтроки
constexpr auto GUID_809 = "36227750-3584-4384-af86-02ade7905a6b"; // ПеречислениеВариантПроверкиОтображенияНовойСтроки;ПеречислениеВариантПроверкиОтображенияНовойСтроки
constexpr auto GUID_810 = "f8d63816-a03b-455e-b416-f66dcfd37c41"; // ВыравниваниеКнопокКоманднойПанели;ВыравниваниеКнопокКоманднойПанели
constexpr auto GUID_811 = "1a655298-f211-4fcc-9340-4e9bf72751b4"; // ПеречислениеВыравниваниеКнопокКоманднойПанели;ПеречислениеВыравниваниеКнопокКоманднойПанели
constexpr auto GUID_812 = "aaad93fe-9a10-4273-b034-41e481dc59d5"; // ДействиеПеретаскивания;ДействиеПеретаскивания
constexpr auto GUID_813 = "d9021b7f-680c-4b18-a938-b03921aea781"; // ПеречислениеДействиеПеретаскивания;ПеречислениеДействиеПеретаскивания
constexpr auto GUID_814 = "4ed4ef49-1dec-487f-960d-fa3ee1beaba0"; // ДопустимыеДействияПеретаскивания;ДопустимыеДействияПеретаскивания
constexpr auto GUID_815 = "265d2e4b-56c0-4405-8fcf-998b2a863868"; // ПеречислениеДопустимыеДействияПеретаскивания;ПеречислениеДопустимыеДействияПеретаскивания
constexpr auto GUID_816 = "2b66b5d3-be3e-4759-9290-fe83f6a06a27"; // ГраницаЭлементаУправления;ГраницаЭлементаУправления
constexpr auto GUID_817 = "d4736e9f-c52f-4c1b-bef6-4eec3b6712d8"; // ПеречислениеГраницаЭлементаУправления;ПеречислениеГраницаЭлементаУправления
constexpr auto GUID_818 = "42a5e9a3-09cc-4250-98f5-e145961f593e"; // ИзменениеРазмераКолонки;ИзменениеРазмераКолонки
constexpr auto GUID_819 = "e1e2bcb1-b842-48a1-a76a-e8d2b2a3fff6"; // ПеречислениеИзменениеРазмераКолонки;ПеречислениеИзменениеРазмераКолонки
constexpr auto GUID_820 = "f21f2f25-0e6c-44f0-8484-fbc39f98180d"; // ПеречислениеИзменениеРазмераОкна;ПеречислениеИзменениеРазмераОкна
constexpr auto GUID_821 = "46ed40ff-31d3-4cd1-a1f6-fae7ad3ff726"; // ПеречислениеИзменениеСпособаОтображенияОкна;ПеречислениеИзменениеСпособаОтображенияОкна
constexpr auto GUID_822 = "16ea9312-efce-4546-9ed1-ecddc88ef3bb"; // ИспользованиеВывода;ИспользованиеВывода
constexpr auto GUID_823 = "8c83bd34-b6dd-4054-8e3a-addc89dba898"; // ПеречислениеИспользованиеВывода;ПеречислениеИспользованиеВывода
constexpr auto GUID_824 = "57f7dec0-6caa-11d5-a3be-0050bae0a776"; // ИспользованиеПолосыПрокрутки;ИспользованиеПолосыПрокрутки
constexpr auto GUID_825 = "57f7dec2-6caa-11d5-a3be-0050bae0a776"; // ПеречислениеИспользованиеПолосыПрокрутки;ПеречислениеИспользованиеПолосыПрокрутки
constexpr auto GUID_826 = "66e6f37d-035f-4283-8780-4337969c540e"; // ИспользованиеРежимаМеню;ИспользованиеРежимаМеню
constexpr auto GUID_827 = "66e6f37f-035f-4283-8780-4337969c540e"; // ПеречислениеИспользованиеРежимаМеню;ПеречислениеИспользованиеРежимаМеню
constexpr auto GUID_828 = "40bf9ca4-be06-4fe0-95f6-a1797e4021ff"; // ОтображениеКнопкиКоманднойПанели;ОтображениеКнопкиКоманднойПанели
constexpr auto GUID_829 = "bd60c810-01d7-427d-a93c-70aeab4fdfd9"; // ПеречислениеОтображениеКнопкиКоманднойПанели;ПеречислениеОтображениеКнопкиКоманднойПанели
constexpr auto GUID_830 = "8ddcb892-7461-11d5-a3be-0050bae0a776"; // ОтображениеРазметкиПолосыРегулирования;ОтображениеРазметкиПолосыРегулирования
constexpr auto GUID_831 = "8ddcb894-7461-11d5-a3be-0050bae0a776"; // ПеречислениеОтображениеРазметкиПолосыРегулирования;ПеречислениеОтображениеРазметкиПолосыРегулирования
constexpr auto GUID_832 = "003ee5c0-65ac-11d5-a3be-0050bae0a776"; // ПоложениеКартинкиКнопки;ПоложениеКартинкиКнопки
constexpr auto GUID_833 = "003ee5c2-65ac-11d5-a3be-0050bae0a776"; // ПеречислениеПоложениеКартинкиКнопки;ПеречислениеПоложениеКартинкиКнопки
constexpr auto GUID_834 = "dcdfce56-e1b1-4a4e-bb83-1c4b3b62d76c"; // ПоложениеКартинкиЭлементаГрафическойСхемы;ПоложениеКартинкиЭлементаГрафическойСхемы
constexpr auto GUID_835 = "dcdfce56-e1b1-4a4e-bb83-1c4b3b62d76e"; // ПеречислениеПоложениеКартинкиЭлементаГрафическойСхемы;ПеречислениеПоложениеКартинкиЭлементаГрафическойСхемы
constexpr auto GUID_836 = "4f43ea59-7661-45b4-8ea7-6c88ff315e1d"; // ПоложениеКолонки;ПоложениеКолонки
constexpr auto GUID_837 = "dec3c35a-d779-4228-96bb-fc63fa6d87ed"; // ПеречислениеПоложениеКолонки;ПеречислениеПоложениеКолонки
constexpr auto GUID_838 = "c48bcf98-d6fb-4dd5-96f4-76c0e770f827"; // ПорядокКнопокКоманднойПанели;ПорядокКнопокКоманднойПанели
constexpr auto GUID_839 = "addf1d0f-62e9-4cd5-a385-9c211771d9c6"; // ПеречислениеПорядокКнопокКоманднойПанели;ПеречислениеПорядокКнопокКоманднойПанели
constexpr auto GUID_840 = "1ba2aadf-bb02-440e-a7de-def03a041022"; // ПоложениеТекстаСоединительнойЛинии;ПоложениеТекстаСоединительнойЛинии
constexpr auto GUID_841 = "1ba2aadf-bb02-440e-a7de-def03a041024"; // ПеречислениеПоложениеТекстаСоединительнойЛинии;ПеречислениеПоложениеТекстаСоединительнойЛинии
constexpr auto GUID_842 = "8ddcb883-7461-11d5-a3be-0050bae0a776"; // РежимВыделенияСтрокиТабличногоПоля;РежимВыделенияСтрокиТабличногоПоля
constexpr auto GUID_843 = "8ddcb885-7461-11d5-a3be-0050bae0a776"; // ПеречислениеРежимВыделенияСтрокиТабличногоПоля;ПеречислениеРежимВыделенияСтрокиТабличногоПоля
constexpr auto GUID_844 = "851a9187-0822-449f-a2c9-66a0a0692a1b"; // РежимВыделенияДаты;РежимВыделенияДаты
constexpr auto GUID_845 = "36b40a9a-d182-47df-8dea-35513e9b411e"; // ПеречислениеРежимВыделенияДаты;ПеречислениеРежимВыделенияДаты
constexpr auto GUID_846 = "1fbcb65c-6f6a-4a51-9068-3a9af9f53def"; // РежимБегущейСтроки;РежимБегущейСтроки
constexpr auto GUID_847 = "e0b3b3c6-03c2-408d-8cb1-b6402c906f04"; // ПеречислениеРежимБегущейСтроки;ПеречислениеРежимБегущейСтроки
constexpr auto GUID_848 = "8ddcb889-7461-11d5-a3be-0050bae0a776"; // РежимВводаСтрокТабличногоПоля;РежимВводаСтрокТабличногоПоля
constexpr auto GUID_849 = "8ddcb88b-7461-11d5-a3be-0050bae0a776"; // ПеречислениеРежимВводаСтрокТабличногоПоля;ПеречислениеРежимВводаСтрокТабличногоПоля
constexpr auto GUID_850 = "8ddcb886-7461-11d5-a3be-0050bae0a776"; // РежимВыделенияТабличногоПоля;РежимВыделенияТабличногоПоля
constexpr auto GUID_851 = "8ddcb888-7461-11d5-a3be-0050bae0a776"; // ПеречислениеРежимВыделенияТабличногоПоля;ПеречислениеРежимВыделенияТабличногоПоля
constexpr auto GUID_852 = "05a674a6-f59f-4701-9d60-bf2fc0933819"; // РежимОтрисовкиСеткиГрафическойСхемы;РежимОтрисовкиСеткиГрафическойСхемы
constexpr auto GUID_853 = "ec576973-624d-4592-aa63-6b69db8ac144"; // ПеречислениеРежимОтрисовкиСеткиГрафическойСхемы;ПеречислениеРежимОтрисовкиСеткиГрафическойСхемы
constexpr auto GUID_854 = "4a2d1ae8-ec6c-470a-8392-04f48b7e9a57"; // РежимПоляHTMLДокумента;РежимПоляHTMLДокумента
constexpr auto GUID_855 = "5aa5db72-409c-45b1-9c25-68445a5f2617"; // ПеречислениеРежимПоляHTMLДокумента;ПеречислениеРежимПоляHTMLДокумента
constexpr auto GUID_856 = "0e9de46f-290d-4f4e-a4fb-20c7898945a4"; // РежимРедактированияКолонки;РежимРедактированияКолонки
constexpr auto GUID_857 = "7456b94d-4904-481e-871c-0cf96d99a316"; // ПеречислениеРежимРедактированияКолонки;ПеречислениеРежимРедактированияКолонки
constexpr auto GUID_858 = "b9635ea0-b8b0-4567-a629-2df218c76a1b"; // РежимСверткиЭлементаУправления;РежимСверткиЭлементаУправления
constexpr auto GUID_859 = "4c1a1742-578e-43dd-bd32-8a028a10cceb"; // ПеречислениеРежимСверткиЭлементаУправления;ПеречислениеРежимСверткиЭлементаУправления
constexpr auto GUID_860 = "8ddcb88f-7461-11d5-a3be-0050bae0a776"; // РежимСглаживанияИндикатора;РежимСглаживанияИндикатора
constexpr auto GUID_861 = "8ddcb891-7461-11d5-a3be-0050bae0a776"; // ПеречислениеРежимСглаживанияИндикатора;ПеречислениеРежимСглаживанияИндикатора
constexpr auto GUID_862 = "7b1ced94-e807-48fe-b3d3-5c2fc1cf6935"; // РежимСпискаЗадач;РежимСпискаЗадач
constexpr auto GUID_863 = "7b1ced96-e807-48fe-b3d3-5c2fc1cf6935"; // ПеречислениеРежимСпискаЗадач;ПеречислениеРежимСпискаЗадач
constexpr auto GUID_864 = "c0602204-28e7-4c14-ad84-555d68464ba6"; // СпособРедактированияСписка;СпособРедактированияСписка
constexpr auto GUID_865 = "fecff022-c15c-4b8d-a678-1ee2c3ee3280"; // ПеречислениеСпособРедактированияСписка;ПеречислениеСпособРедактированияСписка
constexpr auto GUID_866 = "81b8d0f5-6e5d-4985-95d9-edcd3570bffe"; // СтандартноеОформление;СтандартноеОформление
constexpr auto GUID_867 = "6d8e3bd2-23f1-4bc3-a17e-df4582971e5b"; // ПеречислениеСтандартноеОформление;ПеречислениеСтандартноеОформление
constexpr auto GUID_868 = "ca6ed495-58e2-4c34-880b-68e15c49b14d"; // СтильСтрелки;СтильСтрелки
constexpr auto GUID_869 = "ca6ed495-58e2-4c34-880b-68e15c49b14f"; // ПеречислениеСтильСтрелки;ПеречислениеСтильСтрелки
constexpr auto GUID_870 = "cc1fd385-a266-42eb-97b8-a9e5bde7fb77"; // ТипКнопкиКоманднойПанели;ТипКнопкиКоманднойПанели
constexpr auto GUID_871 = "03ff10e7-8fcc-4719-b89b-a681fb478528"; // ПеречислениеТипКнопкиКоманднойПанели;ПеречислениеТипКнопкиКоманднойПанели
constexpr auto GUID_872 = "9b9170c8-87a0-4ab9-b17a-2359432d3873"; // ТипРамкиЭлементаУправления;ТипРамкиЭлементаУправления
constexpr auto GUID_873 = "97740f42-09d2-46f3-8130-5baa6aa15335"; // ПеречислениеТипРамкиЭлементаУправления;ПеречислениеТипРамкиЭлементаУправления
constexpr auto GUID_874 = "44109548-bda9-4408-81ca-79a610a009a0"; // ТипРазмещенияИзмерений;ТипРазмещенияИзмерений
constexpr auto GUID_875 = "84f3ec2d-9ef7-47d2-a1e8-2a4d03d2af84"; // ПеречислениеТипРазмещенияИзмерений;ПеречислениеТипРазмещенияИзмерений
constexpr auto GUID_876 = "aa4fe927-51c0-420e-8104-3ad37e1a2006"; // ТипРазмещенияРеквизитовИзмерений;ТипРазмещенияРеквизитовИзмерений
constexpr auto GUID_877 = "1a456249-4891-4c57-83a9-ca0c29da275d"; // ПеречислениеТипРазмещенияРеквизитовИзмерений;ПеречислениеТипРазмещенияРеквизитовИзмерений
constexpr auto GUID_878 = "ff088700-fcac-4a72-ad28-aada8e61ed52"; // ТипСоединительнойЛинии;ТипСоединительнойЛинии
constexpr auto GUID_879 = "0207a22d-ce50-4cd6-9d6d-e308dc494d6e"; // ПеречислениеТипСоединительнойЛинии;ПеречислениеТипСоединительнойЛинии
constexpr auto GUID_880 = "35182393-6af8-4d47-9cec-dff64fa99522"; // ТипОбластиОформления;ТипОбластиОформления
constexpr auto GUID_881 = "35224ab9-71ea-4bf8-9b81-3dc0f789a300"; // ПеречислениеТипОбластиОформления;ПеречислениеТипОбластиОформления
constexpr auto GUID_882 = "bdb9489b-4245-44fb-810d-3d8094d8e62e"; // ФигурыГрафическойСхемы;ФигурыГрафическойСхемы
constexpr auto GUID_883 = "c85df8cb-c935-44e0-a72e-131ffe83e07a"; // ПеречислениеФигурыГрафическойСхемы;ПеречислениеФигурыГрафическойСхемы
constexpr auto GUID_884 = "98d29f48-b189-4aa2-b5fd-ecbdb1effc7f"; // ФорматКартинки;ФорматКартинки
constexpr auto GUID_885 = "0bfc7a72-6b1e-40f6-a12b-897c68b2e232"; // ПеречислениеФорматКартинки;ПеречислениеФорматКартинки
constexpr auto GUID_886 = "a6dbf6e6-9c82-452c-b056-2a8a180e4b37"; // АвтонумерацияВФорме;АвтонумерацияВФорме
constexpr auto GUID_887 = "f452fbe4-2b60-4198-a725-2c52f3f0382d"; // ПеречислениеАвтонумерацияВФорме;ПеречислениеАвтонумерацияВФорме
constexpr auto GUID_888 = "741ae838-6e42-4ac0-b6a4-17e5604b0669"; // ВидДвиженияБухгалтерии;ВидДвиженияБухгалтерии
constexpr auto GUID_889 = "aaf305e9-1625-4435-a9c0-379e67226481"; // ПеречислениеВидДвиженияБухгалтерии;ПеречислениеВидДвиженияБухгалтерии
constexpr auto GUID_890 = "5a49abd5-936d-4f46-8499-9cb204efe378"; // ВидДвиженияНакопления;ВидДвиженияНакопления
constexpr auto GUID_891 = "5d6a3207-61e5-4ee6-a4c3-32842a3b5d68"; // ПеречислениеВидДвиженияНакопления;ПеречислениеВидДвиженияНакопления
constexpr auto GUID_892 = "eb43f417-48a7-4d0f-8d23-4335291aae47"; // ВидПериодаРегистраРасчета;ВидПериодаРегистраРасчета
constexpr auto GUID_893 = "6e55ad6c-e4f1-4ff0-b13b-1eba0e13983c"; // ПеречислениеВидПериодаРегистраРасчета;ПеречислениеВидПериодаРегистраРасчета
constexpr auto GUID_894 = "872f7198-7083-4e3e-b57e-a2a9802c769e"; // ВидСчета;ВидСчета
constexpr auto GUID_895 = "e7cb41d8-8d23-4d73-8d7a-b8a2c255c596"; // ПеречислениеВидСчета;ПеречислениеВидСчета
constexpr auto GUID_896 = "82d8a678-2251-4db1-8db1-99d4bdf5a04d"; // ВидТочкиМаршрутаБизнесПроцесса;ВидТочкиМаршрутаБизнесПроцесса
constexpr auto GUID_897 = "d96baa15-38f5-4e6a-8f61-7191e68b48f2"; // ПеречислениеВидТочкиМаршрутаБизнесПроцесса;ПеречислениеВидТочкиМаршрутаБизнесПроцесса
constexpr auto GUID_898 = "59ef2b80-c86b-11d5-a3c1-0050bae0a776"; // ИспользованиеГруппИЭлементов;ИспользованиеГруппИЭлементов
constexpr auto GUID_899 = "59ef2b82-c86b-11d5-a3c1-0050bae0a776"; // ПеречислениеИспользованиеГруппИЭлементов;ПеречислениеИспользованиеГруппИЭлементов
constexpr auto GUID_900 = "cd0e3ba7-11df-4af8-a93d-debb031d2192"; // ИспользованиеСреза;ИспользованиеСреза
constexpr auto GUID_901 = "87e661c6-106f-439e-9a04-8e097e22ccb8"; // ПеречислениеИспользованиеСреза;ПеречислениеИспользованиеСреза
constexpr auto GUID_902 = "20d89b09-bd04-4304-a8c7-4d07fac6338a"; // ИспользованиеРежимаПроведения;ИспользованиеРежимаПроведения
constexpr auto GUID_903 = "bef0773a-2d90-40f2-a366-6de5d494f38b"; // ПеречислениеИспользованиеРежимаПроведения;ПеречислениеИспользованиеРежимаПроведения
constexpr auto GUID_904 = "adeb08a0-415c-11d6-b9d1-0050bae0a95d"; // РежимАвтоВремя;РежимАвтоВремя
constexpr auto GUID_905 = "27c7756c-e1cc-435e-962f-22df9eeee925"; // РежимЗаписиДокумента;РежимЗаписиДокумента
constexpr auto GUID_906 = "9bf0cad0-b0da-4b62-9bbd-5f7742d47b13"; // ПеречислениеРежимЗаписиДокумента;ПеречислениеРежимЗаписиДокумента
constexpr auto GUID_907 = "76665f04-21b6-4b9c-abce-ed319bde7c6e"; // РежимПроведенияДокумента;РежимПроведенияДокумента
constexpr auto GUID_908 = "0908ee72-e5ca-4d44-9cfa-7d68aa232fe8"; // ПеречислениеРежимПроведенияДокумента;ПеречислениеРежимПроведенияДокумента
constexpr auto GUID_909 = "02075b46-eab5-4658-b31c-3ff418a5998d"; // АвтоРегистрацияИзменений;АвтоРегистрацияИзменений
constexpr auto GUID_910 = "0154d0c6-d1ea-481f-8094-89aadc2623f2"; // ПеречислениеАвтоРегистрацияИзменений;ПеречислениеАвтоРегистрацияИзменений
constexpr auto GUID_911 = "5f630f48-c59b-4594-ab27-1583b3d5fa05"; // ДопустимыйНомерСообщения;ДопустимыйНомерСообщения
constexpr auto GUID_912 = "f0359f23-5c50-465b-8301-94ce45aa22b9"; // ПеречислениеДопустимыйНомерСообщения;ПеречислениеДопустимыйНомерСообщения
constexpr auto GUID_913 = "66144ad4-89e0-4852-bf1e-a5d477ae0290"; // ОтправкаЭлементаДанных;ОтправкаЭлементаДанных
constexpr auto GUID_914 = "295e65b9-c820-4307-9276-e24b9e4a0a88"; // ПеречислениеОтправкаЭлементаДанных;ПеречислениеОтправкаЭлементаДанных
constexpr auto GUID_915 = "6f021296-c59c-4ef5-91f3-04dff23b2de5"; // ПолучениеЭлементаДанных;ПолучениеЭлементаДанных
constexpr auto GUID_916 = "2f9d8f59-9fa0-4178-bf30-ceefbe80f88b"; // ПеречислениеПолучениеЭлементаДанных;ПеречислениеПолучениеЭлементаДанных
constexpr auto GUID_917 = "53571c39-73d4-4be9-a6f3-2550588d775a"; // ПоложениеИтоговСтрокСводнойТаблицы;ПоложениеИтоговСтрокСводнойТаблицы
constexpr auto GUID_918 = "d797ea1c-a74e-4e1a-8b53-775698ca1bcd"; // ПеречислениеПоложениеИтоговСтрокСводнойТаблицы;ПеречислениеПоложениеИтоговСтрокСводнойТаблицы
constexpr auto GUID_919 = "37d4cfba-bac6-4f91-a927-db057d9a9142"; // ПоложениеИтоговКолонокСводнойТаблицы;ПоложениеИтоговКолонокСводнойТаблицы
constexpr auto GUID_920 = "f99a0062-f2a6-457e-85c6-6ade78ab58ef"; // ПеречислениеПоложениеИтоговКолонокСводнойТаблицы;ПеречислениеПоложениеИтоговКолонокСводнойТаблицы
constexpr auto GUID_921 = "11eeaf93-3c32-41c8-a63b-5c03077b2dc7"; // ТипОтображенияЛинийСводнойТаблицы;ТипОтображенияЛинийСводнойТаблицы
constexpr auto GUID_922 = "daefa7e3-4a0a-4d3e-93c9-5ca17c0b0c29"; // ПеречислениеТипОтображенияЛинийСводнойТаблицы;ПеречислениеТипОтображенияЛинийСводнойТаблицы
constexpr auto GUID_923 = "5bbc5ff8-8a7e-4451-92db-eef34389c3a2"; // ИспользованиеРасшифровкиТабличногоДокумента;ИспользованиеРасшифровкиТабличногоДокумента
constexpr auto GUID_924 = "a05ccb65-70ed-4a14-8bc4-f44085a2a04d"; // ПеречислениеИспользованиеРасшифровкиТабличногоДокумента;ПеречислениеИспользованиеРасшифровкиТабличногоДокумента
constexpr auto GUID_925 = "6d777cfc-25a4-4791-a35f-da85036a2377"; // ТипЗаполненияОбластиТабличногоДокумента;ТипЗаполненияОбластиТабличногоДокумента
constexpr auto GUID_926 = "afd4343d-eff7-4178-bfda-effbcb73c639"; // ПеречислениеТипЗаполненияОбластиТабличногоДокумента;ПеречислениеТипЗаполненияОбластиТабличногоДокумента
constexpr auto GUID_927 = "c3481c23-8545-4dae-91bb-2aaa019fc463"; // ТипЛинииРисункаТабличногоДокумента;ТипЛинииРисункаТабличногоДокумента
constexpr auto GUID_928 = "a3b5f95e-ae3b-4888-b93d-b413a4d5934c"; // ПеречислениеТипЛинииРисункаТабличногоДокумента;ПеречислениеТипЛинииРисункаТабличногоДокумента
constexpr auto GUID_929 = "f995d69c-6b41-4f29-aace-0411364efad9"; // ТипЛинииЯчейкиТабличногоДокумента;ТипЛинииЯчейкиТабличногоДокумента
constexpr auto GUID_930 = "fe9adf35-c9a6-4e13-bd1f-9aefe0811530"; // ПеречислениеТипЛинииЯчейкиТабличногоДокумента;ПеречислениеТипЛинииЯчейкиТабличногоДокумента
constexpr auto GUID_931 = "08d0b862-1233-4bf2-aae0-ce3988ed4284"; // ТипНаправленияПереходаТабличногоДокумента;ТипНаправленияПереходаТабличногоДокумента
constexpr auto GUID_932 = "cb102649-3739-427b-8b22-3da22267d9ca"; // ПеречислениеТипНаправленияПереходаТабличногоДокумента;ПеречислениеТипНаправленияПереходаТабличногоДокумента
constexpr auto GUID_933 = "4ad301a4-77df-4721-b7ec-12a1d96b2963"; // ТипОбластиЯчеекТабличногоДокумента;ТипОбластиЯчеекТабличногоДокумента
constexpr auto GUID_934 = "7cf95d90-4249-475e-9613-5ecbc25af596"; // ПеречислениеТипОбластиЯчеекТабличногоДокумента;ПеречислениеТипОбластиЯчеекТабличногоДокумента
constexpr auto GUID_935 = "554e098c-cbb5-481b-9bca-7ddd05ce514f"; // ТипОтображенияВыделенияТабличногоДокумента;ТипОтображенияВыделенияТабличногоДокумента
constexpr auto GUID_936 = "9399c5fa-3d3c-4dfb-bc41-727db5140946"; // ПеречислениеТипОтображенияВыделенияТабличногоДокумента;ПеречислениеТипОтображенияВыделенияТабличногоДокумента
constexpr auto GUID_937 = "b268057c-d7a7-4b99-8191-3f8538adb4bb"; // ТипРазмещенияТекстаТабличногоДокумента;ТипРазмещенияТекстаТабличногоДокумента
constexpr auto GUID_938 = "43904778-e09e-4e81-a0c2-a80c49eb6796"; // ПеречислениеТипРазмещенияТекстаТабличногоДокумента;ПеречислениеТипРазмещенияТекстаТабличногоДокумента
constexpr auto GUID_939 = "1f0ff470-15b7-47b4-b112-bf948e2e0151"; // ТипРисункаТабличногоДокумента;ТипРисункаТабличногоДокумента
constexpr auto GUID_940 = "5d449c8b-92da-4b84-9b9b-cd9ddc7858fa"; // ПеречислениеТипРисункаТабличногоДокумента;ПеречислениеТипРисункаТабличногоДокумента
constexpr auto GUID_941 = "27ea85c0-2b41-4f12-9f01-8cf6fac9ff10"; // ТипСмещенияТабличногоДокумента;ТипСмещенияТабличногоДокумента
constexpr auto GUID_942 = "c95356a7-7292-4c79-822d-e30f54f336c6"; // ПеречислениеТипСмещенияТабличногоДокумента;ПеречислениеТипСмещенияТабличногоДокумента
constexpr auto GUID_943 = "2f866e03-7374-4cc6-bc99-bc295d4d1711"; // ТипУзораТабличногоДокумента;ТипУзораТабличногоДокумента
constexpr auto GUID_944 = "b2db631a-65cd-42a4-b1ea-d9e5dcba4072"; // ПеречислениеТипУзораТабличногоДокумента;ПеречислениеТипУзораТабличногоДокумента
constexpr auto GUID_945 = "0c3ff22d-327e-4a42-957a-5d4843e622e8"; // ТипФайлаТабличногоДокумента;ТипФайлаТабличногоДокумента
constexpr auto GUID_946 = "9d7c5259-0dfa-48e6-8231-dbbf069fbd4d"; // ПеречислениеТипФайлаТабличногоДокумента;ПеречислениеТипФайлаТабличногоДокумента
constexpr auto GUID_947 = "137b3efa-85d2-46b5-accd-167151436c12"; // РасположениеЗаголовкаГруппировкиТабличногоДокумента;РасположениеЗаголовкаГруппировкиТабличногоДокумента
constexpr auto GUID_948 = "7cba97c4-0fa2-4675-a098-980d2a8d7a80"; // ПеречислениеРасположениеЗаголовкаГруппировкиТабличногоДокумента;ПеречислениеРасположениеЗаголовкаГруппировкиТабличногоДокумента
constexpr auto GUID_949 = "fe5dad88-7ace-4c95-a422-5bc557f0280f"; // ОбходРезультатаЗапроса;ОбходРезультатаЗапроса
constexpr auto GUID_950 = "c125bedf-b785-4267-951b-50d310def8ed"; // ПеречислениеОбходРезультатаЗапроса;ПеречислениеОбходРезультатаЗапроса
constexpr auto GUID_951 = "955c1f8c-6b8a-4e5a-9d46-99af8e3964e7"; // ТипЗаписиЗапроса;ТипЗаписиЗапроса
constexpr auto GUID_952 = "83c2ca64-ee26-476b-a169-f15293388e90"; // ПеречислениеТипЗаписиЗапроса;ПеречислениеТипЗаписиЗапроса
constexpr auto GUID_953 = "0561ae83-b054-4fd0-98fb-0eb757ed92ab"; // ВидЗаполненияРасшифровкиПостроителяОтчета;ВидЗаполненияРасшифровкиПостроителяОтчета
constexpr auto GUID_954 = "3513a539-9254-4011-86ae-82a51096147e"; // ПеречислениеВидЗаполненияРасшифровкиПостроителяОтчета;ПеречислениеВидЗаполненияРасшифровкиПостроителяОтчета
constexpr auto GUID_955 = "c347664e-14cc-4035-9876-1b0d246470d8"; // ТипДобавленияПредставлений;ТипДобавленияПредставлений
constexpr auto GUID_956 = "5f825094-95d6-42ef-8797-b549b62cb706"; // ПеречислениеТипДобавленияПредставлений;ПеречислениеТипДобавленияПредставлений
constexpr auto GUID_957 = "90d4887a-f541-490b-b51b-c8a00bb332de"; // ТипИзмеренияПостроителяОтчета;ТипИзмеренияПостроителяОтчета
constexpr auto GUID_958 = "44ee1e99-da5f-456b-9ce5-a22990a93acc"; // ПеречислениеТипИзмеренияПостроителяОтчета;ПеречислениеТипИзмеренияПостроителяОтчета
constexpr auto GUID_959 = "0f9c62cc-0429-462f-825a-bc6fedc3cebd"; // ТипРазмещенияИтогов;ТипРазмещенияИтогов
constexpr auto GUID_960 = "f70a8512-cfc4-4f8f-857a-e5688911650d"; // ПеречислениеТипРазмещенияИтогов;ПеречислениеТипРазмещенияИтогов
constexpr auto GUID_961 = "940e89c1-4d22-4dff-87a0-b65c745f73f8"; // ТипИзмеренияПостроителяЗапроса;ТипИзмеренияПостроителяЗапроса
constexpr auto GUID_962 = "7c68e3bc-f6e4-48a0-af08-361b579bdd8f"; // ПеречислениеТипИзмеренияПостроителяЗапроса;ПеречислениеТипИзмеренияПостроителяЗапроса
constexpr auto GUID_963 = "3cc7f83c-9e5f-4926-9752-b10cba3d18f3"; // РежимДиалогаВыбораФайла;РежимДиалогаВыбораФайла
constexpr auto GUID_964 = "2383bbb3-8114-4f0a-bdc3-0181b5cc6acd"; // ПеречислениеРежимДиалогаВыбораФайла;ПеречислениеРежимДиалогаВыбораФайла
constexpr auto GUID_965 = "7c3a52af-32ea-4052-9bcc-6f2b1f1600f3"; // СпособСравненияФайлов;СпособСравненияФайлов
constexpr auto GUID_966 = "16106df1-828c-46d7-a4f6-376be2bea4c4"; // ПеречислениеСпособСравненияФайлов;ПеречислениеСпособСравненияФайлов
constexpr auto GUID_967 = "0bc96bbe-a6e8-4fdc-aecd-57f493904535"; // ВидДанныхАнализа;ВидДанныхАнализа
constexpr auto GUID_968 = "0cdaf6c3-d2d2-486d-9649-99441956cfd8"; // ПеречислениеВидДанныхАнализа;ПеречислениеВидДанныхАнализа
constexpr auto GUID_969 = "df706cce-3392-469c-af4c-cd4a13bf13bb"; // МетодКластеризации;МетодКластеризации
constexpr auto GUID_970 = "ff039069-41bd-48d2-81b4-8ed437f1918b"; // ПеречислениеМетодКластеризации;ПеречислениеМетодКластеризации
constexpr auto GUID_971 = "77a01c71-e9b2-4617-af07-c95a4b74548a"; // ТипЕдиницыИнтервалаВремениАнализаДанных;ТипЕдиницыИнтервалаВремениАнализаДанных
constexpr auto GUID_972 = "9369aa17-0d7a-4cc9-b3e1-5e3fec523d56"; // ПеречислениеТипЕдиницыИнтервалаВремениАнализаДанных;ПеречислениеТипЕдиницыИнтервалаВремениАнализаДанных
constexpr auto GUID_973 = "18ae9d87-950e-44a6-883a-1cd1f63040fb"; // ТипЗаполненияТаблицыРезультатаАнализаДанных;ТипЗаполненияТаблицыРезультатаАнализаДанных
constexpr auto GUID_974 = "1094860c-3906-4844-aa7d-008b7d850aee"; // ПеречислениеТипЗаполненияТаблицыРезультатаАнализаДанных;ПеречислениеТипЗаполненияТаблицыРезультатаАнализаДанных
constexpr auto GUID_975 = "2ee0f1c6-3781-421d-b7de-c4c359cb159c"; // ТипИспользованияЧисловыхЗначенийАнализаДанных;ТипИспользованияЧисловыхЗначенийАнализаДанных
constexpr auto GUID_976 = "9d163093-6724-4927-85c4-2aa3c31c1375"; // ПеречислениеТипИспользованияЧисловыхЗначенийАнализаДанных;ПеречислениеТипИспользованияЧисловыхЗначенийАнализаДанных
constexpr auto GUID_977 = "050f918e-cda3-4d92-997a-df4a76f00cd1"; // ТипИсточникаДанныхПоискаАссоциаций;ТипИсточникаДанныхПоискаАссоциаций
constexpr auto GUID_978 = "5812599e-25a6-4076-a2f9-ee8270b9866f"; // ПеречислениеТипИсточникаДанныхПоискаАссоциаций;ПеречислениеТипИсточникаДанныхПоискаАссоциаций
constexpr auto GUID_979 = "5f290fad-aa2a-4245-b200-cd035ab19571"; // ТипКолонкиАнализаДанныхДеревоРешений;ТипКолонкиАнализаДанныхДеревоРешений
constexpr auto GUID_980 = "8e866479-28ac-41d0-83be-7ba58a0135e2"; // ПеречислениеТипКолонкиАнализаДанныхДеревоРешений;ПеречислениеТипКолонкиАнализаДанныхДеревоРешений
constexpr auto GUID_981 = "ffdb46a2-3f23-4712-bad7-ad26997fb2d4"; // ТипКолонкиАнализаДанныхКластеризация;ТипКолонкиАнализаДанныхКластеризация
constexpr auto GUID_982 = "efda27b1-4dd2-4100-a9b9-1d8b8ef02d98"; // ПеречислениеТипКолонкиАнализаДанныхКластеризация;ПеречислениеТипКолонкиАнализаДанныхКластеризация
constexpr auto GUID_983 = "efb63b25-8150-4c82-9687-970924f5f1f8"; // ТипКолонкиАнализаДанныхОбщаяСтатистика;ТипКолонкиАнализаДанныхОбщаяСтатистика
constexpr auto GUID_984 = "cbc29a12-8d73-4edb-94aa-3d590c2c1d4a"; // ПеречислениеТипКолонкиАнализаДанныхОбщаяСтатистика;ПеречислениеТипКолонкиАнализаДанныхОбщаяСтатистика
constexpr auto GUID_985 = "148a98e5-0ad6-42c9-8133-e5ebbff69734"; // ТипКолонкиАнализаДанныхПоискАссоциаций;ТипКолонкиАнализаДанныхПоискАссоциаций
constexpr auto GUID_986 = "1a6beb5d-18ac-4190-942e-12b441682e64"; // ПеречислениеТипКолонкиАнализаДанныхПоискАссоциаций;ПеречислениеТипКолонкиАнализаДанныхПоискАссоциаций
constexpr auto GUID_987 = "7d8b2989-2a0a-4334-afe1-82ceb63cf38a"; // ТипКолонкиАнализаДанныхПоискПоследовательностей;ТипКолонкиАнализаДанныхПоискПоследовательностей
constexpr auto GUID_988 = "5ddb710b-4dcb-46d4-a1e0-7dca0fd47633"; // ПеречислениеТипКолонкиАнализаДанныхПоискПоследовательностей;ПеречислениеТипКолонкиАнализаДанныхПоискПоследовательностей
constexpr auto GUID_989 = "d015cb03-c768-4078-bb5d-b9404d99bc4c"; // ТипКолонкиМоделиПрогноза;ТипКолонкиМоделиПрогноза
constexpr auto GUID_990 = "05fd3a5a-ea46-45f1-8d9f-6a89096ec887"; // ПеречислениеТипКолонкиМоделиПрогноза;ПеречислениеТипКолонкиМоделиПрогноза
constexpr auto GUID_991 = "0d3438ab-6412-4d39-91a9-a7d4e8418d27"; // ТипМерыРасстоянияАнализаДанных;ТипМерыРасстоянияАнализаДанных
constexpr auto GUID_992 = "d25dff56-501f-45fc-9737-d7e18e74e76e"; // ПеречислениеТипМерыРасстоянияАнализаДанных;ПеречислениеТипМерыРасстоянияАнализаДанных
constexpr auto GUID_993 = "f8cdf4bc-4411-4b98-b8a3-d6f8e3ddb1c7"; // ТипОтсеченияПравилАссоциации;ТипОтсеченияПравилАссоциации
constexpr auto GUID_994 = "8b2151ed-3eb0-408e-8dea-e4e86e69167a"; // ПеречислениеТипОтсеченияПравилАссоциации;ПеречислениеТипОтсеченияПравилАссоциации
constexpr auto GUID_995 = "e3facebb-9078-4f04-ac16-e7e75c2d110f"; // ТипПоляАнализаДанных;ТипПоляАнализаДанных
constexpr auto GUID_996 = "5d1a4693-5569-4001-9e77-3ccaafb6b57b"; // ПеречислениеТипПоляАнализаДанных;ПеречислениеТипПоляАнализаДанных
constexpr auto GUID_997 = "afaa3f6e-29a1-4064-a825-73699c7db53b"; // ТипСтандартизацииАнализаДанных;ТипСтандартизацииАнализаДанных
constexpr auto GUID_998 = "35e34b68-360d-41fc-a07f-2dead91aa189"; // ПеречислениеТипСтандартизацииАнализаДанных;ПеречислениеТипСтандартизацииАнализаДанных
constexpr auto GUID_999 = "4622a61b-5817-4bf3-bf46-08bed102c02a"; // ТипУпрощенияДереваРешений;ТипУпрощенияДереваРешений
constexpr auto GUID_1000 = "3702533a-2ed2-48f9-a076-28c76af1cf70"; // ПеречислениеТипУпрощенияДереваРешений;ПеречислениеТипУпрощенияДереваРешений
constexpr auto GUID_1001 = "e838bbb4-8cdd-4b96-8259-66a1c44ca631"; // ТипУпорядочиванияПравилАссоциацииАнализаДанных;ТипУпорядочиванияПравилАссоциацииАнализаДанных
constexpr auto GUID_1002 = "26a65d95-eb6a-4f85-a526-d466b041f992"; // ПеречислениеТипУпорядочиванияПравилАссоциацииАнализаДанных;ПеречислениеТипУпорядочиванияПравилАссоциацииАнализаДанных
constexpr auto GUID_1003 = "6359f32c-4192-46cf-86c0-2f897b70a339"; // ТипУпорядочиванияШаблоновПоследовательностейАнализаДанных;ТипУпорядочиванияШаблоновПоследовательностейАнализаДанных
constexpr auto GUID_1004 = "7e6866b9-d1b4-47e0-889a-8e48c323951f"; // ПеречислениеТипУпорядочиванияШаблоновПоследовательностейАнализаДанных;ПеречислениеТипУпорядочиванияШаблоновПоследовательностейАнализаДанных
constexpr auto GUID_1005 = "32acb50a-6fad-4e27-8ea4-3477d9864119"; // НазначениеТипаXML;НазначениеТипаXML
constexpr auto GUID_1006 = "09c23b59-ee02-4d8c-b0c2-331c1183553f"; // ПеречислениеНазначениеТипаXML;ПеречислениеНазначениеТипаXML
constexpr auto GUID_1007 = "fdfae58f-30f4-42a2-8e44-948af536700c"; // ПробельныеСимволыXML;ПробельныеСимволыXML
constexpr auto GUID_1008 = "314f6b2c-d23e-4b2a-b897-50975215ffc4"; // ПеречислениеПробельныеСимволыXML;ПеречислениеПробельныеСимволыXML
constexpr auto GUID_1009 = "61f676c4-6663-45f5-b126-acb6a30bb37b"; // ТипАтрибутаXML;ТипАтрибутаXML
constexpr auto GUID_1010 = "c0dc2247-e24a-4268-b326-a0e52dbca39f"; // ПеречислениеТипАтрибутаXML;ПеречислениеТипАтрибутаXML
constexpr auto GUID_1011 = "ae0c93dc-bd58-4394-b498-e306561e8267"; // ТипКаноническогоXML;ТипКаноническогоXML
constexpr auto GUID_1012 = "8b7e9d51-079d-4387-ae82-25ed7c861d30"; // ПеречислениеТипКаноническогоXML;ПеречислениеТипКаноническогоXML
constexpr auto GUID_1013 = "af66d99a-aeb8-4e22-8fc5-fee6c1dc85db"; // ТипПроверкиXML;ТипПроверкиXML
constexpr auto GUID_1014 = "258f7fcd-650f-4729-9d45-71958b5d95a5"; // ПеречислениеТипПроверкиXML;ПеречислениеТипПроверкиXML
constexpr auto GUID_1015 = "27f942f9-4100-4eb7-8c24-275839323408"; // ТипУзлаXML;ТипУзлаXML
constexpr auto GUID_1016 = "9ab4c429-a72a-4b27-b246-e892f701b609"; // ПеречислениеТипУзлаXML;ПеречислениеТипУзлаXML
constexpr auto GUID_1017 = "1dc91213-8991-47c9-8ea4-a68ba94eb0ff"; // ВариантXPathXS;ВариантXPathXS
constexpr auto GUID_1018 = "78838ab1-e005-46a7-9b64-ee49cae238d1"; // ПеречислениеВариантXPathXS;ПеречислениеВариантXPathXS
constexpr auto GUID_1019 = "e48243f3-4a29-4223-978d-18d5659340af"; // ВариантПростогоТипаXS;ВариантПростогоТипаXS
constexpr auto GUID_1020 = "5b74e1ee-7a22-4059-8e04-446d3d2bbd10"; // ПеречислениеВариантПростогоТипаXS;ПеречислениеВариантПростогоТипаXS
constexpr auto GUID_1021 = "b9efcbb6-4e90-4b22-8919-99571a582021"; // ВидГруппыМоделиXS;ВидГруппыМоделиXS
constexpr auto GUID_1022 = "a75d6267-02f9-4b28-8e48-0a98e8f7be35"; // ПеречислениеВидГруппыМоделиXS;ПеречислениеВидГруппыМоделиXS
constexpr auto GUID_1023 = "2aaf2e35-cbfb-4d26-a121-32f6daa486b0"; // ЗавершенностьПростогоТипаXS;ЗавершенностьПростогоТипаXS
constexpr auto GUID_1024 = "40302f2a-56c8-4270-a90b-22e32abf3121"; // ПеречислениеЗавершенностьПростогоТипаXS;ПеречислениеЗавершенностьПростогоТипаXS
constexpr auto GUID_1025 = "4f4e332f-7346-4beb-bd19-d5bcccfaceca"; // ЗавершенностьСоставногоТипаXS;ЗавершенностьСоставногоТипаXS
constexpr auto GUID_1026 = "1c01ed7f-1daa-43dc-8ad1-a5401c6fd716"; // ПеречислениеЗавершенностьСоставногоТипаXS;ПеречислениеЗавершенностьСоставногоТипаXS
constexpr auto GUID_1027 = "fa8a46c3-7ef7-4679-9627-a4aa0d73b7a8"; // ЗавершенностьСхемыXS;ЗавершенностьСхемыXS
constexpr auto GUID_1028 = "6cc25958-f25d-4f2e-a9d8-d854d0739f97"; // ПеречислениеЗавершенностьСхемыXS;ПеречислениеЗавершенностьСхемыXS
constexpr auto GUID_1029 = "143cf862-28dd-4e20-8313-88b292ac24ad"; // ЗапрещенныеПодстановкиXS;ЗапрещенныеПодстановкиXS
constexpr auto GUID_1030 = "5cea97ec-a426-404a-b936-44d321e34c0a"; // ПеречислениеЗапрещенныеПодстановкиXS;ПеречислениеЗапрещенныеПодстановкиXS
constexpr auto GUID_1031 = "3427381e-2208-4e80-b703-4a40382a2c9c"; // ИсключенияГруппПодстановкиXS;ИсключенияГруппПодстановкиXS
constexpr auto GUID_1032 = "48f0df08-8ae5-481e-b864-a127b88651fc"; // ПеречислениеИсключенияГруппПодстановкиXS;ПеречислениеИсключенияГруппПодстановкиXS
constexpr auto GUID_1033 = "9d32529d-cfe4-4bae-80c6-1e59899a71d8"; // КатегорияИспользованияАтрибутаXS;КатегорияИспользованияАтрибутаXS
constexpr auto GUID_1034 = "fff6bb75-2f2c-4717-b5be-03ac7f4e8fb8"; // ПеречислениеКатегорияИспользованияАтрибутаXS;ПеречислениеКатегорияИспользованияАтрибутаXS
constexpr auto GUID_1035 = "8a497b15-9c15-44c4-a316-94892da0210d"; // КатегорияОграниченияИдентичностиXS;КатегорияОграниченияИдентичностиXS
constexpr auto GUID_1036 = "cd77895e-5da1-424d-9108-9efe90d25374"; // ПеречислениеКатегорияОграниченияИдентичностиXS;ПеречислениеКатегорияОграниченияИдентичностиXS
constexpr auto GUID_1037 = "f8b8e876-6008-4e05-b37c-67120e3e320f"; // КатегорияОграниченияПространствИменXS;КатегорияОграниченияПространствИменXS
constexpr auto GUID_1038 = "f99185e4-5949-43df-b3bb-90fe7615a3c9"; // ПеречислениеКатегорияОграниченияПространствИменXS;ПеречислениеКатегорияОграниченияПространствИменXS
constexpr auto GUID_1039 = "c9be7a4a-e112-4e9a-b387-489a47ff04ea"; // МодельСодержимогоXS;МодельСодержимогоXS
constexpr auto GUID_1040 = "84861198-8d7a-418d-8dcf-f5c1c20eeaa1"; // ПеречислениеМодельСодержимогоXS;ПеречислениеМодельСодержимогоXS
constexpr auto GUID_1041 = "23653f49-f839-4eaf-87b0-c5ce536fb7f6"; // МетодНаследованияXS;МетодНаследованияXS
constexpr auto GUID_1042 = "5639739e-ab2e-4e9b-bcff-50f760b4c90c"; // ПеречислениеМетодНаследованияXS;ПеречислениеМетодНаследованияXS
constexpr auto GUID_1043 = "fb928b09-2f2b-46a8-9d59-58ededb47db3"; // ОбработкаПробельныхСимволовXS;ОбработкаПробельныхСимволовXS
constexpr auto GUID_1044 = "de0ab85b-1740-490a-8a86-5d2fb5a567e8"; // ПеречислениеОбработкаПробельныхСимволовXS;ПеречислениеОбработкаПробельныхСимволовXS
constexpr auto GUID_1045 = "ba4b8883-9aa3-4a02-9519-ecb698cecf2f"; // ОбработкаСодержимогоXS;ОбработкаСодержимогоXS
constexpr auto GUID_1046 = "5bee4623-8e52-4b70-a7b6-16c041c5c785"; // ПеречислениеОбработкаСодержимогоXS;ПеречислениеОбработкаСодержимогоXS
constexpr auto GUID_1047 = "d9c7f308-7328-45c5-ad9f-b0732a00bf4b"; // ОграничениеЗначенияXS;ОграничениеЗначенияXS
constexpr auto GUID_1048 = "04d7cd8a-d0ef-4cfb-9c8c-b029aa173038"; // ПеречислениеОграничениеЗначенияXS;ПеречислениеОграничениеЗначенияXS
constexpr auto GUID_1049 = "2d79cc49-b5f6-4f68-b7e8-bb252b6d10e8"; // НедопустимыеПодстановкиXS;НедопустимыеПодстановкиXS
constexpr auto GUID_1050 = "4885537f-3ac5-409f-a8e2-efdd15c8ed12"; // ПеречислениеНедопустимыеПодстановкиXS;ПеречислениеНедопустимыеПодстановкиXS
constexpr auto GUID_1051 = "7fee725d-331c-4594-be50-a586b48c70be"; // ТипКомпонентыXS;ТипКомпонентыXS
constexpr auto GUID_1052 = "7c1c3e34-53ef-4de6-8b64-09ec20c46479"; // ПеречислениеТипКомпонентыXS;ПеречислениеТипКомпонентыXS
constexpr auto GUID_1053 = "bf86c82e-52e4-42b3-adcc-0c93eb78ae16"; // ФормаПредставленияXS;ФормаПредставленияXS
constexpr auto GUID_1054 = "732f2f2b-0734-4165-a4a5-aad8b8a3419f"; // ПеречислениеФормаПредставленияXS;ПеречислениеФормаПредставленияXS
constexpr auto GUID_1055 = "3964cb6f-155a-4d30-92a7-70fdc71dcb20"; // ДействиеПостроителяDOM;ДействиеПостроителяDOM
constexpr auto GUID_1056 = "b9838ba0-1585-4ffe-9f57-ff4e696e4715"; // ПеречислениеДействиеПостроителяDOM;ПеречислениеДействиеПостроителяDOM
constexpr auto GUID_1057 = "893866f9-9625-4df7-b10d-24a0ef9dd5c9"; // ПараметрыОтбораУзловDOM;ПараметрыОтбораУзловDOM
constexpr auto GUID_1058 = "2071a747-b6b1-4eea-96d6-17b2230e6ead"; // ПеречислениеПараметрыОтбораУзловDOM;ПеречислениеПараметрыОтбораУзловDOM
constexpr auto GUID_1059 = "5b46f8c0-99dc-4fed-8f6f-ca9f3fe7c1d1"; // ПозицияВДокументеDOM;ПозицияВДокументеDOM
constexpr auto GUID_1060 = "2442dc50-ca52-4ca3-b957-8b4feebd5b1b"; // ПеречислениеПозицияВДокументеDOM;ПеречислениеПозицияВДокументеDOM
constexpr auto GUID_1061 = "f133e20c-f761-4a2c-8826-090dce4485a8"; // ТипРезультатаDOMXPath;ТипРезультатаDOMXPath
constexpr auto GUID_1062 = "0e059a28-ab60-4a98-bd7a-f47e80ea04b1"; // ПеречислениеТипРезультатаDOMXPath;ПеречислениеТипРезультатаDOMXPath
constexpr auto GUID_1063 = "c7f97d2c-a390-4800-92d2-083b06cf3e88"; // ТипУзлаDOM;ТипУзлаDOM
constexpr auto GUID_1064 = "be9b091c-1888-4076-89dd-1ea59750bdc6"; // ПеречислениеТипУзлаDOM;ПеречислениеТипУзлаDOM
constexpr auto GUID_1065 = "8aab2af7-9404-4061-9e66-9ee0d50c8de0"; // ВидФасетаXDTO;ВидФасетаXDTO
constexpr auto GUID_1066 = "92281a74-211d-4d8b-b4d7-2859a9703ce1"; // ПеречислениеВидФасетаXDTO;ПеречислениеВидФасетаXDTO
constexpr auto GUID_1067 = "a0f695f7-9c59-4192-8b3a-ae8c8fac1530"; // ФормаXML;ФормаXML
constexpr auto GUID_1068 = "ddb95a61-e246-49d2-9483-d0d3e52edf8e"; // ПеречислениеФормаXML;ПеречислениеФормаXML
constexpr auto GUID_1069 = "4edbada8-7ba0-455a-aba2-c1432365be7e"; // WSНаправлениеПараметра;WSНаправлениеПараметра
constexpr auto GUID_1070 = "bcc7ecbd-495e-47f7-a40c-54ef47c95390"; // ПеречислениеWSНаправлениеПараметра;ПеречислениеWSНаправлениеПараметра
constexpr auto GUID_1071 = "dcbf2698-3c1f-4a22-997f-48070ae9bd64"; // ВидСравненияКомпоновкиДанных;ВидСравненияКомпоновкиДанных
constexpr auto GUID_1072 = "1638a6f1-2e84-4b88-8833-882615ec2b66"; // ПеречислениеВидСравненияКомпоновкиДанных;ПеречислениеВидСравненияКомпоновкиДанных
constexpr auto GUID_1073 = "513a3e19-bc0e-47f6-a012-c30e75856526"; // ДействиеОбработкиРасшифровкиКомпоновкиДанных;ДействиеОбработкиРасшифровкиКомпоновкиДанных
constexpr auto GUID_1074 = "63cd84a5-9796-4851-ac10-28d253c22bc9"; // ПеречислениеДействиеОбработкиРасшифровкиКомпоновкиДанных;ПеречислениеДействиеОбработкиРасшифровкиКомпоновкиДанных
constexpr auto GUID_1075 = "38643f26-7aaf-4eff-b72a-667614c8aaf1"; // ДействиеПриНедоступностиНастроекКомпоновкиДанных;ДействиеПриНедоступностиНастроекКомпоновкиДанных
constexpr auto GUID_1076 = "cdb0259a-5e48-407a-8ff1-b9ab532856b3"; // ПеречислениеДействиеПриНедоступностиНастроекКомпоновкиДанных;ПеречислениеДействиеПриНедоступностиНастроекКомпоновкиДанных
constexpr auto GUID_1077 = "af4a19b5-da3d-406f-be0c-81143e400452"; // НаправлениеСортировкиКомпоновкиДанных;НаправлениеСортировкиКомпоновкиДанных
constexpr auto GUID_1078 = "40bb83cc-3622-437c-ae26-13e779bd628f"; // ПеречислениеНаправлениеСортировкиКомпоновкиДанных;ПеречислениеНаправлениеСортировкиКомпоновкиДанных
constexpr auto GUID_1079 = "987a9fb1-1eea-4610-a135-a996ed8f14f3"; // РасположениеВложенныхЭлементовРезультатаКомпоновкиДанных;РасположениеВложенныхЭлементовРезультатаКомпоновкиДанных
constexpr auto GUID_1080 = "493a3a3d-747c-4020-bd3c-29f72be815f0"; // ПеречислениеРасположениеВложенныхЭлементовРезультатаКомпоновкиДанных;ПеречислениеРасположениеВложенныхЭлементовРезультатаКомпоновкиДанных
constexpr auto GUID_1081 = "49a51e98-1835-46da-9cb0-382d9387fa79"; // РасположениеИтоговКомпоновкиДанных;РасположениеИтоговКомпоновкиДанных
constexpr auto GUID_1082 = "47a38698-501d-4b51-af1d-836f1a8a2ffe"; // ПеречислениеРасположениеИтоговКомпоновкиДанных;ПеречислениеРасположениеИтоговКомпоновкиДанных
constexpr auto GUID_1083 = "a5ab50bf-eecb-436d-9d38-11842fc9367c"; // РасположениеГруппировкиКомпоновкиДанных;РасположениеГруппировкиКомпоновкиДанных
constexpr auto GUID_1084 = "9dfd0bd0-570d-460a-8a47-90d25d1c6578"; // ПеречислениеРасположениеГруппировкиКомпоновкиДанных;ПеречислениеРасположениеГруппировкиКомпоновкиДанных
constexpr auto GUID_1085 = "71c8fe69-6d13-497c-8751-6bd45ea4ea69"; // РасположениеПолейГруппировкиКомпоновкиДанных;РасположениеПолейГруппировкиКомпоновкиДанных
constexpr auto GUID_1086 = "e880806e-4120-4211-97be-4cd1c4fe237d"; // ПеречислениеРасположениеПолейГруппировкиКомпоновкиДанных;ПеречислениеРасположениеПолейГруппировкиКомпоновкиДанных
constexpr auto GUID_1087 = "a090004e-b706-453f-aa10-090a77b53757"; // РасположениеПоляКомпоновкиДанных;РасположениеПоляКомпоновкиДанных
constexpr auto GUID_1088 = "b43ad7db-e9ce-45f0-a185-b565a8f7dfdf"; // ПеречислениеРасположениеПоляКомпоновкиДанных;ПеречислениеРасположениеПоляКомпоновкиДанных
constexpr auto GUID_1089 = "53303ce0-bebb-4b8f-8545-50afcdc60306"; // РасположениеРеквизитовКомпоновкиДанных;РасположениеРеквизитовКомпоновкиДанных
constexpr auto GUID_1090 = "791caed1-151e-413e-a39b-8b7e6115abed"; // ПеречислениеРасположениеРеквизитовКомпоновкиДанных;ПеречислениеРасположениеРеквизитовКомпоновкиДанных
constexpr auto GUID_1091 = "e194765a-3b47-4ff2-9b39-49b90e6eab79"; // РасположениеРесурсовКомпоновкиДанных;РасположениеРесурсовКомпоновкиДанных
constexpr auto GUID_1092 = "c83d1ffb-a282-4bef-b6cf-d707e6f78a2c"; // ПеречислениеРасположениеРесурсовКомпоновкиДанных;ПеречислениеРасположениеРесурсовКомпоновкиДанных
constexpr auto GUID_1093 = "53b5cdb2-f4e9-44ae-a7ae-dcb6700e6d0a"; // ТипБухгалтерскогоОстаткаКомпоновкиДанных;ТипБухгалтерскогоОстаткаКомпоновкиДанных
constexpr auto GUID_1094 = "8b341830-7d90-43ee-aa1b-f67abf46a0fb"; // ПеречислениеТипБухгалтерскогоОстаткаКомпоновкиДанных;ПеречислениеТипБухгалтерскогоОстаткаКомпоновкиДанных
constexpr auto GUID_1095 = "29498591-852c-4109-9b6a-b9b83b34bdb3"; // ТипВыводаТекстаКомпоновкиДанных;ТипВыводаТекстаКомпоновкиДанных
constexpr auto GUID_1096 = "5e26b668-bb93-4da3-983c-cc2e300256e4"; // ПеречислениеТипВыводаТекстаКомпоновкиДанных;ПеречислениеТипВыводаТекстаКомпоновкиДанных
constexpr auto GUID_1097 = "0e0850cf-0634-414e-85ba-9a88a8bd44c4"; // ТипГруппировкиКомпоновкиДанных;ТипГруппировкиКомпоновкиДанных
constexpr auto GUID_1098 = "86e693d0-2b7b-4c40-8348-3234b4181cd1"; // ПеречислениеТипГруппировкиКомпоновкиДанных;ПеречислениеТипГруппировкиКомпоновкиДанных
constexpr auto GUID_1099 = "b1668747-cd01-442e-84b7-15a47d05c599"; // ТипГруппыЭлементовОтбораКомпоновкиДанных;ТипГруппыЭлементовОтбораКомпоновкиДанных
constexpr auto GUID_1100 = "5627aeb9-f999-42ad-be77-51cd0b2d92ce"; // ПеречислениеТипГруппыЭлементовОтбораКомпоновкиДанных;ПеречислениеТипГруппыЭлементовОтбораКомпоновкиДанных
constexpr auto GUID_1101 = "c6a52555-d20f-452c-bfc2-1b53e9a56063"; // ТипДополненияПериодаКомпоновкиДанных;ТипДополненияПериодаКомпоновкиДанных
constexpr auto GUID_1102 = "30927beb-9381-4f31-a40c-35191162bcb3"; // ПеречислениеТипДополненияПериодаКомпоновкиДанных;ПеречислениеТипДополненияПериодаКомпоновкиДанных
constexpr auto GUID_1103 = "03fa8c34-dda4-461d-8fe6-6c0a3166c8e2"; // ТипЗаголовкаПолейКомпоновкиДанных;ТипЗаголовкаПолейКомпоновкиДанных
constexpr auto GUID_1104 = "73956c62-2fa0-4078-b719-b1c2a934f43b"; // ПеречислениеТипЗаголовкаПолейКомпоновкиДанных;ПеречислениеТипЗаголовкаПолейКомпоновкиДанных
constexpr auto GUID_1105 = "da4b7af4-a00e-465b-92b7-ae727eb137b6"; // ТипМакетаГруппировкиКомпоновкиДанных;ТипМакетаГруппировкиКомпоновкиДанных
constexpr auto GUID_1106 = "9e8607a4-3c39-4d5a-9c70-f54e03169e8b"; // ПеречислениеТипМакетаГруппировкиКомпоновкиДанных;ПеречислениеТипМакетаГруппировкиКомпоновкиДанных
constexpr auto GUID_1107 = "3d68054a-c67b-49e9-9a6e-4b7fb117430a"; // ТипМакетаОбластиКомпоновкиДанных;ТипМакетаОбластиКомпоновкиДанных
constexpr auto GUID_1108 = "3b3fde25-6664-42fa-96c8-be93725da5d2"; // ПеречислениеТипМакетаОбластиКомпоновкиДанных;ПеречислениеТипМакетаОбластиКомпоновкиДанных
constexpr auto GUID_1109 = "312b7d24-354b-4b13-93aa-d2e995c03c41"; // ТипОстаткаКомпоновкиДанных;ТипОстаткаКомпоновкиДанных
constexpr auto GUID_1110 = "a27e4c00-1e79-46a9-a944-df1e34883226"; // ПеречислениеТипОстаткаКомпоновкиДанных;ПеречислениеТипОстаткаКомпоновкиДанных
constexpr auto GUID_1111 = "ba51e852-a409-46ac-aadf-609bbb6e2058"; // ТипПериодаКомпоновкиДанных;ТипПериодаКомпоновкиДанных
constexpr auto GUID_1112 = "2a90e30a-a02b-49bb-90e8-d5a18e31dd47"; // ПеречислениеТипПериодаКомпоновкиДанных;ПеречислениеТипПериодаКомпоновкиДанных
constexpr auto GUID_1113 = "43499e55-7d53-4e3a-8f81-f46a9f882448"; // ТипРазмещенияТекстаКомпоновкиДанных;ТипРазмещенияТекстаКомпоновкиДанных
constexpr auto GUID_1114 = "5ba383fe-2e7c-4025-b515-2f99edbac077"; // ПеречислениеТипРазмещенияТекстаКомпоновкиДанных;ПеречислениеТипРазмещенияТекстаКомпоновкиДанных
constexpr auto GUID_1115 = "b26f564f-5f1c-425f-b129-ef20cbb9e1eb"; // ТипСвязиНаборовДанныхКомпоновкиДанных;ТипСвязиНаборовДанныхКомпоновкиДанных
constexpr auto GUID_1116 = "ebcddffc-3bbb-4e8f-a1b1-8df9eab7aa8f"; // ПеречислениеТипСвязиНаборовДанныхКомпоновкиДанных;ПеречислениеТипСвязиНаборовДанныхКомпоновкиДанных
constexpr auto GUID_1117 = "e607cd19-a3b8-46d1-8a63-db67184712d7"; // ТипЭлементаРезультатаКомпоновкиДанных;ТипЭлементаРезультатаКомпоновкиДанных
constexpr auto GUID_1118 = "590efeae-f74e-41e2-a79d-a3d2d140bf04"; // ПеречислениеТипЭлементаРезультатаКомпоновкиДанных;ПеречислениеТипЭлементаРезультатаКомпоновкиДанных
constexpr auto GUID_1119 = "89fbee88-57ba-4ea2-97b2-57f0fc2df426"; // РасположениеЛегендыДиаграммыКомпоновкиДанных;РасположениеЛегендыДиаграммыКомпоновкиДанных
constexpr auto GUID_1120 = "b8a629ef-d069-4650-9c62-8e11a0a60913"; // ПеречислениеРасположениеЛегендыДиаграммыКомпоновкиДанных;ПеречислениеРасположениеЛегендыДиаграммыКомпоновкиДанных
constexpr auto GUID_1121 = "27d7d459-265e-4fac-9685-d86b957f211f"; // ТипПримененияОтбораКомпоновкиДанных;ТипПримененияОтбораКомпоновкиДанных
constexpr auto GUID_1122 = "6dee8348-960f-4fc3-9134-194bc3eff49d"; // ПеречислениеТипПримененияОтбораКомпоновкиДанных;ПеречислениеТипПримененияОтбораКомпоновкиДанных
constexpr auto GUID_1123 = "9d0d2436-bf2a-4dab-8b8c-30a3c52c569e"; // РежимОтображенияЭлементаНастройкиКомпоновкиДанных;РежимОтображенияЭлементаНастройкиКомпоновкиДанных
constexpr auto GUID_1124 = "aab975a4-c607-4fa4-8f1d-c5b619f970f6"; // ПеречислениеРежимОтображенияЭлементаНастройкиКомпоновкиДанных;ПеречислениеРежимОтображенияЭлементаНастройкиКомпоновкиДанных
constexpr auto GUID_1125 = "c04ead79-749a-4981-915e-6fcb144f44e4"; // РежимОтображенияНастроекКомпоновкиДанных;РежимОтображенияНастроекКомпоновкиДанных
constexpr auto GUID_1126 = "2dc80139-9857-4d12-be42-7efebe8578c1"; // ПеречислениеРежимОтображенияНастроекКомпоновкиДанных;ПеречислениеРежимОтображенияНастроекКомпоновкиДанных
constexpr auto GUID_1127 = "987bb5e6-76c4-4c6d-8d12-e0a3b60c8fe3"; // ВажностьИнтернетПочтовогоСообщения;ВажностьИнтернетПочтовогоСообщения
constexpr auto GUID_1128 = "d83685f3-6026-4e34-a938-02cd58adb077"; // ПеречислениеВажностьИнтернетПочтовогоСообщения;ПеречислениеВажностьИнтернетПочтовогоСообщения
constexpr auto GUID_1129 = "46783db5-31b2-43ac-b0e5-b2557e1a15e2"; // ОбработкаТекстаИнтернетПочтовогоСообщения;ОбработкаТекстаИнтернетПочтовогоСообщения
constexpr auto GUID_1130 = "4fac0844-6a39-4a7e-9d18-048ffb94b87e"; // ПеречислениеОбработкаТекстаИнтернетПочтовогоСообщения;ПеречислениеОбработкаТекстаИнтернетПочтовогоСообщения
constexpr auto GUID_1131 = "a04f8e7f-4441-443a-ba20-84c8d412bd88"; // СпособSMTPАутентификации;СпособSMTPАутентификации
constexpr auto GUID_1132 = "c22f1819-cdfc-4c8c-81d4-07f1abac8093"; // ПеречислениеСпособSMTPАутентификации;ПеречислениеСпособSMTPАутентификации
constexpr auto GUID_1133 = "a284a518-5da1-4780-ae91-e12569ad6e04"; // СпособPOP3Аутентификации;СпособPOP3Аутентификации
constexpr auto GUID_1134 = "0651866f-b99a-4671-a53f-c786fc635d84"; // ПеречислениеСпособPOP3Аутентификации;ПеречислениеСпособPOP3Аутентификации
constexpr auto GUID_1135 = "cbd371c4-5d00-48c0-aa14-4db6a978d477"; // СпособКодированияИнтернетПочтовогоВложения;СпособКодированияИнтернетПочтовогоВложения
constexpr auto GUID_1136 = "d83a2a01-fbba-4c5f-8d03-a3e76bc0800c"; // ПеречислениеСпособКодированияИнтернетПочтовогоВложения;ПеречислениеСпособКодированияИнтернетПочтовогоВложения
constexpr auto GUID_1137 = "393e19f0-b256-4dd3-bbe9-4af4c5b309fd"; // СпособКодированияНеASCIIСимволовИнтернетПочтовогоСообщения;СпособКодированияНеASCIIСимволовИнтернетПочтовогоСообщения
constexpr auto GUID_1138 = "5fc3bcd4-3008-4a07-9f44-59dbade95d9d"; // ПеречислениеСпособКодированияНеASCIIСимволовИнтернетПочтовогоСообщения;ПеречислениеСпособКодированияНеASCIIСимволовИнтернетПочтовогоСообщения
constexpr auto GUID_1139 = "f6da3217-d8cf-40bc-9264-818c480339f1"; // ТипТекстаПочтовогоСообщения;ТипТекстаПочтовогоСообщения
constexpr auto GUID_1140 = "151e20d1-40c2-491b-ae09-858f273116fa"; // ПеречислениеТипТекстаПочтовогоСообщения;ПеречислениеТипТекстаПочтовогоСообщения
constexpr auto GUID_1141 = "5a4c8e65-815b-49c9-9dc5-4ef57ea75aeb"; // РежимТранзакцииЗаписиЖурналаРегистрации;РежимТранзакцииЗаписиЖурналаРегистрации
constexpr auto GUID_1142 = "77663a71-6475-4b47-b1c5-4181dcb87578"; // ПеречислениеРежимТранзакцииЗаписиЖурналаРегистрации;ПеречислениеРежимТранзакцииЗаписиЖурналаРегистрации
constexpr auto GUID_1143 = "15490cc1-856e-4f85-8b01-e52f2450740b"; // СтатусТранзакцииЗаписиЖурналаРегистрации;СтатусТранзакцииЗаписиЖурналаРегистрации
constexpr auto GUID_1144 = "bba8334d-1533-4e04-a743-29644d095926"; // ПеречислениеСтатусТранзакцииЗаписиЖурналаРегистрации;ПеречислениеСтатусТранзакцииЗаписиЖурналаРегистрации
constexpr auto GUID_1145 = "87345ce9-f140-4d75-92e1-4edcc38237cb"; // УровеньЖурналаРегистрации;УровеньЖурналаРегистрации
constexpr auto GUID_1146 = "1cf2ada0-e99f-4dd6-a19c-1447f2731c0e"; // ПеречислениеУровеньЖурналаРегистрации;ПеречислениеУровеньЖурналаРегистрации
constexpr auto GUID_1147 = "c6c53b05-dc12-4212-865a-c43f9d324cd7"; // МетодСжатияZIP;МетодСжатияZIP
constexpr auto GUID_1148 = "49ffe39d-d0c1-47a6-b00f-25057e407123"; // ПеречислениеМетодСжатияZIP;ПеречислениеМетодСжатияZIP
constexpr auto GUID_1149 = "f6e73a58-4e02-4b2e-bd1b-3784fc255551"; // МетодШифрованияZIP;МетодШифрованияZIP
constexpr auto GUID_1150 = "791bc0de-8751-4db8-8084-27f7426dfe09"; // ПеречислениеМетодШифрованияZIP;ПеречислениеМетодШифрованияZIP
constexpr auto GUID_1151 = "33e7b20e-a388-4955-a204-2d1db2b5eddd"; // РежимВосстановленияПутейФайловZIP;РежимВосстановленияПутейФайловZIP
constexpr auto GUID_1152 = "420eb837-fa8e-433d-8afc-d198304818e5"; // ПеречислениеРежимВосстановленияПутейФайловZIP;ПеречислениеРежимВосстановленияПутейФайловZIP
constexpr auto GUID_1153 = "232bab44-9e10-480a-9411-6092220f3867"; // РежимОбработкиПодкаталоговZIP;РежимОбработкиПодкаталоговZIP
constexpr auto GUID_1154 = "ddb771b3-1a36-4632-82a5-987bcd3f17e9"; // ПеречислениеРежимОбработкиПодкаталоговZIP;ПеречислениеРежимОбработкиПодкаталоговZIP
constexpr auto GUID_1155 = "c645c3c8-d299-42aa-a693-f6dba647d653"; // РежимСохраненияПутейZIP;РежимСохраненияПутейZIP
constexpr auto GUID_1156 = "3db1c00f-e715-431b-8c1b-ed6e4ad96169"; // ПеречислениеРежимСохраненияПутейZIP;ПеречислениеРежимСохраненияПутейZIP
constexpr auto GUID_1157 = "9f7c1e1c-6159-4c83-9930-ce23c3122dd1"; // УровеньСжатияZIP;УровеньСжатияZIP
constexpr auto GUID_1158 = "de3b8c2f-bc92-4496-9b03-fba0289897d9"; // ПеречислениеУровеньСжатияZIP;ПеречислениеУровеньСжатияZIP
constexpr auto GUID_1159 = "f7fd0df0-2a30-4d85-a8ce-afc5b705fb87"; // РежимБлокировкиДанных;РежимБлокировкиДанных
constexpr auto GUID_1160 = "1ca36539-86f1-4354-8cbb-a17ceb09cf48"; // ПеречислениеРежимБлокировкиДанных;ПеречислениеРежимБлокировкиДанных
constexpr auto GUID_1161 = "fb622b30-10ef-11d6-b9b9-0050bae0a95d"; // ВариантГраницыИнтервала;ВариантГраницыИнтервала
constexpr auto GUID_1162 = "fb622b32-10ef-11d6-b9b9-0050bae0a95d"; // ПеречислениеВариантГраницыИнтервала;ПеречислениеВариантГраницыИнтервала
constexpr auto GUID_1163 = "631d37cf-f454-4768-bbdb-c6d6374312dd"; // ВариантНастройкиПериода;ВариантНастройкиПериода
constexpr auto GUID_1164 = "cce74ff0-0a8a-44cb-95c6-c3f2c91a5931"; // ПеречислениеВариантНастройкиПериода;ПеречислениеВариантНастройкиПериода
constexpr auto GUID_1165 = "01269bd2-a912-464a-8f77-62104e5fa0c2"; // ВидКартинки;ВидКартинки
constexpr auto GUID_1166 = "05c9ca5d-2e74-40e3-8929-6b9583a0ca90"; // ПеречислениеВидКартинки;ПеречислениеВидКартинки
constexpr auto GUID_1167 = "e5eddbe0-bc77-4f95-b139-068c6d2f0f09"; // ВидРамки;ВидРамки
constexpr auto GUID_1168 = "7fba4fde-53c3-4a90-8bf3-ed86702d01cf"; // ПеречислениеВидРамки;ПеречислениеВидРамки
constexpr auto GUID_1169 = "7c626d2b-6cc1-4f6c-9367-352a9da94a2e"; // ВидЦвета;ВидЦвета
constexpr auto GUID_1170 = "855e72ce-dcee-4213-b394-e9a86f879930"; // ПеречислениеВидЦвета;ПеречислениеВидЦвета
constexpr auto GUID_1171 = "71be5c1b-80a3-4af8-a513-bcb1809976ac"; // ВидШрифта;ВидШрифта
constexpr auto GUID_1172 = "0b18e1f4-5545-4274-8eaa-8c5b18228e73"; // ПеречислениеВидШрифта;ПеречислениеВидШрифта
constexpr auto GUID_1173 = "1eb5c943-b0ef-11d5-a3c0-0050bae0a776"; // КодВозвратаДиалога;КодВозвратаДиалога
constexpr auto GUID_1174 = "1eb5c945-b0ef-11d5-a3c0-0050bae0a776"; // ПеречислениеКодВозвратаДиалога;ПеречислениеКодВозвратаДиалога
constexpr auto GUID_1175 = "43714470-06af-4a4a-9c95-462f8ba5e2ed"; // КодировкаXBase;КодировкаXBase
constexpr auto GUID_1176 = "43a96360-dfa3-4454-b8bf-56b2ae1a0409"; // ПеречислениеКодировкаXBase;ПеречислениеКодировкаXBase
constexpr auto GUID_1177 = "7f714470-06af-4a4a-9c95-462f8ba5e2ed"; // КодировкаТекста;КодировкаТекста
constexpr auto GUID_1178 = "eea96360-dfa3-4454-b8bf-56b2ae1a0409"; // ПеречислениеКодировкаТекста;ПеречислениеКодировкаТекста
constexpr auto GUID_1179 = "8acd280e-c29c-4543-8be7-7f78cad52c06"; // НаправлениеСортировки;НаправлениеСортировки
constexpr auto GUID_1180 = "7ee45c6e-2b87-4cd0-bf41-b561a0bf6556"; // ПеречислениеНаправлениеСортировки;ПеречислениеНаправлениеСортировки
constexpr auto GUID_1181 = "1eb5c940-b0ef-11d5-a3c0-0050bae0a776"; // РежимДиалогаВопрос;РежимДиалогаВопрос
constexpr auto GUID_1182 = "1eb5c942-b0ef-11d5-a3c0-0050bae0a776"; // ПеречислениеРежимДиалогаВопрос;ПеречислениеРежимДиалогаВопрос
constexpr auto GUID_1183 = "32c82ccd-fef3-4070-beb5-b9c52afc781d"; // РежимОкругления;РежимОкругления
constexpr auto GUID_1184 = "a47c4665-311c-405a-828e-0c5a3ca3bdda"; // ПеречислениеРежимОкругления;ПеречислениеРежимОкругления
constexpr auto GUID_1185 = "edc79c5f-f595-4e6d-b865-770fc3aa20f2"; // РежимПолнотекстовогоПоиска;РежимПолнотекстовогоПоиска
constexpr auto GUID_1186 = "edc79c5f-f595-4e6d-b865-770fc3aa20f4"; // ПеречислениеРежимПолнотекстовогоПоиска;ПеречислениеРежимПолнотекстовогоПоиска
constexpr auto GUID_1187 = "3a1cc5f5-5d3e-4914-a43a-2ae1f634dd9d"; // ПеречислениеРежимРабочейДаты;ПеречислениеРежимРабочейДаты
constexpr auto GUID_1188 = "66c64a63-c5f8-477f-beba-0a061835d517"; // СтатусСообщения;СтатусСообщения
constexpr auto GUID_1189 = "3b522af7-970d-48f6-aebf-fe54efd3bb9b"; // ПеречислениеСтатусСообщения;ПеречислениеСтатусСообщения
constexpr auto GUID_1190 = "570a2253-4d05-48d8-809b-fc86ace0624d"; // ПеречислениеТипПоведенияКлавишиEnter;ПеречислениеТипПоведенияКлавишиEnter
constexpr auto GUID_1191 = "bd58b10b-31eb-4e1d-bdd7-1e59e838627d"; // ВидОтображенияПолнотекстовогоПоиска;ВидОтображенияПолнотекстовогоПоиска
constexpr auto GUID_1192 = "bd58b10b-31eb-4e1d-bdd7-1e59e838627f"; // ПеречислениеВидОтображенияПолнотекстовогоПоиска;ПеречислениеВидОтображенияПолнотекстовогоПоиска
constexpr auto GUID_1193 = "2ff40405-45b0-4648-b6fb-10feab4fd73b"; // СостояниеФоновогоЗадания;СостояниеФоновогоЗадания
constexpr auto GUID_1194 = "3fb8f0dd-a68e-41f2-8a17-cdd2a60ef26a"; // ПеречислениеСостояниеФоновогоЗадания;ПеречислениеСостояниеФоновогоЗадания
constexpr auto GUID_1195 = "e0e10ff9-5035-407d-b34b-17da2c2c2c11"; // ВариантСтандартнойДатыНачала;ВариантСтандартнойДатыНачала
constexpr auto GUID_1196 = "a49e77ed-3f3f-401d-950d-d852806e94dd"; // ПеречислениеВариантСтандартнойДатыНачала;ПеречислениеВариантСтандартнойДатыНачала
constexpr auto GUID_1197 = "64918fa8-6f26-4dc3-90e6-b6d3f5b0087f"; // ВариантСтандартногоПериода;ВариантСтандартногоПериода
constexpr auto GUID_1198 = "2f4fb9e5-1e79-4fa3-935b-d6d218b30d64"; // ПеречислениеВариантСтандартногоПериода;ПеречислениеВариантСтандартногоПериода
constexpr auto GUID_1199 = "1c87578f-9e09-4ec0-a991-5629c87b1588"; // Чтение;Чтение
constexpr auto GUID_1200 = "33200740-82b0-4de7-8556-d3fb25ca4328"; // Добавление;Добавление
constexpr auto GUID_1201 = "287b74b8-3a66-4a76-ba27-4f1f6a93770e"; // Изменение;Изменение
constexpr auto GUID_1202 = "c0028105-4cc1-41ca-aef1-bfbd8fc8f8c4"; // Удаление;Удаление
constexpr auto GUID_1203 = "aa6448f2-be0f-42ea-ba26-1af7f52b5b65"; // Просмотр;Просмотр
constexpr auto GUID_1204 = "fb88c756-91c9-4351-9cdf-e027879886c6"; // Интерактивное добавление;Интерактивное добавление
constexpr auto GUID_1205 = "b7bab52d-c1b1-4bd8-8276-02db08d42352"; // Редактирование;Редактирование
constexpr auto GUID_1206 = "b53db6ed-6e5b-4035-8d24-f10083d646ed"; // Интерактивное удаление;Интерактивное удаление
constexpr auto GUID_1207 = "d76b72ba-5388-4b7f-af64-1b351f63a1e1"; // Интерактивная пометка на удаление;Интерактивная пометка на удаление
constexpr auto GUID_1208 = "798cf688-ad74-44fe-a464-236b49e910e0"; // Интерактивное снятие пометки удаления;Интерактивное снятие пометки удаления
constexpr auto GUID_1209 = "fa6dbe86-856a-4ac4-b8ac-bce99f8b8b22"; // Интерактивное удаление помеченных;Интерактивное удаление помеченных
constexpr auto GUID_1210 = "b5f861d3-d9c5-45ec-98bf-0ed4d489a351"; // Ввод по строке;Ввод по строке
constexpr auto GUID_1211 = "c6de80da-a4f7-4ce9-bbeb-0b00ea564ec1"; // Использование;Использование
constexpr auto GUID_1212 = "499e8968-ca89-43f0-9955-8756058b1b53"; // Получение;Получение
constexpr auto GUID_1213 = "1d306db2-d97e-4b57-9b28-5d21e838cd9e"; // Установка;Установка
constexpr auto GUID_1214 = "4d0d77ec-8511-430d-bd77-8407f27bc8f4"; // Интерактивная отмена проведения;Интерактивная отмена проведения
constexpr auto GUID_1215 = "3b869658-ebc9-49ff-9bb3-e7c59686f538"; // Интерактивная активация;Интерактивная активация
constexpr auto GUID_1216 = "65b6855f-85d5-4d33-ab75-be4485326dd5"; // Старт;Старт
constexpr auto GUID_1217 = "84487e82-eb6c-4c51-ae16-3a6db17e886d"; // Интерактивный старт;Интерактивный старт
constexpr auto GUID_1218 = "74fd69fa-368e-4292-956a-65eb2f9877bd"; // Выполнение;Выполнение
constexpr auto GUID_1219 = "5e664189-f0ee-439c-bdc5-eb81cca41ddf"; // Интерактивное выполнение;Интерактивное выполнение
constexpr auto GUID_1220 = "900e3c92-6e18-4874-846a-b28780b5b54c"; // Административные функции;Административные функции
constexpr auto GUID_1221 = "4d87a22d-ca7f-40ba-a367-a4eae62f4a7f"; // Обновление конфигурации базы данных;Обновление конфигурации базы данных
constexpr auto GUID_1222 = "8fb221e3-0d4f-43f2-ad71-1984cad63375"; // Монопольный режим;Монопольный режим
constexpr auto GUID_1223 = "fd05f656-7a23-43a4-8996-f480a806fb97"; // Активные пользователи;Активные пользователи
constexpr auto GUID_1224 = "1c799cf9-342d-4bf7-9b6f-951a009228ce"; // Журнал регистрации;Журнал регистрации
constexpr auto GUID_1225 = "02119c69-f08a-4142-9426-3725d74b7719"; // Внешнее соединение;Внешнее соединение
constexpr auto GUID_1226 = "07ef4641-f7da-417a-bd75-35c40a17c2f7"; // Automation;Automation
constexpr auto GUID_1227 = "7b8359dd-7d4e-4bcd-a61c-b4b26eae19c6"; // Интерактивное открытие внешних обработок;Интерактивное открытие внешних обработок
constexpr auto GUID_1228 = "eb29e198-c338-4a20-a253-be6fc3dd44d9"; // Интерактивное открытие внешних отчетов;Интерактивное открытие внешних отчетов
constexpr auto GUID_1229 = "31c3d4f6-7d02-4654-a14e-06aacafcb4fa"; // Вывод;Вывод
constexpr auto GUID_1230 = "24abfe06-289a-48c5-8bb4-032c733e45c5"; // Управление итогами;Управление итогами
constexpr auto GUID_1231 = "e060de25-bffd-42fd-bb09-f3a788d65760"; // Проведение;Проведение
constexpr auto GUID_1232 = "f55a8f7f-2c65-404f-b530-093d9006adba"; // Отмена проведения;Отмена проведения
constexpr auto GUID_1233 = "5d167fcc-b11f-403a-9a37-1eda64c19df1"; // Интерактивное проведение;Интерактивное проведение
constexpr auto GUID_1234 = "21b4742a-d335-4234-bf0f-a3074a0e31ac"; // Интерактивное проведение неоперативное;Интерактивное проведение неоперативное
constexpr auto GUID_1235 = "b0c0cbfc-f2cc-4b80-8460-5d5d7a599d9d"; // Интерактивное изменение проведенных;Интерактивное изменение проведенных
constexpr auto GUID_1236 = "0fc7e20d-f241-460c-bdf4-5ad88e5474a5"; // Надпись;Надпись
constexpr auto GUID_1237 = "6ff79819-710e-4145-97cd-1618da79e3e2"; // Кнопка;Кнопка
constexpr auto GUID_1238 = "151ef23e-6bb2-4681-83d0-35bc2217230c"; // Поле картинки;Поле картинки
constexpr auto GUID_1239 = "09ccdc77-ea1a-4a6d-ab1c-3435eada2433"; // Элементы управления;Элементы управления
constexpr auto GUID_1240 = "e69bf21d-97b2-4f37-86db-675aea9ec2cb"; // Командная панель;Командная панель
constexpr auto GUID_1241 = "35af3d93-d7c7-4a2e-a8eb-bac87a1a3f26"; // Флажок;Флажок
constexpr auto GUID_1242 = "381ed624-9217-4e63-85db-c4c3cb87daae"; // Поле ввода;Поле ввода
constexpr auto GUID_1243 = "ea83fe3a-ac3c-4cce-8045-3dddf35b28b1"; // Табличное поле;Табличное поле
constexpr auto GUID_1244 = "90db814a-c75f-4b54-bc96-df62e554d67d"; // Рамка группы;Рамка группы
constexpr auto GUID_1245 = "64483e7f-3833-48e2-8c75-2c31aac49f6e"; // Поле выбора;Поле выбора
constexpr auto GUID_1246 = "36e52348-5d60-4770-8e89-a16ed50a2006"; // Разделитель;Разделитель
constexpr auto GUID_1247 = "782e569a-79a7-4a4f-a936-b48d013936ec"; // Переключатель;Переключатель
constexpr auto GUID_1248 = "d92a805c-98ae-4750-9158-d9ce7cec2f20"; // Поле HTML;Поле HTML
constexpr auto GUID_1249 = "b1db1f86-abbb-4cf0-8852-fe6ae21650c2"; // Индикатор;Индикатор
constexpr auto GUID_1250 = "14c4a229-bfc3-42fe-9ce1-2da049fd0109"; // Поле текстового документа;Поле текстового документа
constexpr auto GUID_1251 = "a26da99e-184a-4823-b0d6-62816d38dc4e"; // Сводная диаграмма;Сводная диаграмма
constexpr auto GUID_1252 = "a8b97779-1a4b-4059-b09c-807f86d2a461"; // Диаграмма;Диаграмма
constexpr auto GUID_1253 = "e5fdc112-5c84-4a16-9728-72b85692b6e2"; // Диаграмма Ганта;Диаграмма Ганта
constexpr auto GUID_1254 = "984981b1-622d-4ebc-94f7-885f0cdfb59a"; // Дендрограмма;Дендрограмма
constexpr auto GUID_1255 = "ad37194e-555e-4305-b718-5dca84baf145"; // Поле географической схемы;Поле географической схемы
constexpr auto GUID_1256 = "42248403-7748-49da-b782-e4438fd7bff3"; // Поле графической схемы;Поле графической схемы
constexpr auto GUID_1257 = "e3c063d8-ef92-41be-9c89-b70290b5368b"; // Поле календаря;Поле календаря
constexpr auto GUID_1258 = "6c06cd5d-8481-4b6f-a90a-7a97a8bb8bef"; // Полоса регулирования;Полоса регулирования
constexpr auto GUID_1259 = "236a17b3-7f44-46d9-a907-75f9cdc61ab5"; // Поле табличного документа;Поле табличного документа
constexpr auto GUID_1260 = "19f8b798-314e-4b4e-8121-905b2a7a03f5"; // Поле списка;Поле списка
constexpr auto GUID_1261 = "e1692cc2-605b-4535-84dd-28440238746c"; // Событие;Событие
constexpr auto GUID_1262 = "510405d3-2a0c-4fea-960a-7fee59b32f9b"; // Стандартный реквизит;Стандартный реквизит
constexpr auto GUID_1263 = "90ae4b5d-e0fd-49ef-a008-d67c1e75038c"; // Режим пароля (параметр стандартного реквизита);Режим пароля (параметр стандартного реквизита)
constexpr auto GUID_1264 = "2bbba66b-fabf-4863-8ba3-54b3c64c896e"; // Многострочный режим (параметр стандартного реквизита);Многострочный режим (параметр стандартного реквизита)
constexpr auto GUID_1265 = "4de03908-56f4-4396-a61e-17253afca9ac"; // Расширенное редактирование (параметр стандартного реквизита);Расширенное редактирование (параметр стандартного реквизита)
constexpr auto GUID_1266 = "2c8143d5-4248-4c43-8bfb-307c0be2e415"; // Заполнять из данных заполнения (параметр стандартного реквизита);Заполнять из данных заполнения (параметр стандартного реквизита)
constexpr auto GUID_1267 = "cf4abea4-37b2-11d4-940f-008048da11f9"; // Комментарий (параметр стандартного реквизита);Комментарий (параметр стандартного реквизита)
constexpr auto GUID_1268 = "cf4abea3-37b2-11d4-940f-008048da11f9"; // Синоним (параметр стандартного реквизита);Синоним (параметр стандартного реквизита)
constexpr auto GUID_1269 = "2723eb98-b4c1-498a-a6f3-70444757902f"; // Проверка заполнения (параметр стандартного реквизита);Проверка заполнения (параметр стандартного реквизита)
constexpr auto GUID_1270 = "d4232326-022b-421e-b6d3-88e418f74327"; // Полнотекстовый поиск (параметр стандартного реквизита);Полнотекстовый поиск (параметр стандартного реквизита)
constexpr auto GUID_1271 = "4690ff70-e3fa-4914-9127-6a9acc5fc949"; // Подсказка (параметр стандартного реквизита);Подсказка (параметр стандартного реквизита)
constexpr auto GUID_1272 = "e6b3f5f3-bdf3-4ad0-bc60-7323b3feb208"; // Значение заполнения (параметр стандартного реквизита);Значение заполнения (параметр стандартного реквизита)
constexpr auto GUID_1273 = "580c29e2-8af4-4258-882a-7cf8073e61c8"; // Формат (параметр стандартного реквизита);Формат (параметр стандартного реквизита)
constexpr auto GUID_1274 = "88149a78-9448-4767-867b-0e650d165d2e"; // Формат редактирования (параметр стандартного реквизита);Формат редактирования (параметр стандартного реквизита)
constexpr auto GUID_1275 = "e3da683b-c54a-457a-a243-b9b4f9bf76dd"; // Связи параметров выбора (параметр стандартного реквизита);Связи параметров выбора (параметр стандартного реквизита)
constexpr auto GUID_1276 = "fcf503b8-1c06-454a-970c-06413e64aee5"; // Параметры выбора (параметр стандартного реквизита);Параметры выбора (параметр стандартного реквизита)
constexpr auto GUID_1277 = "6e3a1131-37a3-4da5-8895-572d9d0c9db6"; // Быстрый выбор (параметр стандартного реквизита);Быстрый выбор (параметр стандартного реквизита)
constexpr auto GUID_1278 = "6c4f7074-e7d4-48eb-b31b-132873666262"; // Форма выбора (параметр стандартного реквизита);Форма выбора (параметр стандартного реквизита)
constexpr auto GUID_1279 = "1183c14f-f814-49c6-9233-a3c26b3f64cf"; // Связь по типу (параметр стандартного реквизита);Связь по типу (параметр стандартного реквизита)
constexpr auto GUID_1280 = "3eaf5a8b-06d6-47b0-ac7d-a9698247f499"; // Максимальное значение (параметр стандартного реквизита);Максимальное значение (параметр стандартного реквизита)
constexpr auto GUID_1281 = "b02800e9-a8d1-42ab-9a12-f673e92be968"; // Выделять отрицательные (параметр стандартного реквизита);Выделять отрицательные (параметр стандартного реквизита)
constexpr auto GUID_1282 = "c65a541f-0b91-4f33-bc88-fbaaa57f9992"; // Минимальное значение (параметр стандартного реквизита);Минимальное значение (параметр стандартного реквизита)
constexpr auto GUID_1283 = "f49e4ced-4033-4e6c-8755-9fbaaccd6078"; // Маска (параметр стандартного реквизита);Маска (параметр стандартного реквизита)

constexpr auto CControlPanel = "Панель";
constexpr auto CControlCommandBar = "Командная панель";
constexpr auto CControlEdit = "Поле ввода";
constexpr auto CControlGridColumn = "Колонка таблицы";
constexpr auto CControlGrid = "Таблица";
constexpr auto CControlSmartEdit = "Умное поле ввода";
constexpr auto CControlValuesList = "Список значений";
constexpr auto CControlDropList = "Выпадающий список";
constexpr auto CControlCheckBox = "Флажек";
constexpr auto CControlRadioGroup = "Контролер переключателя";
constexpr auto CCOntrolRadioButton = "Переключатель";
constexpr auto CControlProgressBar = "Индикатор";
constexpr auto CControlSlider = "Полоса регулирования";
constexpr auto CControlSplitter = "Разделитель";

constexpr auto CGUIDPanel = "09CCDC77-EA1A-4A6D-AB1C-3435EADA2433";
constexpr auto CGUIDCommandBar = "E69BF21D-97B2-4f37-86DB-675AEA9EC2CB";
constexpr auto CGUIDEditField = "A7CBE72D-8E4E-466F-8796-06851021A914";
constexpr auto CGUIDGridColumn = "48A6EBC3-FCC8-4F8F-B399-459FB32AA46B";
constexpr auto CGUIDGrid = "342CF854-134C-42BB-8AF9-A2103D5D9723";
constexpr auto CGUIDSmartEdit = "381ED624-9217-4E63-85DB-C4C3CB87DAAE";
constexpr auto CGUIDValuesList = "1A8E49A1-4DAD-4421-8145-6B379F9935C7";
constexpr auto CGuidDropList = "62EA50F7-6461-4504-BE85-85D2BD1A6012";
constexpr auto CGUIDCheckBox = "18CDC661-1873-422E-8FC5-9A6B24A97A2E";
constexpr auto CGUIDRadioGroup = "FCA02E22-79F6-402a-8771-2295867A3C8F";
constexpr auto CGUIDRadioButton = "34393F87-C229-4D0C-9086-2661B9BE8330";
constexpr auto CGUIDProgressBar = "99446F23-3670-47F3-8EED-1EFDCEFBB90D";
constexpr auto CGuidSlider = "3ED9965C-9591-4D56-A693-7AA89A715740";
constexpr auto CGUIDSplitter = "B9404EA3-F841-4018-BE17-49B54B5070C0";
constexpr auto CCommandPanelGuid = "9CA116F6-D116-470B-9612-4ECB6E69AA9C";
constexpr auto SysPropID = "B5F3F9B6-3B17-4129-A5B2-B50F63FCA85D";
constexpr auto SysPropMARK = "E256B574-089D-4E2A-A273-4755B3D618A8";
constexpr auto SysPropVERSION = "DCCF8B63-DF27-4f70-BD53-BD969E6A9158";
constexpr auto SysPropNUMBER = "EDFDA0E9-1922-4105-804A-BAB271073908";  //doc
constexpr auto SysPropDATE = "B75A8697-39CA-4b64-BAB5-5AEC9D49DE1E";  //doc
constexpr auto DocWithForms = "FB880E93-47D7-4127-9357-A20E69C17545";
constexpr auto DocWithParams = "45E46CBC-3E24-4165-8B7B-CC98A6F80211";
constexpr auto DocWithTables = "21C53E09-8950-4B5E-A6A0-1054F1BBC274";
constexpr auto SysPropDESCR = "9CFE5579-8A45-443B-826C-B4A5FA016A8A"; //ref
constexpr auto SysPropCODE = "89625AEA-8846-48f1-9A7E-C36422E1BFA0"; //ref
constexpr auto refWithForms = "FDF816D2-1EAD-11D5-B975-0050BAE0A95D";
constexpr auto RefWithParams = "cf4abea7-37b2-11d4-940f-008048da11f9";
constexpr auto RefWithTables = "932159F9-95B2-4E76-A8DD-8849FE5C5DED";
constexpr auto RegWithForms = "B64D9A44-1642-11D6-A3C7-0050BAE0A776";  //registers
constexpr auto RegResources = "B64D9A41-1642-11D6-A3C7-0050BAE0A776";  //???
constexpr auto RegInfoForms = "13134204-F60B-11D5-A3C7-0050BAE0A776";  //регистр сведений
constexpr auto RegInfoRes = "13134202-F60B-11D5-A3C7-0050BAE0A776";
constexpr auto RegInfoDim = "13134203-F60B-11D5-A3C7-0050BAE0A776";
constexpr auto RegInfoProps = "A2207540-1400-11D6-A3C7-0050BAE0A776";
constexpr auto SubsysForm = "D5B0E5ED-256D-401C-9C36-F630CAFD8A62";
constexpr auto ReportForms = "A3B368C0-29E2-11D6-A3C7-0050BAE0A776";
constexpr auto CommonModules = "0FE48980-252D-11D6-A3C7-0050BAE0A776";  //список общих модулей
constexpr auto Subsystems = "37F2FA9A-B276-11D4-9435-004095E12FC7";  //список подсистем
constexpr auto Documents = "061D872A-5787-460E-95AC-ED74EA3A3E84";  //список документов
constexpr auto WebServices = "8657032E-7740-4E1D-A3BA-5DD6E8AFB78F";  //список WEBсервисов
constexpr auto XDTAPackets = "CC9DF798-7C94-4616-97D2-7AA0B7BC515E";  //список XDTA-пакетов
constexpr auto EventLinks = "4E828DA6-0F44-4B5B-B1C0-A2B3CFE7BDCC";  //список подписок на события
constexpr auto PlanedTasks = "11BDAF85-D5AD-4D91-BB24-AA0EEE139052";  //список регламентых заданий
constexpr auto ValueHost = "E199CA70-93CF-46CE-A54B-6EDC88C3A296";  //тип поля - хранилище значения
constexpr auto Reports = "631B75A0-29E2-11D6-A3C7-0050BAE0A776";  //список отчетов
constexpr auto CalcVarsList = "BF845118-327B-4682-B5C6-285D2A0EB296";  //список обработок
constexpr auto RegAccumList = "B64D9A40-1642-11D6-A3C7-0050BAE0A776";  //список регистров накопления
constexpr auto RegInfoList = "13134201-F60B-11D5-A3C7-0050BAE0A776";  //список регистров сведений
constexpr auto GUID_References = "CF4ABEA6-37B2-11D4-940F-008048DA11F9";  //список справочников







constexpr const char* GUID_config = "30ffe4cc-eef2-4371-8b26-046597e37e22";
constexpr const char* GUID_lang   = "ae3cd3da-a1c0-4b8e-8edf-4d25e853a54e";

constexpr const char* file_root     = "root";
constexpr const char* file_version  = "version";
constexpr const char* file_versions = "versions";

constexpr auto CMetadataFileName     = "metadata";     // имя файла, хранящего структуру метаданных конфигурации
constexpr auto CRootMDObjectFileName = "root";         // имя файла, хранящего идентификатор корневого объекта метаданных(контейнера)
constexpr auto CFileNameVersion      = "version";      // имя файла, хранящего версию конфигурации в целом
constexpr auto CFileNameVersions     = "versions";     // имя файла, хранящего список версий хранящихся файлов
constexpr auto CDeletedListFileName  = "deleted";      // имя файла, в котором хранится список удаленных файлов.
constexpr auto CCommitPhaseFileName  = "commit";       // имя файла обозначающего последнюю фазу сохранения | построения
constexpr auto CConvertPhaseFileName = "convertPhase"; // имя файла обозначающего фазу конвертации

// идентификаторы, используемые при формировании идентификатора файла
constexpr auto CGlobalModuleMDPropTerm = "МодульПриложения";
constexpr auto CExternalConnectionModuleMDPropTerm = "МодульВнешнегоСоединения";


constexpr const char* _root_ =
"{2,30ffe4cc-eef2-4371-8b26-046597e37e22,h55/Mge2fMFztQsFisVlH3XXYBo/afhvXqqsee54Ki3K7GqjefSutU5iFD5GFXc2\n"
"ANz7GLei9du1H2euYINWQg==}";

constexpr const char* _version_ =
"{\n"
"{216,0,\n"
"{80316,0}\n"
"}\n"
"}";

constexpr const char* _versions_ = "{1,6,\"\",b091ac3f-01c3-4eb3-baaa-b35922abaccd,\"30ffe4cc-eef2-4371-8b26-046597e37e22\",76dc5902-3208-497a-8bbb-b57b81c49c25,\"ae3cd3da-a1c0-4b8e-8edf-4d25e853a54e\",181e11fb-0c66-4452-a13c-4421d903566a,\"root\",3e2c7a91-6df6-42be-a959-0e75547a12ce,\"version\",271e22c1-57f1-4d9a-a915-fedaff6e3f2c,\"versions\",2edceba4-96e0-4f37-997e-b2c65ba732ff}";

constexpr const char* _lang_83_ =
"{1,\n"
"{0,\n"
"{2,\n"
"{1,0,ae3cd3da-a1c0-4b8e-8edf-4d25e853a54e},\"Русский\",\n"
"{1,\"ru\",\"Русский\"},\"\",0,0,00000000-0000-0000-0000-000000000000},\"ru\" }, 0}";

constexpr const char* _conf_root_83_ =
"{2,\n"
"{30ffe4cc-eef2-4371-8b26-046597e37e22},6,\n"
"{9cd510cd-abfc-11d4-9434-004095e12fc7,\n"
"{1,\n"
"{59,\n"
"{0,\n"
"{2,\n"
"{1,0,53a9569f-8670-44b8-b424-dee2dce96e57},\"ИмяКонфигурации\",\n"
"{1,\"ru\",\"Синоним конфигурации (имя конфигурации)\"},\"\",0,2,7f676314-716a-4d54-8335-a71a3857b21c,3,9dfcabbf-6a7a-48aa-8721-df5e78b367c6,3,00000000-0000-0000-0000-000000000000}\n"
//"{1,0,53a9569f-8670-44b8-b424-dee2dce96e57},\"BB71D8BD57664101889B95C34FEA2351\",\n"
//"{1,\"ru\",\"B b71 d8 b d57664101889 b95 c34 FEA2351\"},\"\",0,2,7f676314-716a-4d54-8335-a71a3857b21c,3,9dfcabbf-6a7a-48aa-8721-df5e78b367c6,3,00000000-0000-0000-0000-000000000000}\n"
"},\"\",1,\n"
"{0},\n"
"{0},\n"
"{0},\n"
"{0},\n"
"{0},00000000-0000-0000-0000-000000000000,ae3cd3da-a1c0-4b8e-8edf-4d25e853a54e,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,0,\"\",\"\",\"\",1,\n"
"{0,0},1,\n"
"{0,0},1,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,80316,\n"
"{0,0},0,0,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,\n"
"{1,\n"
"{\"#\",1708fdaa-cbce-4289-b373-07a5a74bee91,1}\n"
"},00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,2,00000000-0000-0000-0000-000000000000,3,\n"
"{0,0},\n"
"{24,\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,9},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,1},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,10},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,2},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,3},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,5},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,6},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,7},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,8},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,11},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,12},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,16},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,17},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,18},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,19},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,20},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,21},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,22},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,23},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,24},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,25},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,26},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,27},\n"
"{\"B\",0}\n"
"},\n"
"{\n"
"{\"#\",e4c53f94-e5f7-4a34-8c10-218bd811cae1,28},\n"
"{\"B\",1}\n"
"}\n"
"},2,\"\",80316,1,0,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,00000000-0000-0000-0000-000000000000,1,00000000-0000-0000-0000-000000000000,\n"
"{1,24,\n"
"{1,0,0},\n"
"{2,0,0},\n"
"{3,0,0},\n"
"{5,0,0},\n"
"{6,0,0},\n"
"{7,0,0},\n"
"{8,0,0},\n"
"{9,0,0},\n"
"{10,0,0},\n"
"{11,0,0},\n"
"{12,0,0},\n"
"{16,0,0},\n"
"{17,0,0},\n"
"{18,0,0},\n"
"{19,0,0},\n"
"{20,0,0},\n"
"{21,0,0},\n"
"{22,0,0},\n"
"{23,0,0},\n"
"{24,0,0},\n"
"{25,0,0},\n"
"{26,0,0},\n"
"{27,0,0},\n"
"{28,1,0}\n"
"},\n"
"{0,0}\n"
"},23,\n"
"{09736b02-9cac-4e3f-b4f7-d3e9576ab948,0},\n"
"{0c89c792-16c3-11d5-b96b-0050bae0a95d,0},\n"
"{0fe48980-252d-11d6-a3c7-0050bae0a776,0},\n"
"{0fffc09c-8f4c-47cc-b41c-8d5c5a221d79,0},\n"
"{11bdaf85-d5ad-4d91-bb24-aa0eee139052,0},\n"
"{15794563-ccec-41f6-a83c-ec5f7b9a5bc1,0},\n"
"{24c43748-c938-45d0-8d14-01424a72b11e,0},\n"
"{30d554db-541e-4f62-8970-a1c6dcfeb2bc,0},\n"
"{37f2fa9a-b276-11d4-9435-004095e12fc7,0},\n"
"{39bddf6a-0c3c-452b-921c-d99cfa1c2f1b,0},\n"
"{3e5404af-6ef8-4c73-ad11-91bd2dfac4c8,0},\n"
"{3e7bfcc0-067d-11d6-a3c7-0050bae0a776,0},\n"
"{46b4cd97-fd13-4eaa-aba2-3bddd7699218,0},\n"
"{4e828da6-0f44-4b5b-b1c0-a2b3cfe7bdcc,0},\n"
"{58848766-36ea-4076-8800-e91eb49590d7,0},\n"
"{7dcd43d9-aca5-4926-b549-1842e6a4e8cf,0},\n"
"{857c4a91-e5f4-4fac-86ec-787626f1c108,0},\n"
"{8657032e-7740-4e1d-a3ba-5dd6e8afb78f,0},\n"
"{9cd510ce-abfc-11d4-9434-004095e12fc7,1,ae3cd3da-a1c0-4b8e-8edf-4d25e853a54e},\n"
"{af547940-3268-434f-a3e7-e47d6d2638c3,0},\n"
"{c045099e-13b9-4fb6-9d50-fca00202971e,0},\n"
"{cc9df798-7c94-4616-97d2-7aa0b7bc515e,0},\n"
"{d26096fb-7a5d-4df9-af63-47d04771fa9b,0}\n"
"}\n"
"},\n"
"{9fcd25a0-4822-11d4-9414-008048da11f9,\n"
"{6,\n"
"{1,\n"
"{\n"
"{1,0,df725343-700b-493f-914f-c98ccac10414},00000000-0000-0000-0000-000000000000},15,\n"
"{0195e80c-b157-11d4-9435-004095e12fc7,0},\n"
"{061d872a-5787-460e-95ac-ed74ea3a3e84,0},\n"
"{07ee8426-87f1-11d5-b99c-0050bae0a95d,0},\n"
"{13134201-f60b-11d5-a3c7-0050bae0a776,0},\n"
"{1c57eabe-7349-44b3-b1de-ebfeab67b47d,0},\n"
"{2f1a5187-fb0e-4b05-9489-dc5dd6412348,0},\n"
"{36a8e346-9aaa-4af9-bdbd-83be3c177977,0},\n"
"{4612bd75-71b7-4a5c-8cc5-2b0b65f9fa0d,0},\n"
"{631b75a0-29e2-11d6-a3c7-0050bae0a776,0},\n"
"{82a1b659-b220-4d94-a9bd-14d757b95a48,0},\n"
"{b64d9a40-1642-11d6-a3c7-0050bae0a776,0},\n"
"{bc587f20-35d9-11d6-a3c7-0050bae0a776,0},\n"
"{bf845118-327b-4682-b5c6-285d2a0eb296,0},\n"
"{cf4abea6-37b2-11d4-940f-008048da11f9,0},\n"
"{f6a80749-5ad7-400b-8519-39dc5dff2542,0}\n"
"}\n"
"}\n"
"},\n"
"{e3687481-0a87-462c-a166-9f34594f9bba,\n"
"{1,\n"
"{0,\n"
"{1,0,1253d360-e2ba-490e-bdc2-43d2c9025924}\n"
"},2,\n"
"{238e7e88-3c5f-48b2-8a3b-81ebbecb20ed,0},\n"
"{2deed9b8-0056-4ffe-a473-c20a6c32a0bc,0}\n"
"}\n"
"},\n"
"{9de14907-ec23-4a07-96f0-85521cb6b53b,\n"
"{1,\n"
"{\n"
"{1,0,63655d7a-38b0-4a9b-a2b3-ec9d3a076fcc}\n"
"},2,\n"
"{30b100d6-b29f-47ac-aec7-cb8ca8a54767,0},\n"
"{f2de87a8-64e5-45eb-a22d-b3aedab050e7,0}\n"
"}\n"
"},\n"
"{51f2d5d8-ea4d-4064-8892-82951750031e,\n"
"{1,\n"
"{0,\n"
"{1,0,46f0e3c2-0590-44c9-953f-7fce90ecd2ac}\n"
"},2,\n"
"{3e63355c-1378-4953-be9b-1deb5fb6bec5,0},\n"
"{fcd3404e-1523-48ce-9bc0-ecdb822684a1,0}\n"
"}\n"
"},\n"
"{e68182ea-4237-4383-967f-90c1e3370bc7,\n"
"{1,\n"
"{\n"
"{1,0,ab48276d-b9e8-45a9-9e4e-bc8f7bea0e0b}\n"
"},1,\n"
"{5274d9fc-9c3a-4a71-8f5e-a0db8ab23de5,0}\n"
"}\n"
"},\n"
"{\n"
"{0,\"\",\"\"}\n"
"}\n"
"}";
#endif

