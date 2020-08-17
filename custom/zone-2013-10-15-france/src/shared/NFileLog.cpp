#include "shared/NFileLog.h"
#include "shared/NSystem/NSyncObject.h"


NFileLog::NFileLog(const char* in_szpLogDir, const char* in_szpLogName, const bool in_bOutput)
: m_bOutput(in_bOutput)
{
	m_SequenceFileCnt = 0;
	m_BytesOfWritten = 0;
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	memset(m_szLogFilePrefix, '\0', sizeof(m_szLogFilePrefix));

	if( this->NFileLog::Create(in_szpLogDir, in_szpLogName) )
		m_bOK = true;
}


NFileLog::~NFileLog()
{
	DeleteCriticalSection(&m_CS);
}


bool NFileLog::isOK() const
{
	return m_bOK;
}


void NFileLog::MakeCurLogFileName(char* szBuf, const int nBufLen, const unsigned int nSequenceNum) const
{
	if( nSequenceNum != 0 )
		_snprintf_s(szBuf, nBufLen, _TRUNCATE, "%s-%04d.txt", m_szLogFilePrefix, nSequenceNum);
	else
		_snprintf_s(szBuf, nBufLen, _TRUNCATE, "%s.txt", m_szLogFilePrefix);
}


unsigned int NFileLog::GetLastSqeucenCnt()
{
	unsigned int nPrev = -1; // number of the last file that was successfully accessed
	unsigned int nCur = 0;

	// scan for existing files
	while( 1 )
	{
		char TestName[MAX_LOGPATH] = {};
		this->NFileLog::MakeCurLogFileName(TestName, countof(TestName), nCur);

		if( access(TestName, 0) != 0 )
			break;

		nPrev = nCur;
		++nCur;
	}

	if( nPrev < 0 )
	{// no log files.
		m_BytesOfWritten = 0;
		return nCur;
	}

	char FileName[MAX_LOGPATH] = {};
	this->NFileLog::MakeCurLogFileName(FileName, countof(FileName), nPrev);

	FILE* stream = NULL;
	if( fopen_s(&stream, FileName, "r") != 0 || stream == NULL )
	{
		m_BytesOfWritten = 0;
		return nCur;
	}

	// get the size of last existing file
	fseek(stream, 0, SEEK_END);
	int nLastLogSize = ftell(stream);
	m_BytesOfWritten = nLastLogSize;

	fclose(stream);

	if( m_BytesOfWritten >= MAX_BYTESOFWRITTEN )
	{// too big, rotate log file.
		m_BytesOfWritten = 0;
		return nCur;
	}

	// keep writing into the existing file.
	return nPrev;
}


bool NFileLog::Create(const char* in_szpLogDir, const char* in_szpLogName)
{
	char CurrentDirectory[MAX_LOGPATH] = {};
	GetCurrentDirectoryA(countof(CurrentDirectory), CurrentDirectory);
	_snprintf_s(m_szLogDir, countof(m_szLogDir), _TRUNCATE, "%s\\%s", CurrentDirectory, in_szpLogDir);

	CreateDirectoryA(m_szLogDir, NULL);

	SYSTEMTIME st;
	GetLocalTime(&st);
	_snprintf_s(m_szLogFilePrefix, countof(m_szLogFilePrefix), _TRUNCATE, "%s\\%s(%04d%02d%02d)", m_szLogDir, in_szpLogName, st.wYear, st.wMonth, st.wDay);

	this->NFileLog::DeleteLogFile(m_szLogDir, in_szpLogName, 90);

	m_SequenceFileCnt = this->NFileLog::GetLastSqeucenCnt();
	return ( m_SequenceFileCnt <= 9999 );
}


void NFileLog::DeleteLogFile(const char* in_logdir, const char* in_szpLogName, const int in_daycnt)
{
	if( in_daycnt > 365 )
		return;

	time_t timer = time(NULL) - 86400 * in_daycnt;
	tm t = *localtime(&timer);

	char deldatetoken[MAX_PATH] = {};
	_snprintf_s(deldatetoken, countof(deldatetoken), _TRUNCATE, "%s(%04d%02d%2d)", in_szpLogName, 1900 + t.tm_year, t.tm_mon, t.tm_mday);

	char deldir[MAX_LOGPATH] = {};
	_snprintf_s(deldir, countof(deldir), _TRUNCATE, "%s\\%s*.*", in_logdir, in_szpLogName);

	WIN32_FIND_DATAA FindFileData = {};
	HANDLE hFind = FindFirstFileA(deldir, &FindFileData);
	if( hFind != INVALID_HANDLE_VALUE )
	{
		do
		{
			if( strncmp(FindFileData.cFileName, deldatetoken, strlen(deldatetoken)) < 0 )
			{
				char delfilefullpath[MAX_PATH] = {};
				_snprintf_s(delfilefullpath, countof(delfilefullpath), _TRUNCATE, "%s\\%s", in_logdir, FindFileData.cFileName);
				_unlink(delfilefullpath);
			}
		}
		while( FindNextFileA(hFind, &FindFileData) );

		FindClose(hFind);
	}
}


void NFileLog::SetOutput(const bool in_bOutput)
{
	if( this == NULL )
		return;

	m_bOutput = in_bOutput;
}


bool NFileLog::GetOutput() const
{
	if( this == NULL )
		return false;

	return m_bOutput;
}


void NFileLog::WriteFmt(const char* in_szpSourceFileName, const int in_SourceLineNum, const char* in_pFmt, ...)
{
	if( this == NULL )
		return;

	if( !m_bOutput )
		return;

	va_list va;
	va_start(va, in_pFmt);

	char buffer[2048] = {};
	_vsnprintf_s(buffer, countof(buffer), _TRUNCATE, in_pFmt, va);

	const char* pSourceFileName = in_szpSourceFileName;
	if( strrchr(in_szpSourceFileName, '\\') != NULL )
		pSourceFileName = strrchr(in_szpSourceFileName, '\\') + 1;

	char szLogFileName[MAX_LOGPATH];
	this->NFileLog::MakeCurLogFileName(szLogFileName, countof(szLogFileName), m_SequenceFileCnt);

	NSyncObject sync(m_CS);

	FILE* fp = NULL;
	if( fopen_s(&fp, szLogFileName, "a") != 0 || fp == NULL )
	{
		CreateDirectoryA(m_szLogDir, NULL);
		return;
	}

	char sourcebuffer[MAX_PATH] = {};
	_snprintf_s(sourcebuffer, countof(sourcebuffer), _TRUNCATE, "%s(%d)", pSourceFileName, in_SourceLineNum);

	SYSTEMTIME st;
	GetLocalTime(&st);

	m_BytesOfWritten += fprintf(fp, "%-30s [%02d-%02d-%02d %02d:%02d:%02d.%03d] %s\n", sourcebuffer, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, buffer);

	if( m_BytesOfWritten > MAX_BYTESOFWRITTEN )
	{
		++m_SequenceFileCnt;
		m_BytesOfWritten = 0;
	}

	fclose(fp);
	fp = NULL;
}
