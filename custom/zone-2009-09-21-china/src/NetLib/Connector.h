#pragma once
#include "NetLib/Addr.h"


class CConnector
{
public:
	struct vtable_t
	{
		SOCKET (CConnector::* Connect)(const Addr &);
	};

	/* this+0x0 */ //const CConnector::`vftable'

	public: CConnector::CConnector(void);
	public: CConnector::~CConnector(void);
	public: virtual SOCKET CConnector::Connect(const Addr& addr);

private:
	static hook_method<SOCKET (CConnector::*)(const Addr& addr)> CConnector::_Connect;
};
