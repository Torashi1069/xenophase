#pragma once
#include "Enum.h"
#include <dx9sdk/Include/ddraw.h>


class CSurface
{
	/* this+ 0 */ public: //const CSurface::`vftable';
	/* this+ 4 */ protected: DWORD m_w;
	/* this+ 8 */ protected: DWORD m_h;
	/* this+12 */ protected: LPDIRECTDRAWSURFACE7 m_pddsSurface;

//	public: CSurface::CSurface(DWORD w, DWORD h);
//	public: CSurface::CSurface(DWORD w, DWORD h, LPDIRECTDRAWSURFACE7 surface);
	public: virtual CSurface::~CSurface(void);
	public: virtual void CSurface::Update(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch);
	public: virtual void CSurface::ClearSurface(RECT* rect, DWORD color);
	public: virtual void CSurface::DrawSurface(int x, int y, int width, int height, DWORD color);
	public: virtual void CSurface::DrawSurfaceStretch(int x, int y, int width, int height);
//	public: LPDIRECTDRAWSURFACE7 CSurface::GetDDSurface(void);
//	public: bool CSurface::Create(DWORD w, DWORD h);

public:
	static hook_func<void (CSurface::*)(void)> CSurface::_dCSurface;
	static hook_func<void (CSurface::*)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch)> CSurface::_Update;
	static hook_func<void (CSurface::*)(RECT* rect, DWORD color)> CSurface::_ClearSurface;
	static hook_func<void (CSurface::*)(int x, int y, int width, int height, DWORD color)> CSurface::_DrawSurface;
	static hook_func<void (CSurface::*)(int x, int y, int width, int height)> CSurface::_DrawSurfaceStretch;
};


class CTexture : public CSurface
{
	/* this+  0 */ public: //CSurface baseclass_0;
	/* this+ 16 */ protected: PixelFormat m_pf;
	/* this+ 20 */ protected: bool m_blackkey;
	/* this+ 24 */ protected: DWORD m_updateWidth;
	/* this+ 28 */ protected: DWORD m_updateHeight;
	/* this+ 32 */ protected: char m_texName[256];
	/* this+288 */ protected: long m_lockCnt;
	/* this+292 */ protected: DWORD m_timeStamp;

	//TODO
};


class CTexMgr
{
	public: void CTexMgr::DestroyAllTexture(void);

public:
	static hook_func<void (CTexMgr::*)(void)> CTexMgr::_DestroyAllTexture;
};


extern CTexMgr& g_texMgr;
