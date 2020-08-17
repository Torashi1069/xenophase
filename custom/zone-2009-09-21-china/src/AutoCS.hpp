//e:\해외빌드\2009-09-21\ragnarokserver\zoneprocess\svrio.h
#pragma once


class AutoCS
{
	/* this+0 */ public: //const AutoCS::`vftable';
	/* this+4 */ private: RTL_CRITICAL_SECTION* m_cs;

	public: AutoCS::AutoCS(RTL_CRITICAL_SECTION* cs)
	{
		m_cs = cs;
		EnterCriticalSection(cs);
	}

	public: virtual AutoCS::~AutoCS(void)
	{
		LeaveCriticalSection(m_cs);
	}
};
