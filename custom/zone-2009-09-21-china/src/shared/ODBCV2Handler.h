#pragma once
#include "ODBCV2.h"


class CODBCV2Handler
{
	/* this+0x0 */ //const CODBCV2Handler::`vftable'
	/* this+0x4 */ private: SQLHSTMT m_hStmt;
	/* this+0x8 */ private: CODBCV2* m_vcpODBCV2;
	/* this+0xC */ private: bool m_bError;
	/* this+0xD */ private: const bool m_bReqAutoAsyncConnectWhenError;

	public: SQLRETURN CODBCV2Handler::BindParameter(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue);
	public: SQLRETURN CODBCV2Handler::ExecDirect(unsigned char* StatementText, long TextLength);
	public: SQLRETURN CODBCV2Handler::BindCol(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind);
	public: SQLRETURN CODBCV2Handler::Fetch(void);
	public: operator CODBCV2Handler::SQLHSTMT(void);
	public: CODBCV2Handler::CODBCV2Handler(CODBCV2* in_cpODBCV2, const bool in_bReqAutoAsyncConnectWhenError);
	public: virtual CODBCV2Handler::~CODBCV2Handler(void);

private:
	static hook_method<SQLRETURN (CODBCV2Handler::*)(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue)> CODBCV2Handler::_BindParameter;
	static hook_method<SQLRETURN (CODBCV2Handler::*)(unsigned char* StatementText, long TextLength)> CODBCV2Handler::_ExecDirect;
	static hook_method<SQLRETURN (CODBCV2Handler::*)(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind)> CODBCV2Handler::_BindCol;
	static hook_method<SQLRETURN (CODBCV2Handler::*)(void)> CODBCV2Handler::_Fetch;
	static hook_method<SQLHSTMT (CODBCV2Handler::*)(void)> CODBCV2Handler::_operator_SQLHSTMT;
};
