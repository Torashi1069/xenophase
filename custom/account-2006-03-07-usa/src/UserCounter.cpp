#include "Account.h"
#include "CharacterServerInfo.h"
#include "UserCounter.h"
#include "WUCSSvrProcess.h"
#include "Enums.h"


/// singleton instance
static CUserCounter g_CUserCountInstance;
CUserCounter* CSingleton<CUserCounter>::ms_Singleton;


CUserCounter::CUserCounter()
{
	m_fp = NULL;
	memset(m_szPath, 0, sizeof(m_szPath));
	GetCurrentDirectoryA(sizeof(m_szPath), m_szPath);
	CreateDirectoryA("UserCount", NULL);
}


CUserCounter::~CUserCounter()
{
	if( m_fp != NULL )
	{
		fflush(m_fp);
		fclose(m_fp);
		m_fp = NULL;
	}

	m_nLocalSID = 0;

	SetCurrentDirectoryA(m_szPath);
}


void CUserCounter::GetTime()
{
	memset(m_szTime, 0, sizeof(m_szTime));

	time_t ltime;
	time(&ltime);

	strftime(m_szTime, sizeof(m_szTime), "%H:%M:%S", localtime(&ltime));
	strftime(m_szDate, sizeof(m_szDate), "%Y%m%d", localtime(&ltime));
}


void CUserCounter::OpenFile(const char* file)
{
	time_t ltime;
	time(&ltime);
	SetCurrentDirectoryA("UserCount");

	if( m_fp != NULL )
	{
		fflush(m_fp);
		fclose(m_fp);
		m_fp = NULL;
	}

	for( int i = 0; i <= 99; ++i )
	{
		char szFileName[256];
		sprintf(szFileName, "%s_%.2d_%s", m_szDate, i, file);

		m_fp = fopen(szFileName, "r");
		if( m_fp == NULL )
		{
			m_fp = fopen(szFileName, "a");
			break;
		}

		if( _filelength(_fileno(m_fp)) < 1024*1024 )
		{
			fclose(m_fp);
			m_fp = fopen(szFileName, "a");
			break;
		}

		fclose(m_fp);
	}
}


// guessed
void CUserCounter::CloseFile()
{
	if( m_fp != NULL )
	{
		fflush(m_fp);
		fclose(m_fp);
		m_fp = NULL;
	}
}


void CUserCounter::SetProcess(CWUCSSvrClient* process)
{
	m_process = process;
}


void CUserCounter::InitServer(const char* servername, int serverNum)
{
	memset(m_szServerName, '\0', sizeof(m_szServerName));
	strncpy(m_szServerName, servername, strlen(servername));
	m_nServerNumber = serverNum;
}


char* CUserCounter::GetServerName()
{
	return m_szServerName;
}


int CUserCounter::GetServerNumber()
{
	return m_nServerNumber;
}


void CUserCounter::WriteUserCount()
{
	this->CUserCounter::GetTime();

	int iCharacterCount;
	SERVER_ADDR* ServerInfo = g_characterServerInfo[CLIENTTYPE_ENGLISH].CCharacterServerInfo::GetCharacterServerInfo(&iCharacterCount);

	int nTotalUserCount = 0;
	for( int i = 0; i < iCharacterCount; ++i )
		nTotalUserCount += ServerInfo[i].usercount;

	this->CUserCounter::OpenFile("UserCount.txt");
	if( m_fp != NULL )
	{
		fprintf(m_fp, "%s\t%d\t%d\t%s %s\n", m_szServerName, SERVERTYPE_ACCOUNT, nTotalUserCount, m_szDate, m_szTime);

		for( int i = 0; i < iCharacterCount; ++i )
		{
			fprintf(m_fp, "%s_%s\t%d\t%d\t%s %s\n", m_szServerName, ServerInfo[i].name, SERVERTYPE_CHARACTER, ServerInfo[i].usercount, m_szDate, m_szTime);
			m_dwArrCharUserCounter[i] = ServerInfo[i].usercount;
		}

		if( m_process != NULL )
		{
			m_process->CWUCSSvrClient::SendAccUserCounter(nTotalUserCount, m_szDate, m_szTime);
			if( iCharacterCount != 0 )
				m_process->CWUCSSvrClient::SendCharUserCounter(m_dwArrCharUserCounter);
		}
	}

	if( m_fp != NULL )
	{
		fflush(m_fp);
		fclose(m_fp);
		m_fp = NULL;
		SetCurrentDirectoryA(m_szPath);
	}
}
