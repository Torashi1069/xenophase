#include "shared/N2System/DBLog/N2DBLog.h"


N2DBLog::N2DBLog()
{
	m_bOK = true;
}


N2DBLog::~N2DBLog()
{
}


bool N2DBLog::isOK() const
{
	return m_bOK;
}


bool N2DBLog::Run(N2ODBCCtrl& in_ODBCCtrl)
{
	return true;
}
