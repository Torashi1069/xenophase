#pragma once
#include "3dLib/Prim.h" // matrix
#include "Struct.h"
class CActRes;
class CSprRes;
class CRagEffect;
class CMercenaryAI;
class UIEmblemWnd;
class UIWordDisplayWnd;
struct _MSG2AI;
struct SprImg;


struct RPSprite
{
	/* this+ 0 */ float top;
	/* this+ 4 */ float left;
	/* this+ 8 */ float bottom;
	/* this+12 */ float right;
	/* this+16 */ float oow;
	/* this+20 */ float oowup;
	/* this+24 */ unsigned long rgba;
	/* this+28 */ float angle;
	/* this+32 */ int cacheTexNum;
	/* this+36 */ float u;
	/* this+40 */ float v;
	/* this+44 */ SprImg* spr;
};


struct RENDER_INFO_RECT
{
	/* this+ 0 */ float left;
	/* this+ 4 */ float top;
	/* this+ 8 */ float right;
	/* this+12 */ float bottom;
	/* this+16 */ float oow;

	public: void RENDER_INFO_RECT::SetInfo(float left, float top, float right, float bottom, float oow);
	public: void RENDER_INFO_RECT::Update(RPSprite& spr);

public:
	static hook_func<void (RENDER_INFO_RECT::*)(float left, float top, float right, float bottom, float oow)> RENDER_INFO_RECT::_SetInfo;
	static hook_func<void (RENDER_INFO_RECT::*)(RPSprite& spr)> RENDER_INFO_RECT::_Update;
};


class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();
	void OnInit();
	void OnExit();
	virtual bool OnProcess();
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual void Render(matrix& ptm);
	virtual int Get8Dir(float rot);
	int Get8Dir2(float rot, int isReal8Dir);
	int GetDir(float rot);
};


class CRenderObject : public CGameObject
{
	/* this+  0 */ public: //CGameObject baseclass_0;
	/* this+  4 */ public: vector3d m_pos;
	/* this+ 16 */ public: mystd::string m_bodyPaletteName;
	/* this+ 32 */ public: int m_baseAction;
	/* this+ 36 */ public: int m_curAction;
	/* this+ 40 */ public: int m_curMotion;
	/* this+ 44 */ public: int m_oldBaseAction;
	/* this+ 48 */ public: int m_oldMotion;
	/* this+ 52 */ public: int m_bodyPalette;
	/* this+ 56 */ public: float m_roty;
	/* this+ 60 */ public: float m_zoom;
	/* this+ 64 */ public: float m_shadowZoom;
	/* this+ 68 */ public: float m_motionSpeed;
	/* this+ 72 */ public: float m_lastPixelRatio;
	/* this+ 76 */ public: float m_loopCountOfmotionFinish;
	/* this+ 80 */ public: float m_modifyFactorOfmotionSpeed;
	/* this+ 84 */ public: float m_modifyFactorOfmotionSpeed2;
	/* this+ 88 */ public: int m_motionType;
	/* this+ 92 */ public: int m_stateId;
	/* this+ 96 */ public: int m_oldstateId;
	/* this+100 */ public: int m_sprShift;
	/* this+104 */ public: int m_sprAngle;
	/* this+108 */ public: int m_offsetOow;
	/* this+112 */ public: DWORD m_colorOfSingleColor;
	/* this+116 */ public: DWORD m_singleColorStartTick;
	/* this+120 */ public: DWORD m_stateStartTick;
	/* this+124 */ COLOR m_oldColor; //TODO
	/* this+128 */ COLOR m_curColor; //TODO
	/* this+132 */ COLOR m_sprColor; //TODO
	/* this+136 */ bool m_isLieOnGround;
	/* this+137 */ bool m_isMotionFinished;
	/* this+138 */ bool m_isMotionFreezed;
	/* this+139 */ bool m_isSingleColor;
	/* this+140 */ bool m_isVisible;
	/* this+141 */ bool m_isVisibleBody;
	/* this+142 */ bool m_alwaysTopLayer;
	/* this+143 */ bool m_isSprArgbFixed;
	/* this+144 */ bool m_shadowOn;
	/* this+145 */ bool m_shouldAddPickInfo;
	/* this+146 */ BYTE gap_146[2];
	/* this+148 */ int m_isPc;
	/* this+152 */ int m_lastTlvertX;
	/* this+156 */ int m_lastTlvertY;
	/* this+160 */ unsigned char m_forceAct;
	/* this+161 */ unsigned char m_forceMot;
	/* this+162 */ unsigned char m_forceAct2[5];
	/* this+167 */ unsigned char m_forceMot2[5];
	/* this+172 */ unsigned char m_forceMaxMot;
	/* this+173 */ unsigned char m_forceAnimSpeed;
	/* this+174 */ unsigned char m_forceFinishedAct;
	/* this+175 */ unsigned char m_forceFinishedMot;
	/* this+176 */ unsigned char m_forceStartMot;
	/* this+177 */ BYTE gap_177[3];
	/* this+180 */ int m_isForceState;
	/* this+184 */ int m_isForceAnimLoop;
	/* this+188 */ int m_isForceAnimation;
	/* this+192 */ int m_isForceAnimFinish;
	/* this+196 */ int m_isForceState2;
	/* this+200 */ int m_isForceState3;
	/* this+204 */ unsigned long m_forceStateCnt;
	/* this+208 */ unsigned long m_forceStateEndTick;
	/* this+212 */ int m_BodyLight;
	/* this+216 */ char m_BeZero;
	/* this+217 */ char m_BodyFlag;
	/* this+218 */ unsigned char m_BodySin;
	/* this+219 */ unsigned char m_BodySin2;
	/* this+220 */ unsigned char m_BodySin3;
	/* this+221 */ unsigned char m_BodySin4;
	/* this+222 */ unsigned char m_BodySin5;
	/* this+223 */ BYTE gap_223[1];
	/* this+224 */ short m_BodyTime;
	/* this+226 */ unsigned char m_BodyTime2;
	/* this+227 */ unsigned char m_BodyTime3;
	/* this+228 */ short m_FlyMove;
	/* this+230 */ unsigned char m_FlyNow;
	/* this+231 */ char m_camp;
	/* this+232 */ short m_charfont;
	/* this+234 */ unsigned char m_BodyAni;
	/* this+235 */ unsigned char m_BodyAct;
	/* this+236 */ unsigned char m_BodyAniFrame;
	/* this+237 */ BYTE gap_237[3];
	/* this+240 */ private: CSprRes* m_sprRes;
	/* this+244 */ private: CActRes* m_actRes;

	public: CRenderObject::CRenderObject(void);
	public: virtual CRenderObject::~CRenderObject(void);
	public: virtual bool CRenderObject::OnProcess(void);
	public: virtual void CRenderObject::Render(matrix& vtm);
	public: virtual void CRenderObject::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
	public: virtual void CRenderObject::SetTlvert(float tlvertX, float tlvertY);
	public: virtual void CRenderObject::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	public: virtual void CRenderObject::SetAction(int action, int speed, int type);
	public: virtual void CRenderObject::ProcessMotion(void);

	public: void CRenderObject::UpdateTlvertex(matrix& vtm);
	public: void CRenderObject::RenderBody(matrix& vtm, char FLAG1);
	public: void CRenderObject::RenderShadow(matrix& vtm, float zoom);
	public: void CRenderObject::RenderSprite(RPSprite& spr, unsigned long* pal, int renderFlag);
	public: void CRenderObject::SetArgb(int a, int r, int g, int b);
	public: void CRenderObject::SetLmIntensity(float& lmRIntensity, float& lmGIntensity, float& lmBIntensity);
	public: void CRenderObject::SetCharacterSquare(float* top, float* btm, float* left, float* right);
	public: void CRenderObject::SetCharacterAngle(float* angle);
	public: void CRenderObject::SetCharacterPreAngle(int layer, int* imfOffX, int* imfOffY, int* head_imfOffX, int* head_imfOffY);	
	public: void CRenderObject::SetCharacterLight(RPSprite spr, unsigned long* pal);
	public: void CRenderObject::SetCharacterPixelRatio(float* pixelRatio);
	public: short CRenderObject::SetCharacterFlying(void);
	public: void CRenderObject::SetActName(const char* actName);
	void SetForceAnimation(int act, int mot, int maxMot, int finishAct, int finishMot, int isAnim, DWORD endTick, int isLoop);
	void CalcDir(float x, float z);

public:
	static hook_func<CRenderObject* (CRenderObject::*)(void)> CRenderObject::_cCRenderObject;
	static hook_func<void (CRenderObject::*)(void)> CRenderObject::_dCRenderObject;
	static hook_func<bool (CRenderObject::*)(void)> CRenderObject::_OnProcess;
	static hook_func<void (CRenderObject::*)(matrix& vtm)> CRenderObject::_Render;
	static hook_func<void (CRenderObject::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CRenderObject::_SetRenderInfo;
	static hook_func<void (CRenderObject::*)(float tlvertX, float tlvertY)> CRenderObject::_SetTlvert;
	static hook_func<void (CRenderObject::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CRenderObject::_SendMsg;
	static hook_func<void (CRenderObject::*)(int action, int speed, int type)> CRenderObject::_SetAction;
	static hook_func<void (CRenderObject::*)(void)> CRenderObject::_ProcessMotion;
	static hook_func<void (CRenderObject::*)(matrix& vtm)> CRenderObject::_UpdateTlvertex;
	static hook_func<void (CRenderObject::*)(matrix& vtm, char FLAG1)> CRenderObject::_RenderBody;
	static hook_func<void (CRenderObject::*)(matrix& vtm, float zoom)> CRenderObject::_RenderShadow;
	static hook_func<void (CRenderObject::*)(RPSprite& spr, unsigned long* pal, int renderFlag)> CRenderObject::_RenderSprite;
	static hook_func<void (CRenderObject::*)(int a, int r, int g, int b)> CRenderObject::_SetArgb;
	static hook_func<void (CRenderObject::*)(float& lmRIntensity, float& lmGIntensity, float& lmBIntensity)> CRenderObject::_SetLmIntensity;
	static hook_func<void (CRenderObject::*)(float* top, float* btm, float* left, float* right)> CRenderObject::_SetCharacterSquare;
	static hook_func<void (CRenderObject::*)(float* angle)> CRenderObject::_SetCharacterAngle;
	static hook_func<void (CRenderObject::*)(int layer, int* imfOffX, int* imfOffY, int* head_imfOffX, int* head_imfOffY)> CRenderObject::_SetCharacterPreAngle;
	static hook_func<void (CRenderObject::*)(RPSprite spr, unsigned long* pal)> CRenderObject::_SetCharacterLight;
	static hook_func<void (CRenderObject::*)(float* pixelRatio)> CRenderObject::_SetCharacterPixelRatio;
	static hook_func<short (CRenderObject::*)(void)> CRenderObject::_SetCharacterFlying;
};
C_ASSERT( sizeof CRenderObject == 248 );


class CAbleToMakeEffect : public CRenderObject
{
public:
	CAbleToMakeEffect();
	CRagEffect* LaunchEffect(int effectId, vector3d fDeltaPos, float fRot);

public:
	/* this+  0 */ //CRenderObject baseclass_0;
	/* this+248 */ int m_efId;
	/* this+252 */ int m_Sk_Level;
	/* this+256 */ int m_isLoop;
private:
	/* this+260 */ mystd::list<CRagEffect*> m_effectList;
	/* this+272 */ CRagEffect* m_beginSpellEffect;
	/* this+276 */ CRagEffect* m_magicTargetEffect;

private:
	static hook_func<CAbleToMakeEffect* (CAbleToMakeEffect::*)()> CAbleToMakeEffect::_cCAbleToMakeEffect;
	static hook_func<CRagEffect* (CAbleToMakeEffect::*)(int effectId, vector3d fDeltaPos, float fRot)> CAbleToMakeEffect::_LaunchEffect;
};
C_ASSERT( sizeof CAbleToMakeEffect == 280 );


class CGameActor : public CAbleToMakeEffect
{
public:
	CGameActor::CGameActor();
	virtual CGameActor::~CGameActor();
	virtual bool CGameActor::OnProcess() = 0;
	virtual void CGameActor::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual int CGameActor::Get8Dir(float rot);
	virtual void CGameActor::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
	virtual void CGameActor::SetAction(int action, int speed, int type);
	virtual bool CGameActor::ProcessState();
	virtual void CGameActor::SetState(int stateId);
	virtual void CGameActor::RegisterPos();
	virtual void CGameActor::UnRegisterPos();
	virtual void CGameActor::SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal);
	virtual void CGameActor::SetSprAct(int job, int sex);
	virtual void CGameActor::SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState);
	virtual void CGameActor::SetSprJob(int job);
	virtual void CGameActor::SetSprHead(int head);
	virtual void CGameActor::SetSprJobDye(int job);
	virtual void CGameActor::SetSprWeapon(int weapon);
	virtual void CGameActor::SetSprWeapon2(int weapon);
	virtual void CGameActor::SetSprAccessory(int accessory);
	virtual void CGameActor::SetSprAccessory2(int accessory);
	virtual void CGameActor::SetSprAccessory3(int accessory);
	virtual void CGameActor::SetSprShield(int shield);
	virtual void CGameActor::SetSprShoe(int shoe);
	virtual void CGameActor::SetImfFileName();
	virtual void CGameActor::SetHeadPaletteName();
	virtual void CGameActor::SetBodyPaletteName();
	virtual void CGameActor::SetBodyPalette(int bodyPalette);
	virtual void CGameActor::SetHeadPalette(int headPalette);
	virtual int CGameActor::GetWeapon();
	virtual void CGameActor::ProcessMotionWithDist();
	virtual int CGameActor::GetAttackMotion();
	virtual void CGameActor::MakeCorpse();
	virtual void CGameActor::SetModifyFactorOfmotionSpeed(int attackMT);
	virtual void CGameActor::SetHonor(int honor);
	virtual void CGameActor::SetPropensityInfo(int honor, int virtue);
	virtual void CGameActor::SetGuildInfo(int gdid, int emblemVersion);
	virtual int CGameActor::GetGdid();
	virtual int CGameActor::GetEmblemVersion();
	virtual _MSG2AI& CGameActor::GetMsg2AI(int merType);
	virtual void CGameActor::SetMsg2AI(_MSG2AI& msg, int merType);
	virtual _MSG2AI& CGameActor::GetResMsg2AI(int merType);
	virtual void CGameActor::SetResMsg2AI(_MSG2AI& msg, int merType);

	void CGameActor::SetJob(int job);
	int CGameActor::GetJob();
	unsigned long CGameActor::GetGID();
	int CGameActor::GetTargetGid();
	void SetFreezeEndTick(DWORD tick);
	void SetMotionSpeed(float motionSpeed);

public:
	/* this+  0 */ //CAbleToMakeEffect baseclass_0;
	/* this+280 */ int m_moveDestX;
	/* this+284 */ int m_moveDestY;
	/* this+288 */ unsigned long m_speed;
	/* this+292 */ int m_isCounter;
	/* this+296 */ int m_isTrickDead;
	/* this+300 */ int m_isPlayHitWave;
	/* this+304 */ int m_isAsuraAttack;
	/* this+308 */ UIEmblemWnd* m_emblemWnd;
	/* this+312 */ UIWordDisplayWnd* m_WordDisplayWnd;
	/* this+316 */ char m_hitWaveName[128];
	/* this+444 */ BYTE dummy_444[8];
protected:
	/* this+452 */ BYTE dummy_452[68];
	/* this+520 */ unsigned long m_targetGid;
	/* this+524 */ BYTE dummy_524[4];
	/* this+528 */ int m_isBladeStop;
	/* this+532 */ unsigned long m_gid;
	/* this+536 */ int m_job;
	/* this+540 */ int m_sex;
	/* this+544 */ BYTE dummy_544[20];
	/* this+564 */ DWORD m_freezeEndTick;
	/* this+568 */ BYTE dummy_568[60];
	/* this+628 */ int m_willBeDead;
	/* this+632 */ int m_is99;
	/* this+636 */ char m_99;
	/* this+640 */ int m_bodyState;
	/* this+644 */ int m_effectState;
	/* this+648 */ int m_healthState;
	/* this+652 */ int m_pkState;
	/* this+656 */ float m_damageDestX;
	/* this+660 */ float m_damageDestZ;
	/* this+664 */ unsigned long m_effectLaunchCnt;
	/* this+668 */ unsigned long m_vanishTime;
	/* this+672 */ int m_actorType;
	/* this+676 */ int m_bIsMemberAndVisible;
	/* this+680 */ int m_gdid;
	/* this+684 */ int m_emblemVersion;
public:
	/* this+688 */ CMercenaryAI* m_homunAI;
	/* this+692 */ CMercenaryAI* m_merAI;
	/* this+696 */ unsigned char m_objectType;
	/* this+697 */ BYTE dummy697[159];

private:
	static hook_func<CGameActor* (CGameActor::*)()> CGameActor::_cCGameActor;
	static hook_func<void (CGameActor::*)()> CGameActor::_dCGameActor;
	static hook_func<void (CGameActor::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CGameActor::_SendMsg;
	static hook_func<int (CGameActor::*)(float rot)> CGameActor::_Get8Dir;
	static hook_func<void (CGameActor::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CGameActor::_SetRenderInfo;
	static hook_func<void (CGameActor::*)(int action, int speed, int type)> CGameActor::_SetAction;
	static hook_func<bool (CGameActor::*)()> CGameActor::_ProcessState;
	static hook_func<void (CGameActor::*)(int stateId)> CGameActor::_SetState;
	static hook_func<void (CGameActor::*)()> CGameActor::_RegisterPos;
	static hook_func<void (CGameActor::*)()> CGameActor::_UnRegisterPos;
	static hook_func<void (CGameActor::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal)> CGameActor::_SetSprAct;
	static hook_func<void (CGameActor::*)(int job, int sex)> CGameActor::_SetSprAct_;
	static hook_func<void (CGameActor::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)> CGameActor::_SetSprAct2;
	static hook_func<void (CGameActor::*)(int job)> CGameActor::_SetSprJob;
	static hook_func<void (CGameActor::*)(int head)> CGameActor::_SetSprHead;
	static hook_func<void (CGameActor::*)(int job)> CGameActor::_SetSprJobDye;
	static hook_func<void (CGameActor::*)(int weapon)> CGameActor::_SetSprWeapon;
	static hook_func<void (CGameActor::*)(int weapon)> CGameActor::_SetSprWeapon2;
	static hook_func<void (CGameActor::*)(int accessory)> CGameActor::_SetSprAccessory;
	static hook_func<void (CGameActor::*)(int accessory)> CGameActor::_SetSprAccessory2;
	static hook_func<void (CGameActor::*)(int accessory)> CGameActor::_SetSprAccessory3;
	static hook_func<void (CGameActor::*)(int shield)> CGameActor::_SetSprShield;
	static hook_func<void (CGameActor::*)(int shoe)> CGameActor::_SetSprShoe;
	static hook_func<void (CGameActor::*)()> CGameActor::_SetImfFileName;
	static hook_func<void (CGameActor::*)()> CGameActor::_SetHeadPaletteName;
	static hook_func<void (CGameActor::*)()> CGameActor::_SetBodyPaletteName;
	static hook_func<void (CGameActor::*)(int bodyPalette)> CGameActor::_SetBodyPalette;
	static hook_func<void (CGameActor::*)(int headPalette)> CGameActor::_SetHeadPalette;
	static hook_func<int (CGameActor::*)()> CGameActor::_GetWeapon;
	static hook_func<void (CGameActor::*)()> CGameActor::_ProcessMotionWithDist;
	static hook_func<int (CGameActor::*)()> CGameActor::_GetAttackMotion;
	static hook_func<void (CGameActor::*)()> CGameActor::_MakeCorpse;
	static hook_func<void (CGameActor::*)(int attackMT)> CGameActor::_SetModifyFactorOfmotionSpeed;
	static hook_func<void (CGameActor::*)(int honor)> CGameActor::_SetHonor;
	static hook_func<void (CGameActor::*)(int honor, int virtue)> CGameActor::_SetPropensityInfo;
	static hook_func<void (CGameActor::*)(int gdid, int emblemVersion)> CGameActor::_SetGuildInfo;
	static hook_func<int (CGameActor::*)()> CGameActor::_GetGdid;
	static hook_func<int (CGameActor::*)()> CGameActor::_GetEmblemVersion;
	static hook_func<_MSG2AI& (CGameActor::*)(int merType)> CGameActor::_GetMsg2AI;
	static hook_func<void (CGameActor::*)(_MSG2AI& msg, int merType)> CGameActor::_SetMsg2AI;
	static hook_func<_MSG2AI& (CGameActor::*)(int merType)> CGameActor::_GetResMsg2AI;
	static hook_func<void (CGameActor::*)(_MSG2AI& msg, int merType)> CGameActor::_SetResMsg2AI;
	static hook_func<void (CGameActor::*)(int job)> CGameActor::_SetJob;
	static hook_func<int (CGameActor::*)(void)> CGameActor::_GetJob;
};
C_ASSERT( sizeof CGameActor == 856 );
