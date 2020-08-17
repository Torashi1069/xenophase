#include "Actor.h"


CActor::CActor(void) // line 32
{
}


CActor::~CActor(void) // line 36
{
}


hook_method<void (CActor::*)(void)> CActor::_Init(SERVER, "CActor::Init");
void CActor::Init(void) // line 61
{
	return (this->*_Init)();

	this->CCharacter::Init();

}


hook_method<short (CActor::*)(void)> CActor::_GetHealthState(SERVER, "CActor::GetHealthState");
short CActor::GetHealthState(void) // line ??
{
	return (this->*_GetHealthState)();

	return 0;
}


/* hook_method<unsigned long (CActor::*)(const int in_HealthState)> CActor::_GetHealthStateRemainMS(SERVER, "CActor::GetHealthStateRemainMS");
unsigned long CActor::GetHealthStateRemainMS(const int in_HealthState)
{
	return (this->*_GetHealthStateRemainMS)(in_HealthState);

	//TODO
} */


/* hook_method<unsigned long (CActor::*)(const int in_BodyState)> CActor::_GetBodyStateRemainMS(SERVER, "CActor::GetBodyStateRemainMS");
unsigned long CActor::GetBodyStateRemainMS(const int in_BodyState)
{
	return (this->*_GetBodyStateRemainMS)(in_BodyState);

	//TODO
} */


hook_method<int (CActor::*)(unsigned char* out_pData, const int in_MaxBytes)> CActor::_GetStateDBFmt(SERVER, "CActor::GetStateDBFmt");
int CActor::GetStateDBFmt(unsigned char* out_pData, const int in_MaxBytes) // line 82
{
	return (this->*_GetStateDBFmt)(out_pData, in_MaxBytes);

	//TODO
}


hook_method<void (CActor::*)(const unsigned char* in_pData, const int in_Length)> CActor::_SetStateDBFmt(SERVER, "CActor::SetStateDBFmt");
void CActor::SetStateDBFmt(const unsigned char* in_pData, const int in_Length) // line 137
{
	return (this->*_SetStateDBFmt)(in_pData, in_Length);

	//TODO
}


/* hook_method<int (CActor::*)(CCharacter* other, int property, int damage)> CActor::_GetPlusPropertyDamage(SERVER, "CActor::GetPlusPropertyDamage");
int CActor::GetPlusPropertyDamage(CCharacter* other, int property, int damage)
{
	return (this->*_GetPlusPropertyDamage)(other, property, damage);

	//TODO
} */


/* hook_method<int (CActor::*)(CCharacter* ch, int attackProperty, int in_damage)> CActor::_GetModifyAttackPowerByEffective_Variation(SERVER, "CActor::GetModifyAttackPowerByEffective_Variation");
int CActor::GetModifyAttackPowerByEffective_Variation(CCharacter* ch, int attackProperty, int in_damage)
{
	return (this->*_GetModifyAttackPowerByEffective_Variation)(ch, attackProperty, in_damage);

	//TODO
} */


hook_method<void (CActor::*)(int xPos, int yPos, int destDir, int distance, PosInfo& result)> CActor::_GetForwardPosition(SERVER, "CActor::GetForwardPosition");
void CActor::GetForwardPosition(int xPos, int yPos, int destDir, int distance, PosInfo& result) // line 1846
{
	return (this->*_GetForwardPosition)(xPos, yPos, destDir, distance, result);

	//TODO
}


hook_method<int (CActor::*)(PosInfo src, PosInfo dest)> CActor::_GetDirection(SERVER, "CActor::GetDirection");
int CActor::GetDirection(PosInfo src, PosInfo dest) // line 1864
{
	return (this->*_GetDirection)(src, dest);

	//TODO
}
