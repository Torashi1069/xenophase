#pragma once
#include "NetLib/MemoryMgr.h"
#include "structs.hpp"
#include "std/map"
#include "std/string"


class CUserMgr
{
	enum
	{
		SERVER_MOVE_DISCONNECT_TIME = 600000
	};

	struct SERVER_MOVE_USER
	{
		/* this+ 0 */ unsigned long DisConnectTime;
		/* this+ 4 */ unsigned long AID;
		/* this+ 8 */ unsigned long GID;
		/* this+12 */ unsigned long ServerID;
		/* this+16 */ char Name[24];
	};

	/* this+  0 */ public: //const CUserMgr::`vftable';
	/* this+  4 */ private: mystd::map<mystd::string,USER_STRING_MAP_DATA*> m_userStringMap;
	/* this+ 16 */ private: mystd::map<unsigned long,USER_STRING_MAP_DATA*> m_userAIDMap;
	/* this+ 28 */ private: CMemoryMgr<USER_STRING_MAP_DATA> m_userData;
	/* this+ 76 */ private: CMemoryMgr<CUserMgr::SERVER_MOVE_USER> m_ServerMoveUserPool;
	/* this+124 */ private: mystd::map<unsigned long,CUserMgr::SERVER_MOVE_USER*> m_ServerMoveUser;

	public: CUserMgr::CUserMgr(void);
	public: virtual CUserMgr::~CUserMgr(void);
	public: void CUserMgr::Init(int MaxCharacterCount);
	public: unsigned long CUserMgr::SearchUserServerID(const unsigned long in_GID, const unsigned long in_AID);
	public: unsigned long CUserMgr::SearchUserServerID(unsigned long AID);
	public: unsigned long CUserMgr::SearchUserServerID(const char* name, unsigned long& AID);
	public: USER_STRING_MAP_DATA* CUserMgr::AllocUser(void);
	public: void CUserMgr::FreeUser(USER_STRING_MAP_DATA* data);
	public: int CUserMgr::GetUserCount(void);
	public: int CUserMgr::AddUser(unsigned long ServerID, USER_STRING_MAP_DATA* pUser);
	public: void CUserMgr::DeleteUser(unsigned long ServerID, const char* name);
	public: void CUserMgr::MoveServerUser(unsigned long ServerID, unsigned long AID, unsigned long GID, const char* name);
	public: void CUserMgr::DeleteUsers(unsigned long ServerID);
	public: void CUserMgr::SendMsg(unsigned long receiverAID, short len, char* buf);
	public: USER_STRING_MAP_DATA* CUserMgr::SearchUser(unsigned long AID, unsigned long GID);
	public: USER_STRING_MAP_DATA* CUserMgr::SearchUserByAccount(char* Name, unsigned long GID);
	public: USER_STRING_MAP_DATA* CUserMgr::SearchUserByName(char* Name, unsigned long GID);
	public: unsigned long CUserMgr::GetUserGRID(unsigned long AID);
	public: unsigned long CUserMgr::GetFreeSize(void);
	public: void CUserMgr::AddFriend(unsigned long AID, unsigned long GID, unsigned long FriendAID, unsigned long FriendGID);
	public: void CUserMgr::DeleteFriend(unsigned long AID, unsigned long FriendAID, unsigned long FriendGID);
	public: void CUserMgr::Process(void);
	private: void CUserMgr::SendFriendList(int ServerID, unsigned long AID, STRUCT_FRIEND* pFriends, int Number);
	private: void CUserMgr::SendFriendState(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID, bool bState);
	private: void CUserMgr::SendDeleteFriend(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID);
	private: void CUserMgr::SendAddFriend(int ServerID, unsigned long SendAID, short Result, unsigned long FriendAID, unsigned long FriendGID, char* Name);
	private: int CUserMgr::AddFriendList(unsigned long FriendAID, unsigned long FriendDGID, char* Name, STRUCT_FRIEND* pFriends, int& FriendNumber);
	private: void CUserMgr::DeleteFriendList(unsigned long AID, unsigned long GID, STRUCT_FRIEND* pFriends, int& FriendNumber);

private:
	static hook_method<void (CUserMgr::*)(int MaxCharacterCount)> CUserMgr::_Init;
	static hook_method<unsigned long (CUserMgr::*)(const unsigned long in_GID, const unsigned long in_AID)> CUserMgr::_SearchUserServerID;
	static hook_method<unsigned long (CUserMgr::*)(unsigned long AID)> CUserMgr::_SearchUserServerID2;
	static hook_method<unsigned long (CUserMgr::*)(const char* name, unsigned long& AID)> CUserMgr::_SearchUserServerID3;
	static hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(void)> CUserMgr::_AllocUser;
	static hook_method<void (CUserMgr::*)(USER_STRING_MAP_DATA* data)> CUserMgr::_FreeUser;
	static hook_method<int (CUserMgr::*)(void)> CUserMgr::_GetUserCount;
	static hook_method<int (CUserMgr::*)(unsigned long ServerID, USER_STRING_MAP_DATA* pUser)> CUserMgr::_AddUser;
	static hook_method<void (CUserMgr::*)(unsigned long ServerID, const char* name)> CUserMgr::_DeleteUser;
	static hook_method<void (CUserMgr::*)(unsigned long ServerID, unsigned long AID, unsigned long GID, const char* name)> CUserMgr::_MoveServerUser;
	static hook_method<void (CUserMgr::*)(unsigned long ServerID)> CUserMgr::_DeleteUsers;
	static hook_method<void (CUserMgr::*)(unsigned long receiverAID, short len, char* buf)> CUserMgr::_SendMsg;
	static hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(unsigned long AID, unsigned long GID)> CUserMgr::_SearchUser;
	static hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(char* Name, unsigned long GID)> CUserMgr::_SearchUserByAccount;
	static hook_method<USER_STRING_MAP_DATA* (CUserMgr::*)(char* Name, unsigned long GID)> CUserMgr::_SearchUserByName;
	static hook_method<unsigned long (CUserMgr::*)(unsigned long AID)> CUserMgr::_GetUserGRID;
	static hook_method<unsigned long (CUserMgr::*)(void)> CUserMgr::_GetFreeSize;
	static hook_method<void (CUserMgr::*)(unsigned long AID, unsigned long GID, unsigned long FriendAID, unsigned long FriendGID)> CUserMgr::_AddFriend;
	static hook_method<void (CUserMgr::*)(unsigned long AID, unsigned long FriendAID, unsigned long FriendGID)> CUserMgr::_DeleteFriend;
	static hook_method<void (CUserMgr::*)(void)> CUserMgr::_Process;
	static hook_method<void (CUserMgr::*)(int ServerID, unsigned long AID, STRUCT_FRIEND* pFriends, int Number)> CUserMgr::_SendFriendList;
	static hook_method<void (CUserMgr::*)(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID, bool bState)> CUserMgr::_SendFriendState;
	static hook_method<void (CUserMgr::*)(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID)> CUserMgr::_SendDeleteFriend;
	static hook_method<void (CUserMgr::*)(int ServerID, unsigned long SendAID, short Result, unsigned long FriendAID, unsigned long FriendGID, char* Name)> CUserMgr::_SendAddFriend;
	static hook_method<int (CUserMgr::*)(unsigned long FriendAID, unsigned long FriendDGID, char* Name, STRUCT_FRIEND* pFriends, int& FriendNumber)> CUserMgr::_AddFriendList;
	static hook_method<void (CUserMgr::*)(unsigned long AID, unsigned long GID, STRUCT_FRIEND* pFriends, int& FriendNumber)> CUserMgr::_DeleteFriendList;
};
