#include "InterServer.h"
#include "MemorialDungeonConfig.h"
#include "Instant Map/InstantMap.h"
#include "Instant Map/InstantMapLib.h"
#include "Instant Map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeon.h"
#include "Memorial Dungeon/MemorialDungeonDBLogMgr.h"
#include "Memorial Dungeon/MemorialDungeonFactorGenerator.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/N3System/N3MessageMgr.h"


CMemorialDungeon::CMemorialDungeon(const std::string in_Name, const std::string in_NickName, const int in_hParty, const std::string in_PartyName, const int in_TargetZSID, const int in_HsvrID)
: N3Object(), N3Inter(),
  m_InstantMapList(),
  m_MessageQueue(),
  m_Name(in_Name),
  m_NickName(in_NickName),
  m_hParty(in_hParty),
  m_PartyName(in_PartyName),
  m_Factor(CMemorialDungeonFactorGenerator::GetObj()->CN3RecycleIDGenerator::Alloc()),
  m_TargetZSID(in_TargetZSID),
  m_ZSVRregisteredFUCnt(0),
  m_EnterInstantMapName(),
//m_EnterPosX(0),
//m_EnterPosY(0),
//m_LiveTimeMinute(0),
  m_HsvrID(in_HsvrID),
  m_State(STATE_CREATE),
  m_PlayerContainer(),
  m_ScheduleContainer(),
  m_ProcessFuncPtr(&CMemorialDungeon::Process_PROCSTEP_CREATE_INSTANTMAP)
{
	m_bOK = false;

	N3MessageMgr::GetObj()->N3MessageMgr::Insert(this->N3Object::GetMyID(), this);
	if( m_Factor < 0 )
		return;

	std::pair<bool,CMemorialDungeonConfig::lcMDConfigData> MDInfo = CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetOnceMDObj(m_Name);
	if( !MDInfo.first )
		return;

	for( std::list<CMemorialDungeonConfig::lcMDConfigData::MDMapInfo>::const_iterator iter = MDInfo.second.m_MapInfoObj.begin(); iter != MDInfo.second.m_MapInfoObj.end(); ++iter )
	{
		if( !m_InstantMapList.insert(std::pair<const std::string,tagInstantMapInfo>(InstantMap::GetInstantMapName(m_Factor, iter->m_szMapName), iter->m_nMapType)).second )
			return;
	}

	m_LiveTimeMinute = MDInfo.second.m_nLiveTimeMinute;
	m_EnterInstantMapName = InstantMap::GetInstantMapName(m_Factor, MDInfo.second.m_lcEnterMapInfo.m_szMapName);
	m_EnterPosX = MDInfo.second.m_lcEnterMapInfo.m_nXpos;
	m_EnterPosY = MDInfo.second.m_lcEnterMapInfo.m_nYpos;

	N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_CREATE2), 0, 0);
	m_bOK = true;
}


CMemorialDungeon::~CMemorialDungeon()
{
	CMemorialDungeonFactorGenerator::GetObj()->CN3RecycleIDGenerator::Free(m_Factor);
	N3MessageMgr::GetObj()->N3MessageMgr::Remove(this->N3Object::GetMyID(), this);
}


void CMemorialDungeon::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.N3MessageQueue::Put(in_Msg, in_wParam, in_lParam);
}


void CMemorialDungeon::Process_PROCSTEP_OPERATION(const int in_Message, const int in_wParam, const int in_lParam)
{
	switch( in_Message )
	{
	case N3MSG(CMemorialDungeon,MSG_NONE2):
		Sleep(0);
	break;
	case N3MSG(CMemorialDungeon,MSG_DYING_WISH_REQUEST2):
		m_State = STATE_ERROR;
		m_ProcessFuncPtr = &CMemorialDungeon::Process_PROCSTEP_DYING_WISH;
		N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_DESTROY2), 0, 0);
	break;
	default:
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", in_Message);
	break;
	};
}


void CMemorialDungeon::Process_PROCSTEP_CREATE_INSTANTMAP(const int in_Message, const int in_wParam, const int in_lParam)
{
	switch( in_Message )
	{
	case N3MSG(CMemorialDungeon,MSG_NONE2):
	{
		Sleep(0);
	}
	break;
	case N3MSG(CMemorialDungeon,MSG_DYING_WISH_REQUEST2):
	{
		m_State = STATE_ERROR;
		m_ProcessFuncPtr = &CMemorialDungeon::Process_PROCSTEP_DYING_WISH;
		N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_DESTROY2), 0, 0);
	}
	break;
	case N3MSG(CMemorialDungeon,MSG_INSTANTMAP_CREATE2):
	{
		for( INSTANTMAPLISTCONTAINER_ITER iter = m_InstantMapList.begin(); iter != m_InstantMapList.end(); ++iter )
		{
			const std::string& MapName = iter->first;
			tagInstantMapInfo& MapInfo = iter->second;

			if( MapInfo.bCreateRequest != true )
			{
				std::pair<bool,std::string> ret = CInstantMapMgr::GetObj()->CInstantMapMgr::InstantMapCreate(this->N3Object::GetMyID(), m_TargetZSID, MapName, MapInfo.mapType);
				if( !ret.first )
				{
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[MD] TargetZSID(%d), MapName(%s) MapType(%d)", m_TargetZSID, MapName.c_str(), MapInfo.mapType);
					NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[MD] fail %s", ret.second.c_str());
					m_State = STATE_ERROR;
					CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::CreateResult(m_hParty, false);
					m_ProcessFuncPtr = &CMemorialDungeon::Process_PROCSTEP_DYING_WISH;
					N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_DESTROY2), 0, 0);
					return;
				}

				MapInfo.bCreateRequest = true;
				return;
			}
		};

		this->CMemorialDungeon::Schedule_Add(time(NULL) + 60 * m_LiveTimeMinute, SCHEDULE_DESTORY_LIVE_TIMEOUT);
		this->CMemorialDungeon::Schedule_Add(time(NULL) + 60 * CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetEnterLimitMinute(), SCHEDULE_DESTORY_ENTER_TIMEOUT);
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SYNC2(m_HsvrID, -1, this->N3Object::GetMyID(), m_Name, m_hParty, m_PartyName, m_TargetZSID, m_Factor, PACKET_IZ_MEMORIALDUNGEON_SYNC2::EVENT_CREATE);
		m_ZSVRregisteredFUCnt = ++g_FunctionUniqueCnt;
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::CreateResult(m_hParty, true);
		m_ProcessFuncPtr = &CMemorialDungeon::Process_PROCSTEP_OPERATION;
		m_State = STATE_OPERATION;
	}
	break;
	case N3MSG(CInstantMap,MSG_CREATE_SUCCESS2):
	{
		std::string IntantMapName = CInstantMapMgr::GetObj()->CInstantMapMgr::GetInstantMapName(in_wParam);
		INSTANTMAPLISTCONTAINER_ITER iter = m_InstantMapList.find(IntantMapName);
		if( iter == m_InstantMapList.end() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "notify programmer..");
			return;
		}

		N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_CREATE2), 0, 0);
	}
	break;
	case N3MSG(CInstantMap,MSG_CREATE_ERROR2):
	case N3MSG(CInstantMap,MSG_ERROR_FOUND2):
	{
		m_State = STATE_ERROR;
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::CreateResult(m_hParty, false);
		m_ProcessFuncPtr = &CMemorialDungeon::Process_PROCSTEP_DYING_WISH;
		N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_DESTROY2), 0, 0);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[MD] fail MSG(0x%08X) TargetZSID(%d) Name(%s)", in_Message, m_TargetZSID, m_Name.c_str());
	}
	break;
	default:
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%X)", in_Message);
	}
	break;
	};
}


void CMemorialDungeon::Process_PROCSTEP_DYING_WISH(const int in_Message, const int in_wParam, const int in_lParam)
{
	switch( in_Message )
	{
	case N3MSG(CMemorialDungeon,MSG_NONE2):
	{
		Sleep(0);
	}
	break;
	case N3MSG(CMemorialDungeon,MSG_INSTANTMAP_DESTROY2):
	{
		
		for( INSTANTMAPLISTCONTAINER_ITER iter = m_InstantMapList.begin(); iter != m_InstantMapList.end(); ++iter )
		{
			const std::string& MapName = iter->first;
			tagInstantMapInfo& MapInfo = iter->second;

			if( MapInfo.bCreateRequest )
			{
				CInstantMapMgr::GetObj()->CInstantMapMgr::InstantMapDestory(this->N3Object::GetMyID(), MapName);
				MapInfo.bCreateRequest = false;
			}
		}

		m_State = STATE_DESTROY_READY;

		if( m_ZSVRregisteredFUCnt != 0 )
			MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SYNC2(m_HsvrID, -1, this->N3Object::GetMyID(), m_Name, m_hParty, m_PartyName, m_TargetZSID, m_Factor, PACKET_IZ_MEMORIALDUNGEON_SYNC2::EVENT_DESTROY);
	}
	break;
	case N3MSG(CInstantMap,MSG_CREATE_SUCCESS2):
	{
	}
	break;
	case N3MSG(CInstantMap,MSG_ERROR_FOUND2):
	{
	}
	break;
	default:
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "unknown message receive(Msg:0x%08X)", in_Message);
	}
	break;
	};
}


void CMemorialDungeon::Process()
{
	N3MessageQueue::RETGET ret = m_MessageQueue.N3MessageQueue::Get();
	if( std::tr1::get<0>(ret) == true )
		(this->*m_ProcessFuncPtr)(std::tr1::get<1>(ret), std::tr1::get<2>(ret), std::tr1::get<3>(ret));

	this->CMemorialDungeon::Schedule_Process();
}


void CMemorialDungeon::Schedule_Process()
{
	if( !this->CMemorialDungeon::isActive() )
		return;

	unsigned long CurDate = time(NULL);

	for( SCHEDULE_CONTAINER_ITER iter = m_ScheduleContainer.begin(); iter != m_ScheduleContainer.end(); iter = m_ScheduleContainer.erase(iter) )
	{
		const unsigned long Date = iter->first;
		const enumSCHEDULE Job = iter->second;

		if( Date > CurDate )
			break; // done for now.

		if( Job == SCHEDULE_DESTORY_LIVE_TIMEOUT )
		{
			CMemorialDungeonDBLogMgr::GetObj()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_DESTROY_BY_LIVETIME, this->CMemorialDungeon::GetName(), this->CMemorialDungeon::GetPartyName(), m_hParty, m_TargetZSID);
			MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(m_HsvrID, m_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::TYPE_DESTROY_LIVE_TIMEOUT, 0);

			m_State = STATE_ERROR;
			m_ProcessFuncPtr = &CMemorialDungeon::Process_PROCSTEP_DYING_WISH;
			N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_DESTROY2), 0, 0);
		}
		else
		if( Job == SCHEDULE_DESTORY_ENTER_TIMEOUT )
		{
			CMemorialDungeonDBLogMgr::GetObj()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_DESTROY_BY_ENTERTIME, this->CMemorialDungeon::GetName(), this->CMemorialDungeon::GetPartyName(), m_hParty, m_TargetZSID);
			MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(m_HsvrID, m_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::TYPE_DESTROY_ENTER_TIMEOUT, 0);

			m_State = STATE_ERROR;
			m_ProcessFuncPtr = &CMemorialDungeon::Process_PROCSTEP_DYING_WISH;
			N3MessageMgr::GetObj()->N3MessageMgr::Post(this->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_INSTANTMAP_DESTROY2), 0, 0);
		}
	}
}


void CMemorialDungeon::Schedule_Add(const unsigned long in_Date, const enumSCHEDULE in_Job)
{
	m_ScheduleContainer.insert(std::pair<const unsigned long,enumSCHEDULE>(in_Date, in_Job));
}


unsigned long CMemorialDungeon::Schedule_GetDate(const enumSCHEDULE in_Job)
{
    
    for( SCHEDULE_CONTAINER_ITER iter = m_ScheduleContainer.begin(); iter != m_ScheduleContainer.end(); ++iter )
        if( in_Job == iter->second )
            return iter->first; // found.

    return 0; // not found.
}


void CMemorialDungeon::OnEnter(const unsigned long in_GID, const unsigned long in_AID)
{
	m_PlayerContainer.insert(std::pair<const unsigned long,CPlayer>(in_GID, CPlayer(in_AID, in_GID)));

	for( SCHEDULE_CONTAINER_ITER iter = m_ScheduleContainer.begin(); iter != m_ScheduleContainer.end(); )
	{
		if( iter->second == SCHEDULE_DESTORY_ENTER_TIMEOUT )
		{
			iter = m_ScheduleContainer.erase(iter);
			MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(m_HsvrID, m_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::TYPE_NOTIFY, 0);
		}
		else
		{
			++iter;
		}
	}
}


void CMemorialDungeon::OnLeave(const unsigned long in_GID, const unsigned long in_AID)
{
	PLAYERCONTAINER_ITER iter = m_PlayerContainer.find(in_GID);
	if( iter != m_PlayerContainer.end() )
		iter = m_PlayerContainer.erase(iter);

	if( m_PlayerContainer.size() == 0 )
	{
		unsigned long LimitDate = time(NULL) + 60 * CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetEnterLimitMinute();
		this->CMemorialDungeon::Schedule_Add(LimitDate, SCHEDULE_DESTORY_ENTER_TIMEOUT);
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(m_HsvrID, m_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::TYPE_NOTIFY, LimitDate);
	}
}


void CMemorialDungeon::PartyLeave(const unsigned long in_AID, const unsigned long in_GID)
{
	PLAYERCONTAINER_ITER iter = m_PlayerContainer.find(in_AID);
	if( iter == m_PlayerContainer.end() )
		return;

	MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_COMMAND(m_HsvrID, iter->second.m_AID, iter->second.m_GID, PACKET_IZ_MEMORIALDUNGEON_COMMAND::COMMAND_PLAYER_KICK);
}
