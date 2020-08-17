#pragma once
#include "Common/CriticalSection.h"
class CStream;


class CProcess
{
public:
	CProcess();
	virtual ~CProcess();
	void SetStream(CStream* pStream);
	bool Init(DWORD dwStreamSessionID, DWORD dwIP);
	bool CloseOuter(DWORD dwSessionID, DWORD dwTime);
	virtual void Send(char* buf, int len, DWORD dwSessionID, bool bBroadcast);
	DWORD GetSessionID();
	DWORD GetIP();
	void OnStreamClose();
	virtual bool OnRecv(char* buffer, int* len) = 0;
	virtual bool OnConnect() = 0;
	virtual void OnClose() = 0;
	virtual void OnIdle();

protected:
	/* this+ 0 */ //const CProcess::`vftable';
	/* this+ 4 */ CCriticalSection m_cs;
	/* this+28 */ char m_szMacAddr[12+1];
	/* this+44 */ DWORD m_dwIP;
	/* this+48 */ DWORD m_dwSessionID;
	/* this+52 */ CStream* m_pStream;
};
