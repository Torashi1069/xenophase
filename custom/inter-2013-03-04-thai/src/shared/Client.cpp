#include "NetLib/AsyncStream.h"
#include "shared/Client.h"
#include "shared/shared.h"


CClient::CClient()
{
	m_asyncStream = NULL;
	InitializeCriticalSection(&m_disconnector_cs);
	m_dwErrorCount = 0;
	m_nBanTime = 0;
}


CClient::~CClient()
{
	DeleteCriticalSection(&m_disconnector_cs);
}


int CClient::GetType()
{
	return 4; // UNKNOWN_TYPE
}


void CClient::Init()
{
	m_nBanTime = timeGetTime();
}


BOOL CClient::Close()
{
	return m_asyncStream->CAsyncStream::Close(false);
}


void CClient::Send(int len, const char* buf)
{
	m_asyncStream->CAsyncStream::Send(len, buf);
}


int CClient::GetErrorCount()
{
	return m_dwErrorCount;
}


void CClient::AddErrorCnt(const char* in_File, const int in_Line, const DWORD in_Cnt, const DWORD in_TM)
{
	EnterCriticalSection(&m_disconnector_cs);

	if( m_dwErrorCount < 4 )
	{
		m_dwErrorCount += in_Cnt;
		m_nBanTime = in_TM;
	}

	LeaveCriticalSection(&m_disconnector_cs);
}


BOOL CClient::IsErrorClient()
{
	if( m_dwErrorCount < 4 || timeGetTime() - m_nBanTime < 4000 )
		return FALSE;

	Trace("Error Client:%d!!\n", m_dwErrorCount);
	return TRUE;
}


BOOL CClient::IsErrorServer()
{
	if( m_dwErrorCount < 4 )
		return FALSE;

	Trace("Error Server:%d!!\n", m_dwErrorCount);
	return TRUE;
}
