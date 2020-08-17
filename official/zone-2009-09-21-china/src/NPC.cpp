#include "enum.hpp"
#include "CAttackPlusPowerInfo.hpp"
#include "CharacterMgr.h"
#include "FSMMgr.h"
#include "MapResMgr.h"
#include "MonParameterMgr.h"
#include "NPC.h"
#include "CNpcHomun.hpp"
#include "CNpcMercenary.hpp"
#include "ZoneScript.h"
#include "zoneprocess.h"
#include "Common/Packet.h"
#include "shared.h" // Trace


hook_func<int (__cdecl *)(char type)> _IsEventNpc(SERVER, "IsEventNpc");
int __cdecl IsEventNpc(char type) // line 58
{
	return (_IsEventNpc)(type);

	return type == WARP_NPC
		|| type == GUIDE_NPC
		|| type == TALK_NPC
		|| type == TRADER_NPC
		|| type == EFFECT_NPC
		|| type == ARENA_GUIDE_NPC
		|| type == HIDDEN_WARP_NPC
		|| type == CASHTRADER_NPC
		|| type == MOVE_NPC_TYPE01
		|| type == MOVE_NPC_TRADER;
}


hook_method<CNPC* (CNPC::*)(void)> CNPC::_CNPC(SERVER, "CNPC::CNPC");
CNPC::CNPC(void) // line 69
{
	m_type = NPC_TYPE;
	m_mapRes = NULL;
	m_nBanTime = 0;
	m_eatingItemMPool.CMemoryMgr<EATING_ITEM_INVENTORY>::Init(10);
}


hook_method<void (CNPC::*)(void)> CNPC::__CNPC(SERVER, "CNPC::~CNPC");
CNPC::~CNPC(void) // line 78
{
}


//hook_method<int (CNPC::*)(void)> CNPC::_GetJobType(SERVER, "CNPC::GetJobType");
int CNPC::GetJobType(void) // line ??
{
	//return (this->*_GetJobType)();

	return m_characterInfo.job;
}


hook_method<void (CNPC::*)(void)> CNPC::_Init(SERVER, "CNPC::Init");
void CNPC::Init(void) // line 108
{
	return (this->*_Init)();

	this->CActor::Init();
	m_npcType = -1;
	m_mapRes = NULL;
	m_npcUpdater.CNPCUpdater::SetMyOwner(this);
	m_npcUpdater.CNPCUpdater::ResetAttackPCList();
	m_npcStateUpdater.CNPCStateUpdater::SetMyOwner(this);
	m_npcStateUpdater.CNPCStateUpdater::Init();
	m_npcSkill.m_npc = this;
	m_npcSkill.CNPCSkill::Init();
	m_neighborCache.CNeighborCache::Init();
	m_eatingItemMPool.CMemoryMgr<EATING_ITEM_INVENTORY>::Reset();
	m_eatingItem.clear();
	m_pathInfo.CPathInfo::Reset();
	m_myMobList.clear();
	m_effectiveList.clear();
	m_ATKPercentList.clear();
	m_DEFPercentList.clear();
	m_MATKPercentList.clear();
	m_MDEFPercentList.clear();
	memset(&m_characterInfo, 0, sizeof(m_characterInfo));
	m_characterInfo.headerDir = 0;
	m_characterInfo.head = 0;
	m_characterInfo.IsRegen = 1;
	m_characterInfo.isValid = 0;
	this->InitCore();
}


hook_method<void (CNPC::*)(void)> CNPC::_InitTimeInfo(SERVER, "CNPC::InitTimeInfo");
void CNPC::InitTimeInfo(void) // line 251
{
	return (this->*_InitTimeInfo)();

	//TODO
}


//hook_method<unsigned char (CNPC::*)(void)> CNPC::_GetNPCType(SERVER, "CNPC::GetNPCType");
unsigned char CNPC::GetNPCType(void) // line ???
{
//	return (this->*_GetNPCType)();

	return m_npcType;
}


hook_method<void (CNPC::*)(CCharacter* sender, CCharacter* attacker, CCharacter* target, int damage, short count, short level, unsigned short SKID)> CNPC::_NotifySkillAction(SERVER, "CNPC::NotifySkillAction");
void CNPC::NotifySkillAction(CCharacter* sender, CCharacter* attacker, CCharacter* target, int damage, short count, short level, unsigned short SKID) // line 5312 (NPCSkillAttack.cpp)
{
	return (this->*_NotifySkillAction)(sender, attacker, target, damage, count, level, SKID);

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_IsSiegeMode(SERVER, "CNPC::IsSiegeMode");
int CNPC::IsSiegeMode(void) // line 4210
{
	return (this->*_IsSiegeMode)();

	//TODO
}


hook_method<unsigned long (CNPC::*)(void)> CNPC::_GetAccountID(SERVER, "CNPC::GetAccountID");
unsigned long CNPC::GetAccountID(void) // line 339
{
	return (this->*_GetAccountID)();

	//TODO
}


hook_method<int (CNPC::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CNPC::_OnMsg(SERVER, "CNPC::OnMsg");
int CNPC::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // line 343
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	switch( msgID )
	{
	case CM_MODIFYDAMAGE_ATTACKED:
	{
		int& damage = *(int*)((char*)par1 + 0);
		int& isRNGATK = *(int*)((char*)par1 + 4);
		int& type = *(int*)((char*)par1 + 8);
		int& property = *(int*)((char*)par1 + 12);
		int SKID = (int)par2;

		this->CNPC::ModifyDamage_ATKED(sender, damage, isRNGATK, type, property, SKID);
		return damage;
	}

	case CM_REQ_NAME:
	{
		PACKET_ZC_ACK_REQNAME outpacket;
		outpacket.PacketType = HEADER_ZC_ACK_REQNAME;
		outpacket.AID = this->GetAccountID();
		memcpy(outpacket.CName, m_characterInfo.accountName, sizeof(outpacket.CName));
		outpacket.CName[countof(outpacket.CName)-1] = '\0';

		g_characterMgr->CCharacterMgr::SendMsg(receiver, sender, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
		return 0;
	}

	case CM_MOVE_STOP:
	case CM_KNOCKBACK:
		this->CNPC::OnMoveStop(par1, par2, par3);
		return 0;

	case CM_NOTIFY_INFOTOSECTION:
		this->CNPC::NotifyInfoToSection();
		return 0;

	case CM_INIT_CACHEINFO_THEPC:
		this->CNPC::InitThePCCacheInfo(par1);
		return 0;

	case CM_DISAPPEAR:
		m_npcStateUpdater.CNPCStateUpdater::Disappear(par1, 0);
		return 0;

	case CM_EMOTION:
		this->CNPC::OnEmotion(par1);
		return 0;

	case CM_CHANGE_SPRITE:
		m_characterInfo.job = par1;
		this->CNPC::ChangeSprite(par1);
		return 0;

	case CM_SETEFFECTIVE:
		this->SetEffective(par1, par2, par3, 0, 0, 0);
		return 0;

	case CM_RESETEFFECTIVE:
		this->ResetEffective(par1, 0);
		return 0;

	case CM_ADD_MYMOB:
		this->CNPC::AddMYMob(par1);
		return 0;

	case CM_MYMONSTER_DEAD:
		this->CNPC::OnMyMonsterDead(par1, par2);
		return 0;

	case CM_ATTACKSKILL_TOCHARACTER:
	case CM_ATTSKILL_TOCHAR22_1:
	case CM_ATTSKILL_TOCHAR22_2:
		this->CNPC::UseSkillToCharacter(par1, par2, par3);
		return 0;

	case CM_RESET_EFFECTSTATE:
		this->ResetEffectState(par1);
		return 0;

	case CM_SET_EFFECTSTATE:
		this->SetEffectState(par1);
		return 0;

	case CM_MAPMOVE:
		this->CNPC::OnTeleportCharacter(par1, par2, par3);
		return 0;

	case CM_SKILL_GROUNDTYPE:
	case CM_SKILL_GROUNDTYPE22_1:
	case CM_SKILL_GROUNDTYPE22_2:
		this->CNPC::OnGroundSkill(par1, par2, par3);
		return 0;

	case CM_TOUCHED_SKILLOBJECT:
		this->CNPC::OnTouchedSkillObject(par1, par2, par3);
		return 0;

	case CM_OPERATIONSKILL_TOCHARACTER:
	case CM_OPERSKILL_TOCHAR22_1:
	case CM_OPERSKILL_TOCHAR22_2:
		this->CNPC::OperationSkillToCharacter(par1, par2, par3);
		return 0;

	case CM_SPATTACKSKILL_TOCHARACTER:
	case CM_SPATTSKILL_TOCHAR22_2:
		this->CNPC::SPAttackSkillToCharacter(par1, par2, par3);
		return 0;

	case CM_OPERATIONSKILL_TOSELF:
	case CM_OPERSKILL_TOSELF22_1:
	case CM_OPERSKILL_TOSELF22_2:
		this->CNPC::OperationSkillToSelf(par1, par2, par3);
		return 0;

	case CM_NOTIFY_GROUNDSKILL:
	{
		unsigned short SKID = (unsigned short)par1;
		short level = (short)par2;
		short& xPos = *(short*)((char*)par3 + 0);
		short& yPos = *(short*)((char*)par3 + 4);

		this->CNPC::NotifyGroundSkillUsing(SKID, level, xPos, yPos, timeGetTime());
		return 0;
	}

	case CM_SEND_DAMAGEPACKET:
	{
		int& size = (int)par1;
		PACKET& buf = *(PACKET*)par2;

		if( this->IsItPossible(MAPPROPERTY_HIDING_DAMAGE) == 1 )
		{
			switch( buf.PacketType )
			{
			case HEADER_ZC_NOTIFY_ACT:
			{
				PACKET_ZC_NOTIFY_ACT dst;			
				memcpy(&dst, &buf, size);

				if( dst.damage != 0 )
					dst.damage = -29999;

				this->CCharacter::MultiCast((char*)&dst, size);
				return 0;
			}
			break;
			case HEADER_ZC_NOTIFY_SKILL2:
			{
				PACKET_ZC_NOTIFY_SKILL2 dst;
				memcpy(&dst, &buf, size);

				if( dst.damage != 0 )
					dst.damage = -29999;

				this->CCharacter::MultiCast((char*)&dst, size);
				return 0;
			}
			break;
			case HEADER_ZC_NOTIFY_ACT2:
			{
				PACKET_ZC_NOTIFY_ACT2 dst;
				memcpy(&dst, &buf, size);

				if( dst.damage != 0 )
					dst.damage = -29999;

				this->CCharacter::MultiCast((char*)&dst, size);
				return 0;
			}
			break;
			default:
			break;
			}
		}

		this->CCharacter::MultiCast((char*)&buf, size);
		return 0;
	}

	case CM_GET_ENEMYAID:
		return this->m_npcStateUpdater.m_npcStateInfo.enemyAID;

	case CM_MOVE:
	{
		this->CNPC::OnMove((PACKET_CZ_REQUEST_MOVE*)par1);
		return 0;
	}

	case CM_STOP:
		m_npcUpdater.CNPCUpdater::StopMove();
		return 0;

	case CM_MOVETO_MYOWNER:
		m_npcStateUpdater.CNPCStateUpdater::OnMoveToMyOwner(par1);
		return 0;

	case CM_ATTACK_ENEMY:
	{
		CCharacter* ch = g_characterMgr->CCharacterMgr::FastFindCharacter(par1);
		if( ch != NULL && this->IsRechargeTime() )
			m_npcStateUpdater.CNPCStateUpdater::RevengeEnemy(ch, 7);
		return 0;
	}

	case CM_SET_ATKPERCENT:
		this->CNPC::SetATKPercentInfo(par1, par2, par3);
		return 0;

	case CM_SET_DEFPERCENT:
		this->CNPC::SetDEFPercentInfo(par1, par2, par3);
		return 0;

	case CM_ADD_SPECIALZONELIST:
		this->CNPC::AddSpecialZoneList(par1);
		return 0;

	case CM_DEL_SPECIALZONELIST:
		this->CNPC::DelSpecialZoneList();
		return 0;

	case CM_SET_MDEFPERCENT:
		this->CNPC::SetMDEFPercentInfo(par1, par2, par3);
		return 0;

	case CM_RESET_DEFPERCENT:
		this->CNPC::ResetDEFPercentInfo(par1);
		return 0;

	case CM_RESET_MDEFPERCENT:
		this->CNPC::ResetMDEFPercentInfo(par1);
		return 0;

	case CM_NPC_FORCE_USE_SKILL:
	{
		unsigned short& SKID = *(unsigned short*)((char*)par1 + 4);
		int& skLevel = *(int*)((char*)par1 + 8);
		int& castTime = *(int*)((char*)par1 + 12);
		int& chatNo = *(int*)((char*)par1 + 16);

		m_npcSkill.CNPCSkill::ForceUseSkill(SKID, skLevel, castTime, chatNo);
		return 0;
	}

	default:
		return this->CCharacter::OnMsg(sender, receiver, msgID, par1, par2, par3, par4);
	}
}


hook_method<int (CNPC::*)(unsigned short id, int& value)> CNPC::_GetParameterValue(SERVER, "CNPC::GetParameterValue");
int CNPC::GetParameterValue(unsigned short id, int& value) // line 592
{
	return (this->*_GetParameterValue)(id, value);

	//TODO
}


hook_method<int (CNPC::*)(unsigned short id, int value)> CNPC::_UpdateParameterValue(SERVER, "CNPC::UpdateParameterValue");
int CNPC::UpdateParameterValue(unsigned short id, int value) // line 785
{
	return (this->*_UpdateParameterValue)(id, value);

	//TODO
}


hook_method<void (CNPC::*)(COMMAND_QUEUE* command)> CNPC::_InsertCommand(SERVER, "CNPC::InsertCommand");
void CNPC::InsertCommand(COMMAND_QUEUE* command)
{
	return (this->*_InsertCommand)(command);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_CheckCommandQueue(SERVER, "CNPC::CheckCommandQueue");
void CNPC::CheckCommandQueue(void)
{
	return (this->*_CheckCommandQueue)();

	//TODO
}


hook_method<void (CNPC::*)(unsigned long commandID)> CNPC::_DisableCommand(SERVER, "CNPC::DisableCommand");
void CNPC::DisableCommand(unsigned long commandID)
{
	return (this->*_DisableCommand)(commandID);

	//TODO
}


hook_method<COMMAND_QUEUE* (CNPC::*)(unsigned long commandID)> CNPC::_SearchCommand(SERVER, "CNPC::SearchCommand");
COMMAND_QUEUE* CNPC::SearchCommand(unsigned long commandID)
{
	return (this->*_SearchCommand)(commandID);

	//TODO
}


hook_method<int (CNPC::*)(CCharacter* ch, int range)> CNPC::_IsMyArea(SERVER, "CNPC::IsMyArea");
int CNPC::IsMyArea(CCharacter* ch, int range)
{
	return (this->*_IsMyArea)(ch, range);

	return m_npcUpdater.CNPCUpdater::IsMyArea(ch, range);
}


hook_method<unsigned long (CNPC::*)(void)> CNPC::_GetState(SERVER, "CNPC::GetState");
unsigned long CNPC::GetState(void)
{
	return (this->*_GetState)();

	return m_pathInfo.m_moveInfo.state;
}


hook_method<int (CNPC::*)(void)> CNPC::_GetScale(SERVER, "CNPC::GetScale");
int CNPC::GetScale(void)
{
	return (this->*_GetScale)();

	//TODO
}


hook_method<int (CNPC::*)(CCharacter* ch, unsigned long flag)> CNPC::_IsTarget(SERVER, "CNPC::IsTarget");
int CNPC::IsTarget(CCharacter* ch, unsigned long flag)
{
	return (this->*_IsTarget)(ch, flag);

	if( ch == NULL )
	{
		Trace("Step 1");
		return 0;
	}

	if( m_type != 5 )
	{
		Trace("Step 2 AID = %d", ch->GetAccountID());
		return 0;
	}

	if( this->GetEffective(EFST_DA_SPACE, 0) )
	{
		Trace("Step 3 AID = %d", ch->GetAccountID());
		return 0;
	}

	if( this->GetEffective(EFST_MANHOLE, 0) || ch->GetEffective(EFST_MANHOLE, 0) )
	{
		Trace("Step 4 AID = %d", ch->GetAccountID());
		return 0;
	}

	if( m_characterInfo._class == NPC_CLASS_GUARDIAN && m_mapRes->IsAgit() == 1 && static_cast<CAgitMapRes*>(m_mapRes)->CAgitMapRes::IsPKTime() == 0 )
	{
		Trace("Step 5 AID = %d", ch->GetAccountID());
		return 0;
	}

	if( flag & 8 && ch->GetType() == NPC_MOB_TYPE )
	{
		Trace("Step 6 AID = %d", ch->GetAccountID());
		return 0;
	}

	int result;
	if( this->CCharacter::IsTargetInBattleField(ch, flag, result) == 1 )
	{
		Trace("Step 7 AID = %d", ch->GetAccountID());
		return result;
	}

	if( flag & 4 )
		return 1;

	int GDID = 0;

	int type = ch->GetType();
	if( type == PC_TYPE )
	{
		ch->GetParameterValue(VAR_GDID, GDID);
	}
	else
	if( type == NPC_HO_TYPE )
	{
		CPC* owner = static_cast<CNpcHomun*>(ch)->CNpcHomun::GetOwner();
		if( owner != NULL )
			owner->GetParameterValue(VAR_GDID, GDID);
	}
	else
	if( type == NPC_MERSOL_TYPE )
	{
		if( m_characterInfo.job == JT_EMPELIUM )
		{
			Trace("Step 8 AID = %d", ch->GetAccountID());
			return 0;
		}

		if( m_characterInfo._class == NPC_CLASS_BATTLEFIELD )
		{
			Trace("Step 9 AID = %d", ch->GetAccountID());
			return 0;
		}

		CPC* owner = static_cast<CNpcMercenary*>(ch)->CNpcMercenary::GetOwner();
		if( owner != NULL )
			owner->GetParameterValue(VAR_GDID, GDID);
	}

	if( GDID != 0 && this->CNPC::IsSameGuild(GDID) )
	{
		Trace("Step 10 AID = %d", ch->GetAccountID());
		return 0;
	}

	if( flag & 1 && m_characterInfo._class == NPC_CLASS_BOSS )
	{
		Trace("Step 11 AID = %d", ch->GetAccountID());
		return 0;
	}

	return 1;
}


//hook_method<int (CNPC::*)(void)> CNPC::_GetErrorCount(SERVER, "CNPC::GetErrorCount");
int CNPC::GetErrorCount(void)
{
//	return (this->*_GetErrorCount)();

	return m_dwErrorCount;
}


//hook_method<void (CNPC::*)(int i)> CNPC::_SetErrorCount(SERVER, "CNPC::SetErrorCount");
void CNPC::SetErrorCount(int i)
{
//	return (this->*_SetErrorCount)(i);

	m_dwErrorCount = i;
}


hook_method<int (CNPC::*)(void)> CNPC::_IsDamageMotionPossible(SERVER, "CNPC::IsDamageMotionPossible");
int CNPC::IsDamageMotionPossible(void)
{
	return (this->*_IsDamageMotionPossible)();

	//TODO
}


hook_method<int (CNPC::*)(int property)> CNPC::_IsRightProperty(SERVER, "CNPC::IsRightProperty");
int CNPC::IsRightProperty(int property)
{
	return (this->*_IsRightProperty)(property);

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_IsMovable(SERVER, "CNPC::IsMovable");
int CNPC::IsMovable(void)
{
	return (this->*_IsMovable)();

	return !this->GetEffective(EFST_NOACTION, 0)
	    && !this->GetEffective(EFST_AUTOCOUNTER, 0)
	    && !this->GetEffective(EFST_BLADESTOP, 0)
	    && !this->GetEffective(EFST_STOP, 0)
	    && !this->GetEffective(EFST_SPIDERWEB, 0)
	    && !this->GetEffective(EFST_DA_SPACE, 0)
	    && !this->GetEffective(EFST_DEATHBOUND, 0)
	    && !this->GetEffective(EFST_ELECTRICSHOCKER, 0)
	    && !this->GetEffective(EFST_WUGBITE, 0)
	    && !this->GetEffective(EFST_DISABLEMOVE, 0)
	    && this->GetState() != CHARACTER_STATE_DEAD
	    && !this->GetEffective(EFST_ANKLESNARE, 0)
	    && m_characterPInfo.bodyState != 1
	    && m_characterPInfo.bodyState != 2
	    && m_characterPInfo.bodyState != 3
	    && m_characterPInfo.bodyState != 4
	    && m_characterPInfo.bodyState != 8
	    && !(m_characterPInfo.effectState & 2);
}


hook_method<int (CNPC::*)(void)> CNPC::_IsAttackable(SERVER, "CNPC::IsAttackable");
int CNPC::IsAttackable(void)
{
	return (this->*_IsAttackable)();

	//TODO
}


hook_method<int (CNPC::*)(int race, int _class, int level)> CNPC::_IsAvoidable(SERVER, "CNPC::IsAvoidable");
int CNPC::IsAvoidable(int race, int _class, int level)
{
	return (this->*_IsAvoidable)(race, _class, level);

	//TODO
}


hook_method<void (CNPC::*)(int effect)> CNPC::_OnShowEffect(SERVER, "CNPC::OnShowEffect");
void CNPC::OnShowEffect(int effect)
{
	return (this->*_OnShowEffect)(effect);

	//TODO
}


hook_method<void (CNPC::*)(int effect, int numdata)> CNPC::_OnShowEffect3(SERVER, "CNPC::OnShowEffect3");
void CNPC::OnShowEffect3(int effect, int numdata)
{
	return (this->*_OnShowEffect3)(effect, numdata);

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetEffectState(SERVER, "CNPC::GetEffectState");
int CNPC::GetEffectState(void)
{
	return (this->*_GetEffectState)();

	//TODO
}


hook_method<void (CNPC::*)(unsigned long in_loc, CITZMsg* flag)> CNPC::_OnMsgFromItemServer(SERVER, "CNPC::OnMsgFromItemServer");
void CNPC::OnMsgFromItemServer(unsigned long in_loc, CITZMsg* flag)
{
	return (this->*_OnMsgFromItemServer)(in_loc, flag);

	//TODO
}


hook_method<short (CNPC::*)(CCharacter* other, int isRangeAttack)> CNPC::_GetAttackSuccessPercent(SERVER, "CNPC::GetAttackSuccessPercent");
short CNPC::GetAttackSuccessPercent(CCharacter* other, int isRangeAttack)
{
	return (this->*_GetAttackSuccessPercent)(other, isRangeAttack);

	//TODO
}


hook_method<int (CNPC::*)(CCharacter* other, int plusATKPercent, int plusHITPercent, unsigned short SKID, int SKProperty, int isRNGATK)> CNPC::_GetAttackFinalDamage2(SERVER, "?GetAttackFinalDamage@CNPC@@IAEHPAVCCharacter@@HHGHH@Z");
int CNPC::GetAttackFinalDamage(CCharacter* other, int plusATKPercent, int plusHITPercent, unsigned short SKID, int SKProperty, int isRNGATK)
{
	return (this->*_GetAttackFinalDamage2)(other, plusATKPercent, plusHITPercent, SKID, SKProperty, isRNGATK);

	unsigned short v7 = SKProperty * this->GetAttackSuccessPercent(other, isRNGATK) / 100;

	int targetItemDef;
	other->GetParameterValue(VAR_ITEMDEFPOWER, targetItemDef);

	int statusDef;
	other->GetParameterValue(VAR_STATUSDEFPOWER, statusDef);

	if( this->IsRightProperty(PROPERTY_UNDEAD) || m_characterInfo.race == RACETYPE_DEVIL )
	{
		int plusdefPower;
		other->GetParameterValue(VAR_PLUSDEFPOWERINACOLYTE, plusdefPower);
		statusDef += plusdefPower;
	}

	int damage;
	if( this->GetEffective(EFST_AUTOCOUNTER, 0) )
	{
		damage = this->GetAttackPoint(other, 0, 0) * plusATKPercent / 100;
	}
	else
	if( GetServerRandom(0, 20000) % 100 < v7 )
	{
		int v19 = this->GetAttackPoint(other, 0, 0) * plusATKPercent / 100;
		damage = int(v19 - v19 * targetItemDef / 100.0 - statusDef);

		if( damage < 1 )
			damage = 1;
	}
	else
	{// missed
		damage = 0;
	}

	if( other->GetType() != SKILL_TYPE )
	{
		if( SKProperty == PROPERTY_NOTHING )
		{
			if( this->GetEffective(EFST_ENCHANTPOISON, 0) )
				SKProperty = PROPERTY_POISON;
			else
			if( this->GetType() == NPC_MERSOL_TYPE )
				SKProperty = this->GetWeaponProperty(2, 0);
			else
				return damage;
		}

		int curstate = 0;
		other->GetParameterValue(VAR_CURRENTSTATE, curstate);

		int result;
		g_zoneScript->CZoneScript::GetAtkPlusPWByProperty(curstate, SKProperty, result);

		this->ModifyAttackPowerByEffective(other, SKProperty, result);
	}

	if( this->GetEffective(EFST_BERSERK, 0) > 0 )
		damage *= 2;

	return damage;
}


hook_method<int (CNPC::*)(ATTACK_INFO* info)> CNPC::_GetAttackFinalDamage(SERVER, "?GetAttackFinalDamage@CNPC@@UAEHPAUATTACK_INFO@@@Z");
int CNPC::GetAttackFinalDamage(ATTACK_INFO* info)
{
	return (this->*_GetAttackFinalDamage)(info);

	return this->CNPC::GetAttackFinalDamage(info->target, info->plusATTPowerPercent, info->plusATTSuccessPercent, info->SKID, info->skillProperty, info->isRangeAttack);
}


hook_method<int (CNPC::*)(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill)> CNPC::_SkillAttack(SERVER, "CNPC::SkillAttack");
int CNPC::SkillAttack(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill)
{
	return (this->*_SkillAttack)(msg, plusATTPowerPercent, plusATTSuccessPercent, in_bHideSkill);

	//TODO
}


hook_method<short (CNPC::*)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count)> CNPC::_SplashAttack(SERVER, "CNPC::SplashAttack");
short CNPC::SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count)
{
	return (this->*_SplashAttack)(val1, xPos, yPos, type, range, rangeIn, exceptAID, msgDataPtr, val2, count);

	//TODO
}


hook_method<int (CNPC::*)(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc)> CNPC::_SplashAttack2(SERVER, "CNPC::SplashAttack2");
int CNPC::SplashAttack2(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc)
{
	return (this->*_SplashAttack2)(plusATTPower, dest, type, halfWidth, height, msgData, count, plusHitPercent, specialSrc);

	//TODO
}


hook_method<int (CNPC::*)(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime)> CNPC::_SetHandicapState(SERVER, "CNPC::SetHandicapState");
int CNPC::SetHandicapState(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime)
{
	return (this->*_SetHandicapState)(state, other, percent, preDelayTime, delayTime, isSpell, isFixedDelayTime);

	//TODO
}


hook_method<int (CNPC::*)(int index, int time, int val1, int val2, int val3, int isSendClient)> CNPC::_SetEffective(SERVER, "CNPC::SetEffective");
int CNPC::SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient)
{
	return (this->*_SetEffective)(index, time, val1, val2, val3, isSendClient);

	//TODO
}


hook_method<void (CNPC::*)(int index, int val)> CNPC::_ResetEffective(SERVER, "CNPC::ResetEffective");
void CNPC::ResetEffective(int index, int val)
{
	return (this->*_ResetEffective)(index, val);

	//TODO
}


hook_method<void (CNPC::*)(const int in_plusATTPower, const CCharacter* in_srcCH, const CCharacter* in_otherCH, const int in_destDir, const unsigned short in_SKID, const int in_DistCellFactor, mystd::map<CCharacter *,CollideInfo>& io_collidedList)> CNPC::_CollideSplashAttack(SERVER, "CNPC::CollideSplashAttack");
void CNPC::CollideSplashAttack(const int in_plusATTPower, const CCharacter* in_srcCH, const CCharacter* in_otherCH, const int in_destDir, const unsigned short in_SKID, const int in_DistCellFactor, mystd::map<CCharacter *,CollideInfo>& io_collidedList)
{
	return (this->*_CollideSplashAttack)(in_plusATTPower, in_srcCH, in_otherCH, in_destDir, in_SKID, in_DistCellFactor, io_collidedList);

	//TODO
}


hook_method<bool (CNPC::*)(int index, int& SKID, bool& isPlaySolo)> CNPC::_IsGroundEffective(SERVER, "CNPC::IsGroundEffective");
bool CNPC::IsGroundEffective(int index, int& SKID, bool& isPlaySolo)
{
	return (this->*_IsGroundEffective)(index, SKID, isPlaySolo);

	//TODO
}


hook_method<void (CNPC::*)(int par1, int par2, bool par3)> CNPC::_ProcessGroundEffective(SERVER, "CNPC::ProcessGroundEffective");
void CNPC::ProcessGroundEffective(int par1, int par2, bool par3)
{
	return (this->*_ProcessGroundEffective)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int value)> CNPC::_SetOnShowEFST(SERVER, "CNPC::SetOnShowEFST");
void CNPC::SetOnShowEFST(int value)
{
	return (this->*_SetOnShowEFST)(value);

	//TODO
}


hook_method<void (CNPC::*)(int value)> CNPC::_SetOffShowEFST(SERVER, "CNPC::SetOffShowEFST");
void CNPC::SetOffShowEFST(int value)
{
	return (this->*_SetOffShowEFST)(value);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, unsigned short type, unsigned long time, int amount)> CNPC::_OnChangeStatusAmount(SERVER, "CNPC::OnChangeStatusAmount");
void CNPC::OnChangeStatusAmount(int SKID, unsigned short type, unsigned long time, int amount)
{
	return (this->*_OnChangeStatusAmount)(SKID, type, time, amount);

	//TODO
}


hook_method<void (CNPC::*)(unsigned short type, int amount)> CNPC::_NotifyStatusAmount(SERVER, "CNPC::NotifyStatusAmount");
void CNPC::NotifyStatusAmount(unsigned short type, int amount)
{
	return (this->*_NotifyStatusAmount)(type, amount);

	//TODO
}


hook_method<char (CNPC::*)(void)> CNPC::_GetCampID(SERVER, "CNPC::GetCampID");
char CNPC::GetCampID(void)
{
	return (this->*_GetCampID)();

	//TODO
}


hook_method<void (CNPC::*)(char campID)> CNPC::_SetCampID(SERVER, "CNPC::SetCampID");
void CNPC::SetCampID(char campID)
{
	return (this->*_SetCampID)(campID);

	//TODO
}


hook_method<const char* (CNPC::*)(void)> CNPC::_GetNamePtr(SERVER, "CNPC::GetNamePtr");
const char* CNPC::GetNamePtr(void)
{
	return (this->*_GetNamePtr)();

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetHealthState(SERVER, "CNPC::GetHealthState");
short CNPC::GetHealthState(void)
{
	return (this->*_GetHealthState)();

	//TODO
}


hook_method<void (CNPC::*)(short state)> CNPC::_ResetHealthState(SERVER, "CNPC::ResetHealthState");
void CNPC::ResetHealthState(short state)
{
	return (this->*_ResetHealthState)(state);

	//TODO
}


hook_method<void (CNPC::*)(unsigned long time, int state)> CNPC::_SetEffectStateTimeInfo(SERVER, "CNPC::SetEffectStateTimeInfo");
void CNPC::SetEffectStateTimeInfo(unsigned long time, int state)
{
	return (this->*_SetEffectStateTimeInfo)(time, state);

	//TODO
}


hook_method<void (CNPC::*)(int state)> CNPC::_ResetEffectState(SERVER, "CNPC::ResetEffectState");
void CNPC::ResetEffectState(int state)
{
	return (this->*_ResetEffectState)(state);

	//TODO
}


hook_method<void (CNPC::*)(int state)> CNPC::_SetEffectState(SERVER, "CNPC::SetEffectState");
void CNPC::SetEffectState(int state)
{
	return (this->*_SetEffectState)(state);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_Reset(SERVER, "CNPC::Reset");
void CNPC::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


hook_method<void (CNPC::*)(unsigned long killer)> CNPC::_OnDead(SERVER, "CNPC::OnDead");
void CNPC::OnDead(unsigned long killer)
{
	return (this->*_OnDead)(killer);

	Trace("Dead:%d\n", m_characterInfo.accountID);

	if( this->GetType() != NPC_MOB_TYPE )
		this->Dump(0, killer);

	m_npcStateUpdater.Disappear(1, killer);

	g_characterMgr->SendMsg((CCharacter *)this, killer, CM_KILLED, (int)this, 0, 0, 0);

	if ( killer )
	{
		if( m_characterInfo.job == JT_EMPELIUM )
		{
			CAgitMapRes* mapres = (CAgitMapRes*)this->CCharacter::m_mapRes;
			if( mapres->IsAgit() )
				mapres->CAgitMapRes::ChangeOwner(killer);
		}
	}
}


hook_method<void (CNPC::*)(const int in_Length, char* in_pBuffer)> CNPC::_Send(SERVER, "CNPC::Send");
void CNPC::Send(const int in_Length, char* in_pBuffer)
{
	return (this->*_Send)(in_Length, in_pBuffer);

	//TODO
}


hook_method<void (CNPC::*)(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause)> CNPC::_SkillUseAck(SERVER, "CNPC::SkillUseAck");
void CNPC::SkillUseAck(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause)
{
	return (this->*_SkillUseAck)(SKID, NUM, result, cause);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_OnProcess(SERVER, "CNPC::OnProcess");
void CNPC::OnProcess(void)
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<int (CNPC::*)(CCharacter* other, unsigned short SKID, int property)> CNPC::_GetAttackPoint(SERVER, "CNPC::GetAttackPoint");
int CNPC::GetAttackPoint(CCharacter* other, unsigned short SKID, int property)
{
	return (this->*_GetAttackPoint)(other, SKID, property);

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetSpeed(SERVER, "CNPC::GetSpeed");
int CNPC::GetSpeed(void)
{
	return (this->*_GetSpeed)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetAvoidableSuccessPercent(SERVER, "CNPC::GetAvoidableSuccessPercent");
int CNPC::GetAvoidableSuccessPercent(void)
{
	return (this->*_GetAvoidableSuccessPercent)();

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetStatusDef(SERVER, "CNPC::GetStatusDef");
short CNPC::GetStatusDef(void)
{
	return (this->*_GetStatusDef)();

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetDefencePoint(SERVER, "CNPC::GetDefencePoint");
short CNPC::GetDefencePoint(void)
{
	return (this->*_GetDefencePoint)();

	//TODO
}


hook_method<int (CNPC::*)(int value)> CNPC::_GetModifiedValueByEnemySize(SERVER, "CNPC::GetModifiedValueByEnemySize");
int CNPC::GetModifiedValueByEnemySize(int value)
{
	return (this->*_GetModifiedValueByEnemySize)(value);

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetItemMagicDef(SERVER, "CNPC::GetItemMagicDef");
short CNPC::GetItemMagicDef(void)
{
	return (this->*_GetItemMagicDef)();

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetStatusMagicDef(SERVER, "CNPC::GetStatusMagicDef");
short CNPC::GetStatusMagicDef(void)
{
	return (this->*_GetStatusMagicDef)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetMaxHP(SERVER, "CNPC::GetMaxHP");
int CNPC::GetMaxHP(void)
{
	return (this->*_GetMaxHP)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetMaxSP(SERVER, "CNPC::GetMaxSP");
int CNPC::GetMaxSP(void)
{
	return (this->*_GetMaxSP)();

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetDexValue(SERVER, "CNPC::GetDexValue");
short CNPC::GetDexValue(void)
{
	return (this->*_GetDexValue)();

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetIntValue(SERVER, "CNPC::GetIntValue");
short CNPC::GetIntValue(void)
{
	return (this->*_GetIntValue)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_IsRechargeTime(SERVER, "CNPC::IsRechargeTime");
int CNPC::IsRechargeTime(void)
{
	return (this->*_IsRechargeTime)();

	//TODO
}


hook_method<void (CNPC::*)(CCharacter* ch, int attackProperty, int& damage)> CNPC::_ModifyAttackPowerByEffective(SERVER, "CNPC::ModifyAttackPowerByEffective");
void CNPC::ModifyAttackPowerByEffective(CCharacter* ch, int attackProperty, int& damage)
{
	return (this->*_ModifyAttackPowerByEffective)(ch, attackProperty, damage);

	//TODO
}


hook_method<unsigned short (CNPC::*)(int percent)> CNPC::_GetLostItem(SERVER, "CNPC::GetLostItem");
unsigned short CNPC::GetLostItem(int percent)
{
	return (this->*_GetLostItem)(percent);

	return m_npcStateUpdater.CNPCStateUpdater::GetLostItem(percent);
}


hook_method<int (CNPC::*)(void)> CNPC::_GetATKHasteVal1(SERVER, "CNPC::GetATKHasteVal1");
int CNPC::GetATKHasteVal1(void)
{
	return (this->*_GetATKHasteVal1)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetATKHasteVal2(SERVER, "CNPC::GetATKHasteVal2");
int CNPC::GetATKHasteVal2(void)
{
	return (this->*_GetATKHasteVal2)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetAttackSlowValue(SERVER, "CNPC::GetAttackSlowValue");
int CNPC::GetAttackSlowValue(void)
{
	return (this->*_GetAttackSlowValue)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetMoveHasteValue(SERVER, "CNPC::GetMoveHasteValue");
int CNPC::GetMoveHasteValue(void)
{
	return (this->*_GetMoveHasteValue)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetMoveSlowValue(SERVER, "CNPC::GetMoveSlowValue");
int CNPC::GetMoveSlowValue(void)
{
	return (this->*_GetMoveSlowValue)();

	//TODO
}


//hook_method<void (CNPC::*)(unsigned long AID)> CNPC::_SetParentAID(SERVER, "CNPC::SetParentAID");
void CNPC::SetParentAID(unsigned long AID)
{
//	return (this->*_SetParentAID)(AID);

	m_myParentAID = AID;
}


//hook_method<unsigned long (CNPC::*)(void)> CNPC::_GetParentAID(SERVER, "CNPC::GetParentAID");
unsigned long CNPC::GetParentAID(void)
{
//	return (this->*_GetParentAID)();

	return m_myParentAID;
}


//hook_method<void (CNPC::*)(int flag)> CNPC::_SetRegen(SERVER, "CNPC::SetRegen");
void CNPC::SetRegen(int flag)
{
//	return (this->*_SetRegen)(flag);

	m_characterInfo.IsRegen = flag;
}


//hook_method<int (CNPC::*)(void)> CNPC::_IsRegen(SERVER, "CNPC::IsRegen");
int CNPC::IsRegen(void)
{
//	return (this->*_IsRegen)();

	return m_characterInfo.IsRegen;
}


//hook_method<char * (CNPC::*)(void)> CNPC::_GetAccountName(SERVER, "CNPC::GetAccountName");
char * CNPC::GetAccountName(void)
{
//	return (this->*_GetAccountName)();

	return m_characterInfo.accountName;
}


//hook_method<short (CNPC::*)(void)> CNPC::_GetAttackRange(SERVER, "CNPC::GetAttackRange");
short CNPC::GetAttackRange(void)
{
//	return (this->*_GetAttackRange)();

	return m_characterInfo.attackRange;
}


hook_method<int (CNPC::*)(void)> CNPC::_GetRevivalTerm(SERVER, "CNPC::GetRevivalTerm");
int CNPC::GetRevivalTerm(void)
{
	return (this->*_GetRevivalTerm)();

	//FIXME: duplicate evaluation of function with side-effects, this check doesn't work
	return max(1000, GetServerRandom(m_characterInfo.RegenMinTime, m_characterInfo.RegenMinTime + m_characterInfo.RegenMaxTime));
}


hook_method<int (CNPC::*)(void)> CNPC::_GetAttackMotionTime(SERVER, "CNPC::GetAttackMotionTime");
int CNPC::GetAttackMotionTime(void)
{
	return (this->*_GetAttackMotionTime)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetAttackedMotionTime(SERVER, "CNPC::GetAttackedMotionTime");
int CNPC::GetAttackedMotionTime(void)
{
	return (this->*_GetAttackedMotionTime)();

	//TODO
}


//hook_method<int (CNPC::*)(void)> CNPC::_IsCritical(SERVER, "CNPC::IsCritical");
int CNPC::IsCritical(void)
{
//	return (this->*_IsCritical)();

	return 0;
}


//hook_method<NpcInfo* (CNPC::*)(void)> CNPC::_GetCharacterInfo(SERVER, "CNPC::GetCharacterInfo");
NpcInfo* CNPC::GetCharacterInfo(void)
{
//	return (this->*_GetCharacterInfo)();

	return &m_characterInfo;
}


//hook_method<unsigned long (CNPC::*)(void)> CNPC::_GetCurrentFSMState(SERVER, "CNPC::GetCurrentFSMState");
unsigned long CNPC::GetCurrentFSMState(void)
{
//	return (this->*_GetCurrentFSMState)();

	return m_currentState;
}


hook_method<void (CNPC::*)(unsigned long state)> CNPC::_SetCurrentFSMState(SERVER, "CNPC::SetCurrentFSMState");
void CNPC::SetCurrentFSMState(unsigned long state)
{
	return (this->*_SetCurrentFSMState)(state);

	if( state == m_currentState )
		return; // nothing to do.

	m_asDelta = 0;

	if( state == DEAD_ST )
	{
		m_currentState = DEAD_ST;
		m_pathInfo.m_moveInfo.state = CHARACTER_STATE_DEAD;
	}
	else
	{
		if( state == IDLE_ST )
		{
			m_npcStateUpdater.m_npcStateInfo.enemyAID = 0;
			m_npcStateUpdater.m_npcStateInfo.waitStartTime = timeGetTime();
			if( this->GetEffective(EFST_SIEGEMODE, 0) )
				this->ResetEffective(EFST_SIEGEMODE, state);
		}
		
		m_currentState = state;
	}
}


hook_method<void (CNPC::*)(unsigned short SKID, int skLevel, int targetAID, int xPos, int yPos)> CNPC::_OnUseSkill(SERVER, "CNPC::OnUseSkill");
void CNPC::OnUseSkill(unsigned short SKID, int skLevel, int targetAID, int xPos, int yPos)
{
	return (this->*_OnUseSkill)(SKID, skLevel, targetAID, xPos, yPos);

	//TODO
}


hook_method<CCharacter* (CNPC::*)(void)> CNPC::_GetTarget(SERVER, "CNPC::GetTarget");
CCharacter* CNPC::GetTarget(void)
{
	return (this->*_GetTarget)();

	//TODO
}


//hook_method<void (CNPC::*)(int flag)> CNPC::_SetFSMDependent(SERVER, "CNPC::SetFSMDependent");
void CNPC::SetFSMDependent(int flag)
{
//	return (this->*_SetFSMDependent)(flag);

	m_isFSMDependent = flag;
}


/* hook_method<int (CNPC::*)(void)> CNPC::_IsFSMDependent(SERVER, "CNPC::IsFSMDependent");
int CNPC::IsFSMDependent(void)
{
	return (this->*_IsFSMDependent)();

	//TODO
} */


//hook_method<void (CNPC::*)(void)> CNPC::_StopMove(SERVER, "CNPC::StopMove");
void CNPC::StopMove(void)
{
//	return (this->*_StopMove)();

	m_npcUpdater.CNPCUpdater::StopMove();
}


hook_method<int (CNPC::*)(int range)> CNPC::_IsMovableAround(SERVER, "CNPC::IsMovableAround");
int CNPC::IsMovableAround(int range)
{
	return (this->*_IsMovableAround)(range);

	//TODO
}


//hook_method<unsigned long (CNPC::*)(void)> CNPC::_GetEnemyAID(SERVER, "CNPC::GetEnemyAID");
unsigned long CNPC::GetEnemyAID(void)
{
//	return (this->*_GetEnemyAID)();

	return m_npcStateUpdater.m_npcStateInfo.enemyAID;
}


//hook_method<void (CNPC::*)(unsigned long AID)> CNPC::_SetEnemyAID(SERVER, "CNPC::SetEnemyAID");
void CNPC::SetEnemyAID(unsigned long AID)
{
//	return (this->*_SetEnemyAID)(AID);

	m_npcStateUpdater.m_npcStateInfo.enemyAID = AID;
}


hook_method<void (CNPC::*)(short state)> CNPC::_SetBodyState(SERVER, "CNPC::SetBodyState");
void CNPC::SetBodyState(short state)
{
	return (this->*_SetBodyState)(state);

	m_characterPInfo.bodyState = state;

	if( state == 0 && m_characterInfo.race == RACETYPE_UNDEAD )
		m_characterPInfo.bodyState = BODY_UNDEAD;

	this->CNPC::MultiCastStateInfo();
}


hook_method<void (CNPC::*)(short state)> CNPC::_SetHealthState(SERVER, "CNPC::SetHealthState");
void CNPC::SetHealthState(short state)
{
	return (this->*_SetHealthState)(state);

	//TODO
}


hook_method<void (CNPC::*)(short state)> CNPC::_SetCurrentState(SERVER, "CNPC::SetCurrentState");
void CNPC::SetCurrentState(short state)
{
	return (this->*_SetCurrentState)(state);

	m_characterPInfo.currentProperty = state;
	this->CNPC::MultiCastStateInfo();
}


//hook_method<void (CNPC::*)(int speed)> CNPC::_SetSpeed(SERVER, "CNPC::SetSpeed");
void CNPC::SetSpeed(int speed)
{
//	return (this->*_SetSpeed)(speed);

	m_characterInfo.speed = speed;
}


//hook_method<void (CNPC::*)(void)> CNPC::_SetZenyLost(SERVER, "CNPC::SetZenyLost");
void CNPC::SetZenyLost(void)
{
//	return (this->*_SetZenyLost)();

	m_npcStateUpdater.m_isZenyLost = 1;
}


//hook_method<int (CNPC::*)(void)> CNPC::_IsZenyLost(SERVER, "CNPC::IsZenyLost");
int CNPC::IsZenyLost(void)
{
//	return (this->*_IsZenyLost)();

	return m_npcStateUpdater.m_isZenyLost;
}


hook_method<int (CNPC::*)(void* p)> CNPC::_InitByPacket(SERVER, "CNPC::InitByPacket");
int CNPC::InitByPacket(void* p)
{
	return (this->*_InitByPacket)(p);

	PACKET_NZ_NEWNPC& packet = *(PACKET_NZ_NEWNPC*)p;

	if( this->m_characterInfo.isValid )
	{
		Trace("attempt to twice Init.");
		return FALSE;
	}

	m_npcType = packet.npcType;
	int x = packet.xPos;
	int y = packet.yPos;

	m_characterInfo.job = packet.spriteType;
	m_characterInfo.sex = 0;
	m_characterInfo.xSize = packet.xSize;
	m_characterInfo.ySize = packet.ySize;
	m_characterInfo.head = 0;
	m_characterInfo.weapon = 0;
	m_characterInfo.accessory = 0;
	m_characterInfo.RegenMinTime = packet.RegenMinTime;
	m_characterInfo.RegenMaxTime = packet.RegenMaxTime;
	m_characterInfo.revivalYPos = packet.yPos;
	m_characterInfo.RegenType = packet.RegenType;
	m_characterInfo.revivalXPos = packet.xPos;
	m_characterInfo.revivalXRange = packet.xSize;
	m_characterInfo.revivalYRange = packet.ySize;
	memcpy(m_characterInfo.mapName, packet.mapName, sizeof(m_characterInfo.mapName));
	memcpy(m_characterInfo.accountName, packet.NPCName, sizeof(m_characterInfo.accountName));
	m_characterInfo.accountName[sizeof(m_characterInfo.accountName)-1] = '\0';
	m_characterInfo.originalJob = m_characterInfo.job;

	m_npcStateUpdater.CNPCStateUpdater::SetFSM(g_fsmMgr->CFSMMgr::GetFSM(m_npcType));
	if( !m_npcStateUpdater.CNPCStateUpdater::GetFSM() )
	{
		char errMsg[256];
		memset(errMsg, '\0', sizeof(errMsg));
		sprintf(errMsg, "spriteType:%d, npcType:%d FSM is NULL\n", packet.spriteType, m_npcType);
		Trace(errMsg);
		MessageBoxA(NULL, errMsg, NULL, MB_OK);
		return FALSE;
	}

	if( !this->CNPC::SetParameter() )
	{
		Trace("spriteType:%d, npcType:%d FAIL TO GET PARAMETER.\n", packet.spriteType, m_npcType);
		return FALSE;
	}

	m_mapRes = g_mapResMgr->CMapResMgr::GetMapRes(m_characterInfo.mapName);
	if( m_mapRes == NULL )
	{
		Trace("m_mapRes is NULL, map[%s] spriteType[%d] npcType[%d].\n", m_characterInfo.mapName, packet.spriteType, m_npcType);
		return FALSE;
	}

	m_characterInfo.mapID = m_mapRes->CMapRes::GetID();
	int isVisible = 1;

	if( m_mapRes->IsAgit() )
	{
		CAgitMapRes* agitMapRes = (CAgitMapRes*)m_mapRes;

		BOOL ret = TRUE;

		if( m_characterInfo.job == JT_1_M_JOBTESTER )
			ret = agitMapRes->CAgitMapRes::RegisterNPC(1, this, &isVisible);
		else
		if( m_characterInfo.job == JT_4_F_KAFRA1 )
			ret = agitMapRes->CAgitMapRes::RegisterNPC(3, this, &isVisible);
		else
		if( m_characterInfo.job >= JT_ARCHER_GUARDIAN && m_characterInfo.job <= JT_SOLDIER_GUARDIAN )
			ret = agitMapRes->CAgitMapRes::RegisterNPC(0, this, &isVisible);
		else
		if( m_characterInfo.job == JT_EMPELIUM )
			ret = agitMapRes->CAgitMapRes::RegisterNPC(2, this, &isVisible);
		else
		if( m_characterInfo.job >= JT_TREASURE_BOX1 && m_characterInfo.job <= JT_TREASURE_BOX40 )
			ret = agitMapRes->CAgitMapRes::RegisterNPC(4, this, &isVisible);
		else
		if( m_characterInfo.job >= JT_TREASURE_BOX41 && m_characterInfo.job <= JT_TREASURE_BOX49 )
			ret = agitMapRes->CAgitMapRes::RegisterNPC(4, this, &isVisible);

		if( ret == FALSE )
			return FALSE;
	}

	if( isVisible )
	{
		if( x != 0 && y != 0 )
		{
			if( this->GetType() == NPC_MOB_TYPE )
			{
				if( packet.force )
				{
					if( packet.xSize != 0 && packet.ySize != 0 )
					{
						m_mapRes->CMapRes::GetRandomPosByRange(x, y, packet.xSize, packet.ySize, this->GetAccountID());
					}
				}
				else
				{
					if( !m_mapRes->CMapRes::GetRandomPosByRange(x, y, packet.xSize, packet.ySize, this->GetAccountID()) )
					{
						BOOL ret = m_mapRes->CMapRes::GetRandomPos(x, y);
						if( ret == FALSE )
							return FALSE;
					}
				}
			}
		}
		else
		{
			if( !m_mapRes->CMapRes::GetRandomPos(x, y) )
				return FALSE;
		}

		if( !m_npcUpdater.CNPCUpdater::InitPosition(x, y, packet.direction) )
			return FALSE;

		m_characterInfo.isValid = 1;

		if( m_myParentAID != 0 )
			g_characterMgr->CCharacterMgr::SendMsg(this, m_myParentAID, CM_ADD_MYMOB, this->GetAccountID(), 0, 0, 0);

		this->CNPC::SpawnMyMob(packet.spriteType);
	}
	else
	{
		m_characterInfo.RegenType = 2;
		this->CNPC::SetCurrentFSMState(11);
	}

	this->CNPC::InitSkill();

	if( m_characterInfo.isValid )
		m_npcUpdater.CNPCUpdater::CheckMove();

	Trace("NPC[%d] created type:%d, %s, (%d, %d)\n", this->GetAccountID(), m_npcType, packet.mapName, x, y);

	if( m_characterInfo.job == JT_WARPNPC )
		g_characterMgr->CCharacterMgr::AddWarpNpcList(m_mapRes, this);

	return TRUE;
}


//hook_method<int (CNPC::*)(int AID)> CNPC::_SetAccountID(SERVER, "CNPC::SetAccountID");
int CNPC::SetAccountID(int AID)
{
//	return (this->*_SetAccountID)(AID);

	return m_npcUpdater.CNPCUpdater::SetAccountID(AID);
}


hook_method<bool (CNPC::*)(const char* map_name)> CNPC::_RegistBattleFiledNpc(SERVER, "CNPC::RegistBattleFiledNpc");
bool CNPC::RegistBattleFiledNpc(const char* map_name)
{
	return (this->*_RegistBattleFiledNpc)(map_name);

	//TODO
}


hook_method<int (CNPC::*)(const char camp_code)> CNPC::_GetBattleFieldAliveMemberCount(SERVER, "CNPC::GetBattleFieldAliveMemberCount");
int CNPC::GetBattleFieldAliveMemberCount(const char camp_code)
{
	return (this->*_GetBattleFieldAliveMemberCount)(camp_code);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_KVM_StartAliveCheck(SERVER, "CNPC::KVM_StartAliveCheck");
void CNPC::KVM_StartAliveCheck(void)
{
	return (this->*_KVM_StartAliveCheck)();

	//TODO
}


hook_method<void (CNPC::*)(const char* sw)> CNPC::_KVM_Npc_Noti(SERVER, "CNPC::KVM_Npc_Noti");
void CNPC::KVM_Npc_Noti(const char* sw)
{
	return (this->*_KVM_Npc_Noti)(sw);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_InitSkill(SERVER, "CNPC::InitSkill");
void CNPC::InitSkill(void)
{
	return (this->*_InitSkill)();

	//TODO
}


hook_method<void (CNPC::*)(int closeType, int killer)> CNPC::_Dump(SERVER, "CNPC::Dump");
void CNPC::Dump(int closeType, int killer)
{
	return (this->*_Dump)(closeType, killer);

	FILE* log;
	char szTemp[256];

	if( this->CClient::m_dwErrorCount >= 4 )
		this->CClient::m_dwErrorCount = 0;

	log = fopen("npc_disappear.txt", "at");

	if ( log != NULL )
	{
		memset(szTemp, 0, sizeof(szTemp));
		fprintf(log, "*------------------------------------------------------------*\n");
		fprintf(log, "date:%s\n", _strdate(szTemp));
		fprintf(log, "time:%s\n", _strtime(szTemp));
		fprintf(log, "ErrorCount:%d\n", this->CClient::m_dwErrorCount);
		fprintf(log, "closeType:%d\n", closeType);
		fprintf(log, "killer:%d\n", killer);
		fprintf(log, "NPC information\n");
		this->m_characterInfo.mapName[15] = 0;
		this->m_characterInfo.accountName[23] = 0;
		fprintf(log, "AID:%d\n", this->GetAccountID());
		fprintf(log, "Name:%s\n", this->m_characterInfo.accountName);
		fprintf(log, "SpriteType:%d\n", this->m_characterInfo.job);
		fprintf(log, "MapName:%s\n", this->m_characterInfo.mapName);
		fprintf(log, "hp:%d\n", this->m_characterInfo.hp);
		fprintf(log, "IsPet:%d\n", ( this->GetType() == NPC_PET_TYPE ));
		fprintf(log, "m_npcType:%d\n", this->m_npcType);
		fprintf(log, "*------------------------------------------------------------*\n");
		fclose(log);
	}
}


hook_method<void (CNPC::*)(int type)> CNPC::_OnEmotion(SERVER, "CNPC::OnEmotion");
void CNPC::OnEmotion(int type)
{
	return (this->*_OnEmotion)(type);

	//TODO
}


hook_method<void (CNPC::*)(unsigned long sprite)> CNPC::_ChangeSprite(SERVER, "CNPC::ChangeSprite");
void CNPC::ChangeSprite(unsigned long sprite)
{
	return (this->*_ChangeSprite)(sprite);

	//TODO
}


hook_method<int (CNPC::*)(int GuildID)> CNPC::_IsSameGuild(SERVER, "CNPC::IsSameGuild");
int CNPC::IsSameGuild(int GuildID)
{
	return (this->*_IsSameGuild)(GuildID);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_Revival(SERVER, "CNPC::Revival");
void CNPC::Revival(void)
{
	return (this->*_Revival)();

	if( m_currentState == DEAD_ST )
		m_npcStateUpdater.CNPCStateUpdater::OnRevival(IDLE_ST);
}


hook_method<void (CNPC::*)(void)> CNPC::_CancelNPCSkill(SERVER, "CNPC::CancelNPCSkill");
void CNPC::CancelNPCSkill(void)
{
	return (this->*_CancelNPCSkill)();

	m_npcSkill.m_fsmReleaseTime = 0;
	m_isFSMDependent = 1;
	m_npcSkill.m_isSkillUsing = 0;
	m_npcSkill.m_isNoDispel = 0;
}


hook_method<void (CNPC::*)(bool value, unsigned long id)> CNPC::_SetRangedAttacked(SERVER, "CNPC::SetRangedAttacked");
void CNPC::SetRangedAttacked(bool value, unsigned long id)
{
	return (this->*_SetRangedAttacked)(value, id);

	m_isRangeAttacked = value;
	m_npcSkill.m_rangeAttackEnemyID = id;
}


hook_method<void (CNPC::*)(bool value, unsigned long id)> CNPC::_SetRudeAttacked(SERVER, "CNPC::SetRudeAttacked");
void CNPC::SetRudeAttacked(bool value, unsigned long id)
{
	return (this->*_SetRudeAttacked)(value, id);

	m_isRudeAttacked = value;
	m_npcSkill.m_rudeAttackEnemyID = id;
}


//hook_method<void (CNPC::*)(unsigned long skillID)> CNPC::_SetAttackedSkillID(SERVER, "CNPC::SetAttackedSkillID");
void CNPC::SetAttackedSkillID(unsigned long skillID)
{
//	return (this->*_SetAttackedSkillID)(skillID);

	if(m_attackedSkillID == 0)
		m_attackedSkillID = skillID;
}


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnTeleportCharacter(SERVER, "CNPC::OnTeleportCharacter");
void CNPC::OnTeleportCharacter(int par1, int par2, int par3)
{
	return (this->*_OnTeleportCharacter)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, int tarAID, int SKInfo)> CNPC::_OnGroundSkill(SERVER, "CNPC::OnGroundSkill");
void CNPC::OnGroundSkill(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OnGroundSkill)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<void (CNPC::*)(int tarAID, int SKInfo, int par1)> CNPC::_OnTouchedSkillObject(SERVER, "CNPC::OnTouchedSkillObject");
void CNPC::OnTouchedSkillObject(int tarAID, int SKInfo, int par1)
{
	return (this->*_OnTouchedSkillObject)(tarAID, SKInfo, par1);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, int tarAID, int SKInfo)> CNPC::_OperationSkillToCharacter(SERVER, "CNPC::OperationSkillToCharacter");
void CNPC::OperationSkillToCharacter(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OperationSkillToCharacter)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, int tarAID, int SKInfo)> CNPC::_SPAttackSkillToCharacter(SERVER, "CNPC::SPAttackSkillToCharacter");
void CNPC::SPAttackSkillToCharacter(int SKID, int tarAID, int SKInfo)
{
	return (this->*_SPAttackSkillToCharacter)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, int tarAID, int SKInfo)> CNPC::_OperationSkillToSelf(SERVER, "CNPC::OperationSkillToSelf");
void CNPC::OperationSkillToSelf(int SKID, int tarAID, int SKInfo)
{
	return (this->*_OperationSkillToSelf)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<void (CNPC::*)(int plusATTPower, PosInfo dest, int type, MSG_TYPE1_TWODWORD* msgData, int range, int count)> CNPC::_SplashAttack3(SERVER, "CNPC::SplashAttack3");
void CNPC::SplashAttack3(int plusATTPower, PosInfo dest, int type, MSG_TYPE1_TWODWORD* msgData, int range, int count)
{
	return (this->*_SplashAttack3)(plusATTPower, dest, type, msgData, range, count);

	//TODO
}


hook_method<void (CNPC::*)(SKILLATTACK_MSG* msg, short xPos, short yPos, int range, unsigned long exceptID)> CNPC::_SplashNapalmBeat(SERVER, "CNPC::SplashNapalmBeat");
void CNPC::SplashNapalmBeat(SKILLATTACK_MSG* msg, short xPos, short yPos, int range, unsigned long exceptID)
{
	return (this->*_SplashNapalmBeat)(msg, xPos, yPos, range, exceptID);

	//TODO
}


hook_method<void (CNPC::*)(int xPos, int yPos, int destDir, int distance, PosInfo& result)> CNPC::_GetPushedPosition2(SERVER, "CNPC::GetPushedPosition2");
void CNPC::GetPushedPosition2(int xPos, int yPos, int destDir, int distance, PosInfo& result)
{
	return (this->*_GetPushedPosition2)(xPos, yPos, destDir, distance, result);

	//TODO
}


/* hook_method<void (CNPC::*)(PosInfo src, PosInfo dest, int halfWidth, int height, PosInfo* result)> CNPC::_GetSplashCells(SERVER, "CNPC::GetSplashCells");
void CNPC::GetSplashCells(PosInfo src, PosInfo dest, int halfWidth, int height, PosInfo* result)
{
	return (this->*_GetSplashCells)(src, dest, halfWidth, height, result);

	//TODO
} */


hook_method<void (CNPC::*)(PosInfo src, PosInfo dest, int height, PosInfo* result)> CNPC::_GetSplashCells2(SERVER, "CNPC::GetSplashCells2");
void CNPC::GetSplashCells2(PosInfo src, PosInfo dest, int height, PosInfo* result)
{
	return (this->*_GetSplashCells2)(src, dest, height, result);

	//TODO
}


hook_method<int (CNPC::*)(short srcX, short srcY, int desX, int desY, int* result)> CNPC::_GetFireWallNeighborCells(SERVER, "CNPC::GetFireWallNeighborCells");
int CNPC::GetFireWallNeighborCells(short srcX, short srcY, int desX, int desY, int* result)
{
	return (this->*_GetFireWallNeighborCells)(srcX, srcY, desX, desY, result);

	//TODO
}


hook_method<void (CNPC::*)(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, short level, bool result)> CNPC::_NotifyUseSkill(SERVER, "CNPC::NotifyUseSkill");
void CNPC::NotifyUseSkill(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, short level, bool result)
{
	return (this->*_NotifyUseSkill)(SKID, targetAID, srcAID, level, result);

	//TODO
}


hook_method<void (CNPC::*)(unsigned short SKID, short level, short xPos, short yPos, unsigned long startTime)> CNPC::_NotifyGroundSkillUsing(SERVER, "CNPC::NotifyGroundSkillUsing");
void CNPC::NotifyGroundSkillUsing(unsigned short SKID, short level, short xPos, short yPos, unsigned long startTime)
{
	return (this->*_NotifyGroundSkillUsing)(SKID, level, xPos, yPos, startTime);

	//TODO
}


hook_method<void (CNPC::*)(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY)> CNPC::_DetectHidingCharacter(SERVER, "CNPC::DetectHidingCharacter");
void CNPC::DetectHidingCharacter(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY)
{
	return (this->*_DetectHidingCharacter)(range, msg, plusAttPower, deltaX, deltaY);

	//TODO
}


hook_method<void (CNPC::*)(SummonMobList* summonMobList, unsigned short skillID, int slaveFlag, int posFlag)> CNPC::_SummonMonster(SERVER, "CNPC::SummonMonster");
void CNPC::SummonMonster(SummonMobList* summonMobList, unsigned short skillID, int slaveFlag, int posFlag)
{
	return (this->*_SummonMonster)(summonMobList, skillID, slaveFlag, posFlag);

	//TODO
}


hook_method<void (CNPC::*)(SummonMobList* summonMobList)> CNPC::_Metamorphosis(SERVER, "CNPC::Metamorphosis");
void CNPC::Metamorphosis(SummonMobList* summonMobList)
{
	return (this->*_Metamorphosis)(summonMobList);

	//TODO
}


hook_method<CCharacter* (CNPC::*)(unsigned long spriteType, int slaveFlag, int posFlag)> CNPC::_AddMonster(SERVER, "CNPC::AddMonster");
CCharacter* CNPC::AddMonster(unsigned long spriteType, int slaveFlag, int posFlag)
{
	return (this->*_AddMonster)(spriteType, slaveFlag, posFlag);

	//TODO
}


hook_method<void (CNPC::*)(int& damage, int isRangeAttack, int attackType, CCharacter* other, unsigned short SKID)> CNPC::_ModifyDamage(SERVER, "CNPC::ModifyDamage");
void CNPC::ModifyDamage(int& damage, int isRangeAttack, int attackType, CCharacter* other, unsigned short SKID)
{
	return (this->*_ModifyDamage)(damage, isRangeAttack, attackType, other, SKID);

	//TODO
}


hook_method<void (CNPC::*)(CCharacter* other, int& damage, int isRNGATK, int type, int property, int SKID)> CNPC::_ModifyDamage_ATKED(SERVER, "CNPC::ModifyDamage_ATKED");
void CNPC::ModifyDamage_ATKED(CCharacter* other, int& damage, int isRNGATK, int type, int property, int SKID)
{
	return (this->*_ModifyDamage_ATKED)(other, damage, isRNGATK, type, property, SKID);

	//TODO
}


hook_method<void (CNPC::*)(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, int damage)> CNPC::_NotifyMissSkill(SERVER, "CNPC::NotifyMissSkill");
void CNPC::NotifyMissSkill(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, int damage)
{
	return (this->*_NotifyMissSkill)(SKID, targetAID, srcAID, damage);

	//TODO
}


/* hook_method<void (CNPC::*)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, MSG_TYPE1_TWODWORD* msgData, int val2, int count)> CNPC::_NeighborPCAttack(SERVER, "CNPC::NeighborPCAttack");
void CNPC::NeighborPCAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, MSG_TYPE1_TWODWORD* msgData, int val2, int count)
{
	return (this->*_NeighborPCAttack)(val1, xPos, yPos, type, range, rangeIn, exceptAID, msgData, val2, count);

	//TODO
} */


hook_method<void (CNPC::*)(void)> CNPC::_Enable(SERVER, "CNPC::Enable");
void CNPC::Enable(void)
{
	return (this->*_Enable)();

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_Disable(SERVER, "CNPC::Disable");
void CNPC::Disable(void)
{
	return (this->*_Disable)();

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_IsEnable(SERVER, "CNPC::IsEnable");
int CNPC::IsEnable(void)
{
	return (this->*_IsEnable)();

	//TODO
}


hook_method<void (CNPC::*)(int defense, int isInit)> CNPC::_OnChangeDefense(SERVER, "CNPC::OnChangeDefense");
void CNPC::OnChangeDefense(int defense, int isInit)
{
	return (this->*_OnChangeDefense)(defense, isInit);

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_SetParameter(SERVER, "CNPC::SetParameter");
int CNPC::SetParameter(void)
{
	return (this->*_SetParameter)();

	//TODO
}


//hook_method<void (CNPC::*)(void)> CNPC::_InitCache(SERVER, "CNPC::InitCache");
void CNPC::InitCache(void)
{
//	return (this->*_InitCache)();

	m_neighborCache.CNeighborCache::Init();
	m_pathInfo.m_moveInfo.state = 3;
}


hook_method<void (CNPC::*)(void)> CNPC::_OnChangeGuildID(SERVER, "CNPC::OnChangeGuildID");
void CNPC::OnChangeGuildID(void)
{
	return (this->*_OnChangeGuildID)();

	//TODO
}


hook_method<void (CNPC::*)(int SKID, unsigned long time, int val)> CNPC::_SetATKPercentInfo(SERVER, "CNPC::SetATKPercentInfo");
void CNPC::SetATKPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetATKPercentInfo)(SKID, time, val);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, unsigned long time, int val)> CNPC::_SetDEFPercentInfo(SERVER, "CNPC::SetDEFPercentInfo");
void CNPC::SetDEFPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetDEFPercentInfo)(SKID, time, val);

	//TODO
}


hook_method<void (CNPC::*)(int SKID)> CNPC::_ResetATKPercentInfo(SERVER, "CNPC::ResetATKPercentInfo");
void CNPC::ResetATKPercentInfo(int SKID)
{
	return (this->*_ResetATKPercentInfo)(SKID);

	//TODO
}


hook_method<void (CNPC::*)(int SKID)> CNPC::_ResetDEFPercentInfo(SERVER, "CNPC::ResetDEFPercentInfo");
void CNPC::ResetDEFPercentInfo(int SKID)
{
	return (this->*_ResetDEFPercentInfo)(SKID);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, unsigned long time, int val)> CNPC::_SetMATKPercentInfo(SERVER, "CNPC::SetMATKPercentInfo");
void CNPC::SetMATKPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetMATKPercentInfo)(SKID, time, val);

	//TODO
}


hook_method<void (CNPC::*)(int SKID, unsigned long time, int val)> CNPC::_SetMDEFPercentInfo(SERVER, "CNPC::SetMDEFPercentInfo");
void CNPC::SetMDEFPercentInfo(int SKID, unsigned long time, int val)
{
	return (this->*_SetMDEFPercentInfo)(SKID, time, val);

	//TODO
}


/* hook_method<void (CNPC::*)(int SKID)> CNPC::_ResetMATKPercentInfo(SERVER, "CNPC::ResetMATKPercentInfo");
void CNPC::ResetMATKPercentInfo(int SKID)
{
	return (this->*_ResetMATKPercentInfo)(SKID);

	//TODO
} */


hook_method<void (CNPC::*)(int SKID)> CNPC::_ResetMDEFPercentInfo(SERVER, "CNPC::ResetMDEFPercentInfo");
void CNPC::ResetMDEFPercentInfo(int SKID)
{
	return (this->*_ResetMDEFPercentInfo)(SKID);

	//TODO
}


//hook_method<unsigned short (CNPC::*)(void)> CNPC::_GetSpellCasting(SERVER, "CNPC::GetSpellCasting");
unsigned short CNPC::GetSpellCasting(void)
{
//	return (this->*_GetSpellCasting)();

	return m_npcSkill.m_spellCastingSKID;
}


hook_method<int (CNPC::*)(const char* mobName)> CNPC::_OnWhereMyMob_XPos(SERVER, "CNPC::OnWhereMyMob_XPos");
int CNPC::OnWhereMyMob_XPos(const char* mobName)
{
	return (this->*_OnWhereMyMob_XPos)(mobName);

	//TODO
}


hook_method<int (CNPC::*)(const char* mobName)> CNPC::_OnWhereMyMob_YPos(SERVER, "CNPC::OnWhereMyMob_YPos");
int CNPC::OnWhereMyMob_YPos(const char* mobName)
{
	return (this->*_OnWhereMyMob_YPos)(mobName);

	//TODO
}


hook_method<unsigned long (CNPC::*)(const char* mobName)> CNPC::_FindMyMobAID(SERVER, "CNPC::FindMyMobAID");
unsigned long CNPC::FindMyMobAID(const char* mobName)
{
	return (this->*_FindMyMobAID)(mobName);

	//TODO
}


hook_method<void (CNPC::*)(const unsigned short in_SKID)> CNPC::_SetSpellCasting(SERVER, "CNPC::SetSpellCasting");
void CNPC::SetSpellCasting(const unsigned short in_SKID)
{
	return (this->*_SetSpellCasting)(in_SKID);

	//TODO
}


hook_method<int (CNPC::*)(const int in_SKID)> CNPC::_GetSKLevel(SERVER, "CNPC::GetSKLevel");
int CNPC::GetSKLevel(const int in_SKID)
{
	return (this->*_GetSKLevel)(in_SKID);

	//TODO
}


hook_method<bool (CNPC::*)(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData)> CNPC::_OpSKToChar_SKID_ML_DEVOTION(SERVER, "CNPC::OpSKToChar_SKID_ML_DEVOTION");
bool CNPC::OpSKToChar_SKID_ML_DEVOTION(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData)
{
	return (this->*_OpSKToChar_SKID_ML_DEVOTION)(in_TargetCH, in_pData);

	//TODO
}


hook_method<void (CNPC::*)(const int in_SKlevel)> CNPC::_OpSKToSelf_SKID_ML_DEFENDER(SERVER, "CNPC::OpSKToSelf_SKID_ML_DEFENDER");
void CNPC::OpSKToSelf_SKID_ML_DEFENDER(const int in_SKlevel)
{
	return (this->*_OpSKToSelf_SKID_ML_DEFENDER)(in_SKlevel);

	//TODO
}


hook_method<void (CNPC::*)(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value)> CNPC::_OpSKToSelf_SKID_MER_MAGNIFICAT(SERVER, "CNPC::OpSKToSelf_SKID_MER_MAGNIFICAT");
void CNPC::OpSKToSelf_SKID_MER_MAGNIFICAT(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value)
{
	return (this->*_OpSKToSelf_SKID_MER_MAGNIFICAT)(in_SKLevel, in_EFST, in_EFST_time, in_EFST_value);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_OpSKToSelf_SKID_MER_AUTOBERSERK(SERVER, "CNPC::OpSKToSelf_SKID_MER_AUTOBERSERK");
void CNPC::OpSKToSelf_SKID_MER_AUTOBERSERK(void)
{
	return (this->*_OpSKToSelf_SKID_MER_AUTOBERSERK)();

	//TODO
}


hook_method<void (CNPC::*)(unsigned short type, int count)> CNPC::_NotifyParameter(SERVER, "CNPC::NotifyParameter");
void CNPC::NotifyParameter(unsigned short type, int count)
{
	return (this->*_NotifyParameter)(type, count);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_ResetEffective_after_EFST_DEFENDER(SERVER, "CNPC::ResetEffective_after_EFST_DEFENDER");
void CNPC::ResetEffective_after_EFST_DEFENDER(void)
{
	return (this->*_ResetEffective_after_EFST_DEFENDER)();

	//TODO
}


hook_method<void (CNPC::*)(int SKID, MSG_TYPE1_TWODWORD* position, int skLevel, int spCost)> CNPC::_OnUseGroundSkill(SERVER, "CNPC::OnUseGroundSkill");
void CNPC::OnUseGroundSkill(int SKID, MSG_TYPE1_TWODWORD* position, int skLevel, int spCost)
{
	return (this->*_OnUseGroundSkill)(SKID, position, skLevel, spCost);

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetEmblemVersion(SERVER, "CNPC::GetEmblemVersion");
int CNPC::GetEmblemVersion(void)
{
	return (this->*_GetEmblemVersion)();

	//TODO
}


//hook_method<unsigned long (CNPC::*)(int range)> CNPC::_GetNeighborPcNumber(SERVER, "CNPC::GetNeighborPcNumber");
unsigned long CNPC::GetNeighborPcNumber(int range)
{
//	return (this->*_GetNeighborPcNumber)(range);

	return m_npcUpdater.CNPCUpdater::GetNeighborPcNumber(range);
}


hook_method<void (CNPC::*)(unsigned long tick)> CNPC::_CheckSpecialState(SERVER, "CNPC::CheckSpecialState");
void CNPC::CheckSpecialState(unsigned long tick)
{
	return (this->*_CheckSpecialState)(tick);

	//TODO
}


hook_method<void (CNPC::*)(unsigned long tick)> CNPC::_CheckCondition(SERVER, "CNPC::CheckCondition");
void CNPC::CheckCondition(unsigned long tick)
{
	return (this->*_CheckCondition)(tick);

	//TODO
}


hook_method<CItem* (CNPC::*)(unsigned short itmID, int count, int x, int y)> CNPC::_CreateItemOnMap(SERVER, "CNPC::CreateItemOnMap");
CItem* CNPC::CreateItemOnMap(unsigned short itmID, int count, int x, int y)
{
	return (this->*_CreateItemOnMap)(itmID, count, x, y);

	//TODO
}


hook_method<void (CNPC::*)(unsigned long AID)> CNPC::_AddSpecialZoneList(SERVER, "CNPC::AddSpecialZoneList");
void CNPC::AddSpecialZoneList(unsigned long AID)
{
	return (this->*_AddSpecialZoneList)(AID);

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_DelSpecialZoneList(SERVER, "CNPC::DelSpecialZoneList");
void CNPC::DelSpecialZoneList(void)
{
	return (this->*_DelSpecialZoneList)();

	//TODO
}


hook_method<bool (CNPC::*)(unsigned short type, int& amount)> CNPC::_ApplyStatusAmount(SERVER, "CNPC::ApplyStatusAmount");
bool CNPC::ApplyStatusAmount(unsigned short type, int& amount)
{
	return (this->*_ApplyStatusAmount)(type, amount);

	//TODO
}

//hook_method<short (CNPC::*)(void)> CNPC::_GetBodyState(SERVER, "CNPC::GetBodyState");
short CNPC::GetBodyState(void)
{
//	return (this->*_GetBodyState)();

	return static_cast<short>(m_characterPInfo.bodyState);
}


hook_method<void (CNPC::*)(const char* buf, unsigned long color)> CNPC::_Chat(SERVER, "CNPC::Chat");
void CNPC::Chat(const char* buf, unsigned long color) // line 5349-5366
{
	return (this->*_Chat)(buf, color);

	if( buf == NULL )
		return; // no text

	char text[1024] = {};
	sprintf(text, "%s : %s", m_characterInfo.accountName, buf);

	char packet[1024] = {};
	PACKET_ZC_NPC_CHAT* outpacket = reinterpret_cast<PACKET_ZC_NPC_CHAT*>(&packet);
	outpacket->PacketType = HEADER_ZC_NPC_CHAT;
	outpacket->packetLength = strlen(text) + 1 + sizeof(PACKET_ZC_NPC_CHAT);
	outpacket->accountID = this->GetAccountID();
	outpacket->color = color;
	memcpy(outpacket->Text, text, strlen(text) + 1);

	this->CCharacter::MultiCast((char*)outpacket, outpacket->packetLength);
}


hook_method<short (CNPC::*)(void)> CNPC::_GetAttSucPercent(SERVER, "CNPC::GetAttSucPercent");
short CNPC::GetAttSucPercent(void)
{
	return (this->*_GetAttSucPercent)();

	//TODO
}


hook_method<int (CNPC::*)(CCharacter* target)> CNPC::_GetModifiedTargetStatusDEF(SERVER, "CNPC::GetModifiedTargetStatusDEF");
int CNPC::GetModifiedTargetStatusDEF(CCharacter* target)
{
	return (this->*_GetModifiedTargetStatusDEF)(target);

	//TODO
}


hook_method<void (CNPC::*)(int& def, CCharacter* in_cpAtkerCH)> CNPC::_ApplyExtraDEF(SERVER, "CNPC::ApplyExtraDEF");
void CNPC::ApplyExtraDEF(int& def, CCharacter* in_cpAtkerCH)
{
	return (this->*_ApplyExtraDEF)(def, in_cpAtkerCH);

	//TODO
}


hook_method<void (CNPC::*)(int& mdef)> CNPC::_ApplyExtraMDEF(SERVER, "CNPC::ApplyExtraMDEF");
void CNPC::ApplyExtraMDEF(int& mdef)
{
	return (this->*_ApplyExtraMDEF)(mdef);

	//TODO
}


//hook_method<int (CNPC::*)(CCharacter* atker, int damage, unsigned short SKID, int property)> CNPC::_GetMinusStdPropertyDamage(SERVER, "CNPC::GetMinusStdPropertyDamage");
int CNPC::GetMinusStdPropertyDamage(CCharacter* atker, int damage, unsigned short SKID, int property)
{
//	return (this->*_GetMinusStdPropertyDamage)(atker, damage, SKID, property);

	return 0;
}


hook_method<int (CNPC::*)(void)> CNPC::_GetRoomSize(SERVER, "CNPC::GetRoomSize");
int CNPC::GetRoomSize(void)
{
	return (this->*_GetRoomSize)();

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_InitCore(SERVER, "CNPC::InitCore");
void CNPC::InitCore(void)
{
	return (this->*_InitCore)();

	//TODO
}


hook_method<void (CNPC::*)(unsigned long AID)> CNPC::_AddMYMob(SERVER, "CNPC::AddMYMob");
void CNPC::AddMYMob(unsigned long AID)
{
	return (this->*_AddMYMob)(AID);

	//TODO
}


hook_method<void (CNPC::*)(unsigned long AID, unsigned long killer)> CNPC::_OnMyMonsterDead(SERVER, "CNPC::OnMyMonsterDead");
void CNPC::OnMyMonsterDead(unsigned long AID, unsigned long killer)
{
	return (this->*_OnMyMonsterDead)(AID, killer);

	//TODO
}


hook_method<int (CNPC::*)(PACKET_CZ_REQUEST_MOVE* pReq, unsigned long startTime)> CNPC::_StartPath(SERVER, "CNPC::StartPath");
int CNPC::StartPath(PACKET_CZ_REQUEST_MOVE* pReq, unsigned long startTime)
{
	return (this->*_StartPath)(pReq, startTime);

	//TODO
}


hook_method<int (CNPC::*)(PACKET_CZ_REQUEST_MOVE* p)> CNPC::_OnMove(SERVER, "CNPC::OnMove");
int CNPC::OnMove(PACKET_CZ_REQUEST_MOVE* p)
{
	return (this->*_OnMove)(p);

	if( !this->CNPC::IsMovable() )
		return 0;

	return this->CNPC::StartPath(p, timeGetTime());
}


hook_method<void (CNPC::*)(void)> CNPC::_MultiCastStateInfo(SERVER, "CNPC::MultiCastStateInfo");
void CNPC::MultiCastStateInfo(void)
{
	return (this->*_MultiCastStateInfo)();

	//TODO
}


hook_method<void (CNPC::*)(void)> CNPC::_NotifyInfoToSection(SERVER, "CNPC::NotifyInfoToSection");
void CNPC::NotifyInfoToSection(void)
{
	return (this->*_NotifyInfoToSection)();

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetCurrentState(SERVER, "CNPC::GetCurrentState");
short CNPC::GetCurrentState(void)
{
	return (this->*_GetCurrentState)();

	//TODO
}


//hook_method<int (CNPC::*)(void)> CNPC::_GetMYMobSize(SERVER, "CNPC::GetMYMobSize");
int CNPC::GetMYMobSize(void)
{
//	return (this->*_GetMYMobSize)();

	return m_myMobList.size();
}


hook_method<int (CNPC::*)(unsigned long spriteType)> CNPC::_SpawnMyMob(SERVER, "CNPC::SpawnMyMob");
int CNPC::SpawnMyMob(unsigned long spriteType)
{
	return (this->*_SpawnMyMob)(spriteType);

	MONSPAWN_SETINFO* spawnInfo = g_monParameter->CMonParameterMgr::GetMonSpawnInfo(spriteType);
	if( spawnInfo == NULL )
		return 0;

	const char* monName = g_monParameter->CMonParameterMgr::GetMonsterName(spawnInfo->spriteType);
	if( monName == NULL )
		return 0;

	PACKET_NZ_NEWNPC packet;
	packet.NAID = 0;
	packet.xSize = 0;
	packet.ySize = 0;
	packet.force = true;
	packet.direction = 0;
	packet.RegenMinTime = 1;
	packet.RegenMaxTime = 1;
	packet.RegenType = 0;

	for( int i = 0; i < spawnInfo->count; ++i )
	{
		packet.xPos = m_pathInfo.m_moveInfo.xPos;
		packet.yPos = m_pathInfo.m_moveInfo.yPos;
		packet.spriteType = static_cast<short>(spawnInfo->spriteType);
		packet.npcType = static_cast<unsigned char>(spawnInfo->npcType);
		memcpy(packet.mapName, m_characterInfo.mapName, 16);
		memcpy(packet.NPCName, monName, 24);

		CNPC* npc = g_characterMgr->CCharacterMgr::AddNPC(&packet, this->GetAccountID());
		if( npc != NULL && spawnInfo->npcType == 29 )
			npc->CNPC::SetSpeed(this->GetSpeed());
	}

	return 1;
}


hook_method<void (CNPC::*)(void)> CNPC::_OnResetMyMob(SERVER, "CNPC::OnResetMyMob");
void CNPC::OnResetMyMob(void)
{
	return (this->*_OnResetMyMob)();

	//TODO
}


hook_method<void (CNPC::*)(int SKID, int tarAID, int SKInfo)> CNPC::_UseSkillToCharacter(SERVER, "CNPC::UseSkillToCharacter");
void CNPC::UseSkillToCharacter(int SKID, int tarAID, int SKInfo)
{
	return (this->*_UseSkillToCharacter)(SKID, tarAID, SKInfo);

	//TODO
}


hook_method<int (CNPC::*)(CCharacter* other, int plusATTPowerPercent, int plusATTSuccessPercent, unsigned short SKID)> CNPC::_GetMagicAttackFinalDamage(SERVER, "CNPC::GetMagicAttackFinalDamage");
int CNPC::GetMagicAttackFinalDamage(CCharacter* other, int plusATTPowerPercent, int plusATTSuccessPercent, unsigned short SKID)
{
	return (this->*_GetMagicAttackFinalDamage)(other, plusATTPowerPercent, plusATTSuccessPercent, SKID);

	//TODO
}


hook_method<int (CNPC::*)(void)> CNPC::_GetMagicAttPower(SERVER, "CNPC::GetMagicAttPower");
int CNPC::GetMagicAttPower(void)
{
	return (this->*_GetMagicAttPower)();

	//TODO
}


/* hook_method<void (CNPC::*)(int plusATTPowerPercent, short xPos, short yPos, short type, int range, unsigned long exceptAID)> CNPC::_SplashDamageAttack(SERVER, "CNPC::SplashDamageAttack");
void CNPC::SplashDamageAttack(int plusATTPowerPercent, short xPos, short yPos, short type, int range, unsigned long exceptAID)
{
	return (this->*_SplashDamageAttack)(plusATTPowerPercent, xPos, yPos, type, range, exceptAID);

	//TODO
} */


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnMoveStop(SERVER, "CNPC::OnMoveStop");
void CNPC::OnMoveStop(int par1, int par2, int par3)
{
	return (this->*_OnMoveStop)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnChangeAGI(SERVER, "CNPC::OnChangeAGI");
void CNPC::OnChangeAGI(int par1, int par2, int par3)
{
	return (this->*_OnChangeAGI)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnChangeDEX(SERVER, "CNPC::OnChangeDEX");
void CNPC::OnChangeDEX(int par1, int par2, int par3)
{
	return (this->*_OnChangeDEX)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnChangeINT(SERVER, "CNPC::OnChangeINT");
void CNPC::OnChangeINT(int par1, int par2, int par3)
{
	return (this->*_OnChangeINT)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnChangeLUK(SERVER, "CNPC::OnChangeLUK");
void CNPC::OnChangeLUK(int par1, int par2, int par3)
{
	return (this->*_OnChangeLUK)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnChangeSTR(SERVER, "CNPC::OnChangeSTR");
void CNPC::OnChangeSTR(int par1, int par2, int par3)
{
	return (this->*_OnChangeSTR)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int par1, int par2, int par3)> CNPC::_OnChangeVIT(SERVER, "CNPC::OnChangeVIT");
void CNPC::OnChangeVIT(int par1, int par2, int par3)
{
	return (this->*_OnChangeVIT)(par1, par2, par3);

	//TODO
}


hook_method<void (CNPC::*)(int par1)> CNPC::_InitThePCCacheInfo(SERVER, "CNPC::InitThePCCacheInfo");
void CNPC::InitThePCCacheInfo(int par1)
{
	return (this->*_InitThePCCacheInfo)(par1);

	//TODO
}


hook_method<short (CNPC::*)(void)> CNPC::_GetAvoidPercent_Client(SERVER, "CNPC::GetAvoidPercent_Client");
short CNPC::GetAvoidPercent_Client(void)
{
	return (this->*_GetAvoidPercent_Client)();

	//TODO
}


hook_method<unsigned long (CNPC::*)(void)> CNPC::_GetRoomID(SERVER, "CNPC::GetRoomID");
unsigned long CNPC::GetRoomID(void)
{
	return (this->*_GetRoomID)();

	return m_characterInfo.roomID;
}


hook_method<void (CNPC::*)(unsigned long roomID)> CNPC::_SetRoomID(SERVER, "CNPC::SetRoomID");
void CNPC::SetRoomID(unsigned long roomID)
{
	return (this->*_SetRoomID)(roomID);

	m_characterInfo.roomID = roomID;
}
