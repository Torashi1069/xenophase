#pragma once
#include "std/string"
#include "ODBCV2Connector.h"
#include <sql.h>


class CODBCV2
{
public:
	/* this+0x0 */ //const CODBCV2::`vftable'
	/* this+0x4 */ private: SQLHENV m_henv;
	/* this+0x8 */ private: SQLHDBC m_hdbc;
	/* this+0xC */ private: CODBCV2Connector* m_cpConnector;

	public: CODBCV2::CODBCV2(void);
	public: virtual CODBCV2::~CODBCV2(void);
	public: bool CODBCV2::Init(const mystd::string in_strDSN, const mystd::string in_strUserID, const mystd::string in_strPassword, const mystd::string in_strDBName, const enum CODBCV2Connector::enumConnectType in_eConnectType, const bool in_bConnect);
	public: SQLHDBC const CODBCV2::GetDBCHandle(void);
	public: void CODBCV2::Disconnect(void);
	public: void CODBCV2::AsyncConnect(void);
	public: bool CODBCV2::SyncConnect(void);

private:
	static hook_method<bool (CODBCV2::*)(const mystd::string in_strDSN, const mystd::string in_strUserID, const mystd::string in_strPassword, const mystd::string in_strDBName, const enum CODBCV2Connector::enumConnectType in_eConnectType, const bool in_bConnect)> CODBCV2::_Init;
	static hook_method<SQLHDBC const (CODBCV2::*)(void)> CODBCV2::_GetDBCHandle;
	static hook_method<void (CODBCV2::*)(void)> CODBCV2::_Disconnect;
	static hook_method<void (CODBCV2::*)(void)> CODBCV2::_AsyncConnect;
	static hook_method<bool (CODBCV2::*)(void)> CODBCV2::_SyncConnect;
};
