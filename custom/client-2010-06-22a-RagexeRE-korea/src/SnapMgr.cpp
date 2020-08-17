#include "SnapMgr.h"


CSnapMgr& g_snapMgr = VTOR<CSnapMgr>(SymDB::Find("g_snapMgr"));


hook_func<void (CSnapMgr::*)(UIWindow* masterWindow)> CSnapMgr::_BeginMove("CSnapMgr::BeginMove");
void CSnapMgr::BeginMove(UIWindow* masterWindow)
{
	return (this->*_BeginMove)(masterWindow);

	//TODO
}


hook_func<bool (CSnapMgr::*)(UIWindow* window)> CSnapMgr::_IsRegisteredToSnap("CSnapMgr::IsRegisteredToSnap");
bool CSnapMgr::IsRegisteredToSnap(UIWindow* window)
{
	return (this->*_IsRegisteredToSnap)(window);

	//TODO
}


hook_func<void (CSnapMgr::*)(UIWindow* masterWindow, int& deltaDragX, int& deltaDragY)> CSnapMgr::_GetDeltaDrag("CSnapMgr::GetDeltaDrag");
void CSnapMgr::GetDeltaDrag(UIWindow* masterWindow, int& deltaDragX, int& deltaDragY)
{
	return (this->*_GetDeltaDrag)(masterWindow, deltaDragX, deltaDragY);

	//TODO
}


hook_func<void (CSnapMgr::*)(UIWindow* masterWindow, int deltaDragX, int deltaDragY)> CSnapMgr::_MoveDelta("CSnapMgr::MoveDelta");
void CSnapMgr::MoveDelta(UIWindow* masterWindow, int deltaDragX, int deltaDragY)
{
	return (this->*_MoveDelta)(masterWindow, deltaDragX, deltaDragY);

	//TODO
}


hook_func<void (CSnapMgr::*)(UIWindow* moveWindow)> CSnapMgr::_EndMove("CSnapMgr::EndMove");
void CSnapMgr::EndMove(UIWindow* moveWindow)
{
	return (this->*_EndMove)(moveWindow);

	//TODO
}
