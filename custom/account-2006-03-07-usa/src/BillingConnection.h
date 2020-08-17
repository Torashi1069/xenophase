#pragma once
#include "Client_.h"
#include "Common/CriticalSection.h"


class CBillingConnection : public CClient_
{
public:
	CBillingConnection(int idx);
	virtual ~CBillingConnection();
	virtual void Init();
	virtual BOOL Process(char* buf, int* len);
	virtual bool Send(char* Packet, int MsgSize);
	void Close();
	BOOL ProcessPacket(char* packet, int len);
	void SelectThread(void* lpParam);
	DWORD GetLastQueuedTime();

public:
	//bool Listen(WORD wListenPort);
	//void AcceptThread(void* lpParam);
	//void HeartBeatSendThread(void* lpParam);

public:
	/* this+      0 */ //CClient_ baseclass_0;
	/* this+1659276 */ DWORD m_dwLastSendQueuedTime;
	/* this+1659280 */ CCriticalSection m_csSend;
	/* this+1659304 */ int m_nMyID;
	/* this+1659308 */ bool m_bInitialized;
	/* this+1659312 */ SOCKET m_listen_socket;
	/* this+1659316 */ WORD m_wListenPort;
};
