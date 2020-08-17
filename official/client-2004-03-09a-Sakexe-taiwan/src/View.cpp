#include "Globals.h"
#include "ModeMgr.h"
#include "Player.h"
#include "View.h"
////////////////////////////////////////


int& rendered = VTOR<int>(SymDB::Add("rendered", SAKEXE, "rendered")); // = ?;


////////////////////////////////////////


CViewFrustum::CViewFrustum(void) // line 21-22
{
}


hook_method<void (CViewFrustum::*)(float hratio, float vratio, const matrix& viewMatrix, SceneGraphNode* rootNode)> CViewFrustum::_Build(SAKEXE, "CViewFrustum::Build");
void CViewFrustum::Build(float hratio, float vratio, const matrix& viewMatrix, SceneGraphNode* rootNode) // line 25-45
{
	return (this->*_Build)(hratio, vratio, viewMatrix, rootNode);

	//TODO
}


hook_method<void (CViewFrustum::*)(void)> CViewFrustum::_Free(SAKEXE, "CViewFrustum::Free");
void CViewFrustum::Free(void) // line 48-51
{
	return (this->*_Free)();

	m_cubeletListTotal.clear();
	m_cubeletListPartial.clear();
}


hook_method<void (CViewFrustum::*)(SceneGraphNode* node, int level, bool isTotallyInside)> CViewFrustum::_CullSceneNode(SAKEXE, "CViewFrustum::CullSceneNode");
void CViewFrustum::CullSceneNode(SceneGraphNode* node, int level, bool isTotallyInside) // line 110-134
{
	return (this->*_CullSceneNode)(node, level, isTotallyInside);

	//TODO
}


hook_method<int (CViewFrustum::*)(SceneGraphNode* node)> CViewFrustum::_CheckAABBIntersect(SAKEXE, "CViewFrustum::CheckAABBIntersect");
int CViewFrustum::CheckAABBIntersect(SceneGraphNode* node) // line 57-81
{
	return (this->*_CheckAABBIntersect)(node);

	//TODO
}


hook_method<int (CViewFrustum::*)(const C3dOBB& bb)> CViewFrustum::_CheckOBBIntersect(SAKEXE, "CViewFrustum::CheckOBBIntersect");
int CViewFrustum::CheckOBBIntersect(const C3dOBB& bb) // line 84-107
{
	return (this->*_CheckOBBIntersect)(bb);

	//TODO
}


////////////////////////////////////////


CView::CView(void) // line 142-148
{
	m_cur.longitude = 0.0;
	m_isQuake = 0;
	m_quakeStartTick = 0;
	m_isFPSmode = 0;
	m_skyBox = NULL;
}


CView::~CView(void) // line 151-153
{
	delete m_skyBox;
}


hook_method<void (CView::*)(void)> CView::_OnEnterFrame(SAKEXE, "CView::OnEnterFrame");
void CView::OnEnterFrame(void) // line 156-163
{
	return (this->*_OnEnterFrame)();

	m_cur.distance = 300.0;
	m_dest.distance = 300.0;
	m_cur.latitude = -45.0;
	m_dest.latitude = -45.0;
	m_cur.longitude = 0.0;
	m_dest.longitude = 0.0;
	m_cur.at = vector3d(0.0, 0.0, 0.0);
	m_dest.at = vector3d(0.0, 0.0, 0.0);
	m_up = vector3d(0.0, 0.0, 0.0);
}


hook_method<void (CView::*)(void)> CView::_OnExitFrame(SAKEXE, "CView::OnExitFrame");
void CView::OnExitFrame(void) // line 166-167
{
	return (this->*_OnExitFrame)();

	;
}


hook_method<void (CView::*)(void)> CView::_OnRender(SAKEXE, "CView::OnRender");
void CView::OnRender(void) // line 256-374
{
	return (this->*_OnRender)();

	g_modeMgr.CModeMgr::GetGameMode(); // unused?
	rendered = 1;

	m_viewFrustum.CViewFrustum::Build(g_renderer->CRenderer::GetHRatio(), g_renderer->CRenderer::GetVRatio(), m_viewMatrix, m_world->CWorld::GetRootNode());

	g_drawRect.top = 999;
	g_drawRect.bottom = 0;
	g_drawRect.left = 999;
	g_drawRect.right = 0;

	for( mystd::list<SceneGraphNode*>::iterator itNode = m_viewFrustum.m_cubeletListPartial.begin(); itNode != m_viewFrustum.m_cubeletListPartial.end(); ++itNode )
	{
		SceneGraphNode* node = *itNode;

		for( mystd::vector<C3dActor*>::iterator itActor = node->m_actorList.begin(); itActor != node->m_actorList.end(); ++itActor )
		{
			C3dActor* actor = *itActor;

			if( actor->m_renderSignature == g_renderer->m_curFrame )
				continue;

			int ret = m_viewFrustum.CViewFrustum::CheckOBBIntersect(actor->m_oBoundingBox);
			actor->C3dActor::OnProcess();
			if( ret == 1 )
				actor->C3dActor::Render(m_viewMatrix, false, 0);
			if( ret == 2 )
				actor->C3dActor::Render(m_viewMatrix, true, 0);

			actor->m_renderSignature = g_renderer->m_curFrame;
		}

		node->m_ground->Render(m_viewMatrix, node->m_groundArea, true);

		if( g_drawRect.top > node->m_groundArea.top )
			g_drawRect.top = node->m_groundArea.top;
		if( g_drawRect.bottom < node->m_groundArea.bottom )
			g_drawRect.bottom = node->m_groundArea.bottom;
		if( g_drawRect.left > node->m_groundArea.left )
			g_drawRect.left = node->m_groundArea.left;
		if( g_drawRect.right < node->m_groundArea.right )
			g_drawRect.right = node->m_groundArea.right;
	}

	for( mystd::list<SceneGraphNode*>::iterator itNode = m_viewFrustum.m_cubeletListTotal.begin(); itNode != m_viewFrustum.m_cubeletListTotal.end(); ++itNode )
	{
		SceneGraphNode* node = *itNode;

		for( mystd::vector<C3dActor*>::iterator itActor = node->m_actorList.begin(); itActor != node->m_actorList.end(); ++itActor )
		{
			C3dActor* actor = *itActor;

			if( actor->m_renderSignature == g_renderer->m_curFrame )
				continue;

			actor->C3dActor::Render(m_viewMatrix, false, 0);
			actor->m_renderSignature = g_renderer->m_curFrame;
		}

		node->m_ground->Render(m_viewMatrix, node->m_groundArea, false);

		if( g_drawRect.top > node->m_groundArea.top )
			g_drawRect.top = node->m_groundArea.top;
		if( g_drawRect.bottom < node->m_groundArea.bottom )
			g_drawRect.bottom = node->m_groundArea.bottom;
		if( g_drawRect.left > node->m_groundArea.left )
			g_drawRect.left = node->m_groundArea.left;
		if( g_drawRect.right < node->m_groundArea.right )
			g_drawRect.right = node->m_groundArea.right;
	}

	if( !g_groundAttrPosInfo.isRendered )
		m_world->m_ground->RenderAttrTile(m_viewMatrix, g_groundAttrPosInfo.x, g_groundAttrPosInfo.y, g_groundAttrPosInfo.cellColor);

	for( mystd::list<CGameObject*>::iterator itObject = m_world->m_gameObjectList.begin(); itObject != m_world->m_gameObjectList.end(); ++itObject )
		(*itObject)->Render(m_viewMatrix);

	g_renderer->m_eyeVector.x = m_cur.at.x - m_from.x;
	g_renderer->m_eyeVector.y = m_cur.at.y - m_from.y;
	g_renderer->m_eyeVector.z = m_cur.at.z - m_from.z;
	g_renderer->m_eyeVector.vector3d::Normalize(); // inlined

	m_viewFrustum.CViewFrustum::Free(); // inlined
	m_world->m_ground->FlushGround(m_viewMatrix);
}


hook_method<void (CView::*)(void)> CView::_OnCalcViewInfo(SAKEXE, "CView::OnCalcViewInfo");
void CView::OnCalcViewInfo(void) // line 185-189
{
	return (this->*_OnCalcViewInfo)();

	m_dest.at = m_world->m_player->m_pos;
	this->CView::InterpolateViewInfo();
	this->CView::ProcessQuake();
	this->CView::BuildViewMatrix();
}


//hook_method<float (CView::*)(void)> CView::_GetDestLongitude(SAKEXE, "CView::GetDestLongitude");
float CView::GetDestLongitude(void) // line ???-???
{
//	return (this->*_GetDestLongitude)();

	return m_dest.longitude;
}


//hook_method<float (CView::*)(void)> CView::_GetDestLatitude(SAKEXE, "CView::GetDestLatitude");
float CView::GetDestLatitude(void) // line ???-???
{
//	return (this->*_GetDestLatitude)();

	return m_dest.latitude;
}


//hook_method<float (CView::*)(void)> CView::_GetDestDistance(SAKEXE, "CView::GetDestDistance");
float CView::GetDestDistance(void) // line ???-???
{
//	return (this->*_GetDestDistance)();

	return m_dest.distance;
}


//hook_method<float (CView::*)(void)> CView::_GetCurLongitude(SAKEXE, "CView::GetCurLongitude");
float CView::GetCurLongitude(void) // line ???-???
{
//	return (this->*_GetCurLongitude)();

	return m_cur.longitude;
}


//hook_method<float (CView::*)(void)> CView::_GetCurLatitude(SAKEXE, "CView::GetCurLatitude");
float CView::GetCurLatitude(void) // line ???-???
{
//	return (this->*_GetCurLatitude)();

	return m_cur.latitude;
}


//hook_method<float (CView::*)(void)> CView::_GetCurDistance(SAKEXE, "CView::GetCurDistance");
float CView::GetCurDistance(void) // line ???-???
{
//	return (this->*_GetCurDistance)();

	return m_cur.distance;
}


//hook_method<vector3d (CView::*)(void)> CView::_GetCurAt(SAKEXE, "CView::GetCurAt");
vector3d CView::GetCurAt(void) // line ???-???
{
//	return (this->*_GetCurAt)();

	return m_cur.at;
}


//hook_method<vector3d (CView::*)(void)> CView::_GetFrom(SAKEXE, "CView::GetFrom");
vector3d CView::GetFrom(void) // line ???-???
{
//	return (this->*_GetFrom)();

	return m_from;
}


//hook_method<matrix (CView::*)(void)> CView::_GetViewMatrix(SAKEXE, "CView::GetViewMatrix");
matrix CView::GetViewMatrix(void) // line ???-???
{
//	return (this->*_GetViewMatrix)();

	return m_invViewMatrix; // guessed
}


//hook_method<void (CView::*)(float longitude)> CView::_SetDestLongitude(SAKEXE, "CView::SetDestLongitude");
void CView::SetDestLongitude(float longitude) // line ???-???
{
//	return (this->*_SetDestLongitude)(longitude);

	m_dest.longitude = longitude;
}


//hook_method<void (CView::*)(float distance)> CView::_SetDestDistance(SAKEXE, "CView::SetDestDistance");
void CView::SetDestDistance(float distance) // line ???-???
{
//	return (this->*_SetDestDistance)(distance);

	m_dest.distance = distance;
}


//hook_method<void (CView::*)(float latitude)> CView::_SetDestLatitude(SAKEXE, "CView::SetDestLatitude");
void CView::SetDestLatitude(float latitude) // line ???-???
{
//	return (this->*_SetDestLatitude)(latitude);

	m_dest.latitude = latitude;
}


//hook_method<void (CView::*)(float x, float y, float z)> CView::_SetDestAt(SAKEXE, "CView::SetDestAt");
void CView::SetDestAt(float x, float y, float z) // line ???-???
{
//	return (this->*_SetDestAt)(x, y, z);

	m_dest.at.x = x;
	m_dest.at.y = y;
	m_dest.at.z = z;
}


//hook_method<void (CView::*)(float longitude)> CView::_SetCurLongitude(SAKEXE, "CView::SetCurLongitude");
void CView::SetCurLongitude(float longitude) // line ???-???
{
//	return (this->*_SetCurLongitude)(longitude);

	m_cur.longitude = longitude;
}


//hook_method<void (CView::*)(float distance)> CView::_SetCurDistance(SAKEXE, "CView::SetCurDistance");
void CView::SetCurDistance(float distance) // line ???-???
{
//	return (this->*_SetCurDistance)(distance);

	m_cur.distance = distance;
}


//hook_method<void (CView::*)(float latitude)> CView::_SetCurLatitude(SAKEXE, "CView::SetCurLatitude");
void CView::SetCurLatitude(float latitude) // line ???-???
{
//	return (this->*_SetCurLatitude)(latitude);

	m_cur.latitude = latitude;
}


//hook_method<void (CView::*)(float x, float y, float z)> CView::_SetCurAt(SAKEXE, "CView::SetCurAt");
void CView::SetCurAt(float x, float y, float z) // line ???-???
{
//	return (this->*_SetCurAt)(x, y, z);

	m_cur.at.x = x;
	m_cur.at.y = y;
	m_cur.at.z = z;
}


hook_method<void (CView::*)(int isQuake, int Type, float sideQuake, float frontQuake, float latitudeQuake)> CView::_SetQuake(SAKEXE, "CView::SetQuake");
void CView::SetQuake(int isQuake, int Type, float sideQuake, float frontQuake, float latitudeQuake) // line 229-246
{
	return (this->*_SetQuake)(isQuake, Type, sideQuake, frontQuake, latitudeQuake);

	m_isQuake = isQuake;
	m_quakeStartTick = timeGetTime();
	m_sideQuake = sideQuake;
	m_frontQuake = frontQuake;
	m_latitudeQuake = latitudeQuake;
	m_QuakeTime = ( Type == 0 ) ? 650 : ( Type == 1 ) ? 200 : Type;
}


hook_method<void (CView::*)(float sideQuake, float frontQuake, float latitudeQuake)> CView::_SetQuakeInfo(SAKEXE, "CView::SetQuakeInfo");
void CView::SetQuakeInfo(float sideQuake, float frontQuake, float latitudeQuake) // line 249-253
{
	return (this->*_SetQuakeInfo)(sideQuake, frontQuake, latitudeQuake);

	m_sideQuake = sideQuake;
	m_frontQuake = frontQuake;
	m_latitudeQuake = latitudeQuake;
}


hook_method<void (CView::*)(vector3d* eyeVector)> CView::_GetEeyeVector(SAKEXE, "CView::GetEeyeVector");
void CView::GetEeyeVector(vector3d* eyeVector) // line 460-463
{
	return (this->*_GetEeyeVector)(eyeVector);

	//TODO
}


hook_method<void (CView::*)(void)> CView::_InterpolateViewInfo(SAKEXE, "CView::InterpolateViewInfo");
void CView::InterpolateViewInfo(void) // line 382-436
{
	return (this->*_InterpolateViewInfo)();

	//TODO
}


hook_method<void (CView::*)(void)> CView::_ProcessQuake(SAKEXE, "CView::ProcessQuake");
void CView::ProcessQuake(void) // line 195-226
{
	return (this->*_ProcessQuake)();

	//TODO
}


hook_method<void (CView::*)(void)> CView::_BuildViewMatrix(SAKEXE, "CView::BuildViewMatrix");
void CView::BuildViewMatrix(void) // line 439-457
{
	return (this->*_BuildViewMatrix)();

	//TODO
}


////////////////////////////////////////
