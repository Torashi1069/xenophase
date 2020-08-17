#pragma once
#include "PathFinder.h"
#include "Struct.h"
#include "3dLib/Prim.h"
#include "Resource/Action.h"
#include "Resource/Sprite.h"
class CMsgEffect;
class CRagEffect;
class UIBalloonText;
class UIChatRoomTitle;
class UIEmblemWnd;
class UIMerchantShopTitle;
class UIRechargeGage;


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

	void SetInfo(float left, float top, float right, float bottom, float oow);
	void Update(const struct RPSprite& spr);
};


struct WBA // "Will Be Attack(ed)"
{
	/* this+ 0 */ int message;
	/* this+ 4 */ int damage;
	/* this+ 8 */ unsigned long time;
	/* this+12 */ unsigned long targetGid;
	/* this+16 */ int tCellX;
	/* this+20 */ int tCellY;
	/* this+24 */ int effectId1;
	/* this+28 */ int effectId2;
	/* this+32 */ int effectLevel;
	/* this+36 */ float attackedSpeedFactor;

	WBA(int message, int damage, unsigned long time, unsigned long targetGid, int tCellX, int tCellY, int effectId1, int effectId2, int effectLevel, float attackedSpeedFactor);
};


/// @see CGameActor::SendMsg()
enum ACTORMESSAGE
{
	AM_0 = 0,
	AM_3_STANDENTRY_EXISTING = 3,
	AM_4_STANDENTRY_NEW      = 4,
	//TODO
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
	int Get8Dir2(float rot, BOOL isReal8Dir);
	int GetDir(float rot);

public:
	/* this+0 */ //const CGameObject::`vftable';
};


class CRenderObject : public CGameObject
{
public:
	/* this+  0 */ //CGameObject baseclass_0;
	/* this+  4 */ vector3d m_pos;
	/* this+ 16 */ mystd::string m_bodyPaletteName;
	/* this+ 32 */ int m_baseAction;
	/* this+ 36 */ int m_curAction;
	/* this+ 40 */ int m_curMotion;
	/* this+ 44 */ int m_oldBaseAction;
	/* this+ 48 */ int m_oldMotion;
	/* this+ 52 */ int m_bodyPalette;
	/* this+ 56 */ float m_roty;
	/* this+ 60 */ float m_zoom;
	/* this+ 64 */ float m_shadowZoom;
	/* this+ 68 */ float m_motionSpeed;
	/* this+ 72 */ float m_lastPixelRatio;
	/* this+ 76 */ float m_loopCountOfmotionFinish;
	/* this+ 80 */ float m_modifyFactorOfmotionSpeed;
	/* this+ 84 */ int m_motionType;
	/* this+ 88 */ int m_stateId;
	/* this+ 92 */ int m_sprShift;
	/* this+ 96 */ int m_sprAngle;
	/* this+100 */ int m_offsetOow;
	/* this+104 */ unsigned long m_colorOfSingleColor;
	/* this+108 */ unsigned long m_singleColorStartTick;
	/* this+112 */ DWORD m_stateStartTick;
	/* this+116 */ ACTOR_COLOR m_oldColor;
	/* this+120 */ ACTOR_COLOR m_curColor;
	union {
	/* this+124 */ unsigned long m_sprArgb;
	/* this+124 */ COLOR m_sprColor;
	};
	/* this+128 */ bool m_isLieOnGround;
	/* this+129 */ bool m_isMotionFinished;
	/* this+130 */ bool m_isMotionFreezed;
	/* this+131 */ bool m_isSingleColor;
	/* this+132 */ bool m_isVisible;
	/* this+133 */ bool m_isVisibleBody;
	/* this+134 */ bool m_alwaysTopLayer;
	/* this+135 */ bool m_isSprArgbFixed;
	/* this+136 */ bool m_shadowOn;
	/* this+137 */ bool m_shouldAddPickInfo;
	/* this+140 */ int m_isPc;
	/* this+144 */ int m_lastTlvertX;
	/* this+148 */ int m_lastTlvertY;
	/* this+152 */ unsigned char m_forceAct;
	/* this+153 */ unsigned char m_forceMot;
	/* this+154 */ unsigned char m_forceMaxMot;
	/* this+155 */ unsigned char m_forceAnimSpeed;
	/* this+156 */ unsigned char m_forceFinishedAct;
	/* this+157 */ unsigned char m_forceFinishedMot;
	/* this+158 */ unsigned char m_forceStartMot;
	/* this+160 */ int m_isForceState;
	/* this+164 */ int m_isForceAnimLoop;
	/* this+168 */ int m_isForceAnimation;
	/* this+172 */ int m_isForceAnimFinish;
	/* this+176 */ unsigned long m_forceStateCnt;
	/* this+180 */ unsigned long m_forceStateEndTick;
	/* this+184 */ char m_BodyLight;
	/* this+185 */ char m_BodyHit;
	/* this+188 */ float m_BodyHeight;
	/* this+192 */ char m_BodyFlag;
	/* this+193 */ unsigned char m_BodySin;
private:
	/* this+196 */ CSprRes* m_sprRes;
	/* this+200 */ CActRes* m_actRes;

public:
	CRenderObject();
	virtual ~CRenderObject();
	void OnInit();
	void OnExit();
	virtual bool OnProcess();
	virtual void Render(matrix& vtm);
	void UpdateTlvertex(matrix& vtm);
	void RenderBody(matrix& vtm);
	void RenderShadow(matrix& vtm, float zoom);
	void RenderSprite(const RPSprite& spr, unsigned long* pal, int renderFlag);
	virtual void SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
	virtual void SetTlvert(float tlvertX, float tlvertY);
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual void SetAction(int action, int speed, int type);
	float CalcDist(float x, float z);
	float CalcDist(float x, float y, float z);
	void CalcDir(float x, float z);
	float CalcDir(float sx, float sz, float x, float z);
	void ModifyArgb(int a, int r, int g, int b);
	void SetArgb(int a, int r, int g, int b);
	bool GetTargetPos(unsigned long targetGid, vector3d& tPos);
	//float GetStateCnt();
	float GetLastPixelRatio();
	int GetLastTlvertX();
	int GetLastTlvertY();
	virtual void ProcessMotion();
	void ProcessSound();
	void SetLmIntensity(float& lmRIntensity, float& lmGIntensity, float& lmBIntensity);
	void SetForceAnimSpeed(unsigned char speed);
	void SetForceAnimEndTick(unsigned long tick);
	void SetForceAnimation(int act, int mot, int maxMot, int finishAct, int finishMot, int isAnim, unsigned long endTick, int isLoop);
	void SetSprName(const char* sprName);
	const char* GetSprName();
	CSprRes* GetSprRes();
	void SetActName(const char* actName);
	const char* GetActName();
	CActRes* GetActRes();
};


class CMousePointer : public CRenderObject
{
public:
	CMousePointer();
	virtual ~CMousePointer();
	void OnInit();
	void OnExit();
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual bool OnProcess();

public:
	/* this+  0 */ //CRenderObject baseclass_0;
	/* this+204 */ int m_visibleTime;
};


class CAbleToMakeEffect : public CRenderObject
{
public:
	CAbleToMakeEffect();
	virtual ~CAbleToMakeEffect();
	void OnInit();
	void OnExit();
	virtual void SendMsg(CGameObject* sender, int msgid, int val1, int val2, int val3);
	CRagEffect* LaunchEffect(int effectId, vector3d fDeltaPos, float fRot);
	bool IsExistEffect(CRagEffect* pEffect);
	int IsEffectExist(int EffectId);

public:
	/* this+  0 */ //CRenderObject baseclass_0;
	/* this+204 */ int m_efId;
	/* this+208 */ int m_Sk_Level;
	/* this+212 */ int m_isLoop;
	/* this+216 */ mystd::list<CRagEffect*> m_effectList;
private:
	/* this+228 */ CRagEffect* m_beginSpellEffect;
	/* this+232 */ CRagEffect* m_magicTargetEffect;
};


class CGameActor : public CAbleToMakeEffect
{
public:
	CGameActor();
	virtual ~CGameActor();
	void OnInit();
	void OnExit();
	virtual bool OnProcess() = 0;
	virtual bool ProcessState();
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual void SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
	virtual void SetState(int stateId);
	virtual void RegisterPos();
	virtual void UnRegisterPos();
	virtual void SetAction(int action, int speed, int type);
	virtual int Get8Dir(float rot);
	virtual void SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal);
	virtual void SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState);
	virtual void SetSprAct(int job, int sex);
	virtual void SetSprJob(int job);
	virtual void SetSprHead(int head);
	virtual void SetSprJobDye(int job);
	virtual void SetSprWeapon(int weapon);
	virtual void SetSprWeapon2(int weapon);
	virtual void SetSprAccessory(int accessory);
	virtual void SetSprAccessory2(int accessory);
	virtual void SetSprAccessory3(int accessory);
	virtual void SetSprShield(int shield);
	virtual void SetSprShoe(int shoe);
	virtual void SetImfFileName();
	virtual void SetHeadPaletteName();
	virtual void SetBodyPaletteName();
	virtual void SetBodyPalette(int bodyPalette);
	virtual void SetHeadPalette(int headPalette);
	virtual int GetWeapon();
	virtual void ProcessMotionWithDist();
	virtual int GetAttackMotion();
	virtual void MakeCorpse();
	virtual void SetModifyFactorOfmotionSpeed(int attackMT);
	virtual void SetHonor(int honor);
	virtual void SetPropensityInfo(int honor, int virtue);
	bool FindPath(int mssx, int mssy, int mscellX, int mscellY, int msdx, int msdy, int msspeed);
	void ProcessWillBeAttacked();
	void MakeSpecialAttackEffect(unsigned long targetGid, float hideTime);
	//void CGameActor::CalcAccel(float);
	//struct vector3d CGameActor::CalcAccel3d(struct vector3d, float);
	//void CGameActor::ProcessActionWithDir();
	//void CGameActor::AddDist(struct vector3d &, struct vector3d &);
	unsigned long GetGID();
	void CGameActor::ProcessChatBalloon();
	void SetJob(int job);
	int GetJob();
	void SetSex(int sex);
	//int GetSex();
	//UIChatRoomTitle* GetChatRoomTitle();
	void SetPKState(int isPKModeON);
	void SetAttrState(int bodyState, int effectState, int healthState, bool changedNow);
	void ProcessEffectState();
	void DeleteMatchingEffect(CMsgEffect* msgEffect);
	//unsigned char CGameActor::ProcessVanish();
	void ProcessBodyState();
	void SetVanish();
	//CMsgEffect* GetBird();
	int GetProperJob(int job, int effectState);
	int GetBodyState();
	int GetEffectState();
	void SetHeadType(int headType);
	int GetHeadType();
	int GetActorType();
	void Am_Skill(CGameObject* sender, int arg1, int arg2, int arg3);
	void Am_Action(CGameObject* sender, int arg1, int arg2, int arg3);
	void Am_Groundskill(CGameObject* sender, int arg1, int arg2, int arg3);
	void Am_Make_Number(CGameObject* sender, int arg1, int arg2, int arg3);
	void MakePartyEffect(int AID);
	void DeleteTotalNumber();
	//void AddMsgEffect(CMsgEffect*);
	//int CGameActor::IsDarkEffect(int);
	//void CGameActor::Delete99LevelEffects();
	virtual void SetGuildInfo(int gdid, int emblemVersion);
	virtual int GetGdid();
	virtual int GetEmblemVersion();
	void DeleteEmblemWnd();
	void MakeEmblemWnd();
	BOOL IsFreezeState();
	void SetFreezeEndTick(unsigned long freezeEndTick);
	int GetTargetGid();

private:
	static hook_func<bool (CGameActor::*)()> CGameActor::_ProcessState;
	static hook_func<void (CGameActor::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CGameActor::_SendMsg;
	static hook_func<void (CGameActor::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CGameActor::_SetRenderInfo;
	static hook_func<int (CGameActor::*)(float rot)> CGameActor::_Get8Dir;
	static hook_func<int (CGameActor::*)()> CGameActor::_GetAttackMotion;
	static hook_func<bool (CGameActor::*)(int mssx, int mssy, int mscellX, int mscellY, int msdx, int msdy, int msspeed)> CGameActor::_FindPath;
	static hook_func<void (CGameActor::*)()> CGameActor::_ProcessChatBalloon;
	static hook_func<void (CGameActor::*)(int bodyState, int effectState, int healthState, bool changedNow)> CGameActor::_SetAttrState;
	static hook_func<void (CGameActor::*)()> CGameActor::_ProcessEffectState;
	static hook_func<void (CGameActor::*)(CGameObject* sender, int arg1, int arg2, int arg3)> CGameActor::_Am_Action;
	static hook_func<void (CGameActor::*)(CGameObject* sender, int arg1, int arg2, int arg3)> CGameActor::_Am_Skill;
	static hook_func<void (CGameActor::*)(CGameObject* sender, int arg1, int arg2, int arg3)> CGameActor::_Am_Groundskill;

public:
	/* this+  0 */ //CAbleToMakeEffect baseclass_0;
	/* this+236 */ int m_moveDestX;
	/* this+240 */ int m_moveDestY;
	/* this+244 */ unsigned long m_speed;
	/* this+248 */ int m_isCounter;
	/* this+252 */ int m_isTrickDead;
	/* this+256 */ int m_isPlayHitWave;
	/* this+260 */ int m_isAsuraAttack;
	/* this+264 */ UIEmblemWnd* m_emblemWnd; // @custom
	/* this+268 */ char m_hitWaveName[128];
	/* this+396 */ unsigned long m_colorEndTick;
protected:
	/* this+400 */ vector3d m_accel;
	/* this+412 */ CPathInfo m_path;
	/* this+440 */ unsigned long m_moveStartTime;
	/* this+444 */ bool m_isNeverAnimation;
	/* this+448 */ int m_pathStartCell;
	/* this+452 */ float m_dist;
	/* this+456 */ unsigned long m_lastProcessStateTime;
	/* this+460 */ unsigned long m_lastServerTime;
	/* this+464 */ unsigned long m_chatTick;
	/* this+468 */ unsigned long m_targetGid;
	/* this+472 */ float m_attackMotion;
	/* this+476 */ int m_isBladeStop;
	/* this+480 */ unsigned long m_gid;
	/* this+484 */ int m_job;
	/* this+488 */ int m_sex;
	/* this+492 */ UIBalloonText* m_balloon;
	/* this+496 */ UIChatRoomTitle* m_chatTitle;
	/* this+500 */ UIMerchantShopTitle* m_merchantShopTitle;
	/* this+504 */ UIRechargeGage* m_skillRechargeGage;
	/* this+508 */ unsigned long m_freezeEndTick;
	/* this+512 */ unsigned long m_petEmotionStartTick;
	/* this+516 */ unsigned long m_skillRechargeEndTick;
	/* this+520 */ unsigned long m_skillRechargeStartTick;
	/* this+524 */ int m_chatWidth;
	/* this+528 */ int m_chatHeight;
	/* this+532 */ int m_nameWidth;
	/* this+536 */ int m_xSize;
	/* this+540 */ int m_ySize;
	/* this+544 */ int m_headType;
	/* this+548 */ mystd::list<WBA> m_willBeAttackList;
	/* this+560 */ mystd::list<WBA> m_willBeAttackedList;
	/* this+572 */ int m_willBeDead;
	/* this+576 */ int m_is99;
	/* this+580 */ char m_99;
	/* this+584 */ int m_bodyState;
	/* this+588 */ int m_effectState;
	/* this+592 */ int m_healthState;
	/* this+596 */ int m_pkState;
	/* this+600 */ float m_damageDestX;
	/* this+604 */ float m_damageDestZ;
	/* this+608 */ unsigned long m_effectLaunchCnt;
	/* this+612 */ unsigned long m_vanishTime;
	/* this+616 */ int m_actorType;
	/* this+620 */ int m_gdid;
	/* this+624 */ int m_emblemVersion;
private:
	/* this+628 */ CMsgEffect* m_birdEffect;
	/* this+632 */ CMsgEffect* m_cartEffect;
	/* this+636 */ CMsgEffect* m_pkEffect;
	/* this+640 */ CMsgEffect* m_iceEffect;
	/* this+644 */ CMsgEffect* m_curseEffect;
	/* this+648 */ CMsgEffect* m_sleepEffect;
	/* this+652 */ CMsgEffect* m_stunEffect;
	/* this+656 */ CMsgEffect* m_silenceEffect;
	/* this+660 */ CMsgEffect* m_angelusEffect;
	/* this+664 */ CMsgEffect* m_crusisEffect;
	/* this+668 */ CMsgEffect* m_chatProhibitEffect;
	/* this+672 */ mystd::list<CMsgEffect*> m_msgEffectList;
};


#include "Npc.h"
#include "GameActor3d.h"
