#include "ZoneProcess.h"
#include "Instant map/InstantMapConfiguration.h"


/// singleton instance
CInstantMapConfiguration*& CInstantMapConfiguration::m_cpSelf = VTOR<CInstantMapConfiguration*>(DetourFindFunction(EXEPATH(), "CInstantMapConfiguration::m_cpSelf"));


CInstantMapConfiguration::CInstantMapConfiguration()
: m_FirstScriptEventRunSecond(30), m_Allow(false), m_expect_maximum_life_minute(300), m_bOK(false)
{
	if( this->CInstantMapConfiguration::Create() )
		m_bOK = true;
}


CInstantMapConfiguration::~CInstantMapConfiguration()
{
}


bool CInstantMapConfiguration::Create()
{
	m_FirstScriptEventRunSecond = GetPrivateProfileIntA("Instant Map", "second of first script event time out check", 30, g_infFile);
	m_Allow = GetPrivateProfileIntA("Instant Map", "allow", 0, g_infFile) != 0;
	m_expect_maximum_life_minute = GetPrivateProfileIntA("Instant Map", "expect maximum life minute", 300, g_infFile);

	return true;
}


void CInstantMapConfiguration::Destroy()
{
}


bool CInstantMapConfiguration::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CInstantMapConfiguration();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CInstantMapConfiguration::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CInstantMapConfiguration::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CInstantMapConfiguration* CInstantMapConfiguration::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CInstantMapConfiguration::isOK() const
{
	return m_bOK;
}


int CInstantMapConfiguration::GetFirstScriptEventRunSecond()
{
	return m_FirstScriptEventRunSecond;
}


bool CInstantMapConfiguration::IsAllow()
{
	return m_Allow;
}


int CInstantMapConfiguration::GetExpectMaximumLifeMinute()
{
	return m_expect_maximum_life_minute;
}
