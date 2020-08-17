#include "CDateTime.h"


CDateTime::CDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST) // line 31
{
	tm atm;
	atm.tm_min = nMin;
	atm.tm_sec = nSec;
	atm.tm_hour = nHour;
	atm.tm_mon = nMonth - 1;
	atm.tm_mday = nDay;
	atm.tm_year = nYear - 1900;
	atm.tm_isdst = nDST;

	m_time = mktime(&atm);
}


CDateTime::CDateTime(void) // line 21
{
}


CDateTime::CDateTime(const time_t in_time) // line 16
{
	m_time = in_time;
}


CDateTime::~CDateTime(void) // line 28
{
}


hook_method<void (CDateTime::*)(int Day, int Hour, int Min)> CDateTime::_AddTime(SERVER, "CDateTime::AddTime");
void CDateTime::AddTime(int Day, int Hour, int Min) // line 116
{
	return (this->*_AddTime)(Day, Hour, Min);

	//TODO
}


hook_method<time_t (CDateTime::*)(void)> CDateTime::_operator_time_t(SERVER, "??BCDateTime@@QAEJXZ");
CDateTime::operator time_t(void) // line 28 (CDateTime.h)
{
	return (this->*_operator_time_t)();

	return m_time;
}
