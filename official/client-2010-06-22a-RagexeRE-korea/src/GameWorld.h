#pragma once
#include "3dActor.h"
#include "3dLib/Prim.h"
#include "std/list"
#include "std/vector"
class C3dActor;
class C3dAttr;
class C3dGround;
class CGameActor;
class CGameObject;
class CItem;
class CMode;
class CPlayer;
class CSkill;


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

	//TODO
};
C_ASSERT( sizeof SceneGraphNode == 128 );


class CRayPicker
{
	/* this+ 0 */ public: mystd::list<SceneGraphNode*> m_cubeletList;
	/* this+12 */ private: lineSegment3d m_ray;

	public: CRayPicker::CRayPicker(void);
	public: void CRayPicker::Build(const ray3d& ray, SceneGraphNode* rootNode);

public:
	static hook_func<CRayPicker* (CRayPicker::*)(void)> CRayPicker::_cCRayPicker;
	static hook_func<void (CRayPicker::*)(const ray3d& ray, SceneGraphNode* rootNode)> CRayPicker::_Build;
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
	/* this+ 92 */ private: int m_isPKZone;
	/* this+ 96 */ private: BOOL m_isSiegeMode;
	/* this+100 */ private: int m_isBattleFieldMode;
	/* this+104 */ private: int m_isEventPVPMode;
	/* this+108 */ private: SceneGraphNode m_rootNode;
	/* this+236 */ private: SceneGraphNode* m_Calculated;

	public: CWorld::CWorld(void);
	public: virtual CWorld::~CWorld(void);
	public: CGameActor* CWorld::GetGameActorByAID(unsigned long GID);
	public: CItem* CWorld::GetItemByAID(unsigned long AID);
	public: SceneGraphNode* CWorld::GetRootNode();
	BOOL IsPKZone();
	BOOL IsSiegeMode();

public:
	static hook_func<CWorld* (CWorld::*)(void)> CWorld::_cCWorld;
	static hook_func<void (CWorld::*)(void)> CWorld::_dCWorld;
};
C_ASSERT( sizeof CWorld == 240 );
