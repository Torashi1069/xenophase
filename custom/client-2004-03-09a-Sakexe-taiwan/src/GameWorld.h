#pragma once
#include "3dActor.h" // C3dAABB
#include "3dGround.h"
#include "Struct.h"
#include "3dLib/Prim.h" // vector3d
class CGameObject;
class CGameActor;
class CItem;
class CMode;
class CSkill;
class CPlayer;
class C3dAttr;
class C3dActor;
class CFile;


struct SceneGraphNode
{
	/* this+  0 */ SceneGraphNode* m_parent;
	/* this+  4 */ SceneGraphNode* m_child[4];
	/* this+ 20 */ C3dAABB m_aabb;
	/* this+ 44 */ vector3d m_center;
	/* this+ 56 */ vector3d m_halfSize;
	/* this+ 68 */ int m_needUpdate;
	/* this+ 72 */ mystd::vector<C3dActor*> m_actorList;
	/* this+ 88 */ C3dGround* m_ground;
	/* this+ 92 */ RECT m_groundArea;
	/* this+108 */ C3dAttr* m_attr;
	/* this+112 */ RECT m_attrArea;

	public: SceneGraphNode::SceneGraphNode(void);
	public: SceneGraphNode::~SceneGraphNode(void);
	public: void SceneGraphNode::Build(int level);
	public: void SceneGraphNode::InsertObject(C3dActor* actor, int level);
	public: void SceneGraphNode::InsertObject(C3dGround* ground, int level);
	public: void SceneGraphNode::InsertObject(C3dAttr* attr, int level);
	public: void SceneGraphNode::RemoveObject(C3dActor* actor, int level);
	public: void SceneGraphNode::UpdateVolume(int level);
	public: void SceneGraphNode::UpdateVolumeAfter(int level);
	public: mystd::vector<C3dActor*>* SceneGraphNode::GetActorList(float x, float z, int level);
	public: void SceneGraphNode::InsertObjectAfter(C3dActor* actor, int level);
	public: void SceneGraphNode::LoadSceneGraph(CFile* fp, int Level);
	public: void SceneGraphNode::CopySceneGraph(int Level, SceneGraphNode* graph);

private:
	static hook_method<void (SceneGraphNode::*)(int level)> SceneGraphNode::_Build;
	static hook_method<void (SceneGraphNode::*)(C3dActor* actor, int level)> SceneGraphNode::_InsertObject;
	static hook_method<void (SceneGraphNode::*)(C3dGround* ground, int level)> SceneGraphNode::_InsertObject2;
	static hook_method<void (SceneGraphNode::*)(C3dAttr* attr, int level)> SceneGraphNode::_InsertObject3;
	static hook_method<void (SceneGraphNode::*)(C3dActor* actor, int level)> SceneGraphNode::_RemoveObject;
	static hook_method<void (SceneGraphNode::*)(int level)> SceneGraphNode::_UpdateVolume;
	static hook_method<void (SceneGraphNode::*)(int level)> SceneGraphNode::_UpdateVolumeAfter;
	static hook_method<mystd::vector<C3dActor*>* (SceneGraphNode::*)(float x, float z, int level)> SceneGraphNode::_GetActorList;
	static hook_method<void (SceneGraphNode::*)(C3dActor* actor, int level)> SceneGraphNode::_InsertObjectAfter;
	static hook_method<void (SceneGraphNode::*)(CFile* fp, int Level)> SceneGraphNode::_LoadSceneGraph;
	static hook_method<void (SceneGraphNode::*)(int Level, SceneGraphNode* graph)> SceneGraphNode::_CopySceneGraph;
};


class CRayPicker
{
	/* this+ 0 */ public: mystd::list<SceneGraphNode*> m_cubeletList;
	/* this+12 */ private: lineSegment3d m_ray;

	public: CRayPicker::CRayPicker(void);
	public: void CRayPicker::Build(const ray3d& ray, SceneGraphNode* rootNode);
	public: void CRayPicker::Build(const lineSegment3d& ray, SceneGraphNode* rootNode);
	//public: void CRayPicker::Free();
	public: int CRayPicker::CheckAABBIntersect(SceneGraphNode* node);
	public: int CRayPicker::CheckAABBIntersect(const C3dAABB& aabb) const;
	private: void CRayPicker::CullSceneNode(SceneGraphNode* node, int level);

private:
	static hook_method<void (CRayPicker::*)(const ray3d& ray, SceneGraphNode* rootNode)> CRayPicker::_Build;
	static hook_method<void (CRayPicker::*)(const lineSegment3d& ray, SceneGraphNode* rootNode)> CRayPicker::_Build2;
	static hook_method<int (CRayPicker::*)(SceneGraphNode* node)> CRayPicker::_CheckAABBIntersect;
	static hook_method<int (CRayPicker::*)(const C3dAABB& aabb) const> CRayPicker::_CheckAABBIntersect2;
	static hook_method<void (CRayPicker::*)(SceneGraphNode* node, int level)> CRayPicker::_CullSceneNode;
};


class CWorld
{
	/* this+  0 */ public: //const CWorld::`vftable';
	/* this+  4 */ public: CMode* m_curMode;
	/* this+  8 */ public: mystd::list<CGameObject*> m_gameObjectList;
	/* this+ 20 */ public: mystd::list<CGameActor*> m_actorList;
	/* this+ 32 */ public: mystd::list<CItem*> m_itemList;
	/* this+ 44 */ public: mystd::list<CSkill*> m_skillList;
	/* this+ 56 */ public: C3dGround* m_ground;
	/* this+ 60 */ public: CPlayer* m_player;
	/* this+ 64 */ public: C3dAttr* m_attr;
	/* this+ 68 */ public: mystd::vector<C3dActor*> m_bgObjList;
	/* this+ 84 */ public: long m_bgObjCount;
	/* this+ 88 */ public: long m_bgObjThread;
	/* this+ 92 */ private: BOOL m_isPKZone;
	/* this+ 96 */ private: BOOL m_isSiegeMode;
	/* this+100 */ private: BOOL m_isEventPVPMode;
	/* this+104 */ private: SceneGraphNode m_rootNode;
	/* this+232 */ private: SceneGraphNode* m_Calculated;
	/* this+236 */ private: int m_nNightCnt;
	/* this+240 */ private: int m_bNight;

	public: CWorld::CWorld(void);
	public: virtual CWorld::~CWorld(void);
	public: void CWorld::OnEnterFrame(void);
	public: void CWorld::MakeFixedActor(void);
	public: void CWorld::OnExitFrame(void);
	public: void CWorld::ProcessActors(void);
	public: void CWorld::RemoveGameObject(CGameObject* object);
	//public: void CWorld::InitPlayer();
	//public: int CWorld::CheckAttr(struct vector3d);
	//public: int CWorld::CheckGround(struct vector3d);
	//public: void CWorld::AdjustPos(struct vector3d &);
	//public: void CWorld::AdjustPos2(struct vector3d &);
	//public: float CWorld::CalcShadowHeight(struct vector3d &);
	public: CGameActor* CWorld::GetGameActorByAID(unsigned long GID);
	public: CItem* CWorld::GetItemByAID(unsigned long AID);
	public: CSkill* CWorld::GetSkillByAID(unsigned long AID);
	public: bool CWorld::RemoveSkill(unsigned long AID);
	//public: unsigned char CWorld::RemoveGameActor(CGameObject*);
	//public: unsigned char CWorld::RemoveGameActor(unsigned long);
	public: bool CWorld::RemoveItem(unsigned long ITAID);
	public: void CWorld::RemoveGameActorAll(void);
	//public: void CWorld::GetServerCoor(float, float, int &, int &);
	//public: void CWorld::GetClientCoor(float, float, float &, float &);
	//public: void CWorld::GetClientCoor(int, int, float &, float &);
	public: SceneGraphNode* CWorld::GetRootNode(void);
	//public: void SetCellInfo(int, int, int);
	//public: void CWorld::Add3DActorToWorld(C3dActor* actor);
	public: void CWorld::WaitForThreadEnd(void);
	public: void CWorld::SetPKZone(BOOL isPKZone);
	public: void CWorld::SetSiegeMode(BOOL isSiegeMode);
	public: void CWorld::SetEventPVPMode(BOOL isEventPVPMode);
	public: BOOL CWorld::IsPKZone(void);
	public: BOOL CWorld::IsSiegeMode(void);
	public: BOOL CWorld::IsEventPVPMode(void);
	private: void CWorld::BuildSceneGraph(void);
	private: void CWorld::FreeSceneGraph(void);

private:
	static hook_method<void (CWorld::*)(void)> CWorld::_OnEnterFrame;
	static hook_method<void (CWorld::*)(void)> CWorld::_MakeFixedActor;
	static hook_method<void (CWorld::*)(void)> CWorld::_OnExitFrame;
	static hook_method<void (CWorld::*)(void)> CWorld::_ProcessActors;
	static hook_method<void (CWorld::*)(CGameObject* object)> CWorld::_RemoveGameObject;
	static hook_method<CGameActor* (CWorld::*)(unsigned long GID)> CWorld::_GetGameActorByAID;
	static hook_method<CItem* (CWorld::*)(unsigned long AID)> CWorld::_GetItemByAID;
	static hook_method<CSkill* (CWorld::*)(unsigned long AID)> CWorld::_GetSkillByAID;
	static hook_method<bool (CWorld::*)(unsigned long AID)> CWorld::_RemoveSkill;
	static hook_method<bool (CWorld::*)(unsigned long ITAID)> CWorld::_RemoveItem;
	static hook_method<void (CWorld::*)(void)> CWorld::_RemoveGameActorAll;
	static hook_method<SceneGraphNode* (CWorld::*)(void)> CWorld::_GetRootNode;
	static hook_method<void (CWorld::*)(void)> CWorld::_WaitForThreadEnd;
	static hook_method<void (CWorld::*)(BOOL isPKZone)> CWorld::_SetPKZone;
	static hook_method<void (CWorld::*)(BOOL isSiegeMode)> CWorld::_SetSiegeMode;
	static hook_method<void (CWorld::*)(BOOL isEventPVPMode)> CWorld::_SetEventPVPMode;
	static hook_method<BOOL (CWorld::*)(void)> CWorld::_IsPKZone;
	static hook_method<BOOL (CWorld::*)(void)> CWorld::_IsSiegeMode;
	static hook_method<BOOL (CWorld::*)(void)> CWorld::_IsEventPVPMode;
	static hook_method<void (CWorld::*)(void)> CWorld::_BuildSceneGraph;
	static hook_method<void (CWorld::*)(void)> CWorld::_FreeSceneGraph;
};
