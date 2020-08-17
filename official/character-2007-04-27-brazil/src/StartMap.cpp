#include "StartMap.h"


/// singleton instance
static CStartMap CStartMapInstance;
CStartMap* CSingleton<CStartMap>::ms_Singleton;


CStartMap::CStartMap()
{
	m_pStartMapInfo = NULL;
	m_dwMapCount = 0;
}


CStartMap::~CStartMap()
{
	if( m_pStartMapInfo != NULL )
	{
		delete[] m_pStartMapInfo;
		m_pStartMapInfo = NULL;
	}
}


bool CStartMap::Initialize()
{
	if( !m_parser.CScriptParser::LoadFile("character.startMap.txt") )
	{// file missing, use some meaningful defaults
		m_pStartMapInfo = new _SSTARTMAP_[5];
		m_dwMapCount = 5;
		for( size_t i = 0; i < 5; ++i )
		{
			m_pStartMapInfo[i].m_nXPos = 53;
			m_pStartMapInfo[i].m_nYPos = 111;
			m_pStartMapInfo[i].m_nSxPos = 53;
			m_pStartMapInfo[i].m_nSyPos = 111;
		}

		strcpy(m_pStartMapInfo[0].m_szMapName, "new_1-1.gat");
		strcpy(m_pStartMapInfo[0].m_szRestartMapName, "new_1-1.gat");
		strcpy(m_pStartMapInfo[1].m_szMapName, "new_2-1.gat");
		strcpy(m_pStartMapInfo[1].m_szRestartMapName, "new_2-1.gat");
		strcpy(m_pStartMapInfo[2].m_szMapName, "new_3-1.gat");
		strcpy(m_pStartMapInfo[2].m_szRestartMapName, "new_3-1.gat");
		strcpy(m_pStartMapInfo[3].m_szMapName, "new_4-1.gat");
		strcpy(m_pStartMapInfo[3].m_szRestartMapName, "new_4-1.gat");
		strcpy(m_pStartMapInfo[4].m_szMapName, "new_5-1.gat");
		strcpy(m_pStartMapInfo[4].m_szRestartMapName, "new_5-1.gat");
		return true;
	}

	m_pStartMapInfo = new _SSTARTMAP_[m_parser.size()];
	m_dwMapCount = m_parser.size();

	for( size_t i = 0; i < m_parser.size(); ++i )
	{
		const char* szXPos = m_parser.CScriptParser::GetItem(i, 0);
		if( szXPos == NULL ) return false;
		m_pStartMapInfo[i].m_nXPos = atoi(szXPos);

		const char* szYPos = m_parser.CScriptParser::GetItem(i, 1);
		if( szYPos == NULL ) return false;
		m_pStartMapInfo[i].m_nYPos = atoi(szYPos);

		const char* szMapName = m_parser.CScriptParser::GetItem(i, 2);
		if( szMapName == NULL ) return false;
		strcpy(m_pStartMapInfo[i].m_szMapName, szMapName);

		const char* szSxPos = m_parser.CScriptParser::GetItem(i, 3);
		if( szSxPos == NULL ) return false;
		m_pStartMapInfo[i].m_nSxPos = atoi(szSxPos);

		const char* szSyPos = m_parser.CScriptParser::GetItem(i, 4);
		if( szSyPos == NULL ) return false;
		m_pStartMapInfo[i].m_nSyPos = atoi(szSyPos);

		const char* szRestartMapName = m_parser.CScriptParser::GetItem(i, 5);
		if( szRestartMapName == NULL ) return false;
		strcpy(m_pStartMapInfo[i].m_szRestartMapName, szRestartMapName);
	}

	return true;
}


void CStartMap::GetRandomOne(_SSTARTMAP_& rData)
{
	memcpy(&rData, &m_pStartMapInfo[rand() % m_dwMapCount], sizeof(_SSTARTMAP_));
}
