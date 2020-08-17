#include "Window/UINewChatWnd.h"
#include "Window/UIWindowMgr.h"
#include "Enum.h"
#include "Globals.h"


UINewChatWnd::UINewChatWnd()
{
	m_commonChat_TODO = NULL;
	m_whisperChat_TODO = NULL;
	m_lastFocusChat_TODO = NULL;
	m_resizer_TODO = NULL;
	this->field_C0 = 10;
	g_windowMgr.m_chatWndStickOn = true;
	m_state = 0;
	m_comboMode = 0;
	m_tab = 0;
	m_saveState = 0;
	m_titleHeight = 16;
	m_titleWidth = 71;
	m_chatEditHeight = 24;

	switch( g_serviceType )
	{
	case ServiceGermany:
		m_titleWidth = 71;
	break;
	case ServiceFrance:
		m_titleWidth = 90;
	break;
	case ServiceAmerica:
	case ServicePhilippine:
	case ServiceIndia:
		m_titleWidth = 110;
	break;
	default:
	break;
	};
}


hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_dtor("UINewChatWnd::~UINewChatWnd");
UINewChatWnd::~UINewChatWnd()
{
	(this->*_dtor)(); return;

	//TODO
}


hook_func<void (UINewChatWnd::*)(int cx, int cy)> UINewChatWnd::_OnCreate("UINewChatWnd::OnCreate");
void UINewChatWnd::OnCreate(int cx, int cy)
{
	return (this->*_OnCreate)(cx, cy);

	//TODO
}


hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_OnDraw("UINewChatWnd::OnDraw");
void UINewChatWnd::OnDraw()
{
	return (this->*_OnDraw)();

	//TODO
}


hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_OnLBtnDown("UINewChatWnd::OnLBtnDown");
void UINewChatWnd::OnLBtnDown(int x, int y)
{
	return (this->*_OnLBtnDown)(x, y);

	//TODO
}


hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_OnMouseMove("UINewChatWnd::OnMouseMove");
void UINewChatWnd::OnMouseMove(int x, int y)
{
	return (this->*_OnMouseMove)(x, y);

	//TODO
}


hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_OnLBtnUp("UINewChatWnd::OnLBtnUp");
void UINewChatWnd::OnLBtnUp(int x, int y)
{
	return (this->*_OnLBtnUp)(x, y);

	//TODO
}


hook_func<int (UINewChatWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3, int val4)> UINewChatWnd::_SendMsg("UINewChatWnd::SendMsg");
int UINewChatWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4)
{
	return (this->*_SendMsg)(sender, message, val1, val2, val3, val4);

	//TODO
}


hook_func<bool (UINewChatWnd::*)(BOXINFO* boxInfo)> UINewChatWnd::_GetTransBoxInfo2("UINewChatWnd::GetTransBoxInfo2");
bool UINewChatWnd::GetTransBoxInfo2(BOXINFO* boxInfo)
{
	return (this->*_GetTransBoxInfo2)(boxInfo);

	//TODO
}


hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_DrawBoxScreen2("UINewChatWnd::DrawBoxScreen2");
void UINewChatWnd::DrawBoxScreen2()
{
	return (this->*_DrawBoxScreen2)();

	//TODO
}


hook_func<void (UINewChatWnd::*)(int x, int y)> UINewChatWnd::_Move("UINewChatWnd::Move");
void UINewChatWnd::Move(int x, int y)
{
	return (this->*_Move)(x, y);

	//TODO
}


hook_func<void (UINewChatWnd::*)(int cx, int cy)> UINewChatWnd::_Resize("UINewChatWnd::Resize");
void UINewChatWnd::Resize(int cx, int cy)
{
	return (this->*_Resize)(cx, cy);

	//TODO
}


hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_StoreInfo("UINewChatWnd::StoreInfo");
void UINewChatWnd::StoreInfo()
{
	return (this->*_StoreInfo)();

	//TODO
}


hook_func<void (UINewChatWnd::*)(BOOL visible)> UINewChatWnd::_SetShow("UINewChatWnd::SetShow");
void UINewChatWnd::SetShow(BOOL visible)
{
	return (this->*_SetShow)(visible);

	//TODO
}


hook_func<void (UINewChatWnd::*)(int state)> UINewChatWnd::_SetState("UINewChatWnd::SetState");
void UINewChatWnd::SetState(int state)
{
	return (this->*_SetState)(state);

	//TODO
}


hook_func<void (UINewChatWnd::*)()> UINewChatWnd::_WriteChatToFile("UINewChatWnd::WriteChatToFile");
void UINewChatWnd::WriteChatToFile()
{
	return (this->*_WriteChatToFile)();

	//TODO
}


void UINewChatWnd::StickOnOff(bool stickOn)
{
	g_windowMgr.m_chatWndStickOn = stickOn;

	if( stickOn )
	{
		m_tab = 0;
		if( m_saveState == 0 )
			m_saveState = 1;
		this->UINewChatWnd::SetState(m_saveState);
		this->Invalidate();
	}
	else
	{
		m_saveState = m_state;
		this->UINewChatWnd::SetState(0);
		this->Invalidate();
	}
}
