#include "Common/Reporter.h"


/// singleton instance
static CReporter g_CReporterInstance;
CReporter* CSingleton<CReporter>::ms_Singleton;


CReporter::CReporter()
{
	m_fp = NULL;
	memset(m_szPath, 0, sizeof(m_szPath));
	GetCurrentDirectoryA(sizeof(m_szPath), m_szPath);
	CreateDirectoryA("Log", NULL);
}


CReporter::~CReporter()
{
	if( m_fp != NULL )
	{
		fflush(m_fp);
		fclose(m_fp);
		m_fp = NULL;
	}

	SetCurrentDirectoryA(m_szPath);
}


void CReporter::FilePrint(const char* lpszFile, const char* lpszError, ...)
{
	va_list va;
	va_start(va, lpszError);

	m_cs.Enter();

	char szMessage[1024];
	_vsnprintf(szMessage, sizeof(szMessage), lpszError, va);

	this->CReporter::GetTime();

	char szError[1024];
	if( lpszError[strlen(lpszError)-1] == '\n' )
		sprintf(szError, "%s - %s", m_szTime, szMessage);
	else
		sprintf(szError, "%s - %s\n", m_szTime, szMessage);

	this->CReporter::OpenLogFile(lpszFile);

	if( m_fp != NULL )
	{
		fputs(szError, m_fp);
		this->CReporter::CloseLogFile();
	}

	m_cs.Leave();
}


void CReporter::Log(const char* lpszError, ...)
{
	va_list ap;
	va_start(ap, lpszError);

	m_cs.Enter();

	char szMessage[1024] = {};
	char szError[1024] = {};

	this->CReporter::GetTime();

	_vsnprintf(szMessage, sizeof(szMessage), lpszError, ap);

	if( lpszError[strlen(lpszError)-1] == '\n' )
		sprintf(szError, "%s - %s", m_szTime, szMessage);
	else
		sprintf(szError, "%s - %s\n", m_szTime, szMessage);

	this->CReporter::OpenLogFile("log.txt");

	if( m_fp != NULL )
	{
		fputs(szError, m_fp);
		this->CReporter::CloseLogFile();
	}

	m_cs.Leave();
}


void CReporter::MessagePrint(const char* lpszMsg, ...)
{
	va_list ap;
	va_start(ap, lpszMsg);

	m_cs.Enter();

	char szMessage[2048] = {};

	this->CReporter::GetTime();

	_vsnprintf(szMessage, sizeof(szMessage), lpszMsg, ap);

	if( szMessage[strlen(szMessage)-1] != '\n' )
		szMessage[strlen(szMessage)] = '\n';

	printf("%s  ", m_szTime);
	printf("Message: ");
	printf(szMessage); //FIXME: uncontrolled format string vulnerability

	m_cs.Leave();
}


void CReporter::FatalError(const char* lpszError, ...)
{
	va_list ap;
	va_start(ap, lpszError);

	this->CReporter::GetTime();

	char szMessage[1024] = {};
	_vsnprintf(szMessage, sizeof(szMessage), lpszError, ap);

	char szError[1024] = {};
	if( lpszError[strlen(lpszError)-1] == '\n' )
		sprintf(szError, "%s - %s", m_szTime, szMessage);
	else
		sprintf(szError, "%s - %s\n", m_szTime, szMessage);

	char szTitle[1024] = {};
	sprintf(szTitle, "FatalError() - %s", m_szTime);

	this->CReporter::OpenLogFile("FatalError.txt");

	if( m_fp != NULL )
	{
		fputs(szError, m_fp);
		this->CReporter::CloseLogFile();
	}

	MessageBoxA(NULL, szError, szTitle, MB_OK);
	ExitProcess(EXIT_SUCCESS);
}


void CReporter::GetTime()
{
	memset(m_szTime, 0, sizeof(m_szTime));

	time_t ltime;
	time(&ltime);

	strftime(m_szTime, sizeof(m_szTime), "%H:%M:%S", localtime(&ltime));
	strftime(m_szDate, sizeof(m_szDate), "%Y:%m:%d", localtime(&ltime));
}


void CReporter::OpenLogFile(const char* file)
{
	char szFileName[256] = {};
	char szTime[64] = {};

	time_t ltime;
	time(&ltime);
	strftime(szTime, sizeof(szTime), "%Y%m%d", localtime(&ltime));

	SetCurrentDirectoryA("Log");
	CreateDirectoryA(szTime, NULL);
	SetCurrentDirectoryA(szTime);

	if( m_fp != NULL )
	{
		fflush(m_fp);
		fclose(m_fp);
		m_fp = NULL;
	}

	for( int i = 0; i <= 9999; ++i )
	{
		sprintf(szFileName, "%.4d_%s", i, file);

		m_fp = fopen(szFileName, "r");
		if( m_fp == NULL )
		{
			m_fp = fopen(szFileName, "a");
			return;
		}

		if( _filelength(_fileno(m_fp)) < 1024*1024 )
		{
			fclose(m_fp);
			m_fp = fopen(szFileName, "a");
			return;
		}

		fclose(m_fp);
	}
}


void CReporter::CloseLogFile()
{
	if( m_fp != NULL )
	{
		fflush(m_fp);
		fclose(m_fp);
		m_fp = NULL;

		SetCurrentDirectoryA(m_szPath);
	}
}
