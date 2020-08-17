#include "AccountDB.h"
#include "Common/DatabaseStatement.h"
#include "Enums.h"


CAccountDB::CAccountDB()
{
}


CAccountDB::~CAccountDB()
{
}


DWORD CAccountDB::GetAID(const char* lpszID)
{
	DWORD nAID;
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetAID(%s)}", lpszID);
	stmt.CDatabaseStatement::BindNumberColumn(1, &nAID);

	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		nAID = 0;

	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
	return nAID;
}


// guessed
void CAccountDB::GetID(DWORD dwAID, const char* lpszID)
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
//	return bSuccess;
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


void CAccountDB::GetAuthenticateInfo(char* lpszID, BYTE byClientType, SAUTHENTICATE* pAuthencate)
{
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call AuthenticateUser(%s)}", lpszID);

	char szID[23+1] = {};
	stmt.CDatabaseStatement::BindStringColumn(1, szID, sizeof(szID));
	stmt.CDatabaseStatement::BindStringColumn(2, pAuthencate->m_passwd, sizeof(pAuthencate->m_passwd)-1);
	stmt.CDatabaseStatement::BindNumberColumn(3, &pAuthencate->m_dwGrade);
	stmt.CDatabaseStatement::BindNumberColumn(4, &pAuthencate->m_dwConfirmed);
	stmt.CDatabaseStatement::BindNumberColumn(5, &pAuthencate->m_dwAID);

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
	if( _stricmp(lpszID, szID) != 0 )
		pAuthencate->m_dwResult = REFUSE_INVALID_ID;
	else
	{// success
		pAuthencate->m_dwResult = ACCEPT_ID_PASSWD;
	}
}


void CAccountDB::AuthenticateUser(char* lpszID, char* lpszPassword, SAUTHENTICATE& authenticate, BYTE byClientType)
{
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call AuthenticateUser(%s)}", lpszID);

	char szID[26] = {};
	char szPassword[26] = {};
	stmt.CDatabaseStatement::BindStringColumn(1, szID, sizeof(szID));
	stmt.CDatabaseStatement::BindStringColumn(2, szPassword, sizeof(szPassword));
	stmt.CDatabaseStatement::BindNumberColumn(3, &authenticate.m_dwGrade);
	stmt.CDatabaseStatement::BindNumberColumn(4, &authenticate.m_dwConfirmed);
	stmt.CDatabaseStatement::BindNumberColumn(5, &authenticate.m_dwAID);

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
	else
	if( strcmp(lpszPassword, szPassword) != 0 )
		authenticate.m_dwResult = REFUSE_INVALID_PASSWD;
	else
	if( _stricmp(lpszID, szID) != 0 )
		authenticate.m_dwResult = REFUSE_INVALID_ID;
	else
	{// success
		authenticate.m_dwResult = ACCEPT_ID_PASSWD;
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


int CAccountDB::UpdateUserInfo2(DWORD dwAID, SUSERINFO* pUserInfo)
{
	int result;
	m_csAccountDB.Enter();

	CDatabaseStatement stmt(this);
	result = stmt.CDatabaseStatement::Query("{call UpdateUserInfo2(%d,%d)}", dwAID, pUserInfo->m_nIP);
	stmt.CDatabaseStatement::Release();

	m_csAccountDB.Leave();
	return result;
}
