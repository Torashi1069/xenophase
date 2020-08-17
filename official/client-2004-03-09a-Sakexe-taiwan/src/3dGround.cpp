#include "3dGround.h"
#include "Globals.h"
#include <math.h>


CLightmapMgr::CLightmapMgr(void) // line 24
{
}


CLightmapMgr::~CLightmapMgr(void) // line 28
{
	this->CLightmapMgr::Reset();
}


hook_method<void (CLightmapMgr::*)(CGndRes* gnd)> CLightmapMgr::_Create(SAKEXE, "CLightmapMgr::Create");
void CLightmapMgr::Create(CGndRes* gnd) // line 44
{
	return (this->*_Create)(gnd);

	//TODO
}


hook_method<void (CLightmapMgr::*)(void)> CLightmapMgr::_Reset(SAKEXE, "CLightmapMgr::Reset");
void CLightmapMgr::Reset(void) // line 33
{
	return (this->*_Reset)();

	//TODO
}


////////////////////////////////////////


C3dGround::C3dGround(void) // line 126
{
	m_zoom = 10.0;
	m_waterLevel = 0.0;
	m_texAnimCycle = 3;
	m_wavePitch = 50;
	m_waveSpeed = 2;
	m_waveHeight = 1.0;
	m_waterSet = 0;
	m_waterTex = NULL;
	m_isNewVer = 0;
	m_attr = NULL;
	m_pBumpMap = NULL;
}


C3dGround::~C3dGround(void) // line 89 (3dGround.h)
{
}


hook_method<void (C3dGround::*)(void)> C3dGround::_Reset(SAKEXE, "C3dGround::Reset");
void C3dGround::Reset(void) // line 94 (3dGround.h)
{
	return (this->*_Reset)();

	;
}


hook_method<void (C3dGround::*)(int w, int h)> C3dGround::_Create(SAKEXE, "C3dGround::Create");
void C3dGround::Create(int w, int h) // line 95 (3dGround.h)
{
	return (this->*_Create)(w, h);

	;
}


hook_method<void (C3dGround::*)(CGndRes* gnd, vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol)> C3dGround::_AssignGnd(SAKEXE, "C3dGround::AssignGnd");
void C3dGround::AssignGnd(CGndRes* gnd, vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol) // line 96 (3dGround.h)
{
	return (this->*_AssignGnd)(gnd, lightDir, diffuseCol, ambientCol);

	;
}


hook_method<void (C3dGround::*)(const matrix& wtm, const RECT& area, bool needClip)> C3dGround::_Render(SAKEXE, "C3dGround::Render");
void C3dGround::Render(const matrix& wtm, const RECT& area, bool needClip) // line 98 (3dGround.h)
{
	return (this->*_Render)(wtm, area, needClip);

	;
}


hook_method<void (C3dGround::*)(const matrix& wtm, const RECT& area, bool needClip)> C3dGround::_RenderLod(SAKEXE, "C3dGround::RenderLod");
void C3dGround::RenderLod(const matrix& wtm, const RECT& area, bool needClip) // line 99 (3dGround.h)
{
	return (this->*_RenderLod)(wtm, area, needClip);

	;
}


hook_method<void (C3dGround::*)(const matrix& wtm)> C3dGround::_FlushGround(SAKEXE, "C3dGround::FlushGround");
void C3dGround::FlushGround(const matrix& wtm) // line 100 (3dGround.h)
{
	return (this->*_FlushGround)(wtm);

	;
}


hook_method<void (C3dGround::*)(const ray3d& ray, int x, int y, float nearest)> C3dGround::_CheckAlpha(SAKEXE, "C3dGround::CheckAlpha");
void C3dGround::CheckAlpha(const ray3d& ray, int x, int y, float nearest) // line 102 (3dGround.h)
{
	return (this->*_CheckAlpha)(ray, x, y, nearest);

	;
}


hook_method<void (C3dGround::*)(const RECT& area, float& topHeight, float& bottomHeight)> C3dGround::_GetHeightMinMax(SAKEXE, "?GetHeightMinMax@C3dGround@@UAEXABUtagRECT@@AAM1@Z");
void C3dGround::GetHeightMinMax(const RECT& area, float& topHeight, float& bottomHeight) // line 103 (3dGround.h)
{
	return (this->*_GetHeightMinMax)(area, topHeight, bottomHeight);

	;
}


hook_method<void (C3dGround::*)(int x, int y, float& topHeight, float& bottomHeight)> C3dGround::_GetHeightMinMax2(SAKEXE, "?GetHeightMinMax@C3dGround@@UAEXHHAAM0@Z");
void C3dGround::GetHeightMinMax(int x, int y, float& topHeight, float& bottomHeight) // line 104 (3dGround.h)
{
	return (this->*_GetHeightMinMax2)(x, y, topHeight, bottomHeight);

	;
}


hook_method<bool (C3dGround::*)(void)> C3dGround::_IsNewVer(SAKEXE, "C3dGround::IsNewVer");
bool C3dGround::IsNewVer(void) // line 105 (3dGround.h)
{
	return (this->*_IsNewVer)();

	;
}


hook_method<void (C3dGround::*)(void)> C3dGround::_CalcLmIntensityFloatRGBAll(SAKEXE, "C3dGround::CalcLmIntensityFloatRGBAll");
void C3dGround::CalcLmIntensityFloatRGBAll(void) // line 106 (3dGround.h)
{
	return (this->*_CalcLmIntensityFloatRGBAll)();

	;
}


hook_method<int (C3dGround::*)(int cx, int cy, float& r, float& g, float& b)> C3dGround::_GetLmIntensityFloatRGBByGatCoor(SAKEXE, "C3dGround::GetLmIntensityFloatRGBByGatCoor");
int C3dGround::GetLmIntensityFloatRGBByGatCoor(int cx, int cy, float& r, float& g, float& b) // line 107 (3dGround.h)
{
	return (this->*_GetLmIntensityFloatRGBByGatCoor)(cx, cy, r, g, b);

	return 0;
}


hook_method<void (C3dGround::*)(float x, float z, long& cx, long& cy)> C3dGround::_ConvertToCellCoor(SAKEXE, "C3dGround::ConvertToCellCoor");
void C3dGround::ConvertToCellCoor(float x, float z, long& cx, long& cy) // line 141
{
	return (this->*_ConvertToCellCoor)(x, z, cx, cy);

	cx = m_width / 2 + (long)floor(x / m_zoom);
	cy = m_height / 2 + (long)floor(z / m_zoom);
}


hook_method<void (C3dGround::*)(float waterLevel, int textureType, int textureAnimSpeed, int pitch, int speed, float height)> C3dGround::_SetWaterInfo(SAKEXE, "C3dGround::SetWaterInfo");
void C3dGround::SetWaterInfo(float waterLevel, int textureType, int textureAnimSpeed, int pitch, int speed, float height) // line 148
{
	return (this->*_SetWaterInfo)(waterLevel, textureType, textureAnimSpeed, pitch, speed, height);

	m_waterLevel = waterLevel;
	m_wavePitch = pitch;
	m_texAnimCycle = textureAnimSpeed;
	m_waveHeight = height;
	m_waveSpeed = speed % 360;
	m_waterSet = textureType;
}


hook_method<void (C3dGround::*)(void)> C3dGround::_UpdateWater(SAKEXE, "C3dGround::UpdateWater");
void C3dGround::UpdateWater(void) // line 158
{
	return (this->*_UpdateWater)();

	++m_waterCnt;
	if( m_waterCnt >= 32 * m_texAnimCycle )
		m_waterCnt = 0;

	char waterName[20];
	sprintf(waterName, "워터\\water%d%02d.jpg", m_waterSet % 6, m_waterCnt / m_texAnimCycle % 32);
	m_waterTex = g_texMgr.CTexMgr::GetTexture(waterName, 0);

	m_waterOffset += m_waveSpeed;
	if( m_waterOffset > 180 )
		m_waterOffset -= 360;
}


hook_method<void (C3dGround::*)(float amount, int x, int y)> C3dGround::_SetGndRiseAmount(SAKEXE, "C3dGround::SetGndRiseAmount");
void C3dGround::SetGndRiseAmount(float amount, int x, int y) // line 115 (3dGround.h)
{
	return (this->*_SetGndRiseAmount)(amount, x, y);

	;
}


hook_method<void (C3dGround::*)(const matrix& wtm, int attrX, int attrY, unsigned long color)> C3dGround::_RenderAttrTile(SAKEXE, "C3dGround::RenderAttrTile");
void C3dGround::RenderAttrTile(const matrix& wtm, int attrX, int attrY, unsigned long color) // line 117 (3dGround.h)
{
	return (this->*_RenderAttrTile)(wtm, attrX, attrY, color);

	;
}


hook_method<bool (C3dGround::*)(vector3d* nwvert, int attrX, int attrY)> C3dGround::_GetGroundVertics(SAKEXE, "C3dGround::GetGroundVertics");
bool C3dGround::GetGroundVertics(vector3d* nwvert, int attrX, int attrY) // line 179
{
	return (this->*_GetGroundVertics)(nwvert, attrX, attrY);

	CAttrCell* cell = m_attr->C3dAttr::GetCell(attrX, attrY);
	if( cell == NULL )
		return false;

	nwvert[0].y = cell->h1;
	nwvert[1].y = cell->h2;
	nwvert[2].y = cell->h3;
	nwvert[3].y = cell->h4;
	return true;
}


hook_method<void (C3dGround::*)(const matrix& wtm, int attrX, int attrY, unsigned long color, CTexture* tex, vector2d* uv)> C3dGround::_RenderGroundTile(SAKEXE, "C3dGround::RenderGroundTile");
void C3dGround::RenderGroundTile(const matrix& wtm, int attrX, int attrY, unsigned long color, CTexture* tex, vector2d* uv) // line 194
{
	return (this->*_RenderGroundTile)(wtm, attrX, attrY, color, tex, uv);

	vector3d nwvert[4];
	if( !this->GetGroundVertics(nwvert, attrX, attrY) )
		return;

	for( int i = 0; i < 4; ++i )
	{
		if( attrX % 2 )
		{
			if( nwvert[i].x < nwvert[1].x )
				nwvert[i].x += (nwvert[1].x - nwvert[i].x) * 0.5f;
		}
		else
		{
			if( nwvert[i].x > nwvert[0].x )
				nwvert[i].x -= (nwvert[i].x - nwvert[0].x) * 0.5f;
		}

		if( attrY % 2 )
		{
			if( nwvert[i].z < nwvert[2].z )
				nwvert[i].z += (nwvert[2].z - nwvert[i].z) * 0.5f;
		}
		else
		{
			if( nwvert[i].z > nwvert[0].z )
				nwvert[i].z -= (nwvert[i].z - nwvert[0].z) * 0.5f;
		}
	}

	RPQuadFace& rp = g_renderer->CRenderer::BorrowQuadRP();
	for( int i = 0; i < 4; ++i )
	{
		g_renderer->CRenderer::ProjectVertex(nwvert[i], wtm, &rp.verts[i]);
		rp.verts[i].z -= 0.000030517578f;
	}
//
	float u = tex->CTexture::GetUAdjust();
	float v = tex->CTexture::GetVAdjust();
	rp.verts[0].tu = u * uv[0].x;
	rp.verts[0].tv = v * uv[0].y;
	rp.verts[1].tu = u * uv[1].x;
	rp.verts[1].tv = v * uv[1].y;
	rp.verts[2].tu = u * uv[2].x;
	rp.verts[2].tv = v * uv[2].y;
	rp.verts[3].tu = u * uv[3].x;
	rp.verts[3].tv = v * uv[3].y;
	rp.tex = tex;
	rp.srcAlphaMode = 5;
	rp.destAlphaMode = 6;
	rp.verts[0].color = color;
	rp.verts[1].color = color;
	rp.verts[2].color = color;
	rp.verts[3].color = color;
	g_renderer->CRenderer::AddRP(&rp, 1);
//
}


hook_method<CTexture* (C3dGround::*)(void)> C3dGround::_GetWaterTexture(SAKEXE, "C3dGround::GetWaterTexture");
CTexture* C3dGround::GetWaterTexture(void) // line 172
{
	return (this->*_GetWaterTexture)();

	if( m_waterTex == NULL )
		this->C3dGround::UpdateWater(); // inlined

	return m_waterTex;
}


////////////////////////////////////////


hook_method<void (C3dGround15::*)(void)> C3dGround15::_Reset(SAKEXE, "C3dGround15::Reset");
void C3dGround15::Reset(void) // line 260
{
	return (this->*_Reset)();

	;
}


hook_method<void (C3dGround15::*)(int w, int h)> C3dGround15::_Create(SAKEXE, "C3dGround15::Create");
void C3dGround15::Create(int w, int h) // line 267
{
	return (this->*_Create)(w, h);

	;
}


hook_method<void (C3dGround15::*)(CGndRes* gnd, vector3d& light, vector3d& diffuseCol, vector3d& ambientCol)> C3dGround15::_AssignGnd(SAKEXE, "C3dGround15::AssignGnd");
void C3dGround15::AssignGnd(CGndRes* gnd, vector3d& light, vector3d& diffuseCol, vector3d& ambientCol) // line 283
{
	return (this->*_AssignGnd)(gnd, light, diffuseCol, ambientCol);

	//TODO
}


////////////////////////////////////////
