#include "AsyncDBWork/NIDAllocator.h"


hook_ptr<NIDAllocator*> NIDAllocator::m_cpSelf(SERVER, "NIDAllocator::m_cpSelf"); // = ?


NIDAllocator::NIDAllocator(void) // line 13
{
	m_bOK = false;
	m_LastAlloGroupNum = 0;
	InitializeCriticalSection(&m_CS);

	if( this->NIDAllocator::Create() )
		m_bOK = true;

}


NIDAllocator::~NIDAllocator(void) // line 23
{
	this->NIDAllocator::Destroy();
	DeleteCriticalSection(&m_CS);
}


hook_method<bool (NIDAllocator::*)(void)> NIDAllocator::_Create(SERVER, "NIDAllocator::Create");
bool NIDAllocator::Create(void) // line ??
{
	return (this->*_Create)();

	//TODO
}


hook_method<void (NIDAllocator::*)(void)> NIDAllocator::_Destroy(SERVER, "NIDAllocator::Destory");
void NIDAllocator::Destroy(void) // line 35
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<bool (NIDAllocator::*)(void)> NIDAllocator::_isOK(SERVER, "NIDAllocator::isOK");
bool NIDAllocator::isOK(void) // line 31
{
	return (this->*_isOK)();

	//TODO
}


hook_method<bool (NIDAllocator::*)(const mystd::string in_strGroupName, const unsigned int in_MinID, const unsigned int in_MaxID)> NIDAllocator::_RegisterGroup(SERVER, "NIDAllocator::RegisterGroup");
bool NIDAllocator::RegisterGroup(const mystd::string in_strGroupName, const unsigned int in_MinID, const unsigned int in_MaxID) // line 71
{
	return (this->*_RegisterGroup)(in_strGroupName, in_MinID, in_MaxID);

	//TODO
}


hook_method<unsigned int (NIDAllocator::*)(const mystd::string in_strGroupName)> NIDAllocator::_Alloc(SERVER, "NIDAllocator::Alloc");
unsigned int NIDAllocator::Alloc(const mystd::string in_strGroupName) // line 55
{
	return (this->*_Alloc)(in_strGroupName);

	//TODO
}


hook_method<void (NIDAllocator::*)(const mystd::string in_strGroupName, const unsigned int in_ID)> NIDAllocator::_Free(SERVER, "NIDAllocator::Free");
void NIDAllocator::Free(const mystd::string in_strGroupName, const unsigned int in_ID) // line 45
{
	return (this->*_Free)(in_strGroupName, in_ID);

	//TODO
}


hook_method<const int (NIDAllocator::*)(const mystd::string in_strGroupName)> NIDAllocator::_GetGroupID(SERVER, "?GetGroupID@NIDAllocator@@QAE?BHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
const int NIDAllocator::GetGroupID(const mystd::string in_strGroupName) // line 128
{
	return (this->*_GetGroupID)(in_strGroupName);

	//TODO
}


hook_method<const int (NIDAllocator::*)(const unsigned int in_ID)> NIDAllocator::_GetGroupID2(SERVER, "?GetGroupID@NIDAllocator@@QAE?BHI@Z");
const int NIDAllocator::GetGroupID(const unsigned int in_ID) // line 124
{
	return (this->*_GetGroupID2)(in_ID);

	//TODO
}


hook_method<static NIDAllocator* (__cdecl *)(void)> NIDAllocator::_GetObj(SERVER, "NIDAllocator::GetObj");
NIDAllocator* __cdecl NIDAllocator::GetObj(void) // line 101
{
	return (NIDAllocator::_GetObj)();

	return m_cpSelf;
}


hook_method<bool (__cdecl *)(void)> NIDAllocator::_CreateInstance(SERVER, "NIDAllocator::CreateInstance");
bool __cdecl NIDAllocator::CreateInstance(void) // line 106
{
	return (NIDAllocator::_CreateInstance)();

	//TODO
}


hook_method<void (__cdecl *)(void)> NIDAllocator::_DestroyInstance(SERVER, "NIDAllocator::DestoryInstance");
void __cdecl NIDAllocator::DestroyInstance(void) // line 119
{
	return (NIDAllocator::_DestroyInstance)();

	//TODO
}


NIDAllocator::NIDGenerator::NIDGenerator(const unsigned int in_GroupID, const unsigned int in_MinID, const unsigned int in_MaxID) // line 142
: m_MinID(in_MinID), m_MaxID(in_MaxID), m_GroupID(in_GroupID)
{
	m_bOK = false;

	if( m_GroupID <= 0 || m_GroupID > 0xFF )
		return;

	if( m_MinID <= 0 || m_MaxID >= 0xFFFFFF )
		return;

	if( m_MinID >= m_MaxID )
		return;

	unsigned int i;
	for( i = m_MinID; i <= m_MaxID; ++i )
	{
		const unsigned int genID = (i & 0xFFFFFF ^ (m_GroupID << 24));

		mystd::pair<IDCONTAINERITOR,bool> ret = m_IDContainer.insert(mystd::pair<unsigned int,bool>(genID,0));
		if( !ret.second )
			break;

		m_StandbyIDqueue.push(genID);
	}

	if( i > m_MaxID )
		m_bOK = true;
}


NIDAllocator::NIDGenerator::~NIDGenerator(void) // line 169
{
}
