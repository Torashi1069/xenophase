#pragma once
#include "Common/Singleton.h"


class CNetwork : public CSingleton<CNetwork>
{
private:
	/* this+  0 */ //CSingleton<CNetwork> baseclass_0;
	/* this+  0 */ WSADATA m_wsaData;
	/* this+400 */ LONG m_RefCounter;

public:
	CNetwork();
	~CNetwork();

	bool InitializeNetwork();
	void CleanupNetwork();
	void GetTextIP(DWORD dwIP, char* lpszIP);
	DWORD GetDWORDIP(char* lpszIP);
	DWORD GetDWORDIP2(char* lpszIP);
//	void GetTextIP2(DWORD dwIP, char* lpszIP);
	DWORD GetLocalIP(bool mode);
	bool IsPrivateIP(DWORD dwIP);
};
