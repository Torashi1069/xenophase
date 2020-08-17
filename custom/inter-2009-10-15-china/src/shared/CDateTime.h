#pragma once


class CDateTime
{
	/* this+0x0 */ private: time_t m_time;

	public: void CDateTime::AddTime(int Day, int Hour, int Min);
	//public: int CDateTime::CheckTimeOut(long);
	//public: int CDateTime::CheckTimeOut(void);
	//public: void CDateTime::GetNowTime(void);
	//public: void CDateTime::SetTime(short, short, short, short);
	//public: void CDateTime::GetTime(short &, short &, short &, short &);
	//public: time_t CDateTime::GetTime_t(void);
	//public: struct tagTIMESTAMP_STRUCT operator struct tagTIMESTAMP_STRUCT(void);
	public: operator CDateTime::time_t(void);
	//public: int CDateTime::GetYear(void);
	//public: int CDateTime::GetMonth(void);
	//public: int CDateTime::GetDay(void);
	//public: int CDateTime::GetHour(void);
	//public: int CDateTime::GetMin(void);
	//public: int CDateTime::GetSec(void);
	public: CDateTime::CDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST);
	public: CDateTime::CDateTime(void);
	public: CDateTime::CDateTime(const time_t in_time);
	public: CDateTime::~CDateTime(void);

private:
	static hook_method<void (CDateTime::*)(int Day, int Hour, int Min)> CDateTime::_AddTime;
	static hook_method<time_t (CDateTime::*)(void)> CDateTime::_operator_time_t;
};
