#include "globals.hpp" // DBTrace()
#include "CCharInfoDB.hpp"
#include <sql.h>
#include <sqlext.h>


CCharInfoDB::CCharInfoDB(void)
{
}


CCharInfoDB::~CCharInfoDB(void)
{
}


/* hook_method<void (CCharInfoDB::*)(int AID, int money)> CCharInfoDB::_UpdateItemStoreMoney(SERVER, "CCharInfoDB::UpdateItemStoreMoney");
void CCharInfoDB::UpdateItemStoreMoney(int AID, int money)
{
	return (this->*_UpdateItemStoreMoney)(AID, money);

	//TODO
} */


/* hook_method<void (CCharInfoDB::*)(int GID)> CCharInfoDB::_DeleteItem(SERVER, "CCharInfoDB::DeleteItem");
void CCharInfoDB::DeleteItem(int GID)
{
	return (this->*_DeleteItem)(GID);

	//TODO
} */


hook_method<void (CCharInfoDB::*)(int GID)> CCharInfoDB::_InsertWarpInfo(SERVER, "CCharInfoDB::InsertWarpInfo");
void CCharInfoDB::InsertWarpInfo(int GID)
{
	return (this->*_InsertWarpInfo)(GID);

	//TODO
}


hook_method<void (CCharInfoDB::*)(int GID, WARPPORTAL_INFO* warpInfo)> CCharInfoDB::_UpdateWarpInfo(SERVER, "CCharInfoDB::UpdateWarpInfo");
void CCharInfoDB::UpdateWarpInfo(int GID, WARPPORTAL_INFO* warpInfo)
{
	return (this->*_UpdateWarpInfo)(GID, warpInfo);

	//TODO
}


hook_method<int (CCharInfoDB::*)(int GID, WARPPORTAL_INFO* warpInfo)> CCharInfoDB::_GetWarpInfo(SERVER, "CCharInfoDB::GetWarpInfo");
int CCharInfoDB::GetWarpInfo(int GID, WARPPORTAL_INFO* warpInfo)
{
	return (this->*_GetWarpInfo)(GID, warpInfo);

	//TODO
}


hook_method<void (CCharInfoDB::*)(int GID, char* charname)> CCharInfoDB::_GetCharacterName(SERVER, "CCharInfoDB::GetCharacterName");
void CCharInfoDB::GetCharacterName(int GID, char* charname)
{
	return (this->*_GetCharacterName)(GID, charname);

	//TODO
}


hook_method<int (CCharInfoDB::*)(unsigned long AID, mystd::list<MannerPointData>* info, int& LastDate)> CCharInfoDB::_LoadMPInfo(SERVER, "CCharInfoDB::LoadMPInfo");
int CCharInfoDB::LoadMPInfo(unsigned long AID, mystd::list<MannerPointData>* info, int& LastDate)
{
	return (this->*_LoadMPInfo)(AID, info, LastDate);

	//TODO
}


//hook_method<void (CCharInfoDB::*)(unsigned long AID, unsigned long otherGID)> CCharInfoDB::_DeleteMP(SERVER, "CCharInfoDB::DeleteMP");
void CCharInfoDB::DeleteMP(unsigned long AID, unsigned long otherGID)
{
//	return (this->*_DeleteMP)(AID, otherGID);

	m_retcode = SQLAllocHandle(3, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return;

	unsigned int sAID = AID;
	unsigned int oGID = otherGID;
	int cbAID = 0;

	SQLBindParameter(m_hstmt, 1u, 1, -16, 4, 0, 0, &sAID, 0, (SQLINTEGER*)&cbAID);
	SQLBindParameter(m_hstmt, 2u, 1, -16, 4, 0, 0, &oGID, 0, (SQLINTEGER*)&cbAID);
	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call DeleteMannerPoint(?,?)}", SQL_NTS);

	if( m_retcode != 0 && m_retcode != 1 )
		DBTrace(".\\CharInfoDB.cpp", 315, 3, m_hstmt);

	SQLCloseCursor(m_hstmt);
	if( m_hstmt )
		SQLFreeHandle(3, m_hstmt);
}


//hook_method<int (CCharInfoDB::*)(unsigned long AID, unsigned long otherGID, int type)> CCharInfoDB::_InsertNewMP(SERVER, "CCharInfoDB::InsertNewMP");
int CCharInfoDB::InsertNewMP(unsigned long AID, unsigned long otherGID, int type)
{
//	return (this->*_InsertNewMP)(AID, otherGID, type);

	int result;

	m_retcode = SQLAllocHandle(3, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return 0;

	unsigned int sAID = AID;
	unsigned int oGID = otherGID;
	int mtype = type;
	int cbAID = 0;

	SQLBindParameter(m_hstmt, 1u, 1, -16, 4, 0, 0, &sAID, 0, (SQLINTEGER*)&cbAID);
	SQLBindParameter(m_hstmt, 2u, 1, -16, 4, 0, 0, &oGID, 0, (SQLINTEGER*)&cbAID);
	SQLBindParameter(m_hstmt, 3u, 1, -16, 4, 0, 0, &mtype, 0, (SQLINTEGER*)&cbAID);
	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call InsertMannerPoint(?,?,?)}", SQL_NTS);

	if( m_retcode != 0 && m_retcode != 1 )
	{
		DBTrace(".\\CharInfoDB.cpp", 348, 3, m_hstmt);
		result = 0;
	}
	else
		result = 1;

	SQLCloseCursor(m_hstmt);
	if( m_hstmt )
		SQLFreeHandle(3, m_hstmt);

	return result;
}


hook_method<int (CCharInfoDB::*)(char* Name, unsigned long& AID, unsigned long& GID)> CCharInfoDB::_GetCharacterID(SERVER, "CCharInfoDB::GetCharacterID");
int CCharInfoDB::GetCharacterID(char* Name, unsigned long& AID, unsigned long& GID)
{
	return (this->*_GetCharacterID)(Name, AID, GID);

	//TODO
}


/* hook_method<int (CCharInfoDB::*)(char* GID, char* Name)> CCharInfoDB::_UpdatePVPEvent(SERVER, "CCharInfoDB::UpdatePVPEvent");
int CCharInfoDB::UpdatePVPEvent(char* GID, char* Name)
{
	return (this->*_UpdatePVPEvent)(GID, Name);

	//TODO
} */


/* hook_method<int (CCharInfoDB::*)(char* GID, char* Name)> CCharInfoDB::_GetPVPEvent(SERVER, "CCharInfoDB::GetPVPEvent");
int CCharInfoDB::GetPVPEvent(char* GID, char* Name)
{
	return (this->*_GetPVPEvent)(GID, Name);

	//TODO
} */


hook_method<void (CCharInfoDB::*)(void* hStmt, char* lpszError)> CCharInfoDB::_GetErrorString(SERVER, "CCharInfoDB::GetErrorString");
void CCharInfoDB::GetErrorString(void* hStmt, char* lpszError)
{
	return (this->*_GetErrorString)(hStmt, lpszError);

	//TODO
}


hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* pShortCutKey)> CCharInfoDB::_GetShortCutKey(SERVER, "CCharInfoDB::GetShortCutKey");
int CCharInfoDB::GetShortCutKey(unsigned long GID, unsigned char* pShortCutKey)
{
	return (this->*_GetShortCutKey)(GID, pShortCutKey);

	//TODO
}


hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* pShortCutKey)> CCharInfoDB::_UpdateShortCutKey(SERVER, "CCharInfoDB::UpdateShortCutKey");
int CCharInfoDB::UpdateShortCutKey(unsigned long GID, unsigned char* pShortCutKey)
{
	return (this->*_UpdateShortCutKey)(GID, pShortCutKey);

	//TODO
}


hook_method<int (CCharInfoDB::*)(int GID)> CCharInfoDB::_InsertHuntingList(SERVER, "CCharInfoDB::InsertHuntingList");
int CCharInfoDB::InsertHuntingList(int GID)
{
	return (this->*_InsertHuntingList)(GID);

	//TODO
}


hook_method<int (CCharInfoDB::*)(int GID)> CCharInfoDB::_InsertTimeList(SERVER, "CCharInfoDB::InsertTimeList");
int CCharInfoDB::InsertTimeList(int GID)
{
	return (this->*_InsertTimeList)(GID);

	//TODO
}


hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf)> CCharInfoDB::_SelectHuntingList(SERVER, "CCharInfoDB::SelectHuntingList");
int CCharInfoDB::SelectHuntingList(unsigned long GID, unsigned char* buf)
{
	return (this->*_SelectHuntingList)(GID, buf);

	//TODO
}


hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf, int size)> CCharInfoDB::_UpdateHuntingList(SERVER, "CCharInfoDB::UpdateHuntingList");
int CCharInfoDB::UpdateHuntingList(unsigned long GID, unsigned char* buf, int size)
{
	return (this->*_UpdateHuntingList)(GID, buf, size);

	//TODO
}


hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf)> CCharInfoDB::_SelectTimeList(SERVER, "CCharInfoDB::SelectTimeList");
int CCharInfoDB::SelectTimeList(unsigned long GID, unsigned char* buf)
{
	return (this->*_SelectTimeList)(GID, buf);

	//TODO
}


hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf, int size)> CCharInfoDB::_UpdateTimeList(SERVER, "CCharInfoDB::UpdateTimeList");
int CCharInfoDB::UpdateTimeList(unsigned long GID, unsigned char* buf, int size)
{
	return (this->*_UpdateTimeList)(GID, buf, size);

	//TODO
}
