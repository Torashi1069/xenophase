#pragma once
#include "PCHuntIndex.h"
#include "std/map"
#include "std/vector"
class CMission_Hunt;
class CPC;
class CQuestEventInfo;


class CPCQuestEvent
{
public:
	typedef mystd::map<unsigned long,CQuestEventInfo*> TQUEST_MAP;
	typedef mystd::map<unsigned long,CMission_Hunt*> TMISSION_MAP;
	typedef mystd::vector<unsigned long> TCOMPLETEQUEST_VT;

public:
	CPCQuestEvent();
	virtual ~CPCQuestEvent();

protected:
	/* this+ 0 */ //const CPCQuestEvent::`vftable';
	/* this+ 4 */ CPC* m_owner;
	/* this+ 8 */ CPCHuntIndex m_huntIndex;
	/* this+24 */ TQUEST_MAP m_map;
	/* this+36 */ TCOMPLETEQUEST_VT m_vCompleteQuest;
	/* this+52 */ TMISSION_MAP m_huntMap;
	/* this+64 */ bool m_isUpdateData;

public:
	bool InIt(CPC* pc);
	void Reset();
	//public: bool AsyncLoadQuestEvent();
	public: bool AsyncDBComplete_LoadQuestEvent(const unsigned char* in_pData_quest, const int in_Length_quest, const unsigned char* in_pData_hunt, const int in_Length_hunt, const unsigned char* in_pData_time, const int in_Length_time, const unsigned char* in_pData_complete, const int in_Length_complete);
	//public: void AsyncDB_SaveQuestEvent();
	public: int CPCQuestEvent::Save_QuestInfo(unsigned char* buff, int maxSize);
	public: int CPCQuestEvent::Save_CompleteQuest(unsigned char* buff, int maxSize);
	public: int CPCQuestEvent::Save_Quest_Hunt(unsigned char* buff, int maxSize);
	public: int CPCQuestEvent::Save_Quest_Time(unsigned char* buff, int maxSize);
	public: int CPCQuestEvent::OnMessage(int msg, int par1, int par2);
	public: void UpdateMission_Hunt(unsigned long mobGID);
	//public: int CPCQuestEvent::IsBeginQuest(unsigned long);
	//public: int CPCQuestEvent::CheckQuest_Hunting(unsigned long);
	//public: int CPCQuestEvent::CheckQuest_PlayTime(unsigned long);
	//public: int ShowQuestEffect(unsigned long);
	//public: void CPCQuestEvent::OnActiveQuest(unsigned long, bool);
	public: void SetUpdateData();
	public: bool GetUpdateData();
	//private: bool CPCQuestEvent::Parsing_QuestInfo(const unsigned char *, const int);
	//private: bool CPCQuestEvent::Parsing_Hunting(const unsigned char *, const int);
	//private: bool CPCQuestEvent::Parsing_Time(const unsigned char *, const int);
	//private: bool CPCQuestEvent::Parsing_Complete(const unsigned char *, const int);
	//private: bool CPCQuestEvent::InsertQuest(unsigned long, bool);
	//private: bool AddMission(unsigned long, bool, long, int, const char *, int);
	//private: bool CPCQuestEvent::Add_HuntingMission(unsigned long, unsigned long, int);
	//private: bool CPCQuestEvent::Add_TimeMission(unsigned long, long);
	//private: int CPCQuestEvent::AddQuest(unsigned long);
	//private: void CPCQuestEvent::DeleteHuntList(unsigned long);
	//private: int CPCQuestEvent::FuncSetQuest(unsigned long);
	//private: bool CPCQuestEvent::FuncCompleteQuest(unsigned long);
	//private: bool CPCQuestEvent::FuncEraseQuest(unsigned long);
	//private: bool CPCQuestEvent::FuncChangQuest(unsigned long, unsigned long);
	//private: bool CPCQuestEvent::FuncCompleteQuest_Between(unsigned long, unsigned long);
	//private: bool CPCQuestEvent::FuncRecall_ComplereQuest(unsigned long);
	//private: bool CPCQuestEvent::SendAllQuest(void);
	//private: bool CPCQuestEvent::SetCompleteQuest(unsigned long);
	//private: bool CPCQuestEvent::FindCompleteQuest(unsigned long);
	//private: CMission_Hunt* CPCQuestEvent::GetMission(int);
	//private: bool CPCQuestEvent::IsQuest(unsigned long);
	//private: CQuestEventInfo* CPCQuestEvent::FindQuestInfo(unsigned long);

private:
	static hook_method<bool (CPCQuestEvent::*)(const unsigned char* in_pData_quest, const int in_Length_quest, const unsigned char* in_pData_hunt, const int in_Length_hunt, const unsigned char* in_pData_time, const int in_Length_time, const unsigned char* in_pData_complete, const int in_Length_complete)> CPCQuestEvent::_AsyncDBComplete_LoadQuestEvent;
	static hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_QuestInfo;
	static hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_CompleteQuest;
	static hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_Quest_Hunt;
	static hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_Quest_Time;
	static hook_method<int (CPCQuestEvent::*)(int msg, int par1, int par2)> CPCQuestEvent::_OnMessage;
};
