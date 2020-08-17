#include "Window/UIWaitWnd.h"


hook_func<void (UIWaitWnd::*)(const char* waitMsg, int fontHeight, int fontType)> UIWaitWnd::_SetMsg("UIWaitWnd::SetMsg");
void UIWaitWnd::SetMsg(const char* waitMsg, int fontHeight, int fontType)
{
	return (this->*_SetMsg)(waitMsg, fontHeight, fontType);
}
