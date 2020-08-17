#include "CharacterMgr.h"
#include "GlobalVarDB.h"
#include "PC.h"
#include "ScriptEventHandler.h"
#include "ZoneProcess.h"
#include "shared/Client.h" // PC_TYPE
#include "Common/Packet.h"
#include "shared/NCriticalErrorLog.h"


bool CScriptEventHandler::FuncPutMob(const char* zone, int x, int y, int w, int h, int num, int mobId, int regenMin, int regenMax, int regenType, char* name, bool isBoss, bool bUseMobTomb) // 43-146
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetEquipIsSuccessRefinery(int part, TokenData& ret, bool isAdvanced) // 192-224
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncBroadcastServer(char* color, int fontType, int fontSize, int fontAlign, int fontY, char* str) // 227-242
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncClearDialog(int npcID) // 245-248
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncDialog(char* str, int npcID) // 251-256
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncNavigationActive(const char* in_szMapName, const int in_nFindType, const int in_nSetType, const int in_bHide, const int in_nXpos, const int in_nYpos, const char* in_szpMobName) // 267-272
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncCloseDialog(int npcID) // 286-290
{
	this->CScriptEventHandler::Suspend(FUNC_CLOSEDIALOG, 60);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_CLOSE_DIALOG, npcID, 0, 0, 0);
	return true;
}


bool CScriptEventHandler::FuncWaitDialog(int npcID) // 293-297
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncResetSkill() // 308-311
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncShowImage(char* image, int type) // 314-317
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncPcName(TokenData& ret) // 320-327
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncDlgWriteStr(int npcID) // 330-334
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncInputStr(TokenData& ret) // 337-340
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncMenu(std::deque<TokenData>& parm, int npcID) // 343-363
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncReadBook(int bookID, int page) // 366-374
{
	PACKET_ZC_READ_BOOK packet;
	packet.PacketType = HEADER_ZC_READ_BOOK;
	packet.bookID = bookID;
	packet.page = page;

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_SEND_PACKET, sizeof(packet), (int)&packet, 0, 0);
	return true;
}


bool CScriptEventHandler::FuncMapMove(const char* zone, int x, int y) // 377-393
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetEquipPercentRefinery(int part, TokenData& ret, bool isAdvanced) // 396-428
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetEquipWeaponLv(int part, TokenData& ret) // 431-447
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetWeaponClass(int part, TokenData& ret) // 450-465
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetEquipSlotAmount(int part, TokenData& ret) // 468-483
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncSetBuff(const char* in_EfstName, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3) // 487-514
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetBuffValue(char* buffName, TokenData& ret) // 550-580
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncLoudSpeaker(char* color, int fontType, int fontSize, int fontAlign, int fontY, char* str) // 583-635
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncTargetAttackedBuff(int func, int percent, int who, char* buffName, int time, int value) // 638-660
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetMapName(TokenData& ret) // 663-678
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetActivatedSkill(TokenData& ret) // 681-687
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetDeactivatedSkill(TokenData& ret) // 690-696
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncIsSuccessRuneUse(int runeID, TokenData& ret) // 699-705
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetPetRelationship(TokenData& ret) // 708-714
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncSetEffectStatus(int effectenum) // 717-747
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncIsEffectStatus(int effectenum, TokenData& ret) // 750-784
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncRand(int min, int max, TokenData& ret) // 787-799
{
	if( max < min )
	{// swap
		int tmp = max;
		max = min;
		min = tmp;
	}

	int range = max - min + 1;
	if( range == 0 )
		ret = min; //FIXME: missing return statement

	ret = min + rand() % range;
	return true;
}


bool CScriptEventHandler::FuncIsPcCafe(TokenData& ret) // 803-822
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_ownerID, PC_TYPE);
	if( pc == NULL )
		return false;

	PCBANG_INFO* info = pc->CPC::GetPcBangInfo();
	if( info == NULL )
		return false;
	
	ret = info->isPCBang;
	this->EventLog("IsPcCafe  return %d\n", info->isPCBang);

	return true;
}


bool CScriptEventHandler::FuncIsPremiumPcCafe(TokenData& ret) // 826-850
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetExdEquipIsSuccessRefinery(int part, bool isAdvanced, TokenData& ret) // 855-894
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncDownRefItem(int part, int down) // 898-910
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncSuccessRandomRefItem(int part, int min, int max, bool isAdvanced, TokenData& ret) // 914-932
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncPlayBGM(const char* bgm) // 937-941
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncStriptPC2(const int part) // 945-979
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetEquipName(int part, TokenData& ret) // 984-1038
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetEquipItemIdx(int part, TokenData& ret) // 1041-1076
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncSetEffect(const char* EFST_ID, const int ITID) // 1143-1153
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncReSetEffect(const char* EFST_ID) // 1156-1167
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncOpenSearchStorInfo(const int OpenType, const int SearchCount) // 1174-1177
{
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_OPEN_SEARCH_STORE_INFO, OpenType, SearchCount, 0, 0);
	return true;
}


bool CScriptEventHandler::FuncSetReadyMutationHomun(TokenData& ret) // 1184-1192
{
	return false;
	//TODO
	/*
	ret = 0;

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_ownerID, PC_TYPE);
	if( pc == NULL )
		return false;

	ret = pc->m_pcBattle.CPCBattle::SetReadyMutationHomun();
	return true;
	*/
}


bool CScriptEventHandler::FuncMutationHomon(const int in_HomunSType, TokenData& ret) // 1195-1203
{
	return false;
	//TODO
	/*
	ret = 0;

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_ownerID, PC_TYPE);
	if( pc == NULL )
		return false;

	ret = pc->m_pcBattle.CPCBattle::MutationHomun(in_HomunSType);
	return true;
	*/
}


bool CScriptEventHandler::FuncCheckHomunLevel(TokenData& ret) // 1208-1217
{
	return false;
	//TODO
	/*
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_ownerID, PC_TYPE);
	if( pc == NULL )
		return false;
	
	HOMUN_DBINFO* info = &pc->CPC::GetPCBattle()->CPCBattle::GetHomunDBInfo();
	if( info == NULL )
		return false;

	ret = info->clevel;
	return true;
	*/
}


bool CScriptEventHandler::FuncCheckHomunMutation(TokenData& ret) // 1220-1239
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncCheckHomunCall(TokenData& ret) // 1242-1256
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncResetBuff(const char* in_EfstName) // 1260-1276
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncStartCollection(const int in_nITID) // ????
{
	return true;
}


bool CScriptEventHandler::FuncMontransform(const int in_nMonsterJobType, const int in_nMinuteTime, const char* in_szBuffSpecialEfstName) // 1292-1338
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncDeleteAllBodyItem() // 1342-1357
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncIncGlobalVar(const char* in_Name, const int in_nValue) // 1360-1407
{
	if( in_Name == NULL )
		return false;

	if( strlen(in_Name) > 24 )
	{
		char strlog[128] = {};
		sprintf_s(strlog, countof(strlog), "too long globalvar name (IncGlobalVar) %s\n", in_Name);
		this->EventLog(strlog);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, strlog);
		return false;
	}

	int ret = g_globalVarDB.CGlobalVarDB::IncGlobalVar(in_Name, in_nValue);
	if( ret == 1 )
	{
		this->EventLog("FuncIncGlobalVar %s\n", in_Name);
		return true;
	}
	else
	if( ret == 0 )
	{
		char strlog[128] = {};
		sprintf_s(strlog, countof(strlog), "FuncIncGlobalVar failed! no %s in db \n", in_Name);
		this->EventLog(strlog);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, strlog);
		return false;
	}
	else
	{
		this->EventLog("FuncIncGlobalVar failed! \n", in_Name);
		return false;
	}
}


bool CScriptEventHandler::FuncDecGlobalVar(const char* in_Name, const int in_nValue) // 1410-1456
{
	if( in_Name == NULL )
		return false;

	if( strlen(in_Name) > 24 )
	{
		char strlog[128] = {};
		sprintf_s(strlog, countof(strlog), "too long globalvar name (DecGlobalVar) %s\n", in_Name);
		this->EventLog(strlog);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, strlog);
		return false;
	}

	int ret = g_globalVarDB.CGlobalVarDB::DecGlobalVar(in_Name, in_nValue);
	if( ret == 1 )
	{
		this->EventLog("FuncDecGlobalVar %s\n", in_Name);
		return true;
	}
	else
	if( ret == 0 )
	{
		char strlog[128] = {};
		sprintf_s(strlog, countof(strlog), "FuncDecGlobalVar failed! no %s in db \n", in_Name);
		this->EventLog(strlog);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, strlog);
		return false;
	}
	else
	{
		this->EventLog("FuncDecGlobalVar failed! \n", in_Name);
		return false;
	}
}


bool CScriptEventHandler::FuncAddStateEfstATK(const int in_Who, const char* in_EfstName, const int in_Percent, const int in_AtkType, const int in_KeepTime) // 1468-1481
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetAgitInvestMsg(TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncGetAgitEconomy(const char* in_Name, TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncIncAgitEconomy(const char* in_Name, const int in_nValue) // ????
{
	return true;
}


bool CScriptEventHandler::FuncDecAgitEconomy(const char* in_Name, const int in_nValue) // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQMake(const char* in_EntryQueueName, const int in_nType, const int in_nMaxMember, const int in_nMinLevel, const int in_nMaxLevel) // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQCheckUser(const char* in_EntryQueueName, const int in_nTotalUser, TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQNotifyAdmission(const char* in_EntryQueueName) // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQIsReady(const char* in_EntryQueueName, TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQMoveToRoom(const char* in_EntryQueueName, const char* in_MapName, const int in_x, const int in_y) // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQReturnToPreSpace(const char* in_EntryQueueName) // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQMoveToLobby(const char* in_EntryQueueName, const char* in_LobbyName, const int in_nTotalUser, TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyMake(const char* in_LobbyName) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyUserCount(const char* in_LobbyName, TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyNotifyAdmission(const char* in_LobbyName) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyIsReady(const char* in_LobbyName, const int in_nTotalUser, TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyMoveToRoom(const char* in_LobbyName, const char* in_MapName, const int in_x, const int in_y) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyReturnToPreSpace(const char* in_LobbyName) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyInit(const char* in_LobbyName) // ????
{
	return true;
}


bool CScriptEventHandler::FuncActiveMontransform(const int in_JobType) // 1746-1757
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncDeActiveMontransform(const int in_JobType) // 1760-1771
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncCheckJobGroup(const int in_GroupNum, TokenData& ret) // 1774-1786
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetBaseJob(TokenData& ret) // 1789-1795
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetCategoryJob(const int in_GroupNum, TokenData& ret) // 1798-1810
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncEQJobControl(const char* in_EntryQueueName, const int in_nLimitJobType) // ????
{
	return true;
}


bool CScriptEventHandler::FuncLobbyCampCode(const char* in_LobbyName, const char* in_CampCode, const int in_x, const int in_y) // ????
{
	return true;
}


bool CScriptEventHandler::FuncInsertAliveMember() // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQUserInfoInit() // ????
{
	return true;
}


bool CScriptEventHandler::FuncIsLowLevelSiegeJob(TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncResetBuffLowLevelSiege() // ????
{
	return true;
}


bool CScriptEventHandler::FuncEQMoveToLobbyJobMatching(const char* in_EntryQueueName, const char* in_LobbyName_A, const char* in_LobbyName_B, TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncGetYear(TokenData& ret) // 1929-1934
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetMonth(TokenData& ret) // 1937-1942
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetDay(TokenData& ret) // 1945-1950
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncGetWeekDay(TokenData& ret) // 1953-1958
{
	return false;
	//TODO
}


bool CScriptEventHandler::FuncMergeItem() // 1963-1970
{
	return false;
	//TODO
	/*
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_ownerID, PC_TYPE);
	if( pc != NULL )
		m_pcitemInventoryMgr.CPCItemInventoryMgr::SendMergeItemOpen();

	return true;
	*/
}


bool CScriptEventHandler::FuncStoreV2(const int in_iStoreNumber, const char* in_StoreName) // ????
{
	return true;
}


bool CScriptEventHandler::FuncIsPremium(TokenData& ret) // ????
{
	return true;
}


bool CScriptEventHandler::FuncGetPremiumCampaignGrade(const int in_nMask, TokenData& in_ret, int npcID) // ????
{
	return true;
}
