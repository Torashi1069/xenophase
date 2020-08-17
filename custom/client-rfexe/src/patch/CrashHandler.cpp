#include "Config.h"
#include "CrashHandler.h"
#include "AutoRelease/AutoRelease.hpp"
#include <dbghelp.h>


static MINIDUMP_TYPE GetDumpType()
{
	switch( config()->crash_handler )
	{
	default:
	case 2: // minidump (small file, 40kB)
		return MINIDUMP_TYPE(MiniDumpNormal);
	break;
	case 3: // basic dump (180MB, 20MB rar)
		return MINIDUMP_TYPE(MiniDumpWithPrivateReadWriteMemory);
	break;
	case 4: // extended dump (240MB, 40MB rar)
		return MINIDUMP_TYPE(MiniDumpWithPrivateReadWriteMemory|MiniDumpWithDataSegs|MiniDumpWithCodeSegs|MiniDumpWithHandleData|MiniDumpWithThreadInfo|MiniDumpWithProcessThreadData|MiniDumpWithFullMemoryInfo);
	break;
	case 9: // full dump (embeds data.grf, do not use!)
		return MINIDUMP_TYPE(MiniDumpWithFullMemory);
	break;
	}
}


static bool WriteDump(const wchar_t* DumpFilePath, MINIDUMP_TYPE DumpType, EXCEPTION_POINTERS* ExceptionInfo)
{
	HMODULE hDbgHelpDll = LoadLibraryW(L"dbghelp.dll");
	AUTORELEASEL(hDbgHelpDll, (HMODULE& hDll) { FreeLibrary(hDll); });
	if( hDbgHelpDll == NULL )
		return false;

	typedef BOOL (WINAPI* WRITEDUMPFUNC)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, CONST PMINIDUMP_EXCEPTION_INFORMATION, CONST PMINIDUMP_USER_STREAM_INFORMATION, CONST PMINIDUMP_CALLBACK_INFORMATION);
	WRITEDUMPFUNC pfnWriteDump = (WRITEDUMPFUNC)GetProcAddress(hDbgHelpDll, "MiniDumpWriteDump");
	if( pfnWriteDump == NULL )
		return false;

	HANDLE hDumpFile = CreateFileW(DumpFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	AUTORELEASEL(hDumpFile, (HANDLE& hFile) { CloseHandle(hFile); });
	if( hDumpFile == INVALID_HANDLE_VALUE )
		return false;

	MINIDUMP_EXCEPTION_INFORMATION ExInfo;
	ExInfo.ThreadId = GetCurrentThreadId();
	ExInfo.ExceptionPointers = ExceptionInfo;
	ExInfo.ClientPointers = FALSE;

	pfnWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, DumpType, &ExInfo, NULL, NULL);
	return true;
}


static LONG WINAPI CrashHandlerFunc(EXCEPTION_POINTERS* pExceptionInfo)
{
	const wchar_t* crashmsg = L"The client has crashed and will now proceed to save a memory dump for diagnostic purposes. This may take several seconds.";
	MessageBoxW(NULL, crashmsg, L"Crash report", MB_OK|MB_ICONERROR);

	time_t unixtime;
	time(&unixtime);
	wchar_t Timestamp[19+1];
	wcsftime(Timestamp, countof(Timestamp), L"%Y-%m-%d-%H-%M-%S", localtime(&unixtime));

	wchar_t DumpFileName[MAX_PATH];
	_snwprintf(DumpFileName, countof(DumpFileName), L"rfexe-crash-%s.dmp", Timestamp);

	WriteDump(DumpFileName, GetDumpType(), pExceptionInfo);

	const wchar_t* restartmsg = L"Memory dump complete. The client will now restart.";
	MessageBoxW(NULL, restartmsg, L"Crash report", MB_OK|MB_ICONINFORMATION);

	STARTUPINFOW si = { sizeof(si) };
	PROCESS_INFORMATION pi = {};
	CreateProcessW(L"RagnarokFrontier.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	return EXCEPTION_EXECUTE_HANDLER;
}


static hook_func<LPTOP_LEVEL_EXCEPTION_FILTER (WINAPI *)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)> _SetUnhandledExceptionFilter("SetUnhandledExceptionFilter");
static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI my_SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	switch( config()->crash_handler )
	{
	case 0: // no handler
		return NULL;
	case 1: // standard Gravity error handler
		return _SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
	default: // our memory crash handler
		return _SetUnhandledExceptionFilter(&CrashHandlerFunc);
	};
}


void CrashHandler::Initialize()
{
	HookDB::DB().Hook("SetUnhandledExceptionFilter", _SetUnhandledExceptionFilter, &my_SetUnhandledExceptionFilter);
}
