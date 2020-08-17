#include "Common/Network.h"
#include "Common/Reporter.h"
#include "Common/Thread.h"
#include "Network2/CompletionPort.h"
#include "Network2/Stream.h"


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

	m_csCompletionPort.Enter();

	if( m_hCompletionPort != INVALID_HANDLE_VALUE )
	{
		m_csCompletionPort.Leave();
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CCompletionPort::Create - CreateIoCompletionPort fail! already Created\n");
		return false;
	}

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if( m_hCompletionPort == NULL )
	{
		m_csCompletionPort.Leave();
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CCompletionPort::Create - CreateIoCompletionPort failed! gle - %d\n", GetLastError());
		return false;
	}

	m_csCompletionPort.Leave();

	for( int i = 0; i < m_nWorkerThreadNum; ++i )
	{
		int* pParam = new int;
		if( pParam == NULL )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("not enough memory! - CCompletionPort::Create\n");
			return false;
		}

		*pParam = i;

		if( (HANDLE)CreateMemberThread<CCompletionPort>(this, &CCompletionPort::WorkerThread, pParam) == INVALID_HANDLE_VALUE )
		{
			if( errno == EAGAIN )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread<CCompletionPort> fail! errno EAGAIN(%d)", errno);
			else if( errno == EINVAL )
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread<CCompletionPort> fail! errno EINVAL(%d)", errno);
			else
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateMemberThread<CCompletionPort> fail! errno %d", errno);

			return false;
		}
	}

	for( int i = 0; i < 6 && m_nInThreadNum < m_nWorkerThreadNum; ++i )
		Sleep(500);

	if( m_nInThreadNum < m_nWorkerThreadNum )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Worker Thread Create failed\n");
		this->CCompletionPort::Destroy();
		return false;
	}

	return true;
}


void CCompletionPort::Destroy()
{
	m_csCompletionPort.Enter();

	if( m_hCompletionPort == INVALID_HANDLE_VALUE )
	{
		m_csCompletionPort.Leave();
		return;
	}

	for( int i = 0; i < m_nWorkerThreadNum; ++i )
	{
		OVERLAPPEDEX* ovex = new OVERLAPPEDEX;
		memset(&ovex->m_overlapped, 0, sizeof(ovex->m_overlapped));

		if( !PostQueuedCompletionStatus(m_hCompletionPort, 0, NULL, reinterpret_cast<OVERLAPPED*>(ovex)) )
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CCompletionPort::Destroy() failed! gle %d", GetLastError());
	}

	for( int i = 0; i < 500 && m_nInThreadNum > 0; ++i )
		Sleep(10);

	CloseHandle(m_hCompletionPort);
	m_hCompletionPort = INVALID_HANDLE_VALUE;

	m_csCompletionPort.Leave();
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
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("ov null, GQCS fail gle %d\n", dwError);
				continue;
			}

			if( lpStream->m_bDetailedCloseInfo )
			{
				char szIP[100] = {};
				CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(lpStream->GetIP(), szIP);
				CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s closed %s/%s GLE: %d wsagle: %u", szIP, __FUNCTION__, "GetQueuedCompletionStatus returned false", dwError, WSAGetLastError());
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


int CCompletionPort::GetThreadNum()
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
