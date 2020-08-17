#include "GameActor.h"
#include "GameMode.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "View.h"
#include "Base/Res.h"
#include "Resource/Action.h"
#define _USE_MATH_DEFINES
#include <math.h>
////////////////////////////////////////


hook_func<void (RENDER_INFO_RECT::*)(float left, float top, float right, float bottom, float oow)> RENDER_INFO_RECT::_SetInfo("RENDER_INFO_RECT::SetInfo");
void RENDER_INFO_RECT::SetInfo(float left, float top, float right, float bottom, float oow)
{
	return (this->*_SetInfo)(left, top, right, bottom, oow);
}


hook_func<void (RENDER_INFO_RECT::*)(RPSprite& spr)> RENDER_INFO_RECT::_Update("RENDER_INFO_RECT::Update");
void RENDER_INFO_RECT::Update(RPSprite& spr)
{
	return (this->*_Update)(spr);
}


////////////////////////////////////////


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}


void CGameObject::OnInit()
{
}


void CGameObject::OnExit()
{
}


bool CGameObject::OnProcess()
{
	return true;
}


void CGameObject::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3)
{
}


void CGameObject::Render(matrix& ptm)
{
}


int CGameObject::Get8Dir(float rot)
{
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
	if( mode == NULL )
		return 0;

	float angle = -mode->CGameMode::GetView()->CView::GetCurLongitude() - rot;

	while( angle < 0.0 )
		angle += 360.0;

	while( angle >= 360.0 )
		angle -= 360.0;

	return int(angle / 45.0);
}


int CGameObject::Get8Dir2(float rot, int isReal8Dir)
{
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
	if( mode == NULL )
		return 0;

	float angle = -mode->CGameMode::GetView()->CView::GetCurLongitude() - rot;

	while( angle < 0.0 )
		angle += 360.0;

	while( angle >= 360.0 )
		angle -= 360.0;

	if( !isReal8Dir )
		return int(angle / 45.0);
	else
	if( angle >= 22.5 && angle <= 337.5 )
		return int((angle + 22.5) / 45.0);
	else
		return 0;
}


int CGameObject::GetDir(float rot)
{
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
	if( mode == NULL )
		return 0;

	int angle = int(-mode->CGameMode::GetView()->CView::GetCurLongitude() - rot);

	if( angle < 0 )
		angle += 360 * ((360 - 1 - angle) / 360);

	if( angle >= 360 )
		angle = angle % 360;

	return angle;
}


////////////////////////////////////////


hook_func<CRenderObject* (CRenderObject::*)(void)> CRenderObject::_cCRenderObject("CRenderObject::CRenderObject");
CRenderObject::CRenderObject(void)
{
	(this->*_cCRenderObject)(); return;
}


hook_func<void (CRenderObject::*)(void)> CRenderObject::_dCRenderObject("CRenderObject::~CRenderObject");
CRenderObject::~CRenderObject(void)
{
	(this->*_dCRenderObject)(); return;
}


hook_func<bool (CRenderObject::*)(void)> CRenderObject::_OnProcess("CRenderObject::OnProcess");
bool CRenderObject::OnProcess(void)
{
	return (this->*_OnProcess)();
}


hook_func<void (CRenderObject::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CRenderObject::_SendMsg("CRenderObject::SendMsg");
void CRenderObject::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3)
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);
}


hook_func<void (CRenderObject::*)(matrix& vtm)> CRenderObject::_Render("CRenderObject::Render");
void CRenderObject::Render(matrix& vtm)
{
	return (this->*_Render)(vtm);
}


hook_func<void (CRenderObject::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CRenderObject::_SetRenderInfo("CRenderObject::SetRenderInfo");
void CRenderObject::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)
{
	return (this->*_SetRenderInfo)(info, tlvertX, tlvertY);
}


hook_func<void (CRenderObject::*)(float tlvertX, float tlvertY)> CRenderObject::_SetTlvert("CRenderObject::SetTlvert");
void CRenderObject::SetTlvert(float tlvertX, float tlvertY)
{
	return (this->*_SetTlvert)(tlvertX, tlvertY);
}


hook_func<void (CRenderObject::*)(int action, int speed, int type)> CRenderObject::_SetAction("CRenderObject::SetAction");
void CRenderObject::SetAction(int action, int speed, int type)
{
	return (this->*_SetAction)(action, speed, type);
}


hook_func<void (CRenderObject::*)(void)> CRenderObject::_ProcessMotion("CRenderObject::ProcessMotion");
void CRenderObject::ProcessMotion(void)
{
	return (this->*_ProcessMotion)();
}


hook_func<void (CRenderObject::*)(matrix& vtm)> CRenderObject::_UpdateTlvertex("CRenderObject::UpdateTlvertex");
void CRenderObject::UpdateTlvertex(matrix& vtm)
{
	return (this->*_UpdateTlvertex)(vtm);
}


hook_func<void (CRenderObject::*)(matrix& vtm, char FLAG1)> CRenderObject::_RenderBody("CRenderObject::RenderBody");
void CRenderObject::RenderBody(matrix& vtm, char FLAG1)
{
	return (this->*_RenderBody)(vtm, FLAG1);
}


hook_func<void (CRenderObject::*)(matrix& vtm, float zoom)> CRenderObject::_RenderShadow("CRenderObject::RenderShadow");
void CRenderObject::RenderShadow(matrix& vtm, float zoom)
{
	return (this->*_RenderShadow)(vtm, zoom);
}


hook_func<void (CRenderObject::*)(RPSprite& spr, unsigned long* pal, int renderFlag)> CRenderObject::_RenderSprite("CRenderObject::RenderSprite");
void CRenderObject::RenderSprite(RPSprite& spr, unsigned long* pal, int renderFlag)
{
	return (this->*_RenderSprite)(spr, pal, renderFlag);
}


hook_func<void (CRenderObject::*)(int a, int r, int g, int b)> CRenderObject::_SetArgb("CRenderObject::SetArgb");
void CRenderObject::SetArgb(int a, int r, int g, int b)
{
	return (this->*_SetArgb)(a, r, g, b);
}


hook_func<void (CRenderObject::*)(float& lmRIntensity, float& lmGIntensity, float& lmBIntensity)> CRenderObject::_SetLmIntensity("CRenderObject::SetLmIntensity");
void CRenderObject::SetLmIntensity(float& lmRIntensity, float& lmGIntensity, float& lmBIntensity)
{
	return (this->*_SetLmIntensity)(lmRIntensity, lmGIntensity, lmBIntensity);
}


hook_func<void (CRenderObject::*)(float* top, float* btm, float* left, float* right)> CRenderObject::_SetCharacterSquare("CRenderObject::SetCharacterSquare");
void CRenderObject::SetCharacterSquare(float* top, float* btm, float* left, float* right)
{
	return (this->*_SetCharacterSquare)(top, btm, left, right);
}


hook_func<void (CRenderObject::*)(float* angle)> CRenderObject::_SetCharacterAngle("CRenderObject::SetCharacterAngle");
void CRenderObject::SetCharacterAngle(float* angle)
{
	return (this->*_SetCharacterAngle)(angle);
}


hook_func<void (CRenderObject::*)(int layer, int* imfOffX, int* imfOffY, int* head_imfOffX, int* head_imfOffY)> CRenderObject::_SetCharacterPreAngle("CRenderObject::SetCharacterPreAngle");
void CRenderObject::SetCharacterPreAngle(int layer, int* imfOffX, int* imfOffY, int* head_imfOffX, int* head_imfOffY)
{
	return (this->*_SetCharacterPreAngle)(layer, imfOffX, imfOffY, head_imfOffX, head_imfOffY);
}


hook_func<void (CRenderObject::*)(RPSprite spr, unsigned long* pal)> CRenderObject::_SetCharacterLight("CRenderObject::SetCharacterLight");
void CRenderObject::SetCharacterLight(RPSprite spr, unsigned long* pal)
{
	return (this->*_SetCharacterLight)(spr, pal);
}


hook_func<void (CRenderObject::*)(float* pixelRatio)> CRenderObject::_SetCharacterPixelRatio("CRenderObject::SetCharacterPixelRatio");
void CRenderObject::SetCharacterPixelRatio(float* pixelRatio)
{
	return (this->*_SetCharacterPixelRatio)(pixelRatio);
}


hook_func<short (CRenderObject::*)(void)> CRenderObject::_SetCharacterFlying("CRenderObject::SetCharacterFlying");
short CRenderObject::SetCharacterFlying(void)
{
	return (this->*_SetCharacterFlying)();
}


void CRenderObject::SetActName(const char* actName)
{
	if( m_actRes != NULL )
		m_actRes->CRes::Unlock();

	m_actRes = (CActRes*)g_resMgr().CResMgr::Get(actName);
	m_actRes->CRes::Lock();
}


void CRenderObject::SetForceAnimation(int act, int mot, int maxMot, int finishAct, int finishMot, int isAnim, DWORD endTick, int isLoop)
{
	m_forceAct = act;
	m_forceMot = mot;
	m_forceStartMot = mot;
	m_forceMaxMot = maxMot;
	m_forceFinishedMot = finishMot;
	m_isForceAnimLoop = isLoop;
	m_forceFinishedAct = finishAct;
	m_isForceAnimation = isAnim;
	m_isForceAnimFinish = FALSE;
	m_isForceState = 1;
	m_isForceState3 = 0;
	m_isForceState2 = 0;

	if( isAnim )
	{
		m_forceStateCnt = 1;
		m_forceStateEndTick = endTick + timeGetTime();
	}
	else
	{
		m_forceStateCnt = 1;
		m_forceStateEndTick = 0;
	}
}


void CRenderObject::CalcDir(float x, float z)
{
	m_roty = float(atan2(-(z - m_pos.z), (x - m_pos.x)) / M_PI * 180.0f);

	if( m_roty >= 360.0f )
		m_roty -= 360.0f;

	if( m_roty < 0.0f )
		m_roty += 360.0f;
}


////////////////////////////////////////


hook_func<CAbleToMakeEffect* (CAbleToMakeEffect::*)()> CAbleToMakeEffect::_cCAbleToMakeEffect("CAbleToMakeEffect::CAbleToMakeEffect");
CAbleToMakeEffect::CAbleToMakeEffect()
{
	(this->*_cCAbleToMakeEffect)(); return;

	//TODO
}


hook_func<CRagEffect* (CAbleToMakeEffect::*)(int effectId, vector3d fDeltaPos, float fRot)> CAbleToMakeEffect::_LaunchEffect("CAbleToMakeEffect::LaunchEffect");
CRagEffect* CAbleToMakeEffect::LaunchEffect(int effectId, vector3d fDeltaPos, float fRot)
{
	return (this->*_LaunchEffect)(effectId, fDeltaPos, fRot);

	//TODO
}


////////////////////////////////////////


hook_func<CGameActor* (CGameActor::*)()> CGameActor::_cCGameActor("CGameActor::CGameActor");
CGameActor::CGameActor()
{
	(this->*_cCGameActor)(); return;

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_dCGameActor("CGameActor::~CGameActor");
CGameActor::~CGameActor()
{
	(this->*_dCGameActor)(); return;

	//TODO
}


hook_func<void (CGameActor::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CGameActor::_SendMsg("CGameActor::SendMsg");
void CGameActor::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3)
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	//TODO
}


hook_func<int (CGameActor::*)(float rot)> CGameActor::_Get8Dir("CGameActor::Get8Dir");
int CGameActor::Get8Dir(float rot)
{
	return (this->*_Get8Dir)(rot);

	//TODO
}


hook_func<void (CGameActor::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CGameActor::_SetRenderInfo("CGameActor::SetRenderInfo");
void CGameActor::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)
{
	return (this->*_SetRenderInfo)(info, tlvertX, tlvertY);

	//TODO
}


hook_func<void (CGameActor::*)(int action, int speed, int type)> CGameActor::_SetAction("CGameActor::SetAction");
void CGameActor::SetAction(int action, int speed, int type)
{
	return (this->*_SetAction)(action, speed, type);

	//TODO
}


hook_func<bool (CGameActor::*)()> CGameActor::_ProcessState("CGameActor::ProcessState");
bool CGameActor::ProcessState()
{
	return (this->*_ProcessState)();

	//TODO
}


hook_func<void (CGameActor::*)(int stateId)> CGameActor::_SetState("CGameActor::SetState");
void CGameActor::SetState(int stateId)
{
	return (this->*_SetState)(stateId);

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_RegisterPos("CGameActor::RegisterPos");
void CGameActor::RegisterPos()
{
	return (this->*_RegisterPos)();

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_UnRegisterPos("CGameActor::UnRegisterPos");
void CGameActor::UnRegisterPos()
{
	return (this->*_UnRegisterPos)();

	//TODO
}


hook_func<void (CGameActor::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal)> CGameActor::_SetSprAct("?SetSprAct@CGameActor@@UAEXHHHHHHHHHH@Z");
void CGameActor::SetSprAct(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal)
{
	return (this->*_SetSprAct)(job, sex, head, weapon, accessory, accessory2, accessory3, shield, headPal, bodyPal);

	//TODO
}


hook_func<void (CGameActor::*)(int job, int sex)> CGameActor::_SetSprAct_("?SetSprAct@CGameActor@@UAEXHH@Z");
void CGameActor::SetSprAct(int job, int sex)
{
	return (this->*_SetSprAct_)(job, sex);

	//TODO
}


hook_func<void (CGameActor::*)(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)> CGameActor::_SetSprAct2("CGameActor::SetSprAct2");
void CGameActor::SetSprAct2(int job, int sex, int head, int weapon, int accessory, int accessory2, int accessory3, int shield, int headPal, int bodyPal, int effectState)
{
	return (this->*_SetSprAct2)(job, sex, head, weapon, accessory, accessory2, accessory3, shield, headPal, bodyPal, effectState);

	//TODO
}


hook_func<void (CGameActor::*)(int job)> CGameActor::_SetSprJob("CGameActor::SetSprJob");
void CGameActor::SetSprJob(int job)
{
	return (this->*_SetSprJob)(job);

	//TODO
}


hook_func<void (CGameActor::*)(int head)> CGameActor::_SetSprHead("CGameActor::SetSprHead");
void CGameActor::SetSprHead(int head)
{
	return (this->*_SetSprHead)(head);

	//TODO
}



hook_func<void (CGameActor::*)(int job)> CGameActor::_SetSprJobDye("CGameActor::SetSprJobDye");
void CGameActor::SetSprJobDye(int job)
{
	return (this->*_SetSprJobDye)(job);

	//TODO
}


hook_func<void (CGameActor::*)(int weapon)> CGameActor::_SetSprWeapon("CGameActor::SetSprWeapon");
void CGameActor::SetSprWeapon(int weapon)
{
	return (this->*_SetSprWeapon)(weapon);

	//TODO
}


hook_func<void (CGameActor::*)(int weapon)> CGameActor::_SetSprWeapon2("CGameActor::SetSprWeapon2");
void CGameActor::SetSprWeapon2(int weapon)
{
	return (this->*_SetSprWeapon2)(weapon);

	//TODO
}


hook_func<void (CGameActor::*)(int accessory)> CGameActor::_SetSprAccessory("CGameActor::SetSprAccessory");
void CGameActor::SetSprAccessory(int accessory)
{
	return (this->*_SetSprAccessory)(accessory);

	//TODO
}


hook_func<void (CGameActor::*)(int accessory)> CGameActor::_SetSprAccessory2("CGameActor::SetSprAccessory2");
void CGameActor::SetSprAccessory2(int accessory)
{
	return (this->*_SetSprAccessory2)(accessory);

	//TODO
}


hook_func<void (CGameActor::*)(int accessory)> CGameActor::_SetSprAccessory3("CGameActor::SetSprAccessory3");
void CGameActor::SetSprAccessory3(int accessory)
{
	return (this->*_SetSprAccessory3)(accessory);

	//TODO
}


hook_func<void (CGameActor::*)(int shield)> CGameActor::_SetSprShield("CGameActor::SetSprShield");
void CGameActor::SetSprShield(int shield)
{
	return (this->*_SetSprShield)(shield);

	//TODO
}


hook_func<void (CGameActor::*)(int shoe)> CGameActor::_SetSprShoe("CGameActor::SetSprShoe");
void CGameActor::SetSprShoe(int shoe)
{
	return (this->*_SetSprShoe)(shoe);

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_SetImfFileName("CGameActor::SetImfFileName");
void CGameActor::SetImfFileName()
{
	return (this->*_SetImfFileName)();

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_SetHeadPaletteName("CGameActor::SetHeadPaletteName");
void CGameActor::SetHeadPaletteName()
{
	return (this->*_SetHeadPaletteName)();

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_SetBodyPaletteName("CGameActor::SetBodyPaletteName");
void CGameActor::SetBodyPaletteName()
{
	return (this->*_SetBodyPaletteName)();

	//TODO
}


hook_func<void (CGameActor::*)(int bodyPalette)> CGameActor::_SetBodyPalette("CGameActor::SetBodyPalette");
void CGameActor::SetBodyPalette(int bodyPalette)
{
	return (this->*_SetBodyPalette)(bodyPalette);

	//TODO
}


hook_func<void (CGameActor::*)(int headPalette)> CGameActor::_SetHeadPalette("CGameActor::SetHeadPalette");
void CGameActor::SetHeadPalette(int headPalette)
{
	return (this->*_SetHeadPalette)(headPalette);

	//TODO
}


hook_func<int (CGameActor::*)()> CGameActor::_GetWeapon("CGameActor::GetWeapon");
int CGameActor::GetWeapon()
{
	return (this->*_GetWeapon)();

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_ProcessMotionWithDist("CGameActor::ProcessMotionWithDist");
void CGameActor::ProcessMotionWithDist()
{
	return (this->*_ProcessMotionWithDist)();

	//TODO
}


hook_func<int (CGameActor::*)()> CGameActor::_GetAttackMotion("CGameActor::GetAttackMotion");
int CGameActor::GetAttackMotion()
{
	return (this->*_GetAttackMotion)();

	//TODO
}


hook_func<void (CGameActor::*)()> CGameActor::_MakeCorpse("CGameActor::MakeCorpse");
void CGameActor::MakeCorpse()
{
	return (this->*_MakeCorpse)();

	//TODO
}


hook_func<void (CGameActor::*)(int attackMT)> CGameActor::_SetModifyFactorOfmotionSpeed("CGameActor::SetModifyFactorOfmotionSpeed");
void CGameActor::SetModifyFactorOfmotionSpeed(int attackMT)
{
	return (this->*_SetModifyFactorOfmotionSpeed)(attackMT);

	//TODO
}


hook_func<void (CGameActor::*)(int honor)> CGameActor::_SetHonor("CGameActor::SetHonor");
void CGameActor::SetHonor(int honor)
{
	return (this->*_SetHonor)(honor);

	//TODO
}


hook_func<void (CGameActor::*)(int honor, int virtue)> CGameActor::_SetPropensityInfo("CGameActor::SetPropensityInfo");
void CGameActor::SetPropensityInfo(int honor, int virtue)
{
	return (this->*_SetPropensityInfo)(honor, virtue);

	//TODO
}


hook_func<void (CGameActor::*)(int gdid, int emblemVersion)> CGameActor::_SetGuildInfo("CGameActor::SetGuildInfo");
void CGameActor::SetGuildInfo(int gdid, int emblemVersion)
{
	return (this->*_SetGuildInfo)(gdid, emblemVersion);

	//TODO
}


hook_func<int (CGameActor::*)()> CGameActor::_GetGdid("CGameActor::GetGdid");
int CGameActor::GetGdid()
{
	return (this->*_GetGdid)();

	//TODO
}


hook_func<int (CGameActor::*)()> CGameActor::_GetEmblemVersion("CGameActor::GetEmblemVersion");
int CGameActor::GetEmblemVersion()
{
	return (this->*_GetEmblemVersion)();

	//TODO
}


hook_func<_MSG2AI& (CGameActor::*)(int merType)> CGameActor::_GetMsg2AI("CGameActor::GetMsg2AI");
_MSG2AI& CGameActor::GetMsg2AI(int merType)
{
	return (this->*_GetMsg2AI)(merType);

	//TODO
}


hook_func<void (CGameActor::*)(_MSG2AI& msg, int merType)> CGameActor::_SetMsg2AI("CGameActor::SetMsg2AI");
void CGameActor::SetMsg2AI(_MSG2AI& msg, int merType)
{
	return (this->*_SetMsg2AI)(msg, merType);

	//TODO
}


hook_func<_MSG2AI& (CGameActor::*)(int merType)> CGameActor::_GetResMsg2AI("CGameActor::GetResMsg2AI");
_MSG2AI& CGameActor::GetResMsg2AI(int merType)
{
	return (this->*_GetResMsg2AI)(merType);

	//TODO
}


hook_func<void (CGameActor::*)(_MSG2AI& msg, int merType)> CGameActor::_SetResMsg2AI("CGameActor::SetResMsg2AI");
void CGameActor::SetResMsg2AI(_MSG2AI& msg, int merType)
{
	return (this->*_SetResMsg2AI)(msg, merType);

	//TODO
}


hook_func<void (CGameActor::*)(int job)> CGameActor::_SetJob("CGameActor::SetJob");
void CGameActor::SetJob(int job)
{
	return (this->*_SetJob)(job);

	//TODO
}


hook_func<int (CGameActor::*)(void)> CGameActor::_GetJob("CGameActor::GetJob");
int CGameActor::GetJob(void)
{
	return (this->*_GetJob)();

	//TODO
}


unsigned long CGameActor::GetGID()
{
	return m_gid;
}


int CGameActor::GetTargetGid()
{
	return m_targetGid;
}


void CGameActor::SetFreezeEndTick(DWORD tick)
{
	m_freezeEndTick = tick;
}


void CGameActor::SetMotionSpeed(float motionSpeed)
{
	if( motionSpeed > 0.0f )
		m_motionSpeed = motionSpeed;
}


////////////////////////////////////////
