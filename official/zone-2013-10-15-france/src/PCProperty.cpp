#include "PC.h"
#include "PCProperty.h"
#include "SkillTypeInfoMgr.h"


CPCProperty::CPCProperty(CPC* pc)
{
	m_pc = pc;
	this->CPCProperty::Reset();
}


void CPCProperty::Reset()
{
	memset(&m_propertys, 0, sizeof(m_propertys));
}


hook_func<void (__stdcall *)()> CPCProperty__UpdateStatusAttPower(EXEPATH(), "CPCProperty::UpdateStatusAttPower");
void CPCProperty::UpdateStatusAttPower()
{
	void* hookptr = CPCProperty__UpdateStatusAttPower;
	__asm mov eax, this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPCProperty__UpdateItemAttPower(EXEPATH(), "CPCProperty::UpdateItemAttPower");
void CPCProperty::UpdateItemAttPower()
{
	void* hookptr = CPCProperty__UpdateItemAttPower;
	__asm mov esi, this
	__asm call hookptr
	return; //TODO
}


void CPCProperty::UpdateStatusDef()
{
	int lv = m_pc->m_characterInfo.clevel;
	int vit = m_pc->CPC::GetVitValue();
	int agi = m_pc->CPC::GetAgiValue();

	int angelusRate = m_pc->GetEffective(EFST_ANGELUS, 0);
	if( angelusRate != 0 )
		vit += vit * angelusRate / 100;

	int provokeLevel = m_pc->GetEffective(EFST_PROVOKE, 0);
	if( provokeLevel != 0 )
	{
		if( provokeLevel > 10 )
			provokeLevel = 10;
		vit -= vit * 5 * (provokeLevel + 1) / 100;
	}

	m_propertys.statusDef = int((lv + vit) / 2.0 + agi / 5.0);
}


void CPCProperty::UpdateStatusMagicPower()
{
	int lv = m_pc->m_characterInfo.clevel;
	int int_ = m_pc->CPC::GetIntValue();
	int dex = m_pc->CPC::GetDexValue();
	int luk = m_pc->CPC::GetLukValue();

	m_propertys.statusMagicPower = dex / 5 + luk / 3 + int_ + int_ / 2 + lv / 4;
}


void CPCProperty::UpdateStatusMagicDef()
{
	int lv = m_pc->m_characterInfo.clevel;
	int int_ = m_pc->CPC::GetIntValue();
	int dex = m_pc->CPC::GetDexValue();
	int vit = m_pc->CPC::GetVitValue();

	m_propertys.statusMDef = int((vit + dex) / 5.0 + int_ + lv / 4.0);
}


void CPCProperty::UpdateStatusMagicPowerReduce()
{
	int agi = m_pc->CPC::GetAgiValue();
	int luk = m_pc->CPC::GetLukValue();

	m_propertys.statusMPowerReduce = (agi + luk) / 10;
}


void CPCProperty::UpdateItemMagicPower()
{
	int plusItemPower = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSMAGICPOWEROFITEM);
	m_propertys.itemMPowerMin = 0;
	m_propertys.itemMPowerMax = 0;
	if( plusItemPower != 0 )
	{
		CITP* itp = m_pc->CPC::GetITPEquipedWeapon();
		int itemLv = ( itp != NULL ) ? itp->GetItemLevel() : 1;
		m_propertys.itemMPowerMin = plusItemPower - 10 * itemLv * plusItemPower / 100;
		m_propertys.itemMPowerMax = plusItemPower + 10 * itemLv * plusItemPower / 100;
	}
}


void CPCProperty::UpdateCriticalSuccessValue()
{
	int lv = m_pc->m_characterInfo.clevel;
	int luk = m_pc->CPC::GetLukValue();
	int criPercent = m_pc->m_characterInfo.criPercent;

	m_propertys.criticalSuccess = lv / 10
	                            + m_pc->GetEffective(EFST_EXPLOSIONSPIRITS, 0)
	                            + criPercent
	                            + 3 * luk
	                            + 10;
}


void CPCProperty::UpdateCriticalDef()
{
	m_propertys.criticalDef = m_pc->m_characterInfo.clevel / 15 + 2 * m_pc->CPC::GetLukValue();
}


namespace {
bool EXCEPTION_UpdateAvoidableSucPerOnClient_FixedFlee(CPC* in_pPlayer, int& io_Flee)
{
	if( in_pPlayer->GetEffective(EFST_TINDER_BREAKER, 0) )
	{
		io_Flee = 0;
		return true;
	}

	int flee = in_pPlayer->GetEffective(EFST_OVERED_BOOST, 0);
	if( flee != 0 )
	{
		io_Flee = flee;
		return true;
	}

	return false;
}
}; // namespace


void CPCProperty::UpdateAvoidableSucPerOnClient()
{
	if( EXCEPTION_UpdateAvoidableSucPerOnClient_FixedFlee(m_pc, m_propertys.basicAvoidance) )
		return;

	int lv = m_pc->m_characterInfo.clevel;
	int agi = m_pc->CPC::GetAgiValue();
	int luk = m_pc->CPC::GetLukValue();

	int lv_tf_miss = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_TF_MISS, 0);
	int tf_miss = 0;
	if( lv_tf_miss != 0 )
	{
		tf_miss = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(NULL, SKID_TF_MISS, SM_GETINFO_SKILL, lv_tf_miss, 0, 0, 0);

		int job = CPC::GetCategorySecondJob(m_pc->m_characterInfo.job);
		if( job == JT_ROGUE || job == JT_ASSASSIN )
			tf_miss += lv_tf_miss;
	}

	int lv_mo_dodge = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_MO_DODGE, 0);
	int mo_dodge = 0;
	if( lv_mo_dodge != 0 )
	{
		mo_dodge = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(m_pc, SKID_MO_DODGE, SM_GETINFO_SKILL, lv_mo_dodge, 0, 0, 0);
	}

	int spiderweb = m_pc->GetEffective(EFST_SPIDERWEB, 0) ? 50 : 0;

	m_propertys.basicAvoidance = agi
	                           + tf_miss
	                           + mo_dodge
	                           + m_pc->CPC::InstanceCharBuff().CCharBuff::GetParameterValue(VAR_BASICAVOIDANCE)
	                           + luk / 5
	                           + m_pc->CPC::GetExtDodgePercent()
	                           - spiderweb
	                           + lv
	                           + 100;

	m_propertys.basicAvoidance -= m_propertys.basicAvoidance * this->CPCProperty::GetAvoidDecPercent() / 100;
}


hook_func<int (CPCProperty::*)()> CPCProperty__GetAvoidDecPercent(EXEPATH(), "CPCProperty::GetAvoidDecPercent");
int CPCProperty::GetAvoidDecPercent()
{
	return (this->*CPCProperty__GetAvoidDecPercent)(); //TODO
/*
	fatsovector<int> List(6);
	int val;

	val = m_pc->GetHealthState() & HEALTHSTATE_FEAR ? 20 : 0; List.push_back(val);
	val = m_pc->GetEffective(EFST_PARALYSE, 0) ? 10 : 0; List.push_back(val);
	val = m_pc->GetEffective(EFST_INFRAREDSCAN, 0); List.push_back(val);
	val = m_pc->GetHealthState() & HEALTHSTATE_BLIND ? 25 : 0; List.push_back(val);
	val = m_pc->GetEffective(EFST_PYREXIA, 0) ? 25 : 0; List.push_back(val);
	val = m_pc->GetEffective(EFST_FIRE_EXPANSION_TEAR_GAS, 0) ? 50 : 0; List.push_back(val);

	return *std::max_element(List.begin(), List.end());
*/
}


int CPCProperty::GetBasicHitDecPercent()
{
	std::vector<short> DecPercentList;
	int val;

	val = m_pc->GetHealthState() & HEALTHSTATE_FEAR ? 20 : 0; DecPercentList.push_back(val);
	val = m_pc->GetEffective(EFST_FIRE_EXPANSION_TEAR_GAS, 0) ? 50 : 0; DecPercentList.push_back(val);
	val = m_pc->GetEffective(EFST_PARALYSE, 0) ? 10 : 0; DecPercentList.push_back(val);
	val = m_pc->GetEffective(EFST_INFRAREDSCAN, 0); 	DecPercentList.push_back(val);
	val = m_pc->GetHealthState() & HEALTHSTATE_BLIND ? 25 : 0; DecPercentList.push_back(val);
	val = m_pc->GetEffective(EFST_PYREXIA, 0) ? 25 : 0; DecPercentList.push_back(val);

	return *std::max_element(DecPercentList.begin(), DecPercentList.end());
}


void CPCProperty::UpdateAttSucPercentOnClient()
{
	m_propertys.basicHit = m_pc->CPC::InstanceCharBuff().CCharBuff::GetParameterValue(VAR_HITSUCCESSVALUE)
	                     + m_pc->GetEffective(EFST_LKCONCENTRATION, 0)
	                     + m_pc->CPC::GetDexValue()
	                     + m_pc->CPC::GetLukValue() / 3
	                     + m_pc->CPC::GetPlusHitPercent()
	                     + m_pc->m_characterInfo.clevel
	                     + 175;

	m_propertys.basicHit -= m_propertys.basicHit * this->CPCProperty::GetBasicHitDecPercent() / 100;
}


hook_func<void (__stdcall *)()> CPCProperty__UpdateAttackMotionTime(EXEPATH(), "CPCProperty::UpdateAttackMotionTime");
void CPCProperty::UpdateAttackMotionTime()
{
	void* hookptr = CPCProperty__UpdateAttackMotionTime;
	__asm push this
	__asm call hookptr
	return; //TODO
}


void CPCProperty::ItemPowerModifiedByLevelAndDex(int& value)
{
	m_pc->CPC::GetDexValue(); //NOTE: unused
}


int CPCProperty::GetAttackMotionTime_STD()
{
	int result = (m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_GS_SINGLEACTION, 0) + 1) / 2
	           + m_pc->CPC::GetAttackHasteValue1()
	           + m_pc->CPC::GetAttackHasteValue2();

	CITP* itp = m_pc->CPC::GetITPEquipedWeapon();
	if( itp != NULL && itp->GetClass() == WEAPONTYPE_BOOK )
	{
		int skLevel = m_pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_SA_ADVANCEDBOOK, 0);
		if( skLevel != 0 )
			result += (skLevel - 1) / 2 + 1;
	}

	return result;
}


void CPCProperty::UpdateNotifyItemPower()
{
	m_propertys.notifyItemPower = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSATTACKPOWEROFITEM_RHAND)
	                            + m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSATTREFININGPOWEROFITEM_RHAND)
	                            + m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSATTACKPOWEROFITEM_LHAND)
	                            + m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSATTREFININGPOWEROFITEM_LHAND)
	                            + m_pc->m_characterInfo.extAttPower
	                            + m_pc->GetEffective(EFST_IMPOSITIO, 0)
	                            + m_pc->GetEffective(EFST_STRIKING, 0);
}


void CPCProperty::UpdateNotifyItemMPower()
{
	m_propertys.notifyItemMPower = m_pc->m_characterInfo.extAttMPower
	                             + m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSMAGICPOWEROFITEM);
}


void CPCProperty::UpdateNotifyItemDef()
{
	this->m_propertys.notifyItemDef = m_pc->m_characterInfo.extItemDefPower
	                                + m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSDEFPOWEROFITEM)
	                                + m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSDEFREFININGPOWEROFITEM);
}


void CPCProperty::UpdateNotifyItemMDef()
{
	m_propertys.notifyItemMDef = m_pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetPlusPowerOfItem(VAR_PLUSMDEFPOWEROFITEM)
	                           + m_pc->m_characterInfo.extMagicDefPower
	                           + m_pc->GetEffective(EFST_ENDURE_MDEF, 0);
}
