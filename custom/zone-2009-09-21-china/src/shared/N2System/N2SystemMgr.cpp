#include "N2System/N2SystemMgr.h"


hook_ptr<N2SystemMgr *> N2SystemMgr::m_cpSelf(SERVER, "N2SystemMgr::m_cpSelf"); // = ?


N2SystemMgr::N2SystemMgr(void)
{
	m_bOK = false;

	if( this->N2SystemMgr::Create() )
		m_bOK = true;
}


N2SystemMgr::~N2SystemMgr(void)
{
	this->N2SystemMgr::Destroy();
}


hook_method<bool (N2SystemMgr::*)(void)> N2SystemMgr::_Create(SERVER, "N2SystemMgr::Create");
bool N2SystemMgr::Create(void)
{
	return (this->*_Create)();

	//TODO
}


hook_method<void (N2SystemMgr::*)(void)> N2SystemMgr::_Destroy(SERVER, "N2SystemMgr::Destory");
void N2SystemMgr::Destroy(void)
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<const bool (N2SystemMgr::*)(void)> N2SystemMgr::_isOK(SERVER, "N2SystemMgr::isOK");
const bool N2SystemMgr::isOK(void)
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<static bool (__cdecl *)(void)> N2SystemMgr::_CreateInstance(SERVER, "N2SystemMgr::CreateInstance");
bool N2SystemMgr::CreateInstance(void)
{
	return (N2SystemMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> N2SystemMgr::_DestroyInstance(SERVER, "N2SystemMgr::DestoryInstance");
void N2SystemMgr::DestroyInstance(void)
{
	return (N2SystemMgr::_DestroyInstance)();

	//TODO
}
