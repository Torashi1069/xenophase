#include "QuestMission.h"


CQuestMission::CQuestMission()
{
	m_questID = 0;
	memset(m_questName, '\0', sizeof(m_questName));
	memset(m_hunt, 0, sizeof(m_hunt));
	m_playTime = 0;
	m_huntCount = 0;
}


CQuestMission::~CQuestMission()
{
	m_questID = 0;
	memset(m_questName, '\0', sizeof(m_questName));
	memset(m_hunt, 0, sizeof(m_hunt));
	m_playTime = 0;
	m_huntCount = 0;
}


int CQuestMission::SetQuest(unsigned long questID, TQUEST_MISSION* data)
{
	if( questID < 1 || data == NULL )
		return -1;

	m_questID = questID;
	strcpy(m_questName, data->questName);
	m_playTime = data->time;
	memcpy_s(m_hunt, sizeof(m_hunt), data->hunt, sizeof(data->hunt));
	m_huntCount = data->hunt_count;
	return 1;
}


bool CQuestMission::GetQuest(TQUEST_MISSION* quest)
{
	if( m_questID < 1 )
		return false;

	quest->questID = m_questID;
	strcpy(quest->questName, m_questName);
	quest->time = m_playTime;

	for( int i = 0; i < m_huntCount; ++i )
	{
		if( i > countof(m_hunt) )
			return false;

		quest->hunt[i].max_huntCount = m_hunt[i].max_huntCount;
		strcpy(quest->hunt[i].mobName, m_hunt[i].mobName);
		quest->hunt[i].mobIdent = m_hunt[i].mobIdent;
		quest->hunt[i].huntIdent = m_hunt[i].huntIdent;
	}

	quest->hunt_count = m_huntCount;
	return true;
}


int CQuestMission::GetMobMaxCount(unsigned long mobGID)
{
	for( int i = 0; i < m_huntCount; ++i )
		if( mobGID == m_hunt[i].mobIdent )
			return m_hunt[i].max_huntCount; // found.

	return 0; // not found.
}


int CQuestMission::GetMissionIdent(unsigned long mobGID)
{
	for( int i = 0; i < m_huntCount; ++i )
		if( mobGID == m_hunt[i].mobIdent )
			return m_hunt[i].huntIdent; // found.

	return 0; // not found.
}


std::string CQuestMission::GetMobName(unsigned long mobGID)
{
	for( int i = 0; i < m_huntCount; ++i )
		if( mobGID == m_hunt[i].mobIdent )
			return m_hunt[i].mobName; // found.

	return ""; // not found.
}


unsigned long CQuestMission::GetMissionPlayTime()
{
	return m_playTime;
}
