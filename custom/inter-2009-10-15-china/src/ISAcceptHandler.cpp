#include "ISAcceptHandler.h"
#include "MServerMgr.h"
#include "ServerInfo.h"
#include "ZServerMgr.h"
#include "globals.hpp"


CISAcceptHandler::CISAcceptHandler(void) // line 19
{
}


CISAcceptHandler::~CISAcceptHandler(void) // line 23
{
}


hook_method<int (CISAcceptHandler::*)(int streamPoolSize)> CISAcceptHandler::_Init(SERVER, "CISAcceptHandler::Init");
int CISAcceptHandler::Init(int streamPoolSize) // line 28
{
	return (this->*_Init)(streamPoolSize);

	if( g_isExtendDB )
		g_serverInfo.CServerInfo::GetZoneServerIPPrivate(m_set);
	else
		g_serverInfo.CServerInfo::GetZoneServerIP(m_set);

	return m_streamPool.CMemoryMgr<CAsyncStream>::Init(streamPoolSize);
}


hook_method<CAsyncStream* (CISAcceptHandler::*)(void)> CISAcceptHandler::_AllocStream(SERVER, "CISAcceptHandler::AllocStream");
CAsyncStream* CISAcceptHandler::AllocStream(void) // line 25 (ISAcceptHandler.h)
{
	return (this->*_AllocStream)();

	return m_streamPool.CMemoryMgr<CAsyncStream>::Alloc();
}


hook_method<void (CISAcceptHandler::*)(CAsyncStream* stream)> CISAcceptHandler::_FreeStream(SERVER, "CISAcceptHandler::FreeStream");
void CISAcceptHandler::FreeStream(CAsyncStream* stream) // line 26 (ISAcceptHandler.h)
{
	return (this->*_FreeStream)(stream);

	m_streamPool.CMemoryMgr<CAsyncStream>::Free(stream);
}


hook_method<int (CISAcceptHandler::*)(SOCKET s, unsigned long ip)> CISAcceptHandler::_OnConnect(SERVER, "CISAcceptHandler::OnConnect");
int CISAcceptHandler::OnConnect(SOCKET s, unsigned long ip) // line 39
{
	return (this->*_OnConnect)(s, ip);

	if( m_set.find(ip) == m_set.end() )
	{// MServer
		if( g_isExtendDB )
			return 0;

		CAsyncStream* stream = this->CISAcceptHandler::AllocStream();
		if( stream == NULL )
			return 0;

		CMClient* server = g_mServerMgr.CMClientMgr::AllocServer();
		if( server == NULL )
		{
			this->CISAcceptHandler::FreeStream(stream);
			return 0;
		}

		stream->CAsyncStream::Init(&server->m_packetHandler);
		server->CMClient::Init(stream);

		int SID = g_mServerMgr.CMClientMgr::AddServer(server);
		if( !stream->CAsyncStream::Open(s) )
		{
			g_mServerMgr.CMClientMgr::DeleteServer(SID);
			return 0;
		}
	}
	else
	{// ZServer
		int SID = ( g_isExtendDB ) ? g_serverInfo.CServerInfo::GetServerIDPrivate(ip, 3) : g_serverInfo.CServerInfo::GetServerID(ip, 3);
		if( SID == -1 )
			return 0;

		if( g_zServerMgr.CZServerMgr::FindServer(SID) )
		{
			g_zServerMgr.CZServerMgr::DeleteServer(SID);
			Trace("Delete zombie and new zone connected:%d\n", SID);
		}

		CAsyncStream* stream = this->CISAcceptHandler::AllocStream();
		if( stream == NULL )
			return 0;

		stream->CAsyncStream::SetSendQueueSize(8000*1024);
		stream->CAsyncStream::SetRecvQueueSize(8000*1024);

		CZServer* server = g_zServerMgr.CZServerMgr::AllocServer();
		if( server == NULL )
		{
			this->CISAcceptHandler::FreeStream(stream);
			return 0;
		}

		stream->CAsyncStream::Init(&server->m_packetHandler);
		server->CZServer::Init(SID, stream);
		g_zServerMgr.CZServerMgr::AddServer(SID, server);

		if( !stream->CAsyncStream::Open(s) )
		{
			g_zServerMgr.CZServerMgr::DeleteServer(SID);
			return 0;
		}
	}

	return 1;
}
