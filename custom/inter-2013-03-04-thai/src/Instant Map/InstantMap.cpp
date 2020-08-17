#include "InterServer.h" // g_FunctionUniqueCnt
#include "Common/Packet.h"
#include "Zsvr/CZsvrMgr.h"
#include "Instant Map/InstantMap.h"
#include "Instant Map/InstantMapConfiguration.h"
#include "Instant Map/InstantMapIDGenerator.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/N3System/N3MessageMgr.h"


namespace InstantMap
{


void SendPacket_IZ_INSTNATMAP_DESTROY_temp(const int in_TargetZSID, const int in_MapID, std::string in_Name)
{
	PACKET_IZ_INSTNATMAP_DESTROY packet = {};
	packet.PacketType = HEADER_IZ_INSTNATMAP_DESTROY;
	strncpy(packet.mapName, in_Name.c_str(), countof(packet.mapName));
	packet.mapName[countof(packet.mapName)-1] = '\0';
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(in_TargetZSID, sizeof(packet), (char*)&packet);
}


void SendPacket_IZ_INSTANTMAP_ADD3(const int in_TargetZSID, const int in_ZSID, const int in_MapID, const int in_MapType, std::string in_Name, const bool in_bPlayerEnter)
{
	PACKET_IZ_INSTANTMAP_ADD3 packet = {};
    packet.PacketType = HEADER_IZ_INSTANTMAP_ADD3;
    packet.ZSID = in_ZSID;
    packet.mapID = in_MapID;
    packet.mapType = in_MapType;
    packet.bPlayerEnter = in_bPlayerEnter;
    strncpy_s(packet.mapName, countof(packet.mapName), in_Name.c_str(), _TRUNCATE);
    packet.mapName[countof(packet.mapName)-1] = '\0';
    CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(in_TargetZSID, sizeof(packet), (char*)&packet);
}


void BroadCastPacket_IZ_INSTANTMAP_ADD3(const int in_ZSID, const int in_MapID, const int in_MapType, std::string in_Name, const bool in_bPlayerEnter)
{
	PACKET_IZ_INSTANTMAP_ADD3 packet = {};
	packet.PacketType = HEADER_IZ_INSTANTMAP_ADD3;
	packet.ZSID = in_ZSID;
	packet.mapID = in_MapID;
	packet.mapType = in_MapType;
	packet.bPlayerEnter = in_bPlayerEnter;
	strncpy_s(packet.mapName, countof(packet.mapName), in_Name.c_str(), _TRUNCATE);
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(packet), (char*)&packet);
}


void BroadCastPacket_IZ_INSTANTMAP_PLAYER_ENTER3(const int in_MapID, const bool in_bPlayerEnter)
{
	PACKET_IZ_INSTANTMAP_PLAYER_ENTER3 packet = {};
    packet.PacketType = HEADER_IZ_INSTANTMAP_PLAYER_ENTER3;
    packet.mapID = in_MapID;
    packet.bPlayerEnter = in_bPlayerEnter;
    CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(packet), (char*)&packet);
}


void BroadCastPacket_IZ_INSTANTMAP_REMOVE3(const int in_ZSID, const int in_MapID, std::string in_Name)
{
	PACKET_IZ_INSTANTMAP_REMOVE3 packet = {};
	packet.PacketType = HEADER_IZ_INSTANTMAP_REMOVE3;
	packet.ZSID = in_ZSID;
	packet.mapID = in_MapID;
	strncpy_s(packet.mapName, countof(packet.mapName), in_Name.c_str(), _TRUNCATE);
	packet.mapName[countof(packet.mapName)-1] = '\0';
	CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(packet), (char*)&packet);
}


void SendPacket_IZ_INSTANTMAP_CREATE_REQ(const int in_TargetZSID, const unsigned int in_hRequestN2Obj, std::string in_MapName, const int in_MapID, const int in_MapType)
{
	PACKET_IZ_INSTANTMAP_CREATE_REQ packet = {};
    packet.PacketType = HEADER_IZ_INSTANTMAP_CREATE_REQ;
    packet.hRequestN2Obj = in_hRequestN2Obj;
    strncpy(packet.mapName, in_MapName.c_str(), countof(packet.mapName));
    packet.mapName[15] = '\0';
    CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(in_TargetZSID, sizeof(packet), (char*)&packet);
}


}; // namespace


CInstantMap::CInstantMap(const unsigned int in_RequestCreateInter, const int in_ZSID, const std::string in_Name, const int in_mapType)
: N3Object(), N3Inter(),
  m_ZSID(in_ZSID),
  m_MapType(in_mapType),
  m_Name(in_Name),
  m_MapID(0),
  m_RequestCreateInter(in_RequestCreateInter),
  m_ZSVRregisteredFUCnt(0),
  m_MessageQueue(),
  m_State(STATE_CREATE),
  m_ScheduleContainer(),
  m_ProcessFuncPtr(&CInstantMap::Process_PROCSTEP_TARGETZSVR_CREATE)
{
	m_bOK = false;

	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	m_MapID = CInstantMapIDGenerator::GetObj()->CN3RecycleIDGenerator::Alloc();
	if( m_MapID > 0 )
	{
		N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CInstantMap,MSG_TARGETZSVR_CREATE_REQUEST2), 0, 0);
		m_bOK = true;
	}
}


CInstantMap::~CInstantMap()
{
	if( m_MapID > 0 )
	{
		CInstantMapIDGenerator::GetObj()->CN3RecycleIDGenerator::Free(m_MapID);
		m_MapID = 0;
	}

	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


void CInstantMap::Process_PROCSTEP_TARGETZSVR_CREATE(const int in_Message, const int in_wParam, const int in_lParam)
{
	switch( in_Message )
	{
	case N3MSG(CInstantMap,MSG_NONE2):
	{
		Sleep(0);
	}
	break;
	case N3MSG(CInstantMap,MSG_TARGETZSVR_CREATE_REQUEST2):
	{
		InstantMap::SendPacket_IZ_INSTANTMAP_CREATE_REQ(m_ZSID, this->N3Object::GetMyID(), m_Name, m_MapID, m_MapType);
		this->CInstantMap::Schedule_Add(time(NULL) + CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::GetCreateResponseWaitSecond_fromZSVR(), SCHEDULE_CREATERES_WAITTIME_fromZSVR);
	}
	break;
	case N3MSG(CInstantMap,MSG_TARGETZSVR_CREATE_RESPONSE2):
	{
		InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE* response = reinterpret_cast<InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE*>(in_wParam);

		if( m_MapID == response->m_mapID && m_Name == response->m_mapName )
		{
			this->CInstantMap::Schedule_Remove(SCHEDULE_CREATERES_WAITTIME_fromZSVR);
			if( response->m_bSuccess == true )
			{
				CZsvrMgr::GetObj()->CZServerMgr::AddInstantMapZSVR(m_ZSID, m_MapID, m_Name, m_MapType);
				m_ZSVRregisteredFUCnt = ++g_FunctionUniqueCnt;
				InstantMap::BroadCastPacket_IZ_INSTANTMAP_ADD3(m_ZSID, m_MapID, m_MapType, m_Name, true);
				InstantMap::BroadCastPacket_IZ_INSTANTMAP_PLAYER_ENTER3(m_MapID, true);
				N3MessageMgr::GetObj()->N3MessageMgr::Post(m_RequestCreateInter, N3MSG(CInstantMap,MSG_CREATE_SUCCESS2), this->N3Object::GetMyID(), 0);
				m_ProcessFuncPtr = &CInstantMap::Process_PROCSTEP_OPERATION;
				m_State = STATE_OPERATION;
			}
			else
			{
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "존서버(%d)가 인스맵생성을 실패했다.", m_ZSID);
				m_State = STATE_ERROR;
				N3MessageMgr::GetObj()->N3MessageMgr::Post(m_RequestCreateInter, N3MSG(CInstantMap,MSG_CREATE_ERROR2), 0, 0);
			}
		}

		delete response;
	}
	break;
	case N3MSG(CInstantMap,MSG_DYING_WISH_REQUEST2):
	{
		InstantMap::BroadCastPacket_IZ_INSTANTMAP_PLAYER_ENTER3(m_MapID, false);
		InstantMap::BroadCastPacket_IZ_INSTANTMAP_REMOVE3(m_ZSID, m_MapID, m_Name);
		InstantMap::SendPacket_IZ_INSTNATMAP_DESTROY_temp(m_ZSID, m_MapID, m_Name);
		m_State = STATE_DESTORY_READY;
	}
	break;
	default:
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", in_Message);
	}
	break;
	};
}


void CInstantMap::Process_PROCSTEP_OPERATION(const int in_Message, const int in_wParam, const int in_lParam)
{
	switch( in_Message )
	{
	case N3MSG(CInstantMap,MSG_NONE2):
	{
		Sleep(0);
	}
	break;
	case N3MSG(CInstantMap,MSG_ERROR_FOUND_FROMZSVR2):
	{
		m_State = STATE_ERROR;
		N3MessageMgr::GetObj()->N3MessageMgr::Post(m_RequestCreateInter, N3MSG(CInstantMap,MSG_ERROR_FOUND2), 0, 0);
	}
	break;
	case N3MSG(CInstantMap,MSG_DYING_WISH_REQUEST2):
	{
		InstantMap::BroadCastPacket_IZ_INSTANTMAP_PLAYER_ENTER3(m_MapID, false);
		InstantMap::BroadCastPacket_IZ_INSTANTMAP_REMOVE3(m_ZSID, m_MapID, m_Name);
		m_State = STATE_DESTROY_WAIT;
		this->CInstantMap::Schedule_Add(time(NULL) + CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::GetDestroyWiatSecond(), SCHEDULE_DESTORY);
	}
	break;
	default:
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", in_Message);
	}
	break;
	};
}


void CInstantMap::Process()
{
	N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
	if( std::tr1::get<0>(ret) == true )
		(this->*m_ProcessFuncPtr)(std::tr1::get<1>(ret), std::tr1::get<2>(ret), std::tr1::get<3>(ret));

	this->CInstantMap::Schedule_Process();
}


void CInstantMap::Schedule_Process()
{
	unsigned long CurDate = time(NULL);

	for( SCHEDULE_CONTAINER_ITER iter = m_ScheduleContainer.begin(); iter != m_ScheduleContainer.end(); iter = m_ScheduleContainer.erase(iter) )
	{
		const unsigned long Date = iter->first;
		const enumSCHEDULE Job = iter->second;

		if( Date > CurDate )
			break; // done for now.

		if( Job == SCHEDULE_DESTORY )
		{
			InstantMap::SendPacket_IZ_INSTNATMAP_DESTROY_temp(m_ZSID, m_MapID, m_Name);
			CZsvrMgr::GetObj()->CZServerMgr::RemoveInstantMapZSVR(m_ZSID, m_Name);
			m_State = STATE_DESTORY_READY;
		}
		else
		if( Job == SCHEDULE_CREATERES_WAITTIME_fromZSVR )
		{
			m_State = STATE_ERROR; // request timed out
			N3MessageMgr::GetObj()->N3MessageMgr::Post(m_RequestCreateInter, N3MSG(CInstantMap,MSG_CREATE_ERROR2), 0, 0);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "존서버가 인스맵생성에 관한 응답을 시간내에 주지 않았다.");
		}
	}
}


void CInstantMap::Schedule_Add(const unsigned long in_Date, const enumSCHEDULE in_Job)
{
	m_ScheduleContainer.insert(std::pair<const unsigned long,enumSCHEDULE>(in_Date, in_Job));
}


void CInstantMap::Schedule_Remove(const enumSCHEDULE in_Job)
{
	for( SCHEDULE_CONTAINER_ITER iter = m_ScheduleContainer.begin(); iter != m_ScheduleContainer.end(); )
	{
		if( iter->second == in_Job )
			iter = m_ScheduleContainer.erase(iter);
		else
			++iter;
	}
}


void CInstantMap::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}
