#pragma once
#include "Common/CriticalSection.h"
#include "Network2/CompletionPort.h"
#include "Network2/Stream.h"


class CStreamManager
{
public:
	CStreamManager();
	virtual ~CStreamManager();
	bool Create(std::list<CProcess*>& rProcessList, int SendQueueSize, int RecvQueueSize, int RecvBufSize, bool bDetailedCloseInfo);
	bool StartProcessing(int nProcessThreadNum, int nSleepRatio, int nThreadPriority);
	bool Listen(WORD port, int nBackLog, DWORD dwPingTime, int nWorkerThreadNum, int nRefuseLow, int nRefuseHigh, DWORD dwBindIP);
	void Destroy();
	void Init();
//	bool Connect(const char* szIP, WORD wPort, int _unknown, DWORD dwPingTime);
	void Broadcast(char* pBuffer, int nLength);
	int GetConnectionCount();
	int GetWorkerThreadNum();
	int GetRunningWorkerThreadNum();
	LONG GetFreeStreamNum();
//	bool IsRefuseAccepting();
//	LONG GetRunningProcessNum();
//	void PauseAccept();
//	void ResumeAccept();
//	bool IsAcceptPaused();

protected:
	void AcceptThread(void* lpParam);
	void ProcessThread(void* lpParam);
//	void ConnectThread(void* lpParam);

protected:
	/* this+ 0 */ //const CStreamManager::`vftable';
	/* this+ 4 */ bool m_bArrangeThreadStarted;
	/* this+ 8 */ SOCKET m_ListenSocket;
	/* this+12 */ WORD m_ListenPort;
	/* this+14 */ bool m_bProcessPermit;
	/* this+15 */ bool m_bAcceptPermit;
	/* this+16 */ bool m_bPauseAccept;
	/* this+20 */ DWORD m_dwPingTime;
	/* this+24 */ int m_nSleepRatio;
	/* this+28 */ LONG m_nRunningProcessNum;
	/* this+32 */ int m_nRefuseLow;
	/* this+36 */ int m_nRefuseHigh;
	/* this+40 */ bool m_bRefuseAccept;
	/* this+44 */ CStream* m_pStreams;
	/* this+48 */ int m_nMAX_STREAM_NUM;
	/* this+52 */ CCriticalSection* m_csFSQ;
	/* this+56 */ std::queue<CStream*,std::list<CStream*>>* m_FSQ;
	/* this+60 */ LONG m_nFSNum;
	/* this+64 */ int m_nProcessThreadNum;
	/* this+68 */ CCompletionPort m_CompletionPort;
};
