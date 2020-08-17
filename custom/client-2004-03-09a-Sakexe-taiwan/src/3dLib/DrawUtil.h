#pragma once
class CDC;


int __cdecl FindCharSet(const char* buf, int bufLen);
int __cdecl ReadCharSet(const char* buf);
void __cdecl DrawBoxScreen(int x, int y, int cx, int cy, unsigned int color);


class DrawDC
{
	/* this+ 0 */ protected: HDC m_hdc;
	/* this+ 4 */ protected: HFONT m_oldFont;
	/* this+ 8 */ protected: CDC* m_surface;
	/* this+12 */ protected: int m_fontType;
	/* this+16 */ protected: int m_fontHeight;
	/* this+20 */ protected: int m_charset;
	/* this+24 */ protected: int m_fontWeight;
	/* this+28 */ protected: bool m_vertical;
	/* this+29 */ protected: bool m_bold;
	/* static  */ protected: static mystd::vector<unsigned short>& s_wideBuffer;

	public: DrawDC::DrawDC(CDC* surface);
	public: DrawDC::~DrawDC(void);
	public: void DrawDC::SetFont(int fontType, int fontHeight, bool bold);
	public: void DrawDC::SetTextColor(unsigned long colorRef);
	public: void DrawDC::TextOutA(int x, int y, const char* buf, int bufLen);
	public: void DrawDC::GetTextExtentPoint32A(const char* buf, int bufLen, SIZE* size);
	public: operator DrawDC::HDC(void);
	protected: void DrawDC::_textout(int x, int y, const char* buf, int bufLen, int charset);
	protected: void DrawDC::_gettextsize(const char* buf, int bufLen, SIZE* size, int charset);

private:
	static hook_method<void (DrawDC::*)(int fontType, int fontHeight, bool bold)> DrawDC::_SetFont;
	static hook_method<void (DrawDC::*)(unsigned long colorRef)> DrawDC::_SetTextColor;
	static hook_method<void (DrawDC::*)(int x, int y, const char* buf, int bufLen)> DrawDC::_TextOutA;
	static hook_method<void (DrawDC::*)(const char* buf, int bufLen, SIZE* size)> DrawDC::_GetTextExtentPoint32A;
	static hook_method<HDC (DrawDC::*)(void)> DrawDC::_operator_HDC;
	static hook_method<void (DrawDC::*)(int x, int y, const char* buf, int bufLen, int charset)> DrawDC::__textout;
	static hook_method<void (DrawDC::*)(const char* buf, int bufLen, SIZE* size, int charset)> DrawDC::__gettextsize;
};
