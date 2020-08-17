#include "shared/N2System/N2IDGenerator.h"


N2IDGenerator::N2IDGenerator(const unsigned short in_GroupID, const unsigned short in_MinID, const unsigned short in_MaxID)
: m_MinID(in_MinID), m_MaxID(in_MaxID), m_GroupID(in_GroupID)
{
	m_bOK = false;

	if( m_MinID == 0 || m_MinID > m_MaxID )
		return; // invalid input

	for( unsigned int i = m_MinID; i <= m_MaxID; ++i )
	{
		unsigned int id = i + (m_GroupID << 16);

		std::pair<IDCONTAINERITOR,bool> ret = m_IDContainer.insert(std::pair<unsigned int,bool>(id, false));
		if( !ret.second )
			return;

		m_StandbyIDqueue.push(id);
	}

	m_bOK = true;
}


N2IDGenerator::~N2IDGenerator()
{
	for( IDCONTAINERITOR itor = m_IDContainer.begin(); itor != m_IDContainer.end(); ++itor )
		itor->second = false;
}


const bool N2IDGenerator::isOK() const
{
	return m_bOK;
}


unsigned int N2IDGenerator::Alloc()
{
	if( m_StandbyIDqueue.size() == 0 )
		return 0;

	unsigned int allocID = m_StandbyIDqueue.front();

	IDCONTAINERITOR itor = m_IDContainer.find(allocID);
	if( itor == m_IDContainer.end() )
		return 0;
	
	if( itor->second == true )
		return 0;

	itor->second = true;
	m_StandbyIDqueue.pop();

	return allocID;
}


void N2IDGenerator::Free(const unsigned int in_ID)
{
	IDCONTAINERITOR itor = m_IDContainer.find(in_ID);
	if( itor == m_IDContainer.end() )
		return;

	if( itor->second == false )
		return;

	itor->second = false;
	m_StandbyIDqueue.push(in_ID);
}


const int N2IDGenerator::GetGroupID()
{
	return m_GroupID;
}
