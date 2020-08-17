#pragma once
#include "shared/ODBC.h"


// maximum number of query parameters
#define MAX_ODBC_PARAM 30

// query parameter format indicators
#define PARAM_TYPE_DECIMAL 'd'
#define PARAM_TYPE_STRING  's'


class CExtendedODBC : public CODBC
{
public:
	CExtendedODBC();
	virtual ~CExtendedODBC();

public:
	BOOL Connect(const char* FileDsn, const char* lpszPassword);
	BOOL Query(SQLHSTMT hStmt, const char* lpszQuery, ...);
	BOOL AllocStmt(SQLHSTMT* phStmt);
	void FreeStmt(SQLHSTMT* phStmt, int nOption);
	void GetErrorString(SQLHSTMT hStmt, char* lpszError);
	BOOL IsError(SQLRETURN sqlResult);
};
