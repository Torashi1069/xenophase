#include "NetLib/Acceptor.h"
#include "struct.hpp"


hook_func<unsigned int (__stdcall *)(void* p)> _AcceptThread(SERVER, "AcceptThread");
unsigned int __stdcall AcceptThread(void* p) // line 5
{
	return (_AcceptThread)(p);

	_ACCEPT_PARM& ap = *(_ACCEPT_PARM*)p;

	SOCKET s = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( s == INVALID_SOCKET )
	{
		MessageBoxA(NULL, "WSASocket() failed: listener", "error", MB_OK);
		ExitProcess(EXIT_FAILURE);
	}

	sockaddr_in hostAddr = {};
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = ap.ip;
	hostAddr.sin_port = htons(ap.port);

	if( bind(s, (sockaddr*)&hostAddr, sizeof(hostAddr)) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "bind() failed: listener", "error", MB_OK);
		ExitProcess(EXIT_FAILURE);
	}

	if( listen(s, ap.backlog) == SOCKET_ERROR )
	{
		MessageBoxA(NULL, "listen() failed: listener", "error", MB_OK);
		ExitProcess(EXIT_FAILURE);
	}

	while( 1 )
	{
		sockaddr_in remoteAddr;
		SOCKET cs;

		do
		{
			int sockLen = sizeof(remoteAddr);
			cs = WSAAccept(s, (sockaddr*)&remoteAddr, &sockLen, NULL, NULL);
		}
		while( cs == INVALID_SOCKET );

		if( ap.ipLog )
		{
			char buf[32];
			sprintf(buf, "%s\n", inet_ntoa(remoteAddr.sin_addr));
			OutputDebugStringA(buf);
		}

		if( !ap.handler->OnConnect(cs, remoteAddr.sin_addr.s_addr) )
			closesocket(cs);
	}
}


hook_func<unsigned long (__cdecl *)(int type)> _GetLocalIPAddr(SERVER, "GetLocalIPAddr");
unsigned long __cdecl GetLocalIPAddr(int type) // line 81
{
	return (_GetLocalIPAddr)(type);

	char szName[255];
	if( gethostname(szName, sizeof(szName)) == -1 )
	{
		char buf[256];
		sprintf(buf, "gethostname() fail! : %d", WSAGetLastError());
		OutputDebugStringA(buf);
		return 0;
	}

	hostent* h = gethostbyname(szName);
	if( h == NULL )
	{
		char buf[256];
		sprintf(buf, "gethostbyname() fail! : %d", WSAGetLastError());
		OutputDebugStringA(buf);
		return 0;
	}

	DWORD public_ip = 0;
	DWORD private_ip = 0;

	for( int i = 0; h->h_addr_list[i] != NULL; ++i )
	{
		DWORD addr = *(DWORD*)h->h_addr_list[i];
		if( IsPrivateIPAddr(addr) )
		{
			if( private_ip == 0 )
				private_ip = addr;
		}
		else
		{
			if( addr != 0 && public_ip == 0 )
				public_ip = addr;
		}
	}

	if( type == PUBLIC_OR_PRIVATE_IP_ADDRESS )
	{
		if( public_ip != 0 )
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS)  public ip addr!!\n");
			return public_ip;
		}
		else
		if( private_ip != 0 )
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS)  private ip addr!!\n");
			return private_ip;
		}
		else
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS)  there is not public or private ip addr\n");
			return 0;
		}
	}
	else
	if( type == PUBLIC_IP_ADDRESS )
	{
		if( public_ip != 0 )
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_IP_ADDRESS)  public ip addr!!\n");
			return public_ip;
		}
		else
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_IP_ADDRESS)  there is not public ip addr\n");
			return 0;
		}
	}
	else
	if( type == PRIVATE_IP_ADDRESS )
	{
		if( private_ip != 0 )
		{
			OutputDebugStringA("GetLocalIPAddr(PRIVATE_IP_ADDRESS)  private ip addr!!\n");
			return private_ip;
		}
		else
		{
			OutputDebugStringA("GetLocalIPAddr(PRIVATE_IP_ADDRESS)  there is not private ip addr\n");
			return 0;
		}
	}
	else
	{
		OutputDebugStringA("GetLocalIPAddr type invalid\n");
		return 0;
	}
}


hook_func<bool (__cdecl *)(unsigned long dwIP)> _IsPrivateIPAddr(SERVER, "IsPrivateIPAddr");
bool __cdecl IsPrivateIPAddr(unsigned long dwIP) // line 167
{
	return (_IsPrivateIPAddr)(dwIP);

	//TODO
}
