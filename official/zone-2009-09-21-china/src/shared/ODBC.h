#pragma once
#include <sql.h>


enum
{
	DSN_CONNECT_TYPE    = 0,
	DRIVER_CONNECT_TYPE = 1,
};


#pragma pack(push,1)
class CODBC
{
public:
	CODBC();
	virtual ~CODBC();
	int Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type);
	void Reset();
	void GetErrorString(SQLHSTMT hStmt, char* lpszError);

public:
	/* this+ 0 */ //const CODBC::`vftable';
	/* this+ 4 */ SQLHENV m_henv;
	/* this+ 8 */ SQLHDBC m_hdbc;
	/* this+12 */ SQLHSTMT m_hstmt;
	/* this+16 */ SQLRETURN m_retcode;
};
#pragma pack(pop)


class CDBStatement
{
public:
	CDBStatement();
	~CDBStatement();
	operator SQLHSTMT();
	bool Init(SQLHDBC hDBC);

public:
	/* this+0 */ SQLHSTMT m_hStmt;
};


void __cdecl DBTrace(const char* in_SrcFileName, const int in_SrcLineNum, SQLSMALLINT type, SQLHANDLE handle);
BOOL __cdecl AddSystemDSN(const char* dsn, const char* server, const char* db);
