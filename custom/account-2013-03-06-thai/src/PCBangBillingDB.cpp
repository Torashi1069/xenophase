#include "PCBangBillingDB.h"
#include "Common/DatabaseStatement.h"
#include "Common/Network.h"
#include "Common/NSyncObject.h"


/// singleton instance
static CPCBangBillingDB g_PCBangBillingDB;
CPCBangBillingDB* CPCBangBillingDB::m_cpSelf;


CPCBangBillingDB::CPCBangBillingDB()
{
	m_bOK = false;
	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


CPCBangBillingDB::~CPCBangBillingDB()
{
	DeleteCriticalSection(&m_CS);
}


bool CPCBangBillingDB::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CPCBangBillingDB();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
		return false;
	
	return true;
}


void CPCBangBillingDB::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


/// @custom
CPCBangBillingDB* CPCBangBillingDB::GetObj()
{
	return m_cpSelf;
}


bool CPCBangBillingDB::isOK()
{
	return m_bOK;
}


bool CPCBangBillingDB::IsPCBangIP(DWORD dwIP)
{
	NSyncObject sync(m_CS);

	int nRet = 0;

	char szIP[16] = {};
	CNetwork::GetObj()->CNetwork::GetTextIP(dwIP, szIP);

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("SELECT count(*) FROM PcPremiumServiceListDB WHERE IP=%s;", szIP);
	stmt.CDatabaseStatement::BindNumberColumn(1, &nRet);

	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		nRet = 0;
	
	stmt.CDatabaseStatement::Release();
	return ( nRet > 0 );
}


bool CPCBangBillingDB::SetIPBonusLimit(DWORD in_dwIP)
{
	NSyncObject sync(m_CS);

	std::list<DWORD>::const_iterator it;
	for( it = m_listIPBonusLicenseLimit.begin(); it != m_listIPBonusLicenseLimit.end(); ++it )
		if( *it == in_dwIP )
			break;

	if( it != m_listIPBonusLicenseLimit.end() )
		return false; // already exists.

	m_listIPBonusLicenseLimit.push_back(in_dwIP);
	return true;
}


bool CPCBangBillingDB::GetIPBonusLimit(DWORD in_dwIP)
{
	NSyncObject sync(m_CS);

	std::list<DWORD>::const_iterator it;
	for( it = m_listIPBonusLicenseLimit.begin(); it != m_listIPBonusLicenseLimit.end(); ++it )
		if( *it == in_dwIP )
			break;

	if( it != m_listIPBonusLicenseLimit.end() )
		return false;

	return true;
}


void CPCBangBillingDB::DeleteIPBonusLimit(DWORD in_dwIP)
{
	NSyncObject sync(m_CS);

	std::list<DWORD>::const_iterator it;
	for( it = m_listIPBonusLicenseLimit.begin(); it != m_listIPBonusLicenseLimit.end(); ++it )
		if( *it == in_dwIP )
			break;

	if( it == m_listIPBonusLicenseLimit.end() )
		return; // nothing to delete.

	m_listIPBonusLicenseLimit.erase(it);
}
