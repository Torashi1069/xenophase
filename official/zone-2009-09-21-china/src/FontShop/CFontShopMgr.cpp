#include "FontShop/CFontShopMgr.h"


hook_ptr<CFontShopMgr*> CFontShopMgr::m_cpSelf(SERVER, "CFontShopMgr::m_cpSelf"); // = ?


CFontShopMgr::CFontShopMgr(void) // line 46
{
	m_bOK = false;
	if( this->CFontShopMgr::Create() )
		m_bOK = true;
}


CFontShopMgr::~CFontShopMgr(void) // line 53
{
}


hook_method<static bool (__cdecl *)(void)> CFontShopMgr::_CreateInstance(SERVER, "CFontShopMgr::CreateInstance");
bool __cdecl CFontShopMgr::CreateInstance(void) // line 65
{
	return (CFontShopMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CFontShopMgr::_DestroyInstance(SERVER, "CFontShopMgr::DestroyInstance");
void __cdecl CFontShopMgr::DestroyInstance(void) // line 77
{
	return (CFontShopMgr::_DestroyInstance)();

	//TODO
}


hook_method<bool (CFontShopMgr::*)(void)> CFontShopMgr::_Create(SERVER, "CFontShopMgr::Create");
bool CFontShopMgr::Create(void) // line 68
{
	return (this->*_Create)();

	//TODO
}
