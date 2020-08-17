#pragma once
#include "ZGuildPacketDispatcher.h"
#include "shared/Guild.h"


class CZGuildInfo : public CGuild
{
public:
	void LoadEmblem();

public:
	CZGuildInfo();
	virtual ~CZGuildInfo();
	virtual void Init();

public:
	void OnAddExp(char* Buf);
	void OnGetMemberFrag(char* Buf);
	void DeleteRelatedGuild(char* Buf);
	int GetGuildMInfo(char* Buf, const int in_nMaxBufSize);
	BOOL ConvertGuildMInfo(GUILDMINFO MInfo, GUILD_MEMBER_INFO& Info);
	void GuildMemberAdd(char* buf);
	void SendGuildNotice(unsigned long AID);
	void GetGuildNotice(char* buf);
	void GetGuildPosition(char* buf, unsigned short Len);
	void ChangeMemberPosition(char* buf, unsigned short Len);
	void DisOrganizeGuild(char* Buf);
	void SendGuildChat(char* Notice, int PacketLen);
	void SendAllyGuildResult(unsigned char answer);
	void SetCompressedEmblemImage(const char* compressedEmblemImage, unsigned long emblemLen, int GDID, int emblemVersion);
	void SendAckBanGuild(char* CharName, char* AccountName, char* Reason);
	void SendAckLeaveGuild(char* CharName, char* AccountName, char* Reason);
	void BroadCast(int Len, char* Buf);
	void DeleteMember(unsigned long GID);
	void BanMember(char* Buf);
	void OnZenyUpdateAll(char* Buf);
	void NotifySkillInfo(unsigned long AID);
	void OnNotifySkillData(char* Buf, unsigned short Len);
	void UpgradeSkillLevel(unsigned short SKID);
	int GetSkillLevel(unsigned short SKID);
	void MapChange(unsigned long AID, char* MapName);
	void NotifyPositionToGuild(unsigned long AID, short xPos, short yPos, int MapID);
	std::vector<GUILDMINFO*>::iterator GetStartGuildIter();
	std::vector<GUILDMINFO*>::iterator GetEndGuildIter();

	void SetEmblem(const char* in_guildEmblem, int in_emblemSize, int in_emblemVersion); /// @custom

public:
	/* this+   0 */ //CGuild baseclass_0;
	/* this+3996 */ std::map<unsigned short,unsigned short> m_skill;
	/* this+4012 */ unsigned long MemberFragNum;
	/* this+4016 */ CZGuildInfoPacketDispatcher m_packetDispatcher;
	/* this+4024 */ int m_JoinGID;

public:
	void SetJoinGID(int GID);
	int GetJoinGID();

private:
	BOOL IsEnableSkill(unsigned short SKID);
};
