#pragma once
#include <sql.h>


#pragma pack(push,1)
class CODBC
{
	/* this+ 0 */ public: //const CODBC::`vftable';
	/* this+ 4 */ protected: SQLHENV m_henv;
	/* this+ 8 */ protected: SQLHDBC m_hdbc;
	/* this+12 */ protected: SQLHSTMT m_hstmt;
	/* this+16 */ protected: SQLRETURN m_retcode;

	public: CODBC::CODBC(void);
	public: virtual CODBC::~CODBC(void);
	public: int CODBC::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type);
	public: void CODBC::Reset(void);
	public: void CODBC::GetErrorString(SQLHSTMT hStmt, char* lpszError);

private:
	static hook_method<int (CODBC::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CODBC::_Init;
	static hook_method<void (CODBC::*)(void)> CODBC::_Reset;
	static hook_method<void (CODBC::*)(SQLHSTMT hStmt, char* lpszError)> CODBC::_GetErrorString;
};
#pragma pack(pop)


class CDBStatement
{
	/* this+0 */ private: SQLHSTMT m_hStmt;

	public: CDBStatement::CDBStatement(void);
	public: CDBStatement::~CDBStatement(void);
	public: operator SQLHSTMT();
	public: bool CDBStatement::Init(SQLHDBC hDBC);

private:
	static hook_method<SQLHSTMT (CDBStatement::*)(void)> CDBStatement::_operator_SQLHSTMT;
	static hook_method<bool (CDBStatement::*)(SQLHDBC hDBC)> CDBStatement::_Init;
};


void __cdecl DBTrace(const char* in_SrcFileName, const int in_SrcLineNum, SQLSMALLINT type, SQLHSTMT handle);
