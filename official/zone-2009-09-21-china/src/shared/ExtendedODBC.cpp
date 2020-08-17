#include "ExtendedODBC.h"


CExtendedODBC::CExtendedODBC(void)
{
}


CExtendedODBC::~CExtendedODBC(void)
{
}

hook_method<int (CExtendedODBC::*)(const char* lpszID, const char* lpszPassword, const char* lpszDSN, unsigned char byConnectType, const char* lpszDB)> CExtendedODBC::_Connect(SERVER, "CExtendedODBC::Connect");
int CExtendedODBC::Connect(const char* lpszID, const char* lpszPassword, const char* lpszDSN, unsigned char byConnectType, const char* lpszDB)
{
	return (this->*_Connect)(lpszID, lpszPassword, lpszDSN, byConnectType, lpszDB);

	//TODO
}


hook_method<int (CExtendedODBC::*)(SQLHSTMT* phStmt)> CExtendedODBC::_AllocStmt(SERVER, "CExtendedODBC::AllocStmt");
int CExtendedODBC::AllocStmt(SQLHSTMT* phStmt)
{
	return (this->*_AllocStmt)(phStmt);

	//TODO
}


hook_method<void (CExtendedODBC::*)(SQLHSTMT* phStmt, int nOption)> CExtendedODBC::_FreeStmt(SERVER, "CExtendedODBC::FreeStmt");
void CExtendedODBC::FreeStmt(SQLHSTMT* phStmt, int nOption)
{
	return (this->*_FreeStmt)(phStmt, nOption);

	//TODO
}


hook_method<void (CExtendedODBC::*)(SQLHSTMT* hStmt, char* lpszError)> CExtendedODBC::_GetErrorString(SERVER, "CExtendedODBC::GetErrorString");
void CExtendedODBC::GetErrorString(SQLHSTMT* hStmt, char* lpszError)
{
	return (this->*_GetErrorString)(hStmt, lpszError);

	//TODO
}


hook_method<int (CExtendedODBC::*)(short sqlResult)> CExtendedODBC::_IsError(SERVER, "CExtendedODBC::IsError");
int CExtendedODBC::IsError(short sqlResult)
{
	return (this->*_IsError)(sqlResult);

	//TODO
}
