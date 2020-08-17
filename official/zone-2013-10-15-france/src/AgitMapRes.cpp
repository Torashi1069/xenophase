#include "AgitDB.h"
#include "AgitMapRes.h"
#include "CharacterMgr.h"
#include "Enum.h"
#include "NPC.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "Instant map/InstantMapConfiguration.h"
#include "Instant map/InstantMapLib.h"
#include "NpcServer/NpcSvr.h"
#include "shared/shared.h"


/// statics
std::map<std::string,FLAG_INFO*>& CAgitMapRes::m_agitTable = VTOR<std::map<std::string,FLAG_INFO*>>(DetourFindFunction(EXEPATH(), "CAgitMapRes::m_agitTable"));

/// locals
std::map<int,int>& g_siegeMsg = VTOR<std::map<int,int>>(DetourFindFunction(EXEPATH(), "g_siegeMsg"));
int& SIEGE_PERIOD = VTOR<int>(DetourFindFunction(EXEPATH(), "SIEGE_PERIOD")); // = 2;
int& EMPELIUM_LIFETIME = VTOR<int>(DetourFindFunction(EXEPATH(), "EMPELIUM_LIFETIME")); // = SIEGE_PERIOD * 3600;
int(& g_Table)[7] = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_Table")); // = { 2, 1, 0, 3, 2, 1, 0 };
int(& g_IsDay)[7] = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_IsDay")); // = { 1, 0, 0, 1, 0, 0, 0 };
int(& g_Next)[7]  = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_Next"));  // = { 3, 3, 3, 0, 0, 0, 0 };
int(& g_sHour)[7] = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_sHour")); // = { 19, 0, 0, 21, 0, 0, 0 };
int& SIEGE_PERIOD_V15 = VTOR<int>(DetourFindFunction(EXEPATH(), "SIEGE_PERIOD_V15")); // = 2;
int& EMPELIUM_LIFETIME_V15 = VTOR<int>(DetourFindFunction(EXEPATH(), "EMPELIUM_LIFETIME_V15")); // = SIEGE_PERIOD_V15 * 3600;
int(& g_Table_v15)[7] = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_Table_v15")); // = { 2, 1, 0, 3, 2, 1, 0 };
int(& g_IsDay_v15)[7] = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_IsDay_v15")); // = { 1, 0, 0, 1, 0, 0, 0 };
int(& g_Next_v15)[7]  = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_Next_v15"));  // = { 3, 3, 3, 0, 0, 0, 0 };
int(& g_sHour_v15)[7] = VTOR<int[7]>(DetourFindFunction(EXEPATH(), "g_sHour_v15")); // = { 19, 0, 0, 21, 0, 0, 0 };
int(& g_economyTable)[20] = VTOR<int[20]>(DetourFindFunction(EXEPATH(), "g_economyTable")); // = { 5000, 10000, 20000, 35000, 55000, 80000, 110000, 145000, 185000, 230000, 280000, 335000, 395000, 460000, 530000, 605000, 685000, 770000, 860000, 955000 };
int(& g_defenseTable)[20] = VTOR<int[20]>(DetourFindFunction(EXEPATH(), "g_defenseTable")); // = { 10000, 20000, 40000, 70000, 110000, 160000, 220000, 290000, 370000, 460000, 560000, 670000, 790000, 920000, 1060000, 1210000, 1370000, 1540000, 1720000, 1910000 };


int GetNextDay()
{
	time_t t = time(NULL);
	tm* lt = localtime(&t);

	return t + 3600 * (23 - lt->tm_hour) + 60 * (59 - lt->tm_min) + (60 - lt->tm_sec);
}


int GetSiegeHour(int wday)
{
	return g_sHour[wday];
}


time_t GetNextDDay()
{
	time_t t = time(NULL);
	tm* lt = localtime(&t);

	int siegeHour = GetSiegeHour(lt->tm_wday);
	if( g_IsDay[lt->tm_wday] && lt->tm_hour < GetSiegeHour(lt->tm_wday) + SIEGE_PERIOD )
		siegeHour += 24 * (g_Table[lt->tm_wday] + 1);

	t += 3600 * (siegeHour - lt->tm_hour) - 60 * lt->tm_min - lt->tm_sec;
	return t;
}


int GetSiegeHour_v15(int wday)
{
	return g_sHour_v15[wday];
}


time_t GetNextDDay_v15()
{
	time_t t = time(NULL);
	tm* lt = localtime(&t);

	int siegeHour = GetSiegeHour_v15(lt->tm_wday);
	if( !g_IsDay_v15[lt->tm_wday] || lt->tm_hour >= siegeHour + SIEGE_PERIOD_V15 )
		siegeHour += 24 * (g_Table[lt->tm_wday] + 1);

	t += 3600 * (siegeHour - lt->tm_hour) - 60 * lt->tm_min - lt->tm_sec;
	return t;
}


////////////////////////////////////////


CAgitMapRes::CAgitMapRes(const int in_mapType)
: CMapRes(in_mapType)
{
	m_economy = 1;
	m_defense = 1;
	m_guildID = 0;
	m_triggerE = 0;
	m_triggerD = 0;
	m_payTime = 0;
	m_noGuardian = 0;
	m_visibleC = 0;
	memset(m_npcArray, (int)NULL, sizeof(m_npcArray));
	memset(m_guardianArray, (int)NULL, sizeof(m_guardianArray));
	memset(m_visibleG, 0, sizeof(m_visibleG));
	m_agitName[0] = '\0';
	m_isPKTime = FALSE;
	m_isDisableSkill = 0;
	m_createCount = 0;
	m_empeliumConqueror[0] = '\0';
	m_bInstantMapBlockRequest = false;
}


CAgitMapRes::~CAgitMapRes()
{
	this->CAgitMapRes::Reset();
}


void CAgitMapRes::Reset()
{
	this->CMapRes::Reset();
}


time_t CAgitMapRes::GetNextSigeTime()
{
	return GetNextDDay();
}


time_t CAgitMapRes::GetNextSigeTime_v15()
{
	return GetNextDDay_v15();
}


bool CAgitMapRes::SetSiegeTime(const char* timeString, int hour)
{
	int nEntries = strlen(timeString) / 5;
	if( nEntries < 1 || nEntries > 7 )
		return false;

	int siegeHour[7] = {};
	char hh[3] = {};
	int s[7];

	if( nEntries > 0 )
		memset(s, -1, nEntries * sizeof(int));

	static char* w[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

	for( int j = 0; j < countof(w); ++j )
	{
		const char* p = timeString;

		for( int i = 0; i < nEntries; ++i )
		{
			if( memcmp((p + 0), w[j], 3) == 0 )
			{
				s[i] = j;
				hh[0] = *(p + 3);
				hh[1] = *(p + 4);
				siegeHour[i] = atoi(hh);
			}

			p += 5;
		}
	}

	for( int i = 0; i < nEntries && s[i] != -1; ++i )
		if( siegeHour[i] < 0 || siegeHour[i] >= 24 )
			return false;

	memset(g_sHour, 0, sizeof(g_sHour));
	for( int i = 0; i < nEntries; ++i )
		g_sHour[s[i]] = siegeHour[i];

	memset(g_IsDay, 0, sizeof(g_IsDay));
	for( int i = 0; i < nEntries; ++i )
		g_IsDay[s[i]] = TRUE;

	int k = s[0];
	for( int j = 0; j < nEntries; ++j )
	{
		int next = ( j != nEntries - 1 ) ? s[j + 1] : s[0];
		int i = next - s[j];
		if( i <= 0 )
			i += 7;

		while( i > 0 )
		{
			--i;
			g_Next[k] = next;
			g_Table[k] = i;
			k = (k + 1) % 7;
		}
	}

	SIEGE_PERIOD = hour;
	EMPELIUM_LIFETIME = 3600 * hour;

	return true;
}


bool CAgitMapRes::SetSiegeTime_v15(const char* timeString, int hour)
{
	int nEntries = strlen(timeString) / 5;
	if( nEntries < 1 || nEntries > 7 )
		return false;

	int siegeHour[7] = {};
	char hh[3] = {};
	int s[7];

	if( nEntries > 0 )
		memset(s, -1, nEntries * sizeof(int));

	static char* w[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

	for( int j = 0; j < countof(w); ++j )
	{
		const char* p = timeString;

		for( int i = 0; i < nEntries; ++i )
		{
			if( memcmp((p + 0), w[j], 3) == 0 )
			{
				s[i] = j;
				hh[0] = *(p + 3);
				hh[1] = *(p + 4);
				siegeHour[i] = atoi(hh);
			}

			p += 5;
		}
	}

	for( int i = 0; i < nEntries && s[i] != -1; ++i )
		if( siegeHour[i] < 0 || siegeHour[i] >= 24 )
			return false;

	memset(g_sHour_v15, 0, sizeof(g_sHour_v15));
	for( int i = 0; i < nEntries; ++i )
		g_sHour_v15[s[i]] = siegeHour[i];

	memset(g_IsDay_v15, 0, sizeof(g_IsDay_v15));
	for( int i = 0; i < nEntries; ++i )
		g_IsDay_v15[s[i]] = TRUE;

	int k = s[0];
	for( int j = 0; j < nEntries; ++j )
	{
		int next = ( j != nEntries - 1 ) ? s[j + 1] : s[0];
		int i = next - s[j];
		if( i <= 0 )
			i += 7;

		while( i > 0 )
		{
			--i;
			g_Next_v15[k] = next;
			g_Table_v15[k] = i;
			k = (k + 1) % 7;
		}
	}

	SIEGE_PERIOD_V15 = hour;
	EMPELIUM_LIFETIME_V15 = 3600 * hour;

	return true;}


BOOL CAgitMapRes::Load(const char* fileName, int mapID, int mapType)
{
	return this->CMapRes::Load(fileName, mapID, mapType);
}


void CAgitMapRes::InitAgit(const AGIT_DBINFO& info)
{
	memcpy_s(m_agitName, sizeof(m_agitName), info.agitName, sizeof(info.agitName));
	m_guildID = info.guildID;
	m_economy = CAP_VALUE(info.economy, 1, 100);
	m_defense = CAP_VALUE(info.defense, 1, 100);

	if( m_guildID != 0 )
	{
		m_triggerE = info.triggerE;
		m_triggerD = info.triggerD;
		m_incTime = info.nextTime;
		m_payTime = info.payTime;
		m_visibleC = info.visibleC;
		memcpy_s(m_visibleG, sizeof(m_visibleG), info.visibleG, sizeof(info.visibleG));
		this->CAgitMapRes::Schedule(m_incTime, AS_INC);
		this->CAgitMapRes::Schedule(m_payTime, AS_PAY);
	}
	else
	{
		m_triggerE = 0;
		m_triggerD = 0;
		m_incTime = 0;
		m_payTime = 0;
		m_visibleC = 0;
		memcpy_s(m_visibleG, sizeof(m_visibleG), info.visibleG, sizeof(m_visibleG));
	}

	this->CAgitMapRes::SetNextSaveTime();

	if( m_guildID != 0 )
		g_ZGuildMgr.CZGuildMgr::AddAgitGuild(m_guildID);

	g_siegeMsg.insert(std::pair<const int,int>(this->CMapRes::GetID(), 0));
	m_siegeTimeVersion = this->CMapRes::IsItPossible(MAPPROPERTY_SIEGETIME_VERSION);
}


int CAgitMapRes::GetProperty(int n, int& type)
{
	type = 0;

	switch( n )
	{
	case 0:
		return m_economy;
	break;
	case 1:
		return this->CAgitMapRes::GetECondition();
	break;
	case 2:
		return this->CAgitMapRes::GetEMoney();
	break;
	case 3:
		return m_triggerE;
	break;
	case 4:
		return m_defense;
	break;
	case 5:
		return this->CAgitMapRes::GetDCondition();
	break;
	case 6:
		return this->CAgitMapRes::GetDMoney();
	break;
	case 7:
		return m_triggerD;
	break;
	case 8:
		return m_guildID;
	break;
	case 9:
		type = 1;
		return (int)m_agitName;
	break;
	case 10:
	{
		type = 1;
		CGuild* g = g_ZGuildMgr.CGuildMgr::SearchGuild(m_guildID);
		return ( g != NULL ) ? (int)g->CGuild::GetGuildName() : (int)"";
	}
	break;
	case 11:
	{
		type = 1;
		CGuild* g = g_ZGuildMgr.CGuildMgr::SearchGuild(m_guildID);
		return ( g != NULL ) ? (int)g->CGuild::GetMasterName() : (int)"";
	}
	break;
	case 12:
		return g_ZGuildMgr.CZGuildMgr::GetGuildSkillLevel(m_guildID, SKID_GD_KAFRACONTRACT);
	break;
	case 13:
		return g_ZGuildMgr.CZGuildMgr::GetGuildSkillLevel(m_guildID, SKID_GD_GUARDRESEARCH);
	break;
	case 15:
		type = m_isDisableSkill;
		return 0;
	break;
	case 16:
		type = 1;
		return (int)m_empeliumConqueror;
	break;
	default:
		return 0;
	break;
	};
}


BOOL CAgitMapRes::SetProperty(int n, int data)
{
	switch( n )
	{
	case 0:
		m_economy = data;
	break;
	case 4:
		m_defense = data;
	break;
	case 8:
		g_ZGuildMgr.CZGuildMgr::OnChangeAgitGuild(this->CMapRes::GetName(), m_guildID, data);
		m_guildID = data;
		this->CAgitMapRes::OnChangeOwner(m_guildID);
	break;
	case 14:
		for( std::vector<CNPC*>::iterator it = m_flagNpc.begin(); it != m_flagNpc.end(); ++it )
			(*it)->CNPC::OnChangeGuildID();

		for( int i = 0; i < m_noGuardian; ++i )
			m_guardianArray[i]->CNPC::OnChangeGuildID();
	break;
	};

	return TRUE;
}


BOOL CAgitMapRes::Method(int func, int parm1, int parm2)
{
	switch( func )
	{
	case AF_INVEST_ECONOMY:
		this->CAgitMapRes::InvestEconomy();
	break;
	case AF_INVEST_DEFENSE:
		this->CAgitMapRes::InvestDefense();
	break;
	case AF_SCHEDULE_PAYTIME:
		m_payTime = GetServerTime() + 864000;
		this->CAgitMapRes::Schedule(m_payTime, AS_PAY);
	break;
	case AF_FLUSH_GDID:
		Trace("AF_FLUSH_GDID target:%d\n", parm1);
		if( this->CAgitMapRes::IsSiegeTime() )
			this->CAgitMapRes::Flush(parm1);
	break;
	case AF_CHANGE_DEFENSE:
		this->CAgitMapRes::OnChangeDefense(FALSE);
	break;
	};

	return TRUE;
}


BOOL CAgitMapRes::NpcGetProperty(int no, int n, int* data, int* type)
{
	CNPC* npc = this->CAgitMapRes::GetNPC(no);
	if( npc == NULL )
		return FALSE;

	if( type != NULL )
		*type = 0;

	switch( n )
	{
	case 0:
		if( npc->GetType() == NPC_MOB_TYPE )
			*data = ( npc->CNPC::GetCurrentFSMState() != DEAD_ST );
		else
			*data = ( npc->CNPC::IsEnable() == TRUE );
	break;
	case 1:
		*data = npc->CNPC::GetCharacterInfo()->maxhp;
	break;
	case 2:
		*data = npc->CNPC::GetCharacterInfo()->hp;
	break;
	case 3:
		*data = npc->CNPC::GetCharacterInfo()->maxhp / 3;
	break;
	case 4:
		*data = npc->CNPC::GetCharacterInfo()->sp;
	break;
	case 5:
		if( type != NULL )
			*type = 1;
		*data = (int)npc->CNPC::GetCharacterInfo()->accountName;
	break;
	};

	return TRUE;
}


BOOL CAgitMapRes::NpcSetProperty(int no, int n, int data)
{
	CNPC* npc = this->CAgitMapRes::GetNPC(no);
	if( npc == NULL )
		return FALSE;

	switch( n )
	{
	case 0:
	{
		if( data == 1 )
		{
			if( npc->GetType() == NPC_MOB_TYPE )
			{
				npc->CNPC::Revival();
				npc->UpdateParameterValue(VAR_GDID, m_guildID);
				npc->CNPC::OnChangeDefense(m_defense, TRUE);
			}
			else
			{
				npc->CNPC::Enable();
			}
		}
		else
		{
			if( npc->GetType() == NPC_MOB_TYPE )
			{
				CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, npc, CM_DISAPPEAR, 0, 0, 0, 0);
			}
			else
			{
				npc->CNPC::Disable();
			}
		}
	}
	break;
	case 2:
		npc->UpdateParameterValue(VAR_HP, data);
	break;
	case 4:
		npc->UpdateParameterValue(VAR_SP, data);
	break;
	};

	return TRUE;
}


int CAgitMapRes::GetInvestMoney(int percent, int* table, int count)
{
	if( percent > 100 )
		return 0;

	int money = table[(percent - 1) / 5];
	if( count == 1 )
		money *= 4;

	return money;
}


int CAgitMapRes::GetEMoney()
{
	return this->CAgitMapRes::GetInvestMoney(m_economy, g_economyTable, m_triggerE);
}


int CAgitMapRes::GetECondition()
{
	if( m_economy >= 100 )
		return 0;
	else
	if( m_triggerE > 1 )
		return 1;
	else
	if( m_triggerE == 0 )
		return 2;
	else
	{
		return 3;
	}
}


void CAgitMapRes::InvestEconomy()
{
	if( this->CAgitMapRes::GetECondition() != 0 )
		++m_triggerE;
}


int CAgitMapRes::GetDMoney()
{
	return this->CAgitMapRes::GetInvestMoney(m_defense, g_defenseTable, m_triggerD);
}


int CAgitMapRes::GetDCondition()
{
	if( m_defense >= 100 )
		return 0;
	else
	if( m_triggerD > 1 )
		return 1;
	else
	if( m_triggerD == 0 )
		return 2;
	else
	{
		return 3;
	}
}


void CAgitMapRes::InvestDefense()
{
	if( this->CAgitMapRes::GetDCondition() )
		++m_triggerD;
}


CNPC* CAgitMapRes::GetNPC(int no)
{
	if( no < 100 )
	{
		if( no >= 3 )
			return NULL;

		return m_npcArray[no];
	}
	else
	{
		no -= 100;
		if( no >= 8 )
			return NULL;

		return m_guardianArray[no];
	}
}


BOOL CAgitMapRes::RegisterNPC(int type, CNPC* npc, BOOL* isVisible)
{
	*isVisible = TRUE;

	if( type == 0 )
	{
		if( m_noGuardian >= 8 )
			return FALSE;

		npc->UpdateParameterValue(VAR_GDID, m_guildID);
		m_guardianArray[m_noGuardian] = npc;
		npc->CNPC::OnChangeDefense(m_defense, TRUE);
		if( !m_visibleG[m_noGuardian] )
			*isVisible = FALSE;
		++m_noGuardian;
		return TRUE;
	}
	else
	if( type == 1 )
	{
		if( m_npcArray[0] != NULL )
			return FALSE;

		m_npcArray[0] = npc;
		npc->UpdateParameterValue(VAR_GDID, m_guildID);
		return TRUE;
	}
	else
	if( type == 2 )
	{
		if( m_npcArray[1] != NULL )
			return FALSE;

		m_npcArray[1] = npc;
		npc->CNPC::OnChangeDefense(m_defense, TRUE);

		if( m_guildID != 0 )
		{
			if( this->CAgitMapRes::IsSiegeTime() )
			{
				m_createCount = 1;
				*isVisible = TRUE;
				time_t t = ( m_siegeTimeVersion == 1 ) ? EMPELIUM_LIFETIME + GetNextDDay() : EMPELIUM_LIFETIME_V15 + GetNextDDay_v15();
				this->CAgitMapRes::Schedule(t, AS_4);
				m_isPKTime = TRUE;
			}
			else
			{
				m_createCount = 0;
				*isVisible = FALSE;
				if( m_siegeTimeVersion == 1 )
				{
					this->CAgitMapRes::Schedule(GetNextDDay(), AS_3);
					this->CAgitMapRes::Schedule(GetNextDDay() - CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::GetExpectMaximumLifeMinute(), AS_7);
				}
				else
				{
					this->CAgitMapRes::Schedule(GetNextDDay_v15(), AS_3);
					this->CAgitMapRes::Schedule(GetNextDDay_v15() - CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::GetExpectMaximumLifeMinute(), AS_7);
				}
			}
		}
		else
		{
			*isVisible = TRUE;
		}

		npc->UpdateParameterValue(VAR_GDID, m_guildID);
		return TRUE;
	}
	else
	if( type == 3 )
	{
		if( m_npcArray[2] != NULL )
			return FALSE;

		m_npcArray[2] = npc;
		if( !m_visibleC )
			this->CAgitMapRes::NpcSetProperty(2, 0, 0);
		npc->UpdateParameterValue(VAR_GDID, m_guildID);
		return TRUE;
	}
	else
	if( type == 4 )
	{
		m_treasureNpc.push_back(npc);
		*isVisible = FALSE;
		return TRUE;
	}
	else
	{
		npc->UpdateParameterValue(VAR_GDID, m_guildID);
		return TRUE;
	}
}


void CAgitMapRes::RegisterNPC(CNPC* npc)
{
	if( npc->CNPC::GetJobType() == JT_GUILD_FLAG )
	{
		m_flagNpc.push_back(npc);
		npc->UpdateParameterValue(VAR_GDID, m_guildID);
	}
}


void CAgitMapRes::Flush(int target) // 939-988
{
	CCharacterMgr::GetObj()->CCharacterMgr::Flush(this->CMapRes::GetID(), m_guildID, target);
	m_isDisableSkill = 0;
}


void CAgitMapRes::OnChangeOwner(int old) // 1071-1164 (1017-1102)
{
	m_timerQ.clear();
	this->CAgitMapRes::Flush(0);
	this->CAgitMapRes::Schedule(GetServerTime() + 7, AS_6);
	m_isDisableSkill = 1;

	for( int i = 0; i < m_noGuardian; ++i )
	{
		m_guardianArray[i]->CNPC::ResetATKPercentInfo(SKID_GD_GUARDUP);
		m_guardianArray[i]->ResetEffective(EFST_ATTHASTE_INFINITY, 0);
		m_guardianArray[i]->UpdateParameterValue(VAR_GDID, m_guildID);
	}

	for( int i = 0; i < countof(m_npcArray); ++i )
	{
		if( m_npcArray[i] != NULL )
			m_npcArray[i]->UpdateParameterValue(VAR_GDID, m_guildID);
	}

	for( std::vector<CNPC*>::iterator iter = m_flagNpc.begin(); iter != m_flagNpc.end(); ++iter )
		(*iter)->UpdateParameterValue(VAR_GDID, m_guildID);

	m_economy -= 5;
	if( m_economy < 1 )
		m_economy = 1;

	m_defense -= 5;
	if( m_defense < 1 )
		m_defense = 1;

	m_triggerE = 0;
	m_triggerD = 0;

	this->CAgitMapRes::NpcSetProperty(2, 0, 0);

	if( m_guildID != 0 )
	{
		m_payTime = 0;
		m_incTime = GetNextDay();
		this->CAgitMapRes::Schedule(GetNextDay(), AS_INC);
	}
	else
	{
		for( int i = 0; i < m_noGuardian; ++i )
			m_guardianArray[i]->CNPC::Revival();

		if( m_npcArray[1] != NULL )
			m_npcArray[1]->CNPC::Revival();

		m_payTime = 0;
		m_incTime = 0;
		m_createCount = 0;
	}

	this->CAgitMapRes::Schedule(( m_siegeTimeVersion == 1 ) ? GetNextDDay() : GetNextDDay_v15(), AS_3);
	this->CAgitMapRes::OnChangeDefense(TRUE);
	this->CAgitMapRes::Save(old != 0);
}


BOOL CAgitMapRes::IsSiegeTime() // 1170-1183 (1108-1121)
{
	time_t t = GetServerTime();
	tm* lt = localtime(&t);

	if( !g_IsDay[lt->tm_wday] )
		return FALSE;

	int siegeHour = GetSiegeHour(lt->tm_wday);
	if( lt->tm_hour < siegeHour || lt->tm_hour >= siegeHour + SIEGE_PERIOD )
		return FALSE;

	return TRUE;
}


BOOL CAgitMapRes::IsSiegeTime(CMapRes* mapRes) // 1210-1230 (1135-1154)
{
	if( mapRes == NULL )
		return FALSE;

	int siegeVersion = mapRes->CMapRes::IsItPossible(MAPPROPERTY_SIEGETIME_VERSION);
	if( siegeVersion == 1 )
		return CAgitMapRes::IsSiegeTime();
	else
	if( siegeVersion == 15 )
		return CAgitMapRes::IsSiegeTime_v15();
	else
	{
		return FALSE;
	}
}


BOOL CAgitMapRes::IsSiegeTime_v15() // 1233-1246
{
	time_t t = GetServerTime();
	tm* lt = localtime(&t);

	if( !g_IsDay_v15[lt->tm_wday] )
		return FALSE;
	
	int siegeHour = GetSiegeHour_v15(lt->tm_wday);
	if( lt->tm_hour < siegeHour || lt->tm_hour >= siegeHour + SIEGE_PERIOD_V15 )
		return FALSE;

	return TRUE;
}


bool CAgitMapRes::IsAgit() // (184.h)
{
	return true;
}


void CAgitMapRes::UpdateLastSiegeMsg(int mapId, int state) // 1260-1267
{
	std::map<int,int>::iterator iter = g_siegeMsg.find(mapId);
	if( iter == g_siegeMsg.end() )
		return;

	iter->second = state;
}


void CAgitMapRes::OnChangeDefense(BOOL isInit) // 1271-1277
{
	for( int i = 0; i < m_noGuardian; ++i )
		m_guardianArray[i]->CNPC::OnChangeDefense(m_defense, isInit);

	if( m_npcArray[1] != NULL )
		m_npcArray[1]->CNPC::OnChangeDefense(m_defense, isInit);
}


void CAgitMapRes::OnRcvAckFromInter(unsigned char ret) // ??? (1223-1229)
{
	if( ret == ZENY_UPDATE_SUCCESS )
	{
		Trace("OnRcvAckFromInter - 길드자금에서 창고직원 비용 삭감 성공\n");
	}
	else
	{
		this->CAgitMapRes::NpcSetProperty(2, 0, 0);
	}
}


void CAgitMapRes::Save(const bool bNextSave) // 1311-1345 (1235-1265)
{
	this->CAgitMapRes::SetNextSaveTime();
	if( m_npcArray[1] == NULL )
		return;

	AGIT_DBINFO info;
	info.guildID = m_guildID;
	info.economy = m_economy;
	info.defense = m_defense;
	info.triggerE = m_triggerE;
	info.triggerD = m_triggerD;
	info.nextTime = m_incTime;
	info.payTime = 0;
	info.createTime = 0;

	int visible = 0;
	this->CAgitMapRes::NpcGetProperty(2, 0, &visible, 0);
	info.visibleC = visible;
	m_visibleC = visible;

	memset(info.visibleG, 0, sizeof(info.visibleG));

	for( int i = 0; i < m_noGuardian; ++i )
	{
		int visible = 0;
		this->CAgitMapRes::NpcGetProperty(100 + i, 0, &visible, NULL);
		info.visibleG[i] = visible;
		m_visibleG[i] = visible;
	}

	g_AgitDB.CAgitDB::Update(this->CMapRes::GetName(), &info);
}


void CAgitMapRes::SetNextSaveTime() // 1349-1355
{
	this->CAgitMapRes::Schedule(GetServerTime() + 600, AS_SAVE);
	Trace("Save:%d\n", GetServerTime());
}


unsigned long CAgitMapRes::GetGDID() // 156.h
{
	return m_guildID;
}


void CAgitMapRes::UnlinkNPC() // (1279-1300)
{
	this->CAgitMapRes::Save(00000000); //TODO: unknown value

	for( int i = 0; i < m_noGuardian; ++i )
		m_guardianArray[i] = NULL;
	m_noGuardian = 0;

	m_npcArray[0] = NULL;
	m_npcArray[1] = NULL;
	m_npcArray[2] = NULL;

	m_flagNpc.clear();
	m_treasureNpc.clear();

	for( std::map<std::string,FLAG_INFO*>::iterator it = m_agitTable.begin(); it != m_agitTable.end(); ++it )
		it->second->vt.clear();
}


void CAgitMapRes::Schedule(time_t t, int event) // 160-162.h
{
	m_timerQ.insert(std::pair<const time_t,int>(t, event));
}


void CAgitMapRes::OnTimer() // 1383-1396
{
	time_t CurTM = (time_t)GetServerTime();

	for( std::multimap<time_t,int>::iterator it = m_timerQ.begin(); it != m_timerQ.end(); it = m_timerQ.erase(it) )
	{
		if( it->first >= CurTM )
			break; // done for now.

		this->CAgitMapRes::TimerProc(it->first, it->second);
	}
}


int CAgitMapRes::GetTreasureBoxCount() // 1399-1405
{
	return 4 + m_economy / 5;
}


void CAgitMapRes::MakeTreasure() // 1409-1418
{
	std::vector<CNPC*>::iterator iter;
	int i;

	for( iter = m_treasureNpc.begin(), i = 0; iter != m_treasureNpc.end() && i < this->CAgitMapRes::GetTreasureBoxCount(); ++iter, ++i )
		(*iter)->CNPC::Revival();
}


void CAgitMapRes::TimerProc(time_t time, unsigned long event) // 1423-1727
{
	int visible = 0;

	switch( event )
	{
	case 0:
		this->CAgitMapRes::Flush(0);
	break;
	case 1:
		if( m_guildID == 0 )
			break;

		m_incTime = GetNextDay();
		this->CAgitMapRes::Schedule(m_incTime, AS_INC);

		if( m_triggerE != 0 )
		{
			m_economy += m_triggerE;
			m_triggerE = 0;

			if( g_ZGuildMgr.CZGuildMgr::GetGuildSkillLevel(m_guildID, SKID_GD_DEVELOPMENT) >= 1 )
			{
				if( GetServerRandom(0, 20000) % 100 < 50 )
					++m_economy;
			}

			if( m_economy > 100 )
				m_economy = 100;
		}

		if( m_triggerD != 0 )
		{
			m_defense += m_triggerD;
			m_triggerD = 0;

			if( m_defense <= 100 )
				this->CAgitMapRes::OnChangeDefense(FALSE);
			else
				m_defense = 100;
		}

		this->CAgitMapRes::MakeTreasure();
	break;
	case 2:
		if( m_guildID == 0 )
			break;

		this->CAgitMapRes::NpcGetProperty(2, 0, &visible, 0);
		if( visible )
			this->CAgitMapRes::Method(AF_SCHEDULE_PAYTIME, 0, 0);
	break;
	case 3:
		if( m_guildID == 0 )
			break;

		if( m_createCount == 0 )
		{
			this->CAgitMapRes::Flush(0);
			m_isPKTime = 1;
			CAgitMapRes::UpdateLastSiegeMsg(this->CMapRes::GetID(), 1);
			if( m_npcArray[0] != NULL )
			{
				CZNPC2Msg msg;
				msg.CZNPC2Msg::SetMsgID(ZNPC2MSG_CALLEVENT);
				msg.par1 = NPCEVENT_ONSTARTARENA;
				g_npcSvr.CNpcSvr::SendMsg(0, m_npcArray[0]->GetAccountID(), &msg);
			}
		}

		++m_createCount;

		this->CAgitMapRes::NpcGetProperty(1, 0, &visible, 0);
		if( !visible )
		{
			this->CAgitMapRes::NpcSetProperty(1, 0, 1);
			if( m_npcArray[1] != NULL )
				m_npcArray[1]->CNPC::OnChangeDefense(m_defense, TRUE);
		}

		this->CAgitMapRes::Schedule(time + ( m_siegeTimeVersion == 1 ) ? EMPELIUM_LIFETIME : EMPELIUM_LIFETIME_V15, AS_4);
	break;
	case 4:
		m_createCount = 0;
		m_isPKTime = 0;
		CAgitMapRes::UpdateLastSiegeMsg(this->CMapRes::GetID(), 0);

		if( m_npcArray[0] != NULL )
		{
			CZNPC2Msg msg;
			msg.CZNPC2Msg::SetMsgID(ZNPC2MSG_CALLEVENT);
			msg.par1 = NPCEVENT_ONSTARTARENA;
			g_npcSvr.CNpcSvr::SendMsg(0, m_npcArray[0]->GetAccountID(), &msg);
		}

		this->CAgitMapRes::NpcGetProperty(1, 0, &visible, 0);
		if( visible == 1 )
			this->CAgitMapRes::NpcSetProperty(1, 0, 0);

		this->CAgitMapRes::Schedule(( m_siegeTimeVersion == 1 ) ? GetNextDDay() : GetNextDDay_v15(), AS_3);
		this->CAgitMapRes::Schedule(::time(NULL) + 120, AS_8);
	break;
	case 5:
		this->CAgitMapRes::Save(00000000); //TODO: unknown value
	break;
	case 6:
		CAgitMapRes::UpdateLastSiegeMsg(this->CMapRes::GetID(), 2);
		if( m_npcArray[0] != NULL )
		{
			CZNPC2Msg msg;
			msg.CZNPC2Msg::SetMsgID(ZNPC2MSG_CALLEVENT);
			msg.par1 = NPCEVENT_ONSTARTARENA;
			g_npcSvr.CNpcSvr::SendMsg(0, m_npcArray[0]->GetAccountID(), &msg);
		}
	break;
	case 7:
		if( !m_bInstantMapBlockRequest && CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::IsAllow() )
		{
			m_bInstantMapBlockRequest = true;
			InstantMap::Send_PACKET_ZI_INSTANTMAP_ALLOW(false, PACKET_ZI_INSTANTMAP_ALLOW::WHY_AGITWAR_START);
		}
	break;
	case 8:
		if( m_bInstantMapBlockRequest && CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::IsAllow() )
		{
			m_bInstantMapBlockRequest = false;
			InstantMap::Send_PACKET_ZI_INSTANTMAP_ALLOW(true, PACKET_ZI_INSTANTMAP_ALLOW::WHY_AGITWAR_END);
		}
	break;
	default:
	break;
	}
}


void CAgitMapRes::InsertTable(const char* mapName, int GDID, const char* agitName) // 1730-1738 (1518-1526)
{
	FLAG_INFO* Info = new(std::nothrow) FLAG_INFO;
	if( Info == NULL )
		return;

	Info->GDID = GDID;
	memcpy_s(Info->agitName, sizeof(Info->agitName), agitName, 24);
	m_agitTable[mapName] = Info;
}


void CAgitMapRes::OnNotifyFromInter(const char* mapName, int GDID) // 1754-1764 (1542-1552)
{
	std::map<std::string,FLAG_INFO*>::iterator it = m_agitTable.find(mapName);
	if( it == m_agitTable.end() )
		return;

	FLAG_INFO* info = it->second;

	info->GDID = GDID;
	for( std::vector<CNPC*>::iterator it = info->vt.begin(); it != info->vt.end(); ++it )
		(*it)->UpdateParameterValue(VAR_GDID, info->GDID);
}


bool CAgitMapRes::IsAgitMap(const char* mapName) // ??? (1626-1634)
{
	if( mapName == NULL )
		return false;

	std::map<std::string,FLAG_INFO*>::const_iterator it = m_agitTable.find(mapName);
	if( it == m_agitTable.end())
		return false;

	return true;
}
