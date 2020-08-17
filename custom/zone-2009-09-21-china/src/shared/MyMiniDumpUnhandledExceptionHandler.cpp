#include "MyMiniDumpUnhandledExceptionHandler.h"
#include <dbghelp.h>


hook_ptr<CMyMiniDumpUnhandledExceptionHandler *> CMyMiniDumpUnhandledExceptionHandler::m_cpSelf(SERVER, "CMyMiniDumpUnhandledExceptionHandler::m_cpSelf"); // = ?
hook_val<char[260]> CMyMiniDumpUnhandledExceptionHandler::m_MoudleFilePath(SERVER, "CMyMiniDumpUnhandledExceptionHandler::m_MoudleFilePath"); // = ?
hook_val<char[260]> CMyMiniDumpUnhandledExceptionHandler::m_MoudleFileName(SERVER, "CMyMiniDumpUnhandledExceptionHandler::m_MoudleFileName"); // = ?


namespace
{


class CMyFile
{
public:
	/* this+0x0 */ HANDLE m_hFile;

	public: CMyFile::CMyFile(void* hFile)
	{
		m_hFile = hFile;
	}

	public: CMyFile::~CMyFile(void)
	{
		if( m_hFile != INVALID_HANDLE_VALUE )
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
		}
	}

	public: operator HANDLE(void)
	{
		return m_hFile;
	}

	public: int Write(const char* in_pFmt, ...)
	{
		va_list ap;
		va_start(ap, in_pFmt);

		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		_vsnprintf_s(buffer, sizeof(buffer), UINT_MAX, in_pFmt, ap);

		int WriteBytes = 0;
		WriteFile(m_hFile, buffer, strlen(buffer), (LPDWORD)&WriteBytes, NULL);

		return WriteBytes;
	}
};


const char* GetSystemTimeFmtStr(const SYSTEMTIME& st)
{
	static char buffer[20];
	_snprintf_s(buffer, sizeof(buffer), _TRUNCATE, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return buffer;
}


};


hook_method<static long (__stdcall *)(EXCEPTION_POINTERS* pExceptionInfo)> CMyMiniDumpUnhandledExceptionHandler::_UnhandledExceptionHandler(SERVER, "CMyMiniDumpUnhandledExceptionHandler::UnhandledExceptionHandler");
HOOKED long __stdcall CMyMiniDumpUnhandledExceptionHandler::UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo)
{
//	return (CMyMiniDumpUnhandledExceptionHandler::_UnhandledExceptionHandler)(pExceptionInfo);

	int retval = 0;

	SYSTEMTIME st;
	GetLocalTime(&st);

	/////////////////////
	// write memory dump

	char szDbgHelpDllFullPathName[MAX_PATH] = {};
	_snprintf_s(szDbgHelpDllFullPathName, sizeof(szDbgHelpDllFullPathName), UINT_MAX, "%s\\DBGHELP.DLL", m_MoudleFilePath);

	HMODULE hDbgHelpDll = LoadLibraryA(szDbgHelpDllFullPathName);
	if( hDbgHelpDll == NULL )
		hDbgHelpDll = LoadLibraryA("DBGHELP.DLL");

	if( hDbgHelpDll != NULL )
	{
		FARPROC pfnDump = GetProcAddress(hDbgHelpDll, "MiniDumpWriteDump");
		if( pfnDump != (FARPROC)NULL )
		{
			char szDumpFileFullPathName[260];

			memset(szDumpFileFullPathName, 0, sizeof(szDumpFileFullPathName));
			strcpy(szDumpFileFullPathName, "unknown.dmp");
			_snprintf_s(szDumpFileFullPathName, sizeof(szDumpFileFullPathName), UINT_MAX, "%s\\%s.%s.dmp", m_MoudleFilePath, m_MoudleFileName, GetSystemTimeFmtStr(st));

			HANDLE v4 = CreateFileA(szDumpFileFullPathName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if( v4 != INVALID_HANDLE_VALUE )
			{
				MINIDUMP_EXCEPTION_INFORMATION ExInfo;
				ExInfo.ThreadId = GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers = 0;
				if( ((BOOL (WINAPI *)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, CONST PMINIDUMP_EXCEPTION_INFORMATION, CONST PMINIDUMP_USER_STREAM_INFORMATION, CONST PMINIDUMP_CALLBACK_INFORMATION))pfnDump)(GetCurrentProcess(), GetCurrentProcessId(), v4, MiniDumpWithFullMemory, &ExInfo, NULL, NULL) )
					retval = 1;

				CloseHandle(v4);
			}
		}
	}

	////////////////////
	// write stack dump

	SymSetOptions(SYMOPT_LOAD_LINES|SYMOPT_DEFERRED_LOADS|SYMOPT_UNDNAME);
	SymCleanup(GetCurrentProcess());
	if( !SymInitialize(GetCurrentProcess(), NULL, TRUE) )
		return retval;

	CMyFile v8 = CreateFileA("StackDump.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if( v8 == INVALID_HANDLE_VALUE )
		return retval;

	SetFilePointer(v8, 0, NULL, FILE_END);
	v8.CMyFile::Write("*------------------------------------------------------------*\r\n");
	v8.CMyFile::Write("Date:%s\r\n", GetSystemTimeFmtStr(st));
	v8.CMyFile::Write("Process:%x\r\n", GetCurrentProcessId());
	v8.CMyFile::Write("Thread:%x\r\n", GetCurrentThreadId());
	v8.CMyFile::Write("\r\n");
	v8.CMyFile::Write("Exception Type:0x%08x\r\n", pExceptionInfo->ExceptionRecord->ExceptionCode);

	CONTEXT* v11 = pExceptionInfo->ContextRecord;

	STACKFRAME StackFrame = {};
	StackFrame.AddrPC.Mode = AddrModeFlat;
	StackFrame.AddrPC.Offset = v11->Eip;
	StackFrame.AddrStack.Mode = AddrModeFlat;
	StackFrame.AddrStack.Offset = v11->Esp;
	StackFrame.AddrFrame.Mode = AddrModeFlat;
	StackFrame.AddrFrame.Offset = v11->Ebp;

	v8.CMyFile::Write("\r\n");
	v8.CMyFile::Write("eax: 0x%08x\tebx: 0x%08x\r\n", v11->Eax, v11->Ebx);
	v8.CMyFile::Write("ecx: 0x%08x\tedx: 0x%08x\r\n", v11->Ecx, v11->Edx);
	v8.CMyFile::Write("esi: 0x%08x\tedi: 0x%08x\r\n", v11->Esi, v11->Edi);
	v8.CMyFile::Write("ebp: 0x%08x\tesp: 0x%08x\r\n", v11->Ebp, v11->Esp);
	v8.CMyFile::Write("\r\n");

	int v2 = 0;
	while( v2 < 512 && StackFrame.AddrPC.Offset != 0 && StackWalk(IMAGE_FILE_MACHINE_I386, GetCurrentProcess(), GetCurrentThread(), &StackFrame, v11, (PREAD_PROCESS_MEMORY_ROUTINE)NULL, SymFunctionTableAccess, SymGetModuleBase, (PTRANSLATE_ADDRESS_ROUTINE)NULL) )
	{
		DWORD dwDisplacement = 0;

		char symBuf[MAX_PATH] = {};
		IMAGEHLP_SYMBOL* pSymbolInfo = (IMAGEHLP_SYMBOL*)symBuf;
		pSymbolInfo->SizeOfStruct = sizeof(*pSymbolInfo);
		pSymbolInfo->MaxNameLength = 239;

		if( SymGetSymFromAddr(GetCurrentProcess(), StackFrame.AddrPC.Offset, &dwDisplacement, pSymbolInfo) )
			v8.CMyFile::Write("0x%08x - %s() + %xh\r\n", StackFrame.AddrPC.Offset, pSymbolInfo->Name, StackFrame.AddrPC.Offset - pSymbolInfo->Address);
		else
			v8.CMyFile::Write("0x%08x - [Unknown Symbol:Error %d]\r\n", StackFrame.AddrPC.Offset, GetLastError());

		IMAGEHLP_MODULE ModuleInfo = { sizeof(ModuleInfo) };
		if( SymGetModuleInfo(GetCurrentProcess(), StackFrame.AddrPC.Offset, &ModuleInfo) )
		{
			v8.CMyFile::Write("\t\t\t\tImageName:%s\r\n", ModuleInfo.ImageName);
			v8.CMyFile::Write("\t\t\t\tLoadedImageName:%s\r\n", ModuleInfo.LoadedImageName);
		}

		IMAGEHLP_LINE LineInfo = { sizeof(LineInfo) };
		int v3 = 0;
		while( v3 < 512 && !SymGetLineFromAddr(GetCurrentProcess(), StackFrame.AddrPC.Offset - v3, &dwDisplacement, &LineInfo) )
			++v3;

		if( v3 < 512 )
		{
			v8.CMyFile::Write("\t\t\t\tFileName:%s\r\n", LineInfo.FileName);
			v8.CMyFile::Write("\t\t\t\tLineNumber:%d\r\n", LineInfo.LineNumber);
		}

		++v2;
	}

	v8.CMyFile::Write("\r\n");
	v8.CMyFile::Write("stack %08x - %08x\r\n", v11->Esp, v11->Esp + 320 - 1);

	BYTE* v18 = (BYTE*)v11->Esp;

	for( int j = 0; j < 16; ++j )
	{
		v8.CMyFile::Write("%08X : ", v18);

		for( int i = 0; i < 20; ++i )
			v8.CMyFile::Write("%02X ", v18[i]);

		v8.CMyFile::Write("\r\n");
		v18 += 16;
	}

	SymCleanup(GetCurrentProcess());

	return retval;
}


hook_method<static bool (__cdecl *)(void)> CMyMiniDumpUnhandledExceptionHandler::_CreateInstance(SERVER, "CMyMiniDumpUnhandledExceptionHandler::CreateInstance");
bool __cdecl CMyMiniDumpUnhandledExceptionHandler::CreateInstance(void)
{
	return (CMyMiniDumpUnhandledExceptionHandler::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CMyMiniDumpUnhandledExceptionHandler::_DestroyInstance(SERVER, "CMyMiniDumpUnhandledExceptionHandler::DestroyInstance");
void __cdecl CMyMiniDumpUnhandledExceptionHandler::DestroyInstance(void)
{
	return (CMyMiniDumpUnhandledExceptionHandler::_DestroyInstance)();

	//TODO
}
