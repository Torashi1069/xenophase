#pragma once
#include "Enum.h"
#include "Pc.h"
class CGameObject;
class CRagEffect;


class CPlayer : public CPc
{
	struct vtable_t
	{
		void* (CPlayer::* scalar_deleting_destructor)(unsigned int flags);
		bool (CPlayer::* OnProcess)(void);
		void (CPlayer::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CPc::* Render)(matrix& ptm);
		int (CGameActor::* Get8Dir)(float rot);
		void (CGameActor::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CGameActor::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
		void (CPlayer::* ProcessState)(void);

		void (CPlayer::* SetState)(int stateId);
		void (CPlayer::* RegisterPos)(void);
		void (CPlayer::* UnRegisterPos)(void);
		void (CGameActor::* SetSprAct)(int job, int sex);
		void (CPc::* SetSprAct_)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal);
		void (CPc::* SetSprAct2)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState);
		void (CPc::* SetSprJob)(int job);
		void (CPc::* SetSprHead)(int head);
		void (CPc::* SetSprJobDye)(int job);
		void (CPc::* SetSprWeapon)(int weapon);

		void (CPc::* SetSprWeapon2)(int weapon);
		void (CPc::* SetSprAccessory)(int accessory);
		void (CPc::* SetSprAccessory2)(int accessory);
		void (CPc::* SetSprAccessory3)(int accessory);
		void (CPc::* SetSprShield)(int shield);
		void (CPc::* SetSprShoe)(int shoe);
		void (CPc::* SetImfFileName)(void);
		void (CPc::* SetHeadPaletteName)(void);
		void (CPc::* SetBodyPaletteName)(void);
		void (CPc::* SetBodyPalette)(int bodyPalette);

		void (CPc::* SetHeadPalette)(int headPalette);
		int (CPc::* GetWeapon)(void);
		void (CGameActor::* ProcessMotionWithDist)(void);
		int (CGameActor::* GetAttackMotion)(void);
		void (CGameActor::* MakeCorpse)(void);
		void (CPc::* SetModifyFactorOfmotionSpeed)(int attackM);
		void (CPc::* SetHonor)(int honor);
		void (CPc::* SetPropensityInfo)(int honor, int virtue);
		void (CGameActor::* SetGuildInfo)(int gdid, int emblemVersion);
		int (CGameActor::* GetGdid)(void);

		int (CGameActor::* GetEmblemVersion)(void);
	};

	/* this+0     */ public: //CPc baseclass_0;
	/* this+0x338 */ public: int m_destCellX;
	/* this+0x33C */ public: int m_destCellZ;
	/* this+0x340 */ public: unsigned long m_attackReqTime;
	/* this+0x344 */ public: unsigned long m_preMoveStartTick;
	/* this+0x348 */ public: PROCEEDTYPE m_proceedType;
	/* this+0x34C */ public: int m_preMoveOn;
	/* this+0x350 */ public: int m_attackMode;
	/* this+0x354 */ public: int m_isAttackRequest;
	/* this+0x358 */ public: int m_isWaitingMoveAck;
	/* this+0x35C */ public: int m_isPreengageStateOfMove;
	/* this+0x360 */ public: unsigned long m_proceedTargetGid;
	/* this+0x364 */ public: unsigned long m_totalAttackReqCnt;
	/* this+0x368 */ public: unsigned long m_tickOfMoveForAttack;
	/* this+0x36C */ public: unsigned long m_moveReqTick;
	/* this+0x370 */ public: unsigned long m_standTick;
	/* this+0x374 */ public: int m_skillId;
	/* this+0x378 */ public: int m_skillAttackRange;
	/* this+0x37C */ public: int m_skillUseLevel;
	/* this+0x380 */ public: int m_gSkillDx;
	/* this+0x384 */ public: int m_gSkillDy;
	/* this+0x388 */ public: int m_preengageXOfMove;
	/* this+0x38C */ public: int m_preengageYOfMove;
	/* this+0x390 */ public: CRagEffect* m_statusEffect;

	public: CPlayer::CPlayer(void);
	public: virtual CPlayer::~CPlayer(void);
	public: void CPlayer::OnInit(void);
	public: void CPlayer::OnExit(void);
	public: virtual bool CPlayer::OnProcess(void);
	public: virtual bool CPlayer::ProcessState(void);
	public: virtual void CPlayer::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	public: virtual void CPlayer::SetState(int stateId);
	public: virtual void CPlayer::RegisterPos(void);
	public: virtual void CPlayer::UnRegisterPos(void);
	public: void CPlayer::ProcessProceed(void);
	public: void CPlayer::ProcessPreengageMove(void);
	public: void CPlayer::ReLaunchBlurEffects(void);

private:
	static hook_method<void (CPlayer::*)(void)> CPlayer::_OnInit;
	static hook_method<void (CPlayer::*)(void)> CPlayer::_OnExit;
	static hook_method<bool (CPlayer::*)(void)> CPlayer::_OnProcess;
	static hook_method<bool (CPlayer::*)(void)> CPlayer::_ProcessState;
	static hook_method<void (CPlayer::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CPlayer::_SendMsg;
	static hook_method<void (CPlayer::*)(int stateId)> CPlayer::_SetState;
	static hook_method<void (CPlayer::*)(void)> CPlayer::_RegisterPos;
	static hook_method<void (CPlayer::*)(void)> CPlayer::_UnRegisterPos;
	static hook_method<void (CPlayer::*)(void)> CPlayer::_ProcessProceed;
	static hook_method<void (CPlayer::*)(void)> CPlayer::_ProcessPreengageMove;
	static hook_method<void (CPlayer::*)(void)> CPlayer::_ReLaunchBlurEffects;
};
