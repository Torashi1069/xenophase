#pragma once
class CPC;


class CPCProperty
{
public:
	struct PCPROPERTY
	{
		/* this+0x0  */ int statusAttPower;
		/* this+0x4  */ int rhandPowerMin;
		/* this+0x8  */ int rhandPowerMax;
		/* this+0xC  */ int lhandPowerMin;
		/* this+0x10 */ int lhandPowerMax;
		/* this+0x14 */ int itemMPowerMin;
		/* this+0x18 */ int itemMPowerMax;
		/* this+0x1C */ int statusDef;
		/* this+0x20 */ int statusMagicPower;
		/* this+0x24 */ int statusMDef;
		/* this+0x28 */ int statusMPowerReduce;
		/* this+0x2C */ int criticalSuccess;
		/* this+0x30 */ int criticalDef;
		/* this+0x34 */ int basicAvoidance;
		/* this+0x38 */ int basicHit;
		/* this+0x3C */ int attackMotionTime;
		/* this+0x40 */ int notifyItemPower;
		/* this+0x44 */ int notifyItemMPower;
		/* this+0x48 */ int notifyItemDef;
		/* this+0x4C */ int notifyItemMDef;
	};

	/* this+0x0 */ public: CPC* m_pc;
	/* this+0x4 */ public: CPCProperty::PCPROPERTY m_propertys;

	public: CPCProperty::CPCProperty(CPC* pc);
	public: void CPCProperty::Reset(void);
	//public: void CPCProperty::UpdateStatusAttPower();
	//public: void CPCProperty::UpdateStatusDef();
	//public: void CPCProperty::UpdateStatusMagicPower();
	//public: void CPCProperty::UpdateStatusMagicDef();
	//public: void CPCProperty::UpdateStatusMagicPowerReduce();
	//public: void CPCProperty::UpdateCriticalSuccessValue();
	//public: void CPCProperty::UpdateCriticalDef();
	//public: void CPCProperty::UpdateAvoidableSucPerOnClient();
	//public: void CPCProperty::UpdateAttSucPercentOnClient();
	//public: void CPCProperty::UpdateAttackMotionTime();
	//public: void CPCProperty::UpdateItemAttPower();
	//public: void CPCProperty::UpdateItemMagicPower();
	//public: void CPCProperty::UpdateItemDef();
	//public: void CPCProperty::UpdateNotifyItemPower();
	//public: void CPCProperty::UpdateNotifyItemMPower();
	public: void CPCProperty::UpdateNotifyItemDef(void);
	//public: void CPCProperty::UpdateNotifyItemMDef();
	//private: void CPCProperty::ItemPowerModifiedByLevelAndDex(int &);
	//private: int CPCProperty::GetAttackMotionTime_STD();

private:
	static hook_method<void (CPCProperty::*)(void)> CPCProperty::_Reset;
	static hook_method<void (CPCProperty::*)(void)> CPCProperty::_UpdateNotifyItemDef;
};
