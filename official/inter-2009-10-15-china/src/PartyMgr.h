#pragma once
#include "Party.h"
#include "PartyDB.h"
#include "NetLib/MemoryMgr.h"
#include "std/map"


class CPartyMgr
{
public:
	enum
	{
		MAX_PARTY_MEMBER_NUM = 30
	};

	enum enumResultINM
	{
		RESULTINM_UNKNOWN_GROUP   = 0x0,
		RESULTINM_OVERSIZE_MEMBER = 0x1,
		RESULTINM_DUPLICATE_AID   = 0x2,
		RESULTINM_UNKNOWN_ERROR   = 0x3,
		RESULTINM_SUCCESS         = 0x4,
	};

private:
	struct vtable_t // const CPartyMgr::`vftable'
	{
		void* (CPartyMgr::* scalar_deleting_destructor)(unsigned int __flags);
	};

	/* this+ 0 */ public: //const CPartyMgr::`vftable';
	/* this+ 4 */ private: CPartyDB m_groupdb;
	/* this+24 */ private: mystd::map<unsigned long,CParty*> m_group;
	/* this+36 */ private: CMemoryMgr<CParty> m_groupMPool;
	/* this+84 */ private: int m_MaxPartyMemberNum;

	private: bool CPartyMgr::DeleteMember(const unsigned long in_PartyID, const USER_STRING_MAP_DATA* in_pUser, const unsigned long in_type);
	public: void CPartyMgr::Send(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket);
	public: void CPartyMgr::MapMove2(const unsigned long in_hPartyID, const unsigned long in_AID, const char* in_pMapName);
	public: CParty* CPartyMgr::SearchGroup(unsigned long GRID);
	public: CParty* CPartyMgr::SearchGroup(const char* in_pPartyName);
	public: CPartyMgr::CPartyMgr(void);
	public: virtual CPartyMgr::~CPartyMgr(void);
	public: void CPartyMgr::Init(int MaxParty, const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type);
	public: const int CPartyMgr::GetMaxMemberNum(void);
	public: unsigned long CPartyMgr::MakeGroup(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name);
	public: unsigned long CPartyMgr::MakeGroup2(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name, unsigned char bItemPickupRule, unsigned char bItemDivisionRule);
	public: void CPartyMgr::GetGroupName(unsigned long GRID, char* buf);
	public: void CPartyMgr::GetGroupInfo(unsigned long GRID, char* buf, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule);
	public: int CPartyMgr::DeleteGroup(unsigned long GRID);
	public: int CPartyMgr::InsertNewMember(unsigned long AID, unsigned long GRID);
	public: unsigned long CPartyMgr::SearchMember(unsigned long GID);
	public: unsigned long CPartyMgr::GetGroupOwner(unsigned long GRID);
	public: void CPartyMgr::LogonNewUser(unsigned long AID, unsigned long GRID);
	public: void CPartyMgr::LoadGroupInfoFromDB(unsigned long AID, unsigned long GRID);
	public: void CPartyMgr::UserExit(unsigned long AID, unsigned long GRID);
	public: int CPartyMgr::FreeGroup(unsigned long GRID);
	public: void CPartyMgr::NotifyGroupMembers(unsigned long AID, unsigned long GRID);
	public: bool CPartyMgr::LeaveGroup(const unsigned long in_AID, const unsigned long in_GID);
	public: void CPartyMgr::ExpelGroupMember(unsigned long AID, unsigned long GRID, char* name);
	public: void CPartyMgr::ServerMoveUser(unsigned long AID, unsigned long GRID, int isOnLine);
	public: int CPartyMgr::GetGroupSize(void);
	public: unsigned long CPartyMgr::GetFreeSize(void);
	public: enum CPartyMgr::enumResultINM CPartyMgr::InsertNewMemberV2(CParty* const in_cpGroup, const USER_STRING_MAP_DATA* in_pNewMemberData);

private:
	static hook_method<bool (CPartyMgr::*)(const unsigned long in_PartyID, const USER_STRING_MAP_DATA* in_pUser, const unsigned long in_type)> CPartyMgr::_DeleteMember;
	static hook_method<void (CPartyMgr::*)(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)> CPartyMgr::_Send;
	static hook_method<void (CPartyMgr::*)(const unsigned long in_hPartyID, const unsigned long in_AID, const char* in_pMapName)> CPartyMgr::_MapMove2;
	static hook_method<CParty* (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_SearchGroup;
	static hook_method<CParty* (CPartyMgr::*)(const char* in_pPartyName)> CPartyMgr::_SearchGroup2;
	static hook_method<void (CPartyMgr::*)(int MaxParty, const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CPartyMgr::_Init;
	static hook_method<const int (CPartyMgr::*)(void)> CPartyMgr::_GetMaxMemberNum;
	static hook_method<unsigned long (CPartyMgr::*)(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name)> CPartyMgr::_MakeGroup;
	static hook_method<unsigned long (CPartyMgr::*)(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name, unsigned char bItemPickupRule, unsigned char bItemDivisionRule)> CPartyMgr::_MakeGroup2;
	static hook_method<void (CPartyMgr::*)(unsigned long GRID, char* buf)> CPartyMgr::_GetGroupName;
	static hook_method<void (CPartyMgr::*)(unsigned long GRID, char* buf, unsigned char& ItemPickupRule, unsigned char& ItemDivisionRule)> CPartyMgr::_GetGroupInfo;
	static hook_method<int (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_DeleteGroup;
	static hook_method<int (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_InsertNewMember;
	static hook_method<unsigned long (CPartyMgr::*)(unsigned long GID)> CPartyMgr::_SearchMember;
	static hook_method<unsigned long (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_GetGroupOwner;
	static hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_LogonNewUser;
	static hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_LoadGroupInfoFromDB;
	static hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_UserExit;
	static hook_method<int (CPartyMgr::*)(unsigned long GRID)> CPartyMgr::_FreeGroup;
	static hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID)> CPartyMgr::_NotifyGroupMembers;
	static hook_method<bool (CPartyMgr::*)(const unsigned long in_AID, const unsigned long in_GID)> CPartyMgr::_LeaveGroup;
	static hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID, char* name)> CPartyMgr::_ExpelGroupMember;
	static hook_method<void (CPartyMgr::*)(unsigned long AID, unsigned long GRID, int isOnLine)> CPartyMgr::_ServerMoveUser;
	static hook_method<int (CPartyMgr::*)(void)> CPartyMgr::_GetGroupSize;
	static hook_method<unsigned long (CPartyMgr::*)(void)> CPartyMgr::_GetFreeSize;
	static hook_method<enum CPartyMgr::enumResultINM (CPartyMgr::*)(CParty* const in_cpGroup, const USER_STRING_MAP_DATA* in_pNewMemberData)> CPartyMgr::_InsertNewMemberV2;
};


class CPartyMgr* __cdecl InstanceCPartyMgr(void);

