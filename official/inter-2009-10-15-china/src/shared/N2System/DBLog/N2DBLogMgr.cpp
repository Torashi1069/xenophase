#include "N2System/DBLog/N2DBLogMgr.h"


hook_ptr<N2DBLogMgr*> N2DBLogMgr::m_cpSelf(SERVER, "N2DBLogMgr::m_cpSelf"); // = ?


hook_func<N2DBLogMgr* (__cdecl *)(void)> _InstanceN2DBLogMgr(SERVER, "InstanceN2DBLogMgr");
N2DBLogMgr* __cdecl InstanceN2DBLogMgr(void) // line 39 (N2System/DBLog/N2DBLogMgr.h)
{
	return (_InstanceN2DBLogMgr)();

	return N2DBLogMgr::m_cpSelf;
}


N2DBLogMgr::N2DBLogMgr(const int in_WorkThreadNum, const mystd::string in_ConnectStr) // line 13
{
	m_bOK = false;

	if( this->N2DBLogMgr::Create(in_WorkThreadNum, in_ConnectStr) )
		m_bOK = true;
}


N2DBLogMgr::~N2DBLogMgr(void) // line 21
{
	this->N2DBLogMgr::Destroy();
}


hook_method<bool (N2DBLogMgr::*)(const int in_WorkThreadNum, const mystd::string in_ConnectStr)> N2DBLogMgr::_Create(SERVER, "N2DBLogMgr::Create");
bool N2DBLogMgr::Create(const int in_WorkThreadNum, const mystd::string in_ConnectStr) // line 26
{
	return (this->*_Create)(in_WorkThreadNum, in_ConnectStr);

	//TODO
}


hook_method<void (N2DBLogMgr::*)(void)> N2DBLogMgr::_Destroy(SERVER, "N2DBLogMgr::Destroy");
void N2DBLogMgr::Destroy(void) // line 40
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<const bool (N2DBLogMgr::*)(void) const> N2DBLogMgr::_isOK(SERVER, "N2DBLogMgr::isOK");
const bool N2DBLogMgr::isOK(void) const // line 25 (N2DBLogMgr.h)
{
	return (this->*_isOK)();

	//TODO
}


hook_method<bool (N2DBLogMgr::*)(void)> N2DBLogMgr::_Start(SERVER, "N2DBLogMgr::Start");
bool N2DBLogMgr::Start(void) // line 75
{
	return (this->*_Start)();

	//TODO
}


hook_method<void (N2DBLogMgr::*)(void)> N2DBLogMgr::_Stop(SERVER, "N2DBLogMgr::Stop");
void N2DBLogMgr::Stop(void) // line 85
{
	return (this->*_Stop)();

	//TODO
}


hook_method<bool (N2DBLogMgr::*)(N2DBLog* const in_cpDBLog)> N2DBLogMgr::_Add(SERVER, "N2DBLogMgr::Add");
bool N2DBLogMgr::Add(N2DBLog* const in_cpDBLog) // line 28 (N2DBLogMgr.h)
{
	return (this->*_Add)(in_cpDBLog);

	//TODO
}


hook_method<static bool (__cdecl *)(const int in_WorkThreadNum, const mystd::string in_ConnectStr)> N2DBLogMgr::_CreateInstance(SERVER, "N2DBLogMgr::CreateInstance");
bool N2DBLogMgr::CreateInstance(const int in_WorkThreadNum, const mystd::string in_ConnectStr) // line 49
{
	return (_CreateInstance)(in_WorkThreadNum, in_ConnectStr);

	//TODO
}


hook_method<static void (__cdecl *)(void)> N2DBLogMgr::_DestroyInstance(SERVER, "N2DBLogMgr::DestroyInstance");
void N2DBLogMgr::DestroyInstance(void) // line 61
{
	return (_DestroyInstance)();

	//TODO
}
