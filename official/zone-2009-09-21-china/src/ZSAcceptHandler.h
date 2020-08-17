#pragma once
#include "Netlib/Acceptor.h"
#include "NetLib/AsyncStream.h"
#include "NetLib/MemoryMgr.h"


class CZSAcceptHandler : public CAcceptHandler
{
public:
	struct vtable_t // const CZSAcceptHandler::`vftable'
	{
		int (CZSAcceptHandler::* OnConnect)(unsigned int s, unsigned long ip);
		void* (CZSAcceptHandler::* scalar_deleting_destructor)(unsigned int flags);
	};

	/* this+ 0 */ public: //CAcceptHandler baseclass_0;
	/* this+ 4 */ protected: CMemoryMgr<CAsyncStream> m_streamPool;
	/* this+52 */ protected: int m_acceptable;

	public: CZSAcceptHandler::CZSAcceptHandler(void);
	public: virtual CZSAcceptHandler::~CZSAcceptHandler(void);
	public: int CZSAcceptHandler::Init(int streamPoolSize);
	public: virtual int CZSAcceptHandler::OnConnect(unsigned int s, unsigned long ip);
	public: CAsyncStream* CZSAcceptHandler::AllocStream(void);
	public: void CZSAcceptHandler::FreeStream(CAsyncStream* stream);
	public: void CZSAcceptHandler::SetAccpetable(int acceptable);
	public: int CZSAcceptHandler::GetAcceptable(void);

private:
	static hook_method<int (CZSAcceptHandler::*)(int streamPoolSize)> CZSAcceptHandler::_Init;
	static hook_method<int (CZSAcceptHandler::*)(unsigned int s, unsigned long ip)> CZSAcceptHandler::_OnConnect;
	static hook_method<CAsyncStream* (CZSAcceptHandler::*)(void)> CZSAcceptHandler::_AllocStream;
	static hook_method<void (CZSAcceptHandler::*)(CAsyncStream* stream)> CZSAcceptHandler::_FreeStream;
	static hook_method<void (CZSAcceptHandler::*)(int acceptable)> CZSAcceptHandler::_SetAccpetable;
	static hook_method<int (CZSAcceptHandler::*)(void)> CZSAcceptHandler::_GetAcceptable;
};
