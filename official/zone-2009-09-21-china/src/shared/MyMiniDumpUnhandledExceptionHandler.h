#pragma once


class CMyMiniDumpUnhandledExceptionHandler
{
public:
	/* static   */ private: static hook_ptr<CMyMiniDumpUnhandledExceptionHandler *> m_cpSelf;
	/* this+0x0 */ private: bool m_bOK;
	/* static   */ private: static hook_val<char[260]> m_MoudleFilePath;
	/* static   */ private: static hook_val<char[260]> m_MoudleFileName;

	private: static long __stdcall CMyMiniDumpUnhandledExceptionHandler::UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo);
	//private: static void CMyMiniDumpUnhandledExceptionHandler::MyStackWalk(const SYSTEMTIME &, EXCEPTION_POINTERS *);
	public:  static bool __cdecl CMyMiniDumpUnhandledExceptionHandler::CreateInstance(void);
	public:  static void __cdecl CMyMiniDumpUnhandledExceptionHandler::DestroyInstance(void);
	//private: bool CMyMiniDumpUnhandledExceptionHandler::isOK();
	//private: void CMyMiniDumpUnhandledExceptionHandler::CMyMiniDumpUnhandledExceptionHandler();
	//private: void CMyMiniDumpUnhandledExceptionHandler::~CMyMiniDumpUnhandledExceptionHandler();

private:
	static hook_method<static long (__stdcall *)(EXCEPTION_POINTERS* pExceptionInfo)> CMyMiniDumpUnhandledExceptionHandler::_UnhandledExceptionHandler;
	static hook_method<static bool (__cdecl *)(void)> CMyMiniDumpUnhandledExceptionHandler::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CMyMiniDumpUnhandledExceptionHandler::_DestroyInstance;
};
