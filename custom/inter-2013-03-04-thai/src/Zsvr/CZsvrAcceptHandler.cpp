#include "InterServer.h"
#include "Zsvr/CZsvrAcceptHandler.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/ServerInfo.h"


/// singleton instance
CZsvrAcceptHandler*& CZsvrAcceptHandler::m_cpSelf = VTOR<CZsvrAcceptHandler*>(DetourFindFunction(EXEPATH(), "CZsvrAcceptHandler::m_cpSelf"));


CZsvrAcceptHandler::CZsvrAcceptHandler()
{
	m_bOK = true;
}


CZsvrAcceptHandler::~CZsvrAcceptHandler()
{
}


bool CZsvrAcceptHandler::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CZsvrAcceptHandler();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZsvrAcceptHandler::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZsvrAcceptHandler::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZsvrAcceptHandler* CZsvrAcceptHandler::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZsvrAcceptHandler::isOK() const
{
	return m_bOK;
}


BOOL CZsvrAcceptHandler::Init(bool in_bUsePrivateIP, int in_StreamPoolSize)
{
	if( in_bUsePrivateIP )
		g_serverInfo.CServerInfo::GetZoneServerIPPrivate(m_set);
	else
		g_serverInfo.CServerInfo::GetZoneServerIP(m_set);

	return ( m_streamPool.CMemoryMgr<CAsyncStream>::Init(in_StreamPoolSize) == true );
}


CAsyncStream* CZsvrAcceptHandler::AllocStream()
{
	return m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
}


void CZsvrAcceptHandler::FreeStream(CAsyncStream* stream)
{
	m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
}


bool CZsvrAcceptHandler::OnConnect(const SOCKET in_Socket, const int in_ZSID, const DWORD in_dwIP)
{
	if( in_Socket == INVALID_SOCKET || in_ZSID == -1 )
		return false;

	std::set<DWORD>::iterator iter = m_set.find(in_dwIP);
	if( iter == m_set.end() )
		return false;

	if( CZsvrMgr::GetObj()->CZServerMgr::FindServer(in_ZSID) )
		CZsvrMgr::GetObj()->CZsvrMgr::DeleteServer(in_ZSID);

	CAsyncStream* stream = m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
	if( stream == NULL )
		return false;

	stream->CAsyncStream::SetSendQueueSize(8000 * 1024);
	stream->CAsyncStream::SetRecvQueueSize(8000 * 1024);

	CZServer* zserver = CZsvrMgr::GetObj()->CZServerMgr::AllocServer();
	if( zserver == NULL )
	{
		m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
		return false;
	}

	stream->Init(&zserver->m_packetHandler);
	zserver->CZServer::Init(in_ZSID, stream);

	CZsvrMgr::GetObj()->CZServerMgr::AddServer(in_ZSID, zserver, in_dwIP);
	if( !stream->Open(in_Socket) )
	{
		CZsvrMgr::GetObj()->CZsvrMgr::DeleteServer(in_ZSID);
		return false;
	}

	return true;
}
