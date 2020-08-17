#pragma once


class CMyMiniDumpUnhandledExceptionHandler
{
private:
	static LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo);
	static BOOL MyMiniDump(const SYSTEMTIME& st, EXCEPTION_POINTERS* pExceptionInfo); /// @custom
	static void MyStackWalk(const SYSTEMTIME& st, EXCEPTION_POINTERS* pExceptionInfo);

public:
	static bool CreateInstance();
	static void DestroyInstance();

private:
	bool isOK() const;
	CMyMiniDumpUnhandledExceptionHandler();
	~CMyMiniDumpUnhandledExceptionHandler();

private:
	/* static */ static CMyMiniDumpUnhandledExceptionHandler* m_cpSelf;
	/* this+0 */ bool m_bOK;
	/* static */ static char m_MoudleFilePath[MAX_PATH];
	/* static */ static char m_MoudleFileName[MAX_PATH];
};
