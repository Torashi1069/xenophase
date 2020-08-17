#pragma once
#include "Enum.h" // PixelFormat
#include <dx9sdk/Include/ddraw.h>


class CSurface
{
	struct vtable_t
	{
		void* (CSurface::* scalar_deleting_destructor)(unsigned int flags);
		void (CSurface::* Update)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch);
		void (CSurface::* ClearSurface)(RECT* rect, DWORD color);
		void (CSurface::* DrawSurface)(int x, int y, int width, int height, DWORD color);
		void (CSurface::* DrawSurfaceStretch)(int x, int y, int width, int height);
	};

	/* this+ 0 */ public: //const CSurface::`vftable';
	/* this+ 4 */ protected: DWORD m_w;
	/* this+ 8 */ protected: DWORD m_h;
	/* this+12 */ protected: LPDIRECTDRAWSURFACE7 m_pddsSurface;

	public: CSurface::CSurface(void);
	public: CSurface::CSurface(DWORD w, DWORD h);
	public: CSurface::CSurface(DWORD w, DWORD h, LPDIRECTDRAWSURFACE7 surface);
	public: virtual CSurface::~CSurface(void);
	public: virtual void CSurface::Update(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch);
	public: virtual void CSurface::ClearSurface(RECT* rect, DWORD color);
	public: virtual void CSurface::DrawSurface(int x, int y, int width, int height, DWORD color);
	public: virtual void CSurface::DrawSurfaceStretch(int x, int y, int width, int height);
	public: LPDIRECTDRAWSURFACE7 CSurface::GetDDSurface(void);
	public: bool CSurface::Create(DWORD w, DWORD h);

private:
	static hook_func<void (CSurface::*)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch)> CSurface::_Update;
	static hook_func<void (CSurface::*)(RECT* rect, DWORD color)> CSurface::_ClearSurface;
	static hook_func<void (CSurface::*)(int x, int y, int width, int height, DWORD color)> CSurface::_DrawSurface;
	static hook_func<void (CSurface::*)(int x, int y, int width, int height)> CSurface::_DrawSurfaceStretch;
	static hook_func<LPDIRECTDRAWSURFACE7 (CSurface::*)(void)> CSurface::_GetDDSurface;
	static hook_func<bool (CSurface::*)(DWORD w, DWORD h)> CSurface::_Create;
};


class CTexture : public CSurface
{
	struct vtable_t // const CTexture::`vftable'
	{
		void* (CTexture::* scalar_deleting_destructor)(unsigned int flags);
		void (CTexture::* Update)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch);
		void (CTexture::* ClearSurface)(RECT* rect, DWORD color);
		void (CTexture::* DrawSurface)(int x, int y, int width, int height, DWORD color);
		void (CTexture::* DrawSurfaceStretch)(int x, int y, int width, int height);
	};

	/* this+  0 */ public: //CSurface baseclass_0;
	/* this+ 16 */ protected: enum PixelFormat m_pf;
	/* this+ 20 */ protected: bool m_blackkey;
	/* this+ 24 */ protected: DWORD m_updateWidth;
	/* this+ 28 */ protected: DWORD m_updateHeight;
	/* this+ 32 */ protected: char m_texName[256];
	/* this+288 */ protected: long m_lockCnt;
	/* this+292 */ protected: DWORD m_timeStamp;
	/* static   */ protected: static hook_val<float> m_uOffset;
	/* static   */ protected: static hook_val<float> m_vOffset;

	public: virtual void CTexture::Update(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch);
	//public: void CTexture::UpdateSprite(int x, int y, int width, int height, SprImg& img, DWORD* pal);
	public: virtual void CTexture::ClearSurface(RECT* rect, DWORD color);
	public: virtual void CTexture::DrawSurface(int x, int y, int w, int h, DWORD color);
	public: virtual void CTexture::DrawSurfaceStretch(int x, int y, int w, int h);
	public: float CTexture::GetUAdjust(void);
	public: float CTexture::GetVAdjust(void);
	//public: enum PixelFormat GetPixelFormat();
	//public: static void SetUVOffset(float, float);
	public: long CTexture::Lock(void);
	public: long CTexture::Unlock(void);
	//public: long GetLockCount();
	//public: void UpdateStamp();
	//public: void SetName(const char *);
	//public: bool CTexture::CopyTexture(class CTexture *, int, int, int, int, int, int, int, int);
	protected: CTexture::CTexture(DWORD w, DWORD h, enum PixelFormat pf);
	protected: CTexture::CTexture(DWORD w, DWORD h, enum PixelFormat pf, LPDIRECTDRAWSURFACE7 surface);
	protected: bool CTexture::Create(DWORD h, DWORD w, enum PixelFormat pf);
	protected: bool CTexture::CreateBump(DWORD w, DWORD h);
	protected: bool CTexture::CreateBump(DWORD w, DWORD h, LPDIRECTDRAWSURFACE7 pSurface);
	//protected: void CTexture::SetUVAdjust(unsigned long, unsigned long);
	//protected: void CTexture::UpdateMipmap(RECT &);

private:
	static hook_method<void (CTexture::*)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch)> CTexture::_Update;
	static hook_method<void (CTexture::*)(RECT* rect, DWORD color)> CTexture::_ClearSurface;
	static hook_method<void (CTexture::*)(int x, int y, int w, int h, DWORD color)> CTexture::_DrawSurface;
	static hook_method<void (CTexture::*)(int x, int y, int w, int h)> CTexture::_DrawSurfaceStretch;
	static hook_method<float (CTexture::*)(void)> CTexture::_GetUAdjust;
	static hook_method<float (CTexture::*)(void)> CTexture::_GetVAdjust;
	static hook_method<long (CTexture::*)(void)> CTexture::_Lock;
	static hook_method<long (CTexture::*)(void)> CTexture::_Unlock;
	static hook_method<bool (CTexture::*)(DWORD h, DWORD w, enum PixelFormat pf)> CTexture::_Create;
	static hook_method<bool (CTexture::*)(DWORD w, DWORD h)> CTexture::_CreateBump;
	static hook_method<bool (CTexture::*)(DWORD w, DWORD h, LPDIRECTDRAWSURFACE7 pSurface)> CTexture::_CreateBump2;
};
