#include "Control.h"


CMouse::CMouse(void) // inlined ($E15_0)
{
	m_pMouse = NULL;
	m_bSwapButton = 0;
}


hook_method<void (CMouse::*)(void)> CMouse::_Init(SAKEXE, "CMouse::Init");
void CMouse::Init(void) // line 16
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CMouse::*)(void)> CMouse::_Exit(SAKEXE, "CMouse::Exit");
void CMouse::Exit(void) // line 52
{
	return (this->*_Exit)();

	//TODO
}


hook_method<void (CMouse::*)(void)> CMouse::_ReadState(SAKEXE, "CMouse::ReadState");
void CMouse::ReadState(void) // line 67
{
	return (this->*_ReadState)();

	//TODO
}


hook_method<void (CMouse::*)(void)> CMouse::_ResetState(SAKEXE, "CMouse::ResetState");
void CMouse::ResetState(void) // line 184
{
	return (this->*_ResetState)();

	//TODO
}


hook_method<void (CMouse::*)(void)> CMouse::_ResetButtonState(SAKEXE, "CMouse::ResetButtonState");
void CMouse::ResetButtonState(void) // line 197
{
	return (this->*_ResetButtonState)();

	//TODO
}


//hook_method<int (CMouse::*)(void)> CMouse::_GetWheel(SAKEXE, "CMouse::GetWheel");
int CMouse::GetWheel(void) // line ???-???
{
//	return (this->*_GetWheel)();

	return m_wheel;
}


//hook_method<int (CMouse::*)(void)> CMouse::_GetXPos(SAKEXE, "CMouse::GetXPos");
int CMouse::GetXPos(void)
{
//	return (this->*_GetXPos)();

	return m_xPos;
}


//hook_method<int (CMouse::*)(void)> CMouse::_GetYPos(SAKEXE, "CMouse::GetYPos");
int CMouse::GetYPos(void)
{
//	return (this->*_GetYPos)();

	return m_yPos;
}


//hook_method<void (CMouse::*)(int xPos)> CMouse::_SetXPos(SAKEXE, "CMouse::SetXPos");
void CMouse::SetXPos(int xPos)
{
//	return (this->*_SetXPos)(xPos);

	m_xPos = xPos;
}


//hook_method<void (CMouse::*)(int yPos)> CMouse::_SetYPos(SAKEXE, "CMouse::SetYPos");
void CMouse::SetYPos(int yPos)
{
//	return (this->*_SetYPos)(yPos);

	m_yPos = yPos;
}


//hook_method<enum EBtnState (CMouse::*)(void)> CMouse::_GetLBtn(SAKEXE, "CMouse::GetLBtn");
enum EBtnState CMouse::GetLBtn(void)
{
//	return (this->*_GetLBtn)();

	return ( !m_bSwapButton ) ? m_btnState[0] : m_btnState[1];
}


//hook_method<enum EBtnState (CMouse::*)(void)> CMouse::_GetRBtn(SAKEXE, "CMouse::GetRBtn");
enum EBtnState CMouse::GetRBtn(void)
{
//	return (this->*_GetRBtn)();

	return ( !m_bSwapButton ) ? m_btnState[1] : m_btnState[0];
}


hook_func<long (__cdecl *)(int acquire)> _SetAcquire(SAKEXE, "SetAcquire");
long __cdecl SetAcquire(int acquire) // line 205
{
	return (_SetAcquire)(acquire);

	//TODO
}
