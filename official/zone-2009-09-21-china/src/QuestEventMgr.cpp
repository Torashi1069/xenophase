#include "globals.hpp"
#include "Path.h"
#include "QuestEventMgr.h"
#include "QuestMission.h"
#include "QuestTFile.h"


CQuestEventMgr::CQuestEventMgr(void) // line 11
{
}


CQuestEventMgr::~CQuestEventMgr(void) // line 15
{
	this->CQuestEventMgr::Finalize();
}


hook_method<bool (CQuestEventMgr::*)(void)> CQuestEventMgr::_Initialize(SERVER, "CQuestEventMgr::Initialize");
bool CQuestEventMgr::Initialize(void) // line 37
{
	return (this->*_Initialize)();

	CQuestTFile qFile;
	std::string fileName = g_pathData->CPathData::SetFileName("QuestMission.txt");

	if( !qFile.CQuestTFile::Load(fileName.c_str())
	||  !qFile.CQuestTFile::BlockCutting()
	||  !qFile.CQuestTFile::GeneratorSector() )
	{
		qFile.CQuestTFile::Clear();
		return false;
	}

	return true;
}


hook_method<void (CQuestEventMgr::*)(void)> CQuestEventMgr::_Finalize(SERVER, "CQuestEventMgr::Filnalize");
void CQuestEventMgr::Finalize(void) // line 69
{
	return (this->*_Finalize)();

	for( mystd::map<unsigned long,CQuestMission*>::iterator it = m_map.begin(); it != m_map.end(); ++it )
		if( it->second != NULL )
			delete it->second;
}


hook_method<bool (CQuestEventMgr::*)(unsigned long questID, TQUEST_MISSION* data)> CQuestEventMgr::_AddQuest(SERVER, "CQuestEventMgr::AddQuest");
bool CQuestEventMgr::AddQuest(unsigned long questID, TQUEST_MISSION* data) // line 56
{
	return (this->*_AddQuest)(questID, data);

	if( questID == 0 )
		return false;

	if( data == NULL )
		return false;

	if( m_map.find(questID) != m_map.end() )
		return false;

	CQuestMission* qm = new CQuestMission();
	if( qm == NULL || qm->CQuestMission::SetQuest(questID, data) != 1 )
	{
		MessageBoxA(NULL, "Memory Alloc Fail!!(q_5)", "ERROR", MB_OK);
		return false;
	}

	m_map[data->questID] = qm;
	return true;
}


hook_method<bool (CQuestEventMgr::*)(unsigned long questID, TQUEST_MISSION* ret)> CQuestEventMgr::_GetQuest(SERVER, "CQuestEventMgr::GetQuest");
bool CQuestEventMgr::GetQuest(unsigned long questID, TQUEST_MISSION* ret) // line 78
{
	return (this->*_GetQuest)(questID, ret);

	if( questID == 0 )
		return false;

	mystd::map<unsigned long,CQuestMission*>::iterator it = m_map.find(questID);
	if( it == m_map.end() )
		return false;

	CQuestMission* qm = it->second;
	if( qm == NULL )
		return false;

	qm->CQuestMission::GetQuest(ret);
	return true;
}


hook_method<int (CQuestEventMgr::*)(unsigned long questID, unsigned long mobGID)> CQuestEventMgr::_GetMobMaxCount(SERVER, "CQuestEventMgr::GetMobMaxCount");
int CQuestEventMgr::GetMobMaxCount(unsigned long questID, unsigned long mobGID) // line 97
{
	return (this->*_GetMobMaxCount)(questID, mobGID);

	if( questID == 0 )
		return 0;

	mystd::map<unsigned long,CQuestMission*>::iterator it = m_map.find(questID);
	if( it == m_map.end() )
		return 0;

	CQuestMission* qm = it->second;
	if( qm == NULL )
		return 0;

	return qm->CQuestMission::GetMobMaxCount(mobGID);
}


hook_method<int (CQuestEventMgr::*)(unsigned long questID, unsigned long mobGID)> CQuestEventMgr::_GetMissionIdent(SERVER, "CQuestEventMgr::GetMissionIdent");
int CQuestEventMgr::GetMissionIdent(unsigned long questID, unsigned long mobGID) // line 114
{
	return (this->*_GetMissionIdent)(questID, mobGID);

	if( questID == 0 )
		return 0;

	mystd::map<unsigned long,CQuestMission*>::iterator it = m_map.find(questID);
	if( it == m_map.end() )
		return 0;

	CQuestMission* qm = it->second;
	if( qm == NULL )
		return 0;

	return qm->CQuestMission::GetMissionIdent(mobGID);
}


hook_method<unsigned long (CQuestEventMgr::*)(unsigned long questID)> CQuestEventMgr::_GetMissionPlayTime(SERVER, "CQuestEventMgr::GetMissionPlayTime");
unsigned long CQuestEventMgr::GetMissionPlayTime(unsigned long questID) // line 149
{
	return (this->*_GetMissionPlayTime)(questID);

	mystd::map<unsigned long,CQuestMission*>::iterator it = m_map.find(questID);
	if( it == m_map.end() )
		return 0;
	
	CQuestMission* qm = it->second;
	if( qm == NULL )
		return 0;

	return qm->CQuestMission::GetMissionPlayTime();
}	


hook_method<mystd::string (CQuestEventMgr::*)(unsigned long questID, unsigned long mobGID)> CQuestEventMgr::_GetMobName(SERVER, "CQuestEventMgr::GetMobName");
mystd::string CQuestEventMgr::GetMobName(unsigned long questID, unsigned long mobGID) // line 131
{
	return (this->*_GetMobName)(questID, mobGID);

	if( questID == 0 )
		return NULL; //FIXME: strlen nullpo crash

	mystd::map<unsigned long,CQuestMission*>::iterator it = m_map.find(questID);
	if( it == m_map.end() )
		return "";

	CQuestMission* qm = it->second;
	if( qm == NULL )
		return "";

	return qm->CQuestMission::GetMobName(mobGID);
}


hook_method<bool (CQuestEventMgr::*)(unsigned long questID)> CQuestEventMgr::_IsQuest(SERVER, "CQuestEventMgr::IsQuest");
bool CQuestEventMgr::IsQuest(unsigned long questID) // line 163
{
	return (this->*_IsQuest)(questID);

	return ( m_map.find(questID) != m_map.end() );
}
