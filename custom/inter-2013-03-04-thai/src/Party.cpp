#include "CEntryQueueMgr.h"
#include "InterServer.h"
#include "Party.h"
#include "PartyDB.h"
#include "PartyMgr.h"
#include "UserMgr.h"
#include "Common/Packet.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/VarLenPacketPtr.h"


CParty::CParty()
{
	m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Init(g_groupMgr.CPartyMgr::GetMaxMemberNum() + 2);
}


CParty::~CParty()
{
}


void CParty::Init()
{
	m_groupName[0] = '\0';
	m_groupID = 0;
	m_groupInfo.expOption = EXP_NOTSHARED;
	m_groupInfo.ItemPickupRule = true;
	m_groupInfo.ItemDivisionRule = false;

	this->CParty::DeleteAll();
}


void CParty::SetGroupID(unsigned long GRID)
{
	m_groupID = GRID;
}


unsigned long CParty::GetGroupID()
{
	return m_groupID;
}


void CParty::SetGroupName(const char* gname)
{
	memcpy(m_groupName, gname, 24);
}


char* CParty::GetGroupName()
{
	return m_groupName;
}


void CParty::SetPartyRole(bool ItemPickupRule, bool ItemDivisionRule)
{
	m_groupInfo.ItemPickupRule = ItemPickupRule;
	m_groupInfo.ItemDivisionRule = ItemDivisionRule;
}


int CParty::GetMemberCount()
{
	return m_users.size();
}


unsigned long CParty::GetMaster()
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->Role == GROUPMEMBER_ROLE_MASTER )
			return member->AID; // found.
	}

	return 0; // not found.
}


BOOL CParty::AddMember(CHARINFO_IN_GROUP* par, int option)
{
	CHARINFO_IN_GROUP* member = m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Alloc();

	if( this->CParty::SearchMember(par->AID) )
		this->CParty::DeleteMember(par->AID, par->GID, GROUPMEMBER_DELETE_LEAVE);

	if( member == NULL )
		return FALSE;

	memcpy(member, par, sizeof(CHARINFO_IN_GROUP));
	m_users.push_back(member);

	PACKET_IZ_ADD_MEMBER_TO_GROUP2 outpacket;
	outpacket.PacketType = HEADER_IZ_ADD_MEMBER_TO_GROUP2;
//	outpacket.receiverAID = ?; // filled in by Broadcast()
	outpacket.AID = par->AID;
	outpacket.state = par->curState;
	outpacket.Role = par->Role;
	outpacket.ItemPickupRule = m_groupInfo.ItemPickupRule;
	outpacket.ItemDivisionRule = m_groupInfo.ItemDivisionRule;
	memcpy(outpacket.groupName, m_groupName, 24);
	memcpy(outpacket.characterName, par->charName, 24);
	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(par->AID, par->GID);
	if( user != NULL )
		memcpy(outpacket.mapName, user->mapName, 16);
	else
		outpacket.mapName[0] = '\0';
	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);

	this->CParty::CheckExpSharableInfo();

	return TRUE;
}


BOOL CParty::DeleteMember(unsigned long AID, unsigned long GID, unsigned char type)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->AID == AID && member->GID == GID )
		{
			PACKET_IZ_DELETE_MEMBER_FROM_GROUP outpacket;
			outpacket.PacketType = HEADER_IZ_DELETE_MEMBER_FROM_GROUP;
//			outpacket.receiverAID = ?; // filled in by Broadcast()
			outpacket.AID = AID;
			memcpy(outpacket.characterName, member->charName, 24u);
			outpacket.result = type;
			this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);

			memset(member, 0, sizeof(*member));
			m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Free(member);
			m_users.erase(iter);

			this->CParty::UpdateExpOption(EXP_NOTSHARED, true);

			return TRUE;
		}
	}

	return FALSE; // not found.
}


CHARINFO_IN_GROUP* CParty::SearchMember(unsigned long AID)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->AID == AID )
			return member; // found.
	}

	return NULL; // not found.
}


unsigned long CParty::SearchGID(unsigned long AID)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->AID == AID )
			return member->GID; // found.
	}

	return NULL; // not found.
}


unsigned long CParty::SearchGID(char* name)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( strcmp(member->charName, name) == 0 )
			return member->GID; // found.
	}

	return 0; // not found.
}


BOOL CParty::UpdateState(unsigned long AID, unsigned char state)
{
	CHARINFO_IN_GROUP* member = this->CParty::SearchMember(AID);
	if( member == NULL )
		return FALSE;

	PACKET_IZ_ADD_MEMBER_TO_GROUP2 outpacket;
	outpacket.PacketType = 10639;
//	outpacket.receiverAID = ?; // filled in by Broadcast()
	outpacket.AID = member->AID;
	outpacket.Role = member->Role;
	member->curState = state;
	outpacket.state = state;
	memcpy(outpacket.characterName, member->charName, 24);
	memcpy(outpacket.groupName, m_groupName, 24);
	outpacket.ItemPickupRule = m_groupInfo.ItemPickupRule;
	outpacket.ItemDivisionRule = m_groupInfo.ItemDivisionRule;
	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
	if( user != NULL )
		memcpy(outpacket.mapName, user->mapName, 16);
	else
		outpacket.mapName[0] = '\0';
	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);

	if( state == GROUPMEMBER_STATE_CONNECTED )
		this->CParty::CheckExpSharableInfo();

	return TRUE;
}


void CParty::UpdateMapName(unsigned long AID, char* mapName)
{
	CHARINFO_IN_GROUP* member = this->CParty::SearchMember(AID);
	if( member == NULL )
		return;

	PACKET_IZ_ADD_MEMBER_TO_GROUP outpacket;
	outpacket.PacketType = 10537;
	outpacket.state = member->curState;
	outpacket.AID = member->AID;
	outpacket.Role = member->Role;
	memcpy(outpacket.characterName, member->charName, 24);
	memcpy(outpacket.groupName, m_groupName, 24);
	memcpy(outpacket.mapName, mapName, 16);
	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


void CParty::UpdateMapName2(unsigned long AID, const char* mapName)
{
	CHARINFO_IN_GROUP* member = this->CParty::SearchMember(AID);
	if( member == NULL )
		return;

	PACKET_IZ_ADD_MEMBER_TO_GROUP2 outpacket;
	outpacket.PacketType = 10639;
//	outpacket.receiverAID = ?; // filled in by Broadcast()
	outpacket.AID = member->AID;
	outpacket.state = member->curState;
	outpacket.Role = member->Role;
	outpacket.ItemPickupRule = m_groupInfo.ItemPickupRule;
	outpacket.ItemDivisionRule = m_groupInfo.ItemDivisionRule;
	memcpy(outpacket.characterName, member->charName, 24);
	memcpy(outpacket.groupName, m_groupName, 24);
	memcpy(outpacket.mapName, mapName, 16);
	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


void CParty::DeleteAll()
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); iter = m_users.erase(iter) )
	{
		CHARINFO_IN_GROUP* member = *iter;

		memset(member, 0, sizeof(*member));
		m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Free(member);
	}
}


void CParty::Send(const int in_HsvrID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			in_pPartyBroadCastPacket->GID = member->GID;
			in_pPartyBroadCastPacket->AID = member->AID;
			g_userMgr.CUserMgr::SendMsg(in_HsvrID, member->AID, in_Length, (char*)in_pPartyBroadCastPacket);
		}
	}
}


void CParty::Send(const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			in_pPartyBroadCastPacket->GID = member->GID;
			in_pPartyBroadCastPacket->AID = member->AID;
			g_userMgr.CUserMgr::SendMsg(member->AID, in_Length, (char*)in_pPartyBroadCastPacket);
		}
	}
}


void CParty::Send(const int in_HsvrID, const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			in_pPartyBroadCastPacket->GID = member->GID;
			in_pPartyBroadCastPacket->AID = member->AID;
			g_userMgr.CUserMgr::SendMsg(in_HsvrID, member->AID, in_Length, (char*)in_pPartyBroadCastPacket);
		}
	}
}


void CParty::Send(const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			in_pPartyBroadCastPacket->GID = member->GID;
			in_pPartyBroadCastPacket->AID = member->AID;
			g_userMgr.CUserMgr::SendMsg(member->AID, in_Length, (char*)in_pPartyBroadCastPacket);
		}
	}
}


void CParty::BroadCast(int len, char* buf)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			memcpy(buf + 2, &member->AID, 4); //FIXME: a really sketchy optimization
			g_userMgr.CUserMgr::SendMsg(member->AID, len, buf);
		}
	}
}


CHARINFO_IN_GROUP* CParty::GetGroupInfo(unsigned long AID)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->AID == AID )
			return member; // found.
	}

	return NULL; // not found.
}


int CParty::GetConnectedMember()
{
	int count = 0;

	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
			++count;
	}

	return count;
}


void CParty::NotifyGroupMembers(unsigned long AID)
{
	char PacketBuffer[sizeof(PACKET_IZ_GROUP_LIST) + CPartyMgr::MAX_PARTY_MEMBER_NUM * sizeof(GROUPMEMBER_INFO)];
	PACKET_IZ_GROUP_LIST& outPacket = *reinterpret_cast<PACKET_IZ_GROUP_LIST*>(PacketBuffer);
	outPacket.PacketType = HEADER_IZ_GROUP_LIST;
	outPacket.AID = AID;
	outPacket.expOption = m_groupInfo.expOption;
	memcpy(outPacket.groupName, m_groupName, 24);

	int MemberCnt = 0;
	GROUPMEMBER_INFO* Info = outPacket.Info;
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( MemberCnt >= CPartyMgr::MAX_PARTY_MEMBER_NUM )
			break;

		++MemberCnt;

		Info->AID = member->AID;
		memcpy(Info->characterName, member->charName, 24);
		Info->role = member->Role;
		Info->state = member->curState;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
			if( user != NULL )
			{
				memcpy(Info->mapName, user->mapName, 16);
			}
			else
			{
				Info->state = GROUPMEMBER_STATE_DISCONNEDTED;
				this->CParty::UpdateState(member->AID, GROUPMEMBER_STATE_DISCONNEDTED);
			}
		}

		++Info;
	}

	outPacket.PacketLength = sizeof(PACKET_IZ_GROUP_LIST) + MemberCnt * sizeof(GROUPMEMBER_INFO);
	g_userMgr.CUserMgr::SendMsg(AID, outPacket.PacketLength, (char*)&outPacket);
}


void CParty::OnChat(unsigned long AID, int len, char* buf)
{
	PACKET_IZ_CHAT_PARTY outpacket;
	outpacket.PacketType = HEADER_IZ_CHAT_PARTY;
	outpacket.PacketLength = sizeof(outpacket) + len;
	outpacket.senderAID = AID;

	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			outpacket.receiverAID = member->AID;
			g_userMgr.CUserMgr::SendMsg(member->AID, sizeof(outpacket), (char*)&outpacket);
			g_userMgr.CUserMgr::SendMsg(member->AID, len, buf);
		}
	}
}


unsigned long CParty::GetGroupEXPOption()
{
	return m_groupInfo.expOption;
}


void CParty::UpdateExpOption(const unsigned long in_option, const bool in_bNotify)
{
	m_groupInfo.expOption = in_option;

	if( in_bNotify )
	{
		for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
		{
			CHARINFO_IN_GROUP* member = *iter;

			if( member->curState == GROUPMEMBER_STATE_CONNECTED )
				this->CParty::NotifyUpdateExpOption(member->AID, in_option);
		}
	}
}


void CParty::NotifyUpdateExpOption(unsigned long AID, unsigned long option)
{
	PACKET_ZI_GRID_UPDATE outpacket;
	outpacket.PacketType = HEADER_ZI_GRID_UPDATE;
	outpacket.AID = AID;
	outpacket.GRID = this->CParty::GetGroupID();
	outpacket.expOption = option;
	g_userMgr.CUserMgr::SendMsg(AID, sizeof(outpacket), (char*)&outpacket);
}


BOOL CParty::IsExpSharable() const
{
	int maxLevel = 0;
	int minLevel = 1000;

	for( MEMBER_CONTAINER::const_iterator iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
			if( user != NULL )
			{
				if( minLevel > user->level )
					minLevel = user->level;
				if( maxLevel < user->level )
					maxLevel = user->level;
			}
		}
	}

	return ( maxLevel - minLevel <= 15 );
}


void CParty::CheckExpSharableInfo()
{
	if( m_groupInfo.expOption == EXP_SHARED && !this->CParty::IsExpSharable() )
		this->CParty::UpdateExpOption(EXP_NOTSHARED, true);
}


BOOL CParty::IsDupeMember(unsigned long AID)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->AID == AID )
			return TRUE; // found.
	}

	return FALSE; // not found.
}


void CParty::ChangeGroupInfo(GROUP_INFO Info)
{
	m_groupInfo.expOption = Info.expOption;
	m_groupInfo.ItemPickupRule = Info.ItemPickupRule;
	m_groupInfo.ItemDivisionRule = Info.ItemDivisionRule;

	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			PACKET_IZ_REQ_GROUPINFO_CHANGE_V2 outpacket;
			outpacket.PacketType = HEADER_IZ_REQ_GROUPINFO_CHANGE_V2;
			outpacket.AID = member->AID;
			outpacket.GRID = this->CParty::GetGroupID();
			outpacket.expOption = Info.expOption;
			outpacket.ItemPickupRule = Info.ItemPickupRule;
			outpacket.ItemDivisionRule = Info.ItemDivisionRule;
			g_userMgr.CUserMgr::SendMsg(member->AID, sizeof(outpacket), (char*)&outpacket);
		}
	}
}


void CParty::OnChangeGroupMaster(unsigned long MasterAID, unsigned long AID)
{
	CHARINFO_IN_GROUP* MasterInfo = NULL;
	CHARINFO_IN_GROUP* NewMasterInfo = NULL;

	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->Role == GROUPMEMBER_ROLE_MASTER )
		{
			if( member->AID != MasterAID )
				return; // invalid input

			MasterInfo = member;
			break; // found current master.
		}
	}

	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->AID == AID )
		{
			NewMasterInfo = member;
			break; // found new master.
		}
	}

	if( MasterInfo == NULL || NewMasterInfo == NULL )
		return; // not online

	MasterInfo->Role = GROUPMEMBER_ROLE_GENERAL;
	NewMasterInfo->Role = GROUPMEMBER_ROLE_MASTER;
	CPartyDB::GetObj()->CPartyDB::UpdateMemberRole(this->CParty::GetGroupID(), MasterInfo->GID, MasterInfo->Role, NewMasterInfo->GID, NewMasterInfo->Role);

	PACKET_IZ_CHANGE_GROUP_MASTER outpacket;
	outpacket.PacketType = HEADER_IZ_CHANGE_GROUP_MASTER;
//	outpacket.receiverAID = ?; // filled in by Broadcast()
	outpacket.OldMasterAID = MasterAID;
	outpacket.NewMasterAID = AID;
	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


void CParty::GetPartyMemberOnlineList(std::list<unsigned long>& out_listGID)
{
	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
			if( user != NULL )
				out_listGID.push_back(user->GID);
		}
	}
}


void CParty::SendIZBroadcastEntryQueueApply(const int in_ZSID, const unsigned long in_AID, const unsigned long in_GID, const std::string in_EntryQueueName, const short in_ApplyType)
{
	CVarLenPacketPtr<PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY, 12*sizeof(ENTRY_QUEUE_APPLY_INFO)> packetPtr;
	packetPtr->PacketType = HEADER_IZ_NOTIFY_ENTRY_QUEUE_APPLY;
	packetPtr->AID = in_AID;
	packetPtr->GID = in_GID;
	strncpy_s(packetPtr->EntryQueueName, countof(packetPtr->EntryQueueName), in_EntryQueueName.c_str(), _TRUNCATE);
	packetPtr->ApplyType = in_ApplyType;

	for( MEMBER_CONTAINER_ITER iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
			if( user != NULL )
			{
				ENTRY_QUEUE_APPLY_INFO EntryQueueApply(user->AID, user->GID, user->characterName, user->job, user->level);
				packetPtr.add((BYTE*)&EntryQueueApply, sizeof(EntryQueueApply));
				CEntryQueueMgr::GetObj()->CEntryQueueMgr::AddApplicant(user->GID, user->AID, in_EntryQueueName);
			}
		}
	}

	if( packetPtr.size() <= sizeof(PACKET_IZ_NOTIFY_ENTRY_QUEUE_APPLY) )
		return; // zero entries.

	packetPtr->PacketLength = packetPtr.size();
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(in_ZSID, packetPtr->PacketLength, packetPtr);
}


bool CParty::IsBattleFieldMapLocation() const
{
	for( MEMBER_CONTAINER::const_iterator iter = m_users.begin(); iter != m_users.end(); ++iter )
	{
		CHARINFO_IN_GROUP* member = *iter;

		if( member->curState == GROUPMEMBER_STATE_CONNECTED )
		{
			USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
			if( user != NULL )
			{
				if( CEntryQueueMgr::GetObj()->CEntryQueueMgr::IsBattleFieldMap(user->mapName) == true )
					return true; // found.
			}
		}
	}

	return false; // not found.
}
