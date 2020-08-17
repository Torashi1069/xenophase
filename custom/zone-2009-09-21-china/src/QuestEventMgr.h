#pragma once
#include "QuestMission.h"
#include "std/map"


class CQuestEventMgr
{
public:
	/* this+0 */ public: //const CQuestEventMgr::`vftable';
	/* this+4 */ private: mystd::map<unsigned long,CQuestMission*> m_map;

	enum
	{
		CMD_SETQUEST = 0,
		CMD_SETMISSION = 1,
	};

	public: CQuestEventMgr::CQuestEventMgr(void);
	public: virtual CQuestEventMgr::~CQuestEventMgr(void);
	public: bool CQuestEventMgr::Initialize(void);
	public: void CQuestEventMgr::Finalize(void);
	public: bool CQuestEventMgr::AddQuest(unsigned long questID, TQUEST_MISSION* data);
	public: bool CQuestEventMgr::GetQuest(unsigned long questID, TQUEST_MISSION* ret);
	public: int CQuestEventMgr::GetMobMaxCount(unsigned long questID, unsigned long mobGID);
	public: int CQuestEventMgr::GetMissionIdent(unsigned long questID, unsigned long mobGID);
	public: unsigned long CQuestEventMgr::GetMissionPlayTime(unsigned long questID);
	public: mystd::string CQuestEventMgr::GetMobName(unsigned long questID, unsigned long mobGID);
	public: bool CQuestEventMgr::IsQuest(unsigned long questID);

private:
	static hook_method<bool (CQuestEventMgr::*)(void)> CQuestEventMgr::_Initialize;
	static hook_method<void (CQuestEventMgr::*)(void)> CQuestEventMgr::_Finalize;
	static hook_method<bool (CQuestEventMgr::*)(unsigned long questID, TQUEST_MISSION* data)> CQuestEventMgr::_AddQuest;
	static hook_method<bool (CQuestEventMgr::*)(unsigned long questID, TQUEST_MISSION* ret)> CQuestEventMgr::_GetQuest;
	static hook_method<int (CQuestEventMgr::*)(unsigned long questID, unsigned long mobGID)> CQuestEventMgr::_GetMobMaxCount;
	static hook_method<int (CQuestEventMgr::*)(unsigned long questID, unsigned long mobGID)> CQuestEventMgr::_GetMissionIdent;
	static hook_method<unsigned long (CQuestEventMgr::*)(unsigned long questID)> CQuestEventMgr::_GetMissionPlayTime;
	static hook_method<mystd::string (CQuestEventMgr::*)(unsigned long questID, unsigned long mobGID)> CQuestEventMgr::_GetMobName;
	static hook_method<bool (CQuestEventMgr::*)(unsigned long questID)> CQuestEventMgr::_IsQuest;
};
