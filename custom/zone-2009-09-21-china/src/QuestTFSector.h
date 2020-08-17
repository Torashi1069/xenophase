#pragma once
#include "QuestMission.h"
#include "QVar.h"


class CQuestTFSector
{
	/* this+ 0 */ public: //const CQuestTFSector::`vftable';
	/* this+ 4 */ private: char* m_buff;
	/* this+ 8 */ private: int m_size;
	/* this+12 */ private: int m_pos;
	/* this+16 */ private: CQVar m_var;
	/* this+60 */ private: TQUEST_MISSION m_questMission;

	public: CQuestTFSector::CQuestTFSector(void);
	public: virtual CQuestTFSector::~CQuestTFSector(void);
	//public: bool CQuestTFSector::SetData(const char *, int);
	//public: bool CQuestTFSector::Parse(void);
	//private: int FindToken(const char &);
	//private: int FindString(const char *);
	//private: int Replace(const char *, const char *);
	//private: int DelteBuff(int);
	//private: char* SubStr(int);
	//private: int CQuestTFSector::LineComfile(const char *, int);
	//private: int CQuestTFSector::OnFunc(const char *, class CQVar *);
	//private: int CQuestTFSector::OnFuncQuest(unsigned long, const char *);
	//private: int CQuestTFSector::OnFuncHunt(const char *, int);
	//private: int CQuestTFSector::OnFuncTime(unsigned long);
};
