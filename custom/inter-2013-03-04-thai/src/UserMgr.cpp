#include "IGuildMgr.h"
#include "PartyMgr.h"
#include "UserMgr.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/NCriticalErrorLog.h"


/// locals
static int& g_maxConnectClient = VTOR<int>(DetourFindFunction(EXEPATH(), "g_maxConnectClient"));


CUserMgr::CUserMgr()
{
	m_ServerMoveUserPool.CMemoryMgr<SERVER_MOVE_USER>::Init(3000);
	m_ServerMoveUser.clear();
}


CUserMgr::~CUserMgr()
{
}


void CUserMgr::Init(int MaxCharacterCount)
{
	if( !m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::Init(MaxCharacterCount) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Error m_userData.Init");
		MessageBoxA(NULL, "Error CUserMgr", "Error", MB_OK);
	}
}


USER_STRING_MAP_DATA* CUserMgr::AllocUser()
{
	return m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::Alloc();
}


void CUserMgr::FreeUser(USER_STRING_MAP_DATA* data)
{
	m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::Free(data);
}


unsigned long CUserMgr::GetFreeSize()
{
	return m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::GetFreeSize();
}


void CUserMgr::DeleteUsers(unsigned long ServerID)
{
	for( std::map<std::string,USER_STRING_MAP_DATA*>::iterator iter = m_userStringMap.begin(); iter != m_userStringMap.end(); )
	{
		USER_STRING_MAP_DATA* pUser = iter->second;

		if( pUser->ServerID == ServerID )
		{
			this->CUserMgr::FreeUser(pUser);
			g_groupMgr.CPartyMgr::UserExit(pUser->AID, pUser->GRID);

			iter = m_userStringMap.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	m_userAIDMap.clear();
}


BOOL CUserMgr::AddUser(unsigned long ServerID, USER_STRING_MAP_DATA* pUser)
{
	std::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(pUser->AID);
	if( iter != m_userAIDMap.end() )
	{
		PACKET_IZ_DISCONNECT_CHARACTER outpacket;
		outpacket.PacketType = HEADER_IZ_DISCONNECT_CHARACTER;
		outpacket.AID = pUser->AID;
		CZsvrMgr::GetObj()->CZServerMgr::BroadCast(sizeof(outpacket), (char*)&outpacket);

		USER_STRING_MAP_DATA* pUserReal = iter->second;
		this->CUserMgr::DeleteUser(pUserReal->ServerID, pUserReal->characterName);

		return FALSE;
	}

	USER_STRING_MAP_DATA* pNewUser = this->CUserMgr::AllocUser();
	if( pNewUser == NULL )
	{
		PACKET_IZ_DISCONNECT_CHARACTER outpacket;
		outpacket.PacketType = HEADER_IZ_DISCONNECT_CHARACTER;
		outpacket.AID = pUser->AID;
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ServerID, sizeof(outpacket), (char*)&outpacket);

		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CUserMgr::AddUser() -> AllocUser");
		return FALSE;
	}

	memcpy(pNewUser, pUser, sizeof(USER_STRING_MAP_DATA));
	m_userStringMap[pUser->characterName] = pNewUser;
	m_userAIDMap[pUser->AID] = pNewUser;

	CIGuildMgr::GetObj()->CIGuildMgr::LogonUser(ServerID, pNewUser->GID, pNewUser->AID);

	PACKET_IZ_ACK_LOGON AckLogon;
	AckLogon.PacketType = HEADER_IZ_ACK_LOGON;
	AckLogon.Type = 0;
	AckLogon.AID = pUser->AID;
	AckLogon.GID = pUser->GID;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ServerID, sizeof(AckLogon), (char*)&AckLogon);

	int nUserCount = this->CUserMgr::GetUserCount();
	if( g_maxConnectClient < nUserCount )
		g_maxConnectClient = nUserCount;

	unsigned long GRID = g_groupMgr.CPartyMgr::SearchMember(pUser->GID);
	if( GRID != 0 )
	{
		g_groupMgr.CPartyMgr::LogonNewUser(pUser->AID, GRID);

		CParty* group = g_groupMgr.CPartyMgr::SearchGroup(GRID);
		if( group != NULL )
			group->CParty::NotifyUpdateExpOption(pNewUser->AID, group->CParty::GetGroupEXPOption());

		pNewUser->GRID = GRID;
	}

	pNewUser->FriendNumber = 0;
	pNewUser->FriendNumber = g_FriendDB.CFriendDB::LoadFriend(pNewUser->GID, pNewUser->Friends);

	if( pNewUser->FriendNumber > 0 )
	{
		this->CUserMgr::SendFriendList(pNewUser->ServerID, pNewUser->AID, pNewUser->Friends, pNewUser->FriendNumber);

		for( int i = 0; i < pNewUser->FriendNumber; ++i )
		{
			USER_STRING_MAP_DATA* pFriend = this->CUserMgr::SearchUser(pNewUser->Friends[i].AID, pNewUser->Friends[i].GID);
			if( pFriend == NULL )
				continue;

			this->CUserMgr::SendFriendState(pNewUser->ServerID, pNewUser->AID, pFriend->AID, pFriend->GID, false);
			this->CUserMgr::SendFriendState(pFriend->ServerID, pFriend->AID, pNewUser->AID, pNewUser->GID, false);
		}
	}

	return TRUE;
}


void CUserMgr::DeleteUser(unsigned long ServerID, const char* name)
{
	unsigned long AID, GID, GRID;

	std::map<std::string,USER_STRING_MAP_DATA*>::iterator iter = m_userStringMap.find(name);
	if( iter != m_userStringMap.end() )
	{
		USER_STRING_MAP_DATA* pUser = iter->second;
		if( pUser == NULL || pUser->ServerID != ServerID )
			return;

		for( int i = 0; i < pUser->FriendNumber; ++i )
		{
			USER_STRING_MAP_DATA* pFriend = this->CUserMgr::SearchUser(pUser->Friends[i].AID, pUser->Friends[i].GID);
			if( pFriend == NULL )
				continue;

			this->CUserMgr::SendFriendState(pFriend->ServerID, pFriend->AID, pUser->AID, pUser->GID, 1);
		}

		AID = pUser->AID;
		GID = pUser->GID;
		GRID = pUser->GRID;

		CIGuildMgr::GetObj()->CIGuildMgr::ExitUser(ServerID, AID, GID);

		this->CUserMgr::FreeUser(pUser);
		m_userStringMap.erase(iter);
		g_groupMgr.CPartyMgr::UserExit(AID, GRID);
	}

	std::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter2 = m_userAIDMap.find(AID); //FIXME: variable potentially uninitialized
	if( iter2 != m_userAIDMap.end() )
		m_userAIDMap.erase(iter2);
}


unsigned long CUserMgr::SearchUserServerID(const char* name, unsigned long& AID)
{
	std::map<std::string,USER_STRING_MAP_DATA*>::iterator iter = m_userStringMap.find(name);
	if( iter == m_userStringMap.end() )
		return -1;

	AID = iter->second->AID;
	return iter->second->ServerID;
}


unsigned long CUserMgr::SearchUserServerID(unsigned long AID)
{
	std::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(AID);
	if( iter == m_userAIDMap.end() )
		return 0;

	return iter->second->ServerID;
}


unsigned long CUserMgr::SearchUserServerID(const unsigned long in_GID, const unsigned long in_AID)
{
	std::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(in_AID);
	if( iter == m_userAIDMap.end() )
		return 0;

	if( iter->second->GID != in_GID )
		return 0;
	
	return iter->second->ServerID;
}


int CUserMgr::GetUserCount()
{
	return m_userStringMap.size();
}


void CUserMgr::SendMsg(const int in_HsvrID, const unsigned long in_AID, const int in_Length, const char* in_pBuffer)
{
	int ZsvrID = this->CUserMgr::SearchUserServerID(in_AID);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(in_HsvrID, ZsvrID, in_Length, in_pBuffer);
}


void CUserMgr::SendMsg(unsigned long receiverAID, short len, char* buf)
{
	int ZsvrID = this->CUserMgr::SearchUserServerID(receiverAID);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZsvrID, len, buf);
}


USER_STRING_MAP_DATA* CUserMgr::SearchUser(unsigned long AID, unsigned long GID)
{
	std::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(AID);
	if( iter == m_userAIDMap.end() )
		return NULL;

	USER_STRING_MAP_DATA* pUser = iter->second;
	if( GID == 0 || (pUser != NULL && pUser->GID == GID) )
		return pUser;
	else
		return NULL;
}


USER_STRING_MAP_DATA* CUserMgr::SearchUserByAccount(char* Name, unsigned long GID)
{
	for( std::map<std::string,USER_STRING_MAP_DATA*>::iterator iter = m_userStringMap.begin(); iter != m_userStringMap.end(); ++iter )
	{
		USER_STRING_MAP_DATA* pUser = iter->second;

		if( strcmp(pUser->accountName, Name) == 0 )
		{
			if( GID == 0 || (pUser != NULL && pUser->GID == GID) )
				return pUser; // found.
			else
				return NULL; // mismatch.
		}
	}

	return NULL; // not found.
}


USER_STRING_MAP_DATA* CUserMgr::SearchUserByName(const char* Name, unsigned long GID)
{
	std::map<std::string,USER_STRING_MAP_DATA*>::iterator iter = m_userStringMap.find(Name);
	if( iter == m_userStringMap.end() )
		return NULL;

	USER_STRING_MAP_DATA* pUser = iter->second;
	if( GID == 0 || (pUser != NULL && pUser->GID == GID) )
		return pUser;
	else
		return NULL;
}


unsigned long CUserMgr::GetUserGRID(unsigned long AID)
{
	std::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(AID);
	if( iter == m_userAIDMap.end() )
		return 0;

	USER_STRING_MAP_DATA* pUser = iter->second;
	return pUser->GRID;
}


void CUserMgr::DeleteFriend(unsigned long AID, unsigned long FriendAID, unsigned long FriendGID)
{
	USER_STRING_MAP_DATA* pUser = this->CUserMgr::SearchUser(AID, 0);
	USER_STRING_MAP_DATA* pFriend = this->CUserMgr::SearchUser(FriendAID, FriendGID);
	if( pUser == NULL )
		return;

	this->CUserMgr::DeleteFriendList(FriendAID, FriendGID, pUser->Friends, pUser->FriendNumber);
	g_FriendDB.CFriendDB::SaveFriend(pUser->GID, pUser->Friends, pUser->FriendNumber);
	this->CUserMgr::SendDeleteFriend(pUser->ServerID, pUser->AID, FriendAID, FriendGID);

	if( pFriend != NULL )
	{
		this->CUserMgr::DeleteFriendList(pUser->AID, pUser->GID, pFriend->Friends, pFriend->FriendNumber);
		g_FriendDB.CFriendDB::SaveFriend(pFriend->GID, pFriend->Friends, pFriend->FriendNumber);
		this->CUserMgr::SendDeleteFriend(pFriend->ServerID, pFriend->AID, pUser->AID, pUser->GID);
	}
	else
	{
		STRUCT_FRIEND Friends[MAX_FRIENDS_LIST+1];
		int FriendNumber = g_FriendDB.CFriendDB::LoadFriend(FriendGID, Friends);
		if( FriendNumber > MAX_FRIENDS_LIST )
			FriendNumber = MAX_FRIENDS_LIST;

		this->CUserMgr::DeleteFriendList(pUser->AID, pUser->GID, Friends, FriendNumber);
		g_FriendDB.CFriendDB::SaveFriend(FriendGID, Friends, FriendNumber);
	}
}


void CUserMgr::SendFriendList(int ServerID, unsigned long AID, STRUCT_FRIEND* pFriends, int Number)
{
	PACKET_IZ_FRIENDS_LIST Friend_List;
	Friend_List.PacketType = HEADER_IZ_FRIENDS_LIST;
	Friend_List.PacketLength = sizeof(PACKET_IZ_FRIENDS_LIST) + Number * sizeof(STRUCT_FRIEND);
	Friend_List.AID = AID;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ServerID, sizeof(Friend_List), (char*)&Friend_List);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ServerID, Number * sizeof(STRUCT_FRIEND), (char*)pFriends);
}


void CUserMgr::SendFriendState(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID, bool bState)
{
	PACKET_IZ_FRIENDS_STATE FriendsState;
	FriendsState.PacketType = HEADER_IZ_FRIENDS_STATE;
	FriendsState.AID = SendAID;
	FriendsState.FriendAID = FriendAID;
	FriendsState.FriendGID = FriendGID;
	FriendsState.State = bState;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ServerID, sizeof(FriendsState), (char*)&FriendsState);
}


void CUserMgr::SendAddFriend(int ServerID, unsigned long SendAID, short Result, unsigned long FriendAID, unsigned long FriendGID, char* Name)
{
	PACKET_IZ_ADD_FRIENDS AddFriends;
	AddFriends.PacketType = HEADER_IZ_ADD_FRIENDS;
	AddFriends.Result = Result;
	AddFriends.AID = SendAID;
	AddFriends.FriendAID = FriendAID;
	AddFriends.FriendGID = FriendGID;
	memcpy(AddFriends.Name, Name, 24);
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ServerID, sizeof(AddFriends), (char*)&AddFriends);
}


void CUserMgr::SendDeleteFriend(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID)
{
	PACKET_IZ_DELETE_FRIENDS DeleteFriends;
	DeleteFriends.PacketType = HEADER_IZ_DELETE_FRIENDS;
	DeleteFriends.AID = SendAID;
	DeleteFriends.FriendAID = FriendAID;
	DeleteFriends.FriendGID = FriendGID;
	CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ServerID, sizeof(DeleteFriends), (char*)&DeleteFriends);
}


BOOL CUserMgr::AddFriendList(unsigned long FriendAID, unsigned long FriendDGID, char* Name, STRUCT_FRIEND* pFriends, int& FriendNumber)
{
	if( FriendNumber < 0 || FriendNumber >= 40 )
		return FALSE;

	pFriends[FriendNumber].AID = FriendAID;
	pFriends[FriendNumber].GID = FriendDGID;
	memcpy(pFriends[FriendNumber].Name, Name, 24);
	++FriendNumber;

	return TRUE;
}


void CUserMgr::DeleteFriendList(unsigned long AID, unsigned long GID, STRUCT_FRIEND* pFriends, int& FriendNumber)
{
	if( FriendNumber > MAX_FRIENDS_LIST )
		FriendNumber = MAX_FRIENDS_LIST;

	for( int i = 0; i < FriendNumber; ++i )
	{
		if( pFriends[i].AID == AID && pFriends[i].GID == GID )
		{
			if( i + 1 < MAX_FRIENDS_LIST )
				memmove(&pFriends[i], &pFriends[i + 1], (FriendNumber - i - 1) * sizeof(STRUCT_FRIEND));

			--FriendNumber;
			break;
		}
	}
}


void CUserMgr::AddFriend(unsigned long AID, unsigned long GID, unsigned long FriendAID, unsigned long FriendGID)
{
	USER_STRING_MAP_DATA* pUser = this->CUserMgr::SearchUser(AID, GID);
	if( pUser == NULL )
		return;

	USER_STRING_MAP_DATA* pFriend = this->CUserMgr::SearchUser(FriendAID, FriendGID);
	if( pFriend == NULL )
		return;

	if( pUser->FriendNumber >= MAX_FRIENDS_LIST )
	{
		this->CUserMgr::SendAddFriend(pUser->ServerID, AID, FRIEND_ADD_ME_OVERSIZE, FriendAID, FriendGID, pFriend->characterName);
		this->CUserMgr::SendAddFriend(pFriend->ServerID, FriendAID, FRIEND_ADD_OTHER_OVERSIZE, AID, GID, pUser->characterName);
	}
	else
	if( pFriend->FriendNumber >= MAX_FRIENDS_LIST )
	{
		this->CUserMgr::SendAddFriend(pUser->ServerID, AID, FRIEND_ADD_OTHER_OVERSIZE, FriendAID, FriendGID, pFriend->characterName);
		this->CUserMgr::SendAddFriend(pFriend->ServerID, FriendAID, FRIEND_ADD_ME_OVERSIZE, AID, GID, pUser->characterName);
	}
	else
	{
		this->CUserMgr::AddFriendList(FriendAID, FriendGID, pFriend->characterName, pUser->Friends, pUser->FriendNumber);
		g_FriendDB.CFriendDB::SaveFriend(pUser->GID, pUser->Friends, pUser->FriendNumber);

		this->CUserMgr::AddFriendList(AID, GID, pUser->characterName, pFriend->Friends, pFriend->FriendNumber);
		g_FriendDB.CFriendDB::SaveFriend(pFriend->GID, pFriend->Friends, pFriend->FriendNumber);

		this->CUserMgr::SendAddFriend(pUser->ServerID, AID, FRIEND_ADD_SUCCEED, FriendAID, FriendGID, pFriend->characterName);
		this->CUserMgr::SendAddFriend(pFriend->ServerID, FriendAID, FRIEND_ADD_SUCCEED, AID, GID, pUser->characterName);
	}
}


void CUserMgr::MoveServerUser(unsigned long ServerID, unsigned long AID, unsigned long GID, const char* name)
{
	this->CUserMgr::DeleteUser(ServerID, name);
}


void CUserMgr::Process()
{
	// 20 lines disabled here
}
