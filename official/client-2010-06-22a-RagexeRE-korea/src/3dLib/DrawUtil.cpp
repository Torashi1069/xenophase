#include "3dLib/DC.h"
#include "3dLib/DrawUtil.h"
#include "Framework/Language.h"
#include "Enum.h"
#include "Globals.h"
////////////////////////////////////////


bool g_isHex[320] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};


BOOL __cdecl isHex(char c)
{
	return g_isHex[BYTE(c)];
}


////////////////////////////////////////


DrawDC::DrawDC(CDC* surface)
{
	m_hdc = NULL;
	m_surface = surface;

	if( surface->GetDC(&m_hdc) )
	{
		m_oldFont = (HFONT)::GetCurrentObject(m_hdc, OBJ_FONT);
		::SetBkMode(m_hdc, TRANSPARENT);
	}
}


DrawDC::~DrawDC(void)
{
	if( m_surface != NULL && m_hdc != NULL )
	{
		::SelectObject(m_hdc, m_oldFont);
		m_surface->ReleaseDC(m_hdc);
	}
}


void DrawDC::SetFont(int fontType, int fontHeight, bool bold)
{
	if( fontType == 0 )
	{
		switch( g_languageType )
		{
		case LanguageEnglish:
			if( g_serviceType == ServiceIndonesia )
			{
				fontType = 8;
				fontHeight += 2;
			}
			else
			if( g_serviceType == ServiceRussia )
			{
				fontType = 9;
				fontHeight += 3;
			}
			else
			{
				fontType = 1;
				fontHeight += 3;

				if( g_language != NULL && g_language->m_scriptLangId == 31 )
					fontType = 6;
			}
		break;
		case LanguageJapanese:
			fontType = 2;
		break;
		case LanguageSimplifiedChinese:
			fontType = 3;
		break;
		case LanguageTraditionalChinese:
			fontType = 4;
		break;
		case LanguageThai:
			fontType = 5;
			fontHeight += 3;
		break;
		case LanguagePortuguese:
			fontType = 7;
			fontHeight += 3;

			if( g_serviceType == ServiceBrazil || g_serviceType == ServiceFrance )
				fontHeight -= 2;
		break;
		case LanguageVietnam:
			fontType = 10;
			fontHeight += 3;
		break;
		case LanguageArabic:
			fontType = 11;
			fontHeight += 3;
		break;
		default:
		break;
		}
	}

	if( g_languageType == LanguageKorean && fontType >= 20 )
	{
		m_fontType = fontType;
		m_fontHeight = fontHeight;
		m_charset = g_fontCharSet[0];
		m_bold = bold;
	}
	else
	{
		m_fontType = fontType;
		m_fontHeight = fontHeight;
		m_charset = g_fontCharSet[fontType];
		m_bold = bold;
	}
}


void DrawDC::SetTextColor(COLORREF colorRef)
{
	::SetTextColor(m_hdc, colorRef);
}


hook_func<void (DrawDC::*)(int x, int y, const char* buf, int bufLen)> DrawDC::_TextOutA("DrawDC::TextOutA");
void DrawDC::TextOutA(int x, int y, const char* buf, int bufLen)
{
	return (this->*_TextOutA)(x, y, buf, bufLen);

	//TODO
}


hook_func<void (DrawDC::*)(const char* buf, int bufLen, SIZE* size)> DrawDC::_GetTextExtentPoint32A("DrawDC::GetTextExtentPoint32A");
void DrawDC::GetTextExtentPoint32A(const char* buf, int bufLen, SIZE* size)
{
	return (this->*_GetTextExtentPoint32A)(buf, bufLen, size);

	//TODO
}
