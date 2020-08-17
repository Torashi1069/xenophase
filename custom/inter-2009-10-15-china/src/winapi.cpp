#include "NetLib/Acceptor.h" // GetLocalIPAddr()


/// Causes all outgoing connections to have their local side bound to a specific ip address.
hook_func<int (PASCAL *)(SOCKET s, const struct sockaddr* name, int namelen)> _connect("ws2_32.dll", "connect");
HOOKED int PASCAL my_connect(SOCKET s, const struct sockaddr* name, int namelen)
{
	struct sockaddr_in outgoing_addr;
	outgoing_addr.sin_family = AF_INET;
	outgoing_addr.sin_addr.s_addr = GetLocalIPAddr(0);
	outgoing_addr.sin_port = htons(0);

	if( bind(s, (sockaddr *)&outgoing_addr, sizeof(outgoing_addr)) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "Cannot bind to private ip for outgoing connection", "ERROR", MB_OK);
		exit(EXIT_FAILURE);
	}

	return _connect(s, name, namelen);
}


hook_func<HWND (WINAPI *)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)> _CreateWindowExA("user32.dll", "CreateWindowExA");
HOOKED HWND WINAPI my_CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	if( strstr(lpWindowName, "(vc9)INTER") )
	{
		char newname[256];
		_snprintf(newname, sizeof(newname), "(vc9)INTER(%s %s)", __DATE__, __TIME__);
		lpWindowName = newname;
	}

	return _CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}
