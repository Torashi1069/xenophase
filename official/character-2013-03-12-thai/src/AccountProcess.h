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
	bool ProcessPacket_DispatchPremiumInfo(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_ack_LimitInfo(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_notify_pcbang_playing_time(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_Ack_Extend_Billing_Info(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_UpDatePcBangCnt(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_AH_DISPATCH_PREMIUM_INFO_CHN(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_AH_CONNECTED_CHN(const DWORD dwSessionID, char* pPacket);
//	void OnFatigueCHN(const unsigned long, const short, const short, const unsigned long);

private:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+56 */ //CAsyncProcess baseclass_56;
	/* this+60 */ short m_nBeforePKTHeader;
	/* this+64 */ int m_nBeforePKTRecvLength;
	/* this+68 */ int m_nBeforeOrgPKTSize;
};
