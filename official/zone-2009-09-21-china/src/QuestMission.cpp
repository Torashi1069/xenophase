#include "QuestMission.h"


CQuestMission::CQuestMission(void) // line 7
{
	m_questID = 0;
	memset(m_questName, 0, sizeof(m_questName));
	memset(m_hunt, 0, sizeof(m_hunt));
	m_playTime = 0;
	m_huntCount = 0;
}


CQuestMission::~CQuestMission(void) // line 17
{
	m_questID = 0;
	memset(m_questName, 0, sizeof(m_questName));
	memset(m_hunt, 0, sizeof(m_hunt));
	m_playTime = 0;
	m_huntCount = 0;
}


hook_method<int (CQuestMission::*)(unsigned long questID, TQUEST_MISSION* data)> CQuestMission::_SetQuest(SERVER, "CQuestMission::SetQuest");
int CQuestMission::SetQuest(unsigned long questID, TQUEST_MISSION* data) // line 28
{
	return (this->*_SetQuest)(questID, data);

	if( questID < 1 || data == NULL )
		return -1;

	m_questID = questID;
	strcpy(m_questName, data->questName);
	memcpy(m_hunt, data->hunt, sizeof(m_hunt));
	m_playTime = data->time;
	m_huntCount = data->hunt_count;
	return 1;
}


hook_method<bool (CQuestMission::*)(TQUEST_MISSION* quest)> CQuestMission::_GetQuest(SERVER, "CQuestMission::GetQuest");
bool CQuestMission::GetQuest(TQUEST_MISSION* quest) // line 42
{
	return (this->*_GetQuest)(quest);

	if( m_questID < 1 )
		return false;

	quest->questID = m_questID;
	strcpy(quest->questName, m_questName);
	quest->time = m_playTime;

	for( int v7 = 0; v7 < m_huntCount; ++v7 )
	{
		if( v7 >= countof(m_hunt) )
			return false;

		quest->hunt[0].mobIdent = m_hunt[0].mobIdent;
		quest->hunt[0].max_huntCount = m_hunt[0].max_huntCount;
		strcpy(quest->hunt[0].mobName, m_hunt[0].mobName);
		quest->hunt[0].huntIdent = m_hunt[0].huntIdent;
	}

	quest->hunt_count = m_huntCount;
	return true;
}


hook_method<int (CQuestMission::*)(unsigned long mobGID)> CQuestMission::_GetMobMaxCount(SERVER, "CQuestMission::GetMobMaxCount");
int CQuestMission::GetMobMaxCount(unsigned long mobGID) // line 60
{
	return (this->*_GetMobMaxCount)(mobGID);

	for( int i = 0; i < m_huntCount; ++i )
		if( m_hunt[i].mobIdent == mobGID )
			return m_hunt[i].max_huntCount;

	return 0;
}


hook_method<int (CQuestMission::*)(unsigned long mobGID)> CQuestMission::_GetMissionIdent(SERVER, "CQuestMission::GetMissionIdent");
int CQuestMission::GetMissionIdent(unsigned long mobGID) // line 68
{
	return (this->*_GetMissionIdent)(mobGID);

	for( int i = 0; i < m_huntCount; ++i )
		if( m_hunt[i].mobIdent == mobGID )
			return m_hunt[i].huntIdent;

	return 0;
}


hook_method<mystd::string (CQuestMission::*)(unsigned long mobGID)> CQuestMission::_GetMobName(SERVER, "CQuestMission::GetMobName");
mystd::string CQuestMission::GetMobName(unsigned long mobGID) // line 76
{
	return (this->*_GetMobName)(mobGID);

	for( int i = 0; i < m_huntCount; ++i )
		if( m_hunt[i].mobIdent == mobGID )
			return m_hunt[i].mobName;

	return "";
}


//hook_method<unsigned long (CQuestMission::*)(void)> CQuestMission::_GetMissionPlayTime(SERVER, "CQuestMission::GetMissionPlayTime");
unsigned long CQuestMission::GetMissionPlayTime(void) // line ??
{
//	return (this->*_GetMissionPlayTime)();

	return m_playTime;
}
