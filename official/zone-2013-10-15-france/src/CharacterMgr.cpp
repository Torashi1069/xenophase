#include "Character.h"
#include "CharacterMgr.h"
#include "CStaticNPCAIDGenerator.h"
#include "Enum.h"
#include "GVar.h"
#include "Item.h"
#include "MapRes.h"
#include "MapResMgr.h"
#include "NPC.h"
#include "NpcElemental.h"
#include "NpcEvt.h"
#include "NpcMobRecycleMgr.h"
#include "ObjectRecycleMgr.h"
#include "PC.h"
#include "Skill.h"
#include "ZSAcceptHandler.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/InterServerClient/C2InterServerClient.h"
#include "LuaMonsterAI/NLuaMonsterAIMgr.h"
#include "NpcServer/NpcSvr.h"
#include "Player/Inventory/CIVItEquipItem.h"
#include "shared/CMapInfoMgr.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
CCharacterMgr*& CCharacterMgr::m_cpSelf = VTOR<CCharacterMgr*>(DetourFindFunction(EXEPATH(), "CCharacterMgr::m_cpSelf"));


/// globals
int& g_npcMemorySize = VTOR<int>(DetourFindFunction(EXEPATH(), "g_npcMemorySize"));
DWORD& g_MaxDisconnectTime = VTOR<DWORD>(DetourFindFunction(EXEPATH(), "g_MaxDisconnectTime"));


CCharacterMgr::CCharacterMgr() // 97-121
{
//	m_PC = NULL;
//	m_PCCount = 0;
	m_curPlayChar = 0;
	m_curValidPlayChar = 0;
	m_curDisconnectCountPlayChar = 0;
	m_bOK = false;

	InitializeCriticalSection(&m_csPC);
	m_bOK = true;
}


CCharacterMgr::~CCharacterMgr() // 124-127
{
	delete[] m_PC;
	DeleteCriticalSection(&m_csPC);
}


bool CCharacterMgr::CreateInstance() // 161-168
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CCharacterMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CCharacterMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CCharacterMgr::DestroyInstance() // 174-177
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CCharacterMgr* CCharacterMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CCharacterMgr::isOK() const
{
	return m_bOK;
}


hook_func<void (__stdcall *)()> CCharacterMgr__Init(EXEPATH(), "CCharacterMgr::Init");
void CCharacterMgr::Init(int MaxCharacterCount) // 182-208
{
	void* hookptr = CCharacterMgr__Init;
	__asm mov ebx, MaxCharacterCount
	__asm mov esi, this
	__asm call hookptr
	return; //TODO
/*
	m_pcMemoryPool.CMemoryMgr<CPC>::Init(MaxCharacterCount);
	m_itemMemoryPool.CMemoryMgr<CItem>::Init(3000);
	m_skillMemoryPool.CMemoryMgr<CSkill>::Init(g_maxSkill);

	m_PCCount = MaxCharacterCount;
	m_PC = new CPC*[MaxCharacterCount];
	for( int i = 0; i < m_PCCount; ++i )
		m_PC[i] = NULL;

	for( int i = DYN_MINIMUM_AID; i <= DYN_MAXIMUM_AID; ++i )
		this->CCharacterMgr::PutAID(i);

	g_npcMemorySize = sizeof(CNpcEvt);
	m_WarpNPCList2nd.clear();
*/
}


int CCharacterMgr::GetMonsterCount() // ??? (105.h)
{
	return m_npcMap.size();
}


CPC* CCharacterMgr::AllocPC() // 244-247
{
	return m_pcMemoryPool.CMemoryMgr<CPC>::Alloc();
}


int CCharacterMgr::GetPCFreeSize()
{
	return m_pcMemoryPool.CMemoryMgr<CPC>::GetFreeSize();
}


hook_func<void (__stdcall *)()> CCharacterMgr__AllocNPC(EXEPATH(), "CCharacterMgr::AllocNPC");
CNPC* CCharacterMgr::AllocNPC(unsigned char type) // 255-292
{
	CNPC* result;
	unsigned char type_ = type;
	void* hookptr = CCharacterMgr__AllocNPC;
	__asm mov cl, type_
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
/*
	if( IsEventNpc(type) )
		return new(std::nothrow) CNpcEvt();
	else
	if( type == MONSTER_TYPE_25 )
		return new(std::nothrow) CNpcPet();
	else
	if( type == MERCENARY_TYPE_01 )
		return new(std::nothrow) CNpcHomun();
	else
	if( type == MERCENARY_TYPE_02 )
		return new(std::nothrow) CNpcMercenary();
	else
	if( type >= LUA_ELEMENTAL_TYPE && type <= ELEMENTAL_TYPE_OFFENSIVE )
		return CObjectRecycleMgr<CNpcElemental>::Instance()->CObjectRecycleMgr<CNpcElemental>::Get();
	else
	{// default
		return CNpcMobRecycleMgr::GetObj()->CNpcMobRecycleMgr::Get();
	}
*/
}

	
void CCharacterMgr::Free(CCharacter* pc) // 336-423
{
	if( pc == NULL )
		return;

	if( pc->CCharacter::GetMapRes() != NULL )
		pc->CCharacter::GetMapRes()->CMapRes::RemoveCharacter(pc);

	switch( pc->GetType() )
	{
	case PC_TYPE:
	{
		CPC* cpPC = static_cast<CPC*>(pc);

		m_pcMemoryPool.CMemoryMgr<CPC>::Free(cpPC);
	}
	break;
	case NPC_MOB_TYPE:
	{
		CNpcMob* cpNpcMob = static_cast<CNpcMob*>(pc);

		pc->GetAccountID(); // nop
		if( pc->GetAccountID() <= DYN_MAXIMUM_AID )
			this->CCharacterMgr::PutAID(pc->GetAccountID());

		CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Free(pc->GetAccountID());

		if( cpNpcMob->CNpcMob::GetSvrScriptAppID() != 0 )
		{
			NLuaMonsterAIMgr::GetObj()->NLuaMonsterAIMgr::DestroyApp(cpNpcMob->CNpcMob::GetSvrScriptAppID());
			cpNpcMob->CNpcMob::SetSvrScriptAppID(0);
		}

		CNpcMobRecycleMgr::GetObj()->CNpcMobRecycleMgr::Put(cpNpcMob);
	}
	break;
	case NPC_TYPE:
	case NPC_EVT_TYPE:
	case NPC_PET_TYPE:
	case NPC_HO_TYPE:
	case NPC_MERSOL_TYPE:
	{
		pc->GetAccountID(); // nop
		if( pc->GetAccountID() <= DYN_MAXIMUM_AID )
			this->CCharacterMgr::PutAID(pc->GetAccountID());

		CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Free(pc->GetAccountID());
		delete pc;
	}
	break;
	case NPC_ELEMENTAL_TYPE:
	{
		CNpcElemental* cpNpcElemental = static_cast<CNpcElemental*>(pc);

		pc->GetAccountID(); // nop
		if( pc->GetAccountID() <= DYN_MAXIMUM_AID )
			this->CCharacterMgr::PutAID(pc->GetAccountID());

		CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Free(pc->GetAccountID());
		CObjectRecycleMgr<CNpcElemental>::Instance()->CObjectRecycleMgr<CNpcElemental>::Put(cpNpcElemental);
	}
	break;
	case ITEM_TYPE:
	{
		CItem* cpItem = static_cast<CItem*>(pc);

		this->CCharacterMgr::PutAID(pc->GetAccountID());
		m_itemMemoryPool.CMemoryMgr<CItem>::Free(cpItem);
	}
	break;
	case SKILL_TYPE:
	{
		CSkill* cpSkill = static_cast<CSkill*>(pc);

		this->CCharacterMgr::PutAID(pc->GetAccountID());
		m_skillMemoryPool.CMemoryMgr<CSkill>::Free(cpSkill);
	}
	break;
	default:
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "메모리를 삭제하세요(%d)", pc->GetType());
	}
	break;
	};
}


void CCharacterMgr::OnDisconnect_STEP_NONE(CPC* pc) // 435-453
{
	pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_ARRANGE);
	if( pc->CPC::IsValid() != TRUE )
		pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_REMOVE);
}


void CCharacterMgr::OnDisconnect_STEP_REMOVE(CPC* pc) // 456-461
{
	pc->CPC::GetStream()->Close(false);
	pc->CPC::SetMapLoadingFlag(FALSE);
	this->CCharacterMgr::RemoveCharacter(pc);
}


hook_func<void (__stdcall *)()> CCharacterMgr__OnDisconnect_STEP_ARRANGE(EXEPATH(), "CCharacterMgr::OnDisconnect_STEP_ARRANGE");
void CCharacterMgr::OnDisconnect_STEP_ARRANGE(CPC* pc) // 470-569
{
	void* hookptr = CCharacterMgr__OnDisconnect_STEP_ARRANGE;
	__asm push pc
	__asm push this
	__asm call hookptr
	return; //TODO
/*
	pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::CancelMailItem(true, true);
	pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::CancelAuctionItem();

	if( pc->m_eventNo != 0 )
		g_npcSvr.CNpcSvr::CancelEvent(pc->m_eventNo);

	if( pc->GetEffective(EFST_BERSERK, 0) > 0 )
		pc->m_HPAmount = 100;

	if( pc->GetEffective(EFST_BLADESTOP, 0) )
		pc->ResetEffective(EFST_BLADESTOP, 0);

	pc->ResetEffective(EFST_CURSEDCIRCLE_ATKER, 0);
	pc->ResetEffective(EFST_CURSEDCIRCLE_TARGET, 0);

	if( pc->GetEffective(EFST_BDPLAYING, 0) )
	{
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pc->m_pcSkill.m_partnerAID, CM_PLAYSKILL_CANCEL, 0, 0, 0, 0);
		pc->m_pcSkill.CPCSkill::DestroyPlayingSkill();
	}

	if( pc->GetEffective(EFST_SG_WARM, 0) || pc->GetEffective(pc, EFST_DAURA, 0) )
	{
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pc->m_pcSkill.m_partnerAID, CM_PLAYSKILL_CANCEL, 0, 0, 0, 0);
		pc->m_pcSkill.CPCSkill::DestroyPlayingSkill();
	}

	if( pc->GetEffective(EFST_CRYSTAL, 0) )
	{
		pc->ResetEffectState(EFST_WEAPONPROPERTY);
		pc->m_pcClientUpdater.CPCClientUpdater::MapMove(pc->CPC::GetRestartMapName(), pc->m_characterInfo.sxPos, pc->m_characterInfo.syPos, 0, 0);
	}

	pc->m_pcClientUpdater.CPCClientUpdater::NotifyDisconnect();

	g_mapResMgr.CMapResMgr::DeleteWinPoint(pc->CCharacter::GetMapRes(), pc->GetAccountID());
	if( pc->m_pcClientUpdater.m_disconnectType == MOVE_SERVER || pc->m_pcClientUpdater.m_disconnectType == RESTART_HSERVER )
	{
		pc->CPC::RemovePet();
		pc->m_pcBattle.CPCBattle::RemoveHomun();
	}
	else
	{
		pc->m_pcClientUpdater.CPCClientUpdater::RemoveSectionMgr();
		pc->CPC::RemovePet();
	}

	if( pc->GetState() == CHARACTER_STATE_DEAD && !pc->GetEffective(EFST_TRICKDEAD, 0) )
	{
		memcpy_s(pc->m_characterInfo.mapName, sizeof(pc->m_characterInfo.mapName), pc->CPC::GetRestartMapName(), 16);
		pc->m_pathInfo.CHostPathInfo::InitPosition(pc->m_characterInfo.sxPos, pc->m_characterInfo.syPos, 0);
	}

	if( pc->GetEffective(EFST_MARIONETTE_MASTER, 0) )
	{
		unsigned long masterAID = pc->GetEffective(EFST_MARIONETTE_MASTER, 0);
		this->CCharacterMgr::SendMsg(NULL, masterAID, CM_RESETEFFECTIVE, EFST_MARIONETTE, 0, 0, 0);
	}

	pc->CPC::CancelExchangeItem();

	pc->CPC::SaveShortCut();

	if( pc->m_pcClientUpdater.m_disconnectType == MOVE_SERVER || pc->m_pcClientUpdater.m_disconnectType == RESTART_HSERVER )
		pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_COMPLETE);
	else
		pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_ASYNCDB_SAVE_REQUEST);
*/
}


hook_func<void (__stdcall *)()> CCharacterMgr__OnDisconnect_STEP_COMPLETE(EXEPATH(), "CCharacterMgr::OnDisconnect_STEP_COMPLETE");
void CCharacterMgr::OnDisconnect_STEP_COMPLETE(CPC* pc) // 573-681
{
	void* hookptr = CCharacterMgr__OnDisconnect_STEP_COMPLETE;
	__asm mov edx, pc
	__asm mov ecx, this
	__asm call hookptr
	return; //TODO
/*
	if( pc->m_pcClientUpdater.m_disconnectType != MOVE_SERVER )
	{
		if( pc->GetBodyState() == BODYSTATE_STONECURSE_ING )
			pc->CPC::SetBodyStateTimeInfo(0, 9999, BODYSTATE_STONECURSE);
	}

	if( pc->m_exchangeItemInfo.AID != 0 )
		this->CCharacterMgr::SendMsg(pc, pc->m_exchangeItemInfo.AID, CM_EXCHANGE_ITEM_CANCEL, 0, 0, 0, 0);

	g_roomMgr.CRoomMgr::ExitRoom(pc->CPC::GetRoomID(), pc->m_characterInfo.characterName);

	if( pc->m_pcClientUpdater.m_disconnectType != MOVE_SERVER )
	{
		PACKET_ZI_EXIT zipacket;
		zipacket.PacketType = HEADER_ZI_EXIT;
		zipacket.AID = pc->GetAccountID();
		zipacket.GID = pc->CPC::GetCharacterID();
		memcpy_s(zipacket.charName, sizeof(zipacket.charName), pc->m_characterInfo.characterName, sizeof(pc->m_characterInfo.characterName));
		CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(zipacket), (char*)&zipacket);
	}
	if( pc->m_pcClientUpdater.m_disconnectType != MOVE_SERVER && pc->m_pcClientUpdater.m_disconnectType != RESTART_HSERVER )
	{
		PACKET_ZH_CHAR_EXIT Char_Exit_Protochar;
		Char_Exit_Protochar.PacketType = HEADER_ZH_CHAR_EXIT;
		Char_Exit_Protochar.AID = pc->m_pcClientUpdater.CPCClientUpdater::GetAccountID();
		Char_Exit_Protochar.disconnetedType = pc->m_pcClientUpdater.m_disconnectType;
		CCharacterMgr::GetObj()->CCharacterMgr::SendToHServer(sizeof(Char_Exit_Protochar), (char*)&Char_Exit_Protochar);
	}

	pc->CPC::SavePKInfo();
	pc->CPC::SaveHuntingList();
	pc->CPC::SaveTimeList();

	if( pc->m_pcBattle.CPCBattle::GetMercenary() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "용병이 아직도 존재한다. 오류이다.");
		pc->m_pcBattle.CPCBattle::Mercenary_Release(true);
	}

	if( pc->CCharacter::IsBattleFieldMode() )
	{
		CBattleFieldMapRes* cpBattleFieldMapRes = static_cast<CBattleFieldMapRes*>(pc->CPC::GetMapRes());
		cpBattleFieldMapRes->CBattleFieldMapRes::DeleteAliveMember(pc->GetCampID(), pc->GetAccountID());
	}

	pc->m_DisconnectStep = CPC::DISCONNECTSTEP_REMOVE;
*/
}


hook_func<void (__stdcall *)()> CCharacterMgr__OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST(EXEPATH(), "CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST");
void CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST(CPC* const in_pPlayer) // 686-935
{
	void* hookptr = CCharacterMgr__OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST;
	__asm push in_pPlayer
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CCharacterMgr__OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE(EXEPATH(), "CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE");
void CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE(CPC* pc) // 940-981
{
	void* hookptr = CCharacterMgr__OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE;
	__asm mov ecx, pc
	__asm call hookptr
	return; //TODO
/*
	PACKET_ZH_SAVECHARINFO outpacket;
	outpacket.PacketType = HEADER_ZH_SAVECHARINFO;
	outpacket.AID = pc->GetAccountID();
	outpacket.GID = pc->CPC::GetCharacterID();
	outpacket.AuthCode = pc->m_characterInfo.AuthCode;
	this->CCharacterMgr::SendToHServer(sizeof(outpacket), (char*)&outpacket);

	if( pc->m_pcBattle.m_myHomunID != 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(pc, pc->m_pcBattle.m_myHomunID, CM_SAVE_CHARINFO, pc->CPC::GetCharacterID(), 0, 0, 0);

	pc->m_pcBattle.CPCBattle::RemoveHomun();
	pc->CPC::RemovePet();

	if( pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsStoreOpen() )
		pc->m_pcitemInventoryMgr.m_storeItem.Reset();

	Request request2;
	pc->CPC::OnDispatchClientRequest(&request2);

	pc->m_pcBattle.CPCBattle::Mercenary_Release(true);
	pc->m_Elemental.CPCElemental::Release();
	pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_COMPLETE);
*/
}


void CCharacterMgr::OnDisconnect(CPC* pc) // 984-1030
{
	if( pc == NULL )
		return;

	switch( pc->CPC::GetDisconnectStep() )
	{
	case CPC::DISCONNECTSTEP_NONE:
		this->CCharacterMgr::OnDisconnect_STEP_NONE(pc);
		pc->m_DisconnetTime = timeGetTime();
	break;
	case CPC::DISCONNECTSTEP_ARRANGE:
		this->CCharacterMgr::OnDisconnect_STEP_ARRANGE(pc);
	break;
	case CPC::DISCONNECTSTEP_ASYNCDB_SAVE_REQUEST:
		this->CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST(pc);
	break;
	case CPC::DISCONNECTSTEP_ASYNCDB_SAVE_WAIT:
		;
	break;
	case CPC::DISCONNECTSTEP_ASYNCDB_SAVE_COMPLETE:
		this->CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE(pc);
	break;
	case CPC::DISCONNECTSTEP_COMPLETE:
		this->CCharacterMgr::OnDisconnect_STEP_COMPLETE(pc);
	break;
	case CPC::DISCONNECTSTEP_REMOVE:
		this->CCharacterMgr::OnDisconnect_STEP_REMOVE(pc);
	break;
	default:
		MessageBoxA(NULL, "unknow disconnect type found", "critical", MB_OK);
	break;
	};
}


unsigned long CCharacterMgr::GetAID() // 1033-1047
{
	if( m_AIDPool.size() == 0 )
		return 0;

	unsigned long AID = m_AIDPool.front();
	m_AIDPool.pop_front();

	return AID;
}


void CCharacterMgr::PutAID(unsigned long AID) // 1050-1052
{
	m_AIDPool.push_back(AID);
}


BOOL CCharacterMgr::AddCharacter(CCharacter* pCharacter) // 1055-1126
{
	switch( pCharacter->GetType() )
	{
	case PC_TYPE:
	{
		CPC* cpPC = static_cast<CPC*>(pCharacter);

		EnterCriticalSection(&m_csPC);
		++m_curPlayChar;

		for( int i = 0; i < m_PCCount; ++i )
		{
			if( m_PC[i] == NULL )
			{
				cpPC->m_pcClientUpdater.CPCClientUpdater::SetIndex(i);
				m_PC[i] = cpPC;
				break;
			}
		}

		LeaveCriticalSection(&m_csPC);
	}
	break;
	case NPC_TYPE:
	case NPC_MOB_TYPE:
	case NPC_EVT_TYPE:
	case NPC_PET_TYPE:
	case NPC_HO_TYPE:
	case NPC_MERSOL_TYPE:
	case NPC_ELEMENTAL_TYPE:
	{
		CNPC* cpNPC = static_cast<CNPC*>(pCharacter);

		std::map<int,CNPC*>::iterator iter = m_npcMap.find(pCharacter->GetAccountID());
		if( iter != m_npcMap.end() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AddCharacter(NPC) error in double AID : %d", cpNPC->GetAccountID());
			return FALSE;
		}

		m_npcMap[cpNPC->GetAccountID()] = cpNPC;
	}
	break;
	case ITEM_TYPE:
	{
		CItem* cpItem = static_cast<CItem*>(pCharacter);

		std::map<unsigned long,CItem*>::iterator iter = m_item.find(cpItem->GetAccountID());
		if( iter != m_item.end() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AddCharacter(Item) error in double AID : %d", cpItem->GetAccountID());
			m_item.erase(iter);
		}

		int x = 0;
		int y = 0;
		cpItem->GetParameterValue(VAR_CURXPOS, x);
		cpItem->GetParameterValue(VAR_CURYPOS, y);

		if( !cpItem->CCharacter::GetMapRes()->AddCharacter(x, y, cpItem) )
			return FALSE;

		m_item[cpItem->GetAccountID()] = cpItem;
	}
	break;
	case SKILL_TYPE:
	{
		CSkill* cpSkill = static_cast<CSkill*>(pCharacter);

		std::map<unsigned long,CSkill*>::iterator iter = m_skill.find(cpSkill->GetAccountID());
		if( iter != m_skill.end() )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AddCharacter(Skill - %d) double AID : %d", cpSkill->CSkill::GetSKID(), cpSkill->GetAccountID());
			m_skill.erase(iter);
		}

		int x = cpSkill->CSkill::GetxPos();
		int y = cpSkill->CSkill::GetyPos();

		if( !cpSkill->CCharacter::GetMapRes()->AddCharacter(x, y, cpSkill) )
			return FALSE;

		m_skill[cpSkill->GetAccountID()] = cpSkill;
	}
	break;
	default:
	{
		return FALSE;
	}
	break;
	};

	return TRUE;
}


void CCharacterMgr::RemoveCharacter(CCharacter* pCharacter) // 1130-1229
{
	switch( pCharacter->GetType() )
	{
	case PC_TYPE:
	{
		CPC* cpPC = static_cast<CPC*>(pCharacter);

		EnterCriticalSection(&m_csPC);
		--m_curPlayChar;

		int index = this->CCharacterMgr::FindPC(cpPC);
		if( index >= 0 && index < m_PCCount && m_PC[index] != NULL )
		{
			this->CCharacterMgr::DeletePCFromIndexInfo(pCharacter->GetAccountID());

			CPC* cpPC = m_PC[index];
			g_zsAcceptHandler.CZSAcceptHandler::FreeStream(cpPC->CPC::GetStream());
			cpPC->CPC::Reset();
			this->CCharacterMgr::Free(cpPC);
			m_PC[index] = NULL;
		}

		LeaveCriticalSection(&m_csPC);
	}
	break;
	case NPC_TYPE:
	case NPC_MOB_TYPE:
	case NPC_EVT_TYPE:
	case NPC_PET_TYPE:
	case NPC_HO_TYPE:
	case NPC_MERSOL_TYPE:
	case NPC_ELEMENTAL_TYPE:
	{
		CNPC* cpNPC = static_cast<CNPC*>(pCharacter);

		std::map<int,CNPC*>::iterator iter = m_npcMap.find(cpNPC->GetAccountID());
		if( iter == m_npcMap.end() )
		{
			break;
		}

		if( cpNPC->CNPC::GetJobType() == JT_WARPNPC )
			this->CCharacterMgr::RemoveWarpNpcList(cpNPC->CCharacter::GetMapRes(), cpNPC);

		this->CCharacterMgr::Free(pCharacter);
		m_npcMap.erase(iter);
	}
	break;
	case ITEM_TYPE:
	{
		CItem* cpItem = static_cast<CItem*>(pCharacter);

		std::map<unsigned long,CItem*>::iterator iter = m_item.find(cpItem->GetAccountID());
		if( iter == m_item.end() )
		{
			break;
		}

		iter->second->CItem::OnDisappear();
		this->CCharacterMgr::Free(iter->second);
		m_item.erase(iter);
	}
	break;
	case SKILL_TYPE:
	{
		CSkill* cpSkill = static_cast<CSkill*>(pCharacter);

		std::map<unsigned long,CSkill*>::iterator iter = m_skill.find(cpSkill->GetAccountID());
		if( iter == m_skill.end() )
		{
			break;
		}

		iter->second->CSkill::OnDisappear();
		this->CCharacterMgr::Free(iter->second);
		m_skill.erase(iter);
	}
	break;
	default:
	{
	}
	break;
	};
}


int CCharacterMgr::FindPC(CCharacter* pCharacter) // 1232-1239
{
	for( int i = 0; i < m_PCCount; ++i )
		if( pCharacter == m_PC[i] )
			return i; // found.

	return -1; // not found.
}


CPC* CCharacterMgr::FindCharacter(const char* characterName) // 1242-1249
{
	for( int i = 0; i < m_PCCount; ++i )
	{
		CPC* pc = m_PC[i];

		if( pc != NULL && strncmp(pc->CPC::GetCharacterName(), characterName, 24) == 0 )
			return pc; // found.
	}

	return NULL; // not found.
}


CCharacter* CCharacterMgr::FindCharacter(unsigned long AID, unsigned long Type) // 1252-1274
{
	switch( Type )
	{
	case SKILL_TYPE: return this->CCharacterMgr::SearchSkill(AID);
	case NPC_TYPE:   return this->CCharacterMgr::FindNPCByAID(AID);
	case ITEM_TYPE:  return this->CCharacterMgr::SearchItem(AID);
	case PC_TYPE:    return this->CCharacterMgr::SearchPCFromIndexInfo(AID);
	default:
	{
		CCharacter* ch;
		if     ( (ch = this->CCharacterMgr::SearchSkill(AID))           != NULL ) return ch;
		else if( (ch = this->CCharacterMgr::FindNPCByAID(AID))          != NULL ) return ch;
		else if( (ch = this->CCharacterMgr::SearchItem(AID))            != NULL ) return ch;
		else if( (ch = this->CCharacterMgr::SearchPCFromIndexInfo(AID)) != NULL ) return ch;
		else return NULL;
	}
	};
}


BOOL CCharacterMgr::IsSendable(CPC* pc) // (942-944)
{
	return pc->m_pcClientUpdater.CPCClientUpdater::IsSendable();
}


CItem* CCharacterMgr::SearchItem(unsigned long ITAID) // 1283-1290
{
	std::map<unsigned long,CItem*>::iterator iter = m_item.find(ITAID);
	if( iter == m_item.end() )
		return NULL;

	return iter->second;
}


CSkill* CCharacterMgr::SearchSkill(unsigned long AID) // 1293-1300
{
	std::map<unsigned long,CSkill*>::iterator iter = m_skill.find(AID);
	if( iter == m_skill.end() )
		return NULL;

	return iter->second;
}


CSkill* CCharacterMgr::GetSkill(int xPos, int yPos, CMapRes* mapRes) // 1335-1370
{
	std::vector<CSkill*> list;

	if( mapRes != NULL )
	{
		NEIGHBORHOOD_SECTION sections = {};
		mapRes->CMapRes::GetNeighborhoodSections(xPos, yPos, 15, &sections);

		for( size_t i = 0; i < countof(sections.section); ++i )
		{
			std::vector<CCharacter*>* section = sections.section[i];
			if( section == NULL )
				continue;

			for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
			{
				CCharacter* ch = *iter;
				if( ch->GetType() != SKILL_TYPE )
					continue;

				CSkill* skill = static_cast<CSkill*>(ch);
				if( skill == NULL ) //FIXME: checking for NULL too late
					continue;

				if( !skill->CSkill::IsMyArea(xPos, yPos) )
					continue;

				list.push_back(skill);
			}
		}
	}

	if( list.empty() )
		return NULL;

	return list.front();
}


CSkill* CCharacterMgr::GetSkill(int skillID, int xPos, int yPos, CMapRes* mapRes) // 1449-1501
{
	std::vector<CSkill*> list;

	if( mapRes != NULL )
	{
		NEIGHBORHOOD_SECTION sections = {};
		mapRes->CMapRes::GetNeighborhoodSections(xPos, yPos, 15, &sections);

		for( size_t i = 0; i < countof(sections.section); ++i )
		{
			std::vector<CCharacter*>* section = sections.section[i];
			if( section == NULL )
				continue;

			for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
			{
				CCharacter* ch = *iter;
				if( ch->GetType() != SKILL_TYPE )
					continue;

				CSkill* skill = static_cast<CSkill*>(ch);
				if( skill == NULL ) //FIXME: checking for NULL too late
					continue;

				if( !skill->CSkill::IsMyArea(xPos, yPos) )
					continue;

				list.push_back(skill);
			}
		}
	}

	for( std::vector<CSkill*>::iterator iter = list.begin(); iter != list.end(); ++iter )
	{
		CSkill* skill = *iter;

		if( skillID == skill->CSkill::GetSKID() )
			return skill; // found.
	}

	return NULL; // not found.
}


BOOL CCharacterMgr::GetSkillList(int xPos, int yPos, std::vector<CSkill*>& skList, CCharacter* exceptChar, CMapRes* mapRes) // 1548-1578
{
	if( mapRes != NULL )
	{
		NEIGHBORHOOD_SECTION sections = {};
		mapRes->CMapRes::GetNeighborhoodSections(xPos, yPos, 15, &sections);

		for( size_t i = 0; i < countof(sections.section); ++i )
		{
			std::vector<CCharacter*>* section = sections.section[i];
			if( section == NULL )
				continue;

			for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
			{
				CCharacter* ch = *iter;
				if( ch->GetType() != SKILL_TYPE )
					continue;

				CSkill* skill = static_cast<CSkill*>(ch);
				if( skill == exceptChar )
					continue;

				if( !skill->CSkill::IsMyArea(xPos, yPos) )
					continue;

				skList.push_back(skill);
			}
		}
	}

	return ( !skList.empty() );
}


CPC* CCharacterMgr::FindPCByGID(unsigned long GID) // 1622-1630
{
	for( int i = 0; i < m_PCCount; ++i )
	{
		CPC* pPC = m_PC[i];
		if( pPC == NULL )
			continue;

		if( pPC->m_pcClientUpdater.CPCClientUpdater::GetCharacterID() != GID )
			continue;

		if( m_PC[i]->GetType() != PC_TYPE )
			continue;

		return m_PC[i]; // found.
	}

	return NULL; // not found.
}


CNPC* CCharacterMgr::FindNPCByAID(unsigned long AID) // 1633-1640
{
	std::map<int,CNPC*>::iterator iter = m_npcMap.find(AID);
	if( iter == m_npcMap.end() )
		return NULL;

	return iter->second;
}


CPC* CCharacterMgr::FindCharacterByIndex(const unsigned long in_AID, const int in_Index) const // 1644-1655
{
	if( in_Index < 0 || in_Index >= CGVar::GetObj()->CGVar::GetMaxCharacterCount() )
		return NULL;

	CPC* pc = m_PC[in_Index];
	if( pc == NULL )
		return NULL;

	if( pc->GetType() != PC_TYPE )
		return NULL;

	if( pc->GetAccountID() != in_AID )
		return NULL;

	return pc;
}


CCharacter* CCharacterMgr::FastFindCharacter(unsigned long aID) // 1675-1689
{
	if( aID >= PC_MINIMUM_AID )
		return CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(aID, PC_TYPE);

	CCharacter* ch = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(aID, NPC_TYPE);
	if( ch == NULL )
		ch = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(aID, SKILL_TYPE);

	return ch;
}


void CCharacterMgr::ProcessAllCharacter() // 1946-2171
{
	if( g_zsAcceptHandler.CZSAcceptHandler::GetAcceptable() )
	{
		int NumPlayerValidCount = 0;
		int NumPlayerDisconnectCount = 0;

		for( int i = 0; i < m_PCCount; ++i )
		{
			if( m_PC[i] == NULL )
				continue;

			if( m_PC[i]->CPC::AsyncMonopolyProcess() )
				continue;

			if( !m_PC[i]->CClient::IsErrorClient() )
			{
				if( m_PC[i]->CPC::OnProcess() != -1 )
					m_PC[i]->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());

				if( m_PC[i]->CPC::IsValid() == TRUE )
					++NumPlayerValidCount;
			}
			else
			{
				this->CCharacterMgr::OnDisconnect(m_PC[i]);

				if( m_PC[i] == NULL ) //NOTE: may have been changed by the above call
					++NumPlayerDisconnectCount;

				if( m_PC[i] != NULL )
				{
					if( timeGetTime() - m_PC[i]->m_DisconnetTime < 60000 && timeGetTime() - m_PC[i]->m_DisconnetTime > g_MaxDisconnectTime )
					{
						g_MaxDisconnectTime = timeGetTime() - m_PC[i]->m_DisconnetTime;
						NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Disconnect Timer Over(AID=%d,GID=%d), %d", m_PC[i]->GetAccountID(), m_PC[i]->CPC::GetCharacterID(), g_MaxDisconnectTime);
					}
				}
			}
		}

		m_curValidPlayChar = NumPlayerValidCount;
		m_curDisconnectCountPlayChar = NumPlayerDisconnectCount;

		for( std::map<unsigned long,CSkill*>::iterator skillIter = m_skill.begin(); skillIter != m_skill.end(); )
		{
			CSkill* pSkill = skillIter->second;

			if( pSkill->CSkill::OnProcess() == -1 )
			{
				++skillIter;
			}
			else
			{
				pSkill->CSkill::OnDisappear();
				this->CCharacterMgr::Free(pSkill);
				skillIter = m_skill.erase(skillIter);
			}
		}

		for( std::map<unsigned long,CItem*>::iterator itemIter = m_item.begin(); itemIter != m_item.end(); )
		{
			CItem* pItem = itemIter->second;

			if( pItem->CItem::OnProcess() == -1 )
			{
				++itemIter;
			}
			else
			{
				pItem->CItem::OnDisappear();
				this->CCharacterMgr::Free(pItem);
				itemIter = m_item.erase(itemIter);
			}
		}

		for( std::map<int,CNPC*>::iterator npcIter = m_npcMap.begin(); npcIter != m_npcMap.end(); )
		{
			CNPC* pNPC = npcIter->second;

			if( !pNPC->CClient::IsErrorServer() )
			{
				pNPC->OnProcess();
				++npcIter;
			}
			else
			{
				this->CCharacterMgr::Free(pNPC);
				npcIter = m_npcMap.erase(npcIter);
			}
		}
	}
	else
	{
		int NumPlayerValidCount = 0;
		int NumPlayerDisconnectCount = 0;

		for( int i = 0; i < m_PCCount; ++i )
		{
			if( m_PC[i] == NULL )
				continue;

			if( !m_PC[i]->CPC::AsyncMonopolyProcess() )
			{
				if( !m_PC[i]->CClient::IsErrorClient() )
				{
					if( m_PC[i]->CPC::IsValid() )
						++NumPlayerValidCount;

					if( g_IsDisconnectAll == true )
						m_PC[i]->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
				}
				else
				{
					this->CCharacterMgr::OnDisconnect(m_PC[i]);

					if( m_PC[i] == NULL ) //NOTE: may have been changed by the above call
						++NumPlayerDisconnectCount;
				}
			}
		}

		m_curValidPlayChar = NumPlayerValidCount;
		m_curDisconnectCountPlayChar = NumPlayerDisconnectCount;
	}
}


int CCharacterMgr::GetCurPlayChar() // 2195-2200
{
	return max(0, m_curPlayChar);
}


int CCharacterMgr::GetCurValidPlayChar() // 2232-2234
{
	return m_curValidPlayChar;
}


int CCharacterMgr::GetCurDisconnectCountPlayChar() // 2237-2239
{
	return m_curDisconnectCountPlayChar;
}


void CCharacterMgr::BroadCast(int len, char* buf) // 2254-2260
{
	for( int i = 0; i < m_PCCount; ++i )
	{
		CPC* pc = m_PC[i];

		if( pc != NULL && pc->m_pcClientUpdater.CPCClientUpdater::IsSendable() )
			pc->Send(len, buf);
	}
}


void CCharacterMgr::BroadCastExceptME(int len, char* buf, const char* ID) // 2287-2303
{
	for( int i = 0; i < m_PCCount; ++i )
	{
		CPC* pc = m_PC[i];

		if( pc != NULL && pc->m_pcClientUpdater.CPCClientUpdater::IsSendable() )
			if( strncmp(pc->m_characterInfo.accountName, ID, 24) != 0 )
				pc->Send(len, buf);
	}
}


hook_func<void (__stdcall *)()> CCharacterMgr__CreateItem(EXEPATH(), "CCharacterMgr::CreateItem");
CItem* CCharacterMgr::CreateItem(CITP* itp, ITEM_INFO* itemInfo) // 2306-2329
{
	CItem* result;
	void* hookptr = CCharacterMgr__CreateItem;
	__asm mov edi, itemInfo
	__asm push itp
	__asm push this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


int CCharacterMgr::SendMsg(CCharacter* sender, unsigned long receiverID, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 2715-2721
{
	CCharacter* receiver = this->CCharacterMgr::FindCharacter(receiverID, UNKNOWN_TYPE);
	if( receiver == NULL )
		return 1;

	return receiver->OnMsg(sender, receiver, msgID, par1, par2, par3, par4);
}


int CCharacterMgr::SendMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 2724-2730
{
	if( receiver == NULL )
		return 1;

	return receiver->OnMsg(sender, receiver, msgID, par1, par2, par3, par4);
}


void CCharacterMgr::SendToNPCServer(int len, const char* buf) // 2734-2741
{
	CZNPC2Msg msg;
	msg.CMsg::SetMsgID(ZNPC2MSG_PACKET);
	msg.par1 = len;
	msg.par2 = (int)buf;
	msg.par3 = 0;
	g_npcSvr.CNpcSvr::SendMsg(0, 0, &msg);
}


void CCharacterMgr::SendToHServer(int len, const char* buf) // 2744-2750
{
	C2CharacterServerClient::GetObj()->C2CharacterServerClient::Send(len, buf);
}


void CCharacterMgr::SendToIServer(int len, const char* buf) // 2753-2755
{
	C2InterServerClient::GetObj()->C2InterServerClient::Send(len, buf);
}


void CCharacterMgr::AddPCToIndexInfo(unsigned long AID, int index, unsigned long connectionTime) // 2787-2793
{
	PC_INDEX_DATA& data = m_pcNonclusteredIndex[AID];
	data.index = index;
	data.connectionTime = connectionTime;
}


CCharacter* CCharacterMgr::SearchPCFromIndexInfo(unsigned long AID) // 2796-2806
{
	if( AID < 1 )
		return NULL;

	std::map<unsigned long,PC_INDEX_DATA>::iterator iter = m_pcNonclusteredIndex.find(AID);
	if( iter == m_pcNonclusteredIndex.end() )
		return NULL;

	return this->CCharacterMgr::FindCharacterByIndex(AID, iter->second.index);
}


void CCharacterMgr::DeletePCFromIndexInfo(unsigned long AID) // 2809-2816
{
	std::map<unsigned long,PC_INDEX_DATA>::iterator iter = m_pcNonclusteredIndex.find(AID);
	if( iter == m_pcNonclusteredIndex.end() )
		return;

	m_pcNonclusteredIndex.erase(iter);
}


hook_func<void (__stdcall *)()> CCharacterMgr__GetVar(EXEPATH(), "CCharacterMgr::GetVar");
void CCharacterMgr::GetVar(unsigned long AID, CMsg* reqMsg, CMsg* ansMsg) // 2819-2879
{
	void* hookptr = CCharacterMgr__GetVar;
	__asm push ansMsg
	__asm mov eax, reqMsg
	__asm mov ecx, AID
	__asm mov edx, this
	__asm call hookptr
	return; //TODO
/*
	CCharacter* ch = this->CCharacterMgr::FindCharacter(AID, UNKNOWN_TYPE);
	if( ch == NULL )
		return;

	ansMsg->par1 = 0;

	switch( reqMsg->CMsg::GetMsgID() )
	{
	case MSG_REQVAR:
	{
		unsigned short varID = static_cast<unsigned short>(reqMsg->par1);
		ch->GetParameterValue(varID, ansMsg->par1);
	}
	break;
	case MSG_REQITEMCOUNT:
	{
		if( ch->GetType() != PC_TYPE )
			break;

		unsigned short ITID = static_cast<unsigned short>(reqMsg->par1);
		ansMsg->par1 = static_cast<CPC*>(ch)->CPC::GetItemCount(ITID);
	}
	break;
	case MSG_REQREFINELEVEL:
	{
		if( ch->GetType() != PC_TYPE )
			break;

		unsigned long loc;
		switch( reqMsg->par1 )
		{
		case 1: loc = LOCATION_HEAD; break;
		case 2: loc = LOCATION_BODY; break;
		case 3: loc = LOCATION_LARM; break;
		case 4: loc = LOCATION_RARM; break;
		case 5: loc = LOCATION_ROBE; break;
		case 6: loc = LOCATION_SHOES; break;
		case 7: loc = LOCATION_ACCESSORY1; break;
		case 8: loc = LOCATION_ACCESSORY2; break;
		case 9: loc = LOCATION_HEAD2; break;
		case 10: loc = LOCATION_HEAD3; break;
		default: loc = LOCATION_NOTHING; break;
		};

		IVItEquipItem* equipItem = static_cast<CPC*>(ch)->CPC::GetEquipItem(loc);
		if( equipItem == NULL )
			break;

		ansMsg->par1 = equipItem->IVItEquipItem::GetRefiningLevel();
	}
	break;
	};
*/
}


hook_func<void (__stdcall *)()> CCharacterMgr__GetVarFromPC(EXEPATH(), "CCharacterMgr::GetVarFromPC");
void CCharacterMgr::GetVarFromPC(unsigned long AID, CMsg* reqMsg, CMsg* ansMsg) // 2882-2908
{
	void* hookptr = CCharacterMgr__GetVarFromPC;
	__asm push ansMsg
	__asm mov ebx, reqMsg
	__asm mov ecx, AID
	__asm mov edi, this
	__asm call hookptr
	return; //TODO
/*
	CPC* pc = (CPC*)this->CCharacterMgr::FindCharacter(AID, PC_TYPE);
	if( pc == NULL )
		return;

	switch( reqMsg->CMsg::GetMsgID() )
	{
	case FUNC_GETSKILLLEVEL:
	{
		unsigned short SKID = static_cast<unsigned short>(reqMsg->par1);
		ansMsg->par1 = pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID, TRUE);
	}
	break;
	case FUNC_GETPUREJOB:
	{
		ansMsg->par1 = pc->CPC::GetCategoryFirstJob();
	}
	break;
	case FUNC_GETMERCENARYTOTALSUMMONNUM:
	{
		int job = reqMsg->par1;
		ansMsg->par1 = pc->m_pcBattle.m_Mercenary.CPCBattleMercenary::GetTotalSummonNum(job);
	}
	break;
	case FUNC_GETMERCENARYFAITH:
	{
		int job = reqMsg->par1;
		ansMsg->par1 = pc->m_pcBattle.m_Mercenary.CPCBattleMercenary::GetFaith(job);
	}
	break;
	};
*/
}


void CCharacterMgr::SendCommand(unsigned long AID, CITZMsg* reqMsg) // 2911-2919
{
	CCharacter* ch = this->CCharacterMgr::FindCharacter(AID, PC_TYPE);
	if( ch == NULL )
		ch = this->CCharacterMgr::FindCharacter(AID, NPC_TYPE);
	
	if( ch == NULL )
		return;

	ch->OnMsgFromItemServer(AID, reqMsg);
}


void CCharacterMgr::SendMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2) // 2922-2927
{
	CNPC* npc = (CNPC*)this->CCharacterMgr::FindCharacter(receiverAID, NPC_TYPE);
	if( npc == NULL )
		return;

	CNpcEvt* evt = static_cast<CNpcEvt*>(npc);
	evt->CNpcEvt::OnMsgFromNPCServer(senderAID, receiverAID, msg, par1, par2);
}


int CCharacterMgr::GetPCCountIntheMap(char* mapName) // 2937-2987
{
	if( mapName == NULL )
		return -1;

	CMapRes* mapRes = g_mapResMgr.CMapResMgr::GetMapRes(mapName);
	if( mapRes == NULL )
		return -1;

	int mapID = mapRes->CMapRes::GetID();

	int PCCount = 0;

	for( int i = 0; i < m_PCCount; ++i )
	{
		if( m_PC[i] == NULL )
			continue;

		int mid;
		m_PC[i]->GetParameterValue(VAR_MAPID, mid);
		if( mid == mapID )
			++PCCount;
	}

	return PCCount;
}


void CCharacterMgr::Multicast(CMapRes* mapRes, int xPos, int yPos, int len, char* buf, int range) // 3020-3042
{
	NEIGHBORHOOD_SECTION result = {};
	mapRes->CMapRes::GetNeighborhoodSections(xPos, yPos, range, &result);

	for( int k = 0; k < countof(result.section); ++k )
	{
		std::vector<CCharacter*>* section = result.section[k];
		if( section == NULL )
			return;

		for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch->GetType() != PC_TYPE )
				continue;
			
			int x = 0, y = 0;
			ch->GetParameterValue(VAR_CURXPOS, x);
			ch->GetParameterValue(VAR_CURYPOS, y);

			if( abs(x - xPos) >= range || abs(y - yPos) >= range )
				continue; // not in range

			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, ch->GetAccountID(), CM_SEND_PACKET, len, (int)buf, 0, 0);
		}
	}
}


char* CCharacterMgr::GetCharName(unsigned long AID) // 3054-3060
{
	CPC* pc = (CPC*)this->CCharacterMgr::FindCharacter(AID, PC_TYPE);
	if( pc == NULL )
		return NULL;

	return pc->CPC::GetCharacterName();
}


char* CCharacterMgr::GetGuildName(unsigned long AID) // 3063-3069
{
	CPC* pc = (CPC*)this->CCharacterMgr::FindCharacter(AID, PC_TYPE);
	if( pc == NULL )
		return NULL;

	return pc->CPC::GetGuildName();
}


CNPC* CCharacterMgr::AddNPC(void* p, const unsigned long parentAID, const unsigned long parentGID) // 3075-3129
{
	PACKET_NZ_NEWNPC* pPacket = reinterpret_cast<PACKET_NZ_NEWNPC*>(p);

	CNPC* newNPC = this->CCharacterMgr::AllocNPC(pPacket->npcType);
	if( newNPC == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AllocNPC NULL: name=%s, aid=%d, type=%d, map=%s %d %d\n", pPacket->NPCName, pPacket->NAID, pPacket->npcType, pPacket->mapName, pPacket->xPos, pPacket->yPos);

		int error_npc_count = 0;
		for( std::map<int,CNPC*>::iterator iter = m_npcMap.begin(); iter != m_npcMap.end(); ++iter )
		{
			CNPC* npc = iter->second;
			if( npc != NULL && npc->CClient::GetErrorCount() >= 4 )
				++error_npc_count;
		}

		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "totalMonsterCount %d, errorMonsterCount = %d", m_npcMap.size(), error_npc_count);
		return NULL;
	}

	newNPC->Init();

	if( !newNPC->CNPC::SetAccountID(pPacket->NAID) )
	{
		this->CCharacterMgr::Free(newNPC);
		return NULL;
	}

	if( !this->CCharacterMgr::AddCharacter(newNPC) )
	{
		this->CCharacterMgr::Free(newNPC);
		return NULL;
	}

	newNPC->CNPC::SetParentAID(parentAID);
	newNPC->CNPC::SetParentGID(parentGID);

	if( !newNPC->CNPC::InitByPacket(p) )
	{
		this->CCharacterMgr::RemoveCharacter(newNPC);
		return NULL;
	}

	return newNPC;
}


void CCharacterMgr::RemoveWarpNpcList(CMapRes* mapRes, CNPC* npc) // 3160-3173
{
	if( mapRes == NULL || npc == NULL )
		return;

	WARPNPCLIST::iterator wnlIter = m_WarpNPCList2nd.find(mapRes->CMapRes::GetID());
	if( wnlIter == m_WarpNPCList2nd.end() )
		return;

	unsigned long AID = npc->GetAccountID();
	std::vector<unsigned int>::iterator i;

	for( i = wnlIter->second.begin(); i != wnlIter->second.end(); ++i )
		if( *i == AID )
			break;

	if( i == wnlIter->second.end() )
		return;

	wnlIter->second.erase(i);
}


std::vector<CNPC*> CCharacterMgr::GetWarpNpcList(CMapRes* mapRes) const // 3204-3224
{
	if( mapRes == NULL )
		return std::vector<CNPC*>();

	WARPNPCLIST::const_iterator iter = m_WarpNPCList2nd.find(mapRes->CMapRes::GetID());
	if( iter == m_WarpNPCList2nd.end() )
		return std::vector<CNPC*>();

	std::vector<CNPC*> npclist;
	for( std::vector<unsigned int>::const_iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2 )
	{
		std::map<int,CNPC*>::const_iterator npcIter = m_npcMap.find(*iter2);
		if( npcIter != m_npcMap.end() )
		{
			CNPC* npc = npcIter->second;
			if( npc->CClient::GetErrorCount() < 4 )
				npclist.push_back(npc);
		}
	}

	return npclist;
}


void CCharacterMgr::Flush(int mapID, int guildID, int target) // 3281-3306
{
	for( int i = 0; i < m_PCCount; ++i )
	{
		CPC* pc = m_PC[i];

		if( pc == NULL )
			continue;

		int map_id = 0;
		pc->GetParameterValue(VAR_MAPID, map_id);

		if( map_id != mapID )
			continue;

		int guild_id = 0;
		pc->GetParameterValue(VAR_GDID, guild_id);

		if( guildID == 0 || guildID != guild_id )
		{
			if( target == 0 || guild_id == target )
			{
				pc->m_pcClientUpdater.CPCClientUpdater::SetSendable(1);
				pc->m_pcClientUpdater.CPCClientUpdater::ReStart(0);
			}
		}
	}
}


void CCharacterMgr::RegisterBossInMap(CNPC* npc) // 3358-3374
{
	if( npc == NULL )
		return;

	CMapRes* mapRes = npc->CNPC::GetMapRes();
	if( mapRes == NULL )
		return;

	int mapResID = mapRes->CMapRes::GetID();
	if( this->CCharacterMgr::FindBossInMap(mapResID) )
		return;

	m_bossInMap[mapResID] = npc->GetAccountID();
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, npc, CM_SET_BOSS_IN_MAP, 0, 0, 0, 0);
}


CNPC* CCharacterMgr::FindBossInMap(int mapResID) // 3377-3383
{
	std::map<int,int>::iterator iter = m_bossInMap.find(mapResID);
	if( iter == m_bossInMap.end() )
		return NULL;

	unsigned long AID = iter->second;
	return this->CCharacterMgr::FindNPCByAID(AID);
}


bool CCharacterMgr::InstantMapAdd(const int in_MapID, const CMapInfo& in_MapInfo) // 3465-3467
{
	return CMapInfoMgr::GetObj()->CMapInfoMgr::InstantMapAdd2(in_MapInfo);
}


void CCharacterMgr::InstantMapRemove(const int in_MapID, const std::string in_mapName) // 3488-3492
{
	CMapInfoMgr::GetObj()->CMapInfoMgr::InstantMapRemove(in_mapName);
	WARPNPCLIST::iterator iter = m_WarpNPCList2nd.find(in_MapID);
	if( iter != m_WarpNPCList2nd.end() )
		m_WarpNPCList2nd.erase(iter);
}


int CCharacterMgr::GetSkillSize() const // (155.h)
{
	return m_skillMemoryPool.CMemoryMgr<CSkill>::GetFreeSize();
}


int CCharacterMgr::GetSkillObjCnt() const // 3497-3499
{
	if( this == NULL )
		return 0;

	return m_skillMemoryPool.CMemoryMgr<CSkill>::GetAllocSize();
}


int CCharacterMgr::GetSkillObjCapacity() const // 3501-3503
{
	if( this == NULL )
		return 0;

	return m_skillMemoryPool.CMemoryMgr<CSkill>::GetCapacity();
}


int CCharacterMgr::GetItemObjCnt() const // 3506-3508
{
	if( this == NULL )
		return 0;

	return m_itemMemoryPool.CMemoryMgr<CItem>::GetAllocSize();
}


int CCharacterMgr::GetItemObjCapacity() const // 3511-3513
{
	if( this == NULL )
		return 0;

	return m_itemMemoryPool.CMemoryMgr<CItem>::GetCapacity();
}
