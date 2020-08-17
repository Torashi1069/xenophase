#pragma once
#include "NetLib/PacketQueue.h"


class CPacketHandler
{
public:
	virtual int OnProcess();

public:
	CPacketHandler();

public:
	virtual int OnRecvHook(int byteTransferred, char* buf);
	virtual void OnRecvOverflow(int byteTransferred);
	virtual void OnRecv(int byteTransferred);
	virtual void OnClose();
	virtual void SetLastError(DWORD lastError);
	virtual void AddSendBytes(int byteTransferred);
	void Reset();
	virtual void SetQueue(CPacketQueue* queue);

protected:
	/* this+0 */ //const CPacketHandler::`vftable';
	/* this+4 */ CPacketQueue* m_recvQueue;
};
