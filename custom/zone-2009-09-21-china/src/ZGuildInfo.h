#pragma once
#include "Guild.h"
#include "ZGuildInfoPacketDispatcher.h"
#include "std/map"


class CZGuildInfo : public CGuild
{
	struct vtable_t // const CZGuildInfo::`vftable'
	{
		void* (CZGuildInfo::* scalar_deleting_destructor)(unsigned int flags);
		void (CZGuildInfo::* Init)(void);
	};

	/* this+   0 */ public: //CGuild baseclass_0;
	/* this+4044 */ public: mystd::map<unsigned short,unsigned short> m_skill;
	/* this+4056 */ public: unsigned long MemberFragNum;
	/* this+4060 */ public: CZGuildInfoPacketDispatcher m_packetDispatcher;
	/* this+4068 */ public: int m_JoinGID;

	public: CZGuildInfo::CZGuildInfo(void);
	public: virtual CZGuildInfo::~CZGuildInfo(void);
	public: virtual void CZGuildInfo::Init(void);
	public: void CZGuildInfo::LoadEmblem(void);
	public: void CZGuildInfo::OnAddExp(char* Buf);
	public: void CZGuildInfo::OnGetMemberFrag(char* Buf);
	public: void CZGuildInfo::DeleteRelatedGuild(char* Buf);
	public: int CZGuildInfo::GetGuildMInfo(char* Buf);
	//public: int CZGuildInfo::ConvertGuildMInfo(GUILDMINFO, GUILD_MEMBER_INFO &);
	//public: void CZGuildInfo::GuildMemberAdd(char *);
	public: HOOKED void CZGuildInfo::SendGuildNotice(unsigned long AID);
	public: void CZGuildInfo::GetGuildNotice(char* buf);
	//public: void CZGuildInfo::GetGuildEmblem(char *, unsigned short);
	//public: void CZGuildInfo::GetGuildPosition(char *, unsigned short);
	//public: void CZGuildInfo::ChangeMemberPosition(char *, unsigned short);
	//public: void CZGuildInfo::DisOrganizeGuild(char *);
	//public: void CZGuildInfo::SendGuildChat(char *, int);
	//public: void SendAllyGuildResult(unsigned char);
	//public: void SetCompressedEmblemImage(const char *, unsigned long, int, int);
	//public: void SendAckBanGuild(char *, char *, char *);
	//public: void SendAckLeaveGuild(char *, char *, char *);
	public: void CZGuildInfo::BroadCast(int Len, char* Buf);
	//public: void CZGuildInfo::DeleteMember(unsigned long);
	//public: void CZGuildInfo::BanMember(char *);
	//public: void CZGuildInfo::OnZenyUpdateAll(char *);
	public: void CZGuildInfo::NotifySkillInfo(unsigned long AID);
	public: HOOKED void CZGuildInfo::OnNotifySkillData(char* Buf, unsigned short Len);
	//public: void CZGuildInfo::UpgradeSkillLevel(unsigned short);
	public: int CZGuildInfo::GetSkillLevel(unsigned short SKID);
	//public: void CZGuildInfo::MapChange(unsigned long, char *);
	//public: void CZGuildInfo::NotifyPositionToGuild(unsigned long, short, short, int);
	//public: mystd::vector<GUILDMINFO*>::iterator GetStartGuildIter();
	//public: mystd::vector<GUILDMINFO*>::iterator GetEndGuildIter();
	//public: void SetJoinGID(int);
	public: int CZGuildInfo::GetJoinGID(void);
	//private: int CZGuildInfo::IsEnableSkill(unsigned short);

private:
	static hook_method<void (CZGuildInfo::*)(void)> CZGuildInfo::_Init;
	static hook_method<void (CZGuildInfo::*)(void)> CZGuildInfo::_LoadEmblem;
	static hook_method<void (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_OnAddExp;
	static hook_method<void (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_OnGetMemberFrag;
	static hook_method<void (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_DeleteRelatedGuild;
	static hook_method<int  (CZGuildInfo::*)(char* Buf)> CZGuildInfo::_GetGuildMInfo;
	static hook_method<void (CZGuildInfo::*)(unsigned long AID)> CZGuildInfo::_SendGuildNotice;
	static hook_method<void (CZGuildInfo::*)(char* buf)> CZGuildInfo::_GetGuildNotice;
	static hook_method<void (CZGuildInfo::*)(int Len, char* Buf)> CZGuildInfo::_BroadCast;
	static hook_method<void (CZGuildInfo::*)(unsigned long AID)> CZGuildInfo::_NotifySkillInfo;
	static hook_method<void (CZGuildInfo::*)(char* Buf, unsigned short Len)> CZGuildInfo::_OnNotifySkillData;
	static hook_method<int  (CZGuildInfo::*)(unsigned short SKID)> CZGuildInfo::_GetSkillLevel;
	static hook_method<int  (CZGuildInfo::*)(void)> CZGuildInfo::_GetJoinGID;
};
