#include "MonParameterMgr.h"
#include "shared.h"
#include <sql.h>
#include <sqlext.h>


CMonParameterMgr::CMonParameterMgr(void) // line 16-18
{
}


CMonParameterMgr::~CMonParameterMgr(void) // line 21-23
{
}


hook_method<void (CMonParameterMgr::*)(const char* Script)> CMonParameterMgr::_Init(SERVER, "CMonParameterMgr::Init");
void CMonParameterMgr::Init(const char* Script) // line 26-71
{
	return (this->*_Init)(Script);

	this->CMonParameterMgr::Destroy();

	this->CMonsterParameterTable::SetTable();
	this->CODBC::Init(Script, "script", g_GlobaldbPWD, Script, 0);

	this->CMonParameterMgr::LoadMonParameter();
	this->CMonParameterMgr::LoadMonMakingItem();

	if( g_isEventMonsterOn != 0 )
	{
		this->CMonParameterMgr::LoadEventMonParameter();
		this->CMonParameterMgr::LoadEventMonMakingItem();
	}

	this->CODBC::Reset();
	this->CMonParameterMgr::LoadSpawnInfo();
}


hook_method<unsigned long (CMonParameterMgr::*)(const char* keyword)> CMonParameterMgr::_SearchKeyword(SERVER, "CMonParameterMgr::SearchKeyword");
unsigned long CMonParameterMgr::SearchKeyword(const char* keyword) // line 125-132
{
	return (this->*_SearchKeyword)(keyword);

	mystd::map<mystd::string,unsigned long>::const_iterator it = m_spriteName.find(keyword);
	return ( it != m_spriteName.end() ) ? it->second : -1;
}


hook_method<MONPARAMETER* (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonParameter(SERVER, "CMonParameterMgr::GetMonParameter");
MONPARAMETER* CMonParameterMgr::GetMonParameter(unsigned long spriteType) // line 114-122
{
	return (this->*_GetMonParameter)(spriteType);

	mystd::map<unsigned long,MONPARAMETER*>::iterator it = m_parameter.find(spriteType);
	return ( it != m_parameter.end() ) ? it->second : NULL;
}


hook_method<MONSPAWN_SETINFO* (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonSpawnInfo(SERVER, "CMonParameterMgr::GetMonSpawnInfo");
MONSPAWN_SETINFO* CMonParameterMgr::GetMonSpawnInfo(unsigned long spriteType) // line 456-463
{
	return (this->*_GetMonSpawnInfo)(spriteType);

	mystd::map<unsigned long,MONSPAWN_SETINFO>::iterator it = m_spawnSetData.find(spriteType);
	return ( it != m_spawnSetData.end() ) ? &it->second : NULL;
}


hook_method<const char* (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonsterName(SERVER, "CMonParameterMgr::GetMonsterName");
const char* CMonParameterMgr::GetMonsterName(unsigned long spriteType) // line 515-529
{
	return (this->*_GetMonsterName)(spriteType);

	MONPARAMETER* mp = this->CMonParameterMgr::GetMonParameter(spriteType);
	return ( mp != NULL ) ? mp->name : NULL;
}


hook_method<int (CMonParameterMgr::*)(unsigned long spriteType)> CMonParameterMgr::_GetMonsterType(SERVER, "CMonParameterMgr::GetMonsterType");
int CMonParameterMgr::GetMonsterType(unsigned long spriteType) // line 537-551
{
	return (this->*_GetMonsterType)(spriteType);

	MONPARAMETER* mp = this->CMonParameterMgr::GetMonParameter(spriteType);
	return ( mp != NULL )? mp->aiType : -1;
}


hook_method<bool (CMonParameterMgr::*)(unsigned long spriteType, const char* name, int aiType)> CMonParameterMgr::_SetMonsterNameAndAIType(SERVER, "CMonParameterMgr::SetMonsterNameAndAIType");
bool CMonParameterMgr::SetMonsterNameAndAIType(unsigned long spriteType, const char* name, int aiType) // line 558-583
{
	return (this->*_SetMonsterNameAndAIType)(spriteType, name, aiType);

	if( name == NULL )
		return false;

	mystd::map<unsigned long,MONPARAMETER*>::iterator it = m_parameter.find(spriteType);
	if( it == m_parameter.end() )
		return false;

	MONPARAMETER* mp = it->second;
	if( mp == NULL )
		return false;

	memcpy(mp->name, name, sizeof(mp->name)); mp->name[countof(mp->name)-1] = '\0';
	mp->aiType = aiType;

	return true;
}


hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadSpawnInfo(SERVER, "CMonParameterMgr::LoadSpawnInfo");
void CMonParameterMgr::LoadSpawnInfo(void) // line 466-507
{
	return (this->*_LoadSpawnInfo)();

	//TODO
}


hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadMonParameter(SERVER, "CMonParameterMgr::LoadMonParameter");
void CMonParameterMgr::LoadMonParameter(void) // line 254-380
{
	return (this->*_LoadMonParameter)();

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		if( m_hstmt != NULL )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		MessageBoxA(NULL, "LoadMonParameter() SQL Failed", "DB error", MB_OK);
		return;
	}

	m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call Getmonparameter}", SQL_NTS);

	char name[24];
	MONPARAMETER par;
	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	SQLBindCol(m_hstmt,  1, SQL_C_CHAR,  name,             24, &cbChar);
	SQLBindCol(m_hstmt,  2, SQL_C_SLONG, &par.aRan,         0, &cbInt);
	SQLBindCol(m_hstmt,  3, SQL_C_SLONG, &par.LV,           0, &cbInt);
	SQLBindCol(m_hstmt,  4, SQL_C_SLONG, &par.HP,           0, &cbInt);
	SQLBindCol(m_hstmt,  5, SQL_C_SLONG, &par.SP,           0, &cbInt);
	SQLBindCol(m_hstmt,  6, SQL_C_SLONG, &par.str,          0, &cbInt);
	SQLBindCol(m_hstmt,  7, SQL_C_SLONG, &par.Int,          0, &cbInt);
	SQLBindCol(m_hstmt,  8, SQL_C_SLONG, &par.vit,          0, &cbInt);
	SQLBindCol(m_hstmt,  9, SQL_C_SLONG, &par.dex,          0, &cbInt);
	SQLBindCol(m_hstmt, 10, SQL_C_SLONG, &par.agi,          0, &cbInt);
	SQLBindCol(m_hstmt, 11, SQL_C_SLONG, &par.luk,          0, &cbInt);
	SQLBindCol(m_hstmt, 12, SQL_C_SLONG, &par.atk1,         0, &cbInt);
	SQLBindCol(m_hstmt, 13, SQL_C_SLONG, &par.atk2,         0, &cbInt);
	SQLBindCol(m_hstmt, 14, SQL_C_SLONG, &par.def,          0, &cbInt);
	SQLBindCol(m_hstmt, 15, SQL_C_SLONG, &par.exp,          0, &cbInt);
	SQLBindCol(m_hstmt, 16, SQL_C_SLONG, &par.jexp,         0, &cbInt);
	SQLBindCol(m_hstmt, 17, SQL_C_SLONG, &par.inc,          0, &cbInt);
	SQLBindCol(m_hstmt, 18, SQL_C_SLONG, &par.as,           0, &cbInt);
	SQLBindCol(m_hstmt, 19, SQL_C_SLONG, &par.es,           0, &cbInt);
	SQLBindCol(m_hstmt, 20, SQL_C_SLONG, &par.mSpeed,       0, &cbInt);
	SQLBindCol(m_hstmt, 21, SQL_C_SLONG, &par.rechargeTime, 0, &cbInt);
	SQLBindCol(m_hstmt, 22, SQL_C_SLONG, &par.attackedMT,   0, &cbInt);
	SQLBindCol(m_hstmt, 23, SQL_C_SLONG, &par.attackMT,     0, &cbInt);
	SQLBindCol(m_hstmt, 24, SQL_C_SLONG, &par.property,     0, &cbInt);
	SQLBindCol(m_hstmt, 25, SQL_C_SLONG, &par.scale,        0, &cbInt);
	SQLBindCol(m_hstmt, 26, SQL_C_SLONG, &par._class,       0, &cbInt);
	SQLBindCol(m_hstmt, 27, SQL_C_SLONG, &par.race,         0, &cbInt);
	SQLBindCol(m_hstmt, 28, SQL_C_SLONG, &par.mdef,         0, &cbInt);

	while( (m_retcode = SQLFetch(m_hstmt)) != SQL_NO_DATA )
	{
		unsigned long nKeyWord = this->CMonParameterMgr::SearchKeyword(name);
		if( nKeyWord == -1 )
		{
			Trace("%s npc not exist\n", name);
			continue;
		}

		MONPARAMETER* p = new MONPARAMETER;
		memcpy(p->name, name, sizeof(p->name));
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
		this->CMonParameterMgr::AddMonParameter(nKeyWord, p); // inlined
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadMonMakingItem(SERVER, "CMonParameterMgr::LoadMonMakingItem");
void CMonParameterMgr::LoadMonMakingItem(void) // line 385-452
{
	return (this->*_LoadMonMakingItem)();

	//TODO
}


//hook_method<void (CMonParameterMgr::*)(unsigned long spriteType, MONPARAMETER* parameter)> CMonParameterMgr::_AddMonParameter(SERVER, "CMonParameterMgr::AddMonParameter");
void CMonParameterMgr::AddMonParameter(unsigned long spriteType, MONPARAMETER* parameter) // line ???-???
{
//	return (this->*_AddMonParameter)(spriteType, parameter);

	m_parameter[spriteType] = parameter;
}


hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_Destroy(SERVER, "CMonParameterMgr::Destroy");
void CMonParameterMgr::Destroy(void) // line 86-111
{
	return (this->*_Destroy)();

	for( mystd::map<unsigned long,MONPARAMETER*>::iterator it = m_parameter.begin(); it != m_parameter.end(); it = m_parameter.erase(it) )
		delete it->second;

	this->CMonsterParameterTable::Clear();
}


hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadEventMonParameter(SERVER, "CMonParameterMgr::LoadEventMonParameter");
void CMonParameterMgr::LoadEventMonParameter(void) // line 597-710
{
	return (this->*_LoadEventMonParameter)();

	//TODO
}


hook_method<void (CMonParameterMgr::*)(void)> CMonParameterMgr::_LoadEventMonMakingItem(SERVER, "CMonParameterMgr::LoadEventMonMakingItem");
void CMonParameterMgr::LoadEventMonMakingItem(void) // line 726-794
{
	return (this->*_LoadEventMonMakingItem)();

	//TODO
}
