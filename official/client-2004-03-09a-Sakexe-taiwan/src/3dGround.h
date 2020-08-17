#pragma once
#include "Struct.h"
#include "3dLib/Prim.h"
#include "3dLib/Texture.h"
#include "Resource/Attr.h"
#include "Resource/Ground.h"


struct CLightmap
{
	/* this+ 0 */ unsigned char brightObj[3];
	/* this+ 4 */ CTexture* surface;
	/* this+ 8 */ texCoor coor[4];
	/* this+40 */ COLOR intensity[4];
};


class CLightmapMgr
{
	/* this+ 0 */ public: int m_numLightmaps;
	/* this+ 4 */ public: mystd::vector<CLightmap> m_lightmaps;
	/* this+20 */ public: int m_numLmSurfaces;
	/* this+24 */ public: mystd::vector<CTexture*> m_lmSurfaces;

	public: CLightmapMgr::CLightmapMgr(void);
	public: CLightmapMgr::~CLightmapMgr(void);
	public: void CLightmapMgr::Create(CGndRes* gnd);
	public: void CLightmapMgr::Reset(void);

private:
	static hook_method<void (CLightmapMgr::*)(CGndRes* gnd)> CLightmapMgr::_Create;
	static hook_method<void (CLightmapMgr::*)(void)> CLightmapMgr::_Reset;
};


class C3dGround
{
	struct vtable_t
	{
		void* (C3dGround::* scalar_deleting_destructor)(unsigned int flags);
		void (C3dGround::* Reset)(void);
		void (C3dGround::* Create)(int w,int h);
		void (C3dGround::* AssignGnd)(CGndRes* gnd, vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol);
		void (C3dGround::* Render)(const matrix& wtm, const RECT& area, bool needClip);
		void (C3dGround::* RenderLod)(const matrix& wtm, const RECT& area, bool needClip);
		void (C3dGround::* FlushGround)(const matrix& wtm);
		void (C3dGround::* CheckAlpha)(const ray3d& ray, int x, int y, float nearest);
		void (C3dGround::* GetHeightMinMax)(int x, int y, float& topHeight, float& bottomHeight);
		void (C3dGround::* GetHeightMinMax2)(const RECT& area, float& topHeight, float& bottomHeight);
		bool (C3dGround::* IsNewVer)(void);
		void (C3dGround::* CalcLmIntensityFloatRGBAll)(void);
		int  (C3dGround::* GetLmIntensityFloatRGBByGatCoor)(int cx, int cy, float& r, float& g, float& b);
		void (C3dGround::* SetGndRiseAmount)(float amount, int x, int y);
		void (C3dGround::* RenderAttrTile)(const matrix& wtm, int attrX, int attrY, unsigned long color);
		bool (C3dGround::* GetGroundVertics)(vector3d* nwvert, int attrX, int attrY);
	};

	/* this+  0 */ public: //const C3dGround::`vftable';
	/* this+  4 */ protected: C3dAttr* m_attr;
	/* this+  8 */ protected: int m_width;
	/* this+ 12 */ protected: int m_height;
	/* this+ 16 */ protected: float m_zoom;
	/* this+ 20 */ protected: CLightmapMgr m_lightmapMgr;
	/* this+ 60 */ protected: int m_numSurfaces;
	/* this+ 64 */ protected: float m_waterLevel;
	/* this+ 68 */ protected: int m_texAnimCycle;
	/* this+ 72 */ protected: int m_wavePitch;
	/* this+ 76 */ protected: int m_waveSpeed;
	/* this+ 80 */ protected: int m_waterSet;
	/* this+ 84 */ protected: float m_waveHeight;
	/* this+ 88 */ protected: CTexture* m_waterTex;
	/* this+ 92 */ protected: int m_waterCnt;
	/* this+ 96 */ protected: int m_waterOffset;
	/* this+100 */ protected: int m_isNewVer;
	/* this+104 */ protected: CTexture* m_pBumpMap;

	public: C3dGround::C3dGround(void);
	public: virtual C3dGround::~C3dGround(void); // line 89
	public: virtual void C3dGround::Reset(void);
	public: virtual void C3dGround::Create(int w, int h);
	public: virtual void C3dGround::AssignGnd(CGndRes* gnd, vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol);
	public: virtual void C3dGround::Render(const matrix& wtm, const RECT& area, bool needClip);
	public: virtual void C3dGround::RenderLod(const matrix& wtm, const RECT& area, bool needClip);
	public: virtual void C3dGround::FlushGround(const matrix& wtm);
	public: virtual void C3dGround::CheckAlpha(const ray3d& ray, int x, int y, float nearest);
	public: virtual void C3dGround::GetHeightMinMax(const RECT& area, float& topHeight, float& bottomHeight);
	public: virtual void C3dGround::GetHeightMinMax(int x, int y, float& topHeight, float& bottomHeight);
	public: virtual bool C3dGround::IsNewVer(void);
	public: virtual void C3dGround::CalcLmIntensityFloatRGBAll(void);
	public: virtual int C3dGround::GetLmIntensityFloatRGBByGatCoor(int cx, int cy, float& r, float& g, float& b);
	public: void C3dGround::ConvertToCellCoor(float x, float z, long& cx, long& cy);
	public: void C3dGround::SetWaterInfo(float waterLevel, int textureType, int textureAnimSpeed, int pitch, int speed, float height);
	public: void C3dGround::UpdateWater(void);
	public: virtual void C3dGround::SetGndRiseAmount(float amount, int x, int y);
	public: virtual void C3dGround::RenderAttrTile(const matrix& wtm, int attrX, int attrY, unsigned long color);
	public: virtual bool C3dGround::GetGroundVertics(vector3d* nwvert, int attrX, int attrY);
	public: void C3dGround::RenderGroundTile(const matrix& wtm, int attrX, int attrY, unsigned long color, CTexture* tex, vector2d* uv);
	public: CTexture* C3dGround::GetWaterTexture(void);

	/// @custom
	public: int C3dGround::GetWidth() { return m_width; }
	public: int C3dGround::GetHeight() { return m_height; }
	public: float C3dGround::GetZoom() { return m_zoom; }
	public: void C3dGround::SetAttr(C3dAttr* attr) { m_attr = attr; }

private:
	static hook_method<void (C3dGround::*)(void)> C3dGround::_Reset;
	static hook_method<void (C3dGround::*)(int w, int h)> C3dGround::_Create;
	static hook_method<void (C3dGround::*)(CGndRes* gnd, vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol)> C3dGround::_AssignGnd;
	static hook_method<void (C3dGround::*)(const matrix& wtm, const RECT& area, bool needClip)> C3dGround::_Render;
	static hook_method<void (C3dGround::*)(const matrix& wtm, const RECT& area, bool needClip)> C3dGround::_RenderLod;
	static hook_method<void (C3dGround::*)(const matrix& wtm)> C3dGround::_FlushGround;
	static hook_method<void (C3dGround::*)(const ray3d& ray, int x, int y, float nearest)> C3dGround::_CheckAlpha;
	static hook_method<void (C3dGround::*)(const RECT& area, float& topHeight, float& bottomHeight)> C3dGround::_GetHeightMinMax;
	static hook_method<void (C3dGround::*)(int x, int y, float& topHeight, float& bottomHeight)> C3dGround::_GetHeightMinMax2;
	static hook_method<bool (C3dGround::*)(void)> C3dGround::_IsNewVer;
	static hook_method<void (C3dGround::*)(void)> C3dGround::_CalcLmIntensityFloatRGBAll;
	static hook_method<int (C3dGround::*)(int cx, int cy, float& r, float& g, float& b)> C3dGround::_GetLmIntensityFloatRGBByGatCoor;
	static hook_method<void (C3dGround::*)(float x, float z, long& cx, long& cy)> C3dGround::_ConvertToCellCoor;
	static hook_method<void (C3dGround::*)(float waterLevel, int textureType, int textureAnimSpeed, int pitch, int speed, float height)> C3dGround::_SetWaterInfo;
	static hook_method<void (C3dGround::*)(void)> C3dGround::_UpdateWater;
	static hook_method<void (C3dGround::*)(float amount, int x, int y)> C3dGround::_SetGndRiseAmount;
	static hook_method<void (C3dGround::*)(const matrix& wtm, int attrX, int attrY, unsigned long color)> C3dGround::_RenderAttrTile;
	static hook_method<bool (C3dGround::*)(vector3d* nwvert, int attrX, int attrY)> C3dGround::_GetGroundVertics;
	static hook_method<void (C3dGround::*)(const matrix& wtm, int attrX, int attrY, unsigned long color, CTexture* tex, vector2d* uv)> C3dGround::_RenderGroundTile;
	static hook_method<CTexture* (C3dGround::*)(void)> C3dGround::_GetWaterTexture;
};


struct CGndSurface
{
	/* this+  0 */ lmvertex3d vertex[4];
	/* this+128 */ int offset;
	/* this+132 */ CTexture* tex;
	/* this+136 */ CTexture* lmtex;
	/* this+140 */ CLightmap* lmap;
	/* this+144 */ COLOR argb;
	/* this+148 */ unsigned long alpha;
	/* this+152 */ int MtlId;
};


struct LightmapRGBIntensity
{
	/* this+0 */ float rIntensity;
	/* this+4 */ float gIntensity;
	/* this+8 */ float bIntensity;
};


struct CGndCell
{
	/* this+ 0 */ float h[4];
	/* this+16 */ vector3d watervert[4];
	/* this+64 */ CGndSurface* top;
	/* this+68 */ CGndSurface* right;
	/* this+72 */ CGndSurface* front;
	/* this+76 */ int renderSignature;
	/* this+80 */ unsigned char cellColor[3];
};


class C3dGround15 : public C3dGround
{
	struct vtable_t
	{
		void* (C3dGround15::* scalar_deleting_destructor)(unsigned int flags);
		void (C3dGround15::* Reset)(void);
		void (C3dGround15::* Create)(int w,int h);
		void (C3dGround15::* AssignGnd)(CGndRes* gnd, vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol);
		void (C3dGround15::* Render)(const matrix& wtm, const RECT& area, bool needClip);
		void (C3dGround15::* RenderLod)(const matrix& wtm, const RECT& area, bool needClip);
		void (C3dGround15::* FlushGround)(const matrix& wtm);
		void (C3dGround15::* CheckAlpha)(const ray3d& ray, int x, int y, float nearest);
		void (C3dGround15::* GetHeightMinMax)(int x, int y, float& topHeight, float& bottomHeight);
		void (C3dGround15::* GetHeightMinMax2)(const RECT& area, float& topHeight, float& bottomHeight);
		bool (C3dGround15::* IsNewVer)(void);
		void (C3dGround15::* CalcLmIntensityFloatRGBAll)(void);
		int  (C3dGround15::* GetLmIntensityFloatRGBByGatCoor)(int cx, int cy, float& r, float& g, float& b);
		void (C3dGround::* SetGndRiseAmount)(float amount, int x, int y);
		void (C3dGround15::* RenderAttrTile)(const matrix& wtm, int attrX, int attrY, unsigned long color);
		bool (C3dGround15::* GetGroundVertics)(vector3d* nwvert, int attrX, int attrY);
	};

	/* this+  0 */ public: //C3dGround baseclass_0;
	/* this+108 */ private: mystd::vector<CGndSurface> m_V15surfaces;
	/* this+124 */ private: mystd::vector<LightmapRGBIntensity> m_lmRGBIntensities;
	/* this+140 */ private: mystd::vector<CGndCell> m_V15Cells;

	public: virtual void C3dGround15::Reset(void);
	public: virtual void C3dGround15::Create(int w, int h);
	public: virtual void C3dGround15::AssignGnd(CGndRes* gnd, vector3d& light, vector3d& diffuseCol, vector3d& ambientCol);
	//public: virtual void C3dGround15::Render(const struct matrix &, const RECT &, unsigned char);
	//public: virtual void C3dGround15::RenderLod(const struct matrix &, const RECT &, unsigned char);
	//public: virtual void C3dGround15::FlushGround(const struct matrix &);
	//public: virtual void C3dGround15::CheckAlpha(const struct ray3d &, int, int, float);
	//public: virtual void C3dGround15::GetHeightMinMax(int, int, float &, float &);
	//public: virtual void C3dGround15::GetHeightMinMax(const RECT &, float &, float &);
	//public: virtual bool char C3dGround15::IsNewVer(void);
	//public: virtual void C3dGround15::CalcLmIntensityFloatRGBAll(void);
	//public: virtual int C3dGround15::GetLmIntensityFloatRGBByGatCoor(int, int, float &, float &, float &);
	//public: void C3dGround15::GetBrightObjVal(struct vector3d, int *);
	//private: CGndCell* GetCell15(int, int);
	//private: void C3dGround15::GetLmIntensityRGBByGatCoor(int, int, unsigned char &, unsigned char &, unsigned char &, unsigned char &);
	//private: void C3dGround15::SetLmIntensityFloatRGBByGatCoor(int, int, float &, float &, float &);
	//private: void C3dGround15::RenderNew(const struct matrix &, struct CGndSurface *, unsigned char);
	//private: void C3dGround15::RenderNewLod(const struct matrix &, struct CGndSurface *, unsigned char);
	//private: virtual void C3dGround15::RenderAttrTile(const struct matrix &, int, int, unsigned long);
	//private: virtual bool C3dGround15::GetGroundVertics(struct vector3d *, int, int);

private:
	static hook_method<void (C3dGround15::*)(void)> C3dGround15::_Reset;
	static hook_method<void (C3dGround15::*)(int w, int h)> C3dGround15::_Create;
	static hook_method<void (C3dGround15::*)(CGndRes* gnd, vector3d& light, vector3d& diffuseCol, vector3d& ambientCol)> C3dGround15::_AssignGnd;
};
