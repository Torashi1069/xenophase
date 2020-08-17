#pragma once
#include "Common/Packet.h"
#include "NetLib/MemoryMgr.h"


enum enumGROUPEXPOPTION
{
	EXP_NOTSHARED         = 0,
	EXP_SHARED            = 1,
	EXP_CHANGE_IMPOSSIBLE = 2,
};


enum enumGROUPMEMBERROLE
{
	GROUPMEMBER_ROLE_MASTER  = 0,
	GROUPMEMBER_ROLE_GENERAL = 1,
};


enum enumGROUPMEMBERSTATE
{
	GROUPMEMBER_STATE_CONNECTED    = 0,
	GROUPMEMBER_STATE_DISCONNEDTED = 1,
};


enum enumGROUPMEMBERDELETETYPE
{
	GROUPMEMBER_DELETE_LEAVE         = 0,
	GROUPMEMBER_DELETE_EXPEL         = 1,
	GROUPMEMBER_PREVENT_DELETE_LEAVE = 2,
	GROUPMEMBER_PREVENT_DELETE_EXPEL = 3,
};


#pragma pack(push,1)
///

struct GROUP_INFO
{
	/* this+0 */ unsigned long expOption; // enumGROUPEXPOPTION
	/* this+4 */ bool ItemPickupRule;
	/* this+5 */ bool ItemDivisionRule;
};


struct CHARINFO_IN_GROUP
{
	/* this+ 0 */ unsigned long AID;
	/* this+ 4 */ unsigned long GID;
	/* this+ 8 */ char charName[24];
	/* this+32 */ unsigned char Role; // enumGROUPMEMBERROLE
	/* this+33 */ unsigned char curState; // enumGROUPMEMBERSTATE
};

///
#pragma pack(pop)


class CParty
{
public:
	CParty();
	virtual ~CParty();

public:
	BOOL IsDupeMember(unsigned long AID);
	void Init();
	int GetMemberCount();
	BOOL AddMember(CHARINFO_IN_GROUP* par, int option);
	BOOL DeleteMember(unsigned long AID, unsigned long GID, unsigned char type);
	BOOL UpdateState(unsigned long AID, unsigned char state);
	void SetGroupID(unsigned long GRID);
	unsigned long GetGroupID();
	void SetGroupName(const char* gname);
	char* GetGroupName();
	void SetPartyRole(bool ItemPickupRule, bool ItemDivisionRule);
	unsigned long SearchGID(unsigned long AID);
	unsigned long SearchGID(char* name);
	unsigned long GetMaster();
	CHARINFO_IN_GROUP* GetGroupInfo(unsigned long AID);
	int GetConnectedMember();
	void NotifyGroupMembers(unsigned long AID);
	void UpdateMapName(unsigned long AID, char* mapName);
	void UpdateMapName2(unsigned long AID, const char* mapName);
	void OnChat(unsigned long AID, int len, char* buf);
	unsigned long GetGroupEXPOption();
	void UpdateExpOption(const unsigned long in_option, const bool in_bNotify);
	BOOL IsExpSharable() const;
	void NotifyUpdateExpOption(unsigned long AID, unsigned long option);
	void CheckExpSharableInfo();
	void ChangeGroupInfo(GROUP_INFO Info);
	void OnChangeGroupMaster(unsigned long MasterAID, unsigned long AID);
	void Send(const int in_HsvrID, const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket);
	void Send(const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket);
	void Send(const int in_HsvrID, const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket);
	void Send(const int in_Length, PACKET_IZ_PARTY_BROADCAST_VAR* in_pPartyBroadCastPacket);
	void GetPartyMemberOnlineList(std::list<unsigned long>& out_listGID);
	void SendIZBroadcastEntryQueueApply(const int in_ZSID, const unsigned long in_AID, const unsigned long in_GID, const std::string in_EntryQueueName, const short in_ApplyType);
	bool IsBattleFieldMapLocation() const;

private:
	void DeleteAll();
	void BroadCast(int len, char* buf);

private:
	/* this+ 0 */ //const CParty::`vftable';
	/* this+ 4 */ unsigned long m_groupID;
	/* this+ 8 */ GROUP_INFO m_groupInfo;
	/* this+14 */ char m_groupName[24];

	CHARINFO_IN_GROUP* SearchMember(unsigned long AID);

	typedef std::vector<CHARINFO_IN_GROUP*> MEMBER_CONTAINER;
	typedef std::vector<CHARINFO_IN_GROUP*>::iterator MEMBER_CONTAINER_ITER;
	/* this+40 */ MEMBER_CONTAINER m_users;
	/* this+64 */ CMemoryMgr<CHARINFO_IN_GROUP> m_userMPool;
};
