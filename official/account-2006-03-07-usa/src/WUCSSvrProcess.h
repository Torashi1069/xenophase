#pragma once
#include "Network2/Process.h"


class CWUCSSvrClient : public CProcess
{
public:
	CWUCSSvrClient();
	virtual ~CWUCSSvrClient();
	virtual bool OnConnect();
	virtual bool Process();
	virtual void OnClose();
	bool ProcessPacket(WORD wPacketType, WORD wPacketSize, char* pPacket);
//	bool ProcessPacket_SendCheckLine(WORD wPacketType, WORD wPacketSize, char* pPacket);
	bool ProcessPacket_RecvCheckLine(WORD wPacketType, WORD wPacketSize, char* pPacket);
	bool SendAccUserCounter(DWORD counter, const char* date, const char* time);
	bool SendCharUserCounter(DWORD* userCounter);
//	void SendCheckLinePakcet(DWORD);
//	int GetPacketType(char*);
	int GetPacketSize(WORD wPacketType);

private:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+40 */ unsigned long m_nCharSvrCount;
};
