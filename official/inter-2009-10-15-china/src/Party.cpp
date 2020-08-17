#include "Common/packet.h"
#include "PartyMgr.h"
#include "Party.h"
#include "UserMgr.h"
#include "globals.hpp"
#include "enums.hpp"


CParty::CParty(void) // line 11-13
{
	int maxMemberNum = InstanceCPartyMgr()->CPartyMgr::GetMaxMemberNum(); //inlined
	m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Init(maxMemberNum + 2);
}


CParty::~CParty(void) // line 16-17
{
}


hook_method<int (CParty::*)(unsigned long AID)> CParty::_IsDupeMember(SERVER, "CParty::IsDupeMember");
int CParty::IsDupeMember(unsigned long AID) // line 498-507
{
	return (this->*_IsDupeMember)(AID);

	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->AID == AID )
			return 1; // member found
	}
	return 0; // member not found
}


hook_method<void (CParty::*)(void)> CParty::_Init(SERVER, "CParty::Init");
void CParty::Init(void) // line 20-27
{
	return (this->*_Init)();

	m_groupName[0] = '\0';
	m_groupID = 0;
	m_groupInfo.expOption = 0;
	m_groupInfo.ItemPickupRule = 1;
	m_groupInfo.ItemDivisionRule = 0;
	this->CParty::DeleteAll();
}


hook_method<int (CParty::*)(void)> CParty::_GetMemberCount(SERVER, "CParty::GetMemberCount");
int CParty::GetMemberCount(void) // line 57-59
{
	return (this->*_GetMemberCount)();

	return m_users.size();
}


hook_method<int (CParty::*)(CHARINFO_IN_GROUP* par, int option)> CParty::_AddMember(SERVER, "CParty::AddMember");
int CParty::AddMember(CHARINFO_IN_GROUP* par, int option) // line 73-141
{
	return (this->*_AddMember)(par,option);

	CHARINFO_IN_GROUP* member = m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Alloc();

	if( this->CParty::SearchMember(par->AID) != NULL )
		CParty::DeleteMember(par->AID, par->GID, 0);

	if( member == NULL )
		return 0; // out of pool memory

	memcpy(member, par, sizeof(CHARINFO_IN_GROUP));
	m_users.push_back(member);

	PACKET_IZ_ADD_MEMBER_TO_GROUP2 outpacket;
	outpacket.state = par->curState;
	outpacket.Role = par->Role;
	outpacket.ItemPickupRule = m_groupInfo.ItemPickupRule;
	memcpy(outpacket.groupName, m_groupName, sizeof(outpacket.groupName));
	memcpy(outpacket.characterName, par->charName, sizeof(outpacket.characterName));
	outpacket.PacketType = HEADER_IZ_ADD_MEMBER_TO_GROUP2;

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(par->AID,par->GID);
	if( user != NULL )
		memcpy(outpacket.mapName, user->mapName, sizeof(outpacket.mapName));
	else
		outpacket.mapName[0] = '\0';

	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);
	this->CParty::CheckExpSharableInfo();
	return 1; // done
}


hook_method<int (CParty::*)(unsigned long AID, unsigned long GID, unsigned char type)> CParty::_DeleteMember(SERVER, "CParty::DeleteMember");
int CParty::DeleteMember(unsigned long AID, unsigned long GID, unsigned char type) // line 144-165
{
	return (this->*_DeleteMember)(AID,GID,type);

	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		CHARINFO_IN_GROUP* member = *it;
		if( member->AID != AID || member->GID != GID )
			continue; // not target member

		PACKET_IZ_DELETE_MEMBER_FROM_GROUP outpacket;
		outpacket.PacketType = HEADER_IZ_DELETE_MEMBER_FROM_GROUP;
		outpacket.AID = AID;
		memcpy(outpacket.characterName, member->charName, sizeof(outpacket.characterName));
		outpacket.result = type;

		this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);

		memset(member, 0, sizeof(CHARINFO_IN_GROUP));
		m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Free(member);
		m_users.erase(it);

		this->CParty::UpdateExpOption(0);
		return 1; // done
	}
	return 0; // member not found
}


hook_method<int (CParty::*)(unsigned long AID, unsigned char state)> CParty::_UpdateState(SERVER, "CParty::UpdateState");
int CParty::UpdateState(unsigned long AID, unsigned char state) // line 201-271
{
	return (this->*_UpdateState)(AID,state);

	CHARINFO_IN_GROUP* member = this->CParty::SearchMember(AID);
	if( member == NULL )
		return 0; // member not found

	PACKET_IZ_ADD_MEMBER_TO_GROUP2 outpacket;
	outpacket.Role = member->Role;
	member->curState = state;
	memcpy(outpacket.characterName, member->charName, sizeof(outpacket.characterName));
	memcpy(outpacket.groupName, m_groupName, sizeof(outpacket.groupName));
	outpacket.PacketType = HEADER_IZ_ADD_MEMBER_TO_GROUP2;
	outpacket.ItemPickupRule = m_groupInfo.ItemPickupRule;
	outpacket.AID = member->AID;
	outpacket.state = state;
	outpacket.ItemDivisionRule = m_groupInfo.ItemDivisionRule;

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
	if( user != NULL )
		memcpy(outpacket.mapName, user->mapName, sizeof(outpacket.mapName));
	else
		outpacket.mapName[0] = '\0';

	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);

	if( state == 0 )
		this->CParty::CheckExpSharableInfo();

	return 1; // done
}


hook_method<void (CParty::*)(unsigned long GRID)> CParty::_SetGroupID(SERVER, "CParty::SetGroupID");
void CParty::SetGroupID(unsigned long GRID) // line 31-33
{
	return (this->*_SetGroupID)(GRID);

	m_groupID = GRID;
}


hook_method<unsigned long (CParty::*)(void)> CParty::_GetGroupID(SERVER, "CParty::GetGroupID");
unsigned long CParty::GetGroupID(void) // line 36-38
{
	return (this->*_GetGroupID)();

	return m_groupID;
}


hook_method<void (CParty::*)(const char* gname)> CParty::_SetGroupName(SERVER, "CParty::SetGroupName");
void CParty::SetGroupName(const char* gname) // line 41-43
{
	return (this->*_SetGroupName)(gname);

	memcpy(m_groupName, gname, sizeof(m_groupName));
}


hook_method<char* (CParty::*)(void)> CParty::_GetGroupName(SERVER, "CParty::GetGroupName");
char* CParty::GetGroupName(void) // line 46-48
{
	return (this->*_GetGroupName)();

	return m_groupName;
}


hook_method<void (CParty::*)(unsigned char ItemPickupRule, unsigned char ItemDivisionRule)> CParty::_SetPartyRole(SERVER, "CParty::SetPartyRole");
void CParty::SetPartyRole(unsigned char ItemPickupRule, unsigned char ItemDivisionRule) // line 51-54
{
	return (this->*_SetPartyRole)(ItemPickupRule,ItemDivisionRule);

	m_groupInfo.ItemPickupRule = ItemPickupRule;
	m_groupInfo.ItemDivisionRule = ItemDivisionRule;
}


hook_method<unsigned long (CParty::*)(char* name)> CParty::_SearchGID(SERVER, "?SearchGID@CParty@@QAEKPAD@Z");
unsigned long CParty::SearchGID(char* name) // line 190-198
{
	return (this->*_SearchGID)(name);
	
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( strcmp((*it)->charName, name) == 0 )
			return (*it)->GID; // member found
	}
	return 0; // member not found
}


hook_method<unsigned long (CParty::*)(unsigned long AID)> CParty::_SearchGID2(SERVER, "?SearchGID@CParty@@QAEKK@Z");
unsigned long CParty::SearchGID(unsigned long AID) // line 179-187
{
	return (this->*_SearchGID2)(AID);
	
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->AID == AID )
			return (*it)->GID; // member found
	}
	return 0; // member not found
}


hook_method<unsigned long (CParty::*)(void)> CParty::_GetMaster(SERVER, "CParty::GetMaster");
unsigned long CParty::GetMaster(void) // line 62-70
{
	return (this->*_GetMaster)();
	
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->Role == 0 )
			return (*it)->AID; // member found
	}
	return 0; // member not found
}


hook_method<CHARINFO_IN_GROUP* (CParty::*)(unsigned long AID)> CParty::_GetGroupInfo(SERVER, "CParty::GetGroupInfo");
CHARINFO_IN_GROUP* CParty::GetGroupInfo(unsigned long AID) // line 354-362
{
	return (this->*_GetGroupInfo)(AID);
	
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->AID == AID )
			return *it; // member found
	}
	return NULL; // member not found
}


hook_method<int (CParty::*)(void)> CParty::_GetConnectedMember(SERVER, "CParty::GetConnectedMember");
int CParty::GetConnectedMember(void) // line 365-374
{
	return (this->*_GetConnectedMember)();

	int count = 0;
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->curState == 0 )
			++count; // member is connected
	}
	return count;
}


hook_method<void (CParty::*)(unsigned long AID)> CParty::_NotifyGroupMembers(SERVER, "CParty::NotifyGroupMembers");
void CParty::NotifyGroupMembers(unsigned long AID) // line 378-415
{
	return (this->*_NotifyGroupMembers)(AID);

	unsigned char PacketBuffer[sizeof(PACKET_IZ_GROUP_LIST) + sizeof(GROUPMEMBER_INFO) * CPartyMgr::MAX_PARTY_MEMBER_NUM];
	PACKET_IZ_GROUP_LIST* outpacket = (PACKET_IZ_GROUP_LIST*)PacketBuffer;

	outpacket->PacketType = HEADER_IZ_GROUP_LIST;
	outpacket->AID = AID;
	outpacket->expOption = m_groupInfo.expOption;
	memcpy(outpacket->groupName, m_groupName, sizeof(outpacket->groupName));

	Trace("NotifyGroupMembers\n");
	int count = 0;
	GROUPMEMBER_INFO* outmember = outpacket->Member;
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( count >= CPartyMgr::MAX_PARTY_MEMBER_NUM )
			break; // no more members supported

		CHARINFO_IN_GROUP* member = *it;
		outmember->AID = AID;
		memcpy(outmember->characterName, member->charName, sizeof(outmember->characterName));
//		memset(outmember->mapName, '\0', sizeof(outmember->mapName)); //FIXME: uninitialized on some control paths
		outmember->role = member->Role;
		outmember->state = member->curState;
		if( member->curState == 0 )
		{
			USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
			if( user != NULL )
			{
				memcpy(outmember->mapName, user->mapName, sizeof(outmember->mapName));
			}
			else
			{
				outmember->state = 1;
				this->CParty::UpdateState(AID, 1);
			}
		}

		++count;
		++outmember;
	}
	outpacket->PacketLength = sizeof(PACKET_IZ_GROUP_LIST) + sizeof(GROUPMEMBER_INFO) * count;

	g_userMgr.CUserMgr::SendMsg(AID, outpacket->PacketLength, (char*)outpacket);
}


hook_method<void (CParty::*)(unsigned long AID, char* mapName)> CParty::_UpdateMapName(SERVER, "CParty::UpdateMapName");
void CParty::UpdateMapName(unsigned long AID, char* mapName) // line 274-292
{
	return (this->*_UpdateMapName)(AID,mapName);

	CHARINFO_IN_GROUP* member = this->CParty::SearchMember(AID);
	if( member == NULL )
		return; // member not found

	PACKET_IZ_ADD_MEMBER_TO_GROUP outpacket;
	outpacket.PacketType = HEADER_IZ_ADD_MEMBER_TO_GROUP;
	outpacket.state = member->curState;
	outpacket.AID = member->AID;
	outpacket.Role = member->Role;
	memcpy(outpacket.characterName, member->charName, sizeof(outpacket.characterName));
	memcpy(outpacket.groupName, m_groupName, sizeof(outpacket.groupName));
	memcpy(outpacket.mapName, mapName, sizeof(outpacket.mapName));

	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


hook_method<void (CParty::*)(unsigned long AID, char* mapName)> CParty::_UpdateMapName2(SERVER, "CParty::UpdateMapName2");
void CParty::UpdateMapName2(unsigned long AID, char* mapName) // line 295-315
{
	return (this->*_UpdateMapName2)(AID,mapName);

	CHARINFO_IN_GROUP* member = this->CParty::SearchMember(AID);
	if( member == NULL )
		return; // member not found

	PACKET_IZ_ADD_MEMBER_TO_GROUP2 outpacket;
	outpacket.PacketType = HEADER_IZ_ADD_MEMBER_TO_GROUP2;
	outpacket.state = member->curState;
	outpacket.AID = member->AID;
	outpacket.ItemPickupRule = m_groupInfo.ItemPickupRule;
	outpacket.Role = member->Role;
	outpacket.ItemDivisionRule = m_groupInfo.ItemDivisionRule;
	memcpy(outpacket.characterName, member->charName, sizeof(outpacket.characterName));
	memcpy(outpacket.groupName, m_groupName, sizeof(outpacket.groupName));
	memcpy(outpacket.mapName, mapName, sizeof(outpacket.mapName));

	this->CParty::BroadCast(sizeof(outpacket), (char*)&outpacket);
}


hook_method<void (CParty::*)(unsigned long AID, int len, char* buf)> CParty::_OnChat(SERVER, "CParty::OnChat");
void CParty::OnChat(unsigned long AID, int len, char* buf) // line 420-435
{
	return (this->*_OnChat)(AID,len,buf);

	PACKET_IZ_CHAT_PARTY outpacket;
	outpacket.PacketType = HEADER_IZ_CHAT_PARTY;
	outpacket.PacketLength = sizeof(outpacket) + len;
	outpacket.senderAID = AID;
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		CHARINFO_IN_GROUP* member = *it;

		if( member->curState != 0 )
			continue; // member not connected

		outpacket.receiverAID = member->AID;

		g_userMgr.CUserMgr::SendMsg(member->AID, sizeof(outpacket), (char*)&outpacket);
		g_userMgr.CUserMgr::SendMsg(member->AID, len, buf);
	}
}


hook_method<unsigned long (CParty::*)(void)> CParty::_GetGroupEXPOption(SERVER, "CParty::GetGroupEXPOption");
unsigned long CParty::GetGroupEXPOption(void) // line 438-440
{
	return (this->*_GetGroupEXPOption)();

	return m_groupInfo.expOption;
}


hook_method<void (CParty::*)(unsigned long option)> CParty::_UpdateExpOption(SERVER, "CParty::UpdateExpOption");
void CParty::UpdateExpOption(unsigned long option) // line 443-455
{
	return (this->*_UpdateExpOption)(option);

	m_groupInfo.expOption = option;

	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		CHARINFO_IN_GROUP* member = *it;

		if( member->curState != 0 )
			continue; // member not connected

		Trace("PACKET_ZI_GRID_UPDATE3\n");
		this->CParty::NotifyUpdateExpOption(member->AID, option);
	}
}


hook_method<int (CParty::*)(void)> CParty::_IsExpSharable(SERVER, "CParty::IsExpSharable");
int CParty::IsExpSharable(void) // line 468-488
{
	return (this->*_IsExpSharable)();

	int maxLevel = 0;
	int minLevel = 1000;
	
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		CHARINFO_IN_GROUP* member = *it;

		if( member->curState != 0 )
			continue; // member not connected

		USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(member->AID, member->GID);
		if( user == NULL )
			continue; // user not found

		if( minLevel > user->level )
			minLevel = user->level;
		if( maxLevel < user->level )
			maxLevel = user->level;
	}

	Trace("IsExpSharable:max:%d, min:%d\n", maxLevel, minLevel);
	return ( (maxLevel - minLevel) <= 10 );
}


hook_method<void (CParty::*)(unsigned long AID, unsigned long option)> CParty::_NotifyUpdateExpOption(SERVER, "CParty::NotifyUpdateExpOption");
void CParty::NotifyUpdateExpOption(unsigned long AID, unsigned long option) // line 458-465
{
	return (this->*_NotifyUpdateExpOption)(AID,option);

	PACKET_ZI_GRID_UPDATE outpacket;
	outpacket.PacketType = HEADER_ZI_GRID_UPDATE;
	outpacket.AID = AID;
	outpacket.GRID = this->CParty::GetGroupID();
	outpacket.expOption = option;

	g_userMgr.CUserMgr::SendMsg(AID, sizeof(outpacket), (char*)&outpacket);
}


hook_method<void (CParty::*)(void)> CParty::_CheckExpSharableInfo(SERVER, "CParty::CheckExpSharableInfo");
void CParty::CheckExpSharableInfo(void) // line 491-495
{
	return (this->*_CheckExpSharableInfo)();

	if( m_groupInfo.expOption != 1 )
		return; // not sharing exp

	if( this->CParty::IsExpSharable() )
		return; // can continue sharing exp

	// auto-stop sharing exp
	this->CParty::UpdateExpOption(0);
}


hook_method<void (CParty::*)(GROUP_INFO Info)> CParty::_ChangeGroupInfo(SERVER, "CParty::ChangeGroupInfo");
void CParty::ChangeGroupInfo(GROUP_INFO Info) // line 510-532
{
	return (this->*_ChangeGroupInfo)(Info);

	m_groupInfo = Info;
	
	PACKET_IZ_REQ_GROUPINFO_CHANGE_V2 outpacket;

	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		CHARINFO_IN_GROUP* member = *it;

		if( member->curState != 0 )
			continue; // member not connected

		outpacket.PacketType = HEADER_IZ_REQ_GROUPINFO_CHANGE_V2;
		outpacket.AID = member->AID;
		outpacket.GRID = this->CParty::GetGroupID();
		outpacket.expOption = Info.expOption;
		outpacket.ItemPickupRule = Info.ItemPickupRule;
		outpacket.ItemDivisionRule = Info.ItemDivisionRule;

		g_userMgr.CUserMgr::SendMsg(member->AID, sizeof(outpacket), (char*)&outpacket);
	}

	// FIXME: first field name copy-paste typo; prints garbage if outpacket is left uninitialized
	Trace("ChangeGroupInfo:expOption:%d, expOption:%d, ItemPickupRule:%d, ItemDivisionRule:%d\n", outpacket.GRID, outpacket.expOption, outpacket.ItemPickupRule, outpacket.ItemDivisionRule);
}


hook_method<void (CParty::*)(unsigned long MasterAID, unsigned long AID)> CParty::_OnChangeGroupMaster(SERVER, "CParty::OnChangeGroupMaster");
void CParty::OnChangeGroupMaster(unsigned long MasterAID, unsigned long AID) // line 534-573
{
	return (this->*_OnChangeGroupMaster)(MasterAID,AID);

	CHARINFO_IN_GROUP* prevMaster = NULL;
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->Role != 0 )
			continue; // not the master

		if( (*it)->AID != MasterAID )
		{
			Trace("OnChangeGroupMaster : Not Master\n");
			return; // master mismatch
		}

		prevMaster = *it;
		break; // master found
	}

	CHARINFO_IN_GROUP* nextMaster = NULL;
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->AID != AID )
			continue; // not target member

		nextMaster = *it;
		break; // member found
	}

	if( prevMaster != NULL && nextMaster != NULL )
	{
		prevMaster->Role = 1;
		nextMaster->Role = 0;

		USER_STRING_MAP_DATA* prevUser = g_userMgr.CUserMgr::SearchUser(prevMaster->AID, prevMaster->GID);
		if( prevUser == NULL )
			return; // previous user not found

		this->CParty::UpdateMapName2(prevMaster->AID, prevUser->mapName);

		USER_STRING_MAP_DATA* nextUser = g_userMgr.CUserMgr::SearchUser(nextMaster->AID, nextMaster->GID);
		if( nextUser == NULL )
			return; // next user not found

		this->CParty::UpdateMapName2(nextMaster->AID, nextUser->mapName);
	}

	Trace("OnChangeGroupMaster : Change \n");
}


hook_method<void (CParty::*)(const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)> CParty::_Send(SERVER, "CParty::Send");
void CParty::Send(const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket) //line 329-338
{
	return (this->*_Send)(in_Length,in_pPartyBroadCastPacket);

	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		CHARINFO_IN_GROUP* member = *it;

		if( member->curState != 0 )
			continue; // member not connected

		in_pPartyBroadCastPacket->AID = member->AID;
		in_pPartyBroadCastPacket->GID = member->GID;

		g_userMgr.CUserMgr::SendMsg(member->AID, in_Length, (char*)in_pPartyBroadCastPacket);
	}
}


hook_method<void (CParty::*)(void)> CParty::_DeleteAll(SERVER, "CParty::DeleteAll");
void CParty::DeleteAll(void) // line 318-325
{
	return (this->*_DeleteAll)();

	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); )
	{
		CHARINFO_IN_GROUP* member = *it;

		memset(member, 0, sizeof(CHARINFO_IN_GROUP));
		m_userMPool.CMemoryMgr<CHARINFO_IN_GROUP>::Free(member);
		m_users.erase(it); //FIXME: the most inefficient way possible; missing iterator refresh after invalidation
	}
}


hook_method<void (CParty::*)(int len, char* buf)> CParty::_BroadCast(SERVER, "CParty::BroadCast");
void CParty::BroadCast(int len, char* buf) // line 342-351
{
	return (this->*_BroadCast)(len,buf);

	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		CHARINFO_IN_GROUP* member = *it;

		if( member->curState != 0 )
			continue; // member not connected

		PACKET_IZ_ADD_MEMBER_TO_GROUP* temp = (PACKET_IZ_ADD_MEMBER_TO_GROUP*)buf; //NOTE: unsafe placeholder typecast
		temp->receiverAID = member->AID;

		g_userMgr.CUserMgr::SendMsg(member->AID, len, buf);
	}
}


hook_method<CHARINFO_IN_GROUP* (CParty::*)(unsigned long AID)> CParty::_SearchMember(SERVER, "CParty::SearchMember");
CHARINFO_IN_GROUP* CParty::SearchMember(unsigned long AID) // line 168-176
{
	return (this->*_SearchMember)(AID);
	
	for( mystd::vector<CHARINFO_IN_GROUP*>::iterator it = m_users.begin(); it != m_users.end(); ++it )
	{
		if( (*it)->AID == AID )
			return *it; // member found
	}
	return NULL; // member not found
}
