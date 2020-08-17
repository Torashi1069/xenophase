#include "N2SystemMgr.h"


hook_ptr<N2SystemMgr*> N2SystemMgr::m_cpSelf(SERVER, "N2SystemMgr::m_cpSelf");


hook_method<static bool (__cdecl *)(void)> N2SystemMgr::_CreateInstance(SERVER, "N2SystemMgr::CreateInstance");
bool __cdecl N2SystemMgr::CreateInstance(void) // line 56
{
	return (N2SystemMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> N2SystemMgr::_DestroyInstance(SERVER, "N2SystemMgr::DestoryInstance");
void __cdecl N2SystemMgr::DestroyInstance(void) // line 69
{
	return (N2SystemMgr::_DestroyInstance)();

	//TODO
}
