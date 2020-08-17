#pragma once
#include "Network3/Process.h"
#include "Network3/AsyncProcess.h"
struct SUSER_;


class CCharSvrProcess : public CProcess, public CAsyncProcess
{
public:
	CCharSvrProcess();
	virtual ~CCharSvrProcess();
	virtual bool OnRecv(char* buffer, int* len);
	virtual bool OnConnect();
	virtual void OnClose();
	virtual bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);
	int GetPacketSize(WORD wPacketType);
	void OnIPBonusLicenseLimit(DWORD in_dwSessionID, char* in_pPacket);
	void SendLoginAck(SUSER_& user, DWORD dwSessionID);
	void SendLoginAck(DWORD dwAID);
//	static double GetProcessedNumPerSecond();

private:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+60 */ //CAsyncProcess baseclass_60;
	/* this+64 */ int m_nSID;
	/* static  */ static long m_nProcessedNum;
	/* static  */ static DWORD m_dwLastCalTime;
};
