#pragma once


struct TDATA_HUNT
{
	/* this+ 0 */ int huntIdent;
	/* this+ 4 */ unsigned long mobIdent;
	/* this+ 8 */ char mobName[24];
	/* this+32 */ int max_huntCount;
};


struct TQUEST_MISSION
{
	/* this+  0 */ unsigned long questID;
	/* this+  4 */ char questName[64];
	/* this+ 68 */ int hunt_count;
	/* this+ 72 */ TDATA_HUNT hunt[3];
	/* this+180 */ unsigned long time;
};


class CQuestMission
{
	struct THUNT
	{
		/* this+ 0 */ int m_ident;
		/* this+ 4 */ unsigned long m_mobIdent;
		/* this+ 8 */ char m_mobName[24];
		/* this+32 */ int m_maxCount;
	};

	/* this+  0 */ public: //const CQuestMission::`vftable';
	/* this+  4 */ private: unsigned long m_questID;
	/* this+  8 */ private: char m_questName[64];
	/* this+ 72 */ private: int m_huntCount;
	/* this+ 76 */ private: TDATA_HUNT m_hunt[3];
	/* this+184 */ private: unsigned long m_playTime;

	public: CQuestMission::CQuestMission(void);
	public: virtual CQuestMission::~CQuestMission(void);
	public: int CQuestMission::SetQuest(unsigned long questID, TQUEST_MISSION* data);
	public: bool CQuestMission::GetQuest(TQUEST_MISSION* quest);
	public: int CQuestMission::GetMobMaxCount(unsigned long mobGID);
	public: int CQuestMission::GetMissionIdent(unsigned long mobGID);
	public: mystd::string CQuestMission::GetMobName(unsigned long mobGID);
	public: unsigned long CQuestMission::GetMissionPlayTime(void);

private:
	static hook_method<int (CQuestMission::*)(unsigned long questID, TQUEST_MISSION* data)> CQuestMission::_SetQuest;
	static hook_method<bool (CQuestMission::*)(TQUEST_MISSION* quest)> CQuestMission::_GetQuest;
	static hook_method<int (CQuestMission::*)(unsigned long mobGID)> CQuestMission::_GetMobMaxCount;
	static hook_method<int (CQuestMission::*)(unsigned long mobGID)> CQuestMission::_GetMissionIdent;
	static hook_method<mystd::string (CQuestMission::*)(unsigned long mobGID)> CQuestMission::_GetMobName;
	static hook_method<unsigned long (CQuestMission::*)(void)> CQuestMission::_GetMissionPlayTime;
};
