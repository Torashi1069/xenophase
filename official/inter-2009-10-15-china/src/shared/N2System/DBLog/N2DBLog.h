#pragma once
#include "N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"


class N2DBLog
{
	struct vtable_t
	{
		bool (N2DBLog::* Run)(N2ODBCCtrl& in_ODBCCtrl);
		void* (N2DBLog::* scalar_deleting_destructor)(unsigned int flags);
	};

	/* this+0 */ public: //const N2DBLog::`vftable';
	/* this+4 */ private: bool m_bOK;

	public: N2DBLog::N2DBLog(void);
	public: virtual N2DBLog::~N2DBLog(void);
	public: bool N2DBLog::isOK(void) const;
	private: virtual bool N2DBLog::Run(N2ODBCCtrl& in_ODBCCtrl);

private:
	static hook_method<bool (N2DBLog::*)(void) const> N2DBLog::_isOK;
	static hook_method<bool (N2DBLog::*)(N2ODBCCtrl& in_ODBCCtrl)> N2DBLog::_Run;
};
