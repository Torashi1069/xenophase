#include "Party.h"
#include "PartyDB.h"
#include "PartyMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"


CPartyMgr::CPartyMgr()
{
	CPartyDB::CreateInstance();
	m_MaxPartyMemberNum = 12;
}


CPartyMgr::~CPartyMgr()
{
	CPartyDB::GetObj()->CODBC::Reset();
	CPartyDB::DestroyInstance();
}


void CPartyMgr::Init(int MaxParty, const char* FileDsn, const char* PASS)
{
	m_groupMPool.CMemoryMgr<CParty>::Init(MaxParty);
	CPartyDB::GetObj()->CODBC::Init(FileDsn, PASS);
}


const int CPartyMgr::GetMaxMemberNum()
{
	return m_MaxPartyMemberNum;
}


CParty* CPartyMgr::SearchGroup(unsigned long GRID)
{
	std::map<unsigned long,CParty*>::iterator iter = m_group.find(GRID);
	if( iter == m_group.end() )
		return NULL;

	return iter->second;
}


CParty* CPartyMgr::SearchGroup(const char* in_pPartyName)
{
	for( std::map<unsigned long,CParty*>::iterator iter = m_group.begin(); iter != m_group.end(); ++iter )
	{
		CParty* group = iter->second;

		if( strcmp(in_pPartyName, group->CParty::GetGroupName()) == 0 )
			return group; // found.
	}

	return NULL; // not found.
}


unsigned long CPartyMgr::MakeGroup(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name)
{
	name[23] = '\0';
	unsigned long result = CPartyDB::GetObj()->CPartyDB::MakeGroup(AID, GID, name);

	CParty* group = m_groupMPool.CMemoryMgr<CParty>::Alloc();
	if( group == NULL )
		return 1;

	if( result != GROUP_MAKE_SUCCEED )
	{
		m_groupMPool.CMemoryMgr<CParty>::Free(group);
		return result;
	}

	GRID = CPartyDB::GetObj()->CPartyDB::GetGroupID(name);
	if( GRID == 0 )
	{
		CPartyDB::GetObj()->CPartyDB::DeleteGroup(name);
		m_groupMPool.CMemoryMgr<CParty>::Free(group);
		return 1;
	}

	group->CParty::Init();
	group->CParty::SetGroupID(GRID);
	group->CParty::SetGroupName(name);
	m_group[GRID] = group;

	CHARINFO_IN_GROUP data;
	data.AID = AID;
	data.GID = GID;
	data.curState = 0;
	data.Role = 0;

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( user == NULL )
	{
		this->CPartyMgr::DeleteGroup(GRID);
		return 1;
	}

	user->GRID = GRID;
	memcpy(data.charName, user->characterName, 24);

	group->CParty::AddMember(&data, 1);
	CPartyDB::GetObj()->CPartyDB::InsertMember(GID, AID, GRID, data.charName, GROUPMEMBER_ROLE_MASTER);

	return 0;
}


unsigned long CPartyMgr::MakeGroup2(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name, bool bItemPickupRule, bool bItemDivisionRule)
{
	unsigned long result = CPartyDB::GetObj()->CPartyDB::MakeGroup(AID, GID, name, bItemPickupRule, bItemDivisionRule);

	CParty* group = m_groupMPool.CMemoryMgr<CParty>::Alloc();
	if( group == NULL )
		return 1;

	if( result != GROUP_MAKE_SUCCEED )
	{
		m_groupMPool.CMemoryMgr<CParty>::Free(group);
		return result;
	}

	GRID = CPartyDB::GetObj()->CPartyDB::GetGroupID(name);
	if( GRID == 0 )
	{
		CPartyDB::GetObj()->CPartyDB::DeleteGroup(name);
		m_groupMPool.CMemoryMgr<CParty>::Free(group);
		return 1;
	}

	group->CParty::Init();
	group->CParty::SetGroupID(GRID);
	group->CParty::SetGroupName(name);
	group->CParty::SetPartyRole(bItemPickupRule, bItemDivisionRule);
	m_group[GRID] = group;

	CHARINFO_IN_GROUP data;
	data.AID = AID;
	data.GID = GID;
	data.curState = 0;
	data.Role = 0;

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( user == NULL )
	{
		this->CPartyMgr::DeleteGroup(GRID);
		return 1;
	}

	user->GRID = GRID;
	memcpy(data.charName, user->characterName, 24);

	group->CParty::AddMember(&data, 1);
	CPartyDB::GetObj()->CPartyDB::InsertMember(GID, AID, GRID, data.charName, GROUPMEMBER_ROLE_MASTER);
	return 0;
}


void CPartyMgr::GetGroupName(unsigned long GRID, char* buf)
{
	CPartyDB::GetObj()->CPartyDB::GetGroupName(GRID, buf);
}


void CPartyMgr::GetGroupInfo(unsigned long GRID, char* buf, bool& ItemPickupRule, bool& ItemDivisionRule)
{
	CPartyDB::GetObj()->CPartyDB::GetGroupInfo(GRID, buf, ItemPickupRule, ItemDivisionRule);
}


BOOL CPartyMgr::DeleteGroup(unsigned long GRID)
{
	std::map<unsigned long,CParty*>::iterator iter = m_group.find(GRID);
	if( iter != m_group.end() )
	{
		m_groupMPool.CMemoryMgr<CParty>::Free(iter->second);
		m_group.erase(iter);
	}

	return CPartyDB::GetObj()->CPartyDB::DeleteGroup(GRID);
}


int CPartyMgr::InsertNewMember(unsigned long AID, unsigned long GRID)
{
	CParty* group = this->CPartyMgr::SearchGroup(GRID);
	if( group == NULL )
		return 1;

	if( group->CParty::GetMemberCount() >= m_MaxPartyMemberNum )
		return 3;

	if( group->CParty::IsDupeMember(AID) )
		return 4;

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, 0);
	if( user == NULL )
		return 1;

	CHARINFO_IN_GROUP info;
	info.AID = AID;
	info.GID = user->GID;
	info.Role = 1;
	memcpy(info.charName, user->characterName, 24);
	user->GRID = GRID;
	info.curState = 0;

	if( !group->CParty::AddMember(&info, 0) )
		return 1;

	if( !CPartyDB::GetObj()->CPartyDB::InsertMember(user->GID, AID, GRID, user->characterName, GROUPMEMBER_ROLE_GENERAL) )
		return 0;

	return 1;
}


CPartyMgr::enumResultINM CPartyMgr::InsertNewMemberV2(CParty* const in_cpGroup, const USER_STRING_MAP_DATA* in_pNewMemberData)
{
	if( in_cpGroup == NULL || in_pNewMemberData == NULL )
		return RESULTINM_UNKNOWN_ERROR;

	if( in_cpGroup->CParty::GetMemberCount() >= m_MaxPartyMemberNum )
		return RESULTINM_OVERSIZE_MEMBER;

	if( in_cpGroup->CParty::IsDupeMember(in_pNewMemberData->AID) )
		return RESULTINM_DUPLICATE_AID;

	CHARINFO_IN_GROUP info = {};
	info.AID = in_pNewMemberData->AID;
	info.GID = in_pNewMemberData->GID;
	info.Role = GROUPMEMBER_ROLE_GENERAL;
	memcpy(info.charName, in_pNewMemberData->characterName, 24);
	info.curState = 0;

	if( !in_cpGroup->CParty::AddMember(&info, 0) )
		return RESULTINM_UNKNOWN_ERROR;

	CPartyDB::GetObj()->CPartyDB::InsertMember(in_pNewMemberData->GID, in_pNewMemberData->AID, in_cpGroup->CParty::GetGroupID(), const_cast<char*>(in_pNewMemberData->characterName), GROUPMEMBER_ROLE_GENERAL);
	const_cast<USER_STRING_MAP_DATA*>(in_pNewMemberData)->GRID = in_cpGroup->CParty::GetGroupID();

	return RESULTINM_SUCCESS;
}


bool CPartyMgr::DeleteMember(const unsigned long in_PartyID, const USER_STRING_MAP_DATA* in_pUser, const unsigned long in_type)
{
	if( in_pUser == NULL )
		return false;

	if( in_PartyID != in_pUser->GRID )
		return false;

	CParty* group = this->CPartyMgr::SearchGroup(in_PartyID);
	if( group == NULL )
		return false;

	if( in_pUser->AID == group->CParty::GetMaster() )
	{
		if( in_type == GROUPMEMBER_DELETE_EXPEL )
			return false;
		
		if( CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::isSubscription(in_PartyID) == true )
			return false;
	}

	if( !CPartyDB::GetObj()->CPartyDB::DeleteMember(in_pUser->GID) )
		return false;

	group->CParty::UpdateExpOption(EXP_NOTSHARED, true);
	group->CParty::DeleteMember(in_pUser->AID, in_pUser->GID, static_cast<unsigned char>(in_type));
	CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::PartyLeave(in_PartyID, in_pUser->AID, in_pUser->GID);
	const_cast<USER_STRING_MAP_DATA*>(in_pUser)->GRID = 0;
	if( group->CParty::GetMemberCount() <= 0 )
	{
		this->CPartyMgr::DeleteGroup(in_PartyID);
		CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::PartyDestroy(in_PartyID);
	}

	return true;
}


unsigned long CPartyMgr::SearchMember(unsigned long GID)
{
	return CPartyDB::GetObj()->CPartyDB::SearchMember(GID);
}


unsigned long CPartyMgr::GetGroupOwner(unsigned long GRID)
{
    CParty* group = this->CPartyMgr::SearchGroup(GRID);
    if( group == NULL )
		return 0;

	return group->CParty::GetMaster();
}


void CPartyMgr::LogonNewUser(unsigned long AID, unsigned long GRID)
{
	CParty* group = this->CPartyMgr::SearchGroup(GRID);
	if( group != NULL )
	{
		this->CPartyMgr::NotifyGroupMembers(AID, GRID);
		group->CParty::UpdateState(AID, GROUPMEMBER_STATE_CONNECTED);
		group->CParty::CheckExpSharableInfo();
	}
	else
	{
		this->CPartyMgr::LoadGroupInfoFromDB(AID, GRID);
		this->CPartyMgr::NotifyGroupMembers(AID, GRID);
	}
}


void CPartyMgr::LoadGroupInfoFromDB(unsigned long AID, unsigned long GRID)
{
	DBGROUPINFO PartyDBInfoArray[CPartyMgr::MAX_PARTY_MEMBER_NUM];
	int memcount = CPartyDB::GetObj()->CPartyDB::GetGroupMembers(GRID, PartyDBInfoArray, countof(PartyDBInfoArray));

	char gname[24] = "unknown";
	bool ItemPickupRule = false;
	bool ItemDivisionRule = false;
	CPartyDB::GetObj()->CPartyDB::GetGroupInfo(GRID, gname, ItemPickupRule, ItemDivisionRule);

	CParty* group = m_groupMPool.CMemoryMgr<CParty>::Alloc();
	if( group == NULL )
		return;

	group->CParty::Init();
	group->CParty::SetGroupID(GRID);
	group->CParty::SetGroupName(gname);
	m_group[GRID] = group;
	group->CParty::SetPartyRole(true, false);

	for( int i = 0; i < memcount; ++i )
	{
		CHARINFO_IN_GROUP MemberInfo;
		MemberInfo.AID = PartyDBInfoArray[i].AID;
		MemberInfo.GID = PartyDBInfoArray[i].GID;
		MemberInfo.Role = static_cast<unsigned char>(PartyDBInfoArray[i].Role);
		MemberInfo.curState = GROUPMEMBER_STATE_DISCONNEDTED;
		memcpy(MemberInfo.charName, PartyDBInfoArray[i].name, 24);
		if( MemberInfo.AID == AID )
			MemberInfo.curState = GROUPMEMBER_STATE_CONNECTED;

		group->CParty::AddMember(&MemberInfo, 1);
	}
}


void CPartyMgr::UserExit(unsigned long AID, unsigned long GRID)
{
	CParty* group = this->CPartyMgr::SearchGroup(GRID);
	if( group == NULL )
		return;

	group->CParty::UpdateState(AID, GROUPMEMBER_STATE_DISCONNEDTED);
	group->CParty::CheckExpSharableInfo();

	if( group->CParty::GetConnectedMember() <= 0 )
		this->CPartyMgr::FreeGroup(GRID);
}


BOOL CPartyMgr::FreeGroup(unsigned long GRID)
{
	std::map<unsigned long,CParty*>::iterator iter = m_group.find(GRID);
	if( iter == m_group.end() )
		return FALSE;

	m_groupMPool.CMemoryMgr<CParty>::Free(iter->second);
	m_group.erase(iter);

	return TRUE;
}


void CPartyMgr::Send(const int in_HsvrID, const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)
{
	CParty* group = this->CPartyMgr::SearchGroup(in_GRID);
	if( group == NULL )
		return;

	group->CParty::Send(in_HsvrID, in_Length, in_pPartyBroadCastPacket);
}


void CPartyMgr::Send(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)
{
	CParty* group = this->CPartyMgr::SearchGroup(in_GRID);
	if( group == NULL )
		return;

	group->CParty::Send(in_Length, in_pPartyBroadCastPacket);
}


void CPartyMgr::Send(const int in_HsvrID, const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket)
{
	CParty* group = this->CPartyMgr::SearchGroup(in_GRID);
	if( group == NULL )
		return;

	group->CParty::Send(in_HsvrID, in_Length, in_pPartyBroadCastPacket);
}


void CPartyMgr::Send(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket)
{
	CParty* group = this->CPartyMgr::SearchGroup(in_GRID);
	if( group == NULL )
		return;

	group->CParty::Send(in_Length, in_pPartyBroadCastPacket);
}


void CPartyMgr::NotifyGroupMembers(unsigned long AID, unsigned long GRID)
{
	CParty* group = this->CPartyMgr::SearchGroup(GRID);
	if( group == NULL )
		return;

	group->CParty::NotifyGroupMembers(AID);
}


int CPartyMgr::GetGroupSize()
{
	return m_group.size();
}


unsigned long CPartyMgr::GetFreeSize()
{
	return m_groupMPool.CMemoryMgr<CParty>::GetFreeSize();
}


bool CPartyMgr::LeaveGroup(const unsigned long in_AID, const unsigned long in_GID)
{
	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(in_AID, in_GID);
	if( user == NULL )
		return false;

	return this->CPartyMgr::DeleteMember(user->GRID, user, GROUPMEMBER_DELETE_LEAVE);
}


void CPartyMgr::ExpelGroupMember(unsigned long AID, unsigned long GRID, char* name)
{
	CParty* group = this->CPartyMgr::SearchGroup(GRID);
	if( group == NULL )
		return;

	unsigned long GID = group->CParty::SearchGID(name);
	if( GID == 0 )
		return;

	USER_STRING_MAP_DATA* user = g_userMgr.CUserMgr::SearchUser(AID, GID);
	if( user != NULL )
	{
		this->CPartyMgr::DeleteMember(user->GRID, user, GROUPMEMBER_DELETE_EXPEL);
	}
	else
	{
		if( CPartyDB::GetObj()->CPartyDB::DeleteMemberByName(name) )
			group->CParty::DeleteMember(AID, GID, GROUPMEMBER_DELETE_EXPEL);
	}
}


void CPartyMgr::ServerMoveUser(unsigned long AID, unsigned long GRID, BOOL isOnline)
{
	CParty* group = this->CPartyMgr::SearchGroup(GRID);
	if( group == NULL )
		return;

	if( isOnline == TRUE )
	{
		group->CParty::UpdateState(AID, GROUPMEMBER_STATE_CONNECTED);
		group->CParty::CheckExpSharableInfo();
	}
	else
	{
		group->CParty::UpdateState(AID, GROUPMEMBER_STATE_DISCONNEDTED);
		group->CParty::CheckExpSharableInfo();
	}
}


void CPartyMgr::MapMove2(const unsigned long in_hPartyID, const unsigned long in_AID, const char* in_pMapName)
{
	CParty* group = this->CPartyMgr::SearchGroup(in_hPartyID);
	if( group == NULL )
		return;

	group->CParty::UpdateMapName2(in_AID, in_pMapName);
}
