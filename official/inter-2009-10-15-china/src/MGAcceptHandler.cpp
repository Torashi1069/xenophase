#include "MGAcceptHandler.h"
#include "MServerMgr.h"
#include "globals.hpp"


CMGAcceptHandler::CMGAcceptHandler(void) // line 17
{
}


CMGAcceptHandler::~CMGAcceptHandler(void) // line 21
{
}


hook_method<int (CMGAcceptHandler::*)(int streamPoolSize)> CMGAcceptHandler::_Init(SERVER, "CMGAcceptHandler::Init");
int CMGAcceptHandler::Init(int streamPoolSize) // line 26
{
	return (this->*_Init)(streamPoolSize);

	return m_streamPool.CMemoryMgr<CAsyncStream>::Init(streamPoolSize);
}


hook_method<CAsyncStream* (CMGAcceptHandler::*)(void)> CMGAcceptHandler::_AllocStream(SERVER, "CMGAcceptHandler::AllocStream");
CAsyncStream* CMGAcceptHandler::AllocStream(void) // line 25 (MGAcceptHandler.h)
{
	return (this->*_AllocStream)();

	return m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
}


hook_method<void (CMGAcceptHandler::*)(CAsyncStream* stream)> CMGAcceptHandler::_FreeStream(SERVER, "CMGAcceptHandler::FreeStream");
void CMGAcceptHandler::FreeStream(CAsyncStream* stream) // line (MGAcceptHandler.h)
{
	return (this->*_FreeStream)(stream);

	m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
}


hook_method<int (CMGAcceptHandler::*)(SOCKET s, unsigned long ip)> CMGAcceptHandler::_OnConnect(SERVER, "CMGAcceptHandler::OnConnect");
int CMGAcceptHandler::OnConnect(SOCKET s, unsigned long ip) // line 32
{
	return (this->*_OnConnect)(s, ip);

	CAsyncStream* stream = m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
	if( stream == NULL )
		return 0;

	CMClient* client = g_mServerMgr.CMClientMgr::AllocServer();
	if( client == NULL )
	{
		m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
		return 0;
	}

	stream->CAsyncStream::Init(&client->m_packetHandler);
	client->CMClient::Init(stream);

	int SID = g_mServerMgr.CMClientMgr::AddServer(client);
	if( !stream->CAsyncStream::Open(s) )
	{
		g_mServerMgr.CMClientMgr::DeleteServer(SID);
		return 0;
	}

	return 1;
}
