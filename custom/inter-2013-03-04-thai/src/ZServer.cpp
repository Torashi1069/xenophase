#include "CMakerRankMgr.h"
#include "Enum.h"
#include "IGuildMgr.h"
#include "InterServer.h"
#include "ZServer.h"
#include "Common/Packet.h"
#include "Statistics/MAPStatisticLogMgr.h"
#include "Statistics/ZSVRStatisticLogMgr.h"
#include "shared/CMapInfoMgr.h"
#include "shared/ServerInfo.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/N2System/N2SyncObject.h"


CZServer::CZServer()
{
	m_IP = 0;
	m_LastPacketSendTM = timeGetTime();
	m_ZServerID = -1;
}


CZServer::~CZServer()
{
}


namespace {
class lcZSVRLivePing : public N3SchedulerTask<CZServer>
{
public:
	bool operator()(CZServer* in_cpZSVR)
	{
		DWORD curTime = timeGetTime();

		if( curTime > in_cpZSVR->CZServer::GetLastPacketRecvTM() + 18000 )
		{
			in_cpZSVR->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		}
		else
		if( curTime > in_cpZSVR->CZServer::GetLastPacketSendTM() + PERIODETM )
		{
			PACKET_IZ_PING_LIVE packet;
			packet.PacketType = HEADER_IZ_PING_LIVE;
			in_cpZSVR->Send(sizeof(packet), (char*)&packet);
		}

		m_Time += PERIODETM;
		return false;
	}

public:
	lcZSVRLivePing() : N3SchedulerTask<CZServer>(1, timeGetTime() + PERIODETM) { }
	virtual ~lcZSVRLivePing() { }

public:
	enum { PERIODETM = 3000 };
};
}; // namespace


void CZServer::Init(const int in_ZSID, CAsyncStream* stream)
{
	m_packetHandler.CZSPacketHandler::SetMyOwner(this);
	m_ZServerID = -1;
	m_asyncStream = stream;
	m_dwErrorCount = 0;
	m_IP = 0;
	m_nBanTime = 0;
	m_first = 1;
	m_bSendInfo = TRUE;
	m_firstTick = timeGetTime() + 1000;
	m_SendListGDID.clear();
	m_ServiceMap.clear();

	std::vector<int> MapIDList = CMapInfoMgr::GetObj()->CMapInfoMgr::GetMapIDList();
	for( std::vector<int>::iterator iter = MapIDList.begin(); iter != MapIDList.end(); ++iter )
	{
		int MapID = *iter;

		std::pair<bool,CMapInfo> ret = CMapInfoMgr::GetObj()->CMapInfoMgr::GetMapInfo(MapID);
		if( ret.first && ret.second.ZSID == in_ZSID )
			m_ServiceMap.insert(std::make_pair(ret.second.Name, 0));
	}

	m_TotalPlayerNum = 0;
	m_UsedMemoryKBytes = 0;
	m_TotalNPCNum = 0;
	m_InstantMapNum = 0;
	m_InstantMapBlockCnt = 1;
	m_RegisteredMgrFUCnt = 0;

	PACKET_XX_CONNECT packet;
	packet.PacketType = HEADER_XX_CONNECT;
	stream->CAsyncStream::GetRecvQueuePtr()->CPacketQueue::resetANDinsert(sizeof(packet), (char*)&packet);

	m_HsvrID = g_serverInfo.CServerInfo::GetDestinationSID(in_ZSID, TARGET_ONE_SID);
	m_LastPacketSendTM = timeGetTime();

	m_Scheduler.N3Scheduler<CZServer>::Init();
	m_Scheduler.N3Scheduler<CZServer>::Insert(N3Scheduler<CZServer>::TASKPTR(new(std::nothrow) lcZSVRLivePing()));
}


void CZServer::Cleanup()
{
	m_Scheduler.N3Scheduler<CZServer>::Delete(1);
	m_Scheduler.N3Scheduler<CZServer>::Init();
}


void CZServer::AddPlayer(const std::string in_mapName)
{
	SERVICEMAPCONTAINER_ITER iter = m_ServiceMap.find(in_mapName);
	if( iter == m_ServiceMap.end() )
		return;

	++iter->second;
	++m_TotalPlayerNum;
}


void CZServer::RemovePlayer(const std::string in_mapName)
{
	SERVICEMAPCONTAINER_ITER iter = m_ServiceMap.find(in_mapName);
	if( iter == m_ServiceMap.end() )
		return;

	--iter->second;
	--m_TotalPlayerNum;
}


void CZServer::Send(int len, const char* buf)
{
	this->CClient::Send(len, buf);
	m_LastPacketSendTM = timeGetTime();
}


int CZServer::OnProcess()
{
	if( IsSetting(SETTING_GUILDWAR) )
	{
		if( m_first != 0 && m_firstTick < timeGetTime() )
		{
			CIGuildMgr::GetObj()->CIGuildMgr::InitZServerGuild(m_ZServerID, &m_SendListGDID);
			m_first = 0;

			if( m_SendListGDID.size() != 0 )
				m_bSendInfo = FALSE;

			g_MakerRankMgr.CMakerRankMgr::SendZoneMakerRanking(CMakerRankMgr::TYPE_BLACKSMITH);
			g_MakerRankMgr.CMakerRankMgr::SendZoneMakerRanking(CMakerRankMgr::TYPE_ALCHEMIST);
			g_MakerRankMgr.CMakerRankMgr::SendZoneMakerRanking(CMakerRankMgr::TYPE_TAEKWON);
			g_MakerRankMgr.CMakerRankMgr::SendZoneMakerRanking(CMakerRankMgr::TYPE_KILLER);
		}

		if( !m_bSendInfo )
		{
			unsigned long GDID = m_SendListGDID.front();
			m_SendListGDID.pop_front();

			CIGuildMgr::GetObj()->CIGuildMgr::NotifyGuild(m_ZServerID, GDID);

			if( m_SendListGDID.size() == 0 )
				m_bSendInfo = TRUE;
		}
	}

	m_Scheduler.N3Scheduler<CZServer>::Process(this);

	if( m_packetHandler.OnProcess() != -1 )
		return 0;

	return -1;
}


void CZServer::AddErrorCnt(const char* in_pSourceFileName, const int in_SourceLineNum, const unsigned long in_Cnt, const unsigned long in_TM)
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(in_pSourceFileName, in_SourceLineNum, "in_Cnt(%d)", in_Cnt);
	this->CClient::AddErrorCnt(in_pSourceFileName, in_SourceLineNum, in_Cnt, in_TM);
}


void CZServer::SetZServerID(const int in_ServerID, const unsigned long in_IP)
{
	m_ZServerID = in_ServerID;
	m_IP = in_IP;
}


int CZServer::GetZServerID()
{
	return m_ZServerID;
}


void CZServer::OnMgrRegistered()
{
	m_RegisteredMgrFUCnt = ++g_FunctionUniqueCnt;
}


void CZServer::AddInstantMap(const int in_MapID, const std::string in_MapName, const int in_MapType)
{
	CMapInfo MapInfo;
	MapInfo.ZSID = m_ZServerID;
	MapInfo.type = in_MapType;
	MapInfo.MapID = in_MapID;
	MapInfo.bPlayerEnter = true;
	strncpy_s(MapInfo.Name, countof(MapInfo.Name), in_MapName.c_str(), _TRUNCATE);
	MapInfo.Name[countof(MapInfo.Name)-1] = '\0';

	CMapInfoMgr::GetObj()->CMapInfoMgr::InstantMapAdd2(MapInfo);
	m_ServiceMap.insert(std::make_pair(in_MapName, 0));
	++m_InstantMapNum;
}


void CZServer::RemoveInstantMap(const std::string in_MapName)
{
	SERVICEMAPCONTAINER_ITER iter = m_ServiceMap.find(in_MapName);
	if( iter == m_ServiceMap.end() )
		return;

	iter = m_ServiceMap.erase(iter);
	--m_InstantMapNum;
}


void CZServer::OutputZSVRStatisticLog(const time_t in_Date)
{
	CZSVRStatisticLogMgr::GetObj()->CZSVRStatisticLogMgr::Add(in_Date, m_ZServerID, m_TotalPlayerNum, m_TotalNPCNum, m_UsedMemoryKBytes, m_ServiceMap.size(), m_InstantMapNum);
}


void CZServer::OutputMAPStatisticLog(const time_t in_Date)
{
	std::map<std::string,int> mapinfo;

	for( SERVICEMAPCONTAINER_ITER iter = m_ServiceMap.begin(); iter != m_ServiceMap.end(); ++iter )
		mapinfo.insert(std::pair<std::string,int>(iter->first, iter->second));

	CMAPStatisticLogMgr::GetObj()->CMAPStatisticLogMgr::Add(in_Date, m_ZServerID, mapinfo);
}


void CZServer::SendIZResultEntryQueueApply(const unsigned long in_GID, const unsigned char in_Result, const std::string in_EntryQueueName)
{
	PACKET_IZ_RESULT_ENTRY_QUEUE_APPLY outPacket = {};
	outPacket.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_APPLY;
	outPacket.GID = in_GID;
	outPacket.Result = in_Result;
	strncpy_s(outPacket.EntryQueueName, 24, in_EntryQueueName.c_str(), _TRUNCATE);

	this->Send(sizeof(outPacket), (char*)&outPacket);
}


int CZServer::GetType()
{
	return ZSERVER_TYPE;
}


unsigned long CZServer::GetAccountID()
{
	return -1;
}


CAsyncStream* CZServer::GetAsyncStream()
{
	return m_asyncStream;
}


unsigned long CZServer::GetIP()
{
	return m_IP;
}


int CZServer::GetHsvrID()
{
	return m_HsvrID;
}


unsigned int CZServer::GetLastPacketRecvTM()
{
	return m_packetHandler.CZSPacketHandler::GetLastPacketRecvTM();
}


unsigned int CZServer::GetLastPacketSendTM()
{
	return m_LastPacketSendTM;
}


const int CZServer::GetServiceMapNum() const
{
	return (int)m_ServiceMap.size();
}


const int CZServer::GetPlayerNum() const
{
	return m_TotalPlayerNum;
}


const int CZServer::GetNPCNum() const
{
	return m_TotalNPCNum;
}


const int CZServer::GetUsedMemoryKBytes() const
{
	return m_UsedMemoryKBytes;
}


const int CZServer::GetInstantMapNum() const
{
	return m_InstantMapNum;
}


const unsigned long CZServer::GetRegisteredMgrFUCnt() const
{
	return m_RegisteredMgrFUCnt;
}


const bool CZServer::isInstantMapAllow() const
{
	return ( m_InstantMapBlockCnt == 0 );
}


const int CZServer::GetInstantMapBlockCnt() const
{
	return m_InstantMapBlockCnt;
}
