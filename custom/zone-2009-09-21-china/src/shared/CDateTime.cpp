#include "CDateTime.h"


CDateTime::CDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST)
{
	tm atm;
	atm.tm_min = nMin;
	atm.tm_sec = nSec;
	atm.tm_hour = nHour;
	atm.tm_mon = nMonth - 1;
	atm.tm_mday = nDay;
	atm.tm_year = nYear - 1900;
	atm.tm_isdst = nDST;

	m_time = _mktime32(&atm);
}


CDateTime::CDateTime(const long in_time)
{
	m_time = in_time;
}


CDateTime::CDateTime(void)
{
}


CDateTime::~CDateTime(void)
{
}


hook_method<void (CDateTime::*)(int Day, int Hour, int Min)> CDateTime::_AddTime(SERVER, "CDateTime::AddTime");
void CDateTime::AddTime(int Day, int Hour, int Min)
{
	return (this->*_AddTime)(Day, Hour, Min);

	//TODO
}


hook_method<int (CDateTime::*)(long NowTime)> CDateTime::_CheckTimeOut(SERVER, "?CheckTimeOut@CDateTime@@QAEHJ@Z");
int CDateTime::CheckTimeOut(long NowTime)
{
	return (this->*_CheckTimeOut)(NowTime);

	//TODO
}	


/* hook_method<int (CDateTime::*)(void)> CDateTime::_CheckTimeOut2(SERVER, "?CheckTimeOut@CDateTime@@QAEHXZ");
int CDateTime::CheckTimeOut(void)
{
	return (this->*_CheckTimeOut2)();

	//TODO
} */


hook_method<void (CDateTime::*)(void)> CDateTime::_GetNowTime(SERVER, "CDateTime::GetNowTime");
void CDateTime::GetNowTime(void)
{
	return (this->*_GetNowTime)();

	//TODO
}


hook_method<void (CDateTime::*)(short nYear, short nMonth, short nDay, short nHour)> CDateTime::_SetTime(SERVER, "CDateTime::SetTime");
void CDateTime::SetTime(short nYear, short nMonth, short nDay, short nHour)
{
	return (this->*_SetTime)(nYear, nMonth, nDay, nHour);

	//TODO
}


hook_method<void (CDateTime::*)(short& Year, short& Month, short& Day, short& Hour)> CDateTime::_GetTime(SERVER, "CDateTime::GetTime");
void CDateTime::GetTime(short& Year, short& Month, short& Day, short& Hour)
{
	return (this->*_GetTime)(Year, Month, Day, Hour);

	//TODO
}


//hook_method<long (CDateTime::*)(void)> CDateTime::_GetTime_t(SERVER, "CDateTime::GetTime_t");
long CDateTime::GetTime_t(void)
{
//	return (this->*_GetTime_t)();

	return m_time;
}


//hook_method<int (CDateTime::*)(void)> CDateTime::_GetYear(SERVER, "CDateTime::GetYear");
int CDateTime::GetYear(void)
{
//	return (this->*_GetYear)();

	return _localtime32(&m_time)->tm_year + 1900;
}


//hook_method<int (CDateTime::*)(void)> CDateTime::_GetMonth(SERVER, "CDateTime::GetMonth");
int CDateTime::GetMonth(void)
{
//	return (this->*_GetMonth)();

	return _localtime32(&m_time)->tm_mon + 1;
}


//hook_method<int (CDateTime::*)(void)> CDateTime::_GetDay(SERVER, "CDateTime::GetDay");
int CDateTime::GetDay(void)
{
//	return (this->*_GetDay)();

	return _localtime32(&m_time)->tm_mon + 1;
}


//hook_method<int (CDateTime::*)(void)> CDateTime::_GetHour(SERVER, "CDateTime::GetHour");
int CDateTime::GetHour(void)
{
//	return (this->*_GetHour)();

	return _localtime32(&m_time)->tm_hour;
}


//hook_method<int (CDateTime::*)(void)> CDateTime::_GetMin(SERVER, "CDateTime::GetMin");
int CDateTime::GetMin(void)
{
//	return (this->*_GetMin)();

	return _localtime32(&m_time)->tm_min;
}


//hook_method<int (CDateTime::*)(void)> CDateTime::_GetSec(SERVER, "CDateTime::GetSec");
int CDateTime::GetSec(void)
{
//	return (this->*_GetSec)();

	return _localtime32(&m_time)->tm_sec;
}
