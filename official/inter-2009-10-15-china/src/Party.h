#pragma once
#include "NetLib/MemoryMgr.h"
#include "structs.hpp"
#include "std/vector"

struct PACKET_IZ_PARTY_BROADCAST;

class CParty
{
	struct vtable_t // const CParty::`vftable'
	{
		void* (CParty::* scalar_deleting_destructor)(unsigned int __flags);
	};

	/* this+ 0 */ public: //const CParty::`vftable';
	/* this+ 4 */ private: unsigned long m_groupID;
	/* this+ 8 */ private: GROUP_INFO m_groupInfo;
	/* this+14 */ private: char m_groupName[24];
	/* this+40 */ private: mystd::vector<CHARINFO_IN_GROUP*> m_users;
	/* this+56 */ private: CMemoryMgr<CHARINFO_IN_GROUP> m_userMPool;

	public: CParty::CParty(void);
	public: virtual CParty::~CParty(void);
	public: int CParty::IsDupeMember(unsigned long AID);
	public: void CParty::Init(void);
	public: int CParty::GetMemberCount(void);
	public: int CParty::AddMember(CHARINFO_IN_GROUP* par, int option);
	public: int CParty::DeleteMember(unsigned long AID, unsigned long GID, unsigned char type);
	public: int CParty::UpdateState(unsigned long AID, unsigned char state);
	public: void CParty::SetGroupID(unsigned long GRID);
	public: unsigned long CParty::GetGroupID(void);
	public: void CParty::SetGroupName(const char* gname);
	public: char* CParty::GetGroupName(void);
	public: void CParty::SetPartyRole(unsigned char ItemPickupRule, unsigned char ItemDivisionRule);
	public: unsigned long CParty::SearchGID(char* name);
	public: unsigned long CParty::SearchGID(unsigned long AID);
	public: unsigned long CParty::GetMaster(void);
	public: CHARINFO_IN_GROUP* CParty::GetGroupInfo(unsigned long AID);
	public: int CParty::GetConnectedMember(void);
	public: void CParty::NotifyGroupMembers(unsigned long AID);
	public: void CParty::UpdateMapName(unsigned long AID, char* mapName);
	public: void CParty::UpdateMapName2(unsigned long AID, char* mapName);
	public: void CParty::OnChat(unsigned long AID, int len, char* buf);
	public: unsigned long CParty::GetGroupEXPOption(void);
	public: void CParty::UpdateExpOption(unsigned long option);
	public: int CParty::IsExpSharable(void);
	public: void CParty::NotifyUpdateExpOption(unsigned long AID, unsigned long option);
	public: void CParty::CheckExpSharableInfo(void);
	public: void CParty::ChangeGroupInfo(GROUP_INFO Info);
	public: void CParty::OnChangeGroupMaster(unsigned long MasterAID, unsigned long AID);
	public: void CParty::Send(const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket);
	private: void CParty::DeleteAll(void);
	private: void CParty::BroadCast(int len, char* buf);
	private: CHARINFO_IN_GROUP* CParty::SearchMember(unsigned long AID);

private:
	static hook_method<int (CParty::*)(unsigned long AID)> CParty::_IsDupeMember;
	static hook_method<void (CParty::*)(void)> CParty::_Init;
	static hook_method<int (CParty::*)(void)> CParty::_GetMemberCount;
	static hook_method<int (CParty::*)(CHARINFO_IN_GROUP* par, int option)> CParty::_AddMember;
	static hook_method<int (CParty::*)(unsigned long AID, unsigned long GID, unsigned char type)> CParty::_DeleteMember;
	static hook_method<int (CParty::*)(unsigned long AID, unsigned char state)> CParty::_UpdateState;
	static hook_method<void (CParty::*)(unsigned long GRID)> CParty::_SetGroupID;
	static hook_method<unsigned long (CParty::*)(void)> CParty::_GetGroupID;
	static hook_method<void (CParty::*)(const char* gname)> CParty::_SetGroupName;
	static hook_method<char* (CParty::*)(void)> CParty::_GetGroupName;
	static hook_method<void (CParty::*)(unsigned char ItemPickupRule, unsigned char ItemDivisionRule)> CParty::_SetPartyRole;
	static hook_method<unsigned long (CParty::*)(char* name)> CParty::_SearchGID;
	static hook_method<unsigned long (CParty::*)(unsigned long AID)> CParty::_SearchGID2;
	static hook_method<unsigned long (CParty::*)(void)> CParty::_GetMaster;
	static hook_method<CHARINFO_IN_GROUP* (CParty::*)(unsigned long AID)> CParty::_GetGroupInfo;
	static hook_method<int (CParty::*)(void)> CParty::_GetConnectedMember;
	static hook_method<void (CParty::*)(unsigned long AID)> CParty::_NotifyGroupMembers;
	static hook_method<void (CParty::*)(unsigned long AID, char* mapName)> CParty::_UpdateMapName;
	static hook_method<void (CParty::*)(unsigned long AID, char* mapName)> CParty::_UpdateMapName2;
	static hook_method<void (CParty::*)(unsigned long AID, int len, char* buf)> CParty::_OnChat;
	static hook_method<unsigned long (CParty::*)(void)> CParty::_GetGroupEXPOption;
	static hook_method<void (CParty::*)(unsigned long option)> CParty::_UpdateExpOption;
	static hook_method<int (CParty::*)(void)> CParty::_IsExpSharable;
	static hook_method<void (CParty::*)(unsigned long AID, unsigned long option)> CParty::_NotifyUpdateExpOption;
	static hook_method<void (CParty::*)(void)> CParty::_CheckExpSharableInfo;
	static hook_method<void (CParty::*)(GROUP_INFO Info)> CParty::_ChangeGroupInfo;
	static hook_method<void (CParty::*)(unsigned long MasterAID, unsigned long AID)> CParty::_OnChangeGroupMaster;
	static hook_method<void (CParty::*)(const int in_Length, PACKET_IZ_PARTY_BROADCAST* in_pPartyBroadCastPacket)> CParty::_Send;
	static hook_method<void (CParty::*)(void)> CParty::_DeleteAll;
	static hook_method<void (CParty::*)(int len, char* buf)> CParty::_BroadCast;
	static hook_method<CHARINFO_IN_GROUP* (CParty::*)(unsigned long AID)> CParty::_SearchMember;
};
