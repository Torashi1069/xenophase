#include "TestButton.h"


CTestButton::CTestButton(const HMENU in_hMenu) // line 14
: m_hWnd(NULL), m_hMenu(in_hMenu), m_X(0), m_Y(0), m_Width(0), m_Height(0)
{
}


CTestButton::~CTestButton(void) // line ??
{
}


hook_method<void (CTestButton::*)(HWND in_hWndParent, HINSTANCE in_hInstance, const int in_X, const int in_Y, const int in_Width, const int in_Height, const char* in_strName)> CTestButton::_OnCreate(SERVER, "CTestButton::OnCreate");
void CTestButton::OnCreate(HWND in_hWndParent, HINSTANCE in_hInstance, const int in_X, const int in_Y, const int in_Width, const int in_Height, const char* in_strName) // line 36
{
	return (this->*_OnCreate)(in_hWndParent, in_hInstance, in_X, in_Y, in_Width, in_Height, in_strName);

	m_X = in_X;
	m_Y = in_Y;
	m_Width = in_Width;
	m_Height = in_Height;
	m_hWnd = CreateWindowExA(0, "button", in_strName, WS_CHILD|WS_VISIBLE|WS_EX_DLGMODALFRAME, in_X, in_Y, in_Width, in_Height, in_hWndParent, m_hMenu, in_hInstance, NULL);
}


//hook_method<int (CTestButton::*)(void)> CTestButton::_GetX(SERVER, "CTestButton::GetX");
int CTestButton::GetX(void) // line ??
{
//	return (this->*_GetX)();

	return m_X;
}


//hook_method<int (CTestButton::*)(void)> CTestButton::_GetWidth(SERVER, "CTestButton::GetWidth");
int CTestButton::GetWidth(void) // line ??
{
//	return (this->*_GetWidth)();

	return m_Width;
}


//hook_method<int (CTestButton::*)(void)> CTestButton::_GetY(SERVER, "CTestButton::GetY");
int CTestButton::GetY(void) // line ??
{
//	return (this->*_GetY)();

	return m_Y;
}

