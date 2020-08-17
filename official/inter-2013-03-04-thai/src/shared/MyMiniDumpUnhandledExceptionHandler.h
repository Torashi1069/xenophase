#pragma once


typedef void (__cdecl OUTPUTFUNC)();


class CMyMiniDumpUnhandledExceptionHandler
{
private:
	static LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo);
	static BOOL MyMiniDump(const SYSTEMTIME& st, EXCEPTION_POINTERS* pExceptionInfo); /// @custom
	static void MyStackWalk(const SYSTEMTIME& st, EXCEPTION_POINTERS* pExceptionInfo);

public:
	static bool CreateInstance(OUTPUTFUNC* pOutputFunc);
	static void DestroyInstance();

private:
	bool isOK() const;
	CMyMiniDumpUnhandledExceptionHandler(OUTPUTFUNC* in_pOutputFunc);
	~CMyMiniDumpUnhandledExceptionHandler();

private:
	/* static */ static CMyMiniDumpUnhandledExceptionHandler*& m_cpSelf; //TODO
	/* this+0 */ bool m_bOK;
	/* static */ static char (& m_MoudleFilePath)[MAX_PATH]; //TODO
	/* static */ static char (& m_MoudleFileName)[MAX_PATH]; //TODO
	/* static */ static OUTPUTFUNC*& m_pOutputFunc; //TODO
};
