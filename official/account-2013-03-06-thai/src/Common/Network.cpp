#include "Common/EnterTraceLog.h"
#include "Common/Network.h"


/// singleton instance
CNetwork* CNetwork::m_cpSelf;


CNetwork::CNetwork()
{
	m_RefCounter = 0;
	memset(&m_wsaData, 0, sizeof(m_wsaData));
}


CNetwork::~CNetwork()
{
	if( m_RefCounter != 0 )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CNetwork::m_RefCounter is not zero(%d)!!", m_RefCounter);

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


bool CNetwork::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CNetwork();
	if( m_cpSelf == NULL )
		return false;

	return true;
}


void CNetwork::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


/// @custom
CNetwork* CNetwork::GetObj()
{
	return m_cpSelf;
}


bool CNetwork::InitializeNetwork()
{
	if( WSAStartup(MAKEWORD(2,2), &m_wsaData) != 0 )
	{
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "WSAStartup() fail! gle - %d", WSAGetLastError());
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
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CNetwork::m_RefCounter is minus(%d)!!", m_RefCounter);
}


DWORD CNetwork::GetDWORDIP(const char* lpszIP) const
{
	int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
	sscanf(lpszIP, "%d.%d.%d.%d", &a1, &a2, &a3, &a4);
	return BYTE(a1) << 0 | BYTE(a2) << 8 | BYTE(a3) << 16 | BYTE(a4) << 24;
}


std::string CNetwork::GetTextIP(const DWORD in_IPaddr) const
{
	char buffer[20];
	sprintf_s(buffer, sizeof(buffer), "%d.%d.%d.%d", (BYTE)(in_IPaddr >> 0), BYTE(in_IPaddr >> 8), (BYTE)(in_IPaddr >> 16), BYTE(in_IPaddr >> 24));
	return buffer;
}


void CNetwork::GetTextIP(DWORD dwIP, char* lpszIP)
{
	sprintf(lpszIP, "%d.%d.%d.%d", BYTE(dwIP >> 0), BYTE(dwIP >> 8), BYTE(dwIP >> 16), BYTE(dwIP >> 24));
}


namespace {
std::tr1::tuple<bool,DWORD,DWORD> LoadMyIPaddr()
{
	char CurrentDirectory[260] = {};
	GetCurrentDirectoryA(sizeof(CurrentDirectory), CurrentDirectory);

	char myversionfilename[260] = "myversion.ini";
	_snprintf(myversionfilename, sizeof(myversionfilename), "%s\\myip.ini", CurrentDirectory);

	char publicIPstr[260] = {};
	GetPrivateProfileStringA("ip", "public", "xxx.xxx.xxx.xxx", publicIPstr, sizeof(publicIPstr), myversionfilename);

	char privateIPstr[260] = {};
	GetPrivateProfileStringA("ip", "private", "xxx.xxx.xxx.xxx", privateIPstr, sizeof(privateIPstr), myversionfilename);

	if( strcmp(publicIPstr, "xxx.xxx.xxx.xxx") == 0 || strcmp(privateIPstr, "xxx.xxx.xxx.xxx") == 0 )
		return std::tr1::tuple<bool,DWORD,DWORD>(false, 0, 0); // configuration options missing.

	DWORD dwPrivateIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(privateIPstr);
	DWORD dwPublicIP = CNetwork::GetObj()->CNetwork::GetDWORDIP(publicIPstr);
	return std::tr1::tuple<bool,DWORD,DWORD>(true, dwPublicIP, dwPrivateIP);
}
}; // namespace


DWORD CNetwork::GetLocalIP(bool mode)
{
	std::tr1::tuple<bool,DWORD,DWORD> ret = LoadMyIPaddr();
	if( std::tr1::get<0>(ret) == true )
	{// config file override
		if( mode == true )
			return std::tr1::get<1>(ret);
		else
			return std::tr1::get<2>(ret);
	}

	char szHostName[255] = {};
	if( gethostname(szHostName, sizeof(szHostName)) == SOCKET_ERROR )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Failed to get host name. GLE: %d", WSAGetLastError());
		return INADDR_ANY;
	}

	PHOSTENT he = gethostbyname(szHostName);
	if( he == NULL )
	{
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Failed to get PHOSTENT. GLE: %d", WSAGetLastError());
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

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Can't get requested IP. request: %d(%s)", mode, ( mode ) ? "public" : "private");
	return ip; // failed. //FIXME: unpredictable result
}


bool CNetwork::IsPrivateIP(DWORD dwIP)
{
	DWORD ip = BYTE(dwIP >> 0) << 24 | BYTE(dwIP >> 8) << 16 | BYTE(dwIP >> 16) << 8 | BYTE(dwIP >> 24) << 0;
	return( ( ip >= this->CNetwork::GetDWORDIP2("10.0.0.0"   ) && ip <= this->CNetwork::GetDWORDIP2("10.255.255.255" ) )
	     || ( ip >= this->CNetwork::GetDWORDIP2("172.16.0.0" ) && ip <= this->CNetwork::GetDWORDIP2("172.31.255.255" ) )
	     || ( ip >= this->CNetwork::GetDWORDIP2("192.168.0.0") && ip <= this->CNetwork::GetDWORDIP2("192.168.255.255") ) );
}


DWORD CNetwork::GetDWORDIP2(const char* lpszIP) const
{
	int a1, a2, a3, a4;
	sscanf(lpszIP, "%d.%d.%d.%d", &a1, &a2, &a3, &a4);
	return BYTE(a4) << 0 | BYTE(a3) << 8 | BYTE(a2) << 16 | BYTE(a1) << 24;
}
