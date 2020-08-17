#pragma once
#include "N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"


class N2ODBCHandler
{
	/* this+ 0 */ public: //const N2ODBCHandler::`vftable';
	/* this+ 4 */ private: bool m_bOK;
	/* this+ 8 */ private: N2ODBCCtrl& m_vcODBCCtrl;
	/* this+12 */ private: SQLHSTMT m_hStmt;

	public: N2ODBCHandler::N2ODBCHandler(N2ODBCCtrl& in_cODBCCtrl);
	public: virtual N2ODBCHandler::~N2ODBCHandler(void);
	public: bool N2ODBCHandler::isOK(void) const;
	private: bool N2ODBCHandler::Init(void);
	public: SQLRETURN N2ODBCHandler::ExecDirect(const mystd::string in_strQuery);
	public: SQLRETURN N2ODBCHandler::UnBind(void);
	public: SQLRETURN N2ODBCHandler::BindCol(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind);
	public: SQLRETURN N2ODBCHandler::BindParameter(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue);
	public: SQLRETURN N2ODBCHandler::GetData(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind);
	public: SQLRETURN N2ODBCHandler::CloseCursor(void);
	public: SQLRETURN N2ODBCHandler::PutData(void* Data, long StrLen_or_Ind);
	public: SQLRETURN N2ODBCHandler::Fetch(void);
	public: SQLRETURN N2ODBCHandler::ParamData(void** Value);
	public: operator N2ODBCHandler::SQLHSTMT(void);
	public: void N2ODBCHandler::OutputErrorString(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage);

private:
	static hook_method<bool (N2ODBCHandler::*)(void)> N2ODBCHandler::_Init;
	static hook_method<bool (N2ODBCHandler::*)(void) const> N2ODBCHandler::_isOK;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(const mystd::string in_strQuery)> N2ODBCHandler::_ExecDirect;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(void)> N2ODBCHandler::_UnBind;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind)> N2ODBCHandler::_BindCol;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(unsigned short ipar, short fParamType, short fCType, short fSqlType, unsigned long cbColDef, short ibScale, void* rgbValue, long cbValueMax, long* pcbValue)> N2ODBCHandler::_BindParameter;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(unsigned short ColumnNumber, short TargetType, void* TargetValue, long BufferLength, long* StrLen_or_Ind)> N2ODBCHandler::_GetData;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(void)> N2ODBCHandler::_CloseCursor;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(void* Data, long StrLen_or_Ind)> N2ODBCHandler::_PutData;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(void)> N2ODBCHandler::_Fetch;
	static hook_method<SQLRETURN (N2ODBCHandler::*)(void** Value)> N2ODBCHandler::_ParamData;
	static hook_method<SQLHSTMT (N2ODBCHandler::*)(void)> N2ODBCHandler::_operator_SQLHSTMT;
	static hook_method<void (N2ODBCHandler::*)(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage)> N2ODBCHandler::_OutputErrorString;
};
