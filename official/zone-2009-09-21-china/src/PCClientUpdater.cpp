#include "BattleFieldMapRes.h"
#include "CharacterMgr.h"
#include "CITP.hpp"
#include "MapInfo.h"
#include "MapResMgr.h"
#include "CNpcMercenary.hpp"
#include "PC.h"
#include "PCClientUpdater.h"
#include "ServerInfo.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/SaveAllADBWork.h"
#include "Common/Packet.h"
#include "NpcServer/NpcSvr.h"
#include "enum.hpp"
#include "shared.h" // Trace()


CPCClientUpdater::CPCClientUpdater(void) // line 60
{
}


CPCClientUpdater::~CPCClientUpdater(void) // line 64
{
}


hook_method<void (CPCClientUpdater::*)(CPC* pc)> CPCClientUpdater::_SetMyOwner(SERVER, "CPCClientUpdater::SetMyOwner");
void CPCClientUpdater::SetMyOwner(CPC* pc) // line 69
{
	return (this->*_SetMyOwner)(pc);

	m_pc = pc;
}


hook_method<void (CPCClientUpdater::*)(void)> CPCClientUpdater::_Init(SERVER, "CPCClientUpdater::Init");
void CPCClientUpdater::Init(void) // line 74
{
	return (this->*_Init)();

	m_pc->m_dwErrorCount = 0;
	m_disconnectType = NORMAL_DISCONNECT;
}


hook_method<void (CPCClientUpdater::*)(int AccountID)> CPCClientUpdater::_SetAccountID(SERVER, "CPCClientUpdater::SetAccountID");
void CPCClientUpdater::SetAccountID(int AccountID) // line 80
{
	return (this->*_SetAccountID)(AccountID);

	m_pc->m_characterInfo.accountID = AccountID;
}


hook_method<void (CPCClientUpdater::*)(int CharacterID)> CPCClientUpdater::_SetCharacterID(SERVER, "CPCClientUpdater::SetCharacterID");
void CPCClientUpdater::SetCharacterID(int CharacterID) // line 85
{
	return (this->*_SetCharacterID)(CharacterID);

	m_pc->m_characterInfo.characterID = CharacterID;
}


hook_method<void (CPCClientUpdater::*)(const char* buf)> CPCClientUpdater::_SetAccountName(SERVER, "CPCClientUpdater::SetAccountName");
void CPCClientUpdater::SetAccountName(const char* buf) // line 112
{
	return (this->*_SetAccountName)(buf);

	memcpy(m_pc->m_characterInfo.accountName, buf, sizeof(m_pc->m_characterInfo.accountName));
}


hook_method<void (CPCClientUpdater::*)(const char* buf)> CPCClientUpdater::_SetCharacterName(SERVER, "CPCClientUpdater::SetCharacterName");
void CPCClientUpdater::SetCharacterName(const char* buf) // line 117
{
	return (this->*_SetCharacterName)(buf);

	memcpy(m_pc->m_characterInfo.characterName, buf, sizeof(m_pc->m_characterInfo.characterName));
}


hook_method<void (CPCClientUpdater::*)(int AuthCode)> CPCClientUpdater::_SetAuthCode(SERVER, "CPCClientUpdater::SetAuthCode");
void CPCClientUpdater::SetAuthCode(int AuthCode) // line 542
{
	return (this->*_SetAuthCode)(AuthCode);

	m_pc->m_characterInfo.AuthCode = AuthCode;
}


hook_method<void (CPCClientUpdater::*)(int isActive)> CPCClientUpdater::_SetSendable(SERVER, "CPCClientUpdater::SetSendable");
void CPCClientUpdater::SetSendable(int isActive) // line 557
{
	return (this->*_SetSendable)(isActive);

	m_pc->m_characterInfo.isSendable = isActive;
}


hook_method<void (CPCClientUpdater::*)(int xPos, int yPos, unsigned char dir)> CPCClientUpdater::_InitPosition(SERVER, "CPCClientUpdater::InitPosition");
void CPCClientUpdater::InitPosition(int xPos, int yPos, unsigned char dir) // line 2141
{
	return (this->*_InitPosition)(xPos, yPos, dir);

	m_pc->m_pathInfo.CHostPathInfo::InitPosition(xPos, yPos, dir);
}


hook_method<void (CPCClientUpdater::*)(int index)> CPCClientUpdater::_SetIndex(SERVER, "CPCClientUpdater::SetIndex");
void CPCClientUpdater::SetIndex(int index) // line 616-618
{
	return (this->*_SetIndex)(index);

	m_pc->m_index = index;
}


hook_method<int (CPCClientUpdater::*)(CCharacter* other, int xRange, int yRange)> CPCClientUpdater::_IsMyArea(SERVER, "?IsMyArea@CPCClientUpdater@@QAEHPAVCCharacter@@HH@Z");
int CPCClientUpdater::IsMyArea(CCharacter* other, int xRange, int yRange) // line 577
{
	return (this->*_IsMyArea)(other, xRange, yRange);

	//TODO
}


hook_method<int (CPCClientUpdater::*)(CCharacter* other, int Range)> CPCClientUpdater::_IsMyArea2(SERVER, "?IsMyArea@CPCClientUpdater@@QAEHPAVCCharacter@@H@Z");
int CPCClientUpdater::IsMyArea(CCharacter* other, int Range) // line 561
{
	return (this->*_IsMyArea2)(other, Range);

	//TODO
}


hook_method<int (CPCClientUpdater::*)(void)> CPCClientUpdater::_AddSectionMgr(SERVER, "CPCClientUpdater::AddSectionMgr");
int CPCClientUpdater::AddSectionMgr(void) // line 631
{
	return (this->*_AddSectionMgr)();

	//TODO
}


hook_method<void (CPCClientUpdater::*)(void)> CPCClientUpdater::_RemoveSectionMgr(SERVER, "CPCClientUpdater::RemoveSectionMgr");
void CPCClientUpdater::RemoveSectionMgr(void) // line 644
{
	return (this->*_RemoveSectionMgr)();

	//TODO
}


hook_method<int (CPCClientUpdater::*)(const char* mapName, short xPos, short yPos, unsigned long NAID, int type)> CPCClientUpdater::_MapMove(SERVER, "CPCClientUpdater::MapMove");
int CPCClientUpdater::MapMove(const char* mapName, short xPos, short yPos, unsigned long NAID, int type) // line 1796
{
	return (this->*_MapMove)(mapName, xPos, yPos, NAID, type);

	if( m_pc->m_pcClientUpdater.m_disconnectType == MOVE_SERVER || m_pc->m_pcClientUpdater.m_disconnectType == RESTART_HSERVER )
		return 0;

	m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::CancelMailItem(1, 1);
	m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::CancelAuctionItem();
	m_pc->CPC::SetMapLoadingFlag(1);

	if( NAID == 0 && m_pc->m_eventNo != 0 )
		g_npcSvr->CNpcSvr::CancelEvent(m_pc->m_eventNo);

	if( m_pc->m_lastNPCAID != 0 )
		m_pc->m_lastNPCAID = 0;

	if( m_pc->m_exchangeItemInfo.AID != 0 )
		m_pc->CPC::CancelExchangeItem();

	m_pc->CPC::CancelMCStore();

	if( NAID == m_pc->GetAccountID() )
		NAID = 0;
	else
		m_pc->CPC::ResetItemScriptEvent();

	int ServerID = -1;
	bool out_bPlayerEnter = false;
	g_mapInfo->CMapInfo::GetZSVRandPlayerEnter(mapName, ServerID, out_bPlayerEnter);

	if( !out_bPlayerEnter )
		return 0;

	if( ServerID == -1 )
	{// map doesn't exist
		CSaveAllADBWork* work = new CSaveAllADBWork(CSaveAllADBWork::AFTER_ACTION_NONE, m_pc->GetAccountID(), m_pc->CPC::GetCharacterID());
		if( work != NULL )
		{
			m_pc->CPC::GetDBInfo(8, work->m_CharacterData.m_data);

			memcpy(work->m_CharacterData.m_characterName, m_pc->m_characterInfo.characterName, sizeof(work->m_CharacterData.m_characterName));
			work->m_CharacterData.m_bActive = true;

			m_pc->m_pcSkill.CPCSkill::UpdateWarpInfo();

			work->m_BodyItemData.m_Length = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemDBFormat(work->m_BodyItemData.m_data, 16300);
			work->m_BodyItemData.m_bActive = true;

			if( m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsCartOn() )
			{
				work->m_CartItemData.m_Length = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetCartItemDBFormat(work->m_CartItemData.m_Data, 16300);
				work->m_CartItemData.m_bActive = true;
			}

			work->m_questEventData.m_isUpdate = m_pc->m_questEvent.CPCQuestEvent::GetUpdateData();
			if( work->m_questEventData.m_isUpdate )
			{
				work->m_questEventData.m_length_quest = m_pc->m_questEvent.CPCQuestEvent::Save_QuestInfo(work->m_questEventData.m_data_quset, 8000);
				work->m_questEventData.m_length_hunt = m_pc->m_questEvent.CPCQuestEvent::Save_Quest_Hunt(work->m_questEventData.m_data_hunt, 8000);
				work->m_questEventData.m_length_time = m_pc->m_questEvent.CPCQuestEvent::Save_Quest_Time(work->m_questEventData.m_data_time, 8000);
				work->m_questEventData.m_length_complete = m_pc->m_questEvent.CPCQuestEvent::Save_CompleteQuest(work->m_questEventData.m_data_complete, 4000);
			}

			if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
				delete work;
		}

		return 0;
	}

	if( !this->CPCClientUpdater::IsSendable() )
		return 1;

	if( strncmp(m_pc->m_characterInfo.mapName, mapName, sizeof(m_pc->m_characterInfo.mapName)) != 0 )
	{
		if( m_pc->m_pvpWinPoint > 0 )
		{
			m_pc->m_pvpWinPoint = 5;
			g_mapResMgr->CMapResMgr::DeleteWinPoint(m_pc->m_mapRes, m_pc->GetAccountID());
		}
		m_pc->CPC::SetPVPRanking(0);
		m_pc->m_pvpTotal = 0;
		m_pc->ResetEffective(EFST_CASH_BOSS_ALARM, 0);
		m_pc->m_characterInfo.deadCount = 0;
	}

	PACKET_ZC_NOTIFY_VANISH broadcast;
	broadcast.PacketType = HEADER_ZC_NOTIFY_VANISH;
	broadcast.type = ( type == VT_TELEPORT ) ? VT_TELEPORT : VT_OUTOFSIGHT;
	broadcast.GID = this->CPCClientUpdater::GetAccountID();
	m_pc->CCharacter::MultiCast((char*)&broadcast, sizeof(broadcast));

	if( m_pc->GetEffective(EFST_BDPLAYING, 0) )
		m_pc->m_pcSkill.CPCSkill::DisappearPlayingSkill();

	if( m_pc->GetEffective(EFST_SG_WARM, 0) || m_pc->GetEffective(EFST_DAURA, 0) )
		m_pc->m_pcSkill.CPCSkill::DisappearPlayingSkill();

	m_pc->CPC::ClearDevotionList();
	m_pc->ResetEffective(EFST_DEVOTION, 0);
	this->CPCClientUpdater::SetSendable(0);
	this->CPCClientUpdater::ReleaseEffectState();
	this->CPCClientUpdater::RemoveSectionMgr();
	m_pc->m_scrollItemIndex = 0;
	m_pc->m_battleFieldInfo.xPos2 = 0;
	m_pc->m_battleFieldInfo.yPos2 = 0;

	CMapRes* prevMap = m_pc->m_mapRes;
	if( ServerID != g_serverInfo->CServerInfo::GetLocalServerID() )
	{
		if( !this->CPCClientUpdater::MapMove_OtherServer(ServerID, mapName, xPos, yPos, NAID) )
			return 0;
	}
	else
	{
		if( !this->CPCClientUpdater::MapMove_SameServer(mapName, xPos, yPos) )
			return 0;

		if( prevMap == m_pc->m_mapRes )
			return 1;
	}

	if( prevMap && prevMap->IsBattleField() )
		((CBattleFieldMapRes*)prevMap)->CBattleFieldMapRes::DeleteAliveMember(m_pc->GetCampID(), m_pc->GetAccountID());

	return 1;
}


hook_method<int (CPCClientUpdater::*)(const char* in_TargetMapName, short in_TargetXPos, short in_TargetYPos)> CPCClientUpdater::_MapMove_SameServer(SERVER, "CPCClientUpdater::MapMove_SameServer");
int CPCClientUpdater::MapMove_SameServer(const char* in_TargetMapName, short in_TargetXPos, short in_TargetYPos) // line 1459
{
	return (this->*_MapMove_SameServer)(in_TargetMapName, in_TargetXPos, in_TargetYPos);

	//TODO
}


hook_method<int (CPCClientUpdater::*)(const int in_TargetSvrID, const char* in_TargetMapName, short in_TargetXPos, short in_TargetYPos, const unsigned long in_NAID)> CPCClientUpdater::_MapMove_OtherServer(SERVER, "CPCClientUpdater::MapMove_OtherServer");
int CPCClientUpdater::MapMove_OtherServer(const int in_TargetSvrID, const char* in_TargetMapName, short in_TargetXPos, short in_TargetYPos, const unsigned long in_NAID) // line 1765
{
	return (this->*_MapMove_OtherServer)(in_TargetSvrID, in_TargetMapName, in_TargetXPos, in_TargetYPos, in_NAID);

	memcpy(m_pc->m_characterInfo.targetMapName, in_TargetMapName, sizeof(m_pc->m_characterInfo.targetMapName));
	memcpy(m_pc->m_characterInfo.mapName, in_TargetMapName, sizeof(m_pc->m_characterInfo.mapName));
	m_pc->m_mapRes = NULL;

	if( in_TargetXPos == 0 || in_TargetYPos == 0 )
	{
		in_TargetXPos = 100;
		in_TargetYPos = 100;
	}

	m_pc->m_pcClientUpdater.CPCClientUpdater::InitPosition(in_TargetXPos, in_TargetYPos, 0);
	m_pc->m_characterInfo.targetxPos = in_TargetXPos;
	m_pc->m_characterInfo.targetyPos = in_TargetYPos;
	Trace("Set MoveServer\n");

	if( m_pc->CPC::GetBodyState() == BODYSTATE_STONECURSE_ING )
		m_pc->CPC::SetBodyStateTimeInfo(0, 9999, BODYSTATE_STONECURSE);

	if( !this->CPCClientUpdater::MapMove_OtherServer_Part1(in_NAID, in_TargetSvrID) )
	{
		m_pc->AddErrorCount(".\\PCClientUpdater.cpp", 1788, 4, timeGetTime());
		return 0;
	}

	return 1;
}


hook_method<bool (CPCClientUpdater::*)(const unsigned long in_NAID, const int in_TargetSvrID)> CPCClientUpdater::_MapMove_OtherServer_Part1(SERVER, "CPCClientUpdater::MapMove_OtherServer_Part1");
bool CPCClientUpdater::MapMove_OtherServer_Part1(const unsigned long in_NAID, const int in_TargetSvrID) // line 1545
{
	return (this->*_MapMove_OtherServer_Part1)(in_NAID, in_TargetSvrID);

	if( m_pc->m_isValid != 1 )
		return false;

	CSaveAllADBWork* work = new CSaveAllADBWork(CSaveAllADBWork::AFTER_ACTION_MAPMOVE_OTHERSERVER, m_pc->GetAccountID(), m_pc->CPC::GetCharacterID());
	if( work == NULL )
		return false;

	m_pc->CPC::GetDBInfo(3, work->m_CharacterData.m_data);

	memcpy(work->m_CharacterData.m_characterName, m_pc->m_characterInfo.characterName, sizeof(work->m_CharacterData.m_characterName));
	work->m_CharacterData.m_bActive = true;

	m_pc->m_pcSkill.CPCSkill::UpdateWarpInfo();

	work->m_BodyItemData.m_Length = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetBodyItemDBFormat(work->m_BodyItemData.m_data, 16300);
	work->m_BodyItemData.m_bActive = true;

	work->m_MapMoveOtherSvr.m_NID = in_NAID;
	work->m_MapMoveOtherSvr.m_TargetSvrID = in_TargetSvrID;

	work->m_EffectiveData.m_Length = m_pc->CPC::GetEffectiveDBFmt(work->m_EffectiveData.m_Data, 512);
	work->m_EffectiveData.m_bActive = true;

	work->m_StateData.m_Length = m_pc->CActor::GetStateDBFmt(work->m_StateData.m_Data, 512);
	work->m_StateData.m_bActive = true;

	memcpy(&work->m_MercenaryData.m_Owner.m_data, &(CPCBattleMercenary::tagDBData)m_pc->m_pcBattle.m_Mercenary, sizeof(work->m_MercenaryData.m_Owner.m_data));
	work->m_MercenaryData.m_Owner.m_bActive = true;

	CNpcMercenary* cpMercenary = m_pc->m_pcBattle.CPCBattle::GetMercenary();
	if( cpMercenary != NULL )
	{
		m_pc->m_pcBattle.CPCBattle::Mercenary_SaveToProxyDB();
		memcpy(&work->m_MercenaryData.m_Character.m_Info, &m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_Info, sizeof(work->m_MercenaryData.m_Character.m_Info));
		work->m_MercenaryData.m_Character.m_EffectLength = m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectLength;
		if( m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectLength > 0 )
			memcpy(work->m_MercenaryData.m_Character.m_EffectData, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectData, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_EffectLength);
		work->m_MercenaryData.m_Character.m_StateLength = m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateLength;
		if( m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateLength > 0 )
			memcpy(work->m_MercenaryData.m_Character.m_StateData, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateData, m_pc->m_pcBattle.m_Mercenary.m_ProxyDB.m_StateLength);
		if( cpMercenary->GetEffective(EFST_BERSERK, 0) > 0 )
			work->m_MercenaryData.m_Character.m_Info.hp = 100;
		work->m_MercenaryData.m_Character.m_bActive = true;
	}

	if( m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsStoreOpen() )
	{
		work->m_StoreItemData.m_Length = m_pc->CPC::GetStoreItemDBFormat(work->m_StoreItemData.m_Data, 16300);
		work->m_StoreItemData.m_bActive = true;
	}

	if( m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsCartOn() )
	{
		work->m_CartItemData.m_Length = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetCartItemDBFormat(work->m_CartItemData.m_Data, 16300);
		work->m_CartItemData.m_bActive = true;
	}

	work->m_questEventData.m_isUpdate = m_pc->m_questEvent.CPCQuestEvent::GetUpdateData();
	if( work->m_questEventData.m_isUpdate )
	{
		work->m_questEventData.m_length_quest = m_pc->m_questEvent.CPCQuestEvent::Save_QuestInfo(work->m_questEventData.m_data_quset, 8000);
		work->m_questEventData.m_length_hunt = m_pc->m_questEvent.CPCQuestEvent::Save_Quest_Hunt(work->m_questEventData.m_data_hunt, 8000);
		work->m_questEventData.m_length_time = m_pc->m_questEvent.CPCQuestEvent::Save_Quest_Time(work->m_questEventData.m_data_time, 8000);
		work->m_questEventData.m_length_complete = m_pc->m_questEvent.CPCQuestEvent::Save_CompleteQuest(work->m_questEventData.m_data_complete, 4000);
	}

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
	{
		delete work;
		return false;
	}

	m_pc->SetEffective(EFST_NOACTION_WAIT, 40000, work->NAsyncDBWork::GetIdentity(), work->NAsyncDBWork::GetType(), timeGetTime(), 0);
	return true;
}


hook_method<void (CPCClientUpdater::*)(const unsigned long in_NAID, const int in_TargetSvrID)> CPCClientUpdater::_MapMove_OtherServer_Part2(SERVER, "CPCClientUpdater::MapMove_OtherServer_Part2");
void CPCClientUpdater::MapMove_OtherServer_Part2(const unsigned long in_NAID, const int in_TargetSvrID) // line 1682
{
	return (this->*_MapMove_OtherServer_Part2)(in_NAID, in_TargetSvrID);

	PACKET_ZH_SAVECHARINFO outpacket;
	outpacket.PacketType = HEADER_ZH_SAVECHARINFO;
	outpacket.AID = m_pc->GetAccountID();
	outpacket.GID = m_pc->CPC::GetCharacterID();
	outpacket.AuthCode = m_pc->m_characterInfo.AuthCode;
	g_characterMgr->CCharacterMgr::SendToHServer(sizeof(outpacket), (const char*)&outpacket);

	m_pc->CPC::RemovePet();
	if( m_pc->m_pcBattle.m_myHomunID != 0 )
		g_characterMgr->CCharacterMgr::SendMsg(m_pc, m_pc->m_pcBattle.m_myHomunID, CM_SAVE_CHARINFO, m_pc->CPC::GetCharacterID(), 0, 0, 0);
	m_pc->m_pcBattle.CPCBattle::RemoveHomun();
	m_pc->m_pcBattle.CPCBattle::Mercenary_Release(true);
	if( m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsStoreOpen() )
		m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::StoreItemReset(); // inlined

	Request request2;
	request2.Request::SetID(RT_RESET_EXCHANGEITEM);
	m_pc->CPC::OnDispatchClientRequest(&request2);

	m_pc->m_pcClientUpdater.m_disconnectType = MOVE_SERVER;

	PACKET_ZH_MAPMOVE hpacket;
	hpacket.PacketType = HEADER_ZH_MAPMOVE;
	hpacket.AID = m_pc->GetAccountID();
	hpacket.NID = in_NAID;
	hpacket.ServerID = in_TargetSvrID;
	g_characterMgr->CCharacterMgr::SendToHServer(sizeof(hpacket), (const char*)&hpacket);
}


hook_method<void (CPCClientUpdater::*)(unsigned long enemyAID)> CPCClientUpdater::_OnDead(SERVER, "CPCClientUpdater::OnDead");
void CPCClientUpdater::OnDead(unsigned long enemyAID) // line 1292-1436
{
	return (this->*_OnDead)(enemyAID);

	// TODO
}


hook_method<unsigned long (CPCClientUpdater::*)(void)> CPCClientUpdater::_GetAccountID(SERVER, "CPCClientUpdater::GetAccountID");
unsigned long CPCClientUpdater::GetAccountID(void) // line 91
{
	return (this->*_GetAccountID)();

	return m_pc->m_characterInfo.accountID;
}


hook_method<unsigned long (CPCClientUpdater::*)(void)> CPCClientUpdater::_GetCharacterID(SERVER, "CPCClientUpdater::GetCharacterID");
unsigned long CPCClientUpdater::GetCharacterID(void) // line 96
{
	return (this->*_GetCharacterID)();

	return m_pc->m_characterInfo.characterID;
}


hook_method<void (CPCClientUpdater::*)(void)> CPCClientUpdater::_SetParameterPointValue(SERVER, "CPCClientUpdater::SetParameterPointValue");
void CPCClientUpdater::SetParameterPointValue(void) // line 766
{
	return (this->*_SetParameterPointValue)();

	m_pc->m_characterInfo.StrP = this->CPCClientUpdater::GetParPointValue(m_pc->m_characterInfo.Str);
	m_pc->m_characterInfo.AgiP = this->CPCClientUpdater::GetParPointValue(m_pc->m_characterInfo.Agi);
	m_pc->m_characterInfo.VitP = this->CPCClientUpdater::GetParPointValue(m_pc->m_characterInfo.Vit);
	m_pc->m_characterInfo.IntP = this->CPCClientUpdater::GetParPointValue(m_pc->m_characterInfo.Int);
	m_pc->m_characterInfo.DexP = this->CPCClientUpdater::GetParPointValue(m_pc->m_characterInfo.Dex);
	m_pc->m_characterInfo.LukP = this->CPCClientUpdater::GetParPointValue(m_pc->m_characterInfo.Luk);
}


hook_method<void (CPCClientUpdater::*)(unsigned short type, int count)> CPCClientUpdater::_NotifyParameter(SERVER, "CPCClientUpdater::NotifyParameter");
void CPCClientUpdater::NotifyParameter(unsigned short type, int count) // line 810
{
	return (this->*_NotifyParameter)(type, count);

	PACKET_ZC_PAR_CHANGE outpacket;
	outpacket.PacketType = HEADER_ZC_PAR_CHANGE;
	outpacket.varID = type;
	outpacket.count = count;

	switch( type )
	{
	case VAR_DEX:
		this->CPCClientUpdater::NotifyParameter(VAR_ATTPOWER, m_pc->CPC::GetAttPowerOnClient());
		this->CPCClientUpdater::NotifyParameter(VAR_REFININGPOWER, m_pc->CPC::GetRefiningAttPowerOnClient());
		this->CPCClientUpdater::NotifyStatusParameter(type, m_pc->CPC::GetDefaultDexValue(), m_pc->CPC::GetDexPlusValue());
		m_pc->UpdateParameterValue(VAR_ASPD, 0);
		m_pc->UpdateParameterValue(VAR_STATUSATTACKPOWER, 0);
		m_pc->UpdateParameterValue(VAR_BASICHIT, 0);
	break;
	case VAR_STR:
		this->CPCClientUpdater::NotifyParameter(VAR_ATTPOWER, m_pc->CPC::GetAttPowerOnClient());
		this->CPCClientUpdater::NotifyParameter(VAR_REFININGPOWER, m_pc->CPC::GetRefiningAttPowerOnClient());
		this->CPCClientUpdater::NotifyStatusParameter(type, m_pc->CPC::GetDefaultStrValue(), m_pc->CPC::GetStrPlusValue());
		m_pc->UpdateParameterValue(VAR_STATUSATTACKPOWER, 0);
	break;
	case VAR_INT:
		this->CPCClientUpdater::NotifyParameter(VAR_MAX_MATTPOWER, m_pc->CPC::GetMagicAttMaxPowOnClient());
		this->CPCClientUpdater::NotifyParameter(VAR_MIN_MATTPOWER, m_pc->CPC::GetMagicAttMinPowOnClient());
		this->CPCClientUpdater::NotifyParameter(VAR_PLUSMDEFPOWER, m_pc->CPC::GetIntValue());
		this->CPCClientUpdater::NotifyParameter(VAR_MAXSP, m_pc->CPC::GetMaxSP());
		this->CPCClientUpdater::NotifyStatusParameter(type, m_pc->CPC::GetDefaultIntValue(), m_pc->CPC::GetIntPlusValue());
	break;
	case VAR_LUK:
		this->CPCClientUpdater::NotifyParameter(VAR_ATTPOWER, m_pc->CPC::GetAttPowerOnClient());
		this->CPCClientUpdater::NotifyParameter(VAR_REFININGPOWER, m_pc->CPC::GetRefiningAttPowerOnClient());
		this->CPCClientUpdater::NotifyParameter(VAR_PLUSAVOIDSUCCESSVALUE, m_pc->CPC::GetPlusAvoidableSucPerOnClient());
		this->CPCClientUpdater::NotifyParameter(VAR_CRITICALSUCCESSVALUE, m_pc->CPC::GetCriticalSuccessValue());
		this->CPCClientUpdater::NotifyParameter(VAR_PLUSATTREFININGPOWEROFITEM, m_pc->CPC::GetRefiningAttPowerOnClient());
		this->CPCClientUpdater::NotifyStatusParameter(type, m_pc->CPC::GetDefaultLukValue(), m_pc->CPC::GetLukPlusValue());
		m_pc->UpdateParameterValue(VAR_STATUSATTACKPOWER, 0);
	break;
	case VAR_AGI:
		this->CPCClientUpdater::NotifyStatusParameter(type, m_pc->CPC::GetDefaultAgiValue(), m_pc->CPC::GetAgiPlusValue());
		m_pc->UpdateParameterValue(VAR_ASPD, 0);
		m_pc->UpdateParameterValue(VAR_BASICAVOIDANCE, 0);
	break;
	case VAR_VIT:
	{
		double def = m_pc->m_characterInfo.extDEFPercent * (double)(m_pc->m_characterInfo.DEFPercent * m_pc->CPC::GetVitValue() / 100) / 100.0;
		this->CPCClientUpdater::NotifyParameter(VAR_PLUSDEFPOWER, (int)def);
		this->CPCClientUpdater::NotifyParameter(VAR_MAXHP, m_pc->CPC::GetMaxHP());
		this->CPCClientUpdater::NotifyStatusParameter(type, m_pc->CPC::GetDefaultVitValue(), m_pc->CPC::GetVitPlusValue());
	}
	break;
	case VAR_MAX_MATTPOWER:
	case VAR_MIN_MATTPOWER:
	{
		CITP* weapon = m_pc->CPC::GetITPEquipedWeapon();

		if( weapon && (weapon->GetClass() == WEAPONTYPE_ROD || weapon->GetClass() == WPCLASS_TWOHANDROD) )
			outpacket.count = outpacket.count * 115 / 100;

		m_pc->CPC::Send(sizeof(outpacket), (char *)&outpacket);
	}
	break;
	default:
		m_pc->CPC::Send(sizeof(outpacket), (char *)&outpacket);
	break;
	}

	switch( type )
	{
	case VAR_HP:
		m_pc->CPC::BroadcastHP();
		break;
	case VAR_CLEVEL:
		m_pc->UpdateParameterValue(VAR_BASICAVOIDANCE, 0);
		m_pc->UpdateParameterValue(VAR_BASICHIT, 0);
		this->CPCClientUpdater::NotifyParameter(VAR_PLUSAVOIDSUCCESSVALUE, m_pc->CPC::GetPlusAvoidableSucPerOnClient());
		break;
	case VAR_MAXHP:
		m_pc->UpdateParameterValue(VAR_HP, 0);
		break;
	case VAR_MAXSP:
		m_pc->UpdateParameterValue(VAR_SP, 0);
		break;
	}
}


hook_method<int (CPCClientUpdater::*)(char value)> CPCClientUpdater::_GetParPointValue(SERVER, "CPCClientUpdater::GetParPointValue");
int CPCClientUpdater::GetParPointValue(char value) // line 778
{
	return (this->*_GetParPointValue)(value);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(unsigned long NAID)> CPCClientUpdater::_ReStart(SERVER, "CPCClientUpdater::ReStart");
void CPCClientUpdater::ReStart(unsigned long NAID) // line 1439
{
	return (this->*_ReStart)(NAID);

	m_pc->m_characterInfo.deadCount = 0;
	m_pc->CPC::DisableAllCommand();

	if( m_pc->m_characterInfo.reinCarnation )
	{
		m_pc->UpdateParameterValue(VAR_HP, m_pc->CPC::GetMaxHP());
		m_pc->UpdateParameterValue(VAR_SP, m_pc->CPC::GetMaxSP());
	}

	this->CPCClientUpdater::MapMove(m_pc->CPC::GetRestartMapName(), m_pc->m_characterInfo.sxPos, m_pc->m_characterInfo.syPos, NAID, 0);
}


hook_method<int (CPCClientUpdater::*)(void)> CPCClientUpdater::_IsSendable(SERVER, "CPCClientUpdater::IsSendable");
int CPCClientUpdater::IsSendable(void) // line 552
{
	return (this->*_IsSendable)();

	return m_pc->m_characterInfo.isSendable;
}


hook_method<int (CPCClientUpdater::*)(void)> CPCClientUpdater::_GetSPHealVelocity(SERVER, "CPCClientUpdater::GetSPHealVelocity");
int CPCClientUpdater::GetSPHealVelocity(void) // line 2027-2071
{
	return (this->*_GetSPHealVelocity)();

	// TODO
}


hook_method<int (CPCClientUpdater::*)(void)> CPCClientUpdater::_GetHPHealVelocity(SERVER, "CPCClientUpdater::GetHPHealVelocity");
int CPCClientUpdater::GetHPHealVelocity(void) // line 1982-2024
{
	return (this->*_GetHPHealVelocity)();

	// TODO
}


hook_method<void (CPCClientUpdater::*)(void)> CPCClientUpdater::_StopMove(SERVER, "CPCClientUpdater::StopMove");
void CPCClientUpdater::StopMove(void) // line 594
{
	return (this->*_StopMove)();

	if( m_pc->GetEffective(EFST_RUN, 0) )
		return; // can't stop

	if( m_pc->m_pathInfo.m_moveInfo.state != CHARACTER_STATE_MOVE )
		return; // not moving

	m_pc->m_pathInfo.m_moveInfo.state = CHARACTER_STATE_STAND;
	m_pc->m_pathInfo.CPathInfo::Reset();
}


hook_method<void (CPCClientUpdater::*)()> CPCClientUpdater::_NotifyStopMove(SERVER, "CPCClientUpdater::NotifyStopMove");
void CPCClientUpdater::NotifyStopMove()
{
	return (this->*_NotifyStopMove)();

	PACKET_ZC_STOPMOVE outpacket;
	outpacket.PacketType = HEADER_ZC_STOPMOVE;
	outpacket.AID = m_pc->GetAccountID();
	outpacket.xPos = static_cast<short>(m_pc->m_pathInfo.m_moveInfo.xPos);
	outpacket.yPos = static_cast<short>(m_pc->m_pathInfo.m_moveInfo.yPos);
	m_pc->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	m_pc->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


hook_method<void (CPCClientUpdater::*)(void)> CPCClientUpdater::_ReleaseEffectState(SERVER, "CPCClientUpdater::ReleaseEffectState");
void CPCClientUpdater::ReleaseEffectState(void) // line 2414
{
	return (this->*_ReleaseEffectState)();

	//TODO
}


hook_method<void (CPCClientUpdater::*)(mystd::vector<CCharacter*>* section)> CPCClientUpdater::_UpdateCharacter(SERVER, "CPCClientUpdater::UpdateCharacter");
void CPCClientUpdater::UpdateCharacter(mystd::vector<CCharacter*>* section)
{
	return (this->*_UpdateCharacter)(section);

	for( mystd::vector<CCharacter*>::iterator it = section->begin(); it != section->end(); ++it )
	{
		CCharacter* ch = *it;

		if( ch == NULL )
		{
			it = section->erase(it);
			continue;
		}

		switch( ch->GetType() )
		{
		case PC_TYPE:
		{
			CPC* pc = (CPC*)ch;

			if( pc == NULL || pc == m_pc )
				break;

			if( !pc->m_pcClientUpdater.CPCClientUpdater::IsSendable() )
				break;

			if( !this->CPCClientUpdater::IsMyArea(pc, 18) )
				break;

			this->CPCClientUpdater::NotifyUpdateInfo(pc);

			if( !pc->m_characterInfo.isSendable )
				break;

			if( pc->CPC::GetState() != CHARACTER_STATE_MOVE && pc->CPC::GetState() != CHARACTER_STATE_ENTER )
				pc->m_pcClientUpdater.CPCClientUpdater::NotifyUpdateInfo(m_pc);
		}
		break;
		case NPC_TYPE:
		case NPC_MOB_TYPE:
		case NPC_EVT_TYPE:
		case NPC_PET_TYPE:
		case NPC_HO_TYPE:
		case NPC_MERSOL_TYPE:
		{
			CNPC* npc = (CNPC*)ch;

			if( npc->CNPC::GetCharacterInfo()->isValid && npc->CNPC::GetState() != CHARACTER_STATE_MOVE && npc->CNPC::GetState() != CHARACTER_STATE_ENTER && this->CPCClientUpdater::IsMyArea(npc, 18) )
				npc->m_npcUpdater.CNPCUpdater::NotifyUpdateInfo(m_pc);
		}
		break;
		case SKILL_TYPE:
		{
			CSkill* skill = (CSkill*)ch;

			if( skill != NULL && skill->GetState() != CHARACTER_STATE_ENTER && this->CPCClientUpdater::IsMyArea(skill, 18) )
				skill->CSkill::NotifyUpdateInfo(m_pc);
		}
		break;
		case ITEM_TYPE:
		{
			CItem* item = (CItem*)ch;

			if( item != NULL && item->GetState() != CHARACTER_STATE_ENTER && this->CPCClientUpdater::IsMyArea(item, 18) )
				item->CItem::NotifyUpdateInfo(m_pc);
		}
		break;
		default:
		break;
		}

		++it;
	}
}


hook_method<void (CPCClientUpdater::*)(int par1, int par2, int par3)> CPCClientUpdater::_OnDialog(SERVER, "CPCClientUpdater::OnDialog");
void CPCClientUpdater::OnDialog(int par1, int par2, int par3) // line 2317
{
	return (this->*_OnDialog)(par1, par2, par3);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(int par1)> CPCClientUpdater::_OnWaitDialog(SERVER, "CPCClientUpdater::OnWaitDialog");
void CPCClientUpdater::OnWaitDialog(int par1) // line 2330
{
	return (this->*_OnWaitDialog)(par1);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(int par1)> CPCClientUpdater::_OnCloseDialog(SERVER, "CPCClientUpdater::OnCloseDialog");
void CPCClientUpdater::OnCloseDialog(int par1) // line 2339
{
	return (this->*_OnCloseDialog)(par1);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(unsigned long color, unsigned long time)> CPCClientUpdater::_OnProgress(SERVER, "CPCClientUpdater::OnProgress");
void CPCClientUpdater::OnProgress(unsigned long color, unsigned long time) // line 2364
{
	return (this->*_OnProgress)(color, time);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(void)> CPCClientUpdater::_OnPorgressCancel(SERVER, "CPCClientUpdater::OnPorgressCancel");
void CPCClientUpdater::OnPorgressCancel(void) // line 2376
{
	return (this->*_OnPorgressCancel)();

	//TODO
}


hook_method<void (CPCClientUpdater::*)(int par1, int par2, int par3)> CPCClientUpdater::_OnMenuList(SERVER, "CPCClientUpdater::OnMenuList");
void CPCClientUpdater::OnMenuList(int par1, int par2, int par3) // line 2351
{
	return (this->*_OnMenuList)(par1, par2, par3);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(unsigned short varID, int amount)> CPCClientUpdater::_NotifyLongParameter(SERVER, "CPCClientUpdater::NotifyLongParameter");
void CPCClientUpdater::NotifyLongParameter(unsigned short varID, int amount) // line 997
{
	return (this->*_NotifyLongParameter)(varID, amount);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(unsigned long errorCode, int type)> CPCClientUpdater::_NotifyBan(SERVER, "CPCClientUpdater::NotifyBan");
void CPCClientUpdater::NotifyBan(unsigned long errorCode, int type) // line 2294
{
	return (this->*_NotifyBan)(errorCode, type);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(void)> CPCClientUpdater::_ReqStatus(SERVER, "CPCClientUpdater::ReqStatus");
void CPCClientUpdater::ReqStatus(void) // line 2234
{
	return (this->*_ReqStatus)();

	//TODO
}


hook_method<void (CPCClientUpdater::*)(CPC* other)> CPCClientUpdater::_NotifyUpdateInfo(SERVER, "CPCClientUpdater::NotifyUpdateInfo");
void CPCClientUpdater::NotifyUpdateInfo(CPC* other)
{
	return (this->*_NotifyUpdateInfo)(other);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(int par1, short len, char* buf)> CPCClientUpdater::_OnWhisper(SERVER, "CPCClientUpdater::OnWhisper");
void CPCClientUpdater::OnWhisper(int par1, short len, char* buf) // line 2092
{
	return (this->*_OnWhisper)(par1, len, buf);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(unsigned char result)> CPCClientUpdater::_OnWhisperAck(SERVER, "CPCClientUpdater::OnWhisperAck");
void CPCClientUpdater::OnWhisperAck(unsigned char result) // line 2131
{
	return (this->*_OnWhisperAck)(result);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(int par1)> CPCClientUpdater::_OnUserCount(SERVER, "CPCClientUpdater::OnUserCount");
void CPCClientUpdater::OnUserCount(int par1) // line 2395
{
	return (this->*_OnUserCount)(par1);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(CCharacter* character, int par1, char* buf)> CPCClientUpdater::_OnChat(SERVER, "CPCClientUpdater::OnChat");
void CPCClientUpdater::OnChat(CCharacter* character, int par1, char* buf) // line 2403
{
	return (this->*_OnChat)(character, par1, buf);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(unsigned long type, int defaultValue, int plusValue)> CPCClientUpdater::_NotifyStatusParameter(SERVER, "CPCClientUpdater::NotifyStatusParameter");
void CPCClientUpdater::NotifyStatusParameter(unsigned long type, int defaultValue, int plusValue) // line 1280
{
	return (this->*_NotifyStatusParameter)(type, defaultValue, plusValue);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(CPC* other)> CPCClientUpdater::_NotifySpiritsInfo(SERVER, "CPCClientUpdater::NotifySpiritsInfo");
void CPCClientUpdater::NotifySpiritsInfo(CPC* other) // line 2431
{
	return (this->*_NotifySpiritsInfo)(other);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(CPC* other, int type, int value)> CPCClientUpdater::_NotifySpriteChange(SERVER, "CPCClientUpdater::NotifySpriteChange");
void CPCClientUpdater::NotifySpriteChange(CPC* other, int type, int value) // line 2446
{
	return (this->*_NotifySpriteChange)(other, type, value);

	//TODO
}


hook_method<void (CPCClientUpdater::*)(CPC* other)> CPCClientUpdater::_NotifyBattleFieldCampInfo(SERVER, "CPCClientUpdater::NotifyBattleFieldCampInfo");
void CPCClientUpdater::NotifyBattleFieldCampInfo(CPC* other) // line 2656
{
	return (this->*_NotifyBattleFieldCampInfo)(other);

	//TODO
}
