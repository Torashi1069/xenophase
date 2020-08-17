#pragma once
#include <sql.h>
#define MAX_BUFFER_LENGTH 2048


class CDatabase
{
public:
	CDatabase();
	~CDatabase();
	bool Connect(const char* in_szpFileDSN, const char* in_Pwd);
	void Disconnect();
	bool SetTranslateOption(bool bTranslateOpt);

public:
	/* this+0 */ SQLHENV m_hEnv;
	/* this+4 */ SQLHDBC m_hDbc;
	/* this+8 */ std::string m_Name;
};


void GetSQLErrorString(SQLHENV hEnv, SQLHDBC hDbc, SQLHSTMT hStmt, char* pszError);
