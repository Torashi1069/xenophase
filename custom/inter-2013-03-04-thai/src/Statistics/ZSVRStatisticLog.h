#pragma once
#include "shared/N2System/DBLog/N2DBLog.h"


class CZSVRStatisticLog : public N2DBLog
{
private:
	/* this+ 0 */ //N2DBLog baseclass_0;
	/* this+ 8 */ const time_t m_Date;
	/* this+12 */ const int m_ZSID;
	/* this+16 */ const int m_PlayerNum;
	/* this+20 */ const int m_NPCNum;
	/* this+24 */ const int m_MemoryKBytes;
	/* this+28 */ const int m_TotalServiceMapNum;
	/* this+32 */ const int m_ServiceInstantMapNum;

private:
	virtual bool Run(N2ODBCCtrl& in_ODBCCtrl);

public:
	CZSVRStatisticLog(const time_t in_Date, const int in_ZSID, const int in_PlayerNum, const int in_NPCNum, const int in_MemoryKBytes, const int in_TotalServiceMapNum, const int in_ServiceInstantMapNum);
	virtual ~CZSVRStatisticLog();
};
