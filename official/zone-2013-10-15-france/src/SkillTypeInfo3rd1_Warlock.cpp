#include "CharacterMgr.h"
#include "CharSkill.h"
#include "FSMState.h"
#include "SkillScriptHandler.h"
#include "SkillTypeInfo3rd1_Warlock.h"
#include "SkillTypeInfoMgr.h"
////////////////////////////////////////


BOOL SK_WL_WHITEIMPRISON::IsSpellConditionGratify(CCharacter* in_cpSpellCH, CCharacter* in_cpTargetCH, const int in_Level, int& out_USESKILL_FAIL) // 261-295
{
	if( in_cpTargetCH == NULL )
		return FALSE;

	switch( in_cpTargetCH->GetType() )
	{
	case PC_TYPE:
	{
		if( in_cpSpellCH == in_cpTargetCH )
			return TRUE;

		if( in_cpTargetCH->IsTarget(in_cpSpellCH, TARGET_NORMAL) )
			return TRUE;
	}
	break;
	case NPC_MOB_TYPE:
	{
		int targetClass = 0;
		in_cpTargetCH->GetParameterValue(VAR_CLASS, targetClass);

		if( targetClass != NPC_CLASS_BOSS && in_cpTargetCH->IsTarget(in_cpSpellCH, TARGET_NORMAL) )
			return TRUE;
	}
	break;
	};

	out_USESKILL_FAIL = USESKILL_FAIL_TOTARGET;
	return FALSE;
}


int SK_WL_WHITEIMPRISON::OnMsg(CCharacter* in_cpSender, unsigned short in_SKID, int in_MsgID, int in_par1, int in_par2, int in_par3, MSGpar::CVar in_par4) // ???
{
	switch( in_MsgID )
	{
	case SM_USE_SKILL:
	{
		MSG_TYPE_SKILLDATA skilldata;
		skilldata.SKID = in_SKID;
		skilldata.skLevel = in_par1;
		skilldata.spCost = in_par3;
		skilldata.xPos = 0;
		skilldata.yPos = 0;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_cpSender, CM_THIRDJOB_SKILL_OPERATE_TOCHARACTER, in_SKID, in_par2, (int)&skilldata, 0);
	}
	break;
	default:
	{
		this->CSkillTypeInfo::OnMsg(in_cpSender, in_SKID, in_MsgID, in_par1, in_par2, in_par3, 0); //FIXME: par4 not sent
	}
	break;
	};

	return 0;
}


int SK_WL_WHITEIMPRISON::GetLifeTM_when_targetISplayer_and_exclusionOneself(const int in_Level) const // 321-326
{
	static STRUCT_SK_INTVALUE* LifeTM_when_targetISplayer_and_exclusionOneselfTbl = (STRUCT_SK_INTVALUE*)this->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA2);
	return LifeTM_when_targetISplayer_and_exclusionOneselfTbl->value[in_Level - 1];
}


void SK_WL_WHITEIMPRISON::TimeOutProc_BODYSTATE_IMPRISON(CCharacter* in_cpDefCharacter, CCharacter* in_cpAtkCharacter) // 333-372
{
	int SpellLevel = 400 * in_cpDefCharacter->CCharacter::GetInstantVar(CInstantVar::WL_WHITEIMPRISON_SPELL_LEVEL);
	int SpellActorAID = in_cpDefCharacter->CCharacter::GetInstantVar(CInstantVar::WL_WHITEIMPRISON_SPELL_SPELL_ACTORAID);

	COMMAND_QUEUE command;
	command.commandID = ATTACKED_IN;
	command.executionTime = timeGetTime();
	command.sender = SpellActorAID;
	command.par1 = SpellLevel;
	command.par2 = 1;
	in_cpDefCharacter->InsertCommand(&command);

	SendPacket_ZC_NOTIFY_ACT(in_cpDefCharacter, in_cpDefCharacter->GetAccountID(), in_cpDefCharacter->GetAccountID(), timeGetTime(), 0, 0, SpellLevel, 1, 0, 0);

	in_cpDefCharacter->CCharacter::SetInstantVar(CInstantVar::WL_WHITEIMPRISON_SPELL_LEVEL, 0);
	in_cpDefCharacter->CCharacter::SetInstantVar(CInstantVar::WL_WHITEIMPRISON_SPELL_SPELL_ACTORAID, 0);
}


int SK_WL_WHITEIMPRISON::ModifyDamageATKED(CCharacter* in_cpDefCharacter, CCharacter* in_cpAtkCharacter, int& io_damage, const int in_SKID) // 382-411
{
	int BodyState = 0;
	in_cpDefCharacter->GetParameterValue(VAR_BODYSTATE, BodyState);

	if( BodyState == BODYSTATE_IMPRISON )
	{
		if( in_SKID == SKID_MG_NAPALMBEAT || in_SKID == SKID_MG_SOULSTRIKE || in_SKID == SKID_HW_NAPALMVULCAN || in_SKID == SKID_WL_SOULEXPANSION )
		{
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_cpDefCharacter, CM_TIME_BODYSTATE, 0, 0, 0, 0);
			SK_WL_WHITEIMPRISON::TimeOutProc_BODYSTATE_IMPRISON(in_cpDefCharacter, in_cpAtkCharacter);
		}
		else
		{
			io_damage = 0;
		}
	}

	return io_damage;
}


////////////////////////////////////////
