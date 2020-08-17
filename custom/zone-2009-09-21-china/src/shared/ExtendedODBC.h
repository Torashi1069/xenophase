#pragma once
#include "ODBC.h"


class CExtendedODBC : public CODBC
{
public:
	/* this+0x0 */ //CODBC

	public: CExtendedODBC::CExtendedODBC(void);
	public: virtual CExtendedODBC::~CExtendedODBC(void);
	public: int CExtendedODBC::Connect(const char* lpszID, const char* lpszPassword, const char* lpszDSN, unsigned char byConnectType, const char* lpszDB);
	//public: int CExtendedODBC::Query(SQLHSTMT* hStmt, const char* lpszQuery, ...);
	public: int CExtendedODBC::AllocStmt(SQLHSTMT* phStmt);
	public: void CExtendedODBC::FreeStmt(SQLHSTMT* phStmt, int nOption);
	public: void CExtendedODBC::GetErrorString(SQLHSTMT* hStmt, char* lpszError);
	public: int CExtendedODBC::IsError(short sqlResult);

private:
	static hook_method<int (CExtendedODBC::*)(const char* lpszID, const char* lpszPassword, const char* lpszDSN, unsigned char byConnectType, const char* lpszDB)> CExtendedODBC::_Connect;
	static hook_method<int (CExtendedODBC::*)(SQLHSTMT* phStmt)> CExtendedODBC::_AllocStmt;
	static hook_method<void (CExtendedODBC::*)(SQLHSTMT* phStmt, int nOption)> CExtendedODBC::_FreeStmt;
	static hook_method<void (CExtendedODBC::*)(SQLHSTMT* hStmt, char* lpszError)> CExtendedODBC::_GetErrorString;
	static hook_method<int (CExtendedODBC::*)(short sqlResult)> CExtendedODBC::_IsError;
};
