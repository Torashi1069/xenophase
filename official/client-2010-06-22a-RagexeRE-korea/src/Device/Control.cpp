#include "3dLib/Device.h"
#include "Device/Control.h"
#include "Globals.h"
#define DIRECTINPUT_VERSION 0x800
#include <dx9sdk/Include/dinput.h>


hook_func<void (CMouse::*)(void)> CMouse::_Init("CMouse::Init");
void CMouse::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_func<void (CMouse::*)(void)> CMouse::_Exit("CMouse::Exit");
void CMouse::Exit(void)
{
	return (this->*_Exit)();

	//TODO
}


hook_func<void (CMouse::*)(void)> CMouse::_ReadState("CMouse::ReadState");
void CMouse::ReadState(void)
{
	return (this->*_ReadState)();

	int curBtnState[2];
	curBtnState[0] = m_oldBtnState[0];
	curBtnState[1] = m_oldBtnState[1];

	m_xDelta = 0;
	m_yDelta = 0;
	m_wheel = 0;

	DIMOUSESTATE mouseState;
	HRESULT hr = m_pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if( !SUCCEEDED(hr) )
	{
		if( g_isAppActive )
		{
			m_pMouse->Acquire();
			hr = m_pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
		}
	}

	if( SUCCEEDED(hr) )
	{
		m_xDelta = mouseState.lX;
		m_yDelta = mouseState.lY;
		m_xPos += mouseState.lX;
		m_yPos += mouseState.lY;
		m_wheel = mouseState.lZ;

		curBtnState[0] = ( mouseState.rgbButtons[0] != 0 );
		curBtnState[1] = ( mouseState.rgbButtons[1] != 0 );
	}

	if( m_xPos < 0 )
		m_xPos = 0;
	if( m_yPos < 0 )
		m_yPos = 0;
	if( m_xPos >= g_3dDevice.C3dDevice::GetWidth() )
		m_xPos =  g_3dDevice.C3dDevice::GetWidth() - 1;
	if( m_yPos >= g_3dDevice.C3dDevice::GetHeight() )
		m_yPos =  g_3dDevice.C3dDevice::GetHeight() - 1;

	DWORD curTime = timeGetTime();
	for( int i = 0; i < 2; ++i )
	{
		if( m_xDelta != 0 || m_yDelta != 0 )
			m_dblclkCnt[i] = curTime - m_dblclkTime;

		if( !curBtnState[i] )
		{
			if( !m_oldBtnState[i] )
			{
				m_btnState[i] = BTN_NONE;
			}
			else
			{
				m_btnState[i] = BTN_UP;
			}
		}
		else
		{
			if( m_oldBtnState[i] )
			{
				m_btnState[i] = BTN_PRESSED;
			}
			else
			if( curTime >= DWORD(m_dblclkCnt[i] + m_dblclkTime) )
			{
				m_btnState[i] = BTN_DOWN;
				m_dblclkCnt[i] = curTime;
			}
			else
			{
				m_btnState[i] = BTN_DBLCLK;
				m_dblclkCnt[i] = curTime - m_dblclkTime;
			}
		}
	}

	m_oldBtnState[0] = curBtnState[0];
	m_oldBtnState[1] = curBtnState[1];
}


//hook_func<int (CMouse::*)(void)> CMouse::_GetWheel("CMouse::GetWheel");
int CMouse::GetWheel(void)
{
//	return (this->*_GetWheel)();

	return m_wheel;
}


//hook_func<int (CMouse::*)(void)> CMouse::_GetXPos("CMouse::GetXPos");
int CMouse::GetXPos(void)
{
//	return (this->*_GetXPos)();

	return m_xPos;
}


//hook_func<int (CMouse::*)(void)> CMouse::_GetYPos("CMouse::GetYPos");
int CMouse::GetYPos(void)
{
//	return (this->*_GetYPos)();

	return m_yPos;
}


//hook_func<EBtnState (CMouse::*)(void)> CMouse::_GetLBtn("CMouse::GetLBtn");
EBtnState CMouse::GetLBtn(void)
{
//	return (this->*_GetLBtn)();

	return ( !m_bSwapButton ) ? m_btnState[0] : m_btnState[1];
}


//hook_func<EBtnState (CMouse::*)(void)> CMouse::_GetRBtn("CMouse::GetRBtn");
EBtnState CMouse::GetRBtn(void)
{
//	return (this->*_GetRBtn)();

	return ( !m_bSwapButton ) ? m_btnState[1] : m_btnState[0];
}


CMouse& g_mouse = VTOR<CMouse>(SymDB::Find("g_mouse"));
