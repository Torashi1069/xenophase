#include "Common/Network.h"
#include "Common/Reporter.h"


/// singleton instance
static CNetwork CNetworkInstance;
CNetwork* CSingleton<CNetwork>::ms_Singleton;


CNetwork::CNetwork()
{
	m_RefCounter = 0;
	memset(&m_wsaData, 0, sizeof(m_wsaData));
}


CNetwork::~CNetwork()
{
	if( m_RefCounter != 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("CNetwork::m_RefCounter is not zero(%d)!!\n", m_RefCounter);

		if( m_RefCounter > 0 )
		{
			do
			{
				--m_RefCounter;
				WSACleanup();
			}
			while( m_RefCounter != 0 );

			--m_RefCounter;
		}
	}
}


bool CNetwork::InitializeNetwork()
{
	if( WSAStartup(MAKEWORD(2,2), &m_wsaData) != 0 )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("WSAStartup() fail! gle - %d", WSAGetLastError());
		return false;
	}

	InterlockedIncrement(&m_RefCounter);
	return true;
}


void CNetwork::CleanupNetwork()
{
	WSACleanup();
	InterlockedDecrement(&m_RefCounter);

	if( m_RefCounter < 0 )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("CNetwork::m_RefCounter is minus(%d)!!\n", m_RefCounter);
}


DWORD CNetwork::GetDWORDIP(char* lpszIP)
{
	int a1, a2, a3, a4;
	sscanf(lpszIP, "%d.%d.%d.%d", &a1, &a2, &a3, &a4);
	return BYTE(a1) << 0 | BYTE(a2) << 8 | BYTE(a3) << 16 | BYTE(a4) << 24;
}


void CNetwork::GetTextIP(DWORD dwIP, char* lpszIP)
{
	sprintf(lpszIP, "%d.%d.%d.%d", BYTE(dwIP >> 0), BYTE(dwIP >> 8), BYTE(dwIP >> 16), BYTE(dwIP >> 24));
}


DWORD CNetwork::GetLocalIP(bool mode)
{
	char szHostName[255] = {};
	if( gethostname(szHostName, sizeof(szHostName)) == SOCKET_ERROR )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Failed to get host name. GLE: %d", WSAGetLastError());
		return INADDR_ANY;
	}

	PHOSTENT he = gethostbyname(szHostName);
	if( he == NULL )
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Failed to get PHOSTENT. GLE: %d", WSAGetLastError());
		return INADDR_ANY;
	}

	in_addr** addr_list = (in_addr**)he->h_addr_list;
	DWORD ip = INADDR_ANY;

	for( int i = 0; addr_list[i] != NULL; ++i )
	{
		ip = addr_list[i]->s_addr;
		if( this->CNetwork::IsPrivateIP(ip) )
		{// private
			if( mode == false )
				return ip; // found.
		}
		else
		{// public
			if( mode == true )
				return ip; // found.
		}
	}

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Can't get requested IP. request: %d(%s)", mode, ( mode ) ? "public" : "private");
	return ip; // failed. //FIXME: unpredictable result
}


bool CNetwork::IsPrivateIP(DWORD dwIP)
{
	DWORD ip = BYTE(dwIP >> 0) << 24 | BYTE(dwIP >> 8) << 16 | BYTE(dwIP >> 16) << 8 | BYTE(dwIP >> 24) << 0;
	return( ( ip >= this->CNetwork::GetDWORDIP2("10.0.0.0"   ) && ip <= this->CNetwork::GetDWORDIP2("10.255.255.255" ) )
	     || ( ip >= this->CNetwork::GetDWORDIP2("172.16.0.0" ) && ip <= this->CNetwork::GetDWORDIP2("172.31.255.255" ) )
	     || ( ip >= this->CNetwork::GetDWORDIP2("192.168.0.0") && ip <= this->CNetwork::GetDWORDIP2("192.168.255.255") ) );
}


DWORD CNetwork::GetDWORDIP2(char* lpszIP)
{
	int a1, a2, a3, a4;
	sscanf(lpszIP, "%d.%d.%d.%d", &a1, &a2, &a3, &a4);
	return BYTE(a4) << 0 | BYTE(a3) << 8 | BYTE(a2) << 16 | BYTE(a1) << 24;
}
