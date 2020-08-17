#pragma once


class CErrorLog
{
	/* this+0x0 */ public: //const CErrorLog::`vftable';
	/* this+0x4 */ private: RTL_CRITICAL_SECTION m_csCriticalError;

	public: CErrorLog::CErrorLog(void);
	public: virtual CErrorLog::~CErrorLog(void);
	public: HOOKED void CErrorLog::CriticalErrorLogFmt(const char* in_pFileName, const int in_Line, const char* in_pFmt, ...);
	public: HOOKED void CErrorLog::CriticalErrorLog(const char* buf, const int line, const char* filename);
	public: void CErrorLog::KillAllLog(char* buf);
	public: void CErrorLog::MoveLog(char* buf);
	public: void CErrorLog::CreateLog(char* buf);
	public: void CErrorLog::PacketErrorLog(char* buf, unsigned long IP);

private:
	static hook_method<void (CErrorLog::*)(const char* in_pFileName, const int in_Line, const char* in_pFmt, ...)> CErrorLog::_CriticalErrorLogFmt;
	static hook_method<void (CErrorLog::*)(const char* buf, const int line, const char* filename)> CErrorLog::_CriticalErrorLog;
	static hook_method<void (CErrorLog::*)(char* buf)> CErrorLog::_KillAllLog;
	static hook_method<void (CErrorLog::*)(char* buf)> CErrorLog::_MoveLog;
	static hook_method<void (CErrorLog::*)(char* buf)> CErrorLog::_CreateLog;
	static hook_method<void (CErrorLog::*)(char* buf, unsigned long IP)> CErrorLog::_PacketErrorLog;
};
