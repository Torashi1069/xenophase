#include "Memorial Dungeon/MemorialDungeonMgr.h"


hook_ptr<CMemorialDungeonMgr *> CMemorialDungeonMgr::m_cpSelf(SERVER, "CMemorialDungeonMgr::m_cpSelf"); // = ?


CMemorialDungeonMgr::CMemorialDungeonMgr(void) // line 16
{
	m_OpenState = OPENSTATE_UNKNOWN;
	m_bOK = false;
	if( this->CMemorialDungeonMgr::Create() )
		m_bOK = true;
}


CMemorialDungeonMgr::~CMemorialDungeonMgr(void) // line 24
{
}


hook_method<bool (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_Create(SERVER, "CMemorialDungeonMgr::Create");
bool CMemorialDungeonMgr::Create(void) // line ??
{
	return (this->*_Create)();

	return true;
}


//hook_method<void (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_Destroy(SERVER, "CMemorialDungeonMgr::Destroy");
void CMemorialDungeonMgr::Destroy(void) // line ??
{
//	return (this->*_Destroy)();

	;
}


hook_method<static bool (__cdecl *)(void)> CMemorialDungeonMgr::_CreateInstance(SERVER, "CMemorialDungeonMgr::CreateInstance");
bool __cdecl CMemorialDungeonMgr::CreateInstance(void) // line 100
{
	return (CMemorialDungeonMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CMemorialDungeonMgr::_DestroyInstance(SERVER, "CMemorialDungeonMgr::DestroyInstance");
void __cdecl CMemorialDungeonMgr::DestroyInstance(void) // line 112
{
	return (CMemorialDungeonMgr::_DestroyInstance)();

	//TODO
}
