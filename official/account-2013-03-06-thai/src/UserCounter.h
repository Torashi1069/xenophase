#pragma once
#include "Common/Singleton.h"
class CWUCSSvrClient;


class CUserCounter : public CSingleton<CUserCounter>
{
private:
	/* this+  0 */ //CSingleton<CUserCounter> baseclass_0;
	/* this+  0 */ char m_szTime[64];
	/* this+ 64 */ char m_szDate[64];
	/* this+128 */ char m_szServerName[64];
	/* this+192 */ char m_szPath[MAX_PATH];
	/* this+452 */ DWORD m_dwArrCharUserCounter[30];
	/* this+572 */ FILE* m_fp;
	/* this+576 */ CWUCSSvrClient* m_process;
	/* this+580 */ int m_nLocalSID;
	/* this+584 */ int m_nServerNumber;

private:
//	void GetTime();
//	void OpenFile(const char* file);
//	void CloseFile();

public:
//	CUserCounter();
//	~CUserCounter();
//	void SetProcess(CWUCSSvrClient* process);
//	void ReleaseProcess();
//	char* GetServerName();
//	int GetServerNumber();
//	void WriteUserCount();
//	void WriteUserCountUserCountInfo(int* count);
};
