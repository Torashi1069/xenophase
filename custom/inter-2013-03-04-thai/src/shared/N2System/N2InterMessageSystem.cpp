#include "shared/N2System/N2Inter.h"
#include "shared/N2System/N2InterMessageSystem.h"
#include "shared/N2System/N2SyncObject.h"


/// singleton instance
N2InterMessageSystem*& N2InterMessageSystem::m_cpSelf = VTOR<N2InterMessageSystem*>(DetourFindFunction(EXEPATH(), "N2InterMessageSystem::m_cpSelf"));


N2InterMessageSystem::N2InterMessageSystem()
{
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


N2InterMessageSystem::~N2InterMessageSystem()
{
	DeleteCriticalSection(&m_CS);
}


bool N2InterMessageSystem::CreateInstance()
{
	m_cpSelf = new N2InterMessageSystem();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->N2InterMessageSystem::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void N2InterMessageSystem::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


bool N2InterMessageSystem::isOK() const
{
	return m_bOK;
}


bool N2InterMessageSystem::Insert(const unsigned int in_hID, N2Inter* in_cpInter)
{
	N2SyncObject sync(m_CS);

	std::pair<IOBJCONTAINERITOR,bool> ret = m_InterObjContainer.insert(std::pair<unsigned int const,N2Inter*>(in_hID, in_cpInter));
	return ret.second;
}


void N2InterMessageSystem::Remove(const unsigned int in_hID, N2Inter* in_cpInter)
{
	N2SyncObject sync(m_CS);

	IOBJCONTAINERITOR itor = m_InterObjContainer.find(in_hID);
	if( itor == m_InterObjContainer.end() )
		return;
	
	if( itor->second != in_cpInter )
		return;

	m_InterObjContainer.erase(itor);
}


bool N2InterMessageSystem::PostInterMessage(const unsigned int in_ToInter, const unsigned int in_FromInter, const int in_Msg, const int in_wParam, const int in_lParam)
{
	N2SyncObject sync(m_CS);

	IOBJCONTAINERITOR itor = m_InterObjContainer.find(in_ToInter);
	if( itor == m_InterObjContainer.end() )
		return false;

	itor->second->PostInterMessage(in_FromInter, in_Msg, in_wParam, in_lParam);
	return true;
}
