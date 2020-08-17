#include "ISDatabaseAccountMgr.h"


hook_ptr<ISDatabaseAccountMgr*> ISDatabaseAccountMgr::m_cpSelf(SERVER, "ISDatabaseAccountMgr::m_cpSelf");


hook_method<static bool (__cdecl *)(void)> ISDatabaseAccountMgr::_CreateInstance(SERVER, "ISDatabaseAccountMgr::CreateInstance");
bool __cdecl ISDatabaseAccountMgr::CreateInstance(void) // line 63
{
	return (ISDatabaseAccountMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> ISDatabaseAccountMgr::_DestroyInstance(SERVER, "ISDatabaseAccountMgr::DestroyInstance");
void __cdecl ISDatabaseAccountMgr::DestroyInstance(void) // line 76
{
	return (ISDatabaseAccountMgr::_DestroyInstance)();

	//TODO
}
