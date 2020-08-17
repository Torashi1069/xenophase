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
public:
	CQuestMission();
	virtual ~CQuestMission();

private:
	struct THUNT
	{
		/* this+ 0 */ int m_ident;
		/* this+ 4 */ unsigned long m_mobIdent;
		/* this+ 8 */ char m_mobName[24];
		/* this+32 */ int m_maxCount;
	};

private:
	/* this+  0 */ //const CQuestMission::`vftable';
	/* this+  4 */ unsigned long m_questID;
	/* this+  8 */ char m_questName[64];
	/* this+ 72 */ int m_huntCount;
	/* this+ 76 */ TDATA_HUNT m_hunt[3];
	/* this+184 */ unsigned long m_playTime;

public:
	int SetQuest(unsigned long questID, TQUEST_MISSION* data);
	bool GetQuest(TQUEST_MISSION* quest);
	int GetMobMaxCount(unsigned long mobGID);
	int GetMissionIdent(unsigned long mobGID);
	std::string GetMobName(unsigned long mobGID);
	unsigned long GetMissionPlayTime();
};
