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

protected:
	/* this+ 0 */ //const CProcess::`vftable';
	/* this+ 4 */ CCriticalSection m_cs;
	/* this+28 */ DWORD m_dwIP;
	/* this+32 */ DWORD m_dwSessionID;
	/* this+36 */ CStream* m_pStream;
};
