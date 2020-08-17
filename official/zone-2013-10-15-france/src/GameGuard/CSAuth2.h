#pragma once
#include "GameGuard/ggsrv.h"


class CCSAuth2
{
public:
	CCSAuth2();
	~CCSAuth2();

protected:
	PGG_AUTH_PROTOCOL m_pProtocol;
	DWORD m_bPrtcRef;
	DWORD m_dwUserFlag;

public:
	GG_AUTH_DATA m_AuthQuery;
	GG_AUTH_DATA m_AuthAnswer;

public:
	void Init();
	DWORD GetAuthQuery();
	DWORD CheckAuthAnswer();
};
