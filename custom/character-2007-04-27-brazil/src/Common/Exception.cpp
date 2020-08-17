#include "Common/CriticalSection.h"
#include <dbghelp.h>


LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* pExceptionInfo)
{
	static CCriticalSection csException;
	csException.Enter(); //FIXME: not all control paths call csException.Leave()

	/////////////////////
	// write memory dump

	char m_MoudleFilePath[MAX_PATH];
	char m_MoudleFileName[MAX_PATH];
	GetModuleFileNameA(NULL, m_MoudleFilePath, sizeof(m_MoudleFilePath));
	strncpy_s(m_MoudleFileName, sizeof(m_MoudleFileName), strrchr(m_MoudleFilePath, '\\') + 1, _TRUNCATE);
	*strrchr(m_MoudleFilePath, '\\') = '\0';
	*strrchr(m_MoudleFileName, '.') = '\0';

	SYSTEMTIME st;
	GetSystemTime(&st);
	char szTime[20];
	_snprintf_s(szTime, sizeof(szTime), _TRUNCATE, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	HMODULE hDbgHelpDll = LoadLibraryA("DBGHELP.DLL");
	if( hDbgHelpDll != NULL )
	{
		FARPROC pfnDump = GetProcAddress(hDbgHelpDll, "MiniDumpWriteDump");
		if( pfnDump != NULL )
		{
			char szDumpFileFullPathName[MAX_PATH] = "unknown.dmp";
			_snprintf_s(szDumpFileFullPathName, sizeof(szDumpFileFullPathName), _TRUNCATE, "%s\\%s.%s.dmp", m_MoudleFilePath, m_MoudleFileName, szTime);

			HANDLE hDumpFile = CreateFileA(szDumpFileFullPathName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if( hDumpFile != INVALID_HANDLE_VALUE )
			{
				MINIDUMP_EXCEPTION_INFORMATION ExInfo;
				ExInfo.ThreadId = GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers = FALSE;

				typedef BOOL (WINAPI* MINIDUMPWRITEDUMP)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, CONST PMINIDUMP_EXCEPTION_INFORMATION, CONST PMINIDUMP_USER_STREAM_INFORMATION, CONST PMINIDUMP_CALLBACK_INFORMATION);
				reinterpret_cast<MINIDUMPWRITEDUMP>(pfnDump)(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpWithFullMemory, &ExInfo, NULL, NULL);

				CloseHandle(hDumpFile);
			}
		}

		FreeLibrary(hDbgHelpDll);
	}

	////////////////////
	// write stack dump

	SymSetOptions(SYMOPT_LOAD_LINES|SYMOPT_DEFERRED_LOADS|SYMOPT_UNDNAME);

	if( !SymInitialize(GetCurrentProcess(), NULL, TRUE) )
		return 1;

	FILE* fp = fopen("stackdump.txt", "at");
	if( fp == NULL )
		return 1;

	char szTemp[256] = {};
	fprintf(fp, "------------------------------------------------------------------------\n");
	_strdate(szTemp);
	fprintf(fp, "Date : %s\n", szTemp);
	_strtime(szTemp);
	fprintf(fp, "Time : %s\n", szTemp);
	fprintf(fp, "Process ID : %x\n", GetCurrentProcessId());
	fprintf(fp, "Thread ID : %x\n\n", GetCurrentThreadId());
	fprintf(fp, "Exception Type : 0x%08x\n\n", pExceptionInfo->ExceptionRecord->ExceptionCode);

	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread = GetCurrentThread();
	CONTEXT* pContext = pExceptionInfo->ContextRecord;

	STACKFRAME StackFrame = {};
	StackFrame.AddrPC.Offset = pContext->Eip;
	StackFrame.AddrPC.Mode = AddrModeFlat;
	StackFrame.AddrStack.Offset = pContext->Esp;
	StackFrame.AddrStack.Mode = AddrModeFlat;
	StackFrame.AddrFrame.Offset = pContext->Ebp;
	StackFrame.AddrFrame.Mode = AddrModeFlat;

	for( int i = 0; i < 512; ++i )
	{
		if( StackFrame.AddrPC.Offset == 0 )
			break;

		if( !StackWalk(IMAGE_FILE_MACHINE_I386, hProcess, hThread, &StackFrame, pContext, NULL, &SymFunctionTableAccess, &SymGetModuleBase, NULL) )
			break;

		char chSymbol[256] = {};
		IMAGEHLP_SYMBOL* pSymbolInfo = reinterpret_cast<IMAGEHLP_SYMBOL*>(chSymbol);
		pSymbolInfo->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
		pSymbolInfo->MaxNameLength = sizeof(chSymbol) - 3; // ???

		DWORD dwDisplacement = 0;
		if( SymGetSymFromAddr(hProcess, StackFrame.AddrPC.Offset, &dwDisplacement, pSymbolInfo) )
			fprintf(fp, "0x%08x - %s() + %xh\n", StackFrame.AddrPC.Offset, pSymbolInfo->Name, StackFrame.AddrPC.Offset - pSymbolInfo->Address);
		else
			fprintf(fp, "0x%08x - [Unknown Symbol:Error %d]\n", StackFrame.AddrPC.Offset, GetLastError());

		IMAGEHLP_MODULE ModuleInfo = { sizeof(ModuleInfo) };
		if( SymGetModuleInfo(hProcess, StackFrame.AddrPC.Offset, &ModuleInfo) )
		{
			fprintf(fp, "\t\t\t\tImageName:%s\n", ModuleInfo.ImageName);
			fprintf(fp, "\t\t\t\tLoadedImageName:%s\n", ModuleInfo.LoadedImageName);
		}

		IMAGEHLP_LINE LineInfo = { sizeof(LineInfo) };
		for( int offset = 0; offset < 512; ++offset )
		{// walk backwards, trying to locate the nearest available line number information
			DWORD dwDisplacement = 0;
			if( SymGetLineFromAddr(hProcess, StackFrame.AddrPC.Offset - offset, &dwDisplacement, &LineInfo) )
			{
				fprintf(fp, "\t\t\t\tFileName:%s\n", LineInfo.FileName);
				fprintf(fp, "\t\t\t\tLineNumber:%d\n", LineInfo.LineNumber);
				break;
			}
		}
	}

	fclose(fp);
	SymCleanup(hProcess);
	csException.Leave();

	return 1;
}
