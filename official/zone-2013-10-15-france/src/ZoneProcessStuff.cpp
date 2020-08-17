#include "Enum.h" // JT_*
#include "GVar.h"
#include "ObjectRecycleMgr.h"
#include "Struct.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "Common/ServerIdentity.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ServerInfo.h"


/// globals
int (& g_refTbl)[5][10] = VTOR<int[5][10]>(DetourFindFunction(EXEPATH(), "g_refTbl"));
int (& g_advancedRefTbl)[5][10] = VTOR<int[5][10]>(DetourFindFunction(EXEPATH(), "g_advancedRefTbl"));
int (& g_refTblTen)[5][10] = VTOR<int[5][10]>(DetourFindFunction(EXEPATH(), "g_refTblTen"));


hook_func<void (__cdecl*)()> _shutdownlog(EXEPATH(), "shutdownlog");
void shutdownlog()
{
	return (_shutdownlog)();
	//TODO
/*
	bool prevOutput = NCriticalErrorLog::GetObj()->NFileLog::GetOutput();
	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(true);

	if( !NEO_PACKAGEITEM::CNeoPackageItem::GetObj()->NEO_PACKAGEITEM::CNeoPackageItem::SaveGift_NumberInfo() )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"error  NEO_PACKAGEITEM::CNeoPackageItem::SaveGift_NumberInfo()");

	if( CGVar::GetObj() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"used memory = %.2f Mbytes(%d Bytes)",
		CGVar::GetObj()->CGVar::GetUsedMemoryBytes() / 1024. / 1024.,
		CGVar::GetObj()->CGVar::GetUsedMemoryBytes());

	if( CCharacterNameDictionary::GetObj() != NULL )
		CCharacterNameDictionary::GetObj()->CCharacterNameDictionary::shutdownlog();

	if( CObjectRecycleMgr<CLogonPermitADBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"LogonPermitADBWorkRecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CLogonPermitADBWork>::Instance()->CObjectRecycleMgr<CLogonPermitADBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CLogonPermitADBWork>::Instance()->CObjectRecycleMgr<CLogonPermitADBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CLogonPermitADBWork>::Instance()->CObjectRecycleMgr<CLogonPermitADBWork>::GetObjectMaxCnt());

	if( CObjectRecycleMgr<CSaveBodyItemADBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"SaveBodyItemADBWork RecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CSaveBodyItemADBWork>::Instance()->CObjectRecycleMgr<CSaveBodyItemADBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CSaveBodyItemADBWork>::Instance()->CObjectRecycleMgr<CSaveBodyItemADBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CSaveBodyItemADBWork>::Instance()->CObjectRecycleMgr<CSaveBodyItemADBWork>::GetObjectMaxCnt());

	if( CObjectRecycleMgr<CSaveCartADBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"SaveCartADBWork RecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::GetObjectMaxCnt());

	if( CObjectRecycleMgr<CLoadCartADBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"LoadCartADBWork RecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::GetObjectMaxCnt());

	if( CObjectRecycleMgr<CSaveAllADBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"SaveAllADBWorkRecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CSaveAllADBWork>::Instance()->CObjectRecycleMgr<CSaveAllADBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CSaveAllADBWork>::Instance()->CObjectRecycleMgr<CSaveAllADBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CSaveAllADBWork>::Instance()->CObjectRecycleMgr<CSaveAllADBWork>::GetObjectMaxCnt());

	if( CObjectRecycleMgr<CSaveQuestEventDBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"SaveQuestEventADBWorkRecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CSaveQuestEventDBWork>::Instance()->CObjectRecycleMgr<CSaveQuestEventDBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CSaveQuestEventDBWork>::Instance()->CObjectRecycleMgr<CSaveQuestEventDBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CSaveQuestEventDBWork>::Instance()->CObjectRecycleMgr<CSaveQuestEventDBWork>::GetObjectMaxCnt());

	if( CObjectRecycleMgr<CLoadStoreADBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"LoadStoreADBWorkRecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CLoadStoreADBWork>::Instance()->CObjectRecycleMgr<CLoadStoreADBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CLoadStoreADBWork>::Instance()->CObjectRecycleMgr<CLoadStoreADBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CLoadStoreADBWork>::Instance()->CObjectRecycleMgr<CLoadStoreADBWork>::GetObjectMaxCnt());

	if( CObjectRecycleMgr<CSaveStoreADBWork>::Instance() != NULL )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__,
		"SaveStoreADBWorkRecycleMgr Max Object new(%d) delete(%d) max(%d)",
		CObjectRecycleMgr<CSaveStoreADBWork>::Instance()->CObjectRecycleMgr<CSaveStoreADBWork>::GetObjectNewCnt(),
		CObjectRecycleMgr<CSaveStoreADBWork>::Instance()->CObjectRecycleMgr<CSaveStoreADBWork>::GetObjectDeleteCnt(),
		CObjectRecycleMgr<CSaveStoreADBWork>::Instance()->CObjectRecycleMgr<CSaveStoreADBWork>::GetObjectMaxCnt());

	double LuaMonsterAIUsedMBytes;
	if( NLuaMonsterAIMgr::GetObj() != NULL )
		LuaMonsterAIUsedMBytes = NLuaMonsterAIMgr::GetObj()->NLuaMonsterAIMgr::GetUsedMemoryBytes() / 1024. / 1024.;
	else
		LuaMonsterAIUsedMBytes = 0.;
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "__LUAMONSTERAI %.2f Mbytes", LuaMonsterAIUsedMBytes);

	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(prevOutput);
*/
}


int GetPureJob(int in_Job)
{
	switch( in_Job )
	{
	case JT_NOVICE:
	case JT_NOVICE_H:
	case JT_NOVICE_B:
		return JT_NOVICE;
	break;
	case JT_SWORDMAN:
	case JT_SWORDMAN_H:
	case JT_SWORDMAN_B:
		return JT_SWORDMAN;
	break;
	case JT_MAGICIAN:
	case JT_MAGICIAN_H:
	case JT_MAGICIAN_B:
		return JT_MAGICIAN;
	break;
	case JT_ARCHER:
	case JT_ARCHER_H:
	case JT_ARCHER_B:
		return JT_ARCHER;
	break;
	case JT_ACOLYTE:
	case JT_ACOLYTE_H:
	case JT_ACOLYTE_B:
		return JT_ACOLYTE;
	break;
	case JT_MERCHANT:
	case JT_MERCHANT_H:
	case JT_MERCHANT_B:
		return JT_MERCHANT;
	break;
	case JT_THIEF:
	case JT_THIEF_H:
	case JT_THIEF_B:
		return JT_THIEF;
	break;
	case JT_KNIGHT:
	case JT_KNIGHT_H:
	case JT_KNIGHT_B:
		return JT_KNIGHT;
	break;
	case JT_PRIEST:
	case JT_PRIEST_H:
	case JT_PRIEST_B:
		return JT_PRIEST;
	break;
	case JT_WIZARD:
	case JT_WIZARD_H:
	case JT_WIZARD_B:
		return JT_WIZARD;
	break;
	case JT_BLACKSMITH:
	case JT_BLACKSMITH_H:
	case JT_BLACKSMITH_B:
		return JT_BLACKSMITH;
	break;
	case JT_HUNTER:
	case JT_HUNTER_H:
	case JT_HUNTER_B:
		return JT_HUNTER;
	break;
	case JT_ASSASSIN:
	case JT_ASSASSIN_H:
	case JT_ASSASSIN_B:
		return JT_ASSASSIN;
	break;
	case JT_CRUSADER:
	case JT_CRUSADER_H:
	case JT_CRUSADER_B:
		return JT_CRUSADER;
	break;
	case JT_MONK:
	case JT_MONK_H:
	case JT_MONK_B:
		return JT_MONK;
	break;
	case JT_SAGE:
	case JT_SAGE_H:
	case JT_SAGE_B:
		return JT_SAGE;
	break;
	case JT_ROGUE:
	case JT_ROGUE_H:
	case JT_ROGUE_B:
		return JT_ROGUE;
	break;
	case JT_ALCHEMIST:
	case JT_ALCHEMIST_H:
	case JT_ALCHEMIST_B:
		return JT_ALCHEMIST;
	break;
	case JT_BARD:
	case JT_BARD_H:
	case JT_BARD_B:
		return JT_BARD;
	break;
	case JT_DANCER:
	case JT_DANCER_H:
	case JT_DANCER_B:
		return JT_DANCER;
	break;
	case JT_SUPERNOVICE:
	case JT_SUPERNOVICE_B:
		return JT_SUPERNOVICE;
	break;
	case JT_SUPERNOVICE2:
	case JT_SUPERNOVICE2_B:
		return JT_SUPERNOVICE2;
	break;
	case JT_TAEKWON:
		return JT_TAEKWON;
	break;
	case JT_STAR:
		return JT_STAR;
	break;
	case JT_LINKER:
		return JT_LINKER;
	break;
	case JT_RUNE_KNIGHT:
	case JT_RUNE_KNIGHT_H:
	case JT_RUNE_KNIGHT_B:
		return JT_RUNE_KNIGHT;
	break;
	case JT_ARCHBISHOP:
	case JT_ARCHBISHOP_H:
	case JT_ARCHBISHOP_B:
		return JT_ARCHBISHOP;
	break;
	case JT_WARLOCK:
	case JT_WARLOCK_H:
	case JT_WARLOCK_B:
		return JT_WARLOCK;
	break;
	case JT_MECHANIC:
	case JT_MECHANIC_H:
	case JT_MECHANIC_B:
		return JT_MECHANIC;
	break;
	case JT_RANGER:
	case JT_RANGER_H:
	case JT_RANGER_B:
		return JT_RANGER;
	break;
	case JT_GUILLOTINE_CROSS:
	case JT_GUILLOTINE_CROSS_H:
	case JT_GUILLOTINE_CROSS_B:
		return JT_GUILLOTINE_CROSS;
	break;
	case JT_ROYAL_GUARD:
	case JT_ROYAL_GUARD_H:
	case JT_ROYAL_GUARD_B:
		return JT_ROYAL_GUARD;
	break;
	case JT_SURA:
	case JT_SURA_H:
	case JT_SURA_B:
		return JT_SURA;
	break;
	case JT_SORCERER:
	case JT_SORCERER_H:
	case JT_SORCERER_B:
		return JT_SORCERER;
	break;
	case JT_SHADOW_CHASER:
	case JT_SHADOW_CHASER_H:
	case JT_SHADOW_CHASER_B:
		return JT_SHADOW_CHASER;
	break;
	case JT_GENETIC:
	case JT_GENETIC_H:
	case JT_GENETIC_B:
		return JT_GENETIC;
	break;
	case JT_MINSTREL:
	case JT_MINSTREL_H:
	case JT_MINSTREL_B:
		return JT_MINSTREL;
	break;
	case JT_WANDERER:
	case JT_WANDERER_H:
	case JT_WANDERER_B:
		return JT_WANDERER;
	break;
	default:
		return in_Job;
	break;
	};
}


void InitRefinerySuccessPercent()
{
	int refTbl_Free_Server[5][10] = {
		{  80,  70,  70,  60,  60,  40,  40,  20,  20,  10 },
		{  90,  90,  80,  80,  70,  70,  60,  60,  40,  20 },
		{  90,  80,  80,  70,  70,  60,  60,  40,  20,  20 },
		{  80,  80,  70,  70,  60,  60,  50,  20,  20,  20 },
		{  80,  70,  70,  60,  60,  40,  40,  20,  20,  10 },
	};

	int advancedRefTbl_Free_Server[5][10] = {
		{ 100, 100, 100, 100,  60,  40,  40,  20,  20,  10 },
		{ 100, 100, 100, 100, 100, 100, 100,  60,  40,  20 },
		{ 100, 100, 100, 100, 100, 100,  60,  40,  20,  20 },
		{ 100, 100, 100, 100, 100,  60,  50,  20,  20,  20 },
		{ 100, 100, 100, 100,  60,  40,  40,  20,  20,  10 },
	};

	int refTblTen_Free_Server[5][10] = {
		{  7,  7,  7,  7,  6,  6,  6,  6,  4,  4 },
		{ 16, 16, 16, 16, 16, 15, 15, 15, 13, 13 },
		{ 16, 16, 16, 16, 16, 15, 15, 15, 13, 13 },
		{ 16, 16, 16, 16, 16, 15, 15, 15, 13, 13 },
		{  7,  7,  7,  7,  7,  6,  6,  6,  4,  4 },
	};

	int refTbl_Foreign[5][10] = {
		{ 100, 100, 100, 100,  60,  40,  40,  20,  20,  10 },
		{ 100, 100, 100, 100, 100, 100, 100,  60,  40,  20 },
		{ 100, 100, 100, 100, 100, 100,  60,  40,  20,  20 },
		{ 100, 100, 100, 100, 100,  60,  50,  20,  20,  20 },
		{ 100, 100, 100, 100,  60,  40,  40,  20,  20,  10 },
	};

	int advancedRefTbl_Base[5][10] = {
		{ 100, 100, 100, 100,  90,  60,  60,  30,  30,  10 },
		{ 100, 100, 100, 100, 100, 100, 100,  90,  60,  20 },
		{ 100, 100, 100, 100, 100, 100,  90,  60,  30,  20 },
		{ 100, 100, 100, 100, 100,  90,  75,  30,  30,  20 },
		{ 100, 100, 100, 100,  90,  60,  60,  30,  30,  10 },
	};

	int refTblTen_Foreign[5][10] = {
		{  8,  8,  8,  8,  7,  7,  7,  7,  5,  5 },
		{ 18, 18, 18, 18, 18, 17, 17, 17, 15, 15 },
		{ 18, 18, 18, 18, 18, 17, 17, 17, 15, 15 },
		{ 18, 18, 18, 18, 18, 17, 17, 17, 15, 15 },
		{  8,  8,  8,  8,  8,  7,  7,  7,  5,  5 },
	};

	if( g_Free_Server == TRUE )
	{
		memcpy_s(g_refTbl, sizeof(g_refTbl), refTbl_Free_Server, sizeof(refTbl_Free_Server));
		memcpy_s(g_advancedRefTbl, sizeof(g_advancedRefTbl), advancedRefTbl_Free_Server, sizeof(advancedRefTbl_Free_Server));
		memcpy_s(g_refTblTen, sizeof(g_refTblTen), refTblTen_Free_Server, sizeof(refTblTen_Free_Server));
	}
	else
	{
		memcpy_s(g_refTbl, sizeof(g_refTbl), refTbl_Foreign, sizeof(refTbl_Foreign));
		memcpy_s(g_advancedRefTbl, sizeof(g_advancedRefTbl), advancedRefTbl_Base, sizeof(advancedRefTbl_Base));
		memcpy_s(g_refTblTen, sizeof(g_refTblTen), refTblTen_Foreign, sizeof(refTblTen_Foreign));
	}
}


int GetRefinerySuccessPercent(int itemLv, int refiningLv, bool isAdvanced)
{
	if( itemLv > 4 )
		return 0;

	if( refiningLv < 10 )
	{
		if( isAdvanced == true )
			return g_advancedRefTbl[itemLv][refiningLv];
		else
			return g_refTbl[itemLv][refiningLv];
	}
	else
	if( refiningLv < 20 )
	{
		return g_refTblTen[itemLv][refiningLv];
	}
	else
	{
		return 0;
	}
}


int GetLocalServerID()
{
	static int g_serverID = g_serverInfo.CServerInfo::GetLocalServerID();
	return g_serverID;
}


int GetServerRandom(int in_Min, int in_Max)
{
	int range = abs(in_Max - in_Min) + 1;

	LARGE_INTEGER bigInt;
	QueryPerformanceCounter(&bigInt);

	return min(in_Min, in_Max) + (bigInt.LowPart + rand()) % range;
}


int IsSetting(unsigned int setting)
{
	switch( setting )
	{
	case SETTING_NEWHPSP:
		return g_isNEWHPSP;
	break;
	case SETTING_MANNER_POINT:
		return g_isMANNER_POINT;
	break;
	case SETTING_KILLER_SYSTEM:
		return g_isKillerSystem;
	break;
	default:
		return 0;
	break;
	};
}


void OutputServerIdentity(const char in_pStr[])
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, in_pStr); //FIXME: uncontrolled format string vulnerability
}


void ZoneServerIdentity()
{
	bool prevOutput = NCriticalErrorLog::GetObj()->NFileLog::GetOutput();
	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(true);

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "========== server identity check start ...");
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "build version : %s", __DATE__ " " __TIME__);
	ServerIdentity(&OutputServerIdentity);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "========== server identity check end ...");

	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(prevOutput);
}


void CopyEquipItemSlotInfo(EQUIPSLOTINFO* des, EQUIPSLOTINFO* src)
{
	if( des == NULL )
		return;

	if( src != NULL )
	{
		des->info[0] = src->info[0];
		des->info[1] = src->info[1];
		des->info[2] = src->info[2];
		des->info[3] = src->info[3];
	}
	else
	{
		des->info[0] = 0;
		des->info[1] = 0;
		des->info[2] = 0;
		des->info[3] = 0;
	}
}


time_t GetServerTime()
{
	return g_curTime;
}


hook_func<bool (__cdecl*)()> _ScriptCompile(EXEPATH(), "ScriptCompile");
bool ScriptCompile()
{
	return (_ScriptCompile)();
	//TODO
/*
	CScriptCompiler compiler;

	g_itpMgr.CITPMgr::Save(GetScriptFileName(DEF_ITEM));
	g_monParameter.CMonsterParameterTable::SaveToFileNpcSpr(GetScriptFileName(DEF_MOBNAME));
	g_monParameter.CMonsterParameterTable::SaveToFileNpcSpr(GetScriptFileName(DEF_NPCSPR));
	g_skillTypeInfoMgr.CSkillTypeBaseInfo::SaveToFile(GetScriptFileName(DEF_SKILL));

	if( !compiler.CScriptCompiler::Init() )
	{
		MessageBoxA(NULL, "SCRIPT COMPILE FAIL !!", "ERROR", MB_OK);
		return false;
	}

	return true;
*/
}


const char* GetRootPath()
{
	static char szPath[MAX_PATH];
	static bool bFirstTime = true;

	if( bFirstTime )
	{
		bFirstTime = false;
		GetModuleFileNameA(NULL, szPath, countof(szPath));
		*strrchr(szPath, '\\') = '\0';
	}

	return szPath;
}


void OutputDebugLog(bool in_bDaemonServer)
{
	bool prevOutput = NCriticalErrorLog::GetObj()->NFileLog::GetOutput();
	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(true);

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[DaemonServer] shotdown request from daemonserver");

	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(prevOutput);
}


int GetMaxCharacterLevel(short job) // (ZoneProcess.h)
{
	if( job >= JT_RUNE_KNIGHT && job <= JT_MADOGEAR_B || job == JT_SUPERNOVICE2 || job == JT_SUPERNOVICE2_B )
		return 150;
	else
		return 99;
}


int GetIndexFromBitFlag(int bitFlag) // (StdAfx.cpp)
{
	int result = 0;

	while( bitFlag != 0 )
	{
		++result;
		bitFlag >>= 1;
	}

	if( result != 0 )
		--result;

	return result;
}


void ModifyVar(int& var, int val, int max) // (StdAfx.cpp)
{
	var += val;
	if( var < 0 )
		var = 0;
	if( var > max )
		var = max;
}
