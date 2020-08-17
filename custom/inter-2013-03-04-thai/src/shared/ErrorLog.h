#pragma once


class CErrorLog
{
public:
	CErrorLog();
	virtual ~CErrorLog();

public:
	void CmtLog(const unsigned long in_AID, const std::string in_CharName, const std::string in_MapName, const int in_x, const int in_y, const int in_type);
	void KillAllLog(char* buf);
	void MoveLog(char* buf);
	void MoveLogFmt(const char* in_pFmt, ...);
	void CreateLog(char* buf);
	void PacketErrorLog(char* buf, DWORD IP);

private:
	/* this+0 */ //const CErrorLog::`vftable';
	/* this+4 */ RTL_CRITICAL_SECTION m_csCriticalError;
};


extern CErrorLog& g_errorLogs;
