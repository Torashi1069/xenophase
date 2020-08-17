#include "CDGNpcMgr.hpp"


hook_ptr<CDGNpcMgr*> CDGNpcMgr::m_cpSelf(SERVER, "CDGNpcMgr::m_cpSelf"); // = ?


CDGNpcMgr::CDGNpcMgr(void) // line 9
{
	this->CDGNpcMgr::Clear();
}


CDGNpcMgr::~CDGNpcMgr(void) // line 14
{
	this->CDGNpcMgr::Clear();
}


hook_method<void (CDGNpcMgr::*)(void)> CDGNpcMgr::_Clear(SERVER, "CDGNpcMgr::Clear");
void CDGNpcMgr::Clear(void) // line 19
{
	return (this->*_Clear)();

	m_map.clear();
}


hook_method<static CDGNpcMgr* (__cdecl *)(void)> CDGNpcMgr::_GetObj(SERVER, "CDGNpcMgr::GetObj");
CDGNpcMgr* __cdecl CDGNpcMgr::GetObj(void) // line 74
{
	return (CDGNpcMgr::_GetObj)();

	//TODO
}


hook_method<bool (CDGNpcMgr::*)(const char* mapName)> CDGNpcMgr::_AddInstantMap(SERVER, "CDGNpcMgr::AddInstantMap");
bool CDGNpcMgr::AddInstantMap(const char* mapName) // line 34
{
	return (this->*_AddInstantMap)(mapName);

	//TODO
}


/* hook_method<void (CDGNpcMgr::*)(const char* mapName)> CDGNpcMgr::_DeleteDunGeon(SERVER, "CDGNpcMgr::DeleteDunGeon");
void CDGNpcMgr::DeleteDunGeon(const char* mapName)
{
	return (this->*_DeleteDunGeon)(mapName);

	//TODO
} */


hook_method<CDGNpcBin* (CDGNpcMgr::*)(const char* mapName)> CDGNpcMgr::_FindDunGeonBin(SERVER, "CDGNpcMgr::FindDunGeonBin");
CDGNpcBin* CDGNpcMgr::FindDunGeonBin(const char* mapName)
{
	return (this->*_FindDunGeonBin)(mapName);

	//TODO
}
