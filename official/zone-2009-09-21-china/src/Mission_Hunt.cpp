#include "Mission_Hunt.h"


CMission_Hunt::CMission_Hunt()
{
	m_huntCount = 0;
	m_maxCount = 0;
	m_mobGID = 0;
}


CMission_Hunt::~CMission_Hunt()
{
	m_huntCount = 0;
	m_maxCount = 0;
	m_mobGID = 0;
}


bool CMission_Hunt::SetMission(unsigned long questID, int huntIdent, unsigned long mobGID, int maxCount, int count)
{
	if( mobGID <= 0 || questID <= 0 || huntIdent <= 0 )
		return false;

	m_huntIdent = huntIdent;
	m_questID = questID;
	m_mobGID = mobGID;
	m_huntCount = count;
	m_maxCount = maxCount;
	return true;
}


int CMission_Hunt::GetCount()
{
	return m_huntCount;
}


int CMission_Hunt::PlusOneCount()
{
	if( m_huntCount < m_maxCount )
		m_huntCount++;

	return m_huntCount;
}


unsigned long CMission_Hunt::GetMobGID()
{
	return m_mobGID;
}


unsigned long CMission_Hunt::GetQuestID()
{
	return m_questID;
}


bool CMission_Hunt::GetCompleteHunting()
{
	return ( m_huntCount >= m_maxCount );
}
