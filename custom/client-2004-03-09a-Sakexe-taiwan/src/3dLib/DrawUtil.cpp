#include "3dLib/DrawUtil.h"
#include "3dLib/Renderer.h"


mystd::vector<unsigned short>& DrawDC::s_wideBuffer = *(mystd::vector<unsigned short>*)DetourFindFunction(SAKEXE, "DrawDC::s_wideBuffer");


hook_func<int (__cdecl *)(const char* buf, int bufLen)> _FindCharSet(SAKEXE, "FindCharSet");
int __cdecl FindCharSet(const char* buf, int bufLen) // line 102
{
	return (_FindCharSet)(buf, bufLen);

	//TODO
}


hook_func<int (__cdecl *)(const char* buf)> _ReadCharSet(SAKEXE, "ReadCharSet");
int __cdecl ReadCharSet(const char* buf) // line 115
{
	return (_ReadCharSet)(buf);

	//TODO
}


hook_func<void (__cdecl *)(int x, int y, int cx, int cy, unsigned int color)> _DrawBoxScreen(SAKEXE, "DrawBoxScreen");
void __cdecl DrawBoxScreen(int x, int y, int cx, int cy, unsigned int color) // line 123
{
	return (_DrawBoxScreen)(x, y, cx, cy, color);

	//TODO
}


////////////////////////////////////////


DrawDC::DrawDC(CDC* surface) // line 294
{
	m_hdc = NULL;
	m_surface = surface;

	if( surface->GetDC(&m_hdc) )
	{
		m_oldFont = (HFONT)GetCurrentObject(m_hdc, OBJ_FONT);
		SetBkMode(m_hdc, TRANSPARENT);
	}
}


DrawDC::~DrawDC(void)
{
	if( m_surface != NULL && m_hdc != NULL )
	{
		SelectObject(m_hdc, m_oldFont);
		m_surface->ReleaseDC(m_hdc);
	}
}


hook_method<void (DrawDC::*)(int fontType, int fontHeight, bool bold)> DrawDC::_SetFont(SAKEXE, "DrawDC::SetFont");
void DrawDC::SetFont(int fontType, int fontHeight, bool bold)
{
	return (this->*_SetFont)(fontType, fontHeight, bold);

	//TODO
}


hook_method<void (DrawDC::*)(unsigned long colorRef)> DrawDC::_SetTextColor(SAKEXE, "DrawDC::SetTextColor");
void DrawDC::SetTextColor(unsigned long colorRef)
{
	return (this->*_SetTextColor)(colorRef);

	::SetTextColor(m_hdc, colorRef);
}


hook_method<void (DrawDC::*)(int x, int y, const char* buf, int bufLen)> DrawDC::_TextOutA(SAKEXE, "DrawDC::TextOutA");
void DrawDC::TextOutA(int x, int y, const char* buf, int bufLen) // line 356
{
	return (this->*_TextOutA)(x, y, buf, bufLen);

	//TODO
}


hook_method<void (DrawDC::*)(const char* buf, int bufLen, SIZE* size)> DrawDC::_GetTextExtentPoint32A(SAKEXE, "DrawDC::GetTextExtentPoint32A");
void DrawDC::GetTextExtentPoint32A(const char* buf, int bufLen, SIZE* size)
{
	return (this->*_GetTextExtentPoint32A)(buf, bufLen, size);

	//TODO
}


//hook_method<HDC (DrawDC::*)(void)> DrawDC::_operator_HDC(SAKEXE, "???");
DrawDC::operator HDC(void) // line ??
{
//	return (this->*_operator_HDC)();

	return m_hdc;
}


hook_method<void (DrawDC::*)(int x, int y, const char* buf, int bufLen, int charset)> DrawDC::__textout(SAKEXE, "DrawDC::_textout");
void DrawDC::_textout(int x, int y, const char* buf, int bufLen, int charset)
{
	return (this->*__textout)(x, y, buf, bufLen, charset);

	//TODO
}


hook_method<void (DrawDC::*)(const char* buf, int bufLen, SIZE* size, int charset)> DrawDC::__gettextsize(SAKEXE, "DrawDC::_gettextsize");
void DrawDC::_gettextsize(const char* buf, int bufLen, SIZE* size, int charset)
{
	return (this->*__gettextsize)(buf, bufLen, size, charset);

	//TODO
}
