#pragma once
#pragma pack(push,1)


class CODBC
{
public:
	operator SQLHSTMT();

public:
	CODBC();
	virtual ~CODBC();

public:
	void Reset();
	void GetErrorString(SQLHSTMT hStmt, char* lpszError);
	BOOL Init(const char* FileDSN, const char* PASS);

protected:
	/* this+ 0 */ //const CODBC::`vftable';
	/* this+ 4 */ SQLHENV m_henv;
	/* this+ 8 */ SQLHDBC m_hdbc;
	/* this+12 */ SQLHSTMT m_hstmt;
	/* this+16 */ SQLRETURN m_retcode;
};


class CDBStatement
{
public:
	CDBStatement();
	~CDBStatement();

public:
	operator SQLHSTMT();
	bool Init(SQLHSTMT hDBC);

private:
	/* this+0 */ SQLHSTMT m_hStmt;
};


void DBTrace(const char* in_SrcFileName, const int in_SrcLineNum, SQLSMALLINT type, SQLHSTMT handle);


#pragma pack(pop)
