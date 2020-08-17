#include "shared/N2System/N2SystemMgr.h"
#include "shared/N2System/N2IDAllocator.h"
#include "shared/N2System/N2InterMessageSystem.h"


/// singleton instance
N2SystemMgr*& N2SystemMgr::m_cpSelf = VTOR<N2SystemMgr*>(DetourFindFunction(EXEPATH(), "N2SystemMgr::m_cpSelf"));


N2SystemMgr::N2SystemMgr()
{
	m_bOK = false;

	if( this->N2SystemMgr::Create() )
		m_bOK = true;
}


N2SystemMgr::~N2SystemMgr()
{
	this->N2SystemMgr::Destory();
}


bool N2SystemMgr::Create()
{
	if( !N2IDAllocator::CreateInstance() )
		return false;

	if( !N2InterMessageSystem::CreateInstance() )
		return false;

	return true;
}


void N2SystemMgr::Destory()
{
	N2InterMessageSystem::DestoryInstance();
	N2IDAllocator::DestoryInstance();
}


bool N2SystemMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) N2SystemMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->N2SystemMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void N2SystemMgr::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


const bool N2SystemMgr::isOK() const
{
	return m_bOK;
}
