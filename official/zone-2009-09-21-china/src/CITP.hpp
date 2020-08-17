#pragma once


/// ITem Prototype.
class CITP
{
public:
	struct vtable_t
	{
		void (CITP::* Init)(void);
		unsigned short (CITP::* GetType)(void);
		void (CITP::* GetAttackValue)(short &);
		void (CITP::* GetDefence)(short &);
		unsigned short (CITP::* GetLocation)(short);
		int (CITP::* IsApparel)(void);
		short (CITP::* PlusDexValue)(void);
		short (CITP::* PlusStrValue)(void);
		short (CITP::* PlusIntValue)(void);
		short (CITP::* PlusLukValue)(void);
		short (CITP::* PlusAgiValue)(void);
		short (CITP::* PlusVitValue)(void);
		void (CITP::* GetMagicDefence)(short &);
		int (CITP::* GetStatus)(void);
		int (CITP::* GetAttRange)(void);
		short (CITP::* GetClass)(void);
		int (CITP::* GetItemLevel)(void);
		int (CITP::* IsRefinable)(void);
		int (CITP::* IsDamagable)(void);
		int (CITP::* GetMaxSlot)(void);
		int (CITP::* GetProperty)(void);
		int (CITP::* IsMovable)(void);
		unsigned long (CITP::* GetAvailableJobCode)(void);
		bool (CITP::* IsCashItem)(void);
		bool (CITP::* IsWeapon)(void);
		bool (CITP::* IsRangeWeapon)(void);
		bool (CITP::* IsPickUpNotifyParty)(void);
		short (CITP::* GetMATK)(void);
		bool (CITP::* IsBothHandWeapon)(void);
	};

	/* this+0x0   */ //const CITP::`vftable'
	/* this+0x4   */ unsigned short m_ITID;
	/* this+0x8   */ int m_usableLevel;
	/* this+0xC   */ int m_weight;
	/* this+0x10  */ int m_price;
	/* this+0x14  */ int m_location;
	/* this+0x18  */ char m_name[24];
	/* this+0x30  */ char m_emotionName[50];
	/* this+0x62  */ char m_description[200];
	/* this+0x12C */ int m_isRefinable;
	/* this+0x130 */ int m_isDamagable;
	/* this+0x134 */ int m_isMovable;
	/* this+0x138 */ unsigned long m_availableJob;
	/* this+0x13C */ bool m_bCashItem;
	/* this+0x13D */ bool m_isUseEvent;
	/* this+0x13E */ bool m_isBindOnEquip;

	public: CITP::CITP(void);
	public: virtual void CITP::Init(void);
	public: virtual unsigned short CITP::GetType(void);
	public: virtual void CITP::GetAttackValue(short& attackPower);
	public: virtual void CITP::GetDefence(short& defencePower);
	public: virtual unsigned short CITP::GetLocation(short job);
	public: virtual int CITP::IsApparel(void);
	public: virtual short CITP::PlusDexValue(void);
	public: virtual short CITP::PlusStrValue(void);
	public: virtual short CITP::PlusIntValue(void);
	public: virtual short CITP::PlusLukValue(void);
	public: virtual short CITP::PlusAgiValue(void);
	public: virtual short CITP::PlusVitValue(void);
	public: virtual void CITP::GetMagicDefence(short& defencePower);
	public: virtual int CITP::GetStatus(void);
	public: virtual int CITP::GetAttRange(void);
	public: virtual short CITP::GetClass(void);
	public: virtual int CITP::GetItemLevel(void);
	public: virtual int CITP::IsRefinable(void);
	public: virtual int CITP::IsDamagable(void);
	public: virtual int CITP::GetMaxSlot(void);
	public: virtual int CITP::GetProperty(void);
	public: virtual int CITP::IsMovable(void);
	public: virtual unsigned long CITP::GetAvailableJobCode(void);
	public: virtual bool CITP::IsCashItem(void);
	public: virtual bool CITP::IsWeapon(void);
	public: virtual bool CITP::IsRangeWeapon(void);
	public: virtual bool CITP::IsPickUpNotifyParty(void);
	public: virtual short CITP::GetMATK(void);
	public: virtual bool CITP::IsBothHandWeapon(void);
	public: void CITP::SetUseEvent(bool flag);
	public: int CITP::GetUsableLevel(void);
	public: unsigned long CITP::GetBitExpressionJob(short job);
	public: void CITP::SetBindOnEquip(void);
	public: bool CITP::IsBindOnEquip(void);

private:
	static hook_method<void (CITP::*)(void)> CITP::_Init;
	static hook_method<unsigned short (CITP::*)(void)> CITP::_GetType;
	static hook_method<void (CITP::*)(short& attackPower)> CITP::_GetAttackValue;
	static hook_method<void (CITP::*)(short& defencePower)> CITP::_GetDefence;
	static hook_method<unsigned short (CITP::*)(short job)> CITP::_GetLocation;
	static hook_method<int (CITP::*)(void)> CITP::_IsApparel;
	static hook_method<short (CITP::*)(void)> CITP::_PlusDexValue;
	static hook_method<short (CITP::*)(void)> CITP::_PlusStrValue;
	static hook_method<short (CITP::*)(void)> CITP::_PlusIntValue;
	static hook_method<short (CITP::*)(void)> CITP::_PlusLukValue;
	static hook_method<short (CITP::*)(void)> CITP::_PlusAgiValue;
	static hook_method<short (CITP::*)(void)> CITP::_PlusVitValue;
	static hook_method<void (CITP::*)(short& defencePower)> CITP::_GetMagicDefence;
	static hook_method<int (CITP::*)(void)> CITP::_GetStatus;
	static hook_method<int (CITP::*)(void)> CITP::_GetAttRange;
	static hook_method<short (CITP::*)(void)> CITP::_GetClass;
	static hook_method<int (CITP::*)(void)> CITP::_GetItemLevel;
	static hook_method<int (CITP::*)(void)> CITP::_IsRefinable;
	static hook_method<int (CITP::*)(void)> CITP::_IsDamagable;
	static hook_method<int (CITP::*)(void)> CITP::_GetMaxSlot;
	static hook_method<int (CITP::*)(void)> CITP::_GetProperty;
	static hook_method<int (CITP::*)(void)> CITP::_IsMovable;
	static hook_method<unsigned long (CITP::*)(void)> CITP::_GetAvailableJobCode;
	static hook_method<bool (CITP::*)(void)> CITP::_IsCashItem;
	static hook_method<bool (CITP::*)(void)> CITP::_IsWeapon;
	static hook_method<bool (CITP::*)(void)> CITP::_IsRangeWeapon;
	static hook_method<bool (CITP::*)(void)> CITP::_IsPickUpNotifyParty;
	static hook_method<short (CITP::*)(void)> CITP::_GetMATK;
	static hook_method<bool (CITP::*)(void)> CITP::_IsBothHandWeapon;
	static hook_method<void (CITP::*)(bool flag)> CITP::_SetUseEvent;
	static hook_method<int (CITP::*)(void)> CITP::_GetUsableLevel;
	static hook_method<unsigned long (CITP::*)(short job)> CITP::_GetBitExpressionJob;
	static hook_method<void (CITP::*)(void)> CITP::_SetBindOnEquip;
	static hook_method<bool (CITP::*)(void)> CITP::_IsBindOnEquip;
};
