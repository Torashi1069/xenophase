#pragma once


enum enumITEMTYPE
{
	TYPE_HEAL            = 0,
	TYPE_SCHANGE         = 1,
	TYPE_SPECIAL         = 2,
	TYPE_EVENT           = 3,
	TYPE_ARMOR           = 4,
	TYPE_WEAPON          = 5,
	TYPE_CARD            = 6,
	TYPE_QUEST           = 7,
	TYPE_BOW             = 8,
	TYPE_BOTHHAND        = 9,
	TYPE_ARROW           = 10,
	TYPE_ARMORTM         = 11,
	TYPE_ARMORTB         = 12,
	TYPE_ARMORMB         = 13,
	TYPE_ARMORTMB        = 14,
	TYPE_GUN             = 15,
	TYPE_AMMO            = 16,
	TYPE_THROWWEAPON     = 17,
	TYPE_CASH_POINT_ITEM = 18,
	TYPE_CANNONBALL      = 19,
	TYPE_LAST            = 20,
};


enum enumWEAPONTYPE
{
	WEAPONTYPE_NONE                  = 0,
	WEAPONTYPE_SHORTSWORD            = 1,
	WEAPONTYPE_SWORD                 = 2,
	WEAPONTYPE_TWOHANDSWORD          = 3,
	WEAPONTYPE_SPEAR                 = 4,
	WEAPONTYPE_TWOHANDSPEAR          = 5,
	WEAPONTYPE_AXE                   = 6,
	WEAPONTYPE_TWOHANDAXE            = 7,
	WEAPONTYPE_MACE                  = 8,
	WEAPONTYPE_TWOHANDMACE           = 9,
	WEAPONTYPE_ROD                   = 10,
	WEAPONTYPE_BOW                   = 11,
	WEAPONTYPE_KNUKLE                = 12,
	WEAPONTYPE_INSTRUMENT            = 13,
	WEAPONTYPE_WHIP                  = 14,
	WEAPONTYPE_BOOK                  = 15,
	WEAPONTYPE_CATARRH               = 16,
	WPCLASS_GUN_HANDGUN              = 17,
	WPCLASS_GUN_RIFLE                = 18,
	WPCLASS_GUN_GATLING              = 19,
	WPCLASS_GUN_SHOTGUN              = 20,
	WPCLASS_GUN_GRANADE              = 21,
	WPCLASS_SYURIKEN                 = 22,
	WPCLASS_TWOHANDROD               = 23,
	WPCLASS_LAST                     = 24,
	WEAPONTYPE_SHORTSWORD_SHORTSWORD = 25,
	WEAPONTYPE_SWORD_SWORD           = 26,
	WEAPONTYPE_AXE_AXE               = 27,
	WEAPONTYPE_SHORTSWORD_SWORD      = 28,
	WEAPONTYPE_SHORTSWORD_AXE        = 29,
	WEAPONTYPE_SWORD_AXE             = 30,
	WEAPONTYPE_LAST                  = 31,
};


enum enumNOTMOVETYPE
{
	NOTMOVE_DROP     = 0x01,
	NOTMOVE_EXCHANGE = 0x02,
	NOTMOVE_STORE    = 0x04,
	NOTMOVE_CART     = 0x08,
	NOTMOVE_SELL_NPC = 0x10,
	NOTMOVE_MAIL     = 0x20,
	NOTMOVE_AUCTION  = 0x40,
	NOTMOVE_ALL      = 0xFF,
};


class CITP
{
public:
	CITP();
	virtual void Init();
	virtual unsigned short GetType();
	virtual void GetAttackValue(short& attackPower);
	virtual void GetDefence(short& defencePower);
	virtual unsigned short GetLocation(short job);
	virtual BOOL IsApparel();
	virtual short PlusDexValue();
	virtual short PlusStrValue();
	virtual short PlusIntValue();
	virtual short PlusLukValue();
	virtual short PlusAgiValue();
	virtual short PlusVitValue();
	virtual void GetMagicDefence(short& attackPower);
	virtual int GetStatus();
	virtual int GetAttRange();
	virtual short GetClass(); // enumWEAPONTYPE
	virtual int GetItemLevel();
	virtual BOOL IsRefinable();
	virtual BOOL IsDamagable();
	virtual int GetMaxSlot();
	virtual int GetProperty();
	virtual int IsMovable();
	virtual unsigned long GetAvailableJobCode();
	virtual bool IsCashItem();
	virtual bool IsWeapon();
	virtual bool IsRangeWeapon();
	virtual bool IsPickUpNotifyParty();
	virtual short GetMATK();
	virtual bool IsBothHandWeapon();

	void SetUseEvent(bool flag);
	bool IsUsableLevel(const int in_Level);
	unsigned long GetBitExpressionJob(short job);

	void SetBindOnEquip();
	bool IsBindOnEquip();

	/* this+ 0 */ //const CITP::`vftable';
	/* this+ 4 */ unsigned short m_ITID;
	/* this+ 8 */ int m_weight;
	/* this+12 */ int m_price;
	/* this+16 */ int m_location;
	/* this+20 */ char m_name[24];
	/* this+44 */ BOOL m_isRefinable;
	/* this+48 */ BOOL m_isDamagable;
	/* this+52 */ int m_isMovable; // enumNOTMOVETYPE
	/* this+56 */ unsigned long m_availableJob;
	/* this+60 */ bool m_bCashItem;
	/* this+61 */ bool m_isUseEvent;
	/* this+62 */ bool m_isBindOnEquip;
	/* this+64 */ short m_minLevel;
	/* this+66 */ short m_maxLevel;
};


class CITPHeal : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual BOOL IsApparel();
	virtual int GetStatus();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ int m_minHp;
	/* this+72 */ int m_maxHp;
	/* this+76 */ int m_minSp;
	/* this+80 */ int m_maxSp;
	/* this+84 */ int m_abuse_gause;
	/* this+88 */ int m_states;
};


class CITPSpecial : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual BOOL IsApparel();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ unsigned long m_effect;
};


class CITPEvent : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual BOOL IsApparel();

	/* this+ 0 */ //CITP baseclass_0;
};


class CITPArrow : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual BOOL IsApparel();
	virtual void GetAttackValue(short& ATKPower);
	virtual unsigned short GetLocation(short job);
	virtual int GetProperty();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ int m_ATK;
	/* this+72 */ int m_property;
};


class CITPAmmo : public CITP
{
public:
	virtual unsigned short GetType();
	virtual BOOL IsApparel();
	virtual void GetAttackValue(short& ATKPower);
	virtual unsigned short GetLocation(short job);
	virtual int GetProperty();
	virtual unsigned long GetAvailableJobCode();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ int m_ATK;
	/* this+72 */ int m_property;
};


class CITPThrow : public CITP
{
public:
	virtual unsigned short GetType();
	virtual BOOL IsApparel();
	virtual void GetAttackValue(short& ATKPower);
	virtual unsigned short GetLocation(short job);
	virtual int GetProperty();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ int m_ATK;
	/* this+72 */ int m_property;
};


class CITPArmor : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual void GetDefence(short& defencePower);
	virtual BOOL IsApparel();
	virtual short GetClass(); // enumWEAPONTYPE
	virtual unsigned short GetLocation(short job);
	virtual short PlusDexValue();
	virtual short PlusStrValue();
	virtual short PlusIntValue();
	virtual short PlusLukValue();
	virtual short PlusAgiValue();
	virtual short PlusVitValue();
	virtual void GetMagicDefence(short& defencePower);
	virtual int GetMaxSlot();
	virtual bool IsPickUpNotifyParty();

	/* this+  0 */ //CITP baseclass_0;
	/* this+ 68 */ int m_defencePower;
	/* this+ 72 */ int m_maxSlot;
	/* this+ 76 */ int m_str;
	/* this+ 80 */ int m_int;
	/* this+ 84 */ int m_vit;
	/* this+ 88 */ int m_dex;
	/* this+ 92 */ int m_agi;
	/* this+ 96 */ int m_luk;
	/* this+100 */ int m_mdef;
	/* this+104 */ int m_maxHp;
	/* this+108 */ int m_effect;
	/* this+112 */ int m_maxSp;
	/* this+116 */ int m_sex;
	/* this+120 */ short m_class; // enumWEAPONTYPE
};


class CITPArmorTM : public CITPArmor
{
public:
	virtual unsigned short GetType();
	virtual unsigned short GetLocation(short job);
};


class CITPArmorTB : public CITPArmor
{
public:
	virtual unsigned short GetType();
	virtual unsigned short GetLocation(short job);
};


class CITPArmorMB : public CITPArmor
{
	virtual unsigned short GetType();
	virtual unsigned short GetLocation(short job);
};


class CITPArmorTMB : public CITPArmor
{
	virtual unsigned short GetType();
	virtual unsigned short GetLocation(short job);
};


class CITPWeapon : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual void GetAttackValue(short& attackPower);
	virtual BOOL IsApparel();
	virtual short GetClass(); // enumWEAPONTYPE
	virtual unsigned short GetLocation(short job);
	virtual short PlusDexValue();
	virtual short PlusStrValue();
	virtual short PlusIntValue();
	virtual short PlusLukValue();
	virtual short PlusAgiValue();
	virtual short PlusVitValue();
	virtual int GetAttRange();
	virtual int GetProperty();
	virtual int GetItemLevel();
	virtual int GetMaxSlot();
	virtual bool IsWeapon();
	virtual bool IsRangeWeapon();
	virtual bool IsPickUpNotifyParty();
	virtual short GetMATK();

	/* this+  0 */ //CITP baseclass_0;
	/* this+ 68 */ int m_ATK;
	/* this+ 72 */ short m_MATK;
	/* this+ 76 */ int m_AR;
	/* this+ 80 */ int m_maxSlot;
	/* this+ 84 */ int m_str;
	/* this+ 88 */ int m_int;
	/* this+ 92 */ int m_vit;
	/* this+ 96 */ int m_dex;
	/* this+100 */ int m_agi;
	/* this+104 */ int m_luk;
	/* this+108 */ int m_effect;
	/* this+112 */ int m_sex;
	/* this+116 */ int m_level;
	/* this+120 */ short m_class; // enumWEAPONTYPE
	/* this+124 */ int m_property;
};


class CITPBothhand : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual void GetAttackValue(short& attackPower);
	virtual BOOL IsApparel();
	virtual short GetClass(); // enumWEAPONTYPE
	virtual unsigned short GetLocation(short job);
	virtual short PlusDexValue();
	virtual short PlusStrValue();
	virtual short PlusIntValue();
	virtual short PlusLukValue();
	virtual short PlusAgiValue();
	virtual short PlusVitValue();
	virtual int GetAttRange();
	virtual int GetProperty();
	virtual int GetItemLevel();
	virtual int GetMaxSlot();
	virtual bool IsWeapon();
	virtual bool IsRangeWeapon();
	virtual bool IsPickUpNotifyParty();
	virtual short GetMATK();
	virtual bool IsBothHandWeapon();

	/* this+  0 */ //CITP baseclass_0;
	/* this+ 68 */ int m_ATK;
	/* this+ 72 */ short m_MATK;
	/* this+ 76 */ int m_AR;
	/* this+ 80 */ int m_maxSlot;
	/* this+ 84 */ int m_str;
	/* this+ 88 */ int m_int;
	/* this+ 92 */ int m_vit;
	/* this+ 96 */ int m_dex;
	/* this+100 */ int m_agi;
	/* this+104 */ int m_luk;
	/* this+108 */ int m_effect;
	/* this+112 */ int m_sex;
	/* this+116 */ int m_level;
	/* this+120 */ short m_class; // enumWEAPONTYPE
	/* this+124 */ int m_property;
};


class CITPBow : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual void GetAttackValue(short& attackPower);
	virtual BOOL IsApparel();
	virtual short GetClass(); // enumWEAPONTYPE
	virtual unsigned short GetLocation(short job);
	virtual short PlusDexValue();
	virtual short PlusStrValue();
	virtual short PlusIntValue();
	virtual short PlusLukValue();
	virtual short PlusAgiValue();
	virtual short PlusVitValue();
	virtual int GetAttRange();
	virtual int GetProperty();
	virtual int GetItemLevel();
	virtual int GetMaxSlot();
	virtual bool IsWeapon();
	virtual bool IsRangeWeapon();
	virtual bool IsPickUpNotifyParty();
	virtual bool IsBothHandWeapon();

	/* this+  0 */ //CITP baseclass_0;
	/* this+ 68 */ int m_ATK;
	/* this+ 72 */ int m_AR;
	/* this+ 76 */ int m_maxSlot;
	/* this+ 80 */ int m_str;
	/* this+ 84 */ int m_int;
	/* this+ 88 */ int m_vit;
	/* this+ 92 */ int m_dex;
	/* this+ 96 */ int m_agi;
	/* this+100 */ int m_luk;
	/* this+104 */ int m_effect;
	/* this+108 */ int m_sex;
	/* this+112 */ int m_level;
	/* this+116 */ short m_class; // enumWEAPONTYPE
	/* this+120 */ int m_property;
};


class CITPGun : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual void GetAttackValue(short& ATKPower);
	virtual BOOL IsApparel();
	virtual short GetClass(); // enumWEAPONTYPE
	virtual unsigned short GetLocation(short job);
	virtual short PlusDexValue();
	virtual short PlusStrValue();
	virtual short PlusIntValue();
	virtual short PlusLukValue();
	virtual short PlusAgiValue();
	virtual short PlusVitValue();
	virtual int GetAttRange();
	virtual int GetProperty();
	virtual int GetItemLevel();
	virtual int GetMaxSlot();
	virtual bool IsWeapon();
	virtual bool IsRangeWeapon();
	virtual bool IsPickUpNotifyParty();
	virtual bool IsBothHandWeapon();

	/* this+  0 */ //CITP baseclass_0;
	/* this+ 68 */ int m_ATK;
	/* this+ 72 */ int m_AR;
	/* this+ 76 */ int m_maxSlot;
	/* this+ 80 */ int m_str;
	/* this+ 84 */ int m_int;
	/* this+ 88 */ int m_vit;
	/* this+ 92 */ int m_dex;
	/* this+ 96 */ int m_agi;
	/* this+100 */ int m_luk;
	/* this+104 */ int m_effect;
	/* this+108 */ int m_sex;
	/* this+112 */ int m_level;
	/* this+116 */ short m_class; // enumWEAPONTYPE
	/* this+120 */ int m_property;
};


class CITPCard : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual BOOL IsApparel();
	virtual int GetProperty();

	int GetCompositionType();
	int GetCompositionPos();
	BOOL IsCompositionable(CITP* equipItp);

	virtual bool IsPickUpNotifyParty();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ unsigned long m_effect;
	/* this+72 */ int m_property;
	/* this+76 */ int m_class;
	/* this+80 */ int m_compositionType;
	/* this+84 */ int m_compositionPos;
};


class CITPQuest : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual BOOL IsApparel();

	/* this+ 0 */ //CITP baseclass_0;
};


class CITPCashPointItem : public CITP
{
public:
	virtual void Init();
	virtual unsigned short GetType();
	virtual BOOL IsApparel();
	virtual short GetChangeItemID();
	virtual short GetCount();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ unsigned short m_ChangeItemID;
	/* this+72 */ int m_Count;

	CITPCashPointItem();
	virtual ~CITPCashPointItem();
};


class CITPCannonball : public CITP
{
public:
	virtual unsigned short GetType();
	virtual BOOL IsApparel();
	virtual void GetAttackValue(short& ATKPower);
	virtual unsigned short GetLocation(short job);
	virtual int GetProperty();
	virtual unsigned long GetAvailableJobCode();

	/* this+ 0 */ //CITP baseclass_0;
	/* this+68 */ int m_ATK;
	/* this+72 */ int m_property;
};
