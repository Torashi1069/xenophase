#include "network/ConnectionMgr.h"
#include "patch/CrashHandler.h"
#include "Version.h"


void Hook()
{
	if( LOCALVER() == "Client 2010-06-22a RagexeRE Korea" )
	{
		extern void Debug(); Debug();
		extern void Apply_fix_uninitialized_cview_stall(); Apply_fix_uninitialized_cview_stall();
		extern void Apply_fix_uninitialized_cblurpc_crash(); Apply_fix_uninitialized_cblurpc_crash();
		extern void Apply_ui_flash_window_on_whisper(); Apply_ui_flash_window_on_whisper();
	}

	extern void Apply_ui_custom_window_title(); Apply_ui_custom_window_title();
	extern void Apply_misc_antibot(); Apply_misc_antibot();

	CrashHandler::Initialize();
	ConnectionMgr::Initialize();
}


void UnHook()
{
	ConnectionMgr::Finalize();
}


void SymDBInitCallback()
{
	SymDB::Add("CreateWindowExA", "user32.dll", "CreateWindowExA");
	SymDB::Add("LdrLoadDll", "ntdll.dll", "LdrLoadDll");
	SymDB::Add("SetUnhandledExceptionFilter", "kernel32.dll", "SetUnhandledExceptionFilter");
	SymDB::Add("socket", "ws2_32.dll", "socket");
	SymDB::Add("closesocket", "ws2_32.dll", "closesocket");
	SymDB::Add("connect", "ws2_32.dll", "connect");
	SymDB::Add("select", "ws2_32.dll", "select");
	SymDB::Add("send", "ws2_32.dll", "send");
	SymDB::Add("recv", "ws2_32.dll", "recv");

	if( LOCALVER() == "Client 2010-06-22a RagexeRE Korea" )
	{
	SymDB::Add("CView::CView", 0x530F30);
	SymDB::Add("CPc::CPc", 0x61A1E0);
	SymDB::Add("UIWhisperWnd::SendMsg", 0x4873F0);
	SymDB::Add("g_hMainWnd", 0x839F50);
	}
	else
	{// dummy symbols
	SymDB::Add("CView::CView", -1);
	SymDB::Add("CPc::CPc", -1);
	SymDB::Add("UIWhisperWnd::SendMsg", -1);
	SymDB::Add("g_hMainWnd", -1);
	}
}
