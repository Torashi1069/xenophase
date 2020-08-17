#pragma once
#include "FriendDB.h"
#include "InterServer.h"
#include "NetLib/MemoryMgr.h"


enum enumFRIENDADDRETCODE
{
	FRIEND_ADD_SUCCEED        = 0,
	FRIEND_ADD_FALSE          = 1,
	FRIEND_ADD_ME_OVERSIZE    = 2,
	FRIEND_ADD_OTHER_OVERSIZE = 3,
};


#pragma pack(push,1)
struct USER_STRING_MAP_DATA
{
	/* this+   0 */ unsigned long AID;
	/* this+   4 */ unsigned long GID;
	/* this+   8 */ unsigned long ServerID;
	/* this+  12 */ unsigned long GRID;
	/* this+  16 */ int sex;
	/* this+  20 */ short age;
	/* this+  22 */ short level;
	/* this+  24 */ short job;
	/* this+  26 */ short head;
	/* this+  28 */ short headpalette;
	/* this+  30 */ char accountName[24];
	/* this+  54 */ char characterName[24];
	/* this+  78 */ char mapName[16];
	/* this+  94 */ STRUCT_FRIEND Friends[MAX_FRIENDS_LIST];
	/* this+1374 */ int FriendNumber;
};
#pragma pack(pop)


class CUserMgr
{
private:
	enum { SERVER_MOVE_DISCONNECT_TIME = 600000 };

	struct SERVER_MOVE_USER
	{
		/* this+ 0 */ unsigned long DisConnectTime;
		/* this+ 4 */ unsigned long AID;
		/* this+ 8 */ unsigned long GID;
		/* this+12 */ unsigned long ServerID;
		/* this+16 */ char Name[24];
	};

public:
	CUserMgr();
	virtual ~CUserMgr();

public:
	void Init(int MaxCharacterCount);
	unsigned long SearchUserServerID(const char* name, unsigned long& AID);
	unsigned long SearchUserServerID(unsigned long AID);
	unsigned long SearchUserServerID(const unsigned long in_GID, const unsigned long in_AID);
	USER_STRING_MAP_DATA* AllocUser();
	void FreeUser(USER_STRING_MAP_DATA* data);
	int GetUserCount();
	BOOL AddUser(unsigned long ServerID, USER_STRING_MAP_DATA* pUser);
	void DeleteUser(unsigned long ServerID, const char* name);
	void MoveServerUser(unsigned long ServerID, unsigned long AID, unsigned long GID, const char* name);
	void DeleteUsers(unsigned long ServerID);
	void SendMsg(unsigned long receiverAID, short len, char* buf);
	void SendMsg(const int in_HsvrID, const unsigned long in_AID, const int in_Length, const char* in_pBuffer);
	USER_STRING_MAP_DATA* SearchUser(unsigned long AID, unsigned long GID);
	USER_STRING_MAP_DATA* SearchUserByAccount(char* Name, unsigned long GID);
	USER_STRING_MAP_DATA* SearchUserByName(const char* Name, unsigned long GID);
	unsigned long GetUserGRID(unsigned long AID);
	unsigned long GetFreeSize();
	void AddFriend(unsigned long AID, unsigned long GID, unsigned long FriendAID, unsigned long FriendGID);
	void DeleteFriend(unsigned long AID, unsigned long FriendAID, unsigned long FriendGID);
	void Process();

private:
	void SendFriendList(int ServerID, unsigned long AID, STRUCT_FRIEND* pFriends, int Number);
	void SendFriendState(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID, bool bState);
	void SendDeleteFriend(int ServerID, unsigned long SendAID, unsigned long FriendAID, unsigned long FriendGID);
	void SendAddFriend(int ServerID, unsigned long SendAID, short Result, unsigned long FriendAID, unsigned long FriendGID, char* Name);
	BOOL AddFriendList(unsigned long FriendAID, unsigned long FriendDGID, char* Name, STRUCT_FRIEND* pFriends, int& FriendNumber);
	void DeleteFriendList(unsigned long AID, unsigned long GID, STRUCT_FRIEND* pFriends, int& FriendNumber);

private:
	/* this+  0 */ //const CUserMgr::`vftable';
	/* this+  4 */ std::map<std::string,USER_STRING_MAP_DATA*> m_userStringMap;
	/* this+ 36 */ std::map<unsigned long,USER_STRING_MAP_DATA*> m_userAIDMap;
	/* this+ 68 */ CMemoryMgr<USER_STRING_MAP_DATA> m_userData;
	/* this+108 */ CMemoryMgr<SERVER_MOVE_USER> m_ServerMoveUserPool;
	/* this+148 */ std::map<unsigned long,SERVER_MOVE_USER*> m_ServerMoveUser;

};
