#include "Common/EnterTraceLog.h"
#include "Common/InfoScript.h"


CInfoScript::CInfoScript()
{
}


// guessed
CInfoScript::CInfoScript(const char* pszScript)
{
	this->CInfoScript::Open(pszScript);
}


CInfoScript::~CInfoScript()
{
}


void CInfoScript::Open(const char* pszScript)
{
	m_mapInfoScript.clear();

	FILE* pFile = fopen(pszScript, "r");
	if( pFile == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "%s open failed!", pszScript);

	char szBuffer[256] = {};
	char szColumn[256] = {};
	char szInfo[256] = {};

	while( !feof(pFile) )
	{
		memset(szBuffer, '\0', sizeof(szBuffer));
		fgets(szBuffer, sizeof(szBuffer), pFile);

		if( strlen(szBuffer) < 3 )
			continue;

		if( strstr(szBuffer, "//") != NULL )
			continue;

		sscanf(szBuffer, "%s %s", szColumn, szInfo);
		_strupr(szColumn);

		printf("%s %s\n", szColumn, szInfo);
		m_mapInfoScript[szColumn] = szInfo;
	}

	fclose(pFile);
	_flushall();
}


const char* CInfoScript::GetInfo(char* lpszColumn)
{
	const char* szValue;
	m_csInfoScript.Enter();

	char szColumn[256] = {};
	strncpy(szColumn, lpszColumn, sizeof(szColumn)-1);
	_strupr(szColumn);

	std::map<std::string,std::string>::const_iterator iInfo = m_mapInfoScript.find(szColumn);
	szValue = ( iInfo != m_mapInfoScript.end() ) ? iInfo->second.c_str() : NULL;

	m_csInfoScript.Leave();
	return szValue;
}
