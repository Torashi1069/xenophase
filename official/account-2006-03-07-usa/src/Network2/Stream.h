#pragma once
#include "Common/CircleQueue.h"
#include "Common/CriticalSection.h"
class CProcess;


#define WSABUFFER_SIZE 4096
struct OVERLAPPEDEX
{
	/* this+   0 */ OVERLAPPED m_overlapped;
	/* this+  20 */ BYTE m_byOperationCode;
	/* this+  21 */ char m_pBuf[WSABUFFER_SIZE];
	/* this+4120 */ int m_dwTryBytes;
	/* this+4124 */ int m_dwTransferredBytes;
};


class CStream
{
	public: static DWORD CreateSessionID();
	/* static */ private: static LONG m_SESSIONID;

public:
	CStream();
	virtual ~CStream();
	bool Create_RecvBuf_RecvQueue(int buf_size, int queue_size);
	bool CreateSendQueue(int queue_size);
	bool Init(SOCKET s, DWORD dwIP, DWORD dwPingTime);
	void SetProcessObj(CProcess* pProcess, bool bDetailedCloseInfo);
	bool Send(char* buf, DWORD dwLen, DWORD dwSessionID, bool bBroadCast);
	bool HandleIo(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes);
	int AddRef();
	int SubRef();
	int GetRef();
//	void ClearSendQueue();
//	void ClearRecvQueue();
	void Close(DWORD dwTime);
	bool CloseOuter(DWORD dwSessionID, DWORD dwTime);
	void CheckPingTime();
	void SetConnected(bool bConnected);
	bool IsConnected();
	DWORD GetSessionID();
	DWORD GetIP();
//	int GetSendQueueSize();
//	int GetSendQueueFreeSize();
//	int GetRecvQueueSize();
//	int GetRecvQueueFreeSize();
//	int GetRecvBufSize();
//	int GetRecvBufFreeSize();
	bool IsRecvPermit();

private:
	bool OnSendCompleted(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes);
	bool OnRecv(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes);
	void UpdateReceivedTime();
	void InternalClose();
	void DetailedCloseInfo(const char* szFile, const int nLine, const char* szFunc, const char* szReason); /// @custom

public:
	/* this+   0 */ //const CStream::`vftable';
	/* this+   4 */ bool m_bDetailedCloseInfo;
	/* this+   8 */ CCircleQueue m_RecvQueue;
private:
	/* this+  52 */ SOCKET m_socket;
	/* this+  56 */ LONG m_cRef;
	/* this+  60 */ DWORD m_dwIP;
	/* this+  64 */ bool m_bRecvPermit;
	/* this+  68 */ DWORD m_dwPingTime;
	/* this+  72 */ DWORD m_dwLastRecvTime;
	/* this+  76 */ bool m_bConnected;
	/* this+  80 */ OVERLAPPEDEX m_ovRecv;
	/* this+4208 */ char* m_pRecvBuf;
	/* this+4212 */ int RECV_BUF_SIZE;
	/* this+4216 */ int m_nRecvPos;
	/* this+4220 */ OVERLAPPEDEX m_ovSend;
	/* this+8348 */ CCircleQueue m_SendQueue;
	/* this+8392 */ bool m_bInitialSendPostPermit;
	/* this+8396 */ CProcess* m_pProcess;
	/* this+8400 */ DWORD m_dwSessionID;
	/* this+8404 */ CCriticalSection m_cs;

	friend class CStreamManager;
};


class CSubRef
{
public:
	CSubRef(CStream* pStream)
	{
		m_pStream = pStream;
	}

	~CSubRef()
	{
		m_pStream->CStream::SubRef();
	}

private:
	/* this+0 */ CStream* m_pStream;
};
