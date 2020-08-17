#include <windows.h>


namespace patch_ui_custom_window_title
{


hook_func<HWND (WINAPI *)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)> _CreateWindowExA("CreateWindowExA");
HWND WINAPI my_CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	if( strcmp(lpWindowName, "Ragnarok") == 0 )
		lpWindowName = "Ragnarok Frontier";

	return (_CreateWindowExA)(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}


};


using namespace patch_ui_custom_window_title;
void Apply_ui_custom_window_title()
{
	HookDB::DB().Hook("CreateWindowExA", _CreateWindowExA, &my_CreateWindowExA);
}
