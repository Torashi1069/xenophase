#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/Thread.h"
#include "Network3/CompletionPort.h"
#include "Network3/Stream.h"


CCompletionPort::CCompletionPort()
{
	m_hCompletionPort = INVALID_HANDLE_VALUE;
	m_nRunningThread = 0;
	m_nInThreadNum = 0;
	m_nWorkerThreadNum = 0;
}


CCompletionPort::~CCompletionPort()
{
	this->CCompletionPort::Destroy();
}


bool CCompletionPort::Create(int nWorkerThreadNum)
{
	if( nWorkerThreadNum <= 0 )
		return false;

	m_nWorkerThreadNum = nWorkerThreadNum;

	if( m_hCompletionPort != INVALID_HANDLE_VALUE )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - CreateIoCompletionPort fail! already Created", __FUNCTION__);
		return false;
	}

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if( m_hCompletionPort == NULL )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - CreateIoCompletionPort failed! gle - %d", __FUNCTION__, GetLastError());
		return false;
	}

	for( int i = 0; i < m_nWorkerThreadNum; ++i )
	{
		int* pParam = new int;
		if( pParam == NULL )
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - not enough memory!", __FUNCTION__);
			return false;
		}

		*pParam = i;

		if( (HANDLE)CreateMemberThread<CCompletionPort>(this, &CCompletionPort::WorkerThread, pParam) == INVALID_HANDLE_VALUE )
		{
			if( errno == EAGAIN )
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CreateMemberThread<CCompletionPort> fail! errno EAGAIN(%d)", errno);
			else if( errno == EINVAL )
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CreateMemberThread<CCompletionPort> fail! errno EINVAL(%d)", errno);
			else
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CreateMemberThread<CCompletionPort> fail! errno %d", errno);

			return false;
		}
	}

	int nWaitCycles = 0;
	while( m_nInThreadNum < m_nWorkerThreadNum )
	{// wait until all worker threads start
		Sleep(500);
		++nWaitCycles;

		if( nWaitCycles >= 6 )
		{// waited too long, abort.
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - Worker Thread Create failed", __FUNCTION__);
			this->CCompletionPort::Destroy();
			return false;
		}
	}

	return true;
}


void CCompletionPort::Destroy()
{
	if( m_hCompletionPort == INVALID_HANDLE_VALUE )
		return;

	for( int i = 0; i < m_nWorkerThreadNum; ++i )
	{
		OVERLAPPEDEX* ovex = new OVERLAPPEDEX;
		memset(&ovex->m_overlapped, 0, sizeof(ovex->m_overlapped));

		if( !PostQueuedCompletionStatus(m_hCompletionPort, 0, NULL, reinterpret_cast<OVERLAPPED*>(ovex)) )
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - PostQueuedCompletionStatus failed! gle %d", __FUNCTION__, GetLastError());
	}

	int nCount = 0; // wait cycles
	while( m_nInThreadNum > 0 )
	{
		Sleep(100);
		++nCount;

		if( nCount >= 40 )
		{// waited too long, give up.
			break;
		}
	}

	CloseHandle(m_hCompletionPort);
	m_hCompletionPort = INVALID_HANDLE_VALUE;
}


void CCompletionPort::WorkerThread(void* lpThreadData)
{
	delete lpThreadData; // unused

	InterlockedIncrement(&m_nInThreadNum);
	InterlockedIncrement(&m_nRunningThread);

	while( 1 )
	{
		DWORD dwTransferredBytes;
		CStream* lpStream;
		OVERLAPPEDEX* lpOverlappedEx;

		InterlockedDecrement(&m_nRunningThread);

		BOOL bRet = GetQueuedCompletionStatus(m_hCompletionPort, &dwTransferredBytes, (PULONG_PTR)&lpStream, (LPOVERLAPPED*)&lpOverlappedEx, INFINITE);
		DWORD dwError = GetLastError();

		InterlockedIncrement(&m_nRunningThread);

		if( bRet == FALSE )
		{// failure
			if( lpOverlappedEx == NULL )
			{// complete failure
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - ov null, GQCS fail gle %d", __FUNCTION__, dwError);
				continue;
			}

			if( lpStream->m_bDetailedCloseInfo )
			{
				char szIP[100] = {};
				CNetwork::GetObj()->CNetwork::GetTextIP(lpStream->m_dwIP, szIP);
				CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s closed %s/%s GLE: %d wsagle: %u", szIP, __FUNCTION__, "GetQueuedCompletionStatus returned false", dwError, WSAGetLastError());
			}

			lpStream->CStream::Close(0);
			lpStream->CStream::SubRef();
			continue;
		}

		if( dwTransferredBytes == 0 && lpStream == NULL )
		{// shutdown signal?
			delete lpOverlappedEx;
			break;
		}

		lpStream->CStream::HandleIo(lpOverlappedEx, dwTransferredBytes);
	}

	InterlockedDecrement(&m_nRunningThread);
	InterlockedDecrement(&m_nInThreadNum);
}


HANDLE CCompletionPort::AssociateSocket(SOCKET s, DWORD CompletionKey, DWORD& rError)
{
	HANDLE hResult;
	m_csCompletionPort.Enter();

	if( m_hCompletionPort != INVALID_HANDLE_VALUE )
	{
		hResult = CreateIoCompletionPort((HANDLE)s, m_hCompletionPort, CompletionKey, 0);
		rError = GetLastError();
	}
	else
	{
		hResult = NULL;
		rError = -1;
	}

	m_csCompletionPort.Leave();
	return hResult;
}


int CCompletionPort::GetWorkerThreadNum()
{
	return m_nWorkerThreadNum;
}


LONG CCompletionPort::GetInThreadNum()
{
	return m_nInThreadNum;
}


LONG CCompletionPort::GetRunningThreadNum()
{
	return m_nRunningThread;
}
