#pragma once
#include "Network2/Process.h"


class CCharSvrProcess : public CProcess
{
public:
	CCharSvrProcess();
	virtual ~CCharSvrProcess();
	virtual bool OnConnect();
	virtual bool Process();
	virtual void OnClose();
	int GetPacketSize(WORD wPacketType);
	bool ProcessPacket(WORD wPacketType, WORD wPacketSize, char* pPacket);

private:
	bool ProcessPacket_LOGON(char* pPacket);
	bool ProcessPacket_LogOn_Session(char* pPacket);
	bool ProcessPacket_PCINFOUPDATE(char* pPacket);
	bool ProcessPacket_CHAR_EXIT(char* pPacket);

private:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+40 */ int m_nSID;
};
