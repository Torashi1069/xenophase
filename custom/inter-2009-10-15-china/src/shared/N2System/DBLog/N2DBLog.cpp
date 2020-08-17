#include "N2System/DBLog/N2DBLog.h"


N2DBLog::N2DBLog(void) // line 8-11
{
	m_bOK = true;
}


N2DBLog::~N2DBLog(void) // line 14-16
{
}


//hook_method<bool (N2DBLog::*)(void) const> N2DBLog::_isOK(SERVER, "N2DBLog::isOK");
bool N2DBLog::isOK(void) const // line ??
{
//	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (N2DBLog::*)(N2ODBCCtrl& in_ODBCCtrl)> N2DBLog::_Run(SERVER, "N2DBLog::Run");
bool N2DBLog::Run(N2ODBCCtrl& in_ODBCCtrl) // line 14 (shared/N2System/DBLog/N2DBLog.h)
{
	return (this->*_Run)(in_ODBCCtrl);

	return true;
}
