#include "MemorialDungeonMgr.h"
#include "Common/Packet.h"
#include "enums.hpp"
#include "PartyMgr.h"
#include "MemorialDungeonDBLogMgr.h"
#include "MemorialDungeon.h"


hook_ptr<CMemorialDungeonMgr*> CMemorialDungeonMgr::m_cpSelf(SERVER, "CMemorialDungeonMgr::m_cpSelf"); // = NULL;


hook_method<void (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_Process(SERVER, "CMemorialDungeonMgr::Process");
void CMemorialDungeonMgr::Process(void) // line 74
{
	return (this->*_Process)();

	//TODO
}


hook_method<const int (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_GetNum(SERVER, "CMemorialDungeonMgr::GetNum");
const int CMemorialDungeonMgr::GetNum(void) // line 47 (Memorial Dungeon/MemorialDungeonMgr.h)
{
	return (this->*_GetNum)();

	return m_MemorialDungeonContainer2.size();
}


hook_method<void (CMemorialDungeonMgr::*)(const int in_RequestAID, const int in_RequestGID, const mystd::string in_Name, const mystd::string in_NickName, const int in_hParty, const mystd::string in_PartyName)> CMemorialDungeonMgr::_Subscription(SERVER, "CMemorialDungeonMgr::Subscription");
void CMemorialDungeonMgr::Subscription(const int in_RequestAID, const int in_RequestGID, const mystd::string in_Name, const mystd::string in_NickName, const int in_hParty, const mystd::string in_PartyName) // line 378-440
{
	return (this->*_Subscription)(in_RequestAID,in_RequestGID,in_Name,in_NickName,in_hParty,in_PartyName);

	if( InstanceCPartyMgr()->CPartyMgr::GetGroupOwner(in_hParty) != in_RequestAID )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG(in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_RIGHT, in_Name);
		return; // not party leader
	}

	if( !m_bOpen )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG(in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE, in_Name);
		return; // not open
	}

	SUBSCRIPTION_PLAYER_CONTAINER_ITER iter1 = m_SubscriptionPlayerContainer.findSecondaryKey(in_hParty);
	if( iter1 != m_SubscriptionPlayerContainer.end() )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG(in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_DUPLICATE, in_Name);
		return; // subscription already exists
	}

	MEMORIALDUNGEON_CONTAINER_ITER2 iter2 = m_MemorialDungeonContainer2.findPrimaryKey(in_hParty);
	if( iter2 != m_MemorialDungeonContainer2.end() )
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG(in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_EXIST, iter2.GetObj()->CMemorialDungeon::GetName());
		return; // dungeon already exists
	}

	++g_FunctionUniqueCnt;
	int priorityNum = m_SubscriptionPlayerContainer.size() + 1;
	if( m_SubscriptionPlayerContainer.insert(g_FunctionUniqueCnt, in_hParty, CMemorialDungeonReservedPlayer(priorityNum, in_Name, in_NickName, in_hParty, in_PartyName)) )
	{
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(in_hParty, priorityNum, in_Name);
		InstanceCMemorialDungeonDBLogMgr()->CMemorialDungeonDBLogMgr::Add(CMemorialDungeonDBLog::TYPE_SUBSCRIPTION, in_Name, in_PartyName, in_hParty, 0);
		return; // done
	}
	else
	{
		MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG(in_hParty, PACKET_IZ_MEMORIALDUNGEON_MSG::MEMORIALDUNGEON_SUBSCRIPTION_ERROR_CLOSE, in_Name);
		return; // failed to insert subscription
	}
}


hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_hParty, const enum PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command)> CMemorialDungeonMgr::_Command(SERVER, "CMemorialDungeonMgr::Command");
void CMemorialDungeonMgr::Command(const unsigned long in_hParty, const enum PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command) // line 657-669
{
	return (this->*_Command)(in_hParty,in_Command);

	// TODO
}


hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hParty, const mystd::string in_mapName)> CMemorialDungeonMgr::_OnNewbie(SERVER, "CMemorialDungeonMgr::OnNewbie");
void CMemorialDungeonMgr::OnNewbie(const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hParty, const mystd::string in_mapName) // line 565-588
{
	return (this->*_OnNewbie)(in_GID, in_AID, in_hParty, in_mapName);

	SUBSCRIPTION_PLAYER_CONTAINER_ITER iter = m_SubscriptionPlayerContainer.findSecondaryKey(in_hParty);
	if( iter != m_SubscriptionPlayerContainer.end() )
	{
		CMemorialDungeonReservedPlayer& subscription = iter.GetObj();
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(subscription.m_hParty, subscription.m_PriorityNum, subscription.m_Name);
		return; // player already has subscription
	}

	MEMORIALDUNGEON_CONTAINER_ITER2 iter2 = m_MemorialDungeonContainer2.findPrimaryKey(in_hParty);
	if( iter2 != m_MemorialDungeonContainer2.end() )
	{
		CMemorialDungeon* dungeon = iter2.GetObj();
		MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_INFO(dungeon->CMemorialDungeon::GetPartyID(), dungeon->CMemorialDungeon::GetName(), dungeon->CMemorialDungeon::GetLiveDate(), dungeon->CMemorialDungeon::GetEnterLimitDate());
	}

	this->CMemorialDungeonMgr::OnEnter(in_hParty, in_GID, in_AID, in_mapName);
}


hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_PartyID, const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName)> CMemorialDungeonMgr::_OnEnter(SERVER, "CMemorialDungeonMgr::OnEnter");
void CMemorialDungeonMgr::OnEnter(const unsigned long in_PartyID, const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName) // line 696-708
{
	return (this->*_OnEnter)(in_PartyID,in_GID,in_AID,in_mapName);

	// TODO
}


hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName)> CMemorialDungeonMgr::_OnLeave(SERVER, "CMemorialDungeonMgr::OnLeave");
void CMemorialDungeonMgr::OnLeave(const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName) // line 711-720
{
	return (this->*_OnLeave)(in_GID,in_AID,in_mapName);

	// TODO
}


hook_method<bool (CMemorialDungeonMgr::*)(const unsigned long in_hParty)> CMemorialDungeonMgr::_isSubscription(SERVER, "CMemorialDungeonMgr::isSubscription");
bool CMemorialDungeonMgr::isSubscription(const unsigned long in_hParty) // line 723
{
	return (this->*_isSubscription)(in_hParty);

	N2DualKeyMap<unsigned long,unsigned long,CMemorialDungeonReservedPlayer>::Iterator it = m_SubscriptionPlayerContainer.findSecondaryKey(in_hParty);
	return ( it != m_SubscriptionPlayerContainer.end() );
}


hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_hPartyID, const unsigned long in_AID, const unsigned long in_GID)> CMemorialDungeonMgr::_PartyLeave(SERVER, "CMemorialDungeonMgr::PartyLeave");
void CMemorialDungeonMgr::PartyLeave(const unsigned long in_hPartyID, const unsigned long in_AID, const unsigned long in_GID) // line 730
{
	return (this->*_PartyLeave)(in_hPartyID,in_AID,in_GID);

	CMemorialDungeonMgr::MEMORIALDUNGEON_CONTAINER_ITER2 it = m_MemorialDungeonContainer2.findPrimaryKey(in_hPartyID);
	if( it != m_MemorialDungeonContainer2.end() )
	{
		CMemorialDungeon* dungeon = it.GetObj();
		if( dungeon->GetState() == CMemorialDungeon::STATE_CREATE )
			dungeon->CMemorialDungeon::PartyLeave(in_AID, in_GID);
	}
}


hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_hPartyID)> CMemorialDungeonMgr::_PartyDestroy(SERVER, "CMemorialDungeonMgr::PartyDestroy");
void CMemorialDungeonMgr::PartyDestroy(const unsigned long in_hPartyID) // line TODO
{
	return (this->*_PartyDestroy)(in_hPartyID);

	// TODO
}


hook_method<static bool (__cdecl *)(void)> CMemorialDungeonMgr::_CreateInstance(SERVER, "CMemorialDungeonMgr::CreateInstance");
bool CMemorialDungeonMgr::CreateInstance(void) // line 206
{
	return (_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CMemorialDungeonMgr::_DestroyInstance(SERVER, "CMemorialDungeonMgr::DestroyInstance");
void CMemorialDungeonMgr::DestroyInstance(void) // line 221
{
	return (_DestroyInstance)();

	//TODO
}


/// @custom
CMemorialDungeonMgr* CMemorialDungeonMgr::GetObj(void)
{
	return m_cpSelf;
}


////////////////////////////////////////


hook_method<void (__cdecl *)(unsigned long in_PartyID, enum PACKET_IZ_MEMORIALDUNGEON_MSG::enumNotify in_Notify, mystd::string in_MemorialDungeonName)> MemorialDungeon::_SendPacket_IZ_MEMORIALDUNGEON_MSG(SERVER, "MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG");
void __cdecl MemorialDungeon::SendPacket_IZ_MEMORIALDUNGEON_MSG(unsigned long in_PartyID, enum PACKET_IZ_MEMORIALDUNGEON_MSG::enumNotify in_Notify, mystd::string in_MemorialDungeonName) // line 268-279
{
	return (MemorialDungeon::_SendPacket_IZ_MEMORIALDUNGEON_MSG)(in_PartyID,in_Notify,in_MemorialDungeonName);

	PACKET_IZ_MEMORIALDUNGEON_MSG packet; memset(&packet, 0, sizeof(packet));
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_MSG;
	packet.Notify = in_Notify;
	if( in_MemorialDungeonName.length() )
	{
		memcpy(packet.MemorialDungeonName, in_MemorialDungeonName.c_str(), sizeof(packet.MemorialDungeonName) - 1); // FIXME reads outside of buffer if in_MemorialDungeonName.capacity() < 59 (buffer has extra byte for terminator '\0')
		packet.MemorialDungeonName[sizeof(packet.MemorialDungeonName) - 1] = '\0';
	}

	InstanceCPartyMgr()->CPartyMgr::Send(in_PartyID, sizeof(packet), &packet);
}


hook_method<void (__cdecl *)(unsigned long in_PartyID, short in_PriorityOrderNum, mystd::string in_MemorialDungeonName)> MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(SERVER, "MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO");
void __cdecl MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(unsigned long in_PartyID, short in_PriorityOrderNum, mystd::string in_MemorialDungeonName) // line 288-300
{
	return (MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO)(in_PartyID,in_PriorityOrderNum,in_MemorialDungeonName);

	PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO packet; memset(&packet, 0, sizeof(packet));
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO;
	packet.PriorityOrderNum = in_PriorityOrderNum;
	if( in_MemorialDungeonName.length() )
	{
		size_t len = in_MemorialDungeonName.length();
		if( len >= sizeof(packet.MemorialDungeonName) )
			len = sizeof(packet.MemorialDungeonName);
		memcpy(packet.MemorialDungeonName, in_MemorialDungeonName.c_str(), len);
		packet.MemorialDungeonName[sizeof(packet.MemorialDungeonName) - 1] = '\0';
	}

	InstanceCPartyMgr()->CPartyMgr::Send(in_PartyID, sizeof(packet), &packet);
}


hook_method<void (__cdecl *)(unsigned long in_hParty, short in_hPriorityNum)> MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(SERVER, "MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY");
void __cdecl MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(unsigned long in_hParty, short in_hPriorityNum) // line 305-311
{
	return (MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY)(in_hParty,in_hPriorityNum);

	PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY packet; memset(&packet, 0, sizeof(packet));
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY;
	packet.PriorityOrderNum = in_hPriorityNum;

	InstanceCPartyMgr()->CPartyMgr::Send(in_hParty, sizeof(packet), &packet);
}


hook_method<void (__cdecl *)(unsigned long in_hParty, mystd::string in_MemorialDungeonName, unsigned long in_DestroyData, unsigned long in_EnterTimeOutDate)> MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_INFO(SERVER, "MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_INFO");
void __cdecl MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_INFO(unsigned long in_hParty, mystd::string in_MemorialDungeonName, unsigned long in_DestroyData, unsigned long in_EnterTimeOutDate) // line 317-329
{
	return (MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_INFO)(in_hParty,in_MemorialDungeonName,in_DestroyData,in_EnterTimeOutDate);

	PACKET_IZ_MEMORIALDUNGEON_INFO packet; memset(&packet, 0, sizeof(packet));
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_INFO;
	if( in_MemorialDungeonName.length() )
	{
		memcpy(packet.MemorialDungeonName, in_MemorialDungeonName.c_str(), sizeof(packet.MemorialDungeonName) - 1); // FIXME reads outside of buffer if in_MemorialDungeonName.capacity() < 59 (buffer has extra byte for terminator '\0')
		packet.MemorialDungeonName[sizeof(packet.MemorialDungeonName) - 1] = '\0';
	}
	packet.DestroyDate = in_DestroyData;
	packet.EnterTimeOutDate = in_EnterTimeOutDate;

	InstanceCPartyMgr()->CPartyMgr::Send(in_hParty, sizeof(packet), &packet);
}


hook_method<void (__cdecl *)(const unsigned int in_hParty, enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE in_Type, const unsigned int in_EnterLimitDate)> MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(SERVER, "MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY");
void __cdecl MemorialDungeon::Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(const unsigned int in_hParty, enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE in_Type, const unsigned int in_EnterLimitDate) // line 335-342
{
	return (MemorialDungeon::_Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY)(in_hParty,in_Type,in_EnterLimitDate);

	PACKET_IZ_MEMORIALDUNGEON_NOTIFY packet; memset(&packet, 0, sizeof(packet));
	packet.PacketType = HEADER_IZ_MEMORIALDUNGEON_NOTIFY;
	packet.Type = in_Type;
	packet.EnterLimitDate = in_EnterLimitDate;

	InstanceCPartyMgr()->CPartyMgr::Send(in_hParty, sizeof(packet), &packet);
}
