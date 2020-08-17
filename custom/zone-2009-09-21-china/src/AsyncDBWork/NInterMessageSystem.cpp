#include "AsyncDBWork/NInterMessageSystem.h"
#include "AsyncDBWork/NSyncObject.h"


hook_ptr<NInterMessageSystem*> NInterMessageSystem::m_cpSelf(SERVER, "NInterMessageSystem::m_cpSelf");


NInterMessageSystem::NInterMessageSystem(void) // line 15
{
	m_bOK = false;
	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


NInterMessageSystem::~NInterMessageSystem(void) // line 23
{
	DeleteCriticalSection(&m_CS);
}


hook_method<static NInterMessageSystem* (__cdecl *)(void)> NInterMessageSystem::_GetObj(SERVER, "NInterMessageSystem::GetObj");
NInterMessageSystem* __cdecl NInterMessageSystem::GetObj(void) // line 39
{
	return (NInterMessageSystem::_GetObj)();

	return m_cpSelf;
}


hook_method<bool (NInterMessageSystem::*)(const unsigned int in_hID, NInter* in_cpInter)> NInterMessageSystem::_Insert(SERVER, "NInterMessageSystem::Insert");
bool NInterMessageSystem::Insert(const unsigned int in_hID, NInter* in_cpInter) // line 62
{
	return (this->*_Insert)(in_hID, in_cpInter);

	NSyncObject sync(m_CS);
	mystd::pair<mystd::map<unsigned int,NInter*>::iterator,bool> ret = m_InterObjContainer.insert(mystd::pair<const unsigned int,NInter*>(in_hID, in_cpInter));
	return ret.second;
}


hook_method<void (NInterMessageSystem::*)(const unsigned int in_hID, NInter* in_cpInter)> NInterMessageSystem::_Remove(SERVER, "NInterMessageSystem::Remove");
void NInterMessageSystem::Remove(const unsigned int in_hID, NInter* in_cpInter) // line 71-79
{
	return (this->*_Remove)(in_hID, in_cpInter);

	NSyncObject sync(m_CS);
	mystd::map<unsigned int,NInter*>::iterator iter = m_InterObjContainer.find(in_hID);
	if( iter != m_InterObjContainer.end() )
		m_InterObjContainer.erase(iter);
}
