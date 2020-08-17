#include "AsyncDBWork/NIDAllocator.h"
#include "AsyncDBWork/NXSyncObject.h"


/// singleton instance
NIDAllocator*& NIDAllocator::m_cpSelf = VTOR<NIDAllocator*>(DetourFindFunction(EXEPATH(), "NIDAllocator::m_cpSelf"));


NIDAllocator::NIDAllocator()
{
	m_LastAlloGroupNum = 0;
	m_bOK = false;
	InitializeCriticalSection(&m_CS);

	if( this->NIDAllocator::Create() )
		m_bOK = true;
}


NIDAllocator::~NIDAllocator()
{
	this->NIDAllocator::Destory();

	DeleteCriticalSection(&m_CS);
}


bool NIDAllocator::isOK() const
{
	return m_bOK;
}


bool NIDAllocator::Create()
{
	return true;
}


void NIDAllocator::Destory()
{
	for( GROUPCONTAINERITOR itor = m_GroupContainer.begin(); itor != m_GroupContainer.end(); ++itor )
	{
		delete itor->second;
		itor->second = NULL;
	}
}


void NIDAllocator::Free(const std::string in_strGroupName, const unsigned int in_ID)
{
	NXSyncObject sync(m_CS);

	GROUPCONTAINERITOR itor = m_GroupContainer.find(in_strGroupName);
	if( itor == m_GroupContainer.end() )
		return;

	itor->second->NIDAllocator::NIDGenerator::Free(in_ID);
}


unsigned int NIDAllocator::Alloc(const std::string in_strGroupName)
{
	NXSyncObject sync(m_CS);

	GROUPCONTAINERITOR itor = m_GroupContainer.find(in_strGroupName);
	if( itor == m_GroupContainer.end() )
		return 0;

	return itor->second->NIDAllocator::NIDGenerator::Alloc();
}


bool NIDAllocator::RegisterGroup(const std::string in_strGroupName, const unsigned int in_MinID, const unsigned int in_MaxID)
{
	NXSyncObject sync(m_CS);

	if( m_LastAlloGroupNum >= 0xFF )
		return false;

	GROUPCONTAINERITOR itor = m_GroupContainer.find(in_strGroupName);
	if( itor != m_GroupContainer.end() )
		return false;

	NIDGenerator* cpIDGenerator = new NIDGenerator(m_LastAlloGroupNum + 1, in_MinID, in_MaxID);
	if( cpIDGenerator == NULL )
		return false;

	if( !cpIDGenerator->NIDAllocator::NIDGenerator::isOK() )
	{
		delete cpIDGenerator;
		return false;
	}

	std::pair<GROUPCONTAINERITOR,bool> ret = m_GroupContainer.insert(std::pair<std::string,NIDGenerator*>(in_strGroupName, cpIDGenerator));
	if( !ret.second )
		return false;

	++m_LastAlloGroupNum;
	return true;
}


NIDAllocator* NIDAllocator::GetObj()
{
	return m_cpSelf;
}


bool NIDAllocator::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new NIDAllocator();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->NIDAllocator::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NIDAllocator::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


const int NIDAllocator::GetGroupID(const unsigned int in_ID)
{
	return in_ID >> 24;
}


const int NIDAllocator::GetGroupID(const std::string in_strGroupName)
{
	NXSyncObject sync(m_CS);

	GROUPCONTAINERITOR itor = m_GroupContainer.find(in_strGroupName);
	if( itor == m_GroupContainer.end() )
		return 0;

	return itor->second->NIDAllocator::NIDGenerator::GetGroupID();
}


NIDAllocator::NIDGenerator::NIDGenerator(const unsigned int in_GroupID, const unsigned int in_MinID, const unsigned int in_MaxID)
: m_MinID(in_MinID), m_MaxID(in_MaxID), m_GroupID(in_GroupID), m_StandbyIDqueue(), m_IDContainer(), m_bOK(false)
{
	if( m_GroupID <= 0 || m_GroupID > 0xFF )
		return;

	if( m_MinID <= 0 || m_MaxID > 0xFFFFFF )
		return;

	if( m_MinID >= m_MaxID )
		return;

	for( unsigned int num = m_MinID; num <= m_MaxID; ++num )
	{
		unsigned int genID = ((num & 0xFFFFFF) << 0) ^ ((m_GroupID & 0xFF) << 24);

		std::pair<IDCONTAINERITOR,bool> ret = m_IDContainer.insert(std::pair<unsigned int,bool>(genID, false));
		if( !ret.second )
			return;

		m_StandbyIDqueue.push(genID);
	}

	m_bOK = true;
}


NIDAllocator::NIDGenerator::~NIDGenerator()
{
	for( IDCONTAINERITOR itor = m_IDContainer.begin(); itor != m_IDContainer.end(); ++itor )
		itor->second = false;
}


bool NIDAllocator::NIDGenerator::isOK() const
{
	return m_bOK;
}


unsigned int NIDAllocator::NIDGenerator::Alloc()
{
	if( m_StandbyIDqueue.size() == 0 )
		return 0;

	unsigned int allocID = m_StandbyIDqueue.front();
	IDCONTAINERITOR itor = m_IDContainer.find(allocID);
	if( itor == m_IDContainer.end() || itor->second == true )
		return 0;

	itor->second = true;
	m_StandbyIDqueue.pop();

	return allocID;
}


void NIDAllocator::NIDGenerator::Free(const unsigned int in_ID)
{
	IDCONTAINERITOR itor = m_IDContainer.find(in_ID);
	if( itor == m_IDContainer.end() )
		return;

	if( !itor->second )
		return;

	itor->second = false;
	m_StandbyIDqueue.push(in_ID);
}


const int NIDAllocator::NIDGenerator::GetGroupID()
{
	return m_GroupID;
}
