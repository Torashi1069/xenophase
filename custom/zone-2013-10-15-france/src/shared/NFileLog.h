#pragma once


class NFileLog
{
public:
	bool isOK() const;
	void SetOutput(const bool in_bOutput);
	bool GetOutput() const;
	void WriteFmt(const char* in_szpSourceFileName, const int in_SourceLineNum, const char* in_pFmt, ...);

private:
	bool Create(const char* in_szpLogDir, const char* in_szpLogName);
	void DeleteLogFile(const char* in_logdir, const char* in_szpLogName, const int in_daycnt);
	void MakeCurLogFileName(char* szBuf, const int nBufLen, const unsigned int nSequenceNum) const;
	unsigned int GetLastSqeucenCnt();

public:
	NFileLog(const char* in_szpLogDir, const char* in_szpLogName, const bool in_bOutput);
	NFileLog(const NFileLog&); // = delete;
	NFileLog& operator=(const NFileLog&); // = delete;
	virtual ~NFileLog();

private:
	enum { MAX_LOGPATH = 1024, MAX_BYTESOFWRITTEN = 3*1024*1024 };

private:
	/* this+   0 */ //const NFileLog::`vftable';
	/* this+   4 */ bool m_bOK;
	/* this+   5 */ bool m_bOutput;
	/* this+   8 */ RTL_CRITICAL_SECTION m_CS;
	/* this+  32 */ char m_szLogDir[MAX_LOGPATH];
	/* this+1056 */ char m_szLogFilePrefix[MAX_LOGPATH];
	/* this+2080 */ unsigned int m_SequenceFileCnt;
	/* this+2084 */ int m_BytesOfWritten;
};
