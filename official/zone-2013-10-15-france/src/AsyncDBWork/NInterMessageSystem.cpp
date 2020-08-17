#include "AsyncDBWork/NInterMessageSystem.h"
#include "AsyncDBWork/NXSyncObject.h"


/// singleton instance
NInterMessageSystem*& NInterMessageSystem::m_cpSelf = VTOR<NInterMessageSystem*>(DetourFindFunction(EXEPATH(), "NInterMessageSystem::m_cpSelf"));


NInterMessageSystem::NInterMessageSystem()
: m_bOK(false)
{
	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


NInterMessageSystem::~NInterMessageSystem()
{
	DeleteCriticalSection(&m_CS);
}


bool NInterMessageSystem::isOK() const
{
	return m_bOK;
}


NInterMessageSystem* NInterMessageSystem::GetObj()
{
	return m_cpSelf;
}


bool NInterMessageSystem::CreateInstance()
{
	m_cpSelf = new NInterMessageSystem();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->NInterMessageSystem::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NInterMessageSystem::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


bool NInterMessageSystem::Insert(const unsigned int in_hID, NXInter* in_cpInter)
{
	NXSyncObject sync(m_CS);

	std::pair<IOBJCONTAINERITOR,bool> ret = m_InterObjContainer.insert(std::pair<unsigned int,NXInter*>(in_hID, in_cpInter));
	return ret.second;
}


void NInterMessageSystem::Remove(const unsigned int in_hID, NXInter* in_cpInter)
{
	NXSyncObject sync(m_CS);

	IOBJCONTAINERITOR itor = m_InterObjContainer.find(in_hID);
	if( itor == m_InterObjContainer.end() )
		return;

	if( itor->second != in_cpInter )
		return;

	m_InterObjContainer.erase(itor);
}


bool NInterMessageSystem::PostInterMessage(const unsigned int in_ToInter, const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam)
{
	NXSyncObject sync(m_CS);

	IOBJCONTAINERITOR itor = m_InterObjContainer.find(in_ToInter);
	if( itor == m_InterObjContainer.end() )
		return false;

	itor->second->PostInterMessage(in_FromInter, in_ExecTimeMS, in_Msg, in_wParam, in_lParam);
	return true;
}
