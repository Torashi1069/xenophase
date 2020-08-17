#include "QuestTFSector.h"


CQuestTFSector::CQuestTFSector(void) // line 11
{
	m_buff = NULL;
	m_size = 0;
	m_questMission.questID = 0;
	m_questMission.hunt_count = 0;
	m_questMission.time = 0;
	memset(m_questMission.questName, 0, sizeof(m_questMission.questName));
	for( int i = 0; i < countof(m_questMission.hunt); ++i )
	{
		m_questMission.hunt[i].mobIdent = 0;
		memset(m_questMission.hunt[i].mobName, 0, sizeof(m_questMission.hunt[i].mobName));
		m_questMission.hunt[i].max_huntCount = 0;
	}
}


CQuestTFSector::~CQuestTFSector(void) // line 31
{
	delete[] m_buff;
	m_buff = NULL;
	m_size = 0;
}
