#pragma once
class CPC; // #include "PC.h"
class CQuestEventInfo;
class CMission_Hunt;


class CPCQuestEvent
{
private:
	typedef std::map<unsigned long,CQuestEventInfo*> TQUEST_MAP;
	typedef std::list<unsigned long> TARLIMILIST;
	typedef std::map<unsigned long,CMission_Hunt*> TMISSION_MAP;
	typedef std::vector<unsigned long> TCOMPLETEQUEST_VT;

public:
	CPCQuestEvent();
	virtual ~CPCQuestEvent();

private:
	/* this+  0 */ //const CPCQuestEvent::`vftable';
	/* this+  4 */ CPC* m_owner;
	/* this+  8 */ BYTE m_hunt_relation[36]; // CPCQuestRelationShip m_hunt_relation; //TODO
	/* this+ 44 */ BYTE m_huntIndex[20]; // CPCHuntIndex m_huntIndex; //TODO
	/* this+ 64 */ TQUEST_MAP m_map;
	/* this+ 80 */ TMISSION_MAP m_huntMap;
	/* this+ 96 */ TCOMPLETEQUEST_VT m_vCompleteQuest;
	/* this+112 */ TARLIMILIST m_arlimiList;
	/* this+124 */ bool m_isUpdateData;

public:
	bool InIt(CPC* pc);
	void Reset();
//	bool AsyncDBComplete_LoadQuestEvent(const unsigned char *, const int, const unsigned char *, const int, const unsigned char *, const int, const unsigned char *, const int);
//	void AsyncDB_SaveQuestEvent();
//	int Save_QuestInfo(unsigned char *, int);
//	int Save_CompleteQuest(unsigned char *, int);
//	int Save_Quest_Hunt(unsigned char *, int);
//	int Save_Quest_Time(unsigned char *, int);
//	int OnMessage(int, int, int);
//	void UpdateMission_Hunt(unsigned long);
	int IsBeginQuest(unsigned long questID);
//	int CheckQuest_Hunting(unsigned long);
//	int CheckQuest_PlayTime(unsigned long);
//	void OnActiveQuest(unsigned long, bool);
//	void SetUpdateData();
//	bool GetUpdateData();
	void SetArlimiList(unsigned long npcID);
	unsigned long GetArlimiList();
	void ResetArlimiList();

private:
//	bool Parsing_QuestInfo(const unsigned char *, const int);
//	bool Parsing_Hunting(const unsigned char *, const int);
//	bool Parsing_Time(const unsigned char *, const int);
//	bool Parsing_Complete(const unsigned char *, const int);
//	bool InsertQuest(unsigned long, bool);
//	bool AddMission(unsigned long, bool, long, int, const char *, int);
//	bool Add_HuntingMission(unsigned long, unsigned long, int);
//	bool Add_TimeMission(unsigned long, long);
//	int AddQuest(unsigned long);
//	void DeleteHuntList(unsigned long);
//	int FuncSetQuest(unsigned long);
//	bool FuncCompleteQuest(unsigned long);
//	bool FuncEraseQuest(unsigned long);
//	bool FuncChangQuest(unsigned long, unsigned long);
//	bool FuncCompleteQuest_Between(unsigned long, unsigned long);
//	bool FuncRecall_ComplereQuest(unsigned long);
//	bool SendAllQuest();
//	class CMission_Hunt * GetMission(int);
//	bool SetCompleteQuest(unsigned long);
	bool FindCompleteQuest(unsigned long quest);
	bool IsQuest(unsigned long quest);
//	class CQuestEventInfo * FindQuestInfo(unsigned long);
};
