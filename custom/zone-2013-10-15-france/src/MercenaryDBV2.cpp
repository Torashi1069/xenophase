#include "MercenaryDBV2.h"


/// singleton instance
CMercenaryDBV2*& CMercenaryDBV2::m_cpSelf = VTOR<CMercenaryDBV2*>(DetourFindFunction(EXEPATH(), "CMercenaryDBV2::m_cpSelf"));


CMercenaryDBV2::CMercenaryDBV2(const std::string in_strFileDSN, const std::string in_strPWD, const CODBCV2Connector::enumConncetType in_eConnectType)
: m_bOK(false)
{
	if( this->CODBCV2::Init(in_strFileDSN, in_strPWD, in_eConnectType, true) == true )
		m_bOK = true;
}


CMercenaryDBV2::~CMercenaryDBV2()
{
}


CMercenaryDBV2* CMercenaryDBV2::GetObj()
{
	return m_cpSelf;
}


bool CMercenaryDBV2::CreateInstance(const std::string in_strFileDSN, const std::string in_strPWD, const CODBCV2Connector::enumConncetType in_eConnectType)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new CMercenaryDBV2(in_strFileDSN, in_strPWD, in_eConnectType);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMercenaryDBV2::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMercenaryDBV2::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


bool CMercenaryDBV2::isOK() const
{
	return m_bOK;
}
