#include "Common/EnterTraceLog.h"
#include "Common/Thread.h"
#include "Network3/AsyncProcess.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/Process.h"


CAsyncProcessMgr::CAsyncProcessMgr()
{
	m_pPacketQueue = NULL;
	m_nThreadNum = 0;
	m_bProcessPermit = true;
}


CAsyncProcessMgr::~CAsyncProcessMgr()
{
	this->CAsyncProcessMgr::Destroy();

	if( m_pPacketQueue != NULL )
	{
		delete[] m_pPacketQueue;
		m_pPacketQueue = NULL;
	}
}


bool CAsyncProcessMgr::Create(int nThreadNum, int nPacketPoolCount)
{
	if( m_nThreadNum > 0 )
		return false;

	if( nThreadNum <= 0 )
		return false;

	m_pPacketQueue = new PACKET_QUEUE[nThreadNum];
	if( m_pPacketQueue == NULL )
		return false;

	if( !m_async_packet_pool.CMemPool<ASYNCPACKET>::Create(nPacketPoolCount) )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - m_async_packet_pool creation failed", __FUNCTION__);
		return false;
	}

	m_bProcessPermit = true;

	for( int i = 0; i < nThreadNum; ++i )
	{
		if( (HANDLE)CreateMemberThread<CAsyncProcessMgr>(this, &CAsyncProcessMgr::ProcessThread, (void*)i) == INVALID_HANDLE_VALUE )
		{
			if( errno == EAGAIN )
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CreateMemberThread< CAsyncProcessMgr > ProcessThread fail! errno EAGAIN(%d)", errno);
			else if( errno == EINVAL )
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CreateMemberThread< CAsyncProcessMgr > ProcessThread fail! errno EINVAL(%d)", errno);
			else
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CreateMemberThread< CAsyncProcessMgr > ProcessThread fail! errno %d", errno);

			return false;
		}
	}

	m_nThreadNum = nThreadNum;
	return true;
}


void CAsyncProcessMgr::Destroy()
{
	m_bProcessPermit = false;
	Sleep(500);

	if( m_pPacketQueue == NULL )
		return;

	for( int i = 0; i < m_nThreadNum; ++i )
	{
		m_pPacketQueue[i].m_cs.Enter();

		while( m_pPacketQueue[i].m_Queue.size() != 0 )
		{
			ASYNCPACKET* p = m_pPacketQueue[i].m_Queue.front();
			m_pPacketQueue[i].m_Queue.pop();
			m_async_packet_pool.CMemPool<ASYNCPACKET>::Free(p);
		}

		m_pPacketQueue[i].m_cs.Leave();
	}
}


bool CAsyncProcessMgr::PushPacket(ASYNCPACKET* pAsyncPacket, unsigned int thread_idx)
{
	int nIndex = thread_idx % m_nThreadNum;

	if( m_nThreadNum <= 0 || m_pPacketQueue == NULL )
		return false;

	m_pPacketQueue[nIndex].m_cs.Enter();
	m_pPacketQueue[nIndex].m_Queue.push(pAsyncPacket);
	m_pPacketQueue[nIndex].m_cs.Leave();
	return true;
}


ASYNCPACKET* CAsyncProcessMgr::AllocPacket()
{
	return m_async_packet_pool.CMemPool<ASYNCPACKET>::Allocate();
}


int CAsyncProcessMgr::GetPoolSize()
{
	return m_async_packet_pool.CMemPool<ASYNCPACKET>::GetSize();
}


int CAsyncProcessMgr::GetPoolAllocSize()
{
	return m_async_packet_pool.CMemPool<ASYNCPACKET>::GetAllocatedCount();
}


void CAsyncProcessMgr::ProcessThread(void* lpParam)
{
	int threadId = (int)lpParam;
	PACKET_QUEUE& pq = m_pPacketQueue[threadId];

	while( m_bProcessPermit )
	{
		pq.m_cs.Enter();
		size_t size = pq.m_Queue.size();
		pq.m_cs.Leave();

		for( size_t cnt = 0; cnt < size && m_bProcessPermit; ++cnt )
		{
			pq.m_cs.Enter();

			if( pq.m_Queue.size() == 0 )
			{
				pq.m_cs.Leave();
				break;
			}

			ASYNCPACKET* pAsyncPacket = pq.m_Queue.front();
			pq.m_Queue.pop();

			pq.m_cs.Leave();

			class CSomeProcess : public CProcess, public CAsyncProcess {} * p = static_cast<CSomeProcess*>(pAsyncPacket->pProcessPtr);
			if( !p->ProcessPacket(pAsyncPacket->dwSessionID, pAsyncPacket->packet, pAsyncPacket->wPacketType, pAsyncPacket->nPacketSize) )
				p->CProcess::CloseOuter(pAsyncPacket->dwSessionID, 0);

			m_async_packet_pool.CMemPool<ASYNCPACKET>::Free(pAsyncPacket);
		}

		Sleep(1);
	}

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s out", __FUNCTION__);
}
