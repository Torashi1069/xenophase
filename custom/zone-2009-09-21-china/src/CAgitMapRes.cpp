#include "AgitDB.h"
#include "CAgitMapRes.hpp"
#include "NPC.h"
#include "globals.hpp"
#include "shared.h" // Trace
#include "Custom/Settings.h"


hook_val<static mystd::map<mystd::string,FLAG_INFO *> > CAgitMapRes::m_agitTable(SERVER, "CAgitMapRes::m_agitTable"); // = ?


CAgitMapRes::CAgitMapRes(const int in_mapType) : CMapRes(in_mapType)
{
	m_guildID = 0;
	m_triggerE = 0;
	m_triggerD = 0;
	m_payTime = 0;
	m_noGuardian = 0;
	m_visibleC = 0;
	m_economy = 1;
	m_defense = 1;
	memset(&m_npcArray, 0, sizeof(m_npcArray));
	memset(&m_guardianArray, 0, sizeof(m_guardianArray));
	memset(&m_visibleG, 0, sizeof(m_visibleG));
	m_agitName[0] = '\0';
	m_isPKTime = 0;
	m_isDisableSkill = 0;
	m_createCount = 0;
	m_empeliumConqueror[0] = '\0';
	m_bInstantMapBlockRequest = false;
}


CAgitMapRes::~CAgitMapRes(void)
{
	this->CAgitMapRes::Reset();
}


hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_Reset(SERVER, "CAgitMapRes::Reset");
void CAgitMapRes::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_OnTimer(SERVER, "CAgitMapRes::OnTimer");
void CAgitMapRes::OnTimer(void)
{
	return (this->*_OnTimer)();

	//TODO
}


hook_method<int (CAgitMapRes::*)(const char* fileName, int mapID, int mapType)> CAgitMapRes::_Load(SERVER, "CAgitMapRes::Load");
int CAgitMapRes::Load(const char* fileName, int mapID, int mapType)
{
	return (this->*_Load)(fileName, mapID, mapType);

	//TODO
}


hook_method<static long (__cdecl *)(void)> CAgitMapRes::_GetNextSigeTime(SERVER, "CAgitMapRes::GetNextSigeTime");
long CAgitMapRes::GetNextSigeTime(void)
{
	return (CAgitMapRes::_GetNextSigeTime)();

	//TODO
}


hook_method<static long (__cdecl *)(void)> CAgitMapRes::_GetNextSigeTime_v15(SERVER, "CAgitMapRes::GetNextSigeTime_v15");
long CAgitMapRes::GetNextSigeTime_v15(void)
{
	return (CAgitMapRes::_GetNextSigeTime_v15)();

	//TODO
}


hook_method<void (CAgitMapRes::*)(const AGIT_DBINFO& info)> CAgitMapRes::_InitAgit(SERVER, "CAgitMapRes::InitAgit");
void CAgitMapRes::InitAgit(const AGIT_DBINFO& info)
{
	return (this->*_InitAgit)(info);

	//TODO
}


hook_method<int (CAgitMapRes::*)(int n, int& type)> CAgitMapRes::_GetProperty(SERVER, "CAgitMapRes::GetProperty");
int CAgitMapRes::GetProperty(int n, int& type)
{
	return (this->*_GetProperty)(n, type);

	//TODO
}


hook_method<int (CAgitMapRes::*)(int n, int data)> CAgitMapRes::_SetProperty(SERVER, "CAgitMapRes::SetProperty");
int CAgitMapRes::SetProperty(int n, int data)
{
	return (this->*_SetProperty)(n, data);

	//TODO
}


hook_method<int (CAgitMapRes::*)(int func, int parm1, int parm2)> CAgitMapRes::_Method(SERVER, "CAgitMapRes::Method");
int CAgitMapRes::Method(int func, int parm1, int parm2)
{
	return (this->*_Method)(func, parm1, parm2);

	//TODO
}


hook_method<int (CAgitMapRes::*)(int no, int n, int* data, int* type)> CAgitMapRes::_NpcGetProperty(SERVER, "CAgitMapRes::NpcGetProperty");
int CAgitMapRes::NpcGetProperty(int no, int n, int* data, int* type)
{
	return (this->*_NpcGetProperty)(no, n, data, type);

	//TODO
}


hook_method<int (CAgitMapRes::*)(int no, int n, int data)> CAgitMapRes::_NpcSetProperty(SERVER, "CAgitMapRes::NpcSetProperty");
int CAgitMapRes::NpcSetProperty(int no, int n, int data)
{
	return (this->*_NpcSetProperty)(no, n, data);

	//TODO
}


hook_method<void (CAgitMapRes::*)(CNPC* npc)> CAgitMapRes::_RegisterNPC(SERVER, "?RegisterNPC@CAgitMapRes@@QAEXPAVCNPC@@@Z");
void CAgitMapRes::RegisterNPC(CNPC* npc)
{
	return (this->*_RegisterNPC)(npc);

	if( npc->CNPC::GetJobType() == JT_GUILD_FLAG )
	{
		Trace("RegisterNPC GDID:%d", m_guildID);
		m_flagNpc.push_back(npc);
		npc->UpdateParameterValue(VAR_GDID, m_guildID);
	}
}


hook_method<int (CAgitMapRes::*)(int type, CNPC* npc, int* isVisible)> CAgitMapRes::_RegisterNPC2(SERVER, "?RegisterNPC@CAgitMapRes@@QAEHHPAVCNPC@@PAH@Z");
int CAgitMapRes::RegisterNPC(int type, CNPC* npc, int* isVisible)
{
	return (this->*_RegisterNPC2)(type, npc, isVisible);
/*
	*isVisible = 1;

	switch( type )
	{
	case 0:
		if( m_noGuardian >= countof(m_guardianArray) )
			return 0;
		m_guardianArray[m_noGuardian] = npc;

		npc->CNPC::OnChangeDefense(m_defense, 1);
		if( !m_visibleG[m_noGuardian] )
			*isVisible = 0;
		++m_noGuardian;
	break;
	case 1:
		if( m_npcArray[0] != NULL )
			return 0;
		m_npcArray[0] = npc;
	break;
	case 2:
		if( m_npcArray[1] != NULL )
			return 0;
		m_npcArray[1] = npc;

		npc->CNPC::OnChangeDefense(m_defense, 1);

		if( m_guildID == 0 )
		{
			*isVisible = 1;
			break;
		}

		if( CAgitMapRes::IsSiegeTime(this) )
		{
			m_createCount = 1;
			*isVisible = 1;

			if( m_siegeTimeVersion == 1 )
			{
				this->CAgitMapRes::Schedule(EMPELIUM_LIFETIME + GetNextDDay(), 4);
				m_isPKTime = 1;
			}
			else
			{
				this->CAgitMapRes::Schedule(EMPELIUM_LIFETIME_V15 + GetNextDDay_v15(), 4);
				m_isPKTime = 1;
			}
		}
		else
		{
			m_createCount = 0;
			*isVisible = 0;

			if( m_siegeTimeVersion == 1 )
			{
				this->CAgitMapRes::Schedule(GetNextDDay(), 3);
				this->CAgitMapRes::Schedule(GetNextDDay() - CInstantMapConfiguration::m_cpSelf->m_expect_maximum_life_minute, 7);
			}
			else
			{
				this->CAgitMapRes::Schedule(GetNextDDay_v15(), 3);
				this->CAgitMapRes::Schedule(GetNextDDay_v15() - CInstantMapConfiguration::m_cpSelf->m_expect_maximum_life_minute, 7);
			}
		}
	break;
	case 3:
		if( m_npcArray[2] != NULL )
			return 0;
		m_npcArray[2] = npc;

		if( m_visibleC == 0 )
			this->CAgitMapRes::NpcSetProperty(2, 0, 0);
	break;
	case 4:
		m_treasureNpc.push_back(npc);
		*isVisible = 0;
		return 1;
	break;
	default:
	break;
	}

	npc->UpdateParameterValue(VAR_GDID, m_guildID);
	return 1;
*/
}


hook_method<CNPC* (CAgitMapRes::*)(int no)> CAgitMapRes::_GetNPC(SERVER, "CAgitMapRes::GetNPC");
CNPC* CAgitMapRes::GetNPC(int no)
{
	return (this->*_GetNPC)(no);

	//TODO
}


hook_method<void (CAgitMapRes::*)(unsigned long newOwner)> CAgitMapRes::_ChangeOwner(SERVER, "CAgitMapRes::ChangeOwner");
void CAgitMapRes::ChangeOwner(unsigned long newOwner)
{
	return (this->*_ChangeOwner)(newOwner);

	//TODO
}


//hook_method<void (CAgitMapRes::*)(unsigned char ret)> CAgitMapRes::_OnRcvAckFromInter(SERVER, "CAgitMapRes::OnRcvAckFromInter");
void CAgitMapRes::OnRcvAckFromInter(unsigned char ret)
{
//	return (this->*_OnRcvAckFromInter)(ret);

	if( ret == 1 )
		Trace("OnRcvAckFromInter - 길드자금에서 창고직원 비용 삭감 성공\n");
	else
		this->CAgitMapRes::NpcSetProperty(2, 0, 0);
}


//hook_method<unsigned long (CAgitMapRes::*)(void)> CAgitMapRes::_GetGDID(SERVER, "CAgitMapRes::GetGDID");
unsigned long CAgitMapRes::GetGDID(void)
{
//	return (this->*_GetGDID)();

	return m_guildID;
}


//hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_UnlinkNPC(SERVER, "CAgitMapRes::UnlinkNPC");
void CAgitMapRes::UnlinkNPC(void)
{
//	return (this->*_UnlinkNPC)();

	this->CAgitMapRes::Save();

	for( int i = 0; i < m_noGuardian; ++i )
		m_guardianArray[i] = NULL;

	m_noGuardian = 0;
	m_npcArray[0] = 0;
	m_npcArray[1] = 0;
	m_npcArray[2] = 0;

	m_flagNpc.clear();
	m_treasureNpc.clear();

	for( mystd::map<mystd::string,FLAG_INFO*>::iterator it = CAgitMapRes::m_agitTable->begin(); it != CAgitMapRes::m_agitTable->end(); ++it )
		it->second->vt.clear();
}


hook_method<void (CAgitMapRes::*)(long t, int event)> CAgitMapRes::_Schedule(SERVER, "CAgitMapRes::Schedule");
void CAgitMapRes::Schedule(long t, int event)
{
	return (this->*_Schedule)(t, event);

	//TODO
}


//hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_IsPKTime(SERVER, "CAgitMapRes::IsPKTime");
int CAgitMapRes::IsPKTime(void)
{
//	return (this->*_IsPKTime)();

	return m_isPKTime;
}


hook_method<static void (__cdecl *)(const char* mapName, int GDID, const char* agitName)> CAgitMapRes::_InsertTable(SERVER, "CAgitMapRes::InsertTable");
void CAgitMapRes::InsertTable(const char* mapName, int GDID, const char* agitName)
{
	return (_InsertTable)(mapName, GDID, agitName);

	//TODO
}


hook_method<static int (__cdecl *)(CMapRes* mapRes)> CAgitMapRes::_IsSiegeTime(SERVER, "?IsSiegeTime@CAgitMapRes@@SAHPAVCMapRes@@@Z");
int __cdecl CAgitMapRes::IsSiegeTime(CMapRes* mapRes)
{
	return (CAgitMapRes::_IsSiegeTime)(mapRes);

	//TODO
}


hook_method<static int (__cdecl *)(void)> CAgitMapRes::_IsSiegeTime2(SERVER, "?IsSiegeTime@CAgitMapRes@@SAHXZ");
int __cdecl CAgitMapRes::IsSiegeTime(void)
{
	return (CAgitMapRes::_IsSiegeTime2)();

	//TODO
}


hook_method<static int (__cdecl *)(int mapType)> CAgitMapRes::_IsSiegeTime_ByMapType(SERVER, "CAgitMapRes::IsSiegeTime_ByMapType");
int __cdecl CAgitMapRes::IsSiegeTime_ByMapType(int mapType)
{
	return (CAgitMapRes::_IsSiegeTime_ByMapType)(mapType);
/*
	if( mapType == MAPTYPE_AGIT )
		return CAgitMapRes::IsSiegeTime();
	else
	if( mapType == MAPTYPE_AGIT_SIEGEV15 )
		return CAgitMapRes::IsSiegeTime_v15();
	else
		return 0;
*/
}


hook_method<static int (__cdecl *)(void)> CAgitMapRes::_IsSiegeTime_v15(SERVER, "CAgitMapRes::IsSiegeTime_v15");
int __cdecl CAgitMapRes::IsSiegeTime_v15(void)
{
	return (CAgitMapRes::_IsSiegeTime_v15)();

	//TODO
}


hook_method<bool (CAgitMapRes::*)(void)> CAgitMapRes::_IsAgit(SERVER, "CAgitMapRes::IsAgit");
bool CAgitMapRes::IsAgit(void)
{
	return (this->*_IsAgit)();

	//TODO
}


hook_method<void (CAgitMapRes::*)(long time, unsigned long event)> CAgitMapRes::_TimerProc(SERVER, "CAgitMapRes::TimerProc");
void CAgitMapRes::TimerProc(long time, unsigned long event)
{
	return (this->*_TimerProc)(time, event);

	//TODO
}


hook_method<int (CAgitMapRes::*)(int percent, int* table, int count)> CAgitMapRes::_GetInvestMoney(SERVER, "CAgitMapRes::GetInvestMoney");
int CAgitMapRes::GetInvestMoney(int percent, int* table, int count)
{
	return (this->*_GetInvestMoney)(percent, table, count);

	//TODO
}


/* hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetEMoney(SERVER, "CAgitMapRes::GetEMoney");
int CAgitMapRes::GetEMoney(void)
{
	return (this->*_GetEMoney)();

	//TODO
} */


hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetECondition(SERVER, "CAgitMapRes::GetECondition");
int CAgitMapRes::GetECondition(void)
{
	return (this->*_GetECondition)();

	//TODO
}


hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_InvestEconomy(SERVER, "CAgitMapRes::InvestEconomy");
void CAgitMapRes::InvestEconomy(void)
{
	return (this->*_InvestEconomy)();

	//TODO
}


/* hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetDMoney(SERVER, "CAgitMapRes::GetDMoney");
int CAgitMapRes::GetDMoney(void)
{
	return (this->*_GetDMoney)();

	//TODO
} */


hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetDCondition(SERVER, "CAgitMapRes::GetDCondition");
int CAgitMapRes::GetDCondition(void)
{
	return (this->*_GetDCondition)();

	//TODO
}


hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_InvestDefense(SERVER, "CAgitMapRes::InvestDefense");
void CAgitMapRes::InvestDefense(void)
{
	return (this->*_InvestDefense)();

	//TODO
}


hook_method<void (CAgitMapRes::*)(int isInit)> CAgitMapRes::_OnChangeDefense(SERVER, "CAgitMapRes::OnChangeDefense");
void CAgitMapRes::OnChangeDefense(int isInit)
{
	return (this->*_OnChangeDefense)(isInit);

	//TODO
}


hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_MakeTreasure(SERVER, "CAgitMapRes::MakeTreasure");
void CAgitMapRes::MakeTreasure(void)
{
	return (this->*_MakeTreasure)();

	mystd::vector<CNPC*>::iterator it;
	int i;

	for( it = m_treasureNpc.begin(), i = this->CAgitMapRes::GetTreasureBoxCount(); it != m_treasureNpc.end() && i > 0; ++it, --i )
		(*it)->CNPC::Revival();
}


hook_method<void (CAgitMapRes::*)(int target)> CAgitMapRes::_Flush(SERVER, "CAgitMapRes::Flush");
void CAgitMapRes::Flush(int target)
{
	return (this->*_Flush)(target);

	//TODO
}


hook_method<void (CAgitMapRes::*)(int old)> CAgitMapRes::_OnChangeOwner(SERVER, "CAgitMapRes::OnChangeOwner");
void CAgitMapRes::OnChangeOwner(int old)
{
	return (this->*_OnChangeOwner)(old);

	//TODO
}


/* hook_method<void (CAgitMapRes::*)(unsigned char type, int data)> CAgitMapRes::_SendZenyReqest(SERVER, "CAgitMapRes::SendZenyReqest");
void CAgitMapRes::SendZenyReqest(unsigned char type, int data)
{
	return (this->*_SendZenyReqest)(type, data);

	//TODO
} */


hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_SetNextSaveTime(SERVER, "CAgitMapRes::SetNextSaveTime");
void CAgitMapRes::SetNextSaveTime(void)
{
	return (this->*_SetNextSaveTime)();

	//TODO
}


hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_Save(SERVER, "CAgitMapRes::Save");
void CAgitMapRes::Save(void)
{
	return (this->*_Save)();

	this->CAgitMapRes::SetNextSaveTime();

	if( m_npcArray[1] == NULL )
		return;

	AGIT_DBINFO info;
	info.guildID = m_guildID;
	info.triggerE = m_triggerE;
	info.economy = m_economy;
	info.defense = m_defense;
	info.triggerD = m_triggerD;
	info.nextTime = m_incTime;
	info.payTime = 0;
	info.createTime = 0;

	int visibleC = 0;
	this->CAgitMapRes::NpcGetProperty(2, 0, &visibleC, 0);
	info.visibleC = visibleC;
	m_visibleC = visibleC;

	memset(&info.visibleG, 0, sizeof(info.visibleG));
	for( int i = 0; i < m_noGuardian; ++i )
	{
		int visibleG = 0;
		this->CAgitMapRes::NpcGetProperty(100 + i, 0, &visibleG, 0);
		m_visibleG[i] = visibleG;
		info.visibleG[i] = visibleG;
	}

	g_AgitDB->CAgitDB::Update(this->CMapRes::GetName(), &info);
}


/* hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_SetEmpeliumCreateTime(SERVER, "CAgitMapRes::SetEmpeliumCreateTime");
void CAgitMapRes::SetEmpeliumCreateTime(void)
{
	return (this->*_SetEmpeliumCreateTime)();

	//TODO
} */


/// @patch make base treasure box count on investment a setting - r2693
hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetTreasureBoxCount(SERVER, "CAgitMapRes::GetTreasureBoxCount");
HOOKED int CAgitMapRes::GetTreasureBoxCount(void)
{
//	return (this->*_GetTreasureBoxCount)();

	int count = CSettings::GetObj()->base_treasurebox_count + m_economy / 5;
	Trace("Agit AgitName = %s, GuildID =%d, Economy = %d, TreasureBoxCount = %d \n", m_agitName, this->GetGDID(), m_economy, count);
	return count;
}
