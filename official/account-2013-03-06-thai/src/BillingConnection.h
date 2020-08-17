#pragma once
#include "Client_.h"
#include "Common/CriticalSection.h"


enum BILLINGSERVER_TYPE
{
	NOMAL_BILLINGSERVER = 1,
	GAMEBANG_BILLNGSERVER = 2,
};


class CBillingConnection : public CClient_
{
public:
	CBillingConnection();
	virtual ~CBillingConnection();
	void SetServerType(BILLINGSERVER_TYPE type);
	virtual void Init();
	virtual BOOL Process(char* buf, int* len);
	virtual bool Send(char* Packet, int MsgSize);
	BOOL ProcessPacket(char* packet, int len);
	void SelectThread(void* lpParam);
	DWORD GetLastQueuedTime();
	void Close();

public:
	/* this+      0 */ //CClient_ baseclass_0;
	/* this+1659272 */ CCriticalSection m_csSend;
	/* this+1659296 */ DWORD m_dwLastSendQueuedTime;
	/* this+1659300 */ DWORD m_dwLastRecvTime;
	/* this+1659304 */ BILLINGSERVER_TYPE m_BillingServerType;
};


void SendHeartBeatToBill(BILLINGSERVER_TYPE billingServerType);
