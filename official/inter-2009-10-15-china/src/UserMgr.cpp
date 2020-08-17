#include "ErrorLog.h"
#include "FriendDB.h"
#include "PartyMgr.h"
#include "UserMgr.h"
#include "ZServerMgr.h"
#include "enums.hpp"
#include "globals.hpp"
#include "Common/Packet.h"
#include "IGuildMgr.h"
#include "CMailCtrl.h"


CUserMgr::CUserMgr(void) // line 20
{
	m_ServerMoveUserPool.CMemoryMgr<CUserMgr::SERVER_MOVE_USER>::Init(3000);
	m_ServerMoveUser.clear();
}


CUserMgr::~CUserMgr(void) // line 26
{
}


hook_method<void (CUserMgr::*)(int MaxCharacterCount)> CUserMgr::_Init(SERVER, "CUserMgr::Init");
void CUserMgr::Init(int MaxCharacterCount) // line 32
{
	return (this->*_Init)(MaxCharacterCount);

	if( !m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::Init(MaxCharacterCount) )
	{
		g_errorLogs.CErrorLog::CriticalErrorLog("Error m_userData.Init", 34, ".\\UserMgr.cpp");
		MessageBoxA(NULL, "Error CUserMgr", "Error", MB_OK);
	}
}


hook_method<unsigned long (CUserMgr::*)(const unsigned long in_GID, const unsigned long in_AID)> CUserMgr::_SearchUserServerID(SERVER, "?SearchUserServerID@CUserMgr@@QAEKKK@Z");
unsigned long CUserMgr::SearchUserServerID(const unsigned long in_GID, const unsigned long in_AID) // line 320
{
	return (this->*_SearchUserServerID)(in_GID, in_AID);

	mystd::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(in_AID);
	return ( iter != m_userAIDMap.end() && iter->second->GID == in_GID ) ? iter->second->ServerID : 0;
}


hook_method<unsigned long (CUserMgr::*)(unsigned long AID)> CUserMgr::_SearchUserServerID2(SERVER, "?SearchUserServerID@CUserMgr@@QAEKK@Z");
unsigned long CUserMgr::SearchUserServerID(unsigned long AID) // line 311
{
	return (this->*_SearchUserServerID2)(AID);

	mystd::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(AID);
	return ( iter != m_userAIDMap.end() ) ? iter->second->ServerID : 0;
}


hook_method<unsigned long (CUserMgr::*)(const char* name, unsigned long& AID)> CUserMgr::_SearchUserServerID3(SERVER, "?SearchUserServerID@CUserMgr@@QAEKPBDAAK@Z");
unsigned long CUserMgr::SearchUserServerID(const char* name, unsigned long& AID) // line 300
{
	return (this->*_SearchUserServerID3)(name, AID);

	mystd::map<mystd::string,USER_STRING_MAP_DATA*>::iterator it = m_userStringMap.find(name);
	if( it == m_userStringMap.end() )
		return -1;

	AID = it->second->AID;
	return it->second->ServerID;
}


hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(void)> CUserMgr::_AllocUser(SERVER, "CUserMgr::AllocUser");
USER_STRING_MAP_DATA* CUserMgr::AllocUser(void) // line 42
{
	return (this->*_AllocUser)();

	return m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::Alloc();
}


hook_method<void (CUserMgr::*)(USER_STRING_MAP_DATA* data)> CUserMgr::_FreeUser(SERVER, "CUserMgr::FreeUser");
void CUserMgr::FreeUser(USER_STRING_MAP_DATA* data) // line 47
{
	return (this->*_FreeUser)(data);

	m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::Free(data);
}


hook_method<int (CUserMgr::*)(void)> CUserMgr::_GetUserCount(SERVER, "CUserMgr::GetUserCount");
int CUserMgr::GetUserCount(void) // line 330
{
	return (this->*_GetUserCount)();

	return m_userStringMap.size();
}


hook_method<int (CUserMgr::*)(unsigned long ServerID, USER_STRING_MAP_DATA* pUser)> CUserMgr::_AddUser(SERVER, "CUserMgr::AddUser");
int CUserMgr::AddUser(unsigned long ServerID, USER_STRING_MAP_DATA* pUser) // line 74-256
{
	return (this->*_AddUser)(ServerID, pUser);

	mystd::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter = m_userAIDMap.find(pUser->AID);
	if( iter != m_userAIDMap.end() )
	{
		PACKET_IZ_DISCONNECT_CHARACTER outpacket;
		outpacket.PacketType = HEADER_IZ_DISCONNECT_CHARACTER;
		outpacket.AID = pUser->AID;

		g_zServerMgr.CZServerMgr::BroadCast(sizeof(outpacket), (const char *)&outpacket);
		this->CUserMgr::DeleteUser(iter->second->ServerID, iter->second->characterName);
		return 0; // user already exists
	}

	USER_STRING_MAP_DATA* user = this->CUserMgr::AllocUser();
	if( user == NULL )
	{
		PACKET_IZ_DISCONNECT_CHARACTER outpacket;
		outpacket.PacketType = HEADER_IZ_DISCONNECT_CHARACTER;
		outpacket.AID = pUser->AID;

		g_zServerMgr.CZServerMgr::SendMsgToZServer(ServerID, sizeof(outpacket), (const char *)&outpacket);
		g_errorLogs.CErrorLog::CriticalErrorLog("CUserMgr::AddUser() -> AllocUser", 178, ".\\UserMgr.cpp");
		return 0; // failed to allocate user
	}

	memcpy(user, pUser, sizeof(USER_STRING_MAP_DATA));
	Trace("새로운 캐릭터 등장 : 이름: %s, Server:%d\n", pUser->characterName, user->ServerID);
	m_userStringMap[pUser->characterName] = user;
	m_userAIDMap[pUser->AID] = user;
	CIGuildMgr::GetObj()->CIGuildMgr::LogonUserA(ServerID, user->GID, user->AID);

	PACKET_IZ_ACK_LOGON AckLogon;
	AckLogon.PacketType = HEADER_IZ_ACK_LOGON;
	AckLogon.AID = pUser->AID;
	AckLogon.Type = 0;
	AckLogon.GID = pUser->GID;

	g_zServerMgr.CZServerMgr::SendMsgToZServer(ServerID, sizeof(AckLogon), (const char *)&AckLogon);

	int userCount = this->CUserMgr::GetUserCount();
	if( g_maxConnectClient < userCount )
		g_maxConnectClient = userCount;

	unsigned long GRID = InstanceCPartyMgr()->CPartyMgr::SearchMember(pUser->GID);
	if( GRID != 0 )
	{
		Trace("PACKET_ZI_GRID_UPDATE1\n");
		InstanceCPartyMgr()->CPartyMgr::LogonNewUser(pUser->AID, GRID);

		CParty* party = InstanceCPartyMgr()->CPartyMgr::SearchGroup(GRID);
		if( party != NULL )
			party->CParty::NotifyUpdateExpOption(user->AID, party->CParty::GetGroupEXPOption());

		user->GRID = GRID;
	}

	user->FriendNumber = 0;
	user->FriendNumber = g_FriendDB.CFriendDB::LoadFriend(user->GID, user->Friends);
	if( user->FriendNumber > 0 )
	{
		this->CUserMgr::SendFriendList(user->ServerID, user->AID, user->Friends, user->FriendNumber);

		for( int i = 0; i < user->FriendNumber; ++i )
		{
			STRUCT_FRIEND* userFriend = &user->Friends[i];
			USER_STRING_MAP_DATA* otherUser = this->CUserMgr::SearchUser(userFriend->AID, userFriend->GID);
			if( otherUser != NULL )
			{
				this->CUserMgr::SendFriendState(user->ServerID, user->AID, userFriend->AID, userFriend->GID, 0);
				this->CUserMgr::SendFriendState(otherUser->ServerID, otherUser->AID, user->AID, user->GID, 0);
			}
		}
	}

	user->MailCounter = g_MailCtrl.CMailCtrl::GetMail(user->AID, user->GID, user->MailInfo);
	Trace("Read Mail Data : %d \n", user->MailCounter);
	return 1; // done
}


hook_method<void (CUserMgr::*)(unsigned long ServerID, const char* name)> CUserMgr::_DeleteUser(SERVER, "CUserMgr::DeleteUser");
void CUserMgr::DeleteUser(unsigned long ServerID, const char* name) // line 259-296
{
	return (this->*_DeleteUser)(ServerID, name);

	unsigned long AID = reinterpret_cast<unsigned long>(name); // FIXME uninitialized variable in official code; has the same address as the name variable

	mystd::map<mystd::string,USER_STRING_MAP_DATA*>::iterator iter = m_userStringMap.find(name);
	if( iter != m_userStringMap.end() )
	{
		USER_STRING_MAP_DATA* user = iter->second;
		if( user == NULL || user->ServerID != ServerID )
			return; // unexpected user data

		for( int i = 0; i < user->FriendNumber; ++i )
		{
			USER_STRING_MAP_DATA* friendUser = this->CUserMgr::SearchUser(user->Friends[i].AID, user->Friends[i].GID);
			if( friendUser != NULL )
				this->CUserMgr::SendFriendState(friendUser->ServerID, friendUser->AID, user->AID, user->GID, true);
		}

		Trace("%s:지운다.\n", name);

		unsigned long GRID = user->GRID;
		unsigned long GID = user->GID;
		AID = user->AID;

		CIGuildMgr::GetObj()->CIGuildMgr::ExitUser(ServerID, AID, GID);
		this->CUserMgr::FreeUser(user);
		m_userStringMap.erase(iter);
		InstanceCPartyMgr()->CPartyMgr::UserExit(AID, GRID);
	}

	mystd::map<unsigned long,USER_STRING_MAP_DATA*>::iterator iter2 = m_userAIDMap.find(AID); // FIXME use of potentially uninitialized variable in official code (if the user isn't found in m_userStringMap)
	if( iter2 != m_userAIDMap.end() )
		m_userAIDMap.erase(iter2);
}


hook_method<void (CUserMgr::*)(unsigned long ServerID, unsigned long AID, unsigned long GID, const char* name)> CUserMgr::_MoveServerUser(SERVER, "CUserMgr::MoveServerUser");
void CUserMgr::MoveServerUser(unsigned long ServerID, unsigned long AID, unsigned long GID, const char* name) // line 614
{
	return (this->*_MoveServerUser)(ServerID, AID, GID, name);

	g_userMgr.CUserMgr::DeleteUser(ServerID, name);
}


hook_method<void (CUserMgr::*)(unsigned long ServerID)> CUserMgr::_DeleteUsers(SERVER, "CUserMgr::DeleteUsers");
void CUserMgr::DeleteUsers(unsigned long ServerID) // line 57
{
	return (this->*_DeleteUsers)(ServerID);

	mystd::map<mystd::string,USER_STRING_MAP_DATA*>::iterator it = m_userStringMap.begin();
	while( it != m_userStringMap.end() )
	{
		USER_STRING_MAP_DATA* user = it->second;

		if( user->ServerID == ServerID )
		{
			Trace("User String delete:%d\n", user->AID);
			this->CUserMgr::FreeUser(user);
			InstanceCPartyMgr()->CPartyMgr::UserExit(user->AID, user->GRID);
			it = m_userStringMap.erase(it);
		}
		else
		{
			++it;
		}
	}

	m_userAIDMap.clear();
}


hook_method<void (CUserMgr::*)(unsigned long receiverAID, short len, char* buf)> CUserMgr::_SendMsg(SERVER, "CUserMgr::SendMsg");
void CUserMgr::SendMsg(unsigned long receiverAID, short len, char* buf) // line 337
{
	return (this->*_SendMsg)(receiverAID, len, buf);

	unsigned long SID = this->CUserMgr::SearchUserServerID(receiverAID);
	g_zServerMgr.CZServerMgr::SendMsgToZServer(SID, len, buf);
}


hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(unsigned long AID, unsigned long GID)> CUserMgr::_SearchUser(SERVER, "CUserMgr::SearchUser");
USER_STRING_MAP_DATA* CUserMgr::SearchUser(unsigned long AID, unsigned long GID) // line 342
{
	return (this->*_SearchUser)(AID, GID);

	mystd::map<unsigned long,USER_STRING_MAP_DATA*>::iterator it = m_userAIDMap.find(AID);
	if( it == m_userAIDMap.end() )
		return NULL;

	USER_STRING_MAP_DATA* user = it->second;
	if( GID != 0 && (user == NULL || user->GID != GID) )
		return NULL;

	return user;
}


hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(char* Name, unsigned long GID)> CUserMgr::_SearchUserByAccount(SERVER, "CUserMgr::SearchUserByAccount");
USER_STRING_MAP_DATA* CUserMgr::SearchUserByAccount(char* Name, unsigned long GID) // line 361
{
	return (this->*_SearchUserByAccount)(Name, GID);

	for( mystd::map<mystd::string,USER_STRING_MAP_DATA*>::iterator it = m_userStringMap.begin(); it != m_userStringMap.end(); ++it )
	{
		USER_STRING_MAP_DATA* user = it->second;

		if( strcmp(user->accountName, Name) == 0 )
			if( GID == 0 || user == NULL || user->GID == GID )
				return user;
	}

	return NULL;
}


hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(char* Name, unsigned long GID)> CUserMgr::_SearchUserByName(SERVER, "CUserMgr::SearchUserByName");
USER_STRING_MAP_DATA* CUserMgr::SearchUserByName(char* Name, unsigned long GID) // line 384
{
	return (this->*_SearchUserByName)(Name, GID);

	mystd::map<mystd::string,USER_STRING_MAP_DATA*>::iterator it = m_userStringMap.find(Name);
	if( it == m_userStringMap.end() )
		return NULL;
	
	USER_STRING_MAP_DATA* user = it->second;
	if( GID != 0 && (user == NULL || user->GID != GID) )
		return NULL;

	return user;
}


hook_method<unsigned long (CUserMgr::*)(unsigned long AID)> CUserMgr::_GetUserGRID(SERVER, "CUserMgr::GetUserGRID");
unsigned long CUserMgr::GetUserGRID(unsigned long AID) // line 414
{
	return (this->*_GetUserGRID)(AID);

	mystd::map<unsigned long,USER_STRING_MAP_DATA*>::iterator it = m_userAIDMap.find(AID);
	return ( it != m_userAIDMap.end() ) ? it->second->GRID : 0;
}


hook_method<unsigned long (CUserMgr::*)(void)> CUserMgr::_GetFreeSize(SERVER, "CUserMgr::GetFreeSize");
unsigned long CUserMgr::GetFreeSize(void) // line 52
{
	return (this->*_GetFreeSize)();

	return m_userData.CMemoryMgr<USER_STRING_MAP_DATA>::GetFreeSize();
}


hook_method<void (CUserMgr::*)(unsigned long AID, unsigned long GID, unsigned long FriendAID, unsigned long FriendGID)> CUserMgr::_AddFriend(SERVER, "CUserMgr::AddFriend");
void CUserMgr::AddFriend(unsigned long AID, unsigned long GID, unsigned long FriendAID, unsigned long FriendGID) // line 530
{
	return (this->*_AddFriend)(AID, GID, FriendAID, FriendGID);

	//TODO
}


hook_method<void (CUserMgr::*)(unsigned long AID, unsigned long FriendAID, unsigned long FriendGID)> CUserMgr::_DeleteFriend(SERVER, "CUserMgr::DeleteFriend");
void CUserMgr::DeleteFriend(unsigned long AID, unsigned long FriendAID, unsigned long FriendGID) // line 423
{
	return (this->*_DeleteFriend)(AID, FriendAID, FriendGID);

	USER_STRING_MAP_DATA* pPlayer = this->CUserMgr::SearchUser(AID, 0);
	USER_STRING_MAP_DATA* pFriend = this->CUserMgr::SearchUser(FriendAID, FriendGID);
	if( pPlayer == NULL )
		return;

	this->CUserMgr::DeleteFriendList(FriendAID, FriendGID, pPlayer->Friends, pPlayer->FriendNumber);
	g_FriendDB.CFriendDB::SaveFriend(pPlayer->GID, pPlayer->Friends, pPlayer->FriendNumber);
	this->CUserMgr::SendDeleteFriend(pPlayer->ServerID, pPlayer->AID, FriendAID, FriendGID);
	if( pFriend != NULL )
	{
		this->CUserMgr::DeleteFriendList(pPlayer->AID, pPlayer->GID, pFriend->Friends, pFriend->FriendNumber);
		g_FriendDB.CFriendDB::SaveFriend(pFriend->GID, pFriend->Friends, pFriend->FriendNumber);
		this->CUserMgr::SendDeleteFriend(pFriend->ServerID, pFriend->AID, pPlayer->AID, pPlayer->GID);
	}
	else
	{
		STRUCT_FRIEND Friends[41];
		int FriendNumber = g_FriendDB.CFriendDB::LoadFriend(FriendGID, Friends);
		if( FriendNumber > MAX_FRIENDS_LIST )
			FriendNumber = MAX_FRIENDS_LIST;
		this->CUserMgr::DeleteFriendList(pPlayer->AID, pPlayer->GID, Friends, FriendNumber);
		g_FriendDB.CFriendDB::SaveFriend(FriendGID, Friends, FriendNumber);
	}
}


hook_method<void (CUserMgr::*)(void)> CUserMgr::_Process(SERVER, "CUserMgr::Process");
void CUserMgr::Process(void) // line 639
{
	return (this->*_Process)();

	;
}


hook_method<void (CUserMgr::*)(int ServerID, unsigned long AID, STRUCT_FRIEND* pFriends, int Number)> CUserMgr::_SendFriendList(SERVER, "CUserMgr::SendFriendList");
void CUserMgr::SendFriendList(int ServerID, unsigned long AID, STRUCT_FRIEND* pFriends, int Number) // line 451
{
	return (this->*_SendFriendList)(ServerID, AID, pFriends, Number);

	PACKET_IZ_FRIENDS_LIST Friend_List;
	Friend_List.PacketType = HEADER_IZ_FRIENDS_LIST;
	Friend_List.PacketLength = sizeof(Friend_List) + sizeof(STRUCT_FRIEND) * Number;
	Friend_List.AID = AID;

	g_zServerMgr.CZServerMgr::SendMsgToZServer(ServerID, sizeof(Friend_List), (const char*)&Friend_List);
	g_zServerMgr.CZServerMgr::SendMsgToZServer(ServerID, sizeof(STRUCT_FRIEND) * Number, (const char*)pFriends);
}


hook_method<void (CUserMgr::*)(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID, bool bState)> CUserMgr::_SendFriendState(SERVER, "CUserMgr::SendFriendState");
void CUserMgr::SendFriendState(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID, bool bState) // line 463
{
	return (this->*_SendFriendState)(ServerID, SendAID, FriendAID, FriendGID, bState);

	PACKET_IZ_FRIENDS_STATE FriendsState;
	FriendsState.PacketType = HEADER_IZ_FRIENDS_STATE;
	FriendsState.AID = SendAID;
	FriendsState.FriendAID = FriendAID;
	FriendsState.FriendGID = FriendGID;
	FriendsState.State = bState;

	g_zServerMgr.CZServerMgr::SendMsgToZServer(ServerID, sizeof(FriendsState), (const char*)&FriendsState);
}


hook_method<void (CUserMgr::*)(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID)> CUserMgr::_SendDeleteFriend(SERVER, "CUserMgr::SendDeleteFriend");
void CUserMgr::SendDeleteFriend(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID) // line 489
{
	return (this->*_SendDeleteFriend)(ServerID, SendAID, FriendAID, FriendGID);

	PACKET_IZ_DELETE_FRIENDS DeleteFriends;
	DeleteFriends.PacketType = HEADER_IZ_DELETE_FRIENDS;
	DeleteFriends.AID = SendAID;
	DeleteFriends.FriendAID = FriendAID;
	DeleteFriends.FriendGID = FriendGID;

	g_zServerMgr.CZServerMgr::SendMsgToZServer(ServerID, sizeof(DeleteFriends), (const char*)&DeleteFriends);
}


hook_method<void (CUserMgr::*)(int ServerID, unsigned long SendAID, short Result, unsigned long FriendAID, unsigned long FriendGID, char* Name)> CUserMgr::_SendAddFriend(SERVER, "CUserMgr::SendAddFriend");
void CUserMgr::SendAddFriend(int ServerID, unsigned long SendAID, short Result, unsigned long FriendAID, unsigned long FriendGID, char* Name) // line 476
{
	return (this->*_SendAddFriend)(ServerID, SendAID, Result, FriendAID, FriendGID, Name);

	PACKET_IZ_ADD_FRIENDS AddFriends;
	AddFriends.PacketType = HEADER_IZ_ADD_FRIENDS;
	AddFriends.Result = Result;
	AddFriends.AID = SendAID;
	AddFriends.FriendGID = FriendGID;
	AddFriends.FriendAID = FriendAID;
	memcpy(AddFriends.Name, Name, sizeof(AddFriends.Name));

	g_zServerMgr.CZServerMgr::SendMsgToZServer(ServerID, sizeof(AddFriends), (const char*)&AddFriends);
}


hook_method<int (CUserMgr::*)(unsigned long FriendAID, unsigned long FriendDGID, char* Name, STRUCT_FRIEND* pFriends, int& FriendNumber)> CUserMgr::_AddFriendList(SERVER, "CUserMgr::AddFriendList");
int CUserMgr::AddFriendList(unsigned long FriendAID, unsigned long FriendDGID, char* Name, STRUCT_FRIEND* pFriends, int& FriendNumber) // line 501
{
	return (this->*_AddFriendList)(FriendAID, FriendDGID, Name, pFriends, FriendNumber);

	if( FriendNumber < 0 || FriendNumber >= MAX_FRIENDS_LIST )
		return 0;

	pFriends[FriendNumber].AID = FriendAID;
	pFriends[FriendNumber].GID = FriendDGID;
	memcpy(pFriends[FriendNumber].Name, Name, sizeof(pFriends[FriendNumber].Name));
	++FriendNumber;
	return 1;
}


hook_method<void (CUserMgr::*)(unsigned long AID, unsigned long GID, STRUCT_FRIEND* pFriends, int& FriendNumber)> CUserMgr::_DeleteFriendList(SERVER, "CUserMgr::DeleteFriendList");
void CUserMgr::DeleteFriendList(unsigned long AID, unsigned long GID, STRUCT_FRIEND* pFriends, int& FriendNumber) // line 510
{
	return (this->*_DeleteFriendList)(AID, GID, pFriends, FriendNumber);

	if( FriendNumber > MAX_FRIENDS_LIST )
		FriendNumber = MAX_FRIENDS_LIST;

	for( int i = 0; i < FriendNumber; ++i )
	{
		if( pFriends[i].AID == AID && pFriends[i].GID == GID )
		{
			if( i + 1 < MAX_FRIENDS_LIST )
				memmove(&pFriends[i], &pFriends[i + 1], sizeof(STRUCT_FRIEND) * (FriendNumber - i - 1));
			--FriendNumber;
			break;
		}
	}
}
