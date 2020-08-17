#include "NetLib/Acceptor.h" // GetLocalIPAddr()


/// Causes all outgoing connections to have their local side bound to a specific ip address.
hook_func<int (PASCAL *)(SOCKET s, const struct sockaddr* name, int namelen)> _connect("ws2_32.dll", "connect");
HOOKED int PASCAL my_connect(SOCKET s, const struct sockaddr* name, int namelen)
{
	struct sockaddr_in outgoing_addr;
	outgoing_addr.sin_family = AF_INET;
	outgoing_addr.sin_addr.s_addr = GetLocalIPAddr(PRIVATE_IP_ADDRESS);
	outgoing_addr.sin_port = htons(0);

	if( bind(s, (sockaddr *)&outgoing_addr, sizeof(outgoing_addr)) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "Cannot bind to private ip for outgoing connection", "ERROR", MB_OK);
		exit(EXIT_FAILURE);
	}

	return _connect(s, name, namelen);
}


/// Appends the zone's private IP address to the zone's mutex name.
/// This allows multiple zones to run on the same system.
hook_func<HANDLE (WINAPI *)(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)> _CreateMutexA("kernel32.dll", "CreateMutexA");
HOOKED HANDLE WINAPI my_CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)
{
	if( strcmp(lpName, "Global\\Ragnarok Zone Server") == 0 )
	{
		in_addr PrivateIP;
		PrivateIP.s_addr = GetLocalIPAddr(PRIVATE_IP_ADDRESS);
		char newname[256];
		_snprintf(newname, sizeof(newname), "%s [IP: %s]", lpName, inet_ntoa(PrivateIP));
		lpName = newname;
	}

	return _CreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
}


/// Rewrites the zone's window title to provide more information about the zone instance.
/// Includes this dll's build date and the zone's private IP address.
hook_func<HWND (WINAPI *)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)> _CreateWindowExA("user32.dll", "CreateWindowExA");
HOOKED HWND WINAPI my_CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	if( strstr(lpWindowName, "(VC9)RO") )
	{
		in_addr PrivateIP;
		PrivateIP.s_addr = GetLocalIPAddr(PRIVATE_IP_ADDRESS);
		char newname[256];
		_snprintf(newname, sizeof(newname), "(VC9)RO - GROBAL_VERSION ( %s %s ) [IP: %s]", __DATE__, __TIME__, inet_ntoa(PrivateIP));
		lpWindowName = newname;
	}

	return _CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}


/// Sets all sockets to nodelay mode.
hook_func<SOCKET (WSAAPI *)(SOCKET s, struct sockaddr* addr, LPINT addrlen, LPCONDITIONPROC lpfnCondition, DWORD_PTR dwCallbackData)> _WSAAccept("ws2_32.dll", "WSAAccept");
HOOKED SOCKET WSAAPI my_WSAAccept(SOCKET s, struct sockaddr* addr, LPINT addrlen, LPCONDITIONPROC lpfnCondition, DWORD_PTR dwCallbackData)
{
	SOCKET result;

	result = _WSAAccept(s, addr, addrlen, lpfnCondition, dwCallbackData);

	int yes = 1;
	setsockopt(result, IPPROTO_TCP, TCP_NODELAY, (char *)&yes, sizeof(yes));

	return result;
}
