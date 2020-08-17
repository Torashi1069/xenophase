#pragma once
#include "CCharBuff.hpp"
#include "Client.h"
#include "MapRes.h"
#include "CNeighborCache.hpp"
#include "struct.hpp"
#include "std/map"
#include "std/list"
#include "std/vector"
class CITZMsg;


class CCharacter : public CClient
{
public:
	struct vtable_t // const CCharacter::`vftable'
	{
		void* (CCharacter::* scalar_deleting_destructor)(unsigned int flags);
		int (CCharacter::* GetType)(void);
		void (CCharacter::* AddErrorCount)(const char* filename, int line, DWORD count, DWORD time);
		void (CCharacter::* AddErrorCount2)(DWORD count, DWORD time);
		void (CCharacter::* Init)(void);
		int (CCharacter::* GetWeaponProperty)(int position, int isArrowProperty);
		bool (CCharacter::* IsActor)(void);
		int (CCharacter::* IsItPossible)(int property);
		int (CCharacter::* IsSiegeMode)(void);
		unsigned long (CCharacter::* GetAccountID)(void); // __purecall

		int (CCharacter::* OnMsg)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
		int (CCharacter::* GetParameterValue)(unsigned short id, int& value);
		int (CCharacter::* UpdateParameterValue)(unsigned short id, int value);
		void (CCharacter::* InsertCommand)(COMMAND_QUEUE* command); // __purecall
		void (CCharacter::* CheckCommandQueue)(void); // __purecall
		void (CCharacter::* DisableCommand)(unsigned long commandID);
		COMMAND_QUEUE* (CCharacter::* SearchCommand)(unsigned long commandID);
		int (CCharacter::* IsMyArea)(CCharacter* ch, int range); // __purecall
		unsigned long (CCharacter::* GetState)(void);
		int (CCharacter::* GetScale)(void);

		int (CCharacter::* IsTarget)(CCharacter* ch, unsigned long flag); // __purecall
		int (CCharacter::* IsDamageMotionPossible)(void);
		int (CCharacter::* IsRightProperty)(int property);
		int (CCharacter::* IsAvoidable)(int race, int _class, int level);
		int (CCharacter::* IsInitingState)(void);
		int (CCharacter::* IsLucky)(void);
		void (CCharacter::* OnShowEffect)(int effect);
		void (CCharacter::* OnShowEffect3)(int effect, int numdata);
		int (CCharacter::* GetEffectState)(void);
		void (CCharacter::* OnMsgFromItemServer)(unsigned long in_loc, CITZMsg* flag);

		void (CCharacter::* ReduceSPByUseSkill)(int sp);
		bool (CCharacter::* IsExistItem)(int itemID, int count, bool isExternalEffect);
		bool (CCharacter::* ConsumeItemByUseSkill)(int itemID, int count, bool isExternalEffect);
		short (CCharacter::* GetAttackSuccessPercent)(CCharacter* other, int isRangeAttack);
		int (CCharacter::* GetAttackFinalDamage)(ATTACK_INFO* info);
		int (CCharacter::* SkillAttack)(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill);
		short (CCharacter::* SplashAttack)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count);
		int (CCharacter::* SplashAttack2)(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc);
		int (CCharacter::* SetHandicapState)(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime);
		int (CCharacter::* GetModifiedTargetItemDEF)(CCharacter* target);

		int (CCharacter::* GetModifiedTargetItemMDEF)(CCharacter* target);
		int (CCharacter::* SetEffective)(int index, int time, int val1, int val2, int val3, int isSendClient);
		int (CCharacter::* GetEffective)(int index, int enumVal);
		void (CCharacter::* UpdateEffective)(int index, int val, int enumVal);
		void (CCharacter::* ResetEffective)(int index, int val);
		bool (CCharacter::* IsEnableSetEffective)(int index, int time, int val);
		bool (CCharacter::* IsGroundEffective)(int index, int& SKID, bool& isPlaySolo);
		void (CCharacter::* ProcessGroundEffective)(int par1, int par2, bool par3);
		void (CCharacter::* ProcessCheckEffective)(int index, EFFECTIVE_INFO* info);
		void (CCharacter::* SetOnShowEFST)(int value);

		void (CCharacter::* SetOffShowEFST)(int value);
		void (CCharacter::* OnChangeStatusAmount)(int in_SKLevel, unsigned short in_EFST, unsigned long in_EFST_time, int in_EFST_value);
		void (CCharacter::* NotifyStatusAmount)(unsigned short type, int amount);
		char (CCharacter::* GetCampID)(void);
		void (CCharacter::* SetCampID)(char campID);
	};

	struct CHARACTER_PROPERTY_INFO
	{
	/* this+ 0 */ int bodyState; // @see enum eBodyState
	/* this+ 4 */ int healthState; // @see enum eHealthState
	/* this+ 8 */ int armor;
	/* this+12 */ int currentProperty;
	/* this+16 */ int attack;
	/* this+20 */ int effectState;
	};

	/* this+  0 */ public: //CClient baseclass_0;
	/* this+ 40 */ protected: CHARACTER_PROPERTY_INFO m_characterPInfo;
	/* this+ 64 */ protected: int m_type;
	/* this+ 68 */ protected: mystd::list<COMMAND_QUEUE> m_commandQueue;
	/* this+ 80 */ protected: CNeighborCache m_neighborCache;
	/* this+148 */ protected: CMapRes* m_mapRes;
	/* this+152 */ protected: mystd::vector<CCharacter*>* m_sectionList;
	/* this+156 */ protected: mystd::map<int,EFFECTIVE_INFO> m_effectiveList;
	/* this+168 */ protected: mystd::map<int,mystd::map<unsigned short,AmountValue> > m_statusEffInfo;
	/* this+180 */ protected: CCharBuff m_charBuff2;

	public: CCharacter::CCharacter(void);
	public: virtual CCharacter::~CCharacter(void);
	public: virtual int CCharacter::GetType(void);
	public: virtual void CCharacter::AddErrorCount(DWORD count, DWORD time);
	public: virtual void CCharacter::AddErrorCount(const char* filename, int line, DWORD count, DWORD time);
	public: virtual void CCharacter::Init(void);
	public: virtual int CCharacter::GetWeaponProperty(int position, int isArrowProperty);
	public: virtual bool CCharacter::IsActor(void);
	public: CMapRes* CCharacter::GetMapRes(void);
	public: virtual int CCharacter::IsItPossible(int property);
	public: virtual int CCharacter::IsSiegeMode(void);
	public: virtual unsigned long CCharacter::GetAccountID(void) = 0;
	public: virtual int CCharacter::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	public: virtual int CCharacter::GetParameterValue(unsigned short id, int& value);
	public: virtual int CCharacter::UpdateParameterValue(unsigned short id, int value);
	public: virtual void CCharacter::InsertCommand(COMMAND_QUEUE* command) = 0;
	public: virtual void CCharacter::CheckCommandQueue(void) = 0;
	public: virtual void CCharacter::DisableCommand(unsigned long commandID);
	public: virtual COMMAND_QUEUE* CCharacter::SearchCommand(unsigned long commandID);
	public: virtual int CCharacter::IsMyArea(CCharacter* ch, int range) = 0;
	public: virtual unsigned long CCharacter::GetState(void);
	public: virtual int CCharacter::GetScale(void);
	public: virtual int CCharacter::IsTarget(CCharacter* ch, unsigned long flag) = 0;
	public: virtual int CCharacter::IsDamageMotionPossible(void);
	public: virtual int CCharacter::IsRightProperty(int property);
	public: virtual int CCharacter::IsAvoidable(int race, int _class, int level);
	public: virtual int CCharacter::IsInitingState(void);
	public: virtual int CCharacter::IsLucky(void);
	public: virtual void CCharacter::OnShowEffect(int effect);
	public: virtual void CCharacter::OnShowEffect3(int effect, int numdata);
	public: void CCharacter::MultiCast(char* buf, int len);
	public: int CCharacter::IsDirectPath(CCharacter* ch, int isClose);
	public: virtual int CCharacter::GetEffectState(void);
	public: mystd::vector<CCharacter *>* CCharacter::GetSectionList(void);
	public: void CCharacter::SetSectionList(mystd::vector<CCharacter *>* sl);
	public: virtual void CCharacter::OnMsgFromItemServer(unsigned long in_loc, CITZMsg* flag);
	public: virtual void CCharacter::ReduceSPByUseSkill(int sp);
	public: virtual bool CCharacter::IsExistItem(int itemID, int count, bool isExternalEffect);
	public: virtual bool CCharacter::ConsumeItemByUseSkill(int itemID, int count, bool isExternalEffect);
	public: virtual short CCharacter::GetAttackSuccessPercent(CCharacter* other, int isRangeAttack);
	public: virtual int CCharacter::GetAttackFinalDamage(ATTACK_INFO* info);
	public: virtual int CCharacter::SkillAttack(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill);
	public: virtual short CCharacter::SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count);
	public: virtual int CCharacter::SplashAttack2(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc);
	public: virtual int CCharacter::SetHandicapState(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime);
	public: int CCharacter::GetCountInArea(int xPos, int yPos, int range, int isAffectPlayer, int isAffectTrap, int isDeadPlayer);
	public: virtual int CCharacter::GetModifiedTargetItemDEF(CCharacter* target);
	public: virtual int CCharacter::GetModifiedTargetItemMDEF(CCharacter* target);
	public: virtual int CCharacter::SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient);
	public: virtual int CCharacter::GetEffective(int index, int enumVal);
	public: virtual void CCharacter::UpdateEffective(int index, int val, int enumVal);
	public: virtual void CCharacter::ResetEffective(int index, int val);
	public: virtual bool CCharacter::IsEnableSetEffective(int index, int time, int val);
	public: void CCharacter::UpdateEffectiveTime(int index, int time);
	public: EFFECTIVE_INFO* CCharacter::GetEffectiveInfo(int index);
	public: void CCharacter::ProcessAllEffective(void);
	public: virtual bool CCharacter::IsGroundEffective(int index, int& SKID, bool& isPlaySolo);
	public: virtual void CCharacter::ProcessGroundEffective(int par1, int par2, bool par3);
	public: virtual void CCharacter::ProcessCheckEffective(int index, EFFECTIVE_INFO* info);
	public: virtual void CCharacter::SetOnShowEFST(int value);
	public: virtual void CCharacter::SetOffShowEFST(int value);
	public: void CCharacter::GetModifiedHealAmount(int& healAmount);
	public: virtual void CCharacter::OnChangeStatusAmount(int in_SKLevel, unsigned short in_EFST, unsigned long in_EFST_time, int in_EFST_value);
	public: virtual void CCharacter::NotifyStatusAmount(unsigned short type, int amount);
	public: void CCharacter::ResetStatusAmount(unsigned short SKID, unsigned short type);
	public: void CCharacter::ProcessStatusAmount(void);
	public: void CCharacter::GetPushedPosition(PosInfo src, PosInfo dest, int distance, PosInfo& result);
	public: CCharBuff& CCharacter::InstanceCharBuff(void);
	public: bool CCharacter::IsBattleFieldMode(void);
	public: virtual char CCharacter::GetCampID(void);
	public: virtual void CCharacter::SetCampID(char campID);
	public: bool CCharacter::IsTargetInBattleField(CCharacter* ch, unsigned long flag, int& result);

private:
	static hook_method<int (CCharacter::*)(void)> CCharacter::_GetType;
	static hook_method<void (CCharacter::*)(const char* filename, int line, unsigned long count, unsigned long time)> CCharacter::_AddErrorCount;
	static hook_method<void (CCharacter::*)(unsigned long count, unsigned long time)> CCharacter::_AddErrorCount2;
	static hook_method<void (CCharacter::*)(void)> CCharacter::_Init;
	static hook_method<int (CCharacter::*)(int position, int isArrowProperty)> CCharacter::_GetWeaponProperty;
	static hook_method<bool (CCharacter::*)(void)> CCharacter::_IsActor;
	static hook_method<CMapRes* (CCharacter::*)(void)> CCharacter::_GetMapRes;
	static hook_method<int (CCharacter::*)(int property)> CCharacter::_IsItPossible;
	static hook_method<int (CCharacter::*)(void)> CCharacter::_IsSiegeMode;
	static hook_method<int (CCharacter::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CCharacter::_OnMsg;
	static hook_method<int (CCharacter::*)(unsigned short id, int& value)> CCharacter::_GetParameterValue;
	static hook_method<int (CCharacter::*)(unsigned short id, int value)> CCharacter::_UpdateParameterValue;
	static hook_method<void (CCharacter::*)(unsigned long commandID)> CCharacter::_DisableCommand;
	static hook_method<COMMAND_QUEUE* (CCharacter::*)(unsigned long commandID)> CCharacter::_SearchCommand;
	static hook_method<unsigned long (CCharacter::*)(void)> CCharacter::_GetState;
	static hook_method<int (CCharacter::*)(void)> CCharacter::_GetScale;
	static hook_method<int (CCharacter::*)(void)> CCharacter::_IsDamageMotionPossible;
	static hook_method<int (CCharacter::*)(int property)> CCharacter::_IsRightProperty;
	static hook_method<int (CCharacter::*)(int race, int _class, int level)> CCharacter::_IsAvoidable;
	static hook_method<int (CCharacter::*)(void)> CCharacter::_IsInitingState;
	static hook_method<int (CCharacter::*)(void)> CCharacter::_IsLucky;
	static hook_method<void (CCharacter::*)(int effect)> CCharacter::_OnShowEffect;
	static hook_method<void (CCharacter::*)(int effect, int numdata)> CCharacter::_OnShowEffect3;
	static hook_method<void (CCharacter::*)(char* buf, int len)> CCharacter::_MultiCast;
	static hook_method<int (CCharacter::*)(CCharacter* ch, int isClose)> CCharacter::_IsDirectPath;
	static hook_method<int (CCharacter::*)(void)> CCharacter::_GetEffectState;
	static hook_method<mystd::vector<CCharacter *>* (CCharacter::*)(void)> CCharacter::_GetSectionList;
	static hook_method<void (CCharacter::*)(mystd::vector<CCharacter *>* sl)> CCharacter::_SetSectionList;
	static hook_method<void (CCharacter::*)(unsigned long in_loc, CITZMsg* flag)> CCharacter::_OnMsgFromItemServer;
	static hook_method<void (CCharacter::*)(int campID)> CCharacter::_ReduceSPByUseSkill;
	static hook_method<bool (CCharacter::*)(int itemID, int count, bool isExternalEffect)> CCharacter::_IsExistItem;
	static hook_method<bool (CCharacter::*)(int itemID, int count, bool isExternalEffect)> CCharacter::_ConsumeItemByUseSkill;
	static hook_method<short (CCharacter::*)(CCharacter* other, int isRangeAttack)> CCharacter::_GetAttackSuccessPercent;
	static hook_method<int (CCharacter::*)(ATTACK_INFO* info)> CCharacter::_GetAttackFinalDamage;
	static hook_method<int (CCharacter::*)(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill)> CCharacter::_SkillAttack;
	static hook_method<short (CCharacter::*)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count)> CCharacter::_SplashAttack;
	static hook_method<int (CCharacter::*)(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc)> CCharacter::_SplashAttack2;
	static hook_method<int (CCharacter::*)(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime)> CCharacter::_SetHandicapState;
	static hook_method<int (CCharacter::*)(int xPos, int yPos, int range, int isAffectPlayer, int isAffectTrap, int isDeadPlayer)> CCharacter::_GetCountInArea;
	static hook_method<int (CCharacter::*)(CCharacter* target)> CCharacter::_GetModifiedTargetItemDEF;
	static hook_method<int (CCharacter::*)(CCharacter* target)> CCharacter::_GetModifiedTargetItemMDEF;
	static hook_method<int (CCharacter::*)(int index, int time, int val1, int val2, int val3, int isSendClient)> CCharacter::_SetEffective;
	static hook_method<int (CCharacter::*)(int index, int enumVal)> CCharacter::_GetEffective;
	static hook_method<void (CCharacter::*)(int index, int val, int enumVal)> CCharacter::_UpdateEffective;
	static hook_method<void (CCharacter::*)(int index, int val)> CCharacter::_ResetEffective;
	static hook_method<bool (CCharacter::*)(int index, int time, int val)> CCharacter::_IsEnableSetEffective;
	static hook_method<void (CCharacter::*)(int index, int time)> CCharacter::_UpdateEffectiveTime;
	static hook_method<EFFECTIVE_INFO* (CCharacter::*)(int index)> CCharacter::_GetEffectiveInfo;
	static hook_method<void (CCharacter::*)(void)> CCharacter::_ProcessAllEffective;
	static hook_method<bool (CCharacter::*)(int index, int& SKID, bool& isPlaySolo)> CCharacter::_IsGroundEffective;
	static hook_method<void (CCharacter::*)(int par1, int par2, bool par3)> CCharacter::_ProcessGroundEffective;
	static hook_method<void (CCharacter::*)(int index, EFFECTIVE_INFO* info)> CCharacter::_ProcessCheckEffective;
	static hook_method<void (CCharacter::*)(int value)> CCharacter::_SetOnShowEFST;
	static hook_method<void (CCharacter::*)(int value)> CCharacter::_SetOffShowEFST;
	static hook_method<void (CCharacter::*)(int& healAmount)> CCharacter::_GetModifiedHealAmount;
	static hook_method<void (CCharacter::*)(int in_SKLevel, unsigned short in_EFST, unsigned long in_EFST_time, int in_EFST_value)> CCharacter::_OnChangeStatusAmount;
	static hook_method<void (CCharacter::*)(unsigned short type, int amount)> CCharacter::_NotifyStatusAmount;
	static hook_method<void (CCharacter::*)(unsigned short SKID, unsigned short type)> CCharacter::_ResetStatusAmount;
	static hook_method<void (CCharacter::*)(void)> CCharacter::_ProcessStatusAmount;
	static hook_method<void (CCharacter::*)(PosInfo src, PosInfo dest, int distance, PosInfo& result)> CCharacter::_GetPushedPosition;
	static hook_method<CCharBuff& (CCharacter::*)(void)> CCharacter::_InstanceCharBuff;
	static hook_method<bool (CCharacter::*)(void)> CCharacter::_IsBattleFieldMode;
	static hook_method<char (CCharacter::*)(void)> CCharacter::_GetCampID;
	static hook_method<void (CCharacter::*)(char campID)> CCharacter::_SetCampID;
	static hook_method<bool (CCharacter::*)(CCharacter* ch, unsigned long flag, int& result)> CCharacter::_IsTargetInBattleField;
};
