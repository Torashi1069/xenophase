#include "Client.h"
#include "globals.hpp"


CClient::CClient(void)
{
	m_dwErrorCount = 0;
	m_asyncStream = NULL;
	InitializeCriticalSection(&m_disconnector_cs);
	m_nBanTime = 0;
}


CClient::~CClient(void)
{
	DeleteCriticalSection(&m_disconnector_cs);
}


hook_method<int (CClient::*)(void)> CClient::_GetType(SERVER, "CClient::GetType");
int CClient::GetType(void)
{
	return (this->*_GetType)();

	//TODO
}


hook_method<void (CClient::*)(const char* filename, int line, unsigned long count, unsigned long time)> CClient::_AddErrorCount(SERVER, "CClient::AddErrorCount");
void CClient::AddErrorCount(const char* filename, int line, unsigned long count, unsigned long time)
{
	return (this->*_AddErrorCount)(filename, line, count, time);

	//TODO
}


hook_method<void (CClient::*)(unsigned long count, unsigned long time)> CClient::_AddErrorCount2(SERVER, "CClient::AddErrorCount");
void CClient::AddErrorCount(unsigned long count, unsigned long time)
{
	return (this->*_AddErrorCount2)(count, time);

	//TODO
}


hook_method<void (CClient::*)(void)> CClient::_Init(SERVER, "CClient::Init");
void CClient::Init(void)
{
	return (this->*_Init)();

	//TODO
}


/*
hook_method<int (CClient::*)(void)> CClient::_IsErrorClient(SERVER, "CClient::IsErrorClient");
int CClient::IsErrorClient(void)
{
	return (this->*_IsErrorClient)();

	// copied from zone, needs checking
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
*/


hook_method<int (CClient::*)(void)> CClient::_IsErrorServer(SERVER, "CClient::IsErrorServer");
int CClient::IsErrorServer(void)
{
	return (this->*_IsErrorServer)();

	if( m_dwErrorCount < 4 )
		return 0;

	Trace("Error Server:%d!!\n", m_dwErrorCount);
	return 1;
}


hook_method<int (CClient::*)(void)> CClient::_Close(SERVER, "CClient::Close");
int CClient::Close(void)
{
	return (this->*_Close)();

	return m_asyncStream->CAsyncStream::Close();
}


hook_method<void (CClient::*)(int len, const char* buf)> CClient::_Send(SERVER, "CClient::Send");
void CClient::Send(int len, const char* buf)
{
	return (this->*_Send)(len, buf);

	//TODO
}


hook_method<int (CClient::*)(void)> CClient::_GetErrorCount(SERVER, "CClient::GetErrorCount");
int CClient::GetErrorCount(void)
{
	return (this->*_GetErrorCount)();

	//TODO
}
