#pragma once


class CPollTimer
{
	/* this+0 */ private: DWORD m_tick;
	/* this+4 */ private: DWORD m_period;

	public: void CPollTimer::Init(DWORD tick, DWORD period)
	{
		m_tick = tick + period;
		m_period = period;
	}

	public: void CPollTimer::Reset(DWORD now, DWORD period = -1)
	{
		if( period == -1 ) // wild guess
			period = m_period;

		m_tick = now + period;
	}

	public: bool CPollTimer::CheckTimeout(DWORD now)
	{
		return ( now > m_tick );
	}
};
