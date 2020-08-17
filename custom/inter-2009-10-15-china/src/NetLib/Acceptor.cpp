#include "Acceptor.h"
#include "globals.hpp" // g_infFile


hook_func<DWORD (__cdecl *)(int type)> _GetLocalIPAddr(SERVER, "GetLocalIPAddr");
DWORD __cdecl GetLocalIPAddr(int type) // line 81
{
	char szIP[256];
	GetPrivateProfileStringA("NETWORK", "public ip", "0.0.0.0", szIP, sizeof(szIP), g_infFile);
	DWORD dwPublicIP = inet_addr(szIP);
	GetPrivateProfileStringA("NETWORK", "private ip", "0.0.0.0", szIP, sizeof(szIP), g_infFile);
	DWORD dwPrivateIP = inet_addr(szIP);

	if( type == 0 && dwPublicIP != 0 )
		return dwPublicIP;
	else
	if( type == 0 && dwPrivateIP != 0 )
		return dwPrivateIP;
	else
	if( type == 1 && dwPublicIP != 0 )
		return dwPublicIP;
	else
	if( type == 2 && dwPrivateIP != 0 )
		return dwPrivateIP;

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


hook_func<DWORD (__cdecl *)(char* lpszIP)> _GetDWORDIP2(SERVER, "GetDWORDIP2");
DWORD __cdecl GetDWORDIP2(char* lpszIP) // line 149
{
	return (_GetDWORDIP2)(lpszIP);

	int a1, a2, a3, a4;
	sscanf(lpszIP, "%d.%d.%d.%d", &a1, &a2, &a3, &a4);
	return BYTE(a4) << 0 | BYTE(a3) << 8 | BYTE(a2) << 16 | BYTE(a1) << 24;
}


hook_func<bool (__cdecl *)(DWORD dwIP)> _IsPrivateIPAddr(SERVER, "IsPrivateIPAddr");
bool __cdecl IsPrivateIPAddr(DWORD dwIP) // line 167
{
	return (_IsPrivateIPAddr)(dwIP);

	DWORD addr = (BYTE(dwIP >> 24) << 0) | (BYTE(dwIP >> 16) << 8) | (BYTE(dwIP >> 8) << 16) | (BYTE(dwIP >> 0) << 24);
	return( (addr >= GetDWORDIP2("10.0.0.0") && addr <= GetDWORDIP2("10.255.255.255"))
	     || (addr >= GetDWORDIP2("172.16.0.0") && addr <= GetDWORDIP2("172.31.255.255"))
	     || (addr >= GetDWORDIP2("192.168.0.0") && addr <= GetDWORDIP2("192.168.255.255")) );
}


CAcceptHandler::CAcceptHandler(void) // line 197
{
}


CAcceptHandler::~CAcceptHandler(void) // line 201
{
}
