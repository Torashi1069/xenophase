#pragma once


class CDateTime
{
public:
	void AddTime(int Day, int Hour, int Min);
	BOOL CheckTimeOut();
	BOOL CheckTimeOut(time_t NowTime);
	void GetNowTime();
	void SetTime(short nYear, short nMonth, short nDay, short nHour);
	void GetTime(short& Year, short& Month, short& Day, short& Hour);
	time_t GetTime_t();
	operator TIMESTAMP_STRUCT();
	operator time_t();
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMin() const;
	int GetSec() const;

private:
	/* this+0 */ time_t m_time;

public:
	CDateTime(const time_t in_time);
	CDateTime();
	CDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST);
	~CDateTime();
};
