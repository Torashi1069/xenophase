#include "Actor.h"
#include "ActorSchedulerIdentity.h"
#include "Character.h"
#include "CharacterMgr.h"
#include "CharSkill.h"
#include "Enum.h"
#include "EStateTypeInfo3rd1_blreo.h"
#include "EStateTypeInfo3rd2_blreo.h"
#include "EStateTypeInfoMgr.h"
#include "FSMState.h"
#include "PC.h"
#include "ScriptEventHandler.h"
#include "SkillScriptHandler.h"
#include "SkillTypeInfo2.h"
#include "SkillTypeInfo3rd1_Warlock.h"
#include "SkillTypeInfoMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "ZoneScript.h"
#include "Common/Packet.h"


CActor::CActor()
{
}


CActor::~CActor()
{
}


void CActor::Process()
{
	m_Scheduler.ActorScheduler::CScheduler::Process(this);
}


void CActor::InsertSchedule(std::tr1::shared_ptr<ActorScheduler::CTask>& in_TaskPtr)
{
	m_Scheduler.ActorScheduler::CScheduler::Insert(in_TaskPtr);
}


void CActor::DeleteSchedule(const unsigned long in_Identity)
{
	m_Scheduler.ActorScheduler::CScheduler::Delete(in_Identity);
}


void CActor::Init()
{
	this->CCharacter::Init();
	m_FixedSKcasingTMvar.CFixedSKcastingTMvar::Init();
	m_Scheduler.ActorScheduler::CScheduler::Init();
	m_MspdSlowPercentEfstList.clear();
	m_MspdHastePercentEfstList.clear();
	m_AspdSlowPercentEfstList.clear();
	m_AspdHastePercentEfstList.clear();
}


int CActor::GetStateDBFmt(unsigned char* out_pData, const int in_MaxBytes) const
{
	class CStateDBTime
	{
	private:
		/* this+0 */ //const CStateDBTime::`vftable';
		/* this+4 */ const DWORD m_CutTime;

	public:
		DWORD operator()(DWORD in_StateTime)
		{
			if( in_StateTime == 9999 )
				return 9999;

			if( in_StateTime <= m_CutTime )
				return 0;

			DWORD outTime = (in_StateTime - m_CutTime) / 1000;
			if( outTime == 9999 )
				outTime = 9998;
			return outTime;
		}

	public:
		CStateDBTime() : m_CutTime(timeGetTime()) { }
		virtual ~CStateDBTime() { }
	};

	CStateDBTime GetStateDBTime;
	int offset = 0;

	*(WORD*)(out_pData + offset + 0) = static_cast<WORD>(m_BodyStateValue);
	*(WORD*)(out_pData + offset + 2) = static_cast<WORD>(GetStateDBTime(m_BodyStateTime[1]));
	offset += 4;

	for( int i = 0; i < countof(m_HealthStateTime); ++i )
	{
		if( offset > in_MaxBytes - 4 )
			break; // no more room.

		if( m_HealthStateTime[i][1] != 0 )
		{
			*(WORD*)(out_pData + offset + 0) = 1 << i;
			*(WORD*)(out_pData + offset + 2) = static_cast<WORD>(GetStateDBTime(m_HealthStateTime[i][1]));
			offset += 4;
		}
	}

	*(WORD*)(out_pData + offset) = -1;
	offset += 2;

	for( EFFECTSTATEMAP::const_iterator iter = m_effectStateTimeL.begin(); iter != m_effectStateTimeL.end(); ++iter )
	{
		if( offset > in_MaxBytes - 6 )
			break; // no more room.

		int mask = iter->first;
		if( mask == EFFECTSTATE_BURROW )
			continue;

		if( m_characterPInfo.effectState & mask )
		{
			*(DWORD*)(out_pData + offset + 0) = mask;
			*( WORD*)(out_pData + offset + 4) = static_cast<WORD>(GetStateDBTime(iter->second));
			offset += 6;
		}
	}

	return offset;
}


void CActor::SetStateDBFmt(const unsigned char* in_pData, const int in_Length)
{
	if( in_Length <= 0 )
		return;

	DWORD curTime = timeGetTime();
	int offset = 0;

	DWORD state = *(WORD*)(in_pData + offset + 0);
	WORD time = *(WORD*)(in_pData + offset + 2);
	offset += 4;

	if( time > 300 )
		time = 0;

//	m_BodyStateValue = state; //NOTE: unused?

	int bodyStateTM = ( time == 9999 ) ? 9999 : curTime + 1000 * time;
	m_BodyStateTime[1] = bodyStateTM;

	while( offset < in_Length )
	{
		WORD bitflag = *(WORD*)(in_pData + offset);
		offset += 2;

		if( bitflag == -1 )
			break; // separator

		WORD time = *(WORD*)(in_pData + offset);
		offset += 2;

		int healthStateTM = ( time == 9999 ) ? 9999 : curTime + 1000 * time;
		m_HealthStateTime[GetIndexFromBitFlag(bitflag)][1] = healthStateTM;
	}

	while( offset < in_Length )
	{
		DWORD state = *(DWORD*)(in_pData + offset + 0);
		WORD time = *(WORD*)(in_pData + offset + 4);
		offset += 6;

		int efstTM = ( time == 9999 ) ? 9999 : 1000 * time;
		this->SetEffectStateTimeInfo(efstTM, state);
	}
}


void CActor::ResetStatusAmount(unsigned short SKID, unsigned short type)
{
	std::map<int,std::map<unsigned short,AmountValue>>::iterator iter = m_statusEffInfo.find(SKID);
	if( iter == m_statusEffInfo.end() )
		return;

	std::map<unsigned short,AmountValue>& info = iter->second;
	if( type == 0 )
	{
		std::map<unsigned short,AmountValue>::iterator it = info.begin();
		while( it != info.end() )
		{
			this->NotifyStatusAmount(it->first, -it->second.resetAmount);
			it = info.erase(it);
		}

		m_statusEffInfo.erase(iter);
	}
	else
	{
		std::map<unsigned short,AmountValue>::iterator it = info.find(type);
		if( it != info.end() )
		{
			this->NotifyStatusAmount(it->first, -it->second.resetAmount);
			info.erase(it);
		}

		if( info.size() == 0 )
			m_statusEffInfo.erase(iter);
	}
}


void CActor::ProcessStatusAmount()
{
	for( std::map<int,std::map<unsigned short,AmountValue>>::iterator iter = m_statusEffInfo.begin(); iter != m_statusEffInfo.end(); )
	{
		for( std::map<unsigned short,AmountValue>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); )
		{
			if( iter2->second.time == 9999 || timeGetTime() <= iter2->second.time )
			{
				++iter2;
			}
			else
			{
				this->NotifyStatusAmount(iter2->first, -iter2->second.resetAmount);
				iter2 = iter->second.erase(iter2);
			}
		}

		if( iter->second.size() != 0 )
		{
			++iter;
		}
		else
		{
			iter = m_statusEffInfo.erase(iter);
		}
	}
}


int CActor::GetCountInArea(int xPos, int yPos, int range, BOOL isAffectPlayer, BOOL isAffectTrap, BOOL isDeadPlayer)
{
	if( m_mapRes == NULL )
		return 0;

	if( range == 0 )
		range = 1;

	NEIGHBORHOOD_SECTION result = {};
	m_mapRes->CMapRes::GetNeighborhoodSections(xPos, yPos, range, &result);

	int count = 0;

	for( int k = 0; k < countof(result.section); ++k )
	{
		std::vector<CCharacter*>* section = result.section[k];
		if( section == NULL )
			continue;

		for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch == NULL )
				continue;

			if( ch == this && !isAffectPlayer )
				continue;

			if( !ch->IsTarget(this, TARGET_TRAP | TARGET_EXCEPT_BETWEEN_MOB) )
			{
				if( ch->GetType() != PC_TYPE )
					continue;

				if( !isAffectPlayer )
					continue;
			}
			else
			{
				if( isDeadPlayer && ch->GetState() == CHARACTER_STATE_DEAD )
					continue;

				if( ch->GetType() == SKILL_TYPE && !isAffectTrap )
					continue;
			}

			int otherXPos;
			int otherYPos;
			ch->GetParameterValue(VAR_CURXPOS, otherXPos);
			ch->GetParameterValue(VAR_CURYPOS, otherYPos);

			if( abs(xPos - otherXPos) <= range && abs(yPos - otherYPos) <= range )
				++count;
		}
	}

	return count;
}


void CActor::GetPushedPosition(PosInfo src, PosInfo dest, int distance, PosInfo& result)
{
	if( m_mapRes == NULL )
	{
		result.x = dest.x;
		result.y = dest.y;
		return;
	}

	int incx = (dest.x - src.x > 0) ? 1 : -1;
	int incy = (dest.y - src.y > 0) ? 1 : -1;
	int i;

	float decl = float((double)(dest.y - src.y) / ((double)(dest.x - src.x) + 0.001));
	if( fabs(decl) <= 1/3.0 )
	{
		int x = dest.x;
		incy = 0;

		for( i = 1; i <= distance; ++i )
		{
			x += incx;
			if( !m_mapRes->CMapRes::IsMovableCell(x, dest.y) )
				break;
		}
	}
	else
	if( fabs(decl) >= 3.0 )
	{
		int y = dest.y;
		incx = 0;

		for( i = 1; i <= distance; ++i )
		{
			y += incy;
			if( !m_mapRes->CMapRes::IsMovableCell(dest.x, y) )
				break;
		}
	}
	else
	{
		int x = dest.x;
		int y = dest.y;

		for( i = 1; i <= distance; ++i )
		{
			x += incx;
			y += incy;
			if( !m_mapRes->CMapRes::IsMovableCell(x, y) )
				break;
		}
	}

	result.x = dest.x + incx * (i - 1);
	result.y = dest.y + incy * (i - 1);
}


int CActor::GetModifiedTargetItemDEF2(CCharacter* in_cpTargetCH)
{
	int targetItemDef = 0;
	in_cpTargetCH->GetParameterValue(VAR_ITEMDEFPOWER, targetItemDef);
	return targetItemDef;
}


int CActor::GetModifiedTargetItemDEF(CCharacter* target)
{
	int targetItemDef;
	target->GetParameterValue(VAR_ITEMDEFPOWER, targetItemDef);
	return targetItemDef;
}


int CActor::GetModifiedTargetStatusDEF2(CCharacter* in_cpTargetCH)
{
	if( in_cpTargetCH->GetEffective(VAR_DEXAMOUNT, 0) > 0 )
		return 0;

	int targetStatusDef = 0;
	in_cpTargetCH->GetParameterValue(VAR_STATUSDEFPOWER, targetStatusDef);
	return targetStatusDef;
}


int CActor::GetModifiedTargetStatusDEF(CCharacter* target)
{
	int targetStatusDef;
	target->GetParameterValue(VAR_STATUSDEFPOWER, targetStatusDef);
	return targetStatusDef;
}


int CActor::GetModifiedTargetItemMDEF(CCharacter* target)
{
	int targetItemMdef;
	target->GetParameterValue(VAR_MAGICITEMDEFPOWER, targetItemMdef);
	return targetItemMdef;
}


int CActor::GetEffective(int index, int enumVal)
{
	if( enumVal >= countof(EFFECTIVE_INFO().val) )
		return 0;

	EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.find(index);
	if( iter == m_effectiveList.end() )
		return 0;

	return iter->second.val[enumVal];
}


void CActor::UpdateEffective(int index, int val, int enumVal)
{
	if( enumVal >= countof(EFFECTIVE_INFO().val) )
		return;

	EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.find(index);
	if( iter == m_effectiveList.end() )
		return;

	iter->second.val[enumVal] += val;
}


void CActor::UpdateEffectiveTime(int index, int time)
{
	EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.find(index);
	if( iter == m_effectiveList.end() )
		return;

	iter->second.time = timeGetTime() + time;
}


EFFECTIVE_INFO* CActor::GetEffectiveInfo(int index)
{
	EFFECTIVE_CONTAINER::iterator it = m_effectiveList.find(index);
	if( it == m_effectiveList.end() )
		return NULL;

	return &it->second;
}


void CActor::ProcessAllEffective()
{
	DWORD time = timeGetTime();
	for( EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.begin(); iter != m_effectiveList.end(); )
	{
		if( iter->second.val[0] == 0 )
		{
			iter = m_effectiveList.erase(iter);
		}
		else
		{
			int SKID = 0;
			bool isPlaySolo = false;

			if( iter->second.time == 9999 )
			{
				if( this->IsGroundEffective(iter->first, SKID, isPlaySolo) )
					this->ProcessGroundEffective(iter->first, SKID, isPlaySolo);
				else
					this->ProcessCheckEffective(iter->first, &iter->second);
			}
			else
			{
				if( time > iter->second.time )
					this->ResetEffective(iter->first, 0);
				else
					this->ProcessCheckEffective(iter->first, &iter->second);
			}

			++iter;
		}
	}
}


bool CActor::IsGroundEffective(int index, int& SKID, bool& isPlaySolo)
{
	SKID = 0;
	isPlaySolo = false;

	switch( index )
	{
	case EFST_EARTH_INSIGNIA:              SKID = SKID_SO_EARTH_INSIGNIA;                  break;
	case EFST_WIND_INSIGNIA:               SKID = SKID_SO_WIND_INSIGNIA;                   break;
	case EFST_WATER_INSIGNIA:              SKID = SKID_SO_WATER_INSIGNIA;                  break;
	case EFST_FIRE_INSIGNIA:               SKID = SKID_SO_FIRE_INSIGNIA;                   break;
	case EFST_POWER_OF_GAIA:               SKID = SKID_EL_POWER_OF_GAIA;                   break;
	case EFST_ZEPHYR:                      SKID = SKID_EL_ZEPHYR;                          break;
	case EFST_WATER_BARRIER:               SKID = SKID_EL_WATER_BARRIER;                   break;
	case EFST_DONTFORGETME:                SKID = SKID_DC_DONTFORGETME; isPlaySolo = true; break;
	case EFST_ETERNALCHAOS:                SKID = SKID_BD_ETERNALCHAOS;                    break;
	case EFST_ROKISWEIL:                   SKID = SKID_BD_ROKISWEIL;                       break;
	case EFST_FOGWALL:                     SKID = SKID_PF_FOGWALL;                         break;
	case EFST_NEUTRALBARRIER:              SKID = SKID_NC_NEUTRALBARRIER;                  break;
	case EFST_STEALTHFIELD:                SKID = SKID_NC_STEALTHFIELD;                    break;
	case EFST_FIRE_EXPANSION_SMOKE_POWDER: SKID = SKID_GN_FIRE_EXPANSION_SMOKE_POWDER;     break;
	case EFST_FIRE_EXPANSION_TEAR_GAS:     SKID = SKID_GN_FIRE_EXPANSION_TEAR_GAS;         break;
	case EFST_BANDING_DEFENCE:             SKID = SKID_LG_BANDING;                         break;
	case EFST_BLOODYLUST:                  SKID = SKID_SC_BLOODYLUST;                      break;
	case EFST_WARMER:                      SKID = SKID_SO_WARMER;                          break;
	case EFST_DEMONIC_FIRE:                SKID = SKID_GN_DEMONIC_FIRE;                    break;
	default:                               return false;                                   break;
	};

	return true;
}


void CActor::ProcessCheckEffective(int index, EFFECTIVE_INFO* info)
{
	switch( index )
	{
	case EFST_RG_CCONFINE_M:
	{
		unsigned long AID = info->val[1];
		CCharacter* ch = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(AID);
		if( ch == NULL || !this->IsMyArea(ch, 2) )
		{
			this->ResetEffective(EFST_RG_CCONFINE_M, 0);
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, ch, CM_RESETEFFECTIVE, EFST_RG_CCONFINE_S, 0, 0, 0);
		}
	}
	break;
	case EFST_ELECTRICSHOCKER:
	{
		this->CActor::ProcessEffective_ELECTRICSHOCKER();
	}
	break;
	default:
	{
		EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::Process(index, this, info);
	}
	break;
	};
}


void CActor::SetEffectiveComplete(const int index, const int time, const int val1, const int val2, const int val3)
{
	switch( index )
	{
	case EFST_RG_CCONFINE_M:
		this->SetEffective(EFST_DISABLEMOVE, time, 1, 0, 0, 0);
		this->OnChangeStatusAmount(SKID_RG_CLOSECONFINE, VAR_BASICAVOIDANCE, time, 10);
		if( this->GetType() != PC_TYPE )
			this->OnShowEffect(604); //TODO: client's EF_NPC_STOP2
	break;
	case EFST_ASSUMPTIO:
		this->ResetEffective(EFST_KYRIE, 0);
		this->ResetEffective(EFST_BARRIER, 0);
		this->ResetEffective(EFST_KAITE, 0);
		this->SetOnShowEFST(SHOW_EFST_ASSUMPTIO);
	break;
	case EFST_STONESKIN:
		m_charBuff2.CCharBuff::Update_Damaged_DirectSubPercent(val1);
		m_charBuff2.CCharBuff::Update_Damaged_MagicSubPercent(-val1);
		this->OnMsg(NULL, this, CM_SET_MDEFPERCENT, SKID_NPC_STONESKIN, time, val1, 0);
	break;
	case EFST_ANTIMAGIC:
		m_charBuff2.CCharBuff::Update_Damaged_MagicSubPercent(val1);
		this->OnMsg(NULL, this, CM_SET_DEFPERCENT, SKID_NPC_ANTIMAGIC, time, -val1, 0);
	break;
	case EFST_CRITICALWOUND:
		m_charBuff2.CCharBuff::Update_Heal_HP_ModifyPercent(-val1);
	break;
	case EFST_MOVESLOW_POTION:
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
	break;
	case EFST_GIANTGROWTH:
		this->OnChangeStatusAmount(SKID_RK_GIANTGROWTH, VAR_STR, time, 30);
	break;
	default:
		EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::SetComplete(index, this, time, val1, val2, val3);
	break;
	};
}


bool CActor::ResetEffectiveCheckup(const int in_Index, const int in_Val, EFFECTIVE_INFO* io_pInfo)
{
	return EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::ResetCheckup(in_Index, this, in_Val, io_pInfo);
}


void CActor::ResetEffectiveComplete(const int in_Index, const int in_Val1, const int in_Val2, const int in_Val3)
{
	switch( in_Index )
	{
	case EFST_RG_CCONFINE_M:
		this->CActor::ResetStatusAmount(SKID_RG_CLOSECONFINE, 0);
		this->ResetEffective(EFST_DISABLEMOVE, 0);
		if( this->GetType() != PC_TYPE )
			this->OnShowEffect(605); //TODO: client's EF_NPC_STOP2_DEL
	break;
	case EFST_ASSUMPTIO:
		if( !this->GetEffective(EFST_ASSUMPTIO2, 0) )
			this->SetOffShowEFST(SHOW_EFST_ASSUMPTIO);
	break;
	case EFST_STONESKIN:
		this->OnMsg(NULL, this, CM_RESET_MDEFPERCENT, SKID_NPC_STONESKIN, 0, 0, 0);
		m_charBuff2.CCharBuff::Update_Damaged_DirectSubPercent(-in_Val1);
		m_charBuff2.CCharBuff::Update_Damaged_MagicSubPercent(in_Val1);
	break;
	case EFST_ANTIMAGIC:
		this->OnMsg(NULL, this, CM_RESET_DEFPERCENT, SKID_NPC_ANTIMAGIC, 0, 0, 0);
		m_charBuff2.CCharBuff::Update_Damaged_MagicSubPercent(-in_Val1);
	break;
	case EFST_CRITICALWOUND:
		m_charBuff2.CCharBuff::Update_Heal_HP_ModifyPercent(in_Val1);
	break;
	case EFST_MOVESLOW_POTION:
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
	break;
	case EFST_GIANTGROWTH:
		this->CActor::ResetStatusAmount(SKID_RK_GIANTGROWTH, 0);
	break;
	default:
		EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::ResetComplete(in_Index, this, in_Val1, in_Val2, in_Val3);
	break;
	};
}


bool CActor::SetEffectiveCheckup(const int in_Index, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3)
{
	if( io_Time == 0 )
		return false;

	switch( in_Index )
	{
	case EFST_STONESKIN:
		if( this->GetEffective(EFST_STONESKIN, 0) > io_Val1 )
			return false;
		this->ResetEffective(EFST_STONESKIN, 0);
	break;
	case EFST_ANTIMAGIC:
		if( this->GetEffective(EFST_ANTIMAGIC, 0) > io_Val1 )
			return false;
		this->ResetEffective(EFST_ANTIMAGIC, 0);
	break;
	case EFST_CRITICALWOUND:
		if( this->GetEffective(EFST_CRITICALWOUND, 0) )
			this->ResetEffective(EFST_CRITICALWOUND, 0);
	break;
	case EFST_TARGET_BLOOD:
		if( this->GetEffective(EFST_TARGET_BLOOD, 0) )
			return false;
	break;
	case EFST_GIANTGROWTH:
	case EFST_VITALITYACTIVATION:
	case EFST_FIGHTINGSPIRIT:
	case EFST_ABUNDANCE:
		if( this->GetEffective(in_Index, 0) )
			this->ResetEffective(in_Index, 0);
	break;
	case EFST_PROVOKE:
	case EFST_QUAGMIRE:
	case EFST_DEC_AGI:
	case EFST_JOINTBEAT:
		if( this->GetEffective(EFST_REFRESH, 0) )
			return false;
	break;
	case EFST_ELECTRICSHOCKER:
		io_val3 = 0;
		io_Val2 = 0;
	break;
	default:
	{
		if( !EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::SetCheckup(in_Index, this, io_Time, io_Val1, io_Val2, io_val3) )
			return 0;

		ESTATE* pEState = EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::GetPtr(in_Index);
		if( pEState != NULL )
		{
			if( pEState->IsExistScript() )
			{
				int val = this->GetEffective(in_Index, 0);
				if( val > io_Val1 )
					return false;

				if( val != 0 )
					EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::RunScript(this->GetAccountID(), 4, in_Index);
			}

			if( pEState->IsGC_POISON() )
			{
				if( this->GetEffective(EFST_INSPIRATION, 0) )
					return false;
				this->ResetAllEffective(RESET_EFST_GC_NEWPOISON);
			}
		}
	}
	break;
	};

	return true;
}


void CActor::GetModifiedHealAmount(int& healAmount)
{
	if( m_charBuff2.CCharBuff::Get_Heal_HP_ModifyPercent() != 0 )
		healAmount += healAmount * m_charBuff2.CCharBuff::Get_Heal_HP_ModifyPercent() / 100;

	if( this->GetEffective(EFST_STAR2, 0) )
		healAmount /= 4;
}


void CActor::GetModifiedSPHealAmount(int& spHealAmount)
{
	int percent = m_charBuff2.CCharBuff::Get_Heal_SP_ModifyPercent();
	if( percent == 0 )
		return;

	spHealAmount += spHealAmount * percent / 100;
}


void CActor::BeginSkillPostDelay(unsigned short SKID, int skLevel)
{
	if( this->GetType() == NPC_MOB_TYPE )
		return;

	if( skLevel < 1 || skLevel > 10 )
		return;

	this->CActor::BeginSkillSinglePostDelay(SKID, skLevel);
	this->CActor::BeginSkillGlobalPostDelay(SKID, skLevel);
}


void CActor::BeginSkillSinglePostDelay(unsigned short SKID, int skLevel)
{
	if( this->GetType() == NPC_MOB_TYPE )
		return;

	int delaytime = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSkillSinglePostDelay(SKID, skLevel);
	this->SetSkillSinglePostDelay(SKID, delaytime);
}


void CActor::BeginSkillGlobalPostDelay(unsigned short SKID, int skLevel)
{
	if( this->GetType() == NPC_MOB_TYPE )
		return;

	int delayTime = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSkillGlobalPostDelay(SKID, skLevel);
	if( delayTime == 0 )
		return;

	int percent = max(0, m_fvarindsumhistory_GlobalPostDelay_Percent(SKID) + 100);
	int time = int(percent / 100.0 * delayTime);
	this->SetEffective(EFST_POSTDELAY, time, 1, 0, 0, 0);
}


int CActor::GetModifiedDamageByTargetDEF(CCharacter* in_cpTargetCH, const int in_Damage, const int in_MinimumDamage)
{
	if( in_cpTargetCH->GetEffective(EFST_BERSERK, 0) > 0 )
		return in_Damage;

	int TargetItemDef = this->GetModifiedTargetItemDEF2(in_cpTargetCH);
	if( in_cpTargetCH->IsActor() )
		static_cast<CActor*>(in_cpTargetCH)->ApplyExtraDEF(TargetItemDef, this);

	const float decPercent = float(100.0 - TargetItemDef / (TargetItemDef + 400.0) * 90.0);

	int result = int(decPercent / 100.0 * in_Damage - this->GetModifiedTargetStatusDEF2(in_cpTargetCH));
	if( result < in_MinimumDamage )
		result = in_MinimumDamage;

	return result;
}


int CActor::GetModifiedTargetTotalDEF(CCharacter* target)
{
	if( target->GetEffective(EFST_BERSERK, 0) > 0 )
		return 0;

	int TargetStatusDef = this->GetModifiedTargetStatusDEF(target);

	int totalDEF = TargetStatusDef + this->GetModifiedTargetItemDEF(target);
	if( target->IsActor() )
		static_cast<CActor*>(target)->ApplyExtraDEF(totalDEF, this);

	return totalDEF;
}


int CActor::GetModifiedTargetStatusMDEF2(CCharacter* in_cpTargetCH)
{
	int targetStatusMDef = 0;
	in_cpTargetCH->GetParameterValue(VAR_MAGICSTATUSDEFPOWER, targetStatusMDef);
	return targetStatusMDef;
}


int CActor::GetModifiedTargetItemMDEF2(CCharacter* in_cpTargetCH)
{
	return 0;
}


int CActor::GetModifiedDamageByTargetMDEF(CCharacter* in_cpTargetCH, const int in_Damage, const int in_MinimumDamage)
{
	if( in_cpTargetCH->GetEffective(EFST_BERSERK, 0) > 0 )
		return in_Damage;

	int TargetItemMDF = this->GetModifiedTargetItemMDEF2(in_cpTargetCH);
	if( in_cpTargetCH->IsActor() )
		static_cast<CActor*>(in_cpTargetCH)->ApplyExtraMDEF(TargetItemMDF);

	float decPercent = float(100.0 - TargetItemMDF / (TargetItemMDF + 100.0) * 90.0);

	int result = int(decPercent / 100.0 * in_Damage - this->GetModifiedTargetStatusMDEF2(in_cpTargetCH));
	if( result < in_MinimumDamage )
		result = in_MinimumDamage;

	return result;
}


int CActor::GetModifiedTargetTotalMDEF(CCharacter* target)
{
	if( target->GetEffective(EFST_BERSERK, 0) > 0 )
		return 0;

	int targetStatusMDef;
	target->GetParameterValue(VAR_MAGICSTATUSDEFPOWER, targetStatusMDef);

	int totalMDEF = targetStatusMDef + this->GetModifiedTargetItemMDEF(target);
	if( target->GetType() != ITEM_TYPE && target->GetType() != SKILL_TYPE )
		static_cast<CActor*>(target)->ApplyExtraMDEF(totalMDEF);

	return totalMDEF;
}


namespace {
struct HandicapStateToleranceData
{
	/* this+0 */ int RelatedStatus; // enumCHARACTERVAR
	/* this+4 */ int DefaultKeepMS;
	/* this+8 */ int AddKeepMSAmount;

	HandicapStateToleranceData(const int in_RelatedStatus = 0, const int in_DefaultKeepMS = 0, const int in_AddKeepMSAmount = 0) : RelatedStatus(in_RelatedStatus), DefaultKeepMS(in_DefaultKeepMS), AddKeepMSAmount(in_AddKeepMSAmount) { }
};


std::map<int,HandicapStateToleranceData> GetHandicapStateDataTbl()
{
	std::map<int,HandicapStateToleranceData> result;
	result.insert(std::make_pair(BODY_IMPRISON, HandicapStateToleranceData(VAR_STR, 18000, 2000)));
	result.insert(std::make_pair(BODY_STONECURSE, HandicapStateToleranceData(VAR_MAGICITEMDEFPOWER, 17000, 3000)));
	result.insert(std::make_pair(BODY_FREEZING, HandicapStateToleranceData(VAR_MAGICITEMDEFPOWER, 27000, 3000)));
	result.insert(std::make_pair(BODY_STUN, HandicapStateToleranceData(VAR_VIT, 4500, 500)));
	result.insert(std::make_pair(BODY_SLEEP, HandicapStateToleranceData(VAR_AGI, 18000, 2000)));
	result.insert(std::make_pair(HEALTH_POISON, HandicapStateToleranceData(VAR_VIT, 18000, 2000)));
	result.insert(std::make_pair(HEALTH_CURSE, HandicapStateToleranceData(VAR_LUK, 18000, 2000)));
	result.insert(std::make_pair(HEALTH_SILENCE, HandicapStateToleranceData(VAR_INT, 18000, 2000)));
	result.insert(std::make_pair(HEALTH_CONFUSION, HandicapStateToleranceData(VAR_LUK, 18000, 2000)));
	result.insert(std::make_pair(HEALTH_BLIND, HandicapStateToleranceData(VAR_INT, 18000, 2000)));
	result.insert(std::make_pair(HEALTH_HEAVYPOISON, HandicapStateToleranceData(VAR_VIT, 28000, 2000)));
	result.insert(std::make_pair(HEALTH_BLOODING, HandicapStateToleranceData(VAR_AGI, 108000, 12000)));
	result.insert(std::make_pair(HEALTH_FEAR, HandicapStateToleranceData(VAR_INT, 18000, 2000)));
	result.insert(std::make_pair(BODY_BURNNING, HandicapStateToleranceData(VAR_AGI, 18000, 2000)));
	result.insert(std::make_pair(HANDICAPSTATE_DEEPSLEEP, HandicapStateToleranceData(VAR_LUK, 0, 0)));
	result.insert(std::make_pair(HANDICAPSTATE_FROSTMISTY, HandicapStateToleranceData(VAR_LUK, 0, 0)));
	result.insert(std::make_pair(HANDICAPSTATE_COLD, HandicapStateToleranceData(VAR_LUK, 0, 0)));
	return result;
}


HandicapStateToleranceData GetHandicapStateData(const int in_Handicap)
{
	static std::map<int,HandicapStateToleranceData> Tbl = GetHandicapStateDataTbl();
	return Tbl[in_Handicap];
}


std::tr1::tuple<bool,int,int> GetHandicapStateToleranceFactor(int in_Handicap, int in_ApplyPermill, int in_KeepTime, CCharacter* in_cpSourceCH, CCharacter* in_cpTargetCH)
{
	HandicapStateToleranceData HandicapStateData = GetHandicapStateData(in_Handicap);
	if( HandicapStateData.RelatedStatus == 0 )
		return std::tr1::tuple<bool,int,int>(false, 0, 0);

	if( in_KeepTime == 0 )
		in_KeepTime = HandicapStateData.DefaultKeepMS;

	switch( in_Handicap )
	{
	case BODY_STONECURSE:
	case BODY_FREEZING:
	case BODY_STUN:
	case BODY_SLEEP:
	case HEALTH_POISON:
	case HEALTH_CURSE:
	case HEALTH_SILENCE:
	case HEALTH_CONFUSION:
	case HEALTH_BLIND:
	case HEALTH_HEAVYPOISON:
	case HEALTH_BLOODING:
	{
		int otherStatusFactor = 0;
		in_cpTargetCH->GetParameterValue(HandicapStateData.RelatedStatus, otherStatusFactor);

		int otherLevel = 0;
		in_cpTargetCH->GetParameterValue(VAR_CLEVEL, otherLevel);

		int myLevel = 0;
		in_cpSourceCH->GetParameterValue(VAR_CLEVEL, myLevel);

		int otherHandicapStateTolerance = in_Handicap;
		in_cpTargetCH->GetParameterValue(VAR_TOLERACE, otherHandicapStateTolerance);

		if( otherHandicapStateTolerance < 0 )
			otherHandicapStateTolerance = 0;
		else
		if( otherHandicapStateTolerance > 100 )
			otherHandicapStateTolerance = 100;

		int levelAdvantage = max(0, myLevel - otherLevel);

		float ToleranceFactor = float(otherStatusFactor - (int)pow((double)levelAdvantage, 2) / 5.0);
		if( ToleranceFactor > 100 )
			ToleranceFactor = 100;
		else
		if( ToleranceFactor < 0 )
			ToleranceFactor = 0;

		double rate1 = (100.0 - ToleranceFactor) / 100.0;
		double rate2 = (100.0 - otherHandicapStateTolerance) / 100.0;

		int ApplyPermill = int(rate1 * rate2 * in_ApplyPermill);
		int time = int(rate1 * rate2 * in_KeepTime + HandicapStateData.AddKeepMSAmount);

		return std::tr1::tuple<bool,int,int>(true, ApplyPermill, time);
	}
	break;
	case HANDICAPSTATE_DEEPSLEEP:
	{
		int level = 1;
		in_cpTargetCH->GetParameterValue(VAR_CLEVEL, level);

		int joblevel = 1;
		in_cpTargetCH->GetParameterValue(VAR_JOBLEVEL, joblevel);

		int TargetINT = 1;
		in_cpTargetCH->GetParameterValue(VAR_STANDARD_INT, TargetINT);

		int time = int(in_KeepTime - 1000 * (TargetINT / 40.0 + level / 20.0));
		if( time < 0 )
			time = 0;

		return std::tr1::tuple<bool,int,int>(true, in_ApplyPermill, time);
	}
	break;
	case HANDICAPSTATE_FROSTMISTY:
	{
		int time = ESTATE_FROSTMISTY::GetDefaultLifeTM(in_cpTargetCH);
		return std::tr1::tuple<bool,int,int>(true, in_ApplyPermill, time);
	}
	break;
	case HANDICAPSTATE_COLD:
	{
		int TargetVIT = 0;
		in_cpTargetCH->GetParameterValue(VAR_STANDARD_VIT, TargetVIT);

		int reduceTime = 1000 * TargetVIT / 10;
		int time = ( in_KeepTime > reduceTime ) ? in_KeepTime - reduceTime : 0;
		return std::tr1::tuple<bool,int,int>(true, in_ApplyPermill, time);
	}
	break;
	default:
	{
		int otherStatusFactor = 0;
		in_cpTargetCH->GetParameterValue(HandicapStateData.RelatedStatus, otherStatusFactor);

		int otherLevel = 0;
		in_cpTargetCH->GetParameterValue(VAR_CLEVEL, otherLevel);

		int otherLuk = 0;
		in_cpTargetCH->GetParameterValue(VAR_LUK, otherLuk);

		int otherHandicapStateTolerance = in_Handicap;
		in_cpTargetCH->GetParameterValue(VAR_TOLERACE, otherHandicapStateTolerance);

		if( otherHandicapStateTolerance < 0 )
			otherHandicapStateTolerance = 0;
		else
		if( otherHandicapStateTolerance > 100 )
			otherHandicapStateTolerance = 100;

		float ToleranceFactor = float(otherStatusFactor + otherLevel + otherLuk / 2.0);
		if( ToleranceFactor < 0 )
			ToleranceFactor = 0;
		else
		if( ToleranceFactor > 500 )
			ToleranceFactor = 500;

		double rate1 = (500.0 - ToleranceFactor) / 500.0;
		double rate2 = (100.0 - otherHandicapStateTolerance) / 100.0;

		int ApplyPermill = int(rate1 * rate2 * in_ApplyPermill);
		int time = int(rate1 * rate2 * in_KeepTime + HandicapStateData.AddKeepMSAmount);

		return std::tr1::tuple<bool,int,int>(true, ApplyPermill, time);
	}
	break;
	};
}
}; // namespace


bool CActor::IsHandicapState(const int in_HandicapState)
{
	switch( in_HandicapState )
	{
	case BODY_STUN:
		return ( this->GetBodyState() == BODYSTATE_STUN );
	break;
	case BODY_SLEEP:
		return ( this->GetBodyState() == BODYSTATE_SLEEP );
	break;
	case BODY_STONECURSE:
		return ( this->GetBodyState() == BODYSTATE_STONECURSE_ING || this->GetBodyState() == BODYSTATE_STONECURSE );
	break;
	case BODY_FREEZING:
		return ( this->GetBodyState() == BODYSTATE_FREEZING );
	break;
	case BODY_BURNNING:
		return ( this->GetBodyState() == BODYSTATE_BURNNING );
	break;
	case HEALTH_CURSE:
		return ( (this->GetHealthState() & HEALTHSTATE_CURSE) != 0 );
	break;
	case HEALTH_POISON:
		return ( (this->GetHealthState() & (HEALTHSTATE_POISON | HEALTHSTATE_HEAVYPOISON)) != 0 );
	break;
	case HEALTH_BLIND:
		return ( (this->GetHealthState() & HEALTHSTATE_BLIND) != 0 );
	break;
	case HEALTH_SILENCE:
		return ( (this->GetHealthState() & HEALTHSTATE_SILENCE) != 0 );
	break;
	case HEALTH_BLOODING:
		return ( (this->GetHealthState() & HEALTHSTATE_BLOODING) != 0 );
	break;
	case HEALTH_CONFUSION:
		return ( (this->GetHealthState() & HEALTHSTATE_CONFUSION) != 0 );
	break;
	case HEALTH_FEAR:
		return ( (this->GetHealthState() & HEALTHSTATE_FEAR) != 0 );
	break;
	case HANDICAPSTATE_DEEPSLEEP:
		return ( this->GetEffective(EFST_HANDICAPSTATE_DEEP_SLEEP, 0) != 0 );
	break;
	case HANDICAPSTATE_FROSTMISTY:
		return ( this->GetEffective(EFST_FROSTMISTY, 0) != 0 );
	break;
	case HANDICAPSTATE_COLD:
		return ( this->GetEffective(EFST_COLD, 0) != 0 );
	break;
	default:
		return false;
	break;
	};
}


bool CActor::ResetHandicapState(CActor* in_cpTarget, const int in_HandicapState)
{
	switch( in_HandicapState )
	{
	case BODY_STUN:
	case BODY_SLEEP:
	case BODY_STONECURSE:
	case BODY_FREEZING:
	case BODY_BURNNING:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_cpTarget, CM_TIME_BODYSTATE, 0, 0, BODYSTATE_NORMAL, 0);
	break;
	case HEALTH_CURSE:
		this->ResetHealthState(HEALTHSTATE_CURSE);
	break;
	case HEALTH_POISON:
		this->ResetHealthState(HEALTHSTATE_POISON);
	break;
	case HEALTH_BLIND:
		this->ResetHealthState(HEALTHSTATE_BLIND);
	break;
	case HEALTH_SILENCE:
		this->ResetHealthState(HEALTHSTATE_SILENCE);
	break;
	case HEALTH_BLOODING:
		this->ResetHealthState(HEALTHSTATE_BLOODING);
	break;
	case HEALTH_CONFUSION:
		this->ResetHealthState(HEALTHSTATE_CONFUSION);
	break;
	case HEALTH_FEAR:
		this->ResetHealthState(HEALTHSTATE_FEAR);
	break;
	case HANDICAPSTATE_DEEPSLEEP:
		in_cpTarget->ResetEffective(EFST_HANDICAPSTATE_DEEP_SLEEP, 0);
	break;
	case HANDICAPSTATE_FROSTMISTY:
		in_cpTarget->ResetEffective(EFST_FROSTMISTY, 0);
	break;
	case HANDICAPSTATE_COLD:
		in_cpTarget->ResetEffective(EFST_COLD, 0);
	break;
	};

	return true;
}


namespace {
std::map<int,int> HandicapStateMatchEfstList()
{
	std::map<int,int> result;
	result[HANDICAPSTATE_DEEPSLEEP] = EFST_HANDICAPSTATE_DEEP_SLEEP;
	result[HANDICAPSTATE_FROSTMISTY] = EFST_FROSTMISTY;
	result[HANDICAPSTATE_COLD] = EFST_COLD;
	result[HANDICAPSTATE_NORECOVER] = EFST_HANDICAPSTATE_NORECOVER;
	return result;
}
}; // namespace


namespace {
int GetHandicapStateMathEfst(int in_HadicapState)
{
	static std::map<int,int> rList = HandicapStateMatchEfstList();
	std::map<int,int>::iterator iter = rList.find(in_HadicapState);
	if( iter == rList.end() )
		return 0;

	return iter->second;
}
}; // namespace


const DWORD CActor::GetHandcapStateRemainTime(const int in_HandicapState)
{
	switch( in_HandicapState )
	{
	case BODY_STUN:
		return this->CActor::GetBodyStateRemainMS(BODYSTATE_STUN);
	break;
	case BODY_SLEEP:
		return this->CActor::GetBodyStateRemainMS(BODYSTATE_SLEEP);
	break;
	case BODY_STONECURSE:
		return this->CActor::GetBodyStateRemainMS(BODYSTATE_STONECURSE);
	break;
	case BODY_FREEZING:
		return this->CActor::GetBodyStateRemainMS(BODYSTATE_FREEZING);
	break;
	case BODY_BURNNING:
		return this->CActor::GetBodyStateRemainMS(BODYSTATE_BURNNING);
	break;
	case HEALTH_CURSE:
		return this->CActor::GetHealthStateRemainMS(HEALTHSTATE_CURSE);
	break;
	case HEALTH_POISON:
		return this->CActor::GetHealthStateRemainMS(HEALTHSTATE_POISON);
	break;
	case HEALTH_BLIND:
		return this->CActor::GetHealthStateRemainMS(HEALTHSTATE_BLIND);
	break;
	case HEALTH_SILENCE:
		return this->CActor::GetHealthStateRemainMS(HEALTHSTATE_SILENCE);
	break;
	case HEALTH_BLOODING:
		return this->CActor::GetHealthStateRemainMS(HEALTHSTATE_BLOODING);
	break;
	case HEALTH_CONFUSION:
		return this->CActor::GetHealthStateRemainMS(HEALTHSTATE_CONFUSION);
	break;
	case HANDICAPSTATE_DEEPSLEEP:
	case HANDICAPSTATE_FROSTMISTY:
	case HANDICAPSTATE_COLD:
	case HANDICAPSTATE_NORECOVER:
	{
		DWORD curTM = timeGetTime();

		EFFECTIVE_INFO* info = this->CActor::GetEffectiveInfo(GetHandicapStateMathEfst(in_HandicapState));
		if( info == NULL )
			return 0;

		if( info->time == 9999 )
			return 9999;

		if( info->time <= curTM )
			return 0;
		
		return info->time - curTM;
	}
	break;
	default:
		return 0;
	break;
	};
}


BOOL CActor::SetHandicapState(int in_state, CCharacter* in_cpTargetCH, int in_percent, int in_preDelayTime, int in_delayTime, BOOL in_isSpell, BOOL in_isFixedDelayTime)
{
	if( in_cpTargetCH->GetState() == CHARACTER_STATE_DEAD )
		return FALSE;

	if( in_cpTargetCH->GetEffective(EFST_REFRESH, 0) != 0 )
		return FALSE;

	if( in_cpTargetCH->GetEffective(EFST_INSPIRATION, 0) != 0 )
		return FALSE;

	int tarEffectState = EFFECTSTATE_NOTHING;
	in_cpTargetCH->GetParameterValue(VAR_EFFECTSTATE, tarEffectState);

	if( tarEffectState & EFFECTSTATE_SPECIALHIDING )
		return FALSE;

	int tarClass = CLASS_NONE;
	int tarJob = JT_NOVICE;
	in_cpTargetCH->GetParameterValue(VAR_CLASS, tarClass);
	in_cpTargetCH->GetParameterValue(VAR_JOB, tarJob);

	if( tarClass == NPC_CLASS_BOSS || tarClass == NPC_CLASS_GUARDIAN || IsAgitTrigerNPC(tarJob) || tarClass == NPC_CLASS_BATTLEFIELD )
		return FALSE;

	std::tr1::tuple<bool,int,int> ret = GetHandicapStateToleranceFactor(in_state, in_percent, in_delayTime, this, in_cpTargetCH);
	if( !std::tr1::get<0>(ret) )
		return FALSE;

	int ApplyPermill = std::tr1::get<1>(ret);

	int delayTime = in_delayTime;
	if( delayTime != 9999 && !in_isFixedDelayTime )
		delayTime = std::tr1::get<2>(ret);

	switch( in_state )
	{
	case BODY_IMPRISON:
	{
		int tarIsMagicImmune = FALSE;
		if( in_isSpell )
			in_cpTargetCH->GetParameterValue(VAR_ISMAGICIMMUNE, tarIsMagicImmune);

		if( in_cpTargetCH == this )
			ApplyPermill = 1000;

		if( tarIsMagicImmune )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_BODYSTATE, in_preDelayTime, delayTime, BODYSTATE_IMPRISON, 0);
		return TRUE;
	}
	break;
	case BODY_STONECURSE:
	{
		if( in_cpTargetCH->IsRightProperty(PROPERTY_UNDEAD) )
			return FALSE;

		if( in_cpTargetCH->m_fvarb_BODYSTATE_STONECURSE_Cancel() )
			return FALSE;

		int otherBodyState = BODYSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_BODYSTATE, otherBodyState);

		if( otherBodyState == BODYSTATE_NORMAL )
		{
			if( in_isSpell )
			{
				int tarIsMagicImmune = FALSE;
				in_cpTargetCH->GetParameterValue(VAR_ISMAGICIMMUNE, tarIsMagicImmune);

				if( tarIsMagicImmune )
					return FALSE;
			}

			if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
				return FALSE;

			in_cpTargetCH->UpdateParameterValue(VAR_BODYSTATE, BODYSTATE_STONECURSE_ING);

			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_BODYSTATE, in_preDelayTime, delayTime, BODYSTATE_STONECURSE, 0);
			return TRUE;
		}
		else
		if( otherBodyState == BODYSTATE_STONECURSE || otherBodyState == BODYSTATE_STONECURSE_ING )
		{
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_BODYSTATE, 0, 0, BODYSTATE_NORMAL, 0);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	break;
	case BODY_FREEZING:
	{// 1932-1950
		int otherBodyState = BODYSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_BODYSTATE, otherBodyState);

		if( otherBodyState == BODYSTATE_FREEZING )
			return FALSE;

		if( otherBodyState != BODYSTATE_NORMAL )
			return FALSE;

		if( in_cpTargetCH->IsRightProperty(PROPERTY_UNDEAD) )
			return FALSE;

		if( in_cpTargetCH->GetEffective(EFST_WARMER, 0) != 0 )
			return FALSE;

		if( in_isSpell )
		{
			int tarIsMagicImmune = FALSE;
			in_cpTargetCH->GetParameterValue(VAR_ISMAGICIMMUNE, tarIsMagicImmune);
				
			if( tarIsMagicImmune )
				return FALSE;
		}

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_BODYSTATE, in_preDelayTime, delayTime, BODYSTATE_FREEZING, 0);
		return TRUE;
	}
	break;
	case BODY_STUN:
	{
		int otherBodyState = BODYSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_BODYSTATE, otherBodyState);

		if( otherBodyState == BODYSTATE_STUN )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_BODYSTATE, in_preDelayTime, delayTime, BODYSTATE_STUN, 0);
		return TRUE;
	}
	break;
	case BODY_SLEEP:
	{
		int otherBodyState = 0;
		in_cpTargetCH->GetParameterValue(VAR_BODYSTATE, otherBodyState);

		if( otherBodyState == BODYSTATE_SLEEP )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill && !in_isFixedDelayTime )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_BODYSTATE, in_preDelayTime, delayTime, BODYSTATE_SLEEP, 0);
		return TRUE;
	}
	break;
	case HEALTH_POISON:
	{
		int otherHealthState = HEALTHSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_HEALTHSTATE, otherHealthState);

		if( otherHealthState & (HEALTHSTATE_POISON | HEALTHSTATE_HEAVYPOISON) )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, in_preDelayTime, delayTime, HEALTHSTATE_POISON, 0);
		return TRUE;
	}
	break;
	case HEALTH_CURSE:
	{
		int otherHealthState = HEALTHSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_HEALTHSTATE, otherHealthState);

		int otherLuk = 0;
		in_cpTargetCH->GetParameterValue(VAR_LUK, otherLuk);

		if( otherHealthState & HEALTHSTATE_CURSE )
			return FALSE;
			
		if( otherLuk == 0 )
			return FALSE;
			
		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, in_preDelayTime, delayTime, HEALTHSTATE_CURSE, 0);

		if( in_cpTargetCH->GetType() == NPC_MOB_TYPE && delayTime > 0 )
			static_cast<CNpcMob*>(in_cpTargetCH)->CNPC::SetATKPercentInfo(-2, delayTime, -25);

		return TRUE;
	}
	break;
	case HEALTH_SILENCE:
	{
		int otherHealthState = HEALTHSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_HEALTHSTATE, otherHealthState);

		if( otherHealthState & HEALTHSTATE_SILENCE )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, in_preDelayTime, delayTime, HEALTHSTATE_SILENCE, 0);
		return TRUE;
	}
	break;
	case HEALTH_CONFUSION:
	{
		int otherHealthState = HEALTHSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_HEALTHSTATE, otherHealthState);

		if( otherHealthState & HEALTHSTATE_CONFUSION )
		{
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, 0, 0, HEALTHSTATE_CONFUSION, 0);
			return TRUE;
		}

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, in_preDelayTime, delayTime, HEALTHSTATE_CONFUSION, 0);
		return TRUE;
	}
	break;
	case HEALTH_BLIND:
	{
		int otherHealthState = HEALTHSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_HEALTHSTATE, otherHealthState);

		if( otherHealthState & HEALTHSTATE_BLIND )
			return FALSE;

		if( otherHealthState & HEALTHSTATE_FEAR )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, in_preDelayTime, delayTime, HEALTHSTATE_BLIND, 0);
		return TRUE;
	}
	break;
	case HEALTH_HEAVYPOISON:
	{
		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, in_preDelayTime, delayTime, HEALTHSTATE_HEAVYPOISON, 0);
		return TRUE;
	}
	break;
	case HEALTH_BLOODING:
	{
		if( in_cpTargetCH->m_fvarb_HEALTH_BLOODING_Cancel() )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, 0, delayTime, HEALTHSTATE_BLOODING, 0);
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_SETEFFECTIVE, EFST_BLOODING, delayTime, 1, 0);
		return TRUE;
	}
	break;
	case HEALTH_FEAR:
	{
		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		int otherHealthState = HEALTHSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_HEALTHSTATE, otherHealthState);

		if( otherHealthState & HEALTHSTATE_BLIND )
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, 0, 0, HEALTHSTATE_BLIND, 0);

		in_cpTargetCH->SetEffective(EFST_ANKLESNARE, 2000, 1, 0, 0, 0);

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_HEALTHSTATE, in_preDelayTime, delayTime + 2000, HEALTHSTATE_FEAR, 0);
		return TRUE;
	}
	break;
	case BODY_BURNNING:
	{
		int BodyState = BODYSTATE_NORMAL;
		in_cpTargetCH->GetParameterValue(VAR_BODYSTATE, BodyState);

		if( BodyState == BODYSTATE_IMPRISON )
			return FALSE;

		int currentState = PROPERTY_NOTHING;
		in_cpTargetCH->GetParameterValue(VAR_CURRENTSTATE, currentState);

		if( currentState == PROPERTY_FIRE2 )
			return FALSE;

		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		if( delayTime < 10000 )
			delayTime = 10000;

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, in_cpTargetCH, CM_TIME_BODYSTATE, in_preDelayTime, delayTime, BODYSTATE_BURNNING, 0);
		return FALSE; //FIXME: wrong retval?
	}
	break;
	case HANDICAPSTATE_DEEPSLEEP:
	{
		if( GetServerRandom(0, 20000) % 1000 >= ApplyPermill )
			return FALSE;

		if( !in_cpTargetCH->SetEffective(EFST_HANDICAPSTATE_DEEP_SLEEP, delayTime, 1, 0, 0, 0) )
			return FALSE;

		return TRUE;
	}
	break;
	case HANDICAPSTATE_FROSTMISTY:
	{
		if( !in_cpTargetCH->SetEffective(EFST_FROSTMISTY, delayTime, 1, 0, 0, 0) )
			return FALSE;

		return TRUE;
	}
	break;
	case HANDICAPSTATE_COLD:
	{
		if( !in_cpTargetCH->SetEffective(EFST_COLD, delayTime, 1, 0, 0, 0) )
			return FALSE;

		return TRUE;
	}
	break;
	default:
	{
		return FALSE;
	}
	break;
	};
}


int CActor::GetPlusPropertyDamage(CCharacter* other, int property, int damage)
{
	if( other == NULL )
		return 0;

	int curstate;
	other->GetParameterValue(VAR_CURRENTSTATE, curstate);

	int propertyDamage = g_zoneScript.CZoneScript::GetAtkPlusPWByProperty_Variation(curstate, property, damage);
	int efstDamage = this->CActor::GetModifyAttackPowerByEffective_Variation(other, property, damage);

	return propertyDamage + efstDamage;
}


int CActor::GetModifyAttackPowerByEffective_Variation(CCharacter* ch, int attackProperty, int in_damage)
{
	int percent = 0;

	int effective = this->GetEffective(EFST_SPECIALZONE, 0);
	if( effective != 0 )
	{
		int xpos, ypos;
		this->GetParameterValue(VAR_CURXPOS, xpos);
		this->GetParameterValue(VAR_CURYPOS, ypos);

		CSkill* pSkill = CCharacterMgr::GetObj()->CCharacterMgr::GetSkill(xpos, ypos, m_mapRes);
		if( pSkill == NULL )
		{
			this->ResetEffective(EFST_SPECIALZONE, 0);
		}
		else
		if( (effective & ZONE_FIRE) && attackProperty % 10 == PROPERTY_FIRE )
		{
			if( pSkill->CSkill::GetSKID() == SKID_SA_VOLCANO )
				percent = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID_SA_VOLCANO, SM_GET_PLUSATTPOWER, pSkill->CSkill::GetSkillLevel(), 0, 0, 0);
		}
		else
		if( (effective & ZONE_WATER) && attackProperty % 10 == PROPERTY_WATER )
		{
			if( pSkill->CSkill::GetSKID() == SKID_SA_DELUGE )
				percent = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID_SA_DELUGE, SM_GET_PLUSATTPOWER, pSkill->CSkill::GetSkillLevel(), 0, 0, 0);
		}
		else
		if( (effective & ZONE_WIND) && attackProperty % 10 == PROPERTY_WIND )
		{
			if( pSkill->CSkill::GetSKID() == SKID_SA_VIOLENTGALE )
				percent = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(this, SKID_SA_VIOLENTGALE, SM_GET_PLUSATTPOWER, pSkill->CSkill::GetSkillLevel(), 0, 0, 0);
		}
	}

	return in_damage * percent / 100;
}


int CActor::UpdateResistByProperty(const int in_Property, const int in_offsetValue)
{
	m_resistByProperty[in_Property] += in_offsetValue;
	return m_resistByProperty[in_Property];
}


void CActor::ResetAllEffective(int resetType)
{
	for( EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.begin(); iter != m_effectiveList.end(); ++iter )
	{
		int efstType = iter->first;

		if( iter->second.val[0] == 0 )
			continue;

		if( efstType == EFST_ENDURE || efstType == EFST_ENDURE_MDEF )
		{
			if( iter->second.time == 9999 )
				continue;

			this->ResetEffective(efstType, 0);
			continue;
		}

		ESTATE* pEState = EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::GetPtr(efstType);
		if( pEState == NULL )
			continue;

		switch( resetType )
		{
		case RESET_MADOGEAR:
			if( pEState->ESTATE::IsResetMADOGEAR() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_DEAD:
			if( pEState->ESTATE::IsResetDead() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_DISPEL:
			if( pEState->ESTATE::IsResetDispel() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_TAROT:
			if( efstType == EFST_TRICKDEAD )
				break;

			if( pEState->ESTATE::IsResetPretendDead() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_PRETEND_DEAD:
			if( pEState->IsResetPretendDead() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_CLEARANCE:
			if( pEState->ESTATE::IsResetCLEARANCE() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_DEBUFF:
			if( pEState->ESTATE::IsDeBuff() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_GC_NEWPOISON:
			if( pEState->IsGC_POISON() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_WANDERERandMINSTREL_OVERLAPDENY_GROUP_A:
		case RESET_EFST_WANDERERandMINSTREL_OVERLAPDENY_GROUP_B:
			if( resetType == pEState->IsWANDERERandMINSTRELoverlapDeny() )
				this->ResetEffective(efstType, 0);
		break;
		case RESET_EFST_ALL:
			this->ResetEffective(efstType, 0);
		break;
		default:
		break;
		};
	}

	if( resetType == RESET_EFST_CLEARANCE )
	{
		if( this->GetType() == PC_TYPE )
		{
			if( static_cast<CPC*>(this)->m_pcSkill.CPCSkill::GetNumOfSpirits() > 0 )
				static_cast<CPC*>(this)->m_pcSkill.CPCSkill::ResetSpirits();

			static_cast<CPC*>(this)->m_pcSkill.CPCSkill::ResetMillenniumShield();
		}
	}
}


void CActor::GetForwardPosition(int xPos, int yPos, int destDir, int distance, PosInfo& result) const
{
	result.x = xPos;
	result.y = yPos;

	CMapRes* mapRes = m_mapRes;
	if( mapRes == NULL )
		return;

	int dx = g_backpedalTable[destDir][0];
	int dy = g_backpedalTable[destDir][1];
	int x = xPos + dx;
	int y = yPos + dy;
	int i;

	for( i = 1; i <= distance; ++i )
	{
		if( !mapRes->CMapRes::IsMovableCell(x, y) )
			break;

		x += dx;
		y += dy;
	}

	result.x = xPos + (i - 1) * dx;
	result.y = yPos + (i - 1) * dy;
}


int CActor::GetDirection(const PosInfo& src, const PosInfo& dest) const
{
	int dx = dest.x - src.x;
	int dy = dest.y - src.y;

	float decl;
	if( dx != 0 )
		decl = float((double)dy / (double)dx);
	else
		decl = float(dy);

	if( fabs(decl) <= 1/3.0 )
		dy = 0;
	else
	if( fabs(decl) >= 3.0 )
		dx = 0;

	if( dx == 0 )
	{
		if( dy == 0 )
			return 0; // up
		else
		if( dy > 0 )
			return 0; // up
		else
		{//( dy < 0 )
			return 4; // down
		}
	}
	else
	if( dx < 0 )
	{
		if( dy == 0 )
			return 2; // left
		else
		if( dy > 0 )
			return 1; // up-left
		else
		{//( dy < 0 )
			return 3; // down-left
		}
	}
	else //( dx > 0 )
	{
		if( dy == 0 )
			return 6; // right
		else
		if( dy > 0 )
			return 7; // up-right
		else
		{//( dy < 0 )
			return 5; // down-right
		}
	}
}


void CActor::ValidTest_ChatBlock()
{
	int val = 0;
	if( this->CActor::IsHandicapState(HANDICAPSTATE_DEEPSLEEP) )
		++val;

	m_InstantVar(CInstantVar::CHATBLOCK, val);
}


void CActor::ValidTest_ItemUseBlock()
{
	int val = 0;
	if( this->GetEffective(EFST_SHADOWFORM, 0) )
		++val;
	if( this->GetEffective(EFST_INVISIBILITY, 0) )
		++val;
	if( this->GetEffective(EFST_COLD, 0) )
		++val;
	if( this->GetEffective(EFST_SATURDAY_NIGHT_FEVER, 0) )
		++val;
	if( this->GetEffective(EFST_MANHOLE, 0) )
		++val;

	m_InstantVar(CInstantVar::ITEMUSEBLOCK, val);
}


void CActor::ValidTest_MoveBlock()
{
	int val = 0;
	if( this->GetEffective(EFST_CURSEDCIRCLE_ATKER, 0) )
		++val;
	if( this->GetEffective(EFST_CURSEDCIRCLE_TARGET, 0) )
		++val;
	if( this->GetEffective(EFST_MANHOLE, 0) )
		++val;
	if( this->GetEffective(EFST_FALLENEMPIRE, 0) )
		++val;
	if( this->GetEffective(EFST_MAGNETICFIELD, 0) && !this->GetEffective(EFST_HOVERING, 0) )
		++val;
	if( this->GetEffective(EFST_COLD, 0) )
		++val;
	if( this->GetEffective(EFST_NETHERWORLD, 0) )
		++val;
	if( this->CActor::IsHandicapState(HANDICAPSTATE_DEEPSLEEP) )
		++val;
	if( this->GetEffective(EFST_THORNS_TRAP, 0) )
		++val;
	if( this->GetEffective(EFST_VACUUM_EXTREME, 0) )
		++val;
	if( this->GetEffective(EFST_NEEDLE_OF_PARALYZE, 0) )
		++val;
	if( this->GetEffective(EFST_TINDER_BREAKER, 0) )
		++val;

	m_InstantVar(CInstantVar::MOVEBLOCK, val);
}


void CActor::ValidTest_SkillUseBlock()
{
	int val = 0;
	if( this->GetEffective(EFST_SHADOWFORM, 0) )
		++val;
	if( this->GetEffective(EFST_INVISIBILITY, 0) )
		++val;
	if( this->GetEffective(EFST_IGNORANCE, 0) )
		++val;
	if( this->GetEffective(EFST_MANHOLE, 0) )
		++val;
	if( this->GetEffective(EFST_OBLIVIONCURSE, 0) )
		++val;
	if( this->GetEffective(EFST_CURSEDCIRCLE_TARGET, 0) )
		++val;
	if( this->GetEffective(EFST_COLD, 0) )
		++val;
	if( this->CActor::IsHandicapState(HANDICAPSTATE_DEEPSLEEP) )
		++val;
	if( this->GetEffective(EFST_SILENT_BREEZE, 0) )
		++val;
	if( this->GetEffective(EFST_ALL_RIDING, 0) )
		++val;

	m_InstantVar(CInstantVar::SKILLUSEBLOCK, val);
}


void CActor::ValidTest_MeleeAtkBlock()
{
	int val = 0;
	if( this->GetEffective(EFST_SHADOWFORM, 0) )
		++val;
	if( this->GetEffective(EFST_CURSEDCIRCLE_ATKER, 0) )
		++val;
	if( this->GetEffective(EFST_CURSEDCIRCLE_TARGET, 0) )
		++val;
	if( this->GetEffective(EFST_MANHOLE, 0) )
		++val;
	if( this->GetEffective(EFST_FALLENEMPIRE, 0) )
		++val;
	if( this->GetEffective(EFST_COLD, 0) )
		++val;
	if( this->CActor::IsHandicapState(HANDICAPSTATE_DEEPSLEEP) )
		++val;
	if( this->GetEffective(EFST_ALL_RIDING, 0) )
		++val;

	m_InstantVar(CInstantVar::MELEEATKBLOCK, val);
}


int CActor::ModifyFixedSKcastingTM(const int in_TM, const int in_SKID)
{
	return m_FixedSKcasingTMvar.CFixedSKcastingTMvar::Get(in_TM, in_SKID);
}


DWORD CActor::GetHealthStateRemainMS(const int in_HealthState) const
{
	int i;
	for( i = 0; i < countof(m_HealthStateValue); ++i )
		if( in_HealthState == m_HealthStateValue[i] && m_HealthStateTime[i][0] != 0 )
			break; // found.

	if( i >= countof(m_HealthStateValue) )
		return 0; // not found.

	DWORD healthStateTM = m_HealthStateTime[i][1];
	if( healthStateTM == 9999 )
		return 9999;

	DWORD curTM = timeGetTime();
	if( healthStateTM <= curTM )
		return 0;

	return healthStateTM - curTM;
}


DWORD CActor::GetBodyStateRemainMS(const int in_BodyState) const
{
	if( in_BodyState != m_BodyStateValue || m_BodyStateTime[0] != 0 )
		return 0;

	DWORD bodyStateTM = m_BodyStateTime[1];
	if( bodyStateTM == 9999 )
		return 9999;

	DWORD curTM = timeGetTime();
	if( bodyStateTM <= curTM )
		return 0;

	return bodyStateTM - curTM;
}


namespace {
class CTask_BODYSTATE_BURNNING : public ActorScheduler::CTask
{
public:
	virtual bool operator()(CActor* in_cpActor)
	{
		DWORD CurTM = timeGetTime();

		int maxHP = 0;
		in_cpActor->GetParameterValue(VAR_MAXHP, maxHP);

		const int damage = int(1000 + maxHP * 3 / 100.0);
		SendPacket_ZC_NOTIFY_ACT(in_cpActor, in_cpActor->GetAccountID(), in_cpActor->GetAccountID(), CurTM, 10, 10, damage, 1, 0, 0);

		COMMAND_QUEUE command;
		command.commandID = ATTACKED_IN;
		command.executionTime = CurTM;
		command.sender = in_cpActor->GetAccountID();
		command.par1 = damage;
		command.par2 = 1;
		command.par6 = PROPERTY_FIRE;
		in_cpActor->InsertCommand(&command);

		m_Time += LOOP_TIME;
		return false;
	}

public:
	CTask_BODYSTATE_BURNNING() : ActorScheduler::CTask(ActorSchedulerIdentity::TASK_BODYSTATE_BURNNING, timeGetTime())
	{
		m_Time = timeGetTime() + LOOP_TIME;
	}

	virtual ~CTask_BODYSTATE_BURNNING()
	{
	}

private:
	enum { LOOP_TIME = 3000 };
};
}; // namespace


void CActor::SetBodyStateImpl(const int in_SetBodyState)
{
	switch( in_SetBodyState )
	{
	case BODYSTATE_BURNNING:
	{
		CTask_BODYSTATE_BURNNING* pTask = new(std::nothrow) CTask_BODYSTATE_BURNNING();
		this->CActor::InsertSchedule(std::tr1::shared_ptr<ActorScheduler::CTask>(pTask));
	}
	break;
	};
}


void CActor::ResetBodyStateImpl(const int in_ResetBodyState)
{
	switch( in_ResetBodyState )
	{
	case BODYSTATE_BURNNING:
		this->CActor::DeleteSchedule(ActorSchedulerIdentity::TASK_BODYSTATE_BURNNING);
	break;
	case BODYSTATE_IMPRISON:
		SK_WL_WHITEIMPRISON::TimeOutProc_BODYSTATE_IMPRISON(this, NULL); // guessed
	break;
	};
}


bool CActor::IsFailStartUseSkill()
{
	if( this->GetEffective(EFST_VOLCANIC_ASH, 0) && GetServerRandom(0, 20000) % 100 < 50 )
		return true;

	return false;
}


void CActor::SetHandicapStateEFST(CCharacter* in_cpTargetCH, const int in_EFSTID, const int in_DelayTime, const int in_Percent, const int in_KeepTime)
{
	if( GetServerRandom(0, 20000) % 1000 < in_Percent )
	{
		COMMAND_QUEUE command;
		command.commandID = USE_EFST_IN;
		command.executionTime = timeGetTime() + in_DelayTime;
		command.par1 = in_EFSTID;
		command.par2 = in_KeepTime;
		command.par3 = 1;
		if( in_EFSTID == EFST_SIREN )
			command.par4 = this->GetAccountID();
		in_cpTargetCH->InsertCommand(&command);
	}
}


int CActor::GetSPcostForSkill(const int in_SKID, const int in_SKLevel, const int in_SKType, CSkillTypeInfo* in_cpSKTypeInfo)
{
	if( in_cpSKTypeInfo == NULL )
	{
		if( !g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(in_SKID) )
			return 0;
		//FIXME: in_cpSKTypeInfo not updated with return value
	}

	return in_cpSKTypeInfo->GetSPCost(in_SKLevel);
}


void CActor::SetHealthStateTimeInfo(const int in_firstTime, const int in_secondTime, const int in_state)
{
	int idx = GetIndexFromBitFlag(in_state);

	if( m_HealthStateTime[idx][1] == 9999 && in_secondTime != 0 )
		return;

	if( in_secondTime == 0 )
	{
		m_HealthStateTime[idx][0] = 0;
		m_HealthStateTime[idx][1] = 0;

		if( in_state != HEALTHSTATE_NORMAL )
			this->ResetHealthState(in_state);
		else
			this->SetHealthState(HEALTHSTATE_NORMAL);

		return;
	}

	if( in_secondTime <= 0 || in_firstTime >= in_secondTime )
		return;

	if( m_HealthStateTime[idx][1] != 0 )
	{
		if( in_secondTime == 9999 )
		{
			m_HealthStateTime[idx][1] = 9999;
			return;
		}

		DWORD time = in_secondTime - in_firstTime + timeGetTime();
		if( time == 9999 || m_HealthStateTime[idx][1] < time )
		{
			m_HealthStateTime[idx][1] = time;
			return;
		}
	}
	else
	{
		m_HealthStateTime[idx][0] = in_firstTime + timeGetTime();
		m_HealthStateTime[idx][1] = ( in_secondTime == 9999 ) ? 9999 : in_secondTime + timeGetTime();
		m_HealthStateValue[idx] = in_state;
	}
}


CActor::SKILL_RETURN CActor::Actor_ThirdJobSkillAttackToCharacter(unsigned short SKID, CCharacter* target, MSG_TYPE_SKILLDATA* skilldata, SKILLATTACK_MSG* msg) // 15-26 (ActorThirdJob.cpp)
{
	switch( SKID )
	{
	case SKID_RK_SONICWAVE:
		return this->CActor::RK_SONICWAVE(target, skilldata, msg);
	break;
	default:
		return SKILL_RETURN_UNKNOWN;
	break;
	};
}


CActor::SKILL_RETURN CActor::Actor_ThirdJobSkillOperateToCharacter(unsigned short SKID, CCharacter* target, MSG_TYPE_SKILLDATA* skilldata) // 29-66 (ActorThirdJob.cpp)
{
	switch( SKID )
	{
	case SKID_RK_DEATHBOUND:
		return this->CActor::RK_DEATHBOUND(skilldata);
	break;
	case SKID_RK_IGNITIONBREAK:
		return this->CActor::RK_IGNITIONBREAK(*skilldata);
	break;
	case SKID_RK_DRAGONHOWLING:
		return this->CActor::RK_DRAGONHOWLING(skilldata);
	break;
	case SKID_RK_GIANTGROWTH:
		return this->CActor::RK_GIANTGROWTH(skilldata);
	break;
	case SKID_GC_CLOAKINGEXCEED:
		return this->CActor::GC_CLOAKINGEXCEED(*skilldata);
	break;
	case SKID_GC_PHANTOMMENACE:
		return this->CActor::GC_PHANTOMMENACE(*skilldata);
	break;
	case SKID_GC_HALLUCINATIONWALK:
		return this->CActor::GC_HALLUCINATIONWALK(*skilldata);
	break;
	default:
		return SKILL_RETURN_UNKNOWN;
	break;
	};
}


CActor::SKILL_RETURN CActor::Actor_ThirdJobSkillToGround(unsigned short SKID, MSG_TYPE_SKILLDATA* skilldata) // 69-79 (ActorThirdJob.cpp)
{
	switch( SKID )
	{
	case SKID_RK_WINDCUTTER:
		return this->CActor::RK_WINDCUTTER(*skilldata);
	break;
	default:
		return SKILL_RETURN_UNKNOWN;
	break;
	};
}


void CActor::KnockBack(CCharacter* target, int distance) // 83-91 (ActorThirdJob.cpp)
{
	PosInfo myPos;
	this->GetParameterValue(VAR_CURXPOS, myPos.x);
	this->GetParameterValue(VAR_CURYPOS, myPos.y);

	PosInfo targetPos;
	target->GetParameterValue(VAR_CURXPOS, targetPos.x);
	target->GetParameterValue(VAR_CURYPOS, targetPos.y);

	PosInfo newPos;
	this->CActor::GetPushedPosition(myPos, targetPos, distance, newPos);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, target, CM_KNOCKBACK, newPos.x, newPos.y, 1, 0);
}


void CActor::Broadcast_ZC_NOTIFY_SKILL2(int targetAID, unsigned short SKID, int skLevel) // 96-113 (ActorThirdJob.cpp)
{
	int atkMotionTime;
	this->GetParameterValue(VAR_ATTACKMT, atkMotionTime);

	PACKET_ZC_NOTIFY_SKILL2 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_SKILL2;
	outpacket.SKID = SKID;
	outpacket.AID = this->GetAccountID();
	outpacket.targetID = targetAID;
	outpacket.startTime = timeGetTime();
	outpacket.attackMT = atkMotionTime;
	outpacket.attackedMT = 0;
	outpacket.damage = -30000;
	outpacket.level = skLevel;
	outpacket.count = 1;
	outpacket.action = ACTION_SKILL;

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, this, CM_SEND_DAMAGEPACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
}


hook_func<void (__stdcall *)()> CActor__RK_WINDCUTTER(EXEPATH(), "CActor::RK_WINDCUTTER");
CActor::SKILL_RETURN CActor::RK_WINDCUTTER(const MSG_TYPE_SKILLDATA& in_skilldata) // 17-51 (Actor3rd1_RuneKnight.cpp)
{
	SKILL_RETURN result;
	void* hookptr = CActor__RK_WINDCUTTER;
	__asm lea ecx, in_skilldata
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, eax
	return result;
	//TODO
	/*
	static SK_RK_WINDCUTTER* cpSK_RK_WINDCUTTER = (SK_RK_WINDCUTTER*)g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID_RK_WINDCUTTER);

	this->ReduceSPByUseSkill(in_skilldata.spCost);

	PosInfo posinfo;
	posinfo.x = in_skilldata.xPos;
	posinfo.y = in_skilldata.yPos;

	MSG_TYPE1_TWODWORD msgData;
	msgData.data1 = SKID_RK_WINDCUTTER;
	msgData.data2 = in_skilldata.skLevel;

	int myBaseLevel = 0;
	this->GetParameterValue(VAR_CLEVEL, myBaseLevel);

	int ATKPercent = (in_skilldata.skLevel + 2) * myBaseLevel * 50 / 100;
	this->CActor::Broadcast_ZC_NOTIFY_SKILL2(this->GetAccountID(), SKID_RK_WINDCUTTER, in_skilldata.skLevel);
	this->SplashAttack2(ATKPercent, posinfo, SKILLSPLASH_SQUARE, 2, 6, &msgData, 1, 100, NULL);

	return SKILL_RETURN_SUCCESS;
	*/
}


hook_func<void (__stdcall *)()> CActor__RK_IGNITIONBREAK(EXEPATH(), "CActor::RK_IGNITIONBREAK");
CActor::SKILL_RETURN CActor::RK_IGNITIONBREAK(const MSG_TYPE_SKILLDATA& in_skilldata) // 121-214 (Actor3rd1_RuneKnight.cpp)
{
	CActor::SKILL_RETURN result;
	void* hookptr = CActor__RK_IGNITIONBREAK;
	__asm lea ecx, in_skilldata
	__asm mov edx, this
	__asm call hookptr
	__asm mov eax, result
	return result;
	//TODO
}


hook_func<void (__stdcall *)()> CActor__RK_SONICWAVE(EXEPATH(), "CActor::RK_SONICWAVE");
CActor::SKILL_RETURN CActor::RK_SONICWAVE(CCharacter* in_cpTarget, MSG_TYPE_SKILLDATA* in_skilldata, SKILLATTACK_MSG* in_msg) // 218-236 (Actor3rd1_RuneKnight.cpp)
{
	CActor::SKILL_RETURN result;
	void* hookptr = CActor__RK_SONICWAVE;
	__asm push in_msg
	__asm mov ebx, in_skilldata
//	__asm mov mm1, in_cpTarget
	__asm mov edi, this
	__asm call hookptr
	__asm mov eax, result
	return result;
	//TODO
}


CActor::SKILL_RETURN CActor::RK_DEATHBOUND(MSG_TYPE_SKILLDATA* skilldata) // 36-49 (Actor3rd1_sun.cpp)
{
	static CSkillTypeInfo2* skillTypeInfo = (CSkillTypeInfo2*)g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID_RK_DEATHBOUND);

	this->ReduceSPByUseSkill(skilldata->spCost);

	int atkPercent = skillTypeInfo->CSkillTypeInfo2::GetATKPercent(skilldata->skLevel);
	this->SetEffective(EFST_DEATHBOUND, 2000, 1, atkPercent, 1, 0);

	return SKILL_RETURN_SUCCESS;
}


hook_func<void (__stdcall *)()> CActor__RK_DEATHBOUND_REFLECT(EXEPATH(), "CActor::RK_DEATHBOUND_REFLECT");
void CActor::RK_DEATHBOUND_REFLECT(CCharacter* atker, int& damage, short& leftdamage) // 52-113 (Actor3rd1_sun.cpp)
{
	void* hookptr = CActor__RK_DEATHBOUND_REFLECT;
	__asm lea ax, leftdamage
	__asm push ax
	__asm lea eax, damage
	__asm push damage
	__asm mov edi, atker
	__asm mov ecx, this
	__asm call hookptr
	return;
	//TODO
}


CActor::SKILL_RETURN CActor::RK_DRAGONHOWLING(MSG_TYPE_SKILLDATA* skilldata) // 117-140 (Actor3rd1_sun.cpp)
{
	static CSkillTypeInfo2* skillTypeInfo = (CSkillTypeInfo2*)g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID_RK_DRAGONHOWLING);

	this->ReduceSPByUseSkill(skilldata->spCost);

	int xPos, yPos;
	this->GetParameterValue(VAR_CURXPOS, xPos);
	this->GetParameterValue(VAR_CURXPOS, yPos);

	MSG_TYPE1_TWODWORD msgData;
	msgData.data1 = SKID_RK_DRAGONHOWLING;
	msgData.data2 = skilldata->skLevel;

	int splashRange[5];
	splashRange[0] = 3;
	splashRange[1] = 4;
	splashRange[2] = 5;
	splashRange[3] = 6;
	splashRange[4] = 7;

	STRUCT_SK_INTVALUE* data1 = (STRUCT_SK_INTVALUE*)skillTypeInfo->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA1);
	this->CActor::Broadcast_ZC_NOTIFY_SKILL2(this->GetAccountID(), SKID_RK_DRAGONHOWLING, skilldata->skLevel);
	int val1 = data1->value[skilldata->skLevel - 1];
	int range = splashRange[skilldata->skLevel - 1];
	this->SplashAttack(val1, xPos, yPos, 0, range, range, this->GetAccountID(), &msgData, 0, 1);

	return SKILL_RETURN_SUCCESS;
}


CActor::SKILL_RETURN CActor::RK_GIANTGROWTH(MSG_TYPE_SKILLDATA* skilldata) // 160-169 (Actor3rd1_sun.cpp)
{
	static CSkillTypeInfo2* skillTypeInfo = (CSkillTypeInfo2*)g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID_RK_GIANTGROWTH);

	STRUCT_SK_INTVALUE* data1 = (STRUCT_SK_INTVALUE*)skillTypeInfo->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA1);
	int val1 = data1->value[skilldata->skLevel - 1];
	this->SetEffective(EFST_GIANTGROWTH, val1, 1, 0, 0, 0);

	return SKILL_RETURN_SUCCESS;
}


void CActor::ProcessEffective_ELECTRICSHOCKER() // 172-189 (Actor3rd1_sun.cpp)
{
	DWORD curtime = timeGetTime();
	DWORD shockertime = this->GetEffective(EFST_ELECTRICSHOCKER, 1);

	if( shockertime >= curtime )
		return;

	if( shockertime != 0 )
	{
		int percent = this->GetEffective(EFST_ELECTRICSHOCKER, 0);

		int maxsp;
		this->GetParameterValue(VAR_MAXSP, maxsp);

		this->UpdateParameterValue(VAR_SP, - maxsp * percent / 100);
	}

	m_effectiveList[EFST_ELECTRICSHOCKER].val[1] = curtime + 1000;
}


hook_func<void (__stdcall *)()> CActor__SetEffective_POISONINGWEAPON(EXEPATH(), "CActor::SetEffective_POISONINGWEAPON");
void CActor::SetEffective_POISONINGWEAPON(const int in_PosionEFST, CCharacter* in_cpAtkerCH, int in_DelayTM) // 346-388 (Actor3rd1_sun.cpp)
{
	void* hookptr = CActor__SetEffective_POISONINGWEAPON;
	__asm push in_DelayTM
	__asm push in_cpAtkerCH
	__asm push in_PosionEFST
	__asm mov eax, this
	__asm call hookptr
	return;
	//TODO
	/*
	if( CNewPoisonItemInfo::GetObj()->CNewPoisonItemInfo::IsApplyPosion(this) )
		return; // already poisoned

	if( in_DelayTM == 0 )
	{
		in_DelayTM = CNewPoisonItemInfo::GetObj()->CNewPoisonItemInfo::GetDealyTime(in_PosionEFST);
		if( in_DelayTM <= 0 )
			return;
	}

	int myVIT = 0;
	int myLUK = 0;
	this->GetParameterValue(VAR_VIT, myVIT);
	this->GetParameterValue(VAR_LUK, myLUK);

	int time = in_DelayTM - 1000 * (myLUK + myVIT) / 2;
	if( time < 100 )
		time = 100;

	int sklevel;
	if( in_cpAtkerCH->GetType() == PC_TYPE )
		sklevel = static_cast<CPC*>(in_cpAtkerCH)->m_pcSkill.CPCSkill::GetSkillLevel(SKID_GC_RESEARCHNEWPOISON, 0);
	else
		sklevel = 0;

	this->SetEffective(in_PosionEFST, time, 1, sklevel, 0, 0);
	*/
}


hook_func<void (__stdcall *)()> CActor__GC_CLOAKINGEXCEED(EXEPATH(), "CActor::GC_CLOAKINGEXCEED");
CActor::SKILL_RETURN CActor::GC_CLOAKINGEXCEED(const MSG_TYPE_SKILLDATA& in_skilldata) // 392-421 (Actor3rd1_sun.cpp)
{
	CActor::SKILL_RETURN result;
	void* hookptr = CActor__GC_CLOAKINGEXCEED;
	__asm lea ebx, in_skilldata
	__asm mov edi, this
	__asm call hookptr
	__asm mov eax, result
	return result;
	//TODO
}


hook_func<void (__stdcall *)()> CActor__GC_PHANTOMMENACE(EXEPATH(), "CActor::GC_PHANTOMMENACE");
CActor::SKILL_RETURN CActor::GC_PHANTOMMENACE(const MSG_TYPE_SKILLDATA& in_skilldata) // 424-448 (Actor3rd1_sun.cpp)
{
	CActor::SKILL_RETURN result;
	void* hookptr = CActor__GC_PHANTOMMENACE;
	__asm lea ebx, in_skilldata
	__asm mov edi, this
	__asm call hookptr
	__asm mov eax, result
	return result;
	//TODO
}


hook_func<void (__stdcall *)()> CActor__GC_HALLUCINATIONWALK(EXEPATH(), "CActor::GC_HALLUCINATIONWALK");
CActor::SKILL_RETURN CActor::GC_HALLUCINATIONWALK(const MSG_TYPE_SKILLDATA& in_skilldata) // 131-154 (PC3rd1_GuillotineCross.cpp)
{
	CActor::SKILL_RETURN result;
	void* hookptr = CActor__GC_HALLUCINATIONWALK;
	__asm lea ebx, in_skilldata
	__asm mov edi, this
	__asm call hookptr
	__asm mov eax, result
	return result;
	//TODO
}
