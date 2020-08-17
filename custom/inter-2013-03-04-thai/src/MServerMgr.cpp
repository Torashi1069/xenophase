#include "MServerMgr.h"


CMClientMgr::CMClientMgr()
{
}


CMClientMgr::~CMClientMgr()
{
	DeleteCriticalSection(&m_mserverMgr_cs);
}


int CMClientMgr::AddServer(CMClient* mServer)
{
	EnterCriticalSection(&m_mserverMgr_cs);

	++m_serverIDcounter;
	m_mServerMap[m_serverIDcounter] = mServer;
	mServer->CMClient::SetServerID(m_serverIDcounter);

	LeaveCriticalSection(&m_mserverMgr_cs);
	return m_serverIDcounter;
}


void CMClientMgr::Init(int count)
{
	InitializeCriticalSection(&m_mserverMgr_cs);
	m_mserverMemoryPool.CMemoryMgr<CMClient>::Init(count);
	m_serverIDcounter = 5;
}


void CMClientMgr::SendMsgToMServer(int zServerID, short len, const char* buf)
{
	EnterCriticalSection(&m_mserverMgr_cs);

	std::map<int,CMClient*>::iterator Serveriterator = m_mServerMap.find(zServerID);
	if( Serveriterator != m_mServerMap.end() )
		Serveriterator->second->Send(len, buf);

	LeaveCriticalSection(&m_mserverMgr_cs);
}


void CMClientMgr::BroadCast(short len, const char* buf)
{
	EnterCriticalSection(&m_mserverMgr_cs);

	for( std::map<int,CMClient*>::iterator iter = m_mServerMap.begin(); iter != m_mServerMap.end(); ++iter )
		iter->second->CClient::Send(len, buf);

	LeaveCriticalSection(&m_mserverMgr_cs);
}


CMClient* CMClientMgr::AllocServer()
{
	return m_mserverMemoryPool.CMemoryMgr<CMClient>::Alloc();
}


void CMClientMgr::FreeServer(CMClient* server)
{
	m_mserverMemoryPool.CMemoryMgr<CMClient>::Free(server);
}


BOOL CMClientMgr::IsConnectedServer(int SID)
{
	BOOL result;
	EnterCriticalSection(&m_mserverMgr_cs);

	if( m_mServerMap.find(SID) == m_mServerMap.end() )
		result = FALSE;
	else
		result = TRUE;

	LeaveCriticalSection(&m_mserverMgr_cs);
	return result;
}
