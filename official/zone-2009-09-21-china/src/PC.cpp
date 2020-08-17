#include "CBuffInfoMgr.hpp"
#include "CharacterMgr.h"
#include "CharSkill.h"
#include "CCoupleInfoDB.hpp"
#include "CItemList.hpp"
#include "ItemLog.h"
#include "CITPMgr.hpp"
#include "CMakerRankMgr.hpp"
#include "MakingLog.h"
#include "MapInfo.h"
#include "ServerInfo.h"
#include "CSkillTypeInfoMgr.hpp"
#include "CUIDGenerator.hpp"
#include "ErrorLog.h"
#include "NPC.h"
#include "NpcPet.h"
#include "PC.h"
#include "zoneprocess.h"
#include "AsyncDBWork/LoadCartADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/SaveAllADBWork.h"
#include "Common/Packet.h"
#include "ZoneScript.h"
#include "CGVar.hpp"
#include "enum.hpp"
#include "globals.hpp"
#include "shared.h" // Trace
#include <math.h> // sqrt()


CPC::CPC(void) // line 261
{
	m_dwErrorCount = 0;
	m_type = PC_TYPE;
	m_mapRes = NULL;
	m_DisconnectStep = DISCONNECTSTEP_NONE;
	m_pcproperty = new CPCProperty(this);
}


CPC::~CPC(void) // line 278
{
//	delete m_pcproperty; //FIXME: memory leak
}


hook_method<int (CPC::*)(int position, int isArrowProperty)> CPC::_GetWeaponProperty(SERVER, "CPC::GetWeaponProperty");
int CPC::GetWeaponProperty(int position, int isArrowProperty) // line 3840
{
	return (this->*_GetWeaponProperty)(position, isArrowProperty);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsSiegeMode(SERVER, "CPC::IsSiegeMode");
int CPC::IsSiegeMode(void) // line 4210
{
	return (this->*_IsSiegeMode)();

	return 0;
}


hook_method<void (CPC::*)(void)> CPC::_ForceMapMove_To_RestartMap(SERVER, "CPC::ForceMapMove_To_RestartMap");
void CPC::ForceMapMove_To_RestartMap(void)
{
	return (this->*_ForceMapMove_To_RestartMap)();

	//TODO
}


//hook_method<bool (CPC::*)(void)> CPC::_IsOpenEquipmentWin(SERVER, "CPC::IsOpenEquipmentWin");
bool CPC::IsOpenEquipmentWin(void)
{
//	return (this->*_IsOpenEquipmentWin)();

	return m_characterInfo.bOpenEquipmentWin;
}


//hook_method<void (CPC::*)(const enum CPC::enumDisconnectStep in_Step)> CPC::_SetDisconnectStep(SERVER, "CPC::SetDisconnectStep");
void CPC::SetDisconnectStep(const enum CPC::enumDisconnectStep in_Step)
{
//	return (this->*_SetDisconnectStep)(in_Step);

	m_DisconnectStep = in_Step;
}


//hook_method<const enum CPC::enumDisconnectStep (CPC::*)(void)> CPC::_GetDisconnectStep(SERVER, "CPC::GetDisconnectStep");
const enum CPC::enumDisconnectStep CPC::GetDisconnectStep(void)
{
//	return (this->*_GetDisconnectStep)();

	return m_DisconnectStep;
}


//hook_method<CPCClientUpdater* (CPC::*)(void)> CPC::_GetClientUpdaterPtr(SERVER, "CPC::GetClientUpdaterPtr");
CPCClientUpdater* CPC::GetClientUpdaterPtr(void)
{
//	return (this->*_GetClientUpdaterPtr)();

	return &m_pcClientUpdater;
}


hook_method<void (CPC::*)(void)> CPC::_AsyncSaveBodyItem(SERVER, "CPC::AsyncSaveBodyItem");
void CPC::AsyncSaveBodyItem(void) // line 20836
{
	return (this->*_AsyncSaveBodyItem)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_AsyncSaveStore(SERVER, "CPC::AsyncSaveStore");
void CPC::AsyncSaveStore(void)
{
	return (this->*_AsyncSaveStore)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_AsyncSaveCart(SERVER, "CPC::AsyncSaveCart");
void CPC::AsyncSaveCart(void)
{
	return (this->*_AsyncSaveCart)();

	//TODO
}


hook_method<void (CPC::*)(const int in_callfunc)> CPC::_AsyncSaveCharacterInfo(SERVER, "CPC::AsyncSaveCharacterInfo");
void CPC::AsyncSaveCharacterInfo(const int in_callfunc)
{
	return (this->*_AsyncSaveCharacterInfo)(in_callfunc);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_AsyncLoadStore(SERVER, "CPC::AsyncLoadStore");
void CPC::AsyncLoadStore(void)
{
	return (this->*_AsyncLoadStore)();

	//TODO
}


hook_method<void (CPC::*)(CCharacter* const in_pSender)> CPC::_AsyncLoadCart(SERVER, "CPC::AsyncLoadCart");
void CPC::AsyncLoadCart(CCharacter* const in_pSender) // line 5091
{
	return (this->*_AsyncLoadCart)(in_pSender);

	short level = m_pcSkill.CPCSkill::GetSkillLevel(SKID_MC_PUSHCART, 0);
	if( level == 0 )
	{
		level = m_pcSkill.CPCSkill::GetSkillLevel(SKID_DA_MAGICCART, 0);
		if( level > 1 )
			level = 1;
	}

	if( in_pSender )
		this->SetEffectState(8);

	if( level <= 0 )
		return;

	if( m_pcitemInventoryMgr.CPCItemInventoryMgr::IsCartOn() )
	{
		if( m_dwErrorCount < 4 )
			m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyItemInfo(1);
	}
	else
	{
		CLoadCartADBWork* work = new CLoadCartADBWork(this->GetAccountID(), this->CPC::GetCharacterID(), level);
		if( work != NULL )
		{
			if( NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
			{
				this->SetEffective(EFST_NOACTION_WAIT, 40000, work->NAsyncDBWork::GetIdentity(), work->NAsyncDBWork::GetType(), timeGetTime(), 0);
				return;
			}

			delete work;
		}

		this->AddErrorCount(".\\PC.cpp", 5125, 4, timeGetTime());
	}
}


hook_method<void (CPC::*)(void)> CPC::_AsyncSaveALL_AFTER_ACTION_NONE(SERVER, "CPC::AsyncSaveALL_AFTER_ACTION_NONE");
void CPC::AsyncSaveALL_AFTER_ACTION_NONE(void) // line 20959
{
	return (this->*_AsyncSaveALL_AFTER_ACTION_NONE)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_AsyncSaveALL_AFTER_ACTION_ANYTIME(SERVER, "CPC::AsyncSaveALL_AFTER_ACTION_ANYTIME");
void CPC::AsyncSaveALL_AFTER_ACTION_ANYTIME(void)
{
	return (this->*_AsyncSaveALL_AFTER_ACTION_ANYTIME)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_AsyncSaveALL_AFTER_ACTION_XXX(SERVER, "CPC::AsyncSaveALL_AFTER_ACTION_XXX");
void CPC::AsyncSaveALL_AFTER_ACTION_XXX(void) // line 20919
{
	return (this->*_AsyncSaveALL_AFTER_ACTION_XXX)();

	//TODO
}


hook_method<void (CPC::*)(const int in_Length, const unsigned char* in_pData)> CPC::_ParseDBFmtStoreItemData(SERVER, "CPC::ParseDBFmtStoreItemData");
void CPC::ParseDBFmtStoreItemData(const int in_Length, const unsigned char* in_pData)
{
	return (this->*_ParseDBFmtStoreItemData)(in_Length, in_pData);

	//TODO
}


hook_method<void (CPC::*)(const int in_SKLevel, const unsigned char* in_pData, const int in_Length)> CPC::_AsyncDBComplete_LoadCart(SERVER, "CPC::AsyncDBComplete_LoadCart");
void CPC::AsyncDBComplete_LoadCart(const int in_SKLevel, const unsigned char* in_pData, const int in_Length)
{
	return (this->*_AsyncDBComplete_LoadCart)(in_SKLevel, in_pData, in_Length);

	//TODO
}


//hook_method<int (CPC::*)(unsigned char* out_pBuffer, const int in_MaxBytes)> CPC::_GetStoreItemDBFormat(SERVER, "CPC::GetStoreItemDBFormat");
int CPC::GetStoreItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes)
{
//	return (this->*_GetStoreItemDBFormat)(out_pBuffer, in_MaxBytes);

	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetStoreItemDBFormat(out_pBuffer, in_MaxBytes);
}


hook_method<void (CPC::*)(const int in_callfunc, CHARINFO_TO_CHARACTERDB& io_DBInfo)> CPC::_GetDBInfo(SERVER, "CPC::GetDBInfo");
void CPC::GetDBInfo(const int in_callfunc, CHARINFO_TO_CHARACTERDB& io_DBInfo)
{
	return (this->*_GetDBInfo)(in_callfunc, io_DBInfo);

	//TODO
}


hook_method<IVItItem* (CPC::*)(const enum enumInventoryType in_InventoryType, const __int64 in_UID)> CPC::_SearchItemByUniqueIdentityNum(SERVER, "CPC::SearchItemByUniqueIdentityNum");
IVItItem* CPC::SearchItemByUniqueIdentityNum(const enum enumInventoryType in_InventoryType, const __int64 in_UID)
{
	return (this->*_SearchItemByUniqueIdentityNum)(in_InventoryType, in_UID);

	return m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByUniqueIdentityNum(in_InventoryType, in_UID);
}


//hook_method<void (CPC::*)(const enum enumInventoryType in_InventoryType, IVItItem* in_pItem)> CPC::_HireItemCheckAdd(SERVER, "CPC::HireItemCheckAdd");
void CPC::HireItemCheckAdd(const enum enumInventoryType in_InventoryType, IVItItem* in_pItem)
{
//	return (this->*_HireItemCheckAdd)(in_InventoryType, in_pItem);

	m_HireItemCtrl.CPCHireItemCtrl::RequestAdd(in_InventoryType, in_pItem);
}


hook_method<void (CPC::*)(CCharacter* const in_TransferCH, const int in_SKID, const int in_SKLevel, const int in_EFST, const int in_EFST_Time, const int in_EFST_Value)> CPC::_TransferSKILLtoPARTYmember(SERVER, "CPC::TransferSKILLtoPARTYmember");
void CPC::TransferSKILLtoPARTYmember(CCharacter* const in_TransferCH, const int in_SKID, const int in_SKLevel, const int in_EFST, const int in_EFST_Time, const int in_EFST_Value)
{
	return (this->*_TransferSKILLtoPARTYmember)(in_TransferCH, in_SKID, in_SKLevel, in_EFST, in_EFST_Time, in_EFST_Value);

	//TODO
}


//hook_method<void (CPC::*)(const int in_Job)> CPC::_MercenaryCall_Create_After(SERVER, "CPC::MercenaryCall_Create_After");
void CPC::MercenaryCall_Create_After(const int in_Job)
{
//	return (this->*_MercenaryCall_Create_After)(in_Job);

	m_pcBattle.CPCBattle::MercenaryCall_Create_After(in_Job);
}


//hook_method<void (CPC::*)(const int in_reason)> CPC::_MercenaryCall_Delete_After(SERVER, "CPC::MercenaryCall_Delete_After");
void CPC::MercenaryCall_Delete_After(const int in_reason)
{
//	return (this->*_MercenaryCall_Delete_After)(in_reason);

	m_pcBattle.CPCBattle::MercenaryCall_Delete_After(in_reason);
}


hook_method<int (CPC::*)(int item)> CPC::_GetCountOfMyNameItem(SERVER, "CPC::GetCountOfMyNameItem");
int CPC::GetCountOfMyNameItem(int item)
{
	return (this->*_GetCountOfMyNameItem)(item);

	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetCountItemOfMyGID(item);
}


//hook_method<void (CPC::*)(unsigned long time)> CPC::_SetBanTime(SERVER, "CPC::SetBanTime");
void CPC::SetBanTime(unsigned long time)
{
//	return (this->*_SetBanTime)(time);

	if( m_nBanTime == 0 )
		m_nBanTime = time;
}


//hook_method<unsigned long (CPC::*)(void)> CPC::_GetBanTime(SERVER, "CPC::GetBanTime");
unsigned long CPC::GetBanTime(void)
{
//	return (this->*_GetBanTime)();

	return m_nBanTime;
}


hook_method<void (CPC::*)(CAsyncStream* stream, unsigned long ip)> CPC::_Init(SERVER, "CPC::Init");
void CPC::Init(CAsyncStream* stream, unsigned long ip) // line 282
{
	return (this->*_Init)(stream, ip);

	this->CActor::Init();

	m_DisconnectStep = CPC::DISCONNECTSTEP_NONE;
	m_nBanTime = 0;
	m_dwErrorCount = 0;
	m_asyncStream = stream;
	m_ip = ip;
	m_mapRes = NULL;
	m_eventNo = 0;
	m_captureItemList.clear();
	m_useIncubator = 0;
	m_isPetOwner = false;
	memset(&m_characterInfo, 0, sizeof(m_characterInfo));
	m_characterInfo.extDEFPercent = 100.0;
	m_characterInfo.accountID = -1;
	m_characterInfo.mapID = -1;
	m_characterInfo.bodypalette = 0;
	m_characterInfo.accessory3 = 0;
	m_characterInfo.headpalette = 0;
	m_characterInfo.accessory2 = 0;
	m_characterInfo.headDir = 0;
	m_characterInfo.targetxPos = 100;
	m_characterInfo.targetyPos = 100;
	m_characterInfo.NotifyPositionY = 9999;
	m_characterInfo.xSize = 5;
	m_characterInfo.ySize = 5;
	m_characterInfo.MHP_Percent = 100;
	m_characterInfo.MSP_Percent = 100;
	m_characterInfo.isWhisperAcceptable = 1;
	m_characterInfo.shoes = 0;
	m_characterInfo.NotifyPositionX = 9999;
	m_characterInfo.ATKPercent = 100;
	m_characterInfo.DEFPercent = 100;
	this->CPC::InitTime();
	memset(&m_characterPInfo, 0, sizeof(m_characterPInfo));
	memset(&m_plusStatusByJob, 0, sizeof(m_plusStatusByJob));
	m_cookSucc_Tool = 0;
	m_isValid = 0;
	m_isPKModeON = 0;
	m_index = 0;
	m_lastNPCAID = 0;
	m_npcTouchCount = 0;
	m_lastCardIndex = 0;
	m_isItemMovable = 1;
	this->CPC::ResetGroupMember();
	m_whisperExRegister.clear();
	m_pathInfo.CPathInfo::Reset();
	m_neighborCache.CNeighborCache::Init();
//	m_pcClientUpdater.CPCPacketHandler::SetMyOwner(this);
//	m_pcClientUpdater.CPCClientUpdater::Init();
	m_pcClientUpdater.CPCClientUpdater::SetSendable(0);
//	m_pcItem.CPCItem::Init();
//	m_pcItem.CPCItem::SetMyOwner(this);
//	m_pcitemInventoryMgr.CPCItemInventoryMgr::Init();
//	m_pcitemInventoryMgr.CPCItemInventoryMgr::SetMyOwner(this);
	m_questEvent.CPCQuestEvent::Reset();
//	m_pcSkill.CPCSkill::Init();
//	m_pcSkill.CPCSkill::SetMyOwner(this);
//	m_packetHandler.CPCPacketHandler::Init();
//	m_packetHandler.CPCPacketHandler::SetMyOwner(this);
	m_pcBattle.CPCBattle::Init();
	m_pcBattle.CPCBattle::SetMyOwner(this);
	m_exchangeItemInfo.AID = 0;
	m_exchangeItemInfo.isPermited = 0;
	m_exchangeItemInfo.isConcluded = 0;
	m_mannerPoint.MannerPointInfo::Init(this);
	m_touchNPCList.clear();
	this->CPC::InitEnemyInfo();
	m_skillUseRefCounter = 0;
	m_lockCounter = 0;
	m_lastSendTime = 0;
	m_loadingCompleteTime = 0;
	m_pvpWinPoint = 5;
	m_pvpRanking = 0;
	this->CPC::SetPVPRanking(0);
	m_pvpFGStratTime = 0;
	m_pvpTotal = 0;
	m_myPetID = 0;
	m_effectiveList.clear();
	m_effectStateTimeL.clear();
	m_disappearHP_ItemList.clear();
	m_disappearSP_ItemList.clear();
	m_makingItemFlag = 0;
	m_devotionList.clear();
	m_magicTargetAID = 0;
	m_marriageInfo.bMarried = 0;
	m_marriageInfo.partnerGID = 0;
	memset(m_marriageInfo.partnerName, 0, sizeof(m_marriageInfo.partnerName));
	m_specialSP = 0;
	m_specialDeath = 1;
	m_questEvent.CPCQuestEvent::InIt(this);
	m_characterInfo.virtue = 0;
	m_statusEffInfo.clear();
	m_lastTargetAID = 0;
	m_palmstrikeList.clear();
	m_characterInfo.MATKPercent = 100;
	m_characterInfo.MDEFPercent = 100;
	memset(&m_familyInfo, 0, sizeof(m_familyInfo));
	m_noPointEvent = 0;
	m_makerRankPoint = 0;
	m_makerAMPoint = 0;
	m_isLessEffect = 0;
	memset(&m_PKInfo, 0, sizeof(m_PKInfo));
	m_storePasswordInfo._STORE_PASSWORD_INFO::Init();
	m_CashPasswordInfo._CASHSHOP_PASSWORD_INFO::Init();
	m_lottoNumbers._LOTTO_NUMBERS::Init();
	m_isMapLoading = 0;
	m_invalidPacket = 0;
	m_isAuctionOpen = 0;
	m_isMailOpen = 0;
	m_isTraderOpen = 0;
	isInitSendGameGuard = 0;
	m_PCBangInfo.isPCBang = 0;
	m_PCBangInfo.NotifyToClientCnt = 0;
	m_PCBangInfo.PremiumType = 0;
	m_CashPoint = 0;
	m_HireItemCtrl.CPCHireItemCtrl::Init(this);
	m_itemScriptEventNo = 0;
	m_charBuff2.SetOwner(this);
	this->CPC::ScriptTimeClear();
	m_scrollItemIndex = 0;
	m_pcproperty->CPCProperty::Reset();
	memset(&m_battleFieldInfo, 0, sizeof(m_battleFieldInfo));
	m_characterInfo.deadCount = 0;
	m_isProgress = 0;
	m_PubScheduler.CPubScheduler::Init();
	m_open_simpleCashShop = 0;
	m_clientVersion = 0;
}


hook_method<void (CPC::*)(void)> CPC::_GameGuardInit(SERVER, "CPC::GameGuardInit");
void CPC::GameGuardInit(void) // line 567
{
	return (this->*_GameGuardInit)();

	if( g_isGameGuardOn == 1 )
	{
		m_isSetGameGuard = 1;
		m_GameGuardAuth.CCSAuth2::Init();
		this->CPC::CheckGameGuard();
		m_lastGameGuardCheckTime = g_isGameGuardInitTime + timeGetTime();
	}

	isInitSendGameGuard = 1;
}


hook_method<int (CPC::*)(void)> CPC::_OnProcess(SERVER, "CPC::OnProcess");
int CPC::OnProcess(void)
{
	return (this->*_OnProcess)();

	DWORD now = timeGetTime();

	if( m_isValid )
	{
		if( m_characterTimeInfo.lastPacketArrivedTime + 300000 < now )
		{
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PC.cpp", 700, "int CPC::OnProcess() 인증시간초과 AID=%d,GID=%d", this->GetAccountID(), this->CPC::GetCharacterID());
			return 0;
		}
	}
	else
	{
		if( m_characterTimeInfo.connectedTime + 30000 < now || m_characterTimeInfo.lastPacketArrivedTime + 30000 < now )
			return 0;
	}

	if( m_packetHandler.OnProcess() != -1 )
		return 0;

	this->CPC::CheckTouchNPCList();

	if( m_pcClientUpdater.CPCClientUpdater::IsSendable() && m_pcClientUpdater.m_disconnectType != MOVE_SERVER )
	{
		this->CheckCommandQueue();
		this->CPC::CheckMove();
		this->CPC::CheckStateChange();
		this->CPC::CheckMannerPoint();
		this->CPC::CheckGuildPassiveSkill();
		m_HireItemCtrl.CPCHireItemCtrl::Process();
	}

	if( m_lastSendTime != 0 && m_lastSendTime + 10000 <= timeGetTime() )
		this->CPC::PingSend();

	if( g_isGameGuardOn == 1 && isInitSendGameGuard == 1 && m_lastGameGuardCheckTime <= now )
	{
		char Buf[256];
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "m_lastGameGuardCheckTime \n");
		g_errorLogs->CErrorLog::CriticalErrorLog(Buf, 752, ".\\PC.cpp");

		if( !this->CPC::CheckGameGuard() )
			return 0;
	}

	m_PubScheduler.CPubScheduler::Process(now, this);

	return -1;
}


hook_method<unsigned long (CPC::*)(void)> CPC::_GetAccountID(SERVER, "CPC::GetAccountID");
unsigned long CPC::GetAccountID(void)
{
	return (this->*_GetAccountID)();

	return m_characterInfo.accountID;
}


//hook_method<const char* (CPC::*)(void)> CPC::_GetAccountName(SERVER, "CPC::GetAccountName");
const char* CPC::GetAccountName(void)
{
//	return (this->*_GetAccountName)();

	return m_characterInfo.accountName;
}


hook_method<int (CPC::*)(unsigned short id, int& value)> CPC::_GetParameterValue(SERVER, "CPC::GetParameterValue");
int CPC::GetParameterValue(unsigned short id, int& value) // line 2682
{
	return (this->*_GetParameterValue)(id, value);
/*
	switch ( id )
	{
	case 0x0Bu: value = this->m_characterInfo.clevel; break;
	case 0x0Cu: value = this->m_characterInfo.sppoint; break;
	case 0x76u: value = this->m_characterInfo.plusAttRange; break;
	case 0x0Du: value = this->CPC::GetStrValue(); break;
	case 0x0Eu: value = this->CPC::GetAgiValue(); break;
	case 0x0Fu: value = this->CPC::GetVitValue(); break;
	case 0x10u: value = this->CPC::GetIntValue(); break;
	case 0x11u: value = this->CPC::GetDexValue(); break;
	case 0x12u: value = this->CPC::GetLukValue(); break;
	case 0x20u: value = this->m_characterInfo.Str; break;
	case 0x21u: value = this->m_characterInfo.Agi; break;
	case 0x22u: value = this->m_characterInfo.Vit; break;
	case 0x23u: value = this->m_characterInfo.Int; break;
	case 0x24u: value = this->m_characterInfo.Dex; break;
	case 0x25u: value = this->m_characterInfo.Luk; break;
	case 0x00u: value = this->CPC::GetSpeed(); break;
	case 0x40u: value = this->m_characterInfo.characterID; break;
	case 0x01u: value = this->m_characterInfo.exp; break;
	case 0x02u: value = this->m_characterInfo.jobexp; break;
	case 0x03u: value = this->m_characterInfo.virtue; break;
	case 0x04u: value = this->m_characterInfo.honor; break;
	case 0x05u: value = this->m_characterInfo.hp; break;
	case 0x06u: value = this->CPC::GetMaxHP(); break;
	case 0x07u: value = this->m_characterInfo.sp; break;
	case 0x08u: value = this->CPC::GetMaxSP(); break;
	case 0x09u: value = this->m_characterInfo.jobpoint; break;
	case 0x0Au: value = this->m_characterInfo.haircolor; break;
	case 0x13u: value = this->m_characterInfo.job; break;
	case 0x4Cu: value = this->m_characterInfo.head; break;
	case 0x4Du: value = this->m_characterInfo.weapon; break;
	case 0x4Eu: value = this->m_characterInfo.accessory; break;
	case 0x14u: value = this->m_characterInfo.money; break;
	case 0x15u: value = this->m_characterInfo.sex; break;
	case 0x26u: value = this->CPC::GetAttackMotionTime(); break;
	case 0x27u: value = this->CPC::GetAttackedMotionTime(); break;
	case 0x3Du: value = this->m_pathInfo.m_moveInfo.xPos; break;
	case 0x3Eu: value = this->m_pathInfo.m_moveInfo.yPos; break;
	case 0x3Fu: value = this->m_pathInfo.m_moveInfo.dir; break;
	case 0x2Du: value = this->CPC::GetItemDef(1, 0); break;
	case 0x79u: value = this->CPC::GetStatusDef(); break;
	case 0x7Bu: value = this->CPC::GetItemMagicDef(); break;
	case 0x7Cu: value = this->CPC::GetStatusMagicDef(); break;
	case 0x42u: value = this->m_characterInfo.mapID; break;
	case 0x4Fu: value = (*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 18))(); break;
	case 0x50u: value = this->m_pathInfo.m_moveInfo.LastTime; break;
	case 0x51u: value = this->m_characterInfo.GroupID; break;
	case 0x28u: value = this->m_pcSkill.CPCSkill::GetSkillLevel(1u, 0); break;
	case 0x57u: value = this->CPC::GetBodyState(); break;
	case 0x58u: value = (signed __int16)(*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))(); break;
	case 0x5Au: value = this->CPC::GetCurrentState(); break;
	case 0x5Du: value = (*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 28))(); break;
	case 0x5Fu: value = this->m_characterTimeInfo.SightRange; break;
	case 0x60u: value = this->m_characterTimeInfo.SightplusAttackPower; break;
	case 0x67u: value = this->m_characterInfo.StrAmount; break;
	case 0x68u: value = this->m_characterInfo.AgiAmount; break;
	case 0x69u: value = this->m_characterInfo.VitAmount; break;
	case 0x6Au: value = this->m_characterInfo.IntAmount; break;
	case 0x6Bu: value = this->m_characterInfo.DexAmount; break;
	case 0x6Cu: value = this->m_characterInfo.LukAmount; break;
	case 0x73u: value = this->m_characterTimeInfo.SpeedMount; break;
	case 0x77u: value = this->m_pcSkill.CPCSkill::GetDiscountPercent(); break;
	case 0x78u: value = this->CPC::GetAvoidableSuccessPercent(); break;
	case 0x7Au: value = this->m_characterTimeInfo.PlusDefencePowerInAcolyte; break;
	case 0x89u: value = (*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 25))(); break;
	case 0x38u: value = this->m_characterInfo.accessory2; break;
	case 0x39u: value = this->m_characterInfo.accessory3; break;
	case 0x3Au: value = this->m_characterInfo.headpalette; break;
	case 0x3Bu: value = this->m_characterInfo.bodypalette; break;
	case 0x8Eu:
		v5 = m_characterPInfo.effectState;
		if ( v5 & 0x88 || v5 & 0x700 )
			value = 1;
		else
			value = 0;
		break;
	case 0x8Au: value = this->baseclass_0.baseclass_0.m_characterPInfo.attack; break;
	case 0x8Bu: value = this->m_pcSkill.m_stormGustCnt; break;
	case 0x5Cu: value = (*((int (__stdcall **)(_DWORD, _DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 42))(value, 0); break;
	case 0x8Fu: value = this->m_characterInfo.GuildID; break;
	case 0x37u: value = this->m_characterInfo.joblevel; break;
	case 0x18u: value = this->CPC::GetBodyItemWeight(); break;
	case 0x19u: value = this->CPC::GetBodyMaxItemWeight(); break;
	case 0x92u:
		if ( CPCSkill::GetSkillLevel(&this->m_pcSkill, 0x229u, 0) < 1 || (*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 42))(this, 212, 0) != 1155 )
			value = 7;
		else
			value = 9;
		break;
	case 0x99u: value = this->m_characterInfo.attackDamageArmor[value + 1]; break;
	case 0x9Bu: value = this->m_characterInfo.magicImmune; break;
	case 0x9Du: value = this->m_pcSkill.CPCSkill::GetSkillLevel(0x3Fu, 0); break;
	case 0x9Cu: value = this->m_pcSkill.CPCSkill::GetSkillLevel(0x7Fu, 0); break;
	case 0xA8u: value = this->m_groupMember._Mysize; break;
	case 0xA9u: value = this->m_marriageInfo.bMarried; break;
	case 0xAAu: value = this->m_characterInfo.GuildID != 0; break;
	case 0xABu: value = (this->baseclass_0.baseclass_0.m_characterPInfo.effectState & 0x10u) >> 4; break;
	case 0xACu: value = (this->baseclass_0.baseclass_0.m_characterPInfo.effectState & 0x20u) >> 5; break;
	case 0xADu: value = this->m_characterInfo.isGroupMaster; break;
	case 0x93u: value = (*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 19))(); break;
	case 0xAEu: value = this->CPC::IsGuildMaster(this->m_characterInfo.GuildID); break;
	case 0xAFu: value = this->CPC::GetBodyState() == 0; break;
	case 0x1Bu: value = this->CPC::GetBodyState() == 1; break;
	case 0x1Du: value = this->CPC::GetBodyState() == 2; break;
	case 0xB1u: value = this->CPC::GetBodyState() == 3; break;
	case 0xB2u: value = this->CPC::GetBodyState() == 4; break;
	case 0xB3u: value = (*((int (__stdcall **)(_DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 22))(9) != 0; break;
	case 0xB0u: value = (unsigned __int16)(*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))() == 0; break;
	case 0x1Au: value = (*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))() & 1; break;
	case 0x1Cu: value = ((unsigned int)(*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))() >> 1) & 1; break;
	case 0x1Eu: value = ((unsigned int)(*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))() >> 2) & 1; break;
	case 0x1Fu: value = ((unsigned int)(*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))() >> 3) & 1; break;
	case 0xB4u: value = ((unsigned int)(*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))() >> 4) & 1; break;
	case 0xB5u: value = ((unsigned int)(*((int (**)(void))this->baseclass_0.baseclass_0.baseclass_0.vtable + 56))() >> 6) & 1; break;
	case 0xB6u:
		if ( CPC::GetCategorySecondJob(this->m_characterInfo.job) == 10 )
			value = this->m_makerRankPoint;
		else
			value = 0;
		break;
	case 0xB7u:
		if ( CPC::GetCategorySecondJob(this->m_characterInfo.job) != 18 )
			value = 0;
		else
			value = this->m_makerRankPoint;
		break;
	case 0xB8u:
		if ( CPC::GetCategorySecondJob(this->m_characterInfo.job) != 10 )
			value = 0;
		else
			value = g_makerRankMgr->CMakerRankMgr::GetRankFromTop10(this);
		break;
	case 0xB9u:
		if ( CPC::GetCategorySecondJob(this->m_characterInfo.job) == 18 )
			value = g_makerRankMgr->CMakerRankMgr::GetRankFromTop10(this);
		else
			value = 0;
		break;
	case 0xBCu: value = this->m_pcBattle.CPCBattle::GetMagicATKPower(0, 1); break;
	case 0x34u: value = this->m_characterInfo.criPercent; break;
	case 0xBFu: value = this->m_characterInfo.MDEFPercent; break;
	case 0xC2u: value = this->m_pcproperty->m_propertys.statusMPowerReduce; break;
	default:
		value = 0;
		return 0;
	}
	return 1;
*/
}


hook_method<int (CPC::*)(unsigned short id, int value)> CPC::_UpdateParameterValue(SERVER, "CPC::UpdateParameterValue");
int CPC::UpdateParameterValue(unsigned short id, int value)
{
	return (this->*_UpdateParameterValue)(id, value);
/*
	int result; // eax@5
	PACKET_ZC_SPRITE_CHANGE2 outpacket;

	switch ( id )
	{
	case 0xBu:
		m_characterInfo.clevel = max(value + m_characterInfo.clevel, 0);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xBu, m_characterInfo.clevel);
		return 1;
	case 0xCu:
		m_characterInfo.sppoint = max(value + m_characterInfo.sppoint, 0);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xCu, m_characterInfo.sppoint);
		return 1;
	case 0xDu:
		Trace("STR:%d change to %d\n", this->m_characterInfo.Str, this->m_characterInfo.Str + value);
		m_characterInfo.Str = max(value + m_characterInfo.Str, 0);
		v7 = CPC::GetStrValue(this);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xDu, v7);
		return 1;
	case 0xEu:
		Trace("AGI:%d change to %d\n", this->m_characterInfo.Agi, this->m_characterInfo.Agi + value);
		m_characterInfo.Agi = max(value + m_characterInfo.Agi, 0);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xEu, this->CPC::GetAgiValue());
		return 1;
	case 0xFu:
		Trace("VIT:%d change to %d\n", this->m_characterInfo.Vit, this->m_characterInfo.Vit + value);
		m_characterInfo.Vit = max(value + m_characterInfo.Vit, 0);
		v9 = CPC::GetVitValue(this);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xFu, v9);
		return 1;
	case 0x10u:
		Trace("INT:%d change to %d\n", this->m_characterInfo.Int, this->m_characterInfo.Int + value);
		m_characterInfo.Int = max(value + m_characterInfo.Int, 0);
		v10 = CPC::GetIntValue(this);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x10u, v10);
		return 1;
	case 0x11u:
		Trace("DEX:%d change to %d\n", this->m_characterInfo.Dex, this->m_characterInfo.Dex + value);
		m_characterInfo.Dex = max(value + m_characterInfo.Dex, 0);
		v11 = CPC::GetDexValue(this);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x11u, v11);
		return 1;
	case 0x12u:
		Trace("LUK:%d change to %d\n", this->m_characterInfo.Luk, this->m_characterInfo.Luk + value);
		m_characterInfo.Luk = max(value + m_characterInfo.Luk, 0);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x12u, this->CPC::GetLukValue());
		return 1;
	case 0x76u:
		this->m_characterInfo.plusAttRange += value;
		Trace("plusAttRange: %d\n", this->m_characterInfo.plusAttRange);
		CPC::NotifyAttackRange(this);
		return 1;
	case VAR_SPEED:
		this->m_characterInfo.speed = max(this->m_characterInfo.speed + value, 0);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0, this->CPC::GetSpeed());
		return 1;
	case 3u:
		if ( abs(this->m_characterInfo.virtue) >= 30000 )
			return 1;
		m_characterInfo.virtue = m_characterInfo.virtue + value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(3u, m_characterInfo.virtue);
		return 1;
	case 4u:
		this->m_characterInfo.honor += value;
		if ( this->m_characterInfo.honor > 0 )
			this->m_characterInfo.honor = 0;
		if ( this->m_characterInfo.honor < -30000 )
			this->m_characterInfo.honor = -30000;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(4u, this->m_characterInfo.honor);
		return 1;
	case 0x3Cu:
		this->m_characterInfo.PKhonor += value;
		if ( this->m_characterInfo.PKhonor > 0 )
			this->m_characterInfo.PKhonor = 0;
		if ( this->m_characterInfo.PKhonor < -30000 )
			this->m_characterInfo.PKhonor = -30000;
		Trace("PK honor: %d\n", this->m_characterInfo.PKhonor);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x3Cu, this->m_characterInfo.PKhonor);
		return 1;
	case 5u:
		this->m_characterInfo.hp += value;
		this->CPC::OnChangedHP();
		return 1;
	case 0x6Du:
		this->m_characterInfo.plusMaxHP += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(6u, this->CPC::GetMaxHP());
		return 1;
	case 0x6Fu:
		this->m_characterInfo.MHP_Percent += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(6u, this->CPC::GetMaxHP());
		return 1;
	case 0x71u:
		this->m_characterTimeInfo.HPAcceleration += value;
		return 1;
	case 7u:
		if ( (*((int (__stdcall **)(_DWORD, _DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 42))(213, 0) && value < 0 )
		{
			if ( this->m_characterInfo.money > -20 * value )
			{
				v17 = 20 * value;
				CharacterInfo::AddMoney(&this->m_characterInfo, v17);
				CPCClientUpdater::NotifyLongParameter(&this->m_pcClientUpdater, 0x14u, this->m_characterInfo.money);
				result = 1;
			}
			else
			{
				(*(void (__thiscall **)(CPC *, signed int, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 44))(this, 213, 0);
				this->m_characterInfo.sp += value;
				CPC::OnChangedSP(this);
				result = 1;
			}
		}
		else
		{
			this->m_characterInfo.sp += value;
			this->CPC::OnChangedSP();
			if ( this->m_characterInfo.sp || !(*(int (__thiscall **)(CPC *, signed int, _DWORD))((int (__thiscall **)(_DWORD, _DWORD, _DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 42))(this, 106, 0) )
			{
				result = 1;
			}
			else
			{
				(*(void (__thiscall **)(CPC *, signed int, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 44))(this, 106, 0);
				result = 1;
			}
		}
		break;
	case 0x6Eu:
		this->m_characterInfo.plusMaxSP += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(8u, this->CPC::GetMaxSP());
		return 1;
	case 0x70u:
		this->m_characterInfo.MSP_Percent += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(8u, this->CPC::GetMaxSP());
		return 1;
	case 0x72u:
		this->m_characterTimeInfo.SPAcceleration += value;
		return 1;
	case 9u:
		m_characterInfo.jobpoint = max(value + m_characterInfo.jobpoint, 0);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(9u, m_characterInfo.jobpoint);
		return 1;
	case 0xAu:
		m_characterInfo.haircolor = max(value + m_characterInfo.haircolor, 0);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xAu, m_characterInfo.haircolor);
		return 1;
	case 0x13u:
		CPC::ChangeJob(this, value);
		return 1;
	case VAR_HEAD:
		this->m_characterInfo.head = value;
		outpacket.PacketType = 471;
		outpacket.GID = CPCClientUpdater::GetAccountID(&this->m_pcClientUpdater);
		outpacket.type = 1;
		outpacket.value = value;
		CPC::Send(this, 11, (char *)&outpacket);
		CCharacter::MultiCast(&this->baseclass_0.baseclass_0, (char *)&outpacket, 11);
		return 1;
	case VAR_WEAPON:
		this->m_characterInfo.weapon = value;
		outpacket.PacketType = 471;
		outpacket.GID = m_characterInfo.accountID;
		outpacket.type = 2;
		outpacket.value = value;
		CPC::Send(this, 11, (char *)&outpacket);
		CCharacter::MultiCast(&this->baseclass_0.baseclass_0, (char *)&outpacket, 11);
		return 1;
	case VAR_ACCESSORY:
		outpacket.PacketType = 471;
		this->m_characterInfo.accessory = value;
		outpacket.GID = CPCClientUpdater::GetAccountID(&this->m_pcClientUpdater);
		outpacket.type = 3;
		outpacket.value = value;
		CPC::Send(this, 11, (char *)&outpacket);
		CCharacter::MultiCast(&this->baseclass_0.baseclass_0, (char *)&outpacket, 11);
		return 1;
	case VAR_ACCESSORY2:
		outpacket.PacketType = 471;
		this->m_characterInfo.accessory2 = value;
		outpacket.GID = CPCClientUpdater::GetAccountID(&this->m_pcClientUpdater);
		outpacket.type = 4;
		outpacket.value = value;
		CPC::Send(this, 11, (char *)&outpacket);
		CCharacter::MultiCast(&this->baseclass_0.baseclass_0, (char *)&outpacket, 11);
		return 1;
	case VAR_ACCESSORY3:
		outpacket.PacketType = 471;
		this->m_characterInfo.accessory3 = value;
		outpacket.GID = CPCClientUpdater::GetAccountID(&this->m_pcClientUpdater);
		outpacket.type = 5;
		outpacket.value = value;
		CPC::Send(this, 11, (char *)&outpacket);
		CCharacter::MultiCast(&this->baseclass_0.baseclass_0, (char *)&outpacket, 11);
		return 1;
	case 0x3Au:
		outpacket.PacketType = 471;
		this->m_characterInfo.headpalette = value;
		outpacket.GID = CPCClientUpdater::GetAccountID(&this->m_pcClientUpdater);
		outpacket.type = 6;
		outpacket.value = value;
		CPC::Send(this, 11, (char *)&outpacket);
		CCharacter::MultiCast(&this->baseclass_0.baseclass_0, (char *)&outpacket, 11);
		return 1;
	case 0x3Bu:
		outpacket.PacketType = 471;
		this->m_characterInfo.bodypalette = value;
		outpacket.GID = CPCClientUpdater::GetAccountID(&this->m_pcClientUpdater);
		outpacket.type = 7;
		outpacket.value = value;
		CPC::Send(this, 11, (char *)&outpacket);
		CCharacter::MultiCast(&this->baseclass_0.baseclass_0, (char *)&outpacket, 11);
		return 1;
	case 1u:
		m_characterInfo.exp = max(m_characterInfo.exp + value, 0);
		CPCClientUpdater::NotifyLongParameter(&this->m_pcClientUpdater, 1u, m_characterInfo.exp);
		return 1;
	case 2u:
		m_characterInfo.jobexp = max(value + m_characterInfo.jobexp, 0);
		CPCClientUpdater::NotifyLongParameter(&this->m_pcClientUpdater, 2u, m_characterInfo.jobexp);
		return 1;
	case 0x14u:
		CharacterInfo::AddMoney(&this->m_characterInfo, value);
		CPCClientUpdater::NotifyLongParameter(&this->m_pcClientUpdater, 0x14u, m_characterInfo.money);
		return 1;
	case 0x56u:
		this->m_characterTimeInfo.DamageNoMotionTime = value;
		return 1;
	case 0x57u:
		CPC::SetBodyState(this, value);
		return 1;
	case 0x58u:
		CPC::SetHealthState(this, value);
		return 1;
	case 0x59u:
		(*((void (__stdcall **)(_DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 57))(value);
		return 1;
	case 0x5Au:
		CPC::SetCurrentState(this, value);
		return 1;
	case 0x5Du:
		(*((void (__stdcall **)(_DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 60))(value);
		return 1;
	case 0x5Fu:
		this->m_characterTimeInfo.SightRange = value;
		return 1;
	case 0x60u:
		this->m_characterTimeInfo.SightplusAttackPower = value;
		return 1;
	case 0x67u:
		this->m_characterInfo.StrAmount += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xDu, 0);
		return 1;
	case 0x68u:
		this->m_characterInfo.AgiAmount += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xEu, 0);
		return 1;
	case 0x69u:
		this->m_characterInfo.VitAmount += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0xFu, 0);
		return 1;
	case 0x6Au:
		this->m_characterInfo.IntAmount += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x10u, 0);
		return 1;
	case 0x6Bu:
		this->m_characterInfo.DexAmount += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x11u, 0);
		return 1;
	case 0x6Cu:
		this->m_characterInfo.LukAmount += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x12u, 0);
		return 1;
	case VAR_SPEEDAMOUNT:
		if ( this->m_pcSkill.m_spellCastingSKID && (v25 = CPCSkill::GetSkillLevel(&this->m_pcSkill, 0x116u, 0)) != 0 )
		{
			this->m_characterTimeInfo.SpeedMount = 5 * (35 - v25);
		}
		else
		{
			this->m_characterTimeInfo.SpeedMount = max(40, 100 - (this->CPC::GetMoveHasteValue1() + this->CPC::GetMoveSlowValue() + this->CPC::GetMoveHasteValue2()));
			Trace("Speed percent: %d, amount: %d\n", this->m_characterTimeInfo.SpeedMount, this->CPC::GetSpeed());
		}
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0, this->CPC::GetSpeed());
		return 1;
	case 0x7Au:
		this->m_characterTimeInfo.PlusDefencePowerInAcolyte = value;
		return 1;
	case 0x8Au:
		this->baseclass_0.baseclass_0.m_characterPInfo.attack = value;
		return 1;
	case 0x8Bu:
		this->m_pcSkill.m_stormGustCnt += value;
		return 1;
	case 0x8Fu:
		this->m_characterInfo.GuildID = value;
		return 1;
	case 0x5Bu:
		(*((void (__stdcall **)(_DWORD, _DWORD))this->baseclass_0.baseclass_0.baseclass_0.vtable + 44))(value, 0);
		return 1;
	case 0x9Au:
		this->baseclass_0.baseclass_0.m_characterPInfo.armor = value;
		return 1;
	case 0xA3u:
		this->m_characterInfo.shoes = value;
		return 1;
	case 0xA4u:
		CPC::UpdateStatusAttPower(this);
		return 1;
	case 0xA5u:
		CPC::UpdateAvoidableSucPerOnClient(this);
		return 1;
	case 0x31u:
		this->m_characterInfo.hitPercent += value;
		CPC::UpdateAttSucPercentOnClient(this);
		return 1;
	case 0xA6u:
		CPC::UpdateAttSucPercentOnClient(this);
		return 1;
	case 0x8Cu:
		this->m_characterInfo.extMagicAtkPercent += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x2Bu, this->CPC::GetMagicAttMaxPowOnClient());
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x2Cu, this->CPC::GetMagicAttMinPowOnClient());
		return 1;
	case 0x36u:
		Trace("plusAttackSpeed + %d...\n", value);
		this->m_characterInfo.plusAttackSpeed += value;
		CPC::UpdateAttackMotionTime(this);
		return 1;
	case 0x35u:
		CPC::UpdateAttackMotionTime(this);
		return 1;
	case 0xA7u:
		CCharBuff::UpdateParameterValue(&this->baseclass_0.baseclass_0.m_charBuff2, 0xA7u, value);
		return 1;
	case 0x3Fu:
		this->m_pathInfo.m_moveInfo.dir = value;
		return 1;
	case 0x29u:
		this->m_characterInfo.extAttPower += value;
		CPC::NotifyParameter(this, 0x29u, 0);
		return 1;
	case VAR_CHANGESPEED:
		m_characterTimeInfo.ChangeSpeed = max(value, 1);
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0, this->CPC::GetSpeed());
		return 1;
	case VAR_CHANGESPEEDTIME:
		this->m_characterTimeInfo.ChangeSpeedTime = max(value, 0);
		return 1;
	case 0x79u: 
		PCProperty::UpdateStatusDef(this->m_pcproperty); return 1;
	case 0x7Cu:
		CPCProperty::UpdateStatusMagicDef(this->m_pcproperty); return 1;
	case 0x34u:
		CPCProperty::UpdateCriticalSuccessValue(this->m_pcproperty); return 1;
	case 0xC0u:
		CPCProperty::UpdateCriticalDef(this->m_pcproperty); return 1;
	case 0xC1u:
		CPCProperty::UpdateItemAttPower(this->m_pcproperty);
		CPCProperty::UpdateNotifyItemPower(this->m_pcproperty);
		return 1;
	case 0xC5u:
		CPCProperty::UpdateItemMagicPower(this->m_pcproperty);
		CPCProperty::UpdateNotifyItemMPower(this->m_pcproperty);
		return 1;
	case 0xC2u:
		CPCProperty::UpdateStatusMagicPowerReduce(this->m_pcproperty);
		return 1;
	case 0xC3u:
		CPCProperty::UpdateStatusMagicPower(this->m_pcproperty);
		return 1;
	case 0x2Du:
		CPCProperty::UpdateNotifyItemDef(this->m_pcproperty);
		return 1;
	case 0x2Fu:
		CPCProperty::UpdateNotifyItemMDef(this->m_pcproperty);
		return 1;
	case 0xC8u:
		this->m_characterInfo.extAttMPower += value;
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x2Bu, this->CPC::GetMagicAttMaxPowOnClient());
		m_pcClientUpdater->CPCClientUpdater::NotifyParameter(0x2Cu, this->CPC::GetMagicAttMinPowOnClient());
		return 1;
	default:
		result = 0;
		break;
	}
	return result;
*/
}


hook_method<void (CPC::*)(COMMAND_QUEUE* command)> CPC::_InsertCommand(SERVER, "CPC::InsertCommand");
void CPC::InsertCommand(COMMAND_QUEUE* command)
{
	return (this->*_InsertCommand)(command);

	m_commandQueue.push_back(*command);
}


hook_method<void (CPC::*)(void)> CPC::_CheckCommandQueue(SERVER, "CPC::CheckCommandQueue");
void CPC::CheckCommandQueue(void)
{
	return (this->*_CheckCommandQueue)();

	//TODO
}


hook_method<void (CPC::*)(unsigned long commandID)> CPC::_DisableCommand(SERVER, "CPC::DisableCommand");
void CPC::DisableCommand(unsigned long commandID)
{
	return (this->*_DisableCommand)(commandID);

	for( mystd::list<COMMAND_QUEUE>::iterator it = m_commandQueue.begin(); it != m_commandQueue.end(); ++it )
		if( it->commandID == commandID )
			it->executionTime = 0;
}


hook_method<COMMAND_QUEUE* (CPC::*)(unsigned long commandID)> CPC::_SearchCommand(SERVER, "CPC::SearchCommand");
COMMAND_QUEUE* CPC::SearchCommand(unsigned long commandID)
{
	return (this->*_SearchCommand)(commandID);

	for( mystd::list<COMMAND_QUEUE>::iterator it = m_commandQueue.begin(); it != m_commandQueue.end(); ++it )
		if( it->commandID == commandID )
			return &*it;

	return NULL;
}


hook_method<int (CPC::*)(CCharacter* ch, int range)> CPC::_IsMyArea(SERVER, "CPC::IsMyArea");
int CPC::IsMyArea(CCharacter* ch, int range)
{
	return (this->*_IsMyArea)(ch, range);

	return m_pcClientUpdater.CPCClientUpdater::IsMyArea(ch, range);
}


hook_method<unsigned short (CPC::*)(unsigned short id)> CPC::_GetItemCount(SERVER, "CPC::GetItemCount");
unsigned short CPC::GetItemCount(unsigned short id)
{
	return (this->*_GetItemCount)(id);

	//TODO
}


//hook_method<int (CPC::*)(unsigned short id, int& value)> CPC::_GetJustBodyItemCount(SERVER, "CPC::GetJustBodyItemCount");
int CPC::GetJustBodyItemCount(unsigned short id, int& value)
{
//	return (this->*_GetJustBodyItemCount)(id, value);

	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetJustBodyItemCount(id, value);
}


hook_method<int (CPC::*)(unsigned short id, int& value)> CPC::_GetEquipItemCount(SERVER, "CPC::GetEquipItemCount");
int CPC::GetEquipItemCount(unsigned short id, int& value)
{
	return (this->*_GetEquipItemCount)(id, value);

	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetJustEquipItemCount(id, value);
}


hook_method<int (CPC::*)(void)> CPC::_IsDisconnectable(SERVER, "CPC::IsDisconnectable");
int CPC::IsDisconnectable(void)
{
	return (this->*_IsDisconnectable)();

	//TODO
}


hook_method<void (CPC::*)(time_t& time)> CPC::_GetAttackLastTime(SERVER, "CPC::GetAttackLastTime");
void CPC::GetAttackLastTime(LONG& time) // line 13453
{
	return (this->*_GetAttackLastTime)(time);

	LONG temptime;
	InterlockedExchange(&temptime, m_characterTimeInfo.AttReqLastTime);
	time = temptime;
}


hook_method<void (CPC::*)(LONG time)> CPC::_SetAttackLastTime(SERVER, "CPC::SetAttackLastTime");
void CPC::SetAttackLastTime(LONG time) // line 13461
{
	return (this->*_SetAttackLastTime)(time);

	InterlockedExchange((LONG*)&m_characterTimeInfo.AttReqLastTime, time);
}


hook_method<void (CPC::*)(long& time)> CPC::_GetLastAttackedTime(SERVER, "CPC::GetLastAttackedTime");
void CPC::GetLastAttackedTime(long& time)
{
	return (this->*_GetLastAttackedTime)(time);

	//TODO
}


hook_method<void (CPC::*)(long time)> CPC::_SetLastAttackedTime(SERVER, "CPC::SetLastAttackedTime");
void CPC::SetLastAttackedTime(long time)
{
	return (this->*_SetLastAttackedTime)(time);

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_GetErrorCount(SERVER, "CPC::GetErrorCount");
int CPC::GetErrorCount(void)
{
//	return (this->*_GetErrorCount)();

	return m_dwErrorCount;
}


hook_method<int (CPC::*)(const char* name)> CPC::_AddExWhisperList(SERVER, "CPC::AddExWhisperList");
int CPC::AddExWhisperList(const char* name)
{
	return (this->*_AddExWhisperList)(name);

	//TODO
}


hook_method<int (CPC::*)(const char* name)> CPC::_DeleteExWhisperList(SERVER, "CPC::DeleteExWhisperList");
int CPC::DeleteExWhisperList(const char* name)
{
	return (this->*_DeleteExWhisperList)(name);

	//TODO
}


hook_method<void (CPC::*)(int flag)> CPC::_SettingWhisperState(SERVER, "CPC::SettingWhisperState");
void CPC::SettingWhisperState(int flag)
{
	return (this->*_SettingWhisperState)(flag);

	//TODO
}


hook_method<void (CPC::*)(int& len, char* buf)> CPC::_GetWhisperList(SERVER, "CPC::GetWhisperList");
void CPC::GetWhisperList(int& len, char* buf)
{
	return (this->*_GetWhisperList)(len, buf);

	//TODO
}


hook_method<int (CPC::*)(const char* name)> CPC::_SearchWhisperList(SERVER, "CPC::SearchWhisperList");
int CPC::SearchWhisperList(const char* name)
{
	return (this->*_SearchWhisperList)(name);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_MulticastDestroyRoom(SERVER, "CPC::MulticastDestroyRoom");
void CPC::MulticastDestroyRoom(void)
{
	return (this->*_MulticastDestroyRoom)();

	//TODO
}


hook_method<void (CPC::*)(unsigned long roomID)> CPC::_RoomNewEntry(SERVER, "CPC::RoomNewEntry");
void CPC::RoomNewEntry(unsigned long roomID)
{
	return (this->*_RoomNewEntry)(roomID);

	//TODO
}


hook_method<void (CPC::*)(unsigned long roomID)> CPC::_MulticastRoomNewEntry(SERVER, "CPC::MulticastRoomNewEntry");
void CPC::MulticastRoomNewEntry(unsigned long roomID)
{
	return (this->*_MulticastRoomNewEntry)(roomID);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsSendable(SERVER, "CPC::IsSendable");
int CPC::IsSendable(void)
{
	return (this->*_IsSendable)();

	return m_pcClientUpdater.CPCClientUpdater::IsSendable();
}


//hook_method<bool (CPC::*)(const int in_Bytes)> CPC::_IsSendable2(SERVER, "CPC::IsSendable2");
bool CPC::IsSendable2(const int in_Bytes)
{
//	return (this->*_IsSendable2)(in_Bytes);

	if( CPC::IsSendable() )
		return m_asyncStream->CAsyncStream::IsSendable2(in_Bytes) != 0;
	else
		return 0;
}


hook_method<int (CPC::*)(void)> CPC::_IsLockOnMode(SERVER, "CPC::IsLockOnMode");
int CPC::IsLockOnMode(void)
{
	return (this->*_IsLockOnMode)();

	return m_characterInfo.IsLockOnMode;
}


hook_method<void (CPC::*)(int flag)> CPC::_SetLockOnMode(SERVER, "CPC::SetLockOnMode");
void CPC::SetLockOnMode(int flag)
{
	return (this->*_SetLockOnMode)(flag);

	m_characterInfo.IsLockOnMode = flag;
}


hook_method<unsigned long (CPC::*)(void)> CPC::_GetTargetAID(SERVER, "CPC::GetTargetAID");
unsigned long CPC::GetTargetAID(void)
{
	return (this->*_GetTargetAID)();

	return m_characterInfo.targetAID;
}


hook_method<void (CPC::*)(unsigned long AID)> CPC::_SetTargetAID(SERVER, "CPC::SetTargetAID");
void CPC::SetTargetAID(unsigned long AID)
{
	return (this->*_SetTargetAID)(AID);

	m_characterInfo.targetAID = AID;
}


hook_method<void (CPC::*)(void)> CPC::_CancelLockOnMode(SERVER, "CPC::CancelLockOnMode");
void CPC::CancelLockOnMode(void)
{
	return (this->*_CancelLockOnMode)();

	CPC::SetLockOnMode(0);
	CPC::SetTargetAID(0);
}


hook_method<CPacketHandler* (CPC::*)(void)> CPC::_GetPacketHandler(SERVER, "CPC::GetPacketHandler");
CPacketHandler* CPC::GetPacketHandler(void)
{
	return (this->*_GetPacketHandler)();

	return &m_packetHandler;
}


hook_method<void (CPC::*)(void)> CPC::_Reset(SERVER, "CPC::Reset");
void CPC::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<unsigned long (CPC::*)(void)> CPC::_GetState(SERVER, "CPC::GetState");
unsigned long CPC::GetState(void)
{
	return (this->*_GetState)();

	return m_pathInfo.m_moveInfo.state;
}


hook_method<void (CPC::*)(unsigned long state)> CPC::_SetState(SERVER, "CPC::SetState");
void CPC::SetState(unsigned long state)
{
	return (this->*_SetState)(state);

	m_pathInfo.m_moveInfo.state = state;
}


hook_method<int (CPC::*)(void)> CPC::_GetScale(SERVER, "CPC::GetScale");
int CPC::GetScale(void)
{
	return (this->*_GetScale)();

	//TODO
}


hook_method<unsigned long (CPC::*)(void)> CPC::_GetRoomID(SERVER, "CPC::GetRoomID");
unsigned long CPC::GetRoomID(void)
{
	return (this->*_GetRoomID)();

	return m_characterInfo.roomID;
}


hook_method<void (CPC::*)(unsigned long roomID)> CPC::_SetRoomID(SERVER, "CPC::SetRoomID");
void CPC::SetRoomID(unsigned long roomID)
{
	return (this->*_SetRoomID)(roomID);

	m_characterInfo.roomID = roomID;
}


hook_method<int (CPC::*)(CCharacter* ch, unsigned long flag)> CPC::_IsTarget(SERVER, "CPC::IsTarget");
int CPC::IsTarget(CCharacter* ch, unsigned long flag)
{
	return (this->*_IsTarget)(ch, flag);

	//TODO
}


hook_method<int (CPC::*)(short xPos, short yPos)> CPC::_isNotifyPosition(SERVER, "CPC::isNotifyPosition");
int CPC::isNotifyPosition(short xPos, short yPos)
{
	return (this->*_isNotifyPosition)(xPos, yPos);

	if( abs(xPos - m_characterInfo.NotifyPositionX) <= 10
	&&  abs(yPos - m_characterInfo.NotifyPositionY) <= 10 )
	{
		return 0;
	}
	else
	{
		this->m_characterInfo.NotifyPositionX = xPos;
		this->m_characterInfo.NotifyPositionY = yPos;
		return 1;
	}
}


//hook_method<int (CPC::*)(void)> CPC::_isPartyMaster(SERVER, "CPC::isPartyMaster");
int CPC::isPartyMaster(void)
{
//	return (this->*_isPartyMaster)();

	return m_characterInfo.isGroupMaster;
}


hook_method<void (CPC::*)(short xPos, short yPos)> CPC::_NotifyPositionToParty(SERVER, "CPC::NotifyPositionToParty");
void CPC::NotifyPositionToParty(short xPos, short yPos) // line 5402-5415
{
	return (this->*_NotifyPositionToParty)(xPos, yPos);

	PACKET_ZC_NOTIFY_POSITION_TO_GROUPM outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_POSITION_TO_GROUPM;
	outpacket.yPos = yPos;
	outpacket.AID = m_characterInfo.accountID;
	outpacket.xPos = xPos;

	for( mystd::list<unsigned long>::iterator it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
	{
		if( *it != m_characterInfo.accountID )
			g_characterMgr->CCharacterMgr::SendMsg(this, *it, CM_NOTIFY_POSITION_PARTY, sizeof(PACKET_ZC_NOTIFY_POSITION_TO_GROUPM), (int)&outpacket, m_characterInfo.mapID, 0);
	}
}


hook_method<void (CPC::*)(short xPos, short yPos)> CPC::_NotifyPositionToGuild(SERVER, "CPC::NotifyPositionToGuild");
void CPC::NotifyPositionToGuild(short xPos, short yPos)
{
	return (this->*_NotifyPositionToGuild)(xPos, yPos);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_NotifyHpToParty(SERVER, "CPC::NotifyHpToParty");
void CPC::NotifyHpToParty(void) // line 5466-5479
{
	return (this->*_NotifyHpToParty)();

	PACKET_ZC_NOTIFY_HP_TO_GROUPM outpacket;
	outpacket.AID = m_characterInfo.accountID;
	outpacket.PacketType = HEADER_ZC_NOTIFY_HP_TO_GROUPM;
	outpacket.hp = (short)m_characterInfo.hp;
	outpacket.maxhp = (short)this->CPC::GetMaxHP();

	for( mystd::list<unsigned long>::iterator it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
	{
		if( *it != m_characterInfo.accountID )
			g_characterMgr->CCharacterMgr::SendMsg(this, *it, CM_NOTIFY_HP_PARTY, sizeof(outpacket), (int)&outpacket, m_characterInfo.GroupID, 0);
	}
}


hook_method<void (CPC::*)(const unsigned long in_AID, const short in_HP, const short in_MaxHP)> CPC::_NotifyHpToParty2(SERVER, "?NotifyHpToParty@CPC@@QAEXKFF@Z");
void CPC::NotifyHpToParty(const unsigned long in_AID, const short in_HP, const short in_MaxHP)
{
	return (this->*_NotifyHpToParty2)(in_AID, in_HP, in_MaxHP);

	//TODO
}


hook_method<void (CPC::*)(unsigned long varID, int par1)> CPC::_NotifyParameter(SERVER, "?NotifyHpToParty@CPC@@QAEXXZ");
void CPC::NotifyParameter(unsigned long varID, int par1)
{
	return (this->*_NotifyParameter)(varID, par1);

	//TODO
}


hook_method<unsigned long (CPC::*)(void)> CPC::_GetCharacterID(SERVER, "CPC::GetCharacterID");
unsigned long CPC::GetCharacterID(void)
{
	return (this->*_GetCharacterID)();

	return m_characterInfo.characterID;
}


hook_method<void (CPC::*)(int flag)> CPC::_SetValid(SERVER, "CPC::SetValid");
void CPC::SetValid(int flag)
{
	return (this->*_SetValid)(flag);

	m_isValid = flag;
}


//hook_method<int (CPC::*)(void)> CPC::_GetJob(SERVER, "CPC::GetJob");
int CPC::GetJob(void)
{
//	return (this->*_GetJob)();

	return m_characterInfo.job;
}


/* hook_method<int (CPC::*)(void)> CPC::_GetPureJob(SERVER, "CPC::GetPureJob");
int CPC::GetPureJob(void)
{
	return (this->*_GetPureJob)();

	//TODO
} */


hook_method<int (CPC::*)(void)> CPC::_GetCategoryFirstJob(SERVER, "CPC::GetCategoryFirstJob");
int CPC::GetCategoryFirstJob(void)
{
	return (this->*_GetCategoryFirstJob)();

	/* if( m_characterInfo.job > 4002 )
	{
		switch( m_characterInfo.job )
		{
		case JT_KNIGHT_H:
		case JT_CRUSADER_H:
		case JT_SWORDMAN_B:
		case JT_KNIGHT_B:
		case JT_CRUSADER_B:
		case JT_RUNE_KNIGHT:
		case JT_RUNE_KNIGHT_H:
		case JT_ROYAL_GUARD:
		case JT_ROYAL_GUARD_H:
			return 1;
		case JT_MAGICIAN_H:
		case JT_WIZARD_H:
		case JT_SAGE_H:
		case JT_MAGICIAN_B:
		case JT_WIZARD_B:
		case JT_SAGE_B:
		case JT_WARLOCK:
		case JT_WARLOCK_H:
		case JT_SORCERER:
		case JT_SORCERER_H:
			return 2;
		case JT_ARCHER_H:
		case JT_HUNTER_H:
		case JT_BARD_H:
		case JT_DANCER_H:
		case JT_ARCHER_B:
		case JT_HUNTER_B:
		case JT_BARD_B:
		case JT_DANCER_B:
		case JT_RANGER:
		case JT_RANGER_H:
		case JT_MINSTREL:
		case JT_WANDERER:
		case JT_MINSTREL_H:
		case JT_WANDERER_H:
			return 3;
		case JT_ACOLYTE_H:
		case JT_PRIEST_H:
		case JT_MONK_H:
		case JT_ACOLYTE_B:
		case JT_PRIEST_B:
		case JT_MONK_B:
		case JT_ARCHBISHOP:
		case JT_ARCHBISHOP_H:
		case JT_SURA:
		case JT_SURA_H:
			return 4;
		case JT_MERCHANT_H:
		case JT_BLACKSMITH_H:
		case JT_ALCHEMIST_H:
		case JT_MERCHANT_B:
		case JT_BLACKSMITH_B:
		case JT_ALCHEMIST_B:
		case JT_MECHANIC:
		case JT_MECHANIC_H:
		case JT_GENETIC:
		case JT_GENETIC_H:
			return 5;
		case JT_THIEF_H:
		case JT_ASSASSIN_H:
		case JT_ROGUE_H:
		case JT_THIEF_B:
		case JT_ASSASSIN_B:
		case JT_ROGUE_B:
		case JT_GUILLOTINE_CROSS:
		case JT_GUILLOTINE_CROSS_H:
		case JT_SHADOW_CHASER:
		case JT_SHADOW_CHASER_H:
			return 6;
		case JT_TAEKWON:
		case JT_STAR:
		case JT_STAR2:
		case JT_LINKER:
			return 4046;
		case JT_GANGSI:
		case JT_DEATHKNIGHT:
		case JT_COLLECTOR:
			return 4050;
		default:
			return 0;
		}
	}
	else
	{
		if( m_characterInfo.job == JT_SWORDMAN_H )
			return 1;
		switch ( m_characterInfo.job )
		{
		case JT_SWORDMAN:
		case JT_KNIGHT:
		case JT_CRUSADER:
			return 1;
		case JT_MAGICIAN:
		case JT_WIZARD:
		case JT_SAGE:
			return 2;
		case JT_ARCHER:
		case JT_HUNTER:
		case JT_BARD:
		case JT_DANCER:
			return 3;
		case JT_ACOLYTE:
		case JT_PRIEST:
		case JT_MONK:
			return 4;
		case JT_MERCHANT:
		case JT_BLACKSMITH:
		case JT_ALCHEMIST:
			return 5;
		case JT_THIEF:
		case JT_ASSASSIN:
		case JT_ROGUE:
			return 6;
		default:
			return 0;
		}
	}

	return 0; */
}


hook_method<int (CPC::*)(void)> CPC::_GetCategorySecondJob(SERVER, "?GetCategorySecondJob@CPC@@QAEHXZ");
int CPC::GetCategorySecondJob(void)
{
	return (this->*_GetCategorySecondJob)();

	//TODO
}


hook_method<static int (__cdecl *)(const int in_Job)> CPC::_GetCategorySecondJob2(SERVER, "?GetCategorySecondJob@CPC@@SAHH@Z");
int CPC::GetCategorySecondJob(const int in_Job)
{
	return (_GetCategorySecondJob2)(in_Job);

	//TODO
}


/* hook_method<int (CPC::*)(void)> CPC::_GetCategoryThirdJob(SERVER, "CPC::GetCategoryThirdJob");
int CPC::GetCategoryThirdJob(void)
{
	return (this->*_GetCategoryThirdJob)();

	//TODO
} */


hook_method<void (CPC::*)(int job)> CPC::_ChangeJob(SERVER, "CPC::ChangeJob");
void CPC::ChangeJob(int job)
{
	return (this->*_ChangeJob)(job);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetSP(SERVER, "CPC::GetSP");
int CPC::GetSP(void)
{
	return (this->*_GetSP)();

	return m_characterInfo.sp;
}


hook_method<void (CPC::*)(int damage)> CPC::_DrainDamage(SERVER, "CPC::DrainDamage");
void CPC::DrainDamage(int damage)
{
	return (this->*_DrainDamage)(damage);

	//TODO
}


hook_method<int (CPC::*)(CCharacter* other, int position, int type, unsigned short SKID, short skLevel, int property)> CPC::_GetNormalAttackPower(SERVER, "CPC::GetNormalAttackPower");
int CPC::GetNormalAttackPower(CCharacter* other, int position, int type, unsigned short SKID, short skLevel, int property)
{
	return (this->*_GetNormalAttackPower)(other, position, type, SKID, skLevel, property);

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetAttPowerOnClient(SERVER, "CPC::GetAttPowerOnClient");
short CPC::GetAttPowerOnClient(void)
{
	return (this->*_GetAttPowerOnClient)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetRefiningAttPowerOnClient(SERVER, "CPC::GetRefiningAttPowerOnClient");
short CPC::GetRefiningAttPowerOnClient(void)
{
	return (this->*_GetRefiningAttPowerOnClient)();

	//TODO
}


/// @param isServer If set, will apply true equation for equipment refine def bonus.
/// @param isClient If set, will omit multiple attacker def penalty and grand cross casting def penalty.
hook_method<short (CPC::*)(int isServer, int isClient)> CPC::_GetItemDef(SERVER, "CPC::GetItemDef");
short CPC::GetItemDef(int isServer, int isClient)
{
	return (this->*_GetItemDef)(isServer, isClient);

	if( this->GetEffective(EFST_STEELBODY, 0) || this->GetEffective(EFST_DBARRIER, 0) )
		return 90;

	if( this->GetEffective(EFST_DPUNISH, 0) == 1 || this->GetEffective(EFST_BERSERK, 0) > 0 || this->GetEffective(EFST_DEFENCE, 0) == 2 )
		return 0;

	int v5 = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSDEFREFININGPOWEROFITEM);
	if( isServer )
		v5 = (int)((double)v5 * 0.7 + 0.5);

	int v9 = v5 + m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSDEFPOWEROFITEM) + m_characterInfo.extItemDefPower;

	if( m_characterPInfo.bodyState == 1 || m_characterPInfo.bodyState == 2 )
		v9 = v9 * 50 / 100;

	int v = this->GetEffective(EFST_LKCONCENTRATION, 0);
	if( this->GetEffective(EFST_LKCONCENTRATION, 0) )
		v9 = v9 * (100 - this->GetEffective(EFST_LKCONCENTRATION, 0) / 2) / 100;

	if( this->GetEffective(EFST_DEFENCE, 0) == 1 )
		v9 = v9 * 2;

	if( !isClient )
	{
		int v13 = m_enemyInfo.size();
		if( v13 >= 3 )
		{
			if( v13 > 22 )
				v13 = 22;

			return v9 * (100 - 5 * (v13 - 2)) / 100;
		}

		if( this->CPC::GetCategorySecondJob() == JT_CRUSADER && m_pcSkill.m_spellCastingSKID == SKID_CR_GRANDCROSS )
			v9 = v9 * 2 / 3;
	}

	if( m_characterInfo.extDEFPercent != 100.0 )
		v9 = (int)((double)v9 * m_characterInfo.extDEFPercent / 100.0);

	return v9;
}


hook_method<int (CPC::*)(void)> CPC::_GetAvoidableSucPerOnClient(SERVER, "CPC::GetAvoidableSucPerOnClient");
int CPC::GetAvoidableSucPerOnClient(void)
{
	return (this->*_GetAvoidableSucPerOnClient)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetPlusAvoidableSucPerOnClient(SERVER, "CPC::GetPlusAvoidableSucPerOnClient");
int CPC::GetPlusAvoidableSucPerOnClient(void)
{
	return (this->*_GetPlusAvoidableSucPerOnClient)();

	//TODO
}


hook_method<void (CPC::*)(const REPAIRITEM_INFO& in_TargetItemInfo)> CPC::_ReqItemRepair(SERVER, "CPC::ReqItemRepair");
void CPC::ReqItemRepair(const REPAIRITEM_INFO& in_TargetItemInfo)
{
	return (this->*_ReqItemRepair)(in_TargetItemInfo);

	//TODO
}


hook_method<void (CPC::*)(short index)> CPC::_ReqWeaponRefine(SERVER, "CPC::ReqWeaponRefine");
void CPC::ReqWeaponRefine(short index)
{
	return (this->*_ReqWeaponRefine)(index);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsDamageMotionPossible(SERVER, "CPC::IsDamageMotionPossible");
int CPC::IsDamageMotionPossible(void)
{
	return (this->*_IsDamageMotionPossible)();

	//TODO
}


hook_method<int (CPC::*)(int property)> CPC::_IsRightProperty(SERVER, "CPC::IsRightProperty");
int CPC::IsRightProperty(int property)
{
	return (this->*_IsRightProperty)(property);

	return (this->CPC::GetCurrentState() % 10 == property);
}


hook_method<int (CPC::*)(void)> CPC::_IsMovable(SERVER, "CPC::IsMovable");
int CPC::IsMovable(void) // line 6795
{
	return (this->*_IsMovable)();

	//TODO
}


hook_method<int (CPC::*)(int race, int _class, int level)> CPC::_IsAvoidable(SERVER, "CPC::IsAvoidable");
int CPC::IsAvoidable(int race, int _class, int level)
{
	return (this->*_IsAvoidable)(race, _class, level);

	//TODO
}


BOOL CPC::IsAttackable(unsigned short SKID)
{
	if( m_pcBattle.m_isReflectedMAGIC )
		return TRUE;

	if( m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemWeightByPercent() >= 90 )
		return FALSE;

	if( this->GetEffective(EFST_NOACTION, 0)
	 || this->GetEffective(EFST_BLADESTOP, 0) )
		return FALSE;

	if( this->GetEffective(EFST_LONGING, 0) )
	{
		if( SKID != 0 && g_skillTypeInfoMgr->CSkillTypeInfoMgr::IsSkillCategory(SKID, 2) )
			return FALSE;
	}
	else
	{
		if( this->GetEffective(EFST_BDPLAYING, 0)
		 && SKID != SKID_BA_MUSICALSTRIKE
		 && SKID != SKID_DC_THROWARROW
		 && SKID != SKID_BA_DISSONANCE
		 && SKID != SKID_CG_LONGINGFREEDOM )
			return FALSE;
	}

	if( this->GetEffective(EFST_GOSPEL, 0) && this->GetEffective(EFST_GOSPEL, 0) <= 10
	 || this->GetEffective(EFST_BASILICA, 0)
	 || this->GetEffective(EFST_CHASEWALK, 0)
	 || this->GetEffective(EFST_CRYSTAL, 0) )
		 return FALSE;

	int bodyState = this->CPC::GetBodyState();
	if( bodyState == BODYSTATE_STONECURSE_ING
	 || bodyState == BODYSTATE_FREEZING
	 || bodyState == BODYSTATE_STONECURSE
	 || bodyState == BODYSTATE_SLEEP
	 || bodyState == BODYSTATE_STUN
	 || bodyState == BODYSTATE_IMPRISON )
		 return FALSE;

	if( this->CPC::GetRoomID() != 0 )
		return FALSE;

	if( this->CPC::IsMCStoreOpen() )
		return FALSE;

	bool isHidingSkill = false;
	switch( SKID )
	{
	case SKID_AS_GRIMTOOTH:
	case SKID_RG_BACKSTAP:
	case SKID_RG_RAID:
	case SKID_NJ_KIRIKAGE:
	case SKID_DE_SLASH:
		isHidingSkill = true;
	break;
	};

	if( !isHidingSkill && this->CPC::GetEffectState() & EFFECTSTATE_BURROW )
		return FALSE;

	if( this->IsInitingState() )
		m_loadingCompleteTime = 0;

	if( this->GetEffectState() & EFFECTSTATE_MARRIED )
		return FALSE;

	if( this->GetEffectState() & (EFFECTSTATE_SANTA | EFFECTSTATE_SUMMER) )
		return FALSE;

	if( (this->GetEffectState() >> 17) & 1 )
		return FALSE;

	return TRUE;
}


hook_method<int (CPC::*)(void)> CPC::_IsPickable(SERVER, "CPC::IsPickable");
int CPC::IsPickable(void)
{
	return (this->*_IsPickable)();

	if(this->GetEffective(EFST_NOACTION, 0)
	|| this->GetEffective(EFST_CLOAKING, 0)
	|| this->GetEffective(EFST_IMPOSSIBLEPICKUP, 0)
	|| this->GetEffective(EFST_NOACTION_WAIT, 0)
	|| this->GetEffective(EFST_CRYSTAL, 0)
	|| this->GetState() == 5
	|| m_characterPInfo.bodyState == 2
	|| m_characterPInfo.bodyState == 6
	|| m_characterPInfo.bodyState == 1
	|| m_characterPInfo.bodyState == 4
	|| m_characterPInfo.bodyState == 3
	|| this->CPC::GetRoomID()
	|| m_pcSkill.m_spellCastingSKID != 0
	)
		return 0;

	return 1;
}


hook_method<int (CPC::*)(unsigned short SKID)> CPC::_IsSkillUsable(SERVER, "CPC::IsSkillUsable");
int CPC::IsSkillUsable(unsigned short SKID)
{
	return (this->*_IsSkillUsable)(SKID);

	//TODO
}


hook_method<int (CPC::*)(int SKID, int level, CCharacter* ch)> CPC::_IsSkillEnable(SERVER, "CPC::IsSkillEnable");
int CPC::IsSkillEnable(int SKID, int level, CCharacter* ch)
{
	return (this->*_IsSkillEnable)(SKID, level, ch);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsSitable(SERVER, "CPC::IsSitable");
int CPC::IsSitable(void)
{
	return (this->*_IsSitable)();

	//TODO
}


hook_method<int (CPC::*)(CCharacter* other, int plusVal)> CPC::_IsCritical(SERVER, "CPC::IsCritical");
int CPC::IsCritical(CCharacter* other, int plusVal)
{
	return (this->*_IsCritical)(other, plusVal);

	//TODO
}


hook_method<int (CPC::*)(unsigned long NAID)> CPC::_IsTouchableState(SERVER, "CPC::IsTouchableState");
int CPC::IsTouchableState(unsigned long NAID)
{
	return (this->*_IsTouchableState)(NAID);

	//TODO
}


hook_method<void (CPC::*)(unsigned long NAID)> CPC::_AddTouchNPCList(SERVER, "CPC::AddTouchNPCList");
void CPC::AddTouchNPCList(unsigned long NAID)
{
	return (this->*_AddTouchNPCList)(NAID);

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetCriticalSuccessValue(SERVER, "CPC::GetCriticalSuccessValue");
short CPC::GetCriticalSuccessValue(void)
{
	return (this->*_GetCriticalSuccessValue)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetPlusAttRange(SERVER, "CPC::GetPlusAttRange");
int CPC::GetPlusAttRange(void) // line 11293
{
	return (this->*_GetPlusAttRange)();

	//TODO
}


hook_method<void (CPC::*)(unsigned long firstTime, unsigned long secondTime, int state)> CPC::_SetBodyStateTimeInfo(SERVER, "CPC::SetBodyStateTimeInfo");
void CPC::SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state)
{
	return (this->*_SetBodyStateTimeInfo)(firstTime, secondTime, state);

	//TODO
}


hook_method<void (CPC::*)(int firstTime, int secondTime, int state)> CPC::_SetHealthStateTimeInfo(SERVER, "CPC::SetHealthStateTimeInfo");
void CPC::SetHealthStateTimeInfo(int firstTime, int secondTime, int state)
{
	return (this->*_SetHealthStateTimeInfo)(firstTime, secondTime, state);

	//TODO
}


hook_method<void (CPC::*)(unsigned long time, int skillID)> CPC::_SetInvincibleTimeInfo(SERVER, "CPC::SetInvincibleTimeInfo");
void CPC::SetInvincibleTimeInfo(unsigned long time, int skillID)
{
	return (this->*_SetInvincibleTimeInfo)(time, skillID);

	//TODO
}


hook_method<int (CPC::*)(int skillID)> CPC::_GetInvincibleTimeInfo(SERVER, "CPC::GetInvincibleTimeInfo");
int CPC::GetInvincibleTimeInfo(int skillID)
{
	return (this->*_GetInvincibleTimeInfo)(skillID);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetSpeed(SERVER, "CPC::GetSpeed");
int CPC::GetSpeed(void)
{
	return (this->*_GetSpeed)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetAttackHasteValue1(SERVER, "CPC::GetAttackHasteValue1");
int CPC::GetAttackHasteValue1(void)
{
	return (this->*_GetAttackHasteValue1)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetAttackHasteValue2(SERVER, "CPC::GetAttackHasteValue2");
int CPC::GetAttackHasteValue2(void)
{
	return (this->*_GetAttackHasteValue2)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetAttackSlowValue(SERVER, "CPC::GetAttackSlowValue");
int CPC::GetAttackSlowValue(void)
{
	return (this->*_GetAttackSlowValue)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetMoveHasteValue1(SERVER, "CPC::GetMoveHasteValue1");
int CPC::GetMoveHasteValue1(void)
{
	return (this->*_GetMoveHasteValue1)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetMoveHasteValue2(SERVER, "CPC::GetMoveHasteValue2");
int CPC::GetMoveHasteValue2(void)
{
	return (this->*_GetMoveHasteValue2)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetMoveSlowValue(SERVER, "CPC::GetMoveSlowValue");
int CPC::GetMoveSlowValue(void)
{
	return (this->*_GetMoveSlowValue)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetBodyMaxItemWeight(SERVER, "CPC::GetBodyMaxItemWeight");
int CPC::GetBodyMaxItemWeight(void)
{
	return (this->*_GetBodyMaxItemWeight)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetCartMaxItemWeight(SERVER, "CPC::GetCartMaxItemWeight");
int CPC::GetCartMaxItemWeight(void)
{
	return (this->*_GetCartMaxItemWeight)();

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_GetBodyMaxItemSize(SERVER, "CPC::GetBodyMaxItemSize");
int CPC::GetBodyMaxItemSize(void)
{
//	return (this->*_GetBodyMaxItemSize)();

	return 100;
}


//hook_method<int (CPC::*)(void)> CPC::_GetCartMaxItemSize(SERVER, "CPC::GetCartMaxItemSize");
int CPC::GetCartMaxItemSize(void)
{
//	return (this->*_GetCartMaxItemSize)();

	return 100;
}


hook_method<int (CPC::*)(void)> CPC::_GetStoreMaxItemSize(SERVER, "CPC::GetStoreMaxItemSize");
int CPC::GetStoreMaxItemSize(void)
{
	return (this->*_GetStoreMaxItemSize)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetBodyItemWeight(SERVER, "CPC::GetBodyItemWeight");
int CPC::GetBodyItemWeight(void)
{
	return (this->*_GetBodyItemWeight)();

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_GetExchangeMaxItemSize(SERVER, "CPC::GetExchangeMaxItemSize");
int CPC::GetExchangeMaxItemSize(void)
{
//	return (this->*_GetExchangeMaxItemSize)();

	return 10;
}


//hook_method<int (CPC::*)(void)> CPC::_GetMailMaxItemSize(SERVER, "CPC::GetMailMaxItemSize");
int CPC::GetMailMaxItemSize(void)
{
//	return (this->*_GetMailMaxItemSize)();

	return 1;
}


//hook_method<int (CPC::*)(void)> CPC::_GetMCStoreMaxSize(SERVER, "CPC::GetMCStoreMaxSize");
int CPC::GetMCStoreMaxSize(void)
{
//	return (this->*_GetMCStoreMaxSize)();

	 return 10;
}


//hook_method<void (CPC::*)(char* dir, char* fileName)> CPC::_SetChatLog(SERVER, "CPC::SetChatLog");
void CPC::SetChatLog(char* dir, char* fileName)
{
//	return (this->*_SetChatLog)(dir, fileName);

	return;
}


//hook_method<void (CPC::*)(char* buf, int len)> CPC::_InsertChatLog(SERVER, "CPC::InsertChatLog");
void CPC::InsertChatLog(char* buf, int len)
{
//	return (this->*_InsertChatLog)(buf, len);

	return;
}


hook_method<int (CPC::*)(unsigned long AID)> CPC::_IsMyPartyMember(SERVER, "CPC::IsMyPartyMember");
int CPC::IsMyPartyMember(unsigned long AID)
{
	return (this->*_IsMyPartyMember)(AID);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsPKModeON(SERVER, "CPC::IsPKModeON");
int CPC::IsPKModeON(void)
{
	return (this->*_IsPKModeON)();

	//TODO
}


hook_method<int (CPC::*)(int SKID, int xPos, int yPos, int param)> CPC::_IsRightForm(SERVER, "CPC::IsRightForm");
int CPC::IsRightForm(int SKID, int xPos, int yPos, int param)
{
	return (this->*_IsRightForm)(SKID, xPos, yPos, param);

	//TODO
}


hook_method<void (CPC::*)(bool flag)> CPC::_ChangePKMode(SERVER, "CPC::ChangePKMode");
void CPC::ChangePKMode(bool flag)
{
	return (this->*_ChangePKMode)(flag);

	//TODO
}


hook_method<void (CPC::*)(unsigned long AID, short xPos, short yPos)> CPC::_InformAttFailureForDistance(SERVER, "CPC::InformAttFailureForDistance");
void CPC::InformAttFailureForDistance(unsigned long AID, short xPos, short yPos)
{
	return (this->*_InformAttFailureForDistance)(AID, xPos, yPos);

	//TODO
}


//hook_method<void (CPC::*)(void)> CPC::_ResetStatus(SERVER, "CPC::ResetStatus");
void CPC::ResetStatus(void)
{
//	return (this->*_ResetStatus)();

	m_characterInfo.AgiAmount = 0;
	m_characterInfo.VitAmount = 0;
	m_characterInfo.DexAmount = 0;
	m_characterInfo.IntAmount = 0;
	m_characterInfo.StrAmount = 0;
	m_characterInfo.LukAmount = 0;
}


hook_method<void (CPC::*)(void)> CPC::_Act_EFST_KAAHI(SERVER, "CPC::Act_EFST_KAAHI");
void CPC::Act_EFST_KAAHI(void)
{
	return (this->*_Act_EFST_KAAHI)();

	//TODO
}


hook_method<int (CPC::*)(CCharacter* tar_ch)> CPC::_Act_EFST_DWARNING(SERVER, "CPC::Act_EFST_DWARNING");
int CPC::Act_EFST_DWARNING(CCharacter* tar_ch)
{
	return (this->*_Act_EFST_DWARNING)(tar_ch);

	//TODO
}


hook_method<int (CPC::*)(CCharacter* tar_ch, int isRangeAttack)> CPC::_Act_EFST_DBLOCK(SERVER, "CPC::Act_EFST_DBLOCK");
int CPC::Act_EFST_DBLOCK(CCharacter* tar_ch, int isRangeAttack)
{
	return (this->*_Act_EFST_DBLOCK)(tar_ch, isRangeAttack);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_Act_EFST_KAUPE(SERVER, "CPC::Act_EFST_KAUPE");
int CPC::Act_EFST_KAUPE(void)
{
	return (this->*_Act_EFST_KAUPE)();

	//TODO
}


hook_method<void (CPC::*)(int& delay)> CPC::_ReductionPredelay(SERVER, "CPC::ReductionPredelay");
void CPC::ReductionPredelay(int& delay)
{
	return (this->*_ReductionPredelay)(delay);

	//TODO
}


hook_method<IVItEquipItem* (CPC::*)(unsigned long loc)> CPC::_GetEquipItem(SERVER, "CPC::GetEquipItem");
IVItEquipItem* CPC::GetEquipItem(unsigned long loc)
{
	return (this->*_GetEquipItem)(loc);

	//TODO
}


/* hook_method<int (CPC::*)(void)> CPC::_IsFirstJob(SERVER, "CPC::IsFirstJob");
int CPC::IsFirstJob(void)
{
	return (this->*_IsFirstJob)();

	//TODO
} */


hook_method<int (CPC::*)(void)> CPC::_IsSecondJob(SERVER, "CPC::IsSecondJob");
int CPC::IsSecondJob(void)
{
	return (this->*_IsSecondJob)();

	//TODO
}


/* hook_method<int (CPC::*)(void)> CPC::_IsThirdJob(SERVER, "CPC::IsThirdJob");
int CPC::IsThirdJob(void)
{
	return (this->*_IsThirdJob)();

	//TODO
} */


/* hook_method<int (CPC::*)(CCharacter* target, short healSkillLevel, unsigned short SKID)> CPC::_GetHealAmount(SERVER, "CPC::GetHealAmount");
int CPC::GetHealAmount(CCharacter* target, short healSkillLevel, unsigned short SKID)
{
	return (this->*_GetHealAmount)(target, healSkillLevel, SKID);

	//TODO
} */


hook_method<short (CPC::*)(CCharacter* other, int& damage, int isRangeAttack, int attackType, unsigned long& targetAID, unsigned short SKID, short skLevel)> CPC::_ModifyDamage(SERVER, "CPC::ModifyDamage");
short CPC::ModifyDamage(CCharacter* other, int& damage, int isRangeAttack, int attackType, unsigned long& targetAID, unsigned short SKID, short skLevel)
{
	return (this->*_ModifyDamage)(other, damage, isRangeAttack, attackType, targetAID, SKID, skLevel);

	//TODO
}


hook_method<void (CPC::*)(CNpcMercenary* const in_cpMercenary, int& io_damage, unsigned long& io_TargetAID, const int in_AttackType, const int in_isRangeAttack, const unsigned short in_SKID)> CPC::_ModifyDamage_EFST_DEVOTION(SERVER, "CPC::ModifyDamage_EFST_DEVOTION");
void CPC::ModifyDamage_EFST_DEVOTION(CNpcMercenary* const in_cpMercenary, int& io_damage, unsigned long& io_TargetAID, const int in_AttackType, const int in_isRangeAttack, const unsigned short in_SKID)
{
	return (this->*_ModifyDamage_EFST_DEVOTION)(in_cpMercenary, io_damage, io_TargetAID, in_AttackType, in_isRangeAttack, in_SKID);

	//TODO
}


hook_method<int (CPC::*)(unsigned long targetID)> CPC::_AttackByAutoSpell(SERVER, "CPC::AttackByAutoSpell");
int CPC::AttackByAutoSpell(unsigned long targetID)
{
	return (this->*_AttackByAutoSpell)(targetID);

	//TODO
}


hook_method<void (CPC::*)(unsigned short SKID, short skLevel)> CPC::_SetSpellCasting(SERVER, "CPC::SetSpellCasting");
void CPC::SetSpellCasting(unsigned short SKID, short skLevel)
{
	return (this->*_SetSpellCasting)(SKID, skLevel);

	//TODO
}


//hook_method<unsigned short (CPC::*)(void)> CPC::_GetSpellCasting(SERVER, "CPC::GetSpellCasting");
unsigned short CPC::GetSpellCasting(void)
{
//	return (this->*_GetSpellCasting)();

	return m_pcSkill.m_spellCastingSKID;
}


hook_method<int (CPC::*)(int xPos, int yPos)> CPC::_IsUsableCellforWaterSkill(SERVER, "CPC::IsUsableCellforWaterSkill");
int CPC::IsUsableCellforWaterSkill(int xPos, int yPos)
{
	return (this->*_IsUsableCellforWaterSkill)(xPos, yPos);

	//TODO
}


hook_method<void (CPC::*)(unsigned long AID)> CPC::_AddSpeicalZoneList(SERVER, "CPC::AddSpeicalZoneList");
void CPC::AddSpeicalZoneList(unsigned long AID)
{
	return (this->*_AddSpeicalZoneList)(AID);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_NotifyDevotionList(SERVER, "CPC::NotifyDevotionList");
void CPC::NotifyDevotionList(void)
{
	return (this->*_NotifyDevotionList)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_NotifySpiritsInfo(SERVER, "CPC::NotifySpiritsInfo");
void CPC::NotifySpiritsInfo(void)
{
	return (this->*_NotifySpiritsInfo)();

	//TODO
}


hook_method<void (CPC::*)(int type, int value, int maxValue)> CPC::_NotifyRecoveryValue(SERVER, "CPC::NotifyRecoveryValue");
void CPC::NotifyRecoveryValue(int type, int value, int maxValue)
{
	return (this->*_NotifyRecoveryValue)(type, value, maxValue);

	//TODO
}


hook_method<void (CPC::*)(int type, int value, int maxValue)> CPC::_NotifyRecoveryValue2(SERVER, "CPC::NotifyRecoveryValue2");
void CPC::NotifyRecoveryValue2(int type, int value, int maxValue)
{
	return (this->*_NotifyRecoveryValue2)(type, value, maxValue);

	//TODO
}


hook_method<CNPC* (CPC::*)(int SPRType, int maxHP, int time, int x, int y)> CPC::_SummonMobBySkill(SERVER, "CPC::SummonMobBySkill");
CNPC* CPC::SummonMobBySkill(int SPRType, int maxHP, int time, int x, int y)
{
	return (this->*_SummonMobBySkill)(SPRType, maxHP, time, x, y);

	//TODO
}


hook_method<void (CPC::*)(int spriteType, int value)> CPC::_UpdateCreatedMobCount(SERVER, "CPC::UpdateCreatedMobCount");
void CPC::UpdateCreatedMobCount(int spriteType, int value)
{
	return (this->*_UpdateCreatedMobCount)(spriteType, value);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_DelSpecialZoneList(SERVER, "CPC::DelSpecialZoneList");
void CPC::DelSpecialZoneList(void)
{
	return (this->*_DelSpecialZoneList)();

	//TODO
}


hook_method<void (CPC::*)(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, short level, bool result)> CPC::_NotifyUseSkill(SERVER, "CPC::NotifyUseSkill");
void CPC::NotifyUseSkill(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, short level, bool result)
{
	return (this->*_NotifyUseSkill)(SKID, targetAID, srcAID, level, result);

	PACKET_ZC_USE_SKILL outpacket;
	outpacket.PacketType = HEADER_ZC_USE_SKILL;
	outpacket.SKID = SKID;
	outpacket.srcAID = srcAID;
	outpacket.targetAID = targetAID;
	outpacket.result = result;
	outpacket.level = level;

	this->CPC::Send(sizeof(outpacket), (char *)&outpacket);
	this->CCharacter::MultiCast((char *)&outpacket, sizeof(outpacket));
}


hook_method<short (CPC::*)(void)> CPC::_GetDexValue(SERVER, "CPC::GetDexValue");
short CPC::GetDexValue(void)
{
	return (this->*_GetDexValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetStrValue(SERVER, "CPC::GetStrValue");
short CPC::GetStrValue(void)
{
	return (this->*_GetStrValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetIntValue(SERVER, "CPC::GetIntValue");
short CPC::GetIntValue(void)
{
	return (this->*_GetIntValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetLukValue(SERVER, "CPC::GetLukValue");
short CPC::GetLukValue(void)
{
	return (this->*_GetLukValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetAgiValue(SERVER, "CPC::GetAgiValue");
short CPC::GetAgiValue(void)
{
	return (this->*_GetAgiValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetVitValue(SERVER, "CPC::GetVitValue");
short CPC::GetVitValue(void)
{
	return (this->*_GetVitValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetDefaultDexValue(SERVER, "CPC::GetDefaultDexValue");
short CPC::GetDefaultDexValue(void)
{
	return (this->*_GetDefaultDexValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetDefaultStrValue(SERVER, "CPC::GetDefaultStrValue");
short CPC::GetDefaultStrValue(void)
{
	return (this->*_GetDefaultStrValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetDefaultIntValue(SERVER, "CPC::GetDefaultIntValue");
short CPC::GetDefaultIntValue(void)
{
	return (this->*_GetDefaultIntValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetDefaultLukValue(SERVER, "CPC::GetDefaultLukValue");
short CPC::GetDefaultLukValue(void)
{
	return (this->*_GetDefaultLukValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetDefaultAgiValue(SERVER, "CPC::GetDefaultAgiValue");
short CPC::GetDefaultAgiValue(void)
{
	return (this->*_GetDefaultAgiValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetDefaultVitValue(SERVER, "CPC::GetDefaultVitValue");
short CPC::GetDefaultVitValue(void)
{
	return (this->*_GetDefaultVitValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetDexPlusValue(SERVER, "CPC::GetDexPlusValue");
short CPC::GetDexPlusValue(void)
{
	return (this->*_GetDexPlusValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetStrPlusValue(SERVER, "CPC::GetStrPlusValue");
short CPC::GetStrPlusValue(void)
{
	return (this->*_GetStrPlusValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetIntPlusValue(SERVER, "CPC::GetIntPlusValue");
short CPC::GetIntPlusValue(void)
{
	return (this->*_GetIntPlusValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetLukPlusValue(SERVER, "CPC::GetLukPlusValue");
short CPC::GetLukPlusValue(void)
{
	return (this->*_GetLukPlusValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetAgiPlusValue(SERVER, "CPC::GetAgiPlusValue");
short CPC::GetAgiPlusValue(void)
{
	return (this->*_GetAgiPlusValue)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetVitPlusValue(SERVER, "CPC::GetVitPlusValue");
short CPC::GetVitPlusValue(void)
{
	return (this->*_GetVitPlusValue)();

	//TODO
}


//hook_method<void (CPC::*)(int var)> CPC::_SetPlusDexValueByJob(SERVER, "CPC::SetPlusDexValueByJob");
void CPC::SetPlusDexValueByJob(int var)
{
//	return (this->*_SetPlusDexValueByJob)(var);

	m_plusStatusByJob.Dex = var;
}


//hook_method<void (CPC::*)(int var)> CPC::_SetPlusStrValueByJob(SERVER, "CPC::SetPlusStrValueByJob");
void CPC::SetPlusStrValueByJob(int var)
{
//	return (this->*_SetPlusStrValueByJob)(var);

	m_plusStatusByJob.Str = var;
}


//hook_method<void (CPC::*)(int var)> CPC::_SetPlusIntValueByJob(SERVER, "CPC::SetPlusIntValueByJob");
void CPC::SetPlusIntValueByJob(int var)
{
//	return (this->*_SetPlusIntValueByJob)(var);

	m_plusStatusByJob.Int = var;
}


//hook_method<void (CPC::*)(int var)> CPC::_SetPlusLukValueByJob(SERVER, "CPC::SetPlusLukValueByJob");
void CPC::SetPlusLukValueByJob(int var)
{
//	return (this->*_SetPlusLukValueByJob)(var);

	m_plusStatusByJob.Luk = var;
}


//hook_method<void (CPC::*)(int var)> CPC::_SetPlusAgiValueByJob(SERVER, "CPC::SetPlusAgiValueByJob");
void CPC::SetPlusAgiValueByJob(int var)
{
//	return (this->*_SetPlusAgiValueByJob)(var);

	m_plusStatusByJob.Agi = var;
}


//hook_method<void (CPC::*)(int var)> CPC::_SetPlusVitValueByJob(SERVER, "CPC::SetPlusVitValueByJob");
void CPC::SetPlusVitValueByJob(int var)
{
//	return (this->*_SetPlusVitValueByJob)(var);

	m_plusStatusByJob.Vit = var;
}


hook_method<int (CPC::*)(void)> CPC::_IsMCStoreOpen(SERVER, "CPC::IsMCStoreOpen");
int CPC::IsMCStoreOpen(void)
{
	return (this->*_IsMCStoreOpen)();

	return m_pcitemInventoryMgr.CPCItemInventoryMgr::IsMCStoreOpen();
}


hook_method<int (CPC::*)(void)> CPC::_IsWarpPossible(SERVER, "CPC::IsWarpPossible");
int CPC::IsWarpPossible(void)
{
	return (this->*_IsWarpPossible)();

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_IsValid(SERVER, "CPC::IsValid");
int CPC::IsValid(void)
{
//	return (this->*_IsValid)();

	return m_isValid;
}


hook_method<int (CPC::*)(void)> CPC::_GetAvoidableSuccessPercent(SERVER, "CPC::GetAvoidableSuccessPercent");
int CPC::GetAvoidableSuccessPercent(void)
{
	return (this->*_GetAvoidableSuccessPercent)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetStatusAttPower(SERVER, "CPC::GetStatusAttPower");
short CPC::GetStatusAttPower(void)
{
	return (this->*_GetStatusAttPower)();

	return LOWORD(m_characterInfo.statusAttPower);
}


hook_method<short (CPC::*)(int itemLevel, int type, int position)> CPC::_GetItemAttPower(SERVER, "CPC::GetItemAttPower");
short CPC::GetItemAttPower(int itemLevel, int type, int position)
{
	return (this->*_GetItemAttPower)(itemLevel, type, position);

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetMagicAttMaxPowOnClient(SERVER, "CPC::GetMagicAttMaxPowOnClient");
short CPC::GetMagicAttMaxPowOnClient(void)
{
	return (this->*_GetMagicAttMaxPowOnClient)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetMagicAttMinPowOnClient(SERVER, "CPC::GetMagicAttMinPowOnClient");
short CPC::GetMagicAttMinPowOnClient(void)
{
	return (this->*_GetMagicAttMinPowOnClient)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetItemMagicDef(SERVER, "CPC::GetItemMagicDef");
short CPC::GetItemMagicDef(void)
{
	return (this->*_GetItemMagicDef)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetStatusMagicDef(SERVER, "CPC::GetStatusMagicDef");
short CPC::GetStatusMagicDef(void)
{
	return (this->*_GetStatusMagicDef)();

	//TODO
}


hook_method<int (CPC::*)(CCharacter* other, int plusATTPowerPercent, int plusATTSuccessPercent, unsigned short SKID)> CPC::_GetMagicAttackFinalDamage(SERVER, "CPC::GetMagicAttackFinalDamage");
int CPC::GetMagicAttackFinalDamage(CCharacter* other, int plusATTPowerPercent, int plusATTSuccessPercent, unsigned short SKID)
{
	return (this->*_GetMagicAttackFinalDamage)(other, plusATTPowerPercent, plusATTSuccessPercent, SKID);

	//TODO
}


hook_method<void (CPC::*)(int type)> CPC::_HealStatus(SERVER, "CPC::HealStatus");
void CPC::HealStatus(int type)
{
	return (this->*_HealStatus)(type);

	//TODO
}


hook_method<void (CPC::*)(unsigned long errorCode)> CPC::_NotifyActionFailure(SERVER, "CPC::NotifyActionFailure");
void CPC::NotifyActionFailure(unsigned long errorCode)
{
	return (this->*_NotifyActionFailure)(errorCode);

	//TODO
}


hook_method<void (CPC::*)(unsigned short index)> CPC::_NotifyArrowEquiped(SERVER, "CPC::NotifyArrowEquiped");
void CPC::NotifyArrowEquiped(unsigned short index)
{
	return (this->*_NotifyArrowEquiped)(index);

	//TODO
}


hook_method<CITP* (CPC::*)(void)> CPC::_GetITPEquipedWeapon(SERVER, "CPC::GetITPEquipedWeapon");
CITP* CPC::GetITPEquipedWeapon(void)
{
	return (this->*_GetITPEquipedWeapon)();

	//TODO
}


hook_method<int (CPC::*)(unsigned short itmNum, int count, IVItItem* p)> CPC::_ConsumeItem(SERVER, "CPC::ConsumeItem");
int CPC::ConsumeItem(unsigned short itmNum, int count, IVItItem* p)
{
	return (this->*_ConsumeItem)(itmNum, count, p);

	//TODO
}


hook_method<int (CPC::*)(unsigned short itmNum, int count)> CPC::_ConsumeItemForSkill(SERVER, "CPC::ConsumeItemForSkill");
int CPC::ConsumeItemForSkill(unsigned short itmNum, int count)
{
	return (this->*_ConsumeItemForSkill)(itmNum, count);

	//TODO
}


/* hook_method<int (CPC::*)(unsigned short itemNum, int count, int spCost)> CPC::_ConsumeJamstone(SERVER, "CPC::ConsumeJamstone");
int CPC::ConsumeJamstone(unsigned short itemNum, int count, int spCost)
{
	return (this->*_ConsumeJamstone)(itemNum, count, spCost);

	//TODO
} */


hook_method<int (CPC::*)(short cnt)> CPC::_ConsumeEquipedArrow(SERVER, "CPC::ConsumeEquipedArrow");
int CPC::ConsumeEquipedArrow(short cnt)
{
	return (this->*_ConsumeEquipedArrow)(cnt);

	//TODO
}


hook_method<unsigned long (CPC::*)(void)> CPC::_GetGroupIDIFexpShare(SERVER, "CPC::GetGroupIDIFexpShare");
unsigned long CPC::GetGroupIDIFexpShare(void)
{
	return (this->*_GetGroupIDIFexpShare)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetMaxHP(SERVER, "CPC::GetMaxHP");
int CPC::GetMaxHP(void)
{
	return (this->*_GetMaxHP)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetMaxSP(SERVER, "CPC::GetMaxSP");
short CPC::GetMaxSP(void)
{
	return (this->*_GetMaxSP)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetAttackMotionTime(SERVER, "CPC::GetAttackMotionTime");
int CPC::GetAttackMotionTime(void)
{
	return (this->*_GetAttackMotionTime)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetAttackedMotionTime(SERVER, "CPC::GetAttackedMotionTime");
int CPC::GetAttackedMotionTime(void)
{
	return (this->*_GetAttackedMotionTime)();

	//TODO
}


hook_method<void (CPC::*)(unsigned long targetAID, int contentLength, char* buf)> CPC::_PurchaseItemFromMCStore(SERVER, "CPC::PurchaseItemFromMCStore");
void CPC::PurchaseItemFromMCStore(unsigned long targetAID, int contentLength, char* buf)
{
	return (this->*_PurchaseItemFromMCStore)(targetAID, contentLength, buf);

	//TODO
}


hook_method<void (CPC::*)(unsigned long NAID, unsigned char type)> CPC::_SelectDealType(SERVER, "CPC::SelectDealType");
void CPC::SelectDealType(unsigned long NAID, unsigned char type)
{
	return (this->*_SelectDealType)(NAID, type);

	//TODO
}


hook_method<void (CPC::*)(int leftLen, char* buf)> CPC::_PurchaseItem(SERVER, "CPC::PurchaseItem");
void CPC::PurchaseItem(int leftLen, char* buf)
{
	return (this->*_PurchaseItem)(leftLen, buf);

	//TODO
}


hook_method<void (CPC::*)(int leftLen, char* buf)> CPC::_SellItem(SERVER, "CPC::SellItem");
void CPC::SellItem(int leftLen, char* buf)
{
	return (this->*_SellItem)(leftLen, buf);

	//TODO
}


hook_method<void (CPC::*)(unsigned long AID)> CPC::_ReqExchangeItem(SERVER, "CPC::ReqExchangeItem");
void CPC::ReqExchangeItem(unsigned long AID) // line 12542-12630
{
	return (this->*_ReqExchangeItem)(AID);

	if( g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(this, SKID_NV_BASIC, 0, m_pcSkill.CPCSkill::GetSkillLevel(SKID_NV_BASIC, 0), 0, 0, MSGpar::CVar(0)) == 0 )
	{
		this->SkillUseAck(SKID_NV_BASIC, 0, false, 0);
		return; // not enough basic skill
	}

	CPC* other = m_neighborCache.CNeighborCache::FindPC(AID);
	if( other == NULL || other == this )
	{
		PACKET_ZC_ACK_EXCHANGE_ITEM outpacket;
		outpacket.result = 1;
		outpacket.PacketType = HEADER_ZC_ACK_EXCHANGE_ITEM;
		this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		return; // invalid target
	}

	if( g_ForeignCode == 5 )
	{
		if ( m_PCBangInfo.isPCBang == 1 && m_PCBangInfo.ExpFactor == 0.0 )
			return; // TODO interpret
	}
	else if( g_ForeignCode == 2 )
	{
		if( m_PCBangInfo.isPCBang == 1 && m_PCBangInfo.PremiumType == 0 )
			return; // TODO interpret
		if( other->m_PCBangInfo.isPCBang == 1 && other->m_PCBangInfo.PremiumType == 0 )
			return; // TODO interpret
	}

	if( g_zoneScript->CZoneScript::SearchID(other->m_characterInfo.accountName, CHECK_ITEM_RESTRICT) == 1 )
		return; // TODO interpret (can't trade in map?)

	if( this->IsMyArea(other, 2) == 0 )
	{
		PACKET_ZC_ACK_EXCHANGE_ITEM outpacket;
		outpacket.result = 0;
		outpacket.PacketType = HEADER_ZC_ACK_EXCHANGE_ITEM;
		this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		return; // out of range
	}

	if ( other->m_exchangeItemInfo.AID || other->CPC::IsItemMovable() == 0 )
	{
		PACKET_ZC_ACK_EXCHANGE_ITEM outpacket;
		outpacket.result = 2;
		outpacket.PacketType = HEADER_ZC_ACK_EXCHANGE_ITEM;
		this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		return; // TODO interpret (already trading?)
	}

	if( other->CPC::GetBodyMaxItemWeight() < other->CPC::GetBodyItemWeight()
		|| this->CPC::GetBodyMaxItemWeight() < this->CPC::GetBodyItemWeight() )
	{
		PACKET_ZC_ACK_EXCHANGE_ITEM outpacket;
		outpacket.result = 2;
		outpacket.PacketType = HEADER_ZC_ACK_EXCHANGE_ITEM;
		this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		return; // TODO interpret (over weight?)
	}

	if( m_exchangeItemInfo.AID != 0 )
		g_characterMgr->CCharacterMgr::SendMsg(this, m_exchangeItemInfo.AID, CM_EXCHANGE_ITEM_CANCEL, 0, 0, 0, 0);

	if( this->CPC::IsMCStoreOpen() != 0 || other->CPC::IsMCStoreOpen() != 0 )
		return; // TODO interpret (storage is open?)

	PACKET_ZC_REQ_EXCHANGE_ITEM2 outpacket;
	outpacket.PacketType = HEADER_ZC_REQ_EXCHANGE_ITEM2;
	outpacket.level = m_characterInfo.clevel;
	outpacket.GID = m_characterInfo.characterID;
	memcpy(outpacket.name, m_characterInfo.characterName, sizeof(outpacket.name));

	other->m_exchangeItemInfo.AID = m_characterInfo.accountID;
	m_exchangeItemInfo.AID = other->GetAccountID();

	other->CPC::Send(sizeof(outpacket), (char *)&outpacket);
}


hook_method<void (CPC::*)(unsigned char result)> CPC::_AckReqExchangeItem(SERVER, "CPC::AckReqExchangeItem");
void CPC::AckReqExchangeItem(unsigned char result) // line 12633-12668
{
	return (this->*_AckReqExchangeItem)(result);

	CPC* other = m_neighborCache.CNeighborCache::FindPC(m_exchangeItemInfo.AID);
	if( other == NULL )
	{
		g_characterMgr->CCharacterMgr::SendMsg(NULL, this, CM_EXCHANGE_ITEM_CANCEL, 0, 0, 0, MSGpar::CVar(0));
		return; // target not found
	}

	if( this->IsMyArea(other, 2) == 0 )
	{
		g_characterMgr->CCharacterMgr::SendMsg(NULL, this, CM_EXCHANGE_ITEM_CANCEL, 0, 0, 0, MSGpar::CVar(0));
		if( other->m_exchangeItemInfo.AID == this->m_characterInfo.accountID )
			g_characterMgr->CCharacterMgr::SendMsg(NULL, other, CM_EXCHANGE_ITEM_CANCEL, 0, 0, 0, MSGpar::CVar(0));
		return; // out of range
	}

	if( result == 4 )
	{
		other->m_exchangeItemInfo.AID = 0;
		this->m_exchangeItemInfo.AID = 0;
		return; // cancelled
	}

	PACKET_ZC_ACK_EXCHANGE_ITEM2 outpacket;
	outpacket.PacketType = HEADER_ZC_ACK_EXCHANGE_ITEM2;
	outpacket.result = result;
	outpacket.level = m_characterInfo.clevel;
	outpacket.GID = m_characterInfo.characterID;

	other->CPC::Send(sizeof(outpacket), (char*)&outpacket);

	outpacket.level = other->m_characterInfo.clevel;
	outpacket.GID = other->m_characterInfo.characterID;

	this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
}


hook_method<void (CPC::*)(short index, int count)> CPC::_AddExchangeItem(SERVER, "CPC::AddExchangeItem");
void CPC::AddExchangeItem(short index, int count)
{
	return (this->*_AddExchangeItem)(index, count);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_ConcludeExchangeItem(SERVER, "CPC::ConcludeExchangeItem");
void CPC::ConcludeExchangeItem(void)
{
	return (this->*_ConcludeExchangeItem)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_CancelExchangeItem(SERVER, "CPC::CancelExchangeItem");
void CPC::CancelExchangeItem(void)
{
	return (this->*_CancelExchangeItem)();

	//TODO
}


hook_method<void (CPC::*)(int len, char* buf)> CPC::_Send(SERVER, "CPC::Send");
void CPC::Send(int len, char* buf)
{
	return (this->*_Send)(len, buf);

	if( this->CPC::IsSendable() )
	{
		m_lastSendTime = timeGetTime();
		if( buf[0] == 0x00 )
			Sleep(0);
		m_asyncStream->CAsyncStream::Send(len, buf);
	}
}


hook_method<void (CPC::*)(int len, char* buf)> CPC::_ForceSend(SERVER, "CPC::ForceSend");
void CPC::ForceSend(int len, char* buf)
{
	return (this->*_ForceSend)(len, buf);

	m_lastSendTime = timeGetTime();
	m_asyncStream->CAsyncStream::Send(len, buf);
}


hook_method<void (CPC::*)(Request* request)> CPC::_OnDispatchClientRequest(SERVER, "CPC::OnDispatchClientRequest");
void CPC::OnDispatchClientRequest(Request* request)
{
	return (this->*_OnDispatchClientRequest)(request);

	this->m_pcitemInventoryMgr.OnDispatchClientRequest(request);
}


//hook_method<void (CPC::*)(void)> CPC::_CloseStore(SERVER, "CPC::CloseStore");
void CPC::CloseStore(void)
{
//	return (this->*_CloseStore)();

	this->m_pcitemInventoryMgr.CPCItemInventoryMgr::CloseStore();
}


//hook_method<int (CPC::*)(void)> CPC::_IsStoreOpen(SERVER, "CPC::IsStoreOpen");
int CPC::IsStoreOpen(void)
{
//	return (this->*_IsStoreOpen)();

	return this->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsStoreOpen();
}


hook_method<void (CPC::*)(MAKABLEITEM_INFO* info)> CPC::_ReqMakingItem(SERVER, "CPC::ReqMakingItem");
void CPC::ReqMakingItem(MAKABLEITEM_INFO* info)
{
	return (this->*_ReqMakingItem)(info);

	if( info == NULL )
		return;

	PACKET_ZC_ACK_REQMAKINGITEM outpacket;
	outpacket.PacketType = 399;
	outpacket.ITID = info->ITID;

	for( int i = 0; i < countof(info->material_ID); ++i )
	{
		int ITID = info->material_ID[i];
		if( ITID == 0 )
			continue;

		IVItItem* item = m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByID(0, ITID);
		if( item == NULL )
		{
			outpacket.result = 1;
			this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
			return;
		}

		m_pcitemInventoryMgr.CPCItemInventoryMgr::DeleteItem(0, item->m_index, 1);
	}

	if( m_pcSkill.CPCSkill::IsMakableItemBySkill(info->ITID)
	&&  m_pcSkill.CPCSkill::IsMakableItemByItem(info->ITID)
	&&  m_pcSkill.CPCSkill::ManufactureItem(info->ITID, 1, info) )
	{
		outpacket.result = 0;
		this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		this->CPC::MulticastEffect(3);
		g_makingLog->CMakingLog::AddMakingLog(this, 1, info->ITID, info->material_ID[0], info->material_ID[1], info->material_ID[2]);
	}
	else
	{
		outpacket.result = 1;
		this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
		this->CPC::MulticastEffect(2);
		g_makingLog->CMakingLog::AddMakingLog(this, 0, info->ITID, info->material_ID[0], info->material_ID[1], info->material_ID[2]);
	}
}


hook_method<void (CPC::*)(unsigned long GID)> CPC::_ReqNameByGID(SERVER, "CPC::ReqNameByGID");
void CPC::ReqNameByGID(unsigned long GID)
{
	return (this->*_ReqNameByGID)(GID);

	//TODO
}


hook_method<void (CPC::*)(int money)> CPC::_AddMoney(SERVER, "CPC::AddMoney");
void CPC::AddMoney(int money)
{
	return (this->*_AddMoney)(money);

	//TODO
}


hook_method<void (CPC::*)(int money)> CPC::_DeleteMoney(SERVER, "CPC::DeleteMoney");
void CPC::DeleteMoney(int money)
{
	return (this->*_DeleteMoney)(money);

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_GetMoney(SERVER, "CPC::GetMoney");
int CPC::GetMoney(void)
{
//	return (this->*_GetMoney)();

	return m_characterInfo.money;
}


/* //hook_method<void (CPC::*)(int len, char* buf)> CPC::_OnReqOpenMCStore(SERVER, "CPC::OnReqOpenMCStore");
void CPC::OnReqOpenMCStore(int len, char* buf)
{
//	return (this->*_OnReqOpenMCStore)(len, buf);

	this->m_pcitemInventoryMgr.CPCItemInventoryMgr::OnReqOpenMCStore(len, buf);
} */


hook_method<void (CPC::*)(unsigned long AID)> CPC::_OnReqItemListFromMCStore(SERVER, "CPC::OnReqItemListFromMCStore");
void CPC::OnReqItemListFromMCStore(unsigned long AID)
{
	return (this->*_OnReqItemListFromMCStore)(AID);

	//TODO
}


hook_method<void (CPC::*)(unsigned long AID)> CPC::_NotifyMCStore(SERVER, "CPC::NotifyMCStore");
void CPC::NotifyMCStore(unsigned long AID)
{
	return (this->*_NotifyMCStore)(AID);

	//TODO
}


//hook_method<void (CPC::*)(Request* request)> CPC::_Save(SERVER, "CPC::Save");
void CPC::Save(Request* request)
{
//	return (this->*_Save)(request);

	this->m_pcitemInventoryMgr.CPCItemInventoryMgr::Save(request);
}


hook_method<void (CPC::*)(void)> CPC::_CancelMCStore(SERVER, "CPC::CancelMCStore");
void CPC::CancelMCStore(void)
{
	return (this->*_CancelMCStore)();

	//TODO
}


hook_method<double (CPC::*)()> CPC::_GetAttackDistance(SERVER, "CPC::GetAttackDistance");
double CPC::GetAttackDistance()
{
	return (this->*_GetAttackDistance)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_ChkGndSkillDurability(SERVER, "CPC::ChkGndSkillDurability");
int CPC::ChkGndSkillDurability(void)
{
	return (this->*_ChkGndSkillDurability)();

	return ( m_pcSkill.m_sanctuaryCnt > 0 );
}


hook_method<void (CPC::*)(int sppoint)> CPC::_SetSPPoint(SERVER, "CPC::SetSPPoint");
void CPC::SetSPPoint(int sppoint)
{
	return (this->*_SetSPPoint)(sppoint);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnResetStat(SERVER, "CPC::OnResetStat");
void CPC::OnResetStat(void)
{
	return (this->*_OnResetStat)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnResetSkill(SERVER, "CPC::OnResetSkill");
void CPC::OnResetSkill(void)
{
	return (this->*_OnResetSkill)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_InitEnemyInfo(SERVER, "CPC::InitEnemyInfo");
void CPC::InitEnemyInfo(void)
{
	return (this->*_InitEnemyInfo)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsInitingState(SERVER, "CPC::IsInitingState");
int CPC::IsInitingState(void)
{
	return (this->*_IsInitingState)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsLucky(SERVER, "CPC::IsLucky");
int CPC::IsLucky(void)
{
	return (this->*_IsLucky)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_PingSend(SERVER, "CPC::PingSend");
void CPC::PingSend(void)
{
	return (this->*_PingSend)();

	//TODO
}


/* hook_method<unsigned long (CPC::*)(void)> CPC::_GetDisconnectTime(SERVER, "CPC::GetDisconnectTime");
unsigned long CPC::GetDisconnectTime(void)
{
	return (this->*_GetDisconnectTime)();

	//TODO
} */


//hook_method<unsigned long (CPC::*)(void)> CPC::_GetIp(SERVER, "CPC::GetIp");
unsigned long CPC::GetIp(void)
{
//	return (this->*_GetIp)();

	return m_ip;
}


//hook_method<CAsyncStream* (CPC::*)(void)> CPC::_GetStream(SERVER, "CPC::GetStream");
CAsyncStream* CPC::GetStream(void)
{
//	return (this->*_GetStream)();

	return m_asyncStream;
}


//hook_method<CharacterInfo* (CPC::*)(void)> CPC::_GetCharacterInfo(SERVER, "CPC::GetCharacterInfo");
CharacterInfo* CPC::GetCharacterInfo(void)
{
//	return (this->*_GetCharacterInfo)();

	return &m_characterInfo;
}


//hook_method<CPCBattle* (CPC::*)(void)> CPC::_GetPCBattle(SERVER, "CPC::GetPCBattle");
CPCBattle* CPC::GetPCBattle(void)
{
//	return (this->*_GetPCBattle)();

	return &m_pcBattle;
}


//hook_method<int (CPC::*)(void)> CPC::_GetDesX(SERVER, "CPC::GetDesX");
int CPC::GetDesX(void)
{
//	return (this->*_GetDesX)();

	return m_pathInfo.m_moveInfo.dxPos;
}


//hook_method<int (CPC::*)(void)> CPC::_GetDesY(SERVER, "CPC::GetDesY");
int CPC::GetDesY(void)
{
//	return (this->*_GetDesY)();

	return m_pathInfo.m_moveInfo.dyPos;
}


//hook_method<int (CPC::*)(void)> CPC::_GetPVPWinPoint(SERVER, "CPC::GetPVPWinPoint");
int CPC::GetPVPWinPoint(void)
{
//	return (this->*_GetPVPWinPoint)();

	return m_pvpWinPoint;
}


//hook_method<void (CPC::*)(int pvpWinPoint)> CPC::_SetPVPWinPoint(SERVER, "CPC::SetPVPWinPoint");
void CPC::SetPVPWinPoint(int pvpWinPoint)
{
//	return (this->*_SetPVPWinPoint)(pvpWinPoint);

	m_pvpWinPoint = pvpWinPoint;
}


hook_method<void (CPC::*)(int winpvpWinPoint)> CPC::_UpdatePVPWinPoint(SERVER, "CPC::UpdatePVPWinPoint");
void CPC::UpdatePVPWinPoint(int winpvpWinPoint)
{
	return (this->*_UpdatePVPWinPoint)(winpvpWinPoint);

	//TODO
}


hook_method<void (CPC::*)(int ranking)> CPC::_SetPVPRanking(SERVER, "CPC::SetPVPRanking");
void CPC::SetPVPRanking(int ranking)
{
	return (this->*_SetPVPRanking)(ranking);

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_GetPVPRanking(SERVER, "CPC::GetPVPRanking");
int CPC::GetPVPRanking(void)
{
//	return (this->*_GetPVPRanking)();

	return m_pvpRanking;
}


//hook_method<void (CPC::*)(int total)> CPC::_SetPVPTotal(SERVER, "CPC::SetPVPTotal");
void CPC::SetPVPTotal(int total)
{
//	return (this->*_SetPVPTotal)(total);

	m_pvpTotal = total;
}


//hook_method<int (CPC::*)(void)> CPC::_GetPVPTotal(SERVER, "CPC::GetPVPTotal");
int CPC::GetPVPTotal(void)
{
//	return (this->*_GetPVPTotal)();

	return m_pvpTotal;
}


hook_method<void (CPC::*)(int effectID)> CPC::_MulticastEffect(SERVER, "CPC::MulticastEffect");
void CPC::MulticastEffect(int effectID)
{
	return (this->*_MulticastEffect)(effectID);

	PACKET_ZC_NOTIFY_EFFECT outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_EFFECT;
	outpacket.AID = this->GetAccountID();
	outpacket.effectID = effectID;
	this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


hook_method<CNPC* (CPC::*)(int spriteType, int xPos, int yPos, const char* mapName, const char* npcName, int parentAID, int npcType)> CPC::_CallMonster(SERVER, "CPC::CallMonster");
CNPC* CPC::CallMonster(int spriteType, int xPos, int yPos, const char* mapName, const char* npcName, int parentAID, int npcType)
{
	return (this->*_CallMonster)(spriteType, xPos, yPos, mapName, npcName, parentAID, npcType);

	//TODO
}


hook_method<void (CPC::*)(IVItEquipItem* item)> CPC::_CallPet(SERVER, "CPC::CallPet");
void CPC::CallPet(IVItEquipItem* item)
{
	return (this->*_CallPet)(item);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_RemovePet(SERVER, "CPC::RemovePet");
void CPC::RemovePet(void)
{
	return (this->*_RemovePet)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetPetRelationship(SERVER, "CPC::GetPetRelationship");
int CPC::GetPetRelationship(void)
{
	return (this->*_GetPetRelationship)();

	//TODO
}


hook_method<void (CPC::*)(int spriteType, int relationship)> CPC::_Gangsi_PetSkill(SERVER, "CPC::Gangsi_PetSkill");
void CPC::Gangsi_PetSkill(int spriteType, int relationship)
{
	return (this->*_Gangsi_PetSkill)(spriteType, relationship);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_Gangsi_ResetEFST(SERVER, "CPC::Gangsi_ResetEFST");
void CPC::Gangsi_ResetEFST(void)
{
	return (this->*_Gangsi_ResetEFST)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsPetActive(SERVER, "CPC::IsPetActive");
int CPC::IsPetActive(void)
{
	return (this->*_IsPetActive)();

	//TODO
}


hook_method<void (CPC::*)(unsigned short id, int value)> CPC::_SetParameterValue(SERVER, "CPC::SetParameterValue");
void CPC::SetParameterValue(unsigned short id, int value)
{
	return (this->*_SetParameterValue)(id, value);

	//TODO
}


hook_method<void (CPC::*)(int type)> CPC::_OnEmotion(SERVER, "CPC::OnEmotion");
void CPC::OnEmotion(int type)
{
	return (this->*_OnEmotion)(type);

	//TODO
}


//hook_method<void (CPC::*)(unsigned long NAID)> CPC::_ReStart(SERVER, "CPC::ReStart");
void CPC::ReStart(unsigned long NAID)
{
//	return (this->*_ReStart)(NAID);

	this->m_pcClientUpdater.CPCClientUpdater::ReStart(NAID);
}


hook_method<int (CPC::*)(int GDID)> CPC::_IsGuildMaster(SERVER, "CPC::IsGuildMaster");
int CPC::IsGuildMaster(int GDID)
{
	return (this->*_IsGuildMaster)(GDID);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetGDID(SERVER, "CPC::GetGDID");
int CPC::GetGDID(void)
{
	return (this->*_GetGDID)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsMyAgitCase(SERVER, "CPC::IsMyAgitCase");
int CPC::IsMyAgitCase(void)
{
	return (this->*_IsMyAgitCase)();

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_IsReadyToSave(SERVER, "CPC::IsReadyToSave");
int CPC::IsReadyToSave(void)
{
//	return (this->*_IsReadyToSave)();
	
	return( m_isValid && m_pcClientUpdater.m_disconnectType != MOVE_SERVER && m_pcClientUpdater.m_disconnectType != RESTART_HSERVER );
}


hook_method<int (CPC::*)(int money)> CPC::_ModifyMoney(SERVER, "CPC::ModifyMoney");
int CPC::ModifyMoney(int money)
{
	return (this->*_ModifyMoney)(money);

	//TODO
}


hook_method<int (CPC::*)(unsigned long GDID)> CPC::_IsAlly(SERVER, "CPC::IsAlly");
int CPC::IsAlly(unsigned long GDID)
{
	return (this->*_IsAlly)(GDID);

	//TODO
}


hook_method<int (CPC::*)(CCharacter* other, int isAllyCHK)> CPC::_IsMyGuildMember(SERVER, "CPC::IsMyGuildMember");
int CPC::IsMyGuildMember(CCharacter* other, int isAllyCHK)
{
	return (this->*_IsMyGuildMember)(other, isAllyCHK);

	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_GetPartyItemPickupRule(SERVER, "CPC::GetPartyItemPickupRule");
int CPC::GetPartyItemPickupRule(void)
{
//	return (this->*_GetPartyItemPickupRule)();

	return m_characterInfo.PartyItemPickupRule;
}


//hook_method<int (CPC::*)(void)> CPC::_GetPartyItemDivisionRule(SERVER, "CPC::GetPartyItemDivisionRule");
int CPC::GetPartyItemDivisionRule(void)
{
//	return (this->*_GetPartyItemDivisionRule)();

	return m_characterInfo.PartyItemDivisionRule;
}


hook_method<int (CPC::*)(void)> CPC::_GetDamagedItemNum(SERVER, "CPC::GetDamagedItemNum");
int CPC::GetDamagedItemNum(void)
{
	return (this->*_GetDamagedItemNum)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_RepairDamagedItem(SERVER, "CPC::RepairDamagedItem");
void CPC::RepairDamagedItem(void)
{
	return (this->*_RepairDamagedItem)();

	//TODO
}


//hook_method<void (CPC::*)(int n)> CPC::_SetEventNo(SERVER, "CPC::SetEventNo");
void CPC::SetEventNo(int n)
{
//	return (this->*_SetEventNo)(n);

	m_eventNo = n;
}


//hook_method<int (CPC::*)(void)> CPC::_GetEventNo(SERVER, "CPC::GetEventNo");
int CPC::GetEventNo(void)
{
//	return (this->*_GetEventNo)();

	return m_eventNo;
}


hook_method<int (CPC::*)(void)> CPC::_IsBadGuy(SERVER, "CPC::IsBadGuy");
int CPC::IsBadGuy(void)
{
	return (this->*_IsBadGuy)();

	if( IsSetting(SETTING_MANNER_POINT) )
		return m_characterInfo.honor < 0;
	else
		return 0;
}


hook_method<void (CPC::*)(int event)> CPC::_OnEnableItemMove(SERVER, "CPC::OnEnableItemMove");
void CPC::OnEnableItemMove(int event)
{
	return (this->*_OnEnableItemMove)(event);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnDisableItemMove(SERVER, "CPC::OnDisableItemMove");
void CPC::OnDisableItemMove(void)
{
	return (this->*_OnDisableItemMove)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsItemMovable(SERVER, "CPC::IsItemMovable");
int CPC::IsItemMovable(void)
{
	return (this->*_IsItemMovable)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_ServerMove(SERVER, "CPC::ServerMove");
void CPC::ServerMove(void)
{
	return (this->*_ServerMove)();

	int SID = g_mapInfo->CMapInfo::GetServerID(m_characterInfo.targetMapName);
	if( SID == -1 )
	{
		Trace("담당맵 서버가 없다.:%s\n", m_characterInfo.targetMapName);
		this->AddErrorCount(".\\PC.cpp", 15262, 4, timeGetTime());
		return;
	}

	m_pcBattle.CPCBattle::Mercenary_Release(1);

	PACKET_ZC_NPCACK_SERVERMOVE outpacket;
	outpacket.PacketType = HEADER_ZC_NPCACK_SERVERMOVE;
	memcpy(outpacket.mapName, m_characterInfo.targetMapName, sizeof(outpacket.mapName));
	outpacket.xPos = m_characterInfo.targetxPos;
	outpacket.yPos = m_characterInfo.targetyPos;
	outpacket.addr.ip = g_serverInfo->CServerInfo::GetServerIPAddr(SID);
	outpacket.addr.port = g_serverInfo->CServerInfo::GetServerPort(SID);
	this->CPC::ForceSend(sizeof(outpacket), (char*)&outpacket);
}


hook_method<void (CPC::*)(void)> CPC::_CheckWeaponState(SERVER, "CPC::CheckWeaponState");
void CPC::CheckWeaponState(void)
{
	return (this->*_CheckWeaponState)();

	//TODO
}


//hook_method<char* (CPC::*)(void)> CPC::_GetCharacterName(SERVER, "CPC::GetCharacterName");
char* CPC::GetCharacterName(void)
{
//	return (this->*_GetCharacterName)();

	return m_characterInfo.characterName;
}


hook_method<void (CPC::*)(unsigned long gid)> CPC::_OnMakeCouple(SERVER, "CPC::OnMakeCouple");
void CPC::OnMakeCouple(unsigned long gid)
{
	return (this->*_OnMakeCouple)(gid);

	CPC* v4;
	CPC* v2;
	if( m_characterInfo.sex )
	{
		v2 = g_characterMgr->CCharacterMgr::FindPCByGID(gid);
		v4 = this;
	}
	else
	{
		v2 = this;
		v4 = g_characterMgr->CCharacterMgr::FindPCByGID(gid);
	}

	if( v4 == NULL
	||  v2 == NULL
	||  v4->m_marriageInfo.bMarried
	||  v2->m_marriageInfo.bMarried
	|| (v4->m_characterInfo.job >= JT_NOVICE_B && v4->m_characterInfo.job <= JT_SUPERNOVICE_B)
	|| (v2->m_characterInfo.job >= JT_NOVICE_B && v2->m_characterInfo.job <= JT_SUPERNOVICE_B) )
		return;

	CoupleInfo info;
	g_coupleInfoDB->CCoupleInfoDB::MakeCouple(v4, v2, info);
	v4->UpdateBodyItemCountByNPC(2634, 1, false);
	v2->UpdateBodyItemCountByNPC(2635, 1, false);
	g_characterMgr->CCharacterMgr::SendMsg(NULL, v4, CM_SAVE_ITEM, 0, 0, 0, 0);
	g_characterMgr->CCharacterMgr::SendMsg(NULL, v2, CM_SAVE_ITEM, 0, 0, 0, 0);
	v4->CPC::SetCoupleInfo(&info, 1);
	v2->CPC::SetCoupleInfo(&info, 1);

	PACKET_ZC_CONGRATULATION outpacket;
	outpacket.PacketType = HEADER_ZC_CONGRATULATION;
	outpacket.AID = v2->GetAccountID();
	v2->CPC::Send(sizeof(outpacket), (char *)&outpacket);
	v2->CCharacter::MultiCast((char *)&outpacket, sizeof(outpacket));
}


hook_method<void (CPC::*)(void* info, int flag)> CPC::_SetCoupleInfo(SERVER, "CPC::SetCoupleInfo");
void CPC::SetCoupleInfo(void* info, int flag)
{
	return (this->*_SetCoupleInfo)(info, flag);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* ch)> CPC::_SetEffectByGospel(SERVER, "CPC::SetEffectByGospel");
void CPC::SetEffectByGospel(CCharacter* ch)
{
	return (this->*_SetEffectByGospel)(ch);

	int type = ch->GetType();
	enum { SUPPORTIVE, OFFENSIVE } mode;

	if( type == PC_TYPE && this->CPC::IsMyPartyMember(ch->GetAccountID()) )
	{
		if( this->GetEffective(EFST_DEVOTION, 0) )
			this->ResetEffective(EFST_DEVOTION, 0);

		mode = SUPPORTIVE;
	}
	else
	{
		if( !ch->IsTarget(this, 1) )
			return;

		mode = OFFENSIVE;
	}

	int effective = EFST_GOSPEL;
	ch->GetParameterValue(VAR_GETEFFECTIVE, effective);
	if( effective != 0 )
		return;

	// type of effect
	int v12;
	if( mode == SUPPORTIVE )
		v12 = 20 + GetServerRandom(0, 20000) % 13;
	else
		v12 = 40 + GetServerRandom(0, 20000) % 10;

	g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_SETEFFECTIVE, EFST_GOSPEL, 10000, v12, 0);

	if( mode == SUPPORTIVE && v12 != 20 && v12 != 26 && v12 != 27 )
	{
		PACKET_ZC_SKILLMSG msg;
		msg.PacketType = HEADER_ZC_SKILLMSG;
		msg.MsgNo = v12;
		g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_SEND_PACKET, sizeof(msg), (int)&msg, 0, 0);
	}

	switch( v12 )
	{
	case 20:
	{
		int v13 = GetServerRandom(0, 20000) % 9000 + 1000;
		ch->UpdateParameterValue(VAR_HP, v13);
		((CPC*)ch)->CPC::NotifyUseSkill(SKID_AL_HEAL, ch->GetAccountID(), 0, v13, true);
		break;
	}
	case 21:
		((CPC*)ch)->CPC::SetBodyState(0);
		((CPC*)ch)->CPC::SetHealthState(0);
		((CPC*)ch)->ResetEffectState(2048);
		break;
	case 22:
		ch->SetEffective(EFST_RESISTHANDICAP, 60000, 100, 0, 0, 0);
		break;
	case 23:
		ch->SetEffective(EFST_MAXHPPERCENT, 60000, 100, 0, 0, 0);
		break;
	case 24:
		ch->SetEffective(EFST_MAXSPPERCENT, 60000, 100, 0, 0, 0);
		break;
	case 25:
		MSG_TYPE1_TWODWORD data;
		data.data1 = SKID_PA_GOSPEL;
		data.data2 = 20;
		ch->SetEffective(EFST_STATUSONE, 60000, (int)&data, 0, 0, 0);
		break;
	case 26:
		g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_BLESSING_FROM_ACOLYTE, 10, 240000, 10, 0);
		break;
	case 27:
		ch->SetEffective(EFST_INC_AGI, 240000, 10, 0, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_AGI_CHANGE, EFST_INC_AGI, 240000, SKID_AL_INCAGI, 0);
		break;
	case 28:
		ch->SetEffective(EFST_ASPERSIO, 60000, 1, 0, 0, 0);
		break;
	case 29:
		ch->SetEffective(EFST_BENEDICTIO, 60000, 1, 0, 0, 0);
		((CPC*)ch)->CPC::SetCurrentState(6);
		break;
	case 30:
		ch->SetEffective(EFST_DEFENCE, 10000, 1, 0, 0, 0);
		break;
	case 31:
		((CPC*)ch)->m_pcBattle.CPCBattle::SetATKPercentInfo(SKID_PA_GOSPEL, 60000, 100);
		break;
	case 32:
		ch->OnChangeStatusAmount(SKID_PA_GOSPEL, VAR_BASICHIT, 60000, 50);
		ch->OnChangeStatusAmount(SKID_PA_GOSPEL, VAR_BASICAVOIDANCE, 60000, 50);
		break;

	case 40:
	{
		int v19 = 3000 + GetServerRandom(0, 20000) % 5000;
		int v21 = this->GetModifiedTargetItemDEF(ch);

		int statusDef;
		ch->GetParameterValue(VAR_STATUSDEFPOWER, statusDef);

		int v18 = (int)((double)v19 - (double)(v19 * v21) / 100.0 - (double)statusDef);
		if( v18 < 0 )
			v18 = 0;

		SKILLATTACK_MSG msg;
		msg.SKID = SKID_PA_GOSPEL;
		msg.targetAID = ch->GetAccountID();
		msg.count = 1;
		msg.level = 1;
		msg.xPos = m_pathInfo.m_moveInfo.xPos;
		msg.yPos = m_pathInfo.m_moveInfo.yPos;
		msg.msgtype = 1;
		msg.skLevel = 1;
		msg.par1 = v18;
		msg.actionType = 6;
		this->SkillAttack(&msg, 100, 100, false);
		break;
	}
	case 41:
	{
		int v18 = 1500 + GetServerRandom(0, 20000) % 4000;

		SKILLATTACK_MSG msg;
		msg.SKID = SKID_PA_GOSPEL;
		msg.targetAID = ch->GetAccountID();
		msg.count = 1;
		msg.level = 1;
		msg.xPos = m_pathInfo.m_moveInfo.xPos;
		msg.yPos = m_pathInfo.m_moveInfo.yPos;
		msg.msgtype = 1;
		msg.skLevel = 1;
		msg.par1 = v18;
		msg.actionType = 6;
		this->SkillAttack(&msg, 100, 100, false);
		break;
	}
	case 42:
		this->SetHandicapState(HEALTH_CURSE, ch, 1000, 0, 1800000, 0, 0);
		break;
	case 43:
		this->SetHandicapState(HEALTH_BLIND, ch, 1000, 0, 1800000, 0, 0);
		break;
	case 44:
		this->SetHandicapState(HEALTH_POISON, ch, 1000, 0, 1800000, 0, 0);
		break;
	case 45:
		if( type == PC_TYPE )
		{
			((CPC*)ch)->m_pcBattle.CPCBattle::SetATKPercentInfo(SKID_PA_GOSPEL, 9999, 32);
			((CPC*)ch)->m_pcBattle.CPCBattle::SetDEFPercentInfo(SKID_PA_GOSPEL, 9999, -55);
		}
		else
		if( type == NPC_MOB_TYPE )
		{
			((CNPC*)ch)->CNPC::SetATKPercentInfo(SKID_PA_GOSPEL, 9999, 32);
			((CNPC*)ch)->CNPC::SetDEFPercentInfo(SKID_PA_GOSPEL, 9999, -55);
		}

		g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_SETEFFECTIVE, EFST_PROVOKE, 9999, 11, 0);
		this->CPC::NotifyUseSkill(SKID_SM_PROVOKE, ch->GetAccountID(), ch->GetAccountID(), 10, true);
		break;
	case 46:
		g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_SETEFFECTIVE, EFST_DEFENCE, 20000, 2, 0);
		break;
	case 47:
		if( type == PC_TYPE )
		{
			((CPC*)ch)->m_pcBattle.CPCBattle::SetATKPercentInfo(SKID_PA_GOSPEL, 20000, -100);
		}
		else
		if( type == NPC_MOB_TYPE )
		{
			((CNPC*)ch)->CNPC::SetATKPercentInfo(SKID_PA_GOSPEL, 20000, -100);
		}
		break;
	case 48:
		if( type == PC_TYPE )
		{
			int flee = ((CPC *)ch)->CPC::GetAvoidableSucPerOnClient();
			ch->OnChangeStatusAmount(SKID_PA_GOSPEL, VAR_BASICAVOIDANCE, 20000, -flee);
		}
		else
		if( type == NPC_MOB_TYPE )
		{
			int agi;
			ch->GetParameterValue(VAR_AGI, agi);
			g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_AGI_CHANGE, -agi, 20000, SKID_PA_GOSPEL, 0);
		}
		break;
	case 49:
		g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_SETEFFECTIVE, EFST_SLOWDOWN, 20000, 1, 0);
		break;
	default:
		break;
	}
}


hook_method<void (CPC::*)(int effect)> CPC::_OnShowEffect(SERVER, "CPC::OnShowEffect");
void CPC::OnShowEffect(int effect)
{
	return (this->*_OnShowEffect)(effect);

	PACKET_ZC_NOTIFY_EFFECT2 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_EFFECT2;
	outpacket.AID = this->GetAccountID();
	outpacket.effectID = effect;
	this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


hook_method<void (CPC::*)(int effect, int numdata)> CPC::_OnShowEffect3(SERVER, "CPC::OnShowEffect3");
void CPC::OnShowEffect3(int effect, int numdata)
{
	return (this->*_OnShowEffect3)(effect, numdata);

	PACKET_ZC_NOTIFY_EFFECT3 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_EFFECT3;
	outpacket.AID = this->GetAccountID();
	outpacket.effectID = effect;
	outpacket.numdata = numdata;
	this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


hook_method<int (CPC::*)(void)> CPC::_GetEffectState(SERVER, "CPC::GetEffectState");
int CPC::GetEffectState(void)
{
	return (this->*_GetEffectState)();

	return m_characterPInfo.effectState;
}


hook_method<void (CPC::*)(unsigned long AID, CITZMsg* reqMsg)> CPC::_OnMsgFromItemServer(SERVER, "CPC::OnMsgFromItemServer");
void CPC::OnMsgFromItemServer(unsigned long AID, CITZMsg* reqMsg)
{
	return (this->*_OnMsgFromItemServer)(AID, reqMsg);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_DeleteMarriagering(SERVER, "CPC::DeleteMarriagering");
void CPC::DeleteMarriagering(void)
{
	return (this->*_DeleteMarriagering)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_InitMobileEvent(SERVER, "CPC::InitMobileEvent");
void CPC::InitMobileEvent(void)
{
	return (this->*_InitMobileEvent)();

	//TODO
}


hook_method<void (CPC::*)(unsigned long gid1, unsigned long gid2)> CPC::_OnMakeFamily(SERVER, "CPC::OnMakeFamily");
void CPC::OnMakeFamily(unsigned long gid1, unsigned long gid2)
{
	return (this->*_OnMakeFamily)(gid1, gid2);

	//TODO
}


hook_method<void (CPC::*)(void* info, int flag)> CPC::_SetFamilyInfo(SERVER, "CPC::SetFamilyInfo");
void CPC::SetFamilyInfo(void* info, int flag)
{
	return (this->*_SetFamilyInfo)(info, flag);

	//TODO
}


hook_method<BOOL (CPC::*)(unsigned long AID, int& exPos, int& eyPos, int dir, int distance, int flag)> CPC::_MoveForward(SERVER, "CPC::MoveForward");
BOOL CPC::MoveForward(unsigned long AID, int& exPos, int& eyPos, int dir, int distance, int flag)
{
	return (this->*_MoveForward)(AID, exPos, eyPos, dir, distance, flag);

	//TODO
}


hook_method<void (CPC::*)(int type)> CPC::_SetReadyMotion(SERVER, "CPC::SetReadyMotion");
void CPC::SetReadyMotion(int type)
{
	return (this->*_SetReadyMotion)(type);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_SetPlusMakerPower(SERVER, "CPC::SetPlusMakerPower");
void CPC::SetPlusMakerPower(void)
{
	return (this->*_SetPlusMakerPower)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsCrazyKiller(SERVER, "CPC::IsCrazyKiller");
int CPC::IsCrazyKiller(void)
{
	return (this->*_IsCrazyKiller)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsGiveExpToCrazyKiller(SERVER, "CPC::IsGiveExpToCrazyKiller");
int CPC::IsGiveExpToCrazyKiller(void)
{
	return (this->*_IsGiveExpToCrazyKiller)();

	if( IsSetting(SETTING_KILLER_SYSTEM) )
		return m_PKInfo.expireTimeCheck == 0;

	return 0;
}


hook_method<int (CPC::*)(void)> CPC::_IsPossibleToGetExp(SERVER, "CPC::IsPossibleToGetExp");
int CPC::IsPossibleToGetExp(void)
{
	return (this->*_IsPossibleToGetExp)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_ProcessPKInfo(SERVER, "CPC::ProcessPKInfo");
void CPC::ProcessPKInfo(void)
{
	return (this->*_ProcessPKInfo)();

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_SavePKInfo(SERVER, "CPC::SavePKInfo");
int CPC::SavePKInfo(void)
{
	return (this->*_SavePKInfo)();

	//TODO
}


hook_method<int (CPC::*)(CPC* winner, CPC* loser)> CPC::_UpdatePKInfo(SERVER, "CPC::UpdatePKInfo");
int CPC::UpdatePKInfo(CPC* winner, CPC* loser)
{
	return (this->*_UpdatePKInfo)(winner, loser);

	if( !IsSetting(SETTING_KILLER_SYSTEM) || winner == NULL || loser == NULL )
		return 0;

	int win = 0;
	int lose = 0;

	if( loser->CPC::IsGiveExpToCrazyKiller() && winner->CPC::IsPossibleToGetExp() )
	{
		win = 1;
		lose = 5;
	}

	int bLoserIsCrazyKiller = loser->CPC::IsCrazyKiller();
	winner->CPC::SetPKInfo(win, 0, loser->m_characterInfo.characterName, 0, bLoserIsCrazyKiller);
	loser->CPC::SetPKInfo(0, lose, 0, winner->m_characterInfo.characterName, bLoserIsCrazyKiller);
	
	return 1;
}


hook_method<void (CPC::*)(int win, int lose, char* kill_name, char* killed_name, int bLoserCrazyKiller)> CPC::_SetPKInfo(SERVER, "CPC::SetPKInfo");
void CPC::SetPKInfo(int win, int lose, char* kill_name, char* killed_name, int bLoserCrazyKiller)
{
	return (this->*_SetPKInfo)(win, lose, kill_name, killed_name, bLoserCrazyKiller);

	m_PKInfo.winPoint += win;
	m_PKInfo.losePoint += lose;

	if( lose != 0 )
	{
		SYSTEMTIME curTime;
		GetLocalTime(&curTime);
		SystemTimeToFileTime(&curTime, &m_PKInfo.expireTime);

		unsigned __int64 t = g_KillerExpireTime + m_PKInfo.expireTime.dwLowDateTime + ((unsigned __int64)m_PKInfo.expireTime.dwHighDateTime << 32);
		m_PKInfo.expireTime.dwLowDateTime += (DWORD)g_KillerExpireTime;
		m_PKInfo.expireTime.dwHighDateTime = (DWORD)(t >> 32);
		m_PKInfo.expireTimeCheck = timeGetTime() + (DWORD)(g_KillerExpireTime / 10000);

		int Point = m_PKInfo.winPoint - m_PKInfo.losePoint;
		g_makerRankMgr->CMakerRankMgr::UpdateMakerRank(this, 3, -lose, Point);
	}

	if( win != 0 )
	{
		m_PKInfo.noPointTime = timeGetTime() + 3600000;

		if( bLoserCrazyKiller == 0 )
			g_characterMgr->CCharacterMgr::SendMsg(this, this, CM_NOTIFY_MANNER_POINT_GIVEN, 1, 5, 0, 0);

		int Point = m_PKInfo.winPoint - m_PKInfo.losePoint;
		g_makerRankMgr->CMakerRankMgr::UpdateMakerRank(this, 3, win, Point);
	}

	if( kill_name != NULL )
		memcpy(m_PKInfo.killName, kill_name, sizeof(m_PKInfo.killName));

	if( killed_name != NULL )
		memcpy(m_PKInfo.killedName, killed_name, sizeof(m_PKInfo.killedName));

	this->CPC::SetKillerSystem();
	this->CPC::NotifyPKInfo();

	if( m_PKInfo.lastCheckTime == 0 )
		m_PKInfo.lastCheckTime = timeGetTime();
}


hook_method<void (CPC::*)(void)> CPC::_SetKillerSystem(SERVER, "CPC::SetKillerSystem");
void CPC::SetKillerSystem(void)
{
	return (this->*_SetKillerSystem)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_NotifyPKInfo(SERVER, "CPC::NotifyPKInfo");
void CPC::NotifyPKInfo(void)
{
	return (this->*_NotifyPKInfo)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_GetPKInfo(SERVER, "CPC::GetPKInfo");
void CPC::GetPKInfo(void)
{
	return (this->*_GetPKInfo)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_CheckPalmStrike(SERVER, "CPC::CheckPalmStrike");
void CPC::CheckPalmStrike(void) // line 9667-9675
{
	return (this->*_CheckPalmStrike)();

	// TODO
}


hook_method<void (CPC::*)(CCharacter* sender, CCharacter* attacker, CCharacter* target, int damage, short count, short level, unsigned short SKID)> CPC::_NotifySkillAction(SERVER, "CPC::NotifySkillAction");
void CPC::NotifySkillAction(CCharacter* sender, CCharacter* attacker, CCharacter* target, int damage, short count, short level, unsigned short SKID)
{
	return (this->*_NotifySkillAction)(sender, attacker, target, damage, count, level, SKID);

	//TODO
}


hook_method<char* (CPC::*)(void)> CPC::_GetRestartMapName(SERVER, "CPC::GetRestartMapName");
char* CPC::GetRestartMapName(void)
{
	return (this->*_GetRestartMapName)();

	return m_characterInfo.restartMapName;
}


hook_method<void (CPC::*)(void)> CPC::_ResetItemScriptEvent(SERVER, "CPC::ResetItemScriptEvent");
void CPC::ResetItemScriptEvent(void)
{
	return (this->*_ResetItemScriptEvent)();

	//TODO
}


hook_method<void (CPC::*)(int sp)> CPC::_ReduceSPByUseSkill(SERVER, "CPC::ReduceSPByUseSkill");
void CPC::ReduceSPByUseSkill(int sp)
{
	return (this->*_ReduceSPByUseSkill)(sp);

	this->UpdateParameterValue(VAR_SP, -sp);
}


hook_method<bool (CPC::*)(int itemID, int count, bool isExternalEffect)> CPC::_IsExistItem(SERVER, "CPC::IsExistItem");
bool CPC::IsExistItem(int itemID, int count, bool isExternalEffect)
{
	return (this->*_IsExistItem)(itemID, count, isExternalEffect);

	//TODO
}


hook_method<bool (CPC::*)(int itemID, int count, bool isExternalEffect)> CPC::_ConsumeItemByUseSkill(SERVER, "CPC::ConsumeItemByUseSkill");
bool CPC::ConsumeItemByUseSkill(int itemID, int count, bool isExternalEffect)
{
	return (this->*_ConsumeItemByUseSkill)(itemID, count, isExternalEffect);

	//TODO
}


hook_method<short (CPC::*)(CCharacter* other, int isRangeAttack)> CPC::_GetAttackSuccessPercent(SERVER, "CPC::GetAttackSuccessPercent");
short CPC::GetAttackSuccessPercent(CCharacter* other, int isRangeAttack)
{
	return (this->*_GetAttackSuccessPercent)(other, isRangeAttack);

	//TODO
}


hook_method<int (CPC::*)(CCharacter* other, int position, int skillProperty, int plusATTPowerPercent, int plusATTSuccessPercent, int type, int isRangeAttack, unsigned short SKID, short skLevel)> CPC::_GetAttackFinalDamage2(SERVER, "?GetAttackFinalDamage@CPC@@AAEHPAVCCharacter@@HHHHHHGF@Z");
int CPC::GetAttackFinalDamage(CCharacter* other, int position, int skillProperty, int plusATTPowerPercent, int plusATTSuccessPercent, int type, int isRangeAttack, unsigned short SKID, short skLevel)
{
	return (this->*_GetAttackFinalDamage2)(other, position, skillProperty, plusATTPowerPercent, plusATTSuccessPercent, type, isRangeAttack, SKID, skLevel);

	//TODO
}


hook_method<int (CPC::*)(ATTACK_INFO* info)> CPC::_GetAttackFinalDamage(SERVER, "?GetAttackFinalDamage@CPC@@UAEHPAUATTACK_INFO@@@Z");
int CPC::GetAttackFinalDamage(ATTACK_INFO* info)
{
	return (this->*_GetAttackFinalDamage)(info);

	return this->CPC::GetAttackFinalDamage(info->target, info->position, info->skillProperty, info->plusATTPowerPercent, info->plusATTSuccessPercent, info->calculateType, info->isRangeAttack, info->SKID, info->skLevel);
}


hook_method<bool (CPC::*)(void)> CPC::_IsDeadState(SERVER, "CPC::IsDeadState");
bool CPC::IsDeadState(void)
{
	return (this->*_IsDeadState)();

	return( this->GetState() == CHARACTER_STATE_DEAD && this->GetEffective(EFST_TRICKDEAD, 0) == 0 );
}


hook_method<void (CPC::*)(int len, char* packet, bool isIncludeSelf)> CPC::_SendPacketToPartyInMap(SERVER, "CPC::SendPacketToPartyInMap");
void CPC::SendPacketToPartyInMap(int len, char* packet, bool isIncludeSelf)
{
	return (this->*_SendPacketToPartyInMap)(len, packet, isIncludeSelf);

	//TODO
}


hook_method<void (CPC::*)(int len, char* packet)> CPC::_SendPacketToPartyInMapOuterRange(SERVER, "CPC::SendPacketToPartyInMapOuterRange");
void CPC::SendPacketToPartyInMapOuterRange(int len, char* packet)
{
	return (this->*_SendPacketToPartyInMapOuterRange)(len, packet);

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetBodyState(SERVER, "CPC::GetBodyState");
short CPC::GetBodyState(void) // line ???
{
	return (this->*_GetBodyState)();

	return static_cast<short>(m_characterPInfo.bodyState);
}


hook_method<void (CPC::*)(char campID, short xPos1, short yPos1, bool isSaveFlag)> CPC::_SetBattleFieldInfo(SERVER, "CPC::SetBattleFieldInfo");
void CPC::SetBattleFieldInfo(char campID, short xPos1, short yPos1, bool isSaveFlag)
{
	return (this->*_SetBattleFieldInfo)(campID, xPos1, yPos1, isSaveFlag);

	//TODO
}


hook_method<bool (CPC::*)(unsigned long AID, int hp, int mhp, const char* name)> CPC::_NotifyHPToBattleFieldCamp(SERVER, "CPC::NotifyHPToBattleFieldCamp");
bool CPC::NotifyHPToBattleFieldCamp(unsigned long AID, int hp, int mhp, const char* name) // line 21217-21256
{
	return (this->*_NotifyHPToBattleFieldCamp)(AID, hp, mhp, name);

	// TODO
}


hook_method<void (CPC::*)(unsigned long AID, int hp, int mhp)> CPC::_BroadcastHP(SERVER, "?BroadcastHP@CPC@@QAEXKHH@Z");
void CPC::BroadcastHP(unsigned long AID, int hp, int mhp)
{
	return (this->*_BroadcastHP)(AID, hp, mhp);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_BroadcastHP2(SERVER, "?BroadcastHP@CPC@@QAEXXZ");
void CPC::BroadcastHP(void) // line 21259-21264
{
	return (this->*_BroadcastHP2)();

	if ( !this->CPC::NotifyHPToBattleFieldCamp(this->GetAccountID(), m_characterInfo.hp, this->CPC::GetMaxHP(), m_characterInfo.characterName) )
		this->CPC::NotifyHpToParty();
}


hook_method<void (CPC::*)(void)> CPC::_ClearDevotionList(SERVER, "CPC::ClearDevotionList");
void CPC::ClearDevotionList(void)
{
	return (this->*_ClearDevotionList)();

	//TODO
}


hook_method<bool (CPC::*)(const int in_ITID)> CPC::_IsMapPropertyBlockEquipItem(SERVER, "CPC::IsMapPropertyBlockEquipItem");
bool CPC::IsMapPropertyBlockEquipItem(const int in_ITID)
{
	return (this->*_IsMapPropertyBlockEquipItem)(in_ITID);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_CheckMove(SERVER, "CPC::CheckMove");
void CPC::CheckMove(void)
{
	return (this->*_CheckMove)();

	if( (m_pathInfo.m_moveInfo.state != CHARACTER_STATE_MOVE && m_pathInfo.m_moveInfo.state != CHARACTER_STATE_ENTER) || m_mapRes == NULL )
		return;

	if( m_pathInfo.m_moveInfo.state == CHARACTER_STATE_MOVE )
	{
		float xPos; float yPos; int dir;
		int currentCell = m_pathInfo.CPathInfo::GetPos(this->CPC::GetSpeed(), timeGetTime(), xPos, yPos, dir);
		if( currentCell == -2 )
			return;

		int xtemp, ytemp, xM, yM;
		TransformFloatPosCellPos(xPos, xtemp, xM);
		TransformFloatPosCellPos(yPos, ytemp, yM);

		if( xtemp != m_pathInfo.m_moveInfo.xPos || ytemp != m_pathInfo.m_moveInfo.yPos )
		{
			if( this->GetEffective(EFST_RUN, 0) && (m_pathInfo.m_moveInfo.dir != dir || !m_mapRes->CMapRes::IsMovableCell((int)xPos, (int)yPos) || !m_mapRes->CMapRes::IsEmptyPos(m_characterInfo.accountID, xtemp, ytemp)) )
			{
				this->SetEffective(EFST_TING, 100, 1, 0, 0, 1);
				this->ResetEffective(EFST_RUN, 0);

				PosInfo newPos;
				this->CPC::GetPushedPosition2(m_pathInfo.m_moveInfo.xPos, m_pathInfo.m_moveInfo.yPos, m_pathInfo.m_moveInfo.dir, 3, newPos);
				g_characterMgr->CCharacterMgr::SendMsg(this, this, 0x48u, newPos.x, newPos.y, 1, 0);
				return;
			}

			if( !m_mapRes->CMapRes::IsMovableCell((int)xPos, (int)yPos) )
			{
				m_pcClientUpdater.CPCClientUpdater::NotifyStopMove();
				return;
			}

			if( this->GetEffective(EFST_BDPLAYING, 0) && !this->GetEffective(EFST_LONGING, 0) )
				m_pcSkill.CPCSkill::SetPosPlayingSkill(xtemp, ytemp);

			if( this->GetEffective(EFST_SG_WARM, 0)
			 || this->GetEffective(EFST_DAURA, 0)
			 || this->GetEffective(EFST_NEUTRALBARRIER_MASTER, 0)
			 || this->GetEffective(EFST_STEALTHFIELD_MASTER, 0) )
				m_pcSkill.CPCSkill::SetPosPlayingSkill(xtemp, ytemp);

			CPC* marionettePc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(this->GetEffective(EFST_MARIONETTE,0), PC_TYPE);
			if( marionettePc != NULL )
			{
				if( !this->IsMyArea(marionettePc, 7) )
					marionettePc->ResetEffective(EFST_MARIONETTE_MASTER, 0);
			}
			else
			{
				CPC* marionetteMasterPc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(this->GetEffective(EFST_MARIONETTE_MASTER,0), PC_TYPE);
				if( marionetteMasterPc != NULL )
				{
					if( !this->IsMyArea(marionetteMasterPc, 7) )
						this->ResetEffective(EFST_MARIONETTE_MASTER, 0);
				}
			}

			mystd::vector<CCharacter*>* srcSection = m_mapRes->CMapRes::GetSectionByCellPos(m_pathInfo.m_moveInfo.xPos, m_pathInfo.m_moveInfo.yPos);
			mystd::vector<CCharacter*>* dstSection = m_mapRes->CMapRes::GetSectionByCellPos(xtemp, ytemp);
			if( srcSection != dstSection && !m_mapRes->CMapRes::MoveCharacter(srcSection, dstSection, this) )
				return;

			m_pathInfo.m_moveInfo.xPos = xtemp;
			m_pathInfo.m_moveInfo.yPos = ytemp;

			if( this->IsInitingState() )
				m_loadingCompleteTime = 0;
		}

		m_pathInfo.m_moveInfo.dir = dir;

		if( currentCell == -1 )
		{
			m_pathInfo.m_moveInfo.dir = dir;
			int exPos = m_pathInfo.m_moveInfo.xPos;
			int eyPos = m_pathInfo.m_moveInfo.yPos;

			if( this->GetEffective(EFST_RUN, 0) )
			{
				if( !this->CPC::MoveForward(m_characterInfo.accountID, exPos, eyPos, dir, 5, 0) )
				{
					this->SetEffective(EFST_TING, 100, 1, 0, 0, TRUE);
					this->ResetEffective(EFST_RUN, 0);

					PosInfo newPos;
					this->CPC::GetPushedPosition2(m_pathInfo.m_moveInfo.xPos, m_pathInfo.m_moveInfo.yPos, dir, 3, newPos);
					g_characterMgr->CCharacterMgr::SendMsg(this, this, CM_MOVE_STOP, newPos.x, newPos.y, 1, 0);
					return;
				}
			}
			else
			{
				m_pathInfo.m_moveInfo.state = CHARACTER_STATE_STAND;
				m_pathInfo.CPathInfo::SetStartCellNumber(0);

				if( !m_mapRes->CMapRes::GetEmptyPosition(m_characterInfo.accountID, exPos, eyPos) )
				{
					PACKET_CZ_REQUEST_MOVE move;
					move.PacketType = HEADER_CZ_REQUEST_MOVE;
					EncodePosDir(exPos, eyPos, dir, move.dest);
					m_packetHandler.CPCPacketHandler::OnMove(&move);
					return;
				}
			}
		}
		else
		{
			m_pathInfo.CPathInfo::SetStartCellNumber(currentCell);
		}
	}

	if( m_characterInfo.isSendable )
	{
		this->CPC::NotifyInfoToSection();

		if( m_pathInfo.m_moveInfo.state == CHARACTER_STATE_ENTER )
			m_pathInfo.m_moveInfo.state = CHARACTER_STATE_STAND;
	}
}


hook_method<void (CPC::*)(void)> CPC::_CheckStateChange(SERVER, "CPC::CheckStateChange");
void CPC::CheckStateChange(void) // line 1395-2190
{
	return (this->*_CheckStateChange)();

	unsigned long time = timeGetTime();
	unsigned long curState = this->CPC::GetState();
	int maxHP = this->CPC::GetMaxHP();
	int maxSP = this->CPC::GetMaxSP();

	// check hp and sp
	if( this->GetEffective(EFST_BERSERK, 0) > 0 && curState != CHARACTER_STATE_DEAD )
	{
		if( time - m_characterTimeInfo.HPLastHealTime >= 10000 )
		{
			m_characterInfo.hp += -5 * maxHP / 100;
			if( m_characterInfo.hp < 100 )
			{
				this->ResetEffective(EFST_BERSERK, 0);
				this->SetEffective(EFST_BERSERK, 300000, -1, 0, 0, 0);
			}

			m_characterTimeInfo.HPLastHealTime = time;
			m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HP, m_characterInfo.hp);
		}
	}
	else if( (m_characterPInfo.healthState & HEALTHSTATE_POISON) != 0 && this->GetEffective(EFST_SLOWPOISON, 0) == 0 )
	{
		if( time - m_characterTimeInfo.HPLastHealTime >= 1000 )
		{
			if( m_characterInfo.hp > maxHP * 25 / 100 )
				m_characterInfo.hp = static_cast<int>(m_characterInfo.hp - maxHP * 1.5 / 100.0 + 2.0);

			m_characterTimeInfo.HPLastHealTime = time;
			m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HP, m_characterInfo.hp);
		}
	}
	else if( (m_characterPInfo.healthState & HEALTHSTATE_HEAVYPOISON) != 0 && this->GetEffective(EFST_SLOWPOISON, 0) == 0 )
	{
		if( time - m_characterTimeInfo.HPLastHealTime >= 1000 )
		{
			if( m_characterInfo.hp > maxHP * 25 / 100 )
				m_characterInfo.hp = m_characterInfo.hp - maxHP * 2 / 100 - 4;

			m_characterTimeInfo.HPLastHealTime = time;
			m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HP, m_characterInfo.hp);
		}
	}
	else if( (m_characterPInfo.healthState & HEALTHSTATE_BLOODING) != 0 && curState != CHARACTER_STATE_DEAD )
	{
		if( time - m_characterTimeInfo.HPLastHealTime >= 10000 )
		{
			m_characterInfo.hp -= GetServerRandom(200, 800);
			if( m_characterInfo.hp < 0 ) // FIXME is a character with 0 hp supposed to be alive?
				m_pcClientUpdater.CPCClientUpdater::OnDead(0);

			m_characterTimeInfo.HPLastHealTime = time;
			m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HP, m_characterInfo.hp);
		}
	}
	else if( m_characterPInfo.bodyState == BODYSTATE_STONECURSE && curState != CHARACTER_STATE_DEAD )
	{
		if( time - m_characterTimeInfo.HPLastHealTime >= 5000 )
		{
			if( m_characterInfo.hp > maxHP * 25 / 100 )
				m_characterInfo.hp = m_characterInfo.hp - maxHP / 100;

			m_characterTimeInfo.HPLastHealTime = time;
			m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HP, m_characterInfo.hp);
		}
	}
	else if( this->GetEffective(EFST_GOSPEL, 0) != 0 && this->GetEffective(EFST_GOSPEL, 0) < 10 && curState != CHARACTER_STATE_DEAD )
	{
		if( time - m_characterTimeInfo.HPLastHealTime >= 10000 )
		{
			int damageHP = 45 + ( this->GetEffective(EFST_GOSPEL, 0) > 5 ) ? 0 : -15;
			int damageSP = 35 + ( this->GetEffective(EFST_GOSPEL, 0) > 5 ) ? 0 : -15;

			this->UpdateParameterValue(VAR_HP, -damageHP);
			this->UpdateParameterValue(VAR_SP, -damageSP);

			if( m_characterInfo.hp < 100 || m_characterInfo.sp == 0 )
				this->ResetEffective(EFST_GOSPEL, 0);

			m_characterTimeInfo.HPLastHealTime = time;
		}
	}
	else
	{
		unsigned long healSpeedMultiplier = 1;
		int isRecoverySP = 1;
		int weightPercent = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemWeightByPercent();

		if( maxHP == m_characterInfo.hp )
			m_characterTimeInfo.LastHPPlusTime = time;

		if( maxSP == m_characterInfo.sp )
			m_characterTimeInfo.LastSPPlusTime = time;

		if( CPC::GetCategorySecondJob(m_characterInfo.job) == JT_MONK )
		{
			if( curState == CHARACTER_STATE_SIT )
				this->CPC::ApplyPlusHpSp(maxHP, maxSP, weightPercent);

			if( this->GetEffective(EFST_EXPLOSIONSPIRITS, 0) != 0 )
				isRecoverySP = 0;

			if( this->GetEffective(EFST_EXTREMITYFIST, 0) != 0 )
				isRecoverySP = 0;

			if( this->GetEffective(EFST_SOULLINK, 0) == JT_MONK )
				isRecoverySP = 1;
		}
		else if( curState == CHARACTER_STATE_SIT )
		{
			this->CPC::ApplyPlusHpSp(maxHP, maxSP, weightPercent);
		}

		if( curState == CHARACTER_STATE_DEAD || (m_characterPInfo.effectState & (EFFECTSTATE_BURROW | EFFECTSTATE_HIDING)) != 0 || this->GetEffective(EFST_BERSERK, 0) < 0 )
		{
			m_characterTimeInfo.LastHPPlusTime = time;
			m_characterTimeInfo.LastSPPlusTime = time;
			m_characterTimeInfo.HPLastHealTime = time;
			isRecoverySP = 0;
		}
		else if( weightPercent >= 50 )
		{
			if( this->GetEffective(EFST_TENSIONRELAX, 0) != 0 )
			{
				healSpeedMultiplier = 2;
				isRecoverySP = 0;
			}
			else if( this->CPC::GetCategorySecondJob(m_characterInfo.job) == JT_MONK )
			{
				m_characterTimeInfo.HPLastHealTime = time;
				isRecoverySP = 0;
			}
			else
			{
				m_characterTimeInfo.LastHPPlusTime = time;
				m_characterTimeInfo.LastSPPlusTime = time;
				m_characterTimeInfo.HPLastHealTime = time;
				isRecoverySP = 0;
			}
		}
		else if( curState == CHARACTER_STATE_MOVE )
		{
			if( m_pcSkill.CPCSkill::GetSkillLevel(SKID_SM_MOVINGRECOVERY, 0) <= 0 )
				m_characterTimeInfo.HPLastHealTime = time;

			m_characterTimeInfo.LastHPPlusTime = time;
			m_characterTimeInfo.LastSPPlusTime = time;
		}

		// recover hp
		unsigned long healSpeed = m_pcClientUpdater.CPCClientUpdater::GetHPHealVelocity();
		if( curState == CHARACTER_STATE_MOVE && m_pcSkill.CPCSkill::GetSkillLevel(SKID_SM_MOVINGRECOVERY, 0) >= 1 )
			healSpeed *= 2;

		if( time - m_characterTimeInfo.HPLastHealTime > healSpeed * healSpeedMultiplier )
		{
			m_characterTimeInfo.HPLastHealTime = time;
			m_characterTimeInfo.HPPartyNotifyTime = time;

			if( IsSetting(SETTING_NEWHPSP) != 0 )
			{
				if ( m_characterInfo.hp < maxHP )
				{
					double amount = maxHP * 0.5 / 100.0;
					if( amount < 1.0 )
						amount = 1.0;

					amount = (this->CPC::GetVitValue() / 5) * amount;

					this->UpdateParameterValue(VAR_HP, static_cast<int>(amount + amount * m_characterTimeInfo.HPAcceleration / 100.0));
				}
				else
				{
					this->CPC::BroadcastHP();
				}
			}
			else
			{
				if( m_characterInfo.hp < maxHP )
					m_characterInfo.hp = m_characterInfo.hp + 1;
				else
					this->CPC::BroadcastHP();
			}
		}
		else if( time - m_characterTimeInfo.HPPartyNotifyTime > healSpeed * healSpeedMultiplier )
		{
			m_characterTimeInfo.HPPartyNotifyTime = time;
			this->CPC::BroadcastHP();
		}

		unsigned long HPPlusTime = m_characterTimeInfo.HPPlusTime;
		if( this->GetEffective(EFST_TENSIONRELAX, 0) != 0 && healSpeedMultiplier == 1 )
			HPPlusTime /= 3;

		if( m_characterTimeInfo.HPPlusTime != 0 && time - m_characterTimeInfo.LastHPPlusTime > HPPlusTime )
		{
			m_characterTimeInfo.LastHPPlusTime = time;
			this->CPC::NotifyRecoveryValue(VAR_HP, maxHP * m_pcSkill.CPCSkill::GetSkillLevel(SKID_SM_RECOVERY, 0) / 500 + m_characterTimeInfo.HPPlusValue, maxHP);
		}

		// recover/consume sp
		if( m_characterTimeInfo.SPPlusTime != 0 && time - m_characterTimeInfo.LastSPPlusTime > m_characterTimeInfo.SPPlusTime )
		{
			m_characterTimeInfo.LastSPPlusTime = time;
			int skillLevel = m_pcSkill.CPCSkill::GetSkillLevel(SKID_MG_SRECOVERY, 0);
			if( skillLevel == 0 )
				skillLevel = m_pcSkill.CPCSkill::GetSkillLevel(SKID_NJ_NINPOU, 0);

			int amount = 0;
			if( IsSetting(SETTING_NEWHPSP) != 0 )
				amount = maxSP * skillLevel / 500;

			amount += m_characterTimeInfo.SPPlusValue;
			if( m_specialSP != 0 )
			{
				amount *= 2;
				m_specialSP = 0;
			}

			this->CPC::NotifyRecoveryValue(VAR_SP, amount, maxSP);
		}

		unsigned long consumeDelay = 0;
		int spAmount = 1;
		if( (m_characterPInfo.effectState & EFFECTSTATE_BURROW) != 0 )
		{
			consumeDelay = 1000 * (m_pcSkill.CPCSkill::GetSkillLevel(SKID_TF_HIDING, 0) + 4);
		}
		else if( (m_characterPInfo.effectState & EFFECTSTATE_HIDING) != 0 )
		{
			consumeDelay = this->GetEffective(EFST_CHASEWALK, 2);
			if( consumeDelay != 0 )
			{
				spAmount = this->GetEffective(EFST_CHASEWALK, 1);
				if ( time - m_characterTimeInfo.SPLastHealTime > consumeDelay )
				{
					if( this->GetEffective(EFST_SOULLINK, 0) == JT_ROGUE )
						this->SetEffective(EFST_CHASEWALK2, 300000, 1, 0, 0, 1);
					else
						this->SetEffective(EFST_CHASEWALK2, 30000, 1, 0, 0, 1);
				}
			}
			else
			{
				consumeDelay = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(NULL, SKID_AS_CLOAKING, 14, m_pcSkill.CPCSkill::GetSkillLevel(SKID_AS_CLOAKING, 0), 0, 0, MSGpar::CVar(0));
			}
		}
		else
		{
			if( this->GetEffective(EFST_MAXIMIZE, 0) != 0 )
				consumeDelay = 1000 * m_pcSkill.CPCSkill::GetSkillLevel(SKID_BS_MAXIMIZE, 0);

			if( this->GetEffective(EFST_BDPLAYING, 0) != 0 )
			{
				consumeDelay = this->GetEffective(EFST_BDPLAYING, 0);

				if( this->GetEffective(EFST_MOON, 0) != 0 )
					spAmount = this->GetEffective(EFST_MOON, 0);

				if( this->GetEffective(EFST_LONGING, 0) != 0 )
					spAmount = this->GetEffective(EFST_LONGING, 0);

				if( this->GetEffective(EFST_HERMODE, 0) != 0 )
					spAmount = 5;
			}
		}

		if( consumeDelay )
		{
			if( time - m_characterTimeInfo.SPLastHealTime > consumeDelay )
			{
				this->UpdateParameterValue(VAR_SP, -spAmount);

				if( m_characterInfo.sp == 0 )
				{ // no more sp
					if( (m_characterPInfo.effectState & EFFECTSTATE_BURROW) != 0 )
						this->ResetEffectState(EFFECTSTATE_BURROW);

					if( (m_characterPInfo.effectState & EFFECTSTATE_HIDING) != 0 )
						this->ResetEffectState(EFFECTSTATE_HIDING | EFFECTSTATE_FOOTPRINT);
					
					this->ResetEffective(EFST_MAXIMIZE, 0);
					this->ResetEffective(EFST_MAXIMIZE, 0);

					if( this->GetEffective(EFST_BDPLAYING, 0) != 0 )
					{
						g_characterMgr->CCharacterMgr::SendMsg(0, m_pcSkill.m_partnerAID, CM_PLAYSKILL_CANCEL, 0, 0, 0, 0);
						m_pcSkill.CPCSkill::DestroyPlayingSkill();
					}

					if( this->GetEffective(EFST_TENSIONRELAX, 0) != 0 )
						this->ResetEffective(EFST_TENSIONRELAX, 0);
				}
			}
		}
		else if( isRecoverySP != 0 )
		{
			if ( time - m_characterTimeInfo.SPLastHealTime > static_cast<unsigned long>(m_pcClientUpdater.CPCClientUpdater::GetSPHealVelocity()) )
			{
				m_characterTimeInfo.SPLastHealTime = time;

				if( IsSetting(SETTING_NEWHPSP) != 0 )
				{
					if( m_characterInfo.sp < maxSP )
					{
						int intValue = this->CPC::GetIntValue();
						int spRecovery = maxSP / 100 + 1 + intValue / 6;
						int spBonusRecovery = spRecovery * m_characterTimeInfo.SPAcceleration / 100 + ( intValue >= 120 )? (intValue - 112) / 2: 0;
						this->UpdateParameterValue(VAR_SP, spRecovery + spBonusRecovery);
					}
				}
				else
				{
					if( m_characterInfo.sp < this->CPC::GetMaxSP() )
						m_characterInfo.sp = m_characterInfo.sp + 1;
				}
			}
		}

		if( time - m_gageRefreshTime > 900 )
		{
			m_gageRefreshTime = time;

			if( IsSetting(SETTING_NEWHPSP) == 0 )
			{
				m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HP, m_characterInfo.hp);
				m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_SP, m_characterInfo.sp);
			}

			if( m_pcSkill.CPCSkill::GetSkillLevel(SKID_DE_GTIME, 0) != 0 )
			{
				unsigned short SKID = static_cast<unsigned short>(this->GetEffective(EFST_DGAUGE, 0)) + m_pcSkill.CPCSkill::GetSkillLevel(SKID_DE_GTIME, 0);
				if( SKID > SKID_2NDJOB_QUESTBEGIN )
					SKID = SKID_2NDJOB_QUESTBEGIN;

				this->SetEffective(EFST_DGAUGE, 9999, SKID, 0, 0, 1);
			}
		}
	}

	m_pcBattle.CPCBattle::ProcessItemHealRegularly();

	// other checks
	if( this->GetEffective(EFST_CLOAKING, 0) != 0 )
	{
		if( this->CPC::IsMovableAround(1) != 0 )
		{
			if( m_pcSkill.CPCSkill::GetSkillLevel(SKID_AS_CLOAKING, 0) <= 2 )
			{
				this->ResetEffectState(EFFECTSTATE_HIDING);
			}
			else
			{
				this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
				if( this->GetEffective(EFST_CLOAKING, 2) == 0 )
					this->UpdateEffective(EFST_CLOAKING, 1, 2); // can move around
			}
		}
		else
		{
			this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
			if( this->GetEffective(EFST_CLOAKING, 2) == 1 )
				this->UpdateEffective(EFST_CLOAKING, -1, 2); // can't move around
		}
	}

	if( time > m_characterTimeInfo.LastCharInfoSaveTime + CGVar::GetObj()->m_character_data_save_interval_minute * 60000 + GetServerRandom(1000, 20000) )
	{
		m_characterTimeInfo.LastCharInfoSaveTime = time;
		if( m_isValid == 1 )
		{
			CSaveAllADBWork* work = new CSaveAllADBWork(CSaveAllADBWork::AFTER_ACTION_ANYTIME, this->GetAccountID(), this->CPC::GetCharacterID());
			if( work != NULL )
			{
				this->CPC::GetDBInfo(2, work->m_CharacterData.m_data);
				memcpy(work->m_CharacterData.m_characterName, m_characterInfo.characterName, sizeof(work->m_CharacterData.m_characterName));
				work->m_CharacterData.m_bActive = 1;

				m_pcSkill.CPCSkill::UpdateWarpInfo();

				work->m_BodyItemData.m_Length = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemDBFormat(work->m_BodyItemData.m_data, sizeof(work->m_BodyItemData.m_data));
				work->m_BodyItemData.m_bActive = 1;

				if( m_pcitemInventoryMgr.CPCItemInventoryMgr::IsCartOn() != 0 )
				{
					work->m_CartItemData.m_Length = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetCartItemDBFormat(work->m_CartItemData.m_Data, sizeof(work->m_CartItemData.m_Data));
					work->m_CartItemData.m_bActive = 1;
				}

				if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
					delete work;
			}
		}
	}

	this->CPC::ProcessPKInfo();

	for( mystd::map<int,unsigned long>::iterator it = m_effectStateTimeL.begin(); it != m_effectStateTimeL.end(); )
	{
		if( time > it->second )
		{
			Trace("End... STATE: %d\n", it->first);
			this->ResetEffectState(it->first);
			it = m_effectStateTimeL.erase(it);
		}
		else
		{
			++it;
		}
	}

	this->CCharacter::ProcessAllEffective();
	this->CCharacter::ProcessStatusAmount();

	if( (m_characterPInfo.effectState & EFFECTSTATE_RUWACH) != 0 )
	{
		SKILLATTACK_MSG msg;
		msg.msgtype = 0;
		msg.SKID = SKID_AL_RUWACH;
		msg.level = 1;
		msg.skLevel = 1;
		msg.count = 1;
		msg.xPos = static_cast<short>(m_pathInfo.m_moveInfo.xPos);
		msg.yPos = static_cast<short>(m_pathInfo.m_moveInfo.yPos);
		msg.par1 = 0;
		msg.isDivide = 0;
		msg.isEnableDirectPath = 1;
		msg.finalDamage = 0;
		msg.actionType = 6;
		msg.srcAID = 0;
		this->CPC::DetectHidingCharacter(m_characterTimeInfo.SightRange, &msg, m_characterTimeInfo.SightplusAttackPower, 0, 0);
	}

	if( (m_characterPInfo.effectState & EFFECTSTATE_SIGHT) != 0 )
		this->CPC::DetectHidingCharacter(m_characterTimeInfo.SightRange, NULL, 0, 0, 0);

	EFFECTIVE_INFO* effectiveInfo = this->CCharacter::GetEffectiveInfo(EFST_WZ_SIGHTBLASTER);
	if( effectiveInfo != NULL )
	{
		int msgData[2] = { SKID_WZ_SIGHTBLASTER, 1 };
		this->SplashAttack(100, static_cast<short>(m_pathInfo.m_moveInfo.xPos), static_cast<short>(m_pathInfo.m_moveInfo.yPos), 1, effectiveInfo->val[0], effectiveInfo->val[0], m_characterInfo.accountID, &msgData, effectiveInfo->val[1], 1);
	}

	long attackLastTime; this->CPC::GetAttackLastTime(attackLastTime);
	if( this->CPC::IsLockOnMode() != 0 && time > static_cast<unsigned long>(attackLastTime + 2 * this->CPC::GetAttackMotionTime()) )
		m_packetHandler.CPCPacketHandler::LockOnAttack();

	if( m_BodyStateTime[0] != 0 && time > m_BodyStateTime [0] )
	{
		m_BodyStateTime[0] = 0;
		if( curState == CHARACTER_STATE_DEAD )
		{
			m_BodyStateTime[1] = 0;
			m_BodyStateTime[2] = 0;
		}
		else
		{
			this->CPC::SetBodyState(static_cast<short>(m_BodyStateValue));
		}
	}

	if( m_BodyStateTime[1] != 0 && m_BodyStateTime[1] != 9999 && time > m_BodyStateTime[1] )
	{
		m_BodyStateTime[1] = 0;
		m_BodyStateValue = 0;
		this->CPC::SetBodyState(0);
	}

	if( curState != CHARACTER_STATE_DEAD && this->GetEffective(EFST_AUTOBERSERK, 0) != 0 )
	{
		if( this->GetEffective(EFST_PROVOKE, 0) == 11 )
		{
			if( m_characterInfo.hp > this->CPC::GetMaxHP() * 25 / 100 )
				this->ResetEffective(EFST_PROVOKE, 0); // deactivate
		}
		else
		{
			if( m_characterInfo.hp <= this->CPC::GetMaxHP() * 25 / 100 )
			{ // activate
				m_pcBattle.CPCBattle::SetATKPercentInfo(SKID_SM_PROVOKE, 9999, 32);
				m_pcBattle.CPCBattle::SetDEFPercentInfo(SKID_SM_PROVOKE, 9999, -55);
				this->SetEffective(EFST_PROVOKE, 9999, 11, 0, 0, 0);
			}
		}
	}

	if( this->GetEffective(EFST_ENERGYCOAT, 0) != 0 && m_characterInfo.sp == 0 )
		this->ResetEffective(EFST_ENERGYCOAT, 0);

	for( int i = 0; i < 8; ++i )
	{
		if( m_HealthStateTime[i][0] != 0 && time > m_HealthStateTime[i][0] )
		{
			if( curState == CHARACTER_STATE_DEAD )
			{
				m_HealthStateTime[i][0] = 0;
				m_HealthStateTime[i][1] = 0;
				continue;
			}

			this->CPC::SetHealthState(static_cast<short>(m_HealthStateValue[i]));
			m_HealthStateTime[i][0] = 0;
		}

		if( m_HealthStateTime[i][1] != 0 && m_HealthStateTime[i][1] != 9999 && time > m_HealthStateTime[i][1] )
		{
			this->ResetHealthState(1 << i);
			m_HealthStateTime[i][1] = 0;
		}
	}

	m_pcBattle.CPCBattle::CheckStateChange();
	this->CPC::CheckSpecialState(time);
	m_pcSkill.CPCSkill::UpdateSpiritsInfo();
	this->CPC::CheckPalmStrike();

	if( curState != CHARACTER_STATE_DEAD )
		m_pcItem.CPCItem::CheckStateSpecialItem();

	if( m_characterTimeInfo.ChangeSpeedTime != 0 )
	{
		if( time > static_cast<unsigned long>(m_characterTimeInfo.ChangeSpeedTime) )
		{
			this->UpdateParameterValue(VAR_CHANGESPEED, 100);
			this->UpdateParameterValue(VAR_CHANGESPEEDTIME, 0);
			m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_SPEED, this->CPC::GetSpeed());
		}
	}
}


hook_method<void (CPC::*)(unsigned long tick)> CPC::_CheckSpecialState(SERVER, "CPC::CheckSpecialState");
void CPC::CheckSpecialState(unsigned long tick) // line 2193-2224
{
	return (this->*_CheckSpecialState)(tick);

	// TODO
}


hook_method<void (CPC::*)(void)> CPC::_CheckMannerPoint(SERVER, "CPC::CheckMannerPoint");
void CPC::CheckMannerPoint(void)
{
	return (this->*_CheckMannerPoint)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_CheckGuildPassiveSkill(SERVER, "CPC::CheckGuildPassiveSkill");
void CPC::CheckGuildPassiveSkill(void)
{
	return (this->*_CheckGuildPassiveSkill)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_CheckTouchNPCList(SERVER, "CPC::CheckTouchNPCList");
void CPC::CheckTouchNPCList(void)
{
	return (this->*_CheckTouchNPCList)();

	//TODO
}


hook_method<int (CPC::*)(int range)> CPC::_IsMovableAround(SERVER, "CPC::IsMovableAround");
int CPC::IsMovableAround(int range)
{
	return (this->*_IsMovableAround)(range);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_WarpBetweenServer(SERVER, "CPC::WarpBetweenServer");
void CPC::WarpBetweenServer(void)
{
	return (this->*_WarpBetweenServer)();

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnCheckPoint(SERVER, "CPC::OnCheckPoint");
void CPC::OnCheckPoint(int par1)
{
	return (this->*_OnCheckPoint)(par1);

	//TODO
}


hook_method<void (CPC::*)(int par)> CPC::_DispatchCommand(SERVER, "CPC::DispatchCommand");
void CPC::DispatchCommand(int par)
{
	return (this->*_DispatchCommand)(par);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_DisableAllCommand(SERVER, "CPC::DisableAllCommand");
void CPC::DisableAllCommand(void)
{
	return (this->*_DisableAllCommand)();

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnExecExchangeItem(SERVER, "CPC::OnExecExchangeItem");
void CPC::OnExecExchangeItem(int par1)
{
	return (this->*_OnExecExchangeItem)(par1);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_ResetExchangeItemInfo(SERVER, "CPC::ResetExchangeItemInfo");
void CPC::ResetExchangeItemInfo(void)
{
	return (this->*_ResetExchangeItemInfo)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_CartOff(SERVER, "CPC::CartOff");
void CPC::CartOff(void)
{
	return (this->*_CartOff)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_MultiCastStateInfo(SERVER, "CPC::MultiCastStateInfo");
void CPC::MultiCastStateInfo(void)
{
	return (this->*_MultiCastStateInfo)();

	PACKET_ZC_STATE_CHANGE3 outpacket;
	outpacket.PacketType = HEADER_ZC_STATE_CHANGE3;
	outpacket.AID = m_characterInfo.accountID;
	outpacket.bodyState = static_cast<short>(m_characterPInfo.bodyState);
	outpacket.healthState = static_cast<short>(m_characterPInfo.healthState);
	outpacket.effectState = m_characterPInfo.effectState;
	outpacket.isPKModeON = ( this->CPC::IsPKModeON() != 0 );

	this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


//hook_method<void (CPC::*)(void)> CPC::_SaveWarpInfo(SERVER, "CPC::SaveWarpInfo");
void CPC::SaveWarpInfo(void)
{
//	return (this->*_SaveWarpInfo)();

	assert(false);
	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_NotifyInfoToSection(SERVER, "CPC::NotifyInfoToSection");
void CPC::NotifyInfoToSection(void)
{
	return (this->*_NotifyInfoToSection)();

	if( m_mapRes == NULL )
		return;

	NEIGHBORHOOD_SECTION result;
	result.section[0] = NULL;
	result.section[1] = NULL;
	result.section[2] = NULL;
	result.section[3] = NULL;
	m_mapRes->CMapRes::GetNeighborhoodSections(m_pathInfo.m_moveInfo.xPos, m_pathInfo.m_moveInfo.yPos, 18, &result); //inlined

	for( int i = 0; i < countof(result.section); ++i )
		if( result.section[i] != NULL )
			m_pcClientUpdater.CPCClientUpdater::UpdateCharacter(result.section[i]);
}


//hook_method<int (CPC::*)(void)> CPC::_GetPartyInMyMapTotalLevel(SERVER, "CPC::GetPartyInMyMapTotalLevel");
int CPC::GetPartyInMyMapTotalLevel(void)
{
//	return (this->*_GetPartyInMyMapTotalLevel)();

	assert(false);
	return 0;
	//TODO
}


//hook_method<int (CPC::*)(void)> CPC::_GetPartyInMyMapTotalNextExp(SERVER, "CPC::GetPartyInMyMapTotalNextExp");
int CPC::GetPartyInMyMapTotalNextExp(void)
{
//	return (this->*_GetPartyInMyMapTotalNextExp)();

	assert(false);
	return 0;
	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_GetPartyMemberCountInMyMap(SERVER, "CPC::GetPartyMemberCountInMyMap");
int CPC::GetPartyMemberCountInMyMap(void)
{
	return (this->*_GetPartyMemberCountInMyMap)();

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_OnAddMemberToGroup(SERVER, "CPC::OnAddMemberToGroup");
void CPC::OnAddMemberToGroup(int par1, int par2)
{
	return (this->*_OnAddMemberToGroup)(par1, par2);

	int size = (int)par1;
	PACKET_IZ_ADD_MEMBER_TO_GROUP2& packet = *(PACKET_IZ_ADD_MEMBER_TO_GROUP2*)par2;

	PACKET_ZC_ADD_MEMBER_TO_GROUP2 outpacket;
	outpacket.PacketType = HEADER_ZC_ADD_MEMBER_TO_GROUP2;
	outpacket.state = packet.state;
	outpacket.Role = packet.Role;
	outpacket.AID = packet.AID;
	outpacket.ItemPickupRule = packet.ItemPickupRule;
	outpacket.ItemDivisionRule = packet.ItemDivisionRule;
	outpacket.xPos = 0;
	outpacket.yPos = 0;
	memcpy(outpacket.groupName, packet.groupName, sizeof(outpacket.groupName));
	memcpy(outpacket.characterName, packet.characterName, sizeof(outpacket.characterName));
	memcpy(outpacket.mapName, packet.mapName, sizeof(outpacket.mapName));

	if( strncmp(packet.mapName, m_characterInfo.mapName, sizeof(packet.mapName)) == 0 )
	{
		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(packet.AID, PC_TYPE);
		if( pc != NULL )
		{
			int xPos;
			int yPos;
			pc->GetParameterValue(VAR_CURXPOS, xPos);
			pc->GetParameterValue(VAR_CURYPOS, yPos);
			outpacket.xPos = xPos;
			outpacket.yPos = yPos;
		}
	}

	m_characterInfo.PartyItemPickupRule = packet.ItemPickupRule;
	m_characterInfo.PartyItemDivisionRule = packet.ItemDivisionRule;

	if( m_characterInfo.accountID == packet.AID )
		m_characterInfo.isGroupMaster = ( packet.Role == 0 );

	if( packet.state )
		this->CPC::DeleteGroupMember(packet.AID);
	else
		this->CPC::AddGroupMember(packet.AID);

	this->CPC::ForceSend(81, (char*)&outpacket);

	int level = m_pcSkill.CPCSkill::GetSkillLevel(SKID_MB_FIGHTING, 0);
	if( level != 0 )
	{
		int count = this->CPC::GetPartyMemberCountInMyMap();
		this->CCharacter::ResetStatusAmount(SKID_MB_FIGHTING, 0);
		this->OnChangeStatusAmount(SKID_MB_FIGHTING, 165, 9999, level * count);
	}
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_OnDeleteMemberFromGroup(SERVER, "CPC::OnDeleteMemberFromGroup");
void CPC::OnDeleteMemberFromGroup(int par1, int par2)
{
	return (this->*_OnDeleteMemberFromGroup)(par1, par2);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_OnAckMakeGroup(SERVER, "CPC::OnAckMakeGroup");
void CPC::OnAckMakeGroup(int par1, int par2)
{
	return (this->*_OnAckMakeGroup)(par1, par2);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnGroupList(SERVER, "CPC::OnGroupList");
void CPC::OnGroupList(int par1, int par2, int par3)
{
	return (this->*_OnGroupList)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_OnAckReqJoinGroup(SERVER, "CPC::OnAckReqJoinGroup");
void CPC::OnAckReqJoinGroup(int par1, int par2)
{
	return (this->*_OnAckReqJoinGroup)(par1, par2);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_OnReqJoinGroup(SERVER, "CPC::OnReqJoinGroup");
void CPC::OnReqJoinGroup(int par1, int par2)
{
	return (this->*_OnReqJoinGroup)(par1, par2);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* ch, int par1, int par2, int par3)> CPC::_OnNotifyPositionParty(SERVER, "CPC::OnNotifyPositionParty");
void CPC::OnNotifyPositionParty(CCharacter* ch, int par1, int par2, int par3)
{
	return (this->*_OnNotifyPositionParty)(ch, par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* ch, int par1, int par2, int par3)> CPC::_OnNotifyPositionGuild(SERVER, "CPC::OnNotifyPositionGuild");
void CPC::OnNotifyPositionGuild(CCharacter* ch, int par1, int par2, int par3)
{
	return (this->*_OnNotifyPositionGuild)(ch, par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* ch, int par1, int par2, int par3)> CPC::_OnNotifyHpParty(SERVER, "CPC::OnNotifyHpParty");
void CPC::OnNotifyHpParty(CCharacter* ch, int par1, int par2, int par3)
{
	return (this->*_OnNotifyHpParty)(ch, par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_OnGRIDUpdate(SERVER, "CPC::OnGRIDUpdate");
void CPC::OnGRIDUpdate(int par1, int par2)
{
	return (this->*_OnGRIDUpdate)(par1, par2);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnChatParty(SERVER, "CPC::OnChatParty");
void CPC::OnChatParty(int par1, int par2, int par3)
{
	return (this->*_OnChatParty)(par1, par2, par3);

	//TODO
}


//hook_method<void (CPC::*)(int par1)> CPC::_OnDeleteFromGroupLIst(SERVER, "CPC::OnDeleteFromGroupLIst");
void CPC::OnDeleteFromGroupLIst(int par1)
{
//	return (this->*_OnDeleteFromGroupLIst)(par1);

	assert(false);
	//TODO
}


//hook_method<void (CPC::*)(unsigned long commandID)> CPC::_DeleteCommand(SERVER, "CPC::DeleteCommand");
void CPC::DeleteCommand(unsigned long commandID)
{
//	return (this->*_DeleteCommand)(commandID);

	assert(false);
	//TODO
}


hook_method<void (CPC::*)(CCharacter* sender, int exp, int par1)> CPC::_OnAddExp(SERVER, "CPC::OnAddExp");
void CPC::OnAddExp(CCharacter* sender, int exp, int par1)
{
	return (this->*_OnAddExp)(sender, exp, par1);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* sender, int exp)> CPC::_AddExp(SERVER, "CPC::AddExp");
void CPC::AddExp(CCharacter* sender, int exp)
{
	return (this->*_AddExp)(sender, exp);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* sender, int par1, int par2, int par3)> CPC::_OnAddJobExp(SERVER, "CPC::OnAddJobExp");
void CPC::OnAddJobExp(CCharacter* sender, int par1, int par2, int par3)
{
	return (this->*_OnAddJobExp)(sender, par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* sender, int exp)> CPC::_AddJobExp(SERVER, "CPC::AddJobExp");
void CPC::AddJobExp(CCharacter* sender, int exp)
{
	return (this->*_AddJobExp)(sender, exp);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsShareEnable(SERVER, "CPC::IsShareEnable");
int CPC::IsShareEnable(void)
{
	return (this->*_IsShareEnable)();

	mystd::list<unsigned long>::const_iterator it;

	for( it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
		if( *it == m_characterInfo.accountID )
			break;

	if( it == m_groupMember.end() )
	{
		Trace("My AccountID is not in groupList\n");
		this->CPC::AddGroupMember(m_characterInfo.accountID);
	}

	if( m_familyInfo.expOption == 1 )
		return 1;

	int maxlv = 0;
	int minlv = 200;
	for( it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
	{
		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(*it, PC_TYPE);
		if( pc == NULL )
			continue;

		int level = 0;
		pc->GetParameterValue(VAR_CLEVEL, level);

		if( maxlv < level )
			maxlv = level;
		if( minlv > level )
			minlv = level;
	}

	return ( maxlv - minlv <= 10 );
}


hook_method<void (CPC::*)(CCharacter* sender, int par1)> CPC::_OnShareExp(SERVER, "CPC::OnShareExp");
void CPC::OnShareExp(CCharacter* sender, int par1)
{
	return (this->*_OnShareExp)(sender, par1);

	if( !this->CPC::IsShareEnable() )
		return;

	int count = this->CPC::GetPartyMemberCountInMyMap();
	if( count < 1 )
		count = 1;

	int exp = 1 + par1 / count;

	for( mystd::list<unsigned long>::const_iterator it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
	{
		unsigned long AID = *it;

		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(AID, PC_TYPE);
		if( pc == NULL )
			continue;

		if( pc->GetState() == CHARACTER_STATE_DEAD )
			continue;

		int mapID;
		pc->GetParameterValue(VAR_MAPID, mapID);
		if( m_characterInfo.mapID != mapID )
			continue;

		g_characterMgr->CCharacterMgr::SendMsg(sender, pc, CM_ADD_EXP, exp, 0, 0, 0);
	}
}


hook_method<void (CPC::*)(CCharacter* sender, int par1)> CPC::_OnShareJobExp(SERVER, "CPC::OnShareJobExp");
void CPC::OnShareJobExp(CCharacter* sender, int par1)
{
	return (this->*_OnShareJobExp)(sender, par1);

	if( !this->CPC::IsShareEnable() )
		return;

	int count = this->CPC::GetPartyMemberCountInMyMap();
	if( count < 1 )
		count = 1;

	int exp = 1 + par1 / count;

	for( mystd::list<unsigned long>::const_iterator it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
	{
		unsigned long AID = *it;

		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(AID, PC_TYPE);
		if( pc == NULL )
			continue;

		if( pc->GetState() == CHARACTER_STATE_DEAD )
			continue;

		int mapID;
		pc->GetParameterValue(VAR_MAPID, mapID);
		if( m_characterInfo.mapID != mapID )
			continue;

		g_characterMgr->CCharacterMgr::SendMsg(sender, pc, CM_ADD_JOBEXP, exp, 0, 0, 0);
	}
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnAddPartyExp(SERVER, "CPC::OnAddPartyExp");
void CPC::OnAddPartyExp(int par1, int par2, int par3)
{
	return (this->*_OnAddPartyExp)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnAddPartyJOBExp(SERVER, "CPC::OnAddPartyJOBExp");
void CPC::OnAddPartyJOBExp(int par1, int par2, int par3)
{
	return (this->*_OnAddPartyJOBExp)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int virtue)> CPC::_OnAddVirtue(SERVER, "CPC::OnAddVirtue");
void CPC::OnAddVirtue(int virtue)
{
	return (this->*_OnAddVirtue)(virtue);

	//TODO
}


hook_method<void (CPC::*)(unsigned long enemyAID, int& isRestart)> CPC::_OnDead(SERVER, "CPC::OnDead");
void CPC::OnDead(unsigned long enemyAID, int& isRestart)
{
	return (this->*_OnDead)(enemyAID, isRestart);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnNotifyMakableWeaponItemList(SERVER, "CPC::OnNotifyMakableWeaponItemList");
void CPC::OnNotifyMakableWeaponItemList(void)
{
	return (this->*_OnNotifyMakableWeaponItemList)();

	char buf[1024];
	unsigned short bufLen = 0;

	int n = 0;
	while( 1 )
	{
		int ITID = g_weaponItemList->CItemList::GetNth(n);
		if( ITID -= -1 )
			break;

		if( !m_pcSkill.CPCSkill::IsMakableItemBySkill(ITID)
		||  !m_pcSkill.CPCSkill::IsMakableItemByItem(ITID) )
			continue;

		MAKABLEITEM_INFO info;
		info.ITID = ITID; // NOTE: rest is sent uninitialized
		memcpy(&buf[bufLen], &info, sizeof(info));
		bufLen += sizeof(info);

		if( bufLen > 1000 )
		{
			bufLen -= sizeof(info);
			break; // no more room.
		}

		++n;
	}

	PACKET_ZC_MAKABLEITEMLIST outpacket;
	outpacket.PacketType = HEADER_ZC_MAKABLEITEMLIST;
	outpacket.PacketLength = sizeof(outpacket) + bufLen;
	this->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	this->CPC::Send(bufLen, buf);

	if( bufLen > 0 )
	{
		m_makingItemFlag = 1;
		this->CPC::OnDisableItemMove();
	}
}


hook_method<void (CPC::*)(void)> CPC::_OnNotifyMakableMetalItemList(SERVER, "CPC::OnNotifyMakableMetalItemList");
void CPC::OnNotifyMakableMetalItemList(void)
{
	return (this->*_OnNotifyMakableMetalItemList)();

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnMVPItem(SERVER, "CPC::OnMVPItem");
void CPC::OnMVPItem(int par1)
{
	return (this->*_OnMVPItem)(par1);

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnMVPExp(SERVER, "CPC::OnMVPExp");
void CPC::OnMVPExp(int par1)
{
	return (this->*_OnMVPExp)(par1);

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnAddSkill(SERVER, "CPC::OnAddSkill");
void CPC::OnAddSkill(int par1)
{
	return (this->*_OnAddSkill)(par1);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_MultiCastMVP(SERVER, "CPC::MultiCastMVP");
void CPC::MultiCastMVP(void)
{
	return (this->*_MultiCastMVP)();

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnSkillLevelUp(SERVER, "CPC::OnSkillLevelUp");
void CPC::OnSkillLevelUp(int par1)
{
	return (this->*_OnSkillLevelUp)(par1);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnHPPlus(SERVER, "CPC::OnHPPlus");
void CPC::OnHPPlus(int par1, int par2, int par3)
{
	return (this->*_OnHPPlus)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnSPPlus(SERVER, "CPC::OnSPPlus");
void CPC::OnSPPlus(int par1, int par2, int par3)
{
	return (this->*_OnSPPlus)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int target, int level, int spCost)> CPC::_OnUseSkill(SERVER, "CPC::OnUseSkill");
void CPC::OnUseSkill(int SKID, int target, int level, int spCost)
{
	return (this->*_OnUseSkill)(SKID, target, level, spCost);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int skLevel, int spCost)> CPC::_OnUseGroundSkill(SERVER, "CPC::OnUseGroundSkill");
void CPC::OnUseGroundSkill(int par1, int par2, int skLevel, int spCost)
{
	return (this->*_OnUseGroundSkill)(par1, par2, skLevel, spCost);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int par2, int par3)> CPC::_ActSkillToChar_SpATK(SERVER, "CPC::ActSkillToChar_SpATK");
void CPC::ActSkillToChar_SpATK(int SKID, int par2, int par3)
{
	return (this->*_ActSkillToChar_SpATK)(SKID, par2, par3);

	int targetID = (int)par2;
	MSG_TYPE4_FIVEDWORD& data = *(MSG_TYPE4_FIVEDWORD*)par3;
	int spCost = (int)data.data4;
	int skLevel = (int)data.data5;

	CCharacter* target = g_characterMgr->CCharacterMgr::FastFindCharacter(targetID);
	if( target == NULL )
	{
		this->SkillUseAck(SKID, 0, false, 10);
		return;
	}

	this->UpdateParameterValue(VAR_SP, -spCost);

	// track number of successful attacks (side-effects don't activate if complete miss)
	int count = 0;

	PosInfo chPos;
	target->GetParameterValue(VAR_CURXPOS, chPos.x);
	target->GetParameterValue(VAR_CURYPOS, chPos.y);

	SKILLATTACK_MSG skillMsg;
	skillMsg.targetAID = targetID;
	skillMsg.level = static_cast<short>(skLevel);
	skillMsg.skLevel = static_cast<short>(skLevel);
	skillMsg.xPos = static_cast<short>(chPos.x);
	skillMsg.yPos = static_cast<short>(chPos.y);
	skillMsg.srcAID = 0;
	skillMsg.isDivide = 0;
	skillMsg.finalDamage = 0;
	skillMsg.count = 1;
	skillMsg.msgtype = 1;
	skillMsg.isEnableDirectPath = true;
	skillMsg.SKID = SKID;
	skillMsg.actionType = 6;
	skillMsg.par1 = -30000;
	count += this->SkillAttack(&skillMsg, 100, 100, false);

	switch( SKID )
	{
	case SKID_SM_MAGNUM:
	{
		int hp = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(NULL, skillMsg.SKID, 14, skillMsg.level, 0, 0, 0);
		this->UpdateParameterValue(VAR_HP, -hp);

		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		count += this->SplashAttack(data.data1, (short)m_pathInfo.m_moveInfo.xPos, (short)m_pathInfo.m_moveInfo.yPos, 1, 2, 1, m_characterInfo.accountID, &msgData, data.data2, 1);
	}
	break;
	case SKID_KN_BOWLINGBASH:
	{
		const int plusAttPower = (int)data.data1;

		if( target->CCharacter::GetMapRes() == NULL )
			break;

		int tarPosX, tarPosY;
		target->GetParameterValue(VAR_CURXPOS, tarPosX);
		target->GetParameterValue(VAR_CURYPOS, tarPosY);

		mystd::vector<CCharacter*>* section = target->CCharacter::GetMapRes()->CMapRes::GetSectionByCellPos(tarPosX, tarPosY);

		mystd::map<CCharacter*,CollideInfo> collidedList;
		CollideInfo& firstInfo = collidedList[target];
		firstInfo.sectionList = section;
		firstInfo.count = 1;

		// compute the collision result list
		this->CPC::CollideSplashAttack(plusAttPower, this, target, m_pathInfo.m_moveInfo.dir, 1, skillMsg.SKID, skillMsg.level, collidedList);

		for( mystd::map<CCharacter*,CollideInfo>::iterator it = collidedList.begin(); it != collidedList.end(); ++it )
		{
			CCharacter* target = it->first;
			mystd::vector<CCharacter*>* srcSection = it->second.sectionList;

			if( target->CCharacter::GetMapRes() == NULL )
				continue;

			target->GetParameterValue(VAR_CURXPOS, tarPosX);
			target->GetParameterValue(VAR_CURYPOS, tarPosY);

			mystd::vector<CCharacter*>* dstSection = target->CCharacter::GetMapRes()->CMapRes::GetSectionByCellPos(tarPosX, tarPosY);
			if( dstSection != srcSection )
				target->CCharacter::GetMapRes()->CMapRes::MoveCharacter(srcSection, dstSection, target);
		}
	}
	break;
	case SKID_KN_BRANDISHSPEAR:
	{
		CITP* itp = this->CPC::GetITPEquipedWeapon();
		if( itp == NULL )
		{
			this->SkillUseAck(skillMsg.SKID, 0, 0, 6);
			break;
		}

		short type = itp->GetClass();
		if( type != WEAPONTYPE_SPEAR && type != WEAPONTYPE_TWOHANDSPEAR )
		{
			this->SkillUseAck(skillMsg.SKID, 0, 0, 6);
			break;
		}

		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		this->SplashAttack2(data.data1, chPos, 1, 2, data.data2, &msgData, 1, 100, NULL);

		this->SetEffective(EFST_NOEQUIPWEAPON, 1000, 1, 0, 0, 0);
	}
	break;
	case SKID_KN_SPEARSTAB:
	{
		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		this->CPC::SplashAttack3(data.data1, chPos, 1, &msgData, data.data2, 1);
	}
	break;
	case SKID_AS_GRIMTOOTH:
	{
		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		count += this->SplashAttack(data.data1, chPos.x, chPos.y, 0, 1, 1, m_characterInfo.accountID, &msgData, data.data2, 1);
	}
	break;
	case SKID_MC_CARTREVOLUTION:
	{
		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		count += this->SplashAttack(data.data1, chPos.x, chPos.y, 1, 1, 1, m_characterInfo.accountID, &msgData, data.data1, 1);
	}
	break;
	case SKID_GS_SPREADATTACK:
	{
		this->CPC::ConsumeEquipedArrow(5);

		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		count += this->SplashAttack(data.data1, chPos.x, chPos.y, 0, data.data2, data.data2, m_characterInfo.accountID, &msgData, data.data1, 1);
	}
	break;
	case SKID_NJ_HUUMA:
	{
		int damage = this->CPC::GetAttackFinalDamage(target, 2, 0, data.data1, 100, 1, 1, 0, 0);
		int number = min(1, this->CCharacter::GetCountInArea(chPos.x, chPos.y, 1, 0, 0, 0)); //FIXME: duplicate evaluation inefficiency

		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		count += this->SplashAttack(damage / number, chPos.x, chPos.y, 0, 1, 1, m_characterInfo.accountID, &msgData, damage / number, data.data3);
	}
	break;
	case SKID_NJ_KAMAITACHI:
	{
		this->CPC::ConsumeItem(ITID_WIND_STONE, 1, NULL);

		MSG_TYPE1_TWODWORD msgData;
		msgData.data1 = skillMsg.SKID;
		msgData.data2 = skillMsg.level;
		if( this->SplashAttack2(data.data1, chPos, 0, 1, data.data2, &msgData, 1, 100, NULL) )
		{
			++count;
			break;
		}

		skillMsg.msgtype = 0;
		skillMsg.par1 = 0;
		skillMsg.actionType = 5;
		count = this->SkillAttack(&skillMsg, data.data1, 100, 0); //NOTE: reuses contents of previous skillMsg
	}
	break;
	default:
		if( GetCharSkill()->CCharSkill::AttSkillToChar(this, target, skillMsg.SKID, &data, &skillMsg) == -1 )
			++count;
	break;
	}

	int postDelayTime = g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetPostDelayTM(skillMsg.SKID, skillMsg.level);
	this->SetEffective(EFST_POSTDELAY, postDelayTime, 1, 0, 0, 0);

	if( count > 0 )
		m_pcBattle.CPCBattle::CheckSkillSpecialOption(skillMsg.SKID, target, 0, 0);
}


hook_method<void (CPC::*)(int SKID, int target, int par1)> CPC::_OPSkillToRangeGuild(SERVER, "CPC::OPSkillToRangeGuild");
void CPC::OPSkillToRangeGuild(int SKID, int target, int par1)
{
	return (this->*_OPSkillToRangeGuild)(SKID, target, par1);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int target, int par1)> CPC::_OPSkillToGuild(SERVER, "CPC::OPSkillToGuild");
void CPC::OPSkillToGuild(int SKID, int target, int par1)
{
	return (this->*_OPSkillToGuild)(SKID, target, par1);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int tarAID, int SKInfo)> CPC::_AttSkillToChar22_1(SERVER, "CPC::AttSkillToChar22_1");
void CPC::AttSkillToChar22_1(int SKID, int tarAID, int SKInfo)
{
	return (this->*_AttSkillToChar22_1)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_SPAttSkillToChar22_1(SERVER, "CPC::SPAttSkillToChar22_1");
void CPC::SPAttSkillToChar22_1(int par1, int par2, int par3)
{
	return (this->*_SPAttSkillToChar22_1)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int target, int par1)> CPC::_SPAttSkillToChar22_2(SERVER, "CPC::SPAttSkillToChar22_2");
void CPC::SPAttSkillToChar22_2(int SKID, int target, int par1)
{
	return (this->*_SPAttSkillToChar22_2)(SKID, target, par1);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int tarAID, int SKInfo)> CPC::_OperSkillToChar22_1(SERVER, "CPC::OperSkillToChar22_1");
void CPC::OperSkillToChar22_1(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OperSkillToChar22_1)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<int (CPC::*)(const int in_SKID, const int in_SKLevel, const int in_SPcost, const int in_ConsumeItemID, const int in_Data2, const int in_FailProbabilityFactor, CCharacter* const in_pTargetCh)> CPC::_OperSkillToChar22_1_SA_family(SERVER, "CPC::OperSkillToChar22_1_SA_family");
int CPC::OperSkillToChar22_1_SA_family(const int in_SKID, const int in_SKLevel, const int in_SPcost, const int in_ConsumeItemID, const int in_Data2, const int in_FailProbabilityFactor, CCharacter* const in_pTargetCh)
{
	return (this->*_OperSkillToChar22_1_SA_family)(in_SKID, in_SKLevel, in_SPcost, in_ConsumeItemID, in_Data2, in_FailProbabilityFactor, in_pTargetCh);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int tarAID, int SKInfo)> CPC::_OperSkillToSelf22_1(SERVER, "CPC::OperSkillToSelf22_1");
void CPC::OperSkillToSelf22_1(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OperSkillToSelf22_1)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int tarAID, int SKInfo)> CPC::_OnGroundSkill22_1(SERVER, "CPC::OnGroundSkill22_1");
void CPC::OnGroundSkill22_1(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OnGroundSkill22_1)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* ch, MSG_TYPE4_FIVEDWORD* data, int par1)> CPC::_OnTouchedSkillObj22_1(SERVER, "CPC::OnTouchedSkillObj22_1");
void CPC::OnTouchedSkillObj22_1(CCharacter* ch, MSG_TYPE4_FIVEDWORD* data, int par1)
{
	return (this->*_OnTouchedSkillObj22_1)(ch, data, par1);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* other, MSG_TYPE4_FIVEDWORD* data, int par1)> CPC::_OnTouchedSkillObj22_2(SERVER, "CPC::OnTouchedSkillObj22_2");
void CPC::OnTouchedSkillObj22_2(CCharacter* other, MSG_TYPE4_FIVEDWORD* data, int par1)
{
	return (this->*_OnTouchedSkillObj22_2)(other, data, par1);

	//TODO
}


hook_method<void (CPC::*)(int flag)> CPC::_CancelCasting(SERVER, "CPC::CancelCasting");
void CPC::CancelCasting(int flag)
{
	return (this->*_CancelCasting)(flag);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnAutoSpellList(SERVER, "CPC::OnAutoSpellList");
void CPC::OnAutoSpellList(int par1, int par2, int par3)
{
	return (this->*_OnAutoSpellList)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int maxHP, int maxSP, int weightPercent)> CPC::_ApplyPlusHpSp(SERVER, "CPC::ApplyPlusHpSp");
void CPC::ApplyPlusHpSp(int maxHP, int maxSP, int weightPercent) // line 8830-8918
{
	return (this->*_ApplyPlusHpSp)(maxHP, maxSP, weightPercent);

	// TODO
}


hook_method<void (CPC::*)(void)> CPC::_AM_ReqMakingHomun(SERVER, "CPC::AM_ReqMakingHomun");
void CPC::AM_ReqMakingHomun(void)
{
	return (this->*_AM_ReqMakingHomun)();

	//TODO
}


hook_method<void (CPC::*)(int SKID, int target, int param)> CPC::_AttSkillToChar22_2(SERVER, "CPC::AttSkillToChar22_2");
void CPC::AttSkillToChar22_2(int SKID, int target, int param)
{
	return (this->*_AttSkillToChar22_2)(SKID, target, param);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int target, int param, MSGpar::CVar in_var)> CPC::_OperSkillToChar22_2(SERVER, "CPC::OperSkillToChar22_2");
void CPC::OperSkillToChar22_2(int SKID, int target, int param, MSGpar::CVar in_var)
{
	return (this->*_OperSkillToChar22_2)(SKID, target, param, in_var);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int target, int param)> CPC::_OperSkillToSelf22_2(SERVER, "CPC::OperSkillToSelf22_2");
void CPC::OperSkillToSelf22_2(int SKID, int target, int param)
{
	return (this->*_OperSkillToSelf22_2)(SKID, target, param);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int target, int param)> CPC::_OnGroundSkill22_2(SERVER, "CPC::OnGroundSkill22_2");
void CPC::OnGroundSkill22_2(int SKID, int target, int param)
{
	return (this->*_OnGroundSkill22_2)(SKID, target, param);

	//TODO
}


hook_method<int (CPC::*)(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bSilenceSkill)> CPC::_SkillAttack(SERVER, "CPC::SkillAttack");
int CPC::SkillAttack(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bSilenceSkill)
{
	return (this->*_SkillAttack)(msg, plusATTPowerPercent, plusATTSuccessPercent, in_bSilenceSkill);
/*
	char v22; // zf@49
	int v23; // eax@49
	int v25; // ebx@57
	int v28; // eax@62
	int v30; // eax@65
	int v31; // ebp@66
	int v33; // eax@68
	__int16 v42; // ax@87
	int v43; // eax@87
	signed int v45; // ebp@92
	int v51; // ebp@116
	signed int v66; // ecx@162
	int v68; // ebp@163
	int v69; // eax@180
	int v70; // ecx@181
	signed int v71; // edx@189
	int v72; // eax@190
	int v73; // eax@192
	int v74; // eax@193
	unsigned __int8 v78; // sf@207
	int v80; // eax@207
	int damage; // [sp+10Ch] [bp-98h]@56
	int chType; // [sp+124h] [bp-80h]@6
	int isMagicImmune; // [sp+128h] [bp-7Ch]@62
	int CHJob; // [sp+12Ch] [bp-78h]@47
	COMMAND_QUEUE command; // [sp+164h] [bp-40h]@78
	int par4; // [sp+1B8h] [bp+14h]@0

	if( msg->SKID == SKID_WZ_FROSTNOVA )
		msg->SKID = SKID_MG_FROSTDIVER;

	if( msg->actionType != 5 )
		m_pcClientUpdater.CPCClientUpdater::StopMove();

	CCharacter* v10 = g_characterMgr->CCharacterMgr::FastFindCharacter(msg->targetAID);
	if( v10 == NULL )
		return 0;

	chType = v10->GetType();

	int state;
	v10->GetParameterValue(VAR_STATE, &state);
	if( state == CHARACTER_STATE_DEAD )
		return 0;

	int effectState;
	v10->GetParameterValue(VAR_EFFECTSTATE, &effectState);
	if( effectState & EFFECTSTATE_SPECIALHIDING )
		return 0;
	if( effectState & EFFECTSTATE_BURROW && g_skillTypeInfoMgr->CSkillTypeInfoMgr::GetProperty(msg->SKID) != 2 )
		return 0;

	signed int v15 = 2; // ecx@10
	v15 = 2;

	switch( msd->SKID )
	{
	case SKID_AM_DEMONSTRATION:
		v15 |= 4;
		break;
	case SKID_RA_CLUSTERBOMB:
	case SKID_HT_LANDMINE:
	case SKID_HT_FREEZINGTRAP:
	case SKID_HT_BLASTMINE:
	case SKID_HT_CLAYMORETRAP:
		v15 |= 4;
		break;
	}
	if( msg->SKID >= 2240 && msg->SKID <= 2254 )
		v15 |= 4u;

	if( msg->par1 != -30000 && !v10->IsTarget(this, v15) )
		return 0;

	if( msg->SKID != SKID_PA_GOSPEL && !this->CPC::IsAttackable(msg->SKID) )
		return 0;

	int desYPos;
	int desXPos;
	v10->GetParameterValue(VAR_CURXPOS, &desXPos);
	v10->GetParameterValue(VAR_CURYPOS, &desYPos);

	if( m_mapRes == NULL )
		return 0;

	if( msg->isEnableDirectPath && !m_mapRes->CMapRes::IsDirectPath(msg->xPos, msg->yPos, desXPos, desYPos, 0) )
		return 0;

	PACKET_ZC_NOTIFY_SKILL2 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_SKILL2;
	outpacket.startTime = timeGetTime();
	outpacket.AID = ( msg->srcAID ) ? msg->srcAID : m_characterInfo.accountID;
	outpacket.action = msg->actionType;
	outpacket.targetID = msg->targetAID;
	outpacket.SKID = msg->SKID;
	outpacket.level = msg->level;

	int targetClass = 0;
	int skillProperty = PROPERTY_NOTHING;

	CSkillTypeInfo* skillTypeInfo = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SearchSkillTypeInfo(msg->SKID);
	if( skillTypeInfo != NULL )
	{
		skillProperty = skillTypeInfo->GetProperty();

		if( msg->SKID >= SKID_SL_STIN && msg->SKID <= SKID_SL_SMA )
		{
			if( this->GetEffective(EFST_PROPERTYWATER, 0) )
				skillProperty = PROPERTY_WATER;
			else
			if( this->GetEffective(EFST_PROPERTYFIRE, 0) )
				skillProperty = PROPERTY_FIRE;
			else
			if( this->GetEffective(EFST_PROPERTYDARK, 0) )
				skillProperty = PROPERTY_DARKNESS;
			else
			if( this->GetEffective(EFST_ASPERSIO, 0) )
				skillProperty = PROPERTY_SAINT;
			else
			if( this->GetEffective(EFST_PROPERTYTELEKINESIS, 0) )
				skillProperty = PROPERTY_TELEKINESIS;
			else
			if( this->GetEffective(EFST_PROPERTYWIND, 0) )
				skillProperty = PROPERTY_WIND;
			else
			if( this->GetEffective(EFST_PROPERTYGROUND, 0) )
				skillProperty = PROPERTY_GROUND;
		}
	}

	int skillPattern = 0;
	int isRangeAttack = 0;
	CHJob = 0;

	if( skillTypeInfo != NULL )
	{
		skillPattern = skillTypeInfo->m_pattern;
		isRangeAttack = ( skillTypeInfo->GetAttackRange(msg->level) >= 4 );

		if( msg->SKID == SKID_DA_CARTSWING )
		{
			v23 = GetServerRandom(0, 20000) & 0x80000001;
			v22 = v23 == 0;
			if ( v23 < 0 )
				v22 = ((v23 - 1) | 0xFFFFFFFE) == -1;

			if ( v22 )
				skillPattern = 2;
		}
	}

	if( msg->msgtype )
	{
		damage = msg->par1;

		if( msg->SKID != SKID_ASC_BREAKER )
			targetClass = 1;

		if( msg->SKID == SKID_HW_MAGICCRASHER || msg->SKID == SKID_LK_SPIRALPIERCE )
		{
			damage += this->CPC::GetRefiningAttPower(2);

			skillProperty = this->GetWeaponProperty(2, 0);

			v45 = 0;
			IVItEquipItem* v44 = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedItem(2u);
			if( v44 )
			{
				if ( v44->baseclass_0.m_slotInfo.info[0] == 255 )
				{
					if( !m_characterPInfo.attack )
					{
						skillProperty = (unsigned __int8)v44->baseclass_0.m_slotInfo.info[1];
					}
					v45 = HIBYTE(v44->baseclass_0.m_slotInfo.info[1]);
					if ( HIBYTE(v44->baseclass_0.m_slotInfo.info[1]) == 15 )
						v45 = 40;
				}
			}

			damage += v45;
		}
	}
	else
	{
		if ( msg->SKID != 0 && skillPattern == 2 )
		{
			damage = this->CPC::GetMagicAttackFinalDamage(v10, plusATTPowerPercent, plusATTSuccessPercent, msg->SKID);
			targetClass = 1;
		}
		else
		{
			v25 = 1;

			switch( msg->SKID )
			{
				case SKID_GS_PIERCINGSHOT:
LABEL_72:
					v25 = 5;
					break;
				case SKID_BA_MUSICALSTRIKE:
				case SKID_DC_THROWARROW:
				case SKID_CG_ARROWVULCAN:
					v25 = 9;
					CHJob = 1;
					break;
				case SKID_SN_SHARPSHOOTING:
					goto $LN134;
				case 530:
$LN134:
					v28 = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(0, msg->SKID, 14, msg->level, 0, 0, 0);
					if( this->CPC::IsCritical(v10, v28) )
						goto LABEL_72;
					break;
				case 614:
					IVItEquipItem* v29 = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedItem(2u);
					if( !v29 || (v30 = (unsigned __int8)IVItEquipItem::GetRefiningLevel(v29), (signed int)(unsigned __int8)v30 <= 5) )
						goto LABEL_70;
					v31 = 5 * v30 - 25;
					goto LABEL_71;
				case 615:
				case 616:
				case 618:
					IVItEquipItem* v32 = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedItem(2u);
					if( v32 && (v33 = (unsigned __int8)IVItEquipItem::GetRefiningLevel(v32), (signed int)(unsigned __int8)v33 > 5) )
						v31 = 3 * v33 - 15;
					else
LABEL_70:
					v31 = 0;
LABEL_71:
					if( GetServerRandom(0, 20000) % 100 < v31 )
						goto LABEL_72;
					break;
				default:
					break;
			}

			if( this->GetEffective(EFST_STAR2, 0) )
			{
				int maxhp, hp;
				this->GetParameterValue(6, &maxhp);
				this->GetParameterValue(5, &hp);

				if( hp < maxhp / 5 )
				{
					m_pcClientUpdater.CPCClientUpdater::OnDead(0);
					return 0;
				}

				command.par1 = 0;
				command.par2 = 0;
				command.par3 = 0;
				command.par4 = 0;
				command.par5 = 0;
				command.par6 = 0;
				*(_DWORD *)&command.par7.m_Var.m_RG_STRIPWEAPON.bBlockClientNotify = 0;
				command.commandID = 6;
				command.executionTime = timeGetTime() + 500;
				command.par1 = this->GetAccountID();
				command.par2 = ( v10->GetType() ) ? (signed int)skillTypeInfo / 50 : (signed int)skillTypeInfo / 13;
				v108 = (unsigned int)&command.executionTime;
				command.par3 = 1;
				this->InsertCommand(&command);
				v25 |= 4u;
			}

			damage = this->CPC::GetAttackFinalDamage(v10, 2, skillProperty, plusATTPowerPercent, plusATTSuccessPercent, v25, isRangeAttack, msg->SKID, msg->skLevel);
			if( !this->CPC::GetITPEquipedWeapon() )
			{
				if( msg->SKID == SKID_TK_STORMKICK || msg->SKID == SKID_TK_DOWNKICK || msg->SKID == SKID_TK_TURNKICK || msg->SKID == SKID_TK_COUNTER )
				{
					v42 = m_pcSkill.CPCSkill::GetSkillLevel(SKID_TK_RUN, 0);
					v43 = g_skillTypeInfoMgr->CSkillTypeInfoMgr::SendMsg(&this->baseclass_0.baseclass_0, 411, 8, v42, 0, 0, 0);
					damage += v43;
				}
			}
		}
	}

	maxhp = 0;
	if( damage != -30000 )
	{
		if( targetClass )
		{
			v10->GetParameterValue(90, &isMagicImmune);

			CAttackPlusPowerInfo *target_attackedMT;
			if( g_zoneScript.m_attackPlusPowerInfo )
				g_zoneScript->m_attackPlusPowerInfo.CAttackPlusPowerInfo::GetAttackPlusPowerByProperty(outpacket.AID, targetClass, (int *)&target_attackedMT);
			else
				target_attackedMT = g_zoneScript.m_attackPlusPowerInfo;

			this->ModifyAttackPowerByEffective(v10, targetClass, target_attackedMT);
		}

		if( skillTypeInfo )
		{
			if ( skillPattern == 1 )
				m_pcBattle.CPCBattle::ModifyDamage_ATK(v10, &damage, isRangeAttack, 1, 0);
			else
			if( skillPattern == 2 )
				m_pcBattle.CPCBattle::ModifyDamage_MATK(v10, &damage);
		}

		if( damage <= 0 )
		{
			if( !chType )
				goto LABEL_135;
		}
		else
		{
			targetClass = 22;
			v10->GetParameterValue(92, &targetClass);
			if( targetClass )
			{
				damage *= 2;
				v10->UpdateParameterValue(91, 22);
			}
			if( chType == 0 || chType == 9 )
			{
				if( v10->GetEffective(19, 0) > 0 )
				{
					v51 = v10->GetEffective(49, 0) - isRangeAttack;
					v10->UpdateEffective(19, -1, 0);
					v10->UpdateEffective(49, -isRangeAttack, 0);
					if( isMagicImmune != 2 )
					{
						if( *(_WORD *)(plusATTSuccessPercent + 4) == 367 )
						{
							isRangeAttack /= 2;
						}
						else
						{
							if ( v51 < 0 )
								isRangeAttack = -v51;
							else
								isRangeAttack = 0;
						}
					}

					if( v10->GetEffective(19, 0) == 1
					||  v10->GetEffective(49, 0) <= 0
					||  msg->SKID == 156 || msg->SKID == 367 )
					{
						v10->ResetEffective(19, 0);
						v10->ResetEffective(49, 0);
					}
				}
			}

			if ( !chType )
			{
				if( v10->CPC::Act_EFST_KAUPE() == 1 )
					damage = 0;
				if( v10->CPC::Act_EFST_DWARNING(&this->baseclass_0.baseclass_0) == 1 )
					damage = 0;
				if( v10->CPC::Act_EFST_DBLOCK(&this->baseclass_0.baseclass_0, isRangeAttack) == 1 )
					damage = 0;
LABEL_135:
				CPCBattle::ModifyDamage_ATKED((CPCBattle *)&v10[15].m_mapRes, &this->baseclass_0.baseclass_0, &damage, isRangeAttack, skillPattern, skillProperty, msg->SKID, CHJob);
				if ( skillPattern != 2 )
				{
					if ( isRangeAttack )
					{
						if( !g_characterMgr->CCharacterMgr::GetSkill(25, desXPos, desYPos, m_mapRes) )
							goto LABEL_142;
						if ( msg->SKID == 367 )
						{
							damage /= 3;
							goto LABEL_142;
						}
					}
					else
					{
						CCharacter* v57 = (CCharacter *)g_characterMgr->CCharacterMgr::GetSkill(12, desXPos, desYPos, m_mapRes);
						if( !v57 || !skillTypeInfo || *(_BYTE *)(skillTypeInfo + 168) & 0x40 )
							goto LABEL_142;
						g_characterMgr->CCharacterMgr::SendMsg(&this->baseclass_0.baseclass_0, v57, 0x8Du, 0, 0, 0, 0);
					}
					damage = 0;
				}
LABEL_142:
				v10->GetParameterValue(155, &isMagicImmune);
				if( isMagicImmune && skillTypeInfo && skillPattern == 2 )
					damage = 0;
				CHJob = v10->GetAccountID();
				v10->CPC::ModifyDamage(&this->baseclass_0.baseclass_0, &damage, isRangeAttack, skillPattern, (unsigned int *)&CHJob, msg->SKID, msg->level);
				if( CHJob != v10->GetAccountID() )
				{
					CCharacter* v61 = g_characterMgr->CCharacterMgr::FindCharacter(CHJob, UNKNOWN_TYPE);
					if( v61 )
					{
						maxhp = 1;
						chType = v61->GetType();
					}
				}
				goto LABEL_162;
			}
		}

		if( chType != 5 )
			goto LABEL_162;

		if( skillPattern != 2 )
		{
			if ( !isRangeAttack )
			{
				CCharacter* v65 = (CCharacter *)g_characterMgr->CCharacterMgr::GetSkill(12, desXPos, desYPos, m_mapRes);
				if( !v65 || !skillTypeInfo || *(_BYTE *)(skillTypeInfo + 168) & 0x40 )
					goto LABEL_161;
				g_characterMgr->CCharacterMgr::SendMsg(&this->baseclass_0.baseclass_0, v65, 0x8Du, 0, 0, 0, 0);
				goto LABEL_160;
			}
			v10->CNPC::SetRangedAttacked(1, m_characterInfo.accountID);
			if( g_characterMgr->CCharacterMgr::GetSkill(25, desXPos, desYPos, m_mapRes) )
			{
LABEL_160:
				damage = 0;
				goto LABEL_161;
			}
		}
LABEL_161:
		v10->CNPC::ModifyDamage(&damage, isRangeAttack, skillPattern, &this->baseclass_0.baseclass_0, msg->SKID);
	}

LABEL_162:
	v66 = damage;
	outpacket.damage = damage;
	outpacket.count = msg->count;
	if ( damage <= 0 )
		goto LABEL_194;

	v10->GetParameterValue(19, &CHJob);
	v68 = chType;
	targetClass = 0;
	if ( chType != 5 )
	{
		if ( chType != 0 )
			goto LABEL_187;

		if( v10->CPC::GetCategorySecondJob() == JT_ROGUE )
		{
			if( v10->GetEffective(EFST_REPRODUCE, 0) <= 0 )
			{
				v69 = CPCSkill::GetSkillLevel((CPCSkill *)&v10[13].baseclass_0.m_asyncStream, SKID_RG_PLAGIARISM, 0);
				if ( (signed __int16)v69 < 1 )
					goto LABEL_185;

				v70 = msg->skLevel;
				if ( v69 < v70 )
					v70 = v69;

				g_characterMgr->CCharacterMgr::SendMsg(0, v10, CM_SKILL_ADDIMITATION, msg->SKID, v70, 0, 0);
			}
			else
			{
				g_characterMgr->CCharacterMgr::SendMsg(0, v10, CM_SKILL_ADDIMITATION3rd, msg->SKID, msg->skLevel, 2285, 0);
			}			
		}

LABEL_185:
		if ( targetClass == 4 )
			goto LABEL_186;
LABEL_187:
		if( !this->IsItPossible(10) || v68 )
		{
			v72 = m_mapRes.CMapRes::GetSkillDamagePercent(outpacket.SKID);
			if ( v72 != 100 )
				outpacket.damage = outpacket.damage * v72 / 100;
		}
		else
		{
			v71 = (signed int)((unsigned __int64)(82463372100i64 * outpacket.damage) >> 32) >> 5;
			outpacket.damage = v71 + ((unsigned int)v71 >> 31);
		}
		goto LABEL_192;
	}
	if ( HIWORD(v10[3].m_charBuff2.m_heal.sp_modifyPercent) == 100 )
	{
LABEL_167:
		outpacket.damage = 1;
		goto LABEL_168;
	}
	if ( HIWORD(v10[3].m_charBuff2.m_heal.sp_modifyPercent) == 128 )
	{
		this->CPC::KnuckBack(v10, 3, 100, 1);
		goto LABEL_167;
	}
LABEL_168:
	if( CHJob == JT_EMPELIUM )
	{
		if ( outpacket.SKID != 263 || g_ZGuildMgr->CZGuildMgr::GetGuildSkillLevel(m_characterInfo.GuildID, SKID_GD_APPROVAL) > 0 )
			v10->GetParameterValue(143, &target_attackedMT);
		else
			outpacket.damage = 0;
	}

	v10->GetParameterValue(125, &targetClass);
	if( targetClass != 4 )
		goto LABEL_187;
	if( outpacket.SKID == 263 )
		goto LABEL_192;
	outpacket.damage = 0;

LABEL_186:
	if ( outpacket.SKID != 263 )
		goto LABEL_187;
LABEL_192:
	v73 = m_pcBattle.CPCBattle::GetDamagePercent_SKID(msg->SKID, 1);
	v66 = outpacket.damage;
	v67 = outpacket.count;

	if( v73 )
	{
		v74 = outpacket.damage * v73 / 100;
		v66 = v74 + outpacket.damage;
		outpacket.damage += v74;
	}

LABEL_194:
	if( v67 > 1 )
	{
		if( msg->isDivide )
		{
			target_attackedMT = (CAttackPlusPowerInfo *)v67;
			v66 /= v67;
		}
		v66 *= v67;
		outpacket.damage = v66;
		outpacket.action = 8;
	}

	if( v66 > 0 && skillTypeInfo != NULL && && skillTypeInfo->m_pattern == 1 )
	{
		this->CPC::DrainDamage(v66);
		if( !isRangeAttack )
		{
			if( !chType )
			{
				int v76 = outpacket.damage * v10->GetEffective(EFST_REFLECTSHIELD, 0) / 100;
				if( v76 > 0 )
					this->CPC::NotifySkillAction(v10, &this->baseclass_0.baseclass_0, &this->baseclass_0.baseclass_0, v76, 1, 1, 0xFCu);
		}
	}

	if( !v10->IsDamageMotionPossible() )
		outpacket.action = (((outpacket.action != 8) - 1) & 5) + 4;

	v80 = outpacket.damage;
	v78 = outpacket.damage < 0;
	if ( outpacket.damage > 0 )
	{
		if ( skillPattern == 2 )
		{
			if( v10->GetEffective(EFST_KAITE, 0) )
			{
				v10->OnShowEffect(438);
				if( v10->GetEffective(EFST_SOULLINK, 0) != 9
				|| (*(_WORD *)(par4 + 4) != 89
				|| this->GetEffective(EFST_KAITE, 0) < 2
				|| this->CPC::GetItemCount(0x1C99u) < 1u)
				&& !this->CPC::ConsumeItem(0x1C99u, 1, 0) )
				{
					*(_DWORD *)&outpacket.action = v10->CPC::GetAttackMotionTime();

					isMagicImmune = 0;
					this->GetParameterValue(39, &isMagicImmune);

					maxhp = isMagicImmune;
					outpacket.damage = m_characterInfo.accountID;
					outpacket.attackedMT = *(_DWORD *)par4;
					g_characterMgr->CCharacterMgr::SendMsg(0, &this->baseclass_0.baseclass_0, 0xB6u, 33, (int)&outpacket.attackMT, 0, 0);
					command.par5 = 0;
					command.par6 = 0;
					*(_DWORD *)&command.par7.m_Var.m_RG_STRIPWEAPON.bBlockClientNotify = 0;
					v127 = 0;
					state = 0;
					effectState = 0;
					v130 = 0;
					command.par2 = 6;
					command.par3 = *(_DWORD *)&outpacket.action + timeGetTime();
					command.par5 = skillTypeInfo;
					command.par4 = v10->GetType();
					command.par6 = SHIWORD(desYPos);
					this->InsertCommand(&command.par2);
				}

				v90 = v10->GetEffective(153, 0);
				v93 = __SETO__(v90, 1);
				v91 = v90 == 1;
				v92 = v90 - 1 < 0;

				if ( (unsigned __int8)(v92 ^ v93) | v91 )
				{
					v10->ResetEffective(153, 0);
				}
				else
				{
					v10->UpdateEffective(153, -1, 0);
				}
				return 0;
			}
			v80 = outpacket.damage;
		}
		v78 = v80 < 0;
	}

	if ( !(v78 ^ 0) || v80 == -30000 )
	{
		if ( skillTypeInfo && *((_DWORD *)skillTypeInfo + 44) == 2 )
		{
			if ( !chType
				&& *((_DWORD *)skillTypeInfo + 46) != 2
				&& CPCBattle::ReflectMagic((CPCBattle *)&v10[15].m_mapRes, &this->baseclass_0.baseclass_0, msg, v80) )
				return 0;
			int v96 = v10->GetEffective(283, 0);
			if( v96 > 0 )
			{
				if ( v96 > GetServerRandom(0, 20000) % 100 && outpacket.damage > 0 )
				{
					this->CPC::NotifySkillAction(v10, v10, &this->baseclass_0.baseclass_0, outpacket.damage, msg->count, -1, outpacket.SKID);
					return 0;
				}
			}
		}

		outpacket.attackMT = this->CPC::GetAttackMotionTime();

		int target_attackedMT = 0;
		v10->GetParameterValue(39, &target_attackedMT);
		outpacket.attackedMT = (int)target_attackedMT;

		if( outpacket.SKID == 369 )
		{
			this->CPC::NotifyAttackAction(&this->baseclass_0.baseclass_0, v10, v10, outpacket.damage, 0);
			v10->OnShowEffect(245);
		}
		else
		{
			g_characterMgr->CCharacterMgr::SendMsg(0, &this->baseclass_0.baseclass_0, 0xB6u, 33, (int)&outpacket, 0, 0);
		}

		if ( maxhp )
		{
			outpacket.level = -1;
			outpacket.SKID = 0;
			outpacket.attackMT = 0;
			outpacket.AID = v10->GetAccountID();
			outpacket.targetID = v10->GetAccountID();
			g_characterMgr->CCharacterMgr::SendMsg(0, &this->baseclass_0.baseclass_0, 0xB6u, 33, (int)&outpacket, 0, 0);
		}

		v80 = outpacket.damage;
	}

	if ( v80 <= 0 )
		return 0;

	if( msg->SKID == SKID_MB_B_GAIN )
		this->CPC::NotifyRecoveryValue2(5, 30 * outpacket.damage * (msg->skLevel + 3) / 100, this->CPC::GetMaxHP());

	command.par1 = 0;
	command.par2 = 0;
	command.par3 = 0;
	command.par4 = 0;
	command.par5 = 0;
	command.par6 = 0;
	*(_DWORD *)&command.par7.m_Var.m_RG_STRIPWEAPON.bBlockClientNotify = 0;
	if ( msg->count == 1 )
		command.commandID = 6;
	else
	if( msg->count >= 2 )
		command.commandID = 38;

	command.executionTime = ( msg->srcAID ) ? timeGetTime() : timeGetTime() + this->CPC::GetAttackMotionTime() + 10;
	command.sender = m_characterInfo.accountID;
	command.par1 = outpacket.damage;
	command.par2 = msg->count;
	command.par3 |= 1u;
	if( skillPattern == 2 )
		command.par3 |= 2u;
	command.par4 = ( isRangeAttack == 0 );
	command.par5 = msg->SKID;
	command.par6 = skillProperty;
	v10->InsertCommand(&command);
	msg->finalDamage = outpacket.damage;
*/
	return 1;
}


hook_method<short (CPC::*)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count)> CPC::_SplashAttack(SERVER, "CPC::SplashAttack");
short CPC::SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count) // line 38 (PCSplashAttack.cpp)
{
	return (this->*_SplashAttack)(val1, xPos, yPos, type, range, rangeIn, exceptAID, msgDataPtr, val2, count);

	//TODO
}


hook_method<int (CPC::*)(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc)> CPC::_SplashAttack2(SERVER, "CPC::SplashAttack2");
int CPC::SplashAttack2(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc)
{
	return (this->*_SplashAttack2)(plusATTPower, dest, type, halfWidth, height, msgData, count, plusHitPercent, specialSrc);

	//TODO
}


hook_method<void (CPC::*)(int plusATTPower, PosInfo dest, int type, MSG_TYPE1_TWODWORD* msgData, int range, int count)> CPC::_SplashAttack3(SERVER, "CPC::SplashAttack3");
void CPC::SplashAttack3(int plusATTPower, PosInfo dest, int type, MSG_TYPE1_TWODWORD* msgData, int range, int count)
{
	return (this->*_SplashAttack3)(plusATTPower, dest, type, msgData, range, count);

	//TODO
}


hook_method<void (CPC::*)(int plusATTPower, CCharacter* src, CCharacter* other, int destDir, int type, unsigned short SKID, int count, mystd::map<CCharacter *,CollideInfo>& collidedList)> CPC::_CollideSplashAttack(SERVER, "CPC::CollideSplashAttack");
void CPC::CollideSplashAttack(int plusATTPower, CCharacter* src, CCharacter* other, int destDir, int type, unsigned short SKID, int count, mystd::map<CCharacter *,CollideInfo>& collidedList)
{
	return (this->*_CollideSplashAttack)(plusATTPower, src, other, destDir, type, SKID, count, collidedList);

	if( m_mapRes == NULL )
		return;

	PosInfo srcPos, destPos;
	src->GetParameterValue(VAR_CURXPOS, srcPos.x);
	src->GetParameterValue(VAR_CURYPOS, srcPos.y);
	other->GetParameterValue(VAR_CURXPOS, destPos.x);
	other->GetParameterValue(VAR_CURYPOS, destPos.y);

	int distCell = (count + 1) / 2;
	NEIGHBORHOOD_SECTION result = {};
	m_mapRes->CMapRes::GetNeighborhoodSections(srcPos.x, srcPos.y, distCell, &result);

	int firstSectionPos;
	for( firstSectionPos = 0; firstSectionPos < countof(result.section); ++firstSectionPos )
		if( result.section[firstSectionPos] != NULL )
			break;
	mystd::vector<CCharacter*>* section = result.section[firstSectionPos];

	int deltaX = g_backpedalTable[destDir][0];
	int deltaY = g_backpedalTable[destDir][1];
	
	int isLoopExit = 0;
	for( int i = 0; i < distCell; ++i )
	{
		destPos.x += deltaX;
		destPos.y += deltaY;

		if( !m_mapRes->CMapRes::IsMovableCell(destPos.x, destPos.y) )
		{
			destPos.x -= deltaX;
			destPos.y -= deltaY;
			break; // collision with wall.
		}

		mystd::vector<CCharacter*> neisection = *section; // copy
		// scan neighbouring cells in current section for objects to collide with and cause recursive knockback
		for( mystd::vector<CCharacter*>::const_iterator iter = neisection.begin(); iter != neisection.end(); ++iter )
		{
			CCharacter* ch = *iter;
			
			if( ch == this )
				continue;

			if( src == other )
				continue;
			
			if( ch->IsTarget(this, 0) == 0 )
				continue;

			PosInfo otherPos;
			ch->GetParameterValue(VAR_CURXPOS, otherPos.x);
			ch->GetParameterValue(VAR_CURYPOS, otherPos.y);

			if( abs(destPos.x - otherPos.x) > 1 || abs(destPos.y - otherPos.y) > 1 )
				continue;

			mystd::map<CCharacter*,CollideInfo>::iterator itList = collidedList.find(ch);
			if( itList == collidedList.end() )
			{
				CollideInfo& info = collidedList[ch];
				info.sectionList = section;
				info.count = 1;
				Trace("AID: %d, CollideCount: %d\n", ch->GetAccountID(), info.count);
			}
			else
			{
				CollideInfo& info = itList->second;
				if( info.count >= 2 )
				{
					Trace("AID: Done!\n");
					continue;
				}
				info.count = info.count + 1;
				info.sectionList = section;
				Trace("AID: %d, CollideCount: %d\n", ch->GetAccountID(), info.count);
			}

			g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_KNOCKBACK, destPos.x, destPos.y, 0, 0);
			this->CPC::CollideSplashAttack(plusATTPower, other, ch, GetServerRandom(0, 20000) % 8, type, SKID, count - 1, collidedList);

			isLoopExit = 1;
		}// neisection

		if( isLoopExit )
			break;

	}// distCell

	SKILLATTACK_MSG msg;
	msg.SKID = SKID;
	msg.targetAID = other->GetAccountID();
	msg.actionType = 5;
	msg.level = m_pcSkill.CPCSkill::GetSkillLevel(SKID, 0);
	msg.skLevel = msg.level;
	msg.xPos = static_cast<short>(destPos.x);
	msg.yPos = static_cast<short>(destPos.y);
	msg.count = 1;

	if( this->SkillAttack(&msg, plusATTPower, 100, false) )
		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_KNOCKBACK, msg.xPos, msg.yPos, 0, 0);
}


hook_method<int (CPC::*)(int weaponLevel, int refiningLevel)> CPC::_AddRandomAttackPower(SERVER, "CPC::AddRandomAttackPower");
int CPC::AddRandomAttackPower(int weaponLevel, int refiningLevel)
{
	return (this->*_AddRandomAttackPower)(weaponLevel, refiningLevel);

	//TODO
}


hook_method<void (CPC::*)(int AID, int par1, int bisSectionMove)> CPC::_OnTouchedSkillObject(SERVER, "CPC::OnTouchedSkillObject");
void CPC::OnTouchedSkillObject(int AID, int par1, int bisSectionMove)
{
	return (this->*_OnTouchedSkillObject)(AID, par1, bisSectionMove);

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnHealHP(SERVER, "CPC::OnHealHP");
void CPC::OnHealHP(int par1) // line ???
{
	return (this->*_OnHealHP)(par1);

	//TODO
}


hook_method<void (CPC::*)(int SKID, int par2, int par3)> CPC::_OnGroundSkill(SERVER, "CPC::OnGroundSkill");
void CPC::OnGroundSkill(int SKID, int par2, int par3)
{
	return (this->*_OnGroundSkill)(SKID, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnTeleportCharacter(SERVER, "CPC::OnTeleportCharacter");
void CPC::OnTeleportCharacter(int par1, int par2, int par3)
{
	return (this->*_OnTeleportCharacter)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnWarpCharacter(SERVER, "CPC::OnWarpCharacter");
void CPC::OnWarpCharacter(int par1, int par2, int par3)
{
	return (this->*_OnWarpCharacter)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnWarpPositionRemember(SERVER, "CPC::OnWarpPositionRemember");
void CPC::OnWarpPositionRemember(int par1, int par2, int par3)
{
	return (this->*_OnWarpPositionRemember)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnStarPlaceRemember(SERVER, "CPC::OnStarPlaceRemember");
void CPC::OnStarPlaceRemember(int par1, int par2, int par3)
{
	return (this->*_OnStarPlaceRemember)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* sender, int par1, int par2, int par3)> CPC::_OnBlessingFromAcolyte(SERVER, "CPC::OnBlessingFromAcolyte");
void CPC::OnBlessingFromAcolyte(CCharacter* sender, int par1, int par2, int par3)
{
	return (this->*_OnBlessingFromAcolyte)(sender, par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnPlusAttRangeOnVulture(SERVER, "CPC::OnPlusAttRangeOnVulture");
void CPC::OnPlusAttRangeOnVulture(int par1, int par2, int par3)
{
	return (this->*_OnPlusAttRangeOnVulture)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int amount)> CPC::_OnIncCarry(SERVER, "CPC::OnIncCarry");
void CPC::OnIncCarry(int amount)
{
	return (this->*_OnIncCarry)(amount);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnIncCarry2(SERVER, "CPC::OnIncCarry2");
void CPC::OnIncCarry2(int par1, int par2, int par3)
{
	return (this->*_OnIncCarry2)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnSgDevil(SERVER, "CPC::OnSgDevil");
void CPC::OnSgDevil(int par1, int par2, int par3)
{
	return (this->*_OnSgDevil)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnSgFriend(SERVER, "CPC::OnSgFriend");
void CPC::OnSgFriend(int par1, int par2, int par3)
{
	return (this->*_OnSgFriend)(par1, par2, par3);

	//TODO
}


/// Called when player uses Vending.
hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnVending(SERVER, "CPC::OnVending");
void CPC::OnVending(int par1, int par2, int par3)
{
	return (this->*_OnVending)(par1, par2, par3);
	/*
	if( this->CPC::GetLockCounter() > 0 )
		return;

	if( m_characterInfo.roomID != 0 )
		return;

	this->CPC::ModifyLockCounter(+1);

	this->UpdateParameterValue(7, -*(_DWORD *)(par3 + 4));

	PACKET_ZC_OPENSTORE outpacket;
	outpacket.PacketType = HEADER_ZC_OPENSTORE;
	outpacket.itemcount = *(_WORD *)par3;
	this->CPC::Send(sizeof(outpacket), (char *)&outpacket);
	*/
}


hook_method<void (CPC::*)(int par1, const int in_CauseSKID)> CPC::_OnResurrection(SERVER, "CPC::OnResurrection");
void CPC::OnResurrection(int par1, const int in_CauseSKID)
{
	return (this->*_OnResurrection)(par1, in_CauseSKID);

	//TODO
}


hook_method<void (CPC::*)(int xPos, int yPos, int par3)> CPC::_OnMoveStop(SERVER, "CPC::OnMoveStop");
void CPC::OnMoveStop(int xPos, int yPos, int par3)
{
	return (this->*_OnMoveStop)(xPos, yPos, par3);

	//TODO
}


int CPC::IsAttackableRange(int xPos, int yPos)
{
	double distance = this->CPC::GetAttackDistance() + 2.0;
	int dx = m_pathInfo.m_moveInfo.xPos - xPos;
	int dy = m_pathInfo.m_moveInfo.yPos - yPos;

	return ( sqrt(double(dx * dx + dy * dy)) <= distance );
}


hook_method<void (CPC::*)(int par1)> CPC::_OnGroupInfoChange(SERVER, "CPC::OnGroupInfoChange");
void CPC::OnGroupInfoChange(int par1)
{
	return (this->*_OnGroupInfoChange)(par1);

	m_characterInfo.GroupExpOption = par1;
	if( !par1 )
		m_familyInfo.expOption = 0;

	PACKET_ZC_GROUPINFO_CHANGE outpacket;
	outpacket.PacketType = HEADER_ZC_GROUPINFO_CHANGE;
	outpacket.expOption = par1;
	this->CPC::ForceSend(sizeof(outpacket), (char *)&outpacket);
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_ReqGroupInfoChangeV2(SERVER, "CPC::ReqGroupInfoChangeV2");
void CPC::ReqGroupInfoChangeV2(int par1, int par2)
{
	return (this->*_ReqGroupInfoChangeV2)(par1, par2);

	PACKET_IZ_REQ_GROUPINFO_CHANGE_V2& packet = *(PACKET_IZ_REQ_GROUPINFO_CHANGE_V2*)par2;

	m_characterInfo.GroupExpOption = packet.expOption;
	m_characterInfo.PartyItemPickupRule = packet.ItemPickupRule;
	m_characterInfo.PartyItemDivisionRule = packet.ItemDivisionRule;

	PACKET_ZC_REQ_GROUPINFO_CHANGE_V2 outpacket;
	outpacket.PacketType = HEADER_ZC_REQ_GROUPINFO_CHANGE_V2;
	outpacket.expOption = packet.expOption;
	outpacket.ItemPickupRule = packet.ItemPickupRule;
	outpacket.ItemDivisionRule = packet.ItemDivisionRule;
	this->CPC::Send(sizeof(outpacket), (char *)&outpacket);
}


hook_method<void (CPC::*)(int par1)> CPC::_OnDlgWrite(SERVER, "CPC::OnDlgWrite");
void CPC::OnDlgWrite(int par1)
{
	return (this->*_OnDlgWrite)(par1);

	//TODO
}


hook_method<void (CPC::*)(int npcID)> CPC::_OnDlgWriteStr(SERVER, "CPC::OnDlgWriteStr");
void CPC::OnDlgWriteStr(int npcID)
{
	return (this->*_OnDlgWriteStr)(npcID);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2)> CPC::_OnHealByPercent(SERVER, "CPC::OnHealByPercent");
void CPC::OnHealByPercent(int par1, int par2)
{
	return (this->*_OnHealByPercent)(par1, par2);

	//TODO
}


hook_method<void (CPC::*)(int NAID, int type, int msg)> CPC::_OnCompass(SERVER, "CPC::OnCompass");
void CPC::OnCompass(int NAID, int type, int msg)
{
	return (this->*_OnCompass)(NAID, type, msg);

	//TODO
}


hook_method<void (CPC::*)(int type, int imageName)> CPC::_OnShowImage(SERVER, "CPC::OnShowImage");
void CPC::OnShowImage(int type, int imageName)
{
	return (this->*_OnShowImage)(type, imageName);

	//TODO
}


hook_method<void (CPC::*)(int where, int palattetype)> CPC::_OnChangePalette(SERVER, "CPC::OnChangePalette");
void CPC::OnChangePalette(int where, int palattetype)
{
	return (this->*_OnChangePalette)(where, palattetype);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnChangeAGI(SERVER, "CPC::OnChangeAGI");
void CPC::OnChangeAGI(int par1, int par2, int par3) // line ???
{
	return (this->*_OnChangeAGI)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnChangeDEX(SERVER, "CPC::OnChangeDEX");
void CPC::OnChangeDEX(int par1, int par2, int par3) // line ???
{
	return (this->*_OnChangeDEX)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnChangeINT(SERVER, "CPC::OnChangeINT");
void CPC::OnChangeINT(int par1, int par2, int par3) // line ???
{
	return (this->*_OnChangeINT)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnChangeLUK(SERVER, "CPC::OnChangeLUK");
void CPC::OnChangeLUK(int par1, int par2, int par3)
{
	return (this->*_OnChangeLUK)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnChangeSTR(SERVER, "CPC::OnChangeSTR");
void CPC::OnChangeSTR(int par1, int par2, int par3)
{
	return (this->*_OnChangeSTR)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnChangeVIT(SERVER, "CPC::OnChangeVIT");
void CPC::OnChangeVIT(int par1, int par2, int par3)
{
	return (this->*_OnChangeVIT)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnCureFromAcolyte(SERVER, "CPC::OnCureFromAcolyte");
void CPC::OnCureFromAcolyte(void)
{
	return (this->*_OnCureFromAcolyte)();

	//TODO
}


hook_method<void (CPC::*)(int par1)> CPC::_OnNotifyItemInfoInMCStore(SERVER, "CPC::OnNotifyItemInfoInMCStore");
void CPC::OnNotifyItemInfoInMCStore(int par1)
{
	return (this->*_OnNotifyItemInfoInMCStore)(par1);

	//TODO
}


hook_method<IVItItem* (CPC::*)(int ID, int type, int par, int Hour, bool isUniqueIdentityNumV2)> CPC::_OnAddItem(SERVER, "CPC::OnAddItem");
IVItItem* CPC::OnAddItem(int ID, int type, int par, int Hour, bool isUniqueIdentityNumV2)
{
	return (this->*_OnAddItem)(ID, type, par, Hour, isUniqueIdentityNumV2);

	IVItItem item;
	item.m_ID = ID;

	if( type == 0 || type == 4 || type == 5 || type == 6 )
	{
		CITP* itp = g_itpMgr->CITPMgr::GetITP(ID);
		if( itp != NULL && !itp->IsApparel() )
			item.m_isIdentified = true;
		item.m_count = par;
		item.IVItItem::SetHireExpireDate(Hour);
	}
	else
	if( type == 3 || type == 7 )
	{
		item.m_isIdentified = true;
		item.m_count = par;
	}
	else
	{
		item.m_count = 1;
	}

	if( Hour != 0 )
		item.IVItItem::SetHireExpireDate(time(NULL) + 3600 * Hour);

	if( isUniqueIdentityNumV2 )
		item.IVItItem::SetUniqueIdentityNumV2(CUIDGenerator::GetObj()->CUIDGenerator::Get());

	IVItItem* pitem = m_pcitemInventoryMgr.CPCItemInventoryMgr::Add(&item, 0, 0, 0, 0);
	if( pitem == NULL )
		return NULL;

	IVItItem* retItem;
	switch( type )
	{
	case 1:
	{
		retItem = pitem;
		pitem->m_isIdentified = true;

		if( pitem->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
		{
			uint8_t element = 0;
			uint8_t plusAttackPower = 0;

			WORD* slot = (WORD*)(par + 2);
			for( int i = 0; i < 3; ++i )
			{
				switch( slot[i] )
				{
				case 994: element = 3; break; // Flame_Heart
				case 995: element = 1; break; // Mistic_Frozen
				case 996: element = 4; break; // Rough_Wind
				case 997: element = 2; break; // Great_Nature
				case 1000: plusAttackPower += 5; break; // Star_Crumb
				default: break;
				}
			}

			pitem->m_slotInfo.info[0] = 255;
			pitem->m_slotInfo.info[1] = element | (plusAttackPower << 8);
			pitem->m_slotInfo.info[2] = BYTE(m_characterInfo.characterID >> 0);
			pitem->m_slotInfo.info[3] = BYTE(m_characterInfo.characterID >> 8);

			CITP* itp = g_itpMgr->CITPMgr::GetITP(ID);
			if( itp != NULL && itp->GetItemLevel() == 3 )
				if( plusAttackPower == 15 || plusAttackPower >= 10 && element != 0 )
					g_makerRankMgr->CMakerRankMgr::UpdateMakerRank(this, 0, 5, m_makerRankPoint);
		}
	}
	break;
	case 2:
		retItem = pitem;
		pitem->m_isIdentified = true;
		pitem->IVItItem::SetUniqueIdentityNumV2(par);
		((IVItEquipItem*)pitem)->m_isDamaged = false;
		pitem->m_slotInfo.info[3] = 0;
	break;
	case 3:
		retItem = pitem;
	break;
	default:
		retItem = &item; //FIXME: returning address of temporary variable
	break;
	}

	m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyAckAddItemToBody(0, retItem);
	m_pcitemInventoryMgr.CPCItemInventoryMgr::RefreshItemWeight();

	int logType;
	switch( type )
	{
	case 4 : logType = 13; break;
	case 5 : logType = 14; break;
	case 1 : logType = 15; break;
	case 6 : logType = 8; break;
	case 7 : logType = 36; break;
	default: logType = 9; break;
	}

	g_itemLog->CItemLog::AddItemLog(logType, this, NULL, pitem, 0, pitem->m_count, NULL);
	return retItem;
}


hook_method<void (CPC::*)(void)> CPC::_OnAddReservedEmpeliumItem(SERVER, "CPC::OnAddReservedEmpeliumItem");
void CPC::OnAddReservedEmpeliumItem(void)
{
	return (this->*_OnAddReservedEmpeliumItem)();

	//TODO
}


hook_method<void (CPC::*)(CCharacter* sender, int type, int point)> CPC::_OnNotifyMannerPointGiven(SERVER, "CPC::OnNotifyMannerPointGiven");
void CPC::OnNotifyMannerPointGiven(CCharacter* sender, int type, int point)
{
	return (this->*_OnNotifyMannerPointGiven)(sender, type, point);

	//TODO
}


hook_method<void (CPC::*)(int par1, int par2, int par3)> CPC::_OnItemIdentifySkill(SERVER, "CPC::OnItemIdentifySkill");
void CPC::OnItemIdentifySkill(int par1, int par2, int par3)
{
	return (this->*_OnItemIdentifySkill)(par1, par2, par3);

	//TODO
}


hook_method<void (CPC::*)(int loc)> CPC::_OnSuccessOfItemRef(SERVER, "CPC::OnSuccessOfItemRef");
void CPC::OnSuccessOfItemRef(int loc)
{
	return (this->*_OnSuccessOfItemRef)(loc);

	//TODO
}


hook_method<void (CPC::*)(int loc)> CPC::_OnFailureOfItemRef(SERVER, "CPC::OnFailureOfItemRef");
void CPC::OnFailureOfItemRef(int loc)
{
	return (this->*_OnFailureOfItemRef)(loc);

	//TODO
}


hook_method<void (CPC::*)(unsigned long var)> CPC::_OnStandardStatChange(SERVER, "CPC::OnStandardStatChange");
void CPC::OnStandardStatChange(unsigned long var)
{
	return (this->*_OnStandardStatChange)(var);

	//TODO
}


hook_method<void (CPC::*)(int point)> CPC::_OnPVPPlusPoint(SERVER, "CPC::OnPVPPlusPoint");
void CPC::OnPVPPlusPoint(int point)
{
	return (this->*_OnPVPPlusPoint)(point);

	//TODO
}


hook_method<void (CPC::*)(int ranking, int total)> CPC::_OnNotifyRankingInfo(SERVER, "CPC::OnNotifyRankingInfo");
void CPC::OnNotifyRankingInfo(int ranking, int total)
{
	return (this->*_OnNotifyRankingInfo)(ranking, total);

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetCurrentState(SERVER, "CPC::GetCurrentState");
short CPC::GetCurrentState(void)
{
	return (this->*_GetCurrentState)();

	//TODO
}


hook_method<void (CPC::*)(short state)> CPC::_SetBodyState(SERVER, "CPC::SetBodyState");
void CPC::SetBodyState(short state)
{
	return (this->*_SetBodyState)(state);

	if( state - 1 <= 1 ) // NOTE: BODYSTATE_STONECURSE or BODYSTATE_FREEZING
		this->ResetEffective(EFST_LEXAETERNA, 0);

	if( this->GetEffective(EFST_BDPLAYING, 0) && (state == BODYSTATE_STONECURSE || state == BODYSTATE_FREEZING || state == BODYSTATE_STUN) )
	{
		this->OnMsg(NULL, this, CM_PLAYSKILL_CANCEL, 0, 0, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(NULL, m_pcSkill.m_partnerAID, CM_PLAYSKILL_CANCEL, 0, 0, 0, 0);
	}

	m_characterPInfo.bodyState = state;
	this->CPC::MultiCastStateInfo();
}


hook_method<void (CPC::*)(short state)> CPC::_SetHealthState(SERVER, "CPC::SetHealthState");
void CPC::SetHealthState(short state)
{
	return (this->*_SetHealthState)(state);

	//TODO
}


hook_method<void (CPC::*)(short state)> CPC::_SetCurrentState(SERVER, "CPC::SetCurrentState");
void CPC::SetCurrentState(short state)
{
	return (this->*_SetCurrentState)(state);

	//TODO
}


hook_method<void (CPC::*)(unsigned long AID)> CPC::_AddGroupMember(SERVER, "CPC::AddGroupMember");
void CPC::AddGroupMember(unsigned long AID)
{
	return (this->*_AddGroupMember)(AID);

	//TODO
}


hook_method<void (CPC::*)(unsigned long AID)> CPC::_DeleteGroupMember(SERVER, "CPC::DeleteGroupMember");
void CPC::DeleteGroupMember(unsigned long AID)
{
	return (this->*_DeleteGroupMember)(AID);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_ResetGroupMember(SERVER, "CPC::ResetGroupMember");
void CPC::ResetGroupMember(void) // line 5373
{
	return (this->*_ResetGroupMember)();

	m_characterInfo.isGroupMaster = 0;
	m_characterInfo.GroupID = 0;
	m_groupMember.clear();
}


hook_method<void (CPC::*)(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY)> CPC::_DetectHidingCharacter(SERVER, "CPC::DetectHidingCharacter");
void CPC::DetectHidingCharacter(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY) // line 8188-8400
{
	return (this->*_DetectHidingCharacter)(range, msg, plusAttPower, deltaX, deltaY);

	// TODO
}


hook_method<void (CPC::*)(CCharacter* ch, short dist, int time, short who)> CPC::_KnuckBack(SERVER, "CPC::KnuckBack");
void CPC::KnuckBack(CCharacter* ch, short dist, int time, short who)
{
	return (this->*_KnuckBack)(ch, dist, time, who);

	//TODO
}


hook_method<void (CPC::*)(unsigned short SKID, short level, short xPos, short yPos, unsigned long startTime)> CPC::_NotifyGroundSkillUsing(SERVER, "CPC::NotifyGroundSkillUsing");
void CPC::NotifyGroundSkillUsing(unsigned short SKID, short level, short xPos, short yPos, unsigned long startTime)
{
	return (this->*_NotifyGroundSkillUsing)(SKID, level, xPos, yPos, startTime);

	//TODO
}


hook_method<void (CPC::*)(int xPos, int yPos, int destDir, int distance, PosInfo& result)> CPC::_GetPushedPosition2(SERVER, "CPC::GetPushedPosition2");
void CPC::GetPushedPosition2(int xPos, int yPos, int destDir, int distance, PosInfo& result)
{
	return (this->*_GetPushedPosition2)(xPos, yPos, destDir, distance, result);

	//TODO
}


hook_method<int (CPC::*)(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime)> CPC::_SetHandicapState(SERVER, "CPC::SetHandicapState");
int CPC::SetHandicapState(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime)
{
	return (this->*_SetHandicapState)(state, other, percent, preDelayTime, delayTime, isSpell, isFixedDelayTime);

	int tarClass, tarJob;
	other->GetParameterValue(VAR_CLASS, tarClass);
	other->GetParameterValue(VAR_JOB, tarJob);

	if( tarClass == NPC_CLASS_BOSS || tarClass == NPC_CLASS_GUARDIAN || tarJob == JT_EMPELIUM || tarClass == NPC_CLASS_BATTLEFIELD )
		return 0; // special mobs are immune to handicap states.

	int tarEffectState;
	other->GetParameterValue(VAR_EFFECTSTATE, tarEffectState);
	if( tarEffectState & EFFECTSTATE_SPECIALHIDING )
		return 0;

	if( other->GetState() == CHARACTER_STATE_DEAD )
		return 0;

	int tarLevel, tarSTR, tarVit, tarInt, tarLuk, tarMDEFItem, tarTolerace, bodyState, healthState;
	tarTolerace = state; //NOTE: in/out parameter logic
	other->GetParameterValue(VAR_CLEVEL, tarLevel);
	other->GetParameterValue(VAR_STR, tarSTR);
	other->GetParameterValue(VAR_VIT, tarVit);
	other->GetParameterValue(VAR_INT, tarInt);
	other->GetParameterValue(VAR_LUK, tarLuk);
	other->GetParameterValue(VAR_MAGICITEMDEFPOWER, tarMDEFItem);
	other->GetParameterValue(VAR_TOLERACE, tarTolerace);
	other->GetParameterValue(VAR_BODYSTATE, bodyState);
	other->GetParameterValue(VAR_HEALTHSTATE, healthState);

	int isMagicImmune = 0;
	if( isSpell )
		other->GetParameterValue(VAR_ISMAGICIMMUNE, isMagicImmune);

	switch( state )
	{
	case BODY_STONECURSE:
	{
		if( other->IsRightProperty(PROPERTY_UNDEAD) )
			return 0; // undead are immune to stonecurse.

		if( bodyState == BODYSTATE_STONECURSE_ING || bodyState == BODYSTATE_STONECURSE )
		{// cancel stonecurse
			g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_BODYSTATE, 0, 0, 0, 0);
			return 1;
		}

		if( bodyState != BODYSTATE_NORMAL )
			return 0; // doesn't stack.

		int rate = percent - percent * tarMDEFItem / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;

		if( isMagicImmune || GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = 20000;

		other->UpdateParameterValue(VAR_BODYSTATE, BODYSTATE_STONECURSE_ING);
		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_BODYSTATE, preDelayTime, time, BODYSTATE_STONECURSE, 0);
		return 1;
	}
	break;
	case BODY_FREEZING:
	{
		if( bodyState == BODYSTATE_FREEZING )
			return 0; // already frozen.

		if( bodyState != BODYSTATE_NORMAL )
			return 0; // doesn't stack.
		
		if( other->IsRightProperty(PROPERTY_UNDEAD) )
			return 0; // undead are immune to freezing.

		int rate = percent - percent * tarMDEFItem / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;

		if( isMagicImmune || GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 12000;
		if( time != 9999 )
			time = preDelayTime + time - time * tarMDEFItem / 100 + 10 * this->CPC::GetLukValue();

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_BODYSTATE, preDelayTime, time, BODYSTATE_FREEZING, 0);
		return 1;
	}
	break;
	case BODY_STUN:
	{
		if( bodyState == BODYSTATE_STUN )
			return 0; // already stunned.

		int rate = percent - percent * tarVit / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 5000;
		if( time != 9999 )
			time = preDelayTime + time - time * tarVit / 100 - 10 * tarLuk;

		Trace("BODY_STUN: %d\n", rate);
		Trace("BODY_STUN time: %d\n", time);

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_BODYSTATE, preDelayTime, time, BODYSTATE_STUN, 0);
		return 1;
	}
	break;
	case BODY_SLEEP:
	{
		if( bodyState == BODYSTATE_SLEEP )
			return 0; // already asleep.

		int rate = percent - percent * tarInt / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;

		if( GetServerRandom(0, 20000) % 1000 >= rate && !isFixedDelayTime ) //NOTE: fixed-delay stun never fails
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 30000;
		if( time != 9999 && !isFixedDelayTime )
			time = preDelayTime + time - time * tarInt / 100 - 10 * tarLuk;

		Trace("BODY_SLEEP: %d\n", time);

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_BODYSTATE, preDelayTime, time, BODYSTATE_SLEEP, 0);
		return 1;
	}
	break;
	case HEALTH_POISON:
	{
		if( healthState & (HEALTHSTATE_HEAVYPOISON | HEALTHSTATE_POISON) )
			return 0; // already poisoned.

		int rate = percent - percent * tarVit / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int baseDelay;
		int baseTime;
		if( other->GetType() != PC_TYPE )
		{
			baseDelay = 10000;
			baseTime = 20000 - 20000 * tarVit / 100;
		}
		else
		{
			baseDelay = 5000;
			baseTime = 55000 - 45000 * tarVit / 100 - 10000 * tarLuk / 100;
		}

		int time = delayTime;
		if( time != 9999 )
			time = preDelayTime + baseTime + baseDelay; //NOTE: input delayTime ignored

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, preDelayTime, time, HEALTHSTATE_POISON, 0);
		return 1;
	}
	break;
	case HEALTH_HEAVYPOISON:
	{
		int rate = percent - percent * tarVit / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int baseDelay;
		int baseTime;
		if( other->GetType() != PC_TYPE )
		{
			baseDelay = 10000;
			baseTime = 20000 - 20000 * tarVit / 100;
		}
		else
		{
			baseDelay = 5000;
			baseTime = 55000 - 45000 * tarVit / 100 - 10000 * tarLuk / 100;
		}

		int time = delayTime;
		if( delayTime != 9999 )
			time = preDelayTime + baseTime + baseDelay;

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, preDelayTime, time, HEALTHSTATE_HEAVYPOISON, 0);
		return 1;
	}
	break;
	case HEALTH_BLIND:
	{
		if( healthState & HEALTHSTATE_BLIND )
			return 0; // already blinded.

		int rate = percent - percent * (tarInt + tarVit) / 200 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;
		Trace("HEALTH_BLIND: %d\n", rate);

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 30000;
		if( time != 9999 )
			time = preDelayTime + time - time * (tarInt + tarVit) / 200 - 10 * tarLuk;

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, preDelayTime, time, HEALTHSTATE_BLIND, 0);
		return 1;
	}
	break;
	case HEALTH_SILENCE:
	{
		if( healthState & HEALTHSTATE_SILENCE )
			return 0; // already silenced.

		int rate = percent - percent * tarVit / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;
		Trace("HEALTH_SILENCE: %d\n", rate);

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 30000;
		if( time != 9999 )
			time = preDelayTime + time - time * tarVit / 100 - 10 * tarLuk;

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, preDelayTime, time, HEALTHSTATE_SILENCE, 0);
		return 1;
	}
	break;
	case HEALTH_CURSE:
	{
		if( healthState & HEALTHSTATE_CURSE )
			return 0; // already cursed.
		
		if( tarLuk == 0 )
			return 0; // targets with no luck are immune to curse.

		int rate = percent - percent * tarLuk / 100 + m_characterInfo.clevel - tarLuk; //NOTE: no -tarLevel penalty
		rate = rate - rate * tarTolerace / 100;

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 30000;
		if( time != 9999 )
			time = preDelayTime + time - time * tarVit / 100 - 10 * tarLuk;

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, preDelayTime, time, HEALTHSTATE_CURSE, 0);

		if( other->GetType() == NPC_MOB_TYPE && time > 0 )
			static_cast<CNPC*>(other)->CNPC::SetATKPercentInfo(-2, time, -25); //TODO: SKID = -2?

		return 1;
	}
	break;
	case HEALTH_CONFUSION:
	{
		if( healthState & HEALTHSTATE_CONFUSION )
		{// cancel confusion
			g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, 0, 0, HEALTHSTATE_CONFUSION, 0);
			return 1;
		}

		int rate = percent - percent * (tarSTR + tarInt) / 200 - m_characterInfo.clevel + tarLevel + tarLuk; //NOTE: sign-inverted penalty
		rate = rate - rate * tarTolerace / 100;

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 30000;
		if( time != 9999 )
			time = preDelayTime + time - time * (tarInt + tarSTR) / 200 - 10 * tarLuk;

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, preDelayTime, time, HEALTHSTATE_CONFUSION, 0);
		return 1;
	}
	break;
	case HEALTH_BLOODING:
	{
		int rate = percent - percent * tarVit / 100 + m_characterInfo.clevel - tarLevel - tarLuk;
		rate = rate - rate * tarTolerace / 100;

		if( GetServerRandom(0, 20000) % 1000 >= rate )
			return 0; // resisted.

		int time = delayTime;
		if( time == 0 )
			time = 120000;
		if( time != 9999 )
			time = time - time * tarVit / 100 - 10 * tarLuk;

		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_TIME_HEALTHSTATE, 0, time, HEALTHSTATE_BLOODING, 0);
		g_characterMgr->CCharacterMgr::SendMsg(this, other, CM_SETEFFECTIVE, EFST_BLOODING, time, 1, 0); //TODO: rate = 1?
		return 1;
	}
	break;
	default:
		return 0;
	break;
	}
}


hook_method<int (CPC::*)(CCharacter* target)> CPC::_GetModifiedTargetItemDEF(SERVER, "CPC::GetModifiedTargetItemDEF");
int CPC::GetModifiedTargetItemDEF(CCharacter* target)
{
	return (this->*_GetModifiedTargetItemDEF)(target);

	//TODO
}


hook_method<int (CPC::*)(CCharacter* target)> CPC::_GetModifiedTargetItemMDEF(SERVER, "CPC::GetModifiedTargetItemMDEF");
int CPC::GetModifiedTargetItemMDEF(CCharacter* target)
{
	return (this->*_GetModifiedTargetItemMDEF)(target);

	//TODO
}


hook_method<int (CPC::*)(int index, int time, int val1, int val2, int val3, int isSendClient)> CPC::_SetEffective(SERVER, "CPC::SetEffective");
int CPC::SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient)
{
	return (this->*_SetEffective)(index, time, val1, val2, val3, isSendClient);
/*
	int v15; // ebx@4
	int v24; // eax@47
	int v25; // eax@50
	int v27; // eax@59
	int v132; // [sp+5Eh] [bp-16h]@130
	int v133; // [sp+64h] [bp-10h]@184
	int arg1C; // [sp+94h] [bp+20h]@0
	int arg24; // [sp+9Ch] [bp+28h]@0
	int arg2C; // [sp+A4h] [bp+30h]@0
	int arg34; // [sp+ACh] [bp+38h]@0
	int arg3C; // [sp+B4h] [bp+40h]@0

	if( time == 0 )
		return 0;

	if( this->IsItPossible(MAPPROPERTY_BLOCK_BUFF) != 0 && m_mapRes->CMapRes::IsPropertyBlockBuff(index) == 1 )
		return 0;

	time = 1;

	switch( index )
	{
	case 10:
	case 12:
	case 13:
	case 192:
	case 330:
		if( val1 < this->GetEffective(index, 0) )
			val2 = 0;
		if( this->GetEffective(149, 0) == 4002 )
			this->ResetEffective(149, 0);
		if ( !time )
			return 0;
		break;
	case 356:
		if( this->GetEffective(356, 0) )
			return 0;
		break;
	case 354:
		this->ResetEffective(354, 0);
		break;
	case 340:
	case 350:
		v24 = this->GetEffective(index, 0);
		if ( v24 <= 0 )
			break;
		if ( v24 > val1 )
			return 0;
		this->ResetEffective(index, 0);
		break;
	case 71:
	case 73:
	case 74:
	case 76:
	case 80:
	case 81:
	case 84:
	case 313:
	case 329:
		v25 = this->GetEffective(index, 0);
		if ( !v25 )
			break;
		if ( val1 <= v25 )
			return 0;
		this->ResetEffective(index, 0);
		break;
	case 1:
	case 315:
		EFFECTIVE_INFO* v26 = this->CCharacter::GetEffectiveInfo(index);
		if ( !v26 )
			break;
		if( v26->time != 9999 )
		{
			if ( time == 9999 )
				this->ResetEffective(index, 0);
			break;
		}
		if ( time != 9999 )
			return 0;

		++v26->val[2];
		Trace("InfinityEndure Count: %d\n", v26->val[2]);
		return 0;
	case 221:
	case 222:
	case 223:
	case 224:
	case 256:
		v27 = this->GetEffective(index, 0);
		if ( !v27 )
			break;
		if ( val1 < v27 )
			return 0;
		this->ResetEffective(index, 0);
		break;
	case 241:
	case 242:
	case 243:
	case 244:
	case 245:
	case 246:
	case 271:
	case 272:
	case 273:
	case 274:
	case 275:
	case 276:
		if( !this->CPC::IsEnableSetEFSTFood(index, val1) )
			time = 0;
		isSendClient = 1;
		if( !time )
			return 0;
		break;
	case 61:
	case 255:
	case 314:
		if( this->GetEffective(index, 0) )
			this->ResetEffective(index, 0);
		break;
	case 60:
		this->ResetEffective(60, 0);
		break;
	case 2:
	case 23:
	case 68:
	case 147:
	case 161:
		isSendClient = 1;
		if( this->GetEffective(13, 0) )
			time = 0;
	//fall through
	case 3:
	case 30:
		if( !this->GetEffective(8, 0) )
		{
			if ( !time )
				return 0;
			break;
		}
		return 0;
	case 70:
	case 72:
	case 75:
	case 77:
		int v19; // eax@18
		v19 = this->GetEffective(index, 0);
		if ( !v19 )
			break;
		if( val1 <= v19 )
			return 0;
		this->ResetEffective(index, 0);
		break;
	case 79:
	case 82:
	case 83:
		if( this->GetEffective(index, 0) )
			return 0;
		break;
	case 118:
		if( this->GetEffective(13, 0) )
		{
			this->ResetEffective(13, 0);
			val2 = 0;
		}
		if( !this->GetEffective(8, 0) )
		{
			if ( !time )
				return 0;
			break;
		}
		this->ResetEffective(8, 0);
		return 0;
	case 176:
	case 177:
	case 178:
		if( !this->GetEffective(index, 0) )
			break;
		this->CCharacter::UpdateEffectiveTime(index, time);
		return 0;
	case 25:
		if( this->GetEffective(188, 0) )
			return 0;
		break;
	case 232:
		if( this->GetEffective(index, 0) > 0 )
			m_pcSkill.CPCSkill::DestroyPlayingSkill();
		break;
	case 247:
	case 248:
	case 249:
		if( this->GetEffective(index, 0) > val1 )
			time = 0;
		if ( !GetParamByEFSTFood(index) )
			time = 0;
		isSendClient = 1;
		if ( !time )
			return 0;
		break;
	case 64:
		this->ResetEffective(64, 0);
		isSendClient = ( val1 == 6 );
		break;
	default:
		time = (unsigned __int8)this->CCharacter::IsEnableSetEffective(index, time, val1);
		if ( !time )
			return 0;
		break;
	}

	CBuffInfo* buffinfo = g_buffInfoMgr->CBuffInfoMgr::GetBuffInfo(index);

	v15 = val1; //FIXME: aliases
	val1 = buffinfo; //FIXME: these two are aliased in the following code

	if( buffinfo != NULL )
		if( !isSendClient )
			isSendClient = buffinfo->CBuffInfo::IsSend();

	EFFECTIVE_INFO* efi = m_effectiveList[index];
	efi->time = ( time == 9999 ) ? 9999 : timeGetTime() + time;
	efi->val[0] = val1;
	efi->val[1] = val2;
	efi->val[2] = val3;
	efi->isSendClient = isSendClient;

	time = 0;

	if( buffinfo != NULL )
		if( buffinfo->IsExistScript() )
			if( !g_buffInfoMgr->CBuffInfoMgr::RunBuffScript(this->GetAccountID(), 2, index) )
				Trace("Buff EVENT_START_EQUIP Error, index = %d\n", index);

	switch( index )
	{
	case 12:
		this->ResetEffective(13, 0);
		(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 29, 14, time, v15 + 2);
		this->UpdateParameterValue(115, 0);
		break;
	case 9:
		this->ResetEffective(11, 0);
		CPC::SetHealthStateTimeInfo(this, 0, time, 32);
		CPCBattle__SetDEFPercentInfo(&m_pcBattle, 33, time, v15);
		break;
	case 10:
		(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 34, 13, time, v15);
		(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 34, 16, time, v15);
		this->OnChangeStatusAmount(34, 17, time, v15);
		break;
	case 30:
		(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 155, 13, time, v15);
		break;
	case 11:
		this->ResetEffective(9, 0);
		break;
	case 4:
	case 27:
	case 41:
	case 42:
	case 69:
	case 116:
	case 118:
	case 119:
	case 185:
	case 192:
	case 239:
	case 289:
		this->UpdateParameterValue(115, 0);
		this->UpdateParameterValue(53, 0);
		break;
	case 152:
	case 171:
	case 222:
		this->UpdateParameterValue(53, 0);
		break;
	case 2:
	case 161:
		this->UpdateParameterValue(115, 0);
		this->UpdateParameterValue(53, 0);
		m_characterInfo.virtue |= 1u;
		break;
	case 207:
		m_characterInfo.virtue |= 0x4000u;
		time = 1;
		break;
	case 223:
	case 256:
		m_characterInfo.extItemDefPower += val1;
		this->CPC::NotifyParameter(0x2Du, 0);
		break;
	case 224:
		(*(void (__thiscall **)(CPC *, signed int, signed int, signed int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 584, 52, 9999, v15);
		this->CPC::NotifyParameter(VAR_CRITICALSUCCESSVALUE, this->CPC::GetCriticalSuccessValue());
		break;
	case 227:
		this->CCharacter::ResetStatusAmount(0x24Eu, 0);
		(*(void (__thiscall **)(CPC *, signed int, signed int, signed int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 590, 165, 9999, v15);
		if ( (*((int (__thiscall **)(_DWORD, _DWORD, _DWORD))this->vtable + 42))(this, 238, 0) )
			this->ResetEffective(238, 0);
		break;
	case 254:
		CCharacter__ResetStatusAmount(this, 0x26Bu, 0);
		this->OnChangeStatusAmount(619, 16, 9999, val1);
		break;
	case 235:
		this->CPC::NotifyParameter(0x2Du, 0);
		this->CPC::NotifyParameter(0x2Fu, 0);
		m_characterInfo.virtue |= 0x10u;
		break;
	case 234:
		this->CPC::NotifyParameter(0x2Du, 0);
		this->CPC::NotifyParameter(0x2Fu, 0);
		break;
	case 238:
		outpacket.PacketType = 645;
		outpacket.index = 100;
		LOWORD(outpacket.AID) = v15;
		this->CPC::Send(6, (char *)&outpacket);

		if( this->GetEffective(227, 0) )
		{
			if( g_makerRankMgr->CMakerRankMgr::GetMakerPower(m_characterInfo.characterID, 5) != 1 )
				this->ResetEffective(227, 0);
		}
		break;
	case 232:
		unsigned int v41 = CZoneSkillGroupUniqueIDGenerator::m_cpSelf->CZoneSkillGroupUniqueIDGenerator::Alloc();
		int v40 = -1;
		do
		{
			int v42 = -1;
			do
			{
				CSkill* v43 = g_characterMgr->CCharacterMgr::CreateSkill2(v41, v40 + LOWORD(m_pathInfo.m_moveInfo.xPos), v42 + LOWORD(m_pathInfo.m_moveInfo.yPos), m_mapRes, 134, m_characterInfo.accountID, timeGetTime() + 3600000, 1, 0x254u, 1, 0, 1);
				if ( v43 )
				{
					m_pcSkill->CPCSkill::AddPlayingSkill(v43->GetAccountID(), v40, v42);
				}
				++v42;
			}
			while ( v42 <= 1 );
			++v40;
		}
		while ( v40 <= 1 );

		m_pcSkill.m_playStartedTime = timeGetTime();
		m_characterInfo.virtue |= 0x1000u;
		time = 1;
		isSendClient = 1;
		break;
	case 165:
	case 166:
	case 167:
		m_characterInfo.virtue |= 0x1000u;
		time = 1;
		isSendClient = 1;
		break;
	case 49:
		if( this->GetEffective(110, 0) )
			this->ResetEffective(110, 0);
		break;
	case 31:
		m_characterInfo.virtue |= 4u;
		break;
	case 68:
		time = 1;
		this->UpdateParameterValue(53, 0);
		m_characterInfo.virtue |= 1u;
		break;
	case 61:
		m_characterInfo.resistByProperty[6] += v15;
		m_characterInfo.resistByRace[6] += v15;
		time = 1;
		break;
	case 255:
		m_characterInfo.plusByRace[v15] += 50;
		break;
	case 266:
		(*(void (__thiscall **)(CPC *, signed int))((void (__thiscall **)(_DWORD, _DWORD))this->vtable + 60))(this, 64);
		break;
	case 64:
		this->ResetEffective(17, 0);
		this->ResetEffective(6, 0);
		this->ResetEffective(146, 0);
		this->ResetEffective(148, 0);
		this->UpdateParameterValue(138, val1);
		break;
	case 90:
		this->UpdateParameterValue(138, 3);
		time = 1;
		break;
	case 91:
		this->UpdateParameterValue(138, 1);
		time = 1;
		break;
	case 93:
		this->UpdateParameterValue(138, 2);
		time = 1;
		break;
	case 92:
		this->UpdateParameterValue(138, 4);
		time = 1;
		break;
	case 67:
		(*(void (__thiscall **)(CPC *, signed int))((void (__thiscall **)(_DWORD, _DWORD))this->vtable + 60))(this, 2048);
		break;
	case 87:
		this->CPC::NotifyParameter(0x2Du, 0);
		this->CPC::NotifyParameter(0x2Fu, 0);
		m_characterInfo.virtue |= 0x10u;
		this->UpdateParameterValue(53, 0);
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(0, this->CPC::GetSpeed());
		time = 1;
		break;
	case 62:
		this->UpdateParameterValue(53, 0);
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(0, this->CPC::GetSpeed());
		time = 1;
		break;
	case 86:
		this->UpdateParameterValue(52, 0);
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(0x34u, this->CPC::GetCriticalSuccessValue());
		m_characterInfo.virtue |= 8u;
		time = 1;
		break;
	case 85:
		if ( v15 > 0 )
		{
			outpacket.PacketType = 465;
			*(_DWORD *)&outpacket.index = this->GetAccountID();
			*(unsigned int *)((char *)&outpacket.AID + 2) = v15;
			v132 = 1;
			this->CPC::Send(14, (char *)&outpacket);
			this->CCharacter::MultiCast((char *)&outpacket, 14);
			m_characterInfo.virtue |= 0x20u;
		}
		break;
	case 70:
		int v51 = *(_DWORD *)v15;
		*(_DWORD *)&outpacket.state = *(_DWORD *)(v15 + 4);
		EFFECTIVE_INFO* v52 = m_effectiveList[index];
		int v53 = *(_DWORD *)&outpacket.state;
		v52->time = *(_DWORD *)&outpacket;
		v52->val[0] = v51;
		v52->val[1] = v53;
		v52->val[2] = val3;
		v52->isSendClient = isSendClient;
		m_characterInfo.extDodgePercent += *(_DWORD *)v15;
		m_characterInfo.extDodgePercent2 += *(_DWORD *)(v15 + 4);
		this->UpdateParameterValue(VAR_BASICAVOIDANCE, 0);
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_PLUSAVOIDSUCCESSVALUE, this->CPC::GetPlusAvoidableSucPerOnClient());
		break;
	case 72:
		int v57 = *(_DWORD *)v15;
		*(_DWORD *)&outpacket.state = *(_DWORD *)(v15 + 4);
		EFFECTIVE_INFO* v58 = m_effectiveList[index];
		int v59 = *(_DWORD *)&outpacket.state;
		v58->time = *(_DWORD *)&outpacket;
		v58->val[0] = v57;
		v58->val[1] = v59;
		v58->val[2] = val3;
		v58->isSendClient = isSendClient;
		m_characterInfo.reduceSpellCastTime += *(_DWORD *)v15;
		m_characterInfo.reducePostDelay += *(_DWORD *)(v15 + 4);
		break;
	case 75:
		this->ResetEffective(12, 0);
		this->ResetEffective(2, 0);
		this->ResetEffective(23, 0);
		this->ResetEffective(68, 0);
		this->ResetEffective(161, 0);
		this->ResetEffective(147, 0);

		int v62 = *(_DWORD *)v15;
		int v63 = *(_DWORD *)(v15 + 4);
		EFFECTIVE_INFO* v64 = m_effectiveList[index];
		v64->time = *(_DWORD *)&outpacket;
		v64->val[0] = v62;
		v64->val[1] = v63;
		v64->val[2] = val3;
		v64->isSendClient = isSendClient;
		this->UpdateParameterValue(115, 0);
		this->UpdateParameterValue(53, 0);
		break;
	case 77:
		int v68 = *(_DWORD *)v15;
		*(_DWORD *)&outpacket.state = *(_DWORD *)(v15 + 4);
		EFFECTIVE_INFO* v69 = m_effectiveList[index];
		int v70 = *(_DWORD *)&outpacket.state;
		v69->time = *(_DWORD *)&outpacket;
		v69->val[0] = v68;
		v69->val[1] = v70;
		v69->val[2] = val3;
		v69->isSendClient = isSendClient;
		this->UpdateParameterValue(112, *(_DWORD *)v15);
		m_characterInfo.reducePercentSP += *(_DWORD *)(v15 + 4);
		break;
	case 79:
		m_pcBattle.CPCBattle::SetDEFPercentInfo(308, 0x270Fu, v15);
		break;
	case 80:
		this->CPC::SendZCWhisperFromServer("The Sound Of a Drum On the Battlefield, Level = %d", buffInfo?); // guessed arg
		m_characterInfo.extItemDefPower += g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(0, 309, 14, v15, 2, 0, 0);
		m_characterInfo.extAttPower += g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(0, 309, 14, v15, 1, 0, 0);
		this->CPC::NotifyParameter(0x29u, 0);
		this->CPC::NotifyParameter(0x2Du, 0);
		break;
	case 84:
		int v72 = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(0, 313, 14, v15, 0, 0, 0);
		m_characterInfo.resistByProperty[3] += v72;
		m_characterInfo.resistByProperty[1] += v72;
		m_characterInfo.resistByProperty[2] += v72;
		m_characterInfo.resistByProperty[4] += v72;
		m_characterInfo.resistByProperty[5] += v72;
		m_characterInfo.resistByProperty[6] += v72;
		m_characterInfo.resistByProperty[7] += v72;
		m_characterInfo.resistByProperty[8] += v72;
		m_characterInfo.resistByProperty[9] += v72;
		int v73 = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(0, 313, 15, v15, 0, 0, 0);
		m_characterInfo.resistHandicapState[0] += v73;
		m_characterInfo.resistHandicapState[1] += v73;
		m_characterInfo.resistHandicapState[2] += v73;
		m_characterInfo.resistHandicapState[3] += v73;
		m_characterInfo.resistHandicapState[5] += v73;
		m_characterInfo.resistHandicapState[6] += v73;
		m_characterInfo.resistHandicapState[7] += v73;
		m_characterInfo.resistHandicapState[8] += v73;
		m_characterInfo.resistHandicapState[9] += v73;
		break;
	case 97:
		m_characterInfo.virtue |= 0x10000u;
		this->ResetEffective(18, 0);
		this->ResetEffective(12, 0);
		this->ResetEffective(10, 0);
		this->CPC::SetCurrentState(29);
		break;
	case 102:
		time = 1;
		std__map_int_EFFECTIVE_INFO_std__less_int__std__allocator_std__pair_int_const_EFFECTIVE_INFO_____operator__(&m_effectiveList, &index)->val[0] = *(_DWORD *)v15;
		(*(void (__thiscall **)(CPC *, _DWORD, signed int, int, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, *(_DWORD *)v15, 13, time, *(_DWORD *)(v15 + 4));
		this->OnChangeStatusAmount(*(_DWORD *)v15, 14, time, *(_DWORD *)(v15 + 4));
		this->OnChangeStatusAmount(*(_DWORD *)v15, 15, time, *(_DWORD *)(v15 + 4));
		this->OnChangeStatusAmount(*(_DWORD *)v15, 16, time, *(_DWORD *)(v15 + 4));
		this->OnChangeStatusAmount(*(_DWORD *)v15, 17, time, *(_DWORD *)(v15 + 4));
		this->OnChangeStatusAmount(*(_DWORD *)v15, 18, time, *(_DWORD *)(v15 + 4));
		break;
	case 315:
		this->CPC::NotifyParameter(0x2Fu, 0);
		if ( time != 9999 )
			std__map_int_EFFECTIVE_INFO_std__less_int__std__allocator_std__pair_int_const_EFFECTIVE_INFO_____operator__(&m_effectiveList, &index)->val[1] = 7;
		index = 1;
		break;
	case 103:
		m_characterInfo.virtue |= 0x40u;
		time = 1;
		break;
	case 110:
		m_characterInfo.virtue |= 0x800u;
		time = 1;
		break;
	case 107:
		if ( v15 >= 0 )
		{
			this->UpdateParameterValue(111, v15);
			this->UpdateParameterValue(5, this->CPC::GetMaxHP());
			this->UpdateParameterValue(53, 0);
			this->UpdateParameterValue(115, 0);
			m_characterInfo.virtue |= 0x80u;
			time = 1;
		}
		break;
	case 105:
		this->UpdateParameterValue(166, 0);
		time = 1;
		break;
	case 113:
		m_characterInfo.virtue |= 0x100u;
		time = 1;
		break;
	case 125:
		time = 1;
		if ( v15 & 1 )
			this->UpdateParameterValue(115, 0);
		if ( v15 & 2 )
			this->UpdateParameterValue(53, 0);
		if ( v15 & 4 )
		{
			this->UpdateParameterValue(115, 0);
			this->UpdateParameterValue(53, 0);
		}
		if ( v15 & 8 )
			CPCBattle__SetDEFPercentInfo(&m_pcBattle, 399, time, -50);
		if ( v15 & 0x10 )
		{
			CPCBattle__SetDEFPercentInfo(&m_pcBattle, 399, time, -25);
			CPCBattle__SetATKPercentInfo(&m_pcBattle, 399, time, -25);
		}
		break;
	case 123:
		m_characterInfo.virtue |= 0x200u;
		time = 1;
		break;
	case 121:
	case 122:
		m_characterInfo.virtue |= 0x400u;
		time = 1;
		break;
	case 133:
		time = 1;
		this->UpdateParameterValue(115, 0);
		break;
	case 146:
		this->ResetEffective(6, 0);
		this->UpdateParameterValue(138, 7);
		break;
	case 148:
		this->ResetEffective(6, 0);
		this->UpdateParameterValue(138, 8);
		break;
	case 153:
		m_characterInfo.virtue |= 0x2000u;
		isSendClient = 1;
		break;
	case 145:
		(*(void (__thiscall **)(CPC *, signed int, signed int, signed int, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 411, 13, 150000, 10);
		isSendClient = 1;
		break;
	case EFST_SOULLINK: //149
		m_characterInfo.virtue |= 0x8000u;
		if( v15 == 4002 )
		{
			int v81 = m_characterInfo.clevel - 10;
			if ( v81 >= 0 )
			{
				if ( v81 > 50 )
					v81 = 50;
			}
			else
			{
				v81 = 0;
			}

			(*(void (__thiscall **)(CPC *, signed int, int *, unsigned int, int, signed int, int, signed int, _DWORD, unsigned int, _DWORD, _DWORD, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 11))(this, 13, &isSendClient);
			int v82 = v81 - arg3C;
			arg3C = v82;
			if ( v82 > 0 )
			{
				v133 = v82;
				(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 494, 13, time, v82);
			}
			v133 = (int)&arg3C;
			*(int *)((char *)&v132 + 2) = 16;

			(void (__thiscall *)(_DWORD))*((_DWORD *)this->vtable + 11)(this);
			int v84 = v81 - arg34;
			arg34 = v84;
			if ( v84 > 0 )
			{
				*(_DWORD *)&outpacket.state = v84;
				(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 494, 16, time, v84);
			}

			*(_DWORD *)&outpacket.state = &arg34;
			outpacket.AID = 17;

			(void (__thiscall *)(_DWORD))*((_DWORD *)this->vtable + 11)(this);
			int v87 = v81 - arg2C;
			arg2C = v87;
			if ( v87 > 0 )
			{
				(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 494, 17, time, v87);
			}

			(void (__thiscall *)(_DWORD))*((_DWORD *)this->vtable + 11)(this);
			int v90 = v81 - arg24;
			arg24 = v90;
			if ( v90 > 0 )
			{
				(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 494, 15, time, v90);
			}

			(void (__thiscall *)(_DWORD))*((_DWORD *)this->vtable + 11)(this);
			int v93 = v81 - arg1C;
			arg1C = v93;
			if ( v93 > 0 )
			{
				(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 494, 14, time, v93);
			}

			(void (__thiscall *)(_DWORD))*((_DWORD *)this->vtable + 11)(this);
			int v96 = v81 - isSendClient;
			isSendClient = v96;
			if ( v96 > 0 )
			{
				(*(void (__thiscall **)(CPC *, signed int, signed int, signed int, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 494, 18, time, v96);
			}
		}
		isSendClient = 1;
		break;
	case 263:
		m_characterInfo.virtue |= 0x20000u;
		isSendClient = 1;
		break;
	case 150:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(0x29u, this->CPC::GetAttPowerOnClient());
		break;
	case 151:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(0x2Bu, this->CPC::GetMagicAttMaxPowOnClient());
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(0x2Cu, this->CPC::GetMagicAttMinPowOnClient());
		break;
	case 129:
		this->UpdateParameterValue(165, 0);
		break;
	case 177:
		this->UpdateParameterValue(111, val1);
		break;
	case 178:
		this->UpdateParameterValue(112, val1);
		break;
	case 182:
		(*(void (__thiscall **)(CPC *, signed int, signed int, int, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 389, 13, time, 1 << (m_pcSkill.CPCSkill::GetSkillLevel(SKID_ST_CHASEWALK, 0) - 1));
		break;
	case 187:
		if ( v15 != 1 )
		{
			this->CPC::UpdateAttackMotionTime();
			break;
		}
		(*(void (__thiscall **)(CPC *, signed int, int, signed int, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 41))(this, 47, time, 1, 0, 0, 0);
		(*(void (__thiscall **)(CPC *, signed int, int, signed int, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 41))(this, 46, time, 1, 0, 0, 0);
		break;
	case 188:
		this->ResetEffective(25, 0);
		m_characterInfo.virtue |= 2u;
		break;
	case 25:
		m_characterInfo.virtue |= 2u;
		break;
	case 189:
		(*(void (__thiscall **)(CPC *, signed int, int, signed int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 43))(this, 69, -this->GetEffective(EFST_BDPLAYING, 1), 1);
		this->CPC::UpdateAttackMotionTime();
		this->UpdateParameterValue(115, 0);
		break;
	case 180:
		CPC::UpdateAttackMotionTime(this);
		this->UpdateParameterValue(115, 0);
		break;
	case 155:
		this->UpdateParameterValue(115, 0);
		break;
	case 190:
		if ( v15 != 5 )
		{
			m_characterInfo.magicImmune |= 4u;
			time = 1;
		}
		break;
	case 191:
		this->OnChangeStatusAmount(489, 166, 30000, -20);
		this->OnChangeStatusAmount(489, 165, 30000, -20);
		break;
	case 200:
		this->OnChangeStatusAmount(1005, 165, time, 10);
		(*((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 41))(this, 202, time, 1, 0, 0, 0);
		isSendClient = 1;
		break;
	case 201:
		(*((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 41))(this, 202, time, 1, 0, 0, 0);
		isSendClient = 1;
		break;
	case 203:
		(*(void (__thiscall **)(CPC *, signed int, int, signed int, _DWORD, _DWORD, _DWORD))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 41))(this, 202, time, 1, 0, 0, 0);
		this->OnChangeStatusAmount(504, 41, time, val2);
		this->CPC::UpdateAttackMotionTime();
		break;
	case 209:
		this->OnChangeStatusAmount(505, 166, time, val2);
		this->OnChangeStatusAmount(505, 165, time, val3);
		break;
	case 210:
		this->OnChangeStatusAmount(506, 166, time, v15);
		this->OnChangeStatusAmount(506, 14, time, val2);
		this->OnChangeStatusAmount(506, 17, time, val2);
		break;
	case 204:
		this->UpdateParameterValue(53, 0);
		int v105 = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(0, 517, 14, val3, 1, 0, 0);
		(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 517, 41, time, v105);
		int v107 = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(0, 517, 14, val3, 2, 0, 0);
		(*(void (__thiscall **)(CPC *, signed int, signed int, int, int))((void (__thiscall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->vtable + 51))(this, 517, 165, time, v107);
		this->UpdateParameterValue(115, 0);
		break;
	case 211:
		this->OnChangeStatusAmount(538, 14, time, val2);
		this->UpdateParameterValue(115, 0);
		break;
	case 208:
		this->OnChangeStatusAmount(543, 13, time, v15);
		this->OnChangeStatusAmount(543, 16, time, v15);
		break;

	case EFST_DEVOTION: //60
		CPC* pc = (CPC *)g_characterMgr->CCharacterMgr::FindCharacter(v15, 4u);
		if( pc == NULL )
			return 0;
		if ( (*(int (__thiscall **)(CPC *))((int (__thiscall **)(_DWORD))pc->vtable + 1))(pc) )
			break;
		int v116 = this->GetAccountID();
		int v117 = (int)pc->m_devotionList._Myhead;
		int v118 = *(_DWORD *)v117;
		val2 = v116;
		if ( v118 == v117 )
			goto LABEL_231;
		while ( *(_DWORD *)(v118 + 8) != v116 )
		{
			v118 = *(_DWORD *)v118;
			if ( v118 == v117 )
			{
LABEL_231:
				std__list_unsigned_long_std__allocator_unsigned_long____push_front(&pc->m_devotionList, (const unsigned int *)&val2);
				break;
			}
		}

		pc->CPC::NotifyDevotionList();
		break;
	}


	///TODO: shovel cases from above down here

	switch( index )
	{
	case EFST_ENDURE: //1
		m_characterTimeInfo.DamageNoMotionTime = ( time == 9999 ) ? 9999 : timeGetTime() + time;
		if( time != 9999 )
			m_effectiveList[index].val[1] = 7;
		break;

	case EFST_ENCHANTPOISON: //6
		this->ResetEffective(EFST_ASPERSIO, 0);
		this->ResetEffective(EFST_WEAPONPROPERTY, 0);
		this->ResetEffective(EFST_PROPERTYDARK, 0);
		this->ResetEffective(EFST_PROPERTYTELEKINESIS, 0);
		this->UpdateParameterValue(VAR_ATTACKPROPERTY, PROPERTY_POISON);
		break;

	case EFST_QUAGMIRE: //8
		this->ResetEffective(EFST_CONCENTRATION, 0);
		this->ResetEffective(EFST_SHOUT, 0);
		this->ResetEffective(EFST_INC_AGI, 0);
		this->ResetEffective(EFST_TWOHANDQUICKEN, 0);
		this->ResetEffective(EFST_ADRENALINE, 0);
		this->ResetEffective(EFST_SPEARQUICKEN, 0);
		this->ResetEffective(EFST_WINDWALK, 0);
		this->ResetEffective(EFST_CARTBOOST, 0);
		this->ResetEffective(EFST_ADRENALINE2, 0);
		this->ResetEffective(EFST_ONEHANDQUICKEN, 0);
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
		this->UpdateParameterValue(VAR_ASPD, 0);
		break;

	case EFST_DEC_AGI: //13
		this->ResetEffective(EFST_INC_AGI, 0);
		this->ResetEffective(EFST_TWOHANDQUICKEN, 0);
		this->ResetEffective(EFST_ADRENALINE, 0);
		this->ResetEffective(EFST_SPEARQUICKEN, 0);
		this->ResetEffective(EFST_CARTBOOST, 0);
		this->ResetEffective(EFST_ONEHANDQUICKEN, 0);
		this->ResetEffective(EFST_ADRENALINE2, 0);
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
		break;

	case EFST_IMPOSITIO: //15
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_STR, 0);
		break;

	case EFST_ASPERSIO: //17
		this->ResetEffective(EFST_ENCHANTPOISON, 0);
		this->ResetEffective(EFST_WEAPONPROPERTY, 0);
		this->ResetEffective(EFST_PROPERTYDARK, 0);
		this->ResetEffective(EFST_PROPERTYTELEKINESIS, 0);
		this->UpdateParameterValue(VAR_ATTACKPROPERTY, PROPERTY_SAINT);
		break;

	case EFST_BENEDICTIO: //18
		this->ResetEffective(EFST_PROPERTYUNDEAD, 0);
		break;

	case EFST_GLORIA: //21
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_LUK, this->CPC::GetLukValue());
		break;

	case EFST_ADRENALINE: //23
	case EFST_ATTHASTE_POTION1: //37
	case EFST_ATTHASTE_POTION2: //38
	case EFST_ATTHASTE_POTION3: //39
	case EFST_ATTHASTE_INFINITY: //40
	case EFST_ASSASSINCROSS: //71
	case EFST_ADRENALINE2: //147
		this->UpdateParameterValue(VAR_ASPD, 0);
		break;

	case EFST_POSTDELAY: //46
		if( time != 9999 && m_characterInfo.reducePostDelay != 0 )
		{
			EFFECTIVE_INFO* efi = &m_effectiveList[index];
			efi->time = timeGetTime() + time - time * m_characterInfo.reducePostDelay / 100;
			efi->val[0] = val1;
			efi->val[1] = val2;
			efi->val[2] = val3;
			efi->isSendClient = isSendClient;
		}
		break;

	case EFST_NOEQUIPWEAPON: //50
	case EFST_NOEQUIPSHIELD: //51
	case EFST_NOEQUIPARMOR: //52
	case EFST_NOEQUIPHELM: //53
	case EFST_PROTECTWEAPON: //54
	case EFST_PROTECTSHIELD: //55
	case EFST_PROTECTARMOR: //56
	case EFST_PROTECTHELM: //57
	case EFST_AUTOSPELL: //65
	case EFST_COMBOATTACK: //89
	case EFST_STOP: //95
	case EFST_PARRYING: //104
	case EFST_TENSIONRELAX: //106
	case EFST_MELTDOWN: //117
	case EFST_BLOODING: //124
	case EFST_MINDBREAKER: //126
	case EFST_MEMORIZE: //127
	case EFST_PROTECTEXP: //130
		time = 1;
		break;

	case EFST_APPLEIDUN: //73
	case EFST_EPICLESIS: //329
		this->UpdateParameterValue(VAR_MAXHPPERCENT, val1);
		break;

	case EFST_HUMMING: //74
		m_characterInfo.hitPercent += val1;
		this->UpdateParameterValue(VAR_BASICHIT, 0);
		break;

	case EFST_FORTUNEKISS: //76
		m_characterInfo.criPercent += val1;
		this->UpdateParameterValue(VAR_CRITICALSUCCESSVALUE, 0);
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_CRITICALSUCCESSVALUE, this->CPC::GetCriticalSuccessValue());
		break;

	case EFST_RESISTHANDICAP: //176
		m_characterInfo.resistHandicapState[0] += val1;
		m_characterInfo.resistHandicapState[1] += val1;
		m_characterInfo.resistHandicapState[2] += val1;
		m_characterInfo.resistHandicapState[3] += val1;
		m_characterInfo.resistHandicapState[4] += val1;
		m_characterInfo.resistHandicapState[5] += val1;
		m_characterInfo.resistHandicapState[6] += val1;
		m_characterInfo.resistHandicapState[7] += val1;
		m_characterInfo.resistHandicapState[8] += val1;
		m_characterInfo.resistHandicapState[9] += val1;
		break;

	case EFST_FOOD_STR: //241
	case EFST_FOOD_AGI: //242
	case EFST_FOOD_VIT: //243
	case EFST_FOOD_DEX: //244
	case EFST_FOOD_INT: //245
	case EFST_FOOD_LUK: //246
	case EFST_FOOD_BASICAVOIDANCE: //247
	case EFST_FOOD_BASICHIT: //248
	case EFST_FOOD_CRITICALSUCCESSVALUE: //249
	case EFST_FOOD_STR_CASH: //271
	case EFST_FOOD_AGI_CASH: //272
	case EFST_FOOD_VIT_CASH: //273
	case EFST_FOOD_DEX_CASH: //274
	case EFST_FOOD_INT_CASH: //275
	case EFST_FOOD_LUK_CASH: //276
		this->OnChangeStatusAmount(30000, GetParamByEFSTFood(index), time, v15);
		break;

	case EFST_CASH_BOSS_ALARM: //253
	{
		CCharacter* ch = g_characterMgr->CCharacterMgr::FindBossInMap(m_mapRes->m_mapID);
		if( ch != NULL )
		{
			m_effectiveList[index].val[0] = ch->GetAccountID();
			g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_REQ_ADD_BOSS_PCLIST, 0, 0, 0, 0);
		}
		break;
	}

	case EFST_PARTYFLEE: //313
		this->OnChangeStatusAmount(693, 165, time, v15);
		break;

	case EFST_ANGEL_PROTECT: //314
		this->UpdateParameterValue(VAR_HPACCELERATION, 50);
		this->UpdateParameterValue(VAR_SPACCELERATION, 50);
		break;

	case EFST_WAVE1: //228
	case EFST_WAVE2: //229
	case EFST_WAVE3: //230
	case EFST_WAVE4: //231
	case EFST_ORATIO: //330
	case EFST_EXPIATIO: //340
	case EFST_DUPLELIGHT: //350
	case EFST_MARSHOFABYSS: //354
	case EFST_AUTOSHADOWSPELL: //393
		break;

	default:
		this->CCharacter::SetEffective(index, time, val1, val2, val3, isSendClient);
		break;
	}

	if( index < EFST_AUTOCOUNTER || time != 0 || isSendClient )
	{
		PACKET_ZC_MSG_STATE_CHANGE outpacket;
		outpacket.PacketType = HEADER_ZC_MSG_STATE_CHANGE;
		outpacket.index = index;
		outpacket.AID = m_characterInfo.accountID;
		outpacket.state = 1;

		this->CPC::Send(sizeof(outpacket), (char *)&outpacket);
		this->CCharacter::MultiCast((char *)&outpacket, sizeof(outpacket));
		this->CPC::SendPacketToPartyInMapOuterRange(sizeof(outpacket), (char *)&outpacket);
	}

	if( buffinfo != NULL )
		if( buffinfo->CBuffInfo::IsSave() )
			m_isSetEffectiveBySpecialItem = true;

	return 1;
*/
}


hook_method<void (CPC::*)(int index, int val)> CPC::_ResetEffective(SERVER, "CPC::ResetEffective");
void CPC::ResetEffective(int index, int val)
{
	return (this->*_ResetEffective)(index, val);

	//TODO
}


hook_method<bool (CPC::*)(int index, int& SKID, bool& isPlaySolo)> CPC::_IsGroundEffective(SERVER, "CPC::IsGroundEffective");
bool CPC::IsGroundEffective(int index, int& SKID, bool& isPlaySolo)
{
	return (this->*_IsGroundEffective)(index, SKID, isPlaySolo);

	//TODO
}


hook_method<void (CPC::*)(int index, int SKID, bool isPlaySolo)> CPC::_ProcessGroundEffective(SERVER, "CPC::ProcessGroundEffective");
void CPC::ProcessGroundEffective(int index, int SKID, bool isPlaySolo)
{
	return (this->*_ProcessGroundEffective)(index, SKID, isPlaySolo);

	//TODO
}


hook_method<void (CPC::*)(int value)> CPC::_SetOnShowEFST(SERVER, "CPC::SetOnShowEFST");
void CPC::SetOnShowEFST(int value)
{
	return (this->*_SetOnShowEFST)(value);

	//TODO
}


hook_method<void (CPC::*)(int value)> CPC::_SetOffShowEFST(SERVER, "CPC::SetOffShowEFST");
void CPC::SetOffShowEFST(int value)
{
	return (this->*_SetOffShowEFST)(value);

	//TODO
}


hook_method<void (CPC::*)(int SKID, unsigned short type, unsigned long time, int amount)> CPC::_OnChangeStatusAmount(SERVER, "CPC::OnChangeStatusAmount");
void CPC::OnChangeStatusAmount(int SKID, unsigned short type, unsigned long time, int amount)
{
	return (this->*_OnChangeStatusAmount)(SKID, type, time, amount);

	//TODO
}


hook_method<void (CPC::*)(unsigned short type, int amount)> CPC::_NotifyStatusAmount(SERVER, "CPC::NotifyStatusAmount");
void CPC::NotifyStatusAmount(unsigned short type, int amount)
{
	return (this->*_NotifyStatusAmount)(type, amount);

	//TODO
}


hook_method<char (CPC::*)(void)> CPC::_GetCampID(SERVER, "CPC::GetCampID");
char CPC::GetCampID(void)
{
	return (this->*_GetCampID)();

	//TODO
}


hook_method<void (CPC::*)(char campID)> CPC::_SetCampID(SERVER, "CPC::SetCampID");
void CPC::SetCampID(char campID)
{
	return (this->*_SetCampID)(campID);

	//TODO
}


hook_method<const char* (CPC::*)(void)> CPC::_GetNamePtr(SERVER, "CPC::GetNamePtr");
const char* CPC::GetNamePtr(void)
{
	return (this->*_GetNamePtr)();

	//TODO
}


hook_method<short (CPC::*)(void)> CPC::_GetHealthState(SERVER, "CPC::GetHealthState");
short CPC::GetHealthState(void) // line 1112-1114
{
	return (this->*_GetHealthState)();

	return static_cast<short>(m_characterPInfo.healthState);
}


hook_method<void (CPC::*)(short state)> CPC::_ResetHealthState(SERVER, "CPC::ResetHealthState");
void CPC::ResetHealthState(short state)
{
	return (this->*_ResetHealthState)(state);

	//TODO
}


hook_method<void (CPC::*)(unsigned long time, int state)> CPC::_SetEffectStateTimeInfo(SERVER, "CPC::SetEffectStateTimeInfo");
void CPC::SetEffectStateTimeInfo(unsigned long time, int state)
{
	return (this->*_SetEffectStateTimeInfo)(time, state);

	//TODO
}


hook_method<void (CPC::*)(int state)> CPC::_ResetEffectState(SERVER, "CPC::ResetEffectState");
void CPC::ResetEffectState(int state)
{
	return (this->*_ResetEffectState)(state);

	//TODO
}


hook_method<void (CPC::*)(int state)> CPC::_SetEffectState(SERVER, "CPC::SetEffectState");
void CPC::SetEffectState(int state)
{
	return (this->*_SetEffectState)(state);

	//TODO
}


hook_method<int (CPC::*)(unsigned short id, int& value)> CPC::_GetBodyItemCount(SERVER, "CPC::GetBodyItemCount");
int CPC::GetBodyItemCount(unsigned short id, int& value)
{
	return (this->*_GetBodyItemCount)(id, value);

	//TODO
}


hook_method<int (CPC::*)(unsigned short id, int count, bool isidentified)> CPC::_UpdateBodyItemCount(SERVER, "CPC::UpdateBodyItemCount");
int CPC::UpdateBodyItemCount(unsigned short id, int count, bool isidentified)
{
	return (this->*_UpdateBodyItemCount)(id, count, isidentified);

	//TODO
}


hook_method<int (CPC::*)(unsigned short id, int count, bool isidentified)> CPC::_UpdateBodyItemCountByNPC(SERVER, "CPC::UpdateBodyItemCountByNPC");
int CPC::UpdateBodyItemCountByNPC(unsigned short id, int count, bool isidentified)
{
	return (this->*_UpdateBodyItemCountByNPC)(id, count, isidentified);

	//TODO
}


hook_method<void (CPC::*)(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause)> CPC::_SkillUseAck(SERVER, "CPC::SkillUseAck");
void CPC::SkillUseAck(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause)
{
	return (this->*_SkillUseAck)(SKID, NUM, result, cause);

	//TODO
}


hook_method<void (CPC::*)(CCharacter* ch, int attackProperty, int& damage)> CPC::_ModifyAttackPowerByEffective(SERVER, "CPC::ModifyAttackPowerByEffective");
void CPC::ModifyAttackPowerByEffective(CCharacter* ch, int attackProperty, int& damage)
{
	return (this->*_ModifyAttackPowerByEffective)(ch, attackProperty, damage);

	//TODO
}


hook_method<void (CPC::*)(int& def, CCharacter* in_cpAtkerCH)> CPC::_ApplyExtraDEF(SERVER, "CPC::ApplyExtraDEF");
void CPC::ApplyExtraDEF(int& def, CCharacter* in_cpAtkerCH)
{
	return (this->*_ApplyExtraDEF)(def, in_cpAtkerCH);

	//TODO
}


hook_method<void (CPC::*)(int& def)> CPC::_ApplyExtraMDEF(SERVER, "CPC::ApplyExtraMDEF");
void CPC::ApplyExtraMDEF(int& def)
{
	return (this->*_ApplyExtraMDEF)(def);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_InitTime(SERVER, "CPC::InitTime");
void CPC::InitTime(void) // line 842-883
{
	return (this->*_InitTime)();

	unsigned long initTime = timeGetTime();

	memset(&m_characterTimeInfo, 0, sizeof(m_characterTimeInfo));
	m_BodyStateValue = 0;
	m_BodyStateTime[0] = 0;
	m_BodyStateTime[1] = 0;
	m_BodyStateTime[2] = 0;
	memset(&m_HealthStateTime, 0, sizeof(m_HealthStateTime));
	memset(&m_HealthStateValue, 0, sizeof(m_HealthStateValue));
	m_characterTimeInfo.connectedTime = initTime;
	m_characterTimeInfo.lastPacketArrivedTime = initTime;
	m_characterTimeInfo.LastHPPlusTime = initTime;
	m_characterTimeInfo.LastSPPlusTime = initTime;
	m_characterTimeInfo.HPLastHealTime = initTime;
	m_characterTimeInfo.SPLastHealTime = initTime;
	m_characterTimeInfo.LastCharInfoSaveTime = initTime;
	m_characterTimeInfo.lastMannerTime = initTime;
	m_characterTimeInfo.lastPKMannerTime = initTime;
	m_characterTimeInfo.HSvrAliveTime = initTime;
	this->CPC::SetAttackLastTime(initTime);
	this->CPC::SetLastAttackedTime(initTime);
	m_characterTimeInfo.SpeedMount = 100;
	m_emoticonTM.CPollTimer::Init(initTime, 2250);
	m_invincibleInfo.clear();
	m_characterTimeInfo.ChangeSpeedTime = 0;
	m_characterTimeInfo.ChangeSpeed = 100;
}


//hook_method<int (CPC::*)(void)> CPC::_GetLockCounter(SERVER, "CPC::GetLockCounter");
int CPC::GetLockCounter(void)
{
//	return (this->*_GetLockCounter)();

	return m_lockCounter;
}


//hook_method<void (CPC::*)(int count)> CPC::_ModifyLockCounter(SERVER, "CPC::ModifyLockCounter");
void CPC::ModifyLockCounter(int count)
{
//	return (this->*_ModifyLockCounter)(count);

	m_lockCounter += count;
}


hook_method<void (CPC::*)(void)> CPC::_OnDamagedWeapon(SERVER, "CPC::OnDamagedWeapon");
void CPC::OnDamagedWeapon(void)
{
	return (this->*_OnDamagedWeapon)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnDamagedArmor(SERVER, "CPC::OnDamagedArmor");
void CPC::OnDamagedArmor(void)
{
	return (this->*_OnDamagedArmor)();

	//TODO
}


hook_method<void (CPC::*)(int type)> CPC::_OnDamageEquipment(SERVER, "CPC::OnDamageEquipment");
void CPC::OnDamageEquipment(int type)
{
	return (this->*_OnDamageEquipment)(type);

	//TODO
}


hook_method<void (CPC::*)(int petMsg, int par1)> CPC::_SendMsgToPet(SERVER, "CPC::SendMsgToPet");
void CPC::SendMsgToPet(int petMsg, int par1) // line 14383-14388
{
	return (this->*_SendMsgToPet)(petMsg, par1);

	CNpcPet* pet = this->CPC::GetMyPetObject();
	if( pet != NULL )
		pet->CNpcPet::OnPetMsg(this, petMsg, par1);
}


hook_method<int (CPC::*)(void)> CPC::_ConvertPetToPetEgg(SERVER, "CPC::ConvertPetToPetEgg");
int CPC::ConvertPetToPetEgg(void)
{
	return (this->*_ConvertPetToPetEgg)();

	//TODO
}


hook_method<CNpcPet* (CPC::*)(void)> CPC::_GetMyPetObject(SERVER, "CPC::GetMyPetObject");
CNpcPet* CPC::GetMyPetObject(void)
{
	return (this->*_GetMyPetObject)();

	//TODO
}


hook_method<int (CPC::*)(unsigned short item)> CPC::_OnUsePetAcc(SERVER, "CPC::OnUsePetAcc");
int CPC::OnUsePetAcc(unsigned short item)
{
	return (this->*_OnUsePetAcc)(item);

	//TODO
}


hook_method<int (CPC::*)(unsigned short item)> CPC::_IsPetWearable(SERVER, "CPC::IsPetWearable");
int CPC::IsPetWearable(unsigned short item)
{
	return (this->*_IsPetWearable)(item);

	//TODO
}


hook_method<void (CPC::*)(const unsigned char* in_pData, const int in_Length)> CPC::_LoadEffectiveInfo(SERVER, "CPC::LoadEffectiveInfo");
void CPC::LoadEffectiveInfo(const unsigned char* in_pData, const int in_Length)
{
	return (this->*_LoadEffectiveInfo)(in_pData, in_Length);

	//TODO
}


hook_method<int (CPC::*)(unsigned char* out_Data, const int in_MaxBytes)> CPC::_GetEffectiveDBFmt(SERVER, "CPC::GetEffectiveDBFmt");
int CPC::GetEffectiveDBFmt(unsigned char* out_Data, const int in_MaxBytes)
{
	return (this->*_GetEffectiveDBFmt)(out_Data, in_MaxBytes);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_CheckGameGuard(SERVER, "CPC::CheckGameGuard");
int CPC::CheckGameGuard(void)
{
	return (this->*_CheckGameGuard)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnCM_NOTIFY_STOREDITEM(SERVER, "CPC::OnCM_NOTIFY_STOREDITEM");
void CPC::OnCM_NOTIFY_STOREDITEM(void)
{
	return (this->*_OnCM_NOTIFY_STOREDITEM)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_OnCM_NOTIFY_CASHITEM(SERVER, "CPC::OnCM_NOTIFY_CASHITEM");
void CPC::OnCM_NOTIFY_CASHITEM(void)
{
	return (this->*_OnCM_NOTIFY_CASHITEM)();

	//TODO
}


hook_method<void (CPC::*)(int ITID)> CPC::_OnConSumeSpecialItem(SERVER, "CPC::OnConSumeSpecialItem");
void CPC::OnConSumeSpecialItem(int ITID)
{
	return (this->*_OnConSumeSpecialItem)(ITID);

	//TODO
}


hook_method<void (CPC::*)(int mob)> CPC::_OnHuntingList(SERVER, "CPC::OnHuntingList");
void CPC::OnHuntingList(int mob)
{
	return (this->*_OnHuntingList)(mob);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_LoadHuntingList(SERVER, "CPC::LoadHuntingList");
void CPC::LoadHuntingList(void)
{
	return (this->*_LoadHuntingList)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_LoadTimeList(SERVER, "CPC::LoadTimeList");
void CPC::LoadTimeList(void)
{
	return (this->*_LoadTimeList)();

	//TODO
}


hook_method<bool (CPC::*)(unsigned short efstType, int val)> CPC::_IsEnableSetEFSTFood(SERVER, "CPC::IsEnableSetEFSTFood");
bool CPC::IsEnableSetEFSTFood(unsigned short efstType, int val)
{
	return (this->*_IsEnableSetEFSTFood)(efstType, val);

	int efstType2;
	bool isCashItem;

	switch( efstType )
	{
	case EFST_FOOD_STR_CASH:
		efstType2 = EFST_FOOD_STR;
		isCashItem = true;
	break;
	case EFST_FOOD_AGI_CASH:
		efstType2 = EFST_FOOD_AGI;
		isCashItem = true;
	break;
	case EFST_FOOD_VIT_CASH:
		efstType2 = EFST_FOOD_VIT;
		isCashItem = true;
	break;
	case EFST_FOOD_DEX_CASH:
		efstType2 = EFST_FOOD_DEX;
		isCashItem = true;
	break;
	case EFST_FOOD_INT_CASH:
		efstType2 = EFST_FOOD_INT;
		isCashItem = true;
	break;
	case EFST_FOOD_LUK_CASH:
		efstType2 = EFST_FOOD_LUK;
		isCashItem = true;
	break;
	case EFST_FOOD_STR:
		efstType2 = EFST_FOOD_STR_CASH;
		isCashItem = false;
	break;
	case EFST_FOOD_AGI:
		efstType2 = EFST_FOOD_AGI_CASH;
		isCashItem = false;
	break;
	case EFST_FOOD_VIT:
		efstType2 = EFST_FOOD_VIT_CASH;
		isCashItem = false;
	break;
	case EFST_FOOD_DEX:
		efstType2 = EFST_FOOD_DEX_CASH;
		isCashItem = false;
	break;
	case EFST_FOOD_INT:
		efstType2 = EFST_FOOD_INT_CASH;
		isCashItem = false;
	break;
	case EFST_FOOD_LUK:
		efstType2 = EFST_FOOD_LUK_CASH;
		isCashItem = false;
	break;
	default:
		return false;
	}

	int oldVal1 = this->GetEffective(efstType, 0);
	int oldVal2 = this->GetEffective(efstType2, 0);

	if( isCashItem )
	{
		if( oldVal1 > val )
			return false;
	}
	else
	{
		if( oldVal2 > 0 )
			return false;

		if( oldVal1 > val )
			return false;

		if( oldVal2 > val )
			return false;
	}

	this->ResetEffective(efstType, 0);
	this->ResetEffective(efstType2, 0);
	return true;
}


hook_method<void (CPC::*)(unsigned short msg)> CPC::_SendZCMsg(SERVER, "CPC::SendZCMsg");
void CPC::SendZCMsg(unsigned short msg)
{
	return (this->*_SendZCMsg)(msg);

	//TODO
}


hook_method<void (CPC::*)(char* packet)> CPC::_OnNotifyBossInfo(SERVER, "CPC::OnNotifyBossInfo");
void CPC::OnNotifyBossInfo(char* packet)
{
	return (this->*_OnNotifyBossInfo)(packet);

	//TODO
}


hook_method<void (CPC::*)(int mob)> CPC::_OnQuestHuntingList(SERVER, "CPC::OnQuestHuntingList");
void CPC::OnQuestHuntingList(int mob)
{
	return (this->*_OnQuestHuntingList)(mob);

	//TODO
}


hook_method<void (CPC::*)(unsigned short SKID, unsigned long delaytime)> CPC::_SetSkillSinglePostDelay(SERVER, "CPC::SetSkillSinglePostDelay");
void CPC::SetSkillSinglePostDelay(unsigned short SKID, unsigned long delaytime)
{
	return (this->*_SetSkillSinglePostDelay)(SKID, delaytime);

	//TODO
}


hook_method<int (CPC::*)(void)> CPC::_IsFirstJobORLowLevel(SERVER, "CPC::IsFirstJobORLowLevel");
int CPC::IsFirstJobORLowLevel(void)
{
	return (this->*_IsFirstJobORLowLevel)();

	if( m_characterInfo.job >= JT_NOVICE && m_characterInfo.job <= JT_THIEF || JT_TAEKWON == m_characterInfo.job || JT_NOVICE_B == m_characterInfo.job || JT_GANGSI == m_characterInfo.job || JT_GUNSLINGER == m_characterInfo.job || JT_NINJA == m_characterInfo.job )
	{
		if( IsSetting(SETTING_KILLER_SYSTEM) )
		{
			if( g_ForeignCode == 5 && m_characterInfo.clevel <= 70 )
					return 1;
			else if( m_characterInfo.clevel <= 60 )
					return 1;
			
		}
		else if( m_characterInfo.clevel <= 50 )
		{
				return 1;
		}
	}

	return 0;
}


hook_method<void (CPC::*)(int bFlag)> CPC::_SetMapLoadingFlag(SERVER, "CPC::SetMapLoadingFlag");
void CPC::SetMapLoadingFlag(int bFlag) // line 19131
{
	return (this->*_SetMapLoadingFlag)(bFlag);

	m_isMapLoading = bFlag;
	m_invalidPacket = 0;

	if( bFlag == 1 )
		m_MapLoadingTick = timeGetTime();
}


//hook_method<int (CPC::*)(void)> CPC::_isAuctionOpen(SERVER, "CPC::isAuctionOpen");
int CPC::isAuctionOpen(void) // line ?????
{
//	return (this->*_isAuctionOpen)();

	return m_isAuctionOpen;
}


//hook_method<int (CPC::*)(void)> CPC::_isMailOpen(SERVER, "CPC::isMailOpen");
int CPC::isMailOpen(void) // line ?????
{
//	return (this->*_isMailOpen)();

	return m_isMailOpen;
}


hook_method<void (CPC::*)(void)> CPC::_AuctionOpen(SERVER, "CPC::AuctionOpen");
void CPC::AuctionOpen(void) // line 19140
{
	return (this->*_AuctionOpen)();

	//TODO
};


hook_method<void (CPC::*)(void)> CPC::_MailOpen(SERVER, "CPC::MailOpen");
void CPC::MailOpen(void) // line 19158
{
	return (this->*_MailOpen)();

	//TODO
}


hook_method<void (CPC::*)(int Index, ShortCutKey SCKey)> CPC::_OnShortcutKey_Change(SERVER, "CPC::OnShortcutKey_Change");
void CPC::OnShortcutKey_Change(int Index, ShortCutKey SCKey) // line 21112
{
	return (this->*_OnShortcutKey_Change)(Index, SCKey);

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_SendShortCutKeyInfo(SERVER, "CPC::SendShortCutKeyInfo");
void CPC::SendShortCutKeyInfo(void) // line 21116
{
	return (this->*_SendShortCutKeyInfo)();

	//TODO
}


hook_method<void (CPC::*)(void)> CPC::_ScriptTimeClear(SERVER, "CPC::ScriptTimeClear");
void CPC::ScriptTimeClear(void) // line 20593
{
	return (this->*_ScriptTimeClear)();

	m_scriptTimeMap.clear();
}


hook_method<void (CPC::*)(int key)> CPC::_SetScriptTime(SERVER, "CPC::SetScriptTime");
void CPC::SetScriptTime(int key) // line 20597
{
	return (this->*_SetScriptTime)(key);

	m_scriptTimeMap.erase(key);
	m_scriptTimeMap.insert(mystd::pair<int,DWORD>(key, timeGetTime()));
}


hook_method<int (CPC::*)(int key)> CPC::_GetScriptTime(SERVER, "CPC::GetScriptTime");
int CPC::GetScriptTime(int key) // line 20604
{
	return (this->*_GetScriptTime)(key);

	mystd::map<int,DWORD>::const_iterator it = m_scriptTimeMap.find(key);
	return ( it != m_scriptTimeMap.end() ) ? it->second : -1;
}


/// Checks if this player's party is a family party that's eligible for even exp share.
/// @custom
bool CPC::IsFamilySharePossible(void)
{
	if( m_familyInfo.baby == 0 )
		return false; // no baby in family

	if( m_groupMember.size() > 3 )
		return false; // other people in party

	CPC* babyPC = g_characterMgr->CCharacterMgr::FindPCByGID(m_familyInfo.baby);

	if( babyPC == NULL )
		return false; // baby not online on this zone

	if( !this->CPC::IsMyPartyMember(babyPC->GetAccountID()) )
		return false; // baby not in this party

	for( mystd::list<unsigned long>::const_iterator it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
	{
		unsigned long memberAID = *it;
		CPC* memberPC = (CPC *)g_characterMgr->CCharacterMgr::FindCharacter(memberAID, UNKNOWN_TYPE);

		if( memberPC == NULL )
			return false; // member not online on this zone

		if( memberPC->m_mapRes != m_mapRes )
			return false; // member on some other map

		unsigned long memberGID = memberPC->CPC::GetCharacterID();

		if( (memberGID != m_familyInfo.father || memberPC->m_characterInfo.clevel < 70)
		&&  (memberGID != m_familyInfo.mother || memberPC->m_characterInfo.clevel < 70)
		&&   memberGID != m_familyInfo.baby )
			return false; // not a valid and eligible family member
	}

	return true;
}
