#include "CITP.hpp"


CITP::CITP(void)
{
}


hook_method<void (CITP::*)(void)> CITP::_Init(SERVER, "CITP::Init");
void CITP::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<unsigned short (CITP::*)(void)> CITP::_GetType(SERVER, "CITP::GetType");
unsigned short CITP::GetType(void)
{
	return (this->*_GetType)();

	return 0;
}


hook_method<void (CITP::*)(short& attackPower)> CITP::_GetAttackValue(SERVER, "CITP::GetAttackValue");
void CITP::GetAttackValue(short& attackPower)
{
	return (this->*_GetAttackValue)(attackPower);

	//TODO
}


hook_method<void (CITP::*)(short& defencePower)> CITP::_GetDefence(SERVER, "CITP::GetDefence");
void CITP::GetDefence(short& defencePower)
{
	return (this->*_GetDefence)(defencePower);

	//TODO
}


hook_method<unsigned short (CITP::*)(short job)> CITP::_GetLocation(SERVER, "CITP::GetLocation");
unsigned short CITP::GetLocation(short job)
{
	return (this->*_GetLocation)(job);

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_IsApparel(SERVER, "CITP::IsApparel");
int CITP::IsApparel(void)
{
	return (this->*_IsApparel)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_PlusDexValue(SERVER, "CITP::PlusDexValue");
short CITP::PlusDexValue(void)
{
	return (this->*_PlusDexValue)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_PlusStrValue(SERVER, "CITP::PlusStrValue");
short CITP::PlusStrValue(void)
{
	return (this->*_PlusStrValue)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_PlusIntValue(SERVER, "CITP::PlusIntValue");
short CITP::PlusIntValue(void)
{
	return (this->*_PlusIntValue)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_PlusLukValue(SERVER, "CITP::PlusLukValue");
short CITP::PlusLukValue(void)
{
	return (this->*_PlusLukValue)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_PlusAgiValue(SERVER, "CITP::PlusAgiValue");
short CITP::PlusAgiValue(void)
{
	return (this->*_PlusAgiValue)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_PlusVitValue(SERVER, "CITP::PlusVitValue");
short CITP::PlusVitValue(void)
{
	return (this->*_PlusVitValue)();

	//TODO
}


hook_method<void (CITP::*)(short& defencePower)> CITP::_GetMagicDefence(SERVER, "CITP::GetMagicDefence");
void CITP::GetMagicDefence(short& defencePower)
{
	return (this->*_GetMagicDefence)(defencePower);

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_GetStatus(SERVER, "CITP::GetStatus");
int CITP::GetStatus(void)
{
	return (this->*_GetStatus)();

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_GetAttRange(SERVER, "CITP::GetAttRange");
int CITP::GetAttRange(void)
{
	return (this->*_GetAttRange)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_GetClass(SERVER, "CITP::GetClass");
short CITP::GetClass(void)
{
	return (this->*_GetClass)();

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_GetItemLevel(SERVER, "CITP::GetItemLevel");
int CITP::GetItemLevel(void)
{
	return (this->*_GetItemLevel)();

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_IsRefinable(SERVER, "CITP::IsRefinable");
int CITP::IsRefinable(void)
{
	return (this->*_IsRefinable)();

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_IsDamagable(SERVER, "CITP::IsDamagable");
int CITP::IsDamagable(void)
{
	return (this->*_IsDamagable)();

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_GetMaxSlot(SERVER, "CITP::GetMaxSlot");
int CITP::GetMaxSlot(void)
{
	return (this->*_GetMaxSlot)();

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_GetProperty(SERVER, "CITP::GetProperty");
int CITP::GetProperty(void)
{
	return (this->*_GetProperty)();

	//TODO
}


hook_method<int (CITP::*)(void)> CITP::_IsMovable(SERVER, "CITP::IsMovable");
int CITP::IsMovable(void)
{
	return (this->*_IsMovable)();

	//TODO
}


hook_method<unsigned long (CITP::*)(void)> CITP::_GetAvailableJobCode(SERVER, "CITP::GetAvailableJobCode");
unsigned long CITP::GetAvailableJobCode(void)
{
	return (this->*_GetAvailableJobCode)();

	//TODO
}


hook_method<bool (CITP::*)(void)> CITP::_IsCashItem(SERVER, "CITP::IsCashItem");
bool CITP::IsCashItem(void)
{
	return (this->*_IsCashItem)();

	//TODO
}


hook_method<bool (CITP::*)(void)> CITP::_IsWeapon(SERVER, "CITP::IsWeapon");
bool CITP::IsWeapon(void)
{
	return (this->*_IsWeapon)();

	//TODO
}


hook_method<bool (CITP::*)(void)> CITP::_IsRangeWeapon(SERVER, "CITP::IsRangeWeapon");
bool CITP::IsRangeWeapon(void)
{
	return (this->*_IsRangeWeapon)();

	//TODO
}


hook_method<bool (CITP::*)(void)> CITP::_IsPickUpNotifyParty(SERVER, "CITP::IsPickUpNotifyParty");
bool CITP::IsPickUpNotifyParty(void)
{
	return (this->*_IsPickUpNotifyParty)();

	//TODO
}


hook_method<short (CITP::*)(void)> CITP::_GetMATK(SERVER, "CITP::GetMATK");
short CITP::GetMATK(void)
{
	return (this->*_GetMATK)();

	//TODO
}


hook_method<bool (CITP::*)(void)> CITP::_IsBothHandWeapon(SERVER, "CITP::IsBothHandWeapon");
bool CITP::IsBothHandWeapon(void)
{
	return (this->*_IsBothHandWeapon)();

	//TODO
}


//hook_method<void (CITP::*)(bool flag)> CITP::_SetUseEvent(SERVER, "CITP::SetUseEvent");
void CITP::SetUseEvent(bool flag)
{
//	return (this->*_SetUseEvent)(flag);

	m_isUseEvent = flag;
}


//hook_method<int (CITP::*)(void)> CITP::_GetUsableLevel(SERVER, "CITP::GetUsableLevel");
int CITP::GetUsableLevel(void)
{
//	return (this->*_GetUsableLevel)();

	return m_usableLevel;
}


//hook_method<unsigned long (CITP::*)(short job)> CITP::_GetBitExpressionJob(SERVER, "CITP::GetBitExpressionJob");
unsigned long CITP::GetBitExpressionJob(short job)
{
//	return (this->*_GetBitExpressionJob)(job);

	switch( job )
	{
	case 0:
	case 23:
	case 4001:
	case 4023:
	case 4045: return 1;
	case 1:
	case 4002:
	case 4024: return 2;
	case 2:
	case 4003:
	case 4025: return 4;
	case 3:
	case 4004:
	case 4026: return 8;
	case 4:
	case 4005:
	case 4027: return 16;
	case 5:
	case 4006:
	case 4028: return 32;
	case 6:
	case 4007:
	case 4029: return 64;
	case 7:
	case 4008:
	case 4030: return 128;
	case 9:
	case 4010:
	case 4032: return 256;
	case 11:
	case 4012:
	case 4034: return 512;
	case 8:
	case 4009:
	case 4031: return 1024;
	case 10:
	case 4011:
	case 4033: return 2048;
	case 12:
	case 4013:
	case 4035: return 4096;
	case 14:
	case 4015:
	case 4037: return 8192;
	case 16:
	case 4017:
	case 4039: return 16384;
	case 19:
	case 4020:
	case 4042: return 32768;
	case 20:
	case 4021:
	case 4043: return 65536;
	case 15:
	case 4016:
	case 4038: return 131072;
	case 18:
	case 4019:
	case 4041: return 262144;
	case 17:
	case 4018:
	case 4040: return 524288;
	default:
		return -1;
	}
}


//hook_method<void (CITP::*)(void)> CITP::_SetBindOnEquip(SERVER, "CITP::SetBindOnEquip");
void CITP::SetBindOnEquip(void)
{
//	return (this->*_SetBindOnEquip)();

	m_isBindOnEquip = true;
}


//hook_method<bool (CITP::*)(void)> CITP::_IsBindOnEquip(SERVER, "CITP::IsBindOnEquip");
bool CITP::IsBindOnEquip(void)
{
//	return (this->*_IsBindOnEquip)();

	return m_isBindOnEquip;
}
