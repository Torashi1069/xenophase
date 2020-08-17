#pragma once
#include "GameActor.h"


class CNpc : public CGameActor
{
	struct vtable_t
	{
		void* (CNpc::* scalar_deleting_destructor)(unsigned int flags);
		bool (CNpc::* OnProcess)(void);
		void (CNpc::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CNpc::* Render)(matrix& ptm);
		int (CGameActor::* Get8Dir)(float rot);
		void (CGameActor::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CGameActor::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
		void (CGameActor::* ProcessState)(void);

		void (CNpc::* SetState)(int stateId);
		void (CNpc::* RegisterPos)(void);
		void (CNpc::* UnRegisterPos)(void);
		void (CNpc::* SetSprAct)(int job, int sex);
		void (CGameActor::* SetSprAct_)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal);
		void (CGameActor::* SetSprAct2)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState);
		void (CNpc::* SetSprJob)(int job);
		void (CNpc::* SetSprHead)(int head);
		void (CNpc::* SetSprJobDye)(int job);
		void (CNpc::* SetSprWeapon)(int weapon);

		void (CGameActor::* SetSprWeapon2)(int weapon);
		void (CNpc::* SetSprAccessory)(int accessory);
		void (CGameActor::* SetSprAccessory2)(int accessory);
		void (CGameActor::* SetSprAccessory3)(int accessory);
		void (CGameActor::* SetSprShield)(int shield);
		void (CGameActor::* SetSprShoe)(int shoe);
		void (CNpc::* SetImfFileName)(void);
		void (CGameActor::* SetHeadPaletteName)(void);
		void (CGameActor::* SetBodyPaletteName)(void);
		void (CGameActor::* SetBodyPalette)(int bodyPalette);

		void (CGameActor::* SetHeadPalette)(int headPalette);
		int (CGameActor::* GetWeapon)(void);
		void (CGameActor::* ProcessMotionWithDist)(void);
		int (CGameActor::* GetAttackMotion)(void);
		void (CGameActor::* MakeCorpse)(void);
		void (CGameActor::* SetModifyFactorOfmotionSpeed)(int attackM);
		void (CGameActor::* SetHonor)(int honor);
		void (CGameActor::* SetPropensityInfo)(int honor, int virtue);
		void (CGameActor::* SetGuildInfo)(int gdid, int emblemVersion);
		int (CGameActor::* GetGdid)(void);

		int (CGameActor::* GetEmblemVersion)(void);
	};

	/* this+  0 */ public: //CGameActor baseclass_0;
	/* this+684 */ public: float m_x1;
	/* this+688 */ public: float m_z1;
	/* this+692 */ public: float m_x2;
	/* this+696 */ public: float m_z2;
	/* this+700 */ public: int m_playerIswithinBox;
	/* this+704 */ public: unsigned long m_lastEffectLaunchTick;
	/* this+708 */ public: int m_doesLaunchEffect;

	public: CNpc::CNpc(void);
	public: virtual CNpc::~CNpc(void);
	public: void CNpc::OnInit(void);
	public: void CNpc::OnExit(void);
	public: void CNpc::ProcessContact(void);
	public: void CNpc::ProcessLaunchEffect(void);
	public: virtual void CNpc::Render(matrix& ptm);
	public: virtual bool CNpc::OnProcess(void);
	public: virtual void CNpc::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	public: virtual void CNpc::SetState(int stateId);
	public: virtual void CNpc::RegisterPos(void);
	public: virtual void CNpc::UnRegisterPos(void);
	public: virtual void CNpc::SetSprAct(int job, int sex);
	public: virtual void CNpc::SetSprJob(int job);
	public: virtual void CNpc::SetSprHead(int head);
	public: virtual void CNpc::SetSprJobDye(int job);
	public: virtual void CNpc::SetSprWeapon(int weapon);
	public: virtual void CNpc::SetSprAccessory(int accessory);
	public: virtual void CNpc::SetImfFileName(void);

private:
	static hook_method<void (CNpc::*)(void)> CNpc::_OnInit;
	static hook_method<void (CNpc::*)(void)> CNpc::_OnExit;
	static hook_method<void (CNpc::*)(void)> CNpc::_ProcessContact;
	static hook_method<void (CNpc::*)(void)> CNpc::_ProcessLaunchEffect;
	static hook_method<void (CNpc::*)(matrix& ptm)> CNpc::_Render;
	static hook_method<bool (CNpc::*)(void)> CNpc::_OnProcess;
	static hook_method<void (CNpc::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CNpc::_SendMsg;
	static hook_method<void (CNpc::*)(int stateId)> CNpc::_SetState;
	static hook_method<void (CNpc::*)(void)> CNpc::_RegisterPos;
	static hook_method<void (CNpc::*)(void)> CNpc::_UnRegisterPos;
	static hook_method<void (CNpc::*)(int job, int sex)> CNpc::_SetSprAct;
	static hook_method<void (CNpc::*)(int job)> CNpc::_SetSprJob;
	static hook_method<void (CNpc::*)(int head)> CNpc::_SetSprHead;
	static hook_method<void (CNpc::*)(int job)> CNpc::_SetSprJobDye;
	static hook_method<void (CNpc::*)(int weapon)> CNpc::_SetSprWeapon;
	static hook_method<void (CNpc::*)(int accessory)> CNpc::_SetSprAccessory;
	static hook_method<void (CNpc::*)(void)> CNpc::_SetImfFileName;
};


class CBlowEffect : public CRenderObject
{
	struct vtable_t
	{
		void* (CBlowEffect::* scalar_deleting_destructor)(unsigned int flags);
		bool (CBlowEffect::* OnProcess)(void);
		void (CBlowEffect::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CRenderObject::* Render)(matrix& ptm);
		int (CGameObject::* Get8Dir)(float rot);
		void (CRenderObject::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CRenderObject::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
	};

	/* this+  0 */ public: //CRenderObject baseclass_0;

	public: CBlowEffect::CBlowEffect(void);
	public: virtual CBlowEffect::~CBlowEffect(void);
	public: void CBlowEffect::OnInit(void);
	public: void CBlowEffect::OnExit(void);
	public: virtual bool CBlowEffect::OnProcess(void);
	public: virtual void CBlowEffect::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);

private:
	static hook_method<void (CBlowEffect::*)(void)> CBlowEffect::_OnInit;
	static hook_method<void (CBlowEffect::*)(void)> CBlowEffect::_OnExit;
	static hook_method<bool (CBlowEffect::*)(void)> CBlowEffect::_OnProcess;
	static hook_method<void (CBlowEffect::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CBlowEffect::_SendMsg;
};


class CCorpse : public CRenderObject
{
	struct vtable_t
	{
		void* (CCorpse::* scalar_deleting_destructor)(unsigned int flags);
		bool (CCorpse::* OnProcess)(void);
		void (CCorpse::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CRenderObject::* Render)(matrix& ptm);
		int (CGameObject::* Get8Dir)(float rot);
		void (CRenderObject::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CRenderObject::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
	};

	/* this+  0 */ public: //CRenderObject baseclass_0;

	public: CCorpse::CCorpse(void);
	public: virtual CCorpse::~CCorpse(void);
	public: void CCorpse::OnInit(void);
	public: void CCorpse::OnExit(void);
	public: virtual bool CCorpse::OnProcess(void);
	public: virtual void CCorpse::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);

private:
	static hook_method<void (CCorpse::*)(void)> CCorpse::_OnInit;
	static hook_method<void (CCorpse::*)(void)> CCorpse::_OnExit;
	static hook_method<bool (CCorpse::*)(void)> CCorpse::_OnProcess;
	static hook_method<void (CCorpse::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CCorpse::_SendMsg;
};


class CMasterChaser : public CRenderObject
{
	struct vtable_t
	{
		void* (CMasterChaser::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRenderObject::* OnProcess)(void);
		void (CRenderObject::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CRenderObject::* Render)(matrix& ptm);
		int (CGameObject::* Get8Dir)(float rot);
		void (CRenderObject::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CRenderObject::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
	};

	/* this+  0 */ public: //CRenderObject baseclass_0;
	/* this+204 */ CGameActor* m_pursuedMaster;

	public: CMasterChaser::CMasterChaser(void);
	public: virtual CMasterChaser::~CMasterChaser(void);
	public: void CMasterChaser::OnInit(void);
	public: void CMasterChaser::OnExit(void);

private:
	static hook_method<void (CMasterChaser::*)(void)> CMasterChaser::_OnInit;
	static hook_method<void (CMasterChaser::*)(void)> CMasterChaser::_OnExit;
};


class CNumEffect : public CRenderObject
{
	struct vtable_t
	{
		void* (CNumEffect::* scalar_deleting_destructor)(unsigned int flags);
		bool (CNumEffect::* OnProcess)(void);
		void (CNumEffect::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CRenderObject::* Render)(matrix& ptm);
		int (CGameObject::* Get8Dir)(float rot);
		void (CRenderObject::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CRenderObject::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
	};
	
	/* this+  0 */ public: //CRenderObject baseclass_0;
	/* this+204 */ protected: float m_orgPosY;
	/* this+208 */ protected: float m_orgZoom;

	public: CNumEffect::CNumEffect(void);
	public: virtual CNumEffect::~CNumEffect(void);
	public: void CNumEffect::OnInit(void);
	public: void CNumEffect::OnExit(void);
	public: virtual bool CNumEffect::OnProcess(void);
	public: virtual void CNumEffect::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);

private:
	static hook_method<void (CNumEffect::*)(void)> CNumEffect::_OnInit;
	static hook_method<void (CNumEffect::*)(void)> CNumEffect::_OnExit;
	static hook_method<bool (CNumEffect::*)(void)> CNumEffect::_OnProcess;
	static hook_method<void (CNumEffect::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CNumEffect::_SendMsg;
};


class CSoundMaker : public CRenderObject
{
	struct vtable_t
	{
		void* (CSoundMaker::* scalar_deleting_destructor)(unsigned int flags);
		bool (CSoundMaker::* OnProcess)(void);
		void (CSoundMaker::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CSoundMaker::* Render)(matrix& vtm);
		int (CGameObject::* Get8Dir)(float rot);
		void (CRenderObject::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CRenderObject::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
	};

	/* this+  0 */ public: //CRenderObject baseclass_0;
	/* this+204 */ private: mystd::string m_waveName;
	/* this+220 */ private: float m_vol;
	/* this+224 */ private: int m_width;
	/* this+228 */ private: int m_height;
	/* this+232 */ private: float m_range;
	/* this+236 */ private: float m_diagonal;
	/* this+240 */ private: unsigned long m_lastPlayTime;
	/* this+244 */ private: unsigned long m_cycle;

	public: CSoundMaker::CSoundMaker(void);
	public: virtual CSoundMaker::~CSoundMaker(void);
	public: void CSoundMaker::OnInit(void);
	public: void CSoundMaker::OnExit(void);
	public: virtual void CSoundMaker::Render(matrix& vtm);
	public: virtual bool CSoundMaker::OnProcess(void);
	public: virtual void CSoundMaker::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);

private:
	static hook_method<void (CSoundMaker::*)(void)> CSoundMaker::_OnInit;
	static hook_method<void (CSoundMaker::*)(void)> CSoundMaker::_OnExit;
	static hook_method<void (CSoundMaker::*)(matrix& vtm)> CSoundMaker::_Render;
	static hook_method<bool (CSoundMaker::*)(void)> CSoundMaker::_OnProcess;
	static hook_method<void (CSoundMaker::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CSoundMaker::_SendMsg;
};
