#include "Common/NFileLog.h"
#include "Common/NSyncObject.h"


NFileLog::NFileLog(const char* in_szLogDir, const char* in_szLogName, const bool in_bOutput)
{
	m_SequenceFileCnt = 0;
	m_BytesOfWritten = 0;
	m_bOK = false;
	m_bOutput = in_bOutput;
	InitializeCriticalSection(&m_CS);
	memset(m_szLogFilePrefix, '\0', sizeof(m_szLogFilePrefix));

	if( this->NFileLog::Create(in_szLogDir, in_szLogName) )
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


void NFileLog::SetOutput(const bool bOutput)
{
	m_bOutput = bOutput;
}


bool NFileLog::GetOutput() const
{
	return m_bOutput;
}


bool NFileLog::Create(const char* in_szpLogDir, const char* in_szpLogName)
{
	char CurrentDirectory[MAX_LOGPATH] = {};
	GetCurrentDirectoryA(sizeof(CurrentDirectory), CurrentDirectory);
	_snprintf_s(m_szLogDir, sizeof(m_szLogDir), _TRUNCATE, "%s\\%s", CurrentDirectory, in_szpLogDir);

	CreateDirectoryA(m_szLogDir, NULL);

	SYSTEMTIME st;
	GetLocalTime(&st);
	_snprintf_s(m_szLogFilePrefix, sizeof(m_szLogFilePrefix), _TRUNCATE, "%s\\%s(%04d%02d%02d)", m_szLogDir, in_szpLogName, st.wYear, st.wMonth, st.wDay);

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
	_snprintf_s(deldatetoken, sizeof(deldatetoken), _TRUNCATE, "%s(%04d%02d%2d)", in_szpLogName, 1900 + t.tm_year, t.tm_mon, t.tm_mday);

	char deldir[MAX_LOGPATH] = {};
	_snprintf_s(deldir, sizeof(deldir), _TRUNCATE, "%s\\%s*.*", in_logdir, in_szpLogName);

	WIN32_FIND_DATAA FindFileData = {};
	HANDLE hFind = FindFirstFileA(deldir, &FindFileData);
	if( hFind != INVALID_HANDLE_VALUE )
	{
		do
		{
			if( strncmp(FindFileData.cFileName, deldatetoken, strlen(deldatetoken)) < 0 )
			{
				char delfilefullpath[MAX_PATH] = {};
				_snprintf_s(delfilefullpath, sizeof(delfilefullpath), _TRUNCATE, "%s\\%s", in_logdir, FindFileData.cFileName);
				_unlink(delfilefullpath);
			}
		}
		while( FindNextFileA(hFind, &FindFileData) );

		FindClose(hFind);
	}
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
		this->NFileLog::MakeCurLogFileName(TestName, sizeof(TestName), nCur);

		if( _access(TestName, 0) != 0 )
			break;

		nPrev = nCur;
		++nCur;
	}

	if( nPrev < 0 )
	{// no log files.
		m_BytesOfWritten = 0;
		return nCur;
	}

	// get the size of last existing file
	///
	char FileName[MAX_LOGPATH] = {};
	this->NFileLog::MakeCurLogFileName(FileName, sizeof(FileName), nPrev);

	FILE* stream = NULL;
	if( fopen_s(&stream, FileName, "r") != 0 || stream == NULL )
	{
		m_BytesOfWritten = 0;
		return nCur;
	}

	fseek(stream, 0, SEEK_END);
	int nLastLogSize = ftell(stream);
	m_BytesOfWritten = nLastLogSize;
	fclose(stream);
	///

	if( m_BytesOfWritten >= MAX_BYTESOFWRITTEN )
	{// too big, rotate log file.
		m_BytesOfWritten = 0;
		return nCur;
	}

	// keep writing into the existing file.
	return nPrev;
}


void NFileLog::WriteFmt(const char* in_szpSourceFileName, const int in_SourceLineNum, const char* in_pFmt, ...)
{
	if( this == NULL || !m_bOutput )
		return;

	va_list va;
	va_start(va, in_pFmt);

	char buffer[2048] = {};
	_vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, in_pFmt, va);

	const char* pSourceFileName = in_szpSourceFileName;
	if( strrchr(in_szpSourceFileName, '\\') != NULL )
		pSourceFileName = strrchr(in_szpSourceFileName, '\\') + 1;

	char szLogFileName[MAX_LOGPATH];
	this->NFileLog::MakeCurLogFileName(szLogFileName, sizeof(szLogFileName), m_SequenceFileCnt);

	NSyncObject sync(m_CS);

	FILE* stream = NULL;
	if( fopen_s(&stream, szLogFileName, "a") != 0 || stream == NULL )
	{
		CreateDirectoryA(m_szLogDir, NULL);
		return;
	}

	char sourcebuffer[260] = {};
	_snprintf_s(sourcebuffer, sizeof(sourcebuffer), _TRUNCATE, "%s(%d)", pSourceFileName, in_SourceLineNum);

	SYSTEMTIME st;
	GetLocalTime(&st);

	m_BytesOfWritten += fprintf(stream, "%-33s [%02d-%02d-%02d %02d:%02d:%02d.%03d] %s\n", sourcebuffer, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, buffer);

	if( m_BytesOfWritten > MAX_BYTESOFWRITTEN )
	{
		++m_SequenceFileCnt;
		m_BytesOfWritten = 0;
	}

	fclose(stream);
	stream = NULL;
}
