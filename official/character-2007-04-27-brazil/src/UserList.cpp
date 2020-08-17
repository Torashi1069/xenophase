#include "UserList.h"
#include "Common/Reporter.h"


#define NUM_BUCKETS 500


CUserList::CUserList()
{
	m_nSize = 0;
	m_pUser = NULL;

	m_pUser = new tag_SMAP[NUM_BUCKETS];
}


CUserList::~CUserList()
{
	if( m_pUser == NULL )
		return;

	for( int i = 0; i < NUM_BUCKETS; ++i )
	{
		tag_SMAP* pUser = &m_pUser[i];

		pUser->m_csMap.Enter();

		for( stdext::hash_map<DWORD,__SUSER__*>::iterator iObject = pUser->m_Map.begin(); iObject != pUser->m_Map.end(); ++iObject )
			delete iObject->second;

		pUser->m_Map.clear();

		pUser->m_csMap.Leave();
	}

	delete[] m_pUser;
	m_pUser = NULL;
}


void CUserList::Insert(DWORD dwAID, __SUSER__& object)
{
	if( dwAID <= 0 || dwAID >= 299999999 )
		return;

	if( m_pUser == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("m_pUser is 0 func %s\n", __FUNCTION__);
		return;
	}

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<DWORD,__SUSER__*>::iterator iObject = pUser->m_Map.find(dwAID);
	if( iObject == pUser->m_Map.end() )
	{// add new entry
		__SUSER__* newUser = new __SUSER__;
		if( newUser == NULL )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CUserList::Insert error !!!!! new fail.. aid %u \n", dwAID);
			pUser->m_csMap.Leave();
			return;
		}

		memcpy(newUser, &object, sizeof(__SUSER__));
		pUser->m_Map[dwAID] = newUser;

		InterlockedIncrement(reinterpret_cast<LONG*>(&m_nSize));
	}
	else
	{// replace existing entry
		memcpy(iObject->second, &object, sizeof(__SUSER__));
	}

	pUser->m_csMap.Leave();
}


void CUserList::Delete(DWORD dwAID)
{
	if( dwAID <= 0 || dwAID >= 299999999 )
		return;

	if( m_pUser == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("m_pUser is 0 func %s\n", __FUNCTION__);
		return;
	}

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<DWORD,__SUSER__*>::iterator iObject = pUser->m_Map.find(dwAID);
	if( iObject == pUser->m_Map.end() )
	{
		pUser->m_csMap.Leave();
		return;
	}

	delete iObject->second;
	pUser->m_Map.erase(iObject);
	InterlockedDecrement(reinterpret_cast<LONG*>(&m_nSize));

	pUser->m_csMap.Leave();
}


BOOL CUserList::Bring(DWORD dwAID, __SUSER__* pObject)
{
	if( dwAID <= 0 || dwAID >= 299999999 )
		return FALSE;

	if( m_pUser == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("m_pUser is 0 func %s\n", __FUNCTION__);
		return FALSE;
	}

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<DWORD,__SUSER__*>::iterator iObject = pUser->m_Map.find(dwAID);
	if( iObject == pUser->m_Map.end() )
	{
		pUser->m_csMap.Leave();
		return FALSE;
	}

	memcpy(pObject, iObject->second, sizeof(__SUSER__));

	delete iObject->second;
	pUser->m_Map.erase(iObject);

	pUser->m_csMap.Leave();

	InterlockedDecrement(reinterpret_cast<LONG*>(&m_nSize));

	return TRUE;
}


BOOL CUserList::Get(DWORD dwAID, __SUSER__* pObject)
{
	if( dwAID <= 0 || dwAID >= 299999999 )
		return FALSE;

	if( m_pUser == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("m_pUser is 0 func %s\n", __FUNCTION__);
		return FALSE;
	}

	tag_SMAP* pUser = &m_pUser[dwAID % NUM_BUCKETS];

	pUser->m_csMap.Enter();

	stdext::hash_map<DWORD,__SUSER__*>::iterator iObject = pUser->m_Map.find(dwAID);
	if( iObject == pUser->m_Map.end() )
	{
		pUser->m_csMap.Leave();
		return FALSE;
	}

	memcpy(pObject, iObject->second, sizeof(__SUSER__));

	pUser->m_csMap.Leave();

	return TRUE;
}


int CUserList::GetCount()
{
	return m_nSize;
}
