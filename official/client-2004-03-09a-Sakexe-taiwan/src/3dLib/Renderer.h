#pragma once
#include "3dLib/Prim.h"
#include "common.h" // CharPrtLess
#include <dx9sdk/Include/ddraw.h>
#include <dx9sdk/Include/d3d.h>
class CBitmapRes;
class CSprRes;
class CTexture;
class CDynamicVB;
struct CMotion;
struct SprImg;


struct RPRaw
{
	/* this+ 0 */ matrix world;
	/* this+48 */ CDynamicVB* vb;
	/* this+52 */ int vertStart;
	/* this+56 */ int numVerts;
	/* this+60 */ unsigned short* indices;
	/* this+64 */ unsigned long numIndices;
	/* this+68 */ CTexture* tex;
	/* this+72 */ CTexture* tex2;

	public: void RPRaw::DrawPri(LPDIRECT3DDEVICE7 device);
	public: void RPRaw::DrawPriIndexed(LPDIRECT3DDEVICE7 device);

private:
	static hook_method<void (RPRaw::*)(LPDIRECT3DDEVICE7 device)> RPRaw::_DrawPri;
	static hook_method<void (RPRaw::*)(LPDIRECT3DDEVICE7 device)> RPRaw::_DrawPriIndexed;
};


struct RPFace
{
	/* this+ 0 */ tlvertex3d* verts;
	/* this+ 4 */ int numVerts;
	/* this+ 8 */ CTexture* tex;
	/* this+12 */ unsigned short* indices;
	/* this+16 */ unsigned long numIndices;
	/* this+20 */ unsigned long srcAlphaMode;
	/* this+24 */ unsigned long destAlphaMode;
	/* this+28 */ unsigned long mtPreset;
	/* this+32 */ D3DPRIMITIVETYPE primType;

	public: RPFace::RPFace(tlvertex3d* vert, int numVert);
	public: void RPFace::SetGeomInfo(int vertId, const tlvertex3d& src);
	public: void RPFace::SetGeomInfo(int vertId, const vector4d& src);
	public: void RPFace::InitSpecular(void);
	public: void RPFace::DrawPri(LPDIRECT3DDEVICE7 device);

private:
	static hook_method<void (RPFace::*)(int vertId, const tlvertex3d& src)> RPFace::_SetGeomInfo;
	static hook_method<void (RPFace::*)(int vertId, const vector4d& src)> RPFace::_SetGeomInfo2;
	static hook_method<void (RPFace::*)(void)> RPFace::_InitSpecular;
	static hook_method<void (RPFace::*)(LPDIRECT3DDEVICE7 device)> RPFace::_DrawPri;
};


struct RPTriFace
{
	/* this+  0 */ tlvertex3d verts[3];
	/* this+ 96 */ CTexture* tex;
	/* this+100 */ unsigned long srcAlphaMode;
	/* this+104 */ unsigned long destAlphaMode;
};


struct RPQuadFace : public RPFace
{
	/* this+ 0 */ //RPFace baseclass_0;
	/* this+36 */ tlvertex3d m_verts[4];

	public: RPQuadFace::RPQuadFace(void);
	public: RPQuadFace::RPQuadFace(const RPQuadFace& rp);
	public: const RPQuadFace& RPQuadFace::operator=(const RPQuadFace& rp);
};


struct RPLmFace
{
	/* this+ 0 */ lmtlvertex3d* lmverts;
	/* this+ 4 */ int numVerts;
	/* this+ 8 */ unsigned short* indices;
	/* this+12 */ unsigned long numIndices;
	/* this+16 */ CTexture* tex;
	/* this+20 */ CTexture* tex2;
	/* this+24 */ D3DPRIMITIVETYPE primType;

	public: void RPLmFace::InitSpecular(void);
	public: void RPLmFace::DrawPri(LPDIRECT3DDEVICE7 device);

private:
	static hook_method<void (RPLmFace::*)(void)> RPLmFace::_InitSpecular;
	static hook_method<void (RPLmFace::*)(LPDIRECT3DDEVICE7 device)> RPLmFace::_DrawPri;
};


struct RPLmQuadFace : public RPLmFace
{
	/* this+ 0 */ //RPLmFace baseclass_0;
	/* this+28 */ lmtlvertex3d m_lmverts[4];

	public: RPLmQuadFace::RPLmQuadFace(void);
	public: RPLmQuadFace::RPLmQuadFace(const RPLmQuadFace& rp);
	public: const RPLmQuadFace& RPLmQuadFace::operator=(const RPLmQuadFace& rp);
};


struct RPMesh : public RPFace
{
	RPMesh();
	~RPMesh();
	void AllocVerts(int numVerts);
};


struct CacheInfo
{
  /* this+ 0 */ unsigned long id;
  /* this+ 4 */ unsigned long palID;
  /* this+ 8 */ unsigned long lastTime;
  /* this+12 */ float tu;
  /* this+16 */ float tv;
  /* this+20 */ float tu1;
  /* this+24 */ float tv1;
  /* this+28 */ unsigned long x;
  /* this+32 */ unsigned long y;
};


struct CacheSurface
{
	/* this+ 0 */ CTexture* tex;
	/* this+ 4 */ int w;
	/* this+ 8 */ int h;
	/* this+12 */ int texWidth;
	/* this+16 */ int texHeight;
	/* this+20 */ mystd::vector<CacheInfo> info;
	/* this+24 */ int isLocked;
	/* this+28 */ DWORD lastTime;
};


class CRenderer
{
	/* this+  0 */ private: float m_hpc;
	/* this+  4 */ private: float m_vpc;
	/* this+  8 */ private: float m_hratio;
	/* this+ 12 */ private: float m_vratio;
	/* this+ 16 */ private: float m_aspectRatio;
	/* this+ 20 */ private: float m_screenXFactor;
	/* this+ 24 */ private: float m_screenYFactor;
	/* this+ 28 */ private: int m_xoffset;
	/* this+ 32 */ private: int m_yoffset;
	/* this+ 36 */ private: int m_width;
	/* this+ 40 */ private: int m_height;
	/* this+ 44 */ private: int m_halfWidth;
	/* this+ 48 */ private: int m_halfHeight;
	/* this+ 52 */ private: int m_curFrame;
	/* this+ 56 */ private: int m_bRGBBitCount;
	/* this+ 60 */ private: unsigned long m_fpsFrameCount;
	/* this+ 64 */ private: unsigned long m_fpsStartTick;
	/* this+ 68 */ private: int m_isFoggy;
	/* this+ 72 */ private: int m_fogChanged;
	/* this+ 76 */ private: int m_isVertexFog;
	/* this+ 80 */ private: CTexture* m_oldTexture;
	/* this+ 84 */ private: CTexture* m_oldLmapTexture;
	/* this+ 88 */ private: float m_guardBandLeft;
	/* this+ 92 */ private: float m_guardBandRight;
	/* this+ 96 */ private: float m_guardBandTop;
	/* this+100 */ private: float m_guardBandBottom;
	/* this+104 */ private: int m_isShowInfo;
	/* this+108 */ private: vector3d m_eyeVector;
	/* this+120 */ private: unsigned long m_nClearColor;
	/* this+124 */ private: LPDIRECT3DDEVICE7 m_device;
	/* this+128 */ private: LPDIRECTDRAWSURFACE7 m_lpSurface;
	/* this+132 */ private: DWORD m_dwScreenWidth;
	/* this+136 */ private: DWORD m_dwScreenHeight;
	/* this+140 */ private: enum PixelFormat m_pf;
	/* this+144 */ private: void* m_lpSurfacePtr;
	/* this+148 */ private: long m_lPitch;
	/* this+152 */ private: mystd::vector<RPFace*> m_rpFaceList;
	/* this+168 */ private: mystd::vector<RPFace*> m_rpLMGroundList;
	/* this+184 */ private: mystd::vector<RPFace*> m_rpLMLightList;
	/* this+200 */ private: mystd::vector< mystd::pair<float,RPFace *> > m_rpAlphaDepthList;
	/* this+216 */ private: mystd::vector< mystd::pair<float,RPFace *> > m_rpAlphaList;
	/* this+232 */ private: mystd::vector< mystd::pair<float,RPFace *> > m_rpAlphaNoDepthList;
	/* this+248 */ private: mystd::vector< mystd::pair<float,RPFace *> > m_rpEmissiveDepthList;
	/* this+264 */ private: mystd::vector< mystd::pair<float,RPFace *> > m_rpEmissiveList;
	/* this+280 */ private: mystd::vector< mystd::pair<float,RPFace *> > m_rpEmissiveNoDepthList;
	/* this+296 */ private: mystd::vector<RPRaw*> m_rpRawList;
	/* this+312 */ private: mystd::vector<RPRaw*> m_rpRawAlphaList;
	/* this+328 */ private: mystd::vector<RPRaw*> m_rpRawEmissiveList;
	/* this+344 */ private: mystd::vector<RPFace*> m_rpAlphaOPList;
	/* this+360 */ private: mystd::vector<RPLmFace*> m_rpLmList;
	/* this+376 */ private: mystd::vector<RPLmFace*> m_rpBumpFaceList;
	/* this+392 */ private: mystd::list<CacheSurface> m_cacheSurfaces[16];
	/* this+584 */ private: mystd::list<CTexture*> m_unusedCacheSurfaces;
	/* this+596 */ private: mystd::list<RPFace> m_rpNullFaceList;
	/* this+608 */ private: mystd::list<RPFace>::iterator m_rpNullFaceListIter;
	/* this+612 */ private: mystd::list<RPQuadFace> m_rpQuadFaceList;
	/* this+624 */ private: mystd::list<RPQuadFace>::iterator m_rpQuadFaceListIter;
	/* this+628 */ private: mystd::list<RPLmQuadFace> m_rpLmQuadFaceList;
	/* this+640 */ private: mystd::list<RPLmQuadFace>::iterator m_rpLmQuadFaceListIter;
	/* this+644 */ private: mystd::vector<tlvertex3d> m_vertBuffer;

	//public: void CRenderer::CRenderer();
	//public: void CRenderer::~CRenderer();
	//public: void CRenderer::SetSize(int, int);
	//public: void CRenderer::SetPixelFormat(enum PixelFormat);
	public: void CRenderer::SetTexture(CTexture* tex);
	public: void CRenderer::SetLmapTexture(CTexture* tex);
	public: void CRenderer::ReleaseCacheSurfaces(void);
	//public: void CRenderer::CreateUnusedCacheSurfaces();
	//public: void CRenderer::ReleaseUnusedCacheSurfaces();
	public: void CRenderer::UnloadRarelyUsedCaches(void);
	public: void CRenderer::DestroyAllRPList(void);
	public: void CRenderer::SetLookAt(vector3d& from, vector3d& at, vector3d& up);
	public: void CRenderer::SetLight(vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol);
	public: void CRenderer::Clear(int clearScreen);
	public: void CRenderer::ClearBackground(void);
	public: void CRenderer::SetBackgroundColor(unsigned long color);
	public: bool CRenderer::DrawScene(void);
	public: int CRenderer::Lock(void);
	public: void CRenderer::Unlock(void);
	public: void CRenderer::Flip(bool vertSync);
	public: void CRenderer::BackupFrame(void);
	public: void CRenderer::RestoreFrame(void);
	public: int CRenderer::SaveBmp(const char* fName, CBitmapRes* bitmap);
	public: int CRenderer::SaveJPG(const char* fName, CBitmapRes* bitmap);
	public: void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow);
	public: void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, tlvertex3d* vert);
	public: float CRenderer::GetPixelRatio(float oow);
	public: float CRenderer::GetScreenXFactor(void);
	//public: float CRenderer::GetScreenYFactor();
	public: void CRenderer::BuildRay(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray);
	//public: struct RPFace& CRenderer::BorrowNullRP();
	public: RPQuadFace& CRenderer::BorrowQuadRP(void);
	//public: struct RPLmQuadFace& CRenderer::BorrowLmQuadRP();
	//public: struct tlvertex3d* CRenderer::BorrowVerts(unsigned int);
	//public: void ResetBorrowedRP();
	public: void CRenderer::AddRP(RPFace* rp, int renderFlag);
	public: void CRenderer::AddRP(RPTriFace* rp, int renderFlag);
	//public: void CRenderer::AddRawRP(struct RPRaw *, int);
	//public: void CRenderer::AddLmRP(struct RPLmFace *, enum RfLmType);
	public: void CRenderer::FlushRenderList(void);
	public: CTexture* CRenderer::AddSpriteIndex(SprImg& img, unsigned long* pal, CacheInfo* info);
	public: CTexture* CRenderer::GetSpriteIndex(SprImg& img, unsigned long palID, CacheInfo* info);
	public: void CRenderer::DoFog(void);
	//public: void CRenderer::FogSwitch(int);
	//public: int FogFactor(float);
	public: void CRenderer::SetMultiTextureMode(int nMode);
	public: int CRenderer::TextOutScreen(int x, int y, const char* text, unsigned long colorRef);
	//public: void CRenderer::ShowInfo();
	//public: void CRenderer::StartFPSCount();
	private: void CRenderer::FlushFaceList(void);
	private: void CRenderer::FlushLMGroundList(void);
	private: void CRenderer::FlushLMLightList(void);
	private: void CRenderer::FlushAlphaDepthList(void);
	private: void CRenderer::FlushAlphaList(void);
	private: void CRenderer::FlushAlphaNoDepthList(void);
	private: void CRenderer::FlushEmissiveDepthList(void);
	private: void CRenderer::FlushEmissiveList(void);
	private: void CRenderer::FlushEmissiveNoDepthList(void);
	private: void CRenderer::FlushRawList(void);
	private: void CRenderer::FlushAlphaRawList(void);
	private: void CRenderer::FlushEmissiveRawList(void);
	private: void CRenderer::FlushEffectList(void);
	private: void CRenderer::FlushBumpList(void);
	private: void CRenderer::FlushLmList(void);

	class RPRawTexPrtLess : public mystd::binary_function<const RPRaw*,const RPRaw*,bool>
	{
		public: bool operator()(const RPRaw* left, const RPRaw* right) // line ???
		{
			return ( left->tex < right->tex );
		}
	};

	class RPFaceTexPrtLess : public mystd::binary_function<const RPFace*,const RPFace*,bool>
	{
		public: bool operator()(const RPFace* left, const RPFace* right) // line ???
		{
			return ( left->tex < right->tex );
		}
	};

	class RPLmFaceTexPrtLess : public mystd::binary_function<const RPLmFace*,const RPLmFace*,bool>
	{
		public: bool operator()(const RPLmFace* left, const RPLmFace* right) // line 566-572
		{
			return ( left->tex != right->tex ) ? ( left->tex < right->tex ) : ( left->tex2 < right->tex2 );
		}
	};

	typedef mystd::list<CacheSurface>::const_iterator cache_surface_vector_iter;
	typedef mystd::list<CTexture*>::const_iterator unused_cache_surface_list_iter;

	/// @custom
	public: int CRenderer::GetWidth(void) { return m_width; }
	public: int CRenderer::GetHeight(void) { return m_height; }
	public: float CRenderer::GetHRatio(void) { return m_hratio; }
	public: float CRenderer::GetVRatio(void) { return m_vratio; }

private:
	static hook_method<void (CRenderer::*)(CTexture* tex)> CRenderer::_SetTexture;
	static hook_method<void (CRenderer::*)(CTexture* tex)> CRenderer::_SetLmapTexture;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_ReleaseCacheSurfaces;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_UnloadRarelyUsedCaches;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_DestroyAllRPList;
	static hook_method<void (CRenderer::*)(vector3d& from, vector3d& at, vector3d& up)> CRenderer::_SetLookAt;
	static hook_method<void (CRenderer::*)(vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol)> CRenderer::_SetLight;
	static hook_method<void (CRenderer::*)(int clearScreen)> CRenderer::_Clear;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_ClearBackground;
	static hook_method<void (CRenderer::*)(unsigned long color)> CRenderer::_SetBackgroundColor;
	static hook_method<bool (CRenderer::*)(void)> CRenderer::_DrawScene;
	static hook_method<int (CRenderer::*)(void)> CRenderer::_Lock;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_Unlock;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushRenderList;
	static hook_method<CTexture* (CRenderer::*)(SprImg& img, unsigned long* pal, CacheInfo* info)> CRenderer::_AddSpriteIndex;
	static hook_method<CTexture* (CRenderer::*)(SprImg& img, unsigned long palID, CacheInfo* info)> CRenderer::_GetSpriteIndex;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_DoFog;
	static hook_method<void (CRenderer::*)(bool vertSync)> CRenderer::_Flip;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_BackupFrame;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_RestoreFrame;
	static hook_method<int (CRenderer::*)(const char* fName, CBitmapRes* bitmap)> CRenderer::_SaveBmp;
	static hook_method<int (CRenderer::*)(const char* fName, CBitmapRes* bitmap)> CRenderer::_SaveJPG;
	static hook_method<void (CRenderer::*)(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow)> CRenderer::_ProjectVertex;
	static hook_method<void (CRenderer::*)(const vector3d& src, const matrix& vtm, tlvertex3d* vert)> CRenderer::_ProjectVertex2;
	static hook_method<float (CRenderer::*)(float oow)> CRenderer::_GetPixelRatio;
	static hook_method<float (CRenderer::*)(void)> CRenderer::_GetScreenXFactor;
	static hook_method<void (CRenderer::*)(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray)> CRenderer::_BuildRay;
	static hook_method<RPQuadFace& (CRenderer::*)(void)> CRenderer::_BorrowQuadRP;
	static hook_method<void (CRenderer::*)(RPFace* rp, int renderFlag)> CRenderer::_AddRP;
	static hook_method<void (CRenderer::*)(RPTriFace* rp, int renderFlag)> CRenderer::_AddRP2;
	static hook_method<void (CRenderer::*)(int nMode)> CRenderer::_SetMultiTextureMode;
	static hook_method<int (CRenderer::*)(int x, int y, const char* text, unsigned long colorRef)> CRenderer::_TextOutScreen;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushFaceList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushLMGroundList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushLMLightList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaDepthList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaNoDepthList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveDepthList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveNoDepthList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushRawList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaRawList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveRawList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEffectList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushBumpList;
	static hook_method<void (CRenderer::*)(void)> CRenderer::_FlushLmList;

	friend class CView; // @see CView::OnRender()
};


class CTexMgr
{
	/* this+0 */ private: mystd::map<const char*, CTexture*, CharPrtLess> m_texTable;
	/* static */ private: static hook_val<CTexture> s_dummy_texture;

	//public: void CTexMgr::CTexMgr();
	//public: void CTexMgr::~CTexMgr();
	public: CTexture* CTexMgr::CreateTexture(unsigned long w, unsigned long h, PixelFormat pf, LPDIRECTDRAWSURFACE7 surface);
	public: CTexture* CTexMgr::CreateTexture(int w, int h, unsigned long* imgData, PixelFormat pf, bool blackkey);
	//public: void CTexMgr::ReCreateTexture(class CTexture *, int, int, unsigned long *);
	public: CTexture* CTexMgr::GetTexture(const char* fName, bool blackkey);
	public: void CTexMgr::DestroyTexture(CTexture* t);
	public: void CTexMgr::DestroyAllTexture(void);
	//public: void CTexMgr::ReloadAllTexture();
	public: void CTexMgr::UnloadRarelyUsedTexture(void);
	public: CTexture* CTexMgr::GetDummyTexture(void);
	//private: CTexture* CTexMgr::FindTexture(const char *);
	//private: CTexture* CTexMgr::LoadTexture(const char *, unsigned char);
	//private: void CTexMgr::AddTexture(class CTexture *);

private:
	static hook_method<CTexture* (CTexMgr::*)(unsigned long w, unsigned long h, PixelFormat pf, LPDIRECTDRAWSURFACE7 surface)> CTexMgr::_CreateTexture;
	static hook_method<CTexture* (CTexMgr::*)(int w, int h, unsigned long* imgData, PixelFormat pf, bool blackkey)> CTexMgr::_CreateTexture2;
	static hook_method<CTexture* (CTexMgr::*)(const char* fName, bool blackkey)> CTexMgr::_GetTexture;
	static hook_method<void (CTexMgr::*)(CTexture* t)> CTexMgr::_DestroyTexture;
	static hook_method<void (CTexMgr::*)(void)> CTexMgr::_DestroyAllTexture;
	static hook_method<void (CTexMgr::*)(void)> CTexMgr::_UnloadRarelyUsedTexture;
	static hook_method<CTexture* (CTexMgr::*)(void)> CTexMgr::_GetDummyTexture;
};


class CDC
{
	struct vtable_t
	{
		void* (CDC::* scalar_deleting_destructor)(unsigned int flags);
		void (CDC::* Resize)(int w, int h); //__purecall
		bool (CDC::* GetDC)(HDC* hdc); //__purecall
		void (CDC::* ReleaseDC)(HDC hdc); //__purecall
		void (CDC::* Update)(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey); //__purecall
		void (CDC::* CopyRect)(int x, int y, int width, int height, CDC* surface); //__purecall
		void (CDC::* BltSprite)(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette); //__purecall
		void (CDC::* BltTexture2)(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy); //__purecall
		void (CDC::* ClearSurface)(RECT* rect, unsigned long color); //__purecall
		void (CDC::* DrawSurface)(int x, int y, int w, int h, unsigned long color); //__purecall
	};

	/* this+0 */ public: //const CDC::`vftable';

	//public: CDC::CDC(void);
	public: virtual CDC::~CDC(void) {}; // line 287
	public: virtual void CDC::Resize(int w, int h) = 0;
	public: virtual bool CDC::GetDC(HDC* hdc) = 0;
	public: virtual void CDC::ReleaseDC(HDC hdc) = 0;
	public: virtual void CDC::Update(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey) = 0;
	public: virtual void CDC::CopyRect(int x, int y, int width, int height, CDC* surface) = 0;
	public: virtual void CDC::BltSprite(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette) = 0;
	public: virtual void CDC::BltTexture2(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy) = 0;
	public: virtual void CDC::ClearSurface(RECT* rect, unsigned long color) = 0;
	public: virtual void CDC::DrawSurface(int x, int y, int w, int h, unsigned long color) = 0;
};


unsigned long __cdecl GetSpecularFromOow(float oow);
float __cdecl GetZFromOow(float oow);
float __cdecl GetOowFromZ(float z);
