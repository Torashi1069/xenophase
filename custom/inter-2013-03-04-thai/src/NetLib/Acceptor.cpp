#include "InterServer.h"
#include "NetLib/Acceptor.h"


DWORD GetLocalIPAddr(int type)
{
	/// [patch] config-controlled ip address
	char szPublicIP[256];
	GetPrivateProfileStringA("NETWORK", "public ip", "0.0.0.0", szPublicIP, sizeof(szPublicIP), g_infFile);
	DWORD dwPublicIP = inet_addr(szPublicIP);

	char szPrivateIP[256];
	GetPrivateProfileStringA("NETWORK", "private ip", "0.0.0.0", szPrivateIP, sizeof(szPrivateIP), g_infFile);
	DWORD dwPrivateIP = inet_addr(szPrivateIP);

	if( (type == PUBLIC_OR_PRIVATE_IP_ADDRESS || type == PUBLIC_IP_ADDRESS) && dwPublicIP != INADDR_ANY ) return dwPublicIP;
	if( (type == PUBLIC_OR_PRIVATE_IP_ADDRESS || type == PRIVATE_IP_ADDRESS) && dwPrivateIP != INADDR_ANY ) return dwPrivateIP;
	/// [/patch]

	char szName[255];
	if( gethostname(szName, sizeof(szName)) == SOCKET_ERROR )
	{
		char buf[256];
		sprintf_s(buf, countof(buf), "gethostname() fail! : %d", WSAGetLastError());
		OutputDebugStringA(buf);
		return INADDR_ANY;
	}

	PHOSTENT he = gethostbyname(szName);
	if( he == NULL )
	{
		char buf[256];
		sprintf_s(buf, countof(buf), "gethostbyname() fail! : %d", WSAGetLastError());
		OutputDebugStringA(buf);
		return INADDR_ANY;
	}

	DWORD public_ip = INADDR_ANY;
	DWORD private_ip = INADDR_ANY;

	for( int i = 0; he->h_addr_list[i] != NULL; ++i )
	{
		DWORD ip = *(DWORD*)he->h_addr_list[i];
		if( IsPrivateIPAddr(ip) )
		{
			if( private_ip == INADDR_ANY )
				private_ip = ip;
		}
		else
		{
			if( ip != INADDR_ANY && public_ip == INADDR_ANY )
				public_ip = ip;
		}
	}

	if( type == PUBLIC_OR_PRIVATE_IP_ADDRESS )
	{
		if( public_ip != INADDR_ANY )
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS)  public ip addr!!\n");
			return public_ip;
		}
		else
		if( private_ip != INADDR_ANY )
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS)  private ip addr!!\n");
			return private_ip;
		}
		else
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS)  there is not public or private ip addr\n");
			return INADDR_ANY;
		}
	}
	else
	if( type == PUBLIC_IP_ADDRESS )
	{
		if( public_ip != INADDR_ANY )
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_IP_ADDRESS)  public ip addr!!\n");
			return public_ip;
		}
		else
		{
			OutputDebugStringA("GetLocalIPAddr(PUBLIC_IP_ADDRESS)  there is not public ip addr\n");
			return INADDR_ANY;
		}
	}
	else
	if( type == PRIVATE_IP_ADDRESS )
	{
		if( private_ip != INADDR_ANY )
		{
			OutputDebugStringA("GetLocalIPAddr(PRIVATE_IP_ADDRESS)  private ip addr!!\n");
			return private_ip;
		}
		else
		{
			OutputDebugStringA("GetLocalIPAddr(PRIVATE_IP_ADDRESS)  there is not private ip addr\n");
			return INADDR_ANY;
		}
	}
	else
	{
		OutputDebugStringA("GetLocalIPAddr type invalid\n");
		return INADDR_ANY;
	}
}


DWORD GetDWORDIP2(char* lpszIP)
{
	int a1, a2, a3, a4;
	sscanf(lpszIP, "%d.%d.%d.%d", &a1, &a2, &a3, &a4);
	return BYTE(a4) << 0 | BYTE(a3) << 8 | BYTE(a2) << 16 | BYTE(a1) << 24;
}


bool IsPrivateIPAddr(DWORD dwIP)
{
	DWORD ip = BYTE(dwIP >> 0) << 24 | BYTE(dwIP >> 8) << 16 | BYTE(dwIP >> 16) << 8 | BYTE(dwIP >> 24) << 0;
	return( ( ip >= GetDWORDIP2("10.0.0.0"   ) && ip <= GetDWORDIP2("10.255.255.255" ) )
	     || ( ip >= GetDWORDIP2("172.16.0.0" ) && ip <= GetDWORDIP2("172.31.255.255" ) )
	     || ( ip >= GetDWORDIP2("192.168.0.0") && ip <= GetDWORDIP2("192.168.255.255") ) );
}


CAcceptHandler::CAcceptHandler()
{
}


CAcceptHandler::~CAcceptHandler()
{
}
