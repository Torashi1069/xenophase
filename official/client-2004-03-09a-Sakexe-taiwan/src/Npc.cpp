#include "GameMode.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "Npc.h"
#include "Player.h"
#include "Resource/Wave.h"
#include "Resource/World.h"
#include "Session.h"
#include <math.h>


CNpc::CNpc(void) // line 22
{
	this->CNpc::OnInit(); //inlined
}


CNpc::~CNpc(void) // line 27
{
	this->CNpc::OnExit(); //inlined
}


hook_method<void (CNpc::*)(void)> CNpc::_OnInit(SAKEXE, "CNpc::OnInit");
void CNpc::OnInit(void) // line 32
{
	return (this->*_OnInit)();
	
	m_playerIswithinBox = 0;
	m_lastEffectLaunchTick = timeGetTime();
	m_doesLaunchEffect = 0;
}


hook_method<void (CNpc::*)(void)> CNpc::_OnExit(SAKEXE, "CNpc::OnExit");
void CNpc::OnExit(void) // line 40
{
	return (this->*_OnExit)();

	;
}


hook_method<void (CNpc::*)(void)> CNpc::_ProcessContact(SAKEXE, "CNpc::ProcessContact");
void CNpc::ProcessContact(void) // line 307
{
	return (this->*_ProcessContact)();

	//TODO
}


hook_method<void (CNpc::*)(void)> CNpc::_ProcessLaunchEffect(SAKEXE, "CNpc::ProcessLaunchEffect");
void CNpc::ProcessLaunchEffect(void) // line 295
{
	return (this->*_ProcessLaunchEffect)();

	//TODO
}


hook_method<void (CNpc::*)(matrix& ptm)> CNpc::_Render(SAKEXE, "CNpc::Render");
void CNpc::Render(matrix& ptm) // line 370
{
	return (this->*_Render)(ptm);

	//TODO
}


hook_method<bool (CNpc::*)(void)> CNpc::_OnProcess(SAKEXE, "CNpc::OnProcess");
bool CNpc::OnProcess(void) // line 329
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<void (CNpc::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CNpc::_SendMsg(SAKEXE, "CNpc::SendMsg");
void CNpc::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 43-61
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	switch( message )
	{
	case 4:
	{
		//TODO: determine struct type
		JOBTYPE jobtype = *(JOBTYPE*)(arg1 + 4);
		int GDID = *(int*)(arg1 + 92);
		int emblemVer = *(int*)(arg1 + 96);

		this->CGameActor::SendMsg(sender, 4, arg1, arg2, arg3);
		m_isVisible = g_session.CSession::IsVisibleNPC(jobtype);
		this->SetGuildInfo(GDID, emblemVer);
	}
	break;
	default:
	{
		this->CGameActor::SendMsg(sender, message, arg1, arg2, arg3);
	}
	break;
	};
}


hook_method<void (CNpc::*)(int stateId)> CNpc::_SetState(SAKEXE, "CNpc::SetState");
void CNpc::SetState(int stateId) // line 96
{
	return (this->*_SetState)(stateId);

	//TODO
}


hook_method<void (CNpc::*)(void)> CNpc::_RegisterPos(SAKEXE, "CNpc::RegisterPos");
void CNpc::RegisterPos(void) // line 261
{
	return (this->*_RegisterPos)();

	//TODO
}


hook_method<void (CNpc::*)(void)> CNpc::_UnRegisterPos(SAKEXE, "CNpc::UnRegisterPos");
void CNpc::UnRegisterPos(void) // line 279
{
	return (this->*_UnRegisterPos)();

	//TODO
}


hook_method<void (CNpc::*)(int job, int sex)> CNpc::_SetSprAct(SAKEXE, "CNpc::SetSprAct");
void CNpc::SetSprAct(int job, int sex) // line 79
{
	return (this->*_SetSprAct)(job, sex);

	//TODO
}


hook_method<void (CNpc::*)(int job)> CNpc::_SetSprJob(SAKEXE, "CNpc::SetSprJob");
void CNpc::SetSprJob(int job) // line 64
{
	return (this->*_SetSprJob)(job);

	m_shadowZoom = g_session.CSession::GetShadowFactorWithJob(job);
	const char* jobName = g_session.m_jobNameTable[job];

	char sprName[128];
	char actName[128];
	if( this->CGameActor::GetJob() >= 1000 )
	{
		sprintf(sprName, "몬스터\\%s.act", jobName);
		sprintf(actName, "몬스터\\%s.spr", g_session.m_jobNameTable[job]);
	}
	else
	{
		sprintf(sprName, "NPC\\%s.spr", jobName);
		sprintf(actName, "NPC\\%s.act", g_session.m_jobNameTable[job]);
	}

	this->CRenderObject::SetSprName(sprName);
	this->CRenderObject::SetActName(actName);
}


hook_method<void (CNpc::*)(int head)> CNpc::_SetSprHead(SAKEXE, "CNpc::SetSprHead");
void CNpc::SetSprHead(int head) // line 1030 (GameActor.h)
{
	return (this->*_SetSprHead)(head);

	;
}


hook_method<void (CNpc::*)(int job)> CNpc::_SetSprJobDye(SAKEXE, "CNpc::SetSprJobDye");
void CNpc::SetSprJobDye(int job) // line 93
{
	return (this->*_SetSprJobDye)(job);

	;
}


hook_method<void (CNpc::*)(int weapon)> CNpc::_SetSprWeapon(SAKEXE, "CNpc::SetSprWeapon");
void CNpc::SetSprWeapon(int weapon) // line 1032 (GameActor.h)
{
	return (this->*_SetSprWeapon)(weapon);

	;
}


hook_method<void (CNpc::*)(int accessory)> CNpc::_SetSprAccessory(SAKEXE, "CNpc::SetSprAccessory");
void CNpc::SetSprAccessory(int accessory) // line 1033 (GameActor.h)
{
	return (this->*_SetSprAccessory)(accessory);

	;
}


hook_method<void (CNpc::*)(void)> CNpc::_SetImfFileName(SAKEXE, "CNpc::SetImfFileName");
void CNpc::SetImfFileName(void) // line 1034 (GameActor.h)
{
	return (this->*_SetImfFileName)();

	;
}


//////////////////////////////////////////////////


CBlowEffect::CBlowEffect(void) // line 449
{
	this->CBlowEffect::OnInit(); //inlined
}


CBlowEffect::~CBlowEffect(void) // line 454
{
	this->CBlowEffect::OnExit(); //inlined
}


hook_method<void (CBlowEffect::*)(void)> CBlowEffect::_OnInit(SERVER, "CBlowEffect::OnInit");
void CBlowEffect::OnInit(void) // line 459
{
	return (this->*_OnInit)();
	
	this->CRenderObject::SetSprName("이팩트\\이팩트.spr");
	this->CRenderObject::SetActName("이팩트\\이팩트.act");
	m_baseAction = 0;
}


hook_method<void (CBlowEffect::*)(void)> CBlowEffect::_OnExit(SERVER, "CBlowEffect::OnExit");
void CBlowEffect::OnExit(void) // line 466
{
	return (this->*_OnExit)();

	;
}


hook_method<bool (CBlowEffect::*)(void)> CBlowEffect::_OnProcess(SERVER, "CBlowEffect::OnProcess");
bool CBlowEffect::OnProcess(void) // line 470
{
	return (this->*_OnProcess)();

	m_curAction = m_baseAction;
	float stateCnt = (timeGetTime() - m_stateStartTick) * (1/24.0f) / m_motionSpeed;
	int motionCnt = this->CRenderObject::GetActRes()->CActRes::GetMotionCount(m_curAction);
	m_curMotion = int(stateCnt) % motionCnt;
	this->CRenderObject::ProcessSound();
	if( stateCnt / motionCnt >= 1.0f )
		return false;
	return true;
}


hook_method<void (CBlowEffect::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CBlowEffect::_SendMsg(SERVER, "CBlowEffect::SendMsg");
void CBlowEffect::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // 485
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);
	
	switch( message )
	{
	case 14:// initialize
		m_pos = *((vector3d*)arg1);
		m_isVisible = 1;
		m_sprArgb = ( arg2 != 0 ) ? 0xFFFF0000 : 0xFFFFFFFF;
		m_stateStartTick = timeGetTime();
	break;
	default:
		this->CRenderObject::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
}


//////////////////////////////////////////////////


CCorpse::CCorpse(void) // line 509
{
	this->CCorpse::OnInit(); //inlined
}


CCorpse::~CCorpse(void) // line 514
{
	this->CCorpse::OnExit(); //inlined
}


hook_method<void (CCorpse::*)(void)> CCorpse::_OnInit(SERVER, "CCorpse::OnInit");
void CCorpse::OnInit(void) // line 519
{
	return (this->*_OnInit)();

	m_isVisible = true;
	m_isLieOnGround = true;
	m_stateStartTick = timeGetTime();
}


hook_method<void (CCorpse::*)(void)> CCorpse::_OnExit(SERVER, "CCorpse::OnExit");
void CCorpse::OnExit(void) // line 526
{
	return (this->*_OnExit)();

	;
}


hook_method<bool (CCorpse::*)(void)> CCorpse::_OnProcess(SERVER, "CCorpse::OnProcess");
bool CCorpse::OnProcess(void) // line 530
{
	return (this->*_OnProcess)();

	float stateCnt = (timeGetTime() - m_stateStartTick) * (1/24.0f);
	m_curAction = m_baseAction + this->Get8Dir(m_roty);
	m_curMotion = this->CRenderObject::GetActRes()->CActRes::GetMotionCount(m_curAction) - 1;
	this->CRenderObject::SetArgb(int(255.0f - stateCnt), -1, -1, -1);
	return ( stateCnt < 255.0f );
}


hook_method<void (CCorpse::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CCorpse::_SendMsg(SERVER, "CCorpse::SendMsg");
void CCorpse::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 553
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	this->CRenderObject::SendMsg(sender, message, arg1, arg2, arg3);
}


//////////////////////////////////////////////////


CMasterChaser::CMasterChaser(void) // line 693
{
	this->CMasterChaser::OnInit(); //inlined
}


CMasterChaser::~CMasterChaser(void) // line 698
{
	this->CMasterChaser::OnExit(); //inlined
}


hook_method<void (CMasterChaser::*)(void)> CMasterChaser::_OnInit(SERVER, "CMasterChaser::OnInit");
void CMasterChaser::OnInit(void) // line 703
{
	return (this->*_OnInit)();

	m_pursuedMaster = NULL;
}


hook_method<void (CMasterChaser::*)(void)> CMasterChaser::_OnExit(SERVER, "CMasterChaser::OnExit");
void CMasterChaser::OnExit(void) // line 708
{
	return (this->*_OnExit)();

	;
}


//////////////////////////////////////////////////


CNumEffect::CNumEffect(void) // line 714
{
	this->CNumEffect::OnInit(); //inlined
}


CNumEffect::~CNumEffect(void) // line 719
{
	this->CNumEffect::OnExit(); //inlined
}


hook_method<void (CNumEffect::*)(void)> CNumEffect::_OnInit(SERVER, "CNumEffect::OnInit");
void CNumEffect::OnInit(void) // line 724
{
	return (this->*_OnInit)();
	
	this->CRenderObject::SetSprName("이팩트\\숫자.spr");
	this->CRenderObject::SetActName("이팩트\\숫자.act");
	m_baseAction = 0;
	m_alwaysTopLayer = true;
}


hook_method<void (CNumEffect::*)(void)> CNumEffect::_OnExit(SERVER, "CNumEffect::OnExit");
void CNumEffect::OnExit(void) // line 732
{
	return (this->*_OnExit)();

	;
}


hook_method<bool (CNumEffect::*)(void)> CNumEffect::_OnProcess(SERVER, "CNumEffect::OnProcess");
bool CNumEffect::OnProcess(void) // line 736
{
	return (this->*_OnProcess)();

	m_curAction = m_baseAction;
	float stateCnt = (timeGetTime() - m_stateStartTick) * (1/24.0f);
	m_pos.y = m_orgPosY - stateCnt * 0.18f;
	if( m_zoom < 1.0f )
		m_zoom = 1.0f;
	else
	if( m_zoom > 1.0f )
		m_zoom = m_orgZoom - stateCnt * 0.24f;
	return ( stateCnt <= 120.0 );
}


hook_method<void (CNumEffect::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CNumEffect::_SendMsg(SERVER, "CNumEffect::SendMsg");
void CNumEffect::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 753
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	switch( message )
	{
	case 14:// start effect
		m_isVisible = true;
		m_pos = *((vector3d*)arg1);
		m_pos.y -= 12.0f;
		m_curMotion = arg2;
		if( arg2 < 0 || arg2 > 9 )
			m_curMotion = 0;
		m_sprShift = arg3;
		m_zoom = 5.0f;
		m_orgZoom = 5.0f;
		m_stateStartTick = timeGetTime();
	break;
	case 22:// ??? empty
	break;
	default:
		this->CRenderObject::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
}


//////////////////////////////////////////////////


CSoundMaker::CSoundMaker(void) // line 782
{
	this->CSoundMaker::OnInit(); //inlined
}


CSoundMaker::~CSoundMaker(void) // line 787
{
	this->CSoundMaker::OnExit(); //inlined
}


hook_method<void (CSoundMaker::*)(void)> CSoundMaker::_OnInit(SERVER, "CSoundMaker::OnInit");
void CSoundMaker::OnInit(void) // line 792
{
	return (this->*_OnInit)();

	m_waveName = "";
	m_vol = 100.0f;;
	m_range = 1.0f;
	m_width = 3;
	m_height = 3;
	m_diagonal = sqrt(18.0f);
	m_lastPlayTime = timeGetTime() - 4000;
}


hook_method<void (CSoundMaker::*)(void)> CSoundMaker::_OnExit(SERVER, "CSoundMaker::OnExit");
void CSoundMaker::OnExit(void) // line 806
{
	return (this->*_OnExit)();

	;
}


hook_method<void (CSoundMaker::*)(matrix& vtm)> CSoundMaker::_Render(SERVER, "CSoundMaker::Render");
void CSoundMaker::Render(matrix& vtm) // line 478
{
	return (this->*_Render)(vtm);

	;
}


hook_method<bool (CSoundMaker::*)(void)> CSoundMaker::_OnProcess(SERVER, "CSoundMaker::OnProcess");
bool CSoundMaker::OnProcess(void) // line 810
{
	return (this->*_OnProcess)();

	//TODO: recheck, I took some liberties with the structure
	CPlayer* player = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player;
	if( this->CRenderObject::CalcDist(player->m_pos.x, player->m_pos.z) - (m_diagonal + m_range) > 130.0f )// circular range
		return true;
	float dist_x = player->m_pos.x - m_pos.x;
	float dist_z = player->m_pos.z - m_pos.z;
	float sign_x = (dist_x >= 0.0f)? 1.0f: -1.0f;
	float sign_z = (dist_z >= 0.0f)? 1.0f: -1.0f;
	float slope = dist_z / dist_x;
	float point_x, point_z;
	if( (double)abs(slope) <= (double)(m_height / m_width) )
	{// point in east/west edge of rectangle
		point_x = m_pos.x + m_width * sign_x * 0.5f;
		point_z = m_pos.z + point_x * slope;
	}
	else
	{// point in north/south edge of rectangle
		point_z = m_pos.z + m_height * sign_z * 0.5f;
		point_x = m_pos.x + point_z / slope;
	}
	if( player->CRenderObject::CalcDist(point_x, point_z) - m_range > 75.0f )// range from rectangle point
		return true;
	if( m_waveName.length() == 0 )
		return true;
	if( timeGetTime() <= m_lastPlayTime + m_cycle )
		return true;
	m_lastPlayTime = timeGetTime();
	PlayWave(m_waveName.c_str(), point_x - player->m_pos.x, 0.0f, point_z - player->m_pos.z, int(m_range), int(m_range * (1/6.0f)), m_vol);
}


hook_method<void (CSoundMaker::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CSoundMaker::_SendMsg(SERVER, "CSoundMaker::SendMsg");
void CSoundMaker::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // 881
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);
	
	switch( message )
	{
	case 14:// initialize
	{
		C3dWorldRes::soundSrcInfo* soundSrcInfo = (C3dWorldRes::soundSrcInfo*)arg1;
		m_waveName = soundSrcInfo->waveName;
		m_vol = soundSrcInfo->vol;
		m_width = soundSrcInfo->width;
		m_height = soundSrcInfo->height;
		m_range = soundSrcInfo->range;
		m_pos = soundSrcInfo->pos;
		m_diagonal = sqrt(float(m_height * m_height + m_width * m_width));
		m_cycle = (unsigned long)(soundSrcInfo->cycle * 1000.0f);
		m_lastPlayTime = timeGetTime() - m_cycle;
	}
	break;
	default:
		this->CRenderObject::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
}
