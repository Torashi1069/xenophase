#pragma once
struct CMotion;
class CSprRes;
class CTexture;


class CDC
{
	/* this+0 */ public: //const CDC::`vftable';

	public: virtual CDC::~CDC(void) {};
	public: virtual void CDC::Resize(int w, int h) = 0;
	public: virtual bool CDC::GetDC(HDC* hdc) = 0;
	public: virtual void CDC::ReleaseDC(HDC hdc) = 0;
	public: virtual void CDC::Update(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey) = 0;
	public: virtual void CDC::CopyRect(int x, int y, int width, int height, CDC* surface) = 0;
	public: virtual void CDC::BltSprite(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette) = 0;
	public: virtual void CDC::BltTexture2(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy) = 0;
	public: virtual void CDC::ClearSurface(RECT* rect, COLORREF color) = 0;
	public: virtual void CDC::DrawSurface(int x, int y, int w, int h, COLORREF color) = 0;
};
