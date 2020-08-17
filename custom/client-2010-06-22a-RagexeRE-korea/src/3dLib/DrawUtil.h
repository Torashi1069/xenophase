#pragma once
class CDC;


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
	/* this+30 */ protected: bool m_field_1E_TODO;

	public: DrawDC::DrawDC(CDC* surface);
	public: DrawDC::~DrawDC(void);
	public: void DrawDC::SetFont(int fontType, int fontHeight, bool bold);
	public: void DrawDC::SetTextColor(COLORREF colorRef);
	public: void DrawDC::TextOutA(int x, int y, const char* buf, int bufLen);
	public: void DrawDC::GetTextExtentPoint32A(const char* buf, int bufLen, SIZE* size);
	//...

private:
	static hook_func<void (DrawDC::*)(int x, int y, const char* buf, int bufLen)> DrawDC::_TextOutA;
	static hook_func<void (DrawDC::*)(const char* buf, int bufLen, SIZE* size)> DrawDC::_GetTextExtentPoint32A;
};
C_ASSERT( sizeof DrawDC == 32 );


BOOL __cdecl isHex(char c);
