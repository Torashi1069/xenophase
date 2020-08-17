#include "Window/UIControl.h"
#include "Window/UISys.h" // CutString()
////////////////////////////////////////


UIBalloonText::UIBalloonText(void)
{
	m_stateCnt = 0;
	m_isBold = false;
	m_fontSize = 12;
	m_fontColor = 0xFFFFFF;
	m_bgColor = 0x000000;
//	m_isBack = false;
}


UIBalloonText::~UIBalloonText(void)
{
}


bool UIBalloonText::ShouldDoHitTest(void)
{
	return false;
}


void UIBalloonText::OnProcess(void)
{
	++m_stateCnt;
}


void UIBalloonText::OnDraw(void)
{
	this->UIWindow::ClearDC(0xFFFFFF);

	int cy = 4;
	for( size_t i = 0; i < m_strings.size(); ++i )
	{
		this->UIWindow::TextOutA(6, cy, m_strings[i].c_str(), 0, 0, m_fontSize, m_fontColor);
		cy += this->UIWindow::GetTextHeight(m_strings[i].c_str(), 0, 0, m_fontSize, false) + 4;
	}
}


void UIBalloonText::SetText(const char* msg, const int maxNumCharLine)
{
	if( strlen(msg) == 0 )
		return;

	m_strings.clear();

	CutString(msg, m_strings, maxNumCharLine);

	if( m_strings.size() != 0 )
		this->UIBalloonText::AdjustSizeByText();
}


void UIBalloonText::AddText(const char* msg)
{
	m_strings.push_back(msg);
	this->UIBalloonText::AdjustSizeByText();
}


void UIBalloonText::SetFntColor(COLORREF fontColor, COLORREF bgColor)
{
	m_fontColor = fontColor;
	m_bgColor = bgColor;
}


void UIBalloonText::SetFntSize(int fontSize)
{
	m_fontSize = fontSize;
	this->UIBalloonText::AdjustSizeByText();
}


void UIBalloonText::SetBackTrans(bool isBack) // inlined
{
	m_isBack = isBack;
}


void UIBalloonText::AdjustSizeByText(void)
{
	int cx = 0;
	int cy = 4;

	for( size_t i = 0; i < m_strings.size(); ++i )
	{
		switch( m_charfont )
		{
		case 2:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 20, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 20, m_fontSize, 0);
		break;
		case 1:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 21, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 21, m_fontSize, 0);
		break;
		case 3:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 22, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 22, m_fontSize, 0);
		break;
		case 4:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 23, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 23, m_fontSize, 0);
		break;
		case 5:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 24, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 24, m_fontSize, 0);
		break;
		case 6:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 25, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 25, m_fontSize, 0);
		break;
		case 7:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 26, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 26, m_fontSize, 0);
		break;
		case 8:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 27, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 27, m_fontSize, 0);
		break;
		case 9:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 28, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 28, m_fontSize, 0);
		break;
		default:
			if( cx <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 0, m_fontSize, 0) )
				cx  = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 0, m_fontSize, 0);
		break;
		}

		if( m_charfont == 3 )
			cy += this->UIWindow::GetTextHeight(m_strings[i].c_str(), 0, 22, m_fontSize, false) + 4;
		else
			cy += this->UIWindow::GetTextHeight(m_strings[i].c_str(), 0, 0, m_fontSize, false) + 4;
	}

	this->Resize(cx + 12, cy);
	this->Invalidate();
}


////////////////////////////////////////


hook_func<void (UINameBalloonText::*)(const char* cName)> UINameBalloonText::_SetNameText2("?SetNameText@UINameBalloonText@@UAEXPBD@Z");
void UINameBalloonText::SetNameText(const char* cName)
{
	return (this->*_SetNameText2)(cName);

	//TODO
}


hook_func<void (UINameBalloonText::*)(const NamePair& namePair, bool cutSharp)> UINameBalloonText::_SetNameText("?SetNameText@UINameBalloonText@@UAEXABUNamePair@@_N@Z");
void UINameBalloonText::SetNameText(const NamePair& namePair, bool cutSharp)
{
	return (this->*_SetNameText)(namePair, cutSharp);

	//TODO
}


////////////////////////////////////////


UITransBalloonText::UITransBalloonText(void)
{
	m_borderLineColor = 0x5C5C5C;
}


UITransBalloonText::~UITransBalloonText(void)
{
}


void UITransBalloonText::Resize(int cx, int cy)
{
	this->UIWindow::Resize(cx, cy);
	m_transBoxInfo.cx = m_w;
	m_transBoxInfo.cy = m_h;
}


void UITransBalloonText::Move(int x, int y)
{
	this->UIWindow::Move(x, y);
	m_transBoxInfo.x = m_x;
	m_transBoxInfo.y = m_y;
}


bool UITransBalloonText::GetTransBoxInfo(BOXINFO* boxInfo)
{
	memcpy(boxInfo, &m_transBoxInfo, sizeof(*boxInfo));
	return true;
}


void UITransBalloonText::OnCreate(int cx, int cy)
{
	m_transBoxInfo.x = m_x;
	m_transBoxInfo.y = m_y;
	m_transBoxInfo.cx = m_w;
	m_transBoxInfo.drawEdge = 0;
	m_transBoxInfo.cy = m_h;
	m_transBoxInfo.color = 0x66000000;
	m_transBoxInfo.color2 = 0x00000000;
	m_charfont = 0;
}


void UITransBalloonText::OnDraw(void)
{
	this->UIWindow::ClearDC(0xFFFF00FF);
	this->UIWindow::DrawBorderLine(0, 0, m_w, m_h, m_borderLineColor);
	
	int fontHeight = m_fontSize;
	if( m_charfont != 0 )
		fontHeight = 12;

	int fontType = 0;
	switch( m_charfont )
	{
	case 1: fontType = 21; break;
	case 2: fontType = 20; break;
	case 3: fontType = 22; break;
	case 4: fontType = 23; break;
	case 5: fontType = 24; break;
	case 6: fontType = 25; break;
	case 7: fontType = 26; break;
	case 8: fontType = 27; break;
	case 9: fontType = 28; break;
	}

	int cy = 4;
	for( size_t i = 0; i < m_strings.size(); ++i )
	{
		COLORREF color = ( i < m_stringsColors.size() && m_stringsColors[i] != 0 ) ? m_stringsColors[i] : m_fontColor;
		this->UIWindow::TextOutWithShadow(6, cy, m_strings[i].c_str(), 0, color, m_bgColor, fontType, fontHeight);
		cy += this->UIWindow::GetTextHeight(m_strings[i].c_str(), 0, 0, m_fontSize, false) + 4;
	}
}


void UITransBalloonText::SetTransBoxColor(COLORREF transboxColor)
{
	m_transBoxInfo.color = transboxColor;
}


/// @custom
void UITransBalloonText::SetBorderLineColor(COLORREF borderLineColor)
{
	m_borderLineColor = borderLineColor;
}


mystd::string UITransBalloonText::GetText(size_t index)
{
	if( m_strings.size() < 1 || index > m_strings.size() ) //FIXME: incomplete range check
		return ""; // invalid input
	
	return m_strings[index];
}


void UITransBalloonText::ChangeText(const char* text, size_t index)
{
	if( index == -1 )
		index = m_strings.size() - 1;

	m_strings[index] = text;
	this->Invalidate();
}


void UITransBalloonText::SetText(const char* text, COLORREF color)
{
	m_strings.clear();
	m_stringsColors.clear();

	this->UIBalloonText::AddText(text);
	m_stringsColors.push_back(color);
}


void UITransBalloonText::AddText(const char* text, COLORREF color)
{
	this->UIBalloonText::AddText(text);
	m_stringsColors.push_back(color);
}


////////////////////////////////////////
