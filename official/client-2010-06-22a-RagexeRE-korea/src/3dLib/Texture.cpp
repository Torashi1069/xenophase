#include "3dLib/Texture.h"
////////////////////////////////////////


hook_func<void (CSurface::*)(void)> CSurface::_dCSurface("CSurface::~CSurface");
CSurface::~CSurface(void)
{
	(this->*_dCSurface)(); return;

	//TODO
}


hook_method<void (CSurface::*)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch)> CSurface::_Update("CSurface::Update");
void CSurface::Update(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch)
{
	return (this->*_Update)(x, y, width, height, image, blackkey, lPitch);
}


hook_method<void (CSurface::*)(RECT* rect, DWORD color)> CSurface::_ClearSurface("CSurface::ClearSurface");
void CSurface::ClearSurface(RECT* rect, DWORD color)
{
	return (this->*_ClearSurface)(rect, color);
}


hook_method<void (CSurface::*)(int x, int y, int width, int height, DWORD color)> CSurface::_DrawSurface("CSurface::DrawSurface");
void CSurface::DrawSurface(int x, int y, int width, int height, DWORD color)
{
	return (this->*_DrawSurface)(x, y, width, height, color);
}


hook_method<void (CSurface::*)(int x, int y, int width, int height)> CSurface::_DrawSurfaceStretch("CSurface::DrawSurfaceStretch");
void CSurface::DrawSurfaceStretch(int x, int y, int width, int height)
{
	return (this->*_DrawSurfaceStretch)(x, y, width, height);
}


////////////////////////////////////////


hook_func<void (CTexMgr::*)(void)> CTexMgr::_DestroyAllTexture("CTexMgr::DestroyAllTexture");
void CTexMgr::DestroyAllTexture(void)
{
	return (this->*_DestroyAllTexture)();
}


CTexMgr& g_texMgr = VTOR<CTexMgr>(SymDB::Find("g_texMgr"));
