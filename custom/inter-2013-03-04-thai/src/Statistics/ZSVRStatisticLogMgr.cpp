#include "InterServer.h"
#include "shared/N2System/DBLog/N2DBLogMgr.h"
#include "Statistics/ZSVRStatisticLog.h"
#include "Statistics/ZSVRStatisticLogMgr.h"


/// singleton instance
CZSVRStatisticLogMgr*& CZSVRStatisticLogMgr::m_cpSelf = VTOR<CZSVRStatisticLogMgr*>(DetourFindFunction(EXEPATH(), "CZSVRStatisticLogMgr::m_cpSelf"));


CZSVRStatisticLogMgr::CZSVRStatisticLogMgr()
{
	m_bOutputLog = false;
	m_bOK = false;

	if( GetPrivateProfileIntA("STATISTIC", "zone server report", 0, g_infFile) )
		m_bOutputLog = true;

	m_bOK = true;
}


CZSVRStatisticLogMgr::~CZSVRStatisticLogMgr()
{
}


bool CZSVRStatisticLogMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CZSVRStatisticLogMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZSVRStatisticLogMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZSVRStatisticLogMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZSVRStatisticLogMgr* CZSVRStatisticLogMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZSVRStatisticLogMgr::isOK() const
{
	return m_bOK;
}


void CZSVRStatisticLogMgr::Add(const time_t in_Date, const int in_ZSID, const int in_PlayerNum, const int in_NPCNum, const int in_MemoryKBytes, const int in_TotalServiceMapNum, const int in_ServiceInstantMapNum)
{
	if( !m_bOutputLog )
		return;

	CZSVRStatisticLog* Log = new(std::nothrow) CZSVRStatisticLog(in_Date, in_ZSID, in_PlayerNum, in_NPCNum, in_MemoryKBytes, in_TotalServiceMapNum, in_ServiceInstantMapNum);
	if( Log == NULL )
		return;

	if( !N2DBLogMgr::GetObj()->N2DBLogMgr::Add(Log) )
	{
		delete Log;
		return;
	}
}
