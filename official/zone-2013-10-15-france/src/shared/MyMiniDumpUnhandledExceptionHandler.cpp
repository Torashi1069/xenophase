#include "shared/MyMiniDumpUnhandledExceptionHandler.h"
#include <dbghelp.h>


/// singleton instance
CMyMiniDumpUnhandledExceptionHandler*& CMyMiniDumpUnhandledExceptionHandler::m_cpSelf = VTOR<CMyMiniDumpUnhandledExceptionHandler*>(DetourFindFunction(EXEPATH(), "CMyMiniDumpUnhandledExceptionHandler::m_cpSelf"));
char (& CMyMiniDumpUnhandledExceptionHandler::m_MoudleFilePath)[MAX_PATH] = VTOR<char[MAX_PATH]>(DetourFindFunction(EXEPATH(), "CMyMiniDumpUnhandledExceptionHandler::m_MoudleFilePath"));
char (& CMyMiniDumpUnhandledExceptionHandler::m_MoudleFileName)[MAX_PATH] = VTOR<char[MAX_PATH]>(DetourFindFunction(EXEPATH(), "CMyMiniDumpUnhandledExceptionHandler::m_MoudleFileName"));
OUTPUTFUNC*& CMyMiniDumpUnhandledExceptionHandler::m_pOutputFunc = VTOR<OUTPUTFUNC*>(DetourFindFunction(EXEPATH(), "CMyMiniDumpUnhandledExceptionHandler::m_pOutputFunc"));


CMyMiniDumpUnhandledExceptionHandler::CMyMiniDumpUnhandledExceptionHandler(OUTPUTFUNC* in_pOutputFunc)
{
	m_pOutputFunc = in_pOutputFunc;
	m_bOK = false;

	GetModuleFileNameA(NULL, m_MoudleFilePath, countof(m_MoudleFilePath));
	if( strrchr(m_MoudleFilePath, '\\') == NULL )
		return;

	strncpy_s(m_MoudleFileName, countof(m_MoudleFileName), strrchr(m_MoudleFilePath, '\\') + 1, _TRUNCATE);
	*strrchr(m_MoudleFilePath, '\\') = '\0';
	*strrchr(m_MoudleFileName, '.') = '\0';
	SetUnhandledExceptionFilter(&UnhandledExceptionHandler);

	m_bOK = true;
}


CMyMiniDumpUnhandledExceptionHandler::~CMyMiniDumpUnhandledExceptionHandler()
{
}


bool CMyMiniDumpUnhandledExceptionHandler::CreateInstance(OUTPUTFUNC* pOutputFunc)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMyMiniDumpUnhandledExceptionHandler(pOutputFunc);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMyMiniDumpUnhandledExceptionHandler::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMyMiniDumpUnhandledExceptionHandler::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


bool CMyMiniDumpUnhandledExceptionHandler::isOK() const
{
	return m_bOK;
}


namespace {
class CMyFile
{
public:
	CMyFile(HANDLE hFile)
	{
		m_hFile = hFile;
	}

	~CMyFile()
	{
		if( m_hFile != INVALID_HANDLE_VALUE )
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
		}
	}

	operator HANDLE()
	{
		return m_hFile;
	}

	int Write(const char* in_pFmt, ...)
	{
		va_list va;
		va_start(va, in_pFmt);

		char buffer[1024] = {};
		_vsnprintf_s(buffer, countof(buffer), _TRUNCATE, in_pFmt, va);

		DWORD WriteBytes = 0;
		WriteFile(m_hFile, buffer, strlen(buffer), &WriteBytes, NULL);

		return WriteBytes;
	}

private:
	/* this+0 */ HANDLE m_hFile;
};


const char* GetSystemTimeFmtStr(const SYSTEMTIME& st)
{
	static char buffer[20];
	_snprintf_s(buffer, countof(buffer), _TRUNCATE, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return buffer;
}
}; // namespace


LONG WINAPI CMyMiniDumpUnhandledExceptionHandler::UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	BOOL retval = MyMiniDump(st, pExceptionInfo);
	MyStackWalk(st, pExceptionInfo);

	if( m_pOutputFunc != NULL )
		m_pOutputFunc();

	return retval;
}


BOOL CMyMiniDumpUnhandledExceptionHandler::MyMiniDump(const SYSTEMTIME& st, EXCEPTION_POINTERS* pExceptionInfo) /// @custom
{
	BOOL retval = FALSE;

	char szDbgHelpDllFullPathName[MAX_PATH] = {};
	_snprintf_s(szDbgHelpDllFullPathName, countof(szDbgHelpDllFullPathName), _TRUNCATE, "%s\\DBGHELP.DLL", m_MoudleFilePath);

	HMODULE hDbgHelpDll = LoadLibraryA(szDbgHelpDllFullPathName);
	if( hDbgHelpDll == NULL )
		hDbgHelpDll = LoadLibraryA("DBGHELP.DLL");

	if( hDbgHelpDll != NULL )
	{
		FARPROC pDump = GetProcAddress(hDbgHelpDll, "MiniDumpWriteDump");
		if( pDump != NULL )
		{
			char szDumpFileFullPathName[MAX_PATH] = "unknown.dmp";
			_snprintf_s(szDumpFileFullPathName, countof(szDumpFileFullPathName), _TRUNCATE, "%s\\%s.%s.dmp", m_MoudleFilePath, m_MoudleFileName, GetSystemTimeFmtStr(st));

			HANDLE hDumpFile = CreateFileA(szDumpFileFullPathName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if( hDumpFile != INVALID_HANDLE_VALUE )
			{
				MINIDUMP_EXCEPTION_INFORMATION ExInfo;
				ExInfo.ThreadId = GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers = FALSE;

				typedef BOOL (WINAPI* MINIDUMPWRITEDUMP)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, CONST PMINIDUMP_EXCEPTION_INFORMATION, CONST PMINIDUMP_USER_STREAM_INFORMATION, CONST PMINIDUMP_CALLBACK_INFORMATION);
				if( reinterpret_cast<MINIDUMPWRITEDUMP>(pDump)(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &ExInfo, NULL, NULL) )
				{// success.
					retval = TRUE;
				}

				CloseHandle(hDumpFile);
			}
		}

//		FreeLibrary(hDbgHelpDll); //FIXME
	}

	return retval;
}


void CMyMiniDumpUnhandledExceptionHandler::MyStackWalk(const SYSTEMTIME& st, EXCEPTION_POINTERS* pExceptionInfo)
{
	SymSetOptions(SYMOPT_LOAD_LINES|SYMOPT_DEFERRED_LOADS|SYMOPT_UNDNAME);

	if( !SymInitialize(GetCurrentProcess(), NULL, TRUE) )
		return;

	CMyFile f = CreateFileA("StackDump.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if( f == INVALID_HANDLE_VALUE )
		return;

	SetFilePointer(f, 0, NULL, FILE_END);
	f.CMyFile::Write("*------------------------------------------------------------*\r\n");
	f.CMyFile::Write("날짜:%d년%d월%d일_%d시%d분%d초\r\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	f.CMyFile::Write("Process:%x\r\n", GetCurrentProcessId());
	f.CMyFile::Write("Thread:%x\r\n", GetCurrentThreadId());
	f.CMyFile::Write("\r\n");
	f.CMyFile::Write("Exception Type:0x%08x\r\n", pExceptionInfo->ExceptionRecord->ExceptionCode);

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

	f.CMyFile::Write("\r\n");
	f.CMyFile::Write("eax: 0x%08x\tebx: 0x%08x\r\n", pContext->Eax, pContext->Ebx);
	f.CMyFile::Write("ecx: 0x%08x\tedx: 0x%08x\r\n", pContext->Ecx, pContext->Edx);
	f.CMyFile::Write("esi: 0x%08x\tedi: 0x%08x\r\n", pContext->Esi, pContext->Edi);
	f.CMyFile::Write("ebp: 0x%08x\tesp: 0x%08x\r\n", pContext->Ebp, pContext->Esp);
	f.CMyFile::Write("\r\n");

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
			f.CMyFile::Write("0x%08x - %s() + %xh\r\n", StackFrame.AddrPC.Offset, pSymbolInfo->Name, StackFrame.AddrPC.Offset - pSymbolInfo->Address);
		else
			f.CMyFile::Write("0x%08x - [Unknown Symbol:Error %d]\r\n", StackFrame.AddrPC.Offset, GetLastError());

		IMAGEHLP_MODULE ModuleInfo = { sizeof(ModuleInfo) };
		if( SymGetModuleInfo(hProcess, StackFrame.AddrPC.Offset, &ModuleInfo) )
		{
			f.CMyFile::Write("\t\t\t\tImageName:%s\r\n", ModuleInfo.ImageName);
			f.CMyFile::Write("\t\t\t\tLoadedImageName:%s\r\n", ModuleInfo.LoadedImageName);
		}

		IMAGEHLP_LINE LineInfo = { sizeof(LineInfo) };
		for( int offset = 0; offset < 512; ++offset )
		{// walk backwards, trying to locate the nearest available line number information
			DWORD dwDisplacement = 0;
			if( SymGetLineFromAddr(hProcess, StackFrame.AddrPC.Offset - offset, &dwDisplacement, &LineInfo) )
			{
				f.CMyFile::Write("\t\t\t\tFileName:%s\r\n", LineInfo.FileName);
				f.CMyFile::Write("\t\t\t\tLineNumber:%d\r\n", LineInfo.LineNumber);
				break;
			}
		}
	}

	BYTE* pStack = (BYTE*)pContext->Esp;
	f.CMyFile::Write("\r\n");
	f.CMyFile::Write("stack %08x - %08x\r\n", pStack + 0, pStack + 1024); //FIXME: the loop below only prints 256 bytes

	for( int j = 0; j < 16; ++j )
	{
		f.CMyFile::Write("%08X : ", pStack);

		for( int i = 0; i < 16; ++i )
			f.CMyFile::Write("%02X ", pStack[i]);

		f.CMyFile::Write("\r\n");
		pStack += 16;
	}

	SymCleanup(hProcess);
}
