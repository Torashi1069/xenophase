#pragma once


class CProcessTimeChecker
{
	/* this+0 */ private: unsigned long m_MarkMS;
	/* this+4 */ private: unsigned long m_max;

	//public: void Start();
	//public: void End();

	public: unsigned long CProcessTimeChecker::GetMax(void)
	{
		return m_max;
	}

	//public: void CProcessTimeChecker();
};
