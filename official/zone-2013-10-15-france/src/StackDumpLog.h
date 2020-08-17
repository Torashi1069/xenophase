#pragma once


class CStackDumpLog
{
private:
	/* this+0 */ //const CStackDumpLog::`vftable';
	/* this+4 */ bool m_bSymbolReady;
	/* this+8 */ RTL_CRITICAL_SECTION m_CS;

private:
	void WriteStack(FILE* in_fp) const;

public:
	void WriteFmt(const char* in_szpSourceFileName, const int in_Line, const char* in_pFmt, ...);
	void Write(const char* in_szpSourceFileName, const int in_Line, const char* in_pMsg);

public:
	CStackDumpLog();
	virtual ~CStackDumpLog();
};
