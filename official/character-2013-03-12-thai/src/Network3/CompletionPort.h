#pragma once
#include "Common/CriticalSection.h"


class CCompletionPort
{
private:
	/* this+ 0 */ //const CCompletionPort::`vftable';
	/* this+ 4 */ HANDLE m_hCompletionPort;
	/* this+ 8 */ CCriticalSection m_csCompletionPort;
	/* this+32 */ LONG m_nRunningThread;
	/* this+36 */ LONG m_nInThreadNum;
	/* this+40 */ int m_nWorkerThreadNum;

private:
	void WorkerThread(void* lpThreadData);

public:
	CCompletionPort();
	virtual ~CCompletionPort();
	bool Create(int nWorkerThreadNum);
	void Destroy();
	int GetWorkerThreadNum();
	LONG GetInThreadNum();
	LONG GetRunningThreadNum();
	HANDLE AssociateSocket(SOCKET s, DWORD CompletionKey, DWORD& rError);
};
