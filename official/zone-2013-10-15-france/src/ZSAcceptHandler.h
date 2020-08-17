#pragma once
#include "NetLib/Acceptor.h"
#include "NetLib/AsyncStream.h"
#include "NetLib/MemoryMgr.h"


class CZSAcceptHandler : public CAcceptHandler
{
protected:
	/* this+ 0 */ //CAcceptHandler baseclass_0;
	/* this+ 4 */ CMemoryMgr<CAsyncStream> m_streamPool;
	/* this+40 */ BOOL m_acceptable;

public:
	BOOL Init(int streamPoolSize);
	virtual BOOL OnConnect(SOCKET s, DWORD ip);

public:
	CZSAcceptHandler();
	virtual ~CZSAcceptHandler();

public:
	CAsyncStream* AllocStream();
	void FreeStream(CAsyncStream* stream);
	void SetAccpetable(BOOL b);
	BOOL GetAcceptable();
};
