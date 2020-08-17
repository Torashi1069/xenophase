#pragma once
#include "shared/N2System/ODBC(open database connectivity)/N2ODBCCtrl.h"


class N2ODBCHandler
{
private:
	/* this+ 0 */ //const N2ODBCHandler::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ N2ODBCCtrl& m_vcODBCCtrl;
	/* this+12 */ SQLHSTMT m_hStmt;

private:
	bool Init();

public:
	bool isOK() const;
	SQLRETURN ExecDirect(const std::string in_strQuery);
	SQLRETURN UnBind();
	SQLRETURN BindCol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_Ind);
	SQLRETURN BindParameter(SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLULEN cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLLEN cbValueMax, SQLLEN* pcbValue);
	SQLRETURN GetData(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLLEN BufferLength, SQLLEN* StrLen_or_Ind);
	SQLRETURN CloseCursor();
	SQLRETURN PutData(SQLPOINTER Data, SQLLEN StrLen_or_Ind);
	SQLRETURN Fetch();
	SQLRETURN ParamData(SQLPOINTER* Value);
	operator SQLHSTMT();
	void OutputErrorString(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage);
	std::string GetErrorString(); //TODO

public:
	N2ODBCHandler(N2ODBCCtrl& in_cODBCCtrl);
	virtual ~N2ODBCHandler();
};
