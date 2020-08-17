#include <windows.h>


namespace patch_ui_flash_window_on_whisper_2010
{
////////////////////////////////////////


enum UIMESSAGE
{
	UM_ADDCHAT = 37,
};


class UIWindow;


class UIWhisperWnd
{
public:
	static hook_func<int (UIWhisperWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3, int val4)> UIWhisperWnd::_SendMsg;
	int UIWhisperWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4);
};


////////////////////////////////////////


hook_val<HWND> g_hMainWnd("g_hMainWnd");


hook_func<int (UIWhisperWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3, int val4)> UIWhisperWnd::_SendMsg("UIWhisperWnd::SendMsg");
int UIWhisperWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3, int val4)
{
	if( message == UM_ADDCHAT )
	{
		if( GetActiveWindow() != g_hMainWnd )
			FlashWindow(g_hMainWnd, TRUE);
	}

	return (this->*_SendMsg)(sender, message, val1, val2, val3, val4);
}


////////////////////////////////////////
};


using namespace patch_ui_flash_window_on_whisper_2010;
void Apply_ui_flash_window_on_whisper()
{
	HookDB::DB().Hook("UIWhisperWnd::SendMsg", FTOV(&UIWhisperWnd::_SendMsg), FTOV(&UIWhisperWnd::SendMsg));
}
