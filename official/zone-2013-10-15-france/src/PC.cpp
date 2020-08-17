#include "CharacterMgr.h"
#include "CharInfoDB.h"
#include "Enum.h"
#include "EStateTypeInfo3rd2_Elemental.h"
#include "EStateTypeInfoMgr.h"
#include "ExpParameter.h"
#include "ITPMgr.h"
#include "MapRes.h"
#include "MapResMgr.h"
#include "ObjectRecycleMgr.h"
#include "PC.h"
#include "PCFormula_PhysicsSupport.h"
#include "PCProperty.h"
#include "RoomMgr.h"
#include "SkillTypeInfo.h"
#include "SkillTypeInfo3rd1_Mechanic.h"
#include "SkillTypeInfoMgr.h"
#include "SSIMgr.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "AsyncDBWork/DeleteCoupleADBWork.h"
#include "AsyncDBWork/LoadCartADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/SaveCartADBWork.h"
#include "Common/Packet.h"
#include "NetLib/AsyncStream.h"
#include "Player/Inventory/CIVItEquipItem.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/shared.h"
#include "shared/VarLenPacketPtr.h"


void MannerPointInfo::Init(CPC* pc) // 241-243 (161-164)
{
	m_owner = pc;
	this->MannerPointInfo::Reset();
}


void MannerPointInfo::Reset() // 247-249 (167-169)
{
	m_info.clear();
}


int MannerPointInfo::LoadMPInfo() // 252-254 (172-174)
{
	return g_charInfoDB.CCharInfoDB::LoadMPInfo(m_owner->GetAccountID(), &m_info, m_lastTimeGivingMP);
}


void MannerPointInfo::InsertNewMP(unsigned long otherGID, int type) // ??? (177-180)
{
	Trace("InsertNewMP gid:%d, type:%d\n", otherGID, type);
	g_charInfoDB.CCharInfoDB::InsertNewMP(m_owner->GetAccountID(), otherGID, type);
}


BOOL MannerPointInfo::SearchOtherCharacter(unsigned long otherGID) // ??? (183-192)
{
	for( std::list<MannerPointData>::iterator iter = m_info.begin(); iter != m_info.end(); ++iter )
		if( iter->otherGID == otherGID )
			return TRUE; // found.

	return FALSE; // not found.
}


int MannerPointInfo::GetSize() // ??? (195-197)
{
	return m_info.size();
}


int MannerPointInfo::DeleteFirstRecord() // ??? (200-210)
{
	std::list<MannerPointData>::iterator iter = m_info.begin();
	unsigned long AID = m_owner->GetAccountID();
	unsigned long otherGID = iter->otherGID;
	m_info.erase(iter);
	g_charInfoDB.CCharInfoDB::DeleteMP(AID, otherGID);
	return -1;
}


unsigned long MannerPointInfo::IsGivableMP(unsigned long otherGID) // ??? (216-234)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	if( this->MannerPointInfo::SearchOtherCharacter(otherGID) )
		return 2;

	if( m_lastTimeGivingMP == st.wDay )
		return 1;

	if( this->MannerPointInfo::GetSize() >= 30 )
		this->MannerPointInfo::DeleteFirstRecord();

	m_lastTimeGivingMP = st.wDay;
	return 0;
}


CPC::CPC() // 351-375
{
	m_dwErrorCount = 0;
	m_type = PC_TYPE;
	m_mapRes = NULL;
	m_DisconnectStep = CPC::DISCONNECTSTEP_NONE;
	m_pcproperty = new CPCProperty(this);
	m_seCashPoint = 0;
	m_Open_SeSimpleCashShop = 0;
}


CPC::~CPC() // 436-437
{
}


hook_func<void (__stdcall *)()> CPC__Init(EXEPATH(), "CPC::Init");
void CPC::Init(CAsyncStream* stream, DWORD ip) // 439-828 (280-540)
{
	void* hookptr = CPC__Init;
	__asm push ip
	__asm push stream
	__asm push this
	__asm call hookptr
	return; //TODO
/*
	this->CActor::Init();
	m_asyncStream = stream;
	m_ip = ip;
	m_DisconnectStep = CPC::DISCONNECTSTEP_NONE;
	m_nBanTime = 0;
	m_dwErrorCount = 0;
	m_mapRes = NULL;
	m_eventNo = 0;
	m_captureItemList.clear();
	m_useIncubator = 0;
	m_isPetOwner = false;
	memset(&m_characterInfo, 0, sizeof(m_characterInfo));
	m_characterInfo.accountID = -1;
	m_characterInfo.mapID = -1;
	m_characterInfo.extDEFPercent = 100.0;
	m_characterInfo.extMDEFPercent = 100.0;
	m_characterInfo.headpalette = 0;
	m_characterInfo.bodypalette = 0;
	m_characterInfo.robe = 0;
	m_characterInfo.accessory2 = 0;
	m_characterInfo.accessory3 = 0;
	m_characterInfo.headDir = 0;
	m_characterInfo.targetxPos = 100;
	m_characterInfo.targetyPos = 100;
	m_characterInfo.shoes = 0;
	m_characterInfo.virtue = 0;
	m_characterInfo.xSize = 5;
	m_characterInfo.ySize = 5;
	m_characterInfo.MHP_Percent = 100;
	m_characterInfo.MSP_Percent = 100;
	m_characterInfo.isWhisperAcceptable = 1;
	m_characterInfo.NotifyPositionX = 9999;
	m_characterInfo.NotifyPositionY = 9999;
	m_characterInfo.ATKPercent = 100;
	m_characterInfo.DEFPercent = 100;
	m_characterInfo.DEFFluctuation = 100;
	m_characterInfo.MDEFFluctuation = 100;
	m_characterInfo.MATKPercent = 100;
	m_characterInfo.MDEFPercent = 100;
	this->CPC::InitTime();
	m_characterPInfo.bodyState = 0;
	m_characterPInfo.healthState = 0;
	m_characterPInfo.effectState = 0;
	m_characterPInfo.armor = 0;
	m_characterPInfo.currentProperty = 0;
	m_characterPInfo.attack = 0;
	memset(&m_plusStatusByJob, 0, sizeof(m_plusStatusByJob));
	m_isValid = FALSE;
	m_isPKModeON = FALSE;
	m_index = 0;
	m_lastNPCAID = 0;
	m_npcTouchCount = 0;
	m_lastCardIndex = 0;
	m_cookSucc_Tool = 0;
	m_isItemMovable = TRUE;
	this->CPC::ResetGroupMember();
	m_whisperExRegister.clear();
	m_pathInfo.CPathInfo::Reset();
	m_neighborCache.CNeighborCache::Init();
	m_pcClientUpdater.CPCClientUpdater::SetMyOwner(this);
	m_pcClientUpdater.CPCClientUpdater::Init();
	m_pcClientUpdater.CPCClientUpdater::SetSendable(0);
	m_pcItem.CPCItem::Init();
	m_pcItem.CPCItem::SetMyOwner(this);
	m_pcitemInventoryMgr.CPCItemInventoryMgr::Init();
	m_pcitemInventoryMgr.CPCItemInventoryMgr::SetMyOwner(this);
	m_questEvent.CPCQuestEvent::Reset();
	m_pcSkill.CPCSkill::Init(false);
	m_pcSkill.CPCSkill::SetMyOwner(this);
	m_packetHandler.CPCPacketHandler::Init();
	m_packetHandler.CPCPacketHandler::SetMyOwner(this);
	m_pcBattle.CPCBattle::Init();
	m_pcBattle.CPCBattle::SetMyOwner(this);
	memset(&m_exchangeItemInfo, 0, sizeof(m_exchangeItemInfo));
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
	m_makingItemFlag = FALSE;
	m_devotionList.clear();
	m_magicTargetAID = 0;
	memset(&m_marriageInfo, 0, sizeof(m_marriageInfo));
	m_specialSP = 0;
	m_specialDeath = TRUE;
	m_questEvent.CPCQuestEvent::InIt(this);
	m_statusEffInfo.clear();
	m_lastTargetAID = 0;
	m_palmstrikeList.clear();
	memset(&m_familyInfo, 0, sizeof(m_familyInfo));
	m_noPointEvent = 0;
	m_makerRankPoint = 0;
	m_makerAMPoint = 0;
	m_isLessEffect = 0;
	memset(&m_PKInfo, 0, sizeof(m_PKInfo));
	memset(&m_storePasswordInfo, 0, sizeof(m_storePasswordInfo));
	memset(&m_CashPasswordInfo, 0, sizeof(m_CashPasswordInfo));
	memset(&m_lottoNumbers, 0, sizeof(m_lottoNumbers));
	m_isMapLoading = FALSE;
	m_invalidPacket = 0;
	m_isAuctionOpen = FALSE;
	m_isMailOpen = FALSE;
	m_isTraderOpen = 0;
	isInitSendGameGuard = FALSE;
	m_PCBangInfo.isPCBang = FALSE;
	m_PCBangInfo.NotifyToClientCnt = 0;
	m_PCBangInfo.PremiumType = 0;
	m_CashPoint = 0;
	m_HireItemCtrl.CPCHireItemCtrl::Init(this);
	m_itemScriptEventNo = 0;
	m_charBuff2.CCharBuff::Reset();
	m_charBuff2.CCharBuff::SetOwner(this);
	this->CPC::ScriptTimeClear();
	m_scrollItemIndex = 0;
	m_pcproperty->CPCProperty::Reset();
	memset(&m_battleFieldInfo, 0, sizeof(m_battleFieldInfo));
	m_characterInfo.deadCount = 0;
	m_isProgress = false;
	m_PubScheduler.CPubScheduler::Init();
	memset(m_resistByProperty, 0, sizeof(m_resistByProperty));
	m_open_simpleCashShop = 0;
	m_clientVersion = 0;
	m_Elemental.CPCElemental::Init();
	m_AsyncMonopolyProcessPtr.reset();
	this->CPC::ClearSearchStoreInfo();
	m_seCashPoint = 0;
	m_Open_SeSimpleCashShop = 0;
	memset(&m_RaceInfo, 0, sizeof(m_RaceInfo));
	m_SPAmount.CSPAmount::Init();
	m_HPAmount.CHPAmount::Init();
*/
}


int CPC::GetStoreMaxItemSize() // 834-856
{
	if( g_bPremium_Service == TRUE )
	{
		if( m_PCBangInfo.PremiumType != 0 )
			return 600;
		else
			return 300;
	}
	else
	{
		return g_StoreMaxItemSize;
	}
}


void CPC::GameGuardInit() // 862-871
{
	if( g_isGameGuardOn )
	{
		m_isSetGameGuard = TRUE;
		m_GameGuardAuth.CCSAuth2::Init();
		m_lastGameGuardCheckTime = timeGetTime() + 30000;
	}

	isInitSendGameGuard = TRUE;
}


BOOL CPC::IsLockOnMode() // 1161-1163
{
	return m_characterInfo.IsLockOnMode;
}


void CPC::SetLockOnMode(BOOL flag) // 1166-1168
{
	m_characterInfo.IsLockOnMode = flag;
}


unsigned long CPC::GetTargetAID() // 1171-1173
{
	return m_characterInfo.targetAID;
}


void CPC::SetTargetAID(unsigned long AID) // 1176-1178
{
	m_characterInfo.targetAID = AID;
}


void CPC::CancelLockOnMode() // 1181-1183
{
	this->CPC::SetLockOnMode(FALSE);
	this->CPC::SetTargetAID(0);
}


void CPC::InitTime() // 1195-1236
{
	DWORD CurTM = timeGetTime();

	memset(&m_characterTimeInfo, 0, sizeof(m_characterTimeInfo));
	m_BodyStateValue = 0;
	memset(&m_BodyStateTime, 0, sizeof(m_BodyStateTime));
	memset(&m_HealthStateValue, 0, sizeof(m_HealthStateValue));
	m_characterTimeInfo.connectedTime = CurTM;
	m_characterTimeInfo.lastPacketArrivedTime = CurTM;
	m_characterTimeInfo.LastHPPlusTime = CurTM;
	m_characterTimeInfo.LastSPPlusTime = CurTM;
	m_characterTimeInfo.HPLastHealTime = CurTM;
	m_characterTimeInfo.SPLastHealTime = CurTM;
	m_characterTimeInfo.LastCharInfoSaveTime = CurTM;
	m_characterTimeInfo.lastMannerTime = CurTM;
	m_characterTimeInfo.lastPKMannerTime = CurTM;
	m_characterTimeInfo.HSvrAliveTime = CurTM;
	this->CPC::SetAttackLastTime(CurTM);
	this->CPC::SetLastAttackedTime(CurTM);
	m_gageRefreshTime = CurTM;
	m_characterTimeInfo.SpeedMount = 100;
	m_emoticonTM.CPollTimer::Init(CurTM, 2250);
	m_invincibleInfo.clear();
	m_characterTimeInfo.ChangeSpeedTime = 0;
	m_characterTimeInfo.ChangeSpeed = 100;
}


void CPC::SetEffectStateTimeInfo(DWORD time, int state) // 1240-1247
{
	if( state == EFFECTSTATE_MARRIED && time == 9999 )
		time = 9000;

	m_effectStateTimeL[state] = timeGetTime() + time;
	this->SetEffectState(state);
}


void CPC::SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state) // 1253-1282
{
	if( m_BodyStateTime[1] == 9999 && m_characterPInfo.bodyState == state && secondTime != 0 )
		return;

	if( secondTime != 0 )
	{
		m_BodyStateTime[0] = firstTime + timeGetTime();
		m_BodyStateTime[1] = ( secondTime == 9999 ) ? 9999 : secondTime + timeGetTime();
		m_BodyStateValue = state;
	}
	else
	{
		m_BodyStateTime[0] = 0;
		m_BodyStateTime[1] = 0;
		m_BodyStateTime[2] = 0;
		this->CPC::SetBodyState(state);
	}
}


hook_func<void (__stdcall *)()> CPC__GetBodyMaxItemWeight(EXEPATH(), "CPC::GetBodyMaxItemWeight");
int CPC::GetBodyMaxItemWeight() // 1351-1458
{
	int result;
	void* hookptr = CPC__GetBodyMaxItemWeight;
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


unsigned short CPC::GetItemCount(unsigned short id) // 1470-1474
{
	int value;
	m_pcitemInventoryMgr.CPCItemInventoryMgr::GetJustBodyItemCount(id, value);

	return value;
}


CPacketHandler* CPC::GetPacketHandler() // 5954-5956
{
	return &m_packetHandler;
}


void CPC::Reset() // 878-1006
{
	//TODO
}


int CPC::OnProcess() // 1012-1126
{
	return 0;
	//TODO
}


const char* CPC::GetNamePtr() const // 819.h (563.h)
{
	return m_characterInfo.characterName;
}


const int CPC::GetMapID() const // 1129-1132
{
	CMapRes* mapRes = const_cast<CPC*>(this)->CCharacter::GetMapRes();
	if( mapRes == NULL )
		return 0;

	return mapRes->CMapRes::GetID();
}


bool CPC::IsPartyJoinMSGRefuse() const // (590.h)
{
	return m_characterInfo.Party.Bit.bRefuseJoinMsg;
}


bool CPC::IsOpenEquipmentWin() const // (594.h)
{
	return m_characterInfo.bOpenEquipmentWin;
}


void CPC::SetDisconnectStep(const enumDisconnectStep in_Step) // (613.h)
{
	m_DisconnectStep = in_Step;
}


const CPC::enumDisconnectStep CPC::GetDisconnectStep() const // (614.h)
{
	return m_DisconnectStep;
}


CPCClientUpdater* CPC::GetClientUpdaterPtr() // (615.h)
{
	return &m_pcClientUpdater;
}


void CPC::StoreItemReset() // (630.h)
{
	m_pcitemInventoryMgr.CPCItemInventoryMgr::StoreItemReset();
}


void CPC::HireItemCheckAdd(const enumInventoryType in_InventoryType, IVItItem* in_pItem) // (639-640.h)
{
	m_HireItemCtrl.CPCHireItemCtrl::RequestAdd(in_InventoryType, in_pItem);
}


void CPC::MercenaryCall_Create_After(const int in_Job) // (655.h)
{
	//TODO
	/*
	m_pcBattle.CPCBattle::MercenaryCall_Create_After(in_Job);
	*/
}


void CPC::MercenaryCall_Delete_After(const int in_reason) // (656.h)
{
	//TODO
	/*
	m_pcBattle.CPCBattle::MercenaryCall_Delete_After(in_reason);
	*/
}


int CPC::GetErrorCount() // ??? (704.h)
{
	return m_dwErrorCount;
}


const char* CPC::GetAccountName() const // 1141-1147
{
	return m_characterInfo.accountName;
}


unsigned long CPC::GetAccountID() // 1151-1153 (791-793)
{
	return m_characterInfo.accountID;
}


unsigned long CPC::GetCharacterID() // 1156-1158 (796-798)
{
	return m_characterInfo.characterID;
}


BOOL CPC::IsValid() // ??? (954.h)
{
	return m_isValid;
}


void CPC::SetValid(const BOOL flag) // ??? (801-803)
{
	m_isValid = flag;
}


BOOL CPC::IsRightProperty(int property) // 1187-1192 (832-837)
{
	return ( this->CPC::GetCurrentState() % 10 == property );
}


CAsyncStream* CPC::GetStream() // ??? (1042.h)
{
	return m_asyncStream;
}


CharacterInfo* CPC::GetCharacterInfo() // ??? (1043.h)
{
	return &m_characterInfo;
}


CPCBattle* CPC::GetPCBattle() // ??? (1044.h)
{
	return &m_pcBattle;
}


void CPC::SetEventNo(int n) // ??? (1082.h)
{
	m_eventNo = n;
}


int CPC::GetEventNo() // ??? (1083.h)
{
	return m_eventNo;
}


void CPC::CheckWeaponState() // 2692-2874
{
	//TODO
}


char* CPC::GetCharacterName() // ??? (1092.h)
{
	return m_characterInfo.characterName;
}


PCBANG_INFO* CPC::GetPcBangInfo() // ??? (1150.h)
{
	return &m_PCBangInfo;
}


BOOL CPC::IsPcBang() // ??? (1159.h)
{
	return m_PCBangInfo.isPCBang;
}


void CPC::SetLessEffect(BOOL bValue) // ??? (1179.h)
{
	m_isLessEffect = bValue;
}


BOOL CPC::GetLessEffect() // ??? (1180.h)
{
	return m_isLessEffect;
}


short CPC::GetExtDodgePercent() // ??? (1288.h)
{
	return m_characterInfo.extDodgePercent;
}


short CPC::GetPlusHitPercent() // ??? (1290.h)
{
  return m_characterInfo.hitPercent;
}


char CPC::GetCampID() // 1741.h (1298.h)
{
	return m_battleFieldInfo.campID;
}


void CPC::SetCampID(char campID) // 1742.h (1299.h)
{
	m_battleFieldInfo.campID = campID;
}


void CPC::MultiCastStateInfo() // 2877-2887
{
	PACKET_ZC_STATE_CHANGE3 outpacket;
	outpacket.PacketType = HEADER_ZC_STATE_CHANGE3;
	outpacket.AID = m_characterInfo.accountID;
	outpacket.bodyState = static_cast<short>(m_characterPInfo.bodyState);
	outpacket.healthState = static_cast<short>(m_characterPInfo.healthState);
	outpacket.effectState = m_characterPInfo.effectState;
	outpacket.isPKModeON = ( this->CPC::IsPKModeON() != FALSE );

	this->Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


hook_func<void (__stdcall *)()> CPC__GetDexValue(EXEPATH(), "CPC::GetDexValue");
short CPC::GetDexValue() // 2890-2892
{
	short result;
	void* hookptr = CPC__GetDexValue;
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPC__GetStrValue(EXEPATH(), "CPC::GetStrValue");
short CPC::GetStrValue() // 2895-2897
{
	short result;
	void* hookptr = CPC__GetStrValue;
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPC__GetIntValue(EXEPATH(), "CPC::GetIntValue");
short CPC::GetIntValue() // 2900-2902
{
	short result;
	void* hookptr = CPC__GetIntValue;
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPC__GetLukValue(EXEPATH(), "CPC::GetLukValue");
short CPC::GetLukValue() // 2905-2907
{
	short result;
	void* hookptr = CPC__GetLukValue;
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPC__GetAgiValue(EXEPATH(), "CPC::GetAgiValue");
short CPC::GetAgiValue() // 2910-2912
{
	short result;
	void* hookptr = CPC__GetAgiValue;
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CPC__GetVitValue(EXEPATH(), "CPC::GetVitValue");
short CPC::GetVitValue() // 2915-2917
{
	short result;
	void* hookptr = CPC__GetVitValue;
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


hook_func<int (CPC::*)(unsigned short id, int& value)> CPC__GetParameterValue(EXEPATH(), "CPC::GetParameterValue");
int CPC::GetParameterValue(unsigned short id, int& value) // 3091-3545 (2675-3083)
{
	return (this->*CPC__GetParameterValue)(id, value); //TODO
}


BOOL CPC::GetBodyItemCount(unsigned short id, int& value) // 3548-3550 (3086-3087)
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemCount(id, value);
}


BOOL CPC::GetJustBodyItemCount(unsigned short id, int& value) // ??? (3091-3092)
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetJustBodyItemCount(id, value);
}


int CPC::GetBodyItemWeight() // 3558-3559 (3096-3097)
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemWeight();
}


hook_func<int (CPC::*)(unsigned short id, int value)> CPC__UpdateParameterValue(EXEPATH(), "CPC::UpdateParameterValue");
int CPC::UpdateParameterValue(unsigned short id, int value) // 3563-4275 (3101-3726)
{
	return (this->*CPC__UpdateParameterValue)(id, value); //TODO
}


hook_func<void (__stdcall *)()> CPC__GetSP(EXEPATH(), "CPC::GetSP");
int CPC::GetSP() // 4278-4280
{
	int result;
	void* hookptr = CPC__GetSP;
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


int CPC::GetWeaponProperty(int position, BOOL isArrowProperty) // 4383-4436
{
	if( this->GetEffective(EFST_INVISIBILITY, 0) )
		return PROPERTY_TELEKINESIS;

	std::pair<bool,int> ret = m_fvarh_ATK_Property();
	if( ret.first )
		return ret.second;

	if( m_characterPInfo.attack != 0 )
		return m_characterPInfo.attack;

	if( this->GetEffective(EFST_ASPERSIO, 0) || this->GetEffective(EFST_ENCHANTPOISON, 0) || this->GetEffective(EFST_WEAPONPROPERTY, 0) )
		return m_characterPInfo.attack;

	if( position == LOCATION_RARM )
	{
		CITP* weaponItp = this->CPC::GetITPEquipedWeapon();
		if( weaponItp != NULL )
		{
			unsigned short weaponType = weaponItp->GetType();
			if( weaponType == TYPE_BOW || weaponType == TYPE_GUN || isArrowProperty )
			{
				IVItItem* arrow = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedArrow();
				if( arrow != NULL )
				{
					CITP* arrowItp = g_itpMgr.CITPMgr::GetITP(arrow->InventoryItem::GetID());
					if( arrowItp != NULL )
						return arrowItp->GetProperty();
				}
			}

			return weaponItp->GetProperty();
		}
	}
	else
	{
		IVItEquipItem* equipItem = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedItem(position);
		if( equipItem != NULL )
		{
			CITP* itp = g_itpMgr.CITPMgr::GetITP(equipItem->InventoryItem::GetID());
			if( itp != NULL )
			{
				if( itp->GetType() == TYPE_WEAPON )
					return itp->GetProperty();
			}
		}
	}

	return m_characterPInfo.attack;
}


hook_func<BOOL (CPC::*)(unsigned short id, int count, bool isidentified)> CPC__UpdateBodyItemCount(EXEPATH(), "CPC::UpdateBodyItemCount");
BOOL CPC::UpdateBodyItemCount(unsigned short id, int count, bool isidentified) // 4441-4452
{
	return (this->*CPC__UpdateBodyItemCount)(id, count, isidentified); //TODO
}


hook_func<IVItItem* (CPC::*)(unsigned short id, int count, bool isidentified)> CPC__UpdateBodyItemCountByNPC(EXEPATH(), "CPC::UpdateBodyItemCountByNPC");
IVItItem* CPC::UpdateBodyItemCountByNPC(unsigned short id, int count, bool isidentified) // 4456-4464 (3898-3909)
{
	return (this->*CPC__UpdateBodyItemCountByNPC)(id, count, isidentified); //TODO
}


void CPC::InsertCommand(COMMAND_QUEUE* command) // ??? (3956-3962)
{
	m_commandQueue.push_back(*command);
}


void CPC::CheckCommandQueue() // 4529-4583 (3965-4019)
{
	std::vector<COMMAND_QUEUE> DispatchVec;

	int count = 0;
	for( std::list<COMMAND_QUEUE>::iterator iter = m_commandQueue.begin(); iter != m_commandQueue.end(); )
	{
		if( iter->executionTime == 0 )
		{
			iter = m_commandQueue.erase(iter);
		}
		else
		if( timeGetTime() >= iter->executionTime )
		{
			DispatchVec.push_back(*iter);
			iter = m_commandQueue.erase(iter);

			++count;
			if( count > 5 )
				break;
		}
		else
		{
			++iter;
		}
	}

	for( std::vector<COMMAND_QUEUE>::iterator iter = DispatchVec.begin(); iter != DispatchVec.end(); ++iter )
		this->CPC::DispatchCommand(reinterpret_cast<int>(&*iter));
}


void CPC::DeleteCommand(unsigned long commandID) // ?4586-4596? (4022-4032)
{
	for( std::list<COMMAND_QUEUE>::iterator iter = m_commandQueue.begin(); iter != m_commandQueue.end(); )
	{		
		if( iter->commandID == commandID )
		{
			iter = m_commandQueue.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


void CPC::ResetCommandQueue() // 4599-4601 (4035-4037)
{
	m_commandQueue.clear();
}


void CPC::DisableAllCommand() // 4604-4626 (4040-4051)
{
	this->DisableCommand(MULTIPLE_ATTACKED_IN);
	this->DisableCommand(ATTACKED_IN);
	this->DisableCommand(USE_SKILL_IN);
	this->DisableCommand(USE_GROUNDSKILL_IN);
	this->DisableCommand(SPEED_CHANGE_IN);
	this->DisableCommand(SPLASH_ATTACK_IN);
	this->CPC::SetSpellCasting(0, 0);
}


bool CPC::IsCancelCasting() // 4630-4637 (-)
{
	if( this->IsSiegeMode()
	 || this->IsItPossible(MAPPROPERTY_TURBOTRACK)
	 || this->CCharacter::IsBattleFieldMode()
	 || !m_characterInfo.noDispel && !this->GetEffective(EFST_UNLIMITED_HUMMING_VOICE, 0)
	 || this->GetEffective(EFST_TOXIN, 0) )
		return true;

	return false;
}


void CPC::DisableCommand(unsigned long commandID) // ??? (4067-4075)
{
	for( std::list<COMMAND_QUEUE>::iterator iter = m_commandQueue.begin(); iter != m_commandQueue.end(); ++iter )
		if( iter->commandID == commandID )
			iter->executionTime = 0;
}


COMMAND_QUEUE* CPC::SearchCommand(unsigned long commandID) // 4653-4658 (4078-4087)
{
	for( std::list<COMMAND_QUEUE>::iterator iter = m_commandQueue.begin(); iter != m_commandQueue.end(); ++iter )
		if( iter->commandID == commandID )
			return &*iter; // found.

	return NULL; // not found.
}


void CPC::DispatchCommand(int par) // 4665-5186
{
	COMMAND_QUEUE* command = reinterpret_cast<COMMAND_QUEUE*>(par);

	switch( command->commandID )
	{
	case ATTACKED_IN:
	case MULTIPLE_ATTACKED_IN:
	{
		const int damage = static_cast<int>(command->par1);
		const int count = static_cast<int>(command->par2);
		const int skATKflag = static_cast<int>(command->par3); // COMMAND_QUEUE::ATK_*
		const BOOL isMeleeATK = static_cast<BOOL>(command->par4);
		const unsigned short SKID = static_cast<unsigned short>(command->par5);
		const int property = static_cast<int>(command->par6);

		if( this->GetState() != CHARACTER_STATE_DEAD || this->GetEffective(EFST_TRICKDEAD, 0) )
		{
			int bodyState = this->GetBodyState();
			if( this->GetState() == CHARACTER_STATE_SIT )
			{
				this->CPC::SetState(CHARACTER_STATE_STAND);
				this->ResetEffective(EFST_SIT, 0);
			}

			if( m_characterPInfo.effectState & EFFECTSTATE_BURROW )
				this->ResetEffectState(EFFECTSTATE_BURROW);

			if( m_characterPInfo.effectState & EFFECTSTATE_HIDING )
			{
				if( !this->GetEffective(EFST_INVISIBILITY, 0) )
				{
					int nHitsLeft = this->GetEffective(EFST_CLOAKINGEXCEED, 0);
					if( nHitsLeft < 1 )
						this->ResetEffectState(EFFECTSTATE_FOOTPRINT | EFFECTSTATE_HIDING);
					else
					if( nHitsLeft == 1 )
						this->ResetEffective(EFST_CLOAKINGEXCEED, 0);
					else
					{
						this->UpdateEffective(EFST_CLOAKINGEXCEED, -1, 0);
					}
				}
			}

			if( this->GetEffective(EFST_TENSIONRELAX, 0) )
				this->ResetEffective(EFST_TENSIONRELAX, 0);

			if( this->GetEffective(EFST_GRAVITATION, 0) )
				this->ResetEffective(EFST_GRAVITATION, 0);

			if( this->IsDamageMotionPossible() )
				m_pcClientUpdater.CPCClientUpdater::StopMove();

			int element = property % 10;
			if( element == PROPERTY_GROUND )
			{
				this->ResetEffective(EFST_MAGNETICFIELD, 0);
			}
			else
			if( element == PROPERTY_FIRE )
			{
				this->ResetEffective(EFST_COLD, 0);
				this->ResetEffective(EFST_THORNS_TRAP, 0);
			}

			this->ResetEffective(EFST_CAMOUFLAGE, 0);
			this->ResetEffective(EFST_SIREN, 0);
			this->CActor::ResetHandicapState(this, HANDICAPSTATE_DEEPSLEEP);

			if( this->GetEffectState() & EFFECTSTATE_MADOGEAR )
			{
				int overheatPoint = ( property % 10 != PROPERTY_FIRE ) ? 1 : 3;

				EFFECTIVE_INFO* cpEFST_OVERHEAT_LIMITPOINT = this->CActor::GetEffectiveInfo(EFST_OVERHEAT_LIMITPOINT);
				if( cpEFST_OVERHEAT_LIMITPOINT != NULL )
				{
					overheatPoint = this->GetEffective(EFST_OVERHEAT_LIMITPOINT, 1) + overheatPoint;
					if( overheatPoint > 999 )
						overheatPoint = 999;
					cpEFST_OVERHEAT_LIMITPOINT->val[0] = timeGetTime();
					cpEFST_OVERHEAT_LIMITPOINT->val[1] = overheatPoint;
				}
				else
				{
					this->SetEffective(EFST_OVERHEAT_LIMITPOINT, 9999, timeGetTime(), overheatPoint, 0, 0);
				}

				if( overheatPoint >= 100 && !this->GetEffective(EFST_OVERHEAT, 0) && overheatPoint >= SK_NC_MAINFRAME::GetExpireOverHeatLimitPoint(this) )
					this->SetEffective(EFST_OVERHEAT, 9999, 1, 0, 0, 0);
			}

			int rageAcquirePercent = this->GetEffective(EFST_FORCEOFVANGUARD, 2);
			if( rageAcquirePercent != 0 && GetServerRandom(0, 20000) % 100 < rageAcquirePercent )
				m_pcSkill.CPCSkill::AddForceOfVanguard(1);

			if( this->GetEffective(EFST_CIRCLE_OF_FIRE_OPTION, 0) )
			{
				const int ATKpercent = this->GetEffective(EFST_CIRCLE_OF_FIRE_OPTION, 1);
				ESTATE_CIRCLE_OF_FIRE_OPTION::Operation(this, ATKpercent);
			}

			m_HPAmount.CHPAmount::operator+=(-damage);

			if( this->GetEffective(EFST_BDPLAYING, 0) )
			{
				if( damage >= this->CPC::GetMaxHP() / 4 )
				{
					CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pcSkill.m_partnerAID, CM_PLAYSKILL_CANCEL, 0, 0, 0, 0);
					m_pcSkill.CPCSkill::DestroyPlayingSkill();
				}
			}

			CCharacter* sender = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(command->sender);
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, sender, CM_PROCESSEFFECT_ATTACK, damage, isMeleeATK, skATKflag, 0);
			if( sender != NULL )
				m_pcBattle.CPCBattle::ApplyEffect_ATKED(sender, isMeleeATK, (skATKflag >> 1) & 1, SKID, damage);

			if( m_HPAmount <= 0 )
			{
				if( CPC::GetCategorySecondJob(m_characterInfo.job) == JT_SUPERNOVICE && m_specialDeath )
				{
					int nextExp = g_expParameter.CExpParameter::GetNextExp(m_characterInfo.clevel, m_characterInfo.job);

					int curExp;
					this->GetParameterValue(VAR_EXP, curExp);

					int perExp;
					if( nextExp <= 100000 )
						perExp = 100 * (int)curExp / nextExp;
					else
						perExp = (int)curExp / (nextExp / 100);
					Trace(" perExp = %d *** \n", perExp);

					if( nextExp != 0 && perExp >= 99 )
					{
						int maxHP;
						this->GetParameterValue(VAR_MAXHP, maxHP);

						m_HPAmount = maxHP;
						m_specialDeath = FALSE;
						this->SetEffective(EFST_STEELBODY, 150000, 1, 0, 0, 0);
						this->CPC::NotifyUseSkill(SKID_MO_STEELBODY, m_characterInfo.accountID, m_characterInfo.accountID, 5, true);
					}
					else
					{
						m_pcClientUpdater.CPCClientUpdater::OnDead(command->sender);
					}
				}
				else
				{
					m_pcClientUpdater.CPCClientUpdater::OnDead(command->sender);
				}
			}

			if( this->GetEffective(EFST_BERSERK, 0) > 0 )
			{
				if( m_HPAmount <= 100 )
				{
					this->ResetEffective(EFST_BERSERK, 0);
					this->SetEffective(EFST_BERSERK, 300000, -1, 0, 0, 0);
				}
			}

			m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HP, m_HPAmount);

			if( this->CPC::IsCancelCasting() )
				this->CPC::CancelCasting(FALSE);

			if( bodyState == BODYSTATE_FREEZING || bodyState == BODYSTATE_STONECURSE || bodyState == BODYSTATE_SLEEP )
				this->CPC::SetBodyStateTimeInfo(0, 0, BODYSTATE_NORMAL);

			this->CPC::SetLastAttackedTime(timeGetTime());

			if( this->GetEffective(EFST_TRICKDEAD, 0) )
			{
				this->CPC::SetState(CHARACTER_STATE_STAND);
				this->ResetEffective(EFST_TRICKDEAD, 0);
			}

			if( this->GetEffective(EFST_ENDURE, 1) > 0 )
			{
				if( command->sender < PC_MINIMUM_AID )
				{
					--m_effectiveList[EFST_ENDURE].val[1];
					if( m_effectiveList[EFST_ENDURE].val[1] == 0 )
						this->ResetEffective(EFST_ENDURE, 0);
				}
			}
			else
			if( this->GetEffective(EFST_ENDURE_MDEF, 1) > 0 )
			{
				if( command->sender < PC_MINIMUM_AID )
				{
					--m_effectiveList[EFST_ENDURE_MDEF].val[1];
					if( m_effectiveList[EFST_ENDURE_MDEF].val[1] == 0 )
						this->ResetEffective(EFST_ENDURE_MDEF, 0);
				}
			}
		}

		if( m_isProgress )
			this->CPC::OnStopedProgress();
	}
	break;
	case USE_SKILL_IN:
	{
		const int SKID = command->par1;
		const int targetAID = command->par2;
		const int skLevel = command->par3;
		const int spCost = command->par4;

		this->ResetEffective(EFST_CURSEDCIRCLE_ATKER, 0);

		this->CPC::OnUseSkill(SKID, targetAID, skLevel, spCost);

		if( SKID != SKID_RA_CAMOUFLAGE )
			this->ResetEffective(EFST_CAMOUFLAGE, 0);

		m_magicTargetAID = 0;
		m_pcBattle.CPCBattle::OnDoubleCasting(SKID, targetAID, skLevel, spCost);
	}
	break;
	case USE_GROUNDSKILL_IN:
	{
		const int SKID = command->par1;
		const int xPos = command->par2;
		const int yPos = command->par3;
		const int skLevel = command->par4;
		const int spCost = command->par5;

		this->ResetEffective(EFST_CAMOUFLAGE, 0);
		this->ResetEffective(EFST_CURSEDCIRCLE_ATKER, 0);

		MSG_TYPE1_TWODWORD msgData = { xPos, yPos };
		this->CPC::OnUseGroundSkill(SKID, (int)&msgData, skLevel, spCost);
	}
	break;
	case SPEED_CHANGE_IN:
	{
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
	}
	break;
	case PKMODE_OFF_IN:
	{
		m_isPKModeON = FALSE;
		this->CPC::MultiCastStateInfo();
	}
	break;
	case SPLASH_ATTACK_IN:
	{
		const int SKID = static_cast<int>(command->par1);

		if( SKID == 0 )
		{
			const int SKID = static_cast<int>(command->par1);
			const short xPos = static_cast<short>(command->par2);
			const short yPos = static_cast<short>(command->par3);
			const unsigned long exceptAID = static_cast<unsigned long>(command->par4);
			const int skLevel = static_cast<int>(command->par5);
			MSG_TYPE1_TWODWORD msgData = { SKID, skLevel };

			this->SplashAttack(100, xPos, yPos, 0, m_characterInfo.splashRange, m_characterInfo.splashRange, exceptAID, &msgData, 100, 1);
		}
		else
		if( SKID == SKID_BA_FROSTJOKER || SKID == SKID_DC_SCREAM )
		{
			const int SKID = static_cast<int>(command->par1);
			const int percent = static_cast<int>(command->par2);
			const int skLevel = static_cast<int>(command->par5);
			MSG_TYPE1_TWODWORD msgData = { SKID, skLevel };

			this->SplashAttack(0, static_cast<short>(m_pathInfo.m_moveInfo.xPos), static_cast<short>(m_pathInfo.m_moveInfo.yPos), 0, 15, 15, command->sender, &msgData, percent, 1);
		}
	}
	break;
	case TELEPORT_IN:
	{
		const char* mapName = reinterpret_cast<const char*>(command->par1);

		if( this->GetState() == CHARACTER_STATE_DEAD )
			break;

		if( mapName == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "TELEPORT_IN, MapName == NULL");
			break;
		}

		MS_MAPMOVE outpar;
		strncpy(outpar.mapName, mapName, countof(outpar.mapName));
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, this, CM_MAPMOVE, (int)&outpar, VT_TELEPORT, 0, 0);
	}
	break;
	case KNUCKBACKED_IN:
	{
		const unsigned long targetAID = command->par1;
		const int x = command->par2;
		const int y = command->par3;

		if( m_mapRes == NULL )
			break;

		if( !m_mapRes->CMapRes::IsMovableCell(x, y) )
			break;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, targetAID, CM_KNOCKBACK, x, y, 0x1, 0);
	}
	break;
	case USE_AUTOSPELL_IN:
	{
		const unsigned short SKID = static_cast<unsigned short>(command->par1);
		const unsigned long targetAID = static_cast<unsigned long>(command->par2);
		const short skillLv = static_cast<short>(command->par3);
		const MSGpar::CVar par = command->par7;

		CCharacter* ch = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(targetAID, UNKNOWN_TYPE);
		if( ch == NULL )
			break;

		m_pcBattle.CPCBattle::UseAutoSpell(SKID, ch, skillLv, par);
	}
	break;
	case USE_AUTOSPELL_GROUND_IN:
	{
		const unsigned short SKID = static_cast<unsigned short>(command->par1);
		const short xPos = static_cast<short>(command->par2);
		const short yPos = static_cast<short>(command->par3);
		const short skillLv = static_cast<short>(command->par4);

		m_pcBattle.CPCBattle::UseAutoSpellToGround(SKID, xPos, yPos, skillLv);
	}
	break;
	case REQUEST_SIT_IN:
	{
		m_packetHandler.CPCPacketHandler::RequestSit();
	}
	break;
	case USE_EFST_IN:
	{
		const int EfstID = command->par1;
		const int time = command->par2;
		const int val1 = command->par3;
		const int val2 = command->par4;

		this->SetEffective(EfstID, time, val1, val2, 0, FALSE);
	}
	break;
	};
}


BOOL CPC::AddExWhisperList(const char* name) // 5189-5196 (4459-4466)
{
	if( m_whisperExRegister.size() > 20 )
		return FALSE;

	m_whisperExRegister[name] = 1;
	return TRUE;
}


BOOL CPC::DeleteExWhisperList(const char* name) // 5199-5206
{
	std::map<std::string,unsigned long>::iterator iter = m_whisperExRegister.find(name);
	if( iter == m_whisperExRegister.end() )
		return FALSE;

	m_whisperExRegister.erase(iter);
	return TRUE;
}


void CPC::SettingWhisperState(BOOL flag) // 5209-5216
{
	if( flag )
	{
		m_characterInfo.isWhisperAcceptable = flag;
		m_whisperExRegister.clear();
	}
	else
	{
		m_characterInfo.isWhisperAcceptable = FALSE;
	}
}


BOOL CPC::SearchWhisperList(const char* name) // 5219-5226
{
	return ( m_whisperExRegister.find(name) != m_whisperExRegister.end() );
}


void CPC::GetWhisperList(int& out_StoreLen, char* buf, const int in_nMaxBufSize) // 5229-5240
{
	out_StoreLen = 0;

	for( std::map<std::string,unsigned long>::iterator iter = m_whisperExRegister.begin(); iter != m_whisperExRegister.end(); ++iter )
	{
		memcpy_s(buf + out_StoreLen, in_nMaxBufSize - out_StoreLen, iter->first.c_str(), 24);
		out_StoreLen += 24;

		if( out_StoreLen > 320 )
		{
			m_whisperExRegister.erase(iter, m_whisperExRegister.end());
			break;
		}
	}
}


unsigned long CPC::GetState() // 5243-5245
{
	return m_pathInfo.m_moveInfo.state;
}


void CPC::SetState(unsigned long state) // 5254-5276
{
	if( state == CHARACTER_STATE_STAND )
		this->ResetEffective(EFST_SIT, 0);
	else
	if( state == CHARACTER_STATE_SIT )
		this->SetEffective(EFST_SIT, 9999, 1, 0, 0, 0);

	m_pathInfo.m_moveInfo.state = state;
}


unsigned long CPC::GetRoomID() // 5280-5282
{
	return m_characterInfo.roomID;
}


void CPC::SetRoomID(unsigned long roomID) // 5285-5287
{
	m_characterInfo.roomID = roomID;
}


void CPC::MulticastDestroyRoom() // 5290-5307
{
	unsigned long roomID = this->CPC::GetRoomID();

	PACKET_ZC_DESTROY_ROOM outpacket;
	outpacket.PacketType = HEADER_ZC_DESTROY_ROOM;
	outpacket.roomID = roomID;

	std::vector<ClientCache*>& cacheList = m_neighborCache.CNeighborCache::GetListPoint();

	for( std::vector<ClientCache*>::iterator iter = cacheList.begin(); iter != cacheList.end(); ++iter )
	{
		ClientCache* cache = *iter;

		CPC* neighborPC = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacterByIndex(cache->AID, cache->Index);
		if( neighborPC == NULL )
			continue;

		if( !m_pcClientUpdater.CPCClientUpdater::IsMyArea(neighborPC, 15) )
			continue;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, neighborPC, CM_DESTROY_ROOM, roomID, sizeof(outpacket), (int)&outpacket, 0);
	}
}


void CPC::RoomNewEntry(unsigned long roomID) // 5310-5328
{
	PACKET_ZC_ROOM_NEWENTRY outpacket;
	outpacket.PacketType = HEADER_ZC_ROOM_NEWENTRY;
	outpacket.AID = g_roomMgr.CRoomMgr::GetOwner(roomID);
	outpacket.curcount = g_roomMgr.CRoomMgr::GetSize(roomID);
	outpacket.maxcount = g_roomMgr.CRoomMgr::GetMaxSize(roomID);
	outpacket.roomID = roomID;
	outpacket.type = g_roomMgr.CRoomMgr::GetType(roomID);

	if( g_roomMgr.CRoomMgr::GetRoomName(roomID) == NULL )
		return;

	char rname[128];
	strncpy(rname, g_roomMgr.CRoomMgr::GetRoomName(roomID), countof(rname));

	outpacket.PacketLength = sizeof(PACKET_ZC_ROOM_NEWENTRY) + strlen(rname);
	this->Send(sizeof(PACKET_ZC_ROOM_NEWENTRY), (const char*)&outpacket);
	this->Send(strlen(rname), rname);
}


void CPC::MulticastRoomNewEntry(unsigned long roomID) // 5331-5348
{
	if( g_roomMgr.CRoomMgr::GetOwner(roomID) != m_characterInfo.accountID )
		return;

	std::vector<ClientCache*>& cacheList = m_neighborCache.CNeighborCache::GetListPoint();

	for( std::vector<ClientCache*>::iterator iter = cacheList.begin(); iter != cacheList.end(); ++iter )
	{
		ClientCache* cache = *iter;

		CPC* neighborPC = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacterByIndex(cache->AID, cache->Index);
		if( neighborPC == NULL )
			continue;

		if( !m_pcClientUpdater.CPCClientUpdater::IsMyArea(neighborPC, 15) )
			continue;

		if( neighborPC->CPC::GetRoomID() == this->CPC::GetRoomID() )
			continue;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, neighborPC, CM_ROOM_NEWENTRY, roomID, 0, 0, 0);
	}
}


BOOL CPC::IsMyArea(CCharacter* ch, int range) // 5351-5353
{
	return m_pcClientUpdater.CPCClientUpdater::IsMyArea(ch, range);
}


bool CPC::IsSendable2(const int in_Bytes) // ??? (4600-4604)
{
	if( !CPC::IsSendable() )
		return false;

	return m_asyncStream->CAsyncStream::IsSendable2(in_Bytes);
}


BOOL CPC::IsSendable() // 5363-5364
{
	return m_pcClientUpdater.CPCClientUpdater::IsSendable();
}


short CPC::GetBodyState() // ??? (4617-4619)
{
	return static_cast<short>(m_characterPInfo.bodyState);
}


short CPC::GetHealthState() // 5378-5380 (4622-4624)
{
	return static_cast<short>(m_characterPInfo.healthState);
}


short CPC::GetCurrentState() // 5383-5399
{
	int armorProperty = this->GetEffective(EFST_ARMOR_PROPERTY, 0);
	if( armorProperty != PROPERTY_NOTHING )
		return armorProperty;

	if( this->GetBodyState() == BODYSTATE_FREEZING )
		return PROPERTY_WATER1;

	if( m_characterPInfo.bodyState == BODYSTATE_STONECURSE )
		return PROPERTY_GROUND1;

	return m_characterPInfo.currentProperty;
}


int CPC::GetEffectState() // 5402-5404 (4644-4646)
{
	return m_characterPInfo.effectState;
}


hook_func<void (__stdcall *)()> CPC__SetBodyState(EXEPATH(), "CPC::SetBodyState");
void CPC::SetBodyState(short state) // 5407-5440
{
	void* hookptr = CPC__SetBodyState;
	__asm push state
	__asm mov ebx, this
	__asm call hookptr
	return; //TODO
}


void CPC::ResetHealthState(short state) // 5443-5499
{
	m_characterPInfo.healthState &= ~state;

	std::vector<int> myHealthStateList = HELP_HEALTHSTATE::GetMyHealthStateList(state);
	for( std::vector<int>::iterator iter = myHealthStateList.begin(); iter != myHealthStateList.end(); ++iter )
	{
		int idx = GetIndexFromBitFlag(*iter);
		m_HealthStateTime[idx][0] = 0;
		m_HealthStateTime[idx][1] = 0;
	}

	if( state & HEALTHSTATE_POISON )
		m_pcBattle.CPCBattle::ResetDEFPercentInfo(-1);

	if( state & HEALTHSTATE_CURSE )
	{
		m_pcBattle.CPCBattle::ResetATKPercentInfo(-2);
		this->CActor::ResetStatusAmount(SKID_NPC_CURSEATTACK, 0);
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
	}

	if( state & HEALTHSTATE_BLIND )
	{
		if( this->GetEffective(EFST_FOGWALL, 0) )
			this->UpdateEffective(EFST_FOGWALL, 1, 0);

		this->UpdateParameterValue(VAR_BASICAVOIDANCE, 0);
	}

	if( state & HEALTHSTATE_BLOODING )
		this->ResetEffective(EFST_BLOODING, 0);

	if( state & HEALTHSTATE_FEAR )
	{
		this->UpdateParameterValue(VAR_BASICAVOIDANCE, 0);
		this->UpdateParameterValue(VAR_BASICHIT, 0);
	}

	if( state & HEALTHSTATE_BLOODING )
		this->ResetEffective(EFST_BLOODING, 0);

	this->CPC::MultiCastStateInfo();
}


hook_func<void (CPC::*)(short state)> CPC__SetHealthState(EXEPATH(), "CPC::SetHealthState");
void CPC::SetHealthState(short state) // 5502-5581
{
	return (this->*CPC__SetHealthState)(state); //TODO
}


void CPC::SetCurrentState(short state) // 5584-5587
{
	m_characterPInfo.currentProperty = state;
	this->CPC::MultiCastStateInfo();
}


hook_func<void (CPC::*)(int state)> CPC__SetEffectState(EXEPATH(), "CPC::SetEffectState");
void CPC::SetEffectState(int state) // 5590-5731
{
	return (this->*CPC__SetEffectState)(state); //TODO
}


void CPC::ResetEffectState(int state) // 5791-5951
{
	m_characterPInfo.effectState &= ~state;

	if( state & EFFECTSTATE_HIDING )
	{
		this->ResetEffective(EFST_CLOAKING, 0);
		this->ResetEffective(EFST_CHASEWALK, 0);
		this->ResetEffective(EFST_CLOAKINGEXCEED, 0);
	}

	switch( state )
	{
	case EFFECTSTATE_CHICKEN:
	case EFFECTSTATE_DRAGON:
	case EFFECTSTATE_DRAGON2:
	case EFFECTSTATE_DRAGON3:
	case EFFECTSTATE_DRAGON4:
	case EFFECTSTATE_DRAGON5:
	{
		this->CPC::OnIncCarry(0);
		this->ResetEffective(EFST_RIDING, 0);
	}
	break;
	case EFFECTSTATE_BIRD:
	{
		this->ResetEffective(EFST_FALCON, 0);
	}
	break;
	case EFFECTSTATE_BURROW:
	{
		this->ResetEffective(EFST_HIDING, 0);
	}
	break;
	case EFFECTSTATE_STAR2:
	{
		this->ResetEffective(EFST_STAR2, 0);
	}
	break;
	case EFFECTSTATE_WUGRIDER:
	{
		this->ResetEffective(EFST_WUGRIDER, 0);
		this->ResetEffective(EFST_WUGDASH, 0);
	}
	break;
	case EFFECTSTATE_MADOGEAR:
	{
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
		this->ResetAllEffective(RESET_MADOGEAR);

		IVItItem* arrow = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedArrow();
		if( arrow == NULL )
			break;

		if( arrow->IVItItem::GetCount() <= 0 )
			break;

		CITP* arrowItp = g_itpMgr.CITPMgr::GetITP(arrow->InventoryItem::GetID());
		if( arrowItp == NULL )
			break;

		if( arrowItp->GetType() == TYPE_CANNONBALL )
		{
			Request request;
			request.Request::SetID(RT_REQ_TAKEOFFEQUIP);
			request.par1 = arrow->IVItItem::GetIndex();
			this->CPC::OnDispatchClientRequest(&request);
		}
	}
	break;
	};

	this->CPC::MultiCastStateInfo();

	if( state == EFFECTSTATE_SANTA || state == EFFECTSTATE_SUMMER || state == EFFECTSTATE_HANBOK || state == EFFECTSTATE_OKTOBERFEST )
		m_pcClientUpdater.CPCClientUpdater::NotifySpriteChange(this, SPRITETYPE_JOB, m_characterInfo.job);

	if( state == EFFECTSTATE_MARRIED )
	{
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
		m_pcClientUpdater.CPCClientUpdater::NotifySpriteChange(this, SPRITETYPE_JOB, m_characterInfo.job);
	}

	if( state == EFFECTSTATE_STAR2 )
		m_pcClientUpdater.CPCClientUpdater::NotifySpriteChange(this, SPRITETYPE_JOB, m_characterInfo.job);
}


void CPC::AsyncLoadStore() // 6024-6088
{
	//TODO
}


void CPC::AsyncDBComplete_LoadCart(int in_SKLevel, const unsigned char* in_pData, int in_Length) // 6107-6116
{
	//TODO
	/*
	if( m_pcitemInventoryMgr.CPCItemInventoryMgr::ParseDBFmtCartItemData(in_Length, in_pData) != true )
		return;

	m_characterInfo.plusCartspeed = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID_MC_PUSHCART, SM_GETINFO_SKILL, in_SKLevel, 0, 0, 0) * m_characterInfo.speed / 100;
	m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_SPEED, this->CPC::GetSpeed());
	*/
}


void CPC::ParseDBFmtStoreItemData(const int in_Length, const unsigned char* in_pData) // 6126-6128
{
	m_pcitemInventoryMgr.CPCItemInventoryMgr::ParseDBFmtStoreItemData(in_Length, in_pData);
}


void CPC::AsyncLoadCart(CCharacter* const in_pSender) // 6139-6198
{
	//TODO
	/*
	short skillLv = m_pcSkill.CPCSkill::GetSkillLevel(SKID_MC_PUSHCART, FALSE);
	if( skillLv == 0 )
	{
		skillLv = m_pcSkill.CPCSkill::GetSkillLevel(SKID_DA_MAGICCART, FALSE);
		if( skillLv > 1 )
			skillLv = 1;
	}

	if( in_pSender != NULL )
		this->SetEffective(EFST_ON_PUSH_CART, 9999, 1, 0, 0, FALSE);

	if( skillLv <= 0 )
		return;

	if( m_pcitemInventoryMgr.CPCItemInventoryMgr::IsCartOn() )
	{
		if( m_dwErrorCount < 4 )
			m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyItemInfo(CART);

		return;
	}

	CLoadCartADBWork* work = CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::Get();
	if( work == NULL )
	{
		this->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	work->CLoadCartADBWork::Init(this->GetAccountID(), this->CPC::GetCharacterID(), skillLv);
	if( NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) != true )
	{
		CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::Put(work);
		this->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	this->SetEffective(EFST_NOACTION_WAIT, 40000, work->NAsyncDBWork::GetIdentity(), work->NAsyncDBWork::GetType(), timeGetTime(), 0);
	*/
}


void CPC::AddGroupMember(unsigned long AID) // 6376-6385
{
	for( std::list<unsigned long>::iterator i = m_groupMember.begin(); i != m_groupMember.end(); ++i )
	{
		if( *i == AID )
			return;
	}

	m_groupMember.push_back(AID);
}


void CPC::DeleteGroupMember(unsigned long AID) // 6388-6401
{
	if( AID == m_characterInfo.accountID )
	{
		memset(m_characterInfo.partyID, '\0', sizeof(m_characterInfo.partyID));
		this->CPC::ResetGroupMember();
	}
	else
	{
		for( std::list<unsigned long>::iterator i = m_groupMember.begin(); i != m_groupMember.end(); ++i )
		{
			if( *i == AID )
			{
				m_groupMember.erase(i);
				return;
			}
		}
	}
}


void CPC::ResetGroupMember() // 6404-6408
{
	m_characterInfo.isGroupMaster = 0;
	m_characterInfo.GroupID = 0;
	m_groupMember.clear();
}


void CPC::GetSplashCells2(PosInfo src, PosInfo dest, int height, PosInfo* result) // ??? (5634-5657)
{
	int incx = ( src.x - dest.x > 0 ) ? 1 : -1;
	int incy = ( src.y - dest.y > 0 ) ? 1 : -1;

	float decl = float((double)(dest.y - src.y) / (double)(dest.x - src.x));
	if( fabs(decl) <= 1/3.0 )
	{
		int x = dest.x;
		int y = dest.y;

		for( int i = 0; i < height; ++i )
		{
			result[i].x = x;
			result[i].y = y;
			x += incx;
		}
	}
	else
	if( fabs(decl) >= 3.0 )
	{
		int x = dest.x;
		int y = dest.y;

		for( int i = 0; i < height; ++i )
		{
			result[i].x = x;
			result[i].y = y;
			y += incy;
		}
	}
	else
	{
		int x = dest.x;
		int y = dest.y;

		for( int i = 0; i < height; ++i )
		{
			result[i].x = x;
			result[i].y = y;
			x += incx;
			y += incy;
		}
	}
}


BOOL CPC::IsDamageMotionPossible() // 6948-6958
{
	if( m_characterTimeInfo.DamageNoMotionTime == 0 )
		return TRUE;

	if( m_characterTimeInfo.DamageNoMotionTime == 9999 || timeGetTime() < m_characterTimeInfo.DamageNoMotionTime )
		return FALSE;

	m_characterTimeInfo.DamageNoMotionTime = 0;
	return TRUE;
}


void CPC::SkillUseAck(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause) // 7427-7437
{
	if( cause == USESKILL_FAIL_MANUAL_NOTIFY )
		return;

	PACKET_ZC_ACK_TOUSESKILL outpacket;
	outpacket.PacketType = HEADER_ZC_ACK_TOUSESKILL;
	outpacket.SKID = SKID;
	outpacket.NUM = NUM;
	outpacket.result = result;
	outpacket.cause = cause;
	this->Send(sizeof(outpacket), (const char*)&outpacket);
}


bool CPC::IsAvoidableImpl(const int in_race, const int in_class, const bool in_bCheckSpecialHiding) // 8178-8221
{
	if( m_pathInfo.m_moveInfo.state == CHARACTER_STATE_DEAD )
		return true;

	if( in_bCheckSpecialHiding && m_characterPInfo.effectState & EFFECTSTATE_SPECIALHIDING )
		return true;

	if( this->GetEffective(EFST_NOACTION, 0) )
		return false;

	if( in_class == NPC_CLASS_BOSS )
		return false;

	if( m_characterPInfo.effectState & (EFFECTSTATE_HIDING | EFFECTSTATE_BURROW) )
	{
		if( this->GetEffective(EFST_CLOAKINGEXCEED, 0) )
			return true;

		if( in_race != RACETYPE_INSECT && in_race != RACETYPE_DEVIL )
			return true;
	}

	if( this->GetEffective(EFST_CAMOUFLAGE, 0) )
	{
		if( in_race != RACETYPE_INSECT && in_race != RACETYPE_DEVIL )
			return true;
	}

	if( CPC::GetCategorySecondJob(m_characterInfo.job) == JT_ROGUE && m_pathInfo.m_moveInfo.state == CHARACTER_STATE_SIT )
	{
		bool param = ( m_pcSkill.CPCSkill::GetSkillLevel(SKID_RG_GANGSTER, FALSE) >= 1 );
		if( this->CPC::IsRightForm(SKID_RG_GANGSTER, m_pathInfo.m_moveInfo.xPos, m_pathInfo.m_moveInfo.yPos, param) )
			return true;
	}

	return false;
}


int CPC::IsAvoidable(int race, int _class, int level) // 8226-8228
{
	return this->CPC::IsAvoidableImpl(race, _class, true);
}


hook_func<void (__stdcall *)()> CPC__IsSkillUsable(EXEPATH(), "CPC::IsSkillUsable");
BOOL CPC::IsSkillUsable(unsigned short SKID) // 8444-8701
{
	BOOL result;
	void* hookptr = CPC__IsSkillUsable;
	__asm push SKID
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


BOOL CPC::IsSkillEnableMapProperty(int SKID) // 8704-8790
{
	if( this->IsItPossible(MAPPROPERTY_TURBOTRACK) )
	{
		switch( SKID )
		{
		case SKID_SM_ENDURE:
		case SKID_AL_WARP:
		case SKID_AL_CURE:
		case SKID_TF_HIDING:
		case SKID_WZ_ICEWALL:
		case SKID_AS_CLOAKING:
		case SKID_MO_BODYRELOCATION:
		case SKID_LK_CONCENTRATION:
		case SKID_LK_BERSERK:
		case SKID_HP_BASILICA:
		case SKID_ST_CHASEWALK:
		case SKID_CG_MOONLIT:
			this->SkillUseAck(SKID, 0, 0, USESKILL_FAIL);
			return FALSE;
		};
	}

	if( SKID == SKID_TK_HIGHJUMP && m_mapRes != NULL && m_mapRes->CMapRes::GetType() == MAPTYPE_AGIT_SIEGEV15 )
	{
		this->SkillUseAck(SKID, 0, 0, USESKILL_FAIL);
		return FALSE;
	}

	if( SKID == SKID_RG_INTIMIDATE && !this->IsItPossible(MAPPROPERTY_TELEPORT) )
	{
		this->SkillUseAck(SKID, 0, 0, USESKILL_FAIL);
		return FALSE;
	}

	if( SKID == SKID_BS_GREED && m_mapRes != NULL && m_mapRes->CMapRes::IsVillage() )
	{
		this->SkillUseAck(SKID, 0, 0, USESKILL_FAIL);
		return FALSE;
	}

	return TRUE;
}


hook_func<void (__stdcall *)()> CPC__IsSkillEnable(EXEPATH(), "CPC::IsSkillEnable");
BOOL CPC::IsSkillEnable(int SKID, int level, CCharacter* ch) // 8795-9505
{
	BOOL result;
	void* hookptr = CPC__IsSkillEnable;
	CCharacter* ch_ = ch;
	__asm push ch_
	__asm push level
	__asm push SKID
	__asm push this
	__asm call hookptr
	__asm mov result, eax
	return result; // TODO
}


hook_func<void (CPC::*)(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY)> CPC__DetectHidingCharacter(EXEPATH(), "CPC::DetectHidingCharacter");
void CPC::DetectHidingCharacter(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY) // 9656-9810
{
	return (this->*CPC__DetectHidingCharacter)(range, msg, plusAttPower, deltaX, deltaY); //TODO
}


void CPC::NotifyUseSkill(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, short level, bool result) // 10063-10076
{
	PACKET_ZC_USE_SKILL outpacket;
	outpacket.PacketType = HEADER_ZC_USE_SKILL;
	outpacket.SKID = SKID;
	outpacket.level = level;
	outpacket.targetAID = targetAID;
	outpacket.srcAID = srcAID;
	outpacket.result = result;
	this->Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


int CPC::GetAttackHasteValue1() // 12639-12661
{
	int result = 0;
	std::vector<int> List;

	if( this->GetEffective(EFST_ATTHASTE_INFINITY, 0) )
		List.push_back(this->GetEffective(EFST_ATTHASTE_INFINITY, 0));
	else
	if( this->GetEffective(EFST_ATTHASTE_POTION3, 0) )
		List.push_back(this->GetEffective(EFST_ATTHASTE_POTION3, 0));
	else
	if( this->GetEffective(EFST_ATTHASTE_POTION2, 0) )
		List.push_back(this->GetEffective(EFST_ATTHASTE_POTION2, 0));
	else
	if( this->GetEffective(EFST_ATTHASTE_POTION1, 0) )
		List.push_back(this->GetEffective(EFST_ATTHASTE_POTION1, 0));

	List.push_back(this->GetEffective(EFST_ATTHASTE_CASH, 0));

	for( std::vector<int>::iterator iter = List.begin(); iter != List.end(); ++iter )
		result += *iter;

	return result;
}


hook_func<int (CPC::*)()> CPC__GetAttackHasteValue2(EXEPATH(), "CPC::GetAttackHasteValue2");
int CPC::GetAttackHasteValue2() // 12686-12717
{
	return (this->*CPC__GetAttackHasteValue2)(); //TODO
/*
	fatsovector<int> List(20);
	int val;

	val = this->GetEffective(EFST_TWOHANDQUICKEN, 0); List.push_back(val);
	val = this->GetEffective(EFST_SPEARQUICKEN, 0) ? 30 : 0; List.push_back(val);
	val = this->GetEffective(EFST_ONEHANDQUICKEN, 0); List.push_back(val);
	val = this->GetEffective(EFST_ADRENALINE, 0); List.push_back(val);
	val = this->GetEffective(EFST_ADRENALINE2, 0); List.push_back(val);
	val = this->GetEffective(EFST_ASSASSINCROSS, 0); List.push_back(val);
	val = this->GetEffective(EFST_DEVIL1, 0) + this->GetEffective(EFST_STAR_COMFORT, 0); List.push_back(val);
	val = this->GetEffective(EFST_GS_MADNESSCANCEL, 0); List.push_back(val);
	val = this->GetEffective(EFST_PSPEED, 0); List.push_back(val);
	val = this->GetEffective(EFST_SWING, 1); List.push_back(val);
	val = this->GetEffective(EFST_DANCE_WITH_WUG, 2); List.push_back(val);
	val = this->GetEffective(EFST_BERSERK, 0) ? 30 : 0; List.push_back(val);

	for( std::map<int,int>::iterator iter = m_AspdHastePercentEfstList.begin(); iter != m_AspdHastePercentEfstList.end(); ++iter )
	{
		val = this->GetEffective(iter->first, iter->second); List.push_back(val);
	}

	return *std::max_element(List.begin(), List.end());
*/
}


void CPC::OnStarPlaceRemember(int par1, int par2, int par3) // 13373-13379
{
	if( m_mapRes == NULL )
		return;

	m_pcSkill.CPCSkill::UpdateStarPlace(m_characterInfo.mapName, par1);
}


int CPC::GetPlusAttRange() // 13442-13444
{
	return m_characterInfo.plusAttRange;
}


void CPC::OnIncCarry(int amount) // 13447-13451
{
	m_pcSkill.CPCSkill::SetPlusItemWeight(amount);
	m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_MAXWEIGHT, this->CPC::GetBodyMaxItemWeight());
	m_pcitemInventoryMgr.CPCItemInventoryMgr::RefreshItemWeight();
}


void CPC::OnIncCarry2(int par1, int par2, int par3) // 13456-13477
{
	const int lvSG_KNOWLEDGE = par3;

	int skLevel = m_pcSkill.CPCSkill::GetSkillLevel(SKID_SG_FEEL, TRUE);
	if( skLevel > 0 )
	{
		int maxWeight = 300 * m_characterInfo.Str + 28000; //FIXME: doesn't agree with CPC::GetBodyMaxItemWeight()

		std::deque<WARP_POSITION>::iterator iter;
		int iCount;

		for( iter = m_pcSkill.m_warpInfo.begin(), iCount = 0; iter != m_pcSkill.m_warpInfo.end() && iCount < skLevel; ++iter, ++iCount )
		{
			if( strcmp(iter->mapName, m_characterInfo.mapName) == 0 )
			{
				int plusItemWeight = int(maxWeight * lvSG_KNOWLEDGE * 10 / 100.);
				m_pcSkill.CPCSkill::SetPlusItemWeight(plusItemWeight);
				break; // found.
			}
		}
	}

	m_pcitemInventoryMgr.CPCItemInventoryMgr::RefreshItemWeight();
}


BOOL CPC::IsMyPartyMember(unsigned long AID) // 13701-13709
{
	for( std::list<unsigned long>::iterator iter = m_groupMember.begin(); iter != m_groupMember.end(); ++iter )
		if( *iter == AID )
			return TRUE; // found.

	return FALSE; // not found.
}


BOOL CPC::IsPKModeON() // 13712-13714
{
	return m_isPKModeON;
}


BOOL CPC::IsRightForm(int SKID, int xPos, int yPos, int param) // 13722-13837
{
	if( m_mapRes == NULL )
		return FALSE;

	NEIGHBORHOOD_SECTION result = {};
	m_mapRes->CMapRes::GetNeighborhoodSections(xPos, yPos, 1, &result);

	int count = 0;

	for( int k = 0; k < countof(result.section); ++k )
	{
		std::vector<CCharacter*>* section = result.section[k];
		if( section == NULL )
			continue;

		for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch == NULL || ch == this || ch->GetType() != PC_TYPE )
				continue;

			CPC* other = static_cast<CPC*>(ch);

			int otherJob = CPC::GetCategorySecondJob(other->m_characterInfo.job);

			int otherXPos, otherYPos;
			other->GetParameterValue(VAR_CURXPOS, otherXPos);
			other->GetParameterValue(VAR_CURYPOS, otherYPos);

			switch( SKID )
			{
			case SKID_NV_BASIC:
			{
				if( xPos == otherXPos && yPos == otherYPos )
					return TRUE;
			}
			break;
			case SKID_DA_ENERGY:
			{
				if( xPos - otherXPos == 3 && yPos == otherYPos
				 || xPos == otherXPos && yPos - otherYPos == 3
				 || xPos - otherXPos == -3 && yPos == otherYPos
				 || xPos == otherXPos && yPos - otherYPos == -3 )
					++count;
				else
					count = 0;

				if( count == 4 )
					return TRUE;
			}
			break;
			case SKID_PR_BENEDICTIO:
			{
				CPC* pc[2];

				if( otherJob == JT_ACOLYTE || otherJob == JT_PRIEST || otherJob == JT_MONK )
				{
					if( xPos - 1 == otherXPos && yPos == otherYPos || xPos + 1 == otherXPos && yPos == otherYPos )
					{
						pc[count] = other;
						++count;
					}
				}

				if( count >= 2 )
				{
					if( pc[0]->CPC::GetSP() < param/2 || pc[1]->CPC::GetSP() < param/2 )
						return FALSE;

					pc[0]->UpdateParameterValue(VAR_SP, -param/2);
					pc[1]->UpdateParameterValue(VAR_SP, -param/2);
					return TRUE;
				}
			}
			break;
			case SKID_RG_GANGSTER:
			{
				if( otherJob != JT_ROGUE )
					break;

				int otherState;
				other->GetParameterValue(VAR_STATE, otherState);

				if( otherState != CHARACTER_STATE_SIT )
					break;

				if( abs(xPos - otherXPos) > 1 || abs(yPos - otherYPos) > 1 )
					break;

				if( param )
					return TRUE;
				else
					return ( other->m_pcSkill.CPCSkill::GetSkillLevel(SKID_RG_GANGSTER, 0) >= 1 );
			}
			break;
			case SKID_BD_LULLABY:
			case SKID_BD_RICHMANKIM:
			case SKID_BD_ETERNALCHAOS:
			case SKID_BD_DRUMBATTLEFIELD:
			case SKID_BD_RINGNIBELUNGEN:
			case SKID_BD_ROKISWEIL:
			case SKID_BD_INTOABYSS:
			case SKID_BD_SIEGFRIED:
			case SKID_CG_MOONLIT:
			{
				if( !this->CPC::IsMyPartyMember(other->GetAccountID()) )
					break;

				int myJob = CPC::GetCategorySecondJob(m_characterInfo.job);
				if( (myJob != JT_BARD || otherJob != JT_DANCER) && (myJob != JT_DANCER || otherJob != JT_BARD) )
					break;

				if( !other->CPC::IsSkillUsable(SKID) )
					break;
				
				if( other->m_pcSkill.CPCSkill::GetSkillLevel(SKID, FALSE) < 1 )
					break;
				
				if( abs(xPos - otherXPos) > 1 || abs(yPos - otherYPos) > 1 )
					break;

				m_pcSkill.m_partnerAID = other->GetAccountID();
				return TRUE;
			}
			break;
			case SKID_TK_HPTIME:
			{
				if( !g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsAvailableJob(otherJob, SKID_TK_HPTIME) )
					break;

				int otherState;
				other->GetParameterValue(VAR_STATE, otherState);

				if( otherState != CHARACTER_STATE_SIT )
					break;

				if( abs(xPos - otherXPos) > 1 || abs(yPos - otherYPos) > 1 )
					break;

				return TRUE;
			}
			break;
			};
		}
	}

	return FALSE;
}


double CPC::GetAttackDistance() // 14040-14052
{
	double distance = (double)m_pcitemInventoryMgr.CPCItemInventoryMgr::GetAttackDistance();

	CITP* itp = m_pcitemInventoryMgr.CPCItemInventoryMgr::GetITPEquipedWeapon();
	if( itp != NULL )
	{
		if( itp->GetClass() == JT_HUNTER || itp->GetType() == JT_MONK )
			distance += this->CPC::GetPlusAttRange();
	}

	return distance;
}


void CPC::NotifyArrowEquiped(unsigned short index) // 14110-14116
{
	PACKET_ZC_EQUIP_ARROW outpacket;
	outpacket.PacketType = HEADER_ZC_EQUIP_ARROW;
	outpacket.index = index;
	this->Send(sizeof(outpacket), (const char*)&outpacket);
}


CITP* CPC::GetITPEquipedWeapon() // 14119-14120
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetITPEquipedWeapon();
}


short CPC::GetEquipedWeaponType() // ???
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipedWeaponType();
}


BOOL CPC::ConsumeItemForSkill(unsigned short itmNum, int count) // 14124-14140
{
	if( itmNum >= ITID_YELLOW_GEMSTONE && itmNum <= ITID_BLUE_GEMSTONE )
	{
		if( m_characterInfo.noJamstone || this->GetEffective(EFST_INTOABYSS, 0) || this->GetEffective(EFST_SOULLINK, 0) == JT_WIZARD )
			return TRUE;
	}

	return this->CPC::ConsumeItem(itmNum, count, NULL, PACKET_ZC_DELETE_ITEM_FROM_BODY::DELETE_TYPE_USE_SKILL);
}


void CPC::OnUseSkill(int SKID, int target, int level, int spCost) // 14158-14239
{
	CSkillTypeInfo* skilltypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( skilltypeInfo == NULL || skilltypeInfo->CSkillTypeInfo::GetType() == SKILLTYPE_TOGROUND )
	{
		this->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( SKID != SKID_SA_CASTCANCEL && SKID != SKID_SO_SPELLFIST && SKID == m_pcSkill.m_spellCastingSKID )
	{
		std::list<COMMAND_QUEUE>::iterator iter;
		for( iter = m_commandQueue.begin(); iter != m_commandQueue.end(); ++iter )
			if( iter->commandID == USE_SKILL_IN && iter->par1 == SKID )
				break; // found

		if( iter == m_commandQueue.end() )
			this->CPC::SetSpellCasting(0, 0);
	}

	if( g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsGuildSkill(SKID) && SKID != SKID_GD_ITEMEMERGENCYCALL )
	{
		g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID, SM_USE_SKILL, level, 0, 0, 0);
		return; // done.
	}

	PC_SKILL_INFO* info = m_pcSkill.CPCSkill::GetSkill(SKID, FALSE);
	if( info != NULL )
	{
		if( info->type == DISPOSABLE_SKILL )
		{
			g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID, SM_USE_SKILL, level, target, 0, 0);
			m_pcSkill.CPCSkill::DeleteSkill(SKID, TRUE);
			return; // done.
		}

		if( info->type == TEMPORARY_DISPOSABLE_SKILL )
		{
			g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID, SM_USE_SKILL, level, target, 0, 0);
			info->type = FIXED_SKILL;
			return; // done.
		}
	}

	if( skilltypeInfo->CSkillTypeInfo::GetType() == SKILLTYPE_TOCHARACTER )
	{
		CCharacter* targetCH = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(target, UNKNOWN_TYPE);
		if( targetCH != NULL )
		{
			int effective = EFST_FOGWALL;
			targetCH->GetParameterValue(VAR_GETEFFECTIVE, effective);

			if( effective != 0 && GetServerRandom(0, 20000) % 100 < 75 )
				return;
		}
	}

	if( this->CActor::IsFailStartUseSkill() )
		return;

	g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID, SM_USE_SKILL, level, target, spCost, 0);
}


void CPC::OnUseGroundSkill(int par1, int par2, int skLevel, int spCost) // 14242-14283
{
	unsigned short SKID = static_cast<unsigned short>(par1);
	MSG_TYPE1_TWODWORD* position = reinterpret_cast<MSG_TYPE1_TWODWORD*>(par2);

	if( SKID == m_pcSkill.m_spellCastingSKID )
		this->CPC::SetSpellCasting(0, 0);

	CSkillTypeInfo* pSkillTypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( pSkillTypeInfo == NULL || pSkillTypeInfo->CSkillTypeInfo::GetType() != SKILLTYPE_TOGROUND )
	{
		this->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	MSG_TYPE1_TWODWORD data;
	data.data1 = position->data1;
	data.data2 = position->data2;

	PC_SKILL_INFO* pSkillInfo = m_pcSkill.CPCSkill::GetSkill(SKID, FALSE);
	if( pSkillInfo != NULL )
	{
		if( pSkillInfo->type == DISPOSABLE_SKILL )
		{
			g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID, SM_USE_SKILL, skLevel, 0, (int)&data, 0);
			m_pcSkill.CPCSkill::DeleteSkill(SKID, TRUE);
			return;
		}

		if( pSkillInfo->type == TEMPORARY_DISPOSABLE_SKILL )
		{
			g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID, SM_USE_SKILL, skLevel, 0, (int)&data, 0);
			pSkillInfo->type = FIXED_SKILL;
			return;
		}
	}

	if( this->CActor::IsFailStartUseSkill() )
		return;

	g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID, SM_USE_SKILL, skLevel, spCost, (int)&data, 0);
}


int CPC::GetMaxHP() // 14359-14415
{
	return 0;
	//TODO
}


short CPC::GetMaxSP() // 14419-14452
{
	return 0;
	//TODO
}


hook_func<void (__stdcall *)()> CPC__OnAddItem(EXEPATH(), "CPC::OnAddItem");
IVItItem* CPC::OnAddItem(int ID, int type, int par, int Hour, bool isUniqueIdentityNumV2, const int in_TimeType) // 14459-14663
{
	IVItItem* result;
	void* hookptr = CPC__OnAddItem;
	int type_ = type;
	__asm movzx eax, isUniqueIdentityNumV2
	__asm push eax
	__asm mov ecx, Hour
	__asm mov edx, par
	__asm push type_
	__asm push ID
	__asm push this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


void CPC::Send(int len, const char* buf) // 15497-15502
{
	if( !this->CPC::IsSendable() )
		return;

	m_lastSendTime = timeGetTime();
	m_asyncStream->CAsyncStream::Send(len, buf);
}


void CPC::ForceSend(int len, char* buf) // 15505-15508
{
	m_lastSendTime = timeGetTime();
	m_asyncStream->CAsyncStream::Send(len, buf);
}


void CPC::OnDispatchClientRequest(Request* request) // 15511-15513
{
	//TODO
	/*
	m_pcitemInventoryMgr.CPCItemInventoryMgr::OnDispatchClientRequest(request);
	*/
}


hook_func<void (__stdcall *)()> CPC__MoveItem(EXEPATH(), "CPC::MoveItem");
void CPC::MoveItem(unsigned char type, short index, int count) // 15516-15531
{
	void* hookptr = CPC__MoveItem;
	unsigned long type_ = type;
	__asm push count
	__asm push index
	__asm push type_
	__asm mov eax, this
	__asm call hookptr
	return; //TODO
/*
	if( !m_pcitemInventoryMgr.CPCItemInventoryMgr::IsMCStoreOpen() )
		return;

	if( !this->CPC::IsItemMovable() )
		return;

	if( m_pcitemInventoryMgr.m_BuyingStore.m_isStoreOpen )
		return;

	m_pcitemInventoryMgr.CPCItemInventoryMgr::MoveItem(type, index, count);
*/
}


void CPC::AddMoney(int money) // 15581-15611
{
	if( m_PCBangInfo.isPCBang == TRUE && g_ForeignCode == FOREIGN_FRANCE && m_PCBangInfo.PremiumType != 0 && m_characterInfo.CharacterInfo::GetMoney() >= 50000 )
		return;

	m_characterInfo.CharacterInfo::AddMoney(money);
	this->CPC::NotifyParameter(VAR_MONEY, 0);
}


void CPC::DeleteMoney(int money) // 15567-15570
{
	m_characterInfo.CharacterInfo::AddMoney(-money);
	if( money <= 0 ) // ???
		return;

	this->CPC::NotifyParameter(VAR_MONEY, 0);
}


int CPC::GetMoney() // ??? (1000.h)
{
	return m_characterInfo.CharacterInfo::GetMoney();
}


void CPC::InitEnemyInfo() // 15614-15616
{
	m_enemyInfo.clear();
}


void CPC::InsertEnemyInfo(ENEMY_INFO* enemyInfo) // 15619-15632
{
	ENEMY_INFO* existingInfo = this->CPC::SearchEnemyInfo(enemyInfo->AID);
	if( existingInfo != NULL )
	{
		existingInfo->attackinglastTime = timeGetTime();
	}
	else
	{
		enemyInfo->attackinglastTime = timeGetTime();
		m_enemyInfo.push_back(*enemyInfo);
	}

	this->CPC::UpdateEnemyInfo();
}


void CPC::UpdateEnemyInfo() // 15635-15645
{
	DWORD CurTM = timeGetTime();
	for( std::vector<ENEMY_INFO>::iterator iter = m_enemyInfo.begin(); iter != m_enemyInfo.end(); )
	{
		if( CurTM > iter->attackinglastTime + 1800 )
		{
			iter = m_enemyInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


ENEMY_INFO* CPC::SearchEnemyInfo(unsigned long AID) // 15648-15656
{
	for( std::vector<ENEMY_INFO>::iterator iter = m_enemyInfo.begin(); iter != m_enemyInfo.end(); ++iter )
		if( iter->AID == AID )
			return &*iter; // found.

	return NULL; // not found.
}


void CPC::NotifyAttackRange() // 15659-15664
{
	PACKET_ZC_ATTACK_RANGE outpacket;
	outpacket.PacketType = HEADER_ZC_ATTACK_RANGE;
	outpacket.currentAttRange = static_cast<short>(this->CPC::GetAttackDistance());
	this->Send(sizeof(outpacket), (const char*)&outpacket);
}


int CPC::GetAttackedMotionTime() // 15673-15680
{
	int result = 4 * (200 - this->CPC::GetAgiValue());
	if( result < 400 )
		result = 400;

	return result;
}


BOOL CPC::IsLucky() // 15687-15694
{
	int rate = this->CPC::GetLukValue() + m_characterInfo.extDodgePercent2 + 10;
	return ( GetServerRandom(0, 20000) % 1000 < rate );
}


void CPC::OnEnableItemMove(BOOL event) // 16080-16085
{
	if( event && (m_eventNo == 0 || !m_makingItemFlag) )
		return;

	m_isItemMovable = TRUE;
}


void CPC::OnDisableItemMove() // 16088-16090
{
	m_isItemMovable = FALSE;
}


void CPC::GetAttackLastTime(time_t& time) // 16148-16152
{
	time_t temptime;
	InterlockedExchange(&temptime, m_characterTimeInfo.AttReqLastTime);
	time = temptime;
}


void CPC::SetAttackLastTime(time_t time) // 16155-16157
{
	InterlockedExchange(&m_characterTimeInfo.AttReqLastTime, time);
}


void CPC::GetLastAttackedTime(time_t& time) // 16160-16164
{
	time_t temptime;
	InterlockedExchange(&temptime, m_characterTimeInfo.LastAttackedTime);
	time = temptime;
}


void CPC::SetLastAttackedTime(time_t time) // 16167-16169
{
	InterlockedExchange(&m_characterTimeInfo.LastAttackedTime, time);
}


BOOL CPC::IsDisconnectable() // 16117-16145
{
	DWORD CurTM = timeGetTime();

	if( this->GetState() == CHARACTER_STATE_DEAD && !this->GetEffective(EFST_TRICKDEAD, 0) )
		return TRUE; // special case

	time_t LastAttackedTime;
	time_t attReqLastTime;
	this->CPC::GetAttackLastTime(attReqLastTime);
	this->CPC::GetLastAttackedTime(LastAttackedTime);

	if( CurTM - attReqLastTime < 4000 || CurTM - LastAttackedTime < 4000 )
		return FALSE;

	if( m_characterPInfo.effectState & (EFFECTSTATE_BURROW | EFFECTSTATE_HIDING) )
		return FALSE;

	if( m_characterPInfo.bodyState == BODYSTATE_FREEZING
	 || m_characterPInfo.bodyState == BODYSTATE_SLEEP
	 || m_characterPInfo.bodyState == BODYSTATE_STONECURSE
	 || m_characterPInfo.bodyState == BODYSTATE_STONECURSE_ING )
		return FALSE;

	return TRUE;
}


BOOL CPC::IsInitingState() // 16882-16909
{
	if( m_pcClientUpdater.CPCClientUpdater::IsSendable() )
	{
		if( m_loadingCompleteTime == 0 )
			return FALSE;

		DWORD CurTM = timeGetTime();

		DWORD timeout = 3000;
		if( this->IsItPossible(MAPPROPERTY_LONG_INSUPERABLE_TIME) )
			timeout = 10000;

		if( CurTM < m_loadingCompleteTime || CurTM > m_loadingCompleteTime + timeout )
		{
			m_loadingCompleteTime = 0;
			return FALSE;
		}
	}

	return TRUE;
}


int CPC::GetPVPWinPoint() // ??? (1048.h)
{
	return m_pvpWinPoint;
}


void CPC::SetPVPWinPoint(int pvpWinPoint) // ??? (1049.h)
{
	m_pvpWinPoint = pvpWinPoint;
}


void CPC::UpdatePVPWinPoint(int winpvpWinPoint) // 16933-16938 (14004-14009)
{
	m_pvpWinPoint += winpvpWinPoint;
	g_mapResMgr.CMapResMgr::UpdateWinPoint(m_mapRes, this->GetAccountID(), m_pvpWinPoint);
}


hook_func<void (__stdcall *)()> CPC__SetPVPRanking(EXEPATH(), "CPC::SetPVPRanking");
void CPC::SetPVPRanking(int ranking) // 16954-16974 (14025-14045)
{
	void* hookptr = CPC__SetPVPRanking;
	__asm mov edi, ranking
	__asm mov esi, this
	__asm call hookptr
	return; //TODO
}


int CPC::GetPVPRanking() // ??? (1052.h)
{
	return m_pvpRanking;
}


void CPC::SetPVPTotal(int total) // ??? (1053.h)
{
	m_pvpTotal = total;
}


int CPC::GetPVPTotal() // ??? (1054.h)
{
	return m_pvpTotal;
}


hook_func<void (__stdcall *)()> CPC__ConsumeItem(EXEPATH(), "CPC::ConsumeItem");
BOOL CPC::ConsumeItem(unsigned short itmNum, int count, IVItItem* p, const short in_DeleteType) // 16988-17006
{
	BOOL result;
	void* hookptr = CPC__ConsumeItem;
	__asm push in_DeleteType
	__asm mov eax, p
	__asm push count
	__asm mov cx, itmNum
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	if( p == NULL )
		p = m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByID(BODY, itmNum);

	if( p == NULL )
		return FALSE;

	if( !m_pcitemInventoryMgr.CPCItemInventoryMgr::DeleteItem(BODY, p->IVItItem::GetIndex(), count) )
		return FALSE;

	this->CPC::NotifyDeleteItemFromBody(p->IVItItem::GetIndex(), count, in_DeleteType);
	return TRUE;
*/
}


BOOL CPC::GetEquipItemCount(unsigned short id, int& value) // 17830-17832 (14802-14803)
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetJustEquipItemCount(id, value);
}


BOOL CPC::IsMapType(int MapType) // ??? (14857-14864)
{
	if( m_mapRes == NULL )
		return FALSE;

	return ( MapType == m_mapRes->CMapRes::GetType() );
}


hook_func<BOOL (CPC::*)(CCharacter* ch, unsigned long flag)> CPC__IsTarget(EXEPATH(), "CPC::IsTarget");
BOOL CPC::IsTarget(CCharacter* ch, unsigned long flag) // 17931-18110 (14870-15007)
{
	return (this->*CPC__IsTarget)(ch, flag); //TODO
}


hook_func<int (CPC::*)()> CPC__GetScale(EXEPATH(), "CPC::GetScale");
int CPC::GetScale() // 18122-18132 (15010-15021)
{
	return (this->*CPC__GetScale)(); //TODO
}


BOOL CPC::IsSiegeMode() // ??? (15025-15027)
{
	return this->IsItPossible(MAPPROPERTY_SIEGE);
}


BOOL CPC::IsReadyToSave() // ??? (15063-15071)
{
	if( !m_isValid )
		return FALSE;

	if( m_pcClientUpdater.m_disconnectType == MOVE_SERVER || m_pcClientUpdater.m_disconnectType == RESTART_HSERVER )
		return FALSE;

	return TRUE;
}


BOOL CPC::ModifyMoney(int money) // 18186-18195 (15075-15084)
{
	int newmoney = m_characterInfo.CharacterInfo::GetMoney() + money;
	if( newmoney < 0 )
		return FALSE;

	m_characterInfo.CharacterInfo::SetMoney(newmoney);
	m_pcClientUpdater.CPCClientUpdater::NotifyLongParameter(VAR_MONEY, newmoney);
	return TRUE;
}


void CPC::SetLastTargetAID(unsigned long aid) // ??? (1128.h)
{
	m_lastTargetAID = aid;
}


unsigned long CPC::GetLastTargetAID() // ??? (1129.h)
{
	return m_lastTargetAID;
}


void CPC::SetOnShowEFST(int value) // 1685.h (1262.h)
{
	m_characterInfo.virtue |= value;
}


void CPC::SetOffShowEFST(int value) // 1686.h (1263.h)
{
	m_characterInfo.virtue &= ~value;
}


DWORD CPC::GetBanTime() // ??? (15201-15203)
{
	return m_nBanTime;
}


void CPC::SetBanTime(DWORD time) // ??? (15206-15209)
{
	if( m_nBanTime == 0 )
		m_nBanTime = time;
}


char* CPC::GetGuildName() // 18547-18556 (15336-15345)
{
	unsigned long GDID = m_characterInfo.GuildID;
	if( GDID == 0 )
		return NULL;

	CGuild* guild = g_ZGuildMgr.CGuildMgr::SearchGuild(GDID);
	if( guild == NULL )
		return NULL;

	return guild->CGuild::GetGuildName();
}


int CPC::GetCountOfMyNameItem(int item) // 18569-18571
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetCountItemOfMyGID(item);
}


hook_func<void (CPC::*)(int SKID, unsigned short type, unsigned long time, int amount)> CPC__OnChangeStatusAmount(EXEPATH(), "CPC::OnChangeStatusAmount");
void CPC::OnChangeStatusAmount(int SKID, unsigned short type, unsigned long time, int amount) // 18575-18645
{
	return (this->*CPC__OnChangeStatusAmount)(SKID, type, time, amount); //TODO
}


hook_func<void (CPC::*)(unsigned short type, int amount)> CPC__NotifyStatusAmount(EXEPATH(), "CPC::NotifyStatusAmount");
void CPC::NotifyStatusAmount(unsigned short type, int amount) // 18648-18714
{
	return (this->*CPC__NotifyStatusAmount)(type, amount); //TODO
}


int CPC::GetJob() // ??? (737.h)
{
	return m_characterInfo.job;
}


int CPC::GetPureJob() // ???
{
	return ::GetPureJob(m_characterInfo.job);
}

int CPC::GetCategoryFirstJob() // 18940-19072
{
	int job = this->CPC::GetJob();
	switch( job )
	{
	case JT_SWORDMAN:
	case JT_KNIGHT:
	case JT_CRUSADER:
	case JT_SWORDMAN_H:
	case JT_KNIGHT_H:
	case JT_CRUSADER_H:
	case JT_SWORDMAN_B:
	case JT_KNIGHT_B:
	case JT_CRUSADER_B:
	case JT_RUNE_KNIGHT:
	case JT_RUNE_KNIGHT_H:
	case JT_ROYAL_GUARD:
	case JT_ROYAL_GUARD_H:
	case JT_RUNE_KNIGHT_B:
	case JT_ROYAL_GUARD_B:
		return JT_SWORDMAN;
	case JT_MAGICIAN:
	case JT_WIZARD:
	case JT_SAGE:
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
	case JT_WARLOCK_B:
	case JT_SORCERER_B:
		return JT_MAGICIAN;
	case JT_ARCHER:
	case JT_HUNTER:
	case JT_BARD:
	case JT_DANCER:
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
	case JT_RANGER_B:
	case JT_MINSTREL_B:
	case JT_WANDERER_B:
		return JT_ARCHER;
	case JT_ACOLYTE:
	case JT_PRIEST:
	case JT_MONK:
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
	case JT_ARCHBISHOP_B:
	case JT_SURA_B:
		return JT_ACOLYTE;
	case JT_MERCHANT:
	case JT_BLACKSMITH:
	case JT_ALCHEMIST:
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
	case JT_MECHANIC_B:
	case JT_GENETIC_B:
		return JT_MERCHANT;
	case JT_THIEF:
	case JT_ASSASSIN:
	case JT_ROGUE:
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
	case JT_GUILLOTINE_CROSS_B:
	case JT_SHADOW_CHASER_B:
		return JT_THIEF;
	case JT_TAEKWON:
	case JT_STAR:
	case JT_STAR2:
	case JT_LINKER:
		return JT_TAEKWON;
	default:
		return JT_NOVICE;
	};
}


int CPC::GetCategorySecondJob(const int in_Job) // 19076-19077
{
	switch( in_Job )
	{
	case JT_NOVICE:
	case JT_NOVICE_H:
	case JT_NOVICE_B:
		return JT_NOVICE;
	case JT_SWORDMAN:
	case JT_SWORDMAN_H:
	case JT_SWORDMAN_B:
		return JT_SWORDMAN;
	case JT_MAGICIAN:
	case JT_MAGICIAN_H:
	case JT_MAGICIAN_B:
		return JT_MAGICIAN;
	case JT_ARCHER:
	case JT_ARCHER_H:
	case JT_ARCHER_B:
		return JT_ARCHER;
	case JT_ACOLYTE:
	case JT_ACOLYTE_H:
	case JT_ACOLYTE_B:
		return JT_ACOLYTE;
	case JT_MERCHANT:
	case JT_MERCHANT_H:
	case JT_MERCHANT_B:
		return JT_MERCHANT;
	case JT_THIEF:
	case JT_THIEF_H:
	case JT_THIEF_B:
		return JT_THIEF;
	case JT_KNIGHT:
	case JT_KNIGHT_H:
	case JT_KNIGHT_B:
	case JT_RUNE_KNIGHT:
	case JT_RUNE_KNIGHT_H:
	case JT_RUNE_KNIGHT_B:
		return JT_KNIGHT;
	case JT_PRIEST:
	case JT_PRIEST_H:
	case JT_PRIEST_B:
	case JT_ARCHBISHOP:
	case JT_ARCHBISHOP_H:
	case JT_ARCHBISHOP_B:
		return JT_PRIEST;
	case JT_WIZARD:
	case JT_WIZARD_H:
	case JT_WIZARD_B:
	case JT_WARLOCK:
	case JT_WARLOCK_H:
	case JT_WARLOCK_B:
		return JT_WIZARD;
	case JT_BLACKSMITH:
	case JT_BLACKSMITH_H:
	case JT_BLACKSMITH_B:
	case JT_MECHANIC:
	case JT_MECHANIC_H:
	case JT_MECHANIC_B:
		return JT_BLACKSMITH;
	case JT_HUNTER:
	case JT_HUNTER_H:
	case JT_HUNTER_B:
	case JT_RANGER:
	case JT_RANGER_H:
	case JT_RANGER_B:
		return JT_HUNTER;
	case JT_ASSASSIN:
	case JT_ASSASSIN_H:
	case JT_ASSASSIN_B:
	case JT_GUILLOTINE_CROSS:
	case JT_GUILLOTINE_CROSS_H:
	case JT_GUILLOTINE_CROSS_B:
		return JT_ASSASSIN;
	case JT_CRUSADER:
	case JT_CRUSADER_H:
	case JT_CRUSADER_B:
	case JT_ROYAL_GUARD:
	case JT_ROYAL_GUARD_H:
	case JT_ROYAL_GUARD_B:
		return JT_CRUSADER;
	case JT_MONK:
	case JT_MONK_H:
	case JT_MONK_B:
	case JT_SURA:
	case JT_SURA_H:
	case JT_SURA_B:
		return JT_MONK;
	case JT_SAGE:
	case JT_SAGE_H:
	case JT_SAGE_B:
	case JT_SORCERER:
	case JT_SORCERER_H:
	case JT_SORCERER_B:
		return JT_SAGE;
	case JT_ROGUE:
	case JT_ROGUE_H:
	case JT_ROGUE_B:
	case JT_SHADOW_CHASER:
	case JT_SHADOW_CHASER_H:
	case JT_SHADOW_CHASER_B:
		return JT_ROGUE;
	case JT_ALCHEMIST:
	case JT_ALCHEMIST_H:
	case JT_ALCHEMIST_B:
	case JT_GENETIC:
	case JT_GENETIC_H:
	case JT_GENETIC_B:
		return JT_ALCHEMIST;
	case JT_BARD:
	case JT_BARD_H:
	case JT_BARD_B:
	case JT_MINSTREL:
	case JT_MINSTREL_H:
	case JT_MINSTREL_B:
		return JT_BARD;
	case JT_DANCER:
	case JT_DANCER_H:
	case JT_DANCER_B:
	case JT_WANDERER:
	case JT_WANDERER_H:
	case JT_WANDERER_B:
		return JT_DANCER;
	case JT_SUPERNOVICE:
	case JT_SUPERNOVICE_B:
	case JT_SUPERNOVICE2:
	case JT_SUPERNOVICE2_B:
		return JT_SUPERNOVICE;
	case JT_TAEKWON:
		return JT_TAEKWON;
	case JT_STAR:
		return JT_STAR;
	case JT_LINKER:
		return JT_LINKER;
	default:
		return in_Job;
	};
}


int CPC::GetCategorySecondJob() // ??? (742.h)
{
	return CPC::GetCategorySecondJob(m_characterInfo.job);
}


int CPC::GetCategoryThirdJob() // 19081-19278
{
	int job = this->CPC::GetJob();
	switch( job )
	{
	case JT_NOVICE:
	case JT_NOVICE_H:
	case JT_NOVICE_B:
		return JT_NOVICE;
	case JT_SWORDMAN:
	case JT_SWORDMAN_H:
	case JT_SWORDMAN_B:
		return JT_SWORDMAN;
	case JT_MAGICIAN:
	case JT_MAGICIAN_H:
	case JT_MAGICIAN_B:
		return JT_MAGICIAN;
	case JT_ARCHER:
	case JT_ARCHER_H:
	case JT_ARCHER_B:
		return JT_ARCHER;
	case JT_ACOLYTE:
	case JT_ACOLYTE_H:
	case JT_ACOLYTE_B:
		return JT_ACOLYTE;
	case JT_MERCHANT:
	case JT_MERCHANT_H:
	case JT_MERCHANT_B:
		return JT_MERCHANT;
	case JT_THIEF:
	case JT_THIEF_H:
	case JT_THIEF_B:
		return JT_THIEF;
	case JT_KNIGHT:
	case JT_KNIGHT_H:
	case JT_KNIGHT_B:
		return JT_KNIGHT;
	case JT_PRIEST:
	case JT_PRIEST_H:
	case JT_PRIEST_B:
		return JT_PRIEST;
	case JT_WIZARD:
	case JT_WIZARD_H:
	case JT_WIZARD_B:
		return JT_WIZARD;
	case JT_BLACKSMITH:
	case JT_BLACKSMITH_H:
	case JT_BLACKSMITH_B:
		return JT_BLACKSMITH;
	case JT_HUNTER:
	case JT_HUNTER_H:
	case JT_HUNTER_B:
		return JT_HUNTER;
	case JT_ASSASSIN:
	case JT_ASSASSIN_H:
	case JT_ASSASSIN_B:
		return JT_ASSASSIN;
	case JT_CRUSADER:
	case JT_CRUSADER_H:
	case JT_CRUSADER_B:
		return JT_CRUSADER;
	case JT_MONK:
	case JT_MONK_H:
	case JT_MONK_B:
		return JT_MONK;
	case JT_SAGE:
	case JT_SAGE_H:
	case JT_SAGE_B:
		return JT_SAGE;
	case JT_ROGUE:
	case JT_ROGUE_H:
	case JT_ROGUE_B:
		return JT_ROGUE;
	case JT_ALCHEMIST:
	case JT_ALCHEMIST_H:
	case JT_ALCHEMIST_B:
		return JT_ALCHEMIST;
	case JT_BARD:
	case JT_BARD_H:
	case JT_BARD_B:
		return JT_BARD;
	case JT_DANCER:
	case JT_DANCER_H:
	case JT_DANCER_B:
		return JT_DANCER;
	case JT_SUPERNOVICE:
	case JT_SUPERNOVICE_B:
	case JT_SUPERNOVICE2:
	case JT_SUPERNOVICE2_B:
		return JT_SUPERNOVICE;
	case JT_TAEKWON:
		return JT_TAEKWON;
	case JT_STAR:
		return JT_STAR;
	case JT_LINKER:
		return JT_LINKER;
	case JT_RUNE_KNIGHT:
	case JT_RUNE_KNIGHT_H:
	case JT_RUNE_KNIGHT_B:
		return JT_RUNE_KNIGHT;
	case JT_ARCHBISHOP:
	case JT_ARCHBISHOP_H:
	case JT_ARCHBISHOP_B:
		return JT_ARCHBISHOP;
	case JT_WARLOCK:
	case JT_WARLOCK_H:
	case JT_WARLOCK_B:
		return JT_WARLOCK;
	case JT_MECHANIC:
	case JT_MECHANIC_H:
	case JT_MECHANIC_B:
		return JT_MECHANIC;
	case JT_RANGER:
	case JT_RANGER_H:
	case JT_RANGER_B:
		return JT_RANGER;
	case JT_GUILLOTINE_CROSS:
	case JT_GUILLOTINE_CROSS_H:
	case JT_GUILLOTINE_CROSS_B:
		return JT_GUILLOTINE_CROSS;
	case JT_ROYAL_GUARD:
	case JT_ROYAL_GUARD_H:
	case JT_ROYAL_GUARD_B:
		return JT_ROYAL_GUARD;
	case JT_SURA:
	case JT_SURA_H:
	case JT_SURA_B:
		return JT_SURA;
	case JT_SORCERER:
	case JT_SORCERER_H:
	case JT_SORCERER_B:
		return JT_SORCERER;
	case JT_SHADOW_CHASER:
	case JT_SHADOW_CHASER_H:
	case JT_SHADOW_CHASER_B:
		return JT_SHADOW_CHASER;
	case JT_GENETIC:
	case JT_GENETIC_H:
	case JT_GENETIC_B:
		return JT_GENETIC;
	case JT_MINSTREL:
	case JT_MINSTREL_H:
	case JT_MINSTREL_B:
		return JT_MINSTREL;
	case JT_WANDERER:
	case JT_WANDERER_H:
	case JT_WANDERER_B:
		return JT_WANDERER;
	default:
		return job;
	};
}


void CPC::OnShowEffect(int effect) // 20098-20105
{
	PACKET_ZC_NOTIFY_EFFECT2 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_EFFECT2;
	outpacket.AID = this->GetAccountID();
	outpacket.effectID = effect;
	this->Send(sizeof(outpacket), (const char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CPC::OnShowEffect3(int effect, int numdata) // 20108-20116
{
	PACKET_ZC_NOTIFY_EFFECT3 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_EFFECT3;
	outpacket.AID = this->GetAccountID();
	outpacket.effectID = effect;
	outpacket.numdata = numdata;
	this->Send(sizeof(outpacket), (const char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CPC::OnShowScript(const char* In_Msg) // 20125-20137
{
	CVarLenPacketPtr<PACKET_ZC_SHOWSCRIPT,128> packet;
	packet->PacketType = HEADER_ZC_SHOWSCRIPT;
	packet->AID = this->GetAccountID();
	const int len = strlen(In_Msg) + 1;
	packet.add((const BYTE*)In_Msg, min(len,128));
	packet->PacketLength = packet.size();
	this->Send(packet->PacketLength, (const char*)packet);
	this->CCharacter::MultiCast((char*)packet, packet->PacketLength);
}


hook_func<void (__stdcall *)()> CPC__OnMakeFamily(EXEPATH(), "CPC::OnMakeFamily");
void CPC::OnMakeFamily(unsigned long gid1, unsigned long gid2) // 20596-20654
{
	void* hookptr = CPC__OnMakeFamily;
	__asm push gid2
	__asm push gid1
	__asm mov edi, this
	__asm call hookptr
	return; //TODO
}


bool CPC::Divorce() // 21265-21281
{
	if( !m_marriageInfo.bMarried )
		return false;

	CDeleteCoupleADBWork* cpWork = new(std::nothrow) CDeleteCoupleADBWork(this->GetAccountID(), this->CPC::GetCharacterID());
	if( cpWork == NULL )
		return true;

	if( NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(cpWork) != true )
	{
		delete cpWork;
		return true;
	}

	this->SetEffective(EFST_NOACTION_WAIT, 40000, cpWork->NAsyncDBWork::GetIdentity(), cpWork->NAsyncDBWork::GetType(), timeGetTime(), 0);
	return true;
}


namespace {
std::vector<unsigned short> GetRingItemList() // 21331-21336
{
	std::vector<unsigned short> result;
	result.push_back(ITID_BRIDEGROOM_RING);
	result.push_back(ITID_BRIDE_RING);
	return result;
}
}; // namespace


void CPC::DeleteMarriagering() // 21339-21401
{
	static std::vector<unsigned short> RingItemList = GetRingItemList();
	static int wedding_sign; // ???

	memset(&m_marriageInfo, 0, sizeof(m_marriageInfo));

	for( std::vector<unsigned short>::iterator iter = RingItemList.begin(); iter != RingItemList.end(); ++iter )
	{
		unsigned short ITID = *iter;

		IVItItem* ring = m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByID(EQUIPMENT, ITID);
		if( ring != NULL )
		{
			Request request;
			request.par1 = ring->IVItItem::GetIndex();
			request.Request::SetID(RT_REQ_TAKEOFFEQUIP);
			this->CPC::OnDispatchClientRequest(&request);
		}

		if( m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByID(BODY, ITID) )
		{
			this->UpdateBodyItemCountByNPC(ITID, -1, false);
			m_pcitemInventoryMgr.CPCItemInventoryMgr::OnSetBodyItem(0, 3112, 0); //FIXME: invalid ITID
		}
	}
}


void CPC::NotifyDivorce(unsigned long gid, char* partnerName) // 21406-21417
{
	if( strlen(partnerName) == 0 )
		return;

	PACKET_ZC_DIVORCE outpacket;
	outpacket.PacketType = HEADER_ZC_DIVORCE;
	memcpy_s(outpacket.name, sizeof(outpacket.name), partnerName, 24);
	this->Send(sizeof(outpacket), (const char*)&outpacket);

	if( this->GetEffectState() & EFFECTSTATE_MARRIED )
		this->ResetEffectState(EFFECTSTATE_MARRIED);
}


PARTNER_INFO* CPC::GetMarriedInfo() // (1116.h)
{
	return &m_marriageInfo;
}


void CPC::GetEfstListDBFmt_And_UpdateResetFlag(std::vector<Effect3rd::tagEffect3rdDBFmt>& io_List, const bool in_bKeepDeleteDBWhenResetFlag) // 22094-22157
{
	//TODO
/*
	DWORD CurTM = timeGetTime();

	for( EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.begin(); iter != m_effectiveList.end(); ++iter )
	{
		int hEfst = iter->first;
		EFFECTIVE_INFO data = iter->second;

		if( !EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::IsSave(CurTM, hEfst, &data) )
			continue;

		if( hEfst == EFST_MACRO_PERMIT )
		{
			EFFECTIVE_INFO* info = this->CActor::GetEffectiveInfo(EFST_MACRO_PLAY);
			if( info != NULL && info->val[0] != 0 )
			{
				DWORD delta = timeGetTime() - info->val[0];
				data.val[0] = ( delta < data.val[0] ) ? data.val[0] - delta : 0;
			}
		}

		DWORD TimeMS = ( data.time != 9999 ) ? data.time - CurTM : 0;
		if( TimeMS == 9999 )
			TimeMS = 9998;

		io_List.push_back(Effect3rd::tagEffect3rdDBFmt(hEfst, TimeMS, data.val[0], data.val[1], data.val[2]);

		if( !in_bKeepDeleteDBWhenResetFlag )
			iter->second.bDeleteDBWhenReset = TRUE;
	}
*/
}


char* CPC::GetRestartMapName() // 22610-22619
{
	return m_characterInfo.restartMapName;
}


void CPC::OnCM_NOTIFY_STOREDITEM() // 22740-22782
{
	//TODO
}


BOOL CPC::isBodyAddMailItem(unsigned short ITID, unsigned long ItemType, int count, EQUIPSLOTINFO slotInfo, __int64 UniqueSerialNum) // 23119-23121
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::isBodyAddMailItem(ITID, ItemType, count, slotInfo, UniqueSerialNum);
}


BOOL CPC::PutInventoryBinaryItem(char* ItemBuffer, int ItemLen) // 23124-23126
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::PutMailBinaryItem(ItemBuffer, ItemLen);
}


void CPC::SetMapLoadingFlag(BOOL bFlag) // 23232-23239
{
	m_invalidPacket = 0;
	m_isMapLoading = bFlag;
	if( bFlag == TRUE )
		m_MapLoadingTick = timeGetTime();
}


void CPC::SetLastCardIndex(short index) // ??? (2120.h)
{
	m_lastCardIndex = index;
}


short CPC::GetLastCardIndex() // ??? (2121.h)
{
	return m_lastCardIndex;
}


void CPC::SetMyPetID(int ID) // ??? (2172.h)
{
	m_myPetID = ID;
}


int CPC::GetMyPetID() // ??? (2173.h)
{
	return m_myPetID;
}


BOOL CPC::isAuctionOpen() // (2261.h)
{
	return m_isAuctionOpen;
}


BOOL CPC::isMailOpen()
{
	return m_isMailOpen;
}


void CPC::AuctionOpen() // 23242-23257
{
	PACKET_ZC_AUCTION_WINDOWS outpacketme;
	outpacketme.PacketType = HEADER_ZC_AUCTION_WINDOWS;
	outpacketme.Type = PACKET_ZC_AUCTION_WINDOWS::TYPE_OPEN;
	m_isAuctionOpen = TRUE;
	this->Send(sizeof(outpacketme), (char*)&outpacketme);
}


void CPC::MailOpen() // 23260-23276
{
	PACKET_ZC_MAIL_WINDOWS outpacketme;
	outpacketme.PacketType = HEADER_ZC_MAIL_WINDOWS;
	outpacketme.Type = PACKET_ZC_MAIL_WINDOWS::TYPE_OPEN;
	m_isMailOpen = TRUE;
	this->Send(sizeof(outpacketme), (char*)&outpacketme);
}


void CPC::SetLastOpenMailName(char* FromName) // 23287-23289
{
	memcpy_s(m_characterInfo.LastOpenMailFromName, sizeof(m_characterInfo.LastOpenMailFromName), FromName, 24);
}


IVItItem* CPC::SearchItemByUniqueIdentityNum(const enumInventoryType in_InventoryType, const __int64 in_UID) // 24259-24261
{
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByUniqueIdentityNum(in_InventoryType, in_UID);
}


bool CPC::IsDeadState() // 24374-24379
{
	if( this->GetState() != CHARACTER_STATE_DEAD )
		return false;
	
	if( this->GetEffective(EFST_TRICKDEAD, 0) )
		return false;

	return true;
}


void CPC::ReduceSPByUseSkill(int sp) // ??? (19862-19864)
{
	this->UpdateParameterValue(VAR_SP, -sp);
}


bool CPC::IsExistItem(int itemID, int count, bool isExternalEffect) // 24588-24604 (19867-19883)
{
	if( isExternalEffect )
	{
		if( itemID >= ITID_YELLOW_GEMSTONE && itemID <= ITID_BLUE_GEMSTONE )
		{
			if( m_characterInfo.noJamstone || this->GetEffective(EFST_INTOABYSS, 0) || this->GetEffective(EFST_SOULLINK, 0) == JT_WIZARD )
				return true;
		}
	}

	return ( count <= this->CPC::GetItemCount(itemID) );
}


bool CPC::ConsumeItemByUseSkill(int itemID, int count, bool isExternalEffect) // 24607-24613
{
	if( isExternalEffect )
		return ( this->CPC::ConsumeItemForSkill(itemID, count) == TRUE );
	else
		return ( this->CPC::ConsumeItem(itemID, count, NULL, PACKET_ZC_DELETE_ITEM_FROM_BODY::DELETE_TYPE_NORMAL) == TRUE );
}


hook_func<bool (CPC::*)(int index, int& SKID, bool& isPlaySolo)> CPC__IsGroundEffective(EXEPATH(), "CPC::IsGroundEffective");
bool CPC::IsGroundEffective(int index, int& SKID, bool& isPlaySolo) // 24617-24680
{
	return (this->*CPC__IsGroundEffective)(index, SKID, isPlaySolo); //TODO
}


hook_func<void (CPC::*)(int index, int SKID, bool isPlaySolo)> CPC__ProcessGroundEffective(EXEPATH(), "CPC::ProcessGroundEffective");
void CPC::ProcessGroundEffective(int index, int SKID, bool isPlaySolo) // 24683-	24702
{
	return (this->*CPC__ProcessGroundEffective)(index, SKID, isPlaySolo); //TODO
}


void CPC::TransferSKILLtoPARTYmember(CCharacter* const in_TransferCH, const int in_SKID, const int in_SKLevel, const int in_EFST, const int in_EFST_Time, const int in_EFST_Value) // 24794-24820
{
	//TODO
}


void CPC::ScriptTimeClear() // 25295-25297
{
	m_scriptTimeMap.clear();
}


void CPC::SetScriptTime(int key) // 25300-25304
{
	m_scriptTimeMap.erase(key);
	m_scriptTimeMap.insert(std::make_pair(key, timeGetTime()));
}


int CPC::GetScriptTime(int key) // 25307-25320
{
	std::map<int,unsigned long>::iterator iter = m_scriptTimeMap.find(key);
	if( iter == m_scriptTimeMap.end() )
		return -1;

	return iter->second;
}


void CPC::GetDBInfo(const int in_callfunc, CHARINFO_TO_CHARACTERDB& io_DBInfo) // 25332-25487
{
	//TODO
}


int CPC::GetStoreItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes) // 25499-25500
{
	return 0; //TODO
	/*
	return m_pcitemInventoryMgr.CPCItemInventoryMgr::GetStoreItemDBFormat(out_pBuffer, in_MaxBytes);
	*/
}


void CPC::AsyncSaveCart() // 25507-25555
{
	//TODO
/*
	if( !m_pcitemInventoryMgr.m_cartItem.m_isFirstCartOn )
		return;

	CSaveCartADBWork* work = CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::Get();
	if( work == NULL )
		return;

	work->CSaveCartADBWork::Init(this->GetAccountID(), this->CPC::GetCharacterID());
	work->m_Length = m_pcitemInventoryMgr->CPCItemInventoryMgr::GetCartItemDBFormat(work->m_Data, sizeof(work->m_Data));
	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
		CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::Put(work);
*/
}


void CPC::AsyncSaveStore(const bool in_bCloseStore) // 25608-25665
{
	//TODO
}


void CPC::AsyncSaveBodyItem() // 25684-25738 (20682-20696)
{
	//TODO
}


hook_func<int (CPC::*)(CCharacter* target)> CPC__GetModifiedTargetItemDEF(EXEPATH(), "CPC::GetModifiedTargetItemDEF");
int CPC::GetModifiedTargetItemDEF(CCharacter* target) // 25741-25765 (20699-20717)
{
	return (this->*CPC__GetModifiedTargetItemDEF)(target); //TODO
}


hook_func<int (CPC::*)(CCharacter* in_cpTargetCH)> CPC__GetModifiedTargetItemMDEF2(EXEPATH(), "CPC::GetModifiedTargetItemMDEF2");
int CPC::GetModifiedTargetItemMDEF2(CCharacter* in_cpTargetCH) // 25769-25797
{
	return (this->*CPC__GetModifiedTargetItemMDEF2)(in_cpTargetCH); //TODO
}


hook_func<int (CPC::*)(CCharacter* target)> CPC__GetModifiedTargetItemMDEF(EXEPATH(), "CPC::GetModifiedTargetItemMDEF");
int CPC::GetModifiedTargetItemMDEF(CCharacter* target) // 25801-25823 (20742-20760)
{
	return (this->*CPC__GetModifiedTargetItemMDEF)(target); //TODO
}


void CPC::AsyncSaveALL_AFTER_ACTION_ANYTIME() // ??? (20765-20799)
{
	//TODO
}


void CPC::AsyncSaveALL_AFTER_ACTION_NONE() // 25853-25896 (20805-20849)
{
	//TODO
}


void CPC::AsyncSaveALL_AFTER_ACTION_XXX() // 25901-25921 (20854-20889)
{
	//TODO
}


void CPC::AsyncSaveCharacterInfo(const int in_callfunc) // 25926-25935
{
	//TODO
}


void CPC::UpdateBattleFieldRespawnPoint2(short xPos, short yPos) // (1301.h)
{
	m_battleFieldInfo.xPos2 = xPos;
	m_battleFieldInfo.yPos2 = yPos;
}


void CPC::MoveToBattleFieldRespawnPoint(short RP_No, unsigned long npcID) // 26067-26086 (21002-21021)
{
	MS_MAPMOVE outpar;
	outpar.AID = npcID;
	strcpy(outpar.mapName, m_characterInfo.mapName);

	if( RP_No == 2 && m_battleFieldInfo.xPos2 != 0 && m_battleFieldInfo.yPos2 != 0 )
	{
		outpar.xPos = m_battleFieldInfo.xPos2;
		outpar.yPos = m_battleFieldInfo.yPos2;
	}
	else
	{
		outpar.xPos = m_battleFieldInfo.xPos1;
		outpar.yPos = m_battleFieldInfo.yPos1;
	}

	this->OnMsg(NULL, this, CM_MAPMOVE, (int)&outpar, VT_TELEPORT, 0, 0);
}


hook_func<void (CPC::*)(unsigned short SKID, unsigned long delaytime)> CPC__SetSkillSinglePostDelay(EXEPATH(), "CPC::SetSkillSinglePostDelay");
void CPC::SetSkillSinglePostDelay(unsigned short SKID, unsigned long delaytime) // 26194-26208
{
	return (this->*CPC__SetSkillSinglePostDelay)(SKID, delaytime); //TODO
}


hook_func<void (__stdcall *)()> CPC__OnStopedProgress(EXEPATH(), "CPC::OnStopedProgress");
void CPC::OnStopedProgress() // 26244-26280
{
	void* hookptr = CPC__OnStopedProgress;
	__asm mov ebx, this
	__asm call hookptr;
	return; //TODO
}


void CPC::SendQuestNotifyEffect(unsigned long npcID, short xPos, short yPos, short effect, short type) // 26990-27002
{
	PACKET_ZC_QUEST_NOTIFY_EFFECT packet;
	packet.PacketType = HEADER_ZC_QUEST_NOTIFY_EFFECT;
	packet.npcID = npcID;
	packet.xPos = xPos;
	packet.yPos = yPos;
	packet.effect = effect;
	packet.type = type;
	this->Send(sizeof(packet), (char*)&packet);
}


bool CPC::SetAsyncMonopolyProcess(std::tr1::shared_ptr<CAsyncMonopolyProcess>& in_Amp) // 27029-27040
{
	if( m_AsyncMonopolyProcessPtr.get() != NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "async monopoly process error");
		return false;
	}

	m_AsyncMonopolyProcessPtr = in_Amp;
	return true;
}


AsyncMonopolyProcess::enumType CPC::GetAsyncMonopolyProcessType() const // 27048-27050
{
	CAsyncMonopolyProcess* pProcess = m_AsyncMonopolyProcessPtr.get();
	if( pProcess == NULL )
		return AsyncMonopolyProcess::TYPE_NONE;

	return pProcess->CAsyncMonopolyProcess::GetType();
}


bool CPC::AsyncMonopolyProcess() // 27057-27064
{
	CAsyncMonopolyProcess* pProcess = m_AsyncMonopolyProcessPtr.get();
	if( pProcess == NULL )
		return false;

	if( !pProcess->operator()() )
		m_AsyncMonopolyProcessPtr.reset();

	return true;
}


int CPC::GetAdditionalSkillSPCost(const int in_SkillID) // 27087-27089
{
	return m_pcBattle.CPCBattle::GetAdditionalSkillSPCost(in_SkillID);
}


void CPC::NotifyDeleteItemFromBody(const unsigned short in_Index, const short in_Count, const short in_DeleteType) // 27092-27106
{
	PACKET_ZC_DELETE_ITEM_FROM_BODY Outpacket;
	Outpacket.PacketType = HEADER_ZC_DELETE_ITEM_FROM_BODY;
	Outpacket.DeleteType = in_DeleteType;
	Outpacket.Index = in_Index;
	Outpacket.Count = in_Count;
	this->Send(sizeof(Outpacket), (const char*)&Outpacket);

	m_pcitemInventoryMgr.CPCItemInventoryMgr::RefreshItemWeight();
}


void CPC::CancelCasting(BOOL flag) // 5803-5828 (PC2_2(1).cpp)
{
	if( !flag )
	{
		if( m_pcSkill.m_spellCastingSKID == 0 )
			return;

		CSkillTypeInfo* pSkillTypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(m_pcSkill.m_spellCastingSKID);

		if( pSkillTypeInfo->CSkillTypeInfo::GetFlag() & SKFLAG_NODISPEL )
			return;

		if( pSkillTypeInfo->CSkillTypeInfo::IsPossibleDispel() != 0 )
			return;
	}

	this->CPC::SetSpellCasting(0, 0);
	m_magicTargetAID = 0;
	this->DisableCommand(USE_SKILL_IN);
	this->DisableCommand(USE_GROUNDSKILL_IN);

	PACKET_ZC_DISPEL outpacket;
	outpacket.PacketType = HEADER_ZC_DISPEL;
	outpacket.AID = this->GetAccountID();
	this->Send(sizeof(outpacket), (const char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CPC::SetSpellCasting(unsigned short SKID, short skLevel) // 5831-5843 (PC2_2(1).cpp)
{
	m_pcSkill.m_spellCastingSKID = SKID;
	m_pcSkill.m_spellCastingSKLevel = skLevel;

	if( m_pcSkill.CPCSkill::GetSkillLevel(SKID_SA_FREECAST, FALSE) || m_pcSkill.CPCSkill::GetSkillLevel(SKID_LG_EXEEDBREAK, FALSE) )
	{
		this->UpdateParameterValue(VAR_ASPD, 0);
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
	}
}


unsigned short CPC::GetSpellCasting()
{
	return m_pcSkill.m_spellCastingSKID;
}


hook_func<void (CPC::*)(CCharacter* ch, int attackProperty, int& damage)> CPC__ModifyAttackPowerByEffective(EXEPATH(), "CPC::ModifyAttackPowerByEffective");
void CPC::ModifyAttackPowerByEffective(CCharacter* ch, int attackProperty, int& damage) // 6599-6666 (PC2_2(1).cpp)
{
	return (this->*CPC__ModifyAttackPowerByEffective)(ch, attackProperty, damage); //TODO
}


void CPC::NotifySpiritsInfo() // 6812-6823 (PC2_2(1).cpp)
{
	PACKET_ZC_SPIRITS outpacket;
	outpacket.PacketType = HEADER_ZC_SPIRITS;
	outpacket.AID = this->GetAccountID();
	outpacket.num = m_pcSkill.CPCSkill::GetNumOfSpirits();
	this->Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


hook_func<int (CPC::*)(int index, int time, int val1, int val2, int val3, int isSendClient)> CPC__SetEffective(EXEPATH(), "CPC::SetEffective");
int CPC::SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient) // 8003-9697 (PC2_2(1).cpp)
{
	return (this->*CPC__SetEffective)(index, time, val1, val2, val3, isSendClient);

	//TODO
}


hook_func<void (CPC::*)(int index, int val)> CPC__ResetEffective(EXEPATH(), "CPC::ResetEffective");
void CPC::ResetEffective(int index, int val) // 9703-11090 (PC2_2(1).cpp)
{
	return (this->*CPC__ResetEffective)(index, val);

	//TODO
}


void CPC::AM_ReqMakingHomun() // 3548-3561 (PC2_2(2).cpp)
{
	if( !this->CPC::ConsumeItem(ITID_GREAT_NATURE, 1, 0, 0)
	 || !this->CPC::ConsumeItem(ITID_IRON, 1, 0, 0)
	 || !this->CPC::ConsumeItem(ITID_STEEL, 1, 0, 0) )
		return;

	short skLevel = m_pcSkill.CPCSkill::GetSkillLevel(SKID_AM_CULTIVATION, 0);
	g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(NULL, SKID_AM_CULTIVATION, SM_GETINFO_SKILL, skLevel, 0, 0, 0);

	//NOTE: strangeness
	this->CPC::GetLukValue();
	GetServerRandom(0, 20000);
}


void CPC::ReqItemRepair(const REPAIRITEM_INFO& in_TargetItemInfo) // 3568-3610 (PC2_2(2).cpp)
{
	CPC* pPC = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_pcSkill.m_weaponMasterAID, PC_TYPE);
	if( pPC == NULL )
		return;

	if( pPC->m_isMapLoading == TRUE )
		return;

	PACKET_ZC_ACK_ITEMREPAIR outpacket;
	outpacket.PacketType = HEADER_ZC_ACK_ITEMREPAIR;
	outpacket.index = in_TargetItemInfo.index;
	outpacket.result = PACKET_ZC_ACK_ITEMREPAIR::ITEMREPAIR_FAIL;

	do { // scope

	if( in_TargetItemInfo.index == -1 )
		break;

	IVItItem* item = pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItem(BODY, in_TargetItemInfo.index);
	if( item == NULL )
		break;

	if( in_TargetItemInfo.ITID != item->InventoryItem::GetID()
	 || item->GetType() != INVENTORYITEMTYPE_EQUIPITEM
	 || in_TargetItemInfo.refiningLevel != static_cast<IVItEquipItem*>(item)->IVItEquipItem::GetRefiningLevel()
	 || memcmp(&in_TargetItemInfo.slot, &item->m_slotInfo, sizeof(EQUIPSLOTINFO)) != 0 )
		break;

	CITP* itp = g_itpMgr.CITPMgr::GetITP(item->InventoryItem::GetID());
	if( itp == NULL )
		break;

	int level = itp->GetItemLevel();
	if( level < 1 || level > 5 )
		level = 5;

	int stuff[5];
	stuff[0] = ITID_IRON_ORE;
	stuff[1] = ITID_IRON;
	stuff[2] = ITID_STEEL;
	stuff[3] = ITID_ORIDECON_STONE;
	stuff[4] = ITID_STEEL;

	if( !this->IsMyArea(pPC, 2) )
		break;

	if( !this->CPC::ConsumeItem(stuff[level - 1], 1, NULL, PACKET_ZC_DELETE_ITEM_FROM_BODY::DELETE_TYPE_NORMAL) )
		break;

	static_cast<IVItEquipItem*>(item)->IVItEquipItem::SetDamageFlag(false);
	pPC->m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyItemInfo(BODY);
	outpacket.result = PACKET_ZC_ACK_ITEMREPAIR::ITEMREPAIR_SUCCESS;

	} while( 0 ); // scope

	pPC->Send(sizeof(outpacket), (char*)&outpacket);

	pPC->CPC::OnEnableItemMove(TRUE);
	m_pcSkill.m_weaponMasterAID = 0;
}


hook_func<void (__stdcall *)()> CPC__ReqWeaponRefine(EXEPATH(), "CPC::ReqWeaponRefine");
void CPC::ReqWeaponRefine(short index) // 3652-3798 (PC2_2(2).cpp)
{
	void* hookptr = CPC__ReqWeaponRefine;
	__asm mov dx, index
	__asm mov ecx, this
	__asm call hookptr
	return; //TODO
}


void CPC::ForceMapMove_To_RestartMap() // 3803-3810 (PC2_2(2).cpp)
{
	MS_MAPMOVE par1 = {};
	par1.MS_MAPMOVE::Set(m_characterInfo.restartMapName, m_characterInfo.sxPos, m_characterInfo.syPos, 0);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, this, CM_MAPMOVE, (int)&par1, VT_OUTOFSIGHT, 0, 0);
}


hook_func<int (CPC::*)(const int in_SKID, const int in_SKLevel, const int in_SKType, CSkillTypeInfo* in_cpSKTypeInfo)> CPC__GetSPcostForSkill(EXEPATH(), "CPC::GetSPcostForSkill");
int CPC::GetSPcostForSkill(const int in_SKID, const int in_SKLevel, const int in_SKType, CSkillTypeInfo* in_cpSKTypeInfo) // 3859-4034 (PC2_2(2).cpp)
{
	return (this->*CPC__GetSPcostForSkill)(in_SKID, in_SKLevel, in_SKType, in_cpSKTypeInfo);
	//TODO
}


hook_func<void (CPC::*)(const int selectedItemID)> CPC__NC_MAGICDECOY_operate(EXEPATH(), "CPC::NC_MAGICDECOY_operate");
void CPC::NC_MAGICDECOY_operate(const int selectedItemID) // 135-210 (PC3rd1_Mechanic.cpp)
{
	return (this->*CPC__NC_MAGICDECOY_operate)(selectedItemID);
	//TODO
}


CNpcElemental* CPC::GetNpcElemental() const // 1274-1280 (PC3rd2_Sorcerer.cpp)
{
	unsigned long elementalAID = m_Elemental.CPCElemental::GetAID();
	if( elementalAID == 0 )
		return NULL;

	CNPC* cpNPC = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(elementalAID, NPC_TYPE);
	if( cpNPC == NULL || cpNPC->GetType() != NPC_ELEMENTAL_TYPE )
		return NULL;

	CNpcElemental* cpNpcElemental = static_cast<CNpcElemental*>(cpNPC);
	return cpNpcElemental;
}


hook_func<void (__stdcall *)()> CPC__GC_POISONINGWEAPONoperation(EXEPATH(), "CPC::GC_POISONINGWEAPONoperation");
void CPC::GC_POISONINGWEAPONoperation(const int in_itemID) // 799-830 (PC3rd1_sun.cpp)
{
	void* hookptr = CPC__GC_POISONINGWEAPONoperation;
	__asm push in_itemID
	__asm mov edi, this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPC__WL_READING_SBoperation(EXEPATH(), "CPC::WL_READING_SBoperation");
void CPC::WL_READING_SBoperation(const int in_itemID) // 116-178 (PC3rd1_Warlock.cpp)
{
	void* hookptr = CPC__WL_READING_SBoperation;
	__asm push in_itemID
	__asm push this
	__asm call hookptr
	return; //TODO
}


void CPC::OpenSearchStoreInfo(const int OpenType, const int Count) // 91-100 (PC0rd0.cpp)
{
	m_SSI_OpenType = OpenType;
	m_SSI_LimitSearchCnt = Count;

	PACKET_ZC_OPEN_SEARCH_STORE_INFO outpacket;
	outpacket.PacketType = HEADER_ZC_OPEN_SEARCH_STORE_INFO;
	outpacket.OpenType = OpenType;
	outpacket.SearchCntMax = Count;
	this->Send(sizeof(outpacket), (char*)&outpacket);
}


void CPC::ClearSearchStoreInfo() // 103-116 (PC0rd0.cpp)
{
	this->ResetEffective(EFST_SEARCH_STORE_INFO, 0);
	m_SSI_LimitSearchCnt = 0;
	m_SSI_OpenType = -1;

	CSSIMgr::GetObj()->m_SSIList.CSSIList::DeleteSearchData(this->GetAccountID());
}


void CPC::SetSSI_LimitSearchCnt(const int LimitSearchCnt) // ??? (PC0rd0.cpp)
{
	m_SSI_LimitSearchCnt = LimitSearchCnt;
}


const int CPC::GetSSI_LimitSearchCnt() // ??? (PC0rd0.cpp)
{
	return m_SSI_LimitSearchCnt;
}


const int CPC::GetSSI_OpenType() // ??? (PC0rd0.cpp)
{
	return m_SSI_OpenType;
}


hook_func<void (CPC::*)(unsigned long varID, int par1)> CPC__NotifyParameter(EXEPATH(), "CPC::NotifyParameter");
void CPC::NotifyParameter(unsigned long varID, int par1) // 245-301 (PCFormula.cpp)
{
	return (this->*CPC__NotifyParameter)(varID, par1); //TODO
	/*
	switch( varID )
	{
	case VAR_STATUSATTACKPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_ATTPOWER, this->CPC::GetStatusAttPower());
	break;
	case VAR_ITEMPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_REFININGPOWER, m_pcproperty->m_propertys.notifyItemPower);
	break;
	case VAR_STATUSDEFPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_ITEMDEFPOWER, m_pcproperty->m_propertys.statusDef);
	break;
	case VAR_ITEMDEFPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_PLUSDEFPOWER, m_pcproperty->m_propertys.notifyItemDef);
	break;
	case VAR_STATUSMAGICPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_MIN_MATTPOWER, m_pcproperty->m_propertys.statusMagicPower);
	break;
	case VAR_ITEMMAGICPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_MAX_MATTPOWER, m_pcproperty->m_propertys.notifyItemMPower);
	break;
	case VAR_MAGICSTATUSDEFPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_MDEFPOWER, m_pcproperty->m_propertys.statusMDef);
	break;
	case VAR_MDEFPOWER:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_PLUSMDEFPOWER, m_pcproperty->m_propertys.notifyItemMDef);
	break;
	case VAR_BASICHIT:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_HITSUCCESSVALUE, this->CPC::GetAttSucPercentOnClient());
	break;
	case VAR_BASICAVOIDANCE:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_AVOIDSUCCESSVALUE, this->CPC::GetAvoidableSucPerOnClient());
	break;
	case VAR_CRITICALSUCCESSVALUE:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_CRITICALSUCCESSVALUE, this->CPC::GetCriticalSuccessValue());
	break;
	case VAR_ASPD:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_ASPD, m_pcproperty->m_propertys.attackMotionTime);
	break;
	case VAR_WEIGHT:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_MAXWEIGHT, this->CPC::GetBodyMaxItemWeight());
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_WEIGHT, this->CPC::GetBodyItemWeight());
	break;
	case VAR_MONEY:
		m_pcClientUpdater.CPCClientUpdater::NotifyLongParameter(VAR_MONEY, m_characterInfo.CharacterInfo::GetMoney());
	break;
	default:
		m_pcClientUpdater.CPCClientUpdater::NotifyParameter(varID, par1);
	break;
	};
	*/
}


hook_func<void (CPC::*)(int& def)> CPC__ApplyExtraMDEF(EXEPATH(), "CPC::ApplyExtraMDEF");
void CPC::ApplyExtraMDEF(int& def) // 255-279 (PCFormula_Magic.cpp)
{
	return (this->*CPC__ApplyExtraMDEF)(def); //TODO
}


int CPC::GetAttackFinalDamage(ATTACK_INFO* info) // 1649-1650 (PC.h)
{
	return this->CPC::GetAttackFinalDamage(info->target, info->position, info->skillProperty, info->plusATTPowerPercent, info->plusATTSuccessPercent, info->calculateType, info->isRangeAttack, info->SKID, info->skLevel);
}


int CPC::GetAttackFinalDamage(CCharacter* other, int position, int skillProperty, int plusATTPowerPercent, int plusATTSuccessPercent, int type, BOOL isRangeAttack, unsigned short SKID, short skLevel) // 30-32 (PCFormula_Physics.cpp)
{
	return this->CPC::GetPhysicsFinalDamage(other, position, skillProperty, plusATTPowerPercent, plusATTSuccessPercent, type, isRangeAttack, SKID, skLevel);
}


hook_func<void (__stdcall *)()> CPC__GetPhysicsFinalDamage(EXEPATH(), "CPC::GetPhysicsFinalDamage");
int CPC::GetPhysicsFinalDamage(CCharacter* in_cpTarget, int in_WeaponPosition, int in_ATKProperty, int in_PlusATKPercent, int in_PlusHITPercent, int in_CalculateDamageType, BOOL in_IsRangeAttack, unsigned short in_SKID, short in_SKLevel) // 47-76 (PCFormula_Physics.cpp)
{
	int result;
	void* hookptr = CPC__GetPhysicsFinalDamage;
	__asm push in_SKLevel
	__asm push in_SKID
	__asm push in_IsRangeAttack
	__asm mov esi, in_CalculateDamageType
	__asm push in_PlusHITPercent
	__asm push in_PlusATKPercent
	__asm push in_ATKProperty
	__asm push in_WeaponPosition
	__asm mov ecx, in_cpTarget
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	CPCFormula_PhysicsSupport PhysicsSupport(this);

	PhysicsSupport.CPCFormula_PhysicsSupport::PreWork_BeforeGetPhysicsFinalDamage(in_PlusATKPercent, in_PlusHITPercent, in_SKID);

	if( !PhysicsSupport.CPCFormula_PhysicsSupport::IsPhysicsATKHit(in_cpTarget, in_PlusHITPercent, in_CalculateDamageType, in_IsRangeAttack, in_SKID) )
		return 0;

	int PhysicsFinalATKPower = PhysicsSupport.CPCFormula_PhysicsSupport::GetPhysicsFinalATKPower(in_cpTarget, in_WeaponPosition, in_ATKProperty, in_PlusATKPercent, in_IsRangeAttack, in_CalculateDamageType, in_IsRangeAttack, in_SKID, in_SKLevel);
	PhysicsSupport.CPCFormula_PhysicsSupport::ModifyPhysicsFinalATKPowerByTargetDEF(in_cpTarget, PhysicsFinalATKPower, in_CalculateDamageType);
	PhysicsSupport.CPCFormula_PhysicsSupport::ModifyPhysicsFinalATKPower_AfterApplyTargetDEF(in_cpTarget, PhysicsFinalATKPower, in_WeaponPosition, in_CalculateDamageType, in_SKID);

	return PhysicsFinalATKPower;
*/
}


hook_func<short (CPC::*)(CCharacter* other, const int in_SKATKPattern, BOOL isRangeAttack)> CPC__GetAttackSuccessPercent(EXEPATH(), "CPC::GetAttackSuccessPercent");
short CPC::GetAttackSuccessPercent(CCharacter* other, const int in_SKATKPattern, BOOL isRangeAttack) // 785-849 (PCFormula_Physics.cpp)
{
	return (this->*CPC__GetAttackSuccessPercent)(other, in_SKATKPattern, isRangeAttack); //TODO
}


hook_func<void (__stdcall *)()> CPC__GetAttackMotionTime(EXEPATH(), "CPC::GetAttackMotionTime");
int CPC::GetAttackMotionTime() // 967-969 (PCFormula_Physics.cpp)
{
	int result;
	void* hookptr = CPC__GetAttackMotionTime;
	__asm mov eax, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


hook_func<void (CPC::*)(int& def, CCharacter* in_cpAtkerCH)> CPC__ApplyExtraDEF(EXEPATH(), "CPC::ApplyExtraDEF");
void CPC::ApplyExtraDEF(int& def, CCharacter* in_cpAtkerCH) // 972-1019 (PCFormula_Physics.cpp)
{
	return (this->*CPC__ApplyExtraDEF)(def, in_cpAtkerCH); //TODO
}


hook_func<void (CPC::*)(unsigned long AID, CITZMsg* reqMsg)> CPC__OnMsgFromItemServer(EXEPATH(), "CPC::OnMsgFromItemServer");
void CPC::OnMsgFromItemServer(unsigned long AID, CITZMsg* reqMsg) // 116-1446 (PCMsg.cpp)
{
	return (this->*CPC__OnMsgFromItemServer)(AID, reqMsg); //TODO
}


hook_func<int (CPC::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CPC__OnMsg(EXEPATH(), "CPC::OnMsg");
int CPC::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 1690-2841 (PCMsg.cpp)
{
	return (this->*CPC__OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}


hook_func<void (__stdcall *)()> CPC__SkillAttack_Manual(EXEPATH(), "CPC::SkillAttack_Manual");
BOOL CPC::SkillAttack_Manual(SKILLATTACK_MSG* in_pMsg, const int in_PlusATKPercent, const int in_PlusHITPercent) // 229-483 (PCSkillAttack.cpp)
{
	BOOL result;
	void* hookptr = CPC__SkillAttack_Manual;
	__asm push in_PlusHITPercent
	__asm push in_PlusATKPercent
	__asm mov edx, in_pMsg
	__asm mov ecx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


int CPC::SkillAttack(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bSilenceSkill) // 487-491 (PCSkillAttack.cpp)
{
	msg->Property = -1;
	msg->bSilenceSkill = in_bSilenceSkill;
	return this->CPC::SkillAttack_Manual(msg, plusATTPowerPercent, plusATTSuccessPercent);
}


hook_func<short (CPC::*)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count)> CPC__SplashAttack(EXEPATH(), "CPC::SplashAttack");
short CPC::SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count) // 58-1103 (PCSplashAttack.cpp)
{
	return (this->*CPC__SplashAttack)(val1, xPos, yPos, type, range, rangeIn, exceptAID, msgDataPtr, val2, count); //TODO
}


void CPC::SplashAttack3(int plusATTPower, PosInfo dest, int type, MSG_TYPE1_TWODWORD* msgData, int range, int count) // 1319-1406 (PCSplashAttack.cpp)
{
	if( m_mapRes == NULL )
		return;

	NEIGHBORHOOD_SECTION result = {};

	PosInfo src;
	src.x = m_pathInfo.m_moveInfo.xPos;
	src.y = m_pathInfo.m_moveInfo.yPos;

	m_mapRes->CMapRes::GetNeighborhoodSections(src.x, src.y, range, &result);

	PosInfo splashPos[9] = {};
	this->CPC::GetSplashCells2(src, dest, range, splashPos);

	int SKID = msgData->data1;
	int level = msgData->data2;

	std::vector<CCharacter*> targetList;
	for( int k = 0; k < countof(result.section); ++k )
	{
		std::vector<CCharacter*>* section = result.section[k];
		if( section == NULL )
			continue;

		for( std::vector<CCharacter*>::iterator nextIter = section->begin(); nextIter != section->end(); ++nextIter )
		{
			CCharacter* ch = *nextIter;

			if( ch == NULL )
				continue;

			if( ch == this )
				continue;

			if( !ch->IsTarget(this, TARGET_TRAP) )
				continue;

			PosInfo other;
			ch->GetParameterValue(VAR_CURXPOS, other.x);
			ch->GetParameterValue(VAR_CURYPOS, other.y);

			for( int i = 0; i < range; ++i )
			{
				if( splashPos[i].x == other.x && splashPos[i].y == other.y )
					targetList.push_back(ch);
			}
		}
	}

	for( std::vector<CCharacter*>::iterator targetIter = targetList.begin(); targetIter != targetList.end(); ++targetIter )
	{
		CCharacter* ch = *targetIter;

		SKILLATTACK_MSG msg;
		msg.SKID = SKID;
		msg.targetAID = ch->GetAccountID();
		msg.level = 1;
		msg.skLevel = level;
		msg.actionType = ACTION_SPLASH;
		msg.count = 1;

		PosInfo other;
		ch->GetParameterValue(VAR_CURXPOS, other.x);
		ch->GetParameterValue(VAR_CURYPOS, other.y);

		PosInfo newPos;
		this->CActor::GetPushedPosition(src, other, 6, newPos);
		msg.xPos = newPos.x;
		msg.yPos = newPos.y;

		if( this->SkillAttack(&msg, plusATTPower, 100, false) )
		{
			if( !this->IsItPossible(MAPPROPERTY_DISABLE_KNOCKBACK) )
			{
				CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, ch, CM_KNOCKBACK, newPos.x, newPos.y, 1, 0);
			}
		}
	}
}


hook_func<void (CPC::*)(int plusATTPower, CCharacter* src, CCharacter* other, int destDir, int type, unsigned short SKID, int count, std::map<CCharacter*,CollideInfo>& collidedList)> CPC__CollideSplashAttack(EXEPATH(), "CPC::CollideSplashAttack");
void CPC::CollideSplashAttack(int plusATTPower, CCharacter* src, CCharacter* other, int destDir, int type, unsigned short SKID, int count, std::map<CCharacter*,CollideInfo>& collidedList) // 1409-1513 (PCSplashAttack.cpp)
{
	return (this->*CPC__CollideSplashAttack)(plusATTPower, src, other, destDir, type, SKID, count, collidedList); //TODO
}


hook_func<BOOL (CPC::*)(int in_plusATTPower, PosInfo in_dest, int in_type, int in_halfWidth, int in_height, MSG_TYPE1_TWODWORD* in_pMsgData, int in_count, int in_plusHitPercent, PosInfo* in_pspecialSrc)> CPC__SplashAttack2(EXEPATH(), "CPC::SplashAttack2");
BOOL CPC::SplashAttack2(int in_plusATTPower, PosInfo in_dest, int in_type, int in_halfWidth, int in_height, MSG_TYPE1_TWODWORD* in_pMsgData, int in_count, int in_plusHitPercent, PosInfo* in_pspecialSrc) // 1775-1913 (PCSplashAttack.cpp)
{
	return (this->*CPC__SplashAttack2)(in_plusATTPower, in_dest, in_type, in_halfWidth, in_height, in_pMsgData, in_count, in_plusHitPercent, in_pspecialSrc); //TODO
}


bool CPC::IsRightWeaponItemClass(short class1, short class2, short class3) // 1640-1652 (PCThirdJob.cpp)
{
	CITP* itp = this->CPC::GetITPEquipedWeapon();
	if( itp == NULL )
		return false;

	short itemClass = itp->GetClass();
	if( itemClass != class1 && itemClass != class2 && itemClass != class3 )
		return false;

	return true;
}
