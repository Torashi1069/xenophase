#pragma once
#include "Character.h"
#include "struct.hpp"
#include "std/vector"
class CITP;


class CItem : public CCharacter
{
public:
	struct vtable_t // const CItem::`vftable'
	{
		void* vector_deleting_destructor; // void* CItem::`vector deleting destructor'(uint)
		int (CCharacter::* GetType)(void);
		void (CCharacter::* AddErrorCount)(const char*, int, unsigned long, unsigned long);
		void* AddErrorCount2;             // void CCharacter::AddErrorCount(ulong,ulong)
		void (CCharacter::* Init)(void);
		int (CCharacter::* GetWeaponProperty)(int, int);
		bool (CCharacter::* IsActor)(void);
		int (CCharacter::* IsItPossible)(int);
		int (CCharacter::* IsSiegeMode)(void);
		unsigned long (CItem::* GetAccountID)(void);

		int (CItem::* OnMsg)(CCharacter *, CCharacter *, unsigned long, int, int, int, MSGpar::CVar);
		int (CItem::* GetParameterValue)(unsigned short, int &);
		int (CItem::* UpdateParameterValue)(unsigned short, int);
		void (CItem::* InsertCommand)(COMMAND_QUEUE*);
		void (CItem::* CheckCommandQueue)(void);
		void (CItem::* DisableCommand)(unsigned long);
		COMMAND_QUEUE* (CCharacter::* SearchCommand)(unsigned long);
		int (CItem::* IsMyArea)(CCharacter*, int);
		unsigned long (CCharacter::* GetState)(void);
		int (CCharacter::* GetScale)(void);

		int (CItem::* IsTarget)(CCharacter *, unsigned long);
		int (CCharacter::* IsDamageMotionPossible)(void);
		int (CCharacter::* IsRightProperty)(int);
		int (CCharacter::* IsAvoidable)(int, int, int);
		int (CCharacter::* IsInitingState)(void);
		int (CCharacter::* IsLucky)(void);
		void (CCharacter::* OnShowEffect)(int);
		void (CCharacter::* OnShowEffect3)(int, int);
		int (CCharacter::* GetEffectState)(void);
		void (CCharacter::* OnMsgFromItemServer)(unsigned long, CITZMsg*);

		void (CCharacter::* ReduceSPByUseSkill)(int);
		bool (CCharacter::* IsExistItem)(int, int, bool);
		bool (CCharacter::* ConsumeItemByUseSkill)(int, int, bool);
		short (CCharacter::* GetAttackSuccessPercent)(CCharacter *, int);
		int (CCharacter::* GetAttackFinalDamage)(ATTACK_INFO*);
		int (CCharacter::* SkillAttack)(SKILLATTACK_MSG*, int, int, const bool);
		short (CCharacter::* SplashAttack)(int, short, short, int, int, int, unsigned long, void*, int, int);
		int (CCharacter::* SplashAttack2)(int, PosInfo, int, int, int, MSG_TYPE1_TWODWORD*, int, int, PosInfo*);
		int (CCharacter::* SetHandicapState)(int, CCharacter*, int, int, int, int, int);
		int (CCharacter::* GetModifiedTargetItemDEF)(CCharacter*);

		int (CCharacter::* GetModifiedTargetItemMDEF)(CCharacter*);
		int (CCharacter::* SetEffective)(int, int, int, int, int, int);
		int (CCharacter::* GetEffective)(int, int);
		void (CCharacter::* UpdateEffective)(int, int, int);
		void (CCharacter::* ResetEffective)(int, int);
		bool (CCharacter::* IsEnableSetEffective)(int, int, int);
		bool (CCharacter::* IsGroundEffective)(int, int&, bool&);
		void (CCharacter::* ProcessGroundEffective)(int, int, bool);
		void (CCharacter::* ProcessCheckEffective)(int, EFFECTIVE_INFO *);
		void (CCharacter::* SetOnShowEFST)(int);

		void (CCharacter::* SetOffShowEFST)(int);
		void (CCharacter::* OnChangeStatusAmount)(int, unsigned short, unsigned long, int);
		void (CCharacter::* NotifyStatusAmount)(unsigned short, int);
		char (CCharacter::* GetCampID)(void);
		void (CCharacter::* SetCampID)(char);
	};

	/* this+0x0   */ //CCharacter
	/* this+0xE8  */ ITEM_INFO m_itemInfo;
	/* this+0x138 */ unsigned long m_ITAID;
	/* this+0x13C */ unsigned long m_pickableType;
	/* this+0x140 */ unsigned long m_pickablePARTYID;
	/* this+0x144 */ mystd::vector<PICKUPABLE_PCLIST> m_pickupablePCList;
	/* this+0x154 */ unsigned long m_pickableTime;

	public: CItem::CItem(void);
	public: virtual CItem::~CItem(void);
	public: const char* CItem::GetName(void);
	public: virtual unsigned long CItem::GetAccountID(void);
	public: void CItem::Init(CITP* itp, ITEM_INFO* itemInfo);
	public: void CItem::UpdateItem(mystd::vector<CCharacter*>* section);
	public: void CItem::Reset(void);
	public: int CItem::OnProcess(void);
	public: void CItem::CheckStateChange(void);
	public: void CItem::NotifyUpdateInfo(CPC* other);
	public: void CItem::OnDisappear(void);
	public: virtual int CItem::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	public: virtual int CItem::GetParameterValue(unsigned short id, int& value);
	public: virtual int CItem::UpdateParameterValue(unsigned short id, int value);
	public: virtual void CItem::InsertCommand(COMMAND_QUEUE* command);
	public: virtual void CItem::CheckCommandQueue(void);
	public: virtual void CItem::DisableCommand(unsigned long commandID);
	public: virtual int CItem::IsMyArea(CCharacter* ch, int range);
	public: virtual int CItem::IsTarget(CCharacter* ch, unsigned long flag);
	public: void CItem::SetAccountID(unsigned long ITAID);
	public: unsigned short CItem::GetITID(void);
	public: unsigned short CItem::GetCount(void);
	public: void CItem::SetPickableType(unsigned long type);
	public: unsigned long CItem::GetPickableType(void);
	public: void CItem::SetPickableParty(unsigned long PAID);
	public: unsigned long CItem::GetPickablePartyID(void);
	public: void CItem::AddPickupablePC(unsigned long val, unsigned long time);
	public: int CItem::IsPickUpable(unsigned long val);
	public: void CItem::SetUniqueIdentifyNumber(const __int64 in_unigue_identity_number);
	public: __int64 CItem::GetUniqueIdentityNumber(void);
	public: long CItem::GetHireExpireDate(void);
	public: void CItem::SetPickableTime(unsigned long time);
	private: void CItem::InitThePCCacheInfo(int par1);

private:
	static hook_method<const char* (CItem::*)(void)> CItem::_GetName;
	static hook_method<unsigned long (CItem::*)(void)> CItem::_GetAccountID;
	static hook_method<void (CItem::*)(CITP* itp, ITEM_INFO* itemInfo)> CItem::_Init;
	static hook_method<void (CItem::*)(mystd::vector<CCharacter*>* section)> CItem::_UpdateItem;
	static hook_method<void (CItem::*)(void)> CItem::_Reset;
	static hook_method<int (CItem::*)(void)> CItem::_OnProcess;
	static hook_method<void (CItem::*)(void)> CItem::_CheckStateChange;
	static hook_method<void (CItem::*)(CPC* other)> CItem::_NotifyUpdateInfo;
	static hook_method<void (CItem::*)(void)> CItem::_OnDisappear;
	static hook_method<int (CItem::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CItem::_OnMsg;
	static hook_method<int (CItem::*)(unsigned short id, int& value)> CItem::_GetParameterValue;
	static hook_method<int (CItem::*)(unsigned short id, int value)> CItem::_UpdateParameterValue;
	static hook_method<void (CItem::*)(COMMAND_QUEUE* command)> CItem::_InsertCommand;
	static hook_method<void (CItem::*)(void)> CItem::_CheckCommandQueue;
	static hook_method<void (CItem::*)(unsigned long commandID)> CItem::_DisableCommand;
	static hook_method<int (CItem::*)(CCharacter* ch, int range)> CItem::_IsMyArea;
	static hook_method<int (CItem::*)(CCharacter* ch, unsigned long flag)> CItem::_IsTarget;
	static hook_method<void (CItem::*)(unsigned long ITAID)> CItem::_SetAccountID;
	static hook_method<unsigned short (CItem::*)(void)> CItem::_GetITID;
	static hook_method<unsigned short (CItem::*)(void)> CItem::_GetCount;
	static hook_method<void (CItem::*)(unsigned long type)> CItem::_SetPickableType;
	static hook_method<unsigned long (CItem::*)(void)> CItem::_GetPickableType;
	static hook_method<void (CItem::*)(unsigned long PAID)> CItem::_SetPickableParty;
	static hook_method<unsigned long (CItem::*)(void)> CItem::_GetPickablePartyID;
	static hook_method<void (CItem::*)(unsigned long val, unsigned long time)> CItem::_AddPickupablePC;
	static hook_method<int (CItem::*)(unsigned long val)> CItem::_IsPickUpable;
	static hook_method<void (CItem::*)(const __int64 in_unigue_identity_number)> CItem::_SetUniqueIdentifyNumber;
	static hook_method<__int64 (CItem::*)(void)> CItem::_GetUniqueIdentityNumber;
	static hook_method<long (CItem::*)(void)> CItem::_GetHireExpireDate;
	static hook_method<void (CItem::*)(unsigned long time)> CItem::_SetPickableTime;
	static hook_method<void (CItem::*)(int par1)> CItem::_InitThePCCacheInfo;
};
