#pragma once
#include "GuildInfoPacketDispatcher.h"
#include "Guild.h"
#include "std/list"
#include "std/map"


class CIGuildInfo : public CGuild
{
	struct ServerInfo
	{
		/* this+0 */ unsigned long ServerID;
		/* this+4 */ int MemberNumber;
	};

	struct vtable_t // const CIGuildInfo::`vftable'
	{
		void* (CIGuildInfo::* vector_deleting_destructor)(unsigned int);
		void (CIGuildInfo::* Init)(void);
	};

	/* this+0x0    */ //CGuild
	/* this+0xFCC  */ public: CIGuildInfoPacketDispatcher m_packetDispatcher;
	/* this+0xFD4  */ protected: int m_bSkillSave;
	/* this+0xFD8  */ protected: CIGuildInfo::ServerInfo m_ZServerInfo[40];
	/* this+0x1118 */ protected: mystd::list<int> m_ZServerList;
	/* this+0x1124 */ protected: mystd::map<int,int> m_MemberZSID;
	/* this+0x1130 */ protected: int m_bAllNotifyInfo;
	/* this+0x1134 */ protected: unsigned long m_lastSaveTime;
	/* this+0x1138 */ protected: int m_DBInfoChange;
	/* this+0x113C */ protected: int m_InfoUse;

	public: CIGuildInfo::CIGuildInfo(void);
	public: virtual CIGuildInfo::~CIGuildInfo(void);
	//public: int CIGuildInfo::DisOrganizeGuild(unsigned long, int, int, int);
	//public: void CIGuildInfo::BanMember(const struct PACKET_ZI_REQ_BAN_GUILD *);
	//public: void CIGuildInfo::GetGuildNotice(char *);
	//public: void CIGuildInfo::RegisterGuildEmblem(char *, unsigned short);
	//public: int CIGuildInfo::AllLoadDB(unsigned long);
	//public: int CIGuildInfo::ReLoadDB();
	//public: int CIGuildInfo::GetMInfo(unsigned long);
	//public: void CIGuildInfo::GetAllyInfo(unsigned long);
	//public: void CIGuildInfo::GetBanishInfo(unsigned long);
	//public: int CIGuildInfo::GetMPosition(unsigned long);
	//public: int CIGuildInfo::DeleteMember(unsigned long);
	//public: int CIGuildInfo::DeleteMember(unsigned long, char *);
	//public: void CIGuildInfo::OnReqGuildPositionInfo(char *, unsigned short);
	public: HOOKED int CIGuildInfo::LoadSkill(int bNotify);
	//public: void CIGuildInfo::OnReqChangePosition(char *, unsigned short);
	//public: void CIGuildInfo::OnGuildSkillUpdate(char *);
	public: void CIGuildInfo::SaveSkillDB(void);
	public: virtual void CIGuildInfo::Init(void);
	//public: void CIGuildInfo::OnProcess(const unsigned long);
	//public: void CIGuildInfo::OnAddExp(char *);
	//public: void CIGuildInfo::OnUpdateGuildZeny(char *);
	public: void CIGuildInfo::UpdateCharGDID(unsigned char TYPE, unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long GDID, int EmblemVer);
	//public: int CIGuildInfo::DeleteRelatedGuild(unsigned long, unsigned long, int);
	public: void CIGuildInfo::JoinGuild(unsigned long ZSID, unsigned long GID, unsigned long AID, char* Name, char* Account, unsigned char answer);
	//public: void CIGuildInfo::GuildErrorLog(char *, int, char *);
	public: void CIGuildInfo::Send(int ZSID, short len, char* buf);
	public: void CIGuildInfo::NotifyGuildSkillInfo(unsigned long ZSID);
	//public: void CIGuildInfo::NotifyAllInfo(int);
	//public: void CIGuildInfo::UpdateMapName(const unsigned long, const char *);
	public: void CIGuildInfo::SetAllNotifyInfo(int bAllNotifyInfo);
	public: int CIGuildInfo::ChangeMemberInfo(unsigned long ZSID, unsigned long AID, unsigned long GID, int status);
	//public: void CIGuildInfo::ResetZoneServer(unsigned long);
	//public: int CIGuildInfo::FindZoneServer(unsigned long);
	//public: void CIGuildInfo::SetUseInfo(int);
	//public: int CIGuildInfo::GetUseInfo();
	//public: void CIGuildInfo::AddZoneServer(unsigned long);
	//public: void CIGuildInfo::RemoveZoneServer(unsigned long);
	public: void CIGuildInfo::OutPutGuildInfo(int bLevelUp);
	//public: int CIGuildInfo::ReloadGuildInfo();
	//public: int CIGuildInfo::ReloadAllyGuildInfo();

private:
	static hook_method<int (CIGuildInfo::*)(int bNotify)> CIGuildInfo::_LoadSkill;
	static hook_method<void (CIGuildInfo::*)(void)> CIGuildInfo::_SaveSkillDB;
	static hook_method<void (CIGuildInfo::*)(void)> CIGuildInfo::_Init;
	static hook_method<void (CIGuildInfo::*)(unsigned char TYPE, unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long GDID, int EmblemVer)> CIGuildInfo::_UpdateCharGDID;
	static hook_method<void (CIGuildInfo::*)(unsigned long ZSID, unsigned long GID, unsigned long AID, char* Name, char* Account, unsigned char answer)> CIGuildInfo::_JoinGuild;
	static hook_method<void (CIGuildInfo::*)(int ZSID, short len, char* buf)> CIGuildInfo::_Send;
	static hook_method<void (CIGuildInfo::*)(unsigned long ZSID)> CIGuildInfo::_NotifyGuildSkillInfo;
	static hook_method<void (CIGuildInfo::*)(int bAllNotifyInfo)> CIGuildInfo::_SetAllNotifyInfo;
	static hook_method<int (CIGuildInfo::*)(unsigned long ZSID, unsigned long AID, unsigned long GID, int status)> CIGuildInfo::_ChangeMemberInfo;
	static hook_method<void (CIGuildInfo::*)(int bLevelUp)> CIGuildInfo::_OutPutGuildInfo;
};
