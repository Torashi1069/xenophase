#include "CZoneProcessConfigMgr.h"


/// singleton instance
CZoneProcessConfigMgr*& CZoneProcessConfigMgr::m_cpSelf = VTOR<CZoneProcessConfigMgr*>(DetourFindFunction(EXEPATH(), "CZoneProcessConfigMgr::m_cpSelf"));


CZoneProcessConfigMgr::CZoneProcessConfigMgr()
: m_bOK(false)
{
	std::pair<bool,std::string> createRet = this->CZoneProcessConfigMgr::Create();
	if( !createRet.first )
	{
		MessageBoxA(NULL, createRet.second.c_str(), "ZoneProcessConfig Error", MB_OK);
		return;
	}

	m_bOK = true;
}


CZoneProcessConfigMgr::~CZoneProcessConfigMgr()
{
}


bool CZoneProcessConfigMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CZoneProcessConfigMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CZoneProcessConfigMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CZoneProcessConfigMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CZoneProcessConfigMgr* CZoneProcessConfigMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CZoneProcessConfigMgr::isOK() const
{
	return m_bOK;
}


std::pair<bool,std::string> CZoneProcessConfigMgr::Create()
{
	return std::pair<bool,std::string>(true, "good");
}
