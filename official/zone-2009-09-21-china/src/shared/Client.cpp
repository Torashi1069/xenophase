#include "enum.hpp"
#include "Client.h"
#include "shared.h" // Trace


CClient::CClient(void) // line 11
{
	m_dwErrorCount = 0;
	m_asyncStream = NULL;
	InitializeCriticalSection(&m_disconnector_cs);
	m_nBanTime = 0;
}


CClient::~CClient(void) // line 19
{
	DeleteCriticalSection(&m_disconnector_cs);
}


hook_method<int (CClient::*)(void)> CClient::_GetType(SERVER, "CClient::GetType");
int CClient::GetType(void) // line ??
{
	return (this->*_GetType)();

	return UNKNOWN_TYPE;
}


hook_method<void (CClient::*)(const char* filename, int line, DWORD count, DWORD time)> CClient::_AddErrorCount(SERVER, "?AddErrorCount@CClient@@UAEXPBDHKK@Z");
void CClient::AddErrorCount(DWORD count, DWORD time) // line 30
{
	return (this->*_AddErrorCount2)(count, time);

	EnterCriticalSection(&m_disconnector_cs);

	Trace("AddErrorCount:%d\n", count);

	if( m_dwErrorCount < 4 )
	{
		m_dwErrorCount += count;
		m_nBanTime = time;
	}

	LeaveCriticalSection(&m_disconnector_cs);
}


hook_method<void (CClient::*)(DWORD count, DWORD time)> CClient::_AddErrorCount2(SERVER, "?AddErrorCount@CClient@@UAEXKK@Z");
void CClient::AddErrorCount(const char* filename, int line, DWORD count, DWORD time) // line 41
{
	return (this->*_AddErrorCount)(filename, line, count, time);

	EnterCriticalSection(&m_disconnector_cs);

	Trace("AddErrorCount:%d, %s(%d)\n", count, filename, line);

	if( m_dwErrorCount < 4 )
	{
		m_dwErrorCount += count;
		m_nBanTime = time;
	}

	LeaveCriticalSection(&m_disconnector_cs);
}


hook_method<void (CClient::*)(void)> CClient::_Init(SERVER, "CClient::Init");
void CClient::Init(void) // line 34 (Client.h)
{
	return (this->*_Init)();

	m_nBanTime = timeGetTime();
}


//hook_method<int (CClient::*)(void)> CClient::_IsErrorClient(SERVER, "CClient::IsErrorClient");
int CClient::IsErrorClient(void) // line ??
{
//	return (this->*_IsErrorClient)();

	if( m_dwErrorCount < 4 || timeGetTime() - m_nBanTime < 4000 )
	{
		return 0;
	}
	else
	{
		Trace("Error Client:%d!!\n", m_dwErrorCount);
		return 1;
	}
}


//hook_method<int (CClient::*)(void)> CClient::_Close(SERVER, "CClient::Close");
int CClient::Close(void) // line ??
{
//	return (this->*_Close)();

	return m_asyncStream->CAsyncStream::Close();
}


//hook_method<int (CClient::*)(void)> CClient::_GetErrorCount(SERVER, "CClient::GetErrorCount");
int CClient::GetErrorCount(void) // line ??
{
//	return (this->*_GetErrorCount)();

	return m_dwErrorCount;
}
