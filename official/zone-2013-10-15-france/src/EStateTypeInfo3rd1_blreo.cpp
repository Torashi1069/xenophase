#include "Character.h"
#include "EStateTypeInfo3rd1_blreo.h"
#include "NPC.h"
#include "PC.h"


bool ESTATE_FROSTMISTY::SetCheckup(CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3)
{
	if( in_cpActor->GetEffective(m_EfstID, 0) )
		return false;

	if( in_cpActor->GetEffective(EFST_INSPIRATION, 0) )
		return false;

	int CHClass = 0;
	in_cpActor->GetParameterValue(VAR_CLASS, CHClass);
	
	if( CHClass == NPC_CLASS_BOSS )
		return false;

	if( in_cpActor->GetEffective(EFST_WARMER, 0) )
		return false;

	return true;
}


hook_func<void (ESTATE_FROSTMISTY::*)(CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3)> ESTATE_FROSTMISTY__SetComplete(EXEPATH(), "ESTATE_FROSTMISTY::SetComplete");
void ESTATE_FROSTMISTY::SetComplete(CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3)
{
	return (this->*ESTATE_FROSTMISTY__SetComplete)(in_cpActor, in_Time, in_Val1, in_Val2, in_Val3);
	//TODO
}


hook_func<void (ESTATE_FROSTMISTY::*)(CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3)> ESTATE_FROSTMISTY__ResetComplete(EXEPATH(), "ESTATE_FROSTMISTY::ResetComplete");
void ESTATE_FROSTMISTY::ResetComplete(CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3)
{
	return (this->*ESTATE_FROSTMISTY__ResetComplete)(in_cpActor, in_Val1, in_Val2, in_Val3);
	//TODO
}


int ESTATE_FROSTMISTY::GetDefaultLifeTM(CCharacter* in_cpTarget)
{
	int dex = 0;
	int vit = 0;
	in_cpTarget->GetParameterValue(VAR_STANDARD_DEX, dex);
	in_cpTarget->GetParameterValue(VAR_STANDARD_VIT, vit);

	int time = 1000 * (30 - (dex + vit) / 20);
	if( time < 0 )
		time = 0;

	return 10000 + time;
}
