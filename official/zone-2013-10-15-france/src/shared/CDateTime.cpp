#include "shared/CDateTime.h"


CDateTime::CDateTime(const time_t in_time)
{
	m_time = in_time;
}


CDateTime::CDateTime()
{
}


CDateTime::~CDateTime()
{
}


CDateTime::CDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST)
{
	tm atm;
	atm.tm_sec   = nSec;
	atm.tm_min   = nMin;
	atm.tm_hour  = nHour;
	atm.tm_mday  = nDay;
	atm.tm_mon   = nMonth - 1;
	atm.tm_year  = nYear - 1900;
	atm.tm_isdst = nDST;

	m_time = mktime(&atm);
}


time_t CDateTime::GetTime_t()
{
	return m_time;
}


CDateTime::operator time_t()
{
	return m_time;
}


void CDateTime::GetNowTime()
{
	time_t the_time;
	m_time = time(&the_time);
}


void CDateTime::SetTime(short nYear, short nMonth, short nDay, short nHour)
{
	tm atm;
	atm.tm_sec  = 0;
	atm.tm_min  = 0;
	atm.tm_hour = nHour;
	atm.tm_mday = nDay;
	atm.tm_mon  = nMonth - 1;
	atm.tm_year = nYear - 1900;

	m_time = mktime(&atm);
}


int CDateTime::GetYear() const
{
	return localtime(&m_time)->tm_year + 1900;
}


int CDateTime::GetMonth() const
{
	return localtime(&m_time)->tm_mon + 1;
}


int CDateTime::GetDay() const
{
	return localtime(&m_time)->tm_mday;
}


int CDateTime::GetHour() const
{
	return localtime(&m_time)->tm_hour;
}


int CDateTime::GetMin() const
{
	return localtime(&m_time)->tm_min;
}


int CDateTime::GetSec() const
{
	return localtime(&m_time)->tm_sec;
}


void CDateTime::GetTime(short& Year, short& Month, short& Day, short& Hour)
{
	tm* t = localtime(&m_time);
	Year  = short(t->tm_year) + 1900;
	Month = short(t->tm_mon) + 1;
	Day   = short(t->tm_mday);
	Hour  = short(t->tm_hour);
}


void CDateTime::AddTime(int Day, int Hour, int Min)
{
	tm* t = localtime(&m_time);
	t->tm_mday += Day;
	t->tm_hour += Hour;
	t->tm_min  += Min;

	m_time = mktime(t);
}


BOOL CDateTime::CheckTimeOut()
{
	time_t Now_time;
	_time32(&Now_time);
	return ( difftime(m_time, Now_time) < 0 );
}


BOOL CDateTime::CheckTimeOut(time_t NowTime)
{
	return ( difftime(m_time, NowTime) < 0 );
}


CDateTime::operator TIMESTAMP_STRUCT()
{
	if( m_time < 0 )
		m_time = 0;

	tm time;
	memcpy(&time, localtime(&m_time), sizeof(time));

	TIMESTAMP_STRUCT result = {};
	result.year     = SQLSMALLINT(time.tm_year) + 1900;
	result.month    = SQLUSMALLINT(time.tm_mon) + 1;
	result.day      = SQLUSMALLINT(time.tm_mday);
	result.hour     = SQLUSMALLINT(time.tm_hour);
	result.minute   = SQLUSMALLINT(time.tm_min);
	result.second   = SQLUSMALLINT(time.tm_sec);
	result.fraction = 0;

	return result;
}
