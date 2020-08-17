#pragma once
#include "GameActor.h"
#include "3dLib/Prim.h"
class C3dActor;
class CRagEffect;
class CTexture;


class CSkill : public CGameActor
{
public:
	CSkill();
	virtual ~CSkill();
	void OnInit();
	void OnExit();
	virtual void Render(matrix& vtm);
	virtual bool OnProcess();
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual void SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
	unsigned long GetAID();

protected:
	char* CSkill::GetTrapModelName();
	void CSkill::ShowModel(char* modelName);
	void CSkill::HideModel();
	void SetAID(unsigned long aid);

private:
	/* this+  0 */ //CGameActor baseclass_0;
	/* this+684 */ unsigned long m_launchCnt;
	/* this+688 */ unsigned long m_aid;
	/* this+692 */ C3dActor* m_3dactor;
	/* this+696 */ CRagEffect* m_LoopEffect;
	/* this+700 */ int m_effectId;

private:
	static hook_func<void (CSkill::*)(matrix& vtm)> CSkill::_Render;
	static hook_func<bool (CSkill::*)()> CSkill::_OnProcess;
	static hook_func<void (CSkill::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CSkill::_SendMsg;
	static hook_func<void (CSkill::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CSkill::_SetRenderInfo;
};


class CGraffiSkill : public CSkill
{
public:
	CGraffiSkill();
	virtual ~CGraffiSkill();
	virtual void OnInit(); // vfn40
	virtual void OnExit(); // vfn41
	virtual void Render(matrix& vtm);
	virtual bool OnProcess();
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);

private:
	/* this+  0 */ //CSkill baseclass_0;
	/* this+704 */ int m_master_gid;
	/* this+708 */ int m_ground_pos_x;
	/* this+712 */ int m_ground_pos_y;
	/* this+716 */ int m_lastingTime;
	/* this+720 */ CTexture* m_tex;
	/* this+724 */ CTexture* m_fontTex;
	/* this+728 */ char m_strMsg[256];
	/* this+984 */ int m_offsX;
	/* this+988 */ int m_offsY;
	/* this+992 */ float m_rot;

private:
	static hook_func<void (CGraffiSkill::*)()> CGraffiSkill::_OnInit;
	static hook_func<void (CGraffiSkill::*)(matrix& vtm)> CGraffiSkill::_Render;
};


class CMsgEffect : public CAbleToMakeEffect
{
	/* this+  0 */ public: //CAbleToMakeEffect baseclass_0;
	/* this+236 */ protected: CGameActor* m_masterActor;
	/* this+240 */ protected: vector3d m_destPos;
	/* this+252 */ protected: vector3d m_targetPos;
	/* this+264 */ protected: vector3d m_destPos2;
	/* this+276 */ protected: unsigned long m_masterGid;
	/* this+280 */ protected: int m_isDisappear;
	/* this+284 */ protected: float m_dist;
	/* this+288 */ protected: float m_orgPosY;
	/* this+292 */ protected: float m_orgPosX;
	/* this+296 */ protected: float m_orgZoom;
	/* this+300 */ protected: float m_moveDist;
	/* this+304 */ protected: int m_stateCnt;
	/* this+308 */ protected: int m_oldAction;
	/* this+312 */ protected: int m_msgEffectType;
	/* this+316 */ protected: int m_orgSprShift;
	/* this+320 */ protected: int m_isAttackTarget;
	/* this+324 */ protected: int m_isAnimation;

	public: CMsgEffect::CMsgEffect(void);
	public: CMsgEffect::~CMsgEffect(void);
	//public: void CMsgEffect::OnInit(void);
	//public: void CMsgEffect::OnExit(void);
	//public: unsigned char CMsgEffect::OnProcess(void);
	//public: void CMsgEffect::SendMsg(CGameObject*, int, int, int, int);
	//public: void CMsgEffect::ProcessPosition(void);
	public: int GetMsgEffectType(void);
};


class CMandraAttackEffect : public CRenderObject
{
	struct vtable_t
	{
		void* (CMandraAttackEffect::* scalar_deleting_destructor)(unsigned int flags);
		bool (CMandraAttackEffect::* OnProcess)(void);
		void (CMandraAttackEffect::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CRenderObject::* Render)(matrix& ptm);
		int (CGameObject::* Get8Dir)(float rot);
		void (CRenderObject::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CRenderObject::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
	};

	/* this+  0 */ public: //CRenderObject baseclass_0;
	/* this+204 */ public: float m_hideTime;

	public: CMandraAttackEffect::CMandraAttackEffect(void);
	public: virtual CMandraAttackEffect::~CMandraAttackEffect(void);
	public: void CMandraAttackEffect::OnInit(void);
	public: void CMandraAttackEffect::OnExit(void);
	public: virtual bool CMandraAttackEffect::OnProcess(void);

private:
	static hook_method<void (CMandraAttackEffect::*)(void)> CMandraAttackEffect::_OnInit;
	static hook_method<void (CMandraAttackEffect::*)(void)> CMandraAttackEffect::_OnExit;
	static hook_method<bool (CMandraAttackEffect::*)(void)> CMandraAttackEffect::_OnProcess;
};
