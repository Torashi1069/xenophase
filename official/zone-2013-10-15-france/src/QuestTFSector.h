#pragma once
#include "QuestMission.h"
#include "QVar.h"


class CQuestTFSector
{
public:
	CQuestTFSector();
	virtual ~CQuestTFSector();

private:
	/* this+ 0 */ //const CQuestTFSector::`vftable';
	/* this+ 4 */ char* m_buff;
	/* this+ 8 */ int m_size;
	/* this+12 */ int m_pos;
	/* this+16 */ CQVar m_var;
	/* this+60 */ TQUEST_MISSION m_questMission;

public:
	bool SetData(const char* buff, int len);
	bool Parse();

private:
	int FindToken(const char& p);
	int FindString(const char* ptr);
	int Replace(const char* strOld, const char* strNew);
	int DelteBuff(int pos);
	char* SubStr(int pos);
	int LineComfile(const char* buff, int size);
	int OnFunc(const char* cmd, CQVar* par);
	int OnFuncQuest(unsigned long questID, const char* questName);
	int OnFuncHunt(const char* spriteName, int maxCount);
	int OnFuncTime(unsigned long playTime);
};
