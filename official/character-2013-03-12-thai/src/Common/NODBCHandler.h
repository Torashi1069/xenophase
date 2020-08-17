#pragma once
class CDatabase;
#include <sql.h>


class NODBCHandler
{
private:
	/* this+ 0 */ //const NODBCHandler::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ CDatabase* m_cpDatabase;
	/* this+12 */ SQLHSTMT m_hStmt;

private:
	bool Init();

public:	
	bool isOK() const;
	SQLRETURN ExecDirect(const std::string in_strQuery);
//	SQLRETURN UnBind();
	SQLRETURN BindCol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_Ind);
	SQLRETURN BindParameter(SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLINTEGER cbValueMax, SQLINTEGER* pcbValue);
	SQLRETURN GetData(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_IndPtr);
	SQLRETURN CloseCursor();
	SQLRETURN PutData(SQLPOINTER Data, SQLINTEGER StrLen_or_Ind);
	SQLRETURN Fetch();
	SQLRETURN ParamData(SQLPOINTER* Value);
	operator SQLHSTMT();
	std::string GetErrorString();

	NODBCHandler(CDatabase* in_cpDatabase);
	virtual ~NODBCHandler();
};
