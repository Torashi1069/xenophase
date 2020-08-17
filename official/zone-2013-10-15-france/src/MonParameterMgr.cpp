#include "FSMMgr.h"
#include "ITPMgr.h"
#include "Path.h"
#include "MonParameterMgr.h"
#include "ZoneProcess.h"
#include "shared/NCriticalErrorLog.h"


CMonParameterMgr::CMonParameterMgr()
{
}


CMonParameterMgr::~CMonParameterMgr()
{
	this->CMonParameterMgr::Destroy();
}


void CMonParameterMgr::Init(const char* Script)
{
	this->CODBC::Init(Script, g_GlobaldbPWD);

	this->CMonParameterMgr::Destroy();

	this->CMonsterParameterTable::SetTable();

	if( !this->CMonParameterMgr::LoadMonParameter() )
		MessageBoxA(NULL, "LoadMonParameter()", "ERROR", MB_OK);

	this->CMonParameterMgr::LoadMonMakingItem();

	if( g_isEventMonsterOn )
	{
		this->CMonParameterMgr::LoadEventMonParameter();
		this->CMonParameterMgr::LoadEventMonMakingItem();
	}

	this->CODBC::Reset();

	this->CMonParameterMgr::LoadSpawnInfo();
}


void CMonParameterMgr::AddMonParameter(unsigned long spriteType, MONPARAMETER* parameter)
{
	m_parameter[spriteType] = parameter;
}


int CMonParameterMgr::GetJob(const char* in_szpMonName) const
{
	std::map<std::string,unsigned long>::const_iterator iter = m_mobName.find(in_szpMonName);
	if( iter == m_mobName.end() )
		return -1;

	return iter->second;
}


unsigned long CMonParameterMgr::SearchKeyword(const char* keyword)
{
	std::map<std::string,unsigned long>::const_iterator iter = m_spriteName.find(keyword);
	if( iter == m_spriteName.end() )
		return -1;

	return iter->second;
}


void CMonParameterMgr::Destroy()
{
	for( std::map<unsigned long,MONPARAMETER*>::iterator iter = m_parameter.begin(); iter != m_parameter.end(); iter = m_parameter.erase(iter) )
		delete iter->second;

	this->CMonsterParameterTable::Clear();
}


MONPARAMETER* CMonParameterMgr::GetMonParameter(unsigned long spriteType)
{
	std::map<unsigned long,MONPARAMETER*>::iterator iter = m_parameter.find(spriteType);
	if( iter == m_parameter.end() )
		return NULL;

	return iter->second;
}


namespace {
class MySTMTHandler
{
public:
	const bool isOK() const
	{
		return m_bOK;
	}

	MySTMTHandler(SQLHDBC in_hDBC) : m_hSTMT(SQL_NULL_HSTMT), m_bOK(false)
	{
		if( SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, in_hDBC, &m_hSTMT)) )
			m_bOK = true;
	}

	~MySTMTHandler()
	{
		if( m_hSTMT != SQL_NULL_HSTMT )
		{
			SQLCloseCursor(m_hSTMT);
			SQLFreeHandle(SQL_HANDLE_STMT, m_hSTMT);
			m_hSTMT = SQL_NULL_HSTMT;
		}
	}

public:
	operator SQLHSTMT()
	{
		return m_hSTMT;
	}

	SQLRETURN ExecDirect(const std::string in_Query)
	{
		return SQLExecDirectA(m_hSTMT, (SQLCHAR*)in_Query.c_str(), SQL_NTS);
	}

	SQLRETURN BindCol(SQLUSMALLINT in_ColumnNumber, SQLSMALLINT in_TargetType, SQLPOINTER in_TargetValue, SQLINTEGER in_BufferLength, SQLINTEGER* in_StrLen_or_Ind)
	{
		return SQLBindCol(m_hSTMT, in_ColumnNumber, in_TargetType, in_TargetValue, in_BufferLength, in_StrLen_or_Ind);
	}

	SQLRETURN Fetch()
	{
		return SQLFetch(m_hSTMT);
	}

private:
	/* this+0 */ SQLHSTMT m_hSTMT;
	/* this+4 */ bool m_bOK;
};
}; // namespace


bool CMonParameterMgr::LoadMonParameter()
{
	MySTMTHandler Handler(m_hdbc);
	if( !Handler.MySTMTHandler::isOK() )
		return false;

	SQLRETURN ret = Handler.ExecDirect("{call usp_getmonparameter}");
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "SQLExecDirect()");
		return false;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	MONPARAMETER par;
	Handler.BindCol( 1, SQL_C_CHAR,  par.name, sizeof(par.name), &cbChar);
	Handler.BindCol( 2, SQL_C_SLONG, &par.aRan, 0, &cbInt);
	Handler.BindCol( 3, SQL_C_SLONG, &par.LV, 0, &cbInt);
	Handler.BindCol( 4, SQL_C_SLONG, &par.HP, 0, &cbInt);
	Handler.BindCol( 5, SQL_C_SLONG, &par.SP, 0, &cbInt);
	Handler.BindCol( 6, SQL_C_SLONG, &par.str, 0, &cbInt);
	Handler.BindCol( 7, SQL_C_SLONG, &par.Int, 0, &cbInt);
	Handler.BindCol( 8, SQL_C_SLONG, &par.vit, 0, &cbInt);
	Handler.BindCol( 9, SQL_C_SLONG, &par.dex, 0, &cbInt);
	Handler.BindCol(10, SQL_C_SLONG, &par.agi, 0, &cbInt);
	Handler.BindCol(11, SQL_C_SLONG, &par.luk, 0, &cbInt);
	Handler.BindCol(12, SQL_C_SLONG, &par.atk1, 0, &cbInt);
	Handler.BindCol(13, SQL_C_SLONG, &par.atk2, 0, &cbInt);
	Handler.BindCol(14, SQL_C_SLONG, &par.def, 0, &cbInt);
	Handler.BindCol(15, SQL_C_SLONG, &par.exp, 0, &cbInt);
	Handler.BindCol(16, SQL_C_SLONG, &par.jexp, 0, &cbInt);
	Handler.BindCol(17, SQL_C_SLONG, &par.inc, 0, &cbInt);
	Handler.BindCol(18, SQL_C_SLONG, &par.as, 0, &cbInt);
	Handler.BindCol(19, SQL_C_SLONG, &par.es, 0, &cbInt);
	Handler.BindCol(20, SQL_C_SLONG, &par.mSpeed, 0, &cbInt);
	Handler.BindCol(21, SQL_C_SLONG, &par.rechargeTime, 0, &cbInt);
	Handler.BindCol(22, SQL_C_SLONG, &par.attackedMT, 0, &cbInt);
	Handler.BindCol(23, SQL_C_SLONG, &par.attackMT, 0, &cbInt);
	Handler.BindCol(24, SQL_C_SLONG, &par.property, 0, &cbInt);
	Handler.BindCol(25, SQL_C_SLONG, &par.scale, 0, &cbInt);
	Handler.BindCol(26, SQL_C_SLONG, &par._class, 0, &cbInt);
	Handler.BindCol(27, SQL_C_SLONG, &par.race, 0, &cbInt);
	Handler.BindCol(28, SQL_C_SLONG, &par.mdef, 0, &cbInt);
	Handler.BindCol(29, SQL_C_SLONG, &par.attr, 0, &cbInt);

	for( ; ; )
	{
		memset(&par, 0, sizeof(par));

		SQLRETURN ret = Handler.Fetch();
		if( ret == SQL_NO_DATA )
			break;

		if( !SQL_SUCCEEDED(ret) )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Fetch()");
			return false;
		}

		par.name[countof(par.name)-1] = '\0';

		unsigned long nKeyWord = this->CMonParameterMgr::SearchKeyword(par.name);
		if( nKeyWord == -1 )
			continue;

		std::auto_ptr<MONPARAMETER> MonParamterPtr(new MONPARAMETER());
		if( MonParamterPtr.get() == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "new MONPARAMETER()");
			return false;
		}

		if( !m_parameter.insert(std::pair<const unsigned long,MONPARAMETER*>(nKeyWord, MonParamterPtr.get())).second )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "LoadMonParameter duplicate: %d", nKeyWord);
			return false;
		}

		MonParamterPtr.release();
	}

	return true;
}


void CMonParameterMgr::LoadMonMakingItem()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call Getmonmakingitem}", SQL_NTS);

	char name[25];
	struct TEMP_MONITEMINFO { MONITEMINFO item[8]; } item;
	SQLBindCol(m_hstmt,  1, SQL_C_CHAR,  name, sizeof(name), &cbChar);
	SQLBindCol(m_hstmt,  2, SQL_C_CHAR,  &item.item[0].name, sizeof(item.item[0].name), &cbChar);
	SQLBindCol(m_hstmt,  3, SQL_C_SLONG, &item.item[0].percent, 0, &cbInt);
	SQLBindCol(m_hstmt,  4, SQL_C_CHAR,  &item.item[1].name, sizeof(item.item[1].name), &cbChar);
	SQLBindCol(m_hstmt,  5, SQL_C_SLONG, &item.item[1].percent, 0, &cbInt);
	SQLBindCol(m_hstmt,  6, SQL_C_CHAR,  &item.item[2].name, sizeof(item.item[2].name), &cbChar);
	SQLBindCol(m_hstmt,  7, SQL_C_SLONG, &item.item[2].percent, 0, &cbInt);
	SQLBindCol(m_hstmt,  8, SQL_C_CHAR,  &item.item[3].name, sizeof(item.item[3].name), &cbChar);
	SQLBindCol(m_hstmt,  9, SQL_C_SLONG, &item.item[3].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 10, SQL_C_CHAR,  &item.item[4].name, sizeof(item.item[4].name), &cbChar);
	SQLBindCol(m_hstmt, 11, SQL_C_SLONG, &item.item[4].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 12, SQL_C_CHAR,  &item.item[5].name, sizeof(item.item[5].name), &cbChar);
	SQLBindCol(m_hstmt, 13, SQL_C_SLONG, &item.item[5].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 14, SQL_C_CHAR,  &item.item[6].name, sizeof(item.item[6].name), &cbChar);
	SQLBindCol(m_hstmt, 15, SQL_C_SLONG, &item.item[6].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 16, SQL_C_CHAR,  &item.item[7].name, sizeof(item.item[7].name), &cbChar);
	SQLBindCol(m_hstmt, 17, SQL_C_SLONG, &item.item[7].percent, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		unsigned long nKeyWord = this->CMonParameterMgr::SearchKeyword(name);

		std::map<unsigned long,MONPARAMETER*>::iterator iter = m_parameter.find(nKeyWord);
		if( iter == m_parameter.end() )
			continue;

		for( int i = 0; i < countof(item.item); ++i )
		{
			iter->second->itemInfo[i].ITID = 0;
			iter->second->itemInfo[i].percent = 0;

			unsigned short ITID = g_itpMgr.CITPMgr::GetITID(item.item[i].name);
			if( ITID < 500 )
			{
				char buffer[260] = {};
				sprintf_s(buffer, countof(buffer), "monster[%s] drop unregistered item[%s] ", name, item.item[i].name);
				MessageBoxA(NULL, buffer, "database monmakingitem error", MB_OK);
				continue;
			}

			iter->second->itemInfo[i].ITID = ITID;
			iter->second->itemInfo[i].percent = item.item[i].percent;
		}
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


MONSPAWN_SETINFO* CMonParameterMgr::GetMonSpawnInfo(unsigned long spriteType)
{
	std::map<unsigned long,MONSPAWN_SETINFO>::iterator iter = m_spawnSetData.find(spriteType);
	if( iter == m_spawnSetData.end() )
		return NULL;

	return &iter->second;
}


void CMonParameterMgr::LoadSpawnInfo()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("SpawnSetInfo.scp"), "r");
	if( fp == NULL )
		return;

	int date;
	fscanf(fp, "%d\n", &date);

	if( date != 20020627 )
		MessageBoxA(NULL, "spawnsetinfo.scp old version?", "error", MB_OK);

	for( ; ; )
	{
		char buf[1024];
		fgets(buf, countof(buf), fp);

		if( strstr(buf, "//") != NULL || strlen(buf) < 5 )
			continue;

		if( feof(fp) )
			break;

		char masterName[24];
		char slaveName[24];
		char npcTypeName[24];
		int count;
		sscanf(buf, "%s%s%s%d", masterName, slaveName, npcTypeName, &count);

		unsigned long nKeyWord = this->CMonParameterMgr::SearchKeyword(masterName);

		MONSPAWN_SETINFO info;
		info.spriteType = this->CMonParameterMgr::SearchKeyword(slaveName);
		info.npcType = g_fsmMgr.CFSMMgr::GetKeyWord(npcTypeName);
		info.count = count;

		if( count < 1 || count > 15 )
			info.count = 3;

		MONSPAWN_SETINFO& set = m_spawnSetData[nKeyWord];
		set.spriteType = info.spriteType;
		set.npcType = info.npcType;
		set.count = info.count;
	}

	fclose(fp);
}


const char* CMonParameterMgr::GetMonsterName(unsigned long spriteType)
{
	MONPARAMETER* p = this->CMonParameterMgr::GetMonParameter(spriteType);
	if( p == NULL )
		return NULL;

	return p->name;
}


int CMonParameterMgr::GetMonsterType(unsigned long spriteType)
{
	MONPARAMETER* p = this->CMonParameterMgr::GetMonParameter(spriteType);
	if( p == NULL )
		return -1;

	return p->aiType;
}


bool CMonParameterMgr::SetMonsterNameAndAIType(unsigned long spriteType, const char* name, int aiType)
{
	if( name == NULL )
		return false;

	std::map<unsigned long,MONPARAMETER*>::iterator iter = m_parameter.find(spriteType);
	if( iter == m_parameter.end() )
		return false;
	
	MONPARAMETER* p = iter->second;
	if( p == NULL )
		return false;
	
	memcpy(p->name, name, sizeof(p->name));
	p->aiType = aiType;
	p->name[countof(p->name)-1] = '\0';
	return true;
}


void CMonParameterMgr::LoadEventMonParameter()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		MessageBoxA(NULL, "LoadEventMonParameter() SQL Failed", "DB error", MB_OK);
		return;
	}

	char name[24] = {};
	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetEventMonParameter}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	}

	MONPARAMETER par;
	SQLBindCol(m_hstmt,  1, SQL_C_CHAR, name, sizeof(name), &cbChar);
	SQLBindCol(m_hstmt,  2, SQL_C_CHAR, par.name, sizeof(par.name), &cbChar);
	SQLBindCol(m_hstmt,  3, SQL_C_SLONG, &par.aiType, 0, &cbInt);
	SQLBindCol(m_hstmt,  4, SQL_C_SLONG, &par, 0, &cbInt);
	SQLBindCol(m_hstmt,  5, SQL_C_SLONG, &par.LV, 0, &cbInt);
	SQLBindCol(m_hstmt,  6, SQL_C_SLONG, &par.HP, 0, &cbInt);
	SQLBindCol(m_hstmt,  7, SQL_C_SLONG, &par.SP, 0, &cbInt);
	SQLBindCol(m_hstmt,  8, SQL_C_SLONG, &par.str, 0, &cbInt);
	SQLBindCol(m_hstmt,  9, SQL_C_SLONG, &par.Int, 0, &cbInt);
	SQLBindCol(m_hstmt, 10, SQL_C_SLONG, &par.vit, 0, &cbInt);
	SQLBindCol(m_hstmt, 11, SQL_C_SLONG, &par.dex, 0, &cbInt);
	SQLBindCol(m_hstmt, 12, SQL_C_SLONG, &par.agi, 0, &cbInt);
	SQLBindCol(m_hstmt, 13, SQL_C_SLONG, &par.luk, 0, &cbInt);
	SQLBindCol(m_hstmt, 14, SQL_C_SLONG, &par.atk1, 0, &cbInt);
	SQLBindCol(m_hstmt, 15, SQL_C_SLONG, &par.atk2, 0, &cbInt);
	SQLBindCol(m_hstmt, 16, SQL_C_SLONG, &par.def, 0, &cbInt);
	SQLBindCol(m_hstmt, 17, SQL_C_SLONG, &par.exp, 0, &cbInt);
	SQLBindCol(m_hstmt, 18, SQL_C_SLONG, &par.jexp, 0, &cbInt);
	SQLBindCol(m_hstmt, 19, SQL_C_SLONG, &par.inc, 0, &cbInt);
	SQLBindCol(m_hstmt, 20, SQL_C_SLONG, &par.as, 0, &cbInt);
	SQLBindCol(m_hstmt, 21, SQL_C_SLONG, &par.es, 0, &cbInt);
	SQLBindCol(m_hstmt, 22, SQL_C_SLONG, &par.mSpeed, 0, &cbInt);
	SQLBindCol(m_hstmt, 23, SQL_C_SLONG, &par.rechargeTime, 0, &cbInt);
	SQLBindCol(m_hstmt, 24, SQL_C_SLONG, &par.attackedMT, 0, &cbInt);
	SQLBindCol(m_hstmt, 25, SQL_C_SLONG, &par.attackMT, 0, &cbInt);
	SQLBindCol(m_hstmt, 26, SQL_C_SLONG, &par.property, 0, &cbInt);
	SQLBindCol(m_hstmt, 27, SQL_C_SLONG, &par.scale, 0, &cbInt);
	SQLBindCol(m_hstmt, 28, SQL_C_SLONG, &par._class, 0, &cbInt);
	SQLBindCol(m_hstmt, 29, SQL_C_SLONG, &par.race, 0, &cbInt);
	SQLBindCol(m_hstmt, 30, SQL_C_SLONG, &par.mdef, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break; // done.

		unsigned long nKeyWord = this->CMonParameterMgr::SearchKeyword(name);
		if( nKeyWord == -1 )
			continue;

		MONPARAMETER* p = new MONPARAMETER;
		memcpy_s(p->name, sizeof(p->name), name, sizeof(name));
		memcpy_s(p->name, sizeof(p->name), par.name, sizeof(par.name));
		p->aiType = par.aiType + 5;
		p->aRan = par.aRan;
		p->LV = par.LV;
		p->HP = par.HP;
		p->SP = par.SP;
		p->str = par.str;
		p->Int = par.Int;
		p->vit = par.vit;
		p->dex = par.dex;
		p->agi = par.agi;
		p->luk = par.luk;
		p->atk1 = par.atk1;
		p->atk2 = par.atk2;
		p->def = par.def;
		p->exp = par.exp;
		p->jexp = par.jexp;
		p->inc = par.inc;
		p->as = par.as;
		p->es = par.es;
		p->rechargeTime = par.rechargeTime;
		p->attackedMT = par.attackedMT;
		p->mSpeed = par.mSpeed;
		p->attackMT = par.attackMT;
		p->property = par.property;
		p->scale = par.scale;
		p->_class = par._class;
		p->race = par.race;
		p->mdef = par.mdef;

		m_parameter[nKeyWord] = p;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


void CMonParameterMgr::LoadEventMonMakingItem()
{
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetEventMonMakingItem}", SQL_NTS);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	}

	char name[25];
	struct TEMP_MONITEMINFO { MONITEMINFO item[8]; } item;
	SQLBindCol(m_hstmt,  1, SQL_C_CHAR,  name, sizeof(name), &cbChar);
	SQLBindCol(m_hstmt,  2, SQL_C_CHAR,  &item.item[0].name, sizeof(item.item[0].name), &cbChar);
	SQLBindCol(m_hstmt,  3, SQL_C_SLONG, &item.item[0].percent, 0, &cbInt);
	SQLBindCol(m_hstmt,  4, SQL_C_CHAR,  &item.item[1].name, sizeof(item.item[1].name), &cbChar);
	SQLBindCol(m_hstmt,  5, SQL_C_SLONG, &item.item[1].percent, 0, &cbInt);
	SQLBindCol(m_hstmt,  6, SQL_C_CHAR,  &item.item[2].name, sizeof(item.item[2].name), &cbChar);
	SQLBindCol(m_hstmt,  7, SQL_C_SLONG, &item.item[2].percent, 0, &cbInt);
	SQLBindCol(m_hstmt,  8, SQL_C_CHAR,  &item.item[3].name, sizeof(item.item[3].name), &cbChar);
	SQLBindCol(m_hstmt,  9, SQL_C_SLONG, &item.item[3].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 10, SQL_C_CHAR,  &item.item[4].name, sizeof(item.item[4].name), &cbChar);
	SQLBindCol(m_hstmt, 11, SQL_C_SLONG, &item.item[4].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 12, SQL_C_CHAR,  &item.item[5].name, sizeof(item.item[5].name), &cbChar);
	SQLBindCol(m_hstmt, 13, SQL_C_SLONG, &item.item[5].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 14, SQL_C_CHAR,  &item.item[6].name, sizeof(item.item[6].name), &cbChar);
	SQLBindCol(m_hstmt, 15, SQL_C_SLONG, &item.item[6].percent, 0, &cbInt);
	SQLBindCol(m_hstmt, 16, SQL_C_CHAR,  &item.item[7].name, sizeof(item.item[7].name), &cbChar);
	SQLBindCol(m_hstmt, 17, SQL_C_SLONG, &item.item[7].percent, 0, &cbInt);

	for( ; ; )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break;

		unsigned long nKeyWord = this->CMonParameterMgr::SearchKeyword(name);

		std::map<unsigned long,MONPARAMETER*>::iterator iter = m_parameter.find(nKeyWord);
		if( iter == m_parameter.end() )
			continue;

		for( int i = 0; i < countof(item.item); ++i )
		{
			unsigned short ITID = g_itpMgr.CITPMgr::GetITID(item.item[i].name);
			if( ITID < 500 )
				continue;

			iter->second->itemInfo[i].ITID = ITID;
			iter->second->itemInfo[i].percent = item.item[i].percent;
		}
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}
