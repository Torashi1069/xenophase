#include "ExceptionHandler.h"
#include "Globals.h"
#include <dbghelp.h>


char (& exception_log)[8096] = *(char(*)[8096])DetourFindFunction(SAKEXE, "exception_log"); // = ?


hook_func<INT_PTR (CALLBACK *)(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)> _DialogProc(SAKEXE, "DialogProc");
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) // line 24
{
	return (_DialogProc)(hwndDlg, uMsg, wParam, lParam);

	//TODO
}


hook_func<BOOL (CALLBACK *)(PCSTR ModuleName, ULONG ModuleBase, ULONG ModuleSize, PVOID UserContext)> _EnumerateLoadedModulesProc(SAKEXE, "EnumerateLoadedModulesProc");
BOOL CALLBACK EnumerateLoadedModulesProc(PCSTR ModuleName, ULONG ModuleBase, ULONG ModuleSize, PVOID UserContext) // line 74
{
	return (_EnumerateLoadedModulesProc)(ModuleName, ModuleBase, ModuleSize, UserContext);

	//TODO
}


hook_func<LONG (__stdcall *)(struct _EXCEPTION_POINTERS* pExceptionInfo)> _ExceptionFilter(SAKEXE, "ExceptionFilter");
LONG __stdcall ExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo) // line 85
{
	return (_ExceptionFilter)(pExceptionInfo);

	HMODULE hDbgHelp = LoadLibraryA("dbghelp.dll");
	if( hDbgHelp == NULL )
	{
		sprintf(&exception_log[strlen(exception_log)], "Can't find DbgHelp.DLL !!!");
	}
	else
	{
		typedef BOOL (WINAPI* tStackWalk)(DWORD MachineType, HANDLE hProcess, HANDLE hThread, LPSTACKFRAME StackFrame, PVOID ContextRecord, PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine, PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine, PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine, PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress);
		typedef DWORD (WINAPI* tGetTimestamp)(HMODULE Module);
		typedef BOOL (WINAPI* tEnumerateLoadedModules)(HANDLE hProcess, PENUMLOADED_MODULES_CALLBACK EnumLoadedModulesCallback, PVOID UserContext);

		tStackWalk dbgStackWalk = (tStackWalk)GetProcAddress(hDbgHelp, "StackWalk");
		tGetTimestamp dbgGetTimeStamp = (tGetTimestamp)GetProcAddress(hDbgHelp, "GetTimestampForLoadedLibrary");
		tEnumerateLoadedModules dbgEnumerateLoadedModules = (tEnumerateLoadedModules)GetProcAddress(hDbgHelp, "EnumerateLoadedModules");

		char module_name[256];
		GetModuleFileNameA(GetModuleHandleA(NULL), module_name, sizeof(module_name));
		time_t module_time = dbgGetTimeStamp(GetModuleHandleA(NULL));

		sprintf(&exception_log[strlen(exception_log)], "Module Name: %s\r\n", module_name);
		sprintf(&exception_log[strlen(exception_log)], "Time Stamp: 0x%08x - %s\r\n", module_time, ctime(&module_time));
		sprintf(&exception_log[strlen(exception_log)], "\r\n");
		sprintf(&exception_log[strlen(exception_log)], "Exception Type: 0x%08x\r\n", pExceptionInfo->ExceptionRecord->ExceptionCode);
		sprintf(&exception_log[strlen(exception_log)], "\r\n");

		CONTEXT* context = pExceptionInfo->ContextRecord;

		STACKFRAME stackFrame;
		memset(&stackFrame, 0, sizeof(stackFrame));
		stackFrame.AddrPC.Offset = context->Eip;
		stackFrame.AddrPC.Mode = AddrModeFlat;
		stackFrame.AddrStack.Offset = context->Esp;
		stackFrame.AddrStack.Mode = AddrModeFlat;
		stackFrame.AddrFrame.Offset = context->Ebp;
		stackFrame.AddrFrame.Mode = AddrModeFlat;

		for( int i = 0; i < 512 && stackFrame.AddrPC.Offset && dbgStackWalk(IMAGE_FILE_MACHINE_I386, GetCurrentProcess(), GetCurrentThread(), &stackFrame, context, NULL, NULL, NULL, NULL); ++i )
		{
			sprintf(&exception_log[strlen(exception_log)], "0x%08x\t", stackFrame.AddrPC.Offset);
			dbgEnumerateLoadedModules(GetCurrentProcess(), &EnumerateLoadedModulesProc, &stackFrame);
			strcat(exception_log, "\r\n");
		}

		sprintf(&exception_log[strlen(exception_log)], "\r\n");
		sprintf(&exception_log[strlen(exception_log)], "eax: 0x%08x\tebx: 0x%08x\r\n", context->Eax, context->Ebx);
		sprintf(&exception_log[strlen(exception_log)], "ecx: 0x%08x\tedx: 0x%08x\r\n", context->Ecx, context->Edx);
		sprintf(&exception_log[strlen(exception_log)], "esi: 0x%08x\tedi: 0x%08x\r\n", context->Esi, context->Edi);
		sprintf(&exception_log[strlen(exception_log)], "ebp: 0x%08x\tesp: 0x%08x\r\n", context->Ebp, context->Esp);
		sprintf(&exception_log[strlen(exception_log)], "\r\n");
		sprintf(&exception_log[strlen(exception_log)], "stack %08x - %08x\r\n", context->Esp, context->Esp + 1024);

		BYTE* stack = (BYTE*)context->Esp;
		for( int j = 0; j < 16; ++j )
		{
			sprintf(&exception_log[strlen(exception_log)], "%08X : ", stack);

			for( int i = 0; i < 16; ++i )
				sprintf(&exception_log[strlen(exception_log)], "%02X ", stack[i]);

			sprintf(&exception_log[strlen(exception_log)], "\r\n");
			stack += 16;
		}

		sprintf(&exception_log[strlen(exception_log)], "\r\nLaunch Info \r\n");

		int pos = 0;
		for( int j = 0; j < 4; ++j )
		{
			for( int i = 0; i < 8; ++i )
			{
				sprintf(&exception_log[strlen(exception_log)], "%04X ", g_recentEffectId[4*j+i]);
				++pos;
			}

			sprintf(&exception_log[strlen(exception_log)], "\r\n");
		}

		sprintf(&exception_log[strlen(exception_log)], "\r\nJob : %s\r\n", g_session.CSession::GetJobName(g_session.CSession::GetJob()));
		FreeLibrary(hDbgHelp);
	}

	DialogBoxParamA(GetModuleHandleA(NULL), MAKEINTRESOURCEA(0x75), NULL, (DLGPROC)&DialogProc, 0);
	return 1;
}
