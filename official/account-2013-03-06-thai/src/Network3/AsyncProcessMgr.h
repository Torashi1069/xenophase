#pragma once
#include "Common/CriticalSection.h"
#include "Common/MemPool.h"
#include "Network3/AsyncProcess.h"


struct ASYNCPACKET
{
	/* this+   0 */ char packet[1024];
	/* this+1024 */ DWORD dwSessionID;
	/* this+1028 */ CAsyncProcess* pProcessPtr;
	/* this+1032 */ WORD wPacketType;
	/* this+1036 */ int nPacketSize;
};


struct PACKET_QUEUE
{
	/* this+ 0 */ CCriticalSection m_cs;
	/* this+24 */ std::queue<ASYNCPACKET*,std::list<ASYNCPACKET*>> m_Queue;
};


class CAsyncProcessMgr
{
public:
	CAsyncProcessMgr();
	~CAsyncProcessMgr();
	bool Create(int nThreadNum, int nPacketPoolCount);
	void Destroy();
	bool PushPacket(ASYNCPACKET* pAsyncPacket, unsigned int thread_idx);
	ASYNCPACKET* AllocPacket();
	int GetPoolSize();
	int GetPoolAllocSize();

private:
	void ProcessThread(void* lpParam);

private:
	/* this+ 0 */ PACKET_QUEUE* m_pPacketQueue;
	/* this+ 4 */ CMemPool<ASYNCPACKET> m_async_packet_pool;
	/* this+56 */ int m_nThreadNum;
	/* this+60 */ bool m_bProcessPermit;
};
