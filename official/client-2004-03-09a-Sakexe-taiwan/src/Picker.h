#pragma once
#include "3dLib/Prim.h"


class CActorPickInfo
{
	/* this+ 0 */ public: vector3d m_vectors[2];
	/* this+24 */ public: unsigned long m_gid;
	/* this+28 */ public: int m_job;
	/* this+32 */ public: int m_classType;
	/* this+36 */ public: int m_isPkState;

	//public: CActorPickInfo(void);
	//public: ~CActorPickInfo(void);
	//public: unsigned long GetGID(void);
	//public: void SetJob(int);
	//public: int GetJob(void);
	//public: unsigned char CActorPickInfo::HitTest(vector2d p);
	//public: vector2d GetCenterPos(void);
};


class CActorPickNode
{
	/* this+ 0 */ public: //const CActorPickNode::`vftable';
	/* this+ 4 */ private: RECT m_region;
	/* this+20 */ private: CActorPickNode* m_child[4];
	/* this+36 */ private: mystd::list<CActorPickInfo*> m_pickInfoList;

	//public: CActorPickNode::CActorPickNode(void);
	//public: CActorPickNode::~CActorPickNode(void);
	public: void CActorPickNode::MakeQuardTree(int level, RECT region);
	public: void CActorPickNode::DeleteSubNode(void);
	public: void CActorPickNode::AddPickInfo(CActorPickInfo* pickInfo);
	public: CActorPickInfo* CActorPickNode::FindPickInfo(vector2d pos);
	//public: RECT CActorPickNode::MakeQuarter(RECT, int);
	//public: int CActorPickNode::GetQuarterNum(int, int);

private:
	static hook_method<void (CActorPickNode::*)(int level, RECT region)> CActorPickNode::_MakeQuardTree;
	static hook_method<void (CActorPickNode::*)(void)> CActorPickNode::_DeleteSubNode;
	static hook_method<void (CActorPickNode::*)(CActorPickInfo* pickInfo)> CActorPickNode::_AddPickInfo;
	static hook_method<CActorPickInfo* (CActorPickNode::*)(vector2d pos)> CActorPickNode::_FindPickInfo;
};
