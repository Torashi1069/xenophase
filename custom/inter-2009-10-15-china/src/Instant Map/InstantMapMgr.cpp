#include "InstantMapMgr.h"


hook_ptr<CInstantMapMgr*> CInstantMapMgr::m_cpSelf(SERVER, "CInstantMapMgr::m_cpSelf"); // = NULL;


hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Process(SERVER, "CInstantMapMgr::Process");
void CInstantMapMgr::Process(void)
{
	return (this->*_Process)();

	//TODO
}


hook_method<const int (CInstantMapMgr::*)(void)> CInstantMapMgr::_GetNum(SERVER, "CInstantMapMgr::GetNum");
const int CInstantMapMgr::GetNum(void) // line 37 (Instant Map/InstantMapMgr.h)
{
	return (this->*_GetNum)();

	return m_Container.size();
}


hook_method<static bool (__cdecl *)(void)> CInstantMapMgr::_CreateInstance(SERVER, "CInstantMapMgr::CreateInstance");
bool CInstantMapMgr::CreateInstance(void) // line 184
{
	return (_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CInstantMapMgr::_DestroyInstance(SERVER, "CInstantMapMgr::DestroyInstance");
void CInstantMapMgr::DestroyInstance(void) // line 198
{
	return (_DestroyInstance)();

	//TODO
}


/// @custom
CInstantMapMgr* CInstantMapMgr::GetObj(void)
{
	return m_cpSelf;
}
