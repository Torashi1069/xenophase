#pragma once
#include "QuestMission.h"


class CQuestEventMgr
{
private:
	typedef std::map<unsigned long,CQuestMission*> TQUEST;

public:
	CQuestEventMgr();
	virtual ~CQuestEventMgr();

private:
	enum
	{
		CMD_SETQUEST   = 0,
		CMD_SETMISSION = 1,
	};

public:
	bool Initialize();
	void Filnalize();
	bool AddQuest(unsigned long questID, TQUEST_MISSION* data);
//	bool GetQuest(unsigned long , TQUEST_MISSION* );
//	int GetMobMaxCount(unsigned long , unsigned long );
//	int GetMissionIdent(unsigned long , unsigned long );
//	unsigned long GetMissionPlayTime(unsigned long );
//	std::string GetMobName(unsigned long , unsigned long );
	bool IsQuest(unsigned long questID);

private:
	/* this+0 */ //const CQuestEventMgr::`vftable';
	/* this+4 */ TQUEST m_map;
};
