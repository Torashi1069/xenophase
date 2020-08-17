#include "ServerManager/CMsvrAcceptHandler.h"
#include "ServerManager/CMsvrMgr.h"


/// singleton instance
CMsvrAcceptHandler*& CMsvrAcceptHandler::m_cpSelf = VTOR<CMsvrAcceptHandler*>(DetourFindFunction(EXEPATH(), "CMsvrAcceptHandler::m_cpSelf"));


CMsvrAcceptHandler::CMsvrAcceptHandler()
{
	m_bOK = true;
}


CMsvrAcceptHandler::~CMsvrAcceptHandler()
{
}


bool CMsvrAcceptHandler::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMsvrAcceptHandler();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMsvrAcceptHandler::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMsvrAcceptHandler::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMsvrAcceptHandler* CMsvrAcceptHandler::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMsvrAcceptHandler::isOK() const
{
	return m_bOK;
}


BOOL CMsvrAcceptHandler::Init(int streamPoolSize)
{
	return ( m_streamPool.CMemoryMgr<CAsyncStream>::Init(streamPoolSize) == true );
}


CAsyncStream* CMsvrAcceptHandler::AllocStream()
{
	return m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
}


void CMsvrAcceptHandler::FreeStream(CAsyncStream* pStream)
{
	m_streamPool.CMemoryMgr<CAsyncStream>::Free(pStream);
}


BOOL CMsvrAcceptHandler::OnConnect(SOCKET s, DWORD ip)
{
	CAsyncStream* stream = m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
	if( stream == NULL )
		return FALSE;

	CMClient* server = CMsvrMgr::GetObj()->CMClientMgr::AllocServer();
	if( server == NULL )
	{
		m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
		return FALSE;
	}

	stream->Init(&server->m_packetHandler);
	server->CMClient::Init(stream, ip);

	int id = CMsvrMgr::GetObj()->CMClientMgr::AddServer(server);
	if( !stream->Open(s) )
	{
		CMsvrMgr::GetObj()->CMsvrMgr::DeleteServer(id);
		return FALSE;
	}

	return TRUE;
}
