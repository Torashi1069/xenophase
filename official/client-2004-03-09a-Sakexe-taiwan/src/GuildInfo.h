#pragma once
#include "Struct.h"


class GuildInfo
{
	/* this+  0 */ public: mystd::string m_guildName;
	/* this+ 16 */ public: mystd::string m_masterName;
	/* this+ 32 */ public: mystd::string m_subjectName;
	/* this+ 48 */ public: mystd::string m_noticeName;
	/* this+ 64 */ public: int m_guildLevel;
	/* this+ 68 */ public: int m_numMember;
	/* this+ 72 */ public: int m_numMaxMember;
	/* this+ 76 */ public: int m_memberAvgLevel;
	/* this+ 80 */ public: mystd::string m_manageLand;
	/* this+ 96 */ public: int m_exp;
	/* this+100 */ public: int m_nextExp;
	/* this+104 */ public: int m_emblem;
	/* this+108 */ public: int m_point;
	/* this+112 */ public: int m_honor;
	/* this+116 */ public: int m_virtue;
	/* this+120 */ public: unsigned long m_zeny;
	/* this+124 */ public: int m_guildTabBitmask;
	/* this+128 */ public: int m_gdid;
	/* this+132 */ public: int m_emblemVersion;
	/* this+136 */ public: int m_rightJoin;
	/* this+140 */ public: int m_rightPunish;
	/* this+144 */ public: int m_amIMaster;
	/* this+148 */ public: int m_isRequestInfo[5];
	/* this+168 */ protected: mystd::list<GUILD_POSITION_INFORMATION> m_posInfoList;
	/* this+180 */ protected: mystd::list<GUILD_MEMBER_INFORMATION> m_memberInfoList;
	/* this+192 */ public: mystd::list<RELATED_GUILD_INFORMATION> m_relatedGuildInfoList;
	/* this+204 */ public: mystd::list<SGUILD_BANISH_INFO> m_banishList;
	/* this+216 */ public: mystd::list<SGUILD_INFO> m_guildList;
	/* this+228 */ public: mystd::map<int,mystd::string> m_positionIdNameMap;
	/* this+244 */ public: mystd::map<int,MEMBER_POSITION_INFORMATION> m_memberPositionInfoListForChange;
	/* this+260 */ public: mystd::map<int,GUILD_POSITION_INFORMATION> m_changedPositionInfoList;

	public: GuildInfo::GuildInfo(void);
	public: GuildInfo::~GuildInfo(void);
	public: void GuildInfo::Init(void);
	public: void GuildInfo::Init2(void);
	//public: void GuildInfo::RecalculateGuildExp();
	//public: void GuildInfo::AddMemberInfo(struct GUILD_MEMBER_INFORMATION *);
	//public: void GuildInfo::ClearMemberInfo();
	public: void GuildInfo::SetMemberInfoState(unsigned long AID, int status);
	public: void GuildInfo::SetMemberInfoState2(unsigned long AID, int status, unsigned long GID, short sex, short head, short headPalette);
	public: void GuildInfo::ChangeMemberPosition(int AID, int GID, int positionID);
	//public: int GuildInfo::RemoveMemberInfo(const char *);
	//public: class std::list<GUILD_MEMBER_INFORMATION,std::allocator<GUILD_MEMBER_INFORMATION> > & GetMemberInfoList();
	//public: struct GUILD_MEMBER_INFORMATION GuildInfo::GetMemberInfoByAID(unsigned long);
	//public: int GuildInfo::GetAIDbyName(const char *);
	//public: void GuildInfo::AddToBanishList(struct SGUILD_BANISH_INFO *);
	//public: void GuildInfo::UpdatePosInfo(struct GUILD_POSITION_INFORMATION);
	//public: class std::list<GUILD_POSITION_INFORMATION,std::allocator<GUILD_POSITION_INFORMATION> > & GetPosInfoList();
	public: void GuildInfo::DeleteRelatedGuild(int gdid, int relation);
	public: int GuildInfo::GetNumRelatedGuild(int relation);

private:
	static hook_method<void (GuildInfo::*)(void)> GuildInfo::_Init;
	static hook_method<void (GuildInfo::*)(void)> GuildInfo::_Init2;
	static hook_method<void (GuildInfo::*)(unsigned long AID, int status)> GuildInfo::_SetMemberInfoState;
	static hook_method<void (GuildInfo::*)(unsigned long AID, int status, unsigned long GID, short sex, short head, short headPalette)> GuildInfo::_SetMemberInfoState2;
	static hook_method<void (GuildInfo::*)(int AID, int GID, int positionID)> GuildInfo::_ChangeMemberPosition;
	static hook_method<void (GuildInfo::*)(int gdid, int relation)> GuildInfo::_DeleteRelatedGuild;
	static hook_method<int (GuildInfo::*)(int relation)> GuildInfo::_GetNumRelatedGuild;
};
