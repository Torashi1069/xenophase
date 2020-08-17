#pragma once
#include "Common/CircleQueue.h"
#include "Common/CriticalSection.h"
class CProcess;


#pragma pack(push,1)
#define WSABUFFER_SIZE 4096
struct OVERLAPPEDEX
{
	/* this+   0 */ OVERLAPPED m_overlapped;
	/* this+  20 */ BYTE m_byOperationCode;
	/* this+  21 */ char m_pBuf[WSABUFFER_SIZE];
	/* this+4117 */ int m_dwTryBytes;
	/* this+4121 */ int m_dwTransferredBytes;
};
#pragma pack(pop)


class CStream
{
	public: static DWORD CreateSessionID();
	/* static */ private: static LONG m_SESSIONID;

public:
	CStream();
	virtual ~CStream();
	bool CreateRecvBuf(int buf_size);
	bool CreateSendQueue(int queue_size);
	void SetProcessObj(CProcess* pProcess, bool bDetailedCloseInfo);
	bool Init(SOCKET s, DWORD dwIP, DWORD dwPingTime);
	bool Send(char* buf, DWORD dwLen, DWORD dwSessionID, bool bBroadCast);
	bool HandleIo(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes);
	LONG GetRef();
	LONG AddRef();
	LONG SubRef();
//	void ClearSendQueue();
//	void ClearRecvBuf();
	bool CloseOuter(DWORD dwSessionID, DWORD dwTime);
	void CheckPingTime();
	void SetConnected(bool bConnected);
	bool IsConnected();
	DWORD GetSessionID();
	DWORD GetIP();
	bool IsRecvPermit();
//	char* GetRecvBuf();

private:
	void Close(DWORD dwTime);
	bool OnSendCompleted(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes);
	bool OnRecv(OVERLAPPEDEX* lpOverlappedEx, DWORD dwTransferredBytes);
	void UpdateReceivedTime();
	void InternalClose();
	void DetailedCloseInfo(const char* szFile, const int nLine, const char* szFunc, const char* szReason); /// @custom

private:
	/* this+   0 */ //const CStream::`vftable';
	/* this+   4 */ bool m_bDetailedCloseInfo;
	/* this+   8 */ SOCKET m_socket;
	/* this+  12 */ LONG m_cRef;
	/* this+  16 */ DWORD m_dwIP;
	/* this+  20 */ bool m_bRecvPermit;
	/* this+  24 */ DWORD m_dwPingTime;
	/* this+  28 */ DWORD m_dwLastRecvTime;
	/* this+  32 */ bool m_bConnected;
	/* this+  36 */ int RECV_BUF_SIZE;
	/* this+  40 */ char* m_pRecvBuf;
	/* this+  44 */ int m_nRecvPos;
	/* this+  48 */ OVERLAPPEDEX m_ovRecv;
	/* this+4176 */ CCircleQueue m_SendQueue;
	/* this+4220 */ bool m_bInitialSendPostPermit;
	/* this+4221 */ OVERLAPPEDEX m_ovSend;
	/* this+8348 */ CProcess* m_pProcess;
	/* this+8352 */ DWORD m_dwSessionID;
	/* this+8356 */ CCriticalSection m_cs;

	friend class CCompletionPort;
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
