#pragma once
class CCharacter;


class CCharBuff
{
public:
	struct vtable_t // const CCharBuff::`vftable'
	{
		void (CCharBuff::* Reset)(void);
	};

	struct CHAR_BUFF_STATUS
	{
	/* this+0x0  */ int flee;
	/* this+0x4  */ int atk;
	/* this+0x8  */ int mhpPercent;
	/* this+0xC  */ int mspPercent;
	/* this+0x10 */ int hit;
	};

	struct CHAR_BUFF_DAMAGED
	{
	/* this+0x0 */ int directSubPercent;
	/* this+0x4 */ int magicSubPercent;
	};

	struct CHAR_BUFF_HEAL
	{
	/* this+0x0 */ int hp_modifyPercent;
	/* this+0x4 */ int sp_modifyPercent;
	};

	struct CHAR_BUFF_ASPD
	{
	/* this+0x0 */ int plusAttackSpeedPercent;
	};

	struct CHAR_BUFF_IMMUNEMAGIC
	{
	/* this+0x0 */ int percent;
	};

	/* this+0x0  */ // const CCharBuff::`vftable'
	/* this+0x4  */ CCharacter* m_owner;
	/* this+0x8  */ CCharBuff::CHAR_BUFF_STATUS m_status;
	/* this+0x1C */ CCharBuff::CHAR_BUFF_DAMAGED m_damaged;
	/* this+0x24 */ CCharBuff::CHAR_BUFF_HEAL m_heal;
	/* this+0x2C */ CCharBuff::CHAR_BUFF_ASPD m_aspd;
	/* this+0x30 */ CCharBuff::CHAR_BUFF_IMMUNEMAGIC m_immuneMagic;

	public: CCharBuff::CCharBuff(void);
	public: CCharBuff::~CCharBuff(void);
	public: void CCharBuff::SetOwner(CCharacter* owner);
	public: bool CCharBuff::UpdateParameterValue(unsigned short type, int value);
	public: int CCharBuff::GetParameterValue(unsigned short type);
	public: void CCharBuff::Update_Damaged_DirectSubPercent(int value);
	public: void CCharBuff::Update_Damaged_MagicSubPercent(int value);
	public: int CCharBuff::Get_Damaged_DirectSubPercent(void);
	public: int CCharBuff::Get_Damaged_MagicSubPercent(void);
	public: void CCharBuff::Update_Heal_HP_ModifyPercent(int value);
	//public: void CCharBuff::Update_Heal_SP_ModifyPercent(int);
	public: int CCharBuff::Get_Heal_HP_ModifyPercent(void);
	public: int CCharBuff::Get_Heal_SP_ModifyPercent(void);
	//public: void CCharBuff::Update_ImmuneMagic_Percent(int);
	public: int CCharBuff::Get_ImmnueMagic_Percnet(void); //TYPO
	public: virtual void CCharBuff::Reset(void);

private:
	static hook_method<void (CCharBuff::*)(CCharacter* owner)> CCharBuff::_SetOwner;
	static hook_method<bool (CCharBuff::*)(unsigned short type, int value)> CCharBuff::_UpdateParameterValue;
	static hook_method<int (CCharBuff::*)(unsigned short type)> CCharBuff::_GetParameterValue;
	static hook_method<void (CCharBuff::*)(int value)> CCharBuff::_Update_Damaged_DirectSubPercent;
	static hook_method<void (CCharBuff::*)(int value)> CCharBuff::_Update_Damaged_MagicSubPercent;
	static hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Damaged_DirectSubPercent;
	static hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Damaged_MagicSubPercent;
	static hook_method<void (CCharBuff::*)(int value)> CCharBuff::_Update_Heal_HP_ModifyPercent;
	static hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Heal_HP_ModifyPercent;
	static hook_method<int (CCharBuff::*)(void)> CCharBuff::_Get_Heal_SP_ModifyPercent;
	static hook_method<void (CCharBuff::*)(void)> CCharBuff::_Reset;
};
