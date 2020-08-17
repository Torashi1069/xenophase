#include "GameActor3d.h"
#include "GameMode.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "Base/ResMgr.h"
#include "Resource/Emblem.h"
#include "Resource/Model.h"


C3dGrannyGameActor::C3dGrannyGameActor(char* strJobFn) // line 18-44
{
	//TODO
}


C3dGrannyGameActor::~C3dGrannyGameActor() // line 47-67
{
	//TODO
}


hook_method<bool (C3dGrannyGameActor::*)()> C3dGrannyGameActor::_OnProcess(SAKEXE, "C3dGrannyGameActor::OnProcess");
bool C3dGrannyGameActor::OnProcess() // line 109-148
{
	return (this->*_OnProcess)();

	//TODO
}


void C3dGrannyGameActor::Render(matrix& view) // line 151-177
{
	m_shadowDotList.clear();
	this->C3dGrannyGameActor::ProcessAni();
	vector3d sunLoc = g_Weather.CWeather::GetSunWorldLoc();

	GrannyLightInfo grannyLInfo;
	grannyLInfo.eyeVec.x = sunLoc.x;
	grannyLInfo.eyeVec.y = sunLoc.y;
	grannyLInfo.eyeVec.z = sunLoc.z;
	grannyLInfo.lightR = 200;
	grannyLInfo.lightG = 200;
	grannyLInfo.lightB = 200;
	grannyLInfo.nContrast = 128;

	if( m_nRenderType != 1 && m_nRenderType != 2 )
	{
		if( m_actorType == 2 )
			this->C3dGrannyGameActor::RenderGuildMark(view);
		else
			this->C3dGrannyGameActor::RenderNormal(view, &grannyLInfo);
	}
}


void C3dGrannyGameActor::SetAction(int action, int speed, int type) // line 719-762
{
	switch( action )
	{
	case 48:
		m_stateId = STATEID_FLINCH;
	break;
	case 80:
	case 88:
		m_stateId = STATEID_ATTACK;
	break;
	case 64:
		m_stateId = STATEID_DEAD;
	break;
	case 0:
		m_stateId = STATEID_STAND;
	break;
	case 8:
		m_stateId = STATEID_WALK;
	break;
	case 24:
		m_stateId = STATEID_PICKUP;
	break;
	case 32:
		m_stateId = STATEID_11;
	break;
	case 40:
		m_stateId = STATEID_12;
	break;
	default:
		m_stateId = STATEID_STAND;
	break;
	}

	m_nLastActAnimation = m_stateId;

	for( int i = 0; i < 20; ++i )
	{
		m_GrannyActorRes->C3dGrannyModelRes::DeActAnimation(m_Control[i]);
		m_Control[i] = NULL;
	}

	m_GameClock = 0;

	if( type == 1 )
		m_Control[m_nLastActAnimation] = m_GrannyActorRes->C3dGrannyModelRes::ActAnimation(m_nLastActAnimation, m_Instance, m_Control[m_nLastActAnimation], 1);
	else
		m_Control[m_nLastActAnimation] = m_GrannyActorRes->C3dGrannyModelRes::ActAnimation(m_nLastActAnimation, m_Instance, m_Control[m_nLastActAnimation], 0);
}


void C3dGrannyGameActor::SetSprAct(int job, int sex) // line 70-106
{
	this->CGameActor::SetJob(job);
	this->CGameActor::SetSex(sex);
	m_GrannyActorRes = (C3dGrannyModelRes*)g_resMgr().CResMgr::Get(m_strJobFn);
	m_Instance = GrannyInstantiateModel(m_GrannyActorRes->C3dGrannyModelRes::GetModel());

	for( int i = 0; i < m_GrannyActorRes->C3dGrannyModelRes::GetMeshNo(); ++i )
	{
		int count = m_GrannyActorRes->C3dGrannyModelRes::GetMeshIndexCount(i);

		m_rp[i] = new RPMesh;
		m_rp[i]->RPMesh::AllocVerts(count);
		m_matVer[i] = new granny_pnt332_vertex[3 * count];
		memset(m_matVer[i], 0, 3 * count * sizeof(granny_pnt332_vertex));
	}

	m_fLastAniCnt = GrannyGetSystemSeconds();
	m_GameClock = 0;

	if( job == JT_ZOMBIE_DRAGON || job == JT_HUGELING )
	{
		m_actorType = 1;

		m_GrannyActorRes->C3dGrannyModelRes::SetHitRad(30.0, 30.0); // inlined
	}
	else
	if( job == JT_GUILD_FLAG )
	{
		m_actorType = 2;

		char strEbm[260];
		g_session.CSession::GetEmblemFileName(strEbm, this->GetGdid(), this->GetEmblemVersion());

		if( !g_resMgr().CResMgr::IsExist(strEbm) )
			g_modeMgr.CModeMgr::GetCurMode()->SendMsg(121, m_gdid, 0, 0);
	}
	else
	{
		m_actorType = 0;
	}
}


void C3dGrannyGameActor::ProcessMotion() // line 705-712
{
	m_isMotionFinished = ( m_stateId != 2 );
}


void C3dGrannyGameActor::ProcessMotionWithDist() // line 715-716
{
}


void C3dGrannyGameActor::MakeCorpse() // line 698-702
{
	g_modeMgr.CModeMgr::GetGameMode()->CGameMode::MakeGrannyCorpse3d(m_pos.x, m_pos.y, m_pos.z, m_fCurRot, m_strJobFn);
}


int C3dGrannyGameActor::GetAttackMotion() // line 765-767
{
	return 0;
}


void C3dGrannyGameActor::SetRenderType(int renderType)
{
	m_nRenderType = renderType;
}


int C3dGrannyGameActor::GetRenderType()
{
	return m_nRenderType;
}


CTexture* C3dGrannyGameActor::GetEmblemTexture()
{
	if( m_emblemTex == NULL )
	{
		m_emblemTex = g_texMgr.CTexMgr::CreateTexture(24, 24, PF_A1R5G5B5, NULL);

		char strEbm[260];
		g_session.CSession::GetEmblemFileName(strEbm, this->GetGdid(), this->GetEmblemVersion());

		unsigned long dwEmblem[24*24];

		CEmblemRes* emblemRes = (CEmblemRes*)g_resMgr().CResMgr::Get(strEbm);
		if( emblemRes != NULL )
		{
			memcpy(dwEmblem, emblemRes->CEmblemRes::GetBitmap()->m_data, sizeof(dwEmblem)); // @custom
		}
		else
		{
			memset(dwEmblem, 0, sizeof(dwEmblem));
		}

		m_emblemTex->Update(0, 0, 24, 24, dwEmblem, false, 0);
	}

	return m_emblemTex;
}


bool C3dGrannyGameActor::ProcessAni() // line 180-198
{
	m_fAniCnt = GrannyGetSystemSeconds();
	float fElapsed = GrannyGetSecondsElapsed(&m_fLastAniCnt, &m_fAniCnt);
	float GameClock = fElapsed + fElapsed + m_GameClock;
	m_GameClock = GameClock;
	m_GrannyActorRes->C3dGrannyModelRes::UpdateAni(GameClock, m_Instance);

	m_fLastAniCnt.Data[0] = m_fAniCnt.Data[0];
	m_fLastAniCnt.Data[1] = m_fAniCnt.Data[1];
	m_fLastAniCnt.Data[2] = m_fAniCnt.Data[2];
	m_fLastAniCnt.Data[3] = m_fAniCnt.Data[3];

	if( m_nLastActAnimation == 2 && m_Control[2] != NULL && GrannyGetControlDurationLeft(m_Control[2]) <= 0.0 )
	{
		m_nLastActAnimation = 0;
		m_Control[m_nLastActAnimation] = m_GrannyActorRes->C3dGrannyModelRes::ActAnimation(0, m_Instance, m_Control[0], 0);
	}

	return true;
}


hook_func<void (C3dGrannyGameActor::*)(matrix& view, GrannyLightInfo* grannyLInfo)> C3dGrannyGameActor::_RenderNormal(SAKEXE, "C3dGrannyGameActor::RenderNormal");
void C3dGrannyGameActor::RenderNormal(matrix& view, GrannyLightInfo* grannyLInfo) // line 201-322
{
	return (this->*_RenderNormal)(view, grannyLInfo);

	//TODO
}


hook_func<void (C3dGrannyGameActor::*)(matrix& vtm)> C3dGrannyGameActor::_RenderBak(SAKEXE, "C3dGrannyGameActor::RenderBak");
void C3dGrannyGameActor::RenderBak(matrix& vtm) // line 325-402
{
	return (this->*_RenderBak)(vtm);

	//TODO
}


void C3dGrannyGameActor::RenderNormalFast(matrix& view) // line 405-407
{
}


void C3dGrannyGameActor::RenderCell(matrix& view) // line 410-412
{
}


hook_func<void (C3dGrannyGameActor::*)(matrix& view)> C3dGrannyGameActor::_RenderGuildMark(SAKEXE, "C3dGrannyGameActor::RenderGuildMark");
void C3dGrannyGameActor::RenderGuildMark(matrix& view) // line 415-527
{
	return (this->*_RenderGuildMark)(view);

	//TODO
}


void C3dGrannyGameActor::RenderEffect(int nMesh, granny_pnt332_vertex* vertArr, vector3d tv) // line 572-588
{
	if( m_job == JT_ZOMBIE_DRAGON && nMesh == 28 )
	{
		vector3d pos = vector3d(vertArr[64].Position[0], vertArr[64].Position[1], vertArr[64].Position[2]);
		this->CAbleToMakeEffect::LaunchEffect(EF_DRAGONSMOKE, pos, -m_fCurRot);
	}
}


hook_func<void (C3dGrannyGameActor::*)(matrix& vtm, vector3d lv, bool isBakRender)> C3dGrannyGameActor::_RenderShadow(SAKEXE, "C3dGrannyGameActor::RenderShadow");
void C3dGrannyGameActor::RenderShadow(matrix& vtm, vector3d lv, bool isBakRender)
{
	return (this->*_RenderShadow)(vtm, lv, isBakRender);

	//TODO
}
