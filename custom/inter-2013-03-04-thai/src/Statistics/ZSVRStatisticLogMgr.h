#pragma once


class CZSVRStatisticLogMgr
{
private:
	/* static */ static CZSVRStatisticLogMgr*& m_cpSelf; //TODO
	/* this+0 */ //const CZSVRStatisticLogMgr::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+5 */ bool m_bOutputLog;

public:
	bool isOK() const;
	void Add(const time_t in_Date, const int in_ZSID, const int in_PlayerNum, const int in_NPCNum, const int in_MemoryKBytes, const int in_TotalServiceMapNum, const int in_ServiceInstantMapNum);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CZSVRStatisticLogMgr* GetObj(); /// @custom

private:
	CZSVRStatisticLogMgr();
	virtual ~CZSVRStatisticLogMgr();
};
