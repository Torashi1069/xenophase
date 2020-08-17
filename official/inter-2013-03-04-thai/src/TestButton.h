#pragma once


class CTestButton
{
private:
	/* this+ 0 */ HWND m_hWnd;
	/* this+ 4 */ HMENU const m_hMenu;
	/* this+ 8 */ int m_X;
	/* this+12 */ int m_Y;
	/* this+16 */ int m_Width;
	/* this+20 */ int m_Height;

public:
	void OnCreate(HWND in_hWndParent, HINSTANCE in_hInstance, const int in_X, const int in_Y, const int in_Width, const int in_Height, const char* in_strName);
	void EnableWindow(const bool in_bEnable);
	bool IsWindowEnabled();
	int GetX();
	int GetWidth();
	int GetY();

public:
	CTestButton(const HMENU in_hMenu);
	~CTestButton();
};
