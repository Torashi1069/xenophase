#include "Window/UITransBalloonText.h"


UITransBalloonText::UITransBalloonText() // line 870-871 (UIControl.cpp)
{
}


UITransBalloonText::~UITransBalloonText() // line 874-875 (UIControl.cpp)
{
}


void UITransBalloonText::OnDraw() // line 904-913 (UIControl.cpp)
{
	this->UIWindow::ClearDC(0xFFFF00FFu);

	int y = 4;
	for( size_t i = 0; i < m_strings.size(); ++i )
	{
		this->UIWindow::TextOutWithShadow(6, y, m_strings[i].c_str(), 0, m_fontColor, m_bgColor, 0, m_fontSize);
		y += this->UIWindow::GetTextHeight(m_strings[i].c_str(), 0, 0, m_fontSize, false) + 4;
	}
}


bool UITransBalloonText::GetTransBoxInfo(BOXINFO* boxInfo) // line 920-924 (UIControl.cpp)
{
	memcpy(boxInfo, &m_transBoxInfo, sizeof(BOXINFO));
	return true;
}


void UITransBalloonText::OnCreate(int cx, int cy) // line 892-901 (UIControl.cpp)
{
	m_transBoxInfo.x = m_x;
	m_transBoxInfo.y = m_y;
	m_transBoxInfo.cx = m_w;
	m_transBoxInfo.drawEdge = 0;
	m_transBoxInfo.cy = m_h;
	m_transBoxInfo.color = 0x66000000;
	m_transBoxInfo.color2 = 0;
}


void UITransBalloonText::Move(int x, int y) // line 878-882 (UIControl.cpp)
{
	this->UIWindow::Move(x, y);
	m_transBoxInfo.x = m_x;
	m_transBoxInfo.y = m_y;
}


void UITransBalloonText::Resize(int cx, int cy) // line 885-889 (UIControl.cpp)
{
	this->UIWindow::Resize(cx, cy);
	m_transBoxInfo.cx = m_w;
	m_transBoxInfo.cy = m_h;
}


void UITransBalloonText::SetTransBoxColor(COLORREF transboxColor) // line 915-917 (UIControl.cpp)
{
	m_transBoxInfo.color = transboxColor;
}
