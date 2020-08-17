#include "Instant Map/InstantMapMgr.h"


hook_ptr<CInstantMapMgr*> CInstantMapMgr::m_cpSelf(SERVER, "CInstantMapMgr::m_cpSelf"); // = ?


CInstantMapMgr::CInstantMapMgr(void) // line 39
{
	m_bOK = false;
	if( this->CInstantMapMgr::Create() )
		m_bOK = true;
}


CInstantMapMgr::~CInstantMapMgr(void) // line 46
{
	this->CInstantMapMgr::Destroy();
}


hook_method<bool (CInstantMapMgr::*)(void)> CInstantMapMgr::_Create(SERVER, "CInstantMapMgr::Create");
bool CInstantMapMgr::Create(void) // line 51
{
	return (this->*_Create)();

	//TODO
}


hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Destroy(SERVER, "CInstantMapMgr::Destory");
void CInstantMapMgr::Destroy(void) // line 65
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Process(SERVER, "CInstantMapMgr::Process");
void CInstantMapMgr::Process(void) // line 120
{
	return (this->*_Process)();

	//TODO
}


hook_method<bool (CInstantMapMgr::*)(void)> CInstantMapMgr::_Start(SERVER, "CInstantMapMgr::Start");
bool CInstantMapMgr::Start(void) // line 80
{
	return (this->*_Start)();

	//TODO
}


hook_method<void (CInstantMapMgr::*)(void)> CInstantMapMgr::_Stop(SERVER, "CInstantMapMgr::Stop");
void CInstantMapMgr::Stop(void) // line 86
{
	return (this->*_Stop)();

	//TODO
}


//hook_method<int (CInstantMapMgr::*)(void)> CInstantMapMgr::_GetCtrlCount(SERVER, "CInstantMapMgr::GetCtrlCount");
int CInstantMapMgr::GetCtrlCount(void)
{
//	return (this->*_GetCtrlCount)();

	return m_InstantMapCtrlContainer.size();
}


hook_method<static bool (__cdecl *)(void)> CInstantMapMgr::_CreateInstance(SERVER, "CInstantMapMgr::CreateInstance");
bool __cdecl CInstantMapMgr::CreateInstance(void) // line 92
{
	return (CInstantMapMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CInstantMapMgr::_DestroyInstance(SERVER, "CInstantMapMgr::DestoryInstance");
void __cdecl CInstantMapMgr::DestroyInstance(void) // line 108
{
	return (CInstantMapMgr::_DestroyInstance)();

	//TODO
}


/// @custom
CInstantMapMgr* CInstantMapMgr::GetObj(void)
{
	return m_cpSelf;
}
