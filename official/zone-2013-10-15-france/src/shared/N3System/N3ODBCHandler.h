#pragma once
#include "shared/N3System/N3ODBCCtrl.h"


class N3ODBCHandler
{
private:
	/* this+ 0 */ //const N3ODBCHandler::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ N3ODBCCtrl& m_vcODBCCtrl;
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
	SQLRETURN MoreResults(); //TODO
	operator SQLHSTMT();
	void OutputErrorString(const char* in_pSourceFileName, const int in_SourceLineNum, const char* in_pMessage);
	std::string GetErrorString();

public:
	N3ODBCHandler(N3ODBCCtrl& in_cODBCCtrl);
	virtual ~N3ODBCHandler();
};
