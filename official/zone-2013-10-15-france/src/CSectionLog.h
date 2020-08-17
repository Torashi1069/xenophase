#pragma once


class CSectionLog
{
protected:
	CSectionLog();
	virtual ~CSectionLog();

private:
	/* this+ 0 */ //const CSectionLog::`vftable';
	/* this+ 4 */ RTL_CRITICAL_SECTION m_csCriticalError;
protected:
	/* this+28 */ std::string m_fileName;

protected:
	void Init(const char* fileName);

public:
	virtual void Log(const char* in_pFileName, const int in_Line, const char* in_pFmt, ...);
};


class CGameGuardLog : public CSectionLog
{
private:
	CGameGuardLog();
	virtual ~CGameGuardLog();

private:
	/* static */ static CGameGuardLog*& m_isSelf; //TODO
	/* this+0 */ //CSectionLog baseclass_0 (size=56)

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CGameGuardLog* GetObj(); /// @custom
};


class CNpcEventLog : public CSectionLog
{
private:
	CNpcEventLog();
	virtual ~CNpcEventLog();

private:
	/* static */ static CNpcEventLog*& m_isSelf; //TODO
	/* this+0 */ //CSectionLog baseclass_0 (size=56)

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CNpcEventLog* GetObj(); /// @custom
};
