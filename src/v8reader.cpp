//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <exception>
#include <signal.h>

#include <System.IOUtils.hpp>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
USEFORM("MainUnit.cpp", MainForm);
//---------------------------------------------------------------------------

static bool IsCrashLoggingEnabled()
{
	String envValue = Trim(GetEnvironmentVariable(L"V8READER_CRASH_LOG")).LowerCase();
	if (envValue == L"0" || envValue == L"false" || envValue == L"no" || envValue == L"off")
		return false;
	if (envValue == L"1" || envValue == L"true" || envValue == L"yes" || envValue == L"on")
		return true;

	for (int i = 1; i <= ParamCount(); i++)
	{
		String arg = Trim(ParamStr(i)).LowerCase();
		if (arg == L"--no-crash-log" || arg == L"/no-crash-log")
			return false;
		if (arg == L"--crash-log" || arg == L"/crash-log")
			return true;
	}

	return false;
}

static void WriteCrashLog(const String& message)
{
	if (!IsCrashLoggingEnabled())
		return;

	try
	{
		String appDir = ExtractFilePath(ParamStr(0));
		String logfile = TPath::Combine(appDir, "v8reader_fatal.log");
		TFileStream* log = NULL;
		if (FileExists(logfile))
		{
			log = new TFileStream(logfile, fmOpenReadWrite | fmShareDenyNone);
			log->Seek(0, soFromEnd);
		}
		else
		{
			log = new TFileStream(logfile, fmCreate | fmShareDenyNone);
			DynamicArray<System::Byte> preamble = TEncoding::UTF8->GetPreamble();
			if (preamble.Length > 0)
				log->WriteBuffer(&preamble[0], preamble.Length);
		}

		TStreamWriter* sw = new TStreamWriter(log, TEncoding::UTF8, 4096);
		TFormatSettings fs;
		fs.DateSeparator = L'.';
		fs.TimeSeparator = L':';
		fs.ShortDateFormat = L"dd.mm.yyyy";
		fs.LongTimeFormat = L"hh:mm:ss:zzz";
		sw->Write(DateTimeToStr(Now(), fs));
		sw->Write(L" ");
		sw->Write(message);
		sw->Write(L"\r\n\r\n");
		delete sw;
		delete log;
	}
	catch (...) {}
}

static void OnTerminateHandler()
{
	WriteCrashLog(L"std::terminate called");
	abort();
}

static void SignalAbortHandler(int signalCode)
{
	WriteCrashLog(L"signal received: " + IntToStr(signalCode));
	::_exit(3);
}

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	std::set_terminate(OnTerminateHandler);
	signal(SIGABRT, SignalAbortHandler);
	signal(SIGTERM, SignalAbortHandler);
	signal(SIGINT, SignalAbortHandler);
	WriteCrashLog(L"Application bootstrap");

	try
	{
		WriteCrashLog(L"Application start");
		Application->Initialize();
		WriteCrashLog(L"Application initialized");
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		WriteCrashLog(L"Main form created");
		Application->Run();
		WriteCrashLog(L"Application finished normally");
	}
	catch (Exception &exception)
	{
		WriteCrashLog(L"Unhandled VCL exception: " + exception.Message);
		Application->ShowException(&exception);
	}
	catch (...)
	{
		WriteCrashLog(L"Unhandled non-VCL exception");
		try
		{
			throw Exception("Unhandled non-VCL exception");
		}
		catch (Exception &exception)
		{
			WriteCrashLog(L"Converted non-VCL exception: " + exception.Message);
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
