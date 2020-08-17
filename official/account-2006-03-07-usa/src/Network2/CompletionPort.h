#pragma once
#include "Common/CriticalSection.h"


class CCompletionPort
{
private:
	/* this+ 0 */ HANDLE m_hCompletionPort;
	/* this+ 4 */ CCriticalSection m_csCompletionPort;
	/* this+28 */ LONG m_nRunningThread;
	/* this+32 */ LONG m_nInThreadNum;
	/* this+36 */ int m_nWorkerThreadNum;

public:
	CCompletionPort();
	~CCompletionPort();
	bool Create(int nWorkerThreadNum);
	void Destroy();
	void WorkerThread(void* lpThreadData);
	int GetThreadNum();
	LONG GetInThreadNum();
	LONG GetRunningThreadNum();
	HANDLE AssociateSocket(SOCKET s, DWORD CompletionKey, DWORD& rError);
};
