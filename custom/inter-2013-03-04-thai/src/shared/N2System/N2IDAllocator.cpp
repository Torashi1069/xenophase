#include "shared/N2System/N2IDAllocator.h"
#include "shared/N2System/N2IDGenerator.h"
#include "shared/N2System/N2SyncObject.h"


/// singleton instance
N2IDAllocator*& N2IDAllocator::m_cpSelf = VTOR<N2IDAllocator*>(DetourFindFunction(EXEPATH(), "N2IDAllocator::m_cpSelf"));


N2IDAllocator::N2IDAllocator()
{
	m_bOK = false;

	InitializeCriticalSection(&m_CS);

	if( this->N2IDAllocator::Create() )
		m_bOK = true;
}


N2IDAllocator::~N2IDAllocator()
{
	this->N2IDAllocator::Destroy();
	DeleteCriticalSection(&m_CS);
}


bool N2IDAllocator::Create()
{
	return true;
}


void N2IDAllocator::Destroy()
{
	for( GROUPCONTAINERITOR itor = m_GroupContainer.begin(); itor == m_GroupContainer.end(); ++itor )
	{
		delete itor->second;
		itor->second = NULL;
	}
}


bool N2IDAllocator::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) N2IDAllocator();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->N2IDAllocator::isOK() )
    {
		delete m_cpSelf;
		m_cpSelf = NULL;
        return false;
    }

    return true;
}


void N2IDAllocator::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


N2IDAllocator* N2IDAllocator::GetObj() ///@custom
{
	return m_cpSelf;
}


bool N2IDAllocator::isOK() const
{
	return m_bOK;
}


unsigned short N2IDAllocator::GetGroupID(const unsigned int in_ID)
{
	return HIWORD(in_ID);
}


bool N2IDAllocator::RegisterGroup(const unsigned short in_GroupID, const unsigned short in_MinID, const unsigned short in_MaxID)
{
	N2SyncObject sync(m_CS);

	GROUPCONTAINERITOR itor = m_GroupContainer.find(in_GroupID);
	if( itor != m_GroupContainer.end() )
		return false;

	N2IDGenerator* generator = new(std::nothrow) N2IDGenerator(in_GroupID, in_MinID, in_MaxID);
	if( generator == NULL )
		return false;

	if( !generator->N2IDGenerator::isOK() )
	{
		delete generator;
		return false;
	}

	std::pair<GROUPCONTAINERITOR,bool> ret = m_GroupContainer.insert(std::pair<unsigned short,N2IDGenerator*>(in_GroupID, generator));
	if( !ret.second )
		return false;

	return true;
};


unsigned int N2IDAllocator::Alloc(const unsigned short in_GroupID)
{
	N2SyncObject sync(m_CS);

	GROUPCONTAINERITOR itor = m_GroupContainer.find(in_GroupID);
	if( itor == m_GroupContainer.end() )
		return 0;

	return itor->second->N2IDGenerator::Alloc();
}


void N2IDAllocator::Free(const unsigned int in_ID)
{
	N2SyncObject sync(m_CS);

	GROUPCONTAINERITOR itor = m_GroupContainer.find(HIWORD(in_ID));
	if( itor == m_GroupContainer.end() )
		return;

	itor->second->N2IDGenerator::Free(in_ID);
}
