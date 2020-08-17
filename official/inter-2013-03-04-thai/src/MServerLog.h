#pragma once


class CMServerLog
{
public:
	bool isOK() const;
	void LogFmt(const char* in_pFmt, ...);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMServerLog* GetObj(); /// @custom

private:
	CMServerLog();
	virtual ~CMServerLog();

private:
	/* this+ 0 */ //const CMServerLog::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_CS;
	/* static  */ static CMServerLog*& m_cpSelf; //TODO
	/* this+28 */ bool m_bOK;
	/* this+29 */ char m_LogFileName[MAX_PATH];
};
