#pragma once
#include "3dLib/Prim.h" // vector3d, vector3d
#include "std/list"


class CActorPickInfo
{
	/* this+ 0 */ public: vector3d m_vectors[2];
	/* this+24 */ public: DWORD m_gid;
	/* this+28 */ public: int m_job;
	/* this+32 */ public: int m_classType;
	/* this+36 */ public: int m_isPkState;

	//...
};


class CActorPickNode
{
	/* this+ 0 */ public: //const CActorPickNode::`vftable';
	/* this+ 4 */ RECT m_region;
	/* this+20 */ CActorPickNode* m_child[4];
	/* this+36 */ mystd::list<CActorPickInfo*> m_pickInfoList;

	public: CActorPickInfo* CActorPickNode::FindPickInfo(vector2d pos);
	//...

private:
	static hook_func<CActorPickInfo* (CActorPickNode::*)(vector2d pos)> CActorPickNode::_FindPickInfo;
};
