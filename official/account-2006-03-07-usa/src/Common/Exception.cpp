#include "Common/CriticalSection.h"
#include <dbghelp.h>


LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* pExceptionInfo)
{
	static CCriticalSection csException;
	csException.Enter(); //FIXME: not all control paths call csException.Leave()

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
