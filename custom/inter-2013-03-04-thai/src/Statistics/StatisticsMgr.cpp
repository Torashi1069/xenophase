#include "InterServer.h"
#include "Statistics/StatisticsMgr.h"
#include "Statistics/MAPStatisticLogMgr.h"
#include "Statistics/ZSVRStatisticLogMgr.h"
#include "Zsvr/CZsvrMgr.h"


/// singleton instance
CStatisticsMgr*& CStatisticsMgr::m_cpSelf = VTOR<CStatisticsMgr*>(DetourFindFunction(EXEPATH(), "CStatisticsMgr::m_cpSelf"));


CStatisticsMgr::CStatisticsMgr()
{
	m_ReportPerMinute = 60;
	m_bOK = false;

	if( this->CStatisticsMgr::Create() )
		m_bOK = true;
}


CStatisticsMgr::~CStatisticsMgr()
{
	this->CStatisticsMgr::Destroy();
}


bool CStatisticsMgr::Create()
{
	if( !CZSVRStatisticLogMgr::CreateInstance()
	||  !CMAPStatisticLogMgr::CreateInstance() )
		return false;

	m_ReportPerMinute = GetPrivateProfileIntA("STATISTIC", "report per minute", 60, g_infFile);

	SYSTEMTIME st;
	GetLocalTime(&st);
	m_LogOutputEvnetDT.CDateTime::SetTime(st.wYear, st.wMonth, st.wDay, st.wHour);
	m_LogOutputEvnetDT.CDateTime::AddTime(0, 0, m_ReportPerMinute);

	time_t t = time(NULL);
	while( t >= m_LogOutputEvnetDT )
		m_LogOutputEvnetDT.CDateTime::AddTime(0, 0, m_ReportPerMinute);

	return true;
}


void CStatisticsMgr::Destroy()
{
	CZSVRStatisticLogMgr::DestroyInstance();
	CMAPStatisticLogMgr::DestroyInstance();
}


bool CStatisticsMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CStatisticsMgr();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->CStatisticsMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CStatisticsMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CStatisticsMgr* CStatisticsMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CStatisticsMgr::isOK() const
{
	return m_bOK;
}


void CStatisticsMgr::Process()
{
	if( time(NULL) >= m_LogOutputEvnetDT )
	{
		m_LogOutputEvnetDT.CDateTime::AddTime(0, 0, m_ReportPerMinute);
		CZsvrMgr::GetObj()->CZServerMgr::OutputZSVRStatisticLog(m_LogOutputEvnetDT);
		CZsvrMgr::GetObj()->CZServerMgr::OutputMAPStatisticLog(m_LogOutputEvnetDT);
	}
}
