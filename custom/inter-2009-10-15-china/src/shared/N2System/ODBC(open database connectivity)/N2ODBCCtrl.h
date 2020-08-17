#pragma once
#include <sql.h>


class N2ODBCCtrl
{
	/* this+ 0 */ public: //const N2ODBCCtrl::`vftable';
	/* this+ 4 */ private: bool m_bOK;
	/* this+ 8 */ private: SQLHENV m_hEnv;
	/* this+12 */ private: SQLHDBC m_hDbc;
	/* this+16 */ private: bool m_bConnect;

	public: N2ODBCCtrl::N2ODBCCtrl(void);
	public: virtual N2ODBCCtrl::~N2ODBCCtrl(void);
	public: bool N2ODBCCtrl::isOK(void) const;
	private: bool N2ODBCCtrl::Init(void);
	public: bool N2ODBCCtrl::Connect(const mystd::string in_strConnectionStr);
	public: void N2ODBCCtrl::Disconnect(void);
	public: operator N2ODBCCtrl::SQLHDBC(void); // line 27
	public: const bool N2ODBCCtrl::isConnect(void) const; // line 28
	public: void N2ODBCCtrl::OutputErrorString(const short in_Type, const SQLHANDLE in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage);

private:
	static hook_method<bool (N2ODBCCtrl::*)(void)> N2ODBCCtrl::_Init;
	static hook_method<bool (N2ODBCCtrl::*)(void) const> N2ODBCCtrl::_isOK;
	static hook_method<bool (N2ODBCCtrl::*)(const mystd::string in_strConnectionStr)> N2ODBCCtrl::_Connect;
	static hook_method<void (N2ODBCCtrl::*)(void)> N2ODBCCtrl::_Disconnect;
	static hook_method<SQLHDBC (N2ODBCCtrl::*)(void)> N2ODBCCtrl::_operator_SQLHDBC;
	static hook_method<const bool (N2ODBCCtrl::*)(void) const> N2ODBCCtrl::_isConnect;
	static hook_method<void (N2ODBCCtrl::*)(const short in_Type, const SQLHANDLE in_Handle, const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)> N2ODBCCtrl::_OutputErrorString;
};
