#pragma once
#include "Struct.h"
#include "3dLib/Anim.h"
#include "3dLib/Prim.h"
class C3dActor;
class C3dGround15;
class C3dMesh;
class C3dModelRes;
class CRayPicker;
class CRenderer;
struct CVolumeBox;
struct C3dNodeRes;


struct C3dOBB // oBoundingBox
{
	/* this+ 0 */ vector3d halfSize;
	/* this+12 */ vector3d center;
	/* this+24 */ vector3d u;
	/* this+36 */ vector3d v;
	/* this+48 */ vector3d w;
	/* this+60 */ vector3d vertices[8];
};


struct C3dAABB // aaBoundingBox
{
	/* this+ 0 */ vector3d min;
	/* this+12 */ vector3d max;
};


class C3dNode
{
	struct vtable_t
	{
		void (C3dNode::* Render)(const matrix& ptm, int flipNormal, bool clip);
		void (C3dNode::* AssignModel)(C3dNodeRes* modelNode);
		void (C3dNode::* UpdateVertexColor)(const matrix& ptm, const vector3d& light, const vector3d& diffuseCol, const vector3d& ambientCol, int shadeType);
		void* (C3dNode::* scalar_deleting_destructor)(unsigned int flags);
	};

	struct ColorInfo
	{
		union
		{
		/* this+ 0 */ unsigned long color[3];
		/* this+ 0 */ COLOR argb[3];
		};
		/* this+12 */ vector2d uv[3];
	};

	/* this+  0 */ public: //const C3dNode::`vftable';
	/* this+  4 */ protected: C3dActor* m_master;
	/* this+  8 */ protected: char m_name[128];
	/* this+136 */ protected: int m_numTexture;
	/* this+140 */ protected: mystd::vector<CTexture*> m_texture;
	/* this+156 */ protected: C3dMesh* m_mesh;
	/* this+160 */ protected: float m_opacity;
	/* this+164 */ protected: C3dNode* m_parent;
	/* this+168 */ protected: mystd::list<C3dNode*> m_child;
	/* this+180 */ protected: matrix m_ltm;
	/* this+228 */ protected: C3dPosAnim m_posAnim;
	/* this+244 */ protected: C3dRotAnim m_rotAnim;
	/* this+260 */ protected: C3dScaleAnim m_scaleAnim;
	/* this+276 */ protected: mystd::vector<C3dNode::ColorInfo> m_colorInfo;
	/* this+292 */ protected: int m_isAlphaForPlayer;
	/* this+296 */ protected: C3dAABB m_aabb;
	/* this+320 */ protected: mystd::vector<int> m_destVertCol;

	public: virtual void C3dNode::Render(const matrix& ptm, int flipNormal, bool clip);
	public: virtual void C3dNode::AssignModel(C3dNodeRes* modelNode);
	public: virtual void C3dNode::UpdateVertexColor(const matrix& ptm, const vector3d& light, const vector3d& diffuseCol, const vector3d& ambientCol, int shadeType);
	protected: C3dNode::C3dNode(void);
	protected: virtual C3dNode::~C3dNode(void);
	protected: void C3dNode::Reset(void);
	protected: void C3dNode::SetFrame(int framepos);
	protected: void C3dNode::UpdateBound(C3dAABB* box, const matrix& ptm);
	protected: void C3dNode::UpdateAABB(const matrix& ptm, const matrix& wtm);
	protected: void C3dNode::CheckAABB(const CRayPicker& rayPicker);
	protected: void C3dNode::UpdateDestVertColor(CRenderer* renderer, const matrix& nodeTM, C3dGround15* pGround);
	protected: C3dNode* C3dNode::FindNode(const char* name);
	protected: void C3dNode::SetToAlpha(void);

private:
	static hook_method<void (C3dNode::*)(const matrix& ptm, int flipNormal, bool clip)> C3dNode::_Render;
	static hook_method<void (C3dNode::*)(C3dNodeRes* modelNode)> C3dNode::_AssignModel;
	static hook_method<void (C3dNode::*)(const matrix& ptm, const vector3d& light, const vector3d& diffuseCol, const vector3d& ambientCol, int shadeType)> C3dNode::_UpdateVertexColor;
	static hook_method<void (C3dNode::*)(void)> C3dNode::_Reset;
	static hook_method<void (C3dNode::*)(int framepos)> C3dNode::_SetFrame;
	static hook_method<void (C3dNode::*)(C3dAABB* box, const matrix& ptm)> C3dNode::_UpdateBound;
	static hook_method<void (C3dNode::*)(const matrix& ptm, const matrix& wtm)> C3dNode::_UpdateAABB;
	static hook_method<void (C3dNode::*)(const CRayPicker& rayPicker)> C3dNode::_CheckAABB;
	static hook_method<void (C3dNode::*)(CRenderer* renderer, const matrix& nodeTM, C3dGround15* pGround)> C3dNode::_UpdateDestVertColor;
	static hook_method<C3dNode* (C3dNode::*)(const char* name)> C3dNode::_FindNode;
	static hook_method<void (C3dNode::*)(void)> C3dNode::_SetToAlpha;

	friend class C3dActor;
};


class C3dActor
{
	/* this+  0 */ private: vector3d m_pos;
	/* this+ 12 */ private: vector3d m_rot;
	/* this+ 24 */ private: vector3d m_scale;
	/* this+ 36 */ private: int m_shadeType;
	/* this+ 40 */ private: C3dNode* m_node;
	/* this+ 44 */ private: char m_name[128];
	/* this+172 */ private: int m_curMotion;
	/* this+176 */ private: int m_animType;
	/* this+180 */ private: float m_animSpeed;
	/* this+184 */ private: int m_animLen;
	/* this+188 */ private: int m_isMatrixNeedUpdate;
	/* this+192 */ private: matrix m_wtm;
	/* this+240 */ private: matrix m_iwtm;
	/* this+288 */ private: vector3d m_posOffset;
	/* this+300 */ private: int m_isBbNeedUpdate;
	/* this+304 */ private: C3dOBB m_oBoundingBox;
	/* this+460 */ private: C3dAABB m_aaBoundingBox;
	/* this+484 */ private: int m_renderSignature;
	/* this+488 */ private: int m_isHideCheck;
	/* this+492 */ private: bool m_isHalfAlpha;
	/* this+493 */ private: unsigned char m_fadeAlphaCnt;
	/* this+496 */ private: int m_blockType;
	/* this+500 */ private: mystd::list<CVolumeBox*> m_volumeBoxList;

	public: C3dActor::C3dActor(void);
	public: C3dActor::~C3dActor(void);
	//public: void OnInit();
	public: void C3dActor::Reset(void);
	public: void C3dActor::SetFrame(int framepos);
	public: void C3dActor::SetPos(const vector3d& pos);
	public: void C3dActor::SetRot(const vector3d& rot);
	public: void C3dActor::SetScale(const vector3d& scale);
	public: void C3dActor::SetOpacity(float opacity);
	public: void C3dActor::SetAnimType(int animType);
	//public: struct vector3d GetPos();
	public: void C3dActor::OnProcess(void);
	public: void C3dActor::Render(matrix& ctm, bool clip, int flagRF);
	public: void C3dActor::AssignModel(C3dModelRes* model);
	public: void C3dActor::UpdateVertexColor(const vector3d& lightDir, const vector3d& diffuseCol, const vector3d& ambientCol);
	public: C3dNode* C3dActor::FindNode(const char* name);
	public: void C3dActor::SetVolumeBoxInfo(mystd::list<CVolumeBox*>* volBoxList);
	//public: int C3dActor::CheckCollision(const struct vector3d &);
	//public: void C3dActor::AdjustCollision(struct vector3d &);
	//public: void C3dActor::CalcShadowHeight(const struct vector3d &, float &);
	//public: void C3dActor::CullByAABB(const class CRayPicker &);
	//public: void C3dActor::CullByOBB(const struct lineSegment3d &);
	public: char* C3dActor::GetName(void);
	public: float C3dActor::GetAnimSpeed(void);
	public: int C3dActor::GetBlockType(void);
	public: int C3dActor::GetIsHideCheck(void);
	public: void C3dActor::SetName(char* name);
	public: void C3dActor::SetAnimSpeed(float speed);
	public: void C3dActor::SetBlockType(int blockType);
	public: void C3dActor::SetIsHideCheck(int isHideCheck);
	//public: void HalfAlphaOn();
	//public: void HalfAlphaOff();
	//public: void ProcessFadeAlpha();
	public: bool C3dActor::IsHalfAlpha(void);
	public: unsigned char C3dActor::GetFadeAlphaCnt(void);
	private: void C3dActor::UpdateMatrix(void);
	private: void C3dActor::UpdateBound(void);

private:
	static hook_method<void (C3dActor::*)(void)> C3dActor::_Reset;
	static hook_method<void (C3dActor::*)(int framepos)> C3dActor::_SetFrame;
	static hook_method<void (C3dActor::*)(const vector3d& pos)> C3dActor::_SetPos;
	static hook_method<void (C3dActor::*)(const vector3d& rot)> C3dActor::_SetRot;
	static hook_method<void (C3dActor::*)(const vector3d& scale)> C3dActor::_SetScale;
	static hook_method<void (C3dActor::*)(float opacity)> C3dActor::_SetOpacity;
	static hook_method<void (C3dActor::*)(int animType)> C3dActor::_SetAnimType;
	static hook_method<void (C3dActor::*)(void)> C3dActor::_OnProcess;
	static hook_method<void (C3dActor::*)(matrix& ctm, bool clip, int flagRF)> C3dActor::_Render;
	static hook_method<void (C3dActor::*)(C3dModelRes* model)> C3dActor::_AssignModel;
	static hook_method<void (C3dActor::*)(const vector3d& lightDir, const vector3d& diffuseCol, const vector3d& ambientCol)> C3dActor::_UpdateVertexColor;
	static hook_method<C3dNode* (C3dActor::*)(const char* name)> C3dActor::_FindNode;
	static hook_method<void (C3dActor::*)(mystd::list<CVolumeBox*>* volBoxList)> C3dActor::_SetVolumeBoxInfo;
	static hook_method<char* (C3dActor::*)(void)> C3dActor::_GetName;
	static hook_method<float (C3dActor::*)(void)> C3dActor::_GetAnimSpeed;
	static hook_method<int (C3dActor::*)(void)> C3dActor::_GetIsHideCheck;
	static hook_method<int (C3dActor::*)(void)> C3dActor::_GetBlockType;
	static hook_method<void (C3dActor::*)(char* name)> C3dActor::_SetName;
	static hook_method<void (C3dActor::*)(float speed)> C3dActor::_SetAnimSpeed;
	static hook_method<void (C3dActor::*)(int blockType)> C3dActor::_SetBlockType;
	static hook_method<void (C3dActor::*)(int isHideCheck)> C3dActor::_SetIsHideCheck;
	static hook_method<bool (C3dActor::*)(void)> C3dActor::_IsHalfAlpha;
	static hook_method<unsigned char (C3dActor::*)(void)> C3dActor::_GetFadeAlphaCnt;
	static hook_method<void (C3dActor::*)(void)> C3dActor::_UpdateMatrix;
	static hook_method<void (C3dActor::*)(void)> C3dActor::_UpdateBound;

	friend struct SceneGraphNode; // @see xref TestAABBvsOBBIntersection()
	friend class CView; // @see CView::OnRender()
};
