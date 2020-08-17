#pragma once


class CMAPStatisticLogMgr
{
private:
	/* static */ static CMAPStatisticLogMgr*& m_cpSelf; //TODO
	/* this+0 */ //const CMAPStatisticLogMgr::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+5 */ bool m_bOutputLog;

public:
	bool isOK() const;
	void Add(const time_t in_Date, const int in_ZSID, const std::map<std::string,int>& in_MapInfoContainer);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMAPStatisticLogMgr* GetObj(); /// @custom

private:
	CMAPStatisticLogMgr();
	virtual ~CMAPStatisticLogMgr();
};
