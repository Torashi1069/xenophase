#include "StackDumpLog.h"


CStackDumpLog::CStackDumpLog()
{
	InitializeCriticalSection(&m_CS);
	m_bSymbolReady = false;

	SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
	if( SymInitialize(GetCurrentProcess(), NULL, TRUE) == TRUE )
		m_bSymbolReady = true;
}


CStackDumpLog::~CStackDumpLog()
{
	if( m_bSymbolReady == true )
		SymCleanup(GetCurrentProcess());

	DeleteCriticalSection(&m_CS);
}


void CStackDumpLog::WriteFmt(const char* in_szpSourceFileName, const int in_Line, const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf(Buffer, countof(Buffer), in_pFmt, va);

	this->CStackDumpLog::Write(in_szpSourceFileName, in_Line, Buffer);
}


void CStackDumpLog::Write(const char* in_szpSourceFileName, const int in_Line, const char* in_pMsg)
{
	EnterCriticalSection(&m_CS);

	SYSTEMTIME st;
	GetLocalTime(&st);

	char szStackDumpLogFileName[MAX_PATH] = {};
	wsprintfA(szStackDumpLogFileName, "stackdumplog.%02d%02d.txt", st.wYear, st.wMonth); //FIXME: deprecated API

	FILE* fp = fopen(szStackDumpLogFileName, "a");
	if( fp != NULL )
	{
		fprintf(fp, "%s(%d) %02d-%02d-%02d %02d:%02d:%02d %s\n", in_szpSourceFileName, in_Line, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, in_pMsg);
		this->CStackDumpLog::WriteStack(fp);
		fclose(fp);
	}

	LeaveCriticalSection(&m_CS);
}


void CStackDumpLog::WriteStack(FILE* in_fp) const
{
	if( !m_bSymbolReady )
		return;

	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread = GetCurrentThread();

	CONTEXT context = {};
	context.ContextFlags = CONTEXT_FULL;
	__asm {
	call x
	x:
	pop eax
	mov context.Eip, eax
	mov context.Ebp, ebp
	mov context.Esp, esp
	};

	STACKFRAME stackFrame = {};
	stackFrame.AddrPC.Offset = context.Eip;
	stackFrame.AddrPC.Mode = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Esp;
	stackFrame.AddrStack.Mode = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Ebp;
	stackFrame.AddrFrame.Mode = AddrModeFlat;

	char chSymbol[256] = {};
	IMAGEHLP_SYMBOL* pSymbol = reinterpret_cast<IMAGEHLP_SYMBOL*>(chSymbol);
	pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
	pSymbol->MaxNameLength = sizeof(chSymbol) - 3; // ???

	for( int count = 0; count < 512; ++count )
	{
		if( stackFrame.AddrPC.Offset == 0 )
			break;

		if( !StackWalk(IMAGE_FILE_MACHINE_I386, hProcess, hThread, &stackFrame, &context, NULL, &SymFunctionTableAccess, &SymGetModuleBase, NULL) )
			break;

		if( count <= 1 )
			continue; // skip the top two stack levels.

		DWORD dwDisplacement = 0;
		if( SymGetSymFromAddr(hProcess, stackFrame.AddrPC.Offset, &dwDisplacement, pSymbol) == TRUE )
			fprintf(in_fp, "\t0x%08x - %s() + %xh\n", stackFrame.AddrPC.Offset, pSymbol->Name, stackFrame.AddrPC.Offset - pSymbol->Address);
		else
			fprintf(in_fp, "\t0x%08x - [Unknown Symbol:Error %d]\n", stackFrame.AddrPC.Offset, GetLastError());
	}
}
