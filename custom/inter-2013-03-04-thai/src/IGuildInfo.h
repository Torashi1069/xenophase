#pragma once
#include "GuildInfoPacketDispatcher.h"
#include "shared/Guild.h"
struct PACKET_ZI_REQ_BAN_GUILD;


class CIGuildInfo : public CGuild
{
public:
	CIGuildInfo();
	virtual ~CIGuildInfo();

public:
	BOOL DisOrganizeGuild(unsigned long ZSID, int GDID, int AID, int GID);
	void BanMember(const PACKET_ZI_REQ_BAN_GUILD* in_pPacket);
	void GetGuildNotice(char* buf);
	void RegisterGuildEmblem(char* buf, unsigned short Len);
	BOOL AllLoadDB(unsigned long GDID);
	BOOL ReLoadDB();
	BOOL GetMInfo(unsigned long GDID);
	void GetAllyInfo(unsigned long GDID);
	void GetBanishInfo(unsigned long GDID);
	BOOL GetMPosition(unsigned long GDID);
	BOOL DeleteMember(unsigned long ZSID, char* Buf);
	BOOL DeleteMember(unsigned long GID);
	void OnReqGuildPositionInfo(char* buf, unsigned short Len);
	BOOL LoadSkill(BOOL bNotify);
	void OnReqChangePosition(char* buf, unsigned short Len);
	void OnGuildSkillUpdate(char* buf);
	void SaveSkillDB();
	virtual void Init();
	void OnProcess(const unsigned long CurTime);
	void OnAddExp(char* buf);
	void OnUpdateGuildZeny(char* buf);
	void UpdateCharGDID(unsigned char TYPE, unsigned long ZSID, unsigned long AID, unsigned long GID, unsigned long GDID, int EmblemVer);
	BOOL DeleteRelatedGuild(unsigned long GDID, unsigned long OpponentGDID, int Relation);
	void JoinGuild(unsigned long ZSID, unsigned long GID, unsigned long AID, char* Name, char* Account, unsigned char answer);
	void GuildErrorLog(char* buf, int line, char* filename);
	void Send(int ZSID, short len, char* buf);

	/* this+4028 */ CIGuildInfoPacketDispatcher m_packetDispatcher;

	void NotifyGuildSkillInfo(unsigned long ZSID);
	void NotifyAllInfo(int ZSID);
	void UpdateMapName(const unsigned long AID, const char* mapName);
	void SetAllNotifyInfo(BOOL bAllNotifyInfo);
	BOOL ChangeMemberInfo(unsigned long ZSID, unsigned long AID, unsigned long GID, int status);
	void ResetZoneServer(unsigned long ZSID);
	BOOL FindZoneServer(unsigned long ZSID);
	void SetUseInfo(BOOL InfoUse);
	BOOL GetUseInfo();
	void AddZoneServer(unsigned long ZSID);
	void RemoveZoneServer(unsigned long ZSID);
	void OutPutGuildInfo(BOOL bLevelUp);
	BOOL ReloadGuildInfo();
	BOOL ReloadAllyGuildInfo();

protected:
	/* this+4036 */ BOOL m_bSkillSave;
	struct ServerInfo {
		/* this+0 */ unsigned long ServerID;
		/* this+4 */ int MemberNumber;
	};
	/* this+4040 */ ServerInfo m_ZServerInfo[40];
	/* this+4360 */ std::list<int> m_ZServerList;
	/* this+4388 */ std::map<int,int> m_MemberZSID;
	/* this+4420 */ BOOL m_bAllNotifyInfo;
	/* this+4424 */ unsigned long m_lastSaveTime;
	/* this+4428 */ int m_DBInfoChange;
	/* this+4432 */ BOOL m_InfoUse;
};
