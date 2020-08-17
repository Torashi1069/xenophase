#include "Common/EnterTraceLog.h"
#include "Common/Network.h"
#include "Common/NSyncObject.h"


/// singleton instance
CEnterTraceLog* CEnterTraceLog::m_cpSelf;


CEnterTraceLog::CEnterTraceLog()
: NFileLog("logs", "EnterTrace", true)
{
	m_bOK = false;

	if( !this->NFileLog::isOK() )
		return;

	InitializeCriticalSection(&m_cs);

	char CurrentDirectory[MAX_LOGPATH] = {};
	GetCurrentDirectoryA(sizeof(CurrentDirectory), CurrentDirectory);

	char LogPathDir[MAX_LOGPATH] = {};
	_snprintf_s(LogPathDir, sizeof(LogPathDir), _TRUNCATE, "%s\\%s\\%s", CurrentDirectory, "logs", "logfiles");

	CreateDirectoryA(LogPathDir, NULL);
	m_bOK = true;
}


CEnterTraceLog::~CEnterTraceLog()
{
	DeleteCriticalSection(&m_cs);
}


bool CEnterTraceLog::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CEnterTraceLog();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CEnterTraceLog::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


/// @custom
CEnterTraceLog* CEnterTraceLog::GetObj()
{
	return m_cpSelf;
}


bool CEnterTraceLog::isOK() const
{
	return m_bOK;
}


void CEnterTraceLog::LogFmt(const char* in_szpSourceFileName, const int in_SourceLineNum, const DWORD in_dwIP, const char* lpszMessage, ...)
{
	va_list va;
	va_start(va, lpszMessage);

	NSyncObject sync(m_cs);

	char szbuf[1024] = {};
	_vsnprintf_s(szbuf, sizeof(szbuf), _TRUNCATE, lpszMessage, va);

	char szIP[16];
	CNetwork::GetObj()->CNetwork::GetTextIP(in_dwIP, szIP);

	char szMessage[1024] = {};
	sprintf_s(szMessage, sizeof(szMessage), "[%s] %s", szIP, szbuf);

	this->NFileLog::WriteFmt(in_szpSourceFileName, in_SourceLineNum, "%s", szMessage);
}


void CEnterTraceLog::LogFile(const char* lpszFile, const char* lpszError, ...)
{
	va_list va;
	va_start(va, lpszError);

	NSyncObject sync(m_cs);

	char szMessage[1024] = {};
	_vsnprintf_s(szMessage, sizeof(szMessage), _TRUNCATE, lpszError, va);

	time_t ltime;
	time(&ltime);

	char szDate[64] = {};
	strftime(szDate, sizeof(szDate), "%Y-%m-%d(%H)", localtime(&ltime));

	char szTime[64] = {};
	strftime(szTime, sizeof(szTime), "%H:%M:%S", localtime(&ltime));

	SYSTEMTIME st;
	GetLocalTime(&st);

	char szError[1024] = {};
	size_t nErrorLen = strlen(lpszError);
	if( nErrorLen <= 0 )
		sprintf(szError, "%02d-%02d-%02d %02d:%02d:%02d.%03d  error strlenXXXX [%d]\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, nErrorLen);
	else if( lpszError[nErrorLen-1] == '\n' )
		sprintf_s(szError, sizeof(szError), "%02d-%02d-%02d %02d:%02d:%02d.%03d %s", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, szMessage);
	else
		sprintf_s(szError, sizeof(szError), "%02d-%02d-%02d %02d:%02d:%02d.%03d %s\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, szMessage);

	memset(szMessage, '\0', sizeof(szMessage));
	sprintf_s(szMessage, sizeof(szMessage), "%s\\%s\\%s_%s", "logs", "logfiles", szDate, lpszFile);

	FILE* pFile = NULL;
	fopen_s(&pFile, szMessage, "a");
	if( pFile != NULL )
	{
		fputs(szError, pFile);
		fclose(pFile);
	}
}


void CEnterTraceLog::FatalError(const char* in_szpSourceFileName, const int in_SourceLineNum, const char* lpszError, ...)
{
	va_list va;
	va_start(va, lpszError);

	NSyncObject sync(m_cs);

	time_t ltime;
	time(&ltime);

	char szTime[64] = {};
	strftime(szTime, sizeof(szTime), "%H:%M:%S", localtime(&ltime));

	char szDate[64] = {};
	strftime(szDate, sizeof(szDate), "%Y:%m:%d", localtime(&ltime));

	char szMessage[1024] = {};
	_vsnprintf_s(szMessage, sizeof(szMessage), _TRUNCATE, lpszError, va);

	char szError[1024] = {};
	if( lpszError[strlen(lpszError)-1] == '\n' )
		sprintf_s(szError, sizeof(szError), "%s - %s", szTime, szMessage);
	else
		sprintf_s(szError, sizeof(szError), "%s - %s\n", szTime, szMessage);

	char szTitle[1024] = {};
	sprintf_s(szTitle, sizeof(szTitle), "FatalError() - %s", szTime);

	this->NFileLog::WriteFmt(in_szpSourceFileName, in_SourceLineNum, "%s : %s", szTitle, szError);
	MessageBoxA(NULL, szError, szTitle, MB_OK);

	ExitProcess(EXIT_FAILURE);
}


void CEnterTraceLog::MessagePrint(const char* lpszMsg, ...)
{
	va_list va;
	va_start(va, lpszMsg);

	NSyncObject sync(m_cs);

	time_t ltime;
	time(&ltime);

	char szTime[64] = {};
	strftime(szTime, sizeof(szTime), "%H:%M:%S", localtime(&ltime));

	char szDate[64] = {};
	strftime(szDate, sizeof(szTime), "%Y:%m:%d", localtime(&ltime));

	char szMessage[2048] = {};
	_vsnprintf_s(szMessage, sizeof(szMessage), _TRUNCATE, lpszMsg, va);

	if( szMessage[strlen(szMessage)-1] != '\n' )
		szMessage[strlen(szMessage)] = '\n';

	char szBuf[2048] = {};
	_snprintf_s(szBuf, sizeof(szBuf), _TRUNCATE, "%s   Message: %s", szTime, szMessage); //NOTE: unused

	printf(szMessage); //FIXME: uncontrolled format string vulnerability
}
