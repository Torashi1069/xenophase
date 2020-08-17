#pragma once
#include "Character.h"
#include "struct.hpp"
class CMapRes;


class CSkill : public CCharacter
{
	struct vtable_t // const CSkill::`vftable'
	{
		void* (CSkill::* scalar_deleting_destructor)(unsigned int __flags);
		int (CCharacter::* GetType)(void);
		void (CCharacter::* AddErrorCount)(const char*, int, unsigned long, unsigned long);
		void (CCharacter::* AddErrorCount2)(unsigned long, unsigned long);
		void (CCharacter::* Init)(void);
		int (CCharacter::* GetWeaponProperty)(int, int);
		bool (CCharacter::* IsActor)(void);
		int (CCharacter::* IsItPossible)(int);
		int (CCharacter::* IsSiegeMode)(void);
		unsigned long (CSkill::* GetAccountID)(void);

		int (CSkill::* OnMsg)(CCharacter*, CCharacter*, unsigned long, int, int, int, MSGpar::CVar);
		int (CSkill::* GetParameterValue)(unsigned short id, int& value);
		int (CSkill::* UpdateParameterValue)(unsigned short id, int value);
		void (CSkill::* InsertCommand)(COMMAND_QUEUE*);
		void (CSkill::* CheckCommandQueue)(void);
		void (CSkill::* DisableCommand)(unsigned long);
		COMMAND_QUEUE* (CCharacter::* SearchCommand)(unsigned long);
		int (CSkill::* IsMyArea)(CCharacter*, int);
		unsigned long (CSkill::* GetState)(void);
		int (CCharacter::* GetScale)(void);

		int (CSkill::* IsTarget)(CCharacter*, unsigned long);
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
		const char* (CSkill::* GetNamePtr)(void);
	};

public:
	/* this+  0 */ public: //CCharacter baseclass_0;
	/* this+232 */ private: char m_Name[24];
	/* this+256 */ private: unsigned long m_AID;
	/* this+260 */ private: int m_mapID;
	/* this+264 */ private: unsigned short m_SKID;
	/* this+266 */ private: unsigned short m_reactSKID;
	/* this+268 */ private: SKILL_INFO m_skillInfo;
	/* this+316 */ private: SKILL_TIME_INFO m_skillTimeInfo;
	/* this+320 */ private: int m_warpSize;
	/* this+324 */ private: int m_expiredCount;
	/* this+328 */ private: short m_warpXPos;
	/* this+330 */ private: short m_warpYPos;
	/* this+332 */ private: char m_warpMapName[16];
	/* this+348 */ private: int m_property;
	/* this+352 */ private: int m_trapState;
	/* this+356 */ private: CCharacter* m_master;
	/* this+360 */ private: unsigned long m_targetAID;
	/* this+364 */ private: char m_talkBoxContents[80];
	/* this+444 */ private: int m_fireWallIndex;
	/* this+448 */ private: int m_visible;
	/* this+452 */ private: unsigned int m_GroupUniqueID;

	public: CSkill::CSkill(void);
	public: virtual CSkill::~CSkill(void);
	public: virtual const char* CSkill::GetNamePtr(void);
	//public: void CSkill::ModifyDamage_ATKED(CCharacter *, int &, int, int, int, int);
	//public: void CSkill::ModifyDamage(int &, int, int, CCharacter *, unsigned short);
	//public: unsigned int CSkill::GetGroupUniqueID();
	public: void CSkill::Init2(const unsigned int in_GroupUniqueID, short x, short y, CMapRes* mapRes, unsigned char job, unsigned long creatorAID, unsigned long expiredTime, short level, unsigned short SKID, int par1, int par2);
	public: virtual int CSkill::IsTarget(CCharacter* ch, unsigned long flag);
	public: virtual unsigned long CSkill::GetState(void);
	public: int CSkill::OnProcess(void);
	public: void CSkill::CheckStateChange(void);
	public: virtual unsigned long CSkill::GetAccountID(void);
	//public: void CSkill::SetTargetAccountID(unsigned long);
	//public: unsigned long CSkill::GetTargetAccountID();
	public: void CSkill::SetAccountID(unsigned long AID);
	public: virtual int CSkill::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	public: virtual void CSkill::InsertCommand(COMMAND_QUEUE* command);
	public: virtual void CSkill::CheckCommandQueue(void);
	public: virtual void CSkill::DisableCommand(unsigned long commandID);
	public: virtual int CSkill::IsMyArea(CCharacter* ch, int range);
	//public: unsigned long CSkill::GetCreatorAID();
	//public: void CSkill::UpdateSkill(mystd::vector<CCharacter*> *);
	public: void CSkill::NotifyUpdateInfo(CPC* other);
	//public: void CSkill::NotifyUpdateSkillInfo();
	public: void CSkill::OnDisappear(void);
	//public: void CSkill::SetWarpMapName(char *);
	public: short CSkill::GetxPos(void);
	public: short CSkill::GetyPos(void);
	public: virtual int CSkill::GetParameterValue(unsigned short id, int& value);
	public: virtual int CSkill::UpdateParameterValue(unsigned short id, int value);
	public: unsigned short CSkill::GetSKID(void);
	public: void CSkill::SetSKID(unsigned short SKID);
	//public: void CSkill::SetWarpXPos(short);
	//public: void CSkill::SetWarpYPos(short);
	//public: void CSkill::SetExpireTime(unsigned short);
	//public: int CSkill::IsVisible();
	//public: int CSkill::GetSkillLevel();
	public: int CSkill::IsPossibleCreateSkill(const unsigned long in_AID, const unsigned short in_SKID, const int in_SKLevel, const short in_x, const short in_y, CMapRes* const in_cpMapRes, unsigned long& io_ExpiredTime);
	//public: int CSkill::GetCreatorXPos();
	//public: int CSkill::GetCreatorYPos();
	//public: void CSkill::SetTalkBoxcontents(char *);
	//public: char * CSkill::GetTalkBoxcontents();
	//public: void CSkill::SetTrapState(int);
	//public: int CSkill::GetTrapState();
	//public: int CSkill::IsTrap();
	//public: CCharacter* CSkill::GetMasterCharacter();
	//public: unsigned long CSkill::GetExpireTime();
	//public: static bool CSkill::IsIgnoreLANDPROTECTOR(unsigned short);
	//private: void CSkill::OnExpired();
	//private: void CSkill::InitThePCCacheInfo(int);
	//private: void CSkill::DispatchCommand(int);
	private: void CSkill::UpdateNeighborhood(void);
	private: void CSkill::ProcessNeighborhood(void);
	//private: void CSkill::ProcessCollision();
	//private: void CSkill::ProcessWarpPortal();

private:
	static hook_method<const char* (CSkill::*)(void)> CSkill::_GetNamePtr;
	static hook_method<void (CSkill::*)(const unsigned int in_GroupUniqueID, short x, short y, CMapRes* mapRes, unsigned char job, unsigned long creatorAID, unsigned long expiredTime, short level, unsigned short SKID, int par1, int par2)> CSkill::_Init2;
	static hook_method<int (CSkill::*)(CCharacter* ch, unsigned long flag)> CSkill::_IsTarget;
	static hook_method<unsigned long (CSkill::*)(void)> CSkill::_GetState;
	static hook_method<int (CSkill::*)(void)> CSkill::_OnProcess;
	static hook_method<void (CSkill::*)(void)> CSkill::_CheckStateChange;
	static hook_method<int (CSkill::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CSkill::_OnMsg;
	static hook_method<void (CSkill::*)(COMMAND_QUEUE* command)> CSkill::_InsertCommand;
	static hook_method<void (CSkill::*)(void)> CSkill::_CheckCommandQueue;
	static hook_method<void (CSkill::*)(unsigned long commandID)> CSkill::_DisableCommand;
	static hook_method<int (CSkill::*)(CCharacter* ch, int range)> CSkill::_IsMyArea;
	static hook_method<void (CSkill::*)(CPC* other)> CSkill::_NotifyUpdateInfo;
	static hook_method<void (CSkill::*)(void)> CSkill::_OnDisappear;
	static hook_method<short (CSkill::*)(void)> CSkill::_GetxPos;
	static hook_method<short (CSkill::*)(void)> CSkill::_GetyPos;
	static hook_method<int (CSkill::*)(unsigned short id, int& value)> CSkill::_GetParameterValue;
	static hook_method<int (CSkill::*)(unsigned short id, int value)> CSkill::_UpdateParameterValue;
	static hook_method<unsigned short (CSkill::*)(void)> CSkill::_GetSKID;
	static hook_method<void (CSkill::*)(unsigned short SKID)> CSkill::_SetSKID;
	static hook_method<int (CSkill::*)(const unsigned long in_AID, const unsigned short in_SKID, const int in_SKLevel, const short in_x, const short in_y, CMapRes* const in_cpMapRes, unsigned long& io_ExpiredTime)> CSkill::_IsPossibleCreateSkill;
	static hook_method<void (CSkill::*)(void)> CSkill::_UpdateNeighborhood;
	static hook_method<void (CSkill::*)(void)> CSkill::_ProcessNeighborhood;
};
