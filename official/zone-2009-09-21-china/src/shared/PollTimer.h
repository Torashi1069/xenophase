#pragma once


class CPollTimer
{
private:
	/* this+0 */ DWORD m_tick;
	/* this+4 */ DWORD m_period;

public:
	void Init(DWORD tick, DWORD period)
	{
		m_tick = tick + period;
		m_period = period;
	}

	void Reset(DWORD cur, DWORD period)
	{
		m_tick = cur + period;

		if( period != 0 )
			m_period = period;
	}

	bool CheckTimeout(DWORD cur)
	{
		if( cur <= m_tick )
			return false;

		m_tick = cur + m_period;
		return true;
	}
};
