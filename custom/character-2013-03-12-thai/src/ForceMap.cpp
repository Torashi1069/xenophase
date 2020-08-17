#include "ForceMap.h"


/// singleton instance
static CForceMap CForceMapInstance;
CForceMap* CSingleton<CForceMap>::ms_Singleton;


CForceMap::CForceMap()
{
	m_dwMapCount = 0;
	m_dwRestartMapCount = 0;
	m_pMapInfo = NULL;
	m_pRestartMapInfo = NULL;
}


CForceMap::~CForceMap()
{
	if( m_pMapInfo != NULL )
	{
		delete[] m_pMapInfo;
		m_pMapInfo = NULL;
	}

	if( m_pRestartMapInfo != NULL )
	{
		delete[] m_pRestartMapInfo;
		m_pRestartMapInfo = NULL;
	}
}


DWORD CForceMap::getMapCount()
{
	return m_dwMapCount;
}


DWORD CForceMap::getRestartMapCount()
{
	return m_dwRestartMapCount;
}
