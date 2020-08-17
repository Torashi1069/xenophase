#pragma once
#include "Enum.h"
struct IDirectInputA;
struct IDirectInputDeviceA;


enum EBtnState
{
	BTN_NONE    = 0,
	BTN_DOWN    = 1,
	BTN_PRESSED = 2,
	BTN_UP      = 3,
	BTN_DBLCLK  = 4,
};


class CMouse
{
	/* this+ 0 */ private: IDirectInputA* m_lpdi;
	/* this+ 4 */ private: IDirectInputDeviceA* m_pMouse;
	/* this+ 8 */ private: HANDLE m_hevtMouse;
	/* this+12 */ private: int m_xDelta;
	/* this+16 */ private: int m_yDelta;
	/* this+20 */ private: int m_xPos;
	/* this+24 */ private: int m_yPos;
	/* this+28 */ private: int m_wheel;
	/* this+32 */ private: int m_oldBtnState[2];
	/* this+40 */ private: enum EBtnState m_btnState[2];
	/* this+48 */ private: int m_dblclkCnt[2];
	/* this+56 */ private: int m_dblclkTime;
	/* this+60 */ private: int m_bSwapButton;

	public: void CMouse::Init(void);
	public: void CMouse::Exit(void);
	public: void CMouse::ReadState(void);
	public: int CMouse::GetWheel(void);
	public: int CMouse::GetXPos(void);
	public: int CMouse::GetYPos(void);
	public: EBtnState CMouse::GetLBtn(void);
	public: EBtnState CMouse::GetRBtn(void);

public:
	static hook_func<void (CMouse::*)(void)> CMouse::_Init;
	static hook_func<void (CMouse::*)(void)> CMouse::_Exit;
	static hook_func<void (CMouse::*)(void)> CMouse::_ReadState;
	static hook_func<int (CMouse::*)(void)> CMouse::_GetWheel;
	static hook_func<int (CMouse::*)(void)> CMouse::_GetXPos;
	static hook_func<int (CMouse::*)(void)> CMouse::_GetYPos;
	static hook_func<EBtnState (CMouse::*)(void)> CMouse::_GetLBtn;
	static hook_func<EBtnState (CMouse::*)(void)> CMouse::_GetRBtn;
};


extern CMouse& g_mouse;
