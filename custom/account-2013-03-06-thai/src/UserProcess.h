#pragma once
#include "Network3/Process.h"
#include "Network3/AsyncProcess.h"


class CUserProcess : public CProcess, public CAsyncProcess
{
public:
	CUserProcess();
	virtual ~CUserProcess();
	virtual bool OnRecv(char* buffer, int* len);
	virtual bool OnConnect();
	virtual void OnClose();
	virtual void OnIdle();
	virtual bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);
	int GetPacketSize(WORD wPacketType);

private:
	bool ProcessPacket_CA_CONNECT_INFO_CHANGED(char* pPacket);
	bool ProcessPacket_CA_REQ_HASH(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);

private:
	/* this+  0 */ //CProcess baseclass_0;
	/* this+ 60 */ //CAsyncProcess baseclass_60;
	/* this+ 64 */ char m_RandStr[16];
	/* this+ 80 */ char m_PasswdMD5[16];
	/* this+ 96 */ bool m_bRandStrSent;
	/* this+100 */ DWORD m_dwAID;
	/* this+104 */ bool m_bCA_LOGIN_Received;
};
