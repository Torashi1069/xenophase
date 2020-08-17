#pragma once
#define DIRECTINPUT_VERSION 0x700
#include <dx9sdk/Include/dinput.h>


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

	public: CMouse::CMouse(void);
	public: void CMouse::Init(void);
	public: void CMouse::Exit(void);
	public: void CMouse::ReadState(void);
	public: void CMouse::ResetState(void);
	public: void CMouse::ResetButtonState(void);
	public: int CMouse::GetWheel(void);
	public: int CMouse::GetXPos(void);
	public: int CMouse::GetYPos(void);
	public: void CMouse::SetXPos(int xPos);
	public: void CMouse::SetYPos(int yPos);
	//public: int GetXDelta();
	//public: int GetYDelta();
	public: enum EBtnState CMouse::GetLBtn(void);
	public: enum EBtnState CMouse::GetRBtn(void);
	//public: void SetLBtn(enum EBtnState);
	//public: void SetRBtn(enum EBtnState);
	//public: void SetButtonPressed(int);

private:
	static hook_method<void (CMouse::*)(void)> CMouse::_Init;
	static hook_method<void (CMouse::*)(void)> CMouse::_Exit;
	static hook_method<void (CMouse::*)(void)> CMouse::_ReadState;
	static hook_method<void (CMouse::*)(void)> CMouse::_ResetState;
	static hook_method<void (CMouse::*)(void)> CMouse::_ResetButtonState;
	static hook_method<int (CMouse::*)(void)> CMouse::_GetWheel;
	static hook_method<int (CMouse::*)(void)> CMouse::_GetXPos;
	static hook_method<int (CMouse::*)(void)> CMouse::_GetYPos;
	static hook_method<void (CMouse::*)(int xPos)> CMouse::_SetXPos;
	static hook_method<void (CMouse::*)(int yPos)> CMouse::_SetYPos;
	static hook_method<enum EBtnState (CMouse::*)(void)> CMouse::_GetLBtn;
	static hook_method<enum EBtnState (CMouse::*)(void)> CMouse::_GetRBtn;
};


long __cdecl SetAcquire(int acquire);
