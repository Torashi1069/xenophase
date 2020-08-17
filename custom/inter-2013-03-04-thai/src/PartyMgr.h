#pragma once
#include "Party.h"
#include "UserMgr.h"
#include "Common/Packet.h"
#include "NetLib/MemoryMgr.h"


class CPartyMgr
{
private:
	bool DeleteMember(const unsigned long in_PartyID, const USER_STRING_MAP_DATA* in_pUser, const unsigned long in_type);

public:
	void Send(const int in_HsvrID, const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket);
	void Send(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket);
	void Send(const int in_HsvrID, const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket);
	void Send(const unsigned long in_GRID, const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket);
	void MapMove2(const unsigned long in_hPartyID, const unsigned long in_AID, const char* in_pMapName);
	CParty* SearchGroup(const char* in_pPartyName);
	CParty* SearchGroup(unsigned long GRID);

public:
	CPartyMgr();
	virtual ~CPartyMgr();
	void Init(int MaxParty, const char* FileDsn, const char* PASS);

	const int GetMaxMemberNum();
	enum { MAX_PARTY_MEMBER_NUM = 30 };

	unsigned long MakeGroup(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name);
	unsigned long MakeGroup2(unsigned long AID, unsigned long GID, unsigned long& GRID, char* name, bool bItemPickupRule, bool bItemDivisionRule);
	void GetGroupName(unsigned long GRID, char* buf);
	void GetGroupInfo(unsigned long GRID, char* buf, bool& ItemPickupRule, bool& ItemDivisionRule);
	BOOL DeleteGroup(unsigned long GRID);
	int InsertNewMember(unsigned long AID, unsigned long GRID);
	unsigned long SearchMember(unsigned long GID);
	unsigned long GetGroupOwner(unsigned long GRID);
	void LogonNewUser(unsigned long AID, unsigned long GRID);
	void LoadGroupInfoFromDB(unsigned long AID, unsigned long GRID);
	void UserExit(unsigned long AID, unsigned long GRID);
	BOOL FreeGroup(unsigned long GRID);
	void NotifyGroupMembers(unsigned long AID, unsigned long GRID);
	bool LeaveGroup(const unsigned long in_AID, const unsigned long in_GID);
	void ExpelGroupMember(unsigned long AID, unsigned long GRID, char* name);
	void ServerMoveUser(unsigned long AID, unsigned long GRID, BOOL isOnline);
	int GetGroupSize();
	unsigned long GetFreeSize();

	enum enumResultINM
	{
		RESULTINM_UNKNOWN_GROUP   = 0,
		RESULTINM_OVERSIZE_MEMBER = 1,
		RESULTINM_DUPLICATE_AID   = 2,
		RESULTINM_UNKNOWN_ERROR   = 3,
		RESULTINM_SUCCESS         = 4,
	};

	enumResultINM InsertNewMemberV2(CParty* const in_cpGroup, const USER_STRING_MAP_DATA* in_pNewMemberData);

private:
	/* this+ 0 */ //const CPartyMgr::`vftable';
	/* this+ 4 */ std::map<unsigned long,CParty*> m_group;
	/* this+36 */ CMemoryMgr<CParty> m_groupMPool;
	/* this+76 */ int m_MaxPartyMemberNum;
};
