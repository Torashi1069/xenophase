#include "PreventNameList.h"


/// singleton instance
static CPreventNameList g_PreventNameList;
CPreventNameList* CSingleton<CPreventNameList>::ms_Singleton;


CPreventNameList::CPreventNameList()
{
	m_nCount = 0;
	memset(m_szPreventName, '\0', sizeof(m_szPreventName));
}


CPreventNameList::~CPreventNameList()
{
}


//void CPreventNameList::InitPreventNameList()
//{
//	// not available
//}


BOOL CPreventNameList::IsPreventName(char* pszName)
{
	for( int i = 0; i < m_nCount; ++i )
		if( strstr(pszName, m_szPreventName[i]) != NULL )
			return TRUE;

	return FALSE;
}
