#pragma once
class CAsyncStream;


class CClient
{
public:
	CClient();
	virtual ~CClient();

public:
	virtual int GetType();
	virtual void AddErrorCnt(const char* in_File, const int in_Line, const DWORD in_Cnt, const DWORD in_TM);
	virtual void Init();
	BOOL IsErrorClient();
	BOOL IsErrorServer();
	BOOL Close();
	virtual void Send(int len, const char* buf);
	int GetErrorCount();

protected:
	/* this+ 0 */ //const CClient::`vftable';
	/* this+ 4 */ CAsyncStream* m_asyncStream;
	/* this+ 8 */ RTL_CRITICAL_SECTION m_disconnector_cs;
	/* this+32 */ DWORD m_dwErrorCount;
	/* this+36 */ DWORD m_nBanTime;
};
