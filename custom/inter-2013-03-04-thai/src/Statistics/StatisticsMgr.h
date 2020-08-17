#pragma once
#include "shared/CDateTime.h"


class CStatisticsMgr
{
private:
	/* static  */ static CStatisticsMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const CStatisticsMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ CDateTime m_LogOutputEvnetDT;
	/* this+12 */ int m_ReportPerMinute;

private:
	bool Create();
	void Destroy();

public:
	bool isOK() const;
	void Process();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CStatisticsMgr* GetObj(); /// @custom

private:
	CStatisticsMgr();
	virtual ~CStatisticsMgr();
};
