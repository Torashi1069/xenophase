#include "ExpParameter.h"
#include "Enum.h"
#include "Path.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"


CExpParameter::CExpParameter()
{
}


CExpParameter::~CExpParameter()
{
}


void CExpParameter::Init(const char* Script)
{
	this->CODBC::Init("script.dsn", g_GlobaldbPWD);
	this->CExpParameter::GetExpParameter();
	this->CExpParameter::GetNoviceExpParameter();
	this->CExpParameter::GetSecondExpParameter();
	this->CExpParameter::GetFirstJobExpParameter();
	this->CExpParameter::GetGuildExpParameter();
	this->CExpParameter::GetExpParameter2();
	this->CExpParameter::GetNoviceExpParameter2();
	this->CExpParameter::GetFirstJobExpParameter2();
	this->CExpParameter::GetSecondJobExpParameter2();
	this->CExpParameter::Get_Ninja_Gunner_JobExpParameter();
	this->CExpParameter::InitExpTable_Homun(const_cast<char*>(Script));
	this->CExpParameter::GetExpParameter3();
	this->CExpParameter::GetThirdJobExpParameter();
	this->CODBC::Reset();
}


void CExpParameter::GetExpParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call Getexp}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_expValue[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetNoviceExpParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetNoviceJobExp}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_jobNoviceExpValue[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetFirstJobExpParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetFirstJobExp}", -3);
	SQLBindCol(m_hstmt, 1u, -15, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2u, -16, &exp, 0, &cbInt);
	for ( m_retcode = SQLFetch(m_hstmt);
		m_retcode != 100;
		m_retcode = SQLFetch(m_hstmt) )
	{
		m_jobFirstJobExpValue[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetSecondExpParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetSecondJobExp}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_jobSecondExpValue[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetGuildExpParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildexp}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_guildexpValue[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


int CExpParameter::GetGuildNextExp(short level)
{
	if( level >= 99 )
		return 99999999;

	short nextLevel = level + 1;

	std::map<short,int>::const_iterator iter = m_guildexpValue.find(nextLevel);
	return( iter != m_guildexpValue.end() ) ? iter->second : 0;
}


int CExpParameter::GetNextJobExp(short level, short job)
{
	std::map<short,int>::const_iterator iter;
	short nextLevel = level + 1;

	switch( job )
	{
	case JT_NOVICE:
	case JT_NOVICE_B:
	{
		if( level >= 10 )
			return 999999999;

		iter = m_jobNoviceExpValue.find(nextLevel);
		return ( iter != m_jobNoviceExpValue.end() ) ? iter->second : 0;
	}
	break;
	case JT_SWORDMAN:
	case JT_SWORDMAN_B:
	case JT_MAGICIAN:
	case JT_MAGICIAN_B:
	case JT_ARCHER:
	case JT_ARCHER_B:
	case JT_ACOLYTE:
	case JT_ACOLYTE_B:
	case JT_MERCHANT:
	case JT_MERCHANT_B:
	case JT_THIEF:
	case JT_THIEF_B:
	{
		if( level >= 50 )
			return 999999999;

		iter = m_jobFirstJobExpValue.find(nextLevel);
		return ( iter != m_jobFirstJobExpValue.end() ) ? iter->second : 0;
	}
	break;
	case JT_SUPERNOVICE:
	case JT_SUPERNOVICE_B:
	{
		if( level >= 99 )
			return 999999999;

		iter = m_jobFirstJobExpValue.find(nextLevel);
		if( iter == m_jobFirstJobExpValue.end() )
		{// fallback?
			if( level < 50 )
				return 0;

			iter = m_jobFirstJobExpValue.find(49);
			if( iter == m_jobFirstJobExpValue.end() )
				return 0;

			return iter->second + 10000 * level;
		}

		return iter->second;
	}
	break;
	case JT_NOVICE_H:
	{
		if( level >= 10 )
			return 999999999;

		iter = m_jobNoviceExpValue2.find(nextLevel);
		return ( iter != m_jobNoviceExpValue2.end() ) ? iter->second : 0;
	}
	break;
	case JT_SWORDMAN_H:
	case JT_MAGICIAN_H:
	case JT_ARCHER_H:
	case JT_ACOLYTE_H:
	case JT_MERCHANT_H:
	case JT_THIEF_H:
	{
		if( level >= 50 )
			return 999999999;

		iter = m_jobFirstJobExpValue2.find(nextLevel);
		return ( iter != m_jobFirstJobExpValue2.end() ) ? iter->second : 0;
	}
	break;
	case JT_KNIGHT_H:
	case JT_PRIEST_H:
	case JT_WIZARD_H:
	case JT_BLACKSMITH_H:
	case JT_HUNTER_H:
	case JT_ASSASSIN_H:
	case JT_CRUSADER_H:
	case JT_MONK_H:
	case JT_SAGE_H:
	case JT_ROGUE_H:
	case JT_ALCHEMIST_H:
	case JT_BARD_H:
	case JT_DANCER_H:
	{
		if( level >= 70 )
			return 999999999;

		iter = m_jobSecondExpValue2.find(nextLevel);
		return ( iter != m_jobSecondExpValue2.end() ) ? iter->second : 0;
	}
	break;
	case JT_GUNSLINGER:
	case JT_NINJA:
	{
		if( level >= 70 )
			return 999999999;

		iter = m_job_Ninja_Gunner_ExpValue.find(nextLevel);
		return ( iter != m_job_Ninja_Gunner_ExpValue.end() ) ? iter->second : 0;
	}
	break;
	case JT_TAEKWON:
	{
		if( level >= 50 )
			return 999999999;

		iter = m_jobFirstJobExpValue.find(nextLevel);
		return ( iter != m_jobFirstJobExpValue.end() ) ? iter->second : 0;
	}
	break;
	case JT_STAR:
	{
		if( level >= 50 )
			return 999999999;

		if( nextLevel < 20 )
		{
			iter = m_jobSecondExpValue.find(20);
			return ( iter != m_jobSecondExpValue.end() ) ? iter->second : 0;
		}
		else
		{
			iter = m_jobSecondExpValue.find(nextLevel);
			return ( iter != m_jobSecondExpValue.end() ) ? 2 * iter->second : 0;
		}
	}
	break;
	default:
	{
		if( job >= JT_RUNE_KNIGHT && job <= JT_MADOGEAR_B )
		{
			if( level >= 50 )
				return 999999999;

			iter = m_thirdJobExpValue.find(nextLevel);
			return ( iter != m_thirdJobExpValue.end() ) ? iter->second : 0;
		}
		else
		if( job == JT_SUPERNOVICE2 || job == JT_SUPERNOVICE2_B )
		{
			if( level >= 50 )
				return 999999999;

			iter = m_thirdJobExpValue.find(nextLevel);
			return ( iter != m_thirdJobExpValue.end() ) ? iter->second : 0;
		}
		else
		{
			if( level >= 50 )
				return 999999999;

			iter = m_jobSecondExpValue.find(nextLevel);
			return ( iter != m_jobSecondExpValue.end() ) ? iter->second : 0;
		}
	}
	break;
	};
}


int CExpParameter::GetNextExp(const short in_level, const short in_job) const
{
	if( in_level >= GetMaxCharacterLevel(in_job) )
		return 99999999;

	short nextLevel = in_level + 1;

	if( in_job >= JT_RUNE_KNIGHT && in_job <= JT_MADOGEAR_B )
	{
		std::map<short,int>::const_iterator iter = m_expValue3.find(nextLevel);
		return ( iter == m_expValue3.end() ) ? iter->second : 0;
	}
	else
	if( in_job >= JT_SUPERNOVICE2 && in_job <= JT_SUPERNOVICE2_B )
	{
		std::map<short,int>::const_iterator iter = m_expValue3.find(nextLevel);
		return ( iter != m_expValue3.end() ) ? iter->second : 0;
	}
	else
	if( in_job >= JT_NOVICE_H && in_job <= JT_DANCER_H )
	{
		std::map<short,int>::const_iterator iter = m_expValue2.find(nextLevel);
		return ( iter != m_expValue2.end() ) ? iter->second : 0;
	}
	else
	{
		std::map<short,int>::const_iterator iter = m_expValue.find(nextLevel);
		return ( iter != m_expValue.end() ) ? iter->second : 0;
	}
}


void CExpParameter::GetExpParameter2()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call Getexp2}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_expValue2[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetNoviceExpParameter2()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetNoviceJobExp2}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_jobNoviceExpValue2[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetFirstJobExpParameter2()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetFirstJobExp2}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_jobFirstJobExpValue2[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::Get_Ninja_Gunner_JobExpParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetFirstJobExp3}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_job_Ninja_Gunner_ExpValue[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetSecondJobExpParameter2()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetSecondJobExp2}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_jobSecondExpValue2[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::InitExpTable_Homun(char* fileName)
{
	if( fileName == NULL )
		return;

	lua_State* L = lua_open();

	if( luaL_loadfile(L, g_pathData.CPathData::SetFileName("Homun.scp")) != 0 || lua_pcall(L, 0, 0, 0) != 0 )
	{
		char buf[256];
		sprintf_s(buf, countof(buf), "cannot run cofig file: %s", lua_tolstring(L, -1, NULL));
		MessageBoxA(NULL, buf, "void CExpParameter :: InitExpTable_Homun", MB_OK);
		lua_close(L);
		return;
	}

	lua_getfield(L, LUA_GLOBALSINDEX, "ExpTable");
	if( lua_type(L, -1) != LUA_TTABLE )
	{
		char buf[256];
		sprintf_s(buf, countof(buf), "'ExpTable' should be a table\n");
		MessageBoxA(NULL, buf, "void CExpParameter :: InitExpTable_Homun", MB_OK);
		lua_close(L);
		return;
	}

	for( int level = 1; level <= 150; ++level )
	{
		lua_pushnumber(L, (double)level);
		lua_gettable(L, -2);

		if( !lua_isnumber(L, -1) )
		{
			char buf[256];
			sprintf_s(buf, countof(buf), "ExpTable[%d] invalid\n", level);
			MessageBoxA(NULL, buf, "void CExpParameter :: InitExpTable_Homun", MB_OK);
			lua_close(L);
			return;
		}

		int exp = (int)lua_tonumber(L, -1);
		lua_settop(L, -2);

		m_expVal_Homun[level] = exp;
	}

	lua_close(L);
}


int CExpParameter::GetNextExp_Homun(const short in_Level, const int in_OwnerJob)
{
	short maxLevel = ( in_OwnerJob > JT_THIRDJOB_BEGIN && in_OwnerJob < JT_THIRDJOB_END ) ? 150 : 99;
	if( in_Level >= maxLevel )
		return 99999999;

	std::map<short,int>::iterator it = m_expVal_Homun.find(in_Level);
	if( it == m_expVal_Homun.end() )
		return 0;

	return it->second;
}


void CExpParameter::GetExpParameter3()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetExp3}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_expValue3[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CExpParameter::GetThirdJobExpParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	short level;
	int exp;
	SQLINTEGER cbInt = 0;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetThirdJobExp}", SQL_NTS);
	SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
	SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		m_thirdJobExpValue[level] = exp;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}
