#pragma once


class CAsyncProcess
{
public:
	virtual bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize) = 0;
};
