#include "CharacterMgr.h"
#include "Item.h"
#include "ITPMgr.h"
#include "MapRes.h"
#include "MonParameterMgr.h"
#include "NPC.h"
#include "NPCStateUpdater.h"
#include "PC.h"
#include "Struct.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "ZoneScript.h"


CNPCStateUpdater::CNPCStateUpdater() // 60-61
{
}


CNPCStateUpdater::~CNPCStateUpdater() // 64-65
{
}


hook_func<void (__stdcall *)()> CNPCStateUpdater__CheckInput(EXEPATH(), "CNPCStateUpdater::CheckInput");
void CNPCStateUpdater::CheckInput() // 171-196
{
	void* hookptr = CNPCStateUpdater__CheckInput;
	__asm mov ebx, this
	__asm call hookptr
	return; //TODO
}


BOOL CNPCStateUpdater::OnRevengeEnemy(CCharacter* ch) // 1191-1193
{
	return m_npc->CNPC::ProcessRevengeEnemy(ch);
}


void CNPCStateUpdater::OnRevival(unsigned long outputState) // 1419-1463
{
	NpcInfo* info = m_npc->CNPC::GetCharacterInfo(); // simplify code
	CMapRes* mapRes = m_npc->CCharacter::GetMapRes(); // simplify code

	info->virtue = 0;

	int xPos;
	int yPos;
	if( info->revivalXPos == 0 && info->revivalYPos == 0 )
	{
		if( !mapRes->CMapRes::GetRandomPos(xPos, yPos) )
			return;
	}
	else
	{
		xPos = info->revivalXPos;
		yPos = info->revivalYPos;
		if( !mapRes->CMapRes::GetRandomPosByRange(xPos, yPos, info->revivalXRange, info->revivalYRange, m_npc->GetAccountID()) )
		{
			if( !mapRes->CMapRes::GetRandomPos(xPos, yPos) )
				return;
		}
	}

	if( m_npc->m_npcUpdater.CNPCUpdater::InitPosition(xPos, yPos, 0) )
	{
		m_npc->m_npcUpdater.CNPCUpdater::SetValidate(TRUE);
		m_npc->CNPC::SpawnMyMob(info->job);
		m_npcStateInfo.deadTime = 0;
		m_npc->CNPC::SetCurrentFSMState(outputState);
		m_npc->CNPC::InitSkill();
	}
}


hook_func<void (__stdcall *)()> CNPCStateUpdater__CreateItemOnPosition(EXEPATH(), "CNPCStateUpdater::CreateItemOnPosition");
CItem* CNPCStateUpdater::CreateItemOnPosition(unsigned short itmID, int count) // 1620-1671
{
	CItem* result;
	void* hookptr = CNPCStateUpdater__CreateItemOnPosition;
	__asm push count
	__asm mov dx, itmID
	__asm mov ecx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


hook_func<void (__stdcall *)()> CNPCStateUpdater__DropItem(EXEPATH(), "CNPCStateUpdater::DropItem");
void CNPCStateUpdater::DropItem(unsigned long killer) // 1674-2016
{
	void* hookptr = CNPCStateUpdater__DropItem;
	__asm mov edx, killer
	__asm mov ecx, this
	__asm call hookptr
	return; //TODO
/*
	MONPARAMETER* par = g_monParameter.CMonParameterMgr::GetMonParameter(m_npc->m_characterInfo.job);
	if( par == NULL )
		return;

	int count = 1;

	SORTED_PCLIST sortedList[3] = {};
	sortedList[0].limitTime = 0;
	sortedList[1].limitTime = 3000;
	sortedList[2].limitTime = 5000;
	if( m_npc->m_characterInfo._class == NPC_CLASS_BOSS )
	{
		sortedList[1].limitTime = 10000;
		sortedList[2].limitTime = 20000;
	}
	m_npc->m_npcUpdater.CNPCUpdater::GetPickableSortList(sortedList);

	CPC* killerPC = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(killer, PC_TYPE);
	if( killerPC != NULL )
	{
		std::map<unsigned short,int> dropList = killerPC->m_pcBattle.m_dropItemOfRace_KILL[m_npc->m_characterInfo.race];
		for( std::map<unsigned short,int>::iterator iter = dropList.begin(); iter != dropList.end(); ++iter )
		{
			unsigned short ITID = iter->first;
			int rate = iter->second;

			if( GetServerRandom(0, 20000) % 10000 < rate )
			{
				CItem* item = this->CNPCStateUpdater::CreateItemOnPosition(ITID, count);
				if( item != NULL )
				{
					this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
					++count;
				}
			}
		}

		std::map<unsigned short,int> dropItemMap;
		if( killerPC->m_pcBattle.CPCBattle::GetDropItemOfMonster_Kill(m_npc->m_characterInfo.job, &dropItemMap) == true )
		{
			for( std::map<unsigned short,int>::iterator iter = dropItemMap.begin(); iter != dropItemMap.end(); ++iter )
			{
				unsigned short ITID = iter->first;
				int rate = iter->second;

				if( GetServerRandom(0, 20000) % 1000 < rate ) //NOTE: 1:1000 scale
				{
					CItem* item = this->CNPCStateUpdater::CreateItemOnPosition(ITID, count);
					if( item != NULL )
					{
						this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
						++count;
					}
				}
			}
		}

		for( int i = ITMGROUP_ORE; i < ITMGROUP_LAST; ++i )
		{
			if( killerPC->m_pcBattle.m_optionInfo.receiveITMGROUP_ID[i] == true )
			{
				unsigned short ITID = g_zoneScript.CZoneScript::GetITMFromGroupID(i);

				CItem* item = this->CNPCStateUpdater::CreateItemOnPosition(ITID, count);
				if( item != NULL )
				{
					this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
					++count;
				}
			}
		}
	}

	CPC* pFirstPc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(sortedList[0].AID, PC_TYPE);

	BOOL bisBPBang = FALSE;
	double DropFactor = 0;
	if( pFirstPc != NULL )
	{
		bisBPBang = pFirstPc->CPC::IsPcBang();
		if( bisBPBang == TRUE && pFirstPc->CPC::GetPcBangInfo() != NULL )
		{
			DropFactor = pFirstPc->CPC::GetPcBangInfo()->DropFactor;
			if( DropFactor == 0 )
				return;
		}
	}

	int cashItemPlusDrop = 0;
	if( pFirstPc != NULL )
	{
		cashItemPlusDrop = pFirstPc->m_pcBattle.m_optionInfo.receiveItem_Equip + pFirstPc->GetEffective(EFST_CASH_RECEIVEITEM, 0);
	}

	int dropLevelRatio = 100;
	if( m_npc->m_characterInfo._class != NPC_CLASS_FIXED_ITEMDROP )
	{
		if( pFirstPc != NULL )
		{
			int atkerLv;
			pFirstPc->GetParameterValue(VAR_CLEVEL, atkerLv);
			dropLevelRatio = CLevelPenaltyMgr::GetObj()->CLevelPenaltyMgr::GetItemDropPercent(m_npc, atkerLv);
		}
	}

	for( int i = 0; i < countof(par->itemInfo); ++i )
	{
		short srand = GetServerRandom(0, 20000) % 10000;
		unsigned short ITID = par->itemInfo[i].ITID;
		int percent = par->itemInfo[i].percent;

		if( percent == 0 && ITID == ITID_APPLE )
			srand = 10000;

		int DropValue = percent;

		if( dropLevelRatio != 100 )
			DropValue = percent * dropLevelRatio / 100;

		if( DropValue < 9000 )
		{
			if( bisBPBang == TRUE )
			{
				DropValue = int(DropValue * DropFactor);
				if( DropValue > 9000 )
					DropValue = 9000;
			}

			if( cashItemPlusDrop != 0 )
			{
				DropValue += percent * cashItemPlusDrop / 100;
				if( DropValue > 9000 )
					DropValue = 9000;
			}
		}

		if( srand <= DropValue )
		{
			CItem* item = this->CNPCStateUpdater::CreateItemOnPosition(ITID, count);
			if( item != NULL )
			{
				this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
				++count;
			}
		}
	}

	if( pFirstPc != NULL )
	{
		if( CPC::GetCategorySecondJob(pFirstPc->m_characterInfo.job) == JT_BLACKSMITH )
		{
			if( pFirstPc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_BS_FINDINGORE, 0) >= 1 )
			{
				unsigned short ITID = g_zoneScript.CZoneScript::GetITMFromGroupID(ITMGROUP_ORE);
				if( ITID != 0 )
				{
					CItem* item = this->CNPCStateUpdater::CreateItemOnPosition(ITID, count);
					if( item != NULL )
					{
						this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
						++count;
					}
				}
			}
		}
	}

	count = 1;

	for( std::list<EATING_ITEM_INVENTORY*>::iterator iter = m_npc->m_eatingItem.begin(); iter != m_npc->m_eatingItem.end(); iter = m_npc->m_eatingItem.erase(iter) )
	{
		ITEM_INFO itemInfo;

		int x = m_npc->m_pathInfo.m_moveInfo.xPos + count % 3 - 1;       // [ 0, +1, -1]
		int y = m_npc->m_pathInfo.m_moveInfo.yPos + (count + 1) % 3 - 1; // [+1, -1,  0]
		m_npc->m_mapRes->CMapRes::GetEmptyPosition(m_npc->GetAccountID(), x, y);

		itemInfo.xPos = x;
		itemInfo.yPos = y;
		itemInfo.mapRes = m_npc->m_mapRes;
		itemInfo.count = (*iter)->count;
		itemInfo.IsIdentified = (*iter)->IsIdentified;
		itemInfo.unique_identity_numberV2 = (*iter)->unique_identity_numberV2;
		itemInfo.hire_expire_date = (*iter)->hire_expire_date;
		itemInfo.IsDamaged = (*iter)->IsDamaged;
		itemInfo.RefiningLevel = (*iter)->RefiningLevel;
		CopyEquipItemSlotInfo(&itemInfo.slot, &(*iter)->slot);
		if( (*iter)->DropMonsterName[0] != '\0' )
			memcpy_s(itemInfo.DropMonsterName, sizeof(itemInfo.DropMonsterName), m_npc->GetNamePtr(), 24);

		CITP* itp = g_itpMgr.CITPMgr::GetITP((*iter)->ITID);

		CItem* item = CCharacterMgr::GetObj()->CCharacterMgr::CreateItem(itp, &itemInfo);
		if( item != NULL )
		{
			this->CNPCStateUpdater::NotifyPickupablePCToItem(item, sortedList);
			++count;
		}

		m_npc->m_eatingItemMPool.CMemoryMgr<EATING_ITEM_INVENTORY>::Free(*iter);
	}
*/
}


void CNPCStateUpdater::NotifyPickupablePCToItem(CItem* item, SORTED_PCLIST* sortedPCList) // 2019-2031
{
	if( item == NULL )
		return;

	unsigned long time = ( m_npc->m_characterInfo._class != NPC_CLASS_BOSS ) ? 7000 : 22000;
	item->CItem::SetPickableTime(time);

	for( int i = 0; i < 3; ++i )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sortedPCList[i].AID, CM_AUTHORIZE_ITEM, (int)item, sortedPCList[i].limitTime, 0, 0);
}


void CNPCStateUpdater::SetFSM(CFSM* fsm) // 2470-2472
{
	m_fsm = fsm;
}
