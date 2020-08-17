#include "PartyMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "UserMgr.h"


hook_method<bool (CPartyMgr::*)(const unsigned long in_PartyID, const USER_STRING_MAP_DATA* in_pUser, const unsigned long in_type)> CPartyMgr::_DeleteMember(SERVER, "CPartyMgr::DeleteMember");
bool CPartyMgr::DeleteMember(const unsigned long in_PartyID, const USER_STRING_MAP_DATA* in_pUser, const unsigned long in_type) // line 230-261
{
	return (this->*_DeleteMember)(in_PartyID,in_pUser,in_type);

	if( in_pUser == NULL )
		return false; // invalid user argument

	if( in_pUser->GRID != in_PartyID )
		return false; // party mismatch

	CParty* party = this->CPartyMgr::SearchGroup(in_pUser->GRID);
	if( party == NULL )
		return false; // party not found

	if( party->CParty::GetMaster() == in_pUser->AID )
	{
		if( in_type == 1 )
			return false; // party owner can't be expeled (he has to leave by himself)
		if( CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::isSubscription(in_PartyID) )
			return false; // party owner can't leave party while it has a memorial dungeon instance
	}

	if( m_groupdb.CPartyDB::DeleteMember(in_pUser->AID) == 0 )
		return false; // failed to delete party member

	party->CParty::UpdateExpOption(0);
	party->CParty::DeleteMember(in_pUser->AID, in_pUser->GID, (unsigned char)in_type);
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::PartyLeave(in_PartyID, in_pUser->AID, in_pUser->GID);

	if( party->CParty::GetMemberCount() <= 0 )
	{
		this->CPartyMgr::DeleteGroup(in_PartyID);
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::PartyDestroy(in_PartyID);
	}
	return true; // done
}


hook_method<void (CPartyMgr::*)(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)> CPartyMgr::_Send(SERVER, "CPartyMgr::Send");
void CPartyMgr::Send(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket) // line 414-418
{
	return (this->*_Send)(in_GRID,in_Length,in_pPartyBroadCastPacket);

	CParty* party = CPartyMgr::SearchGroup(in_GRID);
	if( party != NULL )
		party->CParty::Send(in_Length, in_pPartyBroadCastPacket);
}


hook_method<void (CPartyMgr::*)(const unsigned long in_hPartyID, const unsigned long in_AID, const char* in_pMapName)> CPartyMgr::_MapMove2(SERVER, "CPartyMgr::MapMove2");
void CPartyMgr::MapMove2(const unsigned long in_hPartyID, const unsigned long in_AID, const char* in_pMapName) // line 517-526
{
	return (this->*_MapMove2)(in_hPartyID,in_AID,in_pMapName);

	CParty* party = CPartyMgr::SearchGroup(in_hPartyID);
	if( party != NULL )
		party->CParty::UpdateMapName2(in_AID, const_cast<char*>(in_pMapName));
}


hook_method<CParty* (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_SearchGroup(SERVER, "?SearchGroup@CPartyMgr@@QAEPAVCParty@@K@Z");
CParty* CPartyMgr::SearchGroup(unsigned long GRID) // line 35-41
{
	return (this->*_SearchGroup)(GRID);

	mystd::map<unsigned long,CParty*>::iterator it = m_group.find(GRID);
	if( it != m_group.end() )
		return it->second; // party found

	return NULL; // party not found
}


hook_method<CParty* (CPartyMgr::*)(const char* in_pPartyName)> CPartyMgr::_SearchGroup2(SERVER, "?SearchGroup@CPartyMgr@@QAEPAVCParty@@PBD@Z");
CParty* CPartyMgr::SearchGroup(const char* in_pPartyName) // line 45-51
{
	return (this->*_SearchGroup2)(in_pPartyName);

	for( mystd::map<unsigned long,CParty*>::iterator it = m_group.begin(); it != m_group.end(); ++it )
	{
		if( strcmp(it->second->CParty::GetGroupName(), in_pPartyName) == 0 )
			return it->second; // party found
	}

	return NULL; // party not found
}


CPartyMgr::CPartyMgr(void) // line 15-21
{
	m_MaxPartyMemberNum = 12;
}


CPartyMgr::~CPartyMgr(void) // line 24-26
{
	m_groupdb.CODBC::Reset();
}


hook_method<void (CPartyMgr::*)(int MaxParty, const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CPartyMgr::_Init(SERVER, "CPartyMgr::Init");
void CPartyMgr::Init(int MaxParty, const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type) // line 29-32
{
	return (this->*_Init)(MaxParty, DSN, UID, PASS, DB, type);

	m_groupMPool.CMemoryMgr<CParty>::Init(MaxParty);
	m_groupdb.CODBC::Init(DSN, UID, PASS, DB, type);
}

hook_method<const int (CPartyMgr::*)(void)> CPartyMgr::_GetMaxMemberNum(SERVER, "CPartyMgr::GetMaxMemberNum");
const int CPartyMgr::GetMaxMemberNum(void) // line 46 (PartyMgr.h)
{
	return (this->*_GetMaxMemberNum)();

	return m_MaxPartyMemberNum;
}


hook_method<unsigned long (CPartyMgr::*)(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name)> CPartyMgr::_MakeGroup(SERVER, "CPartyMgr::MakeGroup");
unsigned long CPartyMgr::MakeGroup(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name) // line 57-101
{
	return (this->*_MakeGroup)(AID,GID,GRID,name);

	name[23] = '\0'; // FIXME assumes the name buffer has a length of 24 or more
	unsigned long result = m_groupdb.CPartyDB::MakeGroup(AID, GID, name);

	CParty* party = m_groupMPool.CMemoryMgr<CParty>::Alloc();
	if( party == NULL )
		return 1; // out of pool memory

	if( result == 0 )
	{
		GRID = m_groupdb.CPartyDB::GetGroupID(name);
		if( GRID == 0 )
		{
			m_groupdb.CPartyDB::DeleteGroup(name);
			m_groupMPool.CMemoryMgr<CParty>::Free(party);
			return 1; // failed to get group id
		}

		party->CParty::Init();
		party->CParty::SetGroupID(GRID);
		party->CParty::SetGroupName(name);
		m_group[GRID] = party;

		CHARINFO_IN_GROUP data;
		data.AID = AID;
		data.GID = GID;
		data.curState = 0;
		data.Role = 0;

		USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, GID);
		if( user != NULL )
		{
			memcpy(data.charName, user->characterName, sizeof(data.charName));
			party->CParty::AddMember(&data, 1);
			m_groupdb.CPartyDB::InsertMember(GID, AID, GRID, data.charName, 0);
		}
		else
		{
			this->CPartyMgr::DeleteGroup(GRID);
			return 1; // user not found
		}
	}
	else
	{
		m_groupMPool.CMemoryMgr<CParty>::Free(party);
	}
	return result; // done (value from CPartyDB::MakeGroup)
}


hook_method<unsigned long (CPartyMgr::*)(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name, unsigned char bItemPickupRule, unsigned char bItemDivisionRule)> CPartyMgr::_MakeGroup2(SERVER, "CPartyMgr::MakeGroup2");
unsigned long CPartyMgr::MakeGroup2(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name, unsigned char bItemPickupRule, unsigned char bItemDivisionRule) // line 105-149
{
	return (this->*_MakeGroup2)(AID,GID,GRID,name,bItemPickupRule,bItemDivisionRule);

	unsigned long result = m_groupdb.CPartyDB::MakeGroup(AID, GID, name, bItemPickupRule, bItemDivisionRule);

	CParty* party = m_groupMPool.CMemoryMgr<CParty>::Alloc();
	if( party == NULL )
		return 1; // out of pool memory

	if( result == 0 )
	{
		GRID = m_groupdb.CPartyDB::GetGroupID(name);
		if( GRID == 0 )
		{
			m_groupdb.CPartyDB::DeleteGroup(name);
			m_groupMPool.CMemoryMgr<CParty>::Free(party);
			return 1; // failed to get group id
		}

		party->CParty::Init();
		party->CParty::SetGroupID(GRID);
		party->CParty::SetGroupName(name);
		party->CParty::SetPartyRole(bItemPickupRule, bItemDivisionRule);
		m_group[GRID] = party;

		CHARINFO_IN_GROUP data;
		data.AID = AID;
		data.GID = GID;
		data.curState = 0;
		data.Role = 0;

		USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, GID);
		if( user != NULL )
		{
			memcpy(data.charName, user->characterName, sizeof(data.charName));
			party->CParty::AddMember(&data, 1);
			m_groupdb.CPartyDB::InsertMember(GID, AID, GRID, data.charName, 0);
		}
		else
		{
			this->CPartyMgr::DeleteGroup(GRID);
			return 1; // user not found
		}
	}
	else
	{
		m_groupMPool.CMemoryMgr<CParty>::Free(party);
	}
	return result; // done (value from CPartyDB::MakeGroup)
}


hook_method<void (CPartyMgr::*)(unsigned long GRID, char* buf)> CPartyMgr::_GetGroupName(SERVER, "CPartyMgr::GetGroupName");
void CPartyMgr::GetGroupName(unsigned long GRID, char* buf) // line 152-153
{
	return (this->*_GetGroupName)(GRID,buf);

	m_groupdb.CPartyDB::GetGroupName(GRID, buf);
}


hook_method<void (CPartyMgr::*)(unsigned long GRID, char* buf, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule)> CPartyMgr::_GetGroupInfo(SERVER, "CPartyMgr::GetGroupInfo");
void CPartyMgr::GetGroupInfo(unsigned long GRID, char* buf, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule) // line 157-158
{
	return (this->*_GetGroupInfo)(GRID,buf,ItemPickupRule,ItemDivisionRule);

	m_groupdb.CPartyDB::GetGroupInfo(GRID, buf, ItemPickupRule, ItemDivisionRule);
}


hook_method<int (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_DeleteGroup(SERVER, "CPartyMgr::DeleteGroup");
int CPartyMgr::DeleteGroup(unsigned long GRID) // line 162-170
{
	return (this->*_DeleteGroup)(GRID);

	mystd::map<unsigned long,CParty*>::iterator it = m_group.find(GRID);
	if( it != m_group.end() )
	{
		m_groupMPool.CMemoryMgr<CParty>::Free(it->second);
		m_group.erase(it);
	}
	m_groupdb.CPartyDB::DeleteGroup(GRID);
}


hook_method<int (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_InsertNewMember(SERVER, "CPartyMgr::InsertNewMember");
int CPartyMgr::InsertNewMember(unsigned long AID, unsigned long GRID) // line 173-197
{
	return (this->*_InsertNewMember)(AID,GRID);

	CParty* party = this->CPartyMgr::SearchGroup(GRID);
	if( party == NULL )
		return 1; // party not found

	if( party->CParty::GetMemberCount() >= m_MaxPartyMemberNum )
		return 3; // party is full

	if( party->CParty::IsDupeMember(AID) != 0 )
		return 4; // member already exists

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, 0);
	if( user == NULL )
		return 1; // user not found

	CHARINFO_IN_GROUP info;
	info.GID = user->GID;
	memcpy(info.charName, user->characterName, sizeof(info.charName));
	info.AID = AID;
	info.Role = 1;
	user->GRID = GRID;
	info.curState = 0;

	if( party->CParty::AddMember(&info, 0) == 0 )
		return 1; // failed to add member to party

	return m_groupdb.CPartyDB::InsertMember(user->GID, AID, GRID, user->characterName, 1); // done (value from CPartyDB::InsertMember) // FIXME CPartyDB::InsertMember returns 1 on success, the same as some of our errors
}


hook_method<unsigned long (CPartyMgr::*)(unsigned long GID)> CPartyMgr::_SearchMember(SERVER, "CPartyMgr::SearchMember");
unsigned long CPartyMgr::SearchMember(unsigned long GID) // line 290-291
{
	return (this->*_SearchMember)(GID);

	return m_groupdb.CPartyDB::SearchMember(GID);
}


hook_method<unsigned long (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_GetGroupOwner(SERVER, "CPartyMgr::GetGroupOwner");
unsigned long CPartyMgr::GetGroupOwner(unsigned long GRID) // line 302
{
	return (this->*_GetGroupOwner)(GRID);

	CParty* party = this->CPartyMgr::SearchGroup(GRID);
	if( party == NULL )
		return 0; // party not found

	return party->CParty::GetMaster(); // owner found
}


hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_LogonNewUser(SERVER, "CPartyMgr::LogonNewUser");
void CPartyMgr::LogonNewUser(unsigned long AID, unsigned long GRID) // line 307-319
{
	return (this->*_LogonNewUser)(AID,GRID);

	CParty* party = this->CPartyMgr::SearchGroup(GRID);
	if( party != NULL )
	{
		this->CPartyMgr::NotifyGroupMembers(AID, GRID);
		party->CParty::UpdateState(AID, 0);
		party->CParty::CheckExpSharableInfo();
	}
	else
	{
		this->CPartyMgr::LoadGroupInfoFromDB(AID, GRID);
		this->CPartyMgr::NotifyGroupMembers(AID, GRID);
	}
}


hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_LoadGroupInfoFromDB(SERVER, "CPartyMgr::LoadGroupInfoFromDB");
void CPartyMgr::LoadGroupInfoFromDB(unsigned long AID, unsigned long GRID) // line 323-370
{
	return (this->*_LoadGroupInfoFromDB)(AID,GRID);

	DBGROUPINFO PartyDBInfoArray[CPartyMgr::MAX_PARTY_MEMBER_NUM];
	int count = m_groupdb.CPartyDB::GetGroupMembers(GRID, PartyDBInfoArray, CPartyMgr::MAX_PARTY_MEMBER_NUM);

	char gname[24]; memset(gname, 0, sizeof(gname));
	unsigned char ItemPickupRule = 0;
	unsigned char ItemDivisionRule = 0;
	strcpy(gname, "unknown");

	m_groupdb.CPartyDB::GetGroupInfo(GRID, gname, ItemPickupRule, ItemDivisionRule);

	CParty* party = m_groupMPool.CMemoryMgr<CParty>::Alloc();
	if( party == NULL )
		return; // out of pool memory

	party->CParty::Init();
	party->CParty::SetGroupID(GRID);
	party->CParty::SetGroupName(gname);
	m_group[GRID] = party;
	party->CParty::SetPartyRole(ItemPickupRule, ItemDivisionRule);

	for( DBGROUPINFO* p = PartyDBInfoArray; count != 0; ++p, --count )
	{
		CHARINFO_IN_GROUP MemberInfo;
		MemberInfo.GID = p->GID;
		MemberInfo.Role = static_cast<unsigned char>(p->Role);
		memcpy(MemberInfo.charName, p->name, sizeof(MemberInfo.charName));
		MemberInfo.AID = p->AID;
		MemberInfo.curState = 1;
		if( p->AID == AID )
			MemberInfo.curState = 0;
		party->CParty::AddMember(&MemberInfo, 1);
	}
}


hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_UserExit(SERVER, "CPartyMgr::UserExit");
void CPartyMgr::UserExit(unsigned long AID, unsigned long GRID) // line 375-384
{
	return (this->*_UserExit)(AID, GRID);

	CParty* party = CPartyMgr::SearchGroup(GRID);
	if( party == NULL )
		return; // party not found

	party->CParty::UpdateState(AID, 1);
	party->CParty::CheckExpSharableInfo();
	if( party->CParty::GetConnectedMember() <= 0 )
		this->CPartyMgr::FreeGroup(GRID);
}


hook_method<int (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_FreeGroup(SERVER, "CPartyMgr::FreeGroup");
int CPartyMgr::FreeGroup(unsigned long GRID) // line 401-410
{
	return (this->*_FreeGroup)(GRID);

	mystd::map<unsigned long,CParty*>::iterator it = m_group.find(GRID);
	if( it != m_group.end() )
	{
		m_groupMPool.CMemoryMgr<CParty>::Free(it->second);
		m_group.erase(it);
		return 1; // done
	}

	return 0; // party not found
}


hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_NotifyGroupMembers(SERVER, "CPartyMgr::NotifyGroupMembers");
void CPartyMgr::NotifyGroupMembers(unsigned long AID, unsigned long GRID) // line 423-430
{
	return (this->*_NotifyGroupMembers)(AID,GRID);

	CParty* party = this->CPartyMgr::SearchGroup(GRID);
	if( party != NULL )
		party->CParty::NotifyGroupMembers(AID);
}


hook_method<bool (CPartyMgr::*)(const unsigned long in_AID, const unsigned long in_GID)> CPartyMgr::_LeaveGroup(SERVER, "CPartyMgr::LeaveGroup");
bool CPartyMgr::LeaveGroup(const unsigned long in_AID, const unsigned long in_GID) // line 441-445
{
	return (this->*_LeaveGroup)(in_AID,in_GID);

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(in_AID, in_GID);
	if( user == NULL )
		return false; // user not found

	return this->CPartyMgr::DeleteMember(user->GRID, user, 0); // done (value from CPartyMgr::DeleteMember)
}


hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID, char* name)> CPartyMgr::_ExpelGroupMember(SERVER, "CPartyMgr::ExpelGroupMember");
void CPartyMgr::ExpelGroupMember(unsigned long AID, unsigned long GRID, char* name) // line 463-493
{
	return (this->*_ExpelGroupMember)(AID,GRID,name);

	CParty* party = this->CPartyMgr::SearchGroup(GRID);
	if( party == NULL )
		return; // party not found

	unsigned long GID = party->CParty::SearchGID(name);
	if( GID == 0 )
		return; // party member not found

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( user != NULL )
	{
		this->CPartyMgr::DeleteMember(GRID, user, 1);
	}
	else
	{
		if( m_groupdb.CPartyDB::DeleteMemberByName(name) != 0 )
			party->CParty::DeleteMember(AID, GID, 1);
	}
}


hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID, int isOnLine)> CPartyMgr::_ServerMoveUser(SERVER, "CPartyMgr::ServerMoveUser");
void CPartyMgr::ServerMoveUser(unsigned long AID, unsigned long GRID, int isOnLine) // line 387-398
{
	return (this->*_ServerMoveUser)(AID,GRID,isOnLine);

	CParty* party = CPartyMgr::SearchGroup(GRID);
	if( party == NULL )
		return; // party not found

	unsigned char state = ( isOnLine == 1 ) ? 0 : 1;
	party->CParty::UpdateState(AID, state);
	party->CParty::CheckExpSharableInfo();
}


hook_method<int (CPartyMgr::*)(void)> CPartyMgr::_GetGroupSize(SERVER, "CPartyMgr::GetGroupSize");
int CPartyMgr::GetGroupSize(void) // line 433-435
{
	return (this->*_GetGroupSize)();

	return m_group.size();
}


hook_method<unsigned long (CPartyMgr::*)(void)> CPartyMgr::_GetFreeSize(SERVER, "CPartyMgr::GetFreeSize");
unsigned long CPartyMgr::GetFreeSize(void) // line 74 (PartyMgr.h)
{
	return (this->*_GetFreeSize)();

	return m_groupMPool.CMemoryMgr<CParty>::GetFreeSize();
}


hook_method<enum CPartyMgr::enumResultINM (CPartyMgr::*)(CParty* const in_cpGroup, const USER_STRING_MAP_DATA* in_pNewMemberData)> CPartyMgr::_InsertNewMemberV2(SERVER, "CPartyMgr::InsertNewMemberV2");
enum CPartyMgr::enumResultINM CPartyMgr::InsertNewMemberV2(CParty* const in_cpGroup, const USER_STRING_MAP_DATA* in_pNewMemberData) // line 202-220
{
	return (this->*_InsertNewMemberV2)(in_cpGroup,in_pNewMemberData);

	if( in_cpGroup == NULL )
		return CPartyMgr::RESULTINM_UNKNOWN_ERROR; // invalid party argument

	if( in_pNewMemberData == NULL )
		return CPartyMgr::RESULTINM_UNKNOWN_ERROR; // invalid user argument

	if( in_cpGroup->CParty::GetMemberCount() >= CPartyMgr::MAX_PARTY_MEMBER_NUM )
		return CPartyMgr::RESULTINM_OVERSIZE_MEMBER; // party is full

	if( in_cpGroup->CParty::IsDupeMember(in_pNewMemberData->AID) != 0 )
		return CPartyMgr::RESULTINM_DUPLICATE_AID; // member already exists

	CHARINFO_IN_GROUP info;
	info.Role = 0;
	info.GID = 0;
	memset(info.charName, 0, sizeof(info.charName));

	info.AID = in_pNewMemberData->AID;
	memcpy(info.charName, in_pNewMemberData->characterName, sizeof(info.charName));
	info.GID = in_pNewMemberData->GID;
	info.Role = 1;
	info.curState = 0;
	if( in_cpGroup->CParty::AddMember(&info, 0) == 0 )
		return CPartyMgr::RESULTINM_UNKNOWN_ERROR; // failed to add member

	m_groupdb.CPartyDB::InsertMember(in_pNewMemberData->GID, in_pNewMemberData->AID, in_cpGroup->CParty::GetGroupID(), const_cast<char*>(in_pNewMemberData->characterName), 1);
	const_cast<USER_STRING_MAP_DATA*>(in_pNewMemberData)->GRID = in_cpGroup->CParty::GetGroupID();// FIXME: if it's going to be modified, then don't make it const to begin with...
	return CPartyMgr::RESULTINM_SUCCESS;
}


hook_method<class CPartyMgr* (__cdecl*)(void)> _InstanceCPartyMgr(SERVER, "InstanceCPartyMgr");
class CPartyMgr* __cdecl InstanceCPartyMgr(void) // line 99 (PartyMgr.h)
{
	return (_InstanceCPartyMgr)();

	return &g_groupMgr;
}
