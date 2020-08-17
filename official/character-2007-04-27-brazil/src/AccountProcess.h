#pragma once
#include "Network3/AsyncProcess.h"
#include "Network3/Process.h"


class CAccountProcess : public CProcess, public CAsyncProcess
{
public:
	CAccountProcess();
	virtual ~CAccountProcess();
	virtual bool OnRecv(char* buffer, int* len);
	virtual bool OnConnect();
	virtual void OnClose();
	virtual bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);
	int GetPacketSize(WORD wPacketType);

private:
	bool ProcessPacket_LogonPermit(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_LogonRefuse(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Billing_Ack(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_LogonPermit_Session(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_LogonRefuse_Session(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Disconnect(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Info_Remain_Time(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_res_remain_time(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_AckPacketInfo(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_CollectDead(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_svr_ping(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_ack_LimitInfo(DWORD dwSessionID, char* pPacket);

private:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+40 */ //CAsyncProcess baseclass_40;
};
