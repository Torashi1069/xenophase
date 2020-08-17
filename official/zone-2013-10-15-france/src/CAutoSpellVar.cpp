#include "CAutoSpellVar.h"


CAutoSpellVar::CAutoSpellVar()
{
	m_PlayRefCnt = 1;
}


CAutoSpellVar::~CAutoSpellVar()
{
}


void CAutoSpellVar::Set(const unsigned int in_Identity, const unsigned int in_Level, const unsigned int in_Permill)
{
	m_History.push_back(lcData(in_Identity, in_Level, in_Permill));

	m_Data = *std::max_element(m_History.begin(), m_History.end());
}


void CAutoSpellVar::Reset(const unsigned int in_Identity)
{
	std::vector<lcData>::iterator iter;
	for( iter = m_History.begin(); iter != m_History.end(); ++iter )
		if( iter->m_Identity == in_Identity )
			break;
	if( iter == m_History.end() )
		return;

	m_History.erase(iter);

	if( m_History.begin() != m_History.end() )
		m_Data = *std::max_element(m_History.begin(), m_History.end());
	else
		m_Data = lcData();
}


void CAutoSpellVar::Pause(const unsigned int in_Identity)
{
	--m_PlayRefCnt;
}


void CAutoSpellVar::Resume(const unsigned int in_Identity)
{
	++m_PlayRefCnt;
}


unsigned int CAutoSpellVar::GetPermill()
{
	return m_Data.m_Permill;
}


unsigned int CAutoSpellVar::GetLevel()
{
	return m_Data.m_Level;
}
