#include "CMercenaryDBV2.hpp"


hook_ptr<CMercenaryDBV2 *> CMercenaryDBV2::m_cpSelf(SERVER, "CMercenaryDBV2::m_cpSelf"); // = ?


CMercenaryDBV2::CMercenaryDBV2(const mystd::string in_strDSNname, const mystd::string in_strUserID, const mystd::string in_strPWD, const mystd::string in_strDBname, const enum CODBCV2Connector::enumConnectType in_eConnectType) // line 23
{
	m_bOK = false;
	if( this->CODBCV2::Init(in_strDSNname, in_strUserID, in_strPWD, in_strDBname, in_eConnectType, true) )
		m_bOK = true;
}


CMercenaryDBV2::~CMercenaryDBV2(void) // line 43
{
}


hook_method<bool (CMercenaryDBV2::*)(void)> CMercenaryDBV2::_isOK(SERVER, "CMercenaryDBV2::isOK");
bool CMercenaryDBV2::isOK(void) // line 50
{
	return (this->*_isOK)();

	return m_bOK;
}


hook_method<static bool (__cdecl *)(const mystd::string in_strDSNname, const mystd::string in_strUserID, const mystd::string in_strPWD, const mystd::string in_strDBname, const enum CODBCV2Connector::enumConnectType in_eConnectType)> CMercenaryDBV2::_CreateInstance(SERVER, "CMercenaryDBV2::CreateInstance");
bool __cdecl CMercenaryDBV2::CreateInstance(const mystd::string in_strDSNname, const mystd::string in_strUserID, const mystd::string in_strPWD, const mystd::string in_strDBname, const enum CODBCV2Connector::enumConnectType in_eConnectType) // line 66
{
	return (CMercenaryDBV2::_CreateInstance)(in_strDSNname, in_strUserID, in_strPWD, in_strDBname, in_eConnectType);

	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new CMercenaryDBV2(in_strDSNname, in_strUserID, in_strPWD, in_strDBname, in_eConnectType);

	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMercenaryDBV2::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = (CMercenaryDBV2*)NULL;
		return false;
	}

	return true;
}


//hook_method<static void (__cdecl *)(void)> CMercenaryDBV2::_DestroyInstance(SERVER, "CMercenaryDBV2::DestroyInstance");
void __cdecl CMercenaryDBV2::DestroyInstance(void) // line ??
{
//	return (CMercenaryDBV2::_DestroyInstance)();

	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = (CMercenaryDBV2*)NULL;
	}
}
