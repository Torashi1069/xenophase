#include "UserAuthenticate.h"
#include "Common/EnterTraceLog.h"


CUserAuthenticate::CUserAuthenticate()
{
	m_nSize = 0;
	m_pAuthenticate = NULL;
	m_pAuthenticate = new tag_SMAP_AUTH[500];
}


CUserAuthenticate::~CUserAuthenticate()
{
	if( m_pAuthenticate != NULL )
	{
		for( int i = 0; i < 500; ++i )
		{
			tag_SMAP_AUTH* auth = &m_pAuthenticate[i];

			auth->m_csMap.Enter();
			for( stdext::hash_map<DWORD,__SUSERAUTHENTICATE__*>::iterator it = auth->m_Map.begin(); it != auth->m_Map.end(); ++it )
				delete it->second;
			auth->m_Map.clear();
			auth->m_csMap.Leave();
		}

		delete[] m_pAuthenticate;
		m_pAuthenticate = NULL;
	}
}


void CUserAuthenticate::Insert(DWORD dwAID, __SUSERAUTHENTICATE__& object)
{
	if( dwAID <= 0 || dwAID >= 299999999 )
		return;

	if( m_pAuthenticate == NULL )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "m_pAuthenticate is 0 func %s\n", __FUNCTION__);
		return;
	}

	tag_SMAP_AUTH* auth = &m_pAuthenticate[dwAID % 500];

	auth->m_csMap.Enter();

	stdext::hash_map<DWORD,__SUSERAUTHENTICATE__*>::iterator it = auth->m_Map.find(dwAID);
	if( it == auth->m_Map.end() )
	{
		__SUSERAUTHENTICATE__* pObj = new __SUSERAUTHENTICATE__;
		if( pObj == NULL )
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s error !!!!! new fail.. aid %u \n", __FUNCTION__, dwAID);
			auth->m_csMap.Leave();
			return;
		}

		*pObj = object;
		auth->m_Map[dwAID] = pObj;
		InterlockedIncrement(reinterpret_cast<LONG*>(&m_nSize));
	}
	else
	{
		*it->second = object;
	}

	auth->m_csMap.Leave();
}


BOOL CUserAuthenticate::Bring(DWORD dwAID, __SUSERAUTHENTICATE__* pObject)
{
	if( dwAID <= 0 || dwAID >= 299999999 )
		return FALSE;

	if( m_pAuthenticate == NULL )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "m_pAuthenticate is 0 func %s\n", __FUNCTION__);
		return FALSE;
	}

	tag_SMAP_AUTH* auth = &m_pAuthenticate[dwAID % 500];

	auth->m_csMap.Enter();

	stdext::hash_map<DWORD,__SUSERAUTHENTICATE__*>::iterator it = auth->m_Map.find(dwAID);
	if( it == auth->m_Map.end() )
	{
		auth->m_csMap.Leave();
		return FALSE;
	}

	*pObject = *it->second;
	delete it->second;
	auth->m_Map.erase(it);

	auth->m_csMap.Leave();
	InterlockedDecrement(reinterpret_cast<LONG*>(&m_nSize));
	return TRUE;
}


int CUserAuthenticate::GetCount()
{
	return m_nSize;
}
