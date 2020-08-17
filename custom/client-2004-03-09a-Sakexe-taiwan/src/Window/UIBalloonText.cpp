#include "Window/UIBalloonText.h"
#include "Window/UISys.h" // CutString()


UIBalloonText::UIBalloonText() // line 797-803 (UIControl.cpp)
{
	m_isBold = false;
	m_stateCnt = 0;
	m_bgColor = 0;
	m_fontSize = 12;
	m_fontColor = 0xFFFFFF;
}


UIBalloonText::~UIBalloonText() // line 806-807 (UIControl.cpp)
{
}


void UIBalloonText::OnProcess() // line 810-812 (UIControl.cpp)
{
	++m_stateCnt;
}


void UIBalloonText::OnDraw() // line 815-823 (UIControl.cpp)
{
	this->UIWindow::ClearDC(0xFFFFFF);

	int y = 4;
	for( size_t i = 0; i < m_strings.size(); ++i )
	{
		const char* text = m_strings[i].c_str();
		this->UIWindow::TextOutA(6, y, text, 0, 0, m_fontSize, m_fontColor);
		y += 4 + this->UIWindow::GetTextHeight(text, 0, 0, m_fontSize, 0);
	}
}


bool UIBalloonText::ShouldDoHitTest() // line 380 (Window/UISys.h)
{
	return false;
}


void UIBalloonText::SetText(const char* msg, const int maxNumCharLine) // line 826-834 (UIControl.cpp)
{
	if( strlen(msg) == 0 )
		return;

	m_strings.clear();
	CutString(msg, m_strings, maxNumCharLine);
	this->UIBalloonText::AdjustSizeByText();
}


void UIBalloonText::AddText(const char* msg) // line 837-841 (UIControl.cpp)
{
	m_strings.push_back(msg);
	this->UIBalloonText::AdjustSizeByText();
}


void UIBalloonText::SetFntColor(COLORREF fontColor, COLORREF bgColor) // line ???-???
{
	m_fontColor = fontColor;
	m_bgColor = bgColor;
}


void UIBalloonText::SetFntSize(int fontSize) // line 844-848 (UIControl.cpp)
{
	m_fontSize = fontSize;
	this->UIBalloonText::AdjustSizeByText();
}


void UIBalloonText::SetBackTrans(bool isBack) // line ???-???
{
	m_isBack = isBack;
}


void UIBalloonText::AdjustSizeByText() // line 851-864
{
	int width = 0;
	int height = 4;

	for( size_t i = 0; i < m_strings.size(); ++i )
	{
		if( width <= this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 0, m_fontSize, false) )
			width = this->UIWindow::GetTextWidth(m_strings[i].c_str(), 0, 0, m_fontSize, false);

		height += 4 + this->UIWindow::GetTextHeight(m_strings[i].c_str(), 0, 0, m_fontSize, false);
	}

	this->Resize(12 + width, height);
	this->Invalidate();
}
