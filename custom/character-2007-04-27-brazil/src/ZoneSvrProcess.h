#pragma once
#include "Network3/AsyncProcess.h"
#include "Network3/Process.h"


class CZoneSvrProcess : public CProcess, public CAsyncProcess
{
public:
	CZoneSvrProcess();
	virtual ~CZoneSvrProcess();
	virtual bool OnRecv(char* buffer, int* len);
	virtual bool OnConnect();
	virtual void OnClose();
	int GetPacketSize(WORD wPacketType);
	bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);

public:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+40 */ //CAsyncProcess baseclass_40;

private:
	bool ProcessPacket_ServerEntry(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Logon(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_CharExit(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_SaveCharInfo(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_MapMove(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_SaveUsingTime(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Restart(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_ReqRemainTime(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_MoveToPVPWorld(DWORD dwSessionID, char* pPacket);
};
