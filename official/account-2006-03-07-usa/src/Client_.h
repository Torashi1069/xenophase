#pragma once
#include "RecvQueue.h"
#include "SendQueue.h"


class CClient_
{
public:
	/* this+      0 */ //const CClient_::`vftable';
	/* this+      4 */ SOCKET m_socket;
	/* this+      8 */ CSendQueue m_qSend;
	/* this+ 840044 */ CReceiveQueue m_qReceive;
	/* this+1659256 */ bool m_bConnected;
	/* this+1659257 */ bool m_bSendable;
	/* this+1659260 */ DWORD m_dwIP;
	/* this+1659264 */ time_t m_LastSendTime;
	/* this+1659268 */ DWORD m_dwLastRecvTime;
	/* this+1659272 */ bool m_bProcessPermit;

public:
	CClient_();
	virtual ~CClient_();
	virtual void Init();
	SOCKET GetSocket();
	virtual bool Send(char* Packet, int MsgSize);
	BOOL Recv();
	time_t GetSendCount();
	virtual BOOL Process(char* buf, int* len) = 0;
};
