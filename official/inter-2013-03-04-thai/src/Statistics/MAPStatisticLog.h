#pragma once
#include "shared/N2System/DBLog/N2DBLog.h"


class CMAPStatisticLog : public N2DBLog
{
public:
	typedef std::map<std::string,int> MAPINFO_CONTAINER;
	typedef std::map<std::string,int>::iterator MAPINFO_CONTAINER_ITER;

public:
	/* this+ 0 */ //N2DBLog baseclass_0;
	/* this+ 8 */ time_t m_Date;
private:
	/* this+12 */ const int m_ZSID;
	/* this+16 */ MAPINFO_CONTAINER m_MapInfoContainer;

private:
	virtual bool Run(N2ODBCCtrl& in_ODBCCtrl);

public:
	CMAPStatisticLog(const time_t in_Date, const int in_ZSID, const MAPINFO_CONTAINER& in_MapInfoContainer);
	virtual ~CMAPStatisticLog();
};
