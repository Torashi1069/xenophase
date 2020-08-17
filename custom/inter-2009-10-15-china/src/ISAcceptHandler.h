#pragma once
#include "NetLib/Acceptor.h"
#include "NetLib/AsyncStream.h"
#include "NetLib/MemoryMgr.h"
#include "std/set"


class CISAcceptHandler : public CAcceptHandler
{
	struct vtable_t
	{
		int (CISAcceptHandler::* OnConnect)(SOCKET s, unsigned long ip);
		void* (CISAcceptHandler::* scalar_deleting_destructor)(unsigned int flags);
	};

	/* this+ 0 */ public: //CAcceptHandler baseclass_0;
	/* this+ 4 */ protected: CMemoryMgr<CAsyncStream> m_streamPool;
	/* this+52 */ protected: mystd::set<unsigned long> m_set;

	public: CISAcceptHandler::CISAcceptHandler(void);
	public: virtual CISAcceptHandler::~CISAcceptHandler(void);
	public: int CISAcceptHandler::Init(int streamPoolSize);
	public: CAsyncStream* CISAcceptHandler::AllocStream(void);
	public: void CISAcceptHandler::FreeStream(CAsyncStream* stream);
	public: virtual int CISAcceptHandler::OnConnect(SOCKET s, unsigned long ip);

private:
	static hook_method<int (CISAcceptHandler::*)(int streamPoolSize)> CISAcceptHandler::_Init;
	static hook_method<CAsyncStream* (CISAcceptHandler::*)(void)> CISAcceptHandler::_AllocStream;
	static hook_method<void (CISAcceptHandler::*)(CAsyncStream* stream)> CISAcceptHandler::_FreeStream;
	static hook_method<int (CISAcceptHandler::*)(SOCKET s, unsigned long ip)> CISAcceptHandler::_OnConnect;
};
