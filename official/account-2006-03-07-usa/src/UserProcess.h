#pragma once
#include "Network2/Process.h"


class CUserProcess : public CProcess
{
public:
	CUserProcess();
	virtual ~CUserProcess();
	virtual bool OnConnect();
	virtual bool Process();
	virtual void OnClose();
	int GetPacketSize(WORD wPacketType);
	bool ProcessPacket(WORD wPacketType, WORD wPacketSize, char* pPacket);

public:
	/* this+0 */ //CProcess baseclass_0;
};
