#pragma once
#include "Common/NFileLog.h"


class CEnterTraceLog : public NFileLog
{
public:
	bool isOK() const;
	void LogFmt(const char* in_szpSourceFileName, const int in_SourceLineNum, const DWORD in_dwIP, const char* lpszMessage, ...);
	void LogFile(const char* lpszFile, const char* lpszError, ...);
	void FatalError(const char* in_szpSourceFileName, const int in_SourceLineNum, const char* lpszError, ...);
	void MessagePrint(const char* lpszMsg, ...);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CEnterTraceLog* GetObj();

private:
	CEnterTraceLog();
	virtual ~CEnterTraceLog();

private:
	/* this+   0 */ //NFileLog baseclass_0;
	/* this+2088 */ bool m_bOK;
	/* this+2092 */ RTL_CRITICAL_SECTION m_cs;
	/* static    */ static CEnterTraceLog* m_cpSelf;
};
