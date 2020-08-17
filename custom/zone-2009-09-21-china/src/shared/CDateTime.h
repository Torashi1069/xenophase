#pragma once


class CDateTime
{
public:
	/* this+0x0 */ private: long m_time;

	public: CDateTime::CDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST);
	public: CDateTime::CDateTime(const long in_time);
	public: CDateTime::CDateTime(void);
	public: CDateTime::~CDateTime(void);
	public: void CDateTime::AddTime(int Day, int Hour, int Min);
	public: int CDateTime::CheckTimeOut(long NowTime);
	public: int CDateTime::CheckTimeOut(void);
	public: void CDateTime::GetNowTime(void);
	public: void CDateTime::SetTime(short nYear, short nMonth, short nDay, short nHour);
	public: void CDateTime::GetTime(short& Year, short& Month, short& Day, short& Hour);
	public: long CDateTime::GetTime_t(void);
	//public: tagTIMESTAMP_STRUCT operator tagTIMESTAMP_STRUCT(void);
	//public: long operator __w64 CDateTime::long(void);
	public: int CDateTime::GetYear(void);
	public: int CDateTime::GetMonth(void);
	public: int CDateTime::GetDay(void);
	public: int CDateTime::GetHour(void);
	public: int CDateTime::GetMin(void);
	public: int CDateTime::GetSec(void);

private:
	static hook_method<void (CDateTime::*)(int Day, int Hour, int Min)> CDateTime::_AddTime;
	static hook_method<int (CDateTime::*)(long NowTime)> CDateTime::_CheckTimeOut;
	static hook_method<int (CDateTime::*)(void)> CDateTime::_CheckTimeOut2;
	static hook_method<void (CDateTime::*)(void)> CDateTime::_GetNowTime;
	static hook_method<void (CDateTime::*)(short nYear, short nMonth, short nDay, short nHour)> CDateTime::_SetTime;
	static hook_method<void (CDateTime::*)(short& Year, short& Month, short& Day, short& Hour)> CDateTime::_GetTime;
	static hook_method<long (CDateTime::*)(void)> CDateTime::_GetTime_t;
	static hook_method<int (CDateTime::*)(void)> CDateTime::_GetYear;
	static hook_method<int (CDateTime::*)(void)> CDateTime::_GetMonth;
	static hook_method<int (CDateTime::*)(void)> CDateTime::_GetDay;
	static hook_method<int (CDateTime::*)(void)> CDateTime::_GetHour;
	static hook_method<int (CDateTime::*)(void)> CDateTime::_GetMin;
	static hook_method<int (CDateTime::*)(void)> CDateTime::_GetSec;
};
