#include "CCharBuff.hpp"


/// inlined
CCharBuff::CCharBuff(void)
{
	this->CCharBuff::Reset();
}


/// inlined
CCharBuff::~CCharBuff(void)
{
	this->CCharBuff::Reset();
}


/// inlined
//hook_method<void (CCharBuff::*)(CCharacter* owner)> CCharBuff::_SetOwner(SERVER, "CCharBuff::SetOwner");
void CCharBuff::SetOwner(CCharacter* owner)
{
//	return (this->*_SetOwner)(owner);

	this->Reset();
	m_owner = owner;
}


hook_method<bool (CCharBuff::*)(unsigned short type, int value)> CCharBuff::_UpdateParameterValue(SERVER, "CCharBuff::UpdateParameterValue");
bool CCharBuff::UpdateParameterValue(unsigned short type, int value)
{
	return (this->*_UpdateParameterValue)(type, value);

	//TODO
}


hook_method<int (CCharBuff::*)(unsigned short type)> CCharBuff::_GetParameterValue(SERVER, "CCharBuff::GetParameterValue");
int CCharBuff::GetParameterValue(unsigned short type)
{
	return (this->*_GetParameterValue)(type);

	//TODO
}


//hook_method<void (CCharBuff::*)(int value)> CCharBuff::_Update_Damaged_DirectSubPercent(SERVER, "CCharBuff::Update_Damaged_DirectSubPercent");
void CCharBuff::Update_Damaged_DirectSubPercent(int value)
{
//	return (this->*_Update_Damaged_DirectSubPercent)(value);

	m_damaged.directSubPercent += value;
}


//hook_method<void (CCharBuff::*)(int value)> CCharBuff::_Update_Damaged_MagicSubPercent(SERVER, "CCharBuff::Update_Damaged_MagicSubPercent");
void CCharBuff::Update_Damaged_MagicSubPercent(int value)
{
//	return (this->*_Update_Damaged_MagicSubPercent)(value);

	m_damaged.magicSubPercent += value;
}


//hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Damaged_DirectSubPercent(SERVER, "CCharBuff::Get_Damaged_DirectSubPercent");
int CCharBuff::Get_Damaged_DirectSubPercent(void)
{
//	return (this->*_Get_Damaged_DirectSubPercent)();

	return m_damaged.directSubPercent;
}


//hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Damaged_MagicSubPercent(SERVER, "CCharBuff::Get_Damaged_MagicSubPercent");
int CCharBuff::Get_Damaged_MagicSubPercent(void)
{
//	return (this->*_Get_Damaged_MagicSubPercent)();

	return m_damaged.magicSubPercent;
}


//hook_method<void (CCharBuff::*)(int value)> CCharBuff::_Update_Heal_HP_ModifyPercent(SERVER, "CCharBuff::Update_Heal_HP_ModifyPercent");
void CCharBuff::Update_Heal_HP_ModifyPercent(int value)
{
//	return (this->*_Update_Heal_HP_ModifyPercent)(value);

	m_heal.hp_modifyPercent += value;
}


//hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Heal_HP_ModifyPercent(SERVER, "CCharBuff::Get_Heal_HP_ModifyPercent");
int CCharBuff::Get_Heal_HP_ModifyPercent(void)
{
//	return (this->*_Get_Heal_HP_ModifyPercent)();

	return m_heal.hp_modifyPercent;
}


/* hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Heal_SP_ModifyPercent(SERVER, "CCharBuff::Get_Heal_SP_ModifyPercent");
int CCharBuff::Get_Heal_SP_ModifyPercent(void)
{
	return (this->*_Get_Heal_SP_ModifyPercent)();

	//TODO
} */


hook_method<void (CCharBuff::*)(void)> CCharBuff::_Reset(SERVER, "CCharBuff::Reset");
void CCharBuff::Reset(void)
{
	return (this->*_Reset)();

	m_owner = 0;
	m_status.flee = 0;
	m_status.atk = 0;
	m_status.mhpPercent = 0;
	m_status.mspPercent = 0;
	m_status.hit = 0;
	m_damaged.directSubPercent = 0;
	m_damaged.magicSubPercent = 0;
	m_heal.hp_modifyPercent = 0;
	m_heal.sp_modifyPercent = 0;
	m_aspd.plusAttackSpeedPercent = 0;
	m_immuneMagic.percent = 0;
}
