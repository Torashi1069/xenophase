#include "TestButton.h"


CTestButton::CTestButton(const HMENU in_hMenu)
: m_hWnd(NULL), m_hMenu(in_hMenu), m_X(0), m_Y(0), m_Width(0), m_Height(0)
{
}


CTestButton::~CTestButton()
{
}


void CTestButton::OnCreate(HWND in_hWndParent, HINSTANCE in_hInstance, const int in_X, const int in_Y, const int in_Width, const int in_Height, const char* in_strName)
{
	m_X = in_X;
	m_Y = in_Y;
	m_Width = in_Width;
	m_Height = in_Height;
	m_hWnd = CreateWindowExA(0, "button", in_strName, WS_CHILD | WS_VISIBLE | WS_EX_DLGMODALFRAME, in_X, in_Y, in_Width, in_Height, in_hWndParent, m_hMenu, in_hInstance, NULL);
}


void CTestButton::EnableWindow(const bool in_bEnable)
{
	::EnableWindow(m_hWnd, in_bEnable);
}


bool CTestButton::IsWindowEnabled()
{
	return ( ::IsWindowEnabled(m_hWnd) == TRUE );
}


int CTestButton::GetX()
{
	return m_X;
}


int CTestButton::GetWidth()
{
	return m_Width;
}


int CTestButton::GetY()
{
	return m_Y;
}
