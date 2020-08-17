#include "3dLib/DC.h"


CDCBitmap::CDCBitmap(unsigned long w, unsigned long h)
{
}


CDCBitmap::~CDCBitmap(void)
{
}


hook_method<void (CDCBitmap::*)(int w, int h)> CDCBitmap::_Resize(SAKEXE, "CDCBitmap::Resize");
void CDCBitmap::Resize(int w, int h)
{
	return (this->*_Resize)(w, h);

	//TODO
}


hook_method<bool (CDCBitmap::*)(HDC* hdc)> CDCBitmap::_GetDC(SAKEXE, "CDCBitmap::GetDC");
bool CDCBitmap::GetDC(HDC* hdc)
{
	return (this->*_GetDC)(hdc);

	//TODO
}


hook_method<void (CDCBitmap::*)(HDC hdc)> CDCBitmap::_ReleaseDC(SAKEXE, "CDCBitmap::ReleaseDC");
void CDCBitmap::ReleaseDC(HDC hdc)
{
	return (this->*_ReleaseDC)(hdc);

	//TODO
}


hook_method<void (CDCBitmap::*)(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey)> CDCBitmap::_Update(SAKEXE, "CDCBitmap::Update");
void CDCBitmap::Update(int x, int y, int width, int height, unsigned long* imgData, bool SkipColorKey)
{
	return (this->*_Update)(x, y, width, height, imgData, SkipColorKey);

	if( m_image == NULL )
		return;

	if( imgData == NULL )
		return;

	m_dirty = true;

	unsigned long* data = imgData;
	for( int i = 0; i < height; ++i )
	{
		for( int j = 0; j < width; ++j )
		{
			unsigned long color = data[j];

			if( SkipColorKey && color == 0xFFFF00FF )
				continue;

			m_image[x + j + m_w * (y + i)] = color;
		}

		data += width;
	}
}


hook_method<void (CDCBitmap::*)(int x, int y, int width, int height, CDC* surface)> CDCBitmap::_CopyRect(SAKEXE, "CDCBitmap::CopyRect");
void CDCBitmap::CopyRect(int x, int y, int width, int height, CDC* surface)
{
	return (this->*_CopyRect)(x, y, width, height, surface);

	//TODO
}


hook_method<void (CDCBitmap::*)(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette)> CDCBitmap::_BltSprite(SAKEXE, "CDCBitmap::BltSprite");
void CDCBitmap::BltSprite(int x, int y, CSprRes* sprRes, CMotion* curMotion, unsigned long* palette)
{
	return (this->*_BltSprite)(x, y, sprRes, curMotion, palette);

	//TODO
}


hook_method<void (CDCBitmap::*)(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy)> CDCBitmap::_BltTexture2(SAKEXE, "CDCBitmap::BltTexture2");
void CDCBitmap::BltTexture2(int x, int y, CTexture* src, int srcx, int srcy, int width, int height, int xflip, int zoomx, int zoomy)
{
	return (this->*_BltTexture2)(x, y, src, srcx, srcy, width, height, xflip, zoomx, zoomy);

	//TODO
}


hook_method<void (CDCBitmap::*)(RECT* rect, unsigned long color)> CDCBitmap::_ClearSurface(SAKEXE, "CDCBitmap::ClearSurface");
void CDCBitmap::ClearSurface(RECT* rect, unsigned long color)
{
	return (this->*_ClearSurface)(rect, color);

	//TODO
}


hook_method<void (CDCBitmap::*)(int x, int y, int w, int h, unsigned long color)> CDCBitmap::_DrawSurface(SAKEXE, "CDCBitmap::DrawSurface");
void CDCBitmap::DrawSurface(int x, int y, int w, int h, unsigned long color)
{
	return (this->*_DrawSurface)(x, y, w, h, color);

	//TODO
}


hook_method<void (CDCBitmap::*)(void)> CDCBitmap::_UpdateSurface(SAKEXE, "CDCBitmap::UpdateSurface");
void CDCBitmap::UpdateSurface(void)
{
	return (this->*_UpdateSurface)();

	//TODO
}


hook_method<void (CDCBitmap::*)(unsigned long w, unsigned long h)> CDCBitmap::_CreateDCSurface(SAKEXE, "CDCBitmap::CreateDCSurface");
void CDCBitmap::CreateDCSurface(unsigned long w, unsigned long h)
{
	return (this->*_CreateDCSurface)(w, h);

	//TODO
}
