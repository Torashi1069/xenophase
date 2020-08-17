#pragma once
#include "NetLib/Acceptor.h"
#include "NetLib/AsyncStream.h"
#include "NetLib/MemoryMgr.h"
#include "std/set"


class CMGAcceptHandler : public CAcceptHandler
{
	struct vtable_t
	{
		int (CAcceptHandler::* OnConnect)(SOCKET s, unsigned long ip);
	};

	/* this+ 0 */ public: //CAcceptHandler baseclass_0;
	/* this+ 4 */ protected: CMemoryMgr<CAsyncStream> m_streamPool;
	/* this+52 */ protected: mystd::set<unsigned long> m_set;

	public: CMGAcceptHandler::CMGAcceptHandler(void);
	public: CMGAcceptHandler::~CMGAcceptHandler(void);
	public: int CMGAcceptHandler::Init(int streamPoolSize);
	public: CAsyncStream* CMGAcceptHandler::AllocStream(void);
	public: void CMGAcceptHandler::FreeStream(CAsyncStream* stream);
	public: virtual int CMGAcceptHandler::OnConnect(SOCKET s, unsigned long ip);

private:
	static hook_method<int (CMGAcceptHandler::*)(int streamPoolSize)> CMGAcceptHandler::_Init;
	static hook_method<CAsyncStream* (CMGAcceptHandler::*)(void)> CMGAcceptHandler::_AllocStream;
	static hook_method<void (CMGAcceptHandler::*)(CAsyncStream* stream)> CMGAcceptHandler::_FreeStream;
	static hook_method<int (CMGAcceptHandler::*)(SOCKET s, unsigned long ip)> CMGAcceptHandler::_OnConnect;
};
