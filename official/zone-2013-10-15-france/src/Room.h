#pragma once


enum enumROOMTYPE
{
	ROOMTYPE_PRIVATE = 0,
	ROOMTYPE_PUBLIC  = 1,
	ROOMTYPE_ARENA   = 2,
	ROOMTYPE_PKZONE  = 3,
};


enum enumROOMROLE
{
	ROOMROLE_OWNER   = 0,
	ROOMROLE_GENERAL = 1,
};


enum enumROOMEXITTYPE
{
	ROOMEXITTYPE_EXIT  = 0,
	ROOMEXITTYPE_EXPEL = 1,
};


enum enumREFUSETYPE
{
	REFUSETYPE_OVERFLOW    = 0,
	REFUSETYPE_WRONGPASSWD = 1,
	REFUSETYPE_EXPEL       = 2,
	REFUSETYPE_SUCCEED     = 3,
	REFUSETYPE_ZENY        = 4,
	REFUSETYPE_LOWLEVEL    = 5,
	REFUSETYPE_HIGHLEVEL   = 6,
	REFUSETYPE_JOB         = 7,
};


struct ARENA_ROOM_INFO
{
	/* this+ 0 */ int fee;
	/* this+ 4 */ int lowLevel;
	/* this+ 8 */ int highLevel;
	/* this+12 */ std::list<int> m_exJob;
};


struct MEMBER_DATA
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long ROLE; // enumROOMROLE
	/* this+8 */ char charName[24];
};


class CRoom
{
public:
	CRoom();
	virtual ~CRoom();
	void Init();
	const char* GetRoomName();
	void SetRoomName(const char* name);
	BOOL InsertMember(const char* name, unsigned long AID, unsigned long Role);
	BOOL DeleteMember(const char* name);
	BOOL IsPrivateRoom();
	void SetRoomType(unsigned char flag); // enumROOMTYPE
	BOOL IsCorrectPasswd(const char* passwd);
	int GetSize();
	BOOL IsAcceptablePC(const char* name);
	void Reset();
	void SetPasswd(const char* passwd);
	void SetMaxSize(int maxsize);
	void GetRoomMembers(int& count, char* buf, const int in_nMaxBufSize);
	void BroadCast(int len, char* buf, unsigned long AID);
	void UpdateRoom(short size, unsigned char type, char* passwd, char* rname);
	unsigned long GetOwner();
	void MemberRoleChange(unsigned long AID, const char* name, unsigned long role);
	void OwnerChange(unsigned long AID, const char* name);
	void ExpelMember(const char* name);
	int ExitRoom(const char* name);
	int ExitRoom(unsigned long AID);
	int GetMaxSize();
	unsigned char GetType(); // enumROOMTYPE
	void SetRoomID(unsigned long roomID);
	unsigned long GetFirstMemberAID();
	int GetAcceptableType(unsigned long AID); // enumREFUSETYPE
	void SetLevel(int low, int high);
	void SetFee(int zeny);
	void AddFeeItem(unsigned short ITID, int count);
	void AddExJob(int job);
	int GetFee();
	int GetLowLevel();
	int GetHighLevel();

private:
	BOOL IsAcceptableJob(int job);

private:
	/* this+  0 */ //const CRoom::`vftable';
	/* this+  4 */ char m_roomName[128];
	/* this+132 */ unsigned long m_roomID;
	/* this+136 */ int m_maxRoomSize;
	/* this+140 */ ARENA_ROOM_INFO m_arenaInfo;
	/* this+164 */ char m_password[8];
	/* this+172 */ unsigned char m_type; // enumROOMTYPE
	/* this+176 */ std::vector<MEMBER_DATA> m_members;
	/* this+192 */ std::list<std::string> m_refuseList;
};
