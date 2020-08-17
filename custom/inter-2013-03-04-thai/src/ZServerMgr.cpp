#include "CMakerRankMgr.h"
#include "InterServer.h"
#include "MemorialDungeonConfig.h"
#include "ZServerMgr.h"
#include "shared/CMapInfoMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NSystem/NSyncObject.h"
#include "shared/N2System/N2SyncObject.h"


CZServerMgr::CZServerMgr()
{
	m_bVerMessage = FALSE;
	m_bEpisodeMessage = FALSE;
	InitializeCriticalSection(&m_serverMap_cs);
}


CZServerMgr::~CZServerMgr()
{
	DeleteCriticalSection(&m_serverMap_cs);
}


void CZServerMgr::Init(int count)
{
	m_serverMapMemoryPool.CMemoryMgr<CZServer>::Init(count);
	g_MakerRankMgr.CMakerRankMgr::Setup();
}


void CZServerMgr::AddServer(const int in_SID, CZServer* cpZSVR, const unsigned long in_IP)
{
	EnterCriticalSection(&m_serverMap_cs);

	m_serverMap[in_SID] = cpZSVR;
	cpZSVR->CZServer::SetZServerID(in_SID, in_IP);
	cpZSVR->CZServer::OnMgrRegistered();

	LeaveCriticalSection(&m_serverMap_cs);
}


CAsyncStream* CZServerMgr::FindServer(int SID)
{
	std::map<int,CZServer*>::iterator Serveriterator = m_serverMap.find(SID);
	if( Serveriterator == m_serverMap.end() )
		return NULL;

	return Serveriterator->second->CZServer::GetAsyncStream();
}


void CZServerMgr::SendMsgToZServer(const int in_HsvrID, const int in_ZsvrID, const int in_Length, const char* in_pBuffer)
{
	NSyncObject sync(m_serverMap_cs);

	std::map<int,CZServer*>::const_iterator iter = m_serverMap.find(in_ZsvrID);
	if( iter != m_serverMap.end() && in_HsvrID == iter->second->CZServer::GetHsvrID() )
		iter->second->Send(in_Length, in_pBuffer);
}


void CZServerMgr::SendMsgToZServer(int zServerID, short len, const char* buf)
{
	EnterCriticalSection(&m_serverMap_cs);

	std::map<int,CZServer*>::iterator Serveriterator = m_serverMap.find(zServerID);
	if( Serveriterator != m_serverMap.end() )
		Serveriterator->second->Send(len, buf);

	LeaveCriticalSection(&m_serverMap_cs);
}


void CZServerMgr::BroadCast(const int in_HsvrID, const int in_Length, const char* in_pBuffer)
{
	NSyncObject sync(m_serverMap_cs);

	for( std::map<int,CZServer*>::iterator iter = m_serverMap.begin(); iter != m_serverMap.end(); ++iter )
	{
		CZServer* server = iter->second;

		if( in_HsvrID == server->CZServer::GetHsvrID() )
			server->Send(in_Length, in_pBuffer);
	}
}


void CZServerMgr::BroadCast(short len, const char* buf)
{
	EnterCriticalSection(&m_serverMap_cs);

	for( std::map<int,CZServer*>::iterator Serveriterator = m_serverMap.begin(); Serveriterator != m_serverMap.end(); ++Serveriterator )
		Serveriterator->second->Send(len, buf);

	LeaveCriticalSection(&m_serverMap_cs);
}


CZServer* CZServerMgr::AllocServer()
{
	return m_serverMapMemoryPool.CMemoryMgr<CZServer>::Alloc();
}


void CZServerMgr::FreeServer(CZServer* server)
{
	m_serverMapMemoryPool.CMemoryMgr<CZServer>::Free(server);
}


BOOL CZServerMgr::IsConnectedServer(int SID)
{
	BOOL result;
	EnterCriticalSection(&m_serverMap_cs);

	if( m_serverMap.find(SID) == m_serverMap.end() )
		result = FALSE;
	else
		result = TRUE;

	LeaveCriticalSection(&m_serverMap_cs);
	return result;
}


unsigned long CZServerMgr::GetZoneNumber()
{
	if( this == NULL )
		return 0;

	NSyncObject sync(m_serverMap_cs);

	return m_serverMap.size();
}


void CZServerMgr::OnPaintZoneServerInfo(HDC hdc, int& nY)
{
	char buf[1024] = {};

	sprintf(buf, " Zone Server Number : %d ", m_serverMap.size());
	nY += 16;
	TextOutA(hdc, 0, nY, buf, strlen(buf));

	EnterCriticalSection(&m_serverMap_cs);

	for( std::map<int,CZServer*>::iterator iter = m_serverMap.begin(); iter != m_serverMap.end(); ++iter )
	{
		iter->second->CZServer::GetZServerID();
		int ZSID = iter->second->CZServer::GetZServerID(); //FIXME: why call it twice?

		sprintf(buf, " Zone Server ID : %d ", ZSID);
		nY += 16;
		TextOutA(hdc, 0, nY, buf, strlen(buf));
	}

	LeaveCriticalSection(&m_serverMap_cs);
}


void CZServerMgr::AddInstantMapZSVR(const int in_ZSID, const int in_MapID, const std::string in_MapName, const int in_MapType)
{
	N2SyncObject sync(m_serverMap_cs);

	std::map<int,CZServer*>::iterator iter = m_serverMap.find(in_ZSID);
	if( iter == m_serverMap.end() )
		return;

	iter->second->CZServer::AddInstantMap(in_MapID, in_MapName, in_MapType);
}


void CZServerMgr::RemoveInstantMapZSVR(const int in_ZSID, const std::string in_MapName)
{
	N2SyncObject sync(m_serverMap_cs);

	CMapInfoMgr::GetObj()->CMapInfoMgr::InstantMapRemove(in_MapName);

	std::map<int,CZServer*>::iterator iter = m_serverMap.find(in_ZSID);
	if( iter == m_serverMap.end() )
		return;

	iter->second->CZServer::RemoveInstantMap(in_MapName);
}


void CZServerMgr::OutputZSvrInfo(const HDC& in_hDC, int& in_X, int& in_Y)
{
	N2SyncObject sync(m_serverMap_cs);

	char buffer[1024+1] = {};
	_snprintf(buffer, countof(buffer), "Zone Server List : %d", m_serverMap.size());

	in_Y += 16;
	TextOutA(in_hDC, in_X, in_Y, buffer, strlen(buffer));

	for( std::map<int,CZServer*>::iterator iter = m_serverMap.begin(); iter != m_serverMap.end(); ++iter )
	{
		CZServer* ZServer = iter->second;

		_snprintf(buffer, countof(buffer), "ZSID(%03d) Block(%d) Map(%d) InstantMap(%d) Player(%d) Memory(%.1fMBytes)",
			ZServer->CZServer::GetZServerID(), ZServer->CZServer::GetInstantMapBlockCnt(), ZServer->CZServer::GetServiceMapNum(),
			ZServer->CZServer::GetInstantMapNum(), ZServer->CZServer::GetPlayerNum(), ZServer->GetUsedMemoryKBytes() / 1024.);

		in_Y += 16;
		TextOutA(in_hDC, in_X, in_Y, buffer, strlen(buffer));
	}
}


int CZServerMgr::SelectInstantMapTargetZSVR(const int in_HsvrID, const int in_TargetZSID)
{
	N2SyncObject sync(m_serverMap_cs);

	if( in_TargetZSID == -1 )
	{
		int ZSID = -1;
		int minimum_factor = INT_MAX;

		for( std::map<int,CZServer*>::iterator iter = m_serverMap.begin(); iter != m_serverMap.end(); ++iter )
		{
			CZServer* ZServer = iter->second;

			if( in_HsvrID != ZServer->CZServer::GetHsvrID() )
				continue; // Not Same World.
			
			if( !ZServer->CZServer::isInstantMapAllow() )
				continue; // Refuse Create InstanceMap.

			if( ZServer->CZServer::GetUsedMemoryKBytes() > CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetMaximumZoneResourceMemory() << 10 ) //FIXME: wrong bit shift direction
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "GetUsedMemoryKBytes(%d) > MaxZoneResourceMemory(%d) [ZSID : %d]", ZServer->CZServer::GetUsedMemoryKBytes(), CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetMaximumZoneResourceMemory() << 10, in_TargetZSID); //FIXME: wrong bit shift direction
				return -1;
			}

			int load_factor = ZServer->CZServer::GetServiceMapNum()
			                + ZServer->CZServer::GetPlayerNum()
			                + ZServer->CZServer::GetNPCNum()
			                + ZServer->CZServer::GetInstantMapNum()
			                + ZServer->CZServer::GetUsedMemoryKBytes() / 2048;

			if( load_factor < minimum_factor )
			{
				minimum_factor = load_factor;
				ZSID = ZServer->CZServer::GetZServerID();
			}
		}

		return ZSID;
	}
	else
	{
		std::map<int,CZServer*>::iterator iter = m_serverMap.find(in_TargetZSID);
		if( iter == m_serverMap.end() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "No ServerMap data. [ZSID : %d]", in_TargetZSID);
			return -1;
		}

		CZServer* ZServer = iter->second;

		if( !ZServer->CZServer::isInstantMapAllow() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Refuse Create InstanceMap. [ZSID : %d]", in_TargetZSID);
			return -1;
		}

		if( in_HsvrID != ZServer->CZServer::GetHsvrID() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Not Same World. [Input HSID : %d] [Cur HSID : %d] [ZSID : %d]", in_HsvrID, ZServer->CZServer::GetHsvrID(), in_TargetZSID);
			return -1;
		}

		if( ZServer->CZServer::GetUsedMemoryKBytes() > CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetMaximumZoneResourceMemory() << 10 ) //FIXME: wrong bit shift direction
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "GetUsedMemoryKBytes : %d [ZSID : %d]", ZServer->CZServer::GetUsedMemoryKBytes(), in_TargetZSID);
			return -1;
		}


		int ZSID = iter->first; // == in_TargetZSID
		return ZSID;
	}
}


void CZServerMgr::OutputZSVRStatisticLog(const time_t in_Date)
{
	for( std::map<int,CZServer*>::iterator iter = m_serverMap.begin(); iter != m_serverMap.end(); ++iter )
		iter->second->CZServer::OutputZSVRStatisticLog(in_Date);
}


void CZServerMgr::OutputMAPStatisticLog(const time_t in_Date)
{
	for( std::map<int,CZServer*>::iterator iter = m_serverMap.begin(); iter != m_serverMap.end(); ++iter )
		iter->second->CZServer::OutputMAPStatisticLog(in_Date);
}


void CZServerMgr::AddPlayer(const int in_ZSID, const std::string in_mapName)
{
	N2SyncObject sync(m_serverMap_cs);

	std::map<int,CZServer*>::iterator iter = m_serverMap.find(in_ZSID);
	if( iter == m_serverMap.end() )
		return;

	iter->second->CZServer::AddPlayer(in_mapName);
}
