#pragma once


class CTestButton
{
	/* this+ 0 */ private: HWND m_hWnd;
	/* this+ 4 */ private: const HMENU m_hMenu;
	/* this+ 8 */ private: int m_X;
	/* this+12 */ private: int m_Y;
	/* this+16 */ private: int m_Width;
	/* this+20 */ private: int m_Height;

	public: void CTestButton::OnCreate(HWND in_hWndParent, HINSTANCE in_hInstance, const int in_X, const int in_Y, const int in_Width, const int in_Height, const char* in_strName);
	//public: void EnableWindow(const bool);
	//public: bool IsWindowEnabled();
	public: int CTestButton::GetX(void);
	public: int CTestButton::GetWidth(void);
	public: int CTestButton::GetY(void);
	public: CTestButton::CTestButton(const HMENU in_hMenu);
	public: CTestButton::~CTestButton(void);

private:
	static hook_method<void (CTestButton::*)(HWND in_hWndParent, HINSTANCE in_hInstance, const int in_X, const int in_Y, const int in_Width, const int in_Height, const char* in_strName)> CTestButton::_OnCreate;
	static hook_method<int (CTestButton::*)(void)> CTestButton::_GetX;
	static hook_method<int (CTestButton::*)(void)> CTestButton::_GetWidth;
	static hook_method<int (CTestButton::*)(void)> CTestButton::_GetY;
};
