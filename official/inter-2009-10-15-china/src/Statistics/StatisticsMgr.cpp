#include "StatisticsMgr.h"
#include "ZServerMgr.h"
#include "globals.hpp"


hook_ptr<CStatisticsMgr*> CStatisticsMgr::m_cpSelf(SERVER, "CStatisticsMgr::m_cpSelf"); // = NULL;


CStatisticsMgr::CStatisticsMgr(void) // line 18
{
	m_ReportPerMinute = 60;
	m_bOK = false;

	if( this->CStatisticsMgr::Create() )
		m_bOK = true;
}


CStatisticsMgr::~CStatisticsMgr(void) // line 25
{
	this->CStatisticsMgr::Destroy();
}


hook_method<bool (CStatisticsMgr::*)(void)> CStatisticsMgr::_Create(SERVER, "CStatisticsMgr::Create");
bool CStatisticsMgr::Create(void) // line 36
{
	return (this->*_Create)();

	//TODO
}


hook_method<void (CStatisticsMgr::*)(void)> CStatisticsMgr::_Destroy(SERVER, "CStatisticsMgr::Destroy");
void CStatisticsMgr::Destroy(void) // line 31
{
	return (this->*_Destroy)();

	//TODO
}


hook_method<bool (CStatisticsMgr::*)(void)> CStatisticsMgr::_isOK(SERVER, "CStatisticsMgr::isOK");
bool CStatisticsMgr::isOK(void) // line 22
{
	return (this->*_isOK)();

	//TODO
}


hook_method<void (CStatisticsMgr::*)(void)> CStatisticsMgr::_Process(SERVER, "CStatisticsMgr::Process");
void CStatisticsMgr::Process(void) // line 73
{
	return (this->*_Process)();

	if( time(NULL) < (time_t)m_LogOutputEvnetDT )
		return;

	m_LogOutputEvnetDT.CDateTime::AddTime(0, 0, m_ReportPerMinute);
	g_zServerMgr.CZServerMgr::OutputZSVRStatisticLog(m_LogOutputEvnetDT);
	g_zServerMgr.CZServerMgr::OutputMAPStatisticLog(m_LogOutputEvnetDT);
}


hook_method<static bool (__cdecl *)(void)> CStatisticsMgr::_CreateInstance(SERVER, "CStatisticsMgr::CreateInstance");
bool CStatisticsMgr::CreateInstance(void) // line 55
{
	return (_CreateInstance)();

	if( CStatisticsMgr::m_cpSelf != NULL )
		return false;

	CStatisticsMgr::m_cpSelf = new CStatisticsMgr();
	if( CStatisticsMgr::m_cpSelf == NULL )
		return false;

	if( !CStatisticsMgr::m_cpSelf->m_bOK )
	{
		delete CStatisticsMgr::m_cpSelf;
		CStatisticsMgr::m_cpSelf = (CStatisticsMgr*)NULL;
		return false;
	}

	return true;
}


hook_method<static void (__cdecl *)(void)> CStatisticsMgr::_DestroyInstance(SERVER, "CStatisticsMgr::DestroyInstance");
void CStatisticsMgr::DestroyInstance(void) // line 69
{
	return (_DestroyInstance)();

	if( CStatisticsMgr::m_cpSelf != NULL )
	{
		delete CStatisticsMgr::m_cpSelf;
		CStatisticsMgr::m_cpSelf = (CStatisticsMgr*)NULL;
	}
}


/// @custom
CStatisticsMgr* CStatisticsMgr::GetObj(void)
{
	return m_cpSelf;
}
