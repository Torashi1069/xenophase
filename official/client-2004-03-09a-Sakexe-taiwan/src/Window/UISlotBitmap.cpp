#include "Window/UISlotBitmap.h"
#include "Window/UISys.h" // UM_COMMAND


UISlotBitmap::UISlotBitmap() // line 332-333 (UIControl.cpp)
{
}


UISlotBitmap::~UISlotBitmap() // line 336-337 (UIControl.cpp)
{
}


void UISlotBitmap::OnLBtnDown(int x, int y) // line 340-343 (UIControl.cpp)
{
	if( m_parent != NULL )
		m_parent->SendMsg(this, UM_COMMAND, m_id, 0, 0);
}


void UISlotBitmap::OnLBtnDblClk(int x, int y) // line 346-349 (UIControl.cpp)
{
	if( m_parent != NULL )
		m_parent->SendMsg(this, UM_COMMAND, m_id, 0, 0);
}


int UISlotBitmap::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 352-362 (UIControl.cpp)
{
	switch( message )
	{
	case UM_SETSTATE:
		m_state = val1;
	break;
	default:
		return this->UIWindow::SendMsg(sender, message, val1, val2, val3);
	break;
	}

	return 0;
}
