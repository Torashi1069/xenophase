#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


class CReporter : public CSingleton<CReporter>
{
private:
	/* this+  0 */ //CSingleton<CReporter> baseclass_0;
	/* this+  0 */ CCriticalSection m_cs;
	/* this+ 24 */ char m_szTime[64];
	/* this+ 88 */ char m_szDate[64];
	/* this+152 */ char m_szPath[260];
	/* this+412 */ FILE* m_fp;

private:
	void GetTime();
	void OpenLogFile(const char* file);
	void CloseLogFile();

public:
	CReporter();
	~CReporter();

public:
	void FilePrint(const char* lpszFile, const char* lpszError, ...);
	void FatalError(const char* lpszError, ...);
	void Log(const char* lpszError, ...);
	void MessagePrint(const char* lpszMsg, ...);
};
