#pragma once
#include "GameWorld.h"
#include "3dLib/Prim.h"
#include "Resource/Skybox.h"


struct ViewInfo3d
{
	/* this+ 0 */ float latitude;
	/* this+ 4 */ float longitude;
	/* this+ 8 */ float distance;
	/* this+12 */ vector3d at;
};


class CViewFrustum
{
	/* this+  0 */ private: plane3d m_planes[6];
	/* this+ 96 */ private: vector3d m_planeNormals[6];
	/* this+168 */ private: mystd::list<SceneGraphNode*> m_cubeletListTotal;
	/* this+180 */ private: mystd::list<SceneGraphNode*> m_cubeletListPartial;

	public: CViewFrustum::CViewFrustum(void);
	public: void CViewFrustum::Build(float hratio, float vratio, const matrix& viewMatrix, SceneGraphNode* rootNode);
	public: void CViewFrustum::Free(void);
	private: void CViewFrustum::CullSceneNode(SceneGraphNode* node, int level, bool isTotallyInside);
	private: int CViewFrustum::CheckAABBIntersect(SceneGraphNode* node);
	private: int CViewFrustum::CheckOBBIntersect(const C3dOBB& bb);

private:
	static hook_method<void (CViewFrustum::*)(float hratio, float vratio, const matrix& viewMatrix, SceneGraphNode* rootNode)> CViewFrustum::_Build;
	static hook_method<void (CViewFrustum::*)(void)> CViewFrustum::_Free;
	static hook_method<void (CViewFrustum::*)(SceneGraphNode* node, int level, bool isTotallyInside)> CViewFrustum::_CullSceneNode;
	static hook_method<int (CViewFrustum::*)(SceneGraphNode* node)> CViewFrustum::_CheckAABBIntersect;
	static hook_method<int (CViewFrustum::*)(const C3dOBB& bb)> CViewFrustum::_CheckOBBIntersect;

	friend class CView; // @see CView::OnRender()
};


class CView
{
	struct vtable_t
	{
		void* (CView::* scalar_deleting_destructor)(unsigned int flags);
		void (CView::* OnEnterFrame)(void);
		void (CView::* OnExitFrame)(void);
		void (CView::* OnRender)(void);
		void (CView::* OnCalcViewInfo)(void);
	};

	/* this+  0 */ public: //const CView::`vftable';
	/* this+  4 */ protected: int m_isQuake;
	/* this+  8 */ protected: unsigned long m_quakeStartTick;
	/* this+ 12 */ protected: float m_sideQuake;
	/* this+ 16 */ protected: float m_frontQuake;
	/* this+ 20 */ protected: float m_latitudeQuake;
	/* this+ 24 */ protected: unsigned long m_QuakeTime;
	/* this+ 28 */ protected: ViewInfo3d m_cur;
	/* this+ 52 */ protected: ViewInfo3d m_dest;
	/* this+ 76 */ protected: ViewInfo3d m_backupCur;
	/* this+100 */ protected: ViewInfo3d m_backupDest;
	/* this+124 */ protected: vector3d m_from;
	/* this+136 */ protected: vector3d m_up;
	/* this+148 */ protected: matrix m_viewMatrix;
	/* this+196 */ protected: matrix m_invViewMatrix;
	/* this+244 */ protected: CViewFrustum m_viewFrustum;
	/* this+436 */ protected: CWorld* m_world;
	/* this+440 */ protected: CSkyBoxEllipse* m_skyBox;
	/* this+444 */ protected: bool m_isFPSmode;

	public: CView::CView(void);
	public: virtual CView::~CView(void);
	public: virtual void CView::OnEnterFrame(void);
	public: virtual void CView::OnExitFrame(void);
	public: virtual void CView::OnRender(void);
	public: virtual void CView::OnCalcViewInfo(void);
	public: float CView::GetDestLongitude(void);
	public: float CView::GetDestLatitude(void);
	public: float CView::GetDestDistance(void);
	public: float CView::GetCurLongitude(void);
	public: float CView::GetCurLatitude(void);
	public: float CView::GetCurDistance(void);
	public: vector3d CView::GetCurAt(void);
	public: vector3d CView::GetFrom(void);
	public: matrix CView::GetViewMatrix(void);
	public: void CView::SetDestLongitude(float longitude);
	public: void CView::SetDestDistance(float distance);
	public: void CView::SetDestLatitude(float latitude);
	public: void CView::SetDestAt(float x, float y, float z);
	public: void CView::SetCurLongitude(float longitude);
	public: void CView::SetCurDistance(float distance);
	public: void CView::SetCurLatitude(float latitude);
	public: void CView::SetCurAt(float x, float y, float z);
	//public: void AdjustDestLongitude(float);
	//public: void HoldAt();
	//public: void ResetLongitude(float);
	//public: void ResetLatitude(float);
	//public: void ResetDistance(float);
	//public: void ResetAt(float, float, float);
	//public: void PushCamera();
	//public: void PopCamera();
	//public: void CView::AddLongitude(float);
	//public: void CView::AddLatitude(float);
	//public: void CView::AddDistance(float);
	public: void CView::SetQuake(int isQuake, int Type, float sideQuake, float frontQuake, float latitudeQuake);
	public: void CView::SetQuakeInfo(float sideQuake, float frontQuake, float latitudeQuake);
	public: void CView::GetEeyeVector(vector3d* eyeVector);
	//public: vector3d* GetEeyeFromVector();
	//public: bool IsFPSmode();
	protected: void CView::InterpolateViewInfo(void);
	protected: void CView::ProcessQuake(void);
	protected: void CView::BuildViewMatrix(void);

	/// @custom
	public: void CView::SetWorld(CWorld* world) { m_world = world; }

private:
	static hook_method<void (CView::*)(void)> CView::_OnEnterFrame;
	static hook_method<void (CView::*)(void)> CView::_OnExitFrame;
	static hook_method<void (CView::*)(void)> CView::_OnRender;
	static hook_method<void (CView::*)(void)> CView::_OnCalcViewInfo;
	static hook_method<float (CView::*)(void)> CView::_GetDestLongitude;
	static hook_method<float (CView::*)(void)> CView::_GetDestLatitude;
	static hook_method<float (CView::*)(void)> CView::_GetDestDistance;
	static hook_method<float (CView::*)(void)> CView::_GetCurLongitude;
	static hook_method<float (CView::*)(void)> CView::_GetCurLatitude;
	static hook_method<float (CView::*)(void)> CView::_GetCurDistance;
	static hook_method<vector3d (CView::*)(void)> CView::_GetCurAt;
	static hook_method<vector3d (CView::*)(void)> CView::_GetFrom;
	static hook_method<matrix (CView::*)(void)> CView::_GetViewMatrix;
	static hook_method<void (CView::*)(float longitude)> CView::_SetDestLongitude;
	static hook_method<void (CView::*)(float distance)> CView::_SetDestDistance;
	static hook_method<void (CView::*)(float latitude)> CView::_SetDestLatitude;
	static hook_method<void (CView::*)(float x, float y, float z)> CView::_SetDestAt;
	static hook_method<void (CView::*)(float longitude)> CView::_SetCurLongitude;
	static hook_method<void (CView::*)(float distance)> CView::_SetCurDistance;
	static hook_method<void (CView::*)(float latitude)> CView::_SetCurLatitude;
	static hook_method<void (CView::*)(float x, float y, float z)> CView::_SetCurAt;
	static hook_method<void (CView::*)(int isQuake, int Type, float sideQuake, float frontQuake, float latitudeQuake)> CView::_SetQuake;
	static hook_method<void (CView::*)(float sideQuake, float frontQuake, float latitudeQuake)> CView::_SetQuakeInfo;
	static hook_method<void (CView::*)(vector3d* eyeVector)> CView::_GetEeyeVector;
	static hook_method<void (CView::*)(void)> CView::_InterpolateViewInfo;
	static hook_method<void (CView::*)(void)> CView::_ProcessQuake;
	static hook_method<void (CView::*)(void)> CView::_BuildViewMatrix;
};
