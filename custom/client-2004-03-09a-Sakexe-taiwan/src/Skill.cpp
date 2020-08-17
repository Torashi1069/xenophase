#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "RagEffect.h"
#include "Skill.h"
#include "Base/ResMgr.h"
#include "Window/UIBalloonText.h"
////////////////////////////////////////


CSkill::CSkill() // line 19-21
{
	this->CSkill::OnInit(); //inlined
}


CSkill::~CSkill() // line 24-26
{
	this->CSkill::OnExit(); //inlined
}


void CSkill::OnInit() // line 29-38
{
	m_aid = 0;
	this->CGameActor::SetJob(JT_SAFETYWALL);
	m_launchCnt = 36000;
	m_shouldAddPickInfo = false;
	m_isVisibleBody = false;
	m_balloon = NULL;
	m_3dactor = NULL;
	m_LoopEffect = NULL;
}


void CSkill::OnExit() // line 41-47
{
	if( m_balloon != NULL )
	{
		g_windowMgr.UIWindowMgr::PostQuit(m_balloon);
		m_balloon = NULL;
	}

	this->CSkill::HideModel(); // inlined
}


hook_func<void (CSkill::*)(matrix& vtm)> CSkill::_Render(SAKEXE, "CSkill::Render");
void CSkill::Render(matrix& vtm) // line 577-600
{
	return (this->*_Render)(vtm);

	//TODO
}


hook_func<bool (CSkill::*)()> CSkill::_OnProcess(SAKEXE, "CSkill::OnProcess");
bool CSkill::OnProcess() // line 51-538
{
	return (this->*_OnProcess)();

	//TODO
}


hook_func<void (CSkill::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CSkill::_SendMsg(SAKEXE, "CSkill::SendMsg");
void CSkill::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 605-829
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	//TODO
}


hook_func<void (CSkill::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CSkill::_SetRenderInfo(SAKEXE, "CSkill::SetRenderInfo");
void CSkill::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY) // line 541-574
{
	return (this->*_SetRenderInfo)(info, tlvertX, tlvertY);

	//TODO
}


unsigned long CSkill::GetAID() // line ???-???
{
	return m_aid;
}


char* CSkill::GetTrapModelName() // line 832-858
{
	switch( this->CGameActor::GetJob() )
	{
	case JT_TRAP_BLASTMINE   : return "외부소품\\트랩03_3.rsm";
	case JT_TRAP_SKIDTRAP    : return "외부소품\\트랩02.rsm";
	case JT_TRAP_ANKLESNARE  : return "외부소품\\트랩01.rsm";
	case JT_TRAP_LANDMINE    : return "외부소품\\트랩03.rsm";
	case JT_TRAP_SHOCKWAVE   : return "외부소품\\트랩03_6.rsm";
	case JT_TRAP_SANDMAN     : return "외부소품\\트랩03_4.rsm";
	case JT_TRAP_FLASHER     : return "외부소품\\트랩03_5.rsm";
	case JT_TRAP_FREEZINGTRAP: return "외부소품\\트랩03_2.rsm";
	case JT_TRAP_CLAYMORETRAP: return "외부소품\\트랩04.rsm";
	case JT_TRAP_TALKIEBOX   : return "외부소품\\트랩05.rsm";
	default                  : return NULL;
	}
}


void CSkill::ShowModel(char* modelName) // line 861-885
{
	if( modelName == NULL || !m_isVisibleBody )
		return;

	this->CSkill::HideModel(); // inlined

	vector3d lightDir;
	lightDir.x = 0.5f;
	lightDir.y = 0.7f;
	lightDir.z = 0.5f;

	vector3d diffuseCol;
	diffuseCol.x = 1.0f;
	diffuseCol.y = 1.0f;
	diffuseCol.z = 1.0f;

	vector3d ambientCol;
	ambientCol.x = 0.5f;
	ambientCol.y = 0.5f;
	ambientCol.z = 0.5f;

	C3dModelRes* model = (C3dModelRes*)g_resMgr().CResMgr::Get(modelName);

	m_3dactor = new C3dActor();
	m_3dactor->C3dActor::SetAnimSpeed(1/3.0f);
	m_3dactor->C3dActor::SetVolumeBoxInfo(&model->m_volumeBoxList);
	m_3dactor->C3dActor::SetPos(m_pos);
	m_3dactor->C3dActor::AssignModel(model);
	m_3dactor->C3dActor::SetName(modelName);
	m_3dactor->C3dActor::SetFrame(3);
	m_3dactor->C3dActor::SetBlockType(0);
	m_3dactor->C3dActor::SetIsHideCheck(0);
	m_3dactor->C3dActor::SetAnimType(0);
	m_3dactor->C3dActor::UpdateVertexColor(lightDir, diffuseCol, ambientCol);
	g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->CWorld::GetRootNode()->SceneGraphNode::InsertObjectAfter(m_3dactor, 0);
}


void CSkill::HideModel() // line 888-897
{
	if( m_3dactor == NULL )
		return;

	CWorld* world = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld();
	if( world->CWorld::GetRootNode() != NULL )
		world->CWorld::GetRootNode()->SceneGraphNode::RemoveObject(m_3dactor, 0);

	m_3dactor = NULL;

	if( m_LoopEffect != NULL )
		m_LoopEffect->SendMsg(NULL, 24, 0, 0, 0);

	m_LoopEffect = NULL;
}


void CSkill::SetAID(unsigned long aid) // line ???-???
{
	m_aid = aid;
}


////////////////////////////////////////


CGraffiSkill::CGraffiSkill() // line 902-903
{
}

CGraffiSkill::~CGraffiSkill() // line 906-908
{
	delete m_tex;
}


hook_func<void (CGraffiSkill::*)()> CGraffiSkill::_OnInit(SAKEXE, "CGraffiSkill::OnInit");
void CGraffiSkill::OnInit() // line 911-964
{
	return (this->*_OnInit)();

	//TODO
}


void CGraffiSkill::OnExit() // line 967-969
{
	delete m_tex;
}


bool CGraffiSkill::OnProcess() // line 972-975
{
	return true;
}


hook_func<void (CGraffiSkill::*)(matrix& vtm)> CGraffiSkill::_Render(SAKEXE, "CGraffiSkill::Render");
void CGraffiSkill::Render(matrix& vtm) // line 978-1020
{
	return (this->*_Render)(vtm);

	//TODO
}


void CGraffiSkill::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 1023-1041
{
	switch( message )
	{
	case 22:
		this->CSkill::SetAID(arg1);
	break;
	case 115:
		m_lastingTime = arg1;
	break;
	case 117:
		strcpy(m_strMsg, (const char*)arg1);
		m_ground_pos_x = arg2;
		m_ground_pos_y = arg3;
		this->OnExit();
	break;
	default:
		this->CGameActor::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
}


////////////////////////////////////////


CMsgEffect::CMsgEffect(void) // line 1046
{
	this->CMsgEffect::OnInit();
}


CMsgEffect::~CMsgEffect(void) // line 1051
{
	if( m_masterActor != NULL )
		m_masterActor->SendMsg(this, 48, 0, 0, 0);
}


int CMsgEffect::GetMsgEffectType(void)
{
	return m_msgEffectType;
}


////////////////////////////////////////


CMandraAttackEffect::CMandraAttackEffect(void) // line 2076
{
	this->CMandraAttackEffect::OnInit(); //inlined
}


CMandraAttackEffect::~CMandraAttackEffect(void) // line 2081
{
	this->CMandraAttackEffect::OnExit(); //inlined
}




hook_method<void (CMandraAttackEffect::*)(void)> CMandraAttackEffect::_OnInit(SERVER, "CMandraAttackEffect::OnInit");
void CMandraAttackEffect::OnInit(void) // line 2086
{
	return (this->*_OnInit)();

	this->CRenderObject::SetSprName("몬스터\\mandragora_atk.spr");
	this->CRenderObject::SetActName("몬스터\\mandragora_atk.act");
	m_hideTime = 0.0f;
}


hook_method<void (CMandraAttackEffect::*)(void)> CMandraAttackEffect::_OnExit(SERVER, "CMandraAttackEffect::OnExit");
void CMandraAttackEffect::OnExit(void) // line 2093
{
	return (this->*_OnExit)();

	;
}


hook_method<bool (CMandraAttackEffect::*)(void)> CMandraAttackEffect::_OnProcess(SERVER, "CMandraAttackEffect::OnProcess");
bool CMandraAttackEffect::OnProcess(void) // line 2097
{
	return (this->*_OnProcess)();

	float stateCnt = (timeGetTime() - m_stateStartTick) * (1/24.0f);
	if( stateCnt <= m_hideTime )
	{
		m_isVisible = false;
		return true;
	}
	m_isVisible = true;
	if( !m_isMotionFinished )
	{
		int motionCount = this->CRenderObject::GetActRes()->CActRes::GetMotionCount(m_curAction);
		m_curMotion = int(stateCnt / m_motionSpeed) % motionCount;
		if( (stateCnt / m_motionSpeed) / motionCount >= 1.0f )
		{
			m_isMotionFinished = true;
			m_curMotion = motionCount - 1;
		}
	}
	return ( m_isMotionFinished == false ); 
}
