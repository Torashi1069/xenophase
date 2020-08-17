#pragma once
class CPC;


class CPCProperty
{
public:
	CPCProperty(CPC* pc);
	void Reset();

public:
	struct PCPROPERTY
	{
		/* this+ 0 */ int statusAttPower;
		/* this+ 4 */ int rhandPowerMin;
		/* this+ 8 */ int rhandPowerMax;
		/* this+12 */ int lhandPowerMin;
		/* this+16 */ int lhandPowerMax;
		/* this+20 */ int itemMPowerMin;
		/* this+24 */ int itemMPowerMax;
		/* this+28 */ int statusDef;
		/* this+32 */ int statusMagicPower;
		/* this+36 */ int statusMDef;
		/* this+40 */ int statusMPowerReduce;
		/* this+44 */ int criticalSuccess;
		/* this+48 */ int criticalDef;
		/* this+52 */ int basicAvoidance;
		/* this+56 */ int basicHit;
		/* this+60 */ int attackMotionTime;
		/* this+64 */ int notifyItemPower;
		/* this+68 */ int notifyItemMPower;
		/* this+72 */ int notifyItemDef;
		/* this+76 */ int notifyItemMDef;
	};

public:
	/* this+0 */ CPC* m_pc;
	/* this+4 */ PCPROPERTY m_propertys;

public:
	void UpdateStatusAttPower();
	void UpdateStatusDef();
	void UpdateStatusMagicPower();
	void UpdateStatusMagicDef();
	void UpdateStatusMagicPowerReduce();
	void UpdateCriticalSuccessValue();
	void UpdateCriticalDef();
	void UpdateAvoidableSucPerOnClient();
	void UpdateAttSucPercentOnClient();
	void UpdateAttackMotionTime();
	void UpdateItemAttPower();
	void UpdateItemMagicPower();
	void UpdateItemDef(); // not implemented
	void UpdateNotifyItemPower();
	void UpdateNotifyItemMPower();
	void UpdateNotifyItemDef();
	void UpdateNotifyItemMDef();

private:
	void ItemPowerModifiedByLevelAndDex(int& value);
	int GetAttackMotionTime_STD();
	int GetAvoidDecPercent();
	int GetBasicHitDecPercent();
};
