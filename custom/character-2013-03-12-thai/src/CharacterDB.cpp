#include "CharacterDB.h"
#include "Common/Database.h"
#include "Common/DatabaseStatement.h"
#include "Common/EnterTraceLog.h"
#include <sqlext.h>
////////////////////////////////////////


CCharacterDBBase::CCharacterDBBase(const char* in_szpFileDSNFileName)
: m_strFileDSNfileName(in_szpFileDSNFileName)
{
	m_bIsConnected = false;
}


CCharacterDBBase::~CCharacterDBBase()
{
}


bool CCharacterDBBase::IsConnected()
{
	return m_bIsConnected;
}


void CCharacterDBBase::SetPwd(const char* in_szPwd)
{
	m_strPwd = in_szPwd;
}


bool CCharacterDBBase::Connect()
{
	return this->CDatabase::Connect(m_strFileDSNfileName.c_str(), m_strPwd.c_str());
}


bool CCharacterDBBase::IsOnline()
{
	bool result = false;
	m_csCharacterDB.Enter();

	HSTMT hStmt;
	if( SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &hStmt)) )
	{
		if( SQL_SUCCEEDED(SQLExecDirectA(hStmt, (SQLCHAR*)"SELECT 1", SQL_NTS)) )
		{
			result = true;
		}

		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	m_csCharacterDB.Leave();
	return result;
}


void CCharacterDBBase::VeryfyConnection()
{
	if( this->CCharacterDBBase::IsOnline() )
	{
		if( !m_bIsConnected )
		{
			m_bIsConnected = true;
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "character DB connected. (timegettime:%u)", timeGetTime());
		}
	}
	else
	{
		if( m_bIsConnected )
		{
			m_bIsConnected = false;
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "charcterDB disconnected, try reconnect %u", timeGetTime());
		}

		m_csCharacterDB.Enter();
		this->CDatabase::Disconnect();
		m_csCharacterDB.Leave();

		m_csCharacterDB.Enter();
		if( !this->CCharacterDBBase::Connect() )
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "characterDB connect failed %u", timeGetTime());
		m_csCharacterDB.Leave();
	}
}


int CCharacterDBBase::GetCharInfo(int nAID, SCHARINFO* pCharInfo, bool bTranslateOpt, int nMaxCharInfoCount)
{
	m_csCharacterDB.Enter();

	if( !bTranslateOpt )
		this->CDatabase::SetTranslateOption(false);

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetCharinfo2(%d)}", nAID);

	SCHARINFO charinfo = {};
	stmt.CDatabaseStatement::BindNumberColumn( 1, &charinfo.m_nGID);
	stmt.CDatabaseStatement::BindStringColumn( 2, charinfo.m_szName, 24);
	stmt.CDatabaseStatement::BindNumberColumn( 3, &charinfo.m_nJob);
	stmt.CDatabaseStatement::BindNumberColumn( 4, &charinfo.m_nCLevel);
	stmt.CDatabaseStatement::BindNumberColumn( 5, &charinfo.m_nSpPoint);
	stmt.CDatabaseStatement::BindNumberColumn( 6, &charinfo.m_nExp);
	stmt.CDatabaseStatement::BindNumberColumn( 7, &charinfo.m_nJobPoint);
	stmt.CDatabaseStatement::BindNumberColumn( 8, &charinfo.m_nStr);
	stmt.CDatabaseStatement::BindNumberColumn( 9, &charinfo.m_nAgi);
	stmt.CDatabaseStatement::BindNumberColumn(10, &charinfo.m_nVit);
	stmt.CDatabaseStatement::BindNumberColumn(11, &charinfo.m_nInt);
	stmt.CDatabaseStatement::BindNumberColumn(12, &charinfo.m_nDex);
	stmt.CDatabaseStatement::BindNumberColumn(13, &charinfo.m_nLuk);
	stmt.CDatabaseStatement::BindNumberColumn(14, &charinfo.m_nHp);
	stmt.CDatabaseStatement::BindNumberColumn(15, &charinfo.m_nMaxHp);
	stmt.CDatabaseStatement::BindNumberColumn(16, &charinfo.m_nSp);
	stmt.CDatabaseStatement::BindNumberColumn(17, &charinfo.m_nMaxSp);
	stmt.CDatabaseStatement::BindNumberColumn(18, &charinfo.m_nAID);
	stmt.CDatabaseStatement::BindStringColumn(19, charinfo.m_szMapName, 16);
	stmt.CDatabaseStatement::BindNumberColumn(20, &charinfo.m_nXPos);
	stmt.CDatabaseStatement::BindNumberColumn(21, &charinfo.m_nYPos);
	stmt.CDatabaseStatement::BindNumberColumn(22, &charinfo.m_nGuildID);
	stmt.CDatabaseStatement::BindNumberColumn(23, &charinfo.m_nSlotIndex);
	stmt.CDatabaseStatement::BindNumberColumn(24, &charinfo.m_nSpeed);
	stmt.CDatabaseStatement::BindNumberColumn(25, &charinfo.m_nMoney);
	stmt.CDatabaseStatement::BindNumberColumn(26, &charinfo.m_nJobExp);
	stmt.CDatabaseStatement::BindNumberColumn(27, &charinfo.m_nVirtue);
	stmt.CDatabaseStatement::BindNumberColumn(28, &charinfo.m_nHonor);
	stmt.CDatabaseStatement::BindNumberColumn(29, &charinfo.m_nHairColor);
	stmt.CDatabaseStatement::BindNumberColumn(30, &charinfo.m_nJobLevel);
	stmt.CDatabaseStatement::BindNumberColumn(31, &charinfo.m_nBodyState);
	stmt.CDatabaseStatement::BindNumberColumn(32, &charinfo.m_nHealthState);
	stmt.CDatabaseStatement::BindNumberColumn(33, &charinfo.m_nSxPos);
	stmt.CDatabaseStatement::BindNumberColumn(34, &charinfo.m_nSyPos);
	stmt.CDatabaseStatement::BindStringColumn(35, charinfo.m_szRestartMapName, 16);
	stmt.CDatabaseStatement::BindNumberColumn(36, &charinfo.m_nEffectState);
	stmt.CDatabaseStatement::BindNumberColumn(37, &charinfo.m_nHead);
	stmt.CDatabaseStatement::BindNumberColumn(38, &charinfo.m_nWeapon);
	stmt.CDatabaseStatement::BindNumberColumn(39, &charinfo.m_nAccessory);
	stmt.CDatabaseStatement::BindNumberColumn(40, &charinfo.m_nHeadPalette);
	stmt.CDatabaseStatement::BindNumberColumn(41, &charinfo.m_nBodyPalette);
	stmt.CDatabaseStatement::BindNumberColumn(42, &charinfo.m_nAccessory2);
	stmt.CDatabaseStatement::BindNumberColumn(43, &charinfo.m_nAccessory3);
	stmt.CDatabaseStatement::BindNumberColumn(44, &charinfo.m_nShield);
	stmt.CDatabaseStatement::BindNumberColumn(45, &charinfo.m_nRobe);

	int nCount;
	for( nCount = 0; nCount < nMaxCharInfoCount; ++nCount )
	{
		memset(&charinfo, 0, sizeof(charinfo));

		SQLRETURN sqlResult = stmt.CDatabaseStatement::Fetch();
		if( !SQL_SUCCEEDED(sqlResult) )
		{
			if( sqlResult != SQL_NO_DATA )
				stmt.CDatabaseStatement::ErrLog();

			break;
		}

		charinfo.m_bIsChangedCharName = 1;
		memcpy(&pCharInfo[nCount], &charinfo, sizeof(charinfo));
	}

	if( !bTranslateOpt )
		this->CDatabase::SetTranslateOption(true);

	stmt.CDatabaseStatement::Release(); // [patch] thread-safe sql
	m_csCharacterDB.Leave();
	return min(nCount, nMaxCharInfoCount);
}


BOOL CCharacterDBBase::DeleteCharInfo(int nGID)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	result = stmt.CDatabaseStatement::Query("{call DeleteCharInfo(%d)}", nGID);

	m_csCharacterDB.Leave();
	return result;
}


////////////////////////////////////////


/// singleton instance
static CCharacterDB g_CharacterDB;
CCharacterDB* CSingleton<CCharacterDB>::ms_Singleton;


CCharacterDB::CCharacterDB()
: CCharacterDBBase("character.dsn")
{
}


bool CCharacterDB::IsUsingCharacterPassword()
{
	bool result = false;

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("EXEC sp_columns @table_name = charinfo, @column_name  = CharPassword");

	while( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = true;

	return result;
}


bool CCharacterDB::CheckCharacterPassword(const int iGID, const int iCharacterPassword)
{
	bool result = false;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call CheckCharacterPassword( %d, %d )}", iGID, iCharacterPassword);

	int iRetValue = 0;
	stmt.CDatabaseStatement::BindNumberColumn(1, &iRetValue);

	stmt.CDatabaseStatement::Fetch();

	m_csCharacterDB.Leave();

	result = ( iCharacterPassword == -1 && iRetValue == 1 || iRetValue > 0 );

	return result;
}


bool CCharacterDB::UpdateCharacterPassword(const int iGID, const int iOldPassword, const int iNewPassword)
{
	bool result = false;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call UpdateCharacterPassword( %d, %d, %d )}", iGID, iOldPassword, iNewPassword);

	int iRetValue = 0;
	stmt.CDatabaseStatement::BindNumberColumn(1, &iRetValue);

	stmt.CDatabaseStatement::Fetch();

	m_csCharacterDB.Leave();

	result = ( iRetValue > 0 );

	return result;
}



BOOL CCharacterDB::MakeCharInfo(SCHARINFO* pCharInfo)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	result = stmt.CDatabaseStatement::Query(
		"{ ?= call MakeCharInfo(%s, %d, %d, %d, %d, %d, %d, %d, %s, %d, %d, %d, %d, %d, %s, %d, %d)}",
		pCharInfo->m_szName,
		pCharInfo->m_nStr,
		pCharInfo->m_nAgi,
		pCharInfo->m_nVit,
		pCharInfo->m_nInt,
		pCharInfo->m_nDex,
		pCharInfo->m_nLuk,
		pCharInfo->m_nAID,
		pCharInfo->m_szMapName,
		pCharInfo->m_nXPos,
		pCharInfo->m_nYPos,
		pCharInfo->m_nSlotIndex,
		pCharInfo->m_nSxPos,
		pCharInfo->m_nSyPos,
		pCharInfo->m_szRestartMapName,
		pCharInfo->m_nHead,
		pCharInfo->m_nHeadPalette);

	m_csCharacterDB.Leave();
	result = ( result > 0 ); //NOTE: does nothing, the result of Query() has already had this check applied inside
	return result;
}


int CCharacterDB::DeleteGroupMember(int nGID)
{
	int nResult;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call DeleteMember(%d)}", nGID);

	nResult = 0;
	stmt.CDatabaseStatement::BindNumberColumn(1, &nResult);

	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		nResult = 0;

	m_csCharacterDB.Leave();
	return nResult;
}


int CCharacterDB::GetGroupMemberCount(int nGRID)
{
	int nCount;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetGroupSize(%d)}", nGRID);

	nCount = 0;
	stmt.CDatabaseStatement::BindNumberColumn(1, &nCount);

	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		nCount = 0;

	m_csCharacterDB.Leave();
	return nCount;
}


int CCharacterDB::GetGroupID(int nGID)
{
	int nGRID;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetMember(%d)}", nGID);

	nGRID = 0;
	stmt.CDatabaseStatement::BindNumberColumn(1, &nGRID);

	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		nGRID = 0;

	m_csCharacterDB.Leave();
	return nGRID;
}


void CCharacterDB::DeleteGroup(int nGRID)
{
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call DeleteGroup(%d)}", nGRID);

	m_csCharacterDB.Leave();
}


BOOL CCharacterDB::GetGuildMemberPositionID(int nGID, int* PositionID)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetGuildMemberPositionID(%d)}", nGID);

	stmt.CDatabaseStatement::BindNumberColumn(1, PositionID);

	result = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = FALSE;

	m_csCharacterDB.Leave();
	return result;
}


BOOL CCharacterDB::GetGuildIDByGID(int nGID, int* GDID)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetGuildIDByGID(%d)}", nGID);

	stmt.CDatabaseStatement::BindNumberColumn(1, GDID);

	result = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = FALSE;

	m_csCharacterDB.Leave();
	return result;
}


void CCharacterDB::DeleteGuildMInfo(int nGDID)
{
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call DeleteGuildMInfo(%d)}", nGDID);

	m_csCharacterDB.Leave();
}


void CCharacterDB::DelegateGuildMaster(int nGDID)
{
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("update GuildMInfo with (rowlock) set PositionID = 0 where GID = ( select top 1 GID from GuildMInfo where GDID=%d ORDER BY PositionID)", nGDID);

	m_csCharacterDB.Leave();
}


void CCharacterDB::UpdateCharStartMap(int nGID)
{
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call UpdateCharStartMap(%d)}", nGID);

	m_csCharacterDB.Leave();
}


BOOL CCharacterDB::GetCharInfoByGID(int nGID, SCHARINFO* pCharinfo)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetCharInfoByGID(%d)}", nGID);

	SCHARINFO charinfo;
	stmt.CDatabaseStatement::BindNumberColumn( 1, &charinfo.m_nGID);
	stmt.CDatabaseStatement::BindStringColumn( 2, charinfo.m_szName, 24);
	stmt.CDatabaseStatement::BindNumberColumn( 3, &charinfo.m_nJob);
	stmt.CDatabaseStatement::BindNumberColumn( 4, &charinfo.m_nCLevel);
	stmt.CDatabaseStatement::BindNumberColumn( 5, &charinfo.m_nSpPoint);
	stmt.CDatabaseStatement::BindNumberColumn( 6, &charinfo.m_nExp);
	stmt.CDatabaseStatement::BindNumberColumn( 7, &charinfo.m_nJobPoint);
	stmt.CDatabaseStatement::BindNumberColumn( 8, &charinfo.m_nStr);
	stmt.CDatabaseStatement::BindNumberColumn( 9, &charinfo.m_nAgi);
	stmt.CDatabaseStatement::BindNumberColumn(10, &charinfo.m_nVit);
	stmt.CDatabaseStatement::BindNumberColumn(11, &charinfo.m_nInt);
	stmt.CDatabaseStatement::BindNumberColumn(12, &charinfo.m_nDex);
	stmt.CDatabaseStatement::BindNumberColumn(13, &charinfo.m_nLuk);
	stmt.CDatabaseStatement::BindNumberColumn(14, &charinfo.m_nHp);
	stmt.CDatabaseStatement::BindNumberColumn(15, &charinfo.m_nMaxHp);
	stmt.CDatabaseStatement::BindNumberColumn(16, &charinfo.m_nSp);
	stmt.CDatabaseStatement::BindNumberColumn(17, &charinfo.m_nMaxSp);
	stmt.CDatabaseStatement::BindNumberColumn(18, &charinfo.m_nAID);
	stmt.CDatabaseStatement::BindStringColumn(19, charinfo.m_szMapName, 16);
	stmt.CDatabaseStatement::BindNumberColumn(20, &charinfo.m_nXPos);
	stmt.CDatabaseStatement::BindNumberColumn(21, &charinfo.m_nYPos);
	stmt.CDatabaseStatement::BindNumberColumn(22, &charinfo.m_nGuildID);
	stmt.CDatabaseStatement::BindNumberColumn(23, &charinfo.m_nSlotIndex);
	stmt.CDatabaseStatement::BindNumberColumn(24, &charinfo.m_nSpeed);
	stmt.CDatabaseStatement::BindNumberColumn(25, &charinfo.m_nMoney);
	stmt.CDatabaseStatement::BindNumberColumn(26, &charinfo.m_nJobExp);
	stmt.CDatabaseStatement::BindNumberColumn(27, &charinfo.m_nVirtue);
	stmt.CDatabaseStatement::BindNumberColumn(28, &charinfo.m_nHonor);
	stmt.CDatabaseStatement::BindNumberColumn(29, &charinfo.m_nHairColor);
	stmt.CDatabaseStatement::BindNumberColumn(30, &charinfo.m_nJobLevel);
	stmt.CDatabaseStatement::BindNumberColumn(31, &charinfo.m_nBodyState);
	stmt.CDatabaseStatement::BindNumberColumn(32, &charinfo.m_nHealthState);
	stmt.CDatabaseStatement::BindNumberColumn(33, &charinfo.m_nSxPos);
	stmt.CDatabaseStatement::BindNumberColumn(34, &charinfo.m_nSyPos);
	stmt.CDatabaseStatement::BindStringColumn(35, charinfo.m_szRestartMapName, 16);
	stmt.CDatabaseStatement::BindNumberColumn(36, &charinfo.m_nEffectState);
	stmt.CDatabaseStatement::BindNumberColumn(37, &charinfo.m_nHead);
	stmt.CDatabaseStatement::BindNumberColumn(38, &charinfo.m_nWeapon);
	stmt.CDatabaseStatement::BindNumberColumn(39, &charinfo.m_nAccessory);
	stmt.CDatabaseStatement::BindNumberColumn(40, &charinfo.m_nHeadPalette);
	stmt.CDatabaseStatement::BindNumberColumn(41, &charinfo.m_nBodyPalette);
	stmt.CDatabaseStatement::BindNumberColumn(42, &charinfo.m_nAccessory2);
	stmt.CDatabaseStatement::BindNumberColumn(43, &charinfo.m_nAccessory3);
	stmt.CDatabaseStatement::BindNumberColumn(44, &charinfo.m_nShield);

	result = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = FALSE;

	m_csCharacterDB.Leave();

	if( result == TRUE )
		memcpy(pCharinfo, &charinfo, sizeof(charinfo));

	return result;
}


BOOL CCharacterDB::GetSkill(int nGID, char* skillInfo, SQLINTEGER* outSkillSize)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetSkill(%d)}", nGID);

	stmt.CDatabaseStatement::BindBinaryColumn(1, skillInfo, 256, outSkillSize);

	result = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = FALSE;

	m_csCharacterDB.Leave();
	return result;
}


BOOL CCharacterDB::GetItem(int nGID, char* itemInfo, SQLINTEGER* outSkillSize)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetItemInBody(%d)}", nGID);

	stmt.CDatabaseStatement::BindBinaryColumn(1, itemInfo, 4000, outSkillSize);

	result = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = FALSE;

	m_csCharacterDB.Leave();
	return result;
}


void CCharacterDB::SetOnline(bool isOnline, int iAID, int iGID) /// @custom // [patch] update 'isonline' column
{
	if( isOnline == true && iGID == 0 )
		return; // reject nonsense

	char Q[100];
	int p = 0;
	if( isOnline == true )
		p += sprintf(&Q[p], "UPDATE charinfo SET isonline = %d, lasttime = GETDATE() WHERE 1=1", isOnline);
	else
		p += sprintf(&Q[p], "UPDATE charinfo SET isonline = %d WHERE 1=1", isOnline);
	if( iAID != 0 ) p += sprintf(&Q[p], " AND AID = %d", iAID);
	if( iGID != 0 ) p += sprintf(&Q[p], " AND GID = %d", iGID);

	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query(Q);

	stmt.CDatabaseStatement::Release(); // [patch] thread-safe sql
	m_csCharacterDB.Leave();
}


////////////////////////////////////////


/// singleton instance
static CPVPCharacterDB g_CPVPCharacterDB;
CPVPCharacterDB* CSingleton<CPVPCharacterDB>::ms_Singleton;


CPVPCharacterDB::CPVPCharacterDB()
: CCharacterDBBase("pvpcharacter.dsn")
{
}


void CPVPCharacterDB::MakeSkill(int nGID, char* skillInfo, long SkillSize)
{
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	CDatabaseStatement stmt2(this);
	stmt.CDatabaseStatement::Query("{call InsertSKill(%d)}", nGID);
	stmt2.CDatabaseStatement::Query("{call UpdateSkill(%b, %d)}", skillInfo, SkillSize, nGID);

	m_csCharacterDB.Leave();
}


void CPVPCharacterDB::MakeItem(int nGID, char* itemInfo, long ItemSize)
{
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	CDatabaseStatement stmt2(this);
	stmt.CDatabaseStatement::Query("{call InsertItem(%d)}", nGID);
	stmt.CDatabaseStatement::Query("{call UpdateItemBody(%b, %d)}", itemInfo, ItemSize, nGID);

	m_csCharacterDB.Leave();
}


BOOL CPVPCharacterDB::CopyCharInfo(SCHARINFO* pCharInfo)
{
	BOOL result;
	m_csCharacterDB.Enter();

	CDatabaseStatement stmt(this);
	result = stmt.CDatabaseStatement::Query(
		"{call CopyCharInfo(%s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d)}",
		pCharInfo->m_szName,
		pCharInfo->m_nJob,
		pCharInfo->m_nCLevel,
		pCharInfo->m_nSpPoint,
		pCharInfo->m_nExp,
		pCharInfo->m_nJobPoint,
		pCharInfo->m_nStr,
		pCharInfo->m_nAgi,
		pCharInfo->m_nVit,
		pCharInfo->m_nInt,
		pCharInfo->m_nDex,
		pCharInfo->m_nLuk,
		pCharInfo->m_nHp,
		pCharInfo->m_nMaxHp,
		pCharInfo->m_nSp,
		pCharInfo->m_nMaxSp,
		pCharInfo->m_nAID,
		pCharInfo->m_szMapName,
		pCharInfo->m_nXPos,
		pCharInfo->m_nYPos,
		0,
		pCharInfo->m_nSpeed,
		pCharInfo->m_nMoney,
		pCharInfo->m_nJobExp,
		pCharInfo->m_nVirtue,
		pCharInfo->m_nHonor,
		pCharInfo->m_nHairColor,
		pCharInfo->m_nJobLevel,
		pCharInfo->m_nBodyState,
		pCharInfo->m_nHealthState,
		pCharInfo->m_nSxPos,
		pCharInfo->m_nSyPos,
		pCharInfo->m_szRestartMapName,
		pCharInfo->m_nEffectState,
		pCharInfo->m_nHead,
		pCharInfo->m_nWeapon,
		pCharInfo->m_nAccessory,
		pCharInfo->m_nHeadPalette,
		pCharInfo->m_nBodyPalette,
		pCharInfo->m_nAccessory2,
		pCharInfo->m_nAccessory3,
		pCharInfo->m_nShield);

	m_csCharacterDB.Leave();
	return result;
}


////////////////////////////////////////


/// singleton instance
static CPvPPointDB g_PointDB;
CPvPPointDB* CSingleton<CPvPPointDB>::ms_Singleton;
const std::string CPvPPointDB::m_strFileDSNfileName = "pvppoint.dsn";


BOOL CPvPPointDB::InitPoint(unsigned long AID, const char* newCharName)
{
	BOOL result;
	m_CS.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call InitPoint(%d,%s)}", AID, newCharName);

	char oldCharName[25];
	stmt.CDatabaseStatement::BindStringColumn(1, oldCharName, 25);

	result = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = FALSE;

	m_CS.Leave();
	return result;
}


void CPvPPointDB::SetPwd(const char* in_szPwd)
{
	m_strPwd = in_szPwd;
}


bool CPvPPointDB::Connect()
{
	return this->CDatabase::Connect(m_strFileDSNfileName.c_str(), m_strPwd.c_str());
}


////////////////////////////////////////
