#pragma once
#include <sql.h>


class NODBCCtrl
{
	/* this+0x0 */ //const NODBCCtrl::`vftable'
	/* this+0x4 */ private: bool m_bOK;
	/* this+0x8 */ private: SQLHENV m_hEnv;
	/* this+0xC */ private: SQLHDBC m_hDbc;

	private: bool NODBCCtrl::Init(void);
	//public: bool NODBCCtrl::isOK();
	//public: bool NODBCCtrl::Connect(const mystd::string);
	//public: void NODBCCtrl::Disconnect();
	public: operator NODBCCtrl::SQLHDBC(void);
	//public: void NODBCCtrl::OutputErrorString(const short, void * const, const char *, const int, const char *);
	public: NODBCCtrl::NODBCCtrl(void);
	public: virtual NODBCCtrl::~NODBCCtrl(void);

private:
	static hook_method<bool (NODBCCtrl::*)(void)> NODBCCtrl::_Init;
	static hook_method<SQLHDBC (NODBCCtrl::*)(void)> NODBCCtrl::_operator_SQLHDBC;
};
