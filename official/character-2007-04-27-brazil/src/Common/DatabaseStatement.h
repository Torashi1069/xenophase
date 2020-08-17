/// @source itemobserver-com-2005-09-08/itemInproc/Database*
#pragma once
#include <sql.h>
class CDatabase;


// maximum number of query parameters
#define MAX_ODBC_PARAM 50

// query parameter format indicators
#define PARAM_TYPE_BINARY  'b'
#define PARAM_TYPE_DECIMAL 'd'
#define PARAM_TYPE_BIGINT  'l'
#define PARAM_TYPE_STRING  's'


class CDatabaseStatement
{
public:
	CDatabaseStatement(CDatabase* pDatabase);
	~CDatabaseStatement();
	BOOL Query(char* lpszQuery, ...);
	bool BindNumberColumn(int nColumn, void* pData);
	bool BindFloatColumn(int nColumn, void* pData);
	bool BindStringColumn(int nColumn, char* pszData, int nBufferSize);
	bool BindBinaryColumn(int nColumn, char* pszData, int nBufferSize, SQLINTEGER* outBinSize);
	SQLRETURN Fetch();
	bool Open(CDatabase* pDatabase);
	void Release();
	SQLHSTMT GetStmtHandle();

private:
	/* this+ 0 */ char* m_pszDSN;
	/* this+ 4 */ SQLHENV m_hEnv;
	/* this+ 8 */ SQLHDBC m_hDbc;
	/* this+12 */ SQLHSTMT m_hStmt;
};
