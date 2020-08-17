#include "CMakerRankMgr.h"
#include "ISAcceptHandler.h"
#include "ZServerMgr.h"
#include "N2System/N2SyncObject.h"
#include "globals.hpp"


CZServerMgr::CZServerMgr(void) // line 15
{
	m_bVerMessage = 0;
	m_bEpisodeMessage = 0;
}


CZServerMgr::~CZServerMgr(void) // line 21
{
	DeleteCriticalSection(&m_serverMap_cs);
}


hook_method<void (CZServerMgr::*)(int count)> CZServerMgr::_Init(SERVER, "CZServerMgr::Init");
void CZServerMgr::Init(int count) // line 26
{
	return (this->*_Init)(count);

	InitializeCriticalSection(&m_serverMap_cs);
	m_serverMapMemoryPool.CMemoryMgr<CZServer>::Init(count);
	g_MakerRankMgr.CMakerRankMgr::Setup();
}


hook_method<void (CZServerMgr::*)(void)> CZServerMgr::_ProcessAllCharacter(SERVER, "CZServerMgr::ProcessAllCharacter");
void CZServerMgr::ProcessAllCharacter(void) // line 103
{
	return (this->*_ProcessAllCharacter)();

	//TODO
}


hook_method<void (CZServerMgr::*)(int zServerID, short len, const char* buf)> CZServerMgr::_SendMsgToZServer(SERVER, "CZServerMgr::SendMsgToZServer");
void CZServerMgr::SendMsgToZServer(int zServerID, short len, const char* buf) // line 78
{
	return (this->*_SendMsgToZServer)(zServerID, len, buf);

	//TODO
}


hook_method<void (CZServerMgr::*)(short len, const char* buf)> CZServerMgr::_BroadCast(SERVER, "CZServerMgr::BroadCast");
void CZServerMgr::BroadCast(short len, const char* buf) // line 92
{
	return (this->*_BroadCast)(len, buf);

	//TODO
}


hook_method<void (CZServerMgr::*)(int SID, CZServer* zServer)> CZServerMgr::_AddServer(SERVER, "CZServerMgr::AddServer");
void CZServerMgr::AddServer(int SID, CZServer* zServer) // line 36
{
	return (this->*_AddServer)(SID, zServer);

	Trace("SID:%d\n", SID);
	EnterCriticalSection(&m_serverMap_cs);

	m_serverMap[SID] = zServer;
	zServer->CZServer::SetZServerID(SID);
	zServer->CZServer::OnMgrRegistered();

	LeaveCriticalSection(&m_serverMap_cs);
}


hook_method<void (CZServerMgr::*)(int SID)> CZServerMgr::_DeleteServer(SERVER, "CZServerMgr::DeleteServer");
void CZServerMgr::DeleteServer(int SID) // line 51
{
	return (this->*_DeleteServer)(SID);

	EnterCriticalSection(&m_serverMap_cs);

	mystd::map<int,CZServer*>::iterator it = m_serverMap.find(SID);
	if( it != m_serverMap.end() )
	{
		CZServer* server = it->second;

		server->CZServer::GetAsyncStream()->CAsyncStream::Close();
		_g_isAcceptHandler.CISAcceptHandler::FreeStream(server->CZServer::GetAsyncStream());
		this->CZServerMgr::FreeServer(server);

		Trace("Delete Server:%d\n", SID);
		m_serverMap.erase(it);
	}

	LeaveCriticalSection(&m_serverMap_cs);
}


hook_method<CZServer* (CZServerMgr::*)(void)> CZServerMgr::_AllocServer(SERVER, "CZServerMgr::AllocServer");
CZServer* CZServerMgr::AllocServer(void) // line 134
{
	return (this->*_AllocServer)();

	return m_serverMapMemoryPool.CMemoryMgr<CZServer>::Alloc();
}


hook_method<CAsyncStream* (CZServerMgr::*)(int SID)> CZServerMgr::_FindServer(SERVER, "CZServerMgr::FindServer");
CAsyncStream* CZServerMgr::FindServer(int SID) // line 66
{
	return (this->*_FindServer)(SID);

	mystd::map<int,CZServer*>::iterator it = m_serverMap.find(SID);
	return ( it != m_serverMap.end() ) ? it->second->CZServer::GetAsyncStream() : NULL;
}


hook_method<void (CZServerMgr::*)(HDC hdc, int& nY)> CZServerMgr::_OnPaintZoneServerInfo(SERVER, "CZServerMgr::OnPaintZoneServerInfo");
void CZServerMgr::OnPaintZoneServerInfo(HDC hdc, int& nY) // line 163
{
	return (this->*_OnPaintZoneServerInfo)(hdc, nY);

	//TODO
}


hook_method<void (CZServerMgr::*)(const HDC& in_hDC, int& in_X, int& in_Y)> CZServerMgr::_OutputZSvrInfo(SERVER, "CZServerMgr::OutputZSvrInfo");
void CZServerMgr::OutputZSvrInfo(const HDC& in_hDC, int& in_X, int& in_Y) // line 223
{
	return (this->*_OutputZSvrInfo)(in_hDC, in_X, in_Y);

	N2SyncObject sync(m_serverMap_cs);

	char buffer[1025];
	memset(buffer, 0, sizeof(buffer));

	_snprintf(buffer, 1024, "Zone Server List : %d", m_serverMap.size());
	in_Y += 16;
	TextOutA(in_hDC, in_X, in_Y, buffer, sizeof(buffer));

	for( mystd::map<int,CZServer*>::const_iterator it = m_serverMap.begin(); it != m_serverMap.end(); ++it )
	{
		CZServer* server = it->second;

		_snprintf(buffer, 1024, "ZSID(%03d) Block(%d) Map(%d) InstantMap(%d) Player(%d) Memory(%.1fMBytes)", server->CZServer::GetZServerID(), server->CZServer::GetInstantMapBlockCnt(), server->CZServer::GetServiceMapNum(), server->CZServer::GetInstantMapNum(), server->CZServer::GetPlayerNum(), server->CZServer::GetUsedMemoryKBytes() / 1024.);
		in_Y += 16;
		TextOutA(in_hDC, in_X, in_Y, buffer, strlen(buffer));
	}
}


hook_method<void (CZServerMgr::*)(const time_t in_Date)> CZServerMgr::_OutputZSVRStatisticLog(SERVER, "CZServerMgr::OutputZSVRStatisticLog");
void CZServerMgr::OutputZSVRStatisticLog(const time_t in_Date) // line 301
{
	return (this->*_OutputZSVRStatisticLog)(in_Date);

	//TODO
}


hook_method<void (CZServerMgr::*)(const time_t in_Date)> CZServerMgr::_OutputMAPStatisticLog(SERVER, "CZServerMgr::OutputMAPStatisticLog");
void CZServerMgr::OutputMAPStatisticLog(const time_t in_Date) // line 311
{
	return (this->*_OutputMAPStatisticLog)(in_Date);

	//TODO
}


hook_method<void (CZServerMgr::*)(CZServer* server)> CZServerMgr::_FreeServer(SERVER, "CZServerMgr::FreeServer");
void CZServerMgr::FreeServer(CZServer* server) // line 139
{
	return (this->*_FreeServer)(server);

	m_serverMapMemoryPool.CMemoryMgr<CZServer>::Free(server);
}
