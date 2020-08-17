#include "SnapMgr.h"


SnapObject::SnapObject(void) // line 16
: m_careWindow(NULL), m_isProcessed(0)
{
}


SnapObject::~SnapObject(void) // line 20
{
}


CSnapMgr::CSnapMgr(void) // line 261
: m_masterObject(0)
{
}


CSnapMgr::~CSnapMgr(void) // line 265
{
	for( mystd::list<SnapObject*>::iterator i = m_snapObjectList.begin(); i != m_snapObjectList.end(); ++i )
		if( *i != NULL )
			delete *i;

	m_masterObject = 0;
}


hook_method<void (CSnapMgr::*)(void)> CSnapMgr::_RemoveAll(SAKEXE, "CSnapMgr::RemoveAll");
void CSnapMgr::RemoveAll(void)
{
	return (this->*_RemoveAll)();

	//TODO
}


hook_method<void (CSnapMgr::*)(void)> CSnapMgr::_ClearWayAll(SAKEXE, "CSnapMgr::ClearWayAll");
void CSnapMgr::ClearWayAll(void)
{
	return (this->*_ClearWayAll)();

	//TODO
}


hook_method<void (CSnapMgr::*)(UIWindow* masterWindow)> CSnapMgr::_AddSnapMasterObject(SAKEXE, "CSnapMgr::AddSnapMasterObject");
void CSnapMgr::AddSnapMasterObject(UIWindow* masterWindow) // line 320
{
	return (this->*_AddSnapMasterObject)(masterWindow);

	//TODO
}


hook_method<void (CSnapMgr::*)(UIWindow* window)> CSnapMgr::_AddSnapObject(SAKEXE, "CSnapMgr::AddSnapObject");
void CSnapMgr::AddSnapObject(UIWindow* window) // line 334
{
	return (this->*_AddSnapObject)(window);

	//TODO
}


hook_method<void (CSnapMgr::*)(UIWindow* window)> CSnapMgr::_RemoveSnapObject(SAKEXE, "CSnapMgr::RemoveSnapObject");
void CSnapMgr::RemoveSnapObject(UIWindow* window)
{
	return (this->*_RemoveSnapObject)(window);

	//TODO
}


hook_method<void (CSnapMgr::*)(UIWindow* masterWindow)> CSnapMgr::_BeginMove(SAKEXE, "CSnapMgr::BeginMove");
void CSnapMgr::BeginMove(UIWindow* masterWindow) // line 436
{
	return (this->*_BeginMove)(masterWindow);

	//TODO
}


hook_method<void (CSnapMgr::*)(UIWindow* moveWindow)> CSnapMgr::_EndMove(SAKEXE, "CSnapMgr::EndMove");
void CSnapMgr::EndMove(UIWindow* moveWindow) // line 425
{
	return (this->*_EndMove)(moveWindow);

	//TODO
}


hook_method<void (CSnapMgr::*)(UIWindow* window, int dx, int dy, int snapType)> CSnapMgr::_MoveConnectedObject(SAKEXE, "CSnapMgr::MoveConnectedObject");
void CSnapMgr::MoveConnectedObject(UIWindow* window, int dx, int dy, int snapType)
{
	return (this->*_MoveConnectedObject)(window, dx, dy, snapType);

	//TODO
}
