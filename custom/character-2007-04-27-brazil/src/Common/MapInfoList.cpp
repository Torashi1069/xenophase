#include "Common/MapInfoList.h"


/// singleton instance
static CMapInfoList g_MapInfoList;
CMapInfoList* CSingleton<CMapInfoList>::ms_Singleton;


void CMapInfoList::AddMapInfo(SMAPINFO* pMapInfo)
{
	m_csMapInfoList.Enter();
	m_vectorMapInfoList.push_back(*pMapInfo);
	m_csMapInfoList.Leave();
}


int CMapInfoList::GetSID(char* pMapName)
{
	int nSID = -1;
	m_csMapInfoList.Enter();

	int nCount = m_vectorMapInfoList.size();
	for( int i = 0; i < nCount; ++i )
	{
		if( _stricmp(m_vectorMapInfoList[i].m_szMapName, pMapName) == 0 )
		{
			nSID = m_vectorMapInfoList[i].m_dwSID;
			break; // found.
		}
	}

	m_csMapInfoList.Leave();
	return nSID;
}


int CMapInfoList::GetMapType(char* pMapName)
{
	int nMapType = -1;
	m_csMapInfoList.Enter();

	int nCount = m_vectorMapInfoList.size();
	for( int i = 0; i < nCount; ++i )
	{
		if( _stricmp(m_vectorMapInfoList[i].m_szMapName, pMapName) == 0 )
		{
			nMapType = m_vectorMapInfoList[i].m_dwMapType;
			break; // found.
		}
	}

	m_csMapInfoList.Leave();
	return nMapType;
}
