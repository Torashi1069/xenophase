#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "Player.h"
#include "WinMain.h" // CheckSystemMessage()
#include "Base/ResMgr.h"
#include "Resource/World.h"
#include <math.h>
const float epsilon = 0.00001f;
const float infinity = 999999.0f;
bool __cdecl TestAABBvsOBBIntersection(C3dOBB& obb, C3dAABB& aabb);


mystd::vector< mystd::pair<float,C3dWorldRes::actorInfo*> >& g_3dActors = VTOR< mystd::vector< mystd::pair<float,C3dWorldRes::actorInfo*> > >(SymDB::Add("g_3dActors", SAKEXE, "g_3dActors")); // = ?;


////////////////////////////////////////


hook_func<DWORD (__stdcall *)(void* pvoid)> _LoadFarModels(SAKEXE, "LoadFarModels");
DWORD __stdcall LoadFarModels(void* pvoid) // line 29-82
{
	return (_LoadFarModels)(pvoid);

	CWorld* world = (CWorld*)pvoid;

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	mystd::sort(g_3dActors.begin(), g_3dActors.end());

	for( mystd::vector< mystd::pair<float,C3dWorldRes::actorInfo*> >::iterator i = g_3dActors.begin(); i != g_3dActors.end(); ++i )
	{
		C3dWorldRes::actorInfo* info = i->second;

		C3dModelRes* model = (C3dModelRes*)g_resMgr().CResMgr::Get(info->modelName);
		if( model == NULL )
		{
			Trace("%s model not found.", info->modelName);
			continue;
		}

		if( model->C3dModelRes::FindNode(info->nodeName) == NULL && model->C3dModelRes::GetFirstNode() == NULL )
		{
			Trace("%s model has no node.", info->modelName);
			continue;
		}

		C3dActor* actor = new C3dActor();

		float animSpeed = info->animSpeed;
		if( animSpeed != 0.0 )
			animSpeed = animSpeed / 3;

		actor->C3dActor::SetAnimSpeed(animSpeed); // inlined
		actor->C3dActor::SetVolumeBoxInfo(&model->m_volumeBoxList);
		actor->C3dActor::SetPos(info->pos); // inlined
		actor->C3dActor::SetRot(info->rot); // inlined
		actor->C3dActor::SetScale(info->scale); // inlined
		actor->C3dActor::AssignModel(model);
		actor->C3dActor::SetBlockType(info->blockType); // inlined
		actor->C3dActor::SetIsHideCheck(0); // inlined
		actor->C3dActor::SetName(info->name); // inlined
		actor->C3dActor::UpdateVertexColor(lightDir, diffuseCol, ambientCol);
		world->m_bgObjList.push_back(actor); // inlined

		InterlockedIncrement(&world->m_bgObjThread);
		Sleep(0);
	}

	Trace("Load Model :: Lazy Model Load Complete");
	return 0;
}


////////////////////////////////////////


CWorld::CWorld(void) // line 88-99
{
	m_Calculated = NULL;
	m_bgObjThread = 0;
	m_nNightCnt = 0;
	m_bNight = 0;
	m_ground = NULL;
	m_player = NULL;
	m_isPKZone = 0;
	m_isSiegeMode = 0;
	m_isEventPVPMode = 0;
}


CWorld::~CWorld(void) // line 102-104
{
	delete m_ground;
}


hook_method<void (CWorld::*)(void)> CWorld::_OnEnterFrame(SAKEXE, "CWorld::OnEnterFrame");
void CWorld::OnEnterFrame(void) // line 135-289
{
	return (this->*_OnEnterFrame)();

	mystd::string rswName = (const char*)m_curMode->SendMsg(9, 0, 0, 0);
	C3dWorldRes* world = (C3dWorldRes*)g_resMgr().CResMgr::Get(rswName.c_str());

	m_Calculated = world->m_CalculatedNode;
	((CGameMode*)m_curMode)->CGameMode::SetArea(world->m_groundLeft, world->m_groundRight, world->m_groundTop, world->m_groundBottom);

	lightDir.x = world->m_lightDir.x;
	lightDir.y = world->m_lightDir.y;
	lightDir.z = world->m_lightDir.z;
	diffuseCol.x = world->m_diffuseCol.x;
	diffuseCol.y = world->m_diffuseCol.y;
	diffuseCol.z = world->m_diffuseCol.z;
	ambientCol.x = world->m_ambientCol.x;
	ambientCol.y = world->m_ambientCol.y;
	ambientCol.z = world->m_ambientCol.z;
	g_renderer->CRenderer::SetLight(lightDir, diffuseCol, ambientCol);

	if( world->m_attrFile.size() == 0 )
	{
		ErrorMsg("attr 파일이 rsw 내에 지정되어 있지 않습니다");
		return;
	}

	m_attr = (C3dAttr*)g_resMgr().CResMgr::Get(world->m_attrFile.c_str());
	if( m_attr == NULL )
	{
		ErrorMsg("attr 파일 읽기에 실패");
		return;
	}
	m_attr->m_zoom = 5;

	if( world->m_gndFile.size() == 0 )
	{
		ErrorMsg("gnd 파일이 rsw 내에 지정되어 있지 않습니다");
		return;
	}

	CGndRes* gnd = (CGndRes*)g_resMgr().CResMgr::Get(world->m_gndFile.c_str());
	if( gnd->m_newVer == 0 )
	{
		ErrorMsg("맵이 옛 버젼입니다");
		return;
	}

	m_ground = new C3dGround15();
	m_ground->AssignGnd(gnd, lightDir, diffuseCol, ambientCol);
	m_ground->C3dGround::SetAttr(m_attr);
	g_resMgr().CResMgr::Unload(gnd);

	m_bgObjList.clear();
	m_bgObjList.reserve(world->m_3dActors.size());

	int n = 0;
	int percent = -1;
	for( mystd::list<C3dWorldRes::actorInfo*>::iterator i = world->m_3dActors.begin(); i != world->m_3dActors.end(); ++i )
	{
		C3dWorldRes::actorInfo* info = *i;
		++n;

		int newpercent = 100 * n / world->m_3dActors.size();
		if( percent != newpercent )
		{
			percent = newpercent;

			g_windowMgr.UIWindowMgr::SendMsg(UIM_LOADINGPERCENT, newpercent, 0, 0);
			g_windowMgr.UIWindowMgr::Render();
			if( g_renderer->CRenderer::DrawScene() )
				g_renderer->CRenderer::Flip(0);

			CheckSystemMessage();
		}

		g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetClientCoor(g_session.m_posX, g_session.m_posY, player_pos.x, player_pos.z);
		float dz = info->pos.z - player_pos.z;
		float dy = info->pos.y - player_pos.y;
		float dx = info->pos.x - player_pos.x;
		float dist = _sqrt(dx * dx + dy * dy + dz * dz);

		if( dist <= 200.0 )
		{
			C3dModelRes* model = (C3dModelRes*)g_resMgr().CResMgr::Get(info->modelName);
			if( model == NULL )
				continue;

			if( model->C3dModelRes::FindNode(info->nodeName) == NULL && model->C3dModelRes::GetFirstNode() == NULL )
				continue;

			C3dActor* newObj = new C3dActor();

			float animSpeed = info->animSpeed;
			if( animSpeed != 0.0 )
				animSpeed = animSpeed / 3;

			newObj->C3dActor::SetAnimSpeed(animSpeed); // inlined
			newObj->C3dActor::SetVolumeBoxInfo(&model->m_volumeBoxList);
			newObj->C3dActor::SetPos(info->pos); // inlined
			newObj->C3dActor::SetRot(info->rot); // inlined
			newObj->C3dActor::SetScale(info->scale); // inlined
			newObj->C3dActor::AssignModel(model);
			newObj->C3dActor::SetBlockType(info->blockType); // inlined
			newObj->C3dActor::SetIsHideCheck(0); // inlined
			newObj->C3dActor::SetName(info->name); // inlined
			newObj->C3dActor::UpdateVertexColor(lightDir, diffuseCol, ambientCol);
			m_bgObjList.push_back(newObj); // inlined
		}
		else
		{
			g_3dActors.push_back(mystd::pair<float,C3dWorldRes::actorInfo*>(dist, info));
		}
	}

	this->CWorld::BuildSceneGraph();
	this->CWorld::MakeFixedActor();
	m_ground->CalcLmIntensityFloatRGBAll();
	m_ground->C3dGround::SetWaterInfo(world->m_waterLevel, world->m_waterType, world->m_waterAnimSpeed, (int)world->m_wavePitch, (int)world->m_waveSpeed, world->m_waveHeight);
	m_bgObjCount = m_bgObjList.size();

	int threadId;
	g_farModelThread = CreateThread(NULL, 0, &LoadFarModels, (LPVOID)this, 0, (LPDWORD)&threadId);
	if( g_farModelThread == NULL )
	{
		LoadFarModels(this);
		this->CWorld::WaitForThreadEnd(); // inlined
	}

	m_player = new CPlayer();
	m_gameObjectList.push_back(m_player);
	g_session.m_isShowGameOver = 0;
}


hook_method<void (CWorld::*)(void)> CWorld::_MakeFixedActor(SAKEXE, "CWorld::MakeFixedActor");
void CWorld::MakeFixedActor(void) // line 107-132
{
	return (this->*_MakeFixedActor)();

	//TODO
}


hook_method<void (CWorld::*)(void)> CWorld::_OnExitFrame(SAKEXE, "CWorld::OnExitFrame");
void CWorld::OnExitFrame(void) // line 292-308
{
	return (this->*_OnExitFrame)();

	this->CWorld::WaitForThreadEnd(); // inlined
	this->CWorld::FreeSceneGraph(); // inlined
	this->CWorld::RemoveGameActorAll(); // inlined

	for( mystd::vector<C3dActor*>::iterator it = m_bgObjList.begin(); it != m_bgObjList.end(); ++it )
		delete *it;

	m_bgObjList.clear();

	delete m_ground;
	m_ground = NULL;

	g_resMgr().CResMgr::UnloadRarelyUsedRes();
	g_texMgr.CTexMgr::UnloadRarelyUsedTexture();
}


hook_method<void (CWorld::*)(void)> CWorld::_ProcessActors(SAKEXE, "CWorld::ProcessActors");
void CWorld::ProcessActors(void) // line 470-490
{
	return (this->*_ProcessActors)();

	//TODO
}


hook_method<void (CWorld::*)(CGameObject* object)> CWorld::_RemoveGameObject(SAKEXE, "CWorld::RemoveGameObject");
void CWorld::RemoveGameObject(CGameObject* object) // line 531-537
{
	return (this->*_RemoveGameObject)(object);

	//TODO
}


hook_method<CGameActor* (CWorld::*)(unsigned long GID)> CWorld::_GetGameActorByAID(SAKEXE, "CWorld::GetGameActorByAID");
CGameActor* CWorld::GetGameActorByAID(unsigned long GID) // line 554-562
{
	return (this->*_GetGameActorByAID)(GID);

	//TODO
}


hook_method<CItem* (CWorld::*)(unsigned long AID)> CWorld::_GetItemByAID(SAKEXE, "CWorld::GetItemByAID");
CItem* CWorld::GetItemByAID(unsigned long AID) // line 565-571
{
	return (this->*_GetItemByAID)(AID);

	//TODO
}


hook_method<CSkill* (CWorld::*)(unsigned long AID)> CWorld::_GetSkillByAID(SAKEXE, "CWorld::GetSkillByAID");
CSkill* CWorld::GetSkillByAID(unsigned long AID) // line 588-596
{
	return (this->*_GetSkillByAID)(AID);

	//TODO
}


hook_method<bool (CWorld::*)(unsigned long AID)> CWorld::_RemoveSkill(SAKEXE, "CWorld::RemoveSkill");
bool CWorld::RemoveSkill(unsigned long AID) // line 574-585
{
	return (this->*_RemoveSkill)(AID);

	//TODO
}


hook_method<bool (CWorld::*)(unsigned long ITAID)> CWorld::_RemoveItem(SAKEXE, "CWorld::RemoveItem");
bool CWorld::RemoveItem(unsigned long ITAID) // line 518-528
{
	return (this->*_RemoveItem)(ITAID);

	//TODO
}


hook_method<void (CWorld::*)(void)> CWorld::_RemoveGameActorAll(SAKEXE, "CWorld::RemoveGameActorAll");
void CWorld::RemoveGameActorAll(void) // line 540-551
{
	return (this->*_RemoveGameActorAll)();

	for( mystd::list<CGameObject*>::iterator it = m_gameObjectList.begin(); it != m_gameObjectList.end(); ++it )
		delete *it;

	m_player = NULL;
	m_gameObjectList.clear();
	m_actorList.clear();
	m_itemList.clear();
	m_skillList.clear();
}


//hook_method<SceneGraphNode* (CWorld::*)(void)> CWorld::_GetRootNode(SAKEXE, "CWorld::GetRootNode");
SceneGraphNode* CWorld::GetRootNode(void) // line ???
{
//	return (this->*_GetRootNode)();

	return &m_rootNode;
}


hook_method<void (CWorld::*)(void)> CWorld::_WaitForThreadEnd(SAKEXE, "CWorld::WaitForThreadEnd");
void CWorld::WaitForThreadEnd(void) // line 665-673
{
	return (this->*_WaitForThreadEnd)();

	if( g_farModelThread != NULL )
		WaitForSingleObject(g_farModelThread, INFINITE);

	g_farModelThread = NULL;
	g_3dActors.clear();
	m_bgObjThread = 0;
}


//hook_method<void (CWorld::*)(BOOL isPKZone)> CWorld::_SetPKZone(SAKEXE, "CWorld::SetPKZone");
void CWorld::SetPKZone(BOOL isPKZone)
{
//	return (this->*_SetPKZone)(isPKZone);

	m_isPKZone = isPKZone;
}


//hook_method<void (CWorld::*)(BOOL isSiegeMode)> CWorld::_SetSiegeMode(SAKEXE, "CWorld::SetSiegeMode");
void CWorld::SetSiegeMode(BOOL isSiegeMode)
{
//	return (this->*_SetSiegeMode)(isSiegeMode);

	m_isSiegeMode = isSiegeMode;
}


//hook_method<void (CWorld::*)(BOOL isEventPVPMode)> CWorld::_SetEventPVPMode(SAKEXE, "CWorld::SetEventPVPMode");
void CWorld::SetEventPVPMode(BOOL isEventPVPMode)
{
//	return (this->*_SetEventPVPMode)(isEventPVPMode);

	m_isEventPVPMode = isEventPVPMode;
}


hook_method<BOOL (CWorld::*)(void)> CWorld::_IsPKZone(SAKEXE, "CWorld::IsPKZone");
BOOL CWorld::IsPKZone(void) // line 115 (GameWorld.h)
{
	return (this->*_IsPKZone)();

	return m_isPKZone;
}


//hook_method<BOOL (CWorld::*)(void)> CWorld::_IsSiegeMode(SAKEXE, "CWorld::IsSiegeMode");
BOOL CWorld::IsSiegeMode(void) // line ???
{
//	return (this->*_IsSiegeMode)();

	return m_isSiegeMode;
}


hook_method<BOOL (CWorld::*)(void)> CWorld::_IsEventPVPMode(SAKEXE, "CWorld::IsEventPVPMode");
BOOL CWorld::IsEventPVPMode(void) // line 177 (GameWorld.h)
{
	return (this->*_IsEventPVPMode)();

	return m_isEventPVPMode;
}


hook_method<void (CWorld::*)(void)> CWorld::_BuildSceneGraph(SAKEXE, "CWorld::BuildSceneGraph");
void CWorld::BuildSceneGraph(void) // line 624-646
{
	return (this->*_BuildSceneGraph)();

	this->CWorld::FreeSceneGraph(); // inlined

	m_rootNode.m_aabb.min.x = float(m_ground->C3dGround::GetZoom() * -m_ground->C3dGround::GetWidth()/2);
	m_rootNode.m_aabb.max.x = float(m_ground->C3dGround::GetZoom() * +m_ground->C3dGround::GetWidth()/2 - 1.0);
	m_rootNode.m_aabb.min.z = float(m_ground->C3dGround::GetZoom() * -m_ground->C3dGround::GetHeight()/2);
	m_rootNode.m_aabb.max.z = float(m_ground->C3dGround::GetZoom() * +m_ground->C3dGround::GetHeight()/2 - 1.0);
	m_rootNode.m_center.x = 0.0;
	m_rootNode.m_center.z = 0.0;
	m_rootNode.SceneGraphNode::Build(0);

	for( mystd::vector<C3dActor*>::iterator it = m_bgObjList.begin(); it != m_bgObjList.end(); ++it )
		m_rootNode.SceneGraphNode::InsertObject(*it, 0); // inlined // guessed
	m_rootNode.SceneGraphNode::InsertObject(m_ground, 0);
	m_rootNode.SceneGraphNode::InsertObject(m_attr, 0);

	if( m_Calculated != NULL )
		m_rootNode.SceneGraphNode::CopySceneGraph(0, m_Calculated);
	else
		m_rootNode.SceneGraphNode::UpdateVolume(0);
}


hook_method<void (CWorld::*)(void)> CWorld::_FreeSceneGraph(SAKEXE, "CWorld::FreeSceneGraph");
void CWorld::FreeSceneGraph(void) // line 649-656
{
	return (this->*_FreeSceneGraph)();

	for( int i = 0; i < countof(m_rootNode.m_child); ++i )
	{
		delete m_rootNode.m_child[i];
		m_rootNode.m_child[i] = NULL;
	}
}


////////////////////////////////////////


SceneGraphNode::SceneGraphNode(void) // line 676-682
{
	m_parent = NULL;
	m_child[0] = NULL;
	m_child[1] = NULL;
	m_child[2] = NULL;
	m_child[3] = NULL;
	m_needUpdate = 1;
}


SceneGraphNode::~SceneGraphNode(void) // line 685-692
{
	for( int i = 0; i < countof(m_child); ++i )
	{
		delete m_child[i];
		m_child[i] = NULL;
	}
}


hook_method<void (SceneGraphNode::*)(int level)> SceneGraphNode::_Build(SAKEXE, "SceneGraphNode::Build");
void SceneGraphNode::Build(int level) // line 695-916
{
	return (this->*_Build)(level);

	m_center.y = 0.0;
	m_aabb.min.y = -infinity;
	m_aabb.max.y = infinity;
	m_center.x = (m_aabb.min.x + m_aabb.max.x) / 2;
	m_center.z = (m_aabb.max.z + m_aabb.min.z) / 2;

	if( level == 5 )
		return; // recursion end.

	m_child[0] = new SceneGraphNode();
	m_child[0]->m_parent = this;
	m_child[0]->m_aabb.min.x = m_aabb.min.x;
	m_child[0]->m_aabb.max.x = m_center.x;
	m_child[0]->m_aabb.min.z = m_aabb.min.z;
	m_child[0]->m_aabb.max.z = m_center.z;

	m_child[1] = new SceneGraphNode();
	m_child[1]->m_parent = this;
	m_child[1]->m_aabb.min.x = m_center.x;
	m_child[1]->m_aabb.max.x = m_aabb.max.x;
	m_child[1]->m_aabb.min.z = m_aabb.min.z;
	m_child[1]->m_aabb.max.z = m_center.z;

	m_child[2] = new SceneGraphNode();
	m_child[2]->m_parent = this;
	m_child[2]->m_aabb.min.x = m_aabb.min.x;
	m_child[2]->m_aabb.max.x = m_center.x;
	m_child[2]->m_aabb.min.z = m_center.z;
	m_child[2]->m_aabb.max.z = m_aabb.max.z;

	m_child[3] = new SceneGraphNode();
	m_child[3]->m_parent = this;
	m_child[3]->m_aabb.min.x = m_center.x;
	m_child[3]->m_aabb.max.x = m_aabb.max.x;
	m_child[3]->m_aabb.min.z = m_center.z;
	m_child[3]->m_aabb.max.z = m_aabb.max.z;

	for( int i = 0; i < countof(m_child); ++i )
		m_child[i]->SceneGraphNode::Build(level + 1);
}


hook_method<void (SceneGraphNode::*)(C3dActor* actor, int level)> SceneGraphNode::_InsertObject(SAKEXE, "?InsertObject@SceneGraphNode@@QAEXPAVC3dActor@@H@Z");
void SceneGraphNode::InsertObject(C3dActor* actor, int level) // line 919-940
{
	return (this->*_InsertObject)(actor, level);

	if( level == 5 )
	{
		m_actorList.push_back(actor);

		for( SceneGraphNode* i = this; i != NULL; i = i->m_parent )
			i->m_needUpdate = 1;
	}
	else
	{
		for( int i = 0; i < countof(m_child); ++i )
		{
			if( TestAABBvsOBBIntersection(actor->m_oBoundingBox, m_child[i]->m_aabb) )
				m_child[i]->SceneGraphNode::InsertObject(actor, level + 1);
		}
	}
}


hook_method<void (SceneGraphNode::*)(C3dGround* ground, int level)> SceneGraphNode::_InsertObject2(SAKEXE, "?InsertObject@SceneGraphNode@@QAEXPAVC3dGround@@H@Z");
void SceneGraphNode::InsertObject(C3dGround* ground, int level) // line 961-972
{
	return (this->*_InsertObject2)(ground, level);

	//TODO
}


hook_method<void (SceneGraphNode::*)(C3dAttr* attr, int level)> SceneGraphNode::_InsertObject3(SAKEXE, "?InsertObject@SceneGraphNode@@QAEXPAVC3dAttr@@H@Z");
void SceneGraphNode::InsertObject(C3dAttr* attr, int level) // line 975-986
{
	return (this->*_InsertObject3)(attr, level);

	//TODO
}


hook_method<void (SceneGraphNode::*)(C3dActor* actor, int level)> SceneGraphNode::_RemoveObject(SAKEXE, "SceneGraphNode::RemoveObject");
void SceneGraphNode::RemoveObject(C3dActor* actor, int level) // line 989
{
	return (this->*_RemoveObject)(actor, level);

	//TODO
}


hook_method<void (SceneGraphNode::*)(int level)> SceneGraphNode::_UpdateVolume(SAKEXE, "SceneGraphNode::UpdateVolume");
void SceneGraphNode::UpdateVolume(int level) // line 1017-1056
{
	return (this->*_UpdateVolume)(level);

	//TODO
}


hook_method<void (SceneGraphNode::*)(int level)> SceneGraphNode::_UpdateVolumeAfter(SAKEXE, "SceneGraphNode::UpdateVolumeAfter");
void SceneGraphNode::UpdateVolumeAfter(int level) // line 1059-1096
{
	return (this->*_UpdateVolumeAfter)(level);

	//TODO
}


hook_method<mystd::vector<C3dActor*>* (SceneGraphNode::*)(float x, float z, int level)> SceneGraphNode::_GetActorList(SAKEXE, "SceneGraphNode::GetActorList");
mystd::vector<C3dActor*>* SceneGraphNode::GetActorList(float x, float z, int level) // line 1099-1117
{
	return (this->*_GetActorList)(x, z, level);

	//TODO
}


hook_method<void (SceneGraphNode::*)(C3dActor* actor, int level)> SceneGraphNode::_InsertObjectAfter(SAKEXE, "SceneGraphNode::InsertObjectAfter");
void SceneGraphNode::InsertObjectAfter(C3dActor* actor, int level) // line 943-958
{
	return (this->*_InsertObjectAfter)(actor, level);

	//TODO
}


hook_method<void (SceneGraphNode::*)(CFile* fp, int Level)> SceneGraphNode::_LoadSceneGraph(SAKEXE, "SceneGraphNode::LoadSceneGraph");
void SceneGraphNode::LoadSceneGraph(CFile* fp, int Level) // line 1317-1340
{
	return (this->*_LoadSceneGraph)(fp, Level);

	fp->CFile::Read(&m_aabb.max.x, 4);
	fp->CFile::Read(&m_aabb.max.y, 4);
	fp->CFile::Read(&m_aabb.max.z, 4);
	fp->CFile::Read(&m_aabb.min.x, 4);
	fp->CFile::Read(&m_aabb.min.y, 4);
	fp->CFile::Read(&m_aabb.min.z, 4);
	fp->CFile::Read(&m_halfSize.x, 4);
	fp->CFile::Read(&m_halfSize.y, 4);
	fp->CFile::Read(&m_halfSize.z, 4);
	fp->CFile::Read(&m_center.x, 4);
	fp->CFile::Read(&m_center.y, 4);
	fp->CFile::Read(&m_center.z, 4);

	if( Level == 5 )
		return; // recursion end.

	for( int i = 0; i < countof(m_child); ++i )
		m_child[i]->SceneGraphNode::LoadSceneGraph(fp, Level + 1);
}


hook_method<void (SceneGraphNode::*)(int Level, SceneGraphNode* graph)> SceneGraphNode::_CopySceneGraph(SAKEXE, "SceneGraphNode::CopySceneGraph");
void SceneGraphNode::CopySceneGraph(int Level, SceneGraphNode* graph) // line 1343-1367
{
	return (this->*_CopySceneGraph)(Level, graph);

	m_needUpdate = 0;

	m_aabb.max.x = graph->m_aabb.max.x;
	m_aabb.max.y = graph->m_aabb.max.y;
	m_aabb.max.z = graph->m_aabb.max.z;
	m_aabb.min.x = graph->m_aabb.min.x;
	m_aabb.min.y = graph->m_aabb.min.y;
	m_aabb.min.z = graph->m_aabb.min.z;
	m_halfSize.x = graph->m_halfSize.x;
	m_halfSize.y = graph->m_halfSize.y;
	m_halfSize.z = graph->m_halfSize.z;
	m_center.x = graph->m_center.x;
	m_center.y = graph->m_center.y;
	m_center.z = graph->m_center.z;

	if( Level == 5 )
		return; // recursion end.

	for( int i = 0; i < countof(m_child); ++i )
		m_child[i]->SceneGraphNode::CopySceneGraph(Level + 1, graph->m_child[i]);
}


////////////////////////////////////////


CRayPicker::CRayPicker(void) // line 1120-1121
{
}


hook_method<void (CRayPicker::*)(const ray3d& ray, SceneGraphNode* rootNode)> CRayPicker::_Build(SAKEXE, "?Build@CRayPicker@@QAEXABUray3d@@PAUSceneGraphNode@@@Z");
void CRayPicker::Build(const ray3d& ray, SceneGraphNode* rootNode) // line 1124-1129
{
	return (this->*_Build)(ray, rootNode);

	m_ray.dir = ray.dir;
	m_ray.org = ray.org;
	m_ray.limit = infinity;
	this->CRayPicker::CullSceneNode(rootNode, 0); // inlined
}


hook_method<void (CRayPicker::*)(const lineSegment3d& ray, SceneGraphNode* rootNode)> CRayPicker::_Build2(SAKEXE, "?Build@CRayPicker@@QAEXABUlineSegment3d@@PAUSceneGraphNode@@@Z");
void CRayPicker::Build(const lineSegment3d& ray, SceneGraphNode* rootNode) // line 1132-1135
{
	return (this->*_Build2)(ray, rootNode);

	m_ray.org = ray.org;
	m_ray.dir = ray.dir;
	m_ray.limit = ray.limit;
	this->CRayPicker::CullSceneNode(rootNode, 0); // inlined
}


hook_method<int (CRayPicker::*)(SceneGraphNode* node)> CRayPicker::_CheckAABBIntersect(SAKEXE, "?CheckAABBIntersect@CRayPicker@@AAEHPAUSceneGraphNode@@@Z");
int CRayPicker::CheckAABBIntersect(SceneGraphNode* node) // line 1161-1235
{
	return (this->*_CheckAABBIntersect)(node);

	return this->CRayPicker::CheckAABBIntersect(node->m_aabb);
}


hook_method<int (CRayPicker::*)(const C3dAABB& aabb) const> CRayPicker::_CheckAABBIntersect2(SAKEXE, "?CheckAABBIntersect@CRayPicker@@QBEHABUC3dAABB@@@Z");
int CRayPicker::CheckAABBIntersect(const C3dAABB& aabb) const // line 1238-1314
{
	return (this->*_CheckAABBIntersect2)(aabb);

	float tMin = -infinity;
	float tMax = infinity;

	vector3d center;
	center.x = (aabb.min.x + aabb.max.x) / 2;
	center.y = (aabb.min.y + aabb.max.y) / 2;
	center.z = (aabb.min.z + aabb.max.z) / 2;

	vector3d halfSize;
	halfSize.x = aabb.max.x - center.x;
	halfSize.y = aabb.max.y - center.y;
	halfSize.z = aabb.max.z - center.z;

	vector3d p;
	p.x = center.x - m_ray.org.x;
	p.y = center.y - m_ray.org.y;
	p.z = center.z - m_ray.org.z;

	if( fabs(m_ray.dir.x) <= epsilon )
	{
		double hx = halfSize.x * 0.7;
		if( p.x + hx <= 0.0 || p.x - hx >= 0.0 )
			return 0;
	}
	else
	{
		double t1 = (p.x + halfSize.x) / m_ray.dir.x;
		double t2 = (p.x - halfSize.x) / m_ray.dir.x;
		if( t1 <= t2 )
		{
			if( tMin < t1 ) tMin = (float)t1;
			if( tMax > t2 ) tMax = (float)t2;
		}
		else
		{
			if( tMin < t2 ) tMin = (float)t2;
			if( tMax > t1 ) tMax = (float)t1;
		}

		if( tMin > tMax || tMax < 0.0 )
			return 0;
	}

	if( fabs(m_ray.dir.y) <= epsilon )
	{
		double hy = halfSize.y * 0.7;
		if( p.y + hy <= 0.0 || p.y - hy >= 0.0 )
			return 0;
	}
	else
	{
		double t1 = (p.y + halfSize.y) / m_ray.dir.y;
		double t2 = (p.y - halfSize.y) / m_ray.dir.y;
		if( t1 <= t2 )
		{
			if( tMin < t1 ) tMin = (float)t1;
			if( tMax > t2 ) tMax = (float)t2;
		}
		else
		{
			if( tMin < t2 ) tMin = (float)t2;
			if( tMax > t1 ) tMax = (float)t1;
		}

		if( tMin > tMax || tMax < 0.0 )
			return 0;
	}

	if( fabs(m_ray.dir.z) <= epsilon )
	{
		double hz = halfSize.z * 0.7;
		if( p.z + hz <= 0.0 || p.z - hz >= 0.0 )
			return 0;
	}
	else
	{
		double t1 = (p.z + halfSize.z) / m_ray.dir.z;
		double t2 = (p.z - halfSize.z) / m_ray.dir.z;
		if( t1 <= t2 )
		{
			if( tMin < t1 ) tMin = (float)t1;
			if( tMax > t2 ) tMax = (float)t2;
		}
		else
		{
			if( tMin < t2 ) tMin = (float)t2;
			if( tMax > t1 ) tMax = (float)t1;
		}

		if( tMin > tMax || tMax < 0.0 )
			return 0;
	}

	if( tMin > 0.0 )
	{// box is in front of ray in at least one axis
		if( tMin > m_ray.limit )
			return 0; // box is too far away
	}
	else
	{// we're inside the box
		if( tMax > m_ray.limit )
			return 0; // box is too large?
	}

	return 1;
}


hook_method<void (CRayPicker::*)(SceneGraphNode* node, int level)> CRayPicker::_CullSceneNode(SAKEXE, "CRayPicker::CullSceneNode");
void CRayPicker::CullSceneNode(SceneGraphNode* node, int level) // line 1143-1156
{
	return (this->*_CullSceneNode)(node, level);

	if( level == 5 )
	{
		m_cubeletList.push_back(node);
	}
	else
	{
		for( int i = 0; i < countof(node->m_child); ++i )
			if( this->CRayPicker::CheckAABBIntersect(node->m_child[i]) )
				this->CRayPicker::CullSceneNode(node->m_child[i], level + 1);
	}
}


////////////////////////////////////////


hook_func<bool (__cdecl *)(C3dOBB& obb, C3dAABB& aabb)> _TestAABBvsOBBIntersection(SAKEXE, "TestAABBvsOBBIntersection");
bool __cdecl TestAABBvsOBBIntersection(C3dOBB& obb, C3dAABB& aabb) // line 755-916
{
	return (_TestAABBvsOBBIntersection)(obb, aabb);

	//TODO
}


////////////////////////////////////////
