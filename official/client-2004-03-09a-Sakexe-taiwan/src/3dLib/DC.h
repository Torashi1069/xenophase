#pragma once
#include "3dLib/Renderer.h" // CDC


class CDCBitmap : public CDC
{
	struct vtable_t // const CDCBitmap::`vftable'
	{
		void* (CDCBitmap::* scalar_deleting_destructor)(unsigned int flags);
		void (CDCBitmap::* Resize)(int w, int h);
		bool (CDCBitmap::* GetDC)(HDC* hdc);
		void (CDCBitmap::* ReleaseDC)(HDC hdc);
		void (CDCBitmap::* Update)(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey);
		void (CDCBitmap::* CopyRect)(int x, int y, int width, int height, CDC* surface);
		void (CDCBitmap::* BltSprite)(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette);
		void (CDCBitmap::* BltTexture2)(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy);
		void (CDCBitmap::* ClearSurface)(RECT* rect, unsigned long color);
		void (CDCBitmap::* DrawSurface)(int x, int y, int w, int h, unsigned long color);
	};

	/* this+ 0 */ public: //CDC baseclass_0;
	/* this+ 4 */ protected: unsigned long m_w;
	/* this+ 8 */ protected: unsigned long m_h;
	/* this+12 */ protected: HDC m_dc;
	/* this+16 */ protected: HBITMAP m_bitmap;
	/* this+20 */ protected: HBITMAP m_bitmapOld;
	/* this+24 */ protected: unsigned long* m_image;
	/* this+28 */ protected: bool m_dirty;
	/* this+32 */ protected: mystd::list<CTexture*> m_textureList;

	public: CDCBitmap::CDCBitmap(unsigned long w, unsigned long h);
	public: virtual CDCBitmap::~CDCBitmap(void);
	public: virtual void CDCBitmap::Resize(int w, int h);
	public: virtual bool CDCBitmap::GetDC(HDC* hdc);
	public: virtual void CDCBitmap::ReleaseDC(HDC hdc);
	public: virtual void CDCBitmap::Update(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey);
	public: virtual void CDCBitmap::CopyRect(int x, int y, int width, int height, CDC* surface);
	public: virtual void CDCBitmap::BltSprite(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette);
	public: virtual void CDCBitmap::BltTexture2(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy);
	public: virtual void CDCBitmap::ClearSurface(RECT* rect, unsigned long color);
	public: virtual void CDCBitmap::DrawSurface(int x, int y, int w, int h, unsigned long color);
	protected: void CDCBitmap::UpdateSurface(void);
	protected: void CDCBitmap::CreateDCSurface(unsigned long w, unsigned long h);

	typedef mystd::list<CTexture*>::const_iterator texListIter;

private:
	static hook_method<void (CDCBitmap::*)(int w, int h)> CDCBitmap::_Resize;
	static hook_method<bool (CDCBitmap::*)(HDC* hdc)> CDCBitmap::_GetDC;
	static hook_method<void (CDCBitmap::*)(HDC hdc)> CDCBitmap::_ReleaseDC;
	static hook_method<void (CDCBitmap::*)(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey)> CDCBitmap::_Update;
	static hook_method<void (CDCBitmap::*)(int x, int y, int width, int height, CDC* surface)> CDCBitmap::_CopyRect;
	static hook_method<void (CDCBitmap::*)(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette)> CDCBitmap::_BltSprite;
	static hook_method<void (CDCBitmap::*)(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy)> CDCBitmap::_BltTexture2;
	static hook_method<void (CDCBitmap::*)(RECT* rect, unsigned long color)> CDCBitmap::_ClearSurface;
	static hook_method<void (CDCBitmap::*)(int x, int y, int w, int h, unsigned long color)> CDCBitmap::_DrawSurface;
	static hook_method<void (CDCBitmap::*)(void)> CDCBitmap::_UpdateSurface;
	static hook_method<void (CDCBitmap::*)(unsigned long w, unsigned long h)> CDCBitmap::_CreateDCSurface;
};
