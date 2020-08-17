#include "AccountDB.h"
#include "Common/DatabaseStatement.h"
#include "Enums.h"
#include "hash/md5.hpp"


CAccountDB::CAccountDB()
{
}


CAccountDB::~CAccountDB()
{
}


void CAccountDB::UpdateIsConfirmed(DWORD dwAID, int nVal)
{
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("update login set isConfirmed=%d where (aid=%d)", nVal, dwAID);
	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
}


DWORD CAccountDB::GetAID(const char* lpszID)
{
	DWORD nAID;
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetAID(%s)}", lpszID);
	stmt.CDatabaseStatement::BindNumberColumn(1, &nAID);

	nAID = 0;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		nAID = 0;

	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
	return nAID;
}


bool CAccountDB::GetID(DWORD dwAID, const char* lpszID)
{
	bool bSuccess;
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetID(%d)}", dwAID);
	stmt.CDatabaseStatement::BindStringColumn(1, const_cast<char*>(lpszID), 23);

	bSuccess = true;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		bSuccess = false;

	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
	return bSuccess;
}


BOOL CAccountDB::GetUserInfo(DWORD dwAID, SUSERINFO* pUserInfo)
{
	BOOL bSuccess;
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetUserInfo(%d)}", dwAID);
	stmt.CDatabaseStatement::BindNumberColumn(1, &pUserInfo->m_nSex);
	stmt.CDatabaseStatement::BindStringColumn(2, pUserInfo->m_szPersonalNum, 15);
	stmt.CDatabaseStatement::BindStringColumn(3, pUserInfo->m_szEmail, 32);
	stmt.CDatabaseStatement::BindNumberColumn(4, &pUserInfo->m_nIP);
	stmt.CDatabaseStatement::BindStringColumn(5, pUserInfo->m_szLastConnectionTime, 30);

	bSuccess = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		bSuccess = FALSE;
	else
	{
		if( pUserInfo->m_nSex != SEX_MALE )
			pUserInfo->m_nSex = SEX_FEMALE;
	}

	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
	return bSuccess;
}


void CAccountDB::GetBlockDate(char* lpszID, char* lpszBlockDate)
{
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("select convert(varchar,endblockdate,120) from login where ID = %s", lpszID);
	stmt.CDatabaseStatement::BindStringColumn(1, lpszBlockDate, 17);
	stmt.CDatabaseStatement::Fetch();
	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
}


void CAccountDB::GetAuthenticateInfo(char* szRecvID, BYTE byClientType, SAUTHENTICATE* pAuthencate)
{
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call AuthenticateUser(%s)}", szRecvID);
	
	char szDBID[23+1] = {};
	char szBlockDate[24+1] = {};
	char szDate[24+1] = {};
	stmt.CDatabaseStatement::BindStringColumn(1, szDBID, sizeof(szDBID)-1);
	stmt.CDatabaseStatement::BindStringColumn(2, pAuthencate->m_passwd, sizeof(pAuthencate->m_passwd)-1);
	stmt.CDatabaseStatement::BindNumberColumn(3, &pAuthencate->m_dwGrade);
	stmt.CDatabaseStatement::BindNumberColumn(4, &pAuthencate->m_dwConfirmed);
	stmt.CDatabaseStatement::BindNumberColumn(5, &pAuthencate->m_dwAID);
	stmt.CDatabaseStatement::BindStringColumn(6, szBlockDate, 22);
	stmt.CDatabaseStatement::BindStringColumn(7, szDate, 22);

	SQLRETURN err = stmt.CDatabaseStatement::Fetch();

	stmt.CDatabaseStatement::Release();
	m_csAccountDB.Leave();

	if( !SQL_SUCCEEDED(err) )
		pAuthencate->m_dwResult = REFUSE_INVALID_ID;
	else
	if( byClientType == CLIENTTYPE_THAI_SAKRAY && pAuthencate->m_dwGrade == 1 )
		pAuthencate->m_dwResult = REFUSE_NONSAKRAY_ID_BLOCKED;
	else
	if( pAuthencate->m_dwGrade == 99 )
		pAuthencate->m_dwResult = REFUSE_DELETED_ACCOUNT;
	else
	if( pAuthencate->m_dwConfirmed != 3 )
		pAuthencate->m_dwResult = REFUSE_NOT_CONFIRMED;
	else
	if( _stricmp(szRecvID, szDBID) != 0 )
		pAuthencate->m_dwResult = REFUSE_INVALID_ID;
	else
	{// success
		pAuthencate->m_dwResult = ACCEPT_ID_PASSWD;
	}

	strncpy_s(szRecvID, 23, szDBID, 23);

	if( pAuthencate->m_dwResult == REFUSE_NOT_CONFIRMED && pAuthencate->m_dwConfirmed == 4 )
	{
		if( strcmp(szBlockDate, szDate) > 0 )
			pAuthencate->m_dwResult = REFUSE_BLOCK_TEMPORARY;
		else
		{// ban expired
			this->CAccountDB::UpdateIsConfirmed(pAuthencate->m_dwAID, 3);
			pAuthencate->m_dwResult = ACCEPT_ID_PASSWD;
			pAuthencate->m_dwConfirmed = 3;
		}
	}
}


void CAccountDB::AuthenticateUser(char* lpszID, char* lpszPassword, SAUTHENTICATE& authenticate, BYTE byClientType)
{
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call AuthenticateUser(%s)}", lpszID);

	char szID[26] = {};
	char szPassword[max(26,MD5::HEXHASHSIZE+1)] = {}; // [patch] md5-hex database passwords
	char szBlockDate[25] = {};
	char szDate[25] = {};
	stmt.CDatabaseStatement::BindStringColumn(1, szID, sizeof(szID));
	stmt.CDatabaseStatement::BindStringColumn(2, szPassword, sizeof(szPassword));
	stmt.CDatabaseStatement::BindNumberColumn(3, &authenticate.m_dwGrade);
	stmt.CDatabaseStatement::BindNumberColumn(4, &authenticate.m_dwConfirmed);
	stmt.CDatabaseStatement::BindNumberColumn(5, &authenticate.m_dwAID);
	stmt.CDatabaseStatement::BindStringColumn(6, szBlockDate, 22);
	stmt.CDatabaseStatement::BindStringColumn(7, szDate, 22);

	SQLRETURN err = stmt.CDatabaseStatement::Fetch();

	stmt.CDatabaseStatement::Release();
	m_csAccountDB.Leave();

	if( !SQL_SUCCEEDED(err) )
		authenticate.m_dwResult = REFUSE_INVALID_ID;
	else
	if( byClientType == CLIENTTYPE_THAI_SAKRAY && authenticate.m_dwGrade == 1 )
		authenticate.m_dwResult = REFUSE_NONSAKRAY_ID_BLOCKED;
	else
	if( authenticate.m_dwGrade == 99 )
		authenticate.m_dwResult = REFUSE_DELETED_ACCOUNT;
	else
	if( authenticate.m_dwConfirmed != 3 )
		authenticate.m_dwResult = REFUSE_NOT_CONFIRMED;
#if defined(RFEXE) // [patch] plaintext login packet
	else
	if( strcmp(lpszPassword, szPassword) != 0 && MD5::memhash_hex(lpszPassword, strlen(lpszPassword)) != szPassword ) // [patch] md5-hex database passwords
		authenticate.m_dwResult = REFUSE_INVALID_PASSWD;
#endif
	else
	if( _stricmp(lpszID, szID) != 0 )
		authenticate.m_dwResult = REFUSE_INVALID_ID;
	else
	{// success
		authenticate.m_dwResult = ACCEPT_ID_PASSWD;
	}

	strncpy_s(lpszID, 23, szID, 23);

	if( authenticate.m_dwResult == REFUSE_NOT_CONFIRMED && authenticate.m_dwConfirmed == 4 )
	{
		if( strcmp(szBlockDate, szDate) > 0 )
			authenticate.m_dwResult = REFUSE_BLOCK_TEMPORARY;
#if defined(RFEXE) // [patch] plaintext login packet
		else
		if( strcmp(lpszPassword, szPassword) != 0 && MD5::memhash_hex(lpszPassword, strlen(lpszPassword)) != szPassword ) // [patch] md5-hex database passwords
			authenticate.m_dwResult = REFUSE_INVALID_PASSWD;
#endif
		else
		{// ban expired
			authenticate.m_dwResult = ACCEPT_ID_PASSWD;
			authenticate.m_dwConfirmed = 3;
		}
	}
}


int CAccountDB::UpdateUserInfo(DWORD dwAID, SUSERINFO* pUserInfo)
{
	int result;
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	result = stmt.CDatabaseStatement::Query("{call UpdateUserInfo(%d,%d,%s)}", dwAID, pUserInfo->m_nIP, pUserInfo->m_szLastConnectionTime);
	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
	return result;
}


// guessed
int CAccountDB::UpdateUserInfo2(DWORD dwAID, SUSERINFO* pUserInfo)
{
	int result;
	m_csAccountDB.Enter();

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	char szCurrentTime[30];
	sprintf(szCurrentTime, "%hu-%02hu-%02huT%02hu:%02hu:%02hu.%03hu", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);

	CDatabaseStatement stmt(this);
	result = stmt.CDatabaseStatement::Query("{call UpdateUserInfo(%d,%d,%s)}", dwAID, pUserInfo->m_nIP, szCurrentTime);
	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
	return result;
}


void CAccountDB::GetIsConfirmedMsg(int isConfirmed, char* msg_buf, int buf_len)
{
	m_csAccountDB.Enter();

	std::map<int,std::string>::const_iterator it = m_mapIsConfirmedMsg.find(isConfirmed);
	const char* msg = ( it != m_mapIsConfirmedMsg.end() ) ? it->second.c_str() : "not defined";

	strncpy_s(msg_buf, buf_len, msg, buf_len);
	msg_buf[buf_len-1] = '\0';

	m_csAccountDB.Leave();
}
