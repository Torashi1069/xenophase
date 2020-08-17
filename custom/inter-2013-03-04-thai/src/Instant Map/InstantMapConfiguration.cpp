#include "InterServer.h"
#include "Instant Map/InstantMapConfiguration.h"


/// singleton instance
CInstantMapConfiguration*& CInstantMapConfiguration::m_cpSelf = VTOR<CInstantMapConfiguration*>(DetourFindFunction(EXEPATH(), "CInstantMapConfiguration::m_cpSelf"));


CInstantMapConfiguration::CInstantMapConfiguration()
{
	m_DestroyWaitSecond = 30;
	m_CreateResponseWaitSecond_fromZSVR = 60;
	m_bOpen = true;
	m_bOK = false;

	if( this->CInstantMapConfiguration::Create() )
		m_bOK = true;
}


CInstantMapConfiguration::~CInstantMapConfiguration()
{
}


bool CInstantMapConfiguration::Create()
{
	m_DestroyWaitSecond = GetPrivateProfileIntA("INSTANT MAP", "destroy wait second", 30, g_infFile);
	m_CreateResponseWaitSecond_fromZSVR = GetPrivateProfileIntA("INSTANT MAP", "create wait second from zone server", 60, g_infFile);
	m_bOpen = ( GetPrivateProfileIntA("INSTANT MAP", "open", 1, g_infFile) != 0 );
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


int CInstantMapConfiguration::GetDestroyWiatSecond()
{
	return m_DestroyWaitSecond;
}


int CInstantMapConfiguration::GetCreateResponseWaitSecond_fromZSVR()
{
	return m_CreateResponseWaitSecond_fromZSVR;
}


bool CInstantMapConfiguration::IsOpen()
{
	return m_bOpen;
}
