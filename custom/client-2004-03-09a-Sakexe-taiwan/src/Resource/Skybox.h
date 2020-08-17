#pragma once
#include "Struct.h"
#include "3dLib/Prim.h"
class C3dActor;
class C3dModelRes;


struct Flare
{
	/* this+ 0 */ int wType;
	/* this+ 4 */ float fLoc;
	/* this+ 8 */ float fScale;
	/* this+12 */ float r;
	/* this+16 */ float g;
	/* this+20 */ float b;
	/* this+24 */ vector3d vPositionPt;
	/* this+36 */ float fRenderSize;
};


class CFlare
{
	/* this+  0 */ private: Flare m_Flare[12];
	/* this+480 */ private: unsigned long m_flareColor[12];
	/* this+528 */ private: char m_strTexName[260];
	/* this+788 */ private: vector3d m_vLightPt;

	public: CFlare::~CFlare(void) { }; // line 23
	public: void CFlare::Render(matrix& view, vector3d vFrom, vector3d vAt);
	public: Flare CFlare::SetFlare(int wType, float fLoc, float fScale, float r, float g, float b);
	public: void CFlare::Process(float fTimeKey, vector3d vFrom, vector3d vAt);
	public: void CFlare::Init(void);

private:
	static hook_method<void (CFlare::*)(matrix& view, vector3d vFrom, vector3d vAt)> CFlare::_Render;
	static hook_method<Flare (CFlare::*)(int wType, float fLoc, float fScale, float r, float g, float b)> CFlare::_SetFlare;
	static hook_method<void (CFlare::*)(float fTimeKey, vector3d vFrom, vector3d vAt)> CFlare::_Process;
	static hook_method<void (CFlare::*)(void)> CFlare::_Init;
};


class CSkyBox
{
	/* this+  0 */ tlvertex3d m_pvWall[10];
	/* this+320 */ float m_fLoopRotY;
	/* this+324 */ class CFlare m_flare;

	public: CSkyBox::CSkyBox(void);
	public: CSkyBox::~CSkyBox(void);
	public: void CSkyBox::Render(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt);
	private: bool CSkyBox::ChkVisible(float hratio, float vratio, vector3d vPos, matrix& view, tlvertex3d vert);

private:
	static hook_method<void (CSkyBox::*)(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt)> CSkyBox::_Render;
	static hook_method<bool (CSkyBox::*)(float hratio, float vratio, vector3d vPos, matrix& view, tlvertex3d vert)> CSkyBox::_ChkVisible;
};


class CSkyBoxEllipse
{
	/* this+ 0 */ private: C3dModelRes* m_res;
	/* this+ 4 */ private: C3dActor* m_sky;
	/* this+ 8 */ private: float m_fLoopRotX;
	/* this+12 */ private: CFlare m_flare;

	public: CSkyBoxEllipse::CSkyBoxEllipse(void);
	public: CSkyBoxEllipse::~CSkyBoxEllipse(void);
	public: void CSkyBoxEllipse::Render(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt);

private:
	static hook_method<void (CSkyBoxEllipse::*)(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt)> CSkyBoxEllipse::_Render;
};
