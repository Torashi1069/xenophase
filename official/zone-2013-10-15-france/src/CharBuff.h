#pragma once
class CCharacter;


class CCharBuff
{
private:
	struct CHAR_BUFF_STATUS
	{
		/* this+ 0 */ int flee;
		/* this+ 4 */ int atk;
		/* this+ 8 */ int mhpPercent;
		/* this+12 */ int mspPercent;
		/* this+16 */ int hit;
	};

	struct CHAR_BUFF_DAMAGED
	{
		/* this+0 */ int directSubPercent;
		/* this+4 */ int magicSubPercent;
	};

	struct CHAR_BUFF_HEAL
	{
		/* this+0 */ int hp_modifyPercent;
		/* this+4 */ int sp_modifyPercent;
	};

	struct CHAR_BUFF_ASPD
	{
		/* this+0 */ int plusAttackSpeedPercent;
	};

	struct CHAR_BUFF_IMMUNEMAGIC
	{
		/* this+0 */ int percent;
	};

public:
	CCharBuff();
	~CCharBuff();

public:
	void SetOwner(CCharacter* owner);
	bool UpdateParameterValue(unsigned short type, int value);
	int GetParameterValue(unsigned short type);

public:
	void Update_Damaged_DirectSubPercent(int value);
	int Get_Damaged_DirectSubPercent();
	void Update_Damaged_MagicSubPercent(int value);
	int Get_Damaged_MagicSubPercent();
	void Update_Heal_HP_ModifyPercent(int value);
	int Get_Heal_HP_ModifyPercent();
	void Update_Heal_SP_ModifyPercent(int value);
	int Get_Heal_SP_ModifyPercent();
	void Update_ImmuneMagic_Percent(int value);
	int Get_ImmnueMagic_Percnet();

public:
	virtual void Reset();

private:
	/* this+ 0 */ //const CCharBuff::`vftable';
	/* this+ 4 */ CCharacter* m_owner;
	/* this+ 8 */ CHAR_BUFF_STATUS m_status;
	/* this+28 */ CHAR_BUFF_DAMAGED m_damaged;
	/* this+36 */ CHAR_BUFF_HEAL m_heal;
	/* this+44 */ CHAR_BUFF_ASPD m_aspd;
	/* this+48 */ CHAR_BUFF_IMMUNEMAGIC m_immuneMagic;
};
