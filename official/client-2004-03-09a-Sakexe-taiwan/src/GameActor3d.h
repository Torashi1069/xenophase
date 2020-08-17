#pragma once
//part of GameActor.h
#include "GameActor.h"
#include "3dLib/Prim.h"
#include "granny.h"
class CTexture;
class C3dGrannyModelRes;
struct RPMesh;


struct GrannyLightInfo
{
	/* this+ 0 */ vector3d eyeVec;
	/* this+12 */ int nContrast;
	/* this+16 */ int lightR;
	/* this+20 */ int lightG;
	/* this+24 */ int lightB;
};


class C3dGrannyGameActor : public CGameActor
{
public:
	C3dGrannyGameActor(char* strJobFn);
	virtual ~C3dGrannyGameActor();
	virtual bool OnProcess();
	virtual void Render(matrix& view);
	virtual void SetAction(int action, int speed, int type);
	virtual void SetSprAct(int job, int sex);
	virtual void ProcessMotion();
	virtual void ProcessMotionWithDist();
	virtual void MakeCorpse();
	virtual int GetAttackMotion();
	void SetRenderType(int renderType);
	int GetRenderType();
protected:
	CTexture* GetEmblemTexture();
	bool ProcessAni();
	void RenderNormal(matrix& view, GrannyLightInfo* grannyLInfo);
	void RenderBak(matrix& vtm);
	void RenderNormalFast(matrix& view);
	void RenderCell(matrix& view);
	void RenderGuildMark(matrix& view);
	void RenderEffect(int nMesh, granny_pnt332_vertex* vertArr, vector3d tv);
	void RenderShadow(matrix& vtm, vector3d lv, bool isBakRender);

protected:
	/* this+   0 */ //CGameActor baseclass_0;
	/* this+ 684 */ CTexture* m_emblemTex;
	/* this+ 688 */ C3dGrannyModelRes* m_GrannyActorRes;
	/* this+ 692 */ granny_model_instance* m_Instance;
	/* this+ 696 */ RPMesh* m_rp[30];
	/* this+ 816 */ granny_pnt332_vertex* m_matVer[30];
	/* this+ 936 */ granny_system_clock m_fAniCnt;
	/* this+ 952 */ granny_system_clock m_fLastAniCnt;
	/* this+ 968 */ float m_GameClock;
	/* this+ 972 */ int m_curAction;
	/* this+ 976 */ int m_baseAction;
	/* this+ 980 */ float m_fCurRot;
	/* this+ 984 */ unsigned char m_RenderAlpha;
	/* this+ 988 */ unsigned long m_nVertCol;
	/* this+ 992 */ int m_nLastActAnimation;
	/* this+ 996 */ int m_curFrame;
	/* this+1000 */ char m_strJobFn[260];
	/* this+1260 */ int m_nRenderType;
	/* this+1264 */ CTexture* m_pCellTex;
	/* this+1268 */ granny_control* m_Control[20];
	/* this+1348 */ unsigned char m_isFirstProcess;
	/* this+1352 */ CTexture* m_pTex[30];
	/* this+1472 */ void* m_pFaceArr[30];
	/* this+1592 */ int m_nIndexNo[30];
	/* this+1712 */ matrix m_matPose[30];
private:
	/* this+3152 */ granny_world_pose* m_pWorldPose;
	/* this+3156 */ CTexture* m_shadowTex;
	/* this+3160 */ mystd::vector<vector3d> m_shadowDotList;

private:
	static hook_method<bool (C3dGrannyGameActor::*)(void)> C3dGrannyGameActor::_OnProcess;
	static hook_func<bool (C3dGrannyGameActor::*)()> C3dGrannyGameActor::_ProcessAni;
	static hook_func<void (C3dGrannyGameActor::*)(matrix& view, GrannyLightInfo* grannyLInfo)> C3dGrannyGameActor::_RenderNormal;
	static hook_func<void (C3dGrannyGameActor::*)(matrix& vtm)> C3dGrannyGameActor::_RenderBak;
	static hook_func<void (C3dGrannyGameActor::*)(matrix& view)> C3dGrannyGameActor::_RenderGuildMark;
	static hook_func<void (C3dGrannyGameActor::*)(matrix& vtm, vector3d lv, bool isBakRender)> C3dGrannyGameActor::_RenderShadow;
};
