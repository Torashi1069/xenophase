#include "Globals.h"
#include "3dLib/Device.h" // GDIFlip()


CFileMgr& g_fileMgr = VTOR<CFileMgr>(SymDB::Find("g_fileMgr"));
CPacketLengthExMgr& g_packetLenMapEx = VTOR<CPacketLengthExMgr>(SymDB::Find("g_packetLenMapEx"));

HWND& g_hMainWnd = VTOR<HWND>(SymDB::Find("g_hMainWnd")); // = ?
char(& g_baseDir)[128] = VTOR<char[128]>(SymDB::Find("g_baseDir")); // = "data\\"
char(& g_baseDir3)[128] = VTOR<char[128]>(SymDB::Find("g_baseDir3")); // = ?
bool& g_readFolderFirst = VTOR<bool>(SymDB::Find("g_readFolderFirst")); // = ?


void Trace(const char* str, ...)
{
}


void ErrorMsg(const char* msg)
{
	GDIFlip();
	MessageBoxA(g_hMainWnd, msg, "Error", MB_OK);
}


void ErrorMsg(int num)
{
	char buf[80];
	wsprintfA(buf, "%d\n", num); //FIXME: deprecated API

	GDIFlip();
	MessageBoxA(g_hMainWnd, buf, "Error", MB_OK);
}
