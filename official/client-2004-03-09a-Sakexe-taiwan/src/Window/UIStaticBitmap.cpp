#include "Base/ResMgr.h"
#include "Resource/Bitmap.h"
#include "Window/UIStaticBitmap.h"
#include "MsgStrings.h" // UIBmp()


UIStaticBitmap::UIStaticBitmap() // line 192-193 (UIControl.cpp)
{
}


UIStaticBitmap::~UIStaticBitmap() // line 196-197 (UIControl.cpp)
{
}


void UIStaticBitmap::SetBitmap(const char* bitmapName) // line 200-205 (UIControl.cpp)
{
	m_bitmapName = bitmapName;
	CBitmapRes* bmp = (CBitmapRes*)g_resMgr().CResMgr::Get(m_bitmapName.c_str());
	m_w = bmp->m_width;
	m_h = bmp->m_height;
}


void UIStaticBitmap::OnDraw() // line 208-222 (UIControl.cpp)
{
	if( m_bitmapName.size() == 0 )
		return;

	if( m_state == 0 )
	{
		CBitmapRes* bmp = (CBitmapRes*)g_resMgr().CResMgr::Get(UIBmp(m_bitmapName.c_str()));
		this->UIWindow::DrawBitmap(0, 0, bmp, false);
	}
	else
	if( m_state == 1 )
	{
		this->UIWindow::ClearDC(0xFFFF00FF);
	}
}


void UIStaticBitmap::OnLBtnDown(int x, int y) // line 225-226 (UIControl.cpp)
{
}


void UIStaticBitmap::OnMouseMove(int x, int y) // line 229-230 (UIControl.cpp)
{
}


void UIStaticBitmap::OnLBtnUp(int x, int y) // line 233-234 (UIControl.cpp)
{
}
