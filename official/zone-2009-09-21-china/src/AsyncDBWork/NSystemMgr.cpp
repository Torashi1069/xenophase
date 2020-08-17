#include "AsyncDBWork/NSystemMgr.h"


hook_ptr<NSystemMgr*> NSystemMgr::m_cpSelf(SERVER, "NSystemMgr::m_cpSelf");


NSystemMgr::NSystemMgr(void) // line 16
{
	m_bOK = false;

	if( this->NSystemMgr::Create() )
		m_bOK = true;
}


NSystemMgr::~NSystemMgr(void) // line 24
{
	this->NSystemMgr::Destroy();
}


hook_method<bool (NSystemMgr::*)(void)> NSystemMgr::_Create(SERVER, "NSystemMgr::Create");
bool NSystemMgr::Create(void) // line 43
{
	return (this->*_Create)();

	//TODO
}


hook_method<void (NSystemMgr::*)(void)> NSystemMgr::_Destroy(SERVER, "NSystemMgr::Destory");
void NSystemMgr::Destroy(void) // line 36
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<static bool (__cdecl *)(void)> NSystemMgr::_CreateInstance(SERVER, "NSystemMgr::CreateInstance");
bool __cdecl NSystemMgr::CreateInstance(void) // line 61
{
	return (NSystemMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> NSystemMgr::_DestroyInstance(SERVER, "NSystemMgr::DestoryInstance");
void __cdecl NSystemMgr::DestroyInstance(void) // line 73
{
	return (NSystemMgr::_DestroyInstance)();

	//TODO
}
