#include "PC.h"
#include "PCFormula_PhysicsSupport.h"


CPCFormula_PhysicsSupport::CPCFormula_PhysicsSupport(CPC* pc)
: CPCFormula_CommonSupport(pc)
{
}


void CPCFormula_PhysicsSupport::InsertActionAttackCommandQueue(CCharacter* in_cpTarget, int in_Damage, short in_LeftDamage, int in_atkerATKMotionTime, int in_ATKCount, BOOL in_IsRangeAttack, int in_ATKProperty) // 1489-1538
{
	COMMAND_QUEUE command;
	command.commandID = ATTACKED_IN;

	if( in_ATKCount > 1 )
	{
		command.commandID = MULTIPLE_ATTACKED_IN;
	}
	else
	if( in_cpTarget->GetType() == NPC_MOB_TYPE )
	{
		CNpcMob* cpNpcMob = static_cast<CNpcMob*>(in_cpTarget);
		if( cpNpcMob->CNPC::GetCurrentFSMState() == BERSERK_ST
		 && cpNpcMob->CNPC::GetEnemyAID() != m_pc->GetAccountID()
		 && m_pc->IsMyArea(cpNpcMob, cpNpcMob->CNPC::GetAttackRange() + 1) )
		{
			command.commandID = MILLI_ATTACKED_IN;
		}
	}

	command.executionTime = timeGetTime() + in_atkerATKMotionTime + 10;
	command.sender = m_pc->GetAccountID();
	command.par1 = in_Damage + in_LeftDamage;
	command.par2 = in_ATKCount;
	command.par3 = 0; //TODO: 'not a skill attack' flag
	command.par4 = !in_IsRangeAttack;
	command.par6 = in_ATKProperty;
	in_cpTarget->InsertCommand(&command);

	if( m_pc->m_characterInfo.splashRange != 0 )
	{
		int targetXPos, targetYPos;
		in_cpTarget->GetParameterValue(VAR_CURXPOS, targetXPos);
		in_cpTarget->GetParameterValue(VAR_CURYPOS, targetYPos);

		command.commandID = SPLASH_ATTACK_IN;
		command.executionTime = timeGetTime();
		command.sender = m_pc->GetAccountID();
		command.par1 = 0; // SKID
		command.par2 = targetXPos;
		command.par3 = targetYPos;
		command.par4 = in_cpTarget->GetAccountID();
		command.par5 = 1; // skLevel
		m_pc->InsertCommand(&command);
	}
}
