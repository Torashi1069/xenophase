#include "Common/ServerInfoList.h"


/// singleton instance
static CServerInfoList g_ServerInfoList;
CServerInfoList* CSingleton<CServerInfoList>::ms_Singleton;


CServerInfoList::CServerInfoList()
{
}


CServerInfoList::~CServerInfoList()
{
}


BOOL CServerInfoList::GetServerInfo(SSERVERINFO* pServerInfo, int nSID)
{
	BOOL bFound = FALSE;
	m_csServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorServerInfoList.size(); ++i )
	{
		SSERVERINFO& info = m_vectorServerInfoList[i];

		if( info.m_nSID == nSID )
		{
			memcpy(pServerInfo, &info, sizeof(*pServerInfo));
			bFound = TRUE;
			break; // found.
		}
	}

	m_csServerInfoList.Leave();
	return bFound;
}


void CServerInfoList::AddServerInfo(SSERVERINFO* pServerInfo)
{
	m_csServerInfoList.Enter();
	m_vectorServerInfoList.push_back(*pServerInfo);
	m_csServerInfoList.Leave();
}


int CServerInfoList::GetSID(DWORD dwIP, int nType)
{
	int nSID = 0;
	m_csServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorServerInfoList.size(); ++i )
	{
		SSERVERINFO& info = m_vectorServerInfoList[i];

		if( info.m_dwIP == dwIP || (info.m_dwPrivateIP != 0 && info.m_dwPrivateIP == dwIP) )
			if( info.m_nType == 0 || info.m_nType == nType )
				nSID = info.m_nSID;
	}

	m_csServerInfoList.Leave();
	return nSID;
}


int CServerInfoList::GetSID(int nPrimaryDestnation, int* pnSID)
{
	int nIndex = 0;
	m_csServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorServerInfoList.size(); ++i )
	{
		SSERVERINFO& info = m_vectorServerInfoList[i];

		if( info.m_nPrimaryDestnation == nPrimaryDestnation )
		{
			pnSID[nIndex] = info.m_nSID;
			++nIndex;
		}
	}

	m_csServerInfoList.Leave();
	return nIndex;
}


int CServerInfoList::GetIPType(DWORD dwIP)
{
	int nType = 0;
	m_csServerInfoList.Enter();

	for( size_t i = 0; i < m_vectorServerInfoList.size(); ++i )
	{
		SSERVERINFO& info = m_vectorServerInfoList[i];

		if( info.m_dwIP == dwIP )
		{
			nType = info.m_nType;
			break;
		}
	}

	m_csServerInfoList.Leave();
	return nType;
}
