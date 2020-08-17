#include "shared/N3System/N3RecycleIDGenerator.h"


CN3RecycleIDGenerator::CN3RecycleIDGenerator(const unsigned int in_nFirstIDValue, const unsigned int in_nLastIDValue, const unsigned int in_nMinimumObjCnt)
: m_nFirstIDValue(in_nFirstIDValue), m_nLastIDValue(in_nLastIDValue), m_nMinimumObjCnt(in_nMinimumObjCnt), m_nNextID(in_nFirstIDValue)
{
	m_bOK = true;
}


CN3RecycleIDGenerator::~CN3RecycleIDGenerator()
{
}


bool CN3RecycleIDGenerator::isOK() const
{
	return m_bOK;
}


int CN3RecycleIDGenerator::Alloc()
{
	if( m_RecycleIDContainer.size() <= m_nMinimumObjCnt )
	{
		if( m_nNextID <= m_nLastIDValue )
		{
			int result = m_nNextID;
			m_nNextID = m_nNextID + 1;
			return result;
		}

		if( m_RecycleIDContainer.size() == 0 )
			return -1;
	}

	int result = m_RecycleIDContainer.front();
	m_RecycleIDContainer.pop_front();
	return result;
}


void CN3RecycleIDGenerator::Free(const unsigned int in_nID)
{
	if( in_nID >= m_nNextID || in_nID > m_nLastIDValue )
		return; // input value out of range

	RECYCLEIDCONTAINER::const_iterator iter = std::find(m_RecycleIDContainer.begin(), m_RecycleIDContainer.end(), in_nID);
	if( iter != m_RecycleIDContainer.end() )
		return; // already freed

	m_RecycleIDContainer.push_back(in_nID);
}
