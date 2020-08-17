#include "InterServer.h" // g_serverInfo, g_groupMgr, g_userMgr
#include "PartyMgr.h"
#include "UserMgr.h"
#include "MemorialDungeonConfig.h"
#include "Instant Map/InstantMapLib.h"
#include "Memorial Dungeon/MemorialDungeonConfiguration.h"
#include "Memorial Dungeon/MemorialDungeonDBLogMgr.h"
#include "Memorial Dungeon/MemorialDungeonFactorGenerator.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/CMapInfoMgr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NMemoryHelper.h"
#include "shared/ServerInfo.h"
#include "shared/N2System/N2IDAllocator.h"
#include "shared/N2System/N2Object.h"
#include "shared/N3System/N3MessageMgr.h"


/// singleton instance
CMemorialDungeonMgr*& CMemorialDungeonMgr::m_cpSelf = VTOR<CMemorialDungeonMgr*>(DetourFindFunction(EXEPATH(), "CMemorialDungeonMgr::m_cpSelf"));


CMemorialDungeonMgr::CMemorialDungeonMgr()
: m_bOpen(true), m_Previous_Create_RequestTM(timeGetTime()), m_MemorialDungeonContainer2(), m_SubscriptionPlayerContainer()
{
	m_bOK = false;

	if( this->CMemorialDungeonMgr::Create() )
		m_bOK = true;
}


CMemorialDungeonMgr::~CMemorialDungeonMgr()
{
	this->CMemorialDungeonMgr::Destroy();
}


void CMemorialDungeonMgr::NotifySubscriptionPriority()
{
	int PriorityNum = 1;
	DWORD NotifyAccumulateTM = 10000;
	DWORD CurTM = timeGetTime();

	for( SUBSCRIPTION_PLAYER_CONTAINER_ITER iter = m_SubscriptionPlayerContainer.begin(); iter != m_SubscriptionPlayerContainer.end(); ++iter, ++PriorityNum )
	{
		CMemorialDungeonReservedPlayer& Player = iter.GetObj();
		Player.m_PriorityNum = PriorityNum;

		if( PriorityNum <= 10 )
		{
			Player.m_PriorityNumNotifyTM = CurTM;
			MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(Player.m_HsvrID, Player.m_hParty, PriorityNum);
		}
		else
		{
			if( CurTM - Player.m_PriorityNumNotifyTM > NotifyAccumulateTM )
			{
				Player.m_PriorityNumNotifyTM = CurTM;
				MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(Player.m_HsvrID, Player.m_hParty, PriorityNum);
			}

			NotifyAccumulateTM += 2000;
		}
	}
}


void CMemorialDungeonMgr::Process() // 78-207
{
	for( MEMORIALDUNGEON_CONTAINER_ITER2 iter = m_MemorialDungeonContainer2.begin(); iter != m_MemorialDungeonContainer2.end(); )
	{
		CMemorialDungeon* Dungeon = iter.GetObj();

		if( Dungeon->CMemorialDungeon::IsDestroyReady() )
		{
			delete Dungeon;
			iter = m_MemorialDungeonContainer2.erase(iter);
		}
		else
		{
			Dungeon->CMemorialDungeon::Process();
			++iter;
		}
	}

	SUBSCRIPTION_PLAYER_CONTAINER_ITER SubscriptionPlayerIter = m_SubscriptionPlayerContainer.begin();
	if( SubscriptionPlayerIter == m_SubscriptionPlayerContainer.end() )
		return;

	CMemorialDungeonReservedPlayer& Player = SubscriptionPlayerIter.GetObj();
	DWORD curTime = timeGetTime();

	if( Player.m_bCreateDoing )
	{
		if( curTime - m_Previous_Create_RequestTM > 600000 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "메모리얼던젼이 10분동안 idle상태 입니다.");
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "메모리얼던젼명:%s 파티명:%s", Player.m_Name.c_str(), Player.m_PartyName.c_str());

			MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(Player.m_hParty);
			if( mIter != m_MemorialDungeonContainer2.end() )
			{
				CMemorialDungeon* Dungeon = mIter.GetObj();
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "상태(%d) 타겟ZsvrID(%d)", Dungeon->CMemorialDungeon::GetState(), Dungeon->CMemorialDungeon::GetTargetZSID());
				N3MessageMgr::GetObj()->N3MessageMgr::Post(Dungeon->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_DYING_WISH_REQUEST2), 0, 0);
			}

			m_SubscriptionPlayerContainer.erase(SubscriptionPlayerIter);
			this->CMemorialDungeonMgr::NotifySubscriptionPriority();
		}
	}
	else
	{
		if( 1000 * CMemorialDungeonConfig::GetObj()->GetSubscriptionMinimumDelaySecond() + Player.m_RequestTM <= curTime && m_Previous_Create_RequestTM + 1000 <= curTime )
		{
			m_Previous_Create_RequestTM = curTime;

			if( m_bOpen == false )
			{
				MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(Player.m_HsvrID, Player.m_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE, Player.m_Name);
				MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(Player.m_HsvrID, Player.m_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::TYPE_CREATE_FAIL, 0);
				m_SubscriptionPlayerContainer.erase(SubscriptionPlayerIter);
				this->CMemorialDungeonMgr::NotifySubscriptionPriority();
				return;
			}

			int ret = this->CMemorialDungeonMgr::CreateMemorialDungeonR2(Player);
			if( ret == 1 )
			{
				Player.m_bCreateDoing = true;
			}
			else
			if( ret != 0 )
			{
				MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(Player.m_HsvrID, Player.m_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_CREATE_FAIL, Player.m_Name);
				MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(Player.m_HsvrID, Player.m_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::TYPE_CREATE_FAIL, 0);
				m_SubscriptionPlayerContainer.erase(SubscriptionPlayerIter);
				this->CMemorialDungeonMgr::NotifySubscriptionPriority();
				return;
			}
		}
	}
}


bool CMemorialDungeonMgr::Create()
{
	if( !N2IDAllocator::GetObj()->N2IDAllocator::RegisterGroup(N2ObjectGroupID::CMemorialDungeon, 1, 999) )
		return false;

	if( !CMemorialDungeonConfiguration::CreateInstance()
	 || !CMemorialDungeonFactorGenerator::CreateInstance()
	 || !CMemorialDungeonDBLogMgr::CreateInstance()
	 || !CMemorialDungeonConfig::CreateInstance() )
		 return false;

	if( !CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::Init() )
		return false;

	m_bOpen = CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::isOpen();
	return true;
}


void CMemorialDungeonMgr::Destroy()
{
	for( MEMORIALDUNGEON_CONTAINER_ITER2 iter = m_MemorialDungeonContainer2.begin(); iter != m_MemorialDungeonContainer2.end(); ++iter )
		delete iter.GetObj();

	m_MemorialDungeonContainer2.clear();

	CMemorialDungeonConfiguration::DestroyInstance();
	CMemorialDungeonFactorGenerator::DestoryInstance();
	CMemorialDungeonDBLogMgr::DestroyInstance();
	CMemorialDungeonConfig::DestroyInstance();
}


bool CMemorialDungeonMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	if( !N2IDAllocator::GetObj()->N2IDAllocator::RegisterGroup(N2ObjectGroupID::CMemorialDungeonMgr, 1, 1) )
		return false;

	m_cpSelf = new(std::nothrow) CMemorialDungeonMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMemorialDungeonMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMemorialDungeonMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMemorialDungeonMgr* CMemorialDungeonMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


const bool CMemorialDungeonMgr::isOK() const
{
	return m_bOK;
}


const int CMemorialDungeonMgr::GetNum() const
{
	return m_MemorialDungeonContainer2.size();
}


bool CMemorialDungeonMgr::isOpen() const
{
	return m_bOpen;
}


void CMemorialDungeonMgr::Open()
{
	m_bOpen = true;
}


void CMemorialDungeonMgr::Close()
{
	m_bOpen = false;
}


namespace MemorialDungeon
{


void Send_PACKET_IZ_MEMORIALDUNGEON_SYNC2(const int in_HsvrID, const int in_ToZSID, const unsigned long in_hMemorialDungeonID, std::string in_MemorialDungeonName, const unsigned long in_hPartyID, std::string in_PartyName, const unsigned long in_ExistZSID, const int in_Factor, PACKET_IZ_MEMORIALDUNGEON_SYNC2::enumEVENT in_Event)
{
	size_t nPacketLength = sizeof(PACKET_IZ_MEMORIALDUNGEON_SYNC2) + in_MemorialDungeonName.size();
	void* pPacketBuffer = _malloca(nPacketLength);
	if( pPacketBuffer == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Stack Memory Buffer is NULL.");
		return;
	}

	NMemoryHelper mHelper(pPacketBuffer, nPacketLength);
	PACKET_IZ_MEMORIALDUNGEON_SYNC2& packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_SYNC2*>(mHelper.NMemoryHelper::Get(sizeof(PACKET_IZ_MEMORIALDUNGEON_SYNC2)));

	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_SYNC2;
	packet.hPartyID = in_hPartyID;
	if( in_PartyName.size() != 0 )
		memcpy_s(packet.partyName, 24, in_PartyName.c_str(), 24);
	packet.ExistZSID = in_ExistZSID;
	packet.hMemorialDungeonID = in_hMemorialDungeonID;
	packet.Factor = in_Factor;
	packet.Event = in_Event;
	if( in_MemorialDungeonName.size() != 0 )
		memcpy_s(mHelper.NMemoryHelper::Get(in_MemorialDungeonName.size()), in_MemorialDungeonName.size(), in_MemorialDungeonName.c_str(), in_MemorialDungeonName.size());
	packet.PacketLength = static_cast<short>(mHelper.NMemoryHelper::GetUsedBytes());

	if( in_ToZSID == -1 )
		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(in_HsvrID, packet.PacketLength, (char*)&packet);
	else
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(in_HsvrID, in_ToZSID, packet.PacketLength, (char*)&packet);

	_freea(pPacketBuffer);
}


void SendPacket_IZ_MEMORIALDUNGEON_MSG2(const int in_HsvrID, const unsigned long in_PartyID, PACKET_IZ_MEMORIALDUNGEON_MSG2::enumNotify in_Notify, std::string in_MemorialDungeonName)
{
	size_t nPacketLength = sizeof(PACKET_IZ_MEMORIALDUNGEON_MSG2) + in_MemorialDungeonName.size();
	void* pPacketBuffer = _malloca(nPacketLength);
	if( pPacketBuffer == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Stack Memory Buffer is NULL.");
		return;
	}

	NMemoryHelper mHelper(pPacketBuffer, nPacketLength);
	PACKET_IZ_MEMORIALDUNGEON_MSG2& packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_MSG2*>(mHelper.NMemoryHelper::Get(sizeof(PACKET_IZ_MEMORIALDUNGEON_MSG2)));
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_MSG2;
//	packet.GID = ?; // filled in by CParty::Send()
//	packet.AID = ?; // filled in by CParty::Send()
	packet.Notify = in_Notify;
	if( in_MemorialDungeonName.size() > 0 )
		memcpy_s(mHelper.NMemoryHelper::Get(in_MemorialDungeonName.size()), in_MemorialDungeonName.size(), in_MemorialDungeonName.c_str(), in_MemorialDungeonName.size());
	packet.PacketLength = static_cast<short>(mHelper.NMemoryHelper::GetUsedBytes());
	g_groupMgr.CPartyMgr::Send(in_HsvrID, in_PartyID, packet.PacketLength, &packet);

	_freea(pPacketBuffer);
}


void Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2(const int in_HsvrID, const unsigned long in_PartyID, const short in_PriorityOrderNum, std::string in_MemorialDungeonName)
{
	size_t nPacketLength = sizeof(PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2) + in_MemorialDungeonName.size();
	void* pPacketBuffer = _malloca(nPacketLength);
	if( pPacketBuffer == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Stack Memory Buffer is NULL.");
		return;
	}

	NMemoryHelper mHelper(pPacketBuffer, nPacketLength);
	PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2& packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2*>(mHelper.NMemoryHelper::Get(sizeof(PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2)));

	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2;
	packet.PriorityOrderNum = in_PriorityOrderNum;
	if( in_MemorialDungeonName.size() != 0 )
		memcpy_s(mHelper.NMemoryHelper::Get(in_MemorialDungeonName.size()), in_MemorialDungeonName.size(), in_MemorialDungeonName.c_str(), in_MemorialDungeonName.size());
	packet.PacketLength = static_cast<short>(mHelper.NMemoryHelper::GetUsedBytes());

	g_groupMgr.CPartyMgr::Send(in_HsvrID, in_PartyID, packet.PacketLength, &packet);

	_freea(pPacketBuffer);
}


void Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(const int in_HsvrID, const unsigned long in_hParty, const short in_hPriorityNum)
{
	PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY packet;
	memset(&packet, 0x00, sizeof(packet));
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY;
	packet.PriorityOrderNum = in_hPriorityNum;

	g_groupMgr.CPartyMgr::Send(in_HsvrID, in_hParty, sizeof(packet), &packet);
}


void Send_PACKET_IZ_MEMORIALDUNGEON_INFO2(const int in_HsvrID, const unsigned long in_hParty, std::string in_MemorialDungeonName, const unsigned long in_DestroyData, const unsigned long in_EnterTimeOutDate)
{
	size_t nPacketLength = sizeof(PACKET_IZ_MEMORIALDUNGEON_INFO2) + in_MemorialDungeonName.size();
	void* pPacketBuffer = _malloca(nPacketLength);
	if( pPacketBuffer == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Stack Memory Buffer is NULL.");
		return;
	}

	NMemoryHelper mHelper(pPacketBuffer, nPacketLength);
	PACKET_IZ_MEMORIALDUNGEON_INFO2& packet = *reinterpret_cast<PACKET_IZ_MEMORIALDUNGEON_INFO2*>(mHelper.NMemoryHelper::Get(sizeof(PACKET_IZ_MEMORIALDUNGEON_INFO2)));

	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_INFO2;
	packet.DestroyDate = in_DestroyData;
	packet.EnterTimeOutDate = in_EnterTimeOutDate;
	if( in_MemorialDungeonName.size() != 0 )
		memcpy_s(mHelper.NMemoryHelper::Get(in_MemorialDungeonName.size()), in_MemorialDungeonName.size(), in_MemorialDungeonName.c_str(), in_MemorialDungeonName.size());
	packet.PacketLength = static_cast<short>(mHelper.NMemoryHelper::GetUsedBytes());

	g_groupMgr.CPartyMgr::Send(in_HsvrID, in_hParty, packet.PacketLength, &packet);

	_freea(pPacketBuffer);
}


void Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(const int in_HsvrID, const unsigned long in_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE in_Type, const unsigned long in_EnterLimitDate)
{
	PACKET_IZ_MEMORIALDUNGEON_NOTIFY packet;
	memset(&packet, 0x00, sizeof(packet));
    packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_NOTIFY;
    packet.Type = in_Type;
    packet.EnterLimitDate = in_EnterLimitDate;

    g_groupMgr.CPartyMgr::Send(in_HsvrID, in_hParty, sizeof(packet), &packet);
}


void Send_PACKET_IZ_MEMORIALDUNGEON_COMMAND(const int in_HsvrID, const unsigned long in_AID, const unsigned long in_GID, PACKET_IZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command)
{
	PACKET_IZ_MEMORIALDUNGEON_COMMAND packet;
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_COMMAND;
	packet.GID = in_GID;
	packet.AID = in_AID;
	packet.Command = in_Command;

	g_userMgr.CUserMgr::SendMsg(in_HsvrID, in_AID, sizeof(packet), (char*)&packet);
}


}; // namespace


void CMemorialDungeonMgr::DisconnectZSVR(const int in_ZSID)
{
	for( MEMORIALDUNGEON_CONTAINER_ITER2 iter = m_MemorialDungeonContainer2.begin(); iter != m_MemorialDungeonContainer2.end(); ++iter )
	{
		CMemorialDungeon* Dungeon = iter.GetObj();
		if( Dungeon->CMemorialDungeon::GetTargetZSID() == in_ZSID )
			N3MessageMgr::GetObj()->N3MessageMgr::Post(Dungeon->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_DYING_WISH_REQUEST2), 0, 0);
	}
}


void CMemorialDungeonMgr::Subscription(const int in_HsvrID, const int in_RequestAID, const int in_RequestGID, const std::string in_Name, const std::string in_NickName, const int in_hParty, const std::string in_PartyName)
{
	if( g_groupMgr.CPartyMgr::GetGroupOwner(in_hParty) != in_RequestAID )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(in_HsvrID, in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_RIGHT, in_Name);
		return;
	}

	if( !m_bOpen )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(in_HsvrID, in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE, in_Name);
		return;
	}

	SUBSCRIPTION_PLAYER_CONTAINER_ITER iter1 = m_SubscriptionPlayerContainer.findSecondaryKey(in_hParty);
	if( iter1 != m_SubscriptionPlayerContainer.end() )
	{
		CMemorialDungeonReservedPlayer& Player = iter1.GetObj();
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(in_HsvrID, in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE, Player.m_Name);
		return;
	}

	MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(in_hParty);
	if( mIter != m_MemorialDungeonContainer2.end() )
	{
		CMemorialDungeon* Dungeon = mIter.GetObj();
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(in_HsvrID, in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_EXIST, Dungeon->CMemorialDungeon::GetName());
		return;
	}

	int PriorityNum = m_SubscriptionPlayerContainer.size() + 1;
	if( !m_SubscriptionPlayerContainer.insert(++g_FunctionUniqueCnt, in_hParty, CMemorialDungeonReservedPlayer(in_HsvrID, PriorityNum, in_Name, in_NickName, in_hParty, in_PartyName)) )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(in_HsvrID, in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_UNKNOWN, in_Name);
		return;
	}

	MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2(in_HsvrID, in_hParty, PriorityNum, in_Name);
	CMemorialDungeonDBLogMgr::GetObj()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_SUBSCRIPTION, in_Name, in_PartyName, in_hParty, 0);
}


int CMemorialDungeonMgr::CreateMemorialDungeonR2(CMemorialDungeonReservedPlayer& in_ReservedPlayer)
{
	int TargetZSVR = -1;

	std::pair<bool,CMemorialDungeonConfig::lcMDConfigData> MDConfig = CMemorialDungeonConfig::GetObj()->CMemorialDungeonConfig::GetOnceMDObj(in_ReservedPlayer.m_Name);
	if( !MDConfig.first )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "메모리얼던젼 config를 찾을수없다(%s)", in_ReservedPlayer.m_Name.c_str());
		return -1;
	}

	if( MDConfig.second.m_szPlaceWithMap.size() != 0 )
	{
		int DesireTargetZSVR = CMapInfoMgr::GetObj()->CMapInfoMgr::GetServerID(MDConfig.second.m_szPlaceWithMap);

		if( in_ReservedPlayer.m_HsvrID == g_serverInfo.CServerInfo::GetDestinationSID(DesireTargetZSVR, TARGET_ONE_SID) )
		{
			TargetZSVR = DesireTargetZSVR;
		}
		else
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[메모리얼던젼] 특정월드(%d)의 특정맵(%s)을 찾을수 없습니다", in_ReservedPlayer.m_HsvrID, MDConfig.second.m_szPlaceWithMap.c_str());
		}
	}

	int TargetZSID = CZsvrMgr::GetObj()->CZServerMgr::SelectInstantMapTargetZSVR(in_ReservedPlayer.m_HsvrID, TargetZSVR);
	if( TargetZSID < 0 )
		return 0;

	CMemorialDungeon* Dungeon = new(std::nothrow) CMemorialDungeon(in_ReservedPlayer.m_Name, in_ReservedPlayer.m_NickName, in_ReservedPlayer.m_hParty, in_ReservedPlayer.m_PartyName, TargetZSID, in_ReservedPlayer.m_HsvrID);
	if( Dungeon == NULL )
		return -1;

	if( !Dungeon->CMemorialDungeon::isOK() )
	{
		delete Dungeon;
		return -1;
	}

	if( !m_MemorialDungeonContainer2.insert(Dungeon->CMemorialDungeon::GetPartyID(), Dungeon->GetFactor(), Dungeon) )
		return -1;

	return 1;
}


void CMemorialDungeonMgr::CreateResult(const unsigned long in_hParty, const bool in_bResult)
{
	SUBSCRIPTION_PLAYER_CONTAINER_ITER iter = m_SubscriptionPlayerContainer.begin();
	if( iter == m_SubscriptionPlayerContainer.end() )
		return;

	CMemorialDungeonReservedPlayer& Player = iter.GetObj();
	if( !Player.m_bCreateDoing )
		return;

	if( Player.m_hParty != in_hParty )
		return;

	if( in_bResult )
	{
		MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(in_hParty);
		if( mIter == m_MemorialDungeonContainer2.end() )
			return;

		CMemorialDungeon* Dungeon = mIter.GetObj();
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_INFO2(Dungeon->CMemorialDungeon::GetHsvrID(), Dungeon->CMemorialDungeon::GetPartyID(), Dungeon->CMemorialDungeon::GetName(), Dungeon->CMemorialDungeon::GetLiveDate(), Dungeon->CMemorialDungeon::GetEnterLimitDate());
		CMemorialDungeonDBLogMgr::GetObj()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_CREATE, Dungeon->CMemorialDungeon::GetName(), Dungeon->CMemorialDungeon::GetPartyName(), Dungeon->CMemorialDungeon::GetPartyID(), Dungeon->CMemorialDungeon::GetTargetZSID());
	}
	else
	{
		CMemorialDungeonDBLogMgr::GetObj()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_SUBSCRIPTION_CANCEL_BY_CREATE_FAIL, Player.m_Name, Player.m_PartyName, Player.m_hParty, 0);
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(Player.m_HsvrID, in_hParty, -1);
	}

	m_SubscriptionPlayerContainer.erase(iter);

	this->CMemorialDungeonMgr::NotifySubscriptionPriority();
}


void CMemorialDungeonMgr::Visa(const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hPartyID)
{
	MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(in_hPartyID);
	if( mIter == m_MemorialDungeonContainer2.end() )
		return;

	CMemorialDungeon* Dungeon = mIter.GetObj();
	if( !Dungeon->CMemorialDungeon::isActive() )
		return;

	if( Dungeon->CMemorialDungeon::GetEnterInstantMapName().size() == 0 )
		return;

	PACKET_IZ_MEMORIALDUNGEON_VISA packet = {};
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_VISA;
	packet.GID = in_GID;
	packet.AID = in_AID;
	packet.ZSID = Dungeon->CMemorialDungeon::GetTargetZSID();
	memcpy(packet.mapName, Dungeon->CMemorialDungeon::GetEnterInstantMapName().c_str(), 16); //FIXME: OOB read, garbage write
	packet.mapName[countof(packet.mapName)-1] = '\0';
	packet.x = Dungeon->CMemorialDungeon::GetEnterInstantMapX();
	packet.y = Dungeon->CMemorialDungeon::GetEnterInstantMapY();

	g_userMgr.CUserMgr::SendMsg(packet.AID, sizeof(packet), (char*)&packet);
}


void CMemorialDungeonMgr::OnNewbie(const int in_HsvrID, const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hParty, const std::string in_mapName)
{
	SUBSCRIPTION_PLAYER_CONTAINER_ITER sIter = m_SubscriptionPlayerContainer.findSecondaryKey(in_hParty);
	if( sIter != m_SubscriptionPlayerContainer.end() )
	{
		CMemorialDungeonReservedPlayer& Player = sIter.GetObj();
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2(Player.m_HsvrID, Player.m_hParty, static_cast<short>(Player.m_PriorityNum), Player.m_Name);
	}
	else
	{
		MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(in_hParty);
		if( mIter != m_MemorialDungeonContainer2.end() )
		{
			CMemorialDungeon* Dungeon = mIter.GetObj();
			MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_INFO2(Dungeon->CMemorialDungeon::GetHsvrID(), Dungeon->CMemorialDungeon::GetPartyID(), Dungeon->CMemorialDungeon::GetName(), Dungeon->CMemorialDungeon::GetLiveDate(), Dungeon->CMemorialDungeon::GetEnterLimitDate());
		}

		this->CMemorialDungeonMgr::OnEnter(in_hParty, in_GID, in_AID, in_mapName);
	}
}


void CMemorialDungeonMgr::Command_SubscriptionCancel(const unsigned long in_hParty)
{
	SUBSCRIPTION_PLAYER_CONTAINER_ITER sIter = m_SubscriptionPlayerContainer.findSecondaryKey(in_hParty);
	if( sIter == m_SubscriptionPlayerContainer.end() )
		return;

	CMemorialDungeonReservedPlayer& Player = sIter.GetObj();
	if( Player.m_bCreateDoing == true )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG2(Player.m_HsvrID, Player.m_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG2::MEMORIALDUNGEON_SUBSCRIPTION_CANCEL_FAIL, Player.m_Name);
		return;
	}

	MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(Player.m_HsvrID, in_hParty, -1);
	CMemorialDungeonDBLogMgr::GetObj()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_SUBSCRIPTION_CANCEL_BY_USER, Player.m_Name, Player.m_PartyName, Player.m_hParty, 0);
	m_SubscriptionPlayerContainer.erase(sIter);
	this->CMemorialDungeonMgr::NotifySubscriptionPriority();
}


void CMemorialDungeonMgr::Command_Destroy(const unsigned long in_hPartyID)
{
	MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(in_hPartyID);
	if( mIter == m_MemorialDungeonContainer2.end() )
		return;

	CMemorialDungeon* Dungeon = mIter.GetObj();
	CMemorialDungeonDBLogMgr::GetObj()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_DESTROY_BY_USER, Dungeon->CMemorialDungeon::GetName(), Dungeon->CMemorialDungeon::GetPartyName(), Dungeon->CMemorialDungeon::GetPartyID(), Dungeon->CMemorialDungeon::GetTargetZSID());
	MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(Dungeon->CMemorialDungeon::GetHsvrID(), Dungeon->CMemorialDungeon::GetPartyID(), PACKET_ZC_MEMORIALDUNGEON_NOTIFY::TYPE_DESTROY_USER_REQUEST, 0);
	N3MessageMgr::GetObj()->N3MessageMgr::Post(Dungeon->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_DYING_WISH_REQUEST2), 0, 0);
}


void CMemorialDungeonMgr::Command(const unsigned long in_hParty, const PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command)
{
	switch( in_Command )
	{
	case PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_SUBSCRIPTION_CANCEL:
		this->CMemorialDungeonMgr::Command_SubscriptionCancel(in_hParty);
	break;
	case PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_MEMORIALDUNGEON_DESTROY:
	case PACKET_CZ_MEMORIALDUNGEON_COMMAND::COMMAND_MEMORIALDUNGEON_DESTROY_FORCE:
		this->CMemorialDungeonMgr::Command_Destroy(in_hParty);
	break;
	};
}


void CMemorialDungeonMgr::NotifyAllMemorialDunbeon(const int in_ZSVR, const unsigned long& in_ZSVRRegisteredMgrFUCnt)
{
	for( MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.begin(); mIter != m_MemorialDungeonContainer2.end(); ++mIter )
	{
		CMemorialDungeon* Dungeon = mIter.GetObj();

		if( !Dungeon->CMemorialDungeon::IsDestroyReady() )
		{
			unsigned long cnt = Dungeon->CMemorialDungeon::GetZSVRregisteredFUCnt();
			if( cnt != 0 && in_ZSVRRegisteredMgrFUCnt > cnt )
				MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SYNC2(Dungeon->CMemorialDungeon::GetHsvrID(), in_ZSVR, Dungeon->N3Object::GetMyID(), Dungeon->CMemorialDungeon::GetName(), Dungeon->CMemorialDungeon::GetPartyID(), Dungeon->CMemorialDungeon::GetPartyName(), Dungeon->CMemorialDungeon::GetTargetZSID(), Dungeon->CMemorialDungeon::GetFactor(), PACKET_IZ_MEMORIALDUNGEON_SYNC2::EVENT_CREATE);
		}
	}
}


void CMemorialDungeonMgr::OnEnter(const unsigned long in_PartyID, const unsigned long in_GID, const unsigned long in_AID, const std::string in_mapName)
{
	int Factor = InstantMap::GetInstantMapFactor(in_mapName);
	if( Factor <= 0 )
		return;

	MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findSecondaryKey(Factor);
	if( mIter == m_MemorialDungeonContainer2.end() )
		return;

	CMemorialDungeon* Dungeon = mIter.GetObj();
	if( !Dungeon->CMemorialDungeon::isActive() || in_PartyID != Dungeon->CMemorialDungeon::GetPartyID() )
	{
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_COMMAND(Dungeon->CMemorialDungeon::GetHsvrID(), in_AID, in_GID, PACKET_IZ_MEMORIALDUNGEON_COMMAND::COMMAND_PLAYER_KICK);
		return;
	}

	Dungeon->CMemorialDungeon::OnEnter(in_GID, in_AID);
}


void CMemorialDungeonMgr::OnLeave(const unsigned long in_GID, const unsigned long in_AID, const std::string in_mapName)
{
	int Factor = InstantMap::GetInstantMapFactor(in_mapName);
	if( Factor <= 0 )
		return;

	MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findSecondaryKey(Factor);
	if( mIter == m_MemorialDungeonContainer2.end() )
		return;

	CMemorialDungeon* Dungeon = mIter.GetObj();
	if( !Dungeon->CMemorialDungeon::isActive() )
		return;

	Dungeon->CMemorialDungeon::OnLeave(in_GID, in_AID);
}


bool CMemorialDungeonMgr::isSubscription(const unsigned long in_hParty)
{
	SUBSCRIPTION_PLAYER_CONTAINER_ITER iter = m_SubscriptionPlayerContainer.findSecondaryKey(in_hParty);
	return ( iter != m_SubscriptionPlayerContainer.end() );
}


void CMemorialDungeonMgr::PartyLeave(const unsigned long in_hPartyID, const unsigned long in_AID, const unsigned long in_GID)
{
	MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(in_hPartyID);
	if( mIter == m_MemorialDungeonContainer2.end() )
		return;

	CMemorialDungeon* Dungeon = mIter.GetObj();
	if( !Dungeon->CMemorialDungeon::isActive() )
		return;

	Dungeon->CMemorialDungeon::PartyLeave(in_AID, in_GID);
}


void CMemorialDungeonMgr::PartyDestroy(const unsigned long in_hPartyID)
{
	MEMORIALDUNGEON_CONTAINER_ITER2 mIter = m_MemorialDungeonContainer2.findPrimaryKey(in_hPartyID);
	if( mIter == m_MemorialDungeonContainer2.end() )
		return;

	CMemorialDungeon* Dungeon = mIter.GetObj();
	if( !Dungeon->CMemorialDungeon::isActive() )
		return;

	N3MessageMgr::GetObj()->N3MessageMgr::Post(Dungeon->N3Object::GetMyID(), N3MSG(CMemorialDungeon,MSG_DYING_WISH_REQUEST2), 0, 0);
}
