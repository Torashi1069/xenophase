#pragma once
#include "Common/CriticalSection.h"
class CClient_;


class CSendQueue
{
private:
	/* this+     0 */ int PacketSize[70000];
	/* this+280000 */ char* Packet[70000];
	/* this+560000 */ int SentSize[70000];
public:
	/* this+840000 */ int front;
	/* this+840004 */ int rear;
	/* this+840008 */ CCriticalSection m_csSendQueue;
	/* this+840032 */ LONG m_dwCount;

public:
	CSendQueue();
	~CSendQueue();
	void Init();
	BOOL InsertQueue(char* packet, int MsgSize, int TotalSendSize);
	bool ProcessQueue(CClient_* pClient);
	LONG GetCount();
};
