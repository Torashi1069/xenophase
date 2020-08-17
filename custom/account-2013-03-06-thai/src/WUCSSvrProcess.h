#pragma once
#include "Network3/Process.h"
#include "Network3/AsyncProcess.h"


class CWUCSSvrClient : public CProcess, public CAsyncProcess
{
public:
//	CWUCSSvrClient();
//	~CWUCSSvrClient();
//	bool OnConnect();
//	void OnClose();
//	bool OnRecv(char*, int*);
//	bool ProcessPacket(unsigned long, char*, unsigned short, int);
//	bool ProcessPacket_SendCheckLine(unsigned long, char*, unsigned short, int);
//	bool ProcessPacket_RecvCheckLine(unsigned long, char*, unsigned short, int);
//	bool SendAccUserCounter(unsigned long, const char*, const char*);
//	bool SendCharUserCounter(unsigned long*);
//	void SendCheckLinePakcet(unsigned long);
//	int GetPacketType(char*);
//	int GetPacketSize(unsigned short);

private:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+60 */ //CAsyncProcess baseclass_60;
	/* this+64 */ unsigned long m_nCharSvrCount;
};
