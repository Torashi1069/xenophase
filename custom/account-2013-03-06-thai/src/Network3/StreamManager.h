#pragma once
class CCompletionPort;
class CProcess;
class CStream;


class CStreamManager
{
public:
	CStreamManager();
	virtual ~CStreamManager();
	bool Create(std::list<CProcess*>& rProcessList, int SendQueueSize, int RecvBufSize, CCompletionPort* pCompletionPort, bool bDetailedCloseInfo);
	virtual bool Listen(WORD port, int nBackLog, DWORD dwPingTime, DWORD dwListenIP);
	virtual bool Connect(const char* szIP, WORD wPort, DWORD dwPingTime);
	void Destroy();
	void Broadcast(char* pBuffer, int nLength);
//	void BroadcastExcept(CProcess* pProcess, char* pBuffer, int nLength);
	int GetConnectionCount();
	LONG GetFreeStreamNum();
	void PauseAccept();
	void ResumeAccept();
	bool IsAcceptPaused();
	void SetDOSCheck(DWORD dwClientCutLine, DWORD dwTimeInterval);

protected:
	int ArrangeStreams();
	BOOL CheckDOSIP();
	virtual void AcceptThread(void* lpParam);
	virtual void ConnectThread(void* lpParam);

protected:
	/* this+ 0 */ //const CStreamManager::`vftable';
	/* this+ 4 */ SOCKET m_ListenSocket;
	/* this+ 8 */ WORD m_ListenPort;
	/* this+10 */ bool m_bAcceptPermit;
	/* this+11 */ bool m_bPauseAccept;
	/* this+12 */ bool m_bProcessPermit;
	/* this+13 */ bool m_bMultiIPCheck;
	/* this+16 */ DWORD m_dwClientCutLine;
	/* this+20 */ DWORD m_dwTimeInterval;
	/* this+24 */ DWORD m_dwPingTime;
	/* this+28 */ int m_nMAX_STREAM_NUM;
	/* this+32 */ CStream* m_pStreams;
	/* this+36 */ std::list<CStream*> m_FreeStreamList;
	/* this+48 */ std::list<CStream*> m_AllocStreamList;
	/* this+60 */ LONG m_nFSNum;
	/* this+64 */ CCompletionPort* m_pCompletionPort;
};
