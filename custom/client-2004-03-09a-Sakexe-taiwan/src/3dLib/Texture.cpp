#include "Texture.h"


hook_val<float> CTexture::m_uOffset(SAKEXE, "CTexture::m_uOffset"); // = 0.5;
hook_val<float> CTexture::m_vOffset(SAKEXE, "CTexture::m_vOffset"); // = 0.5;


////////////////////////////////////////


CSurface::CSurface(void) // line ??
: m_pddsSurface(NULL)
{
}


CSurface::CSurface(unsigned long w, unsigned long h) // line 82-84
: m_pddsSurface(NULL)
{
	this->CSurface::Create(w, h);
}


CSurface::CSurface(unsigned long w, unsigned long h, LPDIRECTDRAWSURFACE7 surface) // line 88-89
: m_w(w), m_h(h), m_pddsSurface(surface)
{
}


CSurface::~CSurface(void) // line 92-94
{
	if( m_pddsSurface != NULL )
	{
		m_pddsSurface->Release();
		m_pddsSurface = NULL;
	}
}


hook_func<void (CSurface::*)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch)> CSurface::_Update(SAKEXE, "CSurface::Update");
void CSurface::Update(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch) // line 97-150
{
	return (this->*_Update)(x, y, width, height, image, blackkey, lPitch);

	//TODO
}


hook_func<void (CSurface::*)(RECT* rect, DWORD color)> CSurface::_ClearSurface(SAKEXE, "CSurface::ClearSurface");
void CSurface::ClearSurface(RECT* rect, DWORD color) // line 153-162
{
	return (this->*_ClearSurface)(rect, color);

	//TODO
}


hook_func<void (CSurface::*)(int x, int y, int width, int height, DWORD color)> CSurface::_DrawSurface(SAKEXE, "CSurface::DrawSurface");
void CSurface::DrawSurface(int x, int y, int width, int height, DWORD color) // line 165-177
{
	return (this->*_DrawSurface)(x, y, width, height, color);

	//TODO
}


hook_func<void (CSurface::*)(int x, int y, int width, int height)> CSurface::_DrawSurfaceStretch(SAKEXE, "CSurface::DrawSurfaceStretch");
void CSurface::DrawSurfaceStretch(int x, int y, int width, int height) // line 180-184
{
	return (this->*_DrawSurfaceStretch)(x, y, width, height);

	//TODO
}


//hook_func<LPDIRECTDRAWSURFACE7 (CSurface::*)(void)> CSurface::_GetDDSurface(SAKEXE, "CSurface::GetDDSurface");
LPDIRECTDRAWSURFACE7 CSurface::GetDDSurface(void) // line ???
{
//	return (this->*_GetDDSurface)();

	return m_pddsSurface;
}


hook_func<bool (CSurface::*)(DWORD w, DWORD h)> CSurface::_Create(SAKEXE, "CSurface::Create");
bool CSurface::Create(DWORD w, DWORD h) // line 187-211
{
	return (this->*_Create)(w, h);

	//TODO
}


////////////////////////////////////////


CTexture::CTexture(DWORD w, DWORD h, enum PixelFormat pf) // line 231-239
{
	m_lockCnt = 0;
	m_timeStamp = 0;
	m_texName[0] = '\0';

	if( pf == PF_BUMP )
	{
		this->CTexture::CreateBump(w, h);
	}
	else
	{
		this->CTexture::Create(w, h, pf);

		DWORD i, j;
		for( i = w; i > m_w; i = i / 2 ) {};
		for( j = h; j > m_h; j = j / 2 ) {};

		m_updateWidth = i;
		m_updateHeight = j;
	}
}


CTexture::CTexture(DWORD w, DWORD h, enum PixelFormat pf, LPDIRECTDRAWSURFACE7 surface) // line 243-251
{
	m_lockCnt = 0;
	m_timeStamp = 0;
	m_pf = pf;

	m_w = w;
	m_h = h;

	if( pf == PF_BUMP )
		this->CTexture::CreateBump(w, h, surface);
	else
		m_pddsSurface = surface;
}


hook_method<bool (CTexture::*)(DWORD h, DWORD w, enum PixelFormat pf)> CTexture::_Create(SAKEXE, "CTexture::Create");
bool CTexture::Create(DWORD h, DWORD w, enum PixelFormat pf) // line 531-
{
	return (this->*_Create)(h, w, pf);

	//TODO
}


hook_method<bool (CTexture::*)(DWORD w, DWORD h)> CTexture::_CreateBump(SAKEXE, "CTexture::CreateBump");
bool CTexture::CreateBump(DWORD w, DWORD h) // line 576-659
{
	return (this->*_CreateBump)(w, h);

	//TODO
}


hook_method<bool (CTexture::*)(DWORD w, DWORD h, LPDIRECTDRAWSURFACE7 pSurface)> CTexture::_CreateBump2(SAKEXE, "CTexture::CreateBump");
bool CTexture::CreateBump(DWORD w, DWORD h, LPDIRECTDRAWSURFACE7 pSurface) // line 662-773
{
	return (this->*_CreateBump2)(w, h, pSurface);

	//TODO
}


hook_method<void (CTexture::*)(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch)> CTexture::_Update(SAKEXE, "CTexture::Update");
void CTexture::Update(int x, int y, int width, int height, unsigned long* image, bool blackkey, int lPitch) // line 312-441
{
	return (this->*_Update)(x, y, width, height, image, blackkey, lPitch);

	//TODO
}


hook_method<void (CTexture::*)(RECT* rect, DWORD color)> CTexture::_ClearSurface(SAKEXE, "CTexture::ClearSurface");
void CTexture::ClearSurface(RECT* rect, DWORD color) // line 254-263
{
	return (this->*_ClearSurface)(rect, color);

	//TODO
}


hook_method<void (CTexture::*)(int x, int y, int w, int h, DWORD color)> CTexture::_DrawSurface(SAKEXE, "CTexture::DrawSurface");
void CTexture::DrawSurface(int x, int y, int w, int h, DWORD color) // line 493-509
{
	return (this->*_DrawSurface)(x, y, w, h, color);

	//TODO
}


hook_method<void (CTexture::*)(int x, int y, int w, int h)> CTexture::_DrawSurfaceStretch(SAKEXE, "CTexture::DrawSurfaceStretch");
void CTexture::DrawSurfaceStretch(int x, int y, int w, int h) // line 512-528
{
	return (this->*_DrawSurfaceStretch)(x, y, w, h);

	//TODO
}


//hook_method<float (CTexture::*)(void)> CTexture::_GetUAdjust(SAKEXE, "CTexture::GetUAdjust");
float CTexture::GetUAdjust(void) // line ???
{
//	return (this->*_GetUAdjust)();

	return (float)m_updateWidth / (float)m_w; // guessed
}


//hook_method<float (CTexture::*)(void)> CTexture::_GetVAdjust(SAKEXE, "CTexture::GetVAdjust");
float CTexture::GetVAdjust(void) // line ???
{
//	return (this->*_GetVAdjust)();

	return (float)m_updateHeight / (float)m_h; // guessed
}


hook_method<long (CTexture::*)(void)> CTexture::_Lock(SAKEXE, "CTexture::Lock");
long CTexture::Lock(void) // line 266
{
	return (this->*_Lock)();

	m_timeStamp = timeGetTime();
	return ++m_lockCnt;
}


hook_method<long (CTexture::*)(void)> CTexture::_Unlock(SAKEXE, "CTexture::Unlock");
long CTexture::Unlock(void) // line 274
{
	return (this->*_Unlock)();

	return --m_lockCnt;
}
