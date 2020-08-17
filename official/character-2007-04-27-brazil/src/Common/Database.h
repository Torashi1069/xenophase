#pragma once
#include <sql.h>
#define MAX_BUFFER_LENGTH 2048


class CDatabase
{
public:
	CDatabase();
	~CDatabase();
	bool Connect(const char* lpszID, const char* lpszPassword, const char* lpszDSN);
	void Disconnect();
	bool SetTranslateOption(bool bTranslateOpt);

public:
	/* this+0 */ SQLHENV m_hEnv;
	/* this+4 */ SQLHDBC m_hDbc;
	/* this+8 */ char m_szDSN[MAX_BUFFER_LENGTH];
};


void GetSQLErrorString(SQLHENV hEnv, SQLHDBC hDbc, SQLHSTMT hStmt, char* pszError);
