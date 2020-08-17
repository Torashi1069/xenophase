#include "InterServer.h"
#include "shared/N2System/DBLog/N2DBLogMgr.h"
#include "Statistics/MAPStatisticLog.h"
#include "Statistics/MAPStatisticLogMgr.h"


/// singleton instance
CMAPStatisticLogMgr*& CMAPStatisticLogMgr::m_cpSelf = VTOR<CMAPStatisticLogMgr*>(DetourFindFunction(EXEPATH(), "CMAPStatisticLogMgr::m_cpSelf"));


CMAPStatisticLogMgr::CMAPStatisticLogMgr()
{
	m_bOutputLog = false;
	m_bOK = false;

	if( GetPrivateProfileIntA("STATISTIC", "map report", 0, g_infFile) )
		m_bOutputLog = true;

	m_bOK = true;
}


CMAPStatisticLogMgr::~CMAPStatisticLogMgr()
{
}


bool CMAPStatisticLogMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMAPStatisticLogMgr();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->CMAPStatisticLogMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMAPStatisticLogMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMAPStatisticLogMgr* CMAPStatisticLogMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMAPStatisticLogMgr::isOK() const
{
	return m_bOK;
}


void CMAPStatisticLogMgr::Add(const time_t in_Date, const int in_ZSID, const std::map<std::string,int>& in_MapInfoContainer)
{
	if( !m_bOutputLog )
		return;

	CMAPStatisticLog* Log = new(std::nothrow) CMAPStatisticLog(in_Date, in_ZSID, in_MapInfoContainer);
	if( Log == NULL )
		return;

	if( !N2DBLogMgr::GetObj()->Add(Log) )
	{
		delete Log;
		return;
	}
}
