#pragma once
#include <sql.h>


class CODBCV2Util
{
	/* this+0x0 */ //const CODBCV2Util::`vftable'
	/* static   */ private: static hook_ptr<CODBCV2Util*> m_cpSelf;

	public: static CODBCV2Util* __cdecl CODBCV2Util::GetObj(void);
	public: mystd::string CODBCV2Util::GetErrorString(const short in_HandleType, SQLHANDLE const in_Handle);
	public: bool CODBCV2Util::AddSystemDSN(const mystd::string in_strDSN, const mystd::string in_ServerIP, const mystd::string in_strDBName);
	private: CODBCV2Util::CODBCV2Util(void);
	private: virtual CODBCV2Util::~CODBCV2Util(void);

private:
	static hook_method<static CODBCV2Util* (__cdecl *)(void)> CODBCV2Util::_GetObj;
	static hook_method<mystd::string (CODBCV2Util::*)(const short in_HandleType, SQLHANDLE const in_Handle)> CODBCV2Util::_GetErrorString;
	static hook_method<bool (CODBCV2Util::*)(const mystd::string in_strDSN, const mystd::string in_ServerIP, const mystd::string in_strDBName)> CODBCV2Util::_AddSystemDSN;
};
